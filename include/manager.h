#ifndef MANAGER_H
#define MANAGER_H

#include "participant.h"
#include <vector>
#include <string>

class ScoreManager {
public:
    // Constructor
    ScoreManager() = default;
    
    // Destructor to clean up dynamically allocated memory
    ~ScoreManager();
    
    // Delete copy constructor and assignment operator to prevent shallow copying
    ScoreManager(const ScoreManager&) = delete;
    ScoreManager& operator=(const ScoreManager&) = delete;
    
    void addParticipant(int id, const std::string& name, double score);
    bool deleteParticipant(int id);
    bool updateParticipant(int id, const std::string& newName, double newScore);
    void findParticipantById(int id) const;
    void findParticipantByName(const std::string& name) const;
    void listAllParticipants() const;

private:
    std::vector<Participant*> participants;
    std::vector<Participant*>::iterator findById(int id);
};

#endif // MANAGER_H
