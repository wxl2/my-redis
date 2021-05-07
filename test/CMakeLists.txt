add_executable(test_sds test_sds.c)
target_link_libraries(test_sds base)

add_executable(test_endianconv test_endianconv.c)
target_link_libraries(test_endianconv base)

add_executable(test_adlist test_adlist.c )
target_link_libraries(test_adlist base)
