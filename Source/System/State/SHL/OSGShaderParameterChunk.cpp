/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <cstdlib>
#include <cstdio>

#include <OSGConfig.h>

#include "OSGShaderParameterChunk.h"

#include <OSGShaderParameterAccess.h>

#include <OSGShaderParameter.h>
#include <OSGShaderParameterBool.h>
#include <OSGShaderParameterInt.h>
#include <OSGShaderParameterReal.h>
#include <OSGShaderParameterVec2f.h>
#include <OSGShaderParameterVec3f.h>
#include <OSGShaderParameterVec4f.h>
#include <OSGShaderParameterMatrix.h>
#include <OSGShaderParameterPnt2f.h>
#include <OSGShaderParameterPnt3f.h>

#include <OSGShaderParameterMInt.h>
#include <OSGShaderParameterMReal.h>
#include <OSGShaderParameterMVec2f.h>
#include <OSGShaderParameterMVec3f.h>
#include <OSGShaderParameterMVec4f.h>
#include <OSGShaderParameterMMatrix.h>

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGShaderParameterChunkBase.cpp file.
// To modify it, please change the .fcd file (OSGShaderParameterChunk.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ShaderParameterChunk::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ShaderParameterChunk::ShaderParameterChunk(void) :
     Inherited         (     ),
    _parameter_access  (NULL ),
    _cleared_parameters(false)
{
}

ShaderParameterChunk::ShaderParameterChunk(
    const ShaderParameterChunk &source) :

     Inherited         (source                    ),
    _parameter_access  (source._parameter_access  ),
    _cleared_parameters(source._cleared_parameters)
{
}

ShaderParameterChunk::~ShaderParameterChunk(void)
{
}

void ShaderParameterChunk::onCreate(const ShaderParameterChunk *source)
{
    Inherited::onCreate(source);

    // ignore prototypes.

    if(GlobalSystemState == Startup)
        return;

    _parameter_access = new ShaderParameterAccess(*this);
}

void ShaderParameterChunk::onDestroy(UInt32 uiId)
{
    Inherited::onDestroy(uiId);

    delete _parameter_access;
}

/*----------------------------- class specific ----------------------------*/

