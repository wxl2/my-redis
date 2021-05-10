project(redis-for-x86)
 
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0 -Wall -pthread --std=c99")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./bin)
link_directories(/usr/local/lib)
include_directories(/usr/local/include)
aux_source_directory(. DIRSRCS)
include_directories(./ ./base ./test ./utils)

add_subdirectory(base)
add_subdirectory(utils)
add_subdirectory(test)

add_executable(redis main.c)
target_link_libraries(redis base)
