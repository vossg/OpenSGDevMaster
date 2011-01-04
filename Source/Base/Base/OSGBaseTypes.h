/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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

#ifndef _OSGBASETYPES_H_
#define _OSGBASETYPES_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGBaseDef.h"
#include "OSGReal16.h"

#include <vector>
#include <boost/mpl/if.hpp>

#if defined(OSG_SGI_TYPES) || defined (OSG_LINUX_TYPES) || \
    defined(OSG_SUNOS_TYPES)
#include <sys/types.h>
#endif

#include <cstdlib>

#include <utility>

#include <cfloat>
#include <string>
#include <cstdio>
#include <cmath>

#if defined(OSG_LINUX_TYPES)
#    include <inttypes.h>
#endif

OSG_BEGIN_NAMESPACE

#if defined(OSG_SGI_TYPES)

/*! \var typedef char TChar;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef char           TChar;

/*! \var typedef char Char8;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef char           Char8;

/*! \var typedef unsigned char UChar8;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef unsigned char UChar8;

/*! \var typedef signed signed char SChar8;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef signed char   SChar8;

/*! \var typedef int8_t Int8;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef int8_t    Int8;

/*! \var typedef uint8_t UInt8;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef uint8_t   UInt8;

/*! \var typedef int16_t Int16;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef int16_t   Int16;

/*! \var typedef uint16_t UInt16;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef uint16_t  UInt16;

/*! \var typedef int32_t Int32;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef int32_t   Int32;

/*! \var typedef uint32_t UInt32;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef uint32_t  UInt32;

/*! \var typedef int64_t Int64;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef int64_t   Int64;

/*! \var typedef uint64_t UInt64;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef uint64_t  UInt64;

/*! \var typedef float Real32;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef float     Real32;

/*! \var typedef double Real64;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef double    Real64;

/*! \var typedef long double Real128;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef long double Real128;

#elif defined(OSG_LINUX_TYPES)

/*! \var typedef char TChar;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef char           TChar;

/*! \var typedef char Char8;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef char           Char8;

/*! \var typedef unsigned char UChar8;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef unsigned char UChar8;

/*! \var typedef signed char SChar8;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef signed char   SChar8;

/*! \var typedef int8_t Int8;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef int8_t     Int8;

/*! \var typedef u_int8_t UInt8;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef uint8_t   UInt8;

/*! \var typedef int16_t Int16;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef int16_t    Int16;

/*! \var typedef u_int16_t UInt16;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef uint16_t  UInt16;

/*! \var typedef int32_t Int32;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef int32_t    Int32;

/*! \var typedef u_int32_t UInt32;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef uint32_t  UInt32;

/*! \var typedef int64_t Int64;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef int64_t    Int64;

/*! \var typedef u_int64_t UInt64;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef uint64_t  UInt64;

/*! \var typedef float Real32;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef float      Real32;

/*! \var typedef double Real64;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef double     Real64;

/*! \var typedef long double Real128;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef long double Real128;

#elif defined(OSG_HPUX_TYPES)

/*! \var typedef char TChar;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef char           TChar;

/*! \var typedef char Char8;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef char           Char8;

/*! \var typedef unsigned char UChar8;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef unsigned char UChar8;

/*! \var typedef signed char SChar8;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef signed char   SChar8;

/*! \var typedef int8_t Int8;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef int8_t     Int8;

/*! \var typedef u_int8_t UInt8;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef uint8_t   UInt8;

/*! \var typedef int16_t Int16;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef int16_t    Int16;

/*! \var typedef u_int16_t UInt16;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef uint16_t  UInt16;

/*! \var typedef int32_t Int32;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef int32_t    Int32;

/*! \var typedef u_int32_t UInt32;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef uint32_t  UInt32;

/*! \var typedef int64_t Int64;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef int64_t    Int64;

/*! \var typedef u_int64_t UInt64;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef uint64_t  UInt64;

/*! \var typedef float Real32;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef float      Real32;

/*! \var typedef double Real64;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef double     Real64;

/*! \var typedef long double Real128;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef long double Real128;

#elif defined(OSG_WIN_TYPES)


/*! \var typedef TCHAR TChar;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef TCHAR          TChar;

/*! \var typedef CHAR Char8;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef CHAR           Char8;

/*! \var typedef unsigned char UChar8;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef UCHAR         UChar8;

/*! \var typedef signed char SChar8;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef signed char   SChar8;

/*! \var typedef CHAR Int8;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef signed char   Int8;

/*! \var typedef UCHAR UInt8;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef UCHAR   UInt8;

/*! \var typedef SHORT Int16;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef SHORT   Int16;

/*! \var typedef USHORT UInt16;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef USHORT  UInt16;

/*! \var typedef INT32 Int32;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef INT32   Int32;

/*! \var typedef UINT32 UInt32;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef UINT32  UInt32;

/*! \var typedef INT64 Int64;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef INT64   Int64;

/*! \var typedef UINT64 UInt64;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef UINT64  UInt64;

/*! \var typedef DWORD DWord;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef DWORD   DWord;

/*! \var typedef HANDLE Handle;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef HANDLE  Handle;

/*! \var typedef float Real32;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef float     Real32;

/*! \var typedef double Real64;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef double    Real64;

/*! \var typedef long double Real128;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef long double Real128;

#elif defined(OSG_SUN_TYPES)

/*! \var typedef char TChar;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef char           TChar;

/*! \var typedef char Char8;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef char           Char8;

/*! \var typedef unsigned char UChar8;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef unsigned char UChar8;

/*! \var typedef signed char SChar8;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef signed char   SChar8;

/*! \var typedef int8_t Int8;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef int8_t     Int8;

/*! \var typedef uint8_t UInt8;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef uint8_t   UInt8;

/*! \var typedef int16_t Int16;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef int16_t    Int16;

/*! \var typedef uint16_t UInt16;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef uint16_t  UInt16;

/*! \var typedef int32_t Int32;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef int32_t    Int32;

/*! \var typedef uint32_t UInt32;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef uint32_t  UInt32;

/*! \var typedef long long Int64;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef long long    Int64;

/*! \var typedef unsigned long long UInt64;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef unsigned long long  UInt64;

/*! \var typedef float Real32;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef float      Real32;

/*! \var typedef double Real64;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef double     Real64;

/*! \var typedef long double Real128;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef long double Real128;

#else
#error "Could not define base types, check your system/compiler combination"
#endif

/*! \var UInt64 BitVector;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef UInt64 BitVector;

#ifndef OSG_WIN_TYPES

/*! \var UInt32 RefCountStore;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef Int32 RefCountStore;

#else

/*! \var long RefCountStore;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef long RefCountStore;

#endif

/*! \var size_t SizeT;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef size_t SizeT;

/*! \var UInt8 *MemoryHandle;
 *  Handle to raw memory
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef UInt8 *MemoryHandle;

/*! \var void *VoidP;
 *  Handle to raw memory
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef void *VoidP;

#if defined(OSG_EMBEDDED) && !defined(__linux)
typedef std::wstring   tstring;
#define OSGT(TEXT) L##TEXT
#else
typedef std::string    tstring;
#define OSGT(TEXT) TEXT
#endif


/*! \ingroup GrpBaseBaseConstants
 */

