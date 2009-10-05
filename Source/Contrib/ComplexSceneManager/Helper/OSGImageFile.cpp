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

#include "OSGImageFile.h"
#include "OSGImageFileHandler.h"
#include "OSGOSGSceneFileType.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGImageFileBase.cpp file.
// To modify it, please change the .fcd file (OSGImageFile.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ImageFile::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        OSGSceneFileType::the().registerEndNodeCallback(
            ImageFile::getClassType(),
            reinterpret_cast<OSGSceneFileType::Callback>(
                &ImageFile::postOSGLoading));
    }
}

void ImageFile::postOSGLoading(void)
{
    if(_sfUrl.getValue().empty() == false)
    {
        ImageFileHandler::the()->read(this, _sfUrl.getValue().c_str());
    }
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ImageFile::ImageFile(void) :
    Inherited()
{
}

ImageFile::ImageFile(const ImageFile &source) :
    Inherited(source)
{
}

ImageFile::~ImageFile(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ImageFile::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void ImageFile::dump(      UInt32    ,
                     const BitVector ) const
{
    SLOG << "Dump ImageFile NI" << std::endl;
}

OSG_END_NAMESPACE
