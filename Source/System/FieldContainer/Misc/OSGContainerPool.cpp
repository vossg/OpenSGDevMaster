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

#include "OSGContainerPool.h"

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGContainerPoolBase.cpp file.
// To modify it, please change the .fcd file (OSGContainerPool.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ContainerPool::initMethod(InitPhase ePhase)
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

ContainerPool::ContainerPool(void) :
    Inherited()
{
}

ContainerPool::ContainerPool(const ContainerPool &source) :
    Inherited(source)
{
}

ContainerPool::~ContainerPool(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ContainerPool::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void ContainerPool::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump ContainerPool NI" << std::endl;
}

/*! Add another container to the pool.
* @param container  The container to add.
*/
void ContainerPool::addContainer(FieldContainerPtr container)
{
   /*
   editMField(ContainersFieldMask, _mfContainers);
   _mfContainers.push_back(container);
   addRef(container);
   */
   pushToContainers(container);
}

/*! Remove a container if it is found.
*/
void ContainerPool::subContainer(FieldContainerPtr container)
{
   removeFromContainers(container);
}

/*! Return the number of containers. */
UInt32 ContainerPool::getNContainers()
{
   return _mfContainers.size();
}

