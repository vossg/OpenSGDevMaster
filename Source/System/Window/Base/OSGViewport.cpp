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
#include "OSGViewport.h"
#include "OSGWindow.h"
#include "OSGCamera.h"
#include "OSGForeground.h"
#include "OSGFrameBufferObject.h"

#include "OSGTraversalValidator.h"

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGViewportBase.cpp file.
// To modify it, please change the .fcd file (OSGViewport.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

void Viewport::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);
}

void Viewport::onCreate      (const Viewport *source)
{
    Inherited::onCreate(source);
}

void Viewport::onCreateAspect(const Viewport *createAspect,
                              const Viewport *source)
{
    Inherited::onCreateAspect(createAspect, source);

    // Don't add the prototype instances to the list
    if(GlobalSystemState != Running)
        return;

    _pTravValidator = new TraversalValidator;
}

void Viewport::onDestroy(UInt32 uiContainerId)
{
    Inherited::onDestroy(uiContainerId);
}

void Viewport::onDestroyAspect(UInt32    uiContainerId,
                               UInt32    uiAspect     )
{
    delete _pTravValidator;

    _pTravValidator  = NULL;
    _pForegroundTask = NULL;

    Inherited::onDestroyAspect(uiContainerId, uiAspect);
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*------------- constructors & destructors --------------------------------*/

Viewport::Viewport(void) :
     Inherited      (    ),
    _pTravValidator (NULL),
    _pForegroundTask(NULL)

{
}

Viewport::Viewport(const Viewport &source) :
     Inherited      (source),
    _pTravValidator (NULL  ),
    _pForegroundTask(NULL  )

{
}

Viewport::~Viewport(void)
{
}

void Viewport::changed(ConstFieldMaskArg whichField, 
                       UInt32            origin,
                       BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

/*---------------------------- properties ---------------------------------*/

/*! Calculate the positon of the left border of the viewport. Needs a valid
    _sfParent value.
 */

Int32 Viewport::getPixelLeft(void) const
{
    if(getLeft() > 1)
        return Int32(getLeft());

    if(getParent() == NULL)
    {
        SWARNING << "Viewport::getPixelLeft: viewport has no parent window!" 
                 << std::endl;

        return 0;
    }
    
    return Int32(getParent()->getWidth() * getLeft());
}

/*! Calculate the positon of the right border of the viewport. Needs a valid
    _sfParent value.
 */

Int32 Viewport::getPixelRight(void) const
{
    // >1: pixel
    if(getRight() > 1)
        return Int32(getRight());

    if(getParent() == NULL)
    {
        SWARNING << "Viewport::getPixelRight: viewport has no parent window!" 
                 << std::endl;

        return 0;
    }
    
    // <=1: partial screen, use 1 less to not overlap other windows
    return Int32(getParent()->getWidth() * getRight() - 1);
}

/*! Calculate the positon of the bottom border of the viewport. Needs a valid
    _sfParent value.
 */

Int32 Viewport::getPixelBottom(void) const
{
    if(getBottom() > 1)
        return Int32(getBottom());
    
    if(getParent() == NULL)
    {
        SWARNING << "Viewport::getPixelBottom: viewport has no parent window!"
                 << std::endl;

        return 0;
    }

    return Int32(getParent()->getHeight() * getBottom());
}

/*! Calculate the positon of the top border of the viewport. Needs a valid
    _sfParent value.
 */

Int32 Viewport::getPixelTop(void) const
{
    // >1: pixel
    if(getTop() > 1)
        return Int32(getTop());
    
    if(getParent() == NULL)
    {
        SWARNING << "Viewport::getPixelTop: viewport has no parent window!" 
                 << std::endl;

        return 0;
    }

    // <=1: partial screen, use 1 less to not overlap other windows
    return Int32(getParent()->getHeight() * getTop() - 1);
}

/*! Checks if the viewport fills the whole window. Needs a valid
  _sfParent value.
 */
bool Viewport::isFullWindow(void) const
{
    if(getParent() == NULL)
    {
        SWARNING << "Viewport::isFullWindow: viewport has no parent window!" 
                 << std::endl;

        return false;
    }

    return  
        getPixelBottom() == 0 &&
        getPixelLeft()   == 0 &&
        getPixelTop()    == getParent()->getHeight() - 1 &&
        getPixelRight()  == getParent()->getWidth () - 1;
}

Window *Viewport::getParent(void) const
{
    return dynamic_cast<Window *>(_sfParent.getValue());
}

/*! Returns normalized coordintes from viewport coordinates.

   @param normX Normalized X coordinate in the range [-1.0,1.0].
   @param normY Normalized Y coordinate in the range [-1.0,1.0].
   @param vpX   X coordinate of this viewport in the range [0,width].
   @param vpY   Y coordinate of this viewport in the range [0,height].

   @note Out-of-range input values lead to out-of-range output values.
 */
void Viewport::getNormalizedCoordinates(      Real32& normX,
                                              Real32& normY,
                                        const Int32   vpX  ,
                                        const Int32   vpY  ) const
{
    normX =
        (vpX - getPixelLeft()) /
        static_cast<Real32>(getPixelWidth()) * 2.f - 1.f;

    normY = 1.f - (
        (vpY - (getParent()->getHeight() - getPixelTop())) /
        static_cast<Real32>(getPixelHeight())) * 2.f;
}

/*-------------------------- your_category---------------------------------*/

/*! Draw the viewport. Restrict the OpenGL rendering to the given part of the
  window, clear it, draw it using the given DrawAction and add the Foregrounds.
  
  The _sfCamera, _sfBackground and _sfRoot Fields need to be valid, otherwise
  drawing will fail.
  
  \dev
  
  Activates scissoring only if the viewport doesn't fill the wholw window, as
  it significantly slows down some OpenGL implementations.
  
  \enddev
  
 */

void Viewport::activateSize(void)
{
    GLint pl = getPixelLeft();
    GLint pr = getPixelRight();
    GLint pb = getPixelBottom();
    GLint pt = getPixelTop();
    GLint pw = pr - pl + 1;
    GLint ph = pt - pb + 1;

    glViewport(pl, pb, pw, ph);

    if(!isFullWindow())
    {
        glScissor(pl, pb, pw, ph);
        glEnable(GL_SCISSOR_TEST);
    }
    else
    {
       glDisable(GL_SCISSOR_TEST);
    }
        
}

void Viewport::activate(void)
{
    activateSize();
}

void Viewport::deactivate(void)
{
}

void Viewport::render(RenderActionBase *action)
{
    _pTravValidator->incEventCounter();
 
    if(this->getTravMask() == 0x0000)
        return;

    if(getCamera() == NULL)
    {
        SWARNING << "Viewport::render: no Camera, can not render!" << std::endl;
        return;
    }
    if(getBackground() == NULL)
    {
        SWARNING << "Viewport::render: no Background, can not render!" << std::endl;
        return;
    }
    if(getRoot() == NULL)
    {
        SWARNING << "Viewport::render: no root, can not render!" << std::endl;
        return;
    }

#if 0 // Have to check GV
    activate();
#endif

    action->setCamera    (getCamera    ());
    action->setBackground(getBackground());
    action->setViewport  (this           );
    action->setTravMask  (getTravMask()  );

    action->apply(getRoot());

    Window  *pWin = action->getWindow();

    if((pWin->getDrawMode() & Window::PartitionDrawMask) ==
                                              Window::SequentialPartitionDraw)
    {
        DrawEnv  oEnv;

        oEnv.setWindow(action->getWindow());

        oEnv.setTileFullSize(getCamera()->tileGetFullSize());
        oEnv.setTileRegion  (getCamera()->tileGetRegion  ());

        oEnv.setDrawerId  (action->getDrawerId  ());
        oEnv.setDrawableId(action->getDrawableId());

        for(UInt16 i=0; i < getMFForegrounds()->size(); i++)
        {
            Foreground        *pForeground = getForegrounds(i);
            FrameBufferObject *pTarget     = this->getTarget();

            if(pTarget != NULL)
            {
                pTarget->activate(&oEnv);
            }

            pForeground->draw(&oEnv, this);

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
                new ViewportDrawTask(this, ViewportDrawTask::Foregrounds);
        }

        pWin->queueTaskFromDrawer(_pForegroundTask);
    }

#if 0 // Have to check GV
    deactivate();
#endif
}

void Viewport::renderForegrounds(Window *pWin)
{
    DrawEnv  oEnv;

    oEnv.setWindow(pWin);

    oEnv.setTileFullSize(getCamera()->tileGetFullSize());
    oEnv.setTileRegion  (getCamera()->tileGetRegion  ());

    for(UInt16 i=0; i < getMFForegrounds()->size(); i++)
    {
        Foreground        *pForeground = getForegrounds(i);
        FrameBufferObject *pTarget     = this->getTarget();

        if(pTarget != NULL)
        {
            pTarget->activate(&oEnv);
        }

        pForeground->draw(&oEnv, this);

        if(pTarget != NULL)
        {
            pTarget->deactivate(&oEnv);
        }
    }
}

bool Viewport::isPassive(void)
{
    return false;
}

FrameBufferObject *Viewport::getTarget(void)
{
    return NULL;
}

/*------------------------------- dump ----------------------------------*/

void Viewport::dump(     UInt32    OSG_CHECK_ARG(uiIndent), 
                    const BitVector OSG_CHECK_ARG(bvFlags)) const
{
    SLOG << "Dump Viewport NI" << std::endl;

    fprintf(stderr, "%p %p %p\n", 
            this, 
            _sfCamera.getValue(),
            getCamera());
}


