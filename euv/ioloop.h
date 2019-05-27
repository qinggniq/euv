//
// Created by shengrang on 2019/5/20.
// Copyright (c) 2019 shengrang. All rights reserved.
//

#ifndef EUV_IOLOOP_H
#define EUV_IOLOOP_H

#include <vector>
#include <thread>
#include <mutex>
#include <atomic>

#include "types.h"

#include "ev.h"

namespace euv{

class IOLoop {
 public:

  IOLoop();
  ~IOLoop();

  void Start();

  void Stop();

  void AddCallback(const Callback &);

  bool IsInLoopThread() const;

  void WakeUp();

  // TODO: timeout task
 private:

  const std::thread::id tid_;
  std::mutex mutex_;
  std::atomic<bool> running_;

  struct ev_loop *ev_;
  std::vector<Callback> pending_callbacks_;

  void RunPendingCallback();

};

}

#endif //EUV_IOLOOP_H
