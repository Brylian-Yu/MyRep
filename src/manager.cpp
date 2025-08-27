#include "include/manager.h"
#include <iostream>
#include <algorithm>

ScoreManager& ScoreManager::getInstance() {
    static ScoreManager instance;
    return instance;
}

// Destructor implementation
ScoreManager::~ScoreManager() {
    // Clean up all dynamically allocated Participant objects
    for (auto* participant : participants) {
        delete participant;
    }
    participants.clear();
}

bool ScoreManager::addParticipant(int id, const std::string& name, double score) {
    std::lock_guard<std::mutex> lock(mtx_);
    if (findById(id) != participants.end()) {
        return false;
    }
    participants.push_back(new Participant{id, name, score});
    return true;
}

bool ScoreManager::deleteParticipant(int id) {
    std::lock_guard<std::mutex> lock(mtx_);
    auto it = findById(id);
    if (it != participants.end()) {
        delete *it;
        participants.erase(it);
        return true;
    }
    return false;
}

bool ScoreManager::updateParticipant(int id, const std::string& newName, double newScore) {
    std::lock_guard<std::mutex> lock(mtx_);
    auto it = findById(id);
    if (it != participants.end()) {
        (*it)->name = newName;
        (*it)->score = newScore;
        return true;
    }
    return false;
}

Participant* ScoreManager::findParticipantById(int id) const {
    std::lock_guard<std::mutex> lock(mtx_);
    auto it = std::find_if(participants.begin(), participants.end(), 
                         [id](Participant* p) { return p->id == id; });

    if (it != participants.end()) {
        return *it;
    } else {
        return nullptr;
    }
}

Participant* ScoreManager::findParticipantByName(const std::string& name) const{
    std::lock_guard<std::mutex> lock(mtx_);
    auto it = std::find_if(participants.begin(), participants.end(), 
                         [name](Participant* p) { return p->name == name; });

    if (it != participants.end()) {
        return *it;
    } else {
        return nullptr;
    }
}

const ParticipantList& ScoreManager::listAllParticipants() const {
    std::lock_guard<std::mutex> lock(mtx_);
    return participants;
}

// Private helper function
ParticipantList::iterator ScoreManager::findById(int id) {
    return std::find_if(participants.begin(), participants.end(), 
                        [id](Participant* p) { return p->id == id; });
}

void ScoreManager::clear() {
    std::lock_guard<std::mutex> lock(mtx_);
    // Delete all dynamically allocated Participant objects
    for (auto* participant : participants) {
        delete participant;
    }
    participants.clear();
}
