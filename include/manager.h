#ifndef MANAGER_H
#define MANAGER_H

#include "participant.h"
#include <vector>
#include <string>
#include <mutex>

class ScoreManager {
public:
    // Delete copy constructor and assignment operator
    ScoreManager(const ScoreManager&) = delete;
    ScoreManager& operator=(const ScoreManager&) = delete;

    // Public static method to get the single instance
    static ScoreManager& getInstance();

    // Public interface for managing participants
    bool addParticipant(int id, const std::string& name, double score);
    bool deleteParticipant(int id);
    const ParticipantList& listAllParticipants() const;
    bool updateParticipant(int id, const std::string& newName, double newScore);
    Participant* findParticipantById(int id) const;
    Participant* findParticipantByName(const std::string& name) const;
    void clear();

private:
    // Private constructor and destructor to enforce singleton
    ScoreManager() = default;
    ~ScoreManager();

    ParticipantList participants;
    mutable std::mutex mtx_; // Mutex for thread safety
    ParticipantList::iterator findById(int id); // Must be called with lock held
};

#endif // MANAGER_H
