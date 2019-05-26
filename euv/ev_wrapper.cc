//
// Created by shengrang on 2019/5/21.
// Copyright (c) 2019 shengrang. All rights reserved.
//

#include "ev_wrapper.h"

namespace euv {

void euv::EvIOWatcher::ev_io_cb(struct ev_loop *loop, ev_io *w, int revents) {
  EvIOWatcher * ew = (EvIOWatcher*)(w->data);
  if(ew && ew->cb) {
    ew->cb(revents);
  }
}

EvIOWatcher::EvIOWatcher(int fd, int events): fd(fd), events(events) {
  ev_init(&io_watcher, ev_io_cb);
  io_watcher.data = (void*)this;
  ev_io_set(&io_watcher, fd, events);
}

bool EvIOWatcher::active() const {
  return static_cast<bool>ev_is_active(&io_watcher);
}

void EvIOWatcher::Start(struct ev_loop *loop) {
  owner_ev_loop_ = loop;
  ev_io_start(loop, &io_watcher);
}

void EvIOWatcher::Stop() {
  if(owner_ev_loop_) {
    ev_io_stop(owner_ev_loop_, &io_watcher);
    owner_ev_loop_ = nullptr;
  }
}

}
