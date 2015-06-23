/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright(C) 2000-2002 by the OpenSG Forum                   *
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

#include "OSGGL.h"

#include "OSGField.h"
#include "OSGFieldContainer.h"
#include "OSGAction.h"

#include "OSGRenderActionBase.h"

#include "OSGDrawEnv.h"

#include "OSGBackground.h"
#include "OSGViewarea.h"
#include "OSGWindow.h"
#include "OSGCamera.h"
#include "OSGForeground.h"
#include "OSGFrameBufferObject.h"

#include "OSGTraversalValidator.h"

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGViewareaBase.cpp file.
// To modify it, please change the .fcd file (OSGViewarea.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

void Viewarea::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);
}

void Viewarea::onCreate      (const Viewarea *source)
{
    Inherited::onCreate(source);
}

void Viewarea::onCreateAspect(const Viewarea *createAspect,
                              const Viewarea *source)
{
    Inherited::onCreateAspect(createAspect, source);

    // Don't add the prototype instances to the list
    if(GlobalSystemState != Running)
        return;

    _pTravValidator = new TraversalValidator;
}

void Viewarea::onDestroy(UInt32 uiContainerId)
{
    Inherited::onDestroy(uiContainerId);
}

void Viewarea::onDestroyAspect(UInt32    uiContainerId,
                               UInt32    uiAspect     )
{
    delete _pTravValidator;

    _pTravValidator  = NULL;

    Inherited::onDestroyAspect(uiContainerId, uiAspect);
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*------------- constructors & destructors --------------------------------*/

Viewarea::Viewarea(void) :
     Inherited      (    ),
    _pTravValidator (NULL)

{
}

Viewarea::Viewarea(const Viewarea &source) :
     Inherited      (source),
    _pTravValidator (NULL  )

{
}

Viewarea::~Viewarea(void)
{
}

void Viewarea::changed(ConstFieldMaskArg whichField, 
                       UInt32            origin,
                       BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void Viewarea::computePixelSizes(Window *pWin,

                                 UInt32 &uiPixelWidth,
                                 UInt32 &uiPixelHeight)
{
    Int32 iPixelLeft;
    Int32 iPixelRight;
    Int32 iPixelTop;
    Int32 iPixelBottom;

    if(pWin == NULL)
    {
        uiPixelWidth  = this->getRight() - this->getLeft  () + 1;
        uiPixelHeight = this->getTop  () - this->getBottom() + 1;

        return;
    }

    if(this->getLeft() > 1.f)
        iPixelLeft = Int32(this->getLeft());
    else
        iPixelLeft = Int32(pWin->getWidth() * this->getLeft());

    if(this->getRight() > 1.f)
        iPixelRight = Int32(this->getRight());
    else
        iPixelRight = Int32(pWin->getWidth() * this->getRight()) - 1;


    if(this->getBottom() > 1.f)
        iPixelBottom = Int32(this->getBottom());
    else
        iPixelBottom = Int32(pWin->getHeight() * this->getBottom());

    if(this->getTop() > 1.f)
        iPixelTop = Int32(this->getTop());
    else
        iPixelTop = Int32(pWin->getHeight() * this->getTop()) - 1;

    uiPixelWidth  = iPixelRight - iPixelLeft   + 1;
    uiPixelHeight = iPixelTop   - iPixelBottom + 1;
}


/*---------------------------- properties ---------------------------------*/

void Viewarea::render(RenderActionBase *action)
{
#if 0
    _pTravValidator->incEventCounter();
 
    if(getTravMask() == 0x0000 || getEnabled() == false)
        return;

    if(getCamera() == NULL)
    {
        SWARNING << "Viewarea::render: no Camera, can not render!" << std::endl;
        return;
    }
    if(getBackground() == NULL)
    {
        SWARNING << "Viewarea::render: no Background, can not render!" << std::endl;
        return;
    }
    if(getRoot() == NULL)
    {
        SWARNING << "Viewarea::render: no root, can not render!" << std::endl;
        return;
    }

#if 0 // Have to check GV
    activate();
#endif

    action->setCamera    (getCamera    ());
    action->setBackground(getBackground());
    action->setViewarea  (this           );
    action->setTravMask  (getTravMask()  );

    action->apply(getRoot());

    Window  *pWin = action->getWindow();

    if((pWin->getDrawMode() & Window::PartitionDrawMask) ==
                                              Window::SequentialPartitionDraw)
    {
        DrawEnv  oEnv;

        oEnv.setWindow(action->getWindow());

        Matrix m, t;
        getCamera()->getProjection           (m,
                                              getPixelWidth (),
                                              getPixelHeight());
        getCamera()->getProjectionTranslation(t,
                                              getPixelWidth (),
                                              getPixelHeight());
        oEnv.setupProjection(m, t);

        getCamera()->getViewing(m,
                                getPixelWidth (),
                                getPixelHeight());
        oEnv.setupViewing(m);

        oEnv.setTileFullSize(getCamera()->tileGetFullSize());
        oEnv.setTileRegion  (getCamera()->tileGetRegion  ());

        oEnv.setViewareaDimension(getPixelLeft  (),
                                  getPixelBottom(),
                                  getPixelRight (),
                                  getPixelTop   (),
                                  isFullWindow  ());

        oEnv.setDrawerId  (action->getDrawerId  ());
        oEnv.setDrawableId(action->getDrawableId());

        for(UInt16 i = 0; i < getMFForegrounds()->size(); i++)
        {
            Foreground        *pForeground = getForegrounds(i);
            FrameBufferObject *pTarget     = this->getTarget();

            if(pTarget != NULL)
            {
                pTarget->activate(&oEnv);
            }

            pForeground->draw(&oEnv);

            if(pTarget != NULL)
            {
                pTarget->deactivate(&oEnv);
            }
        }
    }
    else
    {
        if(_pForegroundTask == NULL)
        {
            _pForegroundTask = 
                new ViewareaDrawTask(this, ViewareaDrawTask::Foregrounds);
        }

        pWin->queueTaskFromDrawer(_pForegroundTask);
    }

#if 0 // Have to check GV
    deactivate();
#endif
#endif
}

bool Viewarea::isPassive(void)
{
    return false;
}

FrameBufferObject *Viewarea::getTarget(void)
{
    return NULL;
}

/*------------------------------- dump ----------------------------------*/

void Viewarea::dump(     UInt32    OSG_CHECK_ARG(uiIndent), 
                    const BitVector OSG_CHECK_ARG(bvFlags)) const
{
    SLOG << "Dump Viewarea NI" << std::endl;

    fprintf(stderr, "%p\n", 
            static_cast<const void *>(this));
}


