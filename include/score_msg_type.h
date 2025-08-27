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

#ifndef SCORE_MSG_TYPE_H
#define SCORE_MSG_TYPE_H

#include <string>
#include "participant.h"

/* @brief Defines the types of messages used in the score management system. */
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

/* @brief The header for a score message, containing its type and body length. */
typedef struct ScoreMsgHdr {
    ScoreMsgType type;
    uint32_t bodyLen;
} ScoreMsgHdr;

/* @brief The body of a score message, containing a pointer to the payload. */
typedef struct ScoreMsgBody {
    void* pBody;
} ScoreMsgBody;

/* @brief A complete score message, including header and body. */
typedef struct ScoreMsg {
    ScoreMsgHdr hdr;
    ScoreMsgBody body;
} ScoreMsg;

/* @brief Request to add a participant. */
typedef struct ScoreMsgAddParticipantReq {
    int id;
    int nameLen;
    std::string name;
    double score;
} ScoreMsgAddParticipantReq;

/* @brief Response for adding a participant. */
typedef struct ScoreMsgAddParticipantRsp {
    bool ret;
} ScoreMsgAddParticipantRsp;

/* @brief Request to delete a participant. */
typedef struct ScoreMsgDeleteParticipantReq {
    int id;
} ScoreMsgDeleteParticipantReq;

/* @brief Response for deleting a participant. */
typedef struct ScoreMsgDeleteParticipantRsp {
    bool ret;
} ScoreMsgDeleteParticipantRsp;

/* @brief Request to update a participant. */
typedef struct ScoreMsgUpdateParticipantReq {
    int id;
    int nameLen;
    std::string name;
    double score;
} ScoreMsgUpdateParticipantReq;

/* @brief Response for updating a participant. */
typedef struct ScoreMsgUpdateParticipantRsp {
    bool ret;
} ScoreMsgUpdateParticipantRsp;

/* @brief Request to find a participant by ID. */
typedef struct ScoreMsgFindParticipantByIdReq {
    int id;
} ScoreMsgFindParticipantByIdReq;

/* @brief Response for finding a participant by ID. */
typedef struct ScoreMsgFindParticipantByIdRsp {
    bool ret;
    int id;
    int nameLen;
    std::string name;
    double score;
} ScoreMsgFindParticipantByIdRsp;

/* @brief Request to find a participant by name. */
typedef struct ScoreMsgFindParticipantByNameReq {
    int nameLen;
    std::string name;
} ScoreMsgFindParticipantByNameReq;

/* @brief Response for finding a participant by name. */
typedef struct ScoreMsgFindParticipantByNameRsp {
    bool ret;
    int id;
    int nameLen;
    std::string name;
    double score;
} ScoreMsgFindParticipantByNameRsp;

/* @brief Response for listing all participants. */
typedef struct ScoreMsgListAllParticipantsRsp {
    bool ret;
    ParticipantList participants;
} ScoreMsgListAllParticipantsRsp;

/* @brief Response for clearing all participants. */
typedef struct ScoreMsgClearRsp {
    bool ret;
} ScoreMsgClearRsp;


#endif // SCORE_MSG_TYPE_H