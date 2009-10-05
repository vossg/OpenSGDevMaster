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

#include "OSGCSMViewport.h"
#include "OSGStereoBufferViewport.h"
#include "OSGShearedStereoCameraDecorator.h"
#include "OSGProjectionCameraDecorator.h"
#include "OSGCSMPerspectiveCamera.h"
#include "OSGColorBufferViewport.h"
#include "OSGPassiveViewport.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGCSMViewportBase.cpp file.
// To modify it, please change the .fcd file (OSGCSMViewport.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void CSMViewport::initMethod(InitPhase ePhase)
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

CSMViewport::CSMViewport(void) :
    Inherited()
{
}

CSMViewport::CSMViewport(const CSMViewport &source) :
    Inherited(source)
{
}

CSMViewport::~CSMViewport(void)
{
}

void CSMViewport::resolveLinks(void)
{
    Inherited::resolveLinks();

    ViewportStoreIt      vIt  = _vViewports.begin();
    ViewportStoreConstIt vEnd = _vViewports.end  ();

    for(; vIt != vEnd; ++vIt)
    {
        (*vIt) = NULL;
    }

    _vViewports.clear();
}

/*----------------------------- class specific ----------------------------*/

void CSMViewport::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void CSMViewport::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump CSMViewport NI" << std::endl;
}

