cmake_minimum_required(VERSION 3.25)
project(GovnoChatServer)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(Server)

add_executable(ChatServer main.cpp)
target_link_directories(ChatServer PRIVATE
                            Server/Inculude
                            )
target_link_libraries(ChatServer PRIVATE
                            tcp_server
                            )
