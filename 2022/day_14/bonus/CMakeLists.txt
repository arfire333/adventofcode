# Avoid relative paths Policy CMP0076
add_executable(christmassand)

target_include_directories(christmassand PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_sources(  christmassand 
  PRIVATE  
    src/Main.cpp 
    src/Grid.cpp
)    

target_link_libraries(christmassand raylib)

add_test( RUNIT christmassand )