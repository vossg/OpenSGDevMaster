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

#include "OSGChunkMaterial.h"
#include "OSGFrameBufferObject.h"
#include "OSGSimpleSHLChunk.h"
#include "OSGAlgorithmComputeElementData.h"
#include "OSGAlgorithmComputeElement.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGAlgorithmComputeElementDataBase.cpp file.
// To modify it, please change the .fcd file
// (OSGAlgorithmComputeElementData.fcd) and regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void AlgorithmComputeElementData::initMethod(InitPhase ePhase)
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

AlgorithmComputeElementData::AlgorithmComputeElementData(void) :
     Inherited(    ),
    _pTask    (NULL)
{
}

AlgorithmComputeElementData::AlgorithmComputeElementData(
    const AlgorithmComputeElementData &source) :

     Inherited(source),
    _pTask    (NULL  )
{
}

AlgorithmComputeElementData::~AlgorithmComputeElementData(void)
{
}

void AlgorithmComputeElementData::setTask(ComputeAlgorithmDrawTask *pTask)
{
    _pTask = pTask;
}

ComputeAlgorithmDrawTask *AlgorithmComputeElementData::getTask(void)
{
    return _pTask;
}

void AlgorithmComputeElementData::resolveLinks(void)
{
    Inherited::resolveLinks();

    _pTask = NULL;
}

/*----------------------------- class specific ----------------------------*/

void AlgorithmComputeElementData::changed(ConstFieldMaskArg whichField, 
                                          UInt32            origin,
                                          BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void AlgorithmComputeElementData::dump(      UInt32    ,
                                       const BitVector ) const
{
    SLOG << "Dump AlgorithmComputeElementData NI" << std::endl;
}

#if 0
void VolumeCoreData::updateData(FieldContainer *pCore,
                                BitVector       whichField,
                                UInt32          origin    )
{
}
#endif

OSG_END_NAMESPACE