bool CSMViewport::init(void)
{
    bool returnValue = true;

    bool bQuadBuff   = _sfStereoMode.getValue() == "quadBuffer";
    bool bSplitH     = _sfStereoMode.getValue() == "splitHorizontal";
    bool bSplitV     = _sfStereoMode.getValue() == "splitVertical";
    bool bSLeft      = _sfStereoMode.getValue() == "stereoLeft";
    bool bSRight     = _sfStereoMode.getValue() == "stereoRight";
    bool bAmberBlue  = _sfStereoMode.getValue() == "amberBlue";

    bool bStereo   = (bQuadBuff   || 
                      bSplitH     || 
                      bSplitV     || 
                      bAmberBlue  ||
                      bSLeft      || 
                      bSRight      );

    bool bFallback = false;

    if(bStereo == true && _sfPassive.getValue() == true)
    {
        FWARNING(("CSMViewport: passive set with stereo config, ignoring\n"));
    }

    if(bQuadBuff == true)
    {
        StereoBufferViewportUnrecPtr pPortLeft  = 
            StereoBufferViewport::create();

        StereoBufferViewportUnrecPtr pPortRight = 
            StereoBufferViewport::create();

        // Left
        pPortLeft->setLeft  (_sfLeftBottom.getValue()[0]);
        pPortLeft->setBottom(_sfLeftBottom.getValue()[1]);
        
        pPortLeft->setRight (_sfRightTop  .getValue()[0]);
        pPortLeft->setTop   (_sfRightTop  .getValue()[1]);

        pPortLeft->setLeftBuffer (true );
        pPortLeft->setRightBuffer(false);

        pPortRight->setLeft  (_sfLeftBottom.getValue()[0]);
        pPortRight->setBottom(_sfLeftBottom.getValue()[1]);
        
        pPortRight->setRight (_sfRightTop  .getValue()[0]);
        pPortRight->setTop   (_sfRightTop  .getValue()[1]);

        pPortRight->setLeftBuffer (false);
        pPortRight->setRightBuffer(true );

        _vViewports.push_back(pPortLeft );
        _vViewports.push_back(pPortRight);
    }
    else if(bAmberBlue == true)
    {
        ColorBufferViewportUnrecPtr pPortLeft  = 
            ColorBufferViewport::create();

        ColorBufferViewportUnrecPtr pPortRight = 
            ColorBufferViewport::create();

        // Left
        pPortLeft->setLeft  (_sfLeftBottom.getValue()[0]);
        pPortLeft->setBottom(_sfLeftBottom.getValue()[1]);
        
        pPortLeft->setRight (_sfRightTop  .getValue()[0]);
        pPortLeft->setTop   (_sfRightTop  .getValue()[1]);

        pPortLeft->setRed  (GL_TRUE );
        pPortLeft->setGreen(GL_TRUE );
        pPortLeft->setBlue (GL_FALSE);
        pPortLeft->setAlpha(GL_TRUE );

        pPortRight->setLeft  (_sfLeftBottom.getValue()[0]);
        pPortRight->setBottom(_sfLeftBottom.getValue()[1]);
        
        pPortRight->setRight (_sfRightTop  .getValue()[0]);
        pPortRight->setTop   (_sfRightTop  .getValue()[1]);

        pPortRight->setRed  (GL_FALSE);
        pPortRight->setGreen(GL_FALSE);
        pPortRight->setBlue (GL_TRUE );
        pPortRight->setAlpha(GL_FALSE);

        _vViewports.push_back(pPortLeft );
        _vViewports.push_back(pPortRight);
    }
    else if(bSplitH == true)
    {
        ViewportUnrecPtr pPortLeft  = Viewport::create();
        ViewportUnrecPtr pPortRight = Viewport::create();

        // Left
        Real32 rCenter = _sfLeftBottom.getValue()[0] +
            (_sfRightTop  .getValue()[0] - _sfLeftBottom.getValue()[0]) * 0.5;

        pPortLeft->setLeft  (_sfLeftBottom.getValue()[0]);
        pPortLeft->setBottom(_sfLeftBottom.getValue()[1]);
        
        pPortLeft->setRight ( rCenter                   );
        pPortLeft->setTop   (_sfRightTop  .getValue()[1]);

        // Right
        pPortRight->setLeft  ( rCenter                   );
        pPortRight->setBottom(_sfLeftBottom.getValue()[1]);
        
        pPortRight->setRight (_sfRightTop  .getValue()[0]);
        pPortRight->setTop   (_sfRightTop  .getValue()[1]);

        _vViewports.push_back(pPortLeft );
        _vViewports.push_back(pPortRight);
    }
    else if(bSplitV == true)
    {
        ViewportUnrecPtr pPortLeft  = Viewport::create();
        ViewportUnrecPtr pPortRight = Viewport::create();

        // Left
        Real32 rCenter = _sfLeftBottom.getValue()[1] +
            (_sfRightTop  .getValue()[1] - _sfLeftBottom.getValue()[1]) * 0.5;

        pPortLeft->setLeft  (_sfLeftBottom.getValue()[0]);
        pPortLeft->setBottom(_sfLeftBottom.getValue()[1]);
        
        pPortLeft->setRight (_sfRightTop  .getValue()[0]);
        pPortLeft->setTop   ( rCenter                   );

        // Right
        pPortRight->setLeft  (_sfLeftBottom.getValue()[0]);
        pPortRight->setBottom( rCenter                   );
        
        pPortRight->setRight (_sfRightTop  .getValue()[0]);
        pPortRight->setTop   (_sfRightTop  .getValue()[1]);

        _vViewports.push_back(pPortLeft );
        _vViewports.push_back(pPortRight);
    }
    else
    {
        if(_sfPassive.getValue() == true)
        {
            ViewportUnrecPtr pPort  = PassiveViewport::create();

            _vViewports.push_back(pPort);
        }
        else
        {
            ViewportUnrecPtr pPort  = Viewport::create();

            // Left
            pPort->setLeft  (_sfLeftBottom.getValue()[0]);
            pPort->setBottom(_sfLeftBottom.getValue()[1]);
            
            pPort->setRight (_sfRightTop  .getValue()[0]);
            pPort->setTop   (_sfRightTop  .getValue()[1]);

            _vViewports.push_back(pPort );
        }
    }
    
    CSMPerspectiveCamera *pCSMCam = 
        dynamic_cast<CSMPerspectiveCamera *>(_sfCamera.getValue());

    ProjectionCameraDecorator *pProjCam = 
        dynamic_cast<ProjectionCameraDecorator *>(_sfCamera.getValue());

    if(pCSMCam == NULL)
    {
        if(pProjCam != NULL)
        {
            pCSMCam = dynamic_cast<CSMPerspectiveCamera *>(
                    pProjCam->getDecoratee());
        }
    }

    if(pCSMCam == NULL)
        bFallback = true;

    if((bQuadBuff || bSplitH || bSplitV || bAmberBlue) && (bFallback == false))
    {
        // Left
        StereoCameraDecoratorUnrecPtr pDecoLeft(NULL);

        if(pProjCam != NULL)
        {
            if(pCSMCam->getHeadBeacon() != NULL)
            {
                pProjCam->setUser(pCSMCam->getHeadBeacon());
            }
            else
            {
                pProjCam->setUser(pCSMCam->getBeacon());
            }

            pDecoLeft = pProjCam;
        }
        else
        {
            ShearedStereoCameraDecoratorUnrecPtr pSheared = 
                ShearedStereoCameraDecorator::create();


            pSheared->setZeroParallaxDistance(pCSMCam->getZeroParallax ());
            pSheared->setDecoratee           (pCSMCam                    );  

            pDecoLeft = pSheared;

            addConnection(pCSMCam,    "zeroParallax",
                          pDecoLeft,  "zeroParallaxDistance");
        }

        pDecoLeft->setEyeSeparation       (pCSMCam->getEyeSeparation());
        pDecoLeft->setLeftEye             (true                       );  

        _vViewports[0]->setCamera(pDecoLeft);

        // Right
        StereoCameraDecoratorUnrecPtr pDecoRight(NULL);

        if(pProjCam != NULL)
        {
            ProjectionCameraDecoratorUnrecPtr pProject = 
                ProjectionCameraDecorator::create();

            pProject->setUser     (pProjCam->getUser());
            pProject->setDecoratee(pCSMCam            );

            *(pProject->editMFSurface()) = *(pProjCam->getMFSurface());

            pDecoRight = pProject;
        }
        else
        {
            ShearedStereoCameraDecoratorUnrecPtr pSheared = 
                ShearedStereoCameraDecorator::create();

            pSheared->setZeroParallaxDistance(pCSMCam->getZeroParallax ());
            pSheared->setDecoratee           (pCSMCam                    );  

            pDecoRight = pSheared;

            addConnection(pCSMCam,    "zeroParallax",
                          pDecoRight, "zeroParallaxDistance");
        }

        pDecoRight->setEyeSeparation       (pCSMCam->getEyeSeparation());
        pDecoRight->setLeftEye             (false                      );  

        _vViewports[1]->setCamera(pDecoRight);

        addConnection(pCSMCam,    "eyeSeparation",
                      pDecoRight, "eyeSeparation");


        addConnection(pCSMCam,    "eyeSeparation",
                      pDecoLeft,  "eyeSeparation");
    }
    else if((bSLeft || bSRight) && (bFallback == false))
    {
        StereoCameraDecoratorUnrecPtr pDeco(NULL);

        if(pProjCam != NULL)
        {
            if(pCSMCam->getHeadBeacon() != NULL)
            {
                pProjCam->setUser(pCSMCam->getHeadBeacon());
            }
            else
            {
                pProjCam->setUser(pCSMCam->getBeacon());
            }

            pDeco = pProjCam;
        }
        else
        {
            ShearedStereoCameraDecoratorUnrecPtr pSheared = 
                ShearedStereoCameraDecorator::create();

            pSheared->setZeroParallaxDistance(pCSMCam->getZeroParallax ());
            pSheared->setDecoratee           (pCSMCam                    );  

            pDeco = pSheared;

            addConnection(pCSMCam, "zeroParallax",
                          pDeco,   "zeroParallaxDistance");
        }

        pDeco->setEyeSeparation       (pCSMCam->getEyeSeparation());
        pDeco->setLeftEye             (bSLeft                     );  

        _vViewports[0]->setCamera(pDeco);

    
        addConnection(pCSMCam, "eyeSeparation",
                      pDeco,   "eyeSeparation");
    }
    else
    {
        _vViewports[0]->setCamera(_sfCamera.getValue());

        if(bFallback == false)
        {
            if(pProjCam != NULL)
            {
                if(pCSMCam->getHeadBeacon() != NULL)
                {
                    pProjCam->setUser(pCSMCam->getHeadBeacon());
                }
                else
                {
                    pProjCam->setUser(pCSMCam->getBeacon());
                }
            }
        }
    }

    ViewportStoreConstIt vIt  = _vViewports.begin();
    ViewportStoreConstIt vEnd = _vViewports.end  ();

    for(; vIt != vEnd; ++vIt)
    {
        (*vIt)->setRoot         (_sfRoot         .getValue());
        (*vIt)->setBackground   (_sfBackground   .getValue());
        (*vIt)->setRenderOptions(_sfRenderOptions.getValue());

        MFUnrecForegroundPtr::const_iterator fIt  = getMFForegrounds()->begin();
        MFUnrecForegroundPtr::const_iterator fEnd = getMFForegrounds()->end  ();

        while(fIt != fEnd)
        {
            (*vIt)->addForeground(*fIt);
            
            ++fIt;
        }
    }

    return returnValue;
}

CSMViewport::ViewportStoreConstIt CSMViewport::beginViewports(void) const
{
    return _vViewports.begin();
}

CSMViewport::ViewportStoreConstIt CSMViewport::endViewports(void) const
{
    return _vViewports.end();
}

bool CSMViewport::needsStereoVisual(void)
{
    return _sfStereoMode.getValue() == "quadBuffer";
}

OSG_END_NAMESPACE
