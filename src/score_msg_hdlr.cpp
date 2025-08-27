#include "include/score_msg_hdlr.h"

ScoreMsgHandler& ScoreMsgHandler::getInstance() {
    static ScoreMsgHandler instance;
    return instance;
}

bool ScoreMsgHandler::handleAddParticipant(ScoreMsg* pMsg) {

    if(pMsg == nullptr || pMsg->body.pBody == nullptr){
        return false;
    }

    ScoreMsgAddParticipantReq* pAddParticipantReq = (ScoreMsgAddParticipantReq*)pMsg->body.pBody;

    bool ret = manager.addParticipant(pAddParticipantReq->id, pAddParticipantReq->name, pAddParticipantReq->score);
    
    ScoreMsg* pRsp = new ScoreMsg;
    if(pRsp == nullptr){
        return false;
    }
    pRsp->hdr.type = ADD_PARTICIPANT_RSP;
    pRsp->hdr.bodyLen = sizeof(ScoreMsgAddParticipantRsp);
    pRsp->body.pBody = new ScoreMsgAddParticipantRsp;
    if(pRsp->body.pBody == nullptr){
        delete pRsp;
        return false;
    }
    ((ScoreMsgAddParticipantRsp*)pRsp->body.pBody)->ret = ret;

    if(!sendRsp(pRsp)) {
        // Memory cleanup is handled in sendRsp, but if it fails we need to clean up
        delete static_cast<ScoreMsgAddParticipantRsp*>(pRsp->body.pBody);
        delete pRsp;
        return false;
    }

    return true;
}

bool ScoreMsgHandler::handleDeleteParticipant(ScoreMsg* pMsg) {

    if(pMsg == nullptr || pMsg->body.pBody == nullptr){
        return false;
    }

    ScoreMsgDeleteParticipantReq* pDeleteParticipantReq = (ScoreMsgDeleteParticipantReq*)pMsg->body.pBody;

    bool ret = manager.deleteParticipant(pDeleteParticipantReq->id);
    
    ScoreMsg* pRsp = new ScoreMsg;
    if(pRsp == nullptr){
        return false;
    }
    pRsp->hdr.type = DELETE_PARTICIPANT_RSP;
    pRsp->hdr.bodyLen = sizeof(ScoreMsgDeleteParticipantRsp);
    pRsp->body.pBody = new ScoreMsgDeleteParticipantRsp;
    if(pRsp->body.pBody == nullptr){
        delete pRsp;
        return false;
    }
    ((ScoreMsgDeleteParticipantRsp*)pRsp->body.pBody)->ret = ret;

    if(!sendRsp(pRsp)) {
        delete static_cast<ScoreMsgDeleteParticipantRsp*>(pRsp->body.pBody);
        delete pRsp;
        return false;
    }

    return true;
}

bool ScoreMsgHandler::handleUpdateParticipant(ScoreMsg* pMsg) {

    if(pMsg == nullptr || pMsg->body.pBody == nullptr){
        return false;
    }

    ScoreMsgUpdateParticipantReq* pUpdateParticipantReq = (ScoreMsgUpdateParticipantReq*)pMsg->body.pBody;

    bool ret = manager.updateParticipant(pUpdateParticipantReq->id, pUpdateParticipantReq->name, pUpdateParticipantReq->score);
    
    ScoreMsg* pRsp = new ScoreMsg;
    if(pRsp == nullptr){
        return false;
    }
    pRsp->hdr.type = UPDATE_PARTICIPANT_RSP;
    pRsp->hdr.bodyLen = sizeof(ScoreMsgUpdateParticipantRsp);
    pRsp->body.pBody = new ScoreMsgUpdateParticipantRsp;
    if(pRsp->body.pBody == nullptr){
        delete pRsp;
        return false;
    }
    ((ScoreMsgUpdateParticipantRsp*)pRsp->body.pBody)->ret = ret;

    if(!sendRsp(pRsp)) {
        delete static_cast<ScoreMsgUpdateParticipantRsp*>(pRsp->body.pBody);
        delete pRsp;
        return false;
    }

    return true;
}

bool ScoreMsgHandler::handleFindParticipantById(ScoreMsg* pMsg) {

    if(pMsg == nullptr || pMsg->body.pBody == nullptr){
        return false;
    }

    ScoreMsgFindParticipantByIdReq* pFindParticipantByIdReq = (ScoreMsgFindParticipantByIdReq*)pMsg->body.pBody;

    Participant* pParticipant = manager.findParticipantById(pFindParticipantByIdReq->id);
    bool ret = (pParticipant != nullptr);

    ScoreMsg* pRsp = new ScoreMsg;
    if(pRsp == nullptr){
        return false;
    }
    pRsp->hdr.type = FIND_PARTICIPANT_BY_ID_RSP;
    pRsp->hdr.bodyLen = sizeof(ScoreMsgFindParticipantByIdRsp);
    pRsp->body.pBody = new ScoreMsgFindParticipantByIdRsp;
    if(pRsp->body.pBody == nullptr){
        delete pRsp;
        return false;
    }
    
    auto* rspBody = static_cast<ScoreMsgFindParticipantByIdRsp*>(pRsp->body.pBody);
    rspBody->ret = ret;
    if(ret){
        rspBody->id = pParticipant->id;
        rspBody->nameLen = pParticipant->name.length();
        rspBody->name = pParticipant->name;
        rspBody->score = pParticipant->score;
    }

    if(!sendRsp(pRsp)) {
        delete rspBody;
        delete pRsp;
        return false;
    }

    return true;
}

