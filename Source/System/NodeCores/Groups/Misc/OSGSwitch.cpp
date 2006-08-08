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

#include <stdlib.h>
#include <stdio.h>

#include <OSGConfig.h>

#include "OSGSwitch.h"

#include <OSGRenderAction.h>
#include <OSGIntersectAction.h>

OSG_USING_NAMESPACE

/*! \class osg::Switch
*/

/*-------------------------------------------------------------------------*/
/*                                Sync                                     */

void Switch::changed(ConstFieldMaskArg whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
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

ActionBase::ResultE Switch::render(Action *action)
{
    ActionBase::ResultE  returnValue = ActionBase::Continue;

    DrawActionBase  *da          = dynamic_cast<DrawActionBase *>(action);

    if((getChoice() >= 0                          ) && 
       (UInt32(getChoice()) < action->getNNodes()))
    {
        da->useNodeList();

        if(da->isVisible(getCPtr(action->getNode(getChoice()))))
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

ActionBase::ResultE Switch::intersect(Action *action)
{
    ActionBase::ResultE  returnValue = ActionBase::Continue;
    IntersectAction     *da          = dynamic_cast<IntersectAction *>(action);

    if((getChoice() >= 0                          ) && 
       (UInt32(getChoice()) < action->getNNodes()))
    {
        da->addNode(action->getNode(getChoice()));
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
            getClassType(),
            reinterpret_cast<Action::Callback>(&Switch::render));
        
        IntersectAction::registerEnterDefault(
            getClassType(),
            reinterpret_cast<Action::Callback>(&Switch::intersect));
    }
}


/*-------------------------------------------------------------------------*/
/*                              cvs id's                                   */

#ifdef __sgi
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp[] = "@(#)$Id: $";
    static Char8 cvsid_hpp[] = OSGSWITCH_HEADER_CVSID;
    static Char8 cvsid_inl[] = OSGSWITCH_INLINE_CVSID;
}
