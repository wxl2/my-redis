set(base_SRCS
	sds.c
	zmalloc.c
	adlist.c
	endianconv.c)


add_library(base ${base_SRCS})
target_link_libraries(base jemalloc pthread)
