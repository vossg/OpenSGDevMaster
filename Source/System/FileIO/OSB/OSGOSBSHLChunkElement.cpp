/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                   Copyright (C) 2013 by the OpenSG Forum                  *
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

#include "OSGOSBSHLChunkElement.h"

#include "OSGOSBRootElement.h"
#include "OSGOSBShaderParameterBoolElement.h"
#include "OSGOSBShaderParameterIntElement.h"
#include "OSGOSBShaderParameterMatrixElement.h"
#include "OSGOSBShaderParameterMIntElement.h"
#include "OSGOSBShaderParameterMRealElement.h"
#include "OSGOSBShaderParameterMVec2fElement.h"
#include "OSGOSBShaderParameterMVec3fElement.h"
#include "OSGOSBShaderParameterMVec4fElement.h"
#include "OSGOSBShaderParameterRealElement.h"
#include "OSGOSBShaderParameterVec2fElement.h"
#include "OSGOSBShaderParameterVec3fElement.h"
#include "OSGOSBShaderParameterVec4fElement.h"

#include "OSGSimpleSHLChunk.h"

OSG_BEGIN_NAMESPACE

/*-------------------------------------------------------------------------*/
/* OSBSHLChunkElement                                                      */
/*-------------------------------------------------------------------------*/

/*! Reads the SHLChunk from OpenSG 1.x and converts it to a SimpleSHLChunk.
 */

/*-------------------------------------------------------------------------*/
/* Static members                                                          */

OSBElementRegistrationHelper<OSBSHLChunkElement>
    OSBSHLChunkElement::_regHelper =
        OSBElementRegistrationHelper<OSBSHLChunkElement>("SHLChunk");

/*-------------------------------------------------------------------------*/
/* Constructor                                                             */

