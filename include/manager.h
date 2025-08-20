#ifndef MANAGER_H
#define MANAGER_H

#include "participant.h"
#include <vector>
#include <string>

class ScoreManager {
public:
    void addParticipant(int id, const std::string& name, double score);
    bool deleteParticipant(int id);
    bool updateParticipant(int id, const std::string& newName, double newScore);
    void findParticipant(int id) const;
    void findParticipantByName(const std::string& name) const;
    void listAllParticipants() const;

private:
    std::vector<Participant> participants;
    std::vector<Participant>::iterator findById(int id);
};

#endif // MANAGER_H
