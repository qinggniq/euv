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
      _ev_loop_(nullptr),
      pending_callbacks_{} {
  _ev_loop_ = ev_loop_new(EVFLAG_AUTO);
  waker_.Start(_ev_loop_);
}

IOLoop::~IOLoop() {
  waker_.Stop();
  ev_loop_destroy(_ev_loop_);
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
    ev_run(_ev_loop_, EVRUN_ONCE);
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
    // 如果是同一个线程 AddCallback，暂时的做法是直接调用
    // 如果在同一个线程需要 queue 到 pending_callbacks_，下一次 loop 执行，应该需要 wakeUp
    // 暂时不提供 queue 功能，目前直接调用 callback，不考虑这个问题
    cb();
  } else {
    std::lock_guard<std::mutex> guard(mutex_);
    pending_callbacks_.push_back(cb);
    this->WakeUp();
  }
}

void IOLoop::WakeUp() {
  // ev_async_send is thread-safe
  waker_.AsyncSend();
}

}


