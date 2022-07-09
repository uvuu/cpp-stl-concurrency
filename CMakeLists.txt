cmake_minimum_required(VERSION 3.5)

project(cpp-stl-concurrency LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# For now only these versions of the compilers support the std::jthread
if ((CMAKE_COMPILER_IS_GNUCC AND CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 10.0)
	OR (CMAKE_CXX_COMPILER_ID MATCHES "MSVC" AND CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 19.28))
	add_definitions( -DJTHREADS_ENABLED )
endif()

add_executable(cpp-stl-concurrency
	main.cpp
	
	jthread_execution.h
	jthread_execution.cpp

	thread_execution.h
	thread_execution.cpp
)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(cpp-stl-concurrency PRIVATE Threads::Threads)
