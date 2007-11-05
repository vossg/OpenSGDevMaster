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
    RenderActionT  *ra        = dynamic_cast<RenderActionT  *>(action);

    UInt32          numLevels = action->getNNodes();
    UInt32          numRanges = getMFRange()->size();

    UInt32          limit     = osgMin(numLevels, numRanges); 
    
    Int32           index     = -1;

    Pnt3f            eyepos(0.f, 0.f, 0.f);
    Pnt3f            objpos;

    ra->getActivePartition()->getCameraToWorld().mult(eyepos);

    ra->topMatrix().mult(getCenter(), objpos);
        
    Real32 dist = osgSqrt((eyepos[0] - objpos[0])*(eyepos[0] - objpos[0]) +
                          (eyepos[1] - objpos[1])*(eyepos[1] - objpos[1]) +
                          (eyepos[2] - objpos[2])*(eyepos[2] - objpos[2]));
    
    ra->useNodeList();
    
    if(numRanges != 0 && numLevels!=0 )
    {
        if(dist < (*(getMFRange()))[0])
        {
            index = 0;
        } 
        else if(dist >= (*(getMFRange()))[numRanges-1])
        {
            index = (numLevels > numRanges) ? numRanges : (limit-1); 
        }
        else
        {
            UInt32 i = 1;

            while( (i < numRanges) && 
                  !( ((*(getMFRange()))[i-1] <= dist) && 
                     (dist < (*(getMFRange()))[i]   )   ) )
            {
                i++;
            }
            
            index = osgMin(i, limit-1);
        } 
        
        if(ra->isVisible(getCPtr(action->getNode(index))))
        {
            ra->addNode(action->getNode(index));
        }
    }

    return ActionBase::Continue;
}

OSG_END_NAMESPACE


