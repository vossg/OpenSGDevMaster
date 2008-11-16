/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
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

#include "OSGShaderProgramFile.h"
#include "OSGOSGSceneFileType.h"
#include "OSGSceneFileHandler.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGShaderProgramFileBase.cpp file.
// To modify it, please change the .fcd file (OSGShaderProgramFile.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ShaderProgramFile::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        OSGSceneFileType::the().registerEndNodeCallback(
            ShaderProgramFile::getClassType(),
            reinterpret_cast<OSGSceneFileType::Callback>(
                &ShaderProgramFile::postOSGLoading));
    }
}

void ShaderProgramFile::postOSGLoading(void)
{
    if(_sfProgramUrl.getValue().empty() == false)
    {
        std::string szFilenameResolved = 
            SceneFileHandler::the()->getPathHandler()->findFile(
                _sfProgramUrl.getValue().c_str());

        if(szFilenameResolved.empty() == false)
        {
            Inherited::readProgram(szFilenameResolved.c_str());
        }
    }
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ShaderProgramFile::ShaderProgramFile(void) :
    Inherited()
{
}

ShaderProgramFile::ShaderProgramFile(const ShaderProgramFile &source) :
    Inherited(source)
{
}

ShaderProgramFile::~ShaderProgramFile(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ShaderProgramFile::changed(ConstFieldMaskArg whichField, 
                                UInt32            origin,
                                BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void ShaderProgramFile::dump(      UInt32    ,
                             const BitVector ) const
{
    SLOG << "Dump ShaderProgramFile NI" << std::endl;
}

OSG_END_NAMESPACE
