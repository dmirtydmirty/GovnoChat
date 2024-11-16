cmake_minimum_required(VERSION 3.25)
project(Server)

set(CMAKE_CXX_STANDARD 20)

set(Boost_USE_STATIC_LIBS   ON)

find_package(Boost REQUIRED)

set(SOURCES Source/server.cpp)

add_library(tcp_server ${SOURCES})

set(CMAKE_EXE_LINKER_FLAGS " -static")

target_link_libraries(tcp_server -static-libgcc -static-libstdc++)
target_link_directories(tcp_server PUBLIC Include)

if(Boost_FOUND)
    target_include_directories(tcp_server PUBLIC ${Boost_INCLUDE_DIR})
    target_link_libraries(tcp_server ${Boost_LIBRARIES})
    message(STATUS "Found BOOST ${Boost_VERSION_STRING}")
else()
    message(STATUS "WEBSOCKET BOOST Not Found")
endif()

