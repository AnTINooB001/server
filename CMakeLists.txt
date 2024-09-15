cmake_minimum_required(VERSION 2.8)

project(server)

set(Headers host.hpp utils.h connection_manager.hpp)
set(Sources server.cpp)

add_executable(server ${Sources})

target_link_libraries(server -lboost_thread)

