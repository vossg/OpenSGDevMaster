/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2008 by the OpenSG Forum                          *
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

#ifndef _OSGSHADERATTRIBUTE_H_
#define _OSGSHADERATTRIBUTE_H_

#include "OSGSystemDef.h"
#include "OSGBaseTypes.h"
#include "OSGBaseFieldTraits.h"
#include "OSGSysFieldTraits.h"

#include <utility>

OSG_BEGIN_NAMESPACE

namespace ShaderConstants
{
    static const UInt16 Attribute0Index      = 0;
    static const UInt16 Attribute1Index      = 1;
    static const UInt16 Attribute2Index      = 2;
    static const UInt16 Attribute3Index      = 3;
    static const UInt16 Attribute4Index      = 4;
    static const UInt16 Attribute5Index      = 5;
    static const UInt16 Attribute6Index      = 6;
    static const UInt16 Attribute7Index      = 7;
    static const UInt16 Attribute8Index      = 8;
    static const UInt16 Attribute9Index      = 9;
    static const UInt16 Attribute10Index     = 10;
    static const UInt16 Attribute11Index     = 11;
    static const UInt16 Attribute12Index     = 12;
    static const UInt16 Attribute13Index     = 13;
    static const UInt16 Attribute14Index     = 14;
    static const UInt16 Attribute15Index     = 15;

    static const UInt16 PositionsIndex       = Attribute0Index;
    static const UInt16 NormalsIndex         = Attribute2Index;
    static const UInt16 ColorsIndex          = Attribute3Index;
    static const UInt16 SecondaryColorsIndex = Attribute4Index;
    static const UInt16 TexCoordsIndex       = Attribute8Index;
    static const UInt16 TexCoords1Index      = Attribute9Index;
    static const UInt16 TexCoords2Index      = Attribute10Index;
    static const UInt16 TexCoords3Index      = Attribute11Index;
    static const UInt16 TexCoords4Index      = Attribute12Index;
    static const UInt16 TexCoords5Index      = Attribute13Index;
    static const UInt16 TexCoords6Index      = Attribute14Index;
    static const UInt16 TexCoords7Index      = Attribute15Index;
}

/*! \brief Accessible via #ShaderAttrIndexMapper
    \ingroup GrpSystemShaderBase
    \ingroup GrpLibOSGSystem
    \nohierarchy
 */

class OSG_SYSTEM_DLLMAPPING ShaderAttrIndexMapperBase : 
    public StringValueMapper<UInt16>
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef StringValueMapper<UInt16> Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    ShaderAttrIndexMapperBase(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ShaderAttrIndexMapperBase(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    void initMaps(void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    template <class SingletonT>
    friend class SingletonHolder;
};


/*! \typedef OSG::SingletonHolder<ShaderAttrIndexMapperBase> ShaderAttrIndexMapper;
    \ingroup GrpSystemShaderBase
    \relatesalso OSG::ShaderAttrIndexMapperBase
 */

typedef SingletonHolder<ShaderAttrIndexMapperBase> ShaderAttrIndexMapper;


typedef std::pair<UInt16, std::string> ShaderAttribute;

/*! \ingroup GrpSystemShaderFieldTraits
    \ingroup GrpLibOSGSystem
 */
template <>
struct FieldTraits<ShaderAttribute> : 
    public FieldTraitsTemplateBase<ShaderAttribute>
{
  private:

    static  DataType                 _type;

  public:

    typedef FieldTraits<ShaderAttribute>  Self;

    enum             { Convertible = (Self::ToStreamConvertible  |
                                      Self::FromStringConvertible) };

    static OSG_SYSTEM_DLLMAPPING
                 DataType   &getType      (void);

    static const Char8      *getSName     (void) { return "SFShaderAttribute"; }

    static const Char8      *getMName     (void) { return "MFShaderAttribute"; }

    static       ShaderAttribute getDefault(void) 
    {
        return ShaderAttribute();   
    }

    static       void      putToStream   (const ShaderAttribute &val,
                                                OutStream       &outStr);
 
    static       bool      getFromCString(      ShaderAttribute  &outVal,
                                          const Char8           *&inVal);

    static       UInt32    getBinSize (const ShaderAttribute &oObject)
    {
        return (FieldTraits<UInt16     >::getBinSize(oObject.first ) + 
                FieldTraits<std::string>::getBinSize(oObject.second));
    }

    static       UInt32    getBinSize (const ShaderAttribute *pObjectStore,
                                             UInt32           uiNumObjects)
    {
        UInt32 size=0;

        for(UInt32 i = 0; i < uiNumObjects; ++i)
        {
            size += getBinSize(pObjectStore[i]);
        }

        return size;
    }


    static void copyToBin(      BinaryDataHandler &pMem, 
                          const ShaderAttribute   &oObject)
    {
    	FieldTraits<UInt16     >::copyToBin(pMem, oObject.first );
        FieldTraits<std::string>::copyToBin(pMem, oObject.second);
    }

    static void copyToBin(      BinaryDataHandler &pMem, 
                          const ShaderAttribute   *pObjectStore,
                                UInt32             uiNumObjects)
    {
        for(UInt32 i=0; i < uiNumObjects; ++i)
        {
            copyToBin(pMem, pObjectStore[i]);
        }
    }

    static void copyFromBin(BinaryDataHandler &pMem, 
                            ShaderAttribute   &oObject)
    {
    	FieldTraits<UInt16     >::copyFromBin(pMem, oObject.first );
        FieldTraits<std::string>::copyFromBin(pMem, oObject.second);
    }

    static void copyFromBin(BinaryDataHandler &pMem, 
                            ShaderAttribute   *pObjectStore,
                            UInt32             uiNumObjects)
    {
        for(UInt32 i = 0; i < uiNumObjects; ++i)
        {
            copyFromBin(pMem, pObjectStore[i]);
        }
    }
};

OSG_END_NAMESPACE

#endif
