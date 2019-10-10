add_library(euv
  ""
  ioloop.cc
  ev_wrapper.cc
  netutil.cc channel.cc channel.h)

target_link_libraries(euv ev)