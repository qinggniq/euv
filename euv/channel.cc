//
// Created by shengrang on 2019/10/9.
// Copyright (c) 2019 shengrang. All rights reserved.
//

#include "channel.h"

namespace euv {

Channel::Channel(euv::IOLoop *loop, int fd)
  : loop_(loop),
    fd_(fd),
    events_(0),
    readWatcher_(fd, EV_READ),
    writeWatcher_(fd, EV_WRITE)
{

}

}
