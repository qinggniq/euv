//
// Created by shengrang on 2019/5/20.
// Copyright (c) 2019 shengrang. All rights reserved.
//

#include <cstdio>



#include "ev_wrapper.h"

int main() {
  euv::EvIO eio(0, EV_READ);
  struct ev_loop *loop = ev_default_loop(0);
  int cnt=0;
  euv::WatcherCallback cb = [&cnt](int r) {
    printf("readable %d, r: %d\n", cnt++, r);

  };
  eio.SetCallback(cb);
  eio.Start(loop);
  ev_run(loop, 0);
}