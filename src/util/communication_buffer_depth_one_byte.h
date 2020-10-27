//#pragma once

//#include "communication_base.h"

// namespace util {

// class communication_buffer_depth_one_byte : public communication_base
//{
//  public:
//    using buffer_type = std::uint8_t;

//    virtual ~communication_buffer_depth_one_byte() = default;

//    bool recv(std::uint8_t& byte_to_recv) override
//    {
//        const bool recv_is_ok = recv_buffer_is_full;

//        if (recv_is_ok)
//        {
//            byte_to_recv = recv_buffer;

//            recv_buffer_is_full = false;
//        }

//        return recv_is_ok;
//    }

//    size_type recv_ready() const override { return (recv_buffer_is_full ? 1U : 0U); }

//    bool idle() const override { return true; }

//  protected:
//    communication_buffer_depth_one_byte() noexcept = default;

//    buffer_type recv_buffer{};
//    bool recv_buffer_is_full{false};
//};
//} // namespace util
