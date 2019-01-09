/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2003 by the OpenSG Forum                   *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Library General Public License as published    *
 * by the Free Software Foundation, version 2.                               *
 *                                                                           *
 * This library is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Library General Public License for more details.                          *
 *                                                                           *
 * You should have received a copy of the GNU Library General Public         *
 * License along with this library; if not, write to the Free Software       *
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                 *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                Changes                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/

#ifndef _OSGCONFIG_H_
#define _OSGCONFIG_H_

#ifdef __sgi
#pragma once
#endif

#ifdef __hpux
#include <sys/types.h>
#endif

#if defined(__linux) || defined(WIN32) || defined(__APPLE__)
#include <cassert>
#endif

#ifdef __APPLE__
   #include "TargetConditionals.h"
#endif

/*-------------------------------------------------------------------------*/
/*                                Versioning                               */

/*! @name Version Defines
 */

/*!{*/

/*! The printable Version string. Includes the full version with specifiers,
    e.g. "1.3.0pre1"
 */

#define OSG_VERSION_STRING      "2.0.0-pre1"

/*! The numeric full version, with two digits per major/minor/release, e.g.
    010300
 */

#define OSG_VERSION             0x020000

/*! The numeric major version number, e.g. 1
 */

#define OSG_MAJOR_VERSION       2

/*! The numeric minor version number, e.g. 3
 */

#define OSG_MINOR_VERSION       0

/*! The numeric release version number, e.g. 0
 */

#define OSG_RELEASE_VERSION     0


/*!}*/

// Mac Hack

#ifdef __APPLE__
#define darwin
#endif

/*-------------------------------------------------------------------------*/
/*                              endian general                             */

#if defined(__sgi)
#include <standards.h>
#include <sys/endian.h>
// Some systems (notably VRJuggler) screw up the environment, so kludge it
#  ifndef BYTE_ORDER
#    define LITTLE_ENDIAN  _LITTLE_ENDIAN
#    define BIG_ENDIAN     _BIG_ENDIAN
#    define BYTE_ORDER     _BYTE_ORDER
#  endif
#elif defined(__hpux)
#include <arpa/nameser.h>
#include <pthread.h>
#elif defined(__sun)
#include <arpa/nameser_compat.h>
#elif defined(__APPLE__)
#include <machine/endian.h>
#elif defined(__linux)
#include <endian.h>
#ifndef __USE_BSD
# define LITTLE_ENDIAN  __LITTLE_ENDIAN
# define BIG_ENDIAN     __BIG_ENDIAN
# define PDP_ENDIAN     __PDP_ENDIAN
# define BYTE_ORDER     __BYTE_ORDER
#endif
#elif defined(WIN32) // HACK until I find a better solution
#define LITTLE_ENDIAN 1234
#define BIG_ENDIAN 4321
#define BYTE_ORDER LITTLE_ENDIAN
#elif defined(_WIN32_WCE) // HACK until I find a better solution
#define LITTLE_ENDIAN 1234
#define BIG_ENDIAN 4321
#define BYTE_ORDER LITTLE_ENDIAN
#else
#error Endian determination : could not guess your plattform
#endif


/*-------------------------------------------------------------------------*/
/*                              icc general                                */

#ifdef __ICL
#ifndef __INTEL_COMPILER
#define __INTEL_COMPILER __ICL
#endif
#endif

/*-------------------------------------------------------------------------*/
/*                              gcc general                                */

# ifdef __GNUC__


/*! \brief stream->rdbuf get the new buffer as a parameter
 *  \ingroup GrpBaseDefines
 */

# define OSG_STREAM_RDBUF_HAS_PARAM

/*! \brief stream->isopen is available
 *  \ingroup GrpBaseDefines
 */

# define OSG_STREAM_HAS_ISOPEN

/*! \brief vsnprintf is available
 *  \ingroup GrpBaseDefines
 */

# define OSG_HAS_VSNPRINTF

/*! \brief nilbuffer is defined in the stdlib
 *  \ingroup GrpBaseDefines
 */

# define OSG_HAS_NILBUF

/*! \brief LongLong constants have LL suffix
 *  \ingroup GrpBaseDefines
 */

# define OSG_LONGLONG_HAS_LL

# define OSG_HAS_POSIXMEMALIGN

# define OSG_COMPILER_PART_SPEZ

# define OSG_NEED_BOOL_MFIELD_SPEZ

