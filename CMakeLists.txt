cmake_minimum_required(VERSION 3.0)

project( AdventOfCodeBonusRound )

if(${CMAKE_VERSION} VERSION_GREATER "3.24.0")
    cmake_policy( SET CMP0135 NEW )    
endif()

set(CMAKE_CXX_STANDARD 20)
enable_testing()
include(FetchContent)

# Let CMake search for a raylib-config.cmake
find_package(raylib 4.2 QUIET) 
# If there's none, fetch and build raylib
if (NOT raylib_FOUND)   
  FetchContent_Declare(
    raylib
    URL https://github.com/raysan5/raylib/archive/refs/tags/4.2.0.tar.gz
  )

  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
    set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(raylib)

    # build raylib
    add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
  endif()
endif()

add_subdirectory( 2022/day_14/bonus )
add_subdirectory( 2022/day_22/bonus )
add_subdirectory( 2022/day_23/bonus )


