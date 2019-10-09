add_library(euv
  ""
  ioloop.cc
  ev_wrapper.cc
  netutil.cc)

target_link_libraries(euv ev)