# if __GNUC__ >= 3
#    define OSG_HASH_MAP_AS_EXT

     /*! \brief SGI's stl implementation is available
      *  \ingroup GrpBaseDefines
      */

#    define OSG_SGI_STL

#    define OSG_THROW_NOTHING() throw()

#    define OSG_STDEXCEPTION_NAMESPACE    std

#    if __GNUC__ >= 4 || __GNUC_MINOR__ >=1
#        define OSG_STDEXTENSION_NAMESPACE  __gnu_cxx
#        define OSG_HAS_SSTREAM
#    else
#        define OSG_STDEXTENSION_NAMESPACE  std
#    endif

#    define OSG_STL_HAS_HASH_MAP

# else
#     define OSG_HAS_INPUT_ITERATOR

#     define OSG_THROW_NOTHING() 
#     if __GNUC_MINOR__ <= 96
#         define OSG_GCC_NO_IOS_BASE
#     endif
# endif

# if __GNUC__ >= 8
#  define OSG_THROW(X) 
# else
#  define OSG_THROW(X) throw(X)
# endif
# else // __GNUC__
#  define OSG_THROW(X) throw(X)
# endif


/*-------------------------------------------------------------------------*/
/*                              sgi CC                                     */

# if defined(__sgi) && !defined(__GNUC__)

# if _COMPILER_VERSION < 730
# error compiler version < 730 not supported, please upgrade
# endif

/*! \brief stream->rdbuf get the new buffer as a parameter
 *  \ingroup GrpBaseDefines
 */

# define OSG_STREAM_RDBUF_HAS_PARAM

/*! \brief stream->isopen is available
 *  \ingroup GrpBaseDefines
 */

# define OSG_STREAM_HAS_ISOPEN

/*! \brief vsnprintf is available
 *  \ingroup GrpBaseDefines
 */

# define OSG_HAS_VSNPRINTF

/*! \brief nilbuffer is defined in the stdlib
 *  \ingroup GrpBaseDefines
 */

# define OSG_HAS_NILBUF

/*! \brief Use SGI internal types to define OpenSG base types
 *  \ingroup GrpBaseDefines
 */

# define OSG_SGI_TYPES

/*! \brief atan2f function available
 *  \ingroup GrpBaseDefines
 */

# define OSG_HAS_ATANF2

/*! \brief General float math
 *  \ingroup GrpBaseDefines
 */

# define OSG_HAS_FLOATMATH

/*! \brief SGI's stl implementation is available
 *  \ingroup GrpBaseDefines
 */

# define OSG_SGI_STL

# define OSG_STL_HAS_HASH_MAP

/*! \brief Use GLX 
 *  \ingroup GrpBaseDefines
 */

# define OSG_USE_GLX

/*! \brief LongLong constants have LL suffix
 *  \ingroup GrpBaseDefines
 */

# define OSG_LONGLONG_HAS_LL

# define OSG_COMPILER_PART_SPEZ

# define OSG_THROW_NOTHING() THROW_NOTHING()

# define OSG_SGI_CC

# define OSG_FOUND_OS 

# define OSG_STDEXCEPTION_NAMESPACE std

# endif // defined(__sgi) && !defined(__GNUC__)




/*-------------------------------------------------------------------------*/
/*                              Linux gcc                                  */

# if defined(__GNUC__) && defined(__linux)

/*! \brief streams in std namespace
 */

# define OSG_LINUX_TYPES

# define OSG_HAS_ATANF2

# define OSG_HAS_FLOATMATH

/*! \brief Use the math functions from the std:: namespace
 *  \ingroup GrpBaseDefines
    The std:: namespace has a set of overloaded functions for many
    math operations, up to and including long double versions.
 */

# define OSG_USE_STDMATH

# define OSG_USE_GLX

# define OSG_USE_PTHREADS

# define OSG_LINUX_GCC

# define OSG_FOUND_OS
 
# endif // defined(__GNUC__) && defined(__linux)

/*-------------------------------------------------------------------------*/
/*                              Linux gcc ia64                             */

# if defined(__GNUC__) && defined(__linux) && defined(__ia64)

# define SIZE_T_NEQ_UINT32
# define SIZE_T_64BIT

# endif // defined(__GNUC__) && defined(__linux) && defined(__ia64)

/*-------------------------------------------------------------------------*/
/*                              Linux icc                                  */

# if defined(__INTEL_COMPILER) && defined(__linux)

