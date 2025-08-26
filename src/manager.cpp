#include "../include/manager.h"
#include <iostream>
#include <algorithm>

// Destructor implementation
ScoreManager::~ScoreManager() {
    // Clean up all dynamically allocated Participant objects
    for (auto* participant : participants) {
        delete participant;
    }
    participants.clear();
}

void ScoreManager::addParticipant(int id, const std::string& name, double score) {
    if (findById(id) != participants.end()) {
        std::cout << "Error: Participant with ID " << id << " already exists." << std::endl;
        return;
    }
    participants.push_back(new Participant{id, name, score});
    std::cout << "Participant added successfully." << std::endl;
}

bool ScoreManager::deleteParticipant(int id) {
    auto it = findById(id);
    if (it != participants.end()) {
        delete *it;
        participants.erase(it);
        std::cout << "Participant with ID " << id << " deleted." << std::endl;
        return true;
    }
    std::cout << "Error: Participant with ID " << id << " not found." << std::endl;
    return false;
}

bool ScoreManager::updateParticipant(int id, const std::string& newName, double newScore) {
    auto it = findById(id);
    if (it != participants.end()) {
        (*it)->name = newName;
        (*it)->score = newScore;
        std::cout << "Participant with ID " << id << " updated." << std::endl;
        return true;
    }
    std::cout << "Error: Participant with ID " << id << " not found." << std::endl;
    return false;
}

void ScoreManager::findParticipantById(int id) const {
    auto it = std::find_if(participants.begin(), participants.end(), 
                         [id](const Participant* p) { return p->id == id; });

    if (it != participants.end()) {
        std::cout << "Participant Found: ID: " << (*it)->id << ", Name: " << (*it)->name << ", Score: " << (*it)->score << std::endl;
    } else {
        std::cout << "Participant with ID " << id << " not found." << std::endl;
    }
}

void ScoreManager::findParticipantByName(const std::string& name) const{
    auto it = std::find_if(participants.begin(), participants.end(), 
                         [name](const Participant* p) { return p->name == name; });

    if (it != participants.end()) {
        std::cout << "Participant Found: ID: " << (*it)->id << ", Name: " << (*it)->name << ", Score: " << (*it)->score << std::endl;
    } else {
        std::cout << "Participant with Name " << name << " not found." << std::endl;
    }
}

void ScoreManager::listAllParticipants() const {
    if (participants.empty()) {
        std::cout << "No participants in the system." << std::endl;
        return;
    }
    std::cout << "--- All Participants ---" << std::endl;
    for (const auto& p : participants) {
        std::cout << "ID: " << p->id << ",\tName: " << p->name << ",\tScore: " << p->score << std::endl;
    }
    std::cout << "------------------------" << std::endl;
}

// Private helper function
std::vector<Participant*>::iterator ScoreManager::findById(int id) {
    return std::find_if(participants.begin(), participants.end(), 
                        [id](const Participant* p) { return p->id == id; });
}
