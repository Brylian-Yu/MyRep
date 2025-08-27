#ifndef SCORE_PROC_H
#define SCORE_PROC_H

#include <queue>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include "score_msg_hdlr.h"

class ScoreProc {
public:
    ScoreProc() : shutdown_(false) {}
    
    void run();
    void shutdown();
    void pushToQueue(ScoreMsg* msg);
    ScoreMsg* popFromQueue();
    bool isShutdown() const { return shutdown_.load(); }

private:
    std::queue<ScoreMsg*> msgQueue;
    std::mutex mtx;
    std::condition_variable cv;
    std::atomic<bool> shutdown_;
};

#endif // SCORE_PROC_H
