/**
Target architecture, OS;  base types;  base macros.
Copyright (c) 2013 Simon Zolin
*/

#ifndef FF_VER

#define FF_VER  0x01060000

#if defined __LP64__ || defined _WIN64
	#define FF_64
#endif

#if defined __FreeBSD__
	#define FF_BSD
	#include <FFOS/unix/types.h>

#elif defined __linux__
	#define FF_LINUX
	#ifndef __cplusplus
		#define _GNU_SOURCE
	#endif
	#define _LARGEFILE64_SOURCE
	#include <FFOS/unix/types.h>

#elif defined _WIN32 || defined _WIN64 || defined __CYGWIN__
	#define FF_WIN
	#include <FFOS/win/types.h>

#else
	#error This kernel is not supported.
#endif

typedef int ffbool;

#ifdef __cplusplus
	#define FF_EXTN extern "C"
#else
	#define FF_EXTN extern
#endif

#ifdef _DEBUG
	#define FF_ASSERT(expr)  assert(expr)
#else
	#define FF_ASSERT(expr)
#endif

#ifndef FF_MSVC
	#define FF_FUNC __func__
#else
	#define FF_FUNC __FUNCTION__
#endif

#define FFOFF(structType, member)  (((size_t)&((structType *)0)->member))

#define FF_GETPTR(struct_type, member_name, member_ptr) \
	((struct_type*)((byte*)member_ptr - FFOFF(struct_type, member_name)))


#define FF_LITTLE_ENDIAN  1234
#define FF_BIG_ENDIAN  4321
#define FFENDIAN  FF_LITTLE_ENDIAN

#if FFENDIAN == FF_BIG_ENDIAN
	#define ffhton64(i)  (i)
	#define ffhton32(i)  (i)
	#define ffhton16(i)  (i)

#else
#ifdef FF_BSD
	#define ffhton64  bswap64
	#define ffhton32  bswap32
	#define ffhton16  bswap16

#elif defined FF_LINUX || defined __CYGWIN__
	#define ffhton64  bswap_64
	#define ffhton32  bswap_32
	#define ffhton16  bswap_16

#elif defined FF_MSVC
	#define ffhton64  _byteswap_uint64
	#define ffhton32  _byteswap_ulong
	#define ffhton16  _byteswap_ushort
#endif
#endif

static FFINL void ffint_hton16(void *dst, ushort i) {
	*((ushort*)dst) = ffhton16(i);
}
static FFINL void ffint_hton32(void *dst, uint i) {
	*((uint*)dst) = ffhton32(i);
}

static FFINL ushort ffint_ntoh16(const void *p) {
	return ffhton16(*(ushort*)p);
}
static FFINL uint ffint_ntoh32(const void *p) {
	return ffhton32(*(uint*)p);
}

#define FFCNT(ar)  (sizeof(ar) / sizeof(*(ar)))

#define FF_SAFECLOSE(obj, def, func)\
do { \
	if (obj != def) { \
		func(obj); \
		obj = def; \
	} \
} while (0)

#define ffabs(n)  ((n) < 0 ? -(n) : (n))

static FFINL uint64 ffmin64(uint64 i0, uint64 i1) {
	return (i0 > i1 ? i1 : i0);
}

static FFINL size_t ffmin(size_t i0, size_t i1) {
	return (i0 > i1 ? i1 : i0);
}

static FFINL uint64 ffmax64(uint64 i0, uint64 i1) {
	return (i0 < i1 ? i1 : i0);
}

#if defined FF_SAFECAST_SIZE_T && !defined FF_64
	/** Safer cast 'uint64' to 'size_t'. */
	#define FF_TOSIZE(i)  (size_t)ffmin64(i, (size_t)-1)
#else
	#define FF_TOSIZE(i)  (size_t)(i)
#endif

#if defined FF_SAFECAST_SIZE_T && defined FF_64
	/** Safer cast 'size_t' to 'uint'. */
	#define FF_TOINT(i)  (uint)ffmin(i, (uint)-1)
#else
	#define FF_TOINT(i)  (uint)(i)
#endif

#define FF_BIT64(bit)  (1ULL << (bit))

#define FF_LO32(i64)  ((int)((i64) & 0xffffffff))

#define FF_HI32(i64)  ((int)(((i64) >> 32) & 0xffffffff))

#endif

/** Print FF debug messages. */
extern int ffdbg_print(int t, const char *fmt, ...);
