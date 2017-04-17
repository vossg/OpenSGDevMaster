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


#ifndef _OSGBASEFUNCTIONS_H_
#define _OSGBASEFUNCTIONS_H_
#ifdef __sgi
#pragma once
#endif

#include <cmath>
#include <cstring>

#ifndef WIN32
#include <strings.h>
#include <unistd.h>
#include <cerrno>
#include <iostream>
#include <ctime>
#endif

#ifdef __sun
#include <cstdlib>
#include <ieeefp.h>
#endif

#ifdef __sgi
#include <ieeefp.h>
#endif

#include "OSGConfig.h"
#include "OSGBaseDef.h"
#include "OSGBaseTypes.h"

#include <vector>
#include <string>
#include <iterator>
#include <algorithm>

#ifdef WIN32
#include <tchar.h>
#endif

#ifdef OSG_USE_STDMATH
#endif
#include <cmath>

#ifdef OSG_STL_HAS_HASH_MAP
#    ifdef OSG_USE_HASH_COMPARE
#        ifdef OSG_HASH_MAP_AS_EXT
#            include <ext/hash_map>
#        else
#            include <hash_map>
#        endif
#    endif
#endif

OSG_BEGIN_NAMESPACE

/*---------------------------------------------------------------------*/
/*                        Base Math Runtime Functions                  */

template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgSqrt(const FloatTypeT rValue);

#ifdef OSG_1_COMPAT
template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgsqrt(const FloatTypeT rValue);
#endif


template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgCos(const FloatTypeT rValue);

#ifdef OSG_1_COMPAT
template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgcos(const FloatTypeT rValue);
#endif


template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgSin(const FloatTypeT rValue);

#ifdef OSG_1_COMPAT
template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgsin(const FloatTypeT rValue);
#endif


template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgTan(const FloatTypeT rValue);

#ifdef OSG_1_COMPAT
template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgtan(const FloatTypeT rValue);
#endif


template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgACos(const FloatTypeT rValue);

#ifdef OSG_1_COMPAT
template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgacos(const FloatTypeT rValue);
#endif


template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgASin(const FloatTypeT rValue);

#ifdef OSG_1_COMPAT
template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgasin(const FloatTypeT rValue);
#endif


template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgATan(const FloatTypeT rValue);

#ifdef OSG_1_COMPAT
template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgatan(const FloatTypeT rValue);
#endif


template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgATan2(const FloatTypeT rValue1,
             const FloatTypeT rValue2);

#ifdef OSG_1_COMPAT
template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgatan2(const FloatTypeT rValue1,
             const FloatTypeT rValue2);
#endif


template <class FloatTypeT> inline
FloatTypeT osgAbs(const FloatTypeT rValue);

#ifdef OSG_1_COMPAT
template <class FloatTypeT> inline
FloatTypeT osgabs(const FloatTypeT rValue);
#endif

template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgPow(const FloatTypeT rValue,
           const FloatTypeT rExp);

#ifdef OSG_1_COMPAT
template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgpow(const FloatTypeT rValue,
           const FloatTypeT rExp);
#endif


template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgLog(const FloatTypeT rValue);

#ifdef OSG_1_COMPAT
template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osglog(const FloatTypeT rValue);
#endif


template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgExp(const FloatTypeT rValue);

#ifdef OSG_1_COMPAT
template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgexp(const FloatTypeT rValue);
#endif


template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgFloor(const FloatTypeT rValue);

#ifdef OSG_1_COMPAT
template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgfloor(const FloatTypeT rValue);
#endif


template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgCeil(const FloatTypeT rValue);

#ifdef OSG_1_COMPAT
template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgceil(const FloatTypeT rValue);
#endif

template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgMod(const FloatTypeT lValue, const FloatTypeT rValue);

template <class FloatTypeT> inline
OSG::UInt32 osgFinite(const FloatTypeT rValue);

#ifdef OSG_1_COMPAT
template <class FloatTypeT> inline
OSG::UInt32 osgfinite(const FloatTypeT rValue);
#endif

/*---------------------------------------------------------------------*/
/*                           Min / Max Functions                       */

template <class TypeT> inline
TypeT osgMin(const TypeT lValue, const TypeT rValue);


