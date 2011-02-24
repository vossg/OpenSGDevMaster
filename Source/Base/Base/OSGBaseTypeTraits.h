/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2000-2002,2002 by the OpenSG Forum                *
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

#ifndef _OSGBASETYPETRAITS_H_
#define _OSGBASETYPETRAITS_H_
#ifdef __sgi
#pragma once
#endif

#ifndef _OSGBASETYPES_H_
#error not for direct use, please include OSGBaseTypes.h instead
#endif

#include "OSGGL.h"

#include "OSGIOStream.h"

#include <limits>
#include <boost/lexical_cast.hpp>

// The undef's are needed otherwise the numeric_limits won't work (GV)

#if defined(max)
#undef max
#endif

#if defined(min)
#undef min
#endif

OSG_BEGIN_NAMESPACE

template <class LookupTypeT>
struct TypeTraits;

/*! \ingroup GrpBaseBaseBaseTypeTraits
    \ingroup GrpLibOSGBase
 */

struct TypeTraitsBase
{
#ifdef GV_CHECK_CHECK
    static const  bool               IsPOD    = true;
    static const  MathTypeProperties MathProp = BoolValue;

    static const  bool               BitsSet     = true ;
    static const  bool               BitsClear   = false;

    static        bool              getZeroElement(void)
    {
        return false;
    }

    static        bool              getOneElement (void)
    {
        return true;
    }

    static        bool              getMax        (void)
    {
        return true;
    }

    static        bool              getMin        (void)
    {
        return false;
    }
#endif
};

/*! \ingroup GrpBaseBaseBaseTypeTraits
    \ingroup GrpLibOSGBase
 */

template <class LookupTypeT>
struct TypeTraitsTemplateBase : public TypeTraitsBase
{
    static void putToStream(const LookupTypeT &val,
                                  OutStream   &str)
    {
        str << boost::lexical_cast<std::string>(val);
    }

#ifdef OSG_1_COMPAT
    static LookupTypeT getFromString(const Char8 *szString)
    {
        typedef TypeTraits<LookupTypeT> SelfTraits;

        return SelfTraits::getFromCString(szString);
    }
#endif
};


/*! \ingroup GrpBaseBaseBaseTypeTraits
    \ingroup GrpLibOSGBase
 */

template <class LookupTypeT>
struct TypeTraits : public TypeTraitsTemplateBase<LookupTypeT>
{
    static const bool IsPOD = true;

#ifdef OSG_MICROSOFT_DOTNET_COMPILER_HACKS
    typedef LookupTypeT RealReturnType;
#endif
};

#if defined(__hpux)
template <class LookupTypeT> 
const bool TypeTraits<LookupTypeT>::IsPOD;
#endif


/*! \ingroup GrpBaseBaseBaseTypeTraits
    \ingroup GrpLibOSGBase
 */

template <>
struct TypeTraits<bool> : public TypeTraitsTemplateBase<bool>
{
    static const  bool               IsPOD     = true;
    static const  MathTypeProperties MathProp  = BoolValue;

    static const  bool               BitsSet   = true ;
    static const  bool               BitsClear = false;


    static        bool               getZeroElement(void)
    {
        return false;
    }

    static        bool               getOneElement (void)
    {
        return true;
    }

    static        bool               getMax        (void)
    {
        return true;
    }

    static        bool               getMin        (void)
    {
        return false;
    }

    static bool getFromCString(const Char8 * pData,
                                     Char8 *&pDataEnd)
    {
        if(pData == NULL)
            return false;

        if(pData[0] == 'T' || pData[0] == 't')
        {
            ++pDataEnd;

            if(pData[1] != 'R' && pData[1] != 'r')
            {
                return false;
            }

            ++pDataEnd;

            if(pData[2] != 'U' && pData[2] != 'u')
            {
                return false;
            }

            ++pDataEnd;

            if(pData[3] != 'E' && pData[3] != 'e')
            {
                return false;
            }

            ++pDataEnd;

            return true;
        }
        
        return false;
    }

