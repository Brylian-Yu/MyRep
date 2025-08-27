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

#include "manager.h"
#include <iostream>
#include <algorithm>

/*
 * @brief Get the single instance of the ScoreManager.
 * @return Reference to the ScoreManager instance.
 */
ScoreManager& ScoreManager::getInstance()
{
    static ScoreManager instance;
    return instance;
}

/*
 * @brief Destructor for ScoreManager.
 *        Cleans up all dynamically allocated Participant objects.
 */
ScoreManager::~ScoreManager()
{
    clear();
}

/*
 * @brief Add a new participant.
 * @param id The participant's ID.
 * @param name The participant's name.
 * @param score The participant's score.
 * @return True if the participant was added successfully, false otherwise.
 */
bool ScoreManager::addParticipant(int id, const std::string& name, double score)
{
    std::lock_guard<std::mutex> lock(mtx_);
    if (findById(id) != participants.end()) {
        return false;
    }
    participants.push_back(new Participant{id, name, score});
    return true;
}

/*
 * @brief Delete a participant by ID.
 * @param id The ID of the participant to delete.
 * @return True if the participant was deleted successfully, false otherwise.
 */
bool ScoreManager::deleteParticipant(int id)
{
    std::lock_guard<std::mutex> lock(mtx_);
    auto it = findById(id);
    if (it != participants.end()) {
        delete *it;
        participants.erase(it);
        return true;
    }
    return false;
}

/*
 * @brief Update a participant's information.
 * @param id The ID of the participant to update.
 * @param newName The new name for the participant.
 * @param newScore The new score for the participant.
 * @return True if the update was successful, false otherwise.
 */
bool ScoreManager::updateParticipant(int id, const std::string& newName, double newScore)
{
    std::lock_guard<std::mutex> lock(mtx_);
    auto it = findById(id);
    if (it != participants.end()) {
        (*it)->name = newName;
        (*it)->score = newScore;
        return true;
    }
    return false;
}

/*
 * @brief Find a participant by ID.
 * @param id The ID of the participant to find.
 * @return A pointer to the participant if found, otherwise nullptr.
 */
Participant* ScoreManager::findParticipantById(int id) const
{
    std::lock_guard<std::mutex> lock(mtx_);
    auto it = std::find_if(participants.begin(), participants.end(), 
                         [id](Participant* p) { return p->id == id; });

    if (it != participants.end()) {
        return *it;
    } else {
        return nullptr;
    }
}

/*
 * @brief Find a participant by name.
 * @param name The name of the participant to find.
 * @return A pointer to the participant if found, otherwise nullptr.
 */
Participant* ScoreManager::findParticipantByName(const std::string& name) const
{
    std::lock_guard<std::mutex> lock(mtx_);
    auto it = std::find_if(participants.begin(), participants.end(), 
                         [name](Participant* p) { return p->name == name; });

    if (it != participants.end()) {
        return *it;
    } else {
        return nullptr;
    }
}

/*
 * @brief List all participants.
 * @return A constant reference to the list of all participants.
 */
const ParticipantList& ScoreManager::listAllParticipants() const
{
    std::lock_guard<std::mutex> lock(mtx_);
    return participants;
}

/*
 * @brief Find a participant by ID (must be called with lock held).
 * @param id The ID of the participant to find.
 * @return An iterator to the participant if found, otherwise participants.end().
 */
ParticipantList::iterator ScoreManager::findById(int id)
{
    return std::find_if(participants.begin(), participants.end(), 
                        [id](Participant* p) { return p->id == id; });
}

/*
 * @brief Clear all participants from the list.
 */
void ScoreManager::clear()
{
    std::lock_guard<std::mutex> lock(mtx_);
    /* Delete all dynamically allocated Participant objects. */
    for (auto* participant : participants) {
        delete participant;
    }
    participants.clear();
}
