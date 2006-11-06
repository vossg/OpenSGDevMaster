/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
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

OSG_BEGIN_NAMESPACE

template<class RenderTraversalActionT> inline
ActionBase::ResultE ScreenLOD::render(Action *action)
{
    RenderTraversalActionT  *ra        = dynamic_cast<RenderTraversalActionT  *>(action);

    UInt32          numLevels = action->getNNodes();
    Int32           index     = 0;

    if(numLevels > 1)
    {
        if(ra->getScreenLODCoverageThreshold() > 0.f)
        {
            Matrixr worldToScreen;
#if 1 
            DrawActionBase  *da        = dynamic_cast<DrawActionBase  *>(action);
            Camera* cam = ra->getCamera();
            Viewport* vp = ra->getViewport();
            cam->getWorldToScreen(worldToScreen, *vp);
#else
            worldToScreen = da->getDrawEnv()->getWorldToScreen();
#endif
            
            DynamicVolume volume = ra->getActNode()->getVolume();
            Pnt3r min,max;
            volume.getBounds(min, max);
            Pnt3r p[8];
            p[0].setValues(min[0],min[1],min[2]);
            p[1].setValues(max[0],min[1],min[2]);
            p[2].setValues(min[0],max[1],min[2]);
            p[3].setValues(min[0],min[1],max[2]);
            p[4].setValues(max[0],max[1],min[2]);
            p[5].setValues(max[0],min[1],max[2]);
            p[6].setValues(min[0],max[1],max[2]);
            p[7].setValues(max[0],max[1],max[2]);
            
            for(UInt32 i = 0; i<8;i++)
            {
                ra->topMatrix().mult(p[i]);
                worldToScreen.multFullMatrixPnt(p[i]);
            }
            min=p[0];
            max=p[0];
            for(UInt32 i = 0; i<8; i++)
            {
               for(UInt32 j=0; j<2; j++)
               {
                  if(p[i][j] < min[j])
                  {
                    min[j] = p[i][j];
                  }
                  if(p[i][j] > max[j])
                  {
                    max[j] = p[i][j];
                  }
               }
            }
            max[0] = osgClamp(-1.f, max[0], 1.f);
            max[1] = osgClamp(-1.f, max[1], 1.f);
            min[0] = osgClamp(-1.f, min[0], 1.f);
            min[1] = osgClamp(-1.f, min[1], 1.f);
            
            // cbb is the percent of the screen real estate this would cover
            Real32 cbb = (max[0] - min[0]) * (max[1] - min[1]) / 4.f;

            //Get max LOD number of triangles
            NodePtr pmax = action->getNode(0);
            GeoStatsAttachmentPtr st_max = GeoStatsAttachment::get(pmax);
            if(st_max == NullFC)
            {
               GeoStatsAttachment::addTo(pmax);
               st_max = GeoStatsAttachment::get(pmax);
            }
            st_max->validate();

            //Get min LOD number of triangles
            NodePtr pmin = action->getNode(numLevels-1);
            GeoStatsAttachmentPtr st_min = GeoStatsAttachment::get(pmin);
            if(st_min == NullFC)
            {
               GeoStatsAttachment::addTo(pmin);
               st_min = GeoStatsAttachment::get(pmin);
            }
            st_min->validate();

            // Find out what the average degradation of triangles is each level
            Real32 deg_percent = 1.0 - (st_min->getTriangles() / st_max->getTriangles());
            deg_percent = deg_percent / numLevels;
            if(deg_percent >= 1.0)
            {
                cbb = ra->getScreenLODCoverageThreshold(); //just pick this lod
            }

            Real32 base_percent = ra->getScreenLODCoverageThreshold(); //Above this renders at full res!
            Real32 user_deg_factor = ra->getScreenLODDegradationFactor();
            // While the screen percentage of the object is less that the percent allowed for the current LOD
            // move down a LOD and find out the new allowed percentage
            while(cbb < base_percent)
            {
                base_percent= base_percent * deg_percent * user_deg_factor;
                index++;
                if(index >= numLevels)
                    break;
            }
        }
    }

    if (index >= numLevels)
    {
        index=numLevels-1;
    }

    // See if we have a minimum LOD that we want to maintain
    UInt32 lowestLOD = ra->getScreenLODNumLevels();
    if(lowestLOD != 0) // if using a minLOD
    {
      lowestLOD--; // LODS is 0 based, NumLevels is 1 based
      if(index > lowestLOD)
         index = lowestLOD;
    }

    ra->useNodeList();
    if(ra->isVisible(getCPtr(action->getNode(index))))
    {
        ra->addNode(action->getNode(index));
    }

    return ActionBase::Continue;
}

OSG_END_NAMESPACE

#define OSGSCREENLOD_INLINE_CVSID "@(#)$Id: FCTemplate_inl.h 106 2006-09-14 03:15:53Z dirk $"