    static bool getFromCString(const Char8 *pData)
    {
        Char8 *pDataEnd;

        return getFromCString(pData, pDataEnd);
    }

    static void putToString  (const bool        &val,
                                    std::string &out)
    {
        if(val == true)
        {
            out.append("TRUE");
        }
        else
        {
            out.append("FALSE");
        }
    }

    static void putToStream(const bool      &val,
                                  OutStream &str)
    {
        if(val == true)
        {
            str << "TRUE";
        }
        else
        {
            str << "FALSE";
        }
    }

};


/*! \ingroup GrpBaseBaseBaseTypeTraits
    \ingroup GrpLibOSGBase
 */

template <>
struct TypeTraits<UInt8> : public TypeTraitsTemplateBase<UInt8>
{
    typedef       Real32             RealReturnType;


    static const  bool               IsPOD     = true;
    static const  MathTypeProperties MathProp  = IntValue;

    static const  UInt8              BitsSet   = 0xFF;
    static const  UInt8              BitsClear = 0x00;


    static        UInt8              getDefaultEps(void)
    {
        return 0;
    }

    static        UInt8              getZeroElement(void)
    {
        return 0;
    }

    static        UInt8              getOneElement (void)
    {
        return 1;
    }

    static        UInt8              getMax        (void)
    {
        return std::numeric_limits<UInt8>::max();
    }

    static        UInt8              getMin        (void)
    {
        return std::numeric_limits<UInt8>::min();
    }


    static Real32      getFraction  (UInt8 val)
    {
        return (Real32(val) / Real32(getMax()));
    };

    static UInt8       getPortion   (Real32 val)
    {
#ifdef OSG_WIN32_ICL
#pragma warning (disable : 810)
#endif
        return UInt8((val * Real32(getMax())));
#ifdef OSG_WIN32_ICL
#pragma warning (default : 810)
#endif
    };


    static UInt8       getFromCString(const Char8 * pData,
                                            Char8 *&pDataEnd)
    {
        if(pData != NULL)
        {
            return UInt8(strtoul(pData, &pDataEnd, 0));
        }
        else
        {
            return getZeroElement();
        }
    }

    static UInt8       getFromCString(const Char8 *pData)
    {
        Char8 *pDataEnd;

        return getFromCString(pData, pDataEnd);
    }

    static void putToString  (const UInt8        val,
                                    std::string &out)
    {
        Char8 buffer[10];

        sprintf(buffer, "%u", val);

        out.append(buffer);
    }

    static void putToStream(const UInt8     &val,
                                  OutStream &str)
    {
        str << UInt32(val);
    }
};


/*! \ingroup GrpBaseBaseBaseTypeTraits
    \ingroup GrpLibOSGBase
 */

template <>
struct TypeTraits<Int8> : public TypeTraitsTemplateBase<Int8>
{
    typedef       Real32             RealReturnType;


    static const  bool               IsPOD       = true;
    static const  MathTypeProperties MathProp    = IntValue;

    static const  Int8               BitsSet     =  -1; //0xFF;
    static const  Int8               BitsClear   =  0x00;


    static        Int8               getDefaultEps(void)
    {
        return 0;
    }

    static        Int8               getZeroElement(void)
    {
        return 0;
    }

    static        Int8               getOneElement (void)
    {
        return 1;
    }

    static        Int8               getMin        (void)
    {
        return std::numeric_limits<Int8>::min();
    }

    static        Int8               getMax        (void)
    {
        return std::numeric_limits<Int8>::max();
    }


    static Real32      getFraction  (Int8   val)
    {
        return (Real32(val) / Real32(getMax()));
    };

    static Int8        getPortion   (Real32 val)
    {
        return Int8(val * Real32(getMax()));
    };


    static Int8        getFromCString(const Char8 * pData,
                                             Char8 *&pDataEnd)
    {
        if(pData != NULL)
        {
            return Int8(strtol(pData, &pDataEnd, 0));
        }
        else
        {
            return getZeroElement();
        }
    }

