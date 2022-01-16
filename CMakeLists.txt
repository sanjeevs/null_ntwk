cmake_minimum_required(VERSION 3.5)

project (NullNtwk)
set(CMAKE_CXX_STANDARD 14)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

include_directories(src)
add_subdirectory(tests)