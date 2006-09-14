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

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGMathFieldTraits.h
    \ingroup GrpBaseField
    \ingroup GrpBaseFieldTraits
*/
#endif

/*! \ingroup GrpBaseFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<Matrix> : public FieldTraitsTemplateBase<Matrix>
{
  private:

    static  DataType            _type;

  public:

    typedef FieldTraits<Matrix>  Self;

    enum             { Convertible = Self::NotConvertible           };

    static OSG_BASE_DLLMAPPING
           DataType &getType      (void);

    static Char8    *getSName     (void) { return "SFMatrix";       }
    static Char8    *getMName     (void) { return "MFMatrix";       }

    static Matrix    getDefault   (void) { return Matrix();         }


    static bool      getFromString(      Matrix   &outVal,
                                   const Char8   *&inVal)
    {
        outVal.setValue(inVal, false);
        return true;
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

#ifdef FDFOO
struct MatrixFieldDesc : public FieldDescBase
{
    typedef Matrix ValueType;
};
#endif

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsTemplateBase<Matrix> */
/*! \hideinhierarchy                        */
#endif


/*! \ingroup GrpBaseFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

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

    static Char8    *getSName     (void) { return "SFMatrix4fx";    }
    static Char8    *getMName     (void) { return "MFMatrix4fx";    }

    static Matrix4fx getDefault   (void) { return Matrix4fx();      }


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

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsTemplateBase<Matrix4fx> */
/*! \hideinhierarchy                        */
#endif



/*! \ingroup GrpBaseFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<Quaternion> : public FieldTraitsVec4TemplateBase<Quaternion>
{
  private:

    static  DataType                _type;

  public:

    typedef FieldTraits<Quaternion>  Self;

    enum               { Convertible = Self::ToStreamConvertible    };

    static OSG_BASE_DLLMAPPING
           DataType   &getType      (void);

    static Char8      *getSName     (void) { return "SFQuaternion"; }
    static Char8      *getMName     (void) { return "MFQuaternion"; }

    static Quaternion  getDefault   (void) { return Quaternion();   }

};

#ifdef FDFOO
struct QuaternionFieldDesc : public FieldDescBase
{
    typedef Quaternion ValueType;
};
#endif

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsTemplateBase<Quaternion> */
/*! \hideinhierarchy                            */
#endif



/*! \ingroup GrpBaseFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

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

    static Char8        *getSName     (void) { return "SFQuaternionfx"; }
    static Char8        *getMName     (void) { return "MFQuaternionfx"; }

    static Quaternionfx  getDefault   (void) { return Quaternionfx();   }

};

#ifdef FDFOO
struct QuaternionFieldDesc : public FieldDescBase
{
    typedef Quaternion ValueType;
};
#endif

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsTemplateBase<Quaternionfx> */
/*! \hideinhierarchy                              */
#endif

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

OSG_END_NAMESPACE

#define OSGMATHFIELDTRAITS_HEADER_CVSID "@(#)$Id$"

#endif /* _OSGMATHFIELDTRAITS_H_ */
