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

#include <sstream>
#include <fstream>

#include <boost/bind.hpp>

#include "OSGConfig.h"

#include "OSGAction.h"
#include "OSGCamera.h"
#include "OSGRenderAction.h"
#include "OSGSceneFileHandler.h"
#include "OSGVolumeDraw.h"
#include "OSGIntersectAction.h"

#include "OSGVisitSubTree.h"

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGVisitSubTreeBase.cpp file.
// To modify it, please change the .fcd file (OSGVisitSubTree.fcd) and
// regenerate the base file.

/*-------------------------------------------------------------------------*/
/*                               Sync                                      */

void VisitSubTree::changed(ConstFieldMaskArg whichField, 
                           UInt32            origin,
                           BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

//! Set the value of the VisitSubTree::_sfSubTreeRoot field.
void VisitSubTree::setSubTreeRoot(Node * const value)
{
    editSField(SubTreeRootFieldMask);

    if(_sfSubTreeRoot.getValue() != NULL)
    {
        _sfSubTreeRoot.getValue()->subChangedFunctor(
            boost::bind(&VisitSubTree::rootChanged, this, _1, _2));
    }

    if(value != NULL)
    {
        value->addChangedFunctor(
            boost::bind(&VisitSubTree::rootChanged, this, _1, _2),
            "");
    }

    _sfSubTreeRoot.setValue(value);
}

void VisitSubTree::rootChanged(FieldContainer    *pFC, 
                               ConstFieldMaskArg  whichField)
{
    if(0x0000 != (whichField & Node::VolumeFieldMask))
    {
        this->invalidateVolume();
    }
}

/*-------------------------------------------------------------------------*/
/*                               Dump                                      */

void VisitSubTree::dump(       UInt32    OSG_CHECK_ARG(uiIndent), 
                         const BitVector OSG_CHECK_ARG(bvFlags )) const
{
    SLOG << "Dump VisitSubTree NI" << std::endl;
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

VisitSubTree::VisitSubTree(void) :
    Inherited()
{
}

VisitSubTree::VisitSubTree(const VisitSubTree &source) :
    Inherited(source)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

VisitSubTree::~VisitSubTree(void)
{
}

/*! 
  If url was loaded, extend volume by loaded geometry. Otherwise
  extend volume by the volume given in the proxy object
*/

void VisitSubTree::adjustVolume(Volume &volume)
{
    if(getSubTreeRoot() != NULL)
    {
        getSubTreeRoot()->updateVolume();

        volume.extendBy(getSubTreeRoot()->getVolume());
    }
}

/*-------------------------------------------------------------------------*/
/*                                Draw                                     */

ActionBase::ResultE VisitSubTree::renderEnter(Action *action)
{
    RenderAction *a = dynamic_cast<RenderAction *>(action);

    a->useNodeList();
      
    a->pushTravMask();

    switch(_sfTravMaskMode.getValue())
    {
        case VisitSubTree::AndTravMask:
            a->andTravMask(_sfSubTreeTravMask.getValue());
            break;
        case VisitSubTree::OrTravMask:
            a->orTravMask(_sfSubTreeTravMask.getValue());
            break;
        case VisitSubTree::ReplaceTravMask:
            a->setTravMask(_sfSubTreeTravMask.getValue());
            break;
        default:
            break;
    }

    if(this->getSubTreeRoot() != NULL && a->isVisible(this->getSubTreeRoot()))
    {
        a->addNode(this->getSubTreeRoot());
    }

    return Action::Continue;
}

ActionBase::ResultE VisitSubTree::renderLeave(Action *action)
{
    action->popTravMask();

    return Action::Continue;
}

/*-------------------------------------------------------------------------*/
/*                             Intersect                                   */

ActionBase::ResultE VisitSubTree::intersect(Action *action)
{
          IntersectAction *ia = dynamic_cast<IntersectAction *>(action);
    const BoxVolume       &bv = ia->getActNode()->getVolume();

    if(bv.isValid() && ! bv.intersect(ia->getLine()))
    {
        return Action::Skip;  //bv missed -> can not hit children
    }

    ia->addNode(this->getSubTreeRoot());

    return ActionBase::Continue;
}


/*-------------------------------------------------------------------------*/
/*                               loading                                   */

/*-------------------------------------------------------------------------*/
/*                               Init                                      */

void VisitSubTree::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        RenderAction::registerEnterDefault(
            VisitSubTree::getClassType(),
            reinterpret_cast<Action::Callback>(&VisitSubTree::renderEnter));

        RenderAction::registerLeaveDefault(
            VisitSubTree::getClassType(),
            reinterpret_cast<Action::Callback>(&VisitSubTree::renderLeave));

        IntersectAction::registerEnterDefault(
            getClassType(),
            reinterpret_cast<Action::Callback>(&VisitSubTree::intersect));
    }
}

