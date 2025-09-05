# project
cmake_minimum_required(VERSION 3.22)
Include(FetchContent)
set(CMAKE_GENERATOR_PLATFORM Win32)
cmake_policy(SET CMP0048 NEW)

project(ClientExtensions)

# lua

FILE(GLOB lua-sources lua-5.1/src/*.h lua-5.1/src/*.c)
add_library(lua STATIC ${lua-sources})
target_compile_options(lua PRIVATE -w)

set(FT_DISABLE_HARFBUZZ ON CACHE BOOL "" FORCE)
set(FT_DISABLE_BZIP2 ON CACHE BOOL "" FORCE)
set(FT_DISABLE_PNG ON CACHE BOOL "" FORCE)
set(FT_DISABLE_BROTLI ON CACHE BOOL "" FORCE)
set(FT_DISABLE_ZLIB ON CACHE BOOL "" FORCE)

add_subdirectory(CustomPackets)
add_subdirectory(tests)
add_subdirectory(ClientExtensions)

add_subdirectory(freetype)
target_link_libraries(ClientExtensions PRIVATE freetype)
