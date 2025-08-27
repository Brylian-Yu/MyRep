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

#ifndef MANAGER_H
#define MANAGER_H

#include "participant.h"
#include <vector>
#include <string>
#include <mutex>

class ScoreManager {
public:
    /* Delete copy constructor and assignment operator. */
    ScoreManager(const ScoreManager&) = delete;
    ScoreManager& operator=(const ScoreManager&) = delete;

    /*
     * @brief Get the single instance of the ScoreManager.
     * @return Reference to the ScoreManager instance.
     */
    static ScoreManager& getInstance();

    /*
     * @brief Add a new participant.
     * @param id The participant's ID.
     * @param name The participant's name.
     * @param score The participant's score.
     * @return True if the participant was added successfully, false otherwise.
     */
    bool addParticipant(int id, const std::string& name, double score);

    /*
     * @brief Delete a participant by ID.
     * @param id The ID of the participant to delete.
     * @return True if the participant was deleted successfully, false otherwise.
     */
    bool deleteParticipant(int id);

    /*
     * @brief List all participants.
     * @return A constant reference to the list of all participants.
     */
    const ParticipantList& listAllParticipants() const;

    /*
     * @brief Update a participant's information.
     * @param id The ID of the participant to update.
     * @param newName The new name for the participant.
     * @param newScore The new score for the participant.
     * @return True if the update was successful, false otherwise.
     */
    bool updateParticipant(int id, const std::string& newName, double newScore);

    /*
     * @brief Find a participant by ID.
     * @param id The ID of the participant to find.
     * @return A pointer to the participant if found, otherwise nullptr.
     */
    Participant* findParticipantById(int id) const;

    /*
     * @brief Find a participant by name.
     * @param name The name of the participant to find.
     * @return A pointer to the participant if found, otherwise nullptr.
     */
    Participant* findParticipantByName(const std::string& name) const;

    /*
     * @brief Clear all participants from the list.
     */
    void clear();

private:
    /* Private constructor and destructor to enforce singleton. */
    ScoreManager() = default;
    ~ScoreManager();

    ParticipantList participants;
    mutable std::mutex mtx_; /* Mutex for thread safety. */

    /*
     * @brief Find a participant by ID (must be called with lock held).
     * @param id The ID of the participant to find.
     * @return An iterator to the participant if found, otherwise participants.end().
     */
    ParticipantList::iterator findById(int id);
};

#endif // MANAGER_H
