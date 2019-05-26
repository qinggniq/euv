//
// Created by shengrang on 2019/5/21.
// Copyright (c) 2019 shengrang. All rights reserved.
//

#ifndef EUV_EV_WRAPPER_H
#define EUV_EV_WRAPPER_H

#include <memory>

#include <ev.h>

#include "types.h"

namespace euv {

class IOLoop;

/// 对 ev_io 的封装，在 loop 里期待事件发生，
/// 大部分情况只处理读或者只处理写 (同一个 fd 可以有多个 EvIOWatcher，例如 TCPConn 可以创建 2 个 watcher 分别负责读写)
/// revent 是实际发生事件的 callback 参数，因此大部分时候 IOWatcherCallback 忽略 int revent 的参数。
class EvIOWatcher: private noncopyable {
  static void ev_io_cb(struct ev_loop *, ev_io *, int);
 public:
  ev_io io_watcher;
  const int fd;
  const int events;

  IOWatcherCallback cb;   // void (int revent);

  EvIOWatcher(int fd, int events);

  bool active() const;

  void Start(struct ev_loop *loop);
  void Stop();

 private:
  struct ev_loop *owner_ev_loop_ = nullptr;  // 在一次 [Start(), Stop()] 期间， EvIOWatcher 归属于这个 owner_ev_loop_ ev_loop。
};

}

#endif //EUV_EV_WRAPPER_H
