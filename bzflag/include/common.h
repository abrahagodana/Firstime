/* bzflag
 * Copyright (c) 1993 - 2005 Tim Riker
 *
 * This package is free software;  you can redistribute it and/or
 * modify it under the terms of the license found in the file
 * named COPYING that should have accompanied this file.
 *
 * THIS PACKAGE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */

/*
 * common definitions
 */

#ifndef BZF_COMMON_H
#define	BZF_COMMON_H

// this should always be the very FIRST header
#ifdef _DEVCPP //the Dev-C++ build is acting very stubborn; this is (hopefully) -temporary-
# include_next "config.h"
#else
# include "config.h"
#endif

#ifdef _WIN32
#include "win32.h"
#define _FD_SET(fd, set) FD_SET((unsigned int)fd, set)
#else
#define _FD_SET(fd, set) FD_SET(fd, set)
#endif

#include <stdio.h>
#include <stdlib.h> //needed for bzfrand
#include <math.h>

extern int debugLevel;
// Like verbose debug messages? level 0 for development only
#define DEBUG0 formatDebug
#define DEBUG1 if (debugLevel >= 1) formatDebug
#define DEBUG2 if (debugLevel >= 2) formatDebug
#define DEBUG3 if (debugLevel >= 3) formatDebug
#define DEBUG4 if (debugLevel >= 4) formatDebug

/* near zero by some epsilon convenience define since relying on
* the floating point unit for proper equivalence is not safe
*/
#define NEAR_ZERO(_value,_epsilon)  ( ((_value) > -_epsilon) && ((_value) < _epsilon) )

// seven places of precision is pretty safe, so something less precise
#if defined(FLT_EPSILON)
#  define ZERO_TOLERANCE FLT_EPSILON
#else
#  define ZERO_TOLERANCE 1.0e-06f
#endif

// Might we be BSDish? sys/param.h has BSD defined if so
#ifdef HAVE_SYS_PARAM_H
#  include <sys/param.h>
#endif

#ifdef HAVE__STRICMP
#  define strcasecmp _stricmp
#endif
#ifdef HAVE__STRNICMP
#  define strncasecmp _strnicmp
#endif
#if !defined(HAVE_VSNPRINTF)
#  ifdef HAVE__VSNPRINTF
#    define vsnprintf _vsnprintf
#  else
#    define vsnprintf(buf, size, fmt, list) vsprintf(buf, fmt, list)
#  endif
#endif

// some platforms don't have float versions of the math library
#ifndef HAVE_ASINF
#  define	asinf		(float)asin
#endif
#ifndef HAVE_ATAN2F
#  define	atan2f		(float)atan2
#endif
#ifndef HAVE_ATANF
#  define	atanf		(float)atan
#endif
#ifndef HAVE_COSF
#  define	cosf		(float)cos
#endif
#ifndef HAVE_EXPF
#  define	expf		(float)exp
#endif
#ifndef HAVE_FABSF
#  define	fabsf		(float)fabs
#endif
#ifndef HAVE_FLOORF
#  define	floorf		(float)floor
#endif
#ifndef HAVE_FMODF
#  define	fmodf		(float)fmod
#endif
#ifndef HAVE_HYPOTF
#  define	hypotf		(float)hypot
#endif
#ifndef HAVE_LOGF
#  define	logf		(float)log
#endif
#ifndef HAVE_POWF
#  define	powf		(float)pow
#endif
#ifndef HAVE_SINF
#  define	sinf		(float)sin
#endif
#ifndef HAVE_SQRTF
#  define	sqrtf		(float)sqrt
#endif
#ifndef HAVE_TANF
#  define	tanf		(float)tan
#endif

// random number stuff
#define bzfrand()	((double)rand() / ((double)RAND_MAX + 1.0))
#define bzfsrand(_s)	srand(_s)

#if !defined(_WIN32)

#ifndef __BEOS__
#  ifdef HAVE_VALUES_H
#    include <values.h>
#  endif
#else
#  include <limits.h>
/* BeOS: FIXME */
#  define MAXSHORT SHORT_MAX
#  define MAXINT INT_MAX
#  define MAXLONG LONG_MAX
#endif /* __BEOS__ */

#include <sys/types.h>

#ifdef HAVE_STDINT_H
#  include <stdint.h>
#endif

#if defined(__linux) || (defined(__sgi) && !defined(__INTTYPES_MAJOR))
typedef u_int16_t	uint16_t;
typedef u_int32_t	uint32_t;
#endif

#if defined(sun)
typedef signed short	int16_t;
typedef ushort_t	uint16_t;
typedef signed int	int32_t;
typedef uint_t		uint32_t;
#endif

#endif

typedef unsigned char	uint8_t;

#if defined( __BEOS__ )

// missing constants

#  ifndef MAXFLOAT
#    define	MAXFLOAT	3.402823466e+38f
#  endif

#  ifndef M_PI
#    define	M_PI		  3.14159265358979323846f
#  endif

#  ifndef M_SQRT1_2
#    define	M_SQRT1_2	0.70710678118654752440f
#  endif

// need some integer types
#  include <inttypes.h>

#  ifndef setenv
#    define setenv(a,b,c)
#  endif

#  ifndef putenv
#    define putenv(a)
#  endif
#endif /* defined( __BEOS__ ) */

#ifdef countof
#  undef countof
#endif
#define countof(__x)   (sizeof(__x) / sizeof(__x[0]))


#endif // BZF_COMMON_H


// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
