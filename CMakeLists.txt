cmake_minimum_required(VERSION 3.5)

project(cpp-stl-concurrency LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#add_compile_options(-std=c++2a)

add_executable(cpp-stl-concurrency main.cpp)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(cpp-stl-concurrency PRIVATE Threads::Threads)
