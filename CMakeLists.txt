cmake_minimum_required(VERSION 3.5)

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)

project(raylibqjs LANGUAGES C)

set(CMAKE_C_STANDARD 11)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

message(STATUS "Building in ${CMAKE_BUILD_TYPE} mode")
message(STATUS "Building with ${CMAKE_C_COMPILER_ID} ${CMAKE_C_COMPILER_VERSION} on ${CMAKE_SYSTEM}")

FetchContent_Declare(
    qjs
    GIT_REPOSITORY "https://github.com/napi-bindings/quickjs-build.git"
    GIT_TAG "master"
    GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(qjs)

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # don't build the supplied example games
FetchContent_Declare(
    raylib
    GIT_REPOSITORY "https://github.com/raysan5/raylib.git"
    GIT_TAG "master"
    GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(raylib)

add_library(raylibqjs SHARED src/raylibqjs.c)
set_target_properties(raylibqjs PROPERTIES PREFIX "" SUFFIX ".so")
target_link_libraries(raylibqjs raylib qjs)

