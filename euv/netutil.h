//
// Created by shengrang on 2019/5/31.
// Copyright (c) 2019 shengrang. All rights reserved.
//

#ifndef EUV_NETUTIL_H
#define EUV_NETUTIL_H

#include <cstdint>
#include <string>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

namespace euv {

namespace net {

/// 支持 ipv4, ipv6 的 SockAddr.
/// 暂时只实现 v4.
class SockAddr {
 public:
  SockAddr(const std::string &ip, uint16_t port, bool ipv6 = false);
  SockAddr(uint32_t ip, uint16_t port, bool ipv6 = false);

//  std::string ToString();
 private:
  struct sockaddr_in addr_;
};

}

}

#endif //EUV_NETUTIL_H
