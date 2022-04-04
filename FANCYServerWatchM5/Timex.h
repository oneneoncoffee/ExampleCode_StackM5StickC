#ifndef _TIME_H_
#define _TIME_H_
#include "_ansi.h"
#include <sys/reent.h>
#define __need_size_t
#define __need_NULL
#include <stddef.h>
#include <machine/time.h>
#ifndef _CLOCKS_PER_SEC_
#define _CLOCKS_PER_SEC_ 1000
#endif
#define CLOCKS_PER_SEC _CLOCKS_PER_SEC_
#define CLK_TCK CLOCKS_PER_SEC
#include <sys/types.h>

_BEGIN_STD_C

struct tm
{
  int  tm_sec;
  int tm_min;
  int tm_hour;
  int tm_mday;
  int tm_mon;
  int tm_year;
  int tm_wday;
  int tm_yday;
  int tm_isdst;
#ifdef __TM_GMTOFF
  long  __TM_GMTOFF;
#endif
#ifdef __TM_ZONE
  const char *__TM_ZONE;
#endif
};

clock_t    _EXFUN(clock,    (void));
double     _EXFUN(difftime, (time_t _time2, time_t _time1));
time_t     _EXFUN(mktime,   (struct tm *_timeptr));
time_t     _EXFUN(time,     (time_t *_timer));
#ifndef _REENT_ONLY
char    *_EXFUN(asctime,  (const struct tm *_tblock));
char    *_EXFUN(ctime,    (const time_t *_time));
struct tm *_EXFUN(gmtime,   (const time_t *_timer));
struct tm *_EXFUN(localtime,(const time_t *_timer));
#endif
size_t     _EXFUN(strftime, (char *__restrict _s,
           size_t _maxsize, const char *__restrict _fmt,
           const struct tm *__restrict _t));
char    *_EXFUN(asctime_r,  (const struct tm *__restrict,
         char *__restrict));
char    *_EXFUN(ctime_r,  (const time_t *, char *));
struct tm *_EXFUN(gmtime_r, (const time_t *__restrict,
         struct tm *__restrict));
struct tm *_EXFUN(localtime_r,  (const time_t *__restrict,
         struct tm *__restrict));
_END_STD_C

#ifdef __cplusplus
extern "C" {
#endif
#ifndef __STRICT_ANSI__
char      *_EXFUN(strptime,     (const char *__restrict,
         const char *__restrict,
         struct tm *__restrict));
_VOID      _EXFUN(tzset,  (_VOID));
_VOID      _EXFUN(_tzset_r, (struct _reent *));
typedef struct __tzrule_struct
{
  char ch;
  int m;
  int n;
  int d;
  int s;
  time_t change;
  long offset; 
} __tzrule_type;
typedef struct __tzinfo_struct
{
  int __tznorth;
  int __tzyear;
  __tzrule_type __tzrule[2];
} __tzinfo_type;
__tzinfo_type *_EXFUN (__gettzinfo, (_VOID));
#ifdef HAVE_GETDATE
#ifndef _REENT_ONLY
#define getdate_err (*__getdate_err())
int *_EXFUN(__getdate_err,(_VOID));
struct tm * _EXFUN(getdate, (const char *));
#endif 
int   _EXFUN(getdate_r, (const char *, struct tm *));
#endif 
extern __IMPORT long _timezone;
extern __IMPORT int _daylight;
extern __IMPORT char *_tzname[2];
#ifndef tzname
#define tzname _tzname
#endif
#endif 
#ifdef __cplusplus
}
#endif
#include <sys/features.h>
#ifdef __CYGWIN__
#include <cygwin/time.h>
#endif 
#if defined(_POSIX_TIMERS)
#include <signal.h>
#ifdef __cplusplus
extern "C" {
#endif
int _EXFUN(clock_settime, (clockid_t clock_id, const struct timespec *tp));
int _EXFUN(clock_gettime, (clockid_t clock_id, struct timespec *tp));
int _EXFUN(clock_getres,  (clockid_t clock_id, struct timespec *res));
int _EXFUN(timer_create,
    (clockid_t clock_id,
  struct sigevent *__restrict evp,
  timer_t *__restrict timerid));
int _EXFUN(timer_delete, (timer_t timerid));
int _EXFUN(timer_settime,
  (timer_t timerid, int flags,
  const struct itimerspec *__restrict value,
  struct itimerspec *__restrict ovalue));
int _EXFUN(timer_gettime, (timer_t timerid, struct itimerspec *value));
int _EXFUN(timer_getoverrun, (timer_t timerid));
int _EXFUN(nanosleep, (const struct timespec  *rqtp, struct timespec *rmtp));
#ifdef __cplusplus
}
#endif
#endif 
#if defined(_POSIX_CLOCK_SELECTION)
#ifdef __cplusplus
extern "C" {
#endif
int _EXFUN(clock_nanosleep,
  (clockid_t clock_id, int flags, const struct timespec *rqtp,
   struct timespec *rmtp));
#ifdef __cplusplus
}
#endif
#endif 
#ifdef __cplusplus
extern "C" {
#endif
#define CLOCK_ENABLED  1  
#define CLOCK_DISABLED 0 
#define CLOCK_ALLOWED  1 
#define CLOCK_DISALLOWED 0 
#define CLOCK_REALTIME (clockid_t)1
#define TIMER_ABSTIME 4
#if defined(_POSIX_CPUTIME)
#define CLOCK_PROCESS_CPUTIME_ID (clockid_t)2
#endif
#if defined(_POSIX_THREAD_CPUTIME)
#define CLOCK_THREAD_CPUTIME_ID (clockid_t)3
#endif
#if defined(_POSIX_MONOTONIC_CLOCK)
#define CLOCK_MONOTONIC (clockid_t)4
#endif
#if defined(_POSIX_CPUTIME)
int _EXFUN(clock_getcpuclockid, (pid_t pid, clockid_t *clock_id));
#endif 
#if defined(_POSIX_CPUTIME) || defined(_POSIX_THREAD_CPUTIME)
int _EXFUN(clock_setenable_attr, (clockid_t clock_id, int attr));
int _EXFUN(clock_getenable_attr, (clockid_t clock_id, int *attr));
#endif
#ifdef __cplusplus
}
#endif
#endif 
