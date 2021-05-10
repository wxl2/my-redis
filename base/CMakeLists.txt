set(base_SRCS
	sds.c
	adlist.c
	dict.c)

add_definitions(-D DICT_BENCHMARK_MAIN)
add_library(base ${base_SRCS})
target_link_libraries(base utils)