bool ScoreMsgHandler::handleFindParticipantByName(ScoreMsg* pMsg) {
    if(pMsg == nullptr || pMsg->body.pBody == nullptr){
        return false;
    }

    ScoreMsgFindParticipantByNameReq* pFindParticipantByNameReq = (ScoreMsgFindParticipantByNameReq*)pMsg->body.pBody;

    Participant* pParticipant = manager.findParticipantByName(pFindParticipantByNameReq->name);
    bool ret = (pParticipant != nullptr);

    ScoreMsg* pRsp = new ScoreMsg;
    if(pRsp == nullptr){
        return false;
    }
    pRsp->hdr.type = FIND_PARTICIPANT_BY_NAME_RSP;
    pRsp->hdr.bodyLen = sizeof(ScoreMsgFindParticipantByNameRsp);
    pRsp->body.pBody = new ScoreMsgFindParticipantByNameRsp;
    if(pRsp->body.pBody == nullptr){
        delete pRsp;
        return false;
    }
    
    auto* rspBody = static_cast<ScoreMsgFindParticipantByNameRsp*>(pRsp->body.pBody);
    rspBody->ret = ret;
    if(ret){
        rspBody->id = pParticipant->id;
        rspBody->nameLen = pParticipant->name.length();
        rspBody->name = pParticipant->name;
        rspBody->score = pParticipant->score;
    }

    if(!sendRsp(pRsp)) {
        delete rspBody;
        delete pRsp;
        return false;
    }

    return true;
}

bool ScoreMsgHandler::handleListAllParticipants(ScoreMsg* pMsg) {
    (void)pMsg; // Unused parameter
    
    const auto& participants = manager.listAllParticipants();
    
    ScoreMsg* pRsp = new ScoreMsg;
    if(pRsp == nullptr){
        return false;
    }
    pRsp->hdr.type = LIST_ALL_PARTICIPANTS_RSP;
    pRsp->hdr.bodyLen = sizeof(ScoreMsgListAllParticipantsRsp);
    pRsp->body.pBody = new ScoreMsgListAllParticipantsRsp;
    if(pRsp->body.pBody == nullptr){
        delete pRsp;
        return false;
    }
    
    auto* rspBody = static_cast<ScoreMsgListAllParticipantsRsp*>(pRsp->body.pBody);
    rspBody->ret = true;
    // Note: This is a shallow copy. The client will need to handle the list of pointers.
    rspBody->participants = participants;

    if(!sendRsp(pRsp)) {
        delete rspBody;
        delete pRsp;
        return false;
    }

    return true;
}

bool ScoreMsgHandler::handleClear(ScoreMsg* pMsg) {
    (void)pMsg; // Unused parameter
    manager.clear();

    ScoreMsg* pRsp = new ScoreMsg;
    if(pRsp == nullptr){
        return false;
    }
    pRsp->hdr.type = CLEAR_RSP;
    pRsp->hdr.bodyLen = sizeof(ScoreMsgClearRsp);
    pRsp->body.pBody = new ScoreMsgClearRsp;
    if(pRsp->body.pBody == nullptr){
        delete pRsp;
        return false;
    }
    ((ScoreMsgClearRsp*)pRsp->body.pBody)->ret = true;

    if(!sendRsp(pRsp)) {
        delete static_cast<ScoreMsgClearRsp*>(pRsp->body.pBody);
        delete pRsp;
        return false;
    }

    return true;
}

bool ScoreMsgHandler::handleMsg(ScoreMsg* pMsg) {
    switch (pMsg->hdr.type) {
        case ADD_PARTICIPANT_REQ:
            return handleAddParticipant(pMsg);
            break;
        case DELETE_PARTICIPANT_REQ:
            return handleDeleteParticipant(pMsg);
            break;
        case UPDATE_PARTICIPANT_REQ:
            return handleUpdateParticipant(pMsg);
            break;
        case FIND_PARTICIPANT_BY_ID_REQ:
            return handleFindParticipantById(pMsg);
            break;
        case FIND_PARTICIPANT_BY_NAME_REQ:
            return handleFindParticipantByName(pMsg);
            break;
        case LIST_ALL_PARTICIPANTS_REQ:
            return handleListAllParticipants(pMsg);
            break;
        case CLEAR_REQ:
            return handleClear(pMsg);
            break;
        default:
            return false;
            break;
    }
}

bool ScoreMsgHandler::sendRsp(ScoreMsg* pMsg) {

    // ToDo...impletement sendRsp

    // Deallocate the message body based on its type
    switch (pMsg->hdr.type) {
        case ADD_PARTICIPANT_RSP:
            delete static_cast<ScoreMsgAddParticipantRsp*>(pMsg->body.pBody);
            break;
        case DELETE_PARTICIPANT_RSP:
            delete static_cast<ScoreMsgDeleteParticipantRsp*>(pMsg->body.pBody);
            break;
        case UPDATE_PARTICIPANT_RSP:
            delete static_cast<ScoreMsgUpdateParticipantRsp*>(pMsg->body.pBody);
            break;
        case FIND_PARTICIPANT_BY_ID_RSP:
            delete static_cast<ScoreMsgFindParticipantByIdRsp*>(pMsg->body.pBody);
            break;
        case FIND_PARTICIPANT_BY_NAME_RSP:
            delete static_cast<ScoreMsgFindParticipantByNameRsp*>(pMsg->body.pBody);
            break;
        case LIST_ALL_PARTICIPANTS_RSP:
            delete static_cast<ScoreMsgListAllParticipantsRsp*>(pMsg->body.pBody);
            break;
        case CLEAR_RSP:
            delete static_cast<ScoreMsgClearRsp*>(pMsg->body.pBody);
            break;
        default:
            // Should not happen for response messages, but good practice
            break;
    }

    delete pMsg;

    return true;
}
