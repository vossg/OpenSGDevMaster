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

#include "OSGCSMSceneParameter.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGCSMSceneParameterBase.cpp file.
// To modify it, please change the .fcd file (OSGCSMSceneParameter.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void CSMSceneParameter::initMethod(InitPhase ePhase)
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

CSMSceneParameter::CSMSceneParameter(void) :
    Inherited()
{
}

CSMSceneParameter::CSMSceneParameter(const CSMSceneParameter &source) :
    Inherited(source)
{
}

CSMSceneParameter::~CSMSceneParameter(void)
{
}

/*----------------------------- class specific ----------------------------*/

void CSMSceneParameter::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);

    if(0x0000 != (whichField & SceneRefFieldMask))
    {
        if(_sfSceneRef.getValue() != NULL)
        {
            Vec3f vVolMin;
            Vec3f vVolMax;

            _sfSceneRef.getValue()->editVolume(true).getBounds(vVolMin, 
                                                               vVolMax);

            std::cerr << "Volume: from " 
                      << vVolMin << " to " 
                      << vVolMax << std::endl;

            editSFSceneDiag()->setValue(vVolMax - vVolMin);

            editSFSceneCenter()->setValue(
                Pnt3f((vVolMin[0] + vVolMax[0]) * .5,
                      (vVolMin[1] + vVolMax[1]) * .5,
                      (vVolMin[2] + vVolMax[2]) * .5));

            Real32 rDist = 
                osgMax(_sfSceneDiag.getValue()[0],
                       _sfSceneDiag.getValue()[1]) * _sfDistScale.getValue();

            editSFInitViewPos()->setValue(
                Pnt3f(_sfSceneCenter.getValue()[0],
                      _sfSceneCenter.getValue()[1],
                      _sfSceneCenter.getValue()[2] + rDist));

            std::cerr << "Center: " << getSceneCenter()
                      << std::endl;
        }
    }
}

void CSMSceneParameter::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump CSMSceneParameter NI" << std::endl;
}

OSG_END_NAMESPACE
