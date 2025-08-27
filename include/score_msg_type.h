#ifndef SCORE_MSG_TYPE_H
#define SCORE_MSG_TYPE_H

#include <string>
#include "participant.h"

enum ScoreMsgType {
    ADD_PARTICIPANT_REQ,
    ADD_PARTICIPANT_RSP,
    DELETE_PARTICIPANT_REQ,
    DELETE_PARTICIPANT_RSP,
    UPDATE_PARTICIPANT_REQ,
    UPDATE_PARTICIPANT_RSP,
    FIND_PARTICIPANT_BY_ID_REQ,
    FIND_PARTICIPANT_BY_ID_RSP,
    FIND_PARTICIPANT_BY_NAME_REQ,
    FIND_PARTICIPANT_BY_NAME_RSP,
    LIST_ALL_PARTICIPANTS_REQ,
    LIST_ALL_PARTICIPANTS_RSP,
    CLEAR_REQ,
    CLEAR_RSP
};

typedef struct ScoreMsgHdr {
    ScoreMsgType type;
    uint32_t bodyLen;
} ScoreMsgHdr;

typedef struct ScoreMsgBody {
    void* pBody;
} ScoreMsgBody;

typedef struct ScoreMsg {
    ScoreMsgHdr hdr;
    ScoreMsgBody body;
} ScoreMsg;

typedef struct ScoreMsgAddParticipantReq {
    int id;
    int nameLen;
    std::string name;
    double score;
} ScoreMsgAddParticipantReq;

typedef struct ScoreMsgAddParticipantRsp {
    bool ret;
} ScoreMsgAddParticipantRsp;

typedef struct ScoreMsgDeleteParticipantReq {
    int id;
} ScoreMsgDeleteParticipantReq;

typedef struct ScoreMsgDeleteParticipantRsp {
    bool ret;
} ScoreMsgDeleteParticipantRsp;

typedef struct ScoreMsgUpdateParticipantReq {
    int id;
    int nameLen;
    std::string name;
    double score;
} ScoreMsgUpdateParticipantReq;

typedef struct ScoreMsgUpdateParticipantRsp {
    bool ret;
} ScoreMsgUpdateParticipantRsp;

typedef struct ScoreMsgFindParticipantByIdReq {
    int id;
} ScoreMsgFindParticipantByIdReq;

typedef struct ScoreMsgFindParticipantByIdRsp {
    bool ret;
    int id;
    int nameLen;
    std::string name;
    double score;
} ScoreMsgFindParticipantByIdRsp;

typedef struct ScoreMsgFindParticipantByNameReq {
    int nameLen;
    std::string name;
} ScoreMsgFindParticipantByNameReq;

typedef struct ScoreMsgFindParticipantByNameRsp {
    bool ret;
    int id;
    int nameLen;
    std::string name;
    double score;
} ScoreMsgFindParticipantByNameRsp;

typedef struct ScoreMsgListAllParticipantsRsp {
    bool ret;
    ParticipantList participants;
} ScoreMsgListAllParticipantsRsp;

typedef struct ScoreMsgClearRsp {
    bool ret;
} ScoreMsgClearRsp;


#endif // SCORE_MSG_TYPE_H