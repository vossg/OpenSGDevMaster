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

#ifndef _OSGSHADERPARAMETER_H_
#define _OSGSHADERPARAMETER_H_

#include "OSGSystemDef.h"
#include "OSGBaseTypes.h"
#include "OSGBaseFieldTraits.h"

#include <utility>

OSG_BEGIN_NAMESPACE

typedef std::pair<GLenum, UInt32> ShaderParameter;

/*! \ingroup GrpSystemShaderFieldTraits
    \ingroup GrpLibOSGSystem
 */
template <>
struct FieldTraits<ShaderParameter> : 
    public FieldTraitsTemplateBase<ShaderParameter>
{
  private:

    static  DataType                 _type;

  public:

    typedef FieldTraits<ShaderParameter>  Self;

    enum             { Convertible = (Self::ToStreamConvertible  |
                                      Self::FromStringConvertible) };

    static OSG_SYSTEM_DLLMAPPING
                 DataType   &getType      (void);

    static const Char8      *getSName     (void) { return "SFShaderParameter"; }

    static const Char8      *getMName     (void) { return "MFShaderParameter"; }

    static       ShaderParameter getDefault(void) 
    {
        return ShaderParameter();   
    }

   static void putToStream(const ShaderParameter &val,
                                 OutStream       &outStr)
    {
        const std::string &fVal = GLDefineMapper::the()->toString(val.first);

        outStr << "\"";
        outStr << fVal;
        outStr << " ";

        switch(val.first)
        {
            case GL_GEOMETRY_INPUT_TYPE_EXT:
            case GL_GEOMETRY_OUTPUT_TYPE_EXT:
            {
                const std::string &sVal = 
                    GLDefineMapper::the()->toString(val.second);

                outStr << sVal;
            }
            break;
                
            default:
            {
                outStr << std::setbase(16);
                outStr << "0x";
                outStr << val.second;
                outStr << std::setbase(10);
            }
        }

        outStr << "\"";
    }

    static bool      getFromCString(      ShaderParameter  &outVal,
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

        std::string parName;
        std::string parVal;

        if(szTok != NULL)
        {
            parName = szTok;
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
            parVal = szTok;
        }
        else
        {
            return false;
        }

        outVal.first  = GLDefineMapper::the()->fromString(parName.c_str());
        outVal.second = GLDefineMapper::the()->fromString(parVal .c_str());

        return true;
    }

    static       UInt32    getBinSize (const ShaderParameter &oObject)
    {
        return (FieldTraits<GLenum, 1>::getBinSize(oObject.first) + 
                sizeof(UInt32));
    }

    static       UInt32    getBinSize (const ShaderParameter *pObjectStore,
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
                          const ShaderParameter   &oObject)
    {
    	FieldTraits<GLenum, 1>::copyToBin(pMem, oObject.first);

    	pMem.putValue(oObject.second);
    }

    static void copyToBin(      BinaryDataHandler &pMem, 
                          const ShaderParameter   *pObjectStore,
                                UInt32             uiNumObjects)
    {
        for(UInt32 i=0; i < uiNumObjects; ++i)
        {
            copyToBin(pMem, pObjectStore[i]);
        }
    }

    static void copyFromBin(BinaryDataHandler &pMem, 
                            ShaderParameter   &oObject)
    {
    	FieldTraits<GLenum, 1>::copyFromBin(pMem, oObject.first);

        pMem.getValue(oObject.second);
    }

    static void copyFromBin(BinaryDataHandler &pMem, 
                            ShaderParameter   *pObjectStore,
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
