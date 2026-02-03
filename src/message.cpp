// Croupier C++ SDK - Protocol Layer Implementation
// Copyright (c) 2025 cuihairu
// Licensed under Apache License 2.0

#include "croupier/protocol/message.h"
#include <sstream>
#include <iomanip>
#include <cstring>

namespace croupier {
namespace protocol {

//=============================================================================
// Message class implementation
//=============================================================================

Message::Message()
    : version_(VERSION_1), msg_id_(0), req_id_(0) {}

Message::Message(uint32_t msg_id, uint32_t req_id)
    : version_(VERSION_1), msg_id_(msg_id), req_id_(req_id) {}

std::vector<uint8_t> Message::Encode() const {
    std::vector<uint8_t> result(HEADER_SIZE + body_.size());

    // Version (1 byte)
    result[0] = version_;

    // MsgID (3 bytes, big-endian)
    PutMsgID(result.data() + 1, msg_id_);

    // RequestID (4 bytes, big-endian)
    result[4] = static_cast<uint8_t>(req_id_ >> 24);
    result[5] = static_cast<uint8_t>(req_id_ >> 16);
    result[6] = static_cast<uint8_t>(req_id_ >> 8);
    result[7] = static_cast<uint8_t>(req_id_);

    // Body
    if (!body_.empty()) {
        std::memcpy(result.data() + HEADER_SIZE, body_.data(), body_.size());
    }

    return result;
}

bool Message::Decode(const std::vector<uint8_t>& data) {
    if (data.size() < HEADER_SIZE) {
        return false;
    }
    return Decode(data.data(), data.size());
}

bool Message::Decode(const uint8_t* data, size_t size) {
    if (size < HEADER_SIZE) {
        return false;
    }

    version_ = data[0];
    msg_id_ = GetMsgID(data + 1);

    req_id_ = (static_cast<uint32_t>(data[4]) << 24) |
              (static_cast<uint32_t>(data[5]) << 16) |
              (static_cast<uint32_t>(data[6]) << 8) |
              static_cast<uint32_t>(data[7]);

    if (size > HEADER_SIZE) {
        body_.assign(data + HEADER_SIZE, data + size);
    } else {
        body_.clear();
    }

    return true;
}

bool Message::IsRequest() const {
    return IsRequestMessage(msg_id_);
}

bool Message::IsResponse() const {
    return IsResponseMessage(msg_id_);
}

uint32_t Message::GetResponseMessageID() const {
    return GetResponseMessageID(msg_id_);
}

std::string Message::GetMessageIDString() const {
    return GetMessageTypeName(msg_id_);
}

std::string Message::DebugString() const {
    std::ostringstream oss;
    oss << "Message{Ver=" << static_cast<int>(version_)
        << ", MsgID=0x" << std::hex << std::setw(6) << std::setfill('0') << msg_id_
        << std::dec
        << " (" << GetMessageIDString() << ")"
        << ", ReqID=" << req_id_
        << ", BodySize=" << body_.size()
        << "}";
    return oss.str();
}

//=============================================================================
// Free function implementations
//=============================================================================

std::vector<uint8_t> CreateRequestMessage(
    uint32_t msg_id,
    uint32_t req_id,
    const std::vector<uint8_t>& body
) {
    Message msg(msg_id, req_id);
    msg.SetBody(body);
    return msg.Encode();
}

std::vector<uint8_t> CreateResponseMessage(
    uint32_t msg_id,
    uint32_t req_id,
    const std::vector<uint8_t>& body
) {
    Message msg(msg_id, req_id);
    msg.SetBody(body);
    return msg.Encode();
}

bool ParseMessage(
    const std::vector<uint8_t>& data,
    uint8_t& version,
    uint32_t& msg_id,
    uint32_t& req_id,
    std::vector<uint8_t>& body
) {
    if (data.size() < HEADER_SIZE) {
        return false;
    }

    version = data[0];
    msg_id = GetMsgID(data.data() + 1);

    req_id = (static_cast<uint32_t>(data[4]) << 24) |
             (static_cast<uint32_t>(data[5]) << 16) |
             (static_cast<uint32_t>(data[6]) << 8) |
             static_cast<uint32_t>(data[7]);

    if (data.size() > HEADER_SIZE) {
        body.assign(data.begin() + HEADER_SIZE, data.end());
    } else {
        body.clear();
    }

    return true;
}

std::string GetMessageTypeName(uint32_t msg_id) {
    switch (msg_id) {
        // ControlService
        case MessageType::REGISTER_REQUEST:
            return "RegisterRequest";
        case MessageType::REGISTER_RESPONSE:
            return "RegisterResponse";
        case MessageType::HEARTBEAT_REQUEST:
            return "HeartbeatRequest";
        case MessageType::HEARTBEAT_RESPONSE:
            return "HeartbeatResponse";

        // ClientService
        case MessageType::REGISTER_CLIENT_REQUEST:
            return "RegisterClientRequest";
        case MessageType::REGISTER_CLIENT_RESPONSE:
            return "RegisterClientResponse";
        case MessageType::CLIENT_HEARTBEAT_REQUEST:
            return "ClientHeartbeatRequest";
        case MessageType::CLIENT_HEARTBEAT_RESPONSE:
            return "ClientHeartbeatResponse";

        // InvokerService
        case MessageType::INVOKE_REQUEST:
            return "InvokeRequest";
        case MessageType::INVOKE_RESPONSE:
            return "InvokeResponse";
        case MessageType::START_JOB_REQUEST:
            return "StartJobRequest";
        case MessageType::START_JOB_RESPONSE:
            return "StartJobResponse";
        case MessageType::CANCEL_JOB_REQUEST:
            return "CancelJobRequest";
        case MessageType::CANCEL_JOB_RESPONSE:
            return "CancelJobResponse";

        // LocalControlService
        case MessageType::REGISTER_LOCAL_REQUEST:
            return "RegisterLocalRequest";
        case MessageType::REGISTER_LOCAL_RESPONSE:
            return "RegisterLocalResponse";
        case MessageType::HEARTBEAT_LOCAL_REQUEST:
            return "HeartbeatLocalRequest";
        case MessageType::HEARTBEAT_LOCAL_RESPONSE:
            return "HeartbeatLocalResponse";

        default:
            std::ostringstream oss;
            oss << "Unknown(0x" << std::hex << std::setw(6) << std::setfill('0') << msg_id << std::dec << ")";
            return oss.str();
    }
}

} // namespace protocol
} // namespace croupier
