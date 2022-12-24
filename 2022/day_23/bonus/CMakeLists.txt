# Avoid relative paths Policy CMP0076
add_executable(elfsplit)

target_include_directories(elfsplit PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_sources(  elfsplit
  PRIVATE  
    src/Main.cpp 
    src/Grid.cpp
)    

target_link_libraries(elfsplit raylib)

add_test( RUNIT elfsplit )

file( COPY ${CMAKE_SOURCE_DIR}/2022/day_23/day_23.input 
  DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)

file( COPY ${CMAKE_SOURCE_DIR}/2022/day_23/bonus/resources/elf.png 
  DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug/resources)