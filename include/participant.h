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

#ifndef PARTICIPANT_H
#define PARTICIPANT_H

#include <string>
#include <vector>

/*
 * @brief Represents a single participant with an ID, name, and score.
 */
struct Participant {
    int id;
    std::string name;
    double score;
};

typedef std::vector<Participant*> ParticipantList;

#endif // PARTICIPANT_H
