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

#include "OSGMultiSwitch.h"

#include "OSGRenderAction.h"
#include "OSGIntersectAction.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGMultiSwitchBase.cpp file.
// To modify it, please change the .fcd file (OSGMultiSwitch.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void MultiSwitch::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        RenderAction::registerEnterDefault(
            MultiSwitch::getClassType(),
            reinterpret_cast<Action::Callback>(&MultiSwitch::renderEnter));

        RenderAction::registerLeaveDefault(
            MultiSwitch::getClassType(),
            reinterpret_cast<Action::Callback>(&MultiSwitch::renderLeave));

        IntersectAction::registerEnterDefault(
            MultiSwitch::getClassType(),
            reinterpret_cast<Action::Callback>(&MultiSwitch::intersectEnter));
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*! Sets \c _mfChoices such that it only contains those indices that correspond
    to ones in \a childMask, i.e. if \a childMask is \c 00101 (binary) children
    with indices 0 and 2 are selected.
 */
void MultiSwitch::setBitfield(const BitVector childMask)
{
    _mfChoices.clear();

    BitVector anchor = 1;
    for(UInt32 idx = 0; idx < 64; ++idx)
    {
        BitVector mask = anchor << idx;

        if(childMask & mask)
            _mfChoices.push_back(idx);
    }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

MultiSwitch::MultiSwitch(void) :
    Inherited()
{
}

MultiSwitch::MultiSwitch(const MultiSwitch &source) :
    Inherited(source)
{
}

MultiSwitch::~MultiSwitch(void)
{
}

/*----------------------------- class specific ----------------------------*/

Action::ResultE MultiSwitch::renderEnter(Action *action)
{
    Action::ResultE  returnValue = Action::Continue;
    RenderAction    *ra          = dynamic_cast<RenderAction*>(action);

    if(ra->pushVisibility() == true)
    {
        switch(getSwitchMode())
        {
        default:
            FWARNING(("MultiSwitch::renderEnter: Invalid switchMode.\n"));
            // fall through!
        case CHOICES:
        {
            if(_mfChoices.empty())
            {
                returnValue = Action::Skip;
            }
            else
            {
                ra->useNodeList();

                //
                // Assumption: _mfChoices is sorted; see function changed
                //
                MFChoicesType::const_iterator choiceIt  = _mfChoices.begin();
                MFChoicesType::const_iterator choiceEnd = _mfChoices.end();
                UInt32                        numNodes  = ra->getNNodes();

                for(; choiceIt != choiceEnd; ++choiceIt)
                {
                    if(*choiceIt < numNodes                  &&
                       ra->isVisible(ra->getNode(*choiceIt))   )
                    {
                        ra->addNode(ra->getNode(*choiceIt));
                    }
                }
            }
        }
        break;
        case NONE:
        {
            returnValue = Action::Skip;
        }
        break;
        case ALL:
        {
            if(ra->selectVisibles() == 0)
                returnValue = Action::Skip;
        }
        break;
        }
    }

    return returnValue;
}

Action::ResultE MultiSwitch::renderLeave(Action *action)
{
    RenderAction *ra = dynamic_cast<RenderAction*>(action);

    ra->popVisibility();

    return Action::Continue;
}

Action::ResultE MultiSwitch::intersectEnter(Action *action)
{
    Action::ResultE  returnValue = Action::Continue;
    IntersectAction *ia          = dynamic_cast<IntersectAction *>(action);

    switch(getSwitchMode())
    {
    default:
        FWARNING(("MultiSwitch::intersectEnter: Invalid switchMode.\n"));
        // fall through!
    case CHOICES:
    {
        if(_mfChoices.empty())
        {
            returnValue = Action::Skip;
        }
        else
        {
            ia->useNodeList();

            //
            // Assumption: _mfChoices is sorted; see function changed
            //
            MFChoicesType::const_iterator choiceIt  = _mfChoices.begin();
            MFChoicesType::const_iterator choiceEnd = _mfChoices.end();
            UInt32                        numNodes  = ia->getNNodes();

            for(; choiceIt != choiceEnd; ++choiceIt)
            {
                if(*choiceIt < numNodes)
                   ia->addNode(ia->getNode(*choiceIt));
            }
        }
    }
    break;
    case NONE:
    {
        returnValue = Action::Skip;
    }
    break;
    case ALL:
    {
        returnValue = Action::Continue;
    }
    break;
    }

    return returnValue;
}

void MultiSwitch::changed(ConstFieldMaskArg whichField,
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);

    if(whichField & ChoicesFieldMask)
    {
        // sort _mfChoices and remove duplicates

        std::sort(_mfChoices.begin(), _mfChoices.end());

        _mfChoices.erase(std::unique(_mfChoices.begin(),
                                     _mfChoices.end  () ),
                         _mfChoices.end()                 );
    }
}

void MultiSwitch::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump MultiSwitch NI" << std::endl;
}

OSG_END_NAMESPACE