    static Int8        getFromCString(const Char8 *pData)
    {
        Char8 *pDataEnd;
        
        return getFromCString(pData, pDataEnd);
    }

    static void putToString  (const Int8         val,
                                    std::string &out)
    {
        Char8 buffer[10];

        sprintf(buffer, "%i", val);

        out.append(buffer);
    }

    static void putToStream(const Int8      &val,
                                  OutStream &str)
    {
        str << Int32(val);
    }
};


/*! \ingroup GrpBaseBaseBaseTypeTraits
    \ingroup GrpLibOSGBase
 */

template <>
struct TypeTraits<UInt16> : public TypeTraitsTemplateBase<UInt16>
{
    typedef       Real32             RealReturnType;


    static const  bool               IsPOD       = true;
    static const  MathTypeProperties MathProp    = IntValue;

    static const  UInt16             BitsSet     = 0xFFFF;
    static const  UInt16             BitsClear   = 0x0000;


    static        UInt16             getDefaultEps(void)
    {
        return 0;
    }

    static        UInt16             getZeroElement(void)
    {
        return 0;
    }

    static        UInt16             getOneElement (void)
    {
        return 1;
    }
    
    static        UInt16             getMax        (void)
    {
        return std::numeric_limits<UInt16>::max();
    }

    static        UInt16             getMin        (void)
    {
        return std::numeric_limits<UInt16>::min();
    }


    static Real32      getFraction  (UInt16 val)
    {
        return (Real32(val) / Real32(getMax()));
    };

    static UInt16      getPortion   (Real32 val)
    {
        return UInt16(val * Real32(getMax()));
    };


    static UInt16      getFromCString(const Char8 * pData,
                                            Char8 *&pDataEnd)
    {
        if(pData != NULL)
        {
            return UInt16(strtoul(pData, &pDataEnd, 0));
        }
        else
        {
            return getZeroElement();
        }
    }

    static UInt16      getFromCString(const Char8 *pData)
    {
        Char8 *pDataEnd;

        return getFromCString(pData, pDataEnd);
    }

    static void putToString  (const UInt16       val,
                                    std::string &out)
    {
        Char8 buffer[10];

//      Check WIN32 Version
#ifdef WIN32
        sprintf(buffer, "%u", UInt32(val));
#else
        sprintf(buffer, "%u", val);
#endif

        out.append(buffer);
    }
};


/*! \ingroup GrpBaseBaseBaseTypeTraits
    \ingroup GrpLibOSGBase
 */

template <>
struct TypeTraits<Int16> : public TypeTraitsTemplateBase<Int16>
{
    typedef       Real32             RealReturnType;


    static const  bool               IsPOD       = true;
    static const  MathTypeProperties MathProp    = IntValue;

    static const  Int16              BitsSet     =  -1; //0xFFFF;
    static const  Int16              BitsClear   =  0x0000;


    static        Int16              getDefaultEps(void)
    {
        return 0;
    }

    static        Int16              getZeroElement(void)
    {
        return 0;
    }

    static        Int16              getOneElement (void)
    {
        return 1;
    }

    static        Int16              getMax        (void)
    {
        return std::numeric_limits<Int16>::max();
    }

    static        Int16              getMin        (void)
    {
        return std::numeric_limits<Int16>::min();
    }


    static Real32      getFraction  (Int16  val)
    {
        return (Real32(val) / Real32(getMax()));
    };

    static Int16       getPortion   (Real32 val)
    {
        return Int16(val * Real32(getMax()));
    };


    static Int16       getFromCString(const Char8 * pData,
                                            Char8 *&pDataEnd)
    {
        if(pData != NULL)
        {
            return Int16(strtol(pData, &pDataEnd, 0));
        }
        else
        {
            return getZeroElement();
        }
    }

    static Int16       getFromCString(const Char8 *pData)
    {
        Char8 *pDataEnd;

        return getFromCString(pData, pDataEnd);
    }

