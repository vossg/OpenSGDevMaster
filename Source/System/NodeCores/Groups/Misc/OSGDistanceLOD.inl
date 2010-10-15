/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                     Copyright 2000-2002 by OpenSG Forum                   *
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

OSG_BEGIN_NAMESPACE

template<class RenderActionT> inline
ActionBase::ResultE DistanceLOD::render(Action *action)
{
    action->useNodeList();

    Int32 numLevels = action->getNNodes();

    if(numLevels == 0)
        return Action::Continue;

    RenderActionT  *ra        = dynamic_cast<RenderActionT  *>(action);
    Int32           index     = -1;

    const MFReal32 *range = getMFRange();

    Int32 numRanges = range->size();

    if(numRanges == 0 || numLevels == 1)
    {
        index = 0;
    }
    else
    {
        Pnt3f eyepos;

        ra->getActivePartition()->getCameraToWorld().mult(eyepos, eyepos);

        Pnt3f objpos;

        ra->topMatrix().mult(getCenter(), objpos);

        Real32 dist = eyepos.dist(objpos);

        if(numRanges >= numLevels && numLevels > 1)
            numRanges = numLevels - 1;

        if(dist >= (*range)[numRanges - 1])
        {
            index = numRanges;
        }
        else
        {
            for(index = 0; index < numRanges; ++index)
            {
                if(dist < (*range)[index])
                    break;
            }
        }
    }

    Node *nodePtr = action->getNode(index);

    if(ra->isVisible(nodePtr))
    {
        ra->addNode(nodePtr);
    }

    return ActionBase::Continue;
}

OSG_END_NAMESPACE


