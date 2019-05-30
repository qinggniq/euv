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
#include "ev_wrapper.h"

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

  struct ev_loop *_ev_loop_;
  EvAsync waker_;       // 用来 wakeup IOLoop
  EvCheck checker_;     // 用来在每次 loop 结束执行 pending callbacks
  std::vector<Callback> pending_callbacks_;   // TODO 尝试其他并发队列

  void RunPendingCallback();

};

}

#endif //EUV_IOLOOP_H
