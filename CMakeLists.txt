cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME server)
project(server)


set(SOURCES server.cpp)
set(LIBS -lboost_thread)
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${LIBS})