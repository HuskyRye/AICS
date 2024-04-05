cmake_minimum_required(VERSION 3.5)
project(cnnl_test)

# set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-Werror -g -fPIC -std=c++14 -pthread")
# add_definitions(-D_GLIBCXX_USE_CXX11_ABI=1)

#set(neuware "/usr/local/neuware")

set(neuware "/torch/neuware_home")

include_directories(${neuware}/include)
include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

link_directories(${neuware}/lib64)

link_libraries(libcnrt.so)
link_libraries(libcnnl.so)
link_libraries(libcndrv.so)

file(GLOB src "${CMAKE_CURRENT_LIST_DIR}/src/*.cc")

add_executable(cnnl_test ${src})
