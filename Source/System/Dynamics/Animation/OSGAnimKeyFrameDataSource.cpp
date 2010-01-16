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

#include "OSGAnimKeyFrameDataSource.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGAnimKeyFrameDataSourceBase.cpp file.
// To modify it, please change the .fcd file (OSGAnimKeyFrameDataSource.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void AnimKeyFrameDataSource::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

AnimKeyFrameDataSource::AnimKeyFrameDataSource(void) :
    Inherited()
{
}

AnimKeyFrameDataSource::AnimKeyFrameDataSource(const AnimKeyFrameDataSource &source) :
    Inherited(source)
{
}

AnimKeyFrameDataSource::~AnimKeyFrameDataSource(void)
{
}

/*----------------------------- class specific ----------------------------*/

void AnimKeyFrameDataSource::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

/*! Length of this data source, defined as the time between the first
    and last key frame.
 */
Real32 AnimKeyFrameDataSource::getLength(void) const
{
    if(_mfInValues.empty() == false)
    {
        return _mfInValues.back() - _mfInValues.front();
    }
    else
    {
        return 0.f;
    }
}

void AnimKeyFrameDataSource::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump AnimKeyFrameDataSource NI" << std::endl;
}

OSG_END_NAMESPACE
