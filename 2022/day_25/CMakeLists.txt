# Avoid relative paths Policy CMP0076
add_executable(christmasday)

target_include_directories(christmasday PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_sources(  christmasday
  PRIVATE  
    src/Main.cpp     
)    

target_link_libraries(christmasday )

add_test( RUNIT christmasday )
