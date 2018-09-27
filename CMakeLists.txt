cmake_minimum_required(VERSION 2.8)

project(vault_client)

set(CMAKE_CXX_STANDARD 11)

set(INSTALL_DIR /usr/local/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
include_directories(include)

add_subdirectory(src)