    static void putToString  (const Int16        val,
                                    std::string &out)
    {
        Char8 buffer[10];

        sprintf(buffer, "%i", val);

        out.append(buffer);
    }
};


/*! \ingroup GrpBaseBaseBaseTypeTraits
    \ingroup GrpLibOSGBase
 */

template <>
struct TypeTraits<UInt32> : public TypeTraitsTemplateBase<UInt32>
{
    typedef       Real32                RealReturnType;


    static const  bool               IsPOD       = true;
    static const  MathTypeProperties MathProp    = IntValue;

    static const  UInt32             BitsSet     = 0xFFFFFFFF;
    static const  UInt32             BitsClear   = 0x00000000;


    static        UInt32             getDefaultEps(void)
    {
        return 0;
    }

    static        UInt32             getZeroElement(void)
    {
        return 0;
    }

    static        UInt32             getOneElement (void)
    {
        return 1;
    }

    static        UInt32             getMax        (void) 
    { 
        return std::numeric_limits<UInt32>::max();
    }

    static        UInt32             getMin        (void)
    {
        return std::numeric_limits<UInt32>::min();
    }


    static Real32      getFraction  (UInt32 val)
    {
        return (Real32(val) / Real32(getMax()));
    };

    static UInt32      getPortion   (Real32 val)
    {
        return UInt32(val * Real32(getMax()));
    };


    static UInt32      getFromCString(const Char8 * pData,
                                            Char8 *&pDataEnd)
    {
        if(pData != NULL)
        {
            return UInt32(strtoul(pData, &pDataEnd, 0));
        }
        else
        {
            return getZeroElement();
        }
    }


    static UInt32      getFromCString(const Char8 *pData)
    {
        Char8 *pDataEnd;

        return getFromCString(pData, pDataEnd);
    }


    static void putToString  (const UInt32       val,
                                    std::string &out)
    {
        Char8 buffer[15];

        sprintf(buffer, "%u", val);

        out.append(buffer);
    }
};


/*! \ingroup GrpBaseBaseBaseTypeTraits
    \ingroup GrpLibOSGBase
 */

template <>
struct TypeTraits<Int32> : public TypeTraitsTemplateBase<Int32>
{
    typedef       Real32             RealReturnType;


    static const  bool               IsPOD       = true;
    static const  MathTypeProperties MathProp    = IntValue;

    static const  Int32              BitsSet     =  0xFFFFFFFF;
    static const  Int32              BitsClear   =  0x00000000;

    static        Int32              getDefaultEps(void)
    {
        return 0;
    }

    static        Int32              getZeroElement(void)
    {
        return 0;
    }

    static        Int32              getOneElement (void)
    {
        return 1;
    }

    static        Int32              getMax        (void)
    {
        return std::numeric_limits<Int32>::max(); 
    }

    static        Int32              getMin        (void)
    {
        return std::numeric_limits<Int32>::min();
    }


    static Real32      getFraction  (Int32  val)
    {
        return (Real32(val) / Real32(getMax()));
    };

    static Int32       getPortion   (Real32 val)
    {
        return Int32(val * Real32(getMax()));
    };


    static Int32       getFromCString(const Char8 * pData,
                                            Char8 *&pDataEnd)
    {
        if(pData != NULL)
        {
            return Int32(strtol(pData, &pDataEnd, 0));
        }
        else
        {
            return getZeroElement();
        }
    }

    static Int32       getFromCString(const Char8 *pData)
    {
        Char8 *pDataEnd;

        return getFromCString(pData, pDataEnd);
    }

    static void putToString  (const Int32        val,
                                    std::string &out)
    {
        Char8 buffer[15];

        sprintf(buffer, "%i", val);

        out.append(buffer);
    }
};


/*! \ingroup GrpBaseBaseBaseTypeTraits
    \ingroup GrpLibOSGBase
 */

template <>
struct TypeTraits<UInt64> : public TypeTraitsTemplateBase<UInt64>
{
    typedef       Real32             RealReturnType;


