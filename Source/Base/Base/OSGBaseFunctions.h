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
UInt32 osgFinite(const FloatTypeT rValue);

#ifdef OSG_1_COMPAT
template <class FloatTypeT> inline
UInt32 osgfinite(const FloatTypeT rValue);
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
int osgLog2Int(Real32 v);


inline 
Int32 osgRound2Int(Real64 val);

template<class VecPntT> inline
UInt32 getMaxIndexAbs3(const VecPntT &v);

#ifndef OSG_EMBEDDED
inline
Int32  putenv(Char8 *string);
#else
inline
Char8 *getenv(const Char8 *string);
#endif

inline
void osgSleep(UInt32 millisecs);

#ifdef OSG_1_COMPAT
inline
void osgsleep(UInt32 millisecs);
#endif


inline
Real32 osgRand(void);

#ifdef OSG_1_COMPAT
inline
Real32 osgrand(void);
#endif

OSG_BASE_DLLMAPPING
void osgGetHostname(char *szBuffer, UInt32 uiSize);

#if defined(WIN32) && defined(_MSC_VER) 
#if _MSC_VER <= 1200  // VC6
inline
std::ostream &operator<<(std::ostream &os, UInt64 v);

inline
std::ostream &operator<<(std::ostream &os, Int64  v);
#endif
#endif 

OSG_BASE_DLLMAPPING
std::string getCallStack();


/*---------------------------------------------------------------------*/
/*               big/little endian conversion functions                */

inline
bool osgIsBigEndian(void);

template <class ValueTypeT>
inline ValueTypeT
osgSwapBytes(ValueTypeT src);

template <class TypeT>
inline TypeT
osgHostToBigEndian(TypeT src);

template <class TypeT>
inline TypeT
osgHostToLittleEndian(TypeT src);

template <class TypeT>
inline TypeT
osgBigEndianToHost(TypeT src);

template <class TypeT>
inline TypeT
osgLittleEndianToHost(TypeT src);

template <class TypeT>
inline TypeT
osgHostToNet(const TypeT src);

template <class TypeT>
inline TypeT
osgNetToHost(const TypeT src);

// host to network

inline
UInt16 osghtons  (UInt16  src);

inline
UInt32 osghtonl  (UInt32  src);

inline
UInt64 osghtonll (UInt64  src);

inline
Real32 osghtonf  (Real32  src);

inline
Real64 osghtond  (Real64  src);

inline
Real128 osghtondd(Real128 src);

// network to host

inline
UInt16 osgntohs (UInt16  src);

inline
UInt32 osgntohl (UInt32  src);

inline
UInt64 osgntohll(UInt64  src);

inline
Real32 osgntohf (Real32  src);

inline
Real64 osgntohd (Real64  src);

inline
Real128 osgntohd(Real128 src);

/*---------------------------------------------------------------------*/
/*                   Case String Runtime Functions                     */

inline
void  osgStringDup    (const TChar *szInput,       TChar *&szOutput            );

#ifdef OSG_1_COMPAT
inline
void  stringDup       (const TChar *szInput,       TChar *&szOutput            );
#endif


inline
void  osgStringCopy   (const Char8 *szInput,       Char8 *szOutput             );

#ifdef OSG_1_COMPAT
inline
void  stringcpy       (const Char8 *szInput,       Char8 *szOutput             );
#endif


inline
Int32 osgStringNCmp   (const Char8 *string1, const Char8 *string2, size_t count);

#ifdef OSG_1_COMPAT
inline
Int32 stringncmp      (const Char8 *string1, const Char8 *string2, size_t count);
#endif


inline
Int32 osgStringLen    (const Char8 *string1                                    );

#ifdef OSG_1_COMPAT
inline
Int32 stringlen       (const Char8 *string1                                    );
#endif


inline
Int32 osgStringCmp    (const Char8 *string1, const Char8 *string2              );

#ifdef OSG_1_COMPAT
inline
Int32 stringcmp       (const Char8 *string1, const Char8 *string2              );
#endif


inline
Int32 osgStringCaseCmp(const Char8 *string1, const Char8 *string2              );

#ifdef OSG_1_COMPAT
inline
Int32 stringcasecmp(const Char8 *string1, const Char8 *string2              );
#endif

/*! String less than compare functor used for a STL weak ordering
    \ingroup GrpBaseSTLHelpers
    \ingroup GrpBaseBaseStringFn
    \hideinhierarchy
 */

struct LTString
{
    bool operator()(const Char8 *s1, const Char8 *s2) const
    {
        return ::strcmp(s1, s2) < 0;
    }
};

/*! String equal compare functor
    \ingroup GrpBaseSTLHelpers
    \ingroup GrpBaseBaseStringFn
    \hideinhierarchy
 */

struct EQString
{
    bool operator()(const Char8 *s1, const Char8 *s2) const
    {
        return ::strcmp(s1, s2) == 0;
    }
};

#ifdef OSG_USE_HASH_COMPARE
struct HashCmpString : 
    public OSG_STDEXTENSION_NAMESPACE::hash_compare<const Char8 *, LTString>
{
    typedef       std::hash_compare<const Char8 *, LTString>   Inherited;
    typedef const Char8                                      *_Kty;

    HashCmpString(void) : Inherited() 
    {
    }

    size_t operator()(const _Kty& _Keyval) const
	{
        return OSG_STDEXTENSION_NAMESPACE::hash_value<const Char8 *>(_Keyval);
    }

    bool operator()(const _Kty& _Keyval1, const _Kty& _Keyval2) const
    {
        return Inherited::operator()(_Keyval1, _Keyval2);
    }
};
#endif

// String Tokenizer

struct OSG_BASE_DLLMAPPING string_token_iterator :
#if defined(OSG_HAS_INPUT_ITERATOR)
    public std::input_iterator<std::string, std::ptrdiff_t>
#else
    public std::iterator<std::input_iterator_tag, std::string>
#endif
{
  public:
    string_token_iterator();

    string_token_iterator(const std::string & str_,
                          const char        * separator_ = " ");

    string_token_iterator(const string_token_iterator & rhs);

    string_token_iterator & operator++();

    string_token_iterator operator++(int);

    std::string operator*() const;

    bool operator==(const string_token_iterator & rhs) const;

    bool operator!=(const string_token_iterator & rhs) const;

  private:

    void find_next(void);

    const char                   * _separator;
    const std::string            * _str;
          std::string::size_type   _start;
          std::string::size_type   _end;
};



/*! Indirector
    \ingroup GrpBaseSTLHelpers
    \ingroup GrpBaseBaseStringFn 
    
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


template<class PtrT>
struct PtrStripper
{
    typedef typename PtrT::StoredObject Object;
    typedef PtrT                        Ptr;
};

template<class PtrT>
struct PtrStripper<PtrT *>
{
    typedef PtrT  Object;
    typedef PtrT *Ptr;
};

template<class PtrT>
struct PtrStripper<PtrT const *>
{
    typedef const PtrT  ConstObject;
    typedef       PtrT *Ptr;
};

template<class PtrT>
struct PtrStripper<PtrT * const>
{
    typedef PtrT         Object;
    typedef PtrT * const Ptr;
};

OSG_END_NAMESPACE

#include "OSGBaseFunctions.inl"

#endif /* OSGBASEFUNCTIONS_H */
