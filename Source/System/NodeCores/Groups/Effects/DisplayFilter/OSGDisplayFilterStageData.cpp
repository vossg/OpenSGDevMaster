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

#include "OSGDisplayFilterStageData.h"
#include "OSGDisplayFilterStage.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGDisplayFilterStageDataBase.cpp file.
// To modify it, please change the .fcd file (OSGDisplayFilterStageData.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void DisplayFilterStageData::initMethod(InitPhase ePhase)
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

DisplayFilterStageData::DisplayFilterStageData(void) :
     Inherited        (    ),
    _pColFilter       (NULL),
    _pDistFilter      (NULL),
    _pCalibFilter     (NULL),
    _pInitColTableFrom(NULL)
{
}

DisplayFilterStageData::DisplayFilterStageData(
    const DisplayFilterStageData &source) :

     Inherited        (source),
    _pColFilter       (NULL  ),
    _pDistFilter      (NULL  ),
    _pCalibFilter     (NULL  ),
    _pInitColTableFrom(NULL  )
{
}

DisplayFilterStageData::~DisplayFilterStageData(void)
{
}

/*----------------------------- class specific ----------------------------*/

void DisplayFilterStageData::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void DisplayFilterStageData::dump(      UInt32    ,
                                  const BitVector ) const
{
    SLOG << "Dump DisplayFilterStageData NI" << std::endl;
}

void DisplayFilterStageData::updateData(FieldContainer *pStageCore,
                                        BitVector       whichField,
                                        UInt32          origin    )
{
    DisplayFilterStage *pCore = dynamic_cast<DisplayFilterStage *>(pStageCore);

    if(pCore == NULL)
        return;

    fprintf(stderr, "dfs data updateData %d | 0x%016"PRIx64"\n", 
            origin,
            whichField);
    
    if(0x0000 != (whichField & DisplayFilterStage::EnableMultiSampleFieldMask))
    {
        if(this->getTarget() != NULL)
        {
            this->getTarget()->setEnableMultiSample(
                pCore->getEnableMultiSample());
        }
    }

    if(0x0000 != (whichField & DisplayFilterStage::ColorSamplesFieldMask))
    {
        if(this->getTarget() != NULL)
        {
            this->getTarget()->setColorSamples(
                pCore->getColorSamples());
        }
    }

    if(0x0000 != (whichField & DisplayFilterStage::CoverageSamplesFieldMask))
    {
        if(this->getTarget() != NULL)
        {
            this->getTarget()->setCoverageSamples(
                pCore->getCoverageSamples());
        }
    }

    if(0x0000 != (whichField & 
                  DisplayFilterStage::FixedSampleLocationFieldMask))
    {
        if(this->getTarget() != NULL)
        {
            this->getTarget()->setFixedSampleLocation(
                pCore->getFixedSampleLocation());
        }
    }
}

OSG_END_NAMESPACE
