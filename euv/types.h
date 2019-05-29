//
// Created by shengrang on 2019/5/20.
// Copyright (c) 2019 shengrang. All rights reserved.
//

#ifndef EUV_TYPES_H
#define EUV_TYPES_H

#include <functional>
#include <type_traits>

namespace euv {

typedef std::function<void()> Callback;
typedef std::function<void(int)> WatcherCallback;

class noncopyable {
 protected:
  noncopyable() = default;
  ~noncopyable() = default;

  noncopyable(const noncopyable &) = delete;
  noncopyable &operator=(const noncopyable &) = delete;
};

template<typename T, typename... Rest>
struct is_any  : std::false_type {};

template<typename T, typename First>
struct is_any<T, First> : std::is_same<T, First> {};

template<typename T, typename First, typename... Rest>
struct is_any<T, First, Rest...>
    : std::integral_constant<bool, std::is_same<T, First>::value || is_any<T, Rest...>::value>
{};

}

#endif //EUV_TYPES_H