const Real32 Eps = 1E-6f;

/*! \ingroup GrpBaseBaseConstants
 */

const Real32 Pi  = 3.141592653589793f;

/*! \ingroup GrpBaseBaseConstants
 */

const Real32 TwoPi  = 2.f * Pi;

/*! \ingroup GrpBaseBaseConstants
 */

const Real64 PiHalf  = 1.570796326794896619231322;

/*! \ingroup GrpBaseBaseConstants
 */

const Real32 Sqrt2  = 1.41421356237309504f;

/*! \ingroup GrpBaseBaseConstants
 */

const Real32 Inf = 1E30f;

/*! \ingroup GrpBaseBaseConstants
 */

const Real32 NegInf = - 1E30f;

#ifdef WIN32

/*! \ingroup GrpBaseBaseConstants
 */

static const Char8 *PluginExt     = ".dll";

/*! \ingroup GrpBaseBaseConstants
 */

static const Char8 *PluginPattern = "*.dll";

/*! \ingroup GrpBaseBaseConstants
 */

static const Char8  DirSep    = '\\';

#ifndef PRIx64
#define PRIx64 "llx"
#endif

#elif defined(__APPLE__)

/*! \ingroup GrpBaseBaseConstants
 */

const Char8 PluginExt[]     = ".dylib";