OSBSHLChunkElement::OSBSHLChunkElement(OSBRootElement *root)
    : Inherited(root, OSGOSBHeaderVersion200)
{
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

OSBSHLChunkElement::~OSBSHLChunkElement(void)
{
}

/*-------------------------------------------------------------------------*/
/* Reading                                                                 */

void
OSBSHLChunkElement::read(const std::string &typeName)
{
    OSG_OSB_LOG(("OSBSHLChunkElement::read: [%s]\n", typeName.c_str()));

    BinaryReadHandler *rh = editRoot()->getReadHandler();

    UInt8  ptrTypeId;
    UInt16 version;

    rh->getValue(ptrTypeId);
    rh->getValue(version  );

    OSG_OSB_LOG(("OSBSHLChunkElement::read: version: [%u]\n", version));

    // create replacement chunk
    _pSHLChunk = SimpleSHLChunk::create();
    setContainer(_pSHLChunk);

    std::string    fieldName;
    std::string    fieldTypeName;
    UInt32         fieldSize;
    PtrFieldListIt ptrFieldIt;

    MFGLenum       paramNames;
    MFUInt32       paramValues;

    while(readFieldHeader("", fieldName, fieldTypeName, fieldSize))
    {
        if(isSimpleSHLField(fieldName))
        {
            readFieldContent(fieldName, fieldTypeName, fieldSize, "", ptrFieldIt);
        }
        else if(fieldName == "parameters")
        {
            UInt32 ptrId;
            UInt32 numElements;

            rh->getValue(numElements);
            _paramIds.resize(numElements);

            for(UInt32 i = 0; i < numElements; ++i)
            {
                rh->getValue(ptrId);
                _paramIds[i] = ptrId;
            }
        }
        else if(fieldName == "programParameterNames")
        {
            paramNames.copyFromBin(*rh);
        }
        else if(fieldName == "programParameterValues")
        {
            paramValues.copyFromBin(*rh);
        }
        else
        {
            OSG_OSB_LOG(("Skipping [%d] bytes for field [%s]\n",
                         fieldSize, fieldName.c_str()));
            rh->skip(fieldSize);
        }
    }

    // handle paramNames, paramValues
    if(paramNames.empty() == false)
    {
        if(paramNames.size() != paramValues.size())
        {
            FWARNING(("OSBSHLChunkElement::read: Fields "
                      "'MFProgramParamterNamse' and 'MFProgramParameterValues' "
                      "have inconsistent sizes.\n"));
        }
        else
        {
            for(UInt32 i = 0; i < paramNames.size(); ++i)
            {
                _pSHLChunk->setProgramParameter(paramNames[i], paramValues[i]);
            }
        }
    }
}

void
OSBSHLChunkElement::postRead(void)
{
    OSG_OSB_LOG(("OSBSHLChunkElement::postRead:\n"));

    const OSBRootElement::IdElemMap& elemMap = getRoot()->getIdElemMap();

    for(UInt32 i = 0; i < _paramIds.size(); ++i)
    {
        OSBRootElement::IdElemMapConstIt elemIt = elemMap.find(_paramIds[i]);

        if(elemIt != elemMap.end())
        {
            handleParameterElem(elemIt->second);
        }
        else
        {
            FWARNING(("No entry in IdElemMap for id [%d]\n", _paramIds[i]));
        }
    }
}

/*-------------------------------------------------------------------------*/
/* Writing                                                                 */

void
OSBSHLChunkElement::preWrite(FieldContainer * const)
{
    // This can not be called, SHLChunk does not exist
    OSG_ASSERT(false);
}

void
OSBSHLChunkElement::write(void)
{
    // This can not be called, SHLChunk does not exist
    OSG_ASSERT(false);
}

bool
OSBSHLChunkElement::isSimpleSHLField(const std::string& fieldName) const
{
    return SimpleSHLChunk::getClassType().getFieldDesc(fieldName.c_str()) != NULL;
}

void
OSBSHLChunkElement::handleParameterElem(OSBElementBase* elem)
{
    OSBShaderParameterElement* shElem =
        dynamic_cast<OSBShaderParameterElement*>(elem);

    if(shElem != NULL)
    {
        OSBShaderParameterBoolElement* shElemBool  =
            dynamic_cast<OSBShaderParameterBoolElement*>(shElem);
        OSBShaderParameterIntElement* shElemInt   =
            dynamic_cast<OSBShaderParameterIntElement*>(shElem);
        OSBShaderParameterMatrixElement* shElemMatrix =
            dynamic_cast<OSBShaderParameterMatrixElement*>(shElem);
        OSBShaderParameterMIntElement* shElemMInt =
            dynamic_cast<OSBShaderParameterMIntElement*>(shElem);
        OSBShaderParameterMRealElement* shElemMReal =
            dynamic_cast<OSBShaderParameterMRealElement*>(shElem);
        OSBShaderParameterMVec2fElement* shElemMVec2f =
            dynamic_cast<OSBShaderParameterMVec2fElement*>(shElem);
        OSBShaderParameterMVec3fElement* shElemMVec3f =
            dynamic_cast<OSBShaderParameterMVec3fElement*>(shElem);
        OSBShaderParameterMVec4fElement* shElemMVec4f =
            dynamic_cast<OSBShaderParameterMVec4fElement*>(shElem);
        OSBShaderParameterRealElement* shElemReal =
            dynamic_cast<OSBShaderParameterRealElement*>(shElem);
        OSBShaderParameterVec2fElement* shElemVec2f =
            dynamic_cast<OSBShaderParameterVec2fElement*>(shElem);
        OSBShaderParameterVec3fElement* shElemVec3f =
            dynamic_cast<OSBShaderParameterVec3fElement*>(shElem);
        OSBShaderParameterVec4fElement* shElemVec4f =
            dynamic_cast<OSBShaderParameterVec4fElement*>(shElem);

        if(shElemBool != NULL)
        {
            _pSHLChunk->addUniformVariable<bool>(shElemBool->getName (),
                                                 shElemBool->getValue() );
        }
        else if(shElemInt != NULL)
        {
            _pSHLChunk->addUniformVariable<Int32>(shElemInt->getName (),
                                                  shElemInt->getValue() );
        }
        else if(shElemMatrix != NULL)
        {
            _pSHLChunk->addUniformVariable<Matrix>(shElemMatrix->getName (),
                                                   shElemMatrix->getValue() );
        }
        else if(shElemMInt != NULL)
        {
            _pSHLChunk->addUniformVariable<MFInt32>(shElemMInt->getName (),
                                                    shElemMInt->getValue() );
        }
        else if(shElemMReal != NULL)
        {
            _pSHLChunk->addUniformVariable<MFReal32>(shElemMReal->getName (),
                                                     shElemMReal->getValue() );
        }
        else if(shElemMVec2f != NULL)
        {
            _pSHLChunk->addUniformVariable<MFVec2f>(shElemMVec2f->getName (),
                                                    shElemMVec2f->getValue() );
        }
        else if(shElemMVec3f != NULL)
        {
            _pSHLChunk->addUniformVariable<MFVec3f>(shElemMVec3f->getName (),
                                                    shElemMVec3f->getValue() );
        }
        else if(shElemMVec4f != NULL)
        {
            _pSHLChunk->addUniformVariable<MFVec4f>(shElemMVec4f->getName (),
                                                    shElemMVec4f->getValue() );
        }
        else if(shElemReal != NULL)
        {
            _pSHLChunk->addUniformVariable<Real32>(shElemReal->getName (),
                                                   shElemReal->getValue() );
        }
        else if(shElemVec2f != NULL)
        {
            _pSHLChunk->addUniformVariable<Vec2f>(shElemVec2f->getName (),
                                                  shElemVec2f->getValue() );
        }
        else if(shElemVec3f != NULL)
        {
            _pSHLChunk->addUniformVariable<Vec3f>(shElemVec3f->getName (),
                                                  shElemVec3f->getValue() );
        }
        else if(shElemVec4f != NULL)
        {
            _pSHLChunk->addUniformVariable<Vec4f>(shElemVec4f->getName (),
                                                  shElemVec4f->getValue() );
        }
        else
        {
            FWARNING(("OSBSHLChunkElement::handleParameterElem: "
                      "Unknown parameter type for parameter named '%s'\n",
                      shElem->getName()));
        }
    }
}

OSG_END_NAMESPACE
