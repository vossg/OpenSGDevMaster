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

#include "OSGDynamicStateGenerator.h"
#include "OSGDynamicStateGeneratorStageData.h"
#include "OSGRenderAction.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGDynamicStateGeneratorBase.cpp file.
// To modify it, please change the .fcd file (OSGDynamicStateGenerator.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void DynamicStateGenerator::initMethod(InitPhase ePhase)
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

DynamicStateGenerator::DynamicStateGenerator(void) :
    Inherited()
{
}

DynamicStateGenerator::DynamicStateGenerator(
    const DynamicStateGenerator &source) :
    Inherited(source)
{
}

DynamicStateGenerator::~DynamicStateGenerator(void)
{
}

/*----------------------------- class specific ----------------------------*/

void DynamicStateGenerator::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void DynamicStateGenerator::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump DynamicStateGenerator NI" << std::endl;
}

ActionBase::ResultE DynamicStateGenerator::renderEnter(Action *action)
{
    RenderAction *pAction = 
        dynamic_cast<RenderAction *>(action);

    // pop the state and make sure we have the last word.
    ActionBase::ResultE returnValue = Inherited::renderEnter(action);

    if(pAction != NULL)
    {
        DynamicStateGeneratorStageData *pData = 
            pAction->getData<DynamicStateGeneratorStageData *>(_iDataSlotId);

        if(pData != NULL)
        {
            MFUnrecStateChunkPtr::const_iterator chIt   = pData->beginChunks();
            MFUnrecStateChunkPtr::const_iterator chEnd  = pData->endChunks  ();
            UInt32                               uiSlot = 0;

            while(chIt != chEnd)
            {
                if(*chIt != NULL)
                    pAction->addOverride(uiSlot, *chIt);
                
                ++uiSlot;
                ++chIt;
            }
        }
    }

    return returnValue;
}

ActionBase::ResultE DynamicStateGenerator::renderLeave(Action *action)
{
    return Inherited::renderLeave(action);
}



OSG_END_NAMESPACE
