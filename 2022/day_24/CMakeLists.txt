# Avoid relative paths Policy CMP0076
add_executable(blizzardvalley)

target_include_directories(blizzardvalley PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_sources(  blizzardvalley
  PRIVATE  
    src/Main.cpp 
    src/Grid.cpp
)    

target_link_libraries(blizzardvalley raylib)

add_test( RUNIT blizzardvalley )
