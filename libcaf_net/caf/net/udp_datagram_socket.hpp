/******************************************************************************
 *                       ____    _    _____                                   *
 *                      / ___|  / \  |  ___|    C++                           *
 *                     | |     / _ \ | |_       Actor                         *
 *                     | |___ / ___ \|  _|      Framework                     *
 *                      \____/_/   \_|_|                                      *
 *                                                                            *
 * Copyright 2011-2019 Dominik Charousset                                     *
 *                                                                            *
 * Distributed under the terms and conditions of the BSD 3-Clause License or  *
 * (at your option) under the terms and conditions of the Boost Software      *
 * License 1.0. See accompanying files LICENSE and LICENSE_ALTERNATIVE.       *
 *                                                                            *
 * If you did not receive a copy of the license files, see                    *
 * http://opensource.org/licenses/BSD-3-Clause and                            *
 * http://www.boost.org/LICENSE_1_0.txt.                                      *
 ******************************************************************************/

#pragma once

#include "caf/detail/net_export.hpp"
#include "caf/fwd.hpp"
#include "caf/net/network_socket.hpp"

namespace caf::net {

/// A datagram-oriented network communication endpoint for bidirectional
/// byte transmission.
struct CAF_NET_EXPORT udp_datagram_socket : network_socket {
  using super = network_socket;

  using super::super;
};

/// Creates a `udp_datagram_socket` bound to given port.
/// @param ep ip_endpoint that contains the port to bind to. Pass port '0' to
///           bind to any unused port - The endpoint will be updated with the
///           specific port that was bound.
/// @returns The connected socket or an error.
/// @relates udp_datagram_socket
expected<std::pair<udp_datagram_socket, uint16_t>>
  CAF_NET_EXPORT make_udp_datagram_socket(ip_endpoint ep,
                                          bool reuse_addr = false);

/// Enables or disables `SIO_UDP_CONNRESET` error on `x`.
/// @relates udp_datagram_socket
error CAF_NET_EXPORT allow_connreset(udp_datagram_socket x, bool new_value);

/// Receives the next datagram on socket `x`.
/// @param x The UDP socket for receiving datagrams.
/// @param buf Writable output buffer.
/// @returns The number of received bytes and the sender as `ip_endpoint` on
///          success, an error code otherwise.
/// @relates udp_datagram_socket
/// @post buf was modified and the resulting integer represents the length of
///       the received datagram, even if it did not fit into the given buffer.
variant<std::pair<size_t, ip_endpoint>, sec>
  CAF_NET_EXPORT read(udp_datagram_socket x, span<byte> buf);

/// Sends the content of `bufs` as a datagram to the endpoint `ep` on socket
/// `x`.
/// @param x The UDP socket for sending datagrams.
/// @param bufs Points to the datagram to send, scattered across up to 10
///             buffers.
/// @param ep The enpoint to send the datagram to.
/// @returns The number of written bytes on success, otherwise an error code.
/// @relates udp_datagram_socket
/// @pre `bufs.size() < 10`
variant<size_t, sec> CAF_NET_EXPORT write(udp_datagram_socket x,
                                          span<byte_buffer*> bufs,
                                          ip_endpoint ep);

/// Sends the content of `buf` as a datagram to the endpoint `ep` on socket `x`.
/// @param x The UDP socket for sending datagrams.
/// @param buf The buffer to send.
/// @param ep The enpoint to send the datagram to.
/// @returns The number of written bytes on success, otherwise an error code.
/// @relates udp_datagram_socket
variant<size_t, sec> CAF_NET_EXPORT write(udp_datagram_socket x,
                                          span<const byte> buf, ip_endpoint ep);

/// Converts the result from I/O operation on a ::udp_datagram_socket to either
/// an error code or a non-zero positive integer.
/// @relates udp_datagram_socket
variant<size_t, sec> CAF_NET_EXPORT
check_udp_datagram_socket_io_res(std::make_signed<size_t>::type res);

} // namespace caf::net
