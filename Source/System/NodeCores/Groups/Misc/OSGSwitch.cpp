/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#include "OSGSwitch.h"

#include "OSGRenderAction.h"
#include "OSGIntersectAction.h"

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGSwitchBase.cpp file.
// To modify it, please change the .fcd file (OSGSwitch.fcd) and
// regenerate the base file.

/*-------------------------------------------------------------------------*/
/*                                Sync                                     */

void Switch::changed(ConstFieldMaskArg whichField, 
                     UInt32            origin,
                     BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

/*-------------------------------------------------------------------------*/
/*                               Dump                                      */

void Switch::dump(      UInt32    OSG_CHECK_ARG(uiIndent), 
                  const BitVector OSG_CHECK_ARG(bvFlags )) const
{
    SLOG << "Dump Switch NI" << std::endl;
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

Switch::Switch(void) :
    Inherited()
{
}

Switch::Switch(const Switch &source) :
    Inherited(source)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

Switch::~Switch(void)
{
}

/*-------------------------------------------------------------------------*/
/*                               Draw                                      */

#ifdef OSG_OLD_RENDER_ACTION
ActionBase::ResultE Switch::render(Action *action)
{
    ActionBase::ResultE  returnValue = ActionBase::Continue;

    DrawActionBase  *da          = dynamic_cast<DrawActionBase *>(action);

    if((getChoice() >= 0                          ) && 
       (UInt32(getChoice()) < action->getNNodes()))
    {
        da->useNodeList();

        if(da->isVisible(action->getNode(getChoice())))
        {
            da->addNode(action->getNode(getChoice()));
        }
    }
    else if(getChoice() == ALL)
    {
        if(da->selectVisibles() == 0)
        {
            returnValue = ActionBase::Skip;
        }
    }
    else
    {
        returnValue = ActionBase::Skip;
    }

    return returnValue;
}
#endif

ActionBase::ResultE Switch::renderEnter(Action *action)
{
    Action::ResultE  returnValue = Action::Continue;
    RenderAction    *ra          = dynamic_cast<RenderAction*>(action);
    
    if(ra->pushVisibility() == true)
    {
       if((this->getChoice()                      >= 0              ) &&
          (static_cast<UInt32>(this->getChoice()) <  ra->getNNodes())   )
        {
            ra->useNodeList();
        
            if(ra->isVisible(ra->getNode(this->getChoice())))
            {
                ra->addNode(ra->getNode(this->getChoice()));
            }
            else
            {
                ra->popVisibility();
                returnValue = Action::Skip;
            }
        }
        else if(this->getChoice() == Switch::ALL)
        {
            if(ra->selectVisibles() == 0)
            {
                ra->popVisibility();
                returnValue = Action::Skip;
            }
        }
        else
        {
            ra->popVisibility();
            returnValue = Action::Skip;
        }
    }
    
    return returnValue;
}

ActionBase::ResultE Switch::renderLeave(Action *action)
{
    RenderAction *ra = dynamic_cast<RenderAction *>(action);

    ra->popVisibility();
    
    return ActionBase::Continue;
}

ActionBase::ResultE Switch::intersect(Action *action)
{
    ActionBase::ResultE  returnValue = ActionBase::Continue;
    IntersectAction     *ia          = dynamic_cast<IntersectAction *>(action);

    if((getChoice()         >= 0              ) && 
       (UInt32(getChoice()) <  ia->getNNodes())   )
    {
        ia->useNodeList(                        );
        ia->addNode    (ia->getNode(getChoice()));
    }
    else if(getChoice() == ALL)
    {
        returnValue = ActionBase::Continue;
    }
    else
    {
        returnValue = ActionBase::Skip;
    }

    return returnValue;
}
 
/*-------------------------------------------------------------------------*/
/*                                Init                                     */

void Switch::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        RenderAction::registerEnterDefault(
            Switch::getClassType(),
            reinterpret_cast<Action::Callback>(&Switch::renderEnter));
    
        RenderAction::registerLeaveDefault(
            Switch::getClassType(),
            reinterpret_cast<Action::Callback>(&Switch::renderLeave));
        
        IntersectAction::registerEnterDefault(
            getClassType(),
            reinterpret_cast<Action::Callback>(&Switch::intersect));
    }
}

