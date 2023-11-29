cmake_minimum_required(VERSION 3.5)

project(raylibjs LANGUAGES C)

if (NOT CMAKE_BUILD_TYPE)
    message(STATUS "No build type selected, default to Release")
    set(CMAKE_BUILD_TYPE "Release")
endif()
list(APPEND raylibjs_cflags -Wall -g)
if (CMAKE_BUILD_TYPE MATCHES "Debug")
    list(APPEND raylibjs_cflags -ggdb -O0 -fno-omit-frame-pointer)
endif()

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # don't build the supplied example games

FetchContent_Declare(
    raylib
    GIT_REPOSITORY "https://github.com/raysan5/raylib.git"
    GIT_TAG "master"
    GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(raylib)

FetchContent_Declare(
    quickjs
    GIT_REPOSITORY "https://github.com/mezum/quickjs-cmake.git"
    GIT_TAG "master"
    GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(quickjs)

message(STATUS "Building in ${CMAKE_BUILD_TYPE} mode")
message(STATUS "Building with ${CMAKE_C_COMPILER_ID} ${CMAKE_C_COMPILER_VERSION} on ${CMAKE_SYSTEM}")

set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_C_STANDARD 11)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(raylibjs SHARED src/raylib.c)
set_target_properties(raylibjs PROPERTIES PREFIX "")

# I think quickjs needs this?
set_target_properties(raylibjs PROPERTIES SUFFIX ".so")

target_compile_options(raylibjs PRIVATE ${raylibjs_cflags})
target_link_libraries(raylibjs quickjs raylib)