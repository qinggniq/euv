add_executable(main main.cc)

target_link_libraries(main euv)

include_directories(${PROJECT_SOURCE_DIR}/euv)