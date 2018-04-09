/*! \file os.h
  The intent of this header file is to put operating system and compiler
  specific portability changes in one place.

 \author Jon A. Lambert
 \date 01/12/2005
 \version 0.3
 \remarks
  This source code copyright (C) 2004,2005 by Jon A. Lambert
  All rights reserved.

*/

#ifndef OS_H
#define OS_H

/*-----------------------------------------------------------------------*/
/* COMMON DEFINITIONS SECTION                                            */
/*-----------------------------------------------------------------------*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <stdarg.h>
#include <signal.h>
#include <time.h>               /* Gentoo complains */
#include <sys/types.h>
#include <limits.h>
#include <fcntl.h>
#include <assert.h>
#include <sys/stat.h>

/*-----------------------------------------------------------------------*/
/* WINDOWS DEFINITIONS SECTION                                           */
/*-----------------------------------------------------------------------*/
#ifdef WIN32                    /* Windows portability */

#define ARG_MAX (16384 - 256)
#define FD_SETSIZE 1024
#define NOFILE FD_SETSIZE
#include <winsock2.h>
#include <process.h>
#if defined __LCC__ || defined _MSC_VER
#include <direct.h>
#else
#include <dirent.h>
#endif
#if defined __BORLANDC__
#include <dir.h>
#endif
#define EWOULDBLOCK       WSAEWOULDBLOCK
#define EADDRINUSE        WSAEADDRINUSE
#define ETIMEDOUT         WSAETIMEDOUT
#define ECONNRESET        WSAECONNRESET
#define EMSGSIZE          WSAEMSGSIZE
#define EHOSTUNREACH      WSAEHOSTUNREACH
#define ENETUNREACH       WSAENETRESET
#undef EPIPE
#undef EINVAL
#define EPIPE             WSAENOTCONN
#define EINVAL            WSAEINVAL
#define ECONNREFUSED      WSAECONNABORTED
#undef EINTR
#undef EMFILE
#define EINTR             WSAEINTR
#define EMFILE            WSAEMFILE
#define GETERROR     WSAGetLastError()
#define WIN32STARTUP \
    { \
      WSADATA wsaData; \
      int err = WSAStartup(0x202,&wsaData); \
      if (err) \
        fprintf(stderr,"Error(WSAStartup):%d\n",err); \
    }
#define WIN32CLEANUP WSACleanup();
#define close(X) closesocket(X)
#define index(s, c) strchr((s), (c))
#define bcopy(s, d, n)   memcpy((d), (s), (n))
#define bzero(s, n)      memset((s), 0, (n))
#define getdtablesize() FD_SETSIZE
#define RAND rand
#define SRAND srand
#if defined _MSC_VER
#define stat _stat
#define mkdir _mkdir
#define chdir _chdir
#define fstat _fstat
#define isatty _isatty
#define fileno _fileno
#define unlink _unlink
#define strcasecmp(s1, s2) _stricmp((s1), (s2))
#else
#define strcasecmp(s1, s2) stricmp((s1), (s2))
#endif
#define popen _popen
#define pclose _pclose
/* defined in os.c */
#ifndef __LCC__                 /* simply does not like our prototype ? */
void gettimeofday (struct timeval *tp, struct timezone *tzp);
#endif
extern char *crypt(char *pw, char *salt);
#define FGETS fgets_win
extern char *fgets_win (char *buf, int n, FILE * fp);

/*-----------------------------------------------------------------------*/
/* UNIX DEFINITION SECTION                                               */
/*-----------------------------------------------------------------------*/
#else /* Unix portability - some a consequence of above */

#include <sys/time.h>           /* Redhat BSD need this */
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <sys/param.h>
#include <sys/resource.h>
#include <sys/wait.h>
#ifndef __FreeBSD__
#include <crypt.h>
#endif
#include <dirent.h>
#define GETERROR  errno
#define INVALID_SOCKET -1       /* 0 on Windows */
#define SOCKET_ERROR -1
#define SOCKET int
#define WIN32STARTUP
#define WIN32CLEANUP
#define RAND random
#define SRAND srandom
#define FGETS fgets



#endif

/*-----------------------------------------------------------------------*/
/* COMMON DEFINITION SECTION                                             */
/*-----------------------------------------------------------------------*/
#if defined _POSIX_ARG_MAX
#define MAXCMDLEN _POSIX_ARG_MAX
#elif defined ARG_MAX
#define MAXCMDLEN ARG_MAX
#elif defined NCARGS
#define MAXCMDLEN  NCARGS
#else
#error Cannot determine maximum command argument size
#endif

#ifndef MAXPATHLEN
#ifdef MAXPATH
#define MAXPATHLEN MAXPATH
#else
#define MAXPATHLEN 260
#endif
#endif

#ifndef MAXHOSTNAMELEN
#define MAXHOSTNAMELEN MAXGETHOSTSTRUCT
#endif

#if !defined NOFILE
#if defined OPEN_MAX
#define NOFILE OPEN_MAX
#else
#error Cannot determine maximum open files
#endif
#endif

#endif /* OS_H */
