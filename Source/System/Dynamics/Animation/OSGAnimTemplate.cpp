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

#include "OSGAnimTemplate.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGAnimTemplateBase.cpp file.
// To modify it, please change the .fcd file (OSGAnimTemplate.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void AnimTemplate::initMethod(InitPhase ePhase)
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

AnimTemplate::AnimTemplate(void)
    : Inherited  (    )
    , _animLength(-1.f)
{
}

AnimTemplate::AnimTemplate(const AnimTemplate &source)
    : Inherited  (source)
    , _animLength(-1.f  )
{
}

AnimTemplate::~AnimTemplate(void)
{
}

/*----------------------------- class specific ----------------------------*/

void AnimTemplate::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    if(0 != (SourcesFieldMask & whichField))
    {
        updateLength();
    }

    Inherited::changed(whichField, origin, details);
}

Int32
AnimTemplate::findTargetId(const std::string &targetId, Int32 offset) const
{
    OSG_ASSERT(_mfTargetIds.size() == _mfSources.size());

    Int32 index = -1;

    if(offset >= 0 && offset < Int32(_mfSources.size()))
    {
        MFTargetIdsType::const_iterator idIt  = _mfTargetIds.begin();
        MFTargetIdsType::const_iterator idEnd = _mfTargetIds.end  ();

        idIt += offset;

        for(; idIt != idEnd; ++idIt, ++offset)
        {
            FDEBUG(("AnimTemplate::findTargetId: targetId [%s] - [%s]\n",
                    targetId.c_str(), idIt->c_str()));

            if(idIt->find(targetId) == 0)
            {
                index = offset;
                break;
            }
        }
    }

    return index;
}

void AnimTemplate::dump(      UInt32    uiIndent,
                        const BitVector bvFlags  ) const
{
    SLOG;
    indentLog(uiIndent, PLOG);

    PLOG << "AnimTemplate (" << _sfName.getValue() << ") :\n";

    uiIndent += 4;

    MFTargetIdsType::const_iterator idIt  = _mfTargetIds.begin();
    MFTargetIdsType::const_iterator idEnd = _mfTargetIds.end  ();

    for(; idIt != idEnd; ++idIt)
    {
        SLOG;
        indentLog(uiIndent, PLOG);

        PLOG << *idIt << "\n";
    }
    
    uiIndent -= 4;
}

void AnimTemplate::updateLength(void) const
{
    MFSourcesType::const_iterator sIt  = getMFSources()->begin();
    MFSourcesType::const_iterator sEnd = getMFSources()->end  ();

    if(sIt != sEnd)
    {
        _animLength = 0.f;

        for(; sIt != sEnd; ++sIt)
        {
            _animLength = osgMax(_animLength, (*sIt)->getLength());
        }
    }
    else
    {
        _animLength = -1.f;
    }
}


OSG_END_NAMESPACE
