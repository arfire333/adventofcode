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
