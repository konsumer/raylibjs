cmake_minimum_required(VERSION 3.5)

find_package(PkgConfig REQUIRED)

project(raylibjs LANGUAGES C)

set(CMAKE_C_STANDARD 11)
# set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# set(CMAKE_C_STANDARD_REQUIRED ON)
# set(CMAKE_C_EXTENSIONS ON)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

if (CMAKE_BUILD_TYPE MATCHES "Debug")
    list(APPEND raylibjs_cflags -ggdb -O0 -fno-omit-frame-pointer)
endif()

message(STATUS "Building in ${CMAKE_BUILD_TYPE} mode")
message(STATUS "Building with ${CMAKE_C_COMPILER_ID} ${CMAKE_C_COMPILER_VERSION} on ${CMAKE_SYSTEM}")

pkg_check_modules(raylib REQUIRED IMPORTED_TARGET raylib)

# is there a better way to link to system-version?
set(quickjs_SOURCE_DIR "/usr/local/Cellar/quickjs/2021-03-27/include/quickjs/")
set(quickjs_LIB_DIR "/usr/local/Cellar/quickjs/2021-03-27/lib/quickjs/")

add_library(raylibjs SHARED src/raylibjs.c)
set_target_properties(raylibjs PROPERTIES PREFIX "")
set_target_properties(raylibjs PROPERTIES SUFFIX ".so")
target_link_directories(raylibjs PRIVATE "${quickjs_LIB_DIR}")
target_link_libraries(raylibjs PkgConfig::raylib quickjs)
target_include_directories(raylibjs PUBLIC ${raylib_INCLUDE_DIRS} "${quickjs_SOURCE_DIR}")
target_compile_options(raylibjs PUBLIC ${raylib_CFLAGS_OTHER})

