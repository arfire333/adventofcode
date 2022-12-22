# Avoid relative paths Policy CMP0076
add_executable(monkeymap)

target_include_directories(monkeymap PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_sources(  monkeymap
  PRIVATE  
    src/Main.cpp 
    src/Grid.cpp
)    

target_link_libraries(monkeymap raylib)

add_test( RUNIT monkeymap )

file( COPY ${CMAKE_SOURCE_DIR}/2022/day_22/day_22.input 
  DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)