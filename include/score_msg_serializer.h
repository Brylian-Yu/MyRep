#ifndef SCORE_MSG_SERIALIZER_H
#define SCORE_MSG_SERIALIZER_H

#include "score_msg_type.h"
#include <vector>
#include <cstdint>

class ScoreMsgSerializer {
public:
    // Serializes a ScoreMsg structure into a byte buffer
    static bool serialize(const ScoreMsg* msg, std::vector<uint8_t>& outBuffer);

    // Deserializes a byte buffer into a ScoreMsg structure
    // Note: The caller is responsible for deleting the returned ScoreMsg and its internal pBody.
    static ScoreMsg* deserialize(const uint8_t* buffer, size_t len);
};

#endif // SCORE_MSG_SERIALIZER_H