    static const  bool               IsPOD       = true;
    static const  MathTypeProperties MathProp    = IntValue;

    static const  UInt64             BitsSet     = OSGLL(0xFFFFFFFFFFFFFFFF);
    static const  UInt64             BitsClear   = OSGLL(0x0000000000000000);

    static const  UInt64             Zero        = OSGLL(0x0000000000000000);
    static const  UInt64             One         = OSGLL(0x0000000000000001);


    static        UInt64             getDefaultEps(void)
    {
        return 0;
    }

    static        UInt64             getZeroElement(void)
    {
        return 0;
    }

    static        UInt64             getOneElement (void)
    {
        return 1;
    }


    static        UInt64             getMax        (void)         
    {
        return std::numeric_limits<UInt64>::max();
    }

    static        UInt64             getMin        (void)
    {
        return std::numeric_limits<UInt64>::min();
    }


    static Real32      getFraction  (UInt64 val)
    {
        return (Real32(val) / Real32(getMax()));
    };

    static UInt64      getPortion   (Real32 val)
    {
        return UInt64(val * Real32(getMax()));
    };


    static UInt64      getFromCString(const Char8 * pData,
                                            Char8 *&pDataEnd)
    {
        if(pData != NULL)
        {
#ifndef WIN32
            return UInt64(strtoull(pData, &pDataEnd, 0));
#else
            // FIXME
            return _atoi64(pData);
#endif
        }
        else
        {
            return getZeroElement();
        }
    }

    static UInt64      getFromCString(const Char8 *pData)
    {
        Char8 *pDataEnd;

        return getFromCString(pData, pDataEnd);
    }

    static void putToString  (const UInt64       val,
                                    std::string &out)
    {
        Char8 buffer[25];
#if defined(__x86_64__) && ! defined(__APPLE__)
        sprintf(buffer, "%lu", val);
#else
        sprintf(buffer, "%llu", val);
#endif
        out.append(buffer);
    }
};


/*! \ingroup GrpBaseBaseBaseTypeTraits
    \ingroup GrpLibOSGBase
 */

template <>
struct TypeTraits<Int64> : public TypeTraitsTemplateBase<Int64>
{
    typedef       Real32 RealReturnType;


    static const  bool               IsPOD       = true;
    static const  MathTypeProperties MathProp    = IntValue;

    static const  Int64              BitsSet     =  OSGLL(0xFFFFFFFFFFFFFFFF);
    static const  Int64              BitsClear   =  OSGLL(0x0000000000000000);


    static        Int64              getDefaultEps(void)
    {
        return 0;
    }

    static        Int64              getZeroElement(void)
    {
        return 0;
    }

    static        Int64              getOneElement (void)
    {
        return 1;
    }

    static        Int64              getMax        (void)
    {
        return std::numeric_limits<Int64>::max();
    }

    static        Int64              getMin        (void)
    {
        return std::numeric_limits<Int64>::min();
    }


    static Real32      getFraction  (Int64  val)
    {
        return (Real32(val) / Real32(getMax()));
    };

    static Int64       getPortion   (Real32 val)
    {
        return Int64(val * Real32(getMax()));
    };


    static Int64       getFromCString(const Char8 * pData,
                                            Char8 *&pDataEnd)
    {
        if(pData != NULL)
        {
#ifndef WIN32
            return  Int64(strtoll(pData, &pDataEnd, 0));
#else
            // FIXME
            return _atoi64(pData);
#endif
        }
        else
        {
            return getZeroElement();
        }
    }

    static Int64       getFromCString(const Char8 *pData)
    {
        Char8 *pDataEnd;

        return getFromCString(pData, pDataEnd);
    }

    static void putToString  (const Int64        val,
                                    std::string &out)
    {
        Char8 buffer[25];

#if defined(__x86_64__) && ! defined(__APPLE__)
        sprintf(buffer, "%li", val);
#else
        sprintf(buffer, "%lli", val);
#endif

        out.append(buffer);
    }
};