/*! \ingroup GrpBaseBaseConstants
 */

const Char8 PluginPattern[] = "*.dylib";

/*! \ingroup GrpBaseBaseConstants
 */

const Char8  DirSep    = '/';

#else

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#if defined(__GNUC__)
#define OSG_UNUSED_ATTRIB __attribute__((__unused__))
#else
#define OSG_UNUSED_ATTRIB
#endif
#endif

/*! \ingroup GrpBaseBaseConstants
 */
static const Char8 *PluginExt OSG_UNUSED_ATTRIB = ".so";

/*! \ingroup GrpBaseBaseConstants
 */
static const Char8 *PluginPattern OSG_UNUSED_ATTRIB = "*.so";

/*! \ingroup GrpBaseBaseConstants
 */

static const Char8  DirSep OSG_UNUSED_ATTRIB = '/';

#undef OSG_UNUSED_ATTRIB
#endif

#ifndef DOXYGEN_SHOULD_SKIP_THIS

namespace PointerSize
{
    struct UnknowSize {};

    typedef boost::mpl::if_<boost::mpl::bool_<(sizeof(void *) == 4)>,
                            UInt32,
                            UnknowSize>::type UITmp1;

    typedef boost::mpl::if_<boost::mpl::bool_<(sizeof(void *) == 4)>,
                            Int32,
                            UnknowSize>::type ITmp1;

    typedef boost::mpl::if_<boost::mpl::bool_<(sizeof(void *) == 8)>,
                            UInt64,
                            UITmp1  >::type UIPtrSize;

    typedef boost::mpl::if_<boost::mpl::bool_<(sizeof(void *) == 8)>,
                            Int64,
                            ITmp1  >::type IPtrSize;
}

#endif

/*! \ingroup GrpBaseBaseBaseTypes
 */

typedef PointerSize::UIPtrSize UIntPointer;
typedef PointerSize::IPtrSize  IntPointer;

#ifndef PRISize
# ifdef WIN32
#  define PRISize "Id"
#  define PRIUSize "Iu"
# else
#  define PRISize "zd"
#  define PRIUSize "zu"
# endif
#endif

/*! MathTypeProperties
 *  \ingroup GrpBaseBaseConstants
 */

enum MathTypeProperties
{
    RealValue,
    IntValue,
    BoolValue
};

/*! \ingroup GrpBaseBaseBaseTypes
 */

typedef const BitVector ConstFieldMaskArg;

/*! FieldFlags
    \ingroup GrpBaseBaseBaseTypes
    \ingroup GrpBaseBase
    \ingroup GrpLibOSGBase
    \nohierarchy
 */

struct FieldFlags
{
    BitVector _bSyncFlags;
    BitVector _bThreadLocalFlags;
    BitVector _bClusterLocalFlags;
    BitVector _bNamespaceMask;

    FieldFlags(void);
    FieldFlags(const FieldFlags &source);
    ~FieldFlags(void);
};


/*! \ingroup GrpBaseBaseBaseTypes
 */

typedef std::vector<IntPointer> AspectOffsetStore;

#ifndef DOXYGEN_SHOULD_SKIP_THIS

namespace RenderPropBitVectorSize
{
    struct UnknowSize {};

    typedef boost::mpl::if_<boost::mpl::bool_< (RenderPropertyBits <= 64 &&
                                                RenderPropertyBits >  32   )>,
                            UInt64,
                            UnknowSize>::type Tmp1;

    typedef boost::mpl::if_<boost::mpl::bool_< (RenderPropertyBits <= 32) >,
                            UInt32,
                            Tmp1  >::type BitVectorSize;
}

#endif

/*! \ingroup GrpBaseBaseBaseTypes
 */

typedef RenderPropBitVectorSize::BitVectorSize RenderPropBitVector;

#include "OSGFixed.h"

OSG_END_NAMESPACE

#include "OSGBaseTypeTraits.h"
#include "OSGBaseTypes.inl"

#endif /* OSGBASETYPES_H */
