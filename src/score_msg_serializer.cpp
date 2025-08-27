#include "include/score_msg_serializer.h"
#include <cstring> // For memcpy
#include <cstddef> // For offsetof

// Helper to append data to a vector
template<typename T>
void appendToBuffer(std::vector<uint8_t>& buffer, const T& value) {
    const uint8_t* bytes = reinterpret_cast<const uint8_t*>(&value);
    buffer.insert(buffer.end(), bytes, bytes + sizeof(T));
}

void appendStringToBuffer(std::vector<uint8_t>& buffer, const std::string& str) {
    uint32_t len = str.length();
    appendToBuffer(buffer, len);
    buffer.insert(buffer.end(), str.begin(), str.end());
}

bool ScoreMsgSerializer::serialize(const ScoreMsg* msg, std::vector<uint8_t>& outBuffer) {
    if (!msg) return false;

    outBuffer.clear();
    
    // Serialize header first
    // We will calculate the final bodyLen later
    ScoreMsgHdr hdr = msg->hdr;
    hdr.bodyLen = 0; // Placeholder
    appendToBuffer(outBuffer, hdr);

    // Serialize body based on type
    switch (msg->hdr.type) {
        case ADD_PARTICIPANT_REQ: {
            auto* req = static_cast<ScoreMsgAddParticipantReq*>(msg->body.pBody);
            appendToBuffer(outBuffer, req->id);
            appendStringToBuffer(outBuffer, req->name);
            appendToBuffer(outBuffer, req->score);
            break;
        }
        case DELETE_PARTICIPANT_REQ: {
            auto* req = static_cast<ScoreMsgDeleteParticipantReq*>(msg->body.pBody);
            appendToBuffer(outBuffer, req->id);
            break;
        }
        case UPDATE_PARTICIPANT_REQ: {
            auto* req = static_cast<ScoreMsgUpdateParticipantReq*>(msg->body.pBody);
            appendToBuffer(outBuffer, req->id);
            appendStringToBuffer(outBuffer, req->name);
            appendToBuffer(outBuffer, req->score);
            break;
        }
        case FIND_PARTICIPANT_BY_ID_REQ: {
            auto* req = static_cast<ScoreMsgFindParticipantByIdReq*>(msg->body.pBody);
            appendToBuffer(outBuffer, req->id);
            break;
        }
        case FIND_PARTICIPANT_BY_NAME_REQ: {
            auto* req = static_cast<ScoreMsgFindParticipantByNameReq*>(msg->body.pBody);
            appendStringToBuffer(outBuffer, req->name);
            break;
        }
        case LIST_ALL_PARTICIPANTS_REQ:
        case CLEAR_REQ:
            // No body data for these requests
            break;
        default: // For responses or unknown types
            break;
    }

    // Update body length in the serialized header
    uint32_t bodyLen = outBuffer.size() - sizeof(ScoreMsgHdr);
    memcpy(outBuffer.data() + offsetof(ScoreMsgHdr, bodyLen), &bodyLen, sizeof(bodyLen));

    return true;
}

ScoreMsg* ScoreMsgSerializer::deserialize(const uint8_t* buffer, size_t len) {
    if (!buffer || len < sizeof(ScoreMsgHdr)) return nullptr;

    ScoreMsg* msg = new ScoreMsg();
    if (!msg) return nullptr;

    // Deserialize header
    memcpy(&msg->hdr, buffer, sizeof(ScoreMsgHdr));

    const uint8_t* bodyBuffer = buffer + sizeof(ScoreMsgHdr);
    size_t bodyLen = len - sizeof(ScoreMsgHdr);

    if (static_cast<size_t>(msg->hdr.bodyLen) != bodyLen) {
        delete msg;
        return nullptr; // Mismatched length
    }

    // Deserialize body
    switch (msg->hdr.type) {
        case ADD_PARTICIPANT_REQ: {
            auto* req = new ScoreMsgAddParticipantReq();
            msg->body.pBody = req;
            size_t offset = 0;

            memcpy(&req->id, bodyBuffer + offset, sizeof(req->id));
            offset += sizeof(req->id);

            uint32_t nameLen;
            memcpy(&nameLen, bodyBuffer + offset, sizeof(nameLen));
            offset += sizeof(nameLen);

            req->name.assign(reinterpret_cast<const char*>(bodyBuffer + offset), nameLen);
            offset += nameLen;

            memcpy(&req->score, bodyBuffer + offset, sizeof(req->score));
            req->nameLen = nameLen;
            break;
        }
        case DELETE_PARTICIPANT_REQ: {
            auto* req = new ScoreMsgDeleteParticipantReq();
            msg->body.pBody = req;
            memcpy(&req->id, bodyBuffer, sizeof(req->id));
            break;
        }
        case UPDATE_PARTICIPANT_REQ: {
            auto* req = new ScoreMsgUpdateParticipantReq();
            msg->body.pBody = req;
            size_t offset = 0;

            memcpy(&req->id, bodyBuffer + offset, sizeof(req->id));
            offset += sizeof(req->id);

            uint32_t nameLen;
            memcpy(&nameLen, bodyBuffer + offset, sizeof(nameLen));
            offset += sizeof(nameLen);

            req->name.assign(reinterpret_cast<const char*>(bodyBuffer + offset), nameLen);
            offset += nameLen;

            memcpy(&req->score, bodyBuffer + offset, sizeof(req->score));
            req->nameLen = nameLen;
            break;
        }
        case FIND_PARTICIPANT_BY_ID_REQ: {
            auto* req = new ScoreMsgFindParticipantByIdReq();
            msg->body.pBody = req;
            memcpy(&req->id, bodyBuffer, sizeof(req->id));
            break;
        }
        case FIND_PARTICIPANT_BY_NAME_REQ: {
            auto* req = new ScoreMsgFindParticipantByNameReq();
            msg->body.pBody = req;
            
            uint32_t nameLen;
            memcpy(&nameLen, bodyBuffer, sizeof(nameLen));
            
            req->name.assign(reinterpret_cast<const char*>(bodyBuffer + sizeof(nameLen)), nameLen);
            req->nameLen = nameLen;
            break;
        }
        case LIST_ALL_PARTICIPANTS_REQ:
        case CLEAR_REQ:
            // No body data for these requests
            msg->body.pBody = nullptr;
            break;
        default:
            msg->body.pBody = nullptr;
            break;
    }

    return msg;
}
