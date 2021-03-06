/**
Timer.
Copyright (c) 2013 Simon Zolin
*/

#pragma once

#include <FFOS/queue.h>

#if defined FF_UNIX
#include <FFOS/unix/tmr.h>

#elif defined FF_WIN
#include <FFOS/win/tmr.h>
#endif

/** Start timer.
@period_ms: if negative, timer will fire just once.
Note: Windows: a separate thread is created that starts a kernel timer and sleeps in an alertable
 state to process timer events. */
FF_EXTN int fftmr_start(fftmr tmr, fffd kq, void *udata, int period_ms);
