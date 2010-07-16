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

#include "OSGConfig.h"

#include "OSGRenderActionBase.h"
//#include "OSGRenderTraversalAction.h"

#include "OSGStatCollector.h"
#include "OSGDrawable.h"
#include "OSGVolumeDraw.h"
#include "OSGTraversalValidator.h"
#include "OSGWindow.h"

OSG_BEGIN_NAMESPACE

StatElemDesc<StatTimeElem>
RenderActionBase::statTravTime       ("RT-TravTime",
                                      "time for traversal"       );
# if defined(__APPLE__)
template class DataSlotMixin< MixinHead < RenderDataSlotDesc > >;
#endif

/*
StatElemDesc<StatIntElem>
   RenderTraversalActionBase::statCullTestedNodes("rtCullTestedNodes",
                                                  "nodes tested"             );

StatElemDesc<StatIntElem>
   RenderTraversalActionBase::statCulledNodes    ("rtCulledNodes",
                                                  "nodes culled from frustum");
 */

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

RenderActionBase::RenderActionBase(void) :
     Inherited                (      ),
    _pCamera                  (NULL  ),
    _pBackground              (NULL  ),
    _pWindow                  (NULL  ),
    _pViewport                (NULL  ),
    _pGlobalOverride          (NULL  ),
    _pStatistics              (NULL  ),
    _pTravValidator           (NULL  ),

    _bUseGLFinish             (false ),

    _bFrustumCulling          (true  ),
    _bVolumeDrawing           (false ),
    _bZWriteTrans             (false ),
    _bAutoFrustum             (true  ),
    _bCorrectTwoSidedLighting (false ),
    _oFrustum                 (      ),
    _uiFrameTravCount         (0     ),
    _iDrawerId                (-1    ),
    _iDrawableId              (-1    ),
    _oCurrentRenderProp       (0x0000),
    _bDrawPartPar             (false )
{
    _pTravValidator = new TraversalValidator();
}

RenderActionBase::RenderActionBase(const RenderActionBase &source) :

     Inherited               (source                          ),
    _pCamera                 (source._pCamera                 ),
    _pBackground             (source._pBackground             ),
    _pWindow                 (source._pWindow                 ),
    _pViewport               (source._pViewport               ),
    _pGlobalOverride         (source._pGlobalOverride         ),
    _pStatistics             (NULL                            ),
    _pTravValidator          (NULL                            ),

    _bUseGLFinish            (source._bUseGLFinish            ),

    _bFrustumCulling         (source._bFrustumCulling         ),
    _bVolumeDrawing          (source._bVolumeDrawing          ),
    _bZWriteTrans            (source._bZWriteTrans            ),
    _bAutoFrustum            (source._bAutoFrustum            ),
    _bCorrectTwoSidedLighting(source._bCorrectTwoSidedLighting),
    _oFrustum                (source._oFrustum                ),
    _uiFrameTravCount        (source._uiFrameTravCount        ),
    _iDrawerId               (source._iDrawerId               ),
    _iDrawableId             (source._iDrawableId             ),
    _oCurrentRenderProp      (0x0000                          ),
    _bDrawPartPar            (false                           )
{
    OSG::setRefd(_pStatistics, source._pStatistics);

    _pTravValidator = new TraversalValidator();
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

RenderActionBase::~RenderActionBase(void)
{
    OSG::subRef(_pStatistics);

    delete _pTravValidator;
}

ActionBase::ResultE RenderActionBase::start(void)
{
    if(_bFrustumCulling   == true &&
       _bAutoFrustum      == true &&
        getCamera      () != NULL &&
        getViewport    () != NULL)
    {
        getCamera()->getFrustum(_oFrustum, *getViewport());
    }

    if(_pStatistics != NULL)
    {
        _pStatistics->reset();


        _pStatistics->getElem(statTravTime       )->start();
//    getStatistics()->getElem(statCullTestedNodes)->reset();
//    getStatistics()->getElem(statCulledNodes    )->reset();
    //getStatistics()->getElem(RenderAction::statNTextures)->reset();
    //getStatistics()->getElem(RenderAction::statNTexBytes)->reset();

    // this really doesn't belong here, but don't know a better place to put it
        if(_pStatistics->getElem(Drawable::statNTriangles,false) != NULL)
        {
            _pStatistics->getElem(Drawable::statNTriangles )->set(0);
            _pStatistics->getElem(Drawable::statNLines     )->set(0);
            _pStatistics->getElem(Drawable::statNPoints    )->set(0);
            _pStatistics->getElem(Drawable::statNVertices  )->set(0);
            _pStatistics->getElem(Drawable::statNPrimitives)->set(0);
        }
    }

    _pTravValidator->incEventCounter();

//    _iDrawerId   = (_pWindow   != NULL) ? _pWindow  ->getDrawerId  () : 0;
//    _iDrawableId = (_pViewport != NULL) ? _pViewport->getDrawableId() : 0;

    return Action::Continue;
}

ActionBase::ResultE RenderActionBase::stop(ActionBase::ResultE res)
{
    if(_pStatistics != NULL)
    {
        _pStatistics->getElem(statTravTime)->stop();
    }

    ++_uiFrameTravCount;

    return res;
}

void RenderActionBase::frameInit(void)
{
    _uiFrameTravCount = 0;
}

void RenderActionBase::setViewport(Viewport *pViewport)
{
    _pViewport = pViewport;
}

void RenderActionBase::setCamera(Camera *pCamera)
{
    _pCamera = pCamera;
}

void RenderActionBase::setBackground(Background *pBackground)
{
    _pBackground = pBackground;
}

void RenderActionBase::setWindow(Window *pWindow)
{
    _pWindow = pWindow;
}

void RenderActionBase::setStatCollector(StatCollector *pStatistics)
{
    OSG::setRefd(_pStatistics, pStatistics);
}

void RenderActionBase::setGlobalOverride(Material *pMat)
{
    _pGlobalOverride = pMat;
}


// do frustum culling at all?
// default true

void RenderActionBase::setFrustumCulling(bool val)
{
    _bFrustumCulling = val;
}

void RenderActionBase::setCorrectTwoSidedLighting(bool val)
{
    _bCorrectTwoSidedLighting = val;
}

// draw the tested volumes
// default false

void RenderActionBase::setVolumeDrawing(bool val)
{
    _bVolumeDrawing = val;
}

void RenderActionBase::setZWriteTrans(bool val)
{
    _bZWriteTrans = val;
}

// automatically calc the frustum at the beginning of the traversal
// default true

void RenderActionBase::setAutoFrustum(bool val)
{
    _bAutoFrustum = val;
}

// explicitly set the frustum

void RenderActionBase::setFrustum(FrustumVolume &oFrustum)
{
    _oFrustum = oFrustum;
}


OSG_END_NAMESPACE
