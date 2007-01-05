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

#ifdef OSG_CLEANED_RENDERACTION

#include "OSGRenderTreeNode.h"
#include "OSGBaseFunctions.h"

OSG_USING_NAMESPACE

/*! \class OSG::RenderTreeNode
    \ingroup GrpSystemRenderingBackend
 */

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

RenderTreeNode::RenderTreeNode(void) :
    _pFirstChild   (NULL ),
    _pLastChild    (NULL ),
    _pBrother      (NULL ),
    _pState        (NULL ),
    _pStateOverride(NULL),
    _functor       (     ),
    _hasFunctor    (false),
    _oMatrixStore  (     ),
    _rScalarVal    (0.f  ),
    _isRendered    (false),
    _resultNum     (0),
    _lightsState   (0    ),
    _node          (NULL )
{
    _oMatrixStore.first = 0;
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

RenderTreeNode::~RenderTreeNode(void)
{
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
    static Char8 cvsid_hpp[] = OSGRENDERTREENODE_HEADER_CVSID;
    static Char8 cvsid_inl[] = OSGRENDERTREENODE_INLINE_CVSID;
}

#endif
