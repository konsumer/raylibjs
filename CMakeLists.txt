cmake_minimum_required(VERSION 3.5)

project(raylibjs LANGUAGES C)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

list(APPEND raylibjs_cflags -Wall -g)
if (CMAKE_BUILD_TYPE MATCHES "Debug")
    list(APPEND raylibjs_cflags -ggdb -O0 -fno-omit-frame-pointer)
endif()

message(STATUS "Building in ${CMAKE_BUILD_TYPE} mode")
message(STATUS "Building with ${CMAKE_C_COMPILER_ID} ${CMAKE_C_COMPILER_VERSION} on ${CMAKE_SYSTEM}")

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

include(ExternalProject)
ExternalProject_Add(
  quickjs
  GIT_REPOSITORY "https://github.com/bellard/quickjs.git"
  EXCLUDE_FROM_ALL TRUE
  BUILD_COMMAND make
  STEP_TARGETS build
)

set(quickjs_BINARY_DIR "${CMAKE_BINARY_DIR}/quickjs-prefix")
set(quickjs_SOURCE_DIR "${CMAKE_BINARY_DIR}/quickjs-prefix")

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