/*! \ingroup GrpBaseBaseBaseTypeTraits 
    \ingroup GrpLibOSGBase
*/

template <>
struct TypeTraits<Real16> : public TypeTraitsTemplateBase<Real16>
{
    typedef       Real16             RealReturnType;


    static const  bool               IsPOD       = true;
    static const  MathTypeProperties MathProp    = RealValue;

    static        Real16             getDefaultEps(void)
    {
        return Real16(1E-06f);
    }

    static        Real16             getZeroElement(void)
    {
        return Real16(0.f);
    }

    static        Real16             getOneElement (void)
    {
        return Real16(1.f);
    }

    static        Real16             getMax        (void)
    {
        return  REAL16_MAX;
    }

    static        Real16             getMin        (void)
    {
        return -REAL16_MAX;
    }


    static Real16 getFraction     (Real16 rVal) { return rVal; };
    static Real16 getPortion      (Real16 rVal) { return rVal; };


    static Real16 getFromCString   (const Char8 *szString,
                                          Char8 *&pDataEnd)
    {
        if(szString != NULL)
        {
#if defined(__sgi) || defined(WIN32) || defined(__sun)
            return Real16(Real32(atof  (szString)));
#else
            return Real16(Real32(strtof(szString, &pDataEnd)));
#endif
        }
        else
        {
            return getZeroElement();
        }
    }

    static Real16 getFromCString   (const Char8 *pData)
    {
        Char8 *pDataEnd;

        return getFromCString(pData, pDataEnd);
    }

    static void putToString(const Real16       val,
                                  std::string &out)
    {
        Char8 buffer[20];

        sprintf(buffer, "%e", Real32(val));

        out.append(buffer);
    }
};


/*! \ingroup GrpBaseBaseBaseTypeTraits 
    \ingroup GrpLibOSGBase
 */

template <>
struct TypeTraits<Real32> : public TypeTraitsTemplateBase<Real32>
{
    typedef       Real32             RealReturnType;


    static const  bool               IsPOD       = true;
    static const  MathTypeProperties MathProp    = RealValue;

    static        Real32             ZeroEps(void)
    {
        return 1E-30f;
    }

    static        Real32             getDefaultEps(void)
    {
        return 1E-06f;
    }

    static        Real32             getZeroElement(void)
    {
        return 0.f;
    }

    static        Real32             getOneElement (void)
    {
        return 1.f;
    }

    static        Real32             getMax        (void)
    {
        return  std::numeric_limits<float>::max();
    }

    static        Real32             getMin        (void)
    {
        return -std::numeric_limits<float>::max();
    }


    static Real32 getFraction     (Real32 rVal) { return rVal; };
    static Real32 getPortion      (Real32 rVal) { return rVal; };


    static Real32 getFromCString   (const Char8 * pData,
                                          Char8 *&pDataEnd)
    {
        if(pData != NULL)
        {
#if defined(__sgi) || defined(WIN32) || defined(__sun)
            // FIXME
            return Real32(atof  (pData));
#else
            return Real32(strtof(pData, &pDataEnd));
#endif
        }
        else
        {
            return getZeroElement();
        }
    }

    static Real32 getFromCString   (const Char8 *pData)
    {
        Char8 *pDataEnd;

        return getFromCString(pData, pDataEnd);
    }

    static void putToString(const Real32       val,
                                  std::string &out)
    {
        out.append(boost::lexical_cast<std::string>(val));
    }
};


/*! \ingroup GrpBaseBaseBaseTypeTraits 
    \ingroup GrpLibOSGBase
 */

template <>
struct TypeTraits<Fixed32> : public TypeTraitsTemplateBase<Fixed32>
{
    typedef       Fixed32             RealReturnType;


    static const  bool               IsPOD       = true;
    static const  MathTypeProperties MathProp    = RealValue;


    static        Fixed32            ZeroEps(void)
    {
        return Fixed32(0.00009f);
    }

