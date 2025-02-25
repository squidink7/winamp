/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* ***** BEGIN LICENSE BLOCK *****
* Version: MPL 1.1/GPL 2.0/LGPL 2.1
*
* The contents of this file are subject to the Mozilla Public License Version
* 1.1 (the "License"); you may not use this file except in compliance with
* the License. You may obtain a copy of the License at
* http://www.mozilla.org/MPL/
*
* Software distributed under the License is distributed on an "AS IS" basis,
* WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
* for the specific language governing rights and limitations under the
* License.
*
* The Original Code is the Netscape Portable Runtime (NSPR).
*
* The Initial Developer of the Original Code is
* Netscape Communications Corporation.
* Portions created by the Initial Developer are Copyright (C) 1998-2000
* the Initial Developer. All Rights Reserved.
*
* Contributor(s):
*
* Alternatively, the contents of this file may be used under the terms of
* either the GNU General Public License Version 2 or later (the "GPL"), or
* the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
* in which case the provisions of the GPL or the LGPL are applicable instead
* of those above. If you wish to allow use of your version of this file only
* under the terms of either the GPL or the LGPL, and not to allow others to
* use your version of this file under the terms of the MPL, indicate your
* decision by deleting the provisions above and replace them with the notice
* and other provisions required by the GPL or the LGPL. If you do not delete
* the provisions above, a recipient may use your version of this file under
* the terms of any one of the MPL, the GPL or the LGPL.
*
* ***** END LICENSE BLOCK ***** */

#ifndef pr_sunos4_h___
#define pr_sunos4_h___

#ifndef SVR4

/*
** Hodge podge of random missing prototypes for the Sunos4 system
*/
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <limits.h>
#include <sys/types.h>

#define PATH_MAX _POSIX_PATH_MAX

struct timeval;
struct timezone;
struct itimerval;
struct sockaddr;
struct stat;
struct tm;

/* ctype.h */
extern int tolower(int);
extern int toupper(int);

/* errno.h */
extern char *sys_errlist[];
extern int sys_nerr;

#define strerror(e) sys_errlist[((unsigned)(e) < sys_nerr) ? e : 0]

extern void perror(const char *);

/* getopt */
extern char *optarg;
extern int optind;
extern int getopt(int argc, char **argv, char *spec);

/* math.h */
extern int srandom(long val);
extern long random(void);

/* memory.h */
#define memmove(to,from,len) bcopy((char*)(from),(char*)(to),len)

extern void bcopy(const char *, char *, int);

/* signal.h */
/*
** SunOS4 sigaction hides interrupts by default, so we can safely define
** SA_RESTART to 0.
*/
#define SA_RESTART 0

/* stdio.h */
extern int printf(const char *, ...);
extern int fprintf(FILE *, const char *, ...);
extern int vprintf(const char *, va_list);
extern int vfprintf(FILE *, const char *, va_list);
extern char *vsprintf(char *, const char *, va_list);
extern int scanf(const char *, ...);
extern int sscanf(const char *, const char *, ...);
extern int fscanf(FILE *, const char *, ...);
extern int fgetc(FILE *);
extern int fputc(int, FILE *);
extern int fputs(const char *, FILE *);
extern int puts(const char *);
extern int fread(void *, size_t, size_t, FILE *);
extern int fwrite(const char *, int, int, FILE *);
extern int fseek(FILE *, long, int);
extern long ftell(FILE *);
extern int rewind(FILE *);
extern int fflush(FILE *);
extern int _flsbuf(unsigned char, FILE *);
extern int fclose(FILE *);
extern int remove(const char *);
extern int setvbuf(FILE *, char *, int, size_t);
extern int system(const char *);
extern FILE *popen(const char *, const char *);
extern int pclose(FILE *);

/* stdlib.h */
#define strtoul strtol

extern int isatty(int fildes);
extern long strtol(const char *, char **, int);
extern int putenv(const char *);
extern void srand48(long);
extern long lrand48(void);
extern double drand48(void);

/* string.h */
extern int strcasecmp(const char *, const char *);
extern int strncasecmp(const char *, const char *, size_t);
extern int strcoll(const char *, const char *);

/* time.h */
extern time_t mktime(struct tm *);
extern size_t strftime(char *, size_t, const char *, const struct tm *);
extern int gettimeofday(struct timeval *, struct timezone *);
extern int setitimer(int, struct itimerval *, struct itimerval *);
extern time_t time(time_t *);
extern time_t timegm(struct tm *);
extern struct tm *localtime(const time_t *);
extern struct tm *gmtime(const time_t *);

/* unistd.h */
extern int rename(const char *, const char *);
extern int ioctl(int, int, int *arg);
extern int connect(int, struct sockaddr *, int);
extern int readlink(const char *, char *, int);
extern int symlink(const char *, const char *);
extern int ftruncate(int, off_t);
extern int fchmod(int, mode_t);
extern int fchown(int, uid_t, gid_t);
extern int lstat(const char *, struct stat *);
extern int fstat(int, struct stat *);
extern int select(int, fd_set *, fd_set *, fd_set *, struct timeval *);
extern int gethostname(char *, int);
extern char *getwd(char *);
extern int getpagesize(void);

#endif /* SVR4 */

#endif /* pr_sunos4_h___ */
