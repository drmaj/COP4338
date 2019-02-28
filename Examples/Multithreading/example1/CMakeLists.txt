cmake_minimum_required(VERSION 3.10)
project(thread_proj)
add_executable(prog example1.c)
include(BuildType.cmake)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(prog Threads::Threads)

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