    static        Fixed32            getDefaultEps (void)
    {
        return Fixed32(1E-06f);
    }

    static        Fixed32            getZeroElement(void)
    {
        return Fixed32(0.f);
    }

    static        Fixed32            getOneElement (void)
    {
        return Fixed32(1.f);
    }

    static        Fixed32            getMax        (void)
    {
        return Fixed32(REAL16_MAX);
    }

    static        Fixed32            getMin        (void)
    {
        return Fixed32(-REAL16_MAX);
    }

    static Fixed32 getFromCString   (const Char8 * pData,
                                           Char8 *&OSG_CHECK_ARG(pDataEnd))
    {
        // XXX TODO: implement

        if(pData != NULL)
        {
            return getZeroElement();
        }
        else
        {
            return getZeroElement();
        }
    }

    static Fixed32 getFromCString   (const Char8 *pData)
    {
        // XXX TODO: implement

        Char8 *pDataEnd;

        return getFromCString(pData, pDataEnd);
    }

    static void putToString(const Fixed32       OSG_CHECK_ARG(val),
                                  std::string & OSG_CHECK_ARG(out))
    {
        // XXX TODO: implement
    }
};


/*! \ingroup GrpBaseBaseBaseTypeTraits
    \ingroup GrpLibOSGBase
 */

template <>
struct TypeTraits<Real64> : public TypeTraitsTemplateBase<Real64>
{
    typedef       Real64             RealReturnType;


    static const  bool               IsPOD       = true;
    static const  MathTypeProperties MathProp    = RealValue;

    static        Real64             ZeroEps(void)
    {
        return 1E-30;
    }

    static        Real64             getDefaultEps (void)
    {
        return 1E-12;
    }

    static        Real64             getZeroElement(void)
    {
        return 0.0;
    }

    static        Real64             getOneElement (void)
    {
        return 1.0;
    }

    static        Real64             getMax        (void)
    {
        return  std::numeric_limits<double>::max();
    }

    static        Real64             getMin        (void)
    {
        return -std::numeric_limits<double>::max();
    }


    static Real64 getFraction     (Real64 rVal) { return rVal; };
    static Real64 getPortion      (Real64 rVal) { return rVal; };


    static Real64 getFromCString   (const Char8 * pData,
                                          Char8 *&pDataEnd)
    {
        if(pData != NULL)
        {
            return Real64(strtod(pData, &pDataEnd));
        }
        else
        {
            return getZeroElement();
        }
    }

    static Real64 getFromCString   (const Char8 *pData)
    {
        Char8 *pDataEnd;

        return getFromCString(pData, pDataEnd);
    }

    static void putToString(const Real64       val,
                                  std::string &out)
    {
        out.append(boost::lexical_cast<std::string>(val));
    }
};


/*! \ingroup GrpBaseBaseBaseTypeTraits
    \ingroup GrpLibOSGBase
 */

template <>
struct TypeTraits<Real128> : public TypeTraitsTemplateBase<Real128>
{
    typedef       Real128             RealReturnType;


    static const  bool               IsPOD       = true;
    static const  MathTypeProperties MathProp    = RealValue;

    static        Real64             getDefaultEps (void)
    {
        return 1E-24;
    }

    static        Real128             getZeroElement(void)
    {
        return 0.0;
    }

    static        Real128             getOneElement (void)
    {
        return 1.0;
    }

    static        Real128             getMax        (void)
    {
        return  std::numeric_limits<long double>::max();
    }

    static        Real128             getMin        (void)
    {
        return -std::numeric_limits<long double>::max();
    }


    static Real128 getFraction     (Real128 rVal) { return rVal; };
    static Real128 getPortion      (Real128 rVal) { return rVal; };


    static Real128 getFromCString   (const Char8 * pData,
                                           Char8 *&pDataEnd)
    {
        if(pData != NULL)
        {
#if defined(WIN32) || defined(__sun)
            return Real128(strtod (pData, &pDataEnd));
#else
            return Real128(strtold(pData, &pDataEnd));
#endif
        }
        else
        {
            return getZeroElement();
        }
    }

