/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2003 by the OpenSG Forum                          *
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

#ifndef _OSGSYSFIELDTRAITS_H_
#define _OSGSYSFIELDTRAITS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGFieldTraits.h"
#include "OSGDataType.h"

OSG_BEGIN_NAMESPACE


/*! \ingroup GrpBaseFieldTraits
    \ingroup GrpLibOSGBase 
 */

template <>
struct FieldTraits<bool, 2> : public FieldTraitsPODTemplateBase<bool, 2>
{
  private:

    static  DataType             _type;

  public:

    typedef FieldTraits<bool, 2>  Self;


    enum             { Convertible = (Self::ToStreamConvertible  |
                                      Self::FromStringConvertible)     };

    static OSG_BASE_DLLMAPPING
                 DataType &getType      (void);

    static const Char8    *getSName     (void) { return "SFBool";            }
    static const Char8    *getMName     (void) { return "MFBool";            }

    static       bool      getDefault   (void) { return false;               }


    static SizeT getBinSize (const bool &)
    {
        return sizeof(UInt8);
    }
 
    static void   copyToBin  (      BinaryDataHandler &pMem,
                              const bool              &oObject)
    {
        UInt8 value=oObject;
        pMem.putValue(value);
    }
 
    static void   copyFromBin(      BinaryDataHandler &pMem,
                                    bool              &oObject)
    {
        UInt8 value;
        pMem.getValue(value);
        oObject=(value != 0);
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


/*! \ingroup GrpBaseFieldTraits
    \ingroup GrpLibOSGBase 
 */

template <>
struct FieldTraits<Int8> : public FieldTraitsPODTemplateBase<Int8>
{
  private:

    static  DataType          _type;

  public:

    typedef FieldTraits<Int8>  Self;

    enum             { Convertible = (Self::ToStreamConvertible  |
                                      Self::FromStringConvertible)};

    static OSG_BASE_DLLMAPPING
                 DataType &getType      (void);

    static const Char8    *getSName     (void) { return "SFInt8";            }
    static const Char8    *getMName     (void) { return "MFInt8";            }

    static       Int8      getDefault   (void) { return 0;                   }
};


/*! \ingroup GrpBaseFieldTraits
    \ingroup GrpLibOSGBase 
 */

template <>
struct FieldTraits<UInt8> : public FieldTraitsPODTemplateBase<UInt8>
{
  private:

    static  DataType           _type;

  public:
    
    typedef FieldTraits<UInt8>  Self;

    enum             { Convertible = (Self::ToStreamConvertible  |
                                      Self::FromStringConvertible)     };

    static OSG_BASE_DLLMAPPING
                 DataType &getType      (void);

    static const Char8    *getSName     (void) { return "SFUInt8";           }
    static const Char8    *getMName     (void) { return "MFUInt8";           }

    static       UInt8     getDefault   (void) { return 0;                   }

};


/*! \ingroup GrpBaseFieldTraits
    \ingroup GrpLibOSGBase 
 */

template <>
struct FieldTraits<Int16> : public FieldTraitsPODTemplateBase<Int16>
{
  private:

    static  DataType           _type;

  public:

    typedef FieldTraits<Int16>  Self;

    enum             { Convertible = (Self::ToStreamConvertible  |
                                      Self::FromStringConvertible)     };

    static OSG_BASE_DLLMAPPING
                 DataType &getType      (void);

    static const Char8    *getSName     (void) { return "SFInt16";           }
    static const Char8    *getMName     (void) { return "MFInt16";           }

    static       Int16     getDefault   (void) { return 0;                   }

};


/*! \ingroup GrpBaseFieldTraits
    \ingroup GrpLibOSGBase 
 */

template <>
struct FieldTraits<UInt16> : public FieldTraitsPODTemplateBase<UInt16>
{
  private:

    static  DataType            _type;

  public:

    typedef FieldTraits<UInt16>  Self;

    enum             { Convertible = (Self::ToStreamConvertible  |
                                      Self::FromStringConvertible)     };

    static OSG_BASE_DLLMAPPING
                 DataType &getType      (void);

    static const Char8    *getSName     (void) { return "SFUInt16";          }
    static const Char8    *getMName     (void) { return "MFUInt16";          }

    static       UInt16    getDefault   (void) { return 0;                   }

};


/*! \ingroup GrpBaseFieldTraits
    \ingroup GrpLibOSGBase 
 */

template <>
struct FieldTraits<Int32> : public FieldTraitsPODTemplateBase<Int32>
{
  private:

    static  DataType           _type;

  public:

    typedef FieldTraits<Int32>  Self;

    enum             { Convertible = (Self::ToStreamConvertible  |
                                      Self::FromStringConvertible)     };

    static OSG_BASE_DLLMAPPING
                 DataType &getType      (void);

    static const Char8    *getSName     (void) { return "SFInt32";           }
    static const Char8    *getMName     (void) { return "MFInt32";           }

    static       Int32     getDefault   (void) { return 0;                   }

};


/*! \ingroup GrpBaseFieldTraits
    \ingroup GrpLibOSGBase 
 */

template <>
struct FieldTraits<UInt32> : public FieldTraitsPODTemplateBase<UInt32>
{
  private:

    static  DataType            _type;

  public:

    typedef FieldTraits<UInt32>  Self;

    enum             { Convertible = (Self::ToStreamConvertible  |
                                      Self::FromStringConvertible)     };

    static OSG_BASE_DLLMAPPING
                 DataType &getType      (void);

    static const Char8    *getSName     (void) { return "SFUInt32";          }
    static const Char8    *getMName     (void) { return "MFUInt32";          }

    static       UInt32    getDefault   (void) { return 0;                   }
};



/*! \ingroup GrpBaseFieldTraits
    \ingroup GrpLibOSGBase 
 */

template <>
struct FieldTraits<Int64> : public FieldTraitsPODTemplateBase<Int64>
{
  private:

    static  DataType           _type;

  public:

    typedef FieldTraits<Int64>  Self;

    enum             { Convertible = (Self::ToStreamConvertible  |
                                      Self::FromStringConvertible)     };

    static OSG_BASE_DLLMAPPING
                 DataType &getType      (void);

    static const Char8    *getSName     (void) { return "SFInt64";           }
    static const Char8    *getMName     (void) { return "MFInt64";           }

    static       Int64     getDefault   (void) { return 0;                   }
};


/*! \ingroup GrpBaseFieldTraits
    \ingroup GrpLibOSGBase 
 */

template <>
struct FieldTraits<UInt64> : public FieldTraitsPODTemplateBase<UInt64>
{
  private:

    static  DataType            _type;

  public:

    typedef FieldTraits<UInt64>  Self;

    enum             { Convertible = (Self::ToStreamConvertible |
                                      Self::FromStringConvertible)     };

    static OSG_BASE_DLLMAPPING
                 DataType &getType      (void);

    static const Char8    *getSName     (void) { return "SFUInt64";          }
    static const Char8    *getMName     (void) { return "MFUInt64";          }

    static       UInt64    getDefault   (void) { return 0;                   }
};


/*! \ingroup GrpBaseFieldTraits
    \ingroup GrpLibOSGBase 
 */

template <>
struct FieldTraits<Real16> : public FieldTraitsPODTemplateBase<Real16>
{
  private:

    static  DataType            _type;

  public:

    typedef FieldTraits<Real16>  Self;

    enum             { Convertible = (Self::ToStreamConvertible  |
                                      Self::FromStringConvertible)     };

    static OSG_BASE_DLLMAPPING
                 DataType &getType      (void);

    static const Char8    *getSName     (void) { return "SFReal16";          }
    static const Char8    *getMName     (void) { return "MFReal16";          }

    static       Real32    getDefault   (void) { return 0.f;                 }
};


/*! \ingroup GrpBaseFieldTraits
    \ingroup GrpLibOSGBase 
 */

template <>
struct FieldTraits<Real32> : public FieldTraitsPODTemplateBase<Real32>
{
  private:

    static  DataType            _type;

  public:

    typedef FieldTraits<Real32>  Self;

    enum             { Convertible = (Self::ToStreamConvertible  |
                                      Self::FromStringConvertible)     };

    static OSG_BASE_DLLMAPPING
                 DataType &getType      (void);

    static const Char8    *getSName     (void) { return "SFReal32";          }
    static const Char8    *getMName     (void) { return "MFReal32";          }

    static       Real32    getDefault   (void) { return 0.f;                 }
};


/*! \ingroup GrpBaseFieldTraits
    \ingroup GrpLibOSGBase 
 */

template <>
struct FieldTraits<Fixed32> : public FieldTraitsPODTemplateBase<Fixed32>
{
  private:

    static  DataType            _type;

  public:

    typedef FieldTraits<Fixed32>  Self;

    enum             { Convertible = (Self::ToStreamConvertible  |
                                      Self::FromStringConvertible)     };

    static OSG_BASE_DLLMAPPING
                 DataType &getType      (void);

    static const Char8    *getSName     (void) { return "SFFixed32";          }
    static const Char8    *getMName     (void) { return "MFFixed32";          }

    static       Fixed32    getDefault   (void) { return Fixed32(0.f);        }
};


/*! \ingroup GrpBaseFieldTraits
    \ingroup GrpLibOSGBase 
 */

template <>
struct FieldTraits<Real64> : public FieldTraitsPODTemplateBase<Real64>
{
  private:

    static  DataType            _type;
    
  public:

    typedef FieldTraits<Real64>  Self;

    enum             { Convertible = (Self::ToStreamConvertible  |
                                      Self::FromStringConvertible)     };

    static OSG_BASE_DLLMAPPING
                 DataType &getType      (void);

    static const Char8    *getSName     (void) { return "SFReal64";          }
    static const Char8    *getMName     (void) { return "MFReal64";          }

    static       Real64    getDefault   (void) { return 0.;                  }

};


/*! \ingroup GrpBaseFieldTraits
    \ingroup GrpLibOSGBase 
 */

template <>
struct FieldTraits<void *> : public FieldTraitsPODTemplateBase<void *>
{
  private:

    static  DataType            _type;
    
  public:

    typedef FieldTraits<void *>  Self;
    typedef void *               ArgumentType;
    typedef void *               FieldTypeT;

    enum             { Convertible = Self::NotConvertible              };

    static OSG_BASE_DLLMAPPING
                 DataType &getType      (void);

    static const Char8    *getSName     (void) { return "SFVoidP";           }
    static const Char8    *getMName     (void) { return "MFVoidP";           }

    static       void     *getDefault   (void) { return NULL;                }
    
    // Binary
    
    // TODO Is it correct to just ignore these for binary ??
    
    static SizeT getBinSize(void * const &)
    {
        return 0;
    }

    static SizeT getBinSize(void * const *,
                            SizeT         )
    {
        return 0;
    }

    static void copyToBin(BinaryDataHandler &,
                          void              * const & )
    {
    }

    static void copyToBin(BinaryDataHandler &,
                          void              * const *,
                          SizeT                      )
    {
    }

    static void copyFromBin(BinaryDataHandler &,
                            void              * const & )
    {
    }

    static void copyFromBin(BinaryDataHandler &,
                            void              * const *,
                            SizeT                      )
    {
    }
};

OSG_END_NAMESPACE

#endif /* _OSGSYSFIELDTRAITS_H_ */