void ShaderParameterChunk::changed(ConstFieldMaskArg whichField, 
                                   UInt32            origin,
                                   BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void ShaderParameterChunk::dump(      UInt32    , 
                                const BitVector ) const
{
    SLOG << "Dump ShaderParameterChunk NI" << std::endl;
}

/*---------------------------------- Access -------------------------------*/


/*------------------------------------ Set --------------------------------*/

bool ShaderParameterChunk::setUniformParameter(const Char8 *name, bool value)
{
    return _parameter_access->setSParameter<ShaderParameterBool>(name, value);
}

bool ShaderParameterChunk::setUniformParameter(const Char8 *name, Int32 value)
{
    return _parameter_access->setSParameter<ShaderParameterInt>(name, value);
}

bool ShaderParameterChunk::setUniformParameter(const Char8 *name, Real32 value)
{
    return _parameter_access->setSParameter<ShaderParameterReal>(name, value);
}

bool ShaderParameterChunk::setUniformParameter(const Char8 *name, 
                                               const Vec2f &value)
{
    return _parameter_access->setSParameter<ShaderParameterVec2f>(name, value);
}

bool ShaderParameterChunk::setUniformParameter(const Char8 *name, 
                                               const Vec3f &value)
{
    return _parameter_access->setSParameter<ShaderParameterVec3f>(name, value);
}

bool ShaderParameterChunk::setUniformParameter(const Char8 *name, 
                                               const Vec4f &value)
{
    return _parameter_access->setSParameter<ShaderParameterVec4f>(name, value);
}

bool ShaderParameterChunk::setUniformParameter(const Char8 *name, 
                                               const Matrix &value)
{
    return _parameter_access->setSParameter<ShaderParameterMatrix>(name, value);
}

bool ShaderParameterChunk::setUniformParameter(const Char8 *name, 
                                               const Pnt2f &value)
{
    return _parameter_access->setSParameter<ShaderParameterPnt2f>(name, value);
}

bool ShaderParameterChunk::setUniformParameter(const Char8 *name, 
                                               const Pnt3f &value)
{
    return _parameter_access->setSParameter<ShaderParameterPnt3f>(name, value);
}


// arrays

bool ShaderParameterChunk::setUniformParameter(const Char8   *name, 
                                               const MFInt32 &value)
{
    return _parameter_access->setMParameter<ShaderParameterMInt>(name, value);
}

bool ShaderParameterChunk::setUniformParameter(const Char8   *name, 
                                               const MFReal32 &value)
{
    return _parameter_access->setMParameter<ShaderParameterMReal>(name, value);
}

bool ShaderParameterChunk::setUniformParameter(const Char8   *name, 
                                               const MFVec2f &value)
{
    return _parameter_access->setMParameter<ShaderParameterMVec2f>(name, value);
}

bool ShaderParameterChunk::setUniformParameter(const Char8   *name, 
                                               const MFVec3f &value)
{
    return _parameter_access->setMParameter<ShaderParameterMVec3f>(name, value);
}

bool ShaderParameterChunk::setUniformParameter(const Char8   *name, 
                                               const MFVec4f &value)
{
    return _parameter_access->setMParameter<ShaderParameterMVec4f>(name, value);
}

bool ShaderParameterChunk::setUniformParameter(const Char8   *name, 
                                               const MFMatrix &value)
{
    return _parameter_access->setMParameter<ShaderParameterMMatrix>(name, 
                                                                    value);
}

/*------------------------------------ Get --------------------------------*/

bool ShaderParameterChunk::getUniformParameter(const Char8 *name, bool &value)
{
    return _parameter_access->getSParameter<ShaderParameterBool>(name, value);
}

bool ShaderParameterChunk::getUniformParameter(const Char8 *name, Int32 &value)
{
    return _parameter_access->getSParameter<ShaderParameterInt>(name, value);
}

bool ShaderParameterChunk::getUniformParameter(const Char8  *name, 
                                                     Real32 &value)
{
    return _parameter_access->getSParameter<ShaderParameterReal>(name, value);
}

bool ShaderParameterChunk::getUniformParameter(const Char8 *name, Vec2f &value)
{
    return _parameter_access->getSParameter<ShaderParameterVec2f>(name, value);
}

bool ShaderParameterChunk::getUniformParameter(const Char8 *name, Vec3f &value)
{
    return _parameter_access->getSParameter<ShaderParameterVec3f>(name, value);
}

bool ShaderParameterChunk::getUniformParameter(const Char8 *name, Vec4f &value)
{
    return _parameter_access->getSParameter<ShaderParameterVec4f>(name, value);
}

bool ShaderParameterChunk::getUniformParameter(const Char8  *name, 
                                                     Matrix &value)
{
    return _parameter_access->getSParameter<ShaderParameterMatrix>(name, value);
}

bool ShaderParameterChunk::getUniformParameter(const Char8 *name, Pnt2f &value)
{
    return _parameter_access->getSParameter<ShaderParameterPnt2f>(name, value);
}

bool ShaderParameterChunk::getUniformParameter(const Char8 *name, Pnt3f &value)
{
    return _parameter_access->getSParameter<ShaderParameterPnt3f>(name, value);
}



// arrays

bool ShaderParameterChunk::getUniformParameter(const Char8   *name, 
                                                     MFInt32 &value)
{
    return _parameter_access->getMParameter<ShaderParameterMInt>(name, value);
}

bool ShaderParameterChunk::getUniformParameter(const Char8    *name, 
                                                     MFReal32 &value)
{
    return _parameter_access->getMParameter<ShaderParameterMReal>(name, value);
}

bool ShaderParameterChunk::getUniformParameter(const Char8   *name, 
                                                     MFVec2f &value)
{
    return _parameter_access->getMParameter<ShaderParameterMVec2f>(name, value);
}

bool ShaderParameterChunk::getUniformParameter(const Char8   *name, 
                                                     MFVec3f &value)
{
    return _parameter_access->getMParameter<ShaderParameterMVec3f>(name, value);
}

bool ShaderParameterChunk::getUniformParameter(const Char8   *name, 
                                                     MFVec4f &value)
{
    return _parameter_access->getMParameter<ShaderParameterMVec4f>(name, value);
}

bool ShaderParameterChunk::getUniformParameter(const Char8    *name, 
                                                     MFMatrix &value)
{
    return _parameter_access->getMParameter<ShaderParameterMMatrix>(name, 
                                                                    value);
}

bool ShaderParameterChunk::subUniformParameter(const Char8 *name)
{
    return _parameter_access->subParameter(name);
}

void ShaderParameterChunk::clearUniformParameters(void)
{
    Inherited::clearParameters();

    if(_parameter_access != NULL)
        _parameter_access->updateMap();

    _cleared_parameters = true;
}

void ShaderParameterChunk::resolveLinks(void)
{
    Inherited::resolveLinks();

    if(_parameter_access != NULL)
        _parameter_access->updateMap();

    _cleared_parameters = true;
}
