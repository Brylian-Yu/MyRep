#include "include/score_proc.h"
#include "include/score_msg_hdlr.h"
#include <thread>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <vector>
#include "include/score_msg_serializer.h"
#include <cstring> // For memcpy

// Thread-safe method to push a message to the queue
void ScoreProc::pushToQueue(ScoreMsg* msg) {
    {
        std::lock_guard<std::mutex> lock(mtx);
        if (!shutdown_.load()) {
            msgQueue.push(msg);
        }
    }
    cv.notify_one();
}

// Thread-safe method to pop a message from the queue
ScoreMsg* ScoreProc::popFromQueue() {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [this] { return !msgQueue.empty() || shutdown_.load(); });
    
    if (shutdown_.load() && msgQueue.empty()) {
        return nullptr; // Signal shutdown
    }
    
    ScoreMsg* msg = msgQueue.front();
    msgQueue.pop();
    return msg;
}

// Consumer thread function
void poolMsg(ScoreProc* pScoreProc) {
    while (!pScoreProc->isShutdown()) {
        ScoreMsg* pMsg = pScoreProc->popFromQueue();
        if (pMsg) {
            ScoreMsgHandler::getInstance().handleMsg(pMsg);
        } else {
            // nullptr indicates shutdown
            break;
        }
    }
}

void ScoreProc::shutdown() {
    shutdown_.store(true);
    cv.notify_all(); // Wake up all waiting threads
}

void ScoreProc::run() {

    // Start two consumer threads
    std::thread t1(poolMsg, this);
    std::thread t2(poolMsg, this);
    t1.detach();
    t2.detach();

    // Create TCP socket to listen for client requests (Producer)
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(5036);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    // Producer loop: receive messages and push them to the queue
    while (true) {
        ScoreMsgHdr hdr;
        ssize_t bytes_read = recv(new_socket, &hdr, sizeof(ScoreMsgHdr), MSG_WAITALL);

        if (bytes_read <= 0) {
            if (bytes_read == 0) {
                std::cout << "Client disconnected." << std::endl;
            } else {
                perror("recv header failed");
            }
            break;
        }

        if (bytes_read != sizeof(ScoreMsgHdr)) {
            std::cerr << "Received incomplete header." << std::endl;
            continue;
        }

        std::vector<uint8_t> buffer(sizeof(ScoreMsgHdr) + hdr.bodyLen);
        memcpy(buffer.data(), &hdr, sizeof(ScoreMsgHdr));

        if (hdr.bodyLen > 0) {
            bytes_read = recv(new_socket, buffer.data() + sizeof(ScoreMsgHdr), hdr.bodyLen, MSG_WAITALL);
            if (bytes_read <= 0) {
                perror("recv body failed or connection closed");
                break;
            }
            if (static_cast<size_t>(bytes_read) != hdr.bodyLen) {
                std::cerr << "Received incomplete body." << std::endl;
                continue;
            }
        }
        
        ScoreMsg* pMsg = ScoreMsgSerializer::deserialize(buffer.data(), buffer.size());
        if (pMsg) {
            pushToQueue(pMsg);
        } else {
            std::cerr << "Failed to deserialize message." << std::endl;
        }
    }

    close(new_socket);
    close(server_fd);

}
