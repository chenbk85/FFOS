/**
Copyright (c) 2013 Simon Zolin
*/

#include <signal.h>
#include <dlfcn.h>


/** Expand environment variables in a string.
@dst: expanded string
Return 'dst' or a new allocated buffer (if dst == NULL). */
FF_EXTN char* ffenv_expand(char *dst, size_t cap, const char *src);


/** Process fork.
Return child PID.  Return 0 in the child process.
Return -1 on error. */
#define ffps_fork  fork

/** Create a new process.
Return FF_BADFD on error. */
FF_EXTN fffd ffps_exec(const char *filename, const char **argv, const char **env);

/** Get process ID by process handle. */
#define ffps_id(h)  ((uint)(h))

/** Kill the process. */
#define ffps_kill(h)  kill(h, SIGKILL)

/** Send signal to a process. */
#define ffps_sig(h, sig)  kill(h, sig)

/** Close process handle. */
#define ffps_close(h)  (0)

/** Wait for the process. */
FF_EXTN int ffps_wait(fffd h, uint, int *exit_code);

/** Get the current process handle. */
#define ffps_curhdl  getpid

/** Get ID of the current process. */
#define ffps_curid  getpid

/** Get filename of the current process. */
static FFINL const char* ffps_filename(char *name, size_t cap, const char *argv0)
{
	return argv0;
}

/** Exit the current process. */
#define ffps_exit  _exit


#define FFDL_EXT  "so"

typedef void * ffdl;
typedef void * ffdl_proc;

/** Open library.
Return NULL on error. */
#define ffdl_open(filename, flags)  dlopen(filename, (flags) | RTLD_LAZY)

/** Get the function address from the library.
Return NULL on error. */
#define ffdl_addr  dlsym

/** Get last error message. */
#define ffdl_errstr  dlerror

/** Close the library. */
#define ffdl_close  dlclose


typedef void * ffsysconf;

/** Init sysconf structure. */
#define ffsc_init(sc) ((void)sc)

/** Get value from system config. */
#define ffsc_get(sc, name)  sysconf(name)