# ifndef __ICL
#    define __ICL __INTEL_COMPILER
# endif

# ifndef __INTEL_COMPILER_VERSION
#    define __INTEL_COMPILER_VERSION __INTEL_COMPILER
# endif

# define OSG_STREAM_RDBUF_HAS_PARAM

# define OSG_STREAM_HAS_IOPEN

# define OSG_HAS_NILBUF

# define OSG_LINUX_TYPES

# define OSG_HAS_ATANF2

# define OSG_HAS_FLOATMATH

# define OSG_USE_GLX

# define OSG_LONGLONG_HAS_LL

# define OSG_COMPILER_PART_SPEZ

# if __INTEL_COMPILER_VERSION >= 710
#     define OSG_THROW_NOTHING() throw()
# else
#     define OSG_THROW_NOTHING()
# endif

//# define OSG_NO_INT8_PNT

# define OSG_USE_PTHREADS

# define OSG_LINUX_ICC

# define OSG_FOUND_OS

// icc >=8.1 uses gnu headers anyway, use gnu defines set above
#if __INTEL_COMPILER_VERSION < 810 || ! defined(__GNUC__)
# define OSG_STDEXTENSION_NAMESPACE std
# define OSG_STDEXCEPTION_NAMESPACE std
#endif

# define OSG_STL_HAS_HASH_MAP

# define OSG_HAS_SSTREAM

# define OSG_TMPL_STATIC_MEMBER_NEEDS_HELPER_FCT

# if __INTEL_COMPILER_VERSION >= 800
# define OSG_USE_HASH_COMPARE
# endif

# endif // defined(__INTEL_COMPILER) && defined(__linux)

/*-------------------------------------------------------------------------*/
/*                              Linux icc ia64                             */

# if defined(__INTEL_COMPILER) && defined(__linux) && defined(__ia64)
 
# define OSG_NO_INT8_PNT

# endif // defined(__GNUC__) && defined(__linux) && defined(__ia64)

/*-------------------------------------------------------------------------*/
/*                              Windows icc                                */

# if defined(__INTEL_COMPILER) && !defined(__linux) && !defined(_WIN32_WCE)  && defined(_MSC_VER) && _MSC_VER < 1300

# ifndef __ICL
#    define __ICL __INTEL_COMPILER
# endif

// Use windows internal types to define OpenSG base types
# define OSG_WIN_TYPES

// Use windows threads
# define OSG_USE_WINTHREADS


// general float math
# define OSG_HAS_FLOATMATH

// Use WGL 
# define OSG_USE_WGL

# define OSG_STREAM_HAS_ISOPEN

// it's there, it's just called something else
# define OSG_HAS_VSNPRINTF
# define vsnprintf _vsnprintf

# define OSG_HAS_NILBUF
# define OSG_STREAM_RDBUF_HAS_PARAM

# define OSG_LONGLONG_HAS_LL

# define OSG_COMPILER_PART_SPEZ

# define OSG_THROW_NOTHING()

# define OSG_WIN32_ICL

# define OSG_FOUND_OS

# define OSG_TMPL_STATIC_MEMBER_NEEDS_FUNCTION_INSTANTIATION

//# define OSG_HAS_VSNPRINTF

# endif // defined(__INTEL_COMPILER) && !defined(__linux)


# if defined(__INTEL_COMPILER) && !defined(__linux) && defined(_WIN32_WCE)

# ifndef __ICL
#    define __ICL __INTEL_COMPILER
# endif

// Use windows internal types to define OpenSG base types
# define OSG_WIN_TYPES

// Use windows threads
# define OSG_USE_WINTHREADS


// general float math
# define OSG_HAS_FLOATMATH

// Use WGL 
# define OSG_USE_EGL

# define OSG_GLES 100

# define OSG_WINCE 5

# define OSG_EMBEDDED

# define OSG_GL_ES_VERSION 100
 
# define OSG_STREAM_HAS_ISOPEN

//# define OSG_HAS_VSNPRINTF

# define OSG_HAS_NILBUF
# define OSG_STREAM_RDBUF_HAS_PARAM

# define OSG_LONGLONG_HAS_LL

# define OSG_COMPILER_PART_SPEZ

# define OSG_THROW_NOTHING()

# define OSG_WIN32_ICL

# define OSG_FOUND_OS

# define OSG_TMPL_STATIC_MEMBER_NEEDS_FUNCTION_INSTANTIATION

