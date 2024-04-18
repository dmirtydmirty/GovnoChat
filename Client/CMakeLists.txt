cmake_minimum_required(VERSION 3.27)
project(GovnoChat)

set(CMAKE_CXX_STANDARD 17)

set(Boost_USE_STATIC_LIBS   ON)

IF (WIN32)
#    set(CMAKE_PREFIX_PATH "C:/Qt/Qt5.12.12/5.12.12/mingw73_6/lib/cmake")
    set(BOOST_ROOT "C:/boost-build")
    set(BOOST_INCLUDEDIR "C:/boost-build/include/boost-1_84")
    find_package(Boost REQUIRED)

    if (MINGW)
        link_libraries(ws2_32 wsock32)
    endif ()
    message(STATUS "WIN32")
ENDIF ()

find_package(Boost REQUIRED)

find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)


set(SOURCE_FILES client.cpp)
add_executable(client ${SOURCE_FILES})

set(CMAKE_EXE_LINKER_FLAGS " -static")
target_link_libraries(client -static-libgcc -static-libstdc++)

target_link_libraries(client  Qt5::Core)
target_link_libraries(client Qt5::Gui)
target_link_libraries(client Qt5::Widgets)

if(Boost_FOUND)
    target_include_directories(client PUBLIC ${Boost_INCLUDE_DIR})
    target_link_libraries(client ${Boost_LIBRARIES})
    message(STATUS "Found BOOST ${Boost_VERSION_STRING}")
else()
    message(STATUS "WEBSOCKET BOOST Not Found")
endif()