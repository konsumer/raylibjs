cmake_minimum_required(VERSION 3.5)

find_package(PkgConfig REQUIRED)

project(raylibqjs LANGUAGES C)

set(CMAKE_C_STANDARD 11)
# set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# set(CMAKE_C_STANDARD_REQUIRED ON)
# set(CMAKE_C_EXTENSIONS ON)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

if (CMAKE_BUILD_TYPE MATCHES "Debug")
    list(APPEND raylibqjs_cflags -ggdb -O0 -fno-omit-frame-pointer)
endif()

message(STATUS "Building in ${CMAKE_BUILD_TYPE} mode")
message(STATUS "Building with ${CMAKE_C_COMPILER_ID} ${CMAKE_C_COMPILER_VERSION} on ${CMAKE_SYSTEM}")

pkg_check_modules(raylib REQUIRED IMPORTED_TARGET raylib)

# is there a better way to link to system-version? It didn't come with pkg-config
# probly some better way to build this with cmake...
set(quickjs_SOURCE_DIR "/usr/local/Cellar/quickjs/2021-03-27")
set(quickjs_INCLUDE_DIR "${quickjs_SOURCE_DIR}/include/quickjs/")
set(quickjs_LIB_DIR "${quickjs_SOURCE_DIR}/lib/quickjs/")

add_library(raylibqjs SHARED src/raylibqjs.c)
set_target_properties(raylibqjs PROPERTIES PREFIX "" SUFFIX ".so")
target_link_directories(raylibqjs PRIVATE "${quickjs_LIB_DIR}")
target_link_libraries(raylibqjs PkgConfig::raylib quickjs)
target_include_directories(raylibqjs PUBLIC ${raylib_INCLUDE_DIRS} "${quickjs_INCLUDE_DIR}")
target_compile_options(raylibqjs PUBLIC ${raylib_CFLAGS_OTHER})

