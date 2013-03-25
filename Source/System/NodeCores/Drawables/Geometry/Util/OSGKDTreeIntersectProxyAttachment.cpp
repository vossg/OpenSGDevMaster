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
#include <boost/cast.hpp>

#include "OSGConfig.h"
#include "OSGKDTreeIntersectProxyAttachment.h"

#include "OSGIntersectAction.h"
#include "OSGIntersectKDTree.h"
#include "OSGGeometry.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGKDTreeIntersectProxyAttachmentBase.cpp file.
// To modify it, please change the .fcd file (OSGKDTreeIntersectProxyAttachment.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void KDTreeIntersectProxyAttachment::initMethod(InitPhase ePhase)
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

KDTreeIntersectProxyAttachment::KDTreeIntersectProxyAttachment(void) :
    Inherited()
{
}

KDTreeIntersectProxyAttachment::KDTreeIntersectProxyAttachment(const KDTreeIntersectProxyAttachment &source) :
    Inherited(source)
{
}

KDTreeIntersectProxyAttachment::~KDTreeIntersectProxyAttachment(void)
{
}

/*----------------------------- class specific ----------------------------*/

/* virtual */ Action::ResultE
KDTreeIntersectProxyAttachment::intersectEnter(Node *node, Action *action)
{
    Action::ResultE  res  = Inherited::intersectEnter(node, action);
    IntersectAction *iact =
        boost::polymorphic_downcast<IntersectAction *>(action);

    Real32 closestHitT = iact->didHit() ? iact->getHitT() : iact->getMaxDist();
    Vec3f  hitNormal;
    UInt32 hitTriangle;

    if(_mfTreeNodes.empty() == false)
    {
        UInt32 numTris = 0;
        bool hit = intersectIntersectKDTree(iact->getLine(),
                                            node->getVolume(),
                                            _sfGeometry.getValue(),
                                            &_mfTreeNodes,
                                            &_mfTriIndices,
                                            closestHitT,
                                            hitNormal,
                                            hitTriangle,
                                            &numTris    );

        if(hit == true)
        {
            iact->setHit(closestHitT,
                         node,
                         hitTriangle,
                         hitNormal, 0);
        }

        iact->getStatCollector()->getElem(
            IntersectAction::statNTriangles)->add(numTris);
    }
    else
    {
        // tree was empty - skip this proxy and use conventional
        // intersect
        res = Action::Continue;
    }

    return res;
}

void KDTreeIntersectProxyAttachment::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    if(whichField & GeometryFieldMask)
    {
        editMField(TreeNodesFieldMask,  _mfTreeNodes );
        editMField(TriIndicesFieldMask, _mfTriIndices);

        _mfTreeNodes .clear();
        _mfTriIndices.clear();

        buildIntersectKDTree(_sfGeometry.getValue(),
                             _sfMaxDepth.getValue(),
                             &_mfTreeNodes,
                             &_mfTriIndices        );
    }

    Inherited::changed(whichField, origin, details);
}

void KDTreeIntersectProxyAttachment::dump(      UInt32    ,
                                          const BitVector ) const
{
    SLOG << "Dump KDTreeIntersectProxyAttachment NI" << std::endl;
}

OSG_END_NAMESPACE
