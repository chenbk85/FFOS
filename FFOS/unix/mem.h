/**
Copyright (c) 2013 Simon Zolin
*/

#include <stdlib.h>
#include <errno.h>


#define ffmem_init()

/** Allocate heap memory region. */
#define _ffmem_alloc  malloc

#define _ffmem_calloc  calloc

/** Reallocate heap memory region. */
#define _ffmem_realloc  realloc

/** Deallocate heap memory region. */
#define _ffmem_free  free

/** Allocate aligned memory. */
static FFINL void* _ffmem_align(size_t size, size_t align)
{
	void *buf;
	int e = posix_memalign(&buf, align, size);
	if (e != 0) {
		errno = e;
		return NULL;
	}
	return buf;
}

/** Deallocate aligned memory. */
#define _ffmem_alignfree  free
