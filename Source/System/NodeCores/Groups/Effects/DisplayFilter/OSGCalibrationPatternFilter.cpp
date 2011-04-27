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

#include "OSGCalibrationPatternFilter.h"
#include "OSGDisplayFilterStageData.h"
#include "OSGDrawEnv.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGCalibrationPatternFilterBase.cpp file.
// To modify it, please change the .fcd file (OSGCalibrationPatternFilter.fcd)
// and regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void CalibrationPatternFilter::initMethod(InitPhase ePhase)
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

CalibrationPatternFilter::CalibrationPatternFilter(void) :
    Inherited()
{
}

CalibrationPatternFilter::CalibrationPatternFilter(
    const CalibrationPatternFilter &source) :

    Inherited(source)
{
}

CalibrationPatternFilter::~CalibrationPatternFilter(void)
{
}

void CalibrationPatternFilter::onCreate(const CalibrationPatternFilter *source)
{
    Inherited::onCreate(source);

    // Don't add the prototype instances to the list
    if(GlobalSystemState != Running)
        return;
}

/*----------------------------- class specific ----------------------------*/

void CalibrationPatternFilter::changed(ConstFieldMaskArg whichField, 
                                       UInt32            origin,
                                       BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void CalibrationPatternFilter::dump(      UInt32    ,
                                    const BitVector ) const
{
    SLOG << "Dump CalibrationPatternFilter NI" << std::endl;
}

void CalibrationPatternFilter::processActive(DisplayFilterStageData *pData,
                                            DrawEnv                *pEnv)
{
}

void CalibrationPatternFilter::processInactive(DisplayFilterStageData *pData,
                                               DrawEnv                *pEnv)
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    glOrtho(0, 1, 0, 1, 0, 1);

    glColor3f(0.f, 0.f, 0.f);
    
    glBegin(GL_QUADS);
    {
        glVertex2f  (0.00, 0.00);
        
        glVertex2f  (1.00, 0.00);
        
        glVertex2f  (1.00, 1.00);
        
        glVertex2f  (0.00, 1.00);
    }
    glEnd();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}


OSG_END_NAMESPACE
