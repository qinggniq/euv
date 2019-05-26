add_library(euv
  ""
  ioloop.cc
  ev_wrapper.cc
)

target_link_libraries(euv ev)