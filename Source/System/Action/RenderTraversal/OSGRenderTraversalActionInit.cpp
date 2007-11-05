/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2000,2001,2002 by the OpenSG Forum                *
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
#include <boost/bind.hpp>

#include "OSGConfig.h"

#include "OSGRenderTraversalAction.h"

#include "OSGMaterialDrawable.h"

#include "OSGGeometry.h"
#include "OSGGroup.h"
#include "OSGBillboard.h"
#include "OSGComponentTransform.h"
#include "OSGDistanceLOD.h"
#include "OSGMaterialGroup.h"
#include "OSGChunkOverrideGroup.h"
#include "OSGSwitch.h"
#include "OSGTransform.h"
#include "OSGDirectionalLight.h"
#include "OSGPointLight.h"
#include "OSGSpotLight.h"
#include "OSGLightChunk.h"
#include "OSGStage.h"
#include "OSGSimpleStage.h"
#include "OSGHDRStage.h"
#include "OSGAlgorithmStage.h"
#include "OSGRenderPartition.h"
#include "OSGFrameBufferObject.h"
#include "OSGVisitSubTree.h"
#include "OSGFrameBufferAttachment.h"
#include "OSGParticles.h"
#include "OSGMultiCore.h"
#include "OSGCubeMapGenerator.h"
#include "OSGQuadTreeTerrain.h"
#include "OSGTiledQuadTreeTerrain.h"

#include "OSGTypedGeoIntegralProperty.h"

#include "OSGLightEngine.h"


/*
#include "OSGSlices.h"
#include "OSGParticles.h"
 */

//#define OSG_DUMP_TRAVERSAL

OSG_BEGIN_NAMESPACE


Action::ResultE MaterialDrawableRenderLeave(const NodeCorePtr &pCore,
                                                  Action      *action)
{
    RenderTraversalAction *a = dynamic_cast<RenderTraversalAction *>(action);
    
    MaterialDrawablePtr pMDraw = dynamic_cast<MaterialDrawablePtr>(pCore);

    Material::DrawFunctor func;

    func = boost::bind(&MaterialDrawable::drawPrimitives, getCPtr(pMDraw), _1);

    Material *m = a->getMaterial();

    if(m == NULL)
    {
        if(pMDraw->getMaterial() != NullFC)
        {
            m = getCPtr(pMDraw->getMaterial());
        }
        else
        {
            m = getCPtr(getDefaultMaterial());
            
            FNOTICE(("MaterialDrawable::render: no Material!?!\n"));
        }
    }

    Action::ResultE rc = m->renderLeave(pCore, action);

    if(rc == Action::Skip)
        rc = Action::Continue;

    return rc;
}

/*-------------------------------------------------------------------------*/
/*                                   init                                  */

bool RenderTraversalActionInitialize(void)
{
    return true;
}

struct RenderTraversalActionInit
{
    RenderTraversalActionInit(void) 
    { 
        addPostFactoryInitFunction(RenderTraversalActionInitialize); 
    }
};

static RenderTraversalActionInit initDummy;

OSG_END_NAMESPACE





/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

/*-------------------------------------------------------------------------*/
/*                             Assignment                                  */

/*-------------------------------------------------------------------------*/
/*                             Comparison                                  */

/*-------------------------------------------------------------------------*/
/*                              cvs id's                                   */
