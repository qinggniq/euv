//
// Created by shengrang on 2019/5/21.
// Copyright (c) 2019 shengrang. All rights reserved.
//

#include "ev_wrapper.h"

namespace euv {

EvIO::EvIO(int fd, int events): fd_(fd), events_(events) {
  ev_io_set(&_ev, fd_, events_);
}

}
