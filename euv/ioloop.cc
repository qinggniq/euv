//
// Created by shengrang on 2019/5/20.
// Copyright (c) 2019 shengrang. All rights reserved.
//

#include "ioloop.h"

namespace euv {

IOLoop::IOLoop()
    : tid_(std::this_thread::get_id()),
      mutex_{},
      running_(false),
      ev_(nullptr),
      pending_callbacks_{} {
  ev_ = ev_loop_new(EVFLAG_AUTO);
}

IOLoop::~IOLoop() {
  ev_loop_destroy(ev_);
}

void IOLoop::RunPendingCallback() {
  std::vector<Callback> cbs;
  {
    std::lock_guard<std::mutex> guard(mutex_);
    std::swap(cbs, pending_callbacks_);
  }

  for(const auto &cb: cbs) {
    cb();
  }
}

void IOLoop::Start() {
  running_ = true;
  while(running_) {
    ev_run(ev_, EVRUN_ONCE);
  }
}

void IOLoop::Stop() {
  running_ = false;
  this->WakeUp();
}

bool IOLoop::IsInLoopThread() const {
  return tid_ == std::this_thread::get_id();
}

void IOLoop::AddCallback(const Callback &cb) {
  if(IsInLoopThread()) {
    cb();
  } else {
    std::lock_guard<std::mutex> guard(mutex_);
    pending_callbacks_.push_back(cb);
    this->WakeUp();
  }
}

}


