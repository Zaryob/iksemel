/* iksemel (XML parser for Jabber)
** Copyright (C) 2000-2003 Gurer Ozen
** This code is free software; you can redistribute it and/or
** modify it under the terms of GNU Lesser General Public License.
*/

#ifndef __COMMON_H
#define __COMMON_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <sys/types.h>
#include <stdio.h>

#ifdef STDC_HEADERS
#include <stdlib.h>
#include <stdarg.h>
#endif

#ifdef HAVE_STRING_H
#include <string.h>
#elif HAVE_STRINGS_H
#include <strings.h>
#endif

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

#ifdef HAVE_ERRNO_H
#include <errno.h>
#endif
#ifndef errno
extern int errno;
#endif

/* Branch prediction hints for supported compilers */
#ifdef __GNUC__
#define IKS_LIKELY(x)   __builtin_expect (!!(x), 1)
#define IKS_UNLIKELY(x) __builtin_expect (!!(x), 0)
#else
#define IKS_LIKELY(x)   (x)
#define IKS_UNLIKELY(x) (x)
#endif

#include "finetune.h"

#endif // __COMMON_H
