	/***************************************************************************
    *                                  _   _ ____  _
    *  Project                     ___| | | |  _ \| |
    *                             / __| | | | |_) | |
    *                            | (__| |_| |  _ <| |___
    *                             \___|\___/|_| \_\_____|
    *
    * Copyright (C) 1998 - 2016, Daniel Stenberg, <daniel@haxx.se>, et al.
    *
    * This software is licensed as described in the file COPYING, which
    * you should have received as part of this distribution. The terms
    * are also available at https://curl.haxx.se/docs/copyright.html.
    *
    * You may opt to use, copy, modify, merge, publish, distribute and/or sell
    * copies of the Software, and permit persons to whom the Software is
    * furnished to do so, under the terms of the COPYING file.
    *
    * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
    * KIND, either express or implied.
    *
    ***************************************************************************/
	
	#include "timeval.h"
	
	#if defined(WIN32) && !defined(MSDOS)
	
	struct timeval curlx_tvnow(void)
	{
    /*
    ** GetTickCount() is available on _all_ Windows versions from W95 up
    ** to nowadays. Returns milliseconds elapsed since last system boot,
    ** increases monotonically and wraps once 49.7 days have elapsed.
    */
    struct timeval now;
	#if !defined(_WIN32_WINNT) || !defined(_WIN32_WINNT_VISTA) || \
(_WIN32_WINNT < _WIN32_WINNT_VISTA)
    DWORD milliseconds = GetTickCount();
    now.tv_sec = milliseconds / 1000;
    now.tv_usec = (milliseconds % 1000) * 1000;
	#else
    ULONGLONG milliseconds = GetTickCount64();
    now.tv_sec = (long) (milliseconds / 1000);
    now.tv_usec = (long) (milliseconds % 1000) * 1000;
	#endif
	
    return now;
	}
	
	#elif defined(HAVE_CLOCK_GETTIME_MONOTONIC)
	
	struct timeval curlx_tvnow(void)
	{
    /*
    ** clock_gettime() is granted to be increased monotonically when the
    ** monotonic clock is queried. Time starting point is unspecified, it
    ** could be the system start-up time, the Epoch, or something else,
    ** in any case the time starting point does not change once that the
    ** system has started up.
    */
    struct timeval now;
    struct timespec tsnow;
    if(0 == clock_gettime(CLOCK_MONOTONIC, &tsnow)) {
now.tv_sec = tsnow.tv_sec;
now.tv_usec = tsnow.tv_nsec / 1000;
    }
    /*
    ** Even when the configure process has truly detected monotonic clock
    ** availability, it might happen that it is not actually available at
    ** run-time. When this occurs simply fallback to other time source.
    */
	#ifdef HAVE_GETTIMEOFDAY
    else
(void)gettimeofday(&now, NULL);
	#else
    else {
now.tv_sec = (long)time(NULL);
now.tv_usec = 0;
    }
	#endif
    return now;
	}
	
	#elif defined(HAVE_GETTIMEOFDAY)
	
	struct timeval curlx_tvnow(void)
	{
    /*
    ** gettimeofday() is not granted to be increased monotonically, due to
    ** clock drifting and external source time synchronization it can jump
    ** forward or backward in time.
    */
    struct timeval now;
    (void)gettimeofday(&now, NULL);
    return now;
	}
	
	#else
	
	struct timeval curlx_tvnow(void)
	{
    /*
    ** time() returns the value of time in seconds since the Epoch.
    */
    struct timeval now;
    now.tv_sec = (long)time(NULL);
    now.tv_usec = 0;
    return now;
	}
	
	#endif
	
	/*
    * Make sure that the first argument is the more recent time, as otherwise
    * we'll get a weird negative time-diff back...
    *
    * Returns: the time difference in number of milliseconds. For large diffs it
    * returns 0x7fffffff on 32bit time_t systems.
    */
	time_t curlx_tvdiff(struct timeval newer, struct timeval older)
	{
	#if SIZEOF_TIME_T < 8
    /* for 32bit time_t systems, add a precaution to avoid overflow for really
big time differences */
    time_t diff = newer.tv_sec-older.tv_sec;
    if(diff >= (0x7fffffff/1000))
return 0x7fffffff;
	#endif
    return (newer.tv_sec-older.tv_sec)*1000+
(time_t)(newer.tv_usec-older.tv_usec)/1000;
	}
	
	/*
    * Same as curlx_tvdiff but with full usec resolution.
    *
    * Returns: the time difference in seconds with subsecond resolution.
    */
	double curlx_tvdiff_secs(struct timeval newer, struct timeval older)
	{
    if(newer.tv_sec != older.tv_sec)
return (double)(newer.tv_sec-older.tv_sec)+
(double)(newer.tv_usec-older.tv_usec)/1000000.0;
    else
return (double)(newer.tv_usec-older.tv_usec)/1000000.0;
	}
	
	/* return the number of seconds in the given input timeval struct */
	time_t Curl_tvlong(struct timeval t1)
	{
    return t1.tv_sec;
	}
	