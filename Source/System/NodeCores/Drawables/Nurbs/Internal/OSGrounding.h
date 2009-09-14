/* GTS - Library for the manipulation of triangulated surfaces
 * Copyright (C) 1999 Stéphane Popinet
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */
#ifdef __sgi
#pragma once
#endif

#include "OSGSystemDef.h"
#include "OSGConfig.h"

OSG_BEGIN_NAMESPACE

// This is only necessary for Intel CPUs, to make sure they
// don't use a higher precision internally

#if defined(WIN32) || defined(__linux)

#ifndef WIN32
#define OSG_HAVE_FPU_CONTROL_H  1
#endif /* WIN32 */

#ifdef OSG_HAVE_FPU_CONTROL_H
#  include <fpu_control.h>
#  ifdef _FPU_EXTENDED
static fpu_control_t fpu_round_double =
    (_FPU_DEFAULT & ~_FPU_EXTENDED) | _FPU_DOUBLE;
static fpu_control_t fpu_init;
#    define OSG_FPU_ROUND_DOUBLE  { _FPU_GETCW(fpu_init); \
                                    _FPU_SETCW(fpu_round_double); }
#    define OSG_FPU_RESTORE       {_FPU_SETCW(fpu_init);}
#  else /* not FPU_EXTENDED */
#    define OSG_FPU_ROUND_DOUBLE
#    define OSG_FPU_RESTORE
#  endif /* not FPU_EXTENDED */
#else /* not OSG_HAVE_FPU_CONTROL_H */
#  ifdef OSG_HAVE_FLOATINGPOINT_H
#    include <floatingpoint.h>
#    define OSG_FPU_ROUND_DOUBLE  (fpsetprec(FP_PD))
#    define OSG_FPU_RESTORE       (fpsetprec(FP_PE))
#  else /* not OSG_HAVE_FLOATINGPOINT_H */
#    if defined(WIN32) && !defined(_WIN64)
#      ifdef _MSC_VER
#        include <float.h>
static unsigned int fpu_init;
#        define OSG_FPU_ROUND_DOUBLE (fpu_init = _controlfp(0, 0), \
                                      _controlfp(_PC_53, _MCW_PC))
#        define OSG_FPU_RESTORE      (_controlfp(fpu_init, 0xfffff))
#      else /* not _MSC_VER */
#        error "You need the Microsoft C compiler for the Win32 version"
#      endif /*  not _MSC_VER */
#    elif defined(_WIN64)
#      pragma message("Windows x64 environment does not support rounding mode control")
#      define OSG_FPU_ROUND_DOUBLE
#      define OSG_FPU_RESTORE
#    else
#      error "Unknown CPU: assuming default double precision rounding"
#      define OSG_FPU_ROUND_DOUBLE
#      define OSG_FPU_RESTORE
#    endif
#  endif /* not OSG_HAVE_FLOATINGPOINT_H */
#endif /* not OSG_HAVE_FPU_CONTROL_H */

#else // Other systems: not needed, define empty

#define OSG_FPU_ROUND_DOUBLE
#define OSG_FPU_RESTORE

#endif

OSG_END_NAMESPACE
