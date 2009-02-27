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

#ifndef _OSGMATHFIELDTRAITS_H_
#define _OSGMATHFIELDTRAITS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGFieldTraits.h"
#include "OSGDataType.h"

#include "OSGMatrix.h"
#include "OSGQuaternion.h"

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpBaseFieldTraits
    \ingroup GrpLibOSGBase 
 */

template <>
struct FieldTraits<Matrix> : public FieldTraitsTemplateBase<Matrix>
{
  private:

    static  DataType            _type;

  public:

    typedef FieldTraits<Matrix>  Self;

    enum             { Convertible = (Self::FromStringConvertible |
                                      Self::ToStreamConvertible   ) };

    static OSG_BASE_DLLMAPPING
                 DataType &getType      (void);

    static const Char8    *getSName     (void) { return "SFMatrix";       }
    static const Char8    *getMName     (void) { return "MFMatrix";       }

    static       Matrix    getDefault   (void) { return Matrix();         }


    static bool      getFromCString(      Matrix   &outVal,
                                    const Char8   *&inVal)
    {
        outVal.setValue(inVal, false);
        return true;
    }

    static void putToStream(const Matrix    &val,
                                  OutStream &outStr)
    {
        typedef TypeTraits<Matrix::ValueType> TypeTrait;

        TypeTrait::putToStream((val.getValues())[0], outStr);
        outStr << " ";
        TypeTrait::putToStream((val.getValues())[4], outStr);
        outStr << " ";
        TypeTrait::putToStream((val.getValues())[8], outStr);
        outStr << " ";
        TypeTrait::putToStream((val.getValues())[12], outStr);

        outStr << " ";
        TypeTrait::putToStream((val.getValues())[1], outStr);
        outStr << " ";
        TypeTrait::putToStream((val.getValues())[5], outStr);
        outStr << " ";
        TypeTrait::putToStream((val.getValues())[9], outStr);
        outStr << " ";
        TypeTrait::putToStream((val.getValues())[13], outStr);

        outStr << " ";
        TypeTrait::putToStream((val.getValues())[2], outStr);
        outStr << " ";
        TypeTrait::putToStream((val.getValues())[6], outStr);
        outStr << " ";
        TypeTrait::putToStream((val.getValues())[10], outStr);
        outStr << " ";
        TypeTrait::putToStream((val.getValues())[14], outStr);

        outStr << " ";
        TypeTrait::putToStream((val.getValues())[3], outStr);
        outStr << " ";
        TypeTrait::putToStream((val.getValues())[7], outStr);
        outStr << " ";
        TypeTrait::putToStream((val.getValues())[11], outStr);
        outStr << " ";
        TypeTrait::putToStream((val.getValues())[15], outStr);
    }

    static       UInt32    getBinSize (const Matrix &)
    {
        return sizeof(Real32) * 16;
    }

    static       UInt32    getBinSize (const Matrix  *,
                                             UInt32   uiNumObjects)
    {
        return sizeof(Real32) * 16 * uiNumObjects;
    }

    static void   copyToBin  (      BinaryDataHandler &pMem, 
                              const Matrix            &oObject)
    {
        pMem.putValues(&oObject[0][0], 16);
    }


    static void   copyFromBin(      BinaryDataHandler &pMem, 
                                    Matrix            &oObject)
    {
        pMem.getValues(&oObject[0][0], 16);
    }

    static void copyToBin(      BinaryDataHandler &pMem,
                                const Matrix      *pObjectStore,
                                UInt32             uiNumObjects)
    {
        pMem.putValues(&pObjectStore[0][0][0], uiNumObjects * 16);
    }
    
    static void copyFromBin(    BinaryDataHandler &pMem,
                                Matrix           *pObjectStore,
                                UInt32             uiNumObjects)
    {
        pMem.getValues(&pObjectStore[0][0][0], uiNumObjects * 16);
    }

};


/*! \ingroup GrpBaseFieldTraits
    \ingroup GrpLibOSGBase 
 */

template <>
struct FieldTraits<Matrix4d> : public FieldTraitsTemplateBase<Matrix4d>
{
  private:

    static DataType _type;

  public:

    typedef FieldTraits<Matrix4d>  Self;

    enum             { Convertible = (Self::FromStringConvertible |
                                      Self::ToStreamConvertible   ) };

    static OSG_BASE_DLLMAPPING
                 DataType &getType       (void);

    static const Char8    *getSName      (void) { return "SFMatrix4d";       }
    static const Char8    *getMName      (void) { return "MFMatrix4d";       }

    static       Matrix4d  getDefault    (void) { return Matrix4d();         }

    static bool      getFromCString(      Matrix4d   &outVal,
                                    const Char8     *&inVal)
    {
        outVal.setValue(inVal, false);
        return true;
    }

    static void      putToStream  (const Matrix4d  &val,
                                         OutStream &outStr)
    {
        typedef TypeTraits<Matrix4d::ValueType> TypeTrait;

        TypeTrait::putToStream((val.getValues())[0], outStr);
        outStr << " ";
        TypeTrait::putToStream((val.getValues())[4], outStr);
        outStr << " ";
        TypeTrait::putToStream((val.getValues())[8], outStr);
        outStr << " ";
        TypeTrait::putToStream((val.getValues())[12], outStr);

        outStr << " ";
        TypeTrait::putToStream((val.getValues())[1], outStr);
        outStr << " ";
        TypeTrait::putToStream((val.getValues())[5], outStr);
        outStr << " ";
        TypeTrait::putToStream((val.getValues())[9], outStr);
        outStr << " ";
        TypeTrait::putToStream((val.getValues())[13], outStr);

        outStr << " ";
        TypeTrait::putToStream((val.getValues())[2], outStr);
        outStr << " ";
        TypeTrait::putToStream((val.getValues())[6], outStr);
        outStr << " ";
        TypeTrait::putToStream((val.getValues())[10], outStr);
        outStr << " ";
        TypeTrait::putToStream((val.getValues())[14], outStr);

        outStr << " ";
        TypeTrait::putToStream((val.getValues())[3], outStr);
        outStr << " ";
        TypeTrait::putToStream((val.getValues())[7], outStr);
        outStr << " ";
        TypeTrait::putToStream((val.getValues())[11], outStr);
        outStr << " ";
        TypeTrait::putToStream((val.getValues())[15], outStr);
    }

