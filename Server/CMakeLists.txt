cmake_minimum_required(VERSION 3.25)
project(Server)

set(CMAKE_CXX_STANDARD 20)

set(Boost_USE_STATIC_LIBS   ON)

find_package(Boost REQUIRED)

set(SOURCES Source/Server.cpp
            Source/Session.cpp
            Source/Acceptor.cpp
            Source/ChatService.cpp
            )

add_library(server ${SOURCES})

if(Boost_FOUND)
    target_include_directories(server PUBLIC ${Boost_INCLUDE_DIR})
    target_link_libraries(server ${Boost_LIBRARIES})
    message(STATUS "Found BOOST ${Boost_VERSION_STRING}")
else()
    message(STATUS "WEBSOCKET BOOST Not Found")
endif()

