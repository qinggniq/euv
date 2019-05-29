//
// Created by shengrang on 2019/5/21.
// Copyright (c) 2019 shengrang. All rights reserved.
//

#ifndef EUV_EV_WRAPPER_H
#define EUV_EV_WRAPPER_H

#include <memory>
#include <type_traits>

#include <ev.h>

#include "types.h"

namespace euv {

template<
    typename T,
    void (EV_START)(struct ev_loop*, T *) = nullptr,
    void (EV_STOP)(struct ev_loop*, T *) = nullptr,
    typename std::enable_if<is_any<
        T, ev_io, ev_async
          >::value, int>::type = 0>
class EvWatcher: private noncopyable {

  static void ev_generic_cb(struct ev_loop *, T *w, int revents) {
    auto *ew = static_cast<EvWatcher*>(w->data);
    if(ew && ew->cb_) {
      ew->cb_(revents);
    }
  }

 public:
  T _ev;

  EvWatcher() {
    _ev.data = static_cast<void*>(this);
    ev_init(&_ev, ev_generic_cb);
  }

  void SetCallback(const WatcherCallback &cb) {
    cb_ = cb;
  }

  bool active() const {
    return static_cast<bool>(ev_is_active(&_ev));
  }

  void Start(struct ev_loop *loop) {
    owner_ev_loop_ = loop;
    EV_START(loop, &_ev);
  }

  void Stop() {
    if(owner_ev_loop_) {
      EV_STOP(owner_ev_loop_, &_ev);
      owner_ev_loop_ = nullptr;
    }
  }

 protected:
  struct ev_loop *owner_ev_loop_ = nullptr;
  WatcherCallback cb_;
};


/// 对 ev_io 的封装，在 loop 里期待事件发生，
/// 大部分情况只处理读或者只处理写 (同一个 fd 可以有多个 EvIOWatcher，例如 TCPConn 可以创建 2 个 watcher 分别负责读写)
/// revent 是实际发生事件的 callback 参数，因此大部分时候 IOWatcherCallback 忽略 int revent 的参数。
class EvIO: public EvWatcher<ev_io, ev_io_start, ev_io_stop> {
 public:

  EvIO(int fd, int events);

 private:
  const int fd_;
  int events_;
};

class EvAsync: public EvWatcher<ev_async, ev_async_start, ev_async_stop> {
 public:
  void AsyncSend() {
    assert(active());
    ev_async_send(owner_ev_loop_, &_ev);
  }
};


}

#endif //EUV_EV_WRAPPER_H
