//
// Created by shengrang on 2019/5/20.
// Copyright (c) 2019 shengrang. All rights reserved.
//

#ifndef EUV_TYPES_H
#define EUV_TYPES_H

#include <functional>

namespace euv {

typedef std::function<void()> Callback;
typedef std::function<void(int)> IOWatcherCallback;

class noncopyable {
 protected:
  noncopyable() = default;
  ~noncopyable() = default;

  noncopyable(const noncopyable &) = delete;
  noncopyable &operator=(const noncopyable &) = delete;
};


}

#endif //EUV_TYPES_H
