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

#include "score_msg_serializer.h"
#include <cstring> /* For memcpy. */
#include <cstddef> /* For offsetof. */

/*
 * @brief Appends a plain data type to a byte buffer.
 * @tparam T The type of the value to append.
 * @param buffer The buffer to append to.
 * @param value The value to append.
 */
template<typename T>
void appendToBuffer(std::vector<uint8_t>& buffer, const T& value)
{
    const uint8_t* bytes = reinterpret_cast<const uint8_t*>(&value);
    buffer.insert(buffer.end(), bytes, bytes + sizeof(T));
}

/*
 * @brief Appends a string (length-prefixed) to a byte buffer.
 * @param buffer The buffer to append to.
 * @param str The string to append.
 */
void appendStringToBuffer(std::vector<uint8_t>& buffer, const std::string& str)
{
    uint32_t len = str.length();
    appendToBuffer(buffer, len);
    buffer.insert(buffer.end(), str.begin(), str.end());
}

/*
 * @brief Serializes a ScoreMsg structure into a byte buffer.
 * @param msg A pointer to the ScoreMsg to be serialized.
 * @param outBuffer The output buffer to store the serialized data.
 * @return True if serialization is successful, false otherwise.
 */
bool ScoreMsgSerializer::serialize(const ScoreMsg* msg, std::vector<uint8_t>& outBuffer)
{
    if (!msg)
    {
        return false;
    }

    outBuffer.clear();
    
    /* Serialize header first, with a placeholder for body length. */
    ScoreMsgHdr hdr = msg->hdr;
    hdr.bodyLen = 0;
    appendToBuffer(outBuffer, hdr);

    /* Serialize body based on message type. */
    if (msg->body.pBody != nullptr)
    {
        switch (msg->hdr.type)
        {
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
                /* No body data for these requests. */
                break;
            default:
                /* For responses or unknown types, do nothing. */
                break;
        }
    }

    /* Update body length in the serialized header. */
    uint32_t bodyLen = outBuffer.size() - sizeof(ScoreMsgHdr);
    memcpy(outBuffer.data() + offsetof(ScoreMsgHdr, bodyLen), &bodyLen, sizeof(bodyLen));

    return true;
}

/*
 * @brief Deserializes a byte buffer into a ScoreMsg structure.
 * @param buffer A pointer to the buffer containing the serialized data.
 * @param len The length of the buffer.
 * @return A pointer to the newly allocated ScoreMsg structure, or nullptr on failure.
 * @note The caller is responsible for deleting the returned ScoreMsg and its internal pBody.
 */
ScoreMsg* ScoreMsgSerializer::deserialize(const uint8_t* buffer, size_t len)
{
    if (!buffer || len < sizeof(ScoreMsgHdr))
    {
        return nullptr;
    }

    ScoreMsg* msg = new ScoreMsg();
    if (!msg)
    {
        return nullptr;
    }

    /* Deserialize header. */
    memcpy(&msg->hdr, buffer, sizeof(ScoreMsgHdr));

    const uint8_t* bodyBuffer = buffer + sizeof(ScoreMsgHdr);
    size_t bodyLen = len - sizeof(ScoreMsgHdr);

    if (static_cast<size_t>(msg->hdr.bodyLen) != bodyLen)
    {
        delete msg;
        return nullptr; /* Mismatched length. */
    }

    /* Deserialize body. */
    if (bodyLen > 0)
    {
        switch (msg->hdr.type)
        {
            case ADD_PARTICIPANT_REQ: {
                auto* req = new ScoreMsgAddParticipantReq();
                if (!req) { delete msg; return nullptr; }
                msg->body.pBody = req;
                size_t offset = 0;

                if (bodyLen < offset + sizeof(req->id)) { delete req; delete msg; return nullptr; }
                memcpy(&req->id, bodyBuffer + offset, sizeof(req->id));
                offset += sizeof(req->id);

                uint32_t nameLen;
                if (bodyLen < offset + sizeof(nameLen)) { delete req; delete msg; return nullptr; }
                memcpy(&nameLen, bodyBuffer + offset, sizeof(nameLen));
                offset += sizeof(nameLen);

                if (bodyLen < offset + nameLen) { delete req; delete msg; return nullptr; }
                req->name.assign(reinterpret_cast<const char*>(bodyBuffer + offset), nameLen);
                offset += nameLen;

                if (bodyLen < offset + sizeof(req->score)) { delete req; delete msg; return nullptr; }
                memcpy(&req->score, bodyBuffer + offset, sizeof(req->score));
                req->nameLen = nameLen;
                break;
            }
            case DELETE_PARTICIPANT_REQ: {
                if (bodyLen < sizeof(ScoreMsgDeleteParticipantReq)) { delete msg; return nullptr; }
                auto* req = new ScoreMsgDeleteParticipantReq();
                if (!req) { delete msg; return nullptr; }
                msg->body.pBody = req;
                memcpy(req, bodyBuffer, sizeof(ScoreMsgDeleteParticipantReq));
                break;
            }
            case UPDATE_PARTICIPANT_REQ: {
                auto* req = new ScoreMsgUpdateParticipantReq();
                if (!req) { delete msg; return nullptr; }
                msg->body.pBody = req;
                size_t offset = 0;

                if (bodyLen < offset + sizeof(req->id)) { delete req; delete msg; return nullptr; }
                memcpy(&req->id, bodyBuffer + offset, sizeof(req->id));
                offset += sizeof(req->id);

                uint32_t nameLen;
                if (bodyLen < offset + sizeof(nameLen)) { delete req; delete msg; return nullptr; }
                memcpy(&nameLen, bodyBuffer + offset, sizeof(nameLen));
                offset += sizeof(nameLen);

                if (bodyLen < offset + nameLen) { delete req; delete msg; return nullptr; }
                req->name.assign(reinterpret_cast<const char*>(bodyBuffer + offset), nameLen);
                offset += nameLen;

                if (bodyLen < offset + sizeof(req->score)) { delete req; delete msg; return nullptr; }
                memcpy(&req->score, bodyBuffer + offset, sizeof(req->score));
                req->nameLen = nameLen;
                break;
            }
            case FIND_PARTICIPANT_BY_ID_REQ: {
                if (bodyLen < sizeof(ScoreMsgFindParticipantByIdReq)) { delete msg; return nullptr; }
                auto* req = new ScoreMsgFindParticipantByIdReq();
                if (!req) { delete msg; return nullptr; }
                msg->body.pBody = req;
                memcpy(req, bodyBuffer, sizeof(ScoreMsgFindParticipantByIdReq));
                break;
            }
            case FIND_PARTICIPANT_BY_NAME_REQ: {
                auto* req = new ScoreMsgFindParticipantByNameReq();
                if (!req) { delete msg; return nullptr; }
                msg->body.pBody = req;
                size_t offset = 0;

                uint32_t nameLen;
                if (bodyLen < offset + sizeof(nameLen)) { delete req; delete msg; return nullptr; }
                memcpy(&nameLen, bodyBuffer + offset, sizeof(nameLen));
                offset += sizeof(nameLen);

                if (bodyLen < offset + nameLen) { delete req; delete msg; return nullptr; }
                req->name.assign(reinterpret_cast<const char*>(bodyBuffer + offset), nameLen);
                req->nameLen = nameLen;
                break;
            }
            default:
                msg->body.pBody = nullptr;
                break;
        }
    } else {
        msg->body.pBody = nullptr;
    }

    return msg;
}
