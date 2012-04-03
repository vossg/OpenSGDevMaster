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

#include "OSGConfig.h"

#include "OSGSimpleSHLChunkFile.h"
#include "OSGOSGSceneFileType.h"
#include "OSGSceneFileHandler.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGSimpleSHLChunkFileBase.cpp file.
// To modify it, please change the .fcd file (OSGSimpleSHLChunkFile.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void SimpleSHLChunkFile::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}

void SimpleSHLChunkFile::postOSGLoading(FileContextAttachment * const pContext)
{
    Inherited::postOSGLoading(pContext);

    if(_sfVertexProgramUrl.getValue().empty() == false)
    {
        std::string szFilenameResolved = 
            SceneFileHandler::the()->getPathHandler()->findFile(
                _sfVertexProgramUrl.getValue().c_str());

        if(szFilenameResolved.empty() == false)
        {
            Inherited::readVertexProgram(szFilenameResolved.c_str());
        }
    }

    if(_sfGeometryProgramUrl.getValue().empty() == false)
    {
        std::string szFilenameResolved = 
            SceneFileHandler::the()->getPathHandler()->findFile(
                _sfGeometryProgramUrl.getValue().c_str());

        if(szFilenameResolved.empty() == false)
        {
            Inherited::readGeometryProgram(szFilenameResolved.c_str());
        }
    }

    if(_sfFragmentProgramUrl.getValue().empty() == false)
    {
        std::string szFilenameResolved = 
            SceneFileHandler::the()->getPathHandler()->findFile(
                _sfFragmentProgramUrl.getValue().c_str());

        if(szFilenameResolved.empty() == false)
        {
            Inherited::readFragmentProgram(szFilenameResolved.c_str());
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

SimpleSHLChunkFile::SimpleSHLChunkFile(void) :
    Inherited()
{
}

SimpleSHLChunkFile::SimpleSHLChunkFile(const SimpleSHLChunkFile &source) :
    Inherited(source)
{
}

SimpleSHLChunkFile::~SimpleSHLChunkFile(void)
{
}

/*----------------------------- class specific ----------------------------*/

void SimpleSHLChunkFile::changed(ConstFieldMaskArg whichField, 
                                 UInt32            origin,
                                 BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void SimpleSHLChunkFile::dump(      UInt32    ,
                              const BitVector ) const
{
    SLOG << "Dump SimpleSHLChunkFile NI" << std::endl;
}

OSG_END_NAMESPACE
