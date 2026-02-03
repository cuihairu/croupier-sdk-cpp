// Croupier C++ SDK - Protocol Layer
// Copyright (c) 2025 cuihairu
// Licensed under Apache License 2.0

#ifndef CROUPIER_PROTOCOL_MESSAGE_H
#define CROUPIER_PROTOCOL_MESSAGE_H

#include <cstdint>
#include <vector>
#include <string>
#include <map>
#include <memory>

namespace croupier {
namespace protocol {

// Protocol constants
constexpr uint8_t VERSION_1 = 0x01;
constexpr size_t HEADER_SIZE = 8;  // Version(1) + MsgID(3) + RequestID(4)

// Message type constants (24 bits)
namespace MessageType {
    // ControlService (0x01xx)
    constexpr uint32_t REGISTER_REQUEST         = 0x010101;
    constexpr uint32_t REGISTER_RESPONSE        = 0x010102;
    constexpr uint32_t HEARTBEAT_REQUEST        = 0x010103;
    constexpr uint32_t HEARTBEAT_RESPONSE       = 0x010104;

    // ClientService (0x02xx)
    constexpr uint32_t REGISTER_CLIENT_REQUEST   = 0x020101;
    constexpr uint32_t REGISTER_CLIENT_RESPONSE  = 0x020102;
    constexpr uint32_t CLIENT_HEARTBEAT_REQUEST  = 0x020103;
    constexpr uint32_t CLIENT_HEARTBEAT_RESPONSE = 0x020104;

    // InvokerService (0x03xx)
    constexpr uint32_t INVOKE_REQUEST     = 0x030101;
    constexpr uint32_t INVOKE_RESPONSE    = 0x030102;
    constexpr uint32_t START_JOB_REQUEST  = 0x030103;
    constexpr uint32_t START_JOB_RESPONSE = 0x030104;
    constexpr uint32_t CANCEL_JOB_REQUEST  = 0x030107;
    constexpr uint32_t CANCEL_JOB_RESPONSE = 0x030108;

    // LocalControlService (0x05xx)
    constexpr uint32_t REGISTER_LOCAL_REQUEST   = 0x050101;
    constexpr uint32_t REGISTER_LOCAL_RESPONSE  = 0x050102;
    constexpr uint32_t HEARTBEAT_LOCAL_REQUEST  = 0x050103;
    constexpr uint32_t HEARTBEAT_LOCAL_RESPONSE = 0x050104;
}

/**
 * @brief Message class representing a protocol message
 *
 * Message format:
 *   Header (8 bytes):
 *     Version (1 byte) | MsgID (3 bytes) | RequestID (4 bytes)
 *   Body: protobuf serialized data
 */
class Message {
public:
    Message();
    explicit Message(uint32_t msg_id, uint32_t req_id = 0);

    // Encoding
    std::vector<uint8_t> Encode() const;

    // Decoding
    bool Decode(const std::vector<uint8_t>& data);
    bool Decode(const uint8_t* data, size_t size);

    // Accessors
    uint8_t GetVersion() const { return version_; }
    uint32_t GetMessageID() const { return msg_id_; }
    uint32_t GetRequestID() const { return req_id_; }
    const std::vector<uint8_t>& GetBody() const { return body_; }

    // Setters
    void SetVersion(uint8_t v) { version_ = v; }
    void SetMessageID(uint32_t id) { msg_id_ = id; }
    void SetRequestID(uint32_t id) { req_id_ = id; }
    void SetBody(const std::vector<uint8_t>& body) { body_ = body; }
    void SetBody(std::vector<uint8_t>&& body) { body_ = std::move(body); }

    // Utilities
    bool IsRequest() const;
    bool IsResponse() const;
    uint32_t GetResponseMessageID() const;
    std::string GetMessageIDString() const;

    // Debug
    std::string DebugString() const;

private:
    uint8_t version_;
    uint32_t msg_id_;
    uint32_t req_id_;
    std::vector<uint8_t> body_;
};

/**
 * @brief Encode 24-bit MsgID into buffer (big-endian)
 */
inline void PutMsgID(uint8_t* buf, uint32_t msg_id) {
    buf[0] = static_cast<uint8_t>(msg_id >> 16);
    buf[1] = static_cast<uint8_t>(msg_id >> 8);
    buf[2] = static_cast<uint8_t>(msg_id);
}

/**
 * @brief Decode 24-bit MsgID from buffer (big-endian)
 */
inline uint32_t GetMsgID(const uint8_t* buf) {
    return (static_cast<uint32_t>(buf[0]) << 16) |
           (static_cast<uint32_t>(buf[1]) << 8) |
           static_cast<uint32_t>(buf[2]);
}

/**
 * @brief Create a request message
 */
std::vector<uint8_t> CreateRequestMessage(
    uint32_t msg_id,
    uint32_t req_id,
    const std::vector<uint8_t>& body
);

/**
 * @brief Create a response message
 */
std::vector<uint8_t> CreateResponseMessage(
    uint32_t msg_id,
    uint32_t req_id,
    const std::vector<uint8_t>& body
);

/**
 * @brief Parse a message buffer
 */
bool ParseMessage(
    const std::vector<uint8_t>& data,
    uint8_t& version,
    uint32_t& msg_id,
    uint32_t& req_id,
    std::vector<uint8_t>& body
);

/**
 * @brief Get human-readable message type name
 */
std::string GetMessageTypeName(uint32_t msg_id);

/**
 * @brief Check if message ID is a request (odd number)
 */
inline bool IsRequestMessage(uint32_t msg_id) {
    return (msg_id & 1) == 1;
}

/**
 * @brief Check if message ID is a response (even number)
 */
inline bool IsResponseMessage(uint32_t msg_id) {
    return (msg_id & 1) == 0;
}

/**
 * @brief Get response message ID for a request
 */
inline uint32_t GetResponseMessageID(uint32_t req_msg_id) {
    return req_msg_id + 1;
}

} // namespace protocol
} // namespace croupier

#endif // CROUPIER_PROTOCOL_MESSAGE_H
