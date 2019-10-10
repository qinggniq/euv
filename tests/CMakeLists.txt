add_executable(test_ev_wrapper test_ev_wrapper.cc)

target_link_libraries(test_ev_wrapper euv)

add_executable(test_ioloop test_ioloop.cc)

target_link_libraries(test_ioloop euv)

include_directories(${PROJECT_SOURCE_DIR}/euv)