template <class TypeT> inline
TypeT osgMax(const TypeT lValue, const TypeT rValue);


template <class TypeT> inline
TypeT osgClamp(const TypeT minVal, const TypeT val, const TypeT maxVal);

/*---------------------------------------------------------------------*/
/*                           Equality Comparison                       */

template <class TypeT> inline
bool osgIsEqual(const TypeT lValue, const TypeT rValue, const TypeT tol);

/*---------------------------------------------------------------------*/
/*                               Swap Functions                        */

template <class TypeT> inline
void osgSwap(TypeT & lValue, TypeT & rValue);

/*---------------------------------------------------------------------*/
/*                               Sign Functions                        */

template <class TypeT> inline
Int8 osgSgn(TypeT val);

/*---------------------------------------------------------------------*/
/*                           Rad / Degree Functions                    */

template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgDegree2Rad(const FloatTypeT rValue);

#ifdef OSG_1_COMPAT
template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgdegree2rad(const FloatTypeT rValue);
#endif


template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgRad2Degree(const FloatTypeT rValue);

#ifdef OSG_1_COMPAT
template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgrad2degree(const FloatTypeT rValue);
#endif

#ifdef OSG_1_COMPAT
template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    deg2rad(const FloatTypeT rValue);
#endif

#ifdef OSG_1_COMPAT
template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    rad2deg(const FloatTypeT rValue);
#endif

/*---------------------------------------------------------------------*/
/*                             Power 2 Functions                       */

template <class TypeT> inline
bool osgIsPower2(TypeT rValue);

#ifdef OSG_1_COMPAT
template <class TypeT> inline
bool osgispower2(TypeT rValue);
#endif


template <class TypeT> inline
TypeT osgNextPower2(TypeT rValue);

#ifdef OSG_1_COMPAT
template <class TypeT> inline
TypeT osgnextpower2(TypeT rValue);
#endif

/*---------------------------------------------------------------------*/
/*                    Miscellaneous Functions                          */

inline 
int osgLog2Int(OSG::Real32 v);


inline 
OSG::Int32 osgRound2Int(OSG::Real64 val);

template<class VecPntT> inline
OSG::UInt32 getMaxIndexAbs3(const VecPntT &v);

#if !defined(__linux)
inline
OSG::Int32  putenv(OSG::Char8 *string);

inline
OSG::Char8 *getenv(const OSG::Char8 *string);
#endif

inline
void osgSleep(OSG::UInt32 millisecs);

#ifdef OSG_1_COMPAT
inline
void osgsleep(OSG::UInt32 millisecs);
#endif


inline
OSG::Real32 osgRand(void);

#ifdef OSG_1_COMPAT
inline
OSG::Real32 osgrand(void);
#endif

OSG_BASE_DLLMAPPING
void osgGetHostname(char *szBuffer, OSG::UInt32 uiSize);

#if defined(WIN32) && defined(_MSC_VER) 
#if _MSC_VER <= 1200  // VC6
inline
std::ostream &operator<<(std::ostream &os, OSG::UInt64 v);

inline
std::ostream &operator<<(std::ostream &os, OSG::Int64  v);
#endif
#endif 

OSG_BASE_DLLMAPPING
std::string getCallStack();


/*---------------------------------------------------------------------*/
/*               big/little endian conversion functions                */

inline
bool osgIsBigEndian(void);

template <class ValueTypeT> inline
ValueTypeT osgSwapBytes(ValueTypeT src);

inline
OSG::UInt32 osgSwapBytesFP(OSG::Real32 src);

inline
OSG::Real32 osgSwapBytesFP(OSG::UInt32 src);

inline
OSG::UInt64 osgSwapBytesFP(OSG::Real64 src);

inline
OSG::Real64 osgSwapBytesFP(OSG::UInt64 src);

template <OSG::UInt8 ElemSize> inline
void osgSwapMem(void *mem, OSG::SizeT count);

template <class TypeT> inline
TypeT       osgHostToNet  (const TypeT       src);

inline
OSG::UInt32 osgHostToNetFP(const OSG::Real32 src);

inline
OSG::UInt64 osgHostToNetFP(const OSG::Real64 src);

