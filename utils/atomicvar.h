#include <pthread.h>

#ifndef __ATOMIC_VAR_H
#define __ATOMIC_VAR_H
#if defined(HAVE_ATOMIC)

#define atomicIncr(var,count) __sync_add_and_fetch(&var,(count))
#define atomicGetIncr(var,oldvalue_var,count) do { \
	    oldvalue_var = __sync_fetch_and_add(&var,(count)); \
} while(0)
#define atomicDecr(var,count) __sync_sub_and_fetch(&var,(count))
#define atomicGet(var,dstvar) do { \
	    dstvar = __sync_sub_and_fetch(&var,0); \
} while(0)
#define atomicSet(var,value) do { \
	    while(!__sync_bool_compare_and_swap(&var,var,value)); \
} while(0)
#define REDIS_ATOMIC_API "sync-builtin

#endif
#endif
