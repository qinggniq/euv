//
// Created by shengrang on 2019/5/31.
// Copyright (c) 2019 shengrang. All rights reserved.
//

#include "netutil.h"

namespace euv {

namespace net {

//static uint32_t

SockAddr::SockAddr(const std::string &ip, uint16_t port, bool ipv6) {
  assert(!ipv6);
  if (!ipv6) {
    memset(&addr_, 0, sizeof(addr_));
    addr_.sin_family = AF_INET;
    addr_.sin_port = htons(port);
    ::inet_pton(AF_INET, ip.data(), &addr_.sin_addr);
  }
}

SockAddr::SockAddr(uint32_t ip, uint16_t port, bool ipv6) {
  assert(!ipv6);
  if (!ipv6) {
    memset(&addr_, 0, sizeof(addr_));
    addr_.sin_family = AF_INET;
    addr_.sin_port = htons(port);
    addr_.sin_addr.s_addr = htonl(ip);
  }
}

}

}

