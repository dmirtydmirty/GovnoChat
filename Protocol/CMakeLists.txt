cmake_minimum_required(VERSION 3.25)
project(Protocol)

set(CMAKE_CXX_STANDARD 20)

set(Boost_USE_STATIC_LIBS   ON)

find_package(Boost REQUIRED)

set(SOURCES Source/Protocol.cpp
            )

add_library(protocol ${SOURCES})

if(Boost_FOUND)
    target_include_directories(protocol PUBLIC ${Boost_INCLUDE_DIR})
    target_link_libraries(protocol ${Boost_LIBRARIES})
    message(STATUS "Found BOOST ${Boost_VERSION_STRING}")
else()
    message(STATUS "BOOST Not Found")
endif()

