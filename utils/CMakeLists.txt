set(utils_SRCS
	zmalloc.c
	siphash.c
	endianconv.c
	sha1.c)


add_library(utils ${utils_SRCS})
target_link_libraries(utils jemalloc pthread)
