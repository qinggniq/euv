//
// Created by shengrang on 2019/10/10.
// Copyright (c) 2019 shengrang. All rights reserved.
//

#include <cstdio>

#include "ioloop.h"

int main() {
  euv::IOLoop loop;
  loop.AddCallback([](){
    printf("foo\n");
  });
}