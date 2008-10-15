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

#include "OSGDistortionDisplayFilter.h"
#include "OSGDisplayFilterStageData.h"
#include "OSGDrawEnv.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGDistortionDisplayFilterBase.cpp file.
// To modify it, please change the .fcd file (OSGDistortionDisplayFilter.fcd)
// and regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void DistortionDisplayFilter::initMethod(InitPhase ePhase)
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

DistortionDisplayFilter::DistortionDisplayFilter(void) :
    Inherited()
{
}

DistortionDisplayFilter::DistortionDisplayFilter(
    const DistortionDisplayFilter &source) :

    Inherited(source)
{
}

DistortionDisplayFilter::~DistortionDisplayFilter(void)
{
}

/*----------------------------- class specific ----------------------------*/

void DistortionDisplayFilter::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void DistortionDisplayFilter::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump DistortionDisplayFilter NI" << std::endl;
}

void DistortionDisplayFilter::process(DisplayFilterStageData *pData)
{
    if(this->getRows   () < 2 || 
       this->getColumns() < 2 ||
       this->getRows() * this->getColumns() != this->getMFPositions()->size())
    {
        glBegin(GL_QUADS);
        {
            glTexCoord2f(0.00, 0.00);
            glVertex2f  (0.00, 0.00);
            
            glTexCoord2f(1.00, 0.00);
            glVertex2f  (1.00, 0.00);
            
            glTexCoord2f(1.00, 1.00);
            glVertex2f  (1.00, 1.00);
            
            glTexCoord2f(0.00, 1.00);
            glVertex2f  (0.00, 1.00);
        }
        glEnd();
    }
    else
    {
              UInt32   uiWidth  = this->getColumns() - 1;
              UInt32   uiHeight = this->getRows   () - 1;
        const MFVec2f &vPos     = *(this->getMFPositions());

        UInt16 x,y;
        Real32 xstep,ystep;

        Real32 x0,  x1,  y0,  y1;

        xstep = 1.0f / (uiWidth);
        ystep = 1.0f / (uiHeight);

        x0 = 0; 
        y0 = 0;

        UInt16 yI0 = 0;
        UInt16 yI1 = uiWidth + 1;

        for(y = 0; y < uiHeight; y++)
        {
            y1 = y0 + ystep;

            for(x = 0; x < uiWidth; x++)
            {
                x1 = x0 + xstep;

                glBegin(GL_QUADS);
                {
                    glTexCoord2f(x0, y0);
                    glVertex2fv (vPos[yI0 + x    ].getValues()); 

                    glTexCoord2f(x1, y0);
                    glVertex2fv (vPos[yI0 + x + 1].getValues());

                    glTexCoord2f(x1, y1);
                    glVertex2fv (vPos[yI1 + x + 1].getValues());

                    glTexCoord2f(x0, y1);
                    glVertex2fv (vPos[yI1 + x    ].getValues());
                }
                glEnd();

                x0 += xstep;
            }
            
            x0   =  0;
            y0   = y1;

            yI0  = yI1;
            yI1 += uiWidth + 1;
        }
    }
}

OSG_END_NAMESPACE
