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
#include "OSGRenderAction.h"

#include "OSGScreenLOD.h"
#include "OSGDrawableStatsAttachment.h"

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGScreenLODBase.cpp file.
// To modify it, please change the .fcd file (OSGScreenLOD.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ScreenLOD::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        typedef ActionBase::ResultE (ScreenLOD::*Callback)(Action *);

        Callback enter = &ScreenLOD::renderEnter;

        RenderAction::registerEnterDefault(
            getClassType(),
            reinterpret_cast<Action::Callback>(enter));
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

ActionBase::ResultE ScreenLOD::renderEnter(Action *action)
{
    RenderAction  *ra        = dynamic_cast<RenderAction*>(action);

    Int32           numLevels = action->getNNodes();
    Int32           index     = 0;
    
    Int32           numCovOverrides = getMFCoverageOverride()->size();
    bool            use_overrides(numCovOverrides > 0);

    if(numLevels > 1)
    {
        if((ra->getScreenLODCoverageThreshold() > 0.f) || use_overrides)
        {
            // -- Compute bounding volume screen coverage of current node -- //
            Matrix worldToScreen;
#if 1 
            Camera* cam = ra->getCamera();
            Viewport* vp = ra->getViewport();
            cam->getWorldToScreen(worldToScreen, *vp);
#else
            worldToScreen = da->getDrawEnv()->getWorldToScreen();
#endif
            
            const BoxVolume &volume = ra->getActNode()->getVolume();
            Pnt3f min,max;
            volume.getBounds(min, max);
            Pnt3f p[8];
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
                ra->topMatrix().mult    (p[i], p[i]);
                worldToScreen  .multFull(p[i], p[i]);
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
            
            // cbb (coverage bounding box) is the percent of the screen real estate this would cover
            Real32 cbb = (max[0] - min[0]) * (max[1] - min[1]) / 4.f;

            // Default degredation based computation
            if (!use_overrides)
            {
               //Get max LOD number of triangles
               Node *pmax = action->getNode(0);
               DrawableStatsAttachment *st_max = 
                   DrawableStatsAttachment::get(pmax);

               if(st_max == NULL)
               {
                  DrawableStatsAttachment::addTo(pmax);
                  st_max = DrawableStatsAttachment::get(pmax);
               }
               st_max->validate();
   
               //Get min LOD number of triangles
               Node *pmin = action->getNode(numLevels-1);
               DrawableStatsAttachment *st_min = 
                   DrawableStatsAttachment::get(pmin);
               if(st_min == NULL)
               {
                  DrawableStatsAttachment::addTo(pmin);
                  st_min = DrawableStatsAttachment::get(pmin);
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
            // Use override values
            else
            {
                unsigned idx_limit = osgMin(numLevels, numCovOverrides);

                if(cbb > (*(getMFCoverageOverride()))[0])      // If greater then first, use first index
                {
                    index = 0;
                } 
                else if(cbb <= (*(getMFCoverageOverride()))[numCovOverrides-1])    // If greater then max
                {
                    index = (numLevels > numCovOverrides) ? numCovOverrides : (idx_limit-1); 
                }
                else
                {
                    Int32 i = 1;

                    // While: more to check && ! (over[i-1] >= cbb > over[i])
                    while( (i < numCovOverrides) && 
                           !( (cbb <= (*(getMFCoverageOverride()))[i-1]) && 
                              (cbb >  (*(getMFCoverageOverride()))[i]  )   ) )
                    {
                        i++;
                    }
                    index = i;      // clamped below
                }                 
            }
        }
    }

    if (index >= numLevels)
    {
        index=numLevels-1;
    }

    //if (!use_overrides)
    //{
       // See if we have a minimum LOD that we want to maintain
       Int32 lowestLOD = ra->getScreenLODNumLevels();
       if(lowestLOD != 0) // if using a minLOD
       {
         lowestLOD--; // LODS is 0 based, NumLevels is 1 based
         if(index > lowestLOD)
            index = lowestLOD;
       }
    //}

    ra->useNodeList();
    if(ra->isVisible(action->getNode(index)))
    {
        ra->addNode(action->getNode(index));
    }

    return ActionBase::Continue;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ScreenLOD::ScreenLOD(void) :
    Inherited()
{
}

ScreenLOD::ScreenLOD(const ScreenLOD &source) :
    Inherited(source)
{
}

ScreenLOD::~ScreenLOD(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ScreenLOD::changed(ConstFieldMaskArg whichField, 
                        UInt32            origin,
                        BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void ScreenLOD::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump ScreenLOD NI" << std::endl;
}
