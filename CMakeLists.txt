cmake_minimum_required(VERSION 3.20)
project(vkr)

set(CMAKE_CXX_STANDARD 20)

#find_package(stxxl)

add_executable(vkr main.cpp queue.h linear_function.h defines.h with_multiplicity.h processor.h)
#target_link_libraries(vkr PRIVATE stxxl)
#target_include_directories(vkr PRIVATE ${STXXL_INCLUDE_DIRS})