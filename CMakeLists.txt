cmake_minimum_required(VERSION 3.27)
project(GovnoChat)

set(CMAKE_CXX_STANDARD 17)

include_directories(Lib)


IF (WIN32)
    set(BOOST_ROOT "C:/boost-build")
    set(BOOST_INCLUDEDIR "C:/boost-build/include/boost-1_84")
    find_package(Boost REQUIRED)

    if (MINGW)
        link_libraries(ws2_32 wsock32)
    endif ()
    message(STATUS "WIN32")
ENDIF()

find_package(Boost REQUIRED)


add_executable(server Server/server.cpp)
#add_executable(client Client/client.cpp)

if(Boost_FOUND)
    target_include_directories(server PUBLIC ${Boost_INCLUDE_DIR})
    target_link_libraries(server ${Boost_LIBRARIES})
#    target_include_directories(client PUBLIC ${Boost_INCLUDE_DIR})
#    target_link_libraries(client ${Boost_LIBRARIES})
    message(STATUS "Found BOOST ${Boost_VERSION_STRING}")
else()
    message(STATUS "WEBSOCKET BOOST Not Found")
endif()

