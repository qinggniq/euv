//
// Created by shengrang on 2019/10/9.
// Copyright (c) 2019 shengrang. All rights reserved.
//

#ifndef EUV_CHANNEL_H
#define EUV_CHANNEL_H

#include <functional>

#include "ioloop.h"
#include "ev_wrapper.h"

namespace euv {

class Channel {
 public:
  Channel(IOLoop *loop, int fd);
  ~Channel() = default;

  void enableReading();
  void disableReading();
  void enableWriting();
  void disableWriting();

  bool isReading() {
    return events_ & EV_READ;
  }
  bool isWriting() {
    return events_ & EV_WRITE;
  }

  void SetReadCallback(const WatcherCallback &cb) {
    readWatcher_.SetCallback(cb);
  }

  void SetWriteCallback(const WatcherCallback &cb) {
    writeWatcher_.SetCallback(cb);
  }

 private:
  IOLoop *loop_;
  const int fd_;
  int events_;

  EvIO readWatcher_;
  EvIO writeWatcher_;

};

}

#endif //EUV_CHANNEL_H
