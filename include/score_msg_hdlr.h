#ifndef SCORE_MSG_HDLR_H
#define SCORE_MSG_HDLR_H

#include "manager.h"
#include "score_msg_type.h"

class ScoreMsgHandler {
public:
    // Delete copy constructor and assignment operator
    ScoreMsgHandler(const ScoreMsgHandler&) = delete;
    ScoreMsgHandler& operator=(const ScoreMsgHandler&) = delete;

    // Public static method to get the single instance
    static ScoreMsgHandler& getInstance();

    bool handleAddParticipant(ScoreMsg* pMsg);
    bool handleDeleteParticipant(ScoreMsg* pMsg);
    bool handleUpdateParticipant(ScoreMsg* pMsg);
    bool handleFindParticipantById(ScoreMsg* pMsg);
    bool handleFindParticipantByName(ScoreMsg* pMsg);
    bool handleListAllParticipants(ScoreMsg* pMsg);
    bool handleClear(ScoreMsg* pMsg);

    bool handleMsg(ScoreMsg* pMsg);

    bool sendRsp(ScoreMsg* pMsg);

private:
    // Private constructor to enforce singleton
    ScoreMsgHandler() : manager(ScoreManager::getInstance()) {}

    ScoreManager& manager;
};

#endif // SCORE_MSG_HDLR_H