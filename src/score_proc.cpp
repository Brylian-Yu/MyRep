/*
 * Copyright (c) 2025 SerComm Corporation. All Rights Reserved.
 *
 * SerComm Corporation reserves the right to make changes to this document
 * without notice. SerComm Corporation makes no warranty, representation or
 * guarantee regarding the suitability of its products for any particular
 * purpose.
 *
 * SerComm Corporation assumes no liability arising out of the application or
 * use of any product or circuit. 
 *
 * SerComm Corporation specifically disclaims any and all liability, including
 * without limitation consequential or incidental damages; neither does it convey
 * any license under its patent rights, nor the rights of others.
 */

#include "score_proc.h"
#include "score_msg_hdlr.h"
#include "score_msg_serializer.h"
#include <thread>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <vector>
#include <cstring> /* For memcpy. */

namespace
{
    const int SERVER_PORT = 5036;
    const int MAX_LISTEN_QUEUE = 5;
}

/*
 * @brief Constructor for ScoreProc.
 */
ScoreProc::ScoreProc()
{
    shutdown_.store(false);
}

/*
 * @brief Checks if the processor is shut down.
 * @return True if shut down, false otherwise.
 */
bool ScoreProc::isShutdown() const
{
    return shutdown_.load();
}

/*
 * @brief Pushes a message to the processing queue.
 * @param msg The message to push.
 */
void ScoreProc::pushToQueue(ScoreMsg* msg)
{
    {
        std::lock_guard<std::mutex> lock(mtx);
        if (!shutdown_.load())
        {
            msgQueue.push(msg);
        }
    }
    cv.notify_one();
}

/*
 * @brief Pops a message from the processing queue.
 * @return A pointer to the message, or nullptr if the queue is empty and shutting down.
 */
ScoreMsg* ScoreProc::popFromQueue()
{
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [this] { return !msgQueue.empty() || shutdown_.load(); });
    
    if (shutdown_.load() && msgQueue.empty())
    {
        return nullptr; /* Signal shutdown. */
    }
    
    ScoreMsg* msg = msgQueue.front();
    msgQueue.pop();
    return msg;
}

/*
 * @brief The main function for consumer threads to process messages.
 * @param pScoreProc A pointer to the ScoreProc instance.
 */
void poolMsg(ScoreProc* pScoreProc)
{
    while (!pScoreProc->isShutdown())
    {
        ScoreMsg* pMsg = pScoreProc->popFromQueue();
        if (pMsg)
        {
            ScoreMsgHandler::getInstance().handleMsg(pMsg);
        }
        else
        {
            /* nullptr indicates shutdown. */
            break;
        }
    }
}

/*
 * @brief Shuts down the message processing loop.
 */
void ScoreProc::shutdown()
{
    shutdown_.store(true);
    cv.notify_all(); /* Wake up all waiting threads. */
}

/*
 * @brief Runs the main server loop, accepting connections and processing messages.
 */
void ScoreProc::run()
{
    /* Start two consumer threads. */
    std::thread t1(poolMsg, this);
    std::thread t2(poolMsg, this);

    /* Create TCP socket to listen for client requests (Producer). */
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        return;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(SERVER_PORT);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0)
    {
        perror("bind failed");
        close(server_fd);
        return;
    }
    if (listen(server_fd, MAX_LISTEN_QUEUE) < 0)
    {
        perror("listen");
        close(server_fd);
        return;
    }
    if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0)
    {
        perror("accept");
        close(server_fd);
        return;
    }

    /* Producer loop: receive messages and push them to the queue. */
    while (!isShutdown())
    {
        ScoreMsgHdr hdr;
        ssize_t bytes_read = recv(new_socket, &hdr, sizeof(ScoreMsgHdr), MSG_WAITALL);

        if (bytes_read <= 0)
        {
            if (bytes_read == 0)
            {
                std::cout << "Client disconnected." << std::endl;
            }
            else
            {
                perror("recv header failed");
            }
            break;
        }

        if (bytes_read != sizeof(ScoreMsgHdr))
        {
            std::cerr << "Received incomplete header." << std::endl;
            continue;
        }

        std::vector<uint8_t> buffer(sizeof(ScoreMsgHdr) + hdr.bodyLen);
        memcpy(buffer.data(), &hdr, sizeof(ScoreMsgHdr));

        if (hdr.bodyLen > 0)
        {
            bytes_read = recv(new_socket, buffer.data() + sizeof(ScoreMsgHdr), hdr.bodyLen, MSG_WAITALL);
            if (bytes_read <= 0)
            {
                perror("recv body failed or connection closed");
                break;
            }
            if (static_cast<size_t>(bytes_read) != hdr.bodyLen)
            {
                std::cerr << "Received incomplete body." << std::endl;
                continue;
            }
        }
        
        ScoreMsg* pMsg = ScoreMsgSerializer::deserialize(buffer.data(), buffer.size());
        if (pMsg)
        {
            pushToQueue(pMsg);
        }
        else
        {
            std::cerr << "Failed to deserialize message." << std::endl;
        }
    }

    /* Clean up resources. */
    shutdown();
    t1.join();
    t2.join();
    close(new_socket);
    close(server_fd);
}
