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

#ifndef SCORE_MSG_HDLR_H
#define SCORE_MSG_HDLR_H

#include "manager.h"
#include "score_msg_type.h"

class ScoreMsgHandler {
public:
    /* Delete copy constructor and assignment operator. */
    ScoreMsgHandler(const ScoreMsgHandler&) = delete;
    ScoreMsgHandler& operator=(const ScoreMsgHandler&) = delete;

    /*
     * @brief Get the single instance of the ScoreMsgHandler.
     * @return Reference to the ScoreMsgHandler instance.
     */
    static ScoreMsgHandler& getInstance();

    /*
     * @brief Handle adding a participant.
     * @param pMsg The message containing participant data.
     * @return True on success, false on failure.
     */
    bool handleAddParticipant(ScoreMsg* pMsg);

    /*
     * @brief Handle deleting a participant.
     * @param pMsg The message containing the participant ID.
     * @return True on success, false on failure.
     */
    bool handleDeleteParticipant(ScoreMsg* pMsg);

    /*
     * @brief Handle updating a participant's information.
     * @param pMsg The message containing updated participant data.
     * @return True on success, false on failure.
     */
    bool handleUpdateParticipant(ScoreMsg* pMsg);

    /*
     * @brief Handle finding a participant by ID.
     * @param pMsg The message containing the participant ID.
     * @return True on success, false on failure.
     */
    bool handleFindParticipantById(ScoreMsg* pMsg);

    /*
     * @brief Handle finding a participant by name.
     * @param pMsg The message containing the participant name.
     * @return True on success, false on failure.
     */
    bool handleFindParticipantByName(ScoreMsg* pMsg);

    /*
     * @brief Handle listing all participants.
     * @param pMsg The message to be populated with the participant list.
     * @return True on success, false on failure.
     */
    bool handleListAllParticipants(ScoreMsg* pMsg);

    /*
     * @brief Handle clearing all participants.
     * @param pMsg The message object.
     * @return True on success, false on failure.
     */
    bool handleClear(ScoreMsg* pMsg);

    /*
     * @brief Generic message handler.
     * @param pMsg The message to handle.
     * @return True on success, false on failure.
     */
    bool handleMsg(ScoreMsg* pMsg);

    /*
     * @brief Send a response message.
     * @param pMsg The message to send.
     * @return True on success, false on failure.
     */
    bool sendRsp(ScoreMsg* pMsg);

private:
    /* Private constructor to enforce singleton. */
    ScoreMsgHandler() : manager(ScoreManager::getInstance()) {}

    ScoreManager& manager;
};

#endif // SCORE_MSG_HDLR_H