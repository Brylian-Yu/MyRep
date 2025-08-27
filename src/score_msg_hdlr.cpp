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

#include "score_msg_hdlr.h"

/*
 * @brief Get the single instance of the ScoreMsgHandler.
 * @return Reference to the ScoreMsgHandler instance.
 */
ScoreMsgHandler& ScoreMsgHandler::getInstance()
{
    static ScoreMsgHandler instance;
    return instance;
}

/*
 * @brief Handle adding a participant.
 * @param pMsg The message containing participant data.
 * @return True on success, false on failure.
 */
bool ScoreMsgHandler::handleAddParticipant(ScoreMsg* pMsg)
{
    if (pMsg == nullptr || pMsg->body.pBody == nullptr)
    {
        return false;
    }

    auto* pAddParticipantReq = static_cast<ScoreMsgAddParticipantReq*>(pMsg->body.pBody);
    bool ret = manager.addParticipant(pAddParticipantReq->id, pAddParticipantReq->name, pAddParticipantReq->score);
    
    ScoreMsg* pRsp = new ScoreMsg();
    if (pRsp == nullptr)
    {
        return false;
    }
    pRsp->hdr.type = ADD_PARTICIPANT_RSP;
    pRsp->hdr.bodyLen = sizeof(ScoreMsgAddParticipantRsp);
    pRsp->body.pBody = new ScoreMsgAddParticipantRsp();
    if (pRsp->body.pBody == nullptr)
    {
        delete pRsp;
        return false;
    }
    static_cast<ScoreMsgAddParticipantRsp*>(pRsp->body.pBody)->ret = ret;

    if (!sendRsp(pRsp))
    {
        return false;
    }

    return true;
}

/*
 * @brief Handle deleting a participant.
 * @param pMsg The message containing the participant ID.
 * @return True on success, false on failure.
 */
bool ScoreMsgHandler::handleDeleteParticipant(ScoreMsg* pMsg)
{
    if (pMsg == nullptr || pMsg->body.pBody == nullptr)
    {
        return false;
    }

    auto* pDeleteParticipantReq = static_cast<ScoreMsgDeleteParticipantReq*>(pMsg->body.pBody);
    bool ret = manager.deleteParticipant(pDeleteParticipantReq->id);
    
    ScoreMsg* pRsp = new ScoreMsg();
    if (pRsp == nullptr)
    {
        return false;
    }
    pRsp->hdr.type = DELETE_PARTICIPANT_RSP;
    pRsp->hdr.bodyLen = sizeof(ScoreMsgDeleteParticipantRsp);
    pRsp->body.pBody = new ScoreMsgDeleteParticipantRsp();
    if (pRsp->body.pBody == nullptr)
    {
        delete pRsp;
        return false;
    }
    static_cast<ScoreMsgDeleteParticipantRsp*>(pRsp->body.pBody)->ret = ret;

    if (!sendRsp(pRsp))
    {
        return false;
    }

    return true;
}

/*
 * @brief Handle updating a participant's information.
 * @param pMsg The message containing updated participant data.
 * @return True on success, false on failure.
 */
bool ScoreMsgHandler::handleUpdateParticipant(ScoreMsg* pMsg)
{
    if (pMsg == nullptr || pMsg->body.pBody == nullptr)
    {
        return false;
    }

    auto* pUpdateParticipantReq = static_cast<ScoreMsgUpdateParticipantReq*>(pMsg->body.pBody);
    bool ret = manager.updateParticipant(pUpdateParticipantReq->id, pUpdateParticipantReq->name, pUpdateParticipantReq->score);
    
    ScoreMsg* pRsp = new ScoreMsg();
    if (pRsp == nullptr)
    { 
        return false;
    }
    pRsp->hdr.type = UPDATE_PARTICIPANT_RSP;
    pRsp->hdr.bodyLen = sizeof(ScoreMsgUpdateParticipantRsp);
    pRsp->body.pBody = new ScoreMsgUpdateParticipantRsp();
    if (pRsp->body.pBody == nullptr)
    {
        delete pRsp;
        return false;
    }
    static_cast<ScoreMsgUpdateParticipantRsp*>(pRsp->body.pBody)->ret = ret;

    if (!sendRsp(pRsp))
    {
        return false;
    }

    return true;
}

/*
 * @brief Handle finding a participant by ID.
 * @param pMsg The message containing the participant ID.
 * @return True on success, false on failure.
 */
bool ScoreMsgHandler::handleFindParticipantById(ScoreMsg* pMsg)
{
    if (pMsg == nullptr || pMsg->body.pBody == nullptr)
    {
        return false;
    }

    auto* pFindParticipantByIdReq = static_cast<ScoreMsgFindParticipantByIdReq*>(pMsg->body.pBody);
    Participant* pParticipant = manager.findParticipantById(pFindParticipantByIdReq->id);
    bool ret = (pParticipant != nullptr);

    ScoreMsg* pRsp = new ScoreMsg();
    if (pRsp == nullptr)
    {
        return false;
    }
    pRsp->hdr.type = FIND_PARTICIPANT_BY_ID_RSP;
    pRsp->hdr.bodyLen = sizeof(ScoreMsgFindParticipantByIdRsp);
    pRsp->body.pBody = new ScoreMsgFindParticipantByIdRsp();
    if (pRsp->body.pBody == nullptr)
    {
        delete pRsp;
        return false;
    }
    
    auto* rspBody = static_cast<ScoreMsgFindParticipantByIdRsp*>(pRsp->body.pBody);
    rspBody->ret = ret;
    if (ret)
    {
        rspBody->id = pParticipant->id;
        rspBody->nameLen = pParticipant->name.length();
        rspBody->name = pParticipant->name;
        rspBody->score = pParticipant->score;
    }

    if (!sendRsp(pRsp))
    {
        return false;
    }

    return true;
}