//# define OSG_HAS_VSNPRINTF

# endif // defined(__INTEL_COMPILER) && !defined(__linux)

/*-------------------------------------------------------------------------*/
/*                              Windows vc ce                              */

# if defined(_MSC_VER) && !defined(__ICL) && defined(_WIN32_WCE)
# define OSG_WIN_TYPES
// Use windows threads
# define OSG_USE_WINTHREADS
// general float math
# define OSG_HAS_FLOATMATH

# define OSG_USE_STDMATH

# define OSG_STREAM_HAS_ISOPEN
//# define OSG_HAS_VSNPRINTF
# define OSG_HAS_NILBUF
# define OSG_STREAM_RDBUF_HAS_PARAM

//# define OSG_MICROSOFT_COMPILER_ALERT
//# define OSG_MICROSOFT_COMPILER_HACKS

// Use WGL 
# define OSG_USE_EGL

# define OSG_GLES

# define OSG_GL_ES_VERSION 100

# define OSG_WINCE 5

# define OSG_EMBEDDED

//# define OSG_HAS_TEMPLATE_RETURNVALUES

# define OSG_NEED_EXPLICIT_INST_FOR_STATIC

# define OSG_THROW_NOTHING()

# define OSG_WIN32_CL

# define OSG_FOUND_OS
 
# define OSG_TMPL_STATIC_MEMBER_NEEDS_CLASS_INSTANTIATION

# define OSG_STATIC_MEMEBER_NEEDS_COPY_ASIGN_INIT

# define OSG_MICROSOFT_DOTNET_COMPILER_HACKS

# if _MSC_VER >= 1300 && _MSC_VER < 1310
#    define OSG_WIN32_CL_NET70 1
# endif

# if _MSC_VER > 1300
//# define OSG_NEED_BOOL_MFIELD_SPEZ
# endif

// vc 8.0
# if _MSC_VER >= 1400
# define OSG_STDEXCEPTION_NAMESPACE std
# endif

# endif // defined(_MSC_VER) && !defined(__ICL)

/*-------------------------------------------------------------------------*/
/*                              Windows vc                                 */

# if defined(_MSC_VER) && _MSC_VER >= 1300 && !defined(_WIN32_WCE)
# define OSG_WIN_TYPES
// Use windows threads
# define OSG_USE_WINTHREADS
// general float math
# define OSG_HAS_FLOATMATH

# define OSG_USE_STDMATH

# define OSG_STREAM_HAS_ISOPEN

// it's there, it's just called something else
# define OSG_HAS_VSNPRINTF
// vc 9.0 finally supports vsnprintf!
# if _MSC_VER < 1500
# define vsnprintf _vsnprintf
# endif
# define OSG_HAS_NILBUF
# define OSG_STREAM_RDBUF_HAS_PARAM

//# define OSG_MICROSOFT_COMPILER_ALERT
//# define OSG_MICROSOFT_COMPILER_HACKS

// Use WGL 
# define OSG_USE_WGL

//# define OSG_HAS_TEMPLATE_RETURNVALUES

# define OSG_NEED_EXPLICIT_INST_FOR_STATIC

# define OSG_THROW_NOTHING()

# define OSG_WIN32_CL

# define OSG_FOUND_OS
 
# define OSG_TMPL_STATIC_MEMBER_NEEDS_CLASS_INSTANTIATION

# if _MSC_VER >= 1910
#  define OSG_STATIC_MEMEBER_NEEDS_COPY_ASIGN_INIT 1
#  define BOOST_CONFIG_SUPPRESS_OUTDATED_MESSAGE 1
# endif

# define OSG_MICROSOFT_DOTNET_COMPILER_HACKS

# if _MSC_VER >= 1300 && _MSC_VER < 1310
#    define OSG_WIN32_CL_NET70 1
# endif

# if _MSC_VER > 1300
# define OSG_NEED_BOOL_MFIELD_SPEZ
# endif

// vc 8.0
# if _MSC_VER >= 1400
# define OSG_STDEXCEPTION_NAMESPACE std
# endif

# endif // defined(_MSC_VER) && !defined(__ICL)

/*-------------------------------------------------------------------------*/
/*                              Mac OSX gcc                                */

# if defined(__APPLE__)

# define OSG_LINUX_TYPES
# define OSG_NO_CONCEPT_CHECKS 
# define SIZE_T_NEQ_UINT32

