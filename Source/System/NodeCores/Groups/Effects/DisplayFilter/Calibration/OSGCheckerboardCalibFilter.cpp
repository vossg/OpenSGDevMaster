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

#include "OSGCheckerboardCalibFilter.h"
#include "OSGDisplayFilterStageData.h"
#include "OSGDrawEnv.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGCheckerboardCalibFilterBase.cpp file.
// To modify it, please change the .fcd file (OSGCheckerboardCalibFilter.fcd)
// and regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void CheckerboardCalibFilter::initMethod(InitPhase ePhase)
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

CheckerboardCalibFilter::CheckerboardCalibFilter(void) :
    Inherited()
{
}

CheckerboardCalibFilter::CheckerboardCalibFilter(
    const CheckerboardCalibFilter &source) :

    Inherited(source)
{
}

CheckerboardCalibFilter::~CheckerboardCalibFilter(void)
{
}

/*----------------------------- class specific ----------------------------*/

void CheckerboardCalibFilter::changed(ConstFieldMaskArg whichField, 
                                      UInt32            origin,
                                      BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void CheckerboardCalibFilter::dump(      UInt32    ,
                                   const BitVector ) const
{
    SLOG << "Dump CheckerboardCalibFilter NI" << std::endl;
}

void CheckerboardCalibFilter::processActive(DisplayFilterStageData *pData,
                                            DrawEnv                *pEnv )
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    glOrtho(0, 1, 0, 1, 0, 1);

    glPushAttrib(GL_DEPTH_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);

    glColor3fv(this->getColorWhite().getValuesRGB());
    
    glBegin(GL_QUADS);
    {
        glVertex2f  (0.00, 0.00);
        
        glVertex2f  (1.00, 0.00);
        
        glVertex2f  (1.00, 1.00);
        
        glVertex2f  (0.00, 1.00);
    }
    glEnd();

    UInt32 uiPWidth  = pEnv->getPixelWidth ();
    UInt32 uiPHeight = pEnv->getPixelHeight();

    UInt32 uiNumRows = this->getResolution();
    UInt32 uiNumCols = this->getResolution();

    Real32 rRowStep = 1.f / Real32(uiNumRows);
    Real32 rColStep = 1.f / Real32(uiNumCols);

    Real32 rCurrRow = 0.f;
    Real32 rCurrCol = 0.f;

    UInt32 uiColOff = 0;

    if(uiPWidth < uiPHeight)
    {
        Real32 fFact = Real32(uiPHeight) / Real32(uiPWidth);

        uiNumRows  = UInt32(fFact * Real32(uiNumRows)) + 1;
        rRowStep  /= fFact;

        if(this->getCenter() == true)
        {
            fFact  = 1.f - ((1.f / rRowStep) - UInt32(1.f / rRowStep));

            fFact *= rRowStep / 2.f;

            glTranslatef(0.f, -fFact, 0.f);
        }
    }
    else if(uiPHeight < uiPWidth)
    {
        Real32 fFact = Real32(uiPWidth) / Real32(uiPHeight);

        uiNumCols  = UInt32(fFact * Real32(uiNumCols)) + 1;
        rColStep  /= fFact;
        
        if(this->getCenter() == true)
        {
            fFact  = 1.f - ((1.f / rColStep) - UInt32(1.f / rColStep));

            fFact *= rColStep / 2.f;

            glTranslatef(-fFact, 0.f, 0.f);
        }
    }

    glColor3fv(this->getColorBlack().getValuesRGB());

    for(UInt32 i = 0; i < uiNumRows; ++i)
    {
        for(UInt32 j = uiColOff; j < uiNumCols; j += 2)
        {
            glBegin(GL_QUADS);
            {
                glVertex2f  (rCurrCol,            rCurrRow);
                
                glVertex2f  (rCurrCol + rColStep, rCurrRow);
            
                glVertex2f  (rCurrCol + rColStep, rCurrRow + rRowStep);
            
                glVertex2f  (rCurrCol,            rCurrRow + rRowStep);
            }
            glEnd();

            rCurrCol += 2 * rColStep;
        }

        rCurrRow += rRowStep;
        uiColOff  = 1 - uiColOff;
        rCurrCol  = uiColOff * rColStep;
    }

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glPopAttrib();
}

void CheckerboardCalibFilter::processInactive(DisplayFilterStageData *pData,
                                              DrawEnv                *pEnv )
{
    Inherited::processInactive(pData, pEnv);
}

OSG_END_NAMESPACE