/*
 * @brief Handle finding a participant by name.
 * @param pMsg The message containing the participant name.
 * @return True on success, false on failure.
 */
bool ScoreMsgHandler::handleFindParticipantByName(ScoreMsg* pMsg)
{
    if (pMsg == nullptr || pMsg->body.pBody == nullptr)
    {
        return false;
    }

    auto* pFindParticipantByNameReq = static_cast<ScoreMsgFindParticipantByNameReq*>(pMsg->body.pBody);
    Participant* pParticipant = manager.findParticipantByName(pFindParticipantByNameReq->name);
    bool ret = (pParticipant != nullptr);

    ScoreMsg* pRsp = new ScoreMsg();
    if (pRsp == nullptr)
    {
        return false;
    }
    pRsp->hdr.type = FIND_PARTICIPANT_BY_NAME_RSP;
    pRsp->hdr.bodyLen = sizeof(ScoreMsgFindParticipantByNameRsp);
    pRsp->body.pBody = new ScoreMsgFindParticipantByNameRsp();
    if (pRsp->body.pBody == nullptr)
    {
        delete pRsp;
        return false;
    }
    
    auto* rspBody = static_cast<ScoreMsgFindParticipantByNameRsp*>(pRsp->body.pBody);
    rspBody->ret = ret;
    if (ret)
    {
        rspBody->id = pParticipant->id;
        rspBody->nameLen = pParticipant->name.length();
        rspBody->name = pParticipant->name;
        rspBody->score = pParticipant->score;
    }

    if (!sendRsp(pRsp))
    {
        return false;
    }

    return true;
}

/*
 * @brief Handle listing all participants.
 * @param pMsg The message to be populated with the participant list.
 * @return True on success, false on failure.
 */
bool ScoreMsgHandler::handleListAllParticipants(ScoreMsg* pMsg)
{
    (void)pMsg; /* Unused parameter. */
    
    const auto& participants = manager.listAllParticipants();
    
    ScoreMsg* pRsp = new ScoreMsg();
    if (pRsp == nullptr)
    {
        return false;
    }
    pRsp->hdr.type = LIST_ALL_PARTICIPANTS_RSP;
    pRsp->hdr.bodyLen = sizeof(ScoreMsgListAllParticipantsRsp);
    pRsp->body.pBody = new ScoreMsgListAllParticipantsRsp();
    if (pRsp->body.pBody == nullptr)
    {
        delete pRsp;
        return false;
    }
    
    auto* rspBody = static_cast<ScoreMsgListAllParticipantsRsp*>(pRsp->body.pBody);
    rspBody->ret = true;
    rspBody->participants = participants;

    if (!sendRsp(pRsp))
    {
        return false;
    }

    return true;
}

/*
 * @brief Handle clearing all participants.
 * @param pMsg The message object.
 * @return True on success, false on failure.
 */
bool ScoreMsgHandler::handleClear(ScoreMsg* pMsg)
{
    (void)pMsg; /* Unused parameter. */
    manager.clear();

    ScoreMsg* pRsp = new ScoreMsg();
    if (pRsp == nullptr)
    {
        return false;
    }
    pRsp->hdr.type = CLEAR_RSP;
    pRsp->hdr.bodyLen = sizeof(ScoreMsgClearRsp);
    pRsp->body.pBody = new ScoreMsgClearRsp();
    if (pRsp->body.pBody == nullptr)
    {
        delete pRsp;
        return false;
    }
    static_cast<ScoreMsgClearRsp*>(pRsp->body.pBody)->ret = true;

    if (!sendRsp(pRsp))
    {
        return false;
    }

    return true;
}

/*
 * @brief Generic message handler.
 * @param pMsg The message to handle.
 * @return True on success, false on failure.
 */
bool ScoreMsgHandler::handleMsg(ScoreMsg* pMsg)
{
    if (pMsg == nullptr)
    {
        return false;
    }

    switch (pMsg->hdr.type)
    {
        case ADD_PARTICIPANT_REQ:
            return handleAddParticipant(pMsg);
        case DELETE_PARTICIPANT_REQ:
            return handleDeleteParticipant(pMsg);
        case UPDATE_PARTICIPANT_REQ:
            return handleUpdateParticipant(pMsg);
        case FIND_PARTICIPANT_BY_ID_REQ:
            return handleFindParticipantById(pMsg);
        case FIND_PARTICIPANT_BY_NAME_REQ:
            return handleFindParticipantByName(pMsg);
        case LIST_ALL_PARTICIPANTS_REQ:
            return handleListAllParticipants(pMsg);
        case CLEAR_REQ:
            return handleClear(pMsg);
        default:
            return false;
    }
}

/*
 * @brief Send a response message.
 * @param pMsg The message to send.
 * @return True on success, false on failure.
 */
bool ScoreMsgHandler::sendRsp(ScoreMsg* pMsg)
{
    /* ToDo... implement sendRsp. */

    if (pMsg == nullptr)
    {
        return true; /* Nothing to do. */
    }

    if (pMsg->body.pBody != nullptr)
    {
        delete static_cast<char*>(pMsg->body.pBody);
    }

    delete pMsg;

    return true;
}