#if defined(__x86_64)
#define SIZE_T_64BIT
#endif


# include <AvailabilityMacros.h>
# if !defined(MAC_OS_X_VERSION_10_5) || (MAC_OS_X_VERSION_MAX_ALLOWED < MAC_OS_X_VERSION_10_5)
#  define OSG_GLENUM_NEQ_UINT32
# endif

# define OSG_USE_PTHREADS

# define OSG_DLSYM_NEEDS_UNDERSCORE

# define OSG_USE_STDMATH

# define OSG_FOUND_OS

#if TARGET_OS_IPHONE || TARGET_OS_IPHONE_SIMULATOR
# define OSG_APPLE_IOS 1
#endif

# endif // if defined(__APPLE__)


/*-------------------------------------------------------------------------*/
/*                               HP-UX aC++                                */

# if defined(__hpux) && !defined(__GNUC__)

/*! \brief stream->rdbuf get the new buffer as a parameter
 *  \ingroup GrpBaseDefines
 */

# define OSG_STREAM_RDBUF_HAS_PARAM

/*! \brief stream->isopen is available
 *  \ingroup GrpBaseDefines
 */

# define OSG_STREAM_HAS_ISOPEN

/*! \brief vsnprintf is available
 *  \ingroup GrpBaseDefines
 */

# define OSG_HAS_VSNPRINTF

/*! \brief nilbuffer is defined in the stdlib
 *  \ingroup GrpBaseDefines
 */

# define OSG_HAS_NILBUF

/*! \brief Use SGI internal types to define OpenSG base types
 *  \ingroup GrpBaseDefines
 */

# define OSG_HPUX_TYPES

/*! \brief atan2f function available
 *  \ingroup GrpBaseDefines
 */

# define OSG_HAS_ATANF2

/*! \brief General float math
 *  \ingroup GrpBaseDefines
 */

# define OSG_HAS_FLOATMATH

/*! \brief SGI's stl implementation is available
 *  \ingroup GrpBaseDefines
 */

//# define OSG_SGI_STL

/*! \brief Use GLX 
 *  \ingroup GrpBaseDefines
 */

# define OSG_USE_GLX

/*! \brief LongLong constants have LL suffix
 *  \ingroup GrpBaseDefines
 */

# define OSG_LONGLONG_HAS_LL

# define OSG_COMPILER_PART_SPEZ

# define OSG_THROW_NOTHING() __THROWSPEC_NULL

# define OSG_USE_PTHREADS

# define OSG_HPUX_ACC

# define OSG_FOUND_OS 

// # define OSG_NOGLUTSUBDIR

# define OSG_STDEXCEPTION_NAMESPACE std

# endif // defined(__hpux) && !defined(__GNUC__)


/*-------------------------------------------------------------------------*/
/*                               Sun CC                                    */

# if defined(__sun) && !defined(__GNUC__)

/*! \brief stream->rdbuf get the new buffer as a parameter
 *  \ingroup GrpBaseDefines
 */

# define OSG_STREAM_RDBUF_HAS_PARAM

/*! \brief stream->isopen is available
 *  \ingroup GrpBaseDefines
 */

# define OSG_STREAM_HAS_ISOPEN

/*! \brief vsnprintf is available
 *  \ingroup GrpBaseDefines
 */

# define OSG_HAS_VSNPRINTF

/*! \brief nilbuffer is defined in the stdlib
 *  \ingroup GrpBaseDefines
 */

# define OSG_HAS_NILBUF

/*! \brief Use SGI internal types to define OpenSG base types
 *  \ingroup GrpBaseDefines
 */

# define OSG_SUN_TYPES

/*! \brief atan2f function available
 *  \ingroup GrpBaseDefines
 */

//# define OSG_HAS_ATANF2

/*! \brief General float math
 *  \ingroup GrpBaseDefines
 */

//# define OSG_HAS_FLOATMATH

/*! \brief SGI's stl implementation is available
 *  \ingroup GrpBaseDefines
 */

# define OSG_SGI_STL

/*! \brief Use GLX 
 *  \ingroup GrpBaseDefines
 */

# define OSG_USE_GLX

/*! \brief LongLong constants have LL suffix
 *  \ingroup GrpBaseDefines
 */

# define OSG_LONGLONG_HAS_LL

# define OSG_COMPILER_PART_SPEZ

# define OSG_THROW_NOTHING() throw()