template <class TypeT> inline
TypeT       osgNetToHost  (const TypeT       src);

inline
OSG::Real32 osgNetToHostFP(const OSG::UInt32 src);

inline
OSG::Real64 osgNetToHostFP(const OSG::UInt64 src);

#ifdef OSG_1_COMPAT
// host to network
inline
OSG::UInt16 osghtons  (OSG::UInt16  src);

inline
OSG::UInt32 osghtonl  (OSG::UInt32  src);

inline
OSG::UInt64 osghtonll (OSG::UInt64  src);

inline
OSG::Real32 osghtonf  (OSG::Real32  src);

inline
OSG::Real64 osghtond  (OSG::Real64  src);

inline
OSG::Real128 osghtondd(OSG::Real128 src);

// network to host
inline
OSG::UInt16 osgntohs (OSG::UInt16  src);

inline
OSG::UInt32 osgntohl (OSG::UInt32  src);

inline
OSG::UInt64 osgntohll(OSG::UInt64  src);

inline
OSG::Real32 osgntohf (OSG::Real32  src);

inline
OSG::Real64 osgntohd (OSG::Real64  src);

inline
OSG::Real128 osgntohd(OSG::Real128 src);
#endif // OSG_1_COMPAT

/*---------------------------------------------------------------------*/
/*               allignment helper functions                           */

inline
std::size_t alignOffset(std::size_t base_alignment, std::size_t base_offset);

/*---------------------------------------------------------------------*/
/* BoostPath Utils, merged from OpenSGToolbox,  Author: David Kabala   */

#if BOOST_FILESYSTEM_VERSION == 3
#define OSGBP2STR(BOOST_PATH_OBJ) ((BOOST_PATH_OBJ).string())
#else
#define OSGBP2STR(BOOST_PATH_OBJ) (BOOST_PATH_OBJ)
#endif

OSG_BASE_DLLMAPPING 
BoostPath makeRelative(const BoostPath &oRoot,
                       const BoostPath &oToPath);

/*! Indirector
    \ingroup GrpBaseBase
    \ingroup GrpBaseBaseSTLHelpers
    \ingroup GrpLibOSGBase
    \nohierarchy

    Allows using an indirection field for STL algorithms, e.g. sort.
    
    The idea is to sort an index field instead of the actual data, as the data
    might be large or immovable.
    
    Example:<tt>
    
    std::vector<float> contv;
    std::vector<int>   indv;
    indirector<std::vector<float>, int>  ind(contv);
    
    std::sort(indv.begin(), indv.end(), ind);
    </tt>
 */

template <class ContentT, class IndexT>
class indirector
{
    public:
    
        indirector(ContentT cont);
        
        bool operator()(IndexT a, IndexT b);
       
    private:
    
        ContentT _cont;
};

/*---------------------------------------------------------------------*/
/*                PtrStripper Helper                                   */

/*! Ptr Stripper
    \ingroup GrpBaseBaseHelper
    \ingroup GrpLibOSGBase
    \nohierarchy
 */

template<class PtrT>
struct PtrStripper
{
    typedef typename PtrT::StoredObject Object;
    typedef PtrT                        Ptr;
};

/*! Ptr Stripper
    \ingroup GrpBaseBaseHelper
    \ingroup GrpLibOSGBase
    \nohierarchy
 */

template<class PtrT>
struct PtrStripper<PtrT *>
{
    typedef PtrT  Object;
    typedef PtrT *Ptr;
};

/*! Ptr Stripper
    \ingroup GrpBaseBaseHelper
    \ingroup GrpLibOSGBase
    \nohierarchy
 */

template<class PtrT>
struct PtrStripper<PtrT const *>
{
    typedef const PtrT  ConstObject;
    typedef       PtrT *Ptr;
};

/*! Ptr Stripper
    \ingroup GrpBaseBaseHelper
    \ingroup GrpLibOSGBase
    \nohierarchy
 */

template<class PtrT>
struct PtrStripper<PtrT * const>
{
    typedef PtrT         Object;
    typedef PtrT * const Ptr;
};

OSG_END_NAMESPACE

#include "OSGBaseFunctions.inl"

#endif /* OSGBASEFUNCTIONS_H */