    static       UInt32    getBinSize (const Matrix4d &)
    {
        return sizeof(Real64) * 16;
    }

    static       UInt32    getBinSize (const Matrix4d  *,
                                             UInt32  uiNumObjects)
    {
        return sizeof(Real64) * 16 * uiNumObjects;
    }

    static void   copyToBin  (      BinaryDataHandler &pMem, 
                              const Matrix4d          &oObject)
    {
        pMem.putValues(&oObject[0][0], 16);
    }


    static void   copyFromBin(      BinaryDataHandler &pMem, 
                                    Matrix4d          &oObject)
    {
        pMem.getValues(&oObject[0][0], 16);
    }

    static void copyToBin(      BinaryDataHandler &pMem,
                          const Matrix4d          *pObjectStore,
                                UInt32             uiNumObjects)
    {
        pMem.putValues(&pObjectStore[0][0][0], uiNumObjects * 16);
    }
    
    static void copyFromBin(    BinaryDataHandler &pMem,
                                Matrix4d          *pObjectStore,
                                UInt32             uiNumObjects)
    {
        pMem.getValues(&pObjectStore[0][0][0], uiNumObjects * 16);
    }
};



/*! \ingroup GrpBaseFieldTraits
    \ingroup GrpLibOSGBase 
 */

template <>
struct FieldTraits<Matrix4fx> : public FieldTraitsTemplateBase<Matrix4fx>
{
  private:

    static  DataType               _type;

  public:

    typedef FieldTraits<Matrix4fx>  Self;

    enum             { Convertible = Self::NotConvertible           };

    static OSG_BASE_DLLMAPPING
                 DataType &getType      (void);

    static const Char8    *getSName     (void) { return "SFMatrix4fx";    }
    static const Char8    *getMName     (void) { return "MFMatrix4fx";    }

    static       Matrix4fx getDefault   (void) { return Matrix4fx();      }


    static bool      getFromString(      Matrix4fx &outVal,
                                   const Char8     *&inVal)
    {
        outVal.setValue(inVal, false);
        return true;
    }

    static       UInt32    getBinSize (const Matrix4fx &)
    {
        return sizeof(Fixed32) * 16;
    }

    static       UInt32    getBinSize (const Matrix4fx  *,
                                             UInt32      uiNumObjects)
    {
        return sizeof(Fixed32) * 16 * uiNumObjects;
    }

    static void   copyToBin  (      BinaryDataHandler &pMem, 
                              const Matrix4fx         &oObject)
    {
        pMem.putValues(&oObject[0][0], 16);
    }


    static void   copyFromBin(      BinaryDataHandler &pMem, 
                                    Matrix4fx         &oObject)
    {
        pMem.getValues(&oObject[0][0], 16);
    }

    static void copyToBin(      BinaryDataHandler &pMem,
                          const Matrix4fx         *pObjectStore,
                                UInt32             uiNumObjects)
    {
        pMem.putValues(&pObjectStore[0][0][0], uiNumObjects * 16);
    }
    
    static void copyFromBin(    BinaryDataHandler &pMem,
                                Matrix4fx         *pObjectStore,
                                UInt32             uiNumObjects)
    {
        pMem.getValues(&pObjectStore[0][0][0], uiNumObjects * 16);
    }

};


/*! \ingroup GrpBaseFieldTraits 
 */

template <>
struct FieldTraits<Quaternion> : public FieldTraitsVec4TemplateBase<Quaternion>
{
  private:

    static  DataType                _type;

  public:

    typedef FieldTraits<Quaternion>  Self;

    enum             { Convertible = (Self::FromStringConvertible |
                                      Self::ToStreamConvertible   ) };

    static OSG_BASE_DLLMAPPING
                 DataType   &getType      (void);

    static const Char8      *getSName     (void) { return "SFQuaternion"; }
    static const Char8      *getMName     (void) { return "MFQuaternion"; }

    static       Quaternion  getDefault   (void) { return Quaternion();   }

    static bool        getFromCString(      Quaternion  &outVal,
                                      const Char8      *&inVal)
    {
        // VRML requires axis and angle in radians
        outVal.setValueAsAxisRad(inVal);

        return true;
    }

};


/*! \ingroup GrpBaseFieldTraits
    \ingroup GrpLibOSGBase 
 */

template <>
struct FieldTraits<Quaternionfx> : 
    public FieldTraitsVec4TemplateBase<Quaternionfx>
{
  private:

    static  DataType                  _type;

  public:

    typedef FieldTraits<Quaternionfx>  Self;

    enum               { Convertible = Self::ToStreamConvertible    };

    static OSG_BASE_DLLMAPPING
                 DataType     &getType      (void);

    static const Char8        *getSName     (void) { return "SFQuaternionfx"; }
    static const Char8        *getMName     (void) { return "MFQuaternionfx"; }

    static       Quaternionfx  getDefault   (void) { return Quaternionfx();   }

};

OSG_END_NAMESPACE

#endif /* _OSGMATHFIELDTRAITS_H_ */