# define OSG_USE_PTHREADS

# define OSG_SUN_CC

# define OSG_FOUND_OS 

# define OSG_STDEXCEPTION_NAMESPACE std

# define OSG_NO_INT8_PNT

# endif // defined(__sun) && !defined(__GNUC__)


#ifndef OSG_FOUND_OS
# error Could not determine compiler / os combination
#endif


#include "OSGExportDefines.h"
#include "OSGConfigured.h"


/* Mixed bag defines... */

// STLPORT doesn't support all of std::math
#if defined(STLPORT) ||defined(OSG_WITH_STLPORT)
#undef OSG_USE_STDMATH
#endif

# define OSG_USING_STD_NAMESPACE namespace std {} using namespace std;
# define OSG_STD std

/*! @name Namespace Defines
 */

/*@{*/

/** \brief Begin the osg namespace
 *  \ingroup GrpBaseDefines
 */

#ifdef OSG_USE_OSG2_NAMESPACE
# define OSG_BEGIN_NAMESPACE namespace OSG2 {
#else
# define OSG_BEGIN_NAMESPACE namespace OSG {
#endif

/** \brief End the osg namespace
 *  \ingroup GrpBaseDefines
 */

# define OSG_END_NAMESPACE }

/** \brief Use the osg namespace throughout the following code.
 *  \ingroup GrpBaseDefines
 */

#ifdef OSG_USE_OSG2_NAMESPACE
# define OSG_USING_NAMESPACE namespace OSG2 {} using namespace OSG2;
#else
# define OSG_USING_NAMESPACE namespace OSG {} using namespace OSG;
#endif

/** \brief Import the osg namespace throughout the following code.
 *  \ingroup GrpBaseDefines
 */

#ifdef OSG_USE_OSG2_NAMESPACE
# define OSG_IMPORT_NAMESPACE using namespace OSG2
#else
# define OSG_IMPORT_NAMESPACE using namespace OSG
#endif

#ifdef OSG_USE_OSG2_NAMESPACE
# define OSG_NAMESPACE_PREFIX "OSG2"
#else
# define OSG_NAMESPACE_PREFIX "OSG"
#endif

/*@}*/

#ifdef OSG_USE_OSG2_NAMESPACE
# define OSG OSG2
#endif

#if defined(OSG_DLSYM_NEEDS_UNDERSCORE)
#define OSG_DLSYM_UNDERSCORE "_"
#else
#define OSG_DLSYM_UNDERSCORE
#endif

#ifdef OSG_WIN_TYPES
# ifndef OSG_NO_WINDOWD_H_INCLUDE
#  include <windows.h>
#  include <intrin.h>
# endif
#endif

#ifndef OSG_WIN_TYPES
#    define OSG_APIENTRY
#else
#    ifdef APIENTRY
#        define OSG_APIENTRY APIENTRY
#    elif defined(GLAPIENTRY)
#        define OSG_APIENTRY GLAPIENTRY
#    else
#        error "Neither APIENTRY nor GLAPIENTRY defined"
#    endif
#endif

#ifdef OSG_DEBUG
#define OSG_DEBUG_LOCK_STAT
#endif

#ifdef OSG_DEBUG_ARG
#define OSG_CHECK_ARG(ARG) ARG
#else
#define OSG_CHECK_ARG(ARG)
#endif

#ifdef OSG_DEBUG
#define OSG_DEBUG_CHECK_ARG(ARG) ARG
#else
#define OSG_DEBUG_CHECK_ARG(ARG)
#endif

#ifdef OSG_LONGLONG_HAS_LL
#define OSGLL(ARG) ARG##LL
#else
#define OSGLL(ARG) ARG
#endif

#ifdef OSG_1_COMPAT
#define osg OSG
#endif

#define OSG_ASSERT(expr) assert(expr)

//#define OSG_DBG_MEM
//#define OSG_DBG_LCK

// ToBeChecked Defaults

#if !defined(OSG_STDEXCEPTION_NAMESPACE)
#    define OSG_STDEXCEPTION_NAMESPACE
#endif

#ifndef OSG_STDEXTENSION_NAMESPACE
#    define OSG_STDEXTENSION_NAMESPACE  std
#endif

#ifndef DOXYGEN_SHOULD_SKIP_THIS
# if !defined(OSG_DOC_LEVEL)
#  define OSG_DOC_LEVEL 0
# endif
#endif

