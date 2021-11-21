cmake_minimum_required(VERSION 3.10)
project(http-server VERSION 1.0 LANGUAGES CXX)

################################################################################
##
## Compiler options
##
################################################################################

if ((CMAKE_CXX_COMPILER_ID MATCHES "GNU") OR (CMAKE_CXX_COMPILER_ID MATCHES "Clang"))
    add_compile_options(
        -Werror

        -Wall
        -Wextra
        -Wpedantic

        -Wcast-align
        -Wcast-qual
        -Wconversion
        -Wctor-dtor-privacy
        -Wenum-compare
        -Wfloat-equal
        -Wnon-virtual-dtor
        -Wold-style-cast
        -Woverloaded-virtual
        -Wredundant-decls
        -Wsign-conversion
        -Wsign-promo
    )
endif()

################################################################################
##
## Core library includes
##
################################################################################

add_library(core INTERFACE)
target_include_directories(core INTERFACE
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
target_compile_features(core INTERFACE cxx_std_17)

add_library(Core::core ALIAS core)

################################################################################
##
## Core library sources
##
################################################################################

add_library(core_src src/core/http.cpp)
target_link_libraries(core_src PUBLIC core)

add_library(Core::core_src ALIAS core_src)

################################################################################
##
## Server
##
################################################################################

add_executable(http-server src/main.cpp)
target_link_libraries(http-server PRIVATE core_src)
