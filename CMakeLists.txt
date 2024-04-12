cmake_minimum_required(VERSION 3.26)
project(Tutorial)

set(CMAKE_CXX_STANDARD 17)

include_directories(Lib)

add_executable(server Server/server.cpp)
add_executable(client Client/client.cpp)