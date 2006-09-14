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

#include <sstream>
#include <fstream>

#include <OSGConfig.h>

#include <OSGAction.h>
#include <OSGCamera.h>
#include <OSGRenderAction.h>
#include <OSGSceneFileHandler.h>
#include <OSGVolumeDraw.h>

#include "OSGVisitSubTree.h"

OSG_USING_NAMESPACE

/*! \class OSG::VisitSubTree

*/

/*-------------------------------------------------------------------------*/
/*                               Sync                                      */

void VisitSubTree::changed(ConstFieldMaskArg whichField, UInt32 origin)
{
#if 0
    if(whichField & (UrlFieldMask))
    {
        if(getAbsoluteUrl().empty())
        {
            PathHandler *ph = SceneFileHandler::the()->getPathHandler();

            if(ph != NULL) 
            {
                setAbsoluteUrl(ph->findFile(getUrl().c_str()));
            }

            if(getAbsoluteUrl().empty())
            {
                setAbsoluteUrl(getUrl());
            }

            setState(NOT_LOADED);
        }
    }
    if(whichField & (StateFieldMask |
                     UrlFieldMask   |
                     VolumeFieldMask))
    {
        for(UInt32 i = 0; i < _mfParents.size(); i++)
        {
            _mfParents[i]->invalidateVolume();
        }
    }
#endif

    Inherited::changed(whichField, origin);
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
    if(getSubTreeRoot() != NullFC)
    {
        getSubTreeRoot()->updateVolume();

        volume.extendBy(getSubTreeRoot()->getVolume());
    }
}

/*-------------------------------------------------------------------------*/
/*                                Draw                                     */

/*!
  Draw loaded geometry. If nothing was loaded until now, start
  loading. If loading is not finished, draw the children of 
  thid group.
 */

ActionBase::ResultE VisitSubTree::render(Action *action)
{
    DrawActionBase *da = dynamic_cast<DrawActionBase *>(action);

    da->useNodeList();
    
    if(da->isVisible(getCPtr(getSubTreeRoot())))
        da->addNode(getSubTreeRoot());

    return Action::Continue;
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
            getClassType(),
            reinterpret_cast<Action::Callback>(&VisitSubTree::render));
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
    static Char8 cvsid_cpp[] = "@(#)$Id$";
    static Char8 cvsid_hpp[] = OSGVISITSUBTREE_HEADER_CVSID;
    static Char8 cvsid_inl[] = OSGVISITSUBTREE_INLINE_CVSID;
}

    

