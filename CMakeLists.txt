cmake_minimum_required(VERSION 3.5)
project(List LANGUAGES CXX)

set(THREADS_PREFER_PTHREAD_FLAG ON)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS  "-Ofast")

find_package(Threads REQUIRED)

set(
    core-files
    matrix.cpp
)

add_executable(
    main
    ${core-files}
)

set(
    binaries
    main
)

foreach(target ${BINARIES})
    if ( CMAKE_CXX_COMPILER_ID MATCHES "Clang|AppleClang|GNU" )
        target_compile_options( ${target} PRIVATE -Wall -Wextra -Wunreachable-code -Wpedantic)
    endif()
    if ( CMAKE_CXX_COMPILER_ID MATCHES "MSVC" )
        target_compile_options( ${target} PRIVATE /W4 )
        target_compile_options( ${target} PRIVATE /utf-8 )
    endif()
endforeach()
