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

#include "OSGShaderAttribute.h"
#include "OSGShaderAttributeFields.h"

#include "OSGMField.ins"

#include "OSGSingletonHolder.ins"

OSG_BEGIN_NAMESPACE

DataType FieldTraits<ShaderAttribute>::_type("ShaderAttribute", "BaseType");

OSG_FIELDTRAITS_GETTYPE (        ShaderAttribute)
OSG_FIELD_DLLEXPORT_DEF1(MField, ShaderAttribute)

OSG_SINGLETON_INST(ShaderAttrIndexMapperBase, addPostFactoryExitFunction)

template class SingletonHolder<ShaderAttrIndexMapperBase>;

ShaderAttrIndexMapperBase::ShaderAttrIndexMapperBase(void) :
    Inherited()
{
    initMaps();
}

ShaderAttrIndexMapperBase::~ShaderAttrIndexMapperBase(void)
{
}

void ShaderAttrIndexMapperBase::initMaps(void)
{
    this->addToValuePair("PositionsIndex", ShaderConstants::Attribute0Index);
    this->addToValuePair("NormalsIndex",   ShaderConstants::Attribute2Index);
    this->addToValuePair("ColorsIndex",    ShaderConstants::Attribute3Index);
    this->addToValuePair("SecondaryColorsIndex", 
                         ShaderConstants::Attribute4Index);

    this->addToValuePair("TexCoordsIndex",  ShaderConstants::Attribute8Index );
    this->addToValuePair("TexCoords0Index", ShaderConstants::Attribute8Index );
    this->addToValuePair("TexCoords1Index", ShaderConstants::Attribute9Index );
    this->addToValuePair("TexCoords2Index", ShaderConstants::Attribute10Index);
    this->addToValuePair("TexCoords3Index", ShaderConstants::Attribute11Index);
    this->addToValuePair("TexCoords4Index", ShaderConstants::Attribute12Index);
    this->addToValuePair("TexCoords5Index", ShaderConstants::Attribute13Index);
    this->addToValuePair("TexCoords6Index", ShaderConstants::Attribute14Index);
    this->addToValuePair("TexCoords7Index", ShaderConstants::Attribute15Index);

    this->addToValuePair  ("Attribute0Index",        
                           ShaderConstants::Attribute0Index);
    this->addFromValuePair(ShaderConstants::Attribute0Index, 
                           "Attribute0Index");

    this->addToValuePair  ("Attribute1Index",        
                           ShaderConstants::Attribute1Index);
    this->addFromValuePair(ShaderConstants::Attribute1Index, 
                           "Attribute1Index");

    this->addToValuePair  ("Attribute2Index",        
                           ShaderConstants::Attribute2Index);
    this->addFromValuePair(ShaderConstants::Attribute2Index, 
                           "Attribute2Index");

    this->addToValuePair  ("Attribute3Index",        
                           ShaderConstants::Attribute3Index);
    this->addFromValuePair(ShaderConstants::Attribute3Index, 
                           "Attribute3Index");

    this->addToValuePair  ("Attribute4Index",        
                           ShaderConstants::Attribute4Index);
    this->addFromValuePair(ShaderConstants::Attribute4Index, 
                           "Attribute4Index");

    this->addToValuePair  ("Attribute5Index",        
                           ShaderConstants::Attribute5Index);
    this->addFromValuePair(ShaderConstants::Attribute5Index, 
                           "Attribute5Index");

    this->addToValuePair  ("Attribute6Index",        
                           ShaderConstants::Attribute6Index);
    this->addFromValuePair(ShaderConstants::Attribute6Index, 
                           "Attribute6Index");

    this->addToValuePair  ("Attribute7Index",        
                           ShaderConstants::Attribute7Index);
    this->addFromValuePair(ShaderConstants::Attribute7Index, 
                           "Attribute7Index");

    this->addToValuePair  ("Attribute8Index",        
                           ShaderConstants::Attribute8Index);
    this->addFromValuePair(ShaderConstants::Attribute8Index, 
                           "Attribute8Index");

    this->addToValuePair  ("Attribute9Index",        
                           ShaderConstants::Attribute9Index);
    this->addFromValuePair(ShaderConstants::Attribute9Index, 
                           "Attribute9Index");

    this->addToValuePair  ("Attribute10Index",        
                           ShaderConstants::Attribute10Index);
    this->addFromValuePair(ShaderConstants::Attribute10Index, 
                           "Attribute10Index");

    this->addToValuePair  ("Attribute11Index",        
                           ShaderConstants::Attribute11Index);
    this->addFromValuePair(ShaderConstants::Attribute11Index, 
                           "Attribute11Index");

    this->addToValuePair  ("Attribute12Index",        
                           ShaderConstants::Attribute12Index);
    this->addFromValuePair(ShaderConstants::Attribute12Index, 
                           "Attribute12Index");

    this->addToValuePair  ("Attribute13Index",        
                           ShaderConstants::Attribute13Index);
    this->addFromValuePair(ShaderConstants::Attribute13Index, 
                           "Attribute13Index");

    this->addToValuePair  ("Attribute14Index",        
                           ShaderConstants::Attribute14Index);
    this->addFromValuePair(ShaderConstants::Attribute14Index, 
                           "Attribute14Index");

    this->addToValuePair  ("Attribute15Index",        
                           ShaderConstants::Attribute15Index);
    this->addFromValuePair(ShaderConstants::Attribute15Index, 
                           "Attribute15Index");
}

void FieldTraits<ShaderAttribute>::putToStream(const ShaderAttribute &val,
                                                     OutStream       &outStr)
{
    const std::string &fVal = ShaderAttrIndexMapper::the()->toString(val.first);

    outStr << "\"";
    outStr << fVal;
    outStr << " ";
    outStr << val.second;
    
    outStr << "\"";
}


bool FieldTraits<ShaderAttribute>::getFromCString(     
          ShaderAttribute  &outVal,
    const Char8           *&inVal)
{
    char *szSaveTok = NULL;
        
#ifndef WIN32
    char *szTok = strtok_r(const_cast<Char8 *>(inVal), 
                           " \t\n", 
                           &szSaveTok);
#else
    char *szTok = strtok_s(const_cast<Char8 *>(inVal), 
                           " \t\n", 
                           &szSaveTok);
#endif

    std::string attrName;
    std::string attrVal;

    if(szTok != NULL)
    {
        attrName = szTok;
    }
    else
    {
        return false;
    }

#ifndef WIN32
    szTok = strtok_r(NULL, " \t\n", &szSaveTok);
#else
    szTok = strtok_s(NULL, " \t\n", &szSaveTok);
#endif
    if(szTok != NULL)
    {
        attrVal = szTok;
    }
    else
    {
        return false;
    }

    outVal.first  = ShaderAttrIndexMapper::the()->fromString(attrName.c_str());
    outVal.second = attrVal;
    
    return true;
}

OSG_END_NAMESPACE
