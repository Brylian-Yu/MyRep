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

#ifndef SCORE_MSG_SERIALIZER_H
#define SCORE_MSG_SERIALIZER_H

#include "score_msg_type.h"
#include <vector>
#include <cstdint>

class ScoreMsgSerializer {
public:
    /*
     * @brief Serializes a ScoreMsg structure into a byte buffer.
     * @param msg A pointer to the ScoreMsg to be serialized.
     * @param outBuffer The output buffer to store the serialized data.
     * @return True if serialization is successful, false otherwise.
     */
    static bool serialize(const ScoreMsg* msg, std::vector<uint8_t>& outBuffer);

    /*
     * @brief Deserializes a byte buffer into a ScoreMsg structure.
     * @param buffer A pointer to the buffer containing the serialized data.
     * @param len The length of the buffer.
     * @return A pointer to the newly allocated ScoreMsg structure, or nullptr on failure.
     * @note The caller is responsible for deleting the returned ScoreMsg and its internal pBody.
     */
    static ScoreMsg* deserialize(const uint8_t* buffer, size_t len);
};

#endif // SCORE_MSG_SERIALIZER_H
