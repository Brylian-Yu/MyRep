#ifndef PARTICIPANT_H
#define PARTICIPANT_H

#include <string>
#include <vector>

struct Participant {
    int id;
    std::string name;
    double score;
};

typedef std::vector<Participant*> ParticipantList;

#endif // PARTICIPANT_H
