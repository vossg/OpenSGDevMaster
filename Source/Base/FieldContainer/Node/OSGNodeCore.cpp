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

#include "OSGNodeCore.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGNodeCoreBase.cpp file.
// To modify it, please change the .fcd file (OSGNodeCore.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void NodeCore::initMethod(InitPhase ePhase)
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

NodeCore::NodeCore(void) :
    Inherited()
{
}

NodeCore::NodeCore(const NodeCore &source) :
    Inherited(source)
{
}

NodeCore::~NodeCore(void)
{
}

/*----------------------------- class specific ----------------------------*/

void NodeCore::accumulateMatrix(Matrix &result)
{
}

void NodeCore::adjustVolume(Volume &volume)
{
}

void NodeCore::invalidateVolume(void)
{
    MFParentsType::const_iterator pIt  = _mfParents.begin();
    MFParentsType::const_iterator pEnd = _mfParents.end  ();

    for(; pIt != pEnd; ++pIt)
        (*pIt)->invalidateVolume();
}

void NodeCore::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void NodeCore::dump(      UInt32    uiIndent,
                    const BitVector bvFlags  ) const
{
    indentLog(uiIndent, PLOG);

    PLOG << "Core"
         << "("
         << std::dec
         << this->getId()
         << ") : "
         << getType().getName()
         << " "
         << this
         << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "[" << std::endl;

    indentLog(uiIndent + 4, PLOG);
    PLOG << "Parents : " << std::endl;

    MFParentsType::const_iterator pIt  = _mfParents.begin();
    MFParentsType::const_iterator pEnd = _mfParents.end  ();

    for(UInt32 i = 0; pIt != pEnd; ++pIt)
    {
        indentLog(uiIndent + 4, PLOG);
        PLOG << "           " << i << ") " << *pIt << std::endl;
    }

    Inherited::dump(uiIndent + 4, bvFlags);

    indentLog(uiIndent, PLOG);
    PLOG << "]" << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "{" << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "}" << std::endl;
}

OSG_END_NAMESPACE
