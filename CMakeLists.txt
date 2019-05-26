cmake_minimum_required(VERSION 3.14)
project(Invincible_Server)

set(CMAKE_CXX_STANDARD 11)
set(SOURCE CMAKE_SOURCE_DIR)

add_executable(Invincible_Server main.cpp comm/requestHandler.h)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} ~/pistache/build/src/libpistache.so.0)
