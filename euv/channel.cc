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

void Channel::enableReading() {
  events_ |= EV_READ;
  loop_->EnableEvWatcher(&readWatcher_);
//  readWatcher_.Start(loop_->EvLoop());
}

void Channel::disableReading() {
  events_ &= ~EV_READ;
  loop_->DisableEvWatcher(&readWatcher_);
//  readWatcher_.Stop();
}

void Channel::enableWriting() {
  events_ |= EV_WRITE;
  loop_->EnableEvWatcher(&writeWatcher_);
//  writeWatcher_.Start(loop_->EvLoop());
}

void Channel::disableWriting() {
  events_ &= ~ EV_WRITE;
  loop_->DisableEvWatcher(&writeWatcher_);
//  writeWatcher_.Stop();
}

}