    static Real128 getFromCString   (const Char8 *pData)
    {
        Char8 *pDataEnd;

        return getFromCString(pData, pDataEnd);
    }

    static void putToString(const Real128      val,
                                  std::string &out)
    {
        out.append(boost::lexical_cast<std::string>(val));
    }
};


#ifdef SIZE_T_NEQ_UINT32

/*! \ingroup GrpBaseBaseBaseTypeTraits
    \ingroup GrpLibOSGBase
 */

#ifdef SIZE_T_64BIT
template <>
struct TypeTraits<size_t> : public TypeTraits<UInt64> {};
#else
template <>
struct TypeTraits<size_t> : public TypeTraits<UInt32> {};
#endif

#if 0
template <>
struct TypeTraits<size_t> : public TypeTraitsTemplateBase<size_t>
{
    typedef       Real32                RealReturnType;


    static const  bool               IsPOD       = true;
    static const  MathTypeProperties MathProp    = IntValue;

    static const  UInt32             BitsSet     = 0xFFFFFFFF;
    static const  UInt32             BitsClear   = 0x00000000;


    static        size_t             getZeroElement(void)
    {
        return 0;
    }

    static        size_t             getOneElement (void)
    {
        return 1;
    }

    static        size_t             getMax        (void) 
    { 
        return std::numeric_limits<size_t>::max();
    }

    static        size_t             getMin        (void)
    {
        return std::numeric_limits<size_t>::min();
    }


    static size_t      getFromCString(const Char8 * pData,
                                            Char8 *&pDataEnd)
    {
        if(pData != NULL)
        {
            return size_t(strtoul(pData, &pDataEnd, 0));
        }
        else
        {
            return getZeroElement();
        }
    }


    static size_t      getFromCString(const Char8 *pData)
    {
        Char8 *pDataEnd;

        return getFromCString(pData, pDataEnd);
    }


    static void putToString  (const size_t       val,
                                    std::string &out)
    {
        Char8 buffer[15];

        sprintf(buffer, "%u", val);

        out.append(buffer);
    }
};
#endif

#endif


#ifdef OSG_GLENUM_NEQ_UINT32

/*! \ingroup GrpBaseBaseBaseTypeTraits
    \ingroup GrpLibOSGBase
 */

template <>
struct TypeTraits<GLenum> : public TypeTraitsTemplateBase<GLenum>
{
    typedef       Real32                RealReturnType;


    static const  bool               IsPOD       = true;
    static const  MathTypeProperties MathProp    = IntValue;

    static const  UInt32             BitsSet     = 0xFFFFFFFF;
    static const  UInt32             BitsClear   = 0x00000000;


    static        GLenum             getZeroElement(void)
    {
        return 0;
    }

    static        GLenum             getOneElement (void)
    {
        return 1;
    }

    static        GLenum             getMax        (void) 
    { 
        return 0xFFFFFFFF;
    }

    static        GLenum             getMin        (void)
    {
        return 0x00000000;
    }


    static GLenum      getFromCString(const Char8 * pData,
                                            Char8 *&pDataEnd)
    {
        if(pData != NULL)
        {
            return GLenum(strtoul(pData, reinterpret_cast<char**>(pDataEnd), 0));
        }
        else
        {
            return getZeroElement();
        }
    }

    static GLenum      getFromCString(const Char8 *pData)
    {
        Char8 *pDataEnd;

        return getFromCString(pData, pDataEnd);
    }

    static void putToString  (const GLenum       val,
                                    std::string &out)
    {
        Char8 buffer[15];

        sprintf(buffer, "%lu", static_cast<unsigned long>(val));

        out.append(buffer);
    }
};

#endif

OSG_END_NAMESPACE

#ifndef OSG_DISABLE_DEPRECATED
#define TypeConstants TypeTraits
#define getAllSet()   BitsSet
#endif

#endif /* _OSGBASETYPETRAITS_H_ */
