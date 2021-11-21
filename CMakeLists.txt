cmake_minimum_required(VERSION 3.10)

include_directories("${CMAKE_SOURCE_DIR}/src")

link_directories("${CMAKE_SOURCE_DIR}/src")

project(http-server)

file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})