#define OSG_FLEX_USE_IOSTREAM_INPUT 1

#define OSG_ASPECT_REFCOUNT

//#define OSG_FCPTR_TYPED_STORE

#ifdef OSG_ELDK

# define OSG_EMBEDDED
# define OSG_INTERNAL_GL_ES
# define OSG_GLES 100
# define OSG_GL_ES_VERSION 100

#endif

#define OSG_THREAD_DEBUG_SETASPECTTO

// XXX: Todo: Add build support for this
#if defined(OSG_ICC_GNU_COMPAT)

# undef OSG_USE_HASH_COMPARE

# if __GNUC__ >= 3
#    define OSG_HASH_MAP_AS_EXT

     /*! \brief SGI's stl implementation is available
      *  \ingroup GrpBaseDefines
      */
#    ifdef OSG_STDEXTENSION_NAMESPACE
#        undef OSG_STDEXTENSION_NAMESPACE
#    endif

#    if __GNUC_MINOR__ >=1 || __GNUC__ >= 4
#        define OSG_STDEXTENSION_NAMESPACE  __gnu_cxx
#    else
#        define OSG_STDEXTENSION_NAMESPACE  std
#    endif
# endif
#endif

#if defined(__sgi) || defined(__linux) || defined(__APPLE__) || \
    defined(__sun) || defined(__hpux)

#if defined(__linux) || defined(__hpux) || defined(__APPLE__) || defined(__sun)
#    if defined(__GNUC__)
#        if __GNUC__ >= 3
#            define OSG_STL_DEFAULT_ALLOCATOR(TP) std::allocator<TP>
#        endif
#    elif defined (__ICL)
#        define OSG_STL_DEFAULT_ALLOCATOR(TP) std::allocator<TP>
#    elif defined (OSG_HPUX_ACC)
#        define OSG_STL_DEFAULT_ALLOCATOR(TP) std::allocator<TP>
#    elif defined(OSG_SUN_CC)
#        define OSG_STL_DEFAULT_ALLOCATOR(TP) std::allocator<TP>
#    else
#        define OSG_STL_DEFAULT_ALLOCATOR(TP) std::__STL_DEFAULT_ALLOCATOR(TP)
#    endif
#else
#    define OSG_STL_DEFAULT_ALLOCATOR(TP) std::__STL_DEFAULT_ALLOCATOR(TP)
#endif

#else
#define OSG_STL_DEFAULT_ALLOCATOR(TP) std::allocator< TP >
#endif

#if (defined(__linux) && defined(__i386__)) || defined(WIN32)
#define OSG_FAST_INT 1
#endif

#define OSG_DOUBLEMAGICROUNDEPS (.5-1.4e-11)
#define OSG_DOUBLEMAGIC         double(6755399441055744.0)

#if defined(WIN32)

//
// OSG_DISABLE_MICROSOFT_SECURE_CXXX
//          -D _CRT_SECURE_NO_DEPRECATE
//          -D _CRT_SECURE_NO_WARNINGS
//          -D _CRT_NONSTDC_NO_DEPRECATE
//          -D _SECURE_SCL = 0
//          -D _SCL_SECURE_NO_WARNINGS
//          -D _SCL_SECURE_NO_DEPRECATE
//
# if defined(OSG_DISABLE_MICROSOFT_SECURE_CXXX)
#  if !defined(_SECURE_SCL) || _SECURE_SCL != 0
#    error "mixed up compiler settings, OpenSG libs with OSG_DISABLE_MICROSOFT_SECURE_CXXX on, but _SECURE_SCL not set or not equal 0"
#  endif
# endif //OSG_DISABLE_MICROSOFT_SECURE_CXXX

//
// OSG_DISABLE_MS_ITERATOR_DEBUGGING
//          -D _HAS_ITERATOR_DEBUGGING = 0
//
# if defined(OSG_DISABLE_MS_ITERATOR_DEBUGGING)
#  if !defined(_HAS_ITERATOR_DEBUGGING) || _HAS_ITERATOR_DEBUGGING != 0
#   error "mixed up compiler settings, OpenSG libs with OSG_DISABLE_MS_ITERATOR_DEBUGGING on, but _HAS_ITERATOR_DEBUGGING not set or not equal 0"
#  endif
# endif // OSG_DISABLE_MS_ITERATOR_DEBUGGING

#endif // WIN32

#endif /* _OSGCONFIG_H_ */
