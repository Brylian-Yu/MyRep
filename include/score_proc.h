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

#ifndef SCORE_PROC_H
#define SCORE_PROC_H

#include <queue>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include "score_msg_hdlr.h"

class ScoreProc {
public:
    /*
     * @brief Constructor for ScoreProc.
     */
    ScoreProc();
    
    /*
     * @brief Runs the message processing loop.
     */
    void run();

    /*
     * @brief Shuts down the message processing loop.
     */
    void shutdown();

    /*
     * @brief Pushes a message to the processing queue.
     * @param msg The message to push.
     */
    void pushToQueue(ScoreMsg* msg);

    /*
     * @brief Pops a message from the processing queue.
     * @return A pointer to the message, or nullptr if the queue is empty and shutting down.
     */
    ScoreMsg* popFromQueue();

    /*
     * @brief Checks if the processor is shut down.
     * @return True if shut down, false otherwise.
     */
    bool isShutdown() const;

private:
    std::queue<ScoreMsg*> msgQueue; /* The message queue. */
    std::mutex mtx;                 /* Mutex for thread safety. */
    std::condition_variable cv;     /* Condition variable for the message queue. */
    std::atomic<bool> shutdown_;    /* Atomic flag to signal shutdown. */
};

#endif // SCORE_PROC_H
