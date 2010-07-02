/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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

#include <stdlib.h>
#include <stdio.h>
#include "OSGConfig.h"
#include "OSGGL.h"
#include "OSGViewport.h"
#include "OSGTileCameraDecorator.h"
#include "OSGBaseFunctions.h"
#include "OSGStereoBufferViewport.h"
#include "OSGFieldContainerFields.h"
#include "OSGMultiDisplayWindow.h"
#include "OSGConnection.h"
#include "OSGNode.h"
#include "OSGClusterNetwork.h"
#include "OSGImageComposer.h"

#define FAST_SYNC 0

OSG_USING_NAMESPACE

/*! \class OSG::MultiDisplayWindow
 *  \ingroup GrpSystemCluster
 */

/*----------------------- constructors & destructors ----------------------*/

/*! Constructor
 */

MultiDisplayWindow::MultiDisplayWindow(void) :
    Inherited()
{
}

/*! Copy Constructor
 */

MultiDisplayWindow::MultiDisplayWindow(const MultiDisplayWindow &source) :
    Inherited(source)
{
}

/*! Destructor
 */

MultiDisplayWindow::~MultiDisplayWindow(void)
{
}

/*----------------------------- class specific ----------------------------*/

/*! initialize the static features of the class, e.g. action callbacks
 */
void MultiDisplayWindow::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);
}

/*! react to field changes
 */

void MultiDisplayWindow::changed(ConstFieldMaskArg whichField, 
                                 UInt32            origin,
                                 BitVector         details   )
{
    Inherited::changed(whichField, origin, details);
}

/*! output the instance for debug purposes
 */

void MultiDisplayWindow::dump(      UInt32    , 
                              const BitVector ) const
{
    SLOG << "hServers:" << getHServers() << " "
         << "vServers:" << getVServers() << std::endl;
}

/*----------------------------- server methods ----------------------------*/

/*! initialise the cluster window on the server side. This method is
     called after the first sync.
 */

void MultiDisplayWindow::serverInit(Window * ,
                                    UInt32   )
{
}

#ifdef OSG_OLD_RENDER_ACTION
/*! render server window
 *  
 *  update all viewport parameters and render local viewports
 *  Width and height of the whole window are calculated by 
 *  multiplieing the local window size by hServers and vServers.
 */

void MultiDisplayWindow::serverRender(WindowPtr         serverWindow,
                                      UInt32            id,
                                      DrawActionBase *action )
{
    TileCameraDecoratorPtr deco;
    ViewportPtr serverPort;
    ViewportPtr clientPort;
    StereoBufferViewportPtr clientStereoPort;
    UInt32 sv,cv;
    Int32 l,r,t,b;
    Int32 cleft,cright,ctop,cbottom;

    // sync, otherwise viewports will be out of date

    if(!getHServers())
    {
        setHServers(getServers().size());
    }
    if(!getVServers())
    {
        setVServers(1);
    }

    UInt32 row   =id/getHServers();
    UInt32 column=id%getHServers();

    // calculate width and height from local width and height
    UInt32 width  = serverWindow->getWidth() ;
    UInt32 height = serverWindow->getHeight();

    if(getWidth()==0)
    {
        setWidth( width*getHServers() );
    }
    if(getHeight()==0)
    {
        setHeight( height*getVServers() );
    }

    Int32 left   = column * width  - column * getXOverlap();
    Int32 bottom = row    * height - row    * getYOverlap();
    Int32 right  = left   + width  - 1;
    Int32 top    = bottom + height - 1;
    Real64 scaleCWidth  = 
        ((width - getXOverlap()) * (getHServers() - 1) + width) / 
        (float)getWidth();
    Real64 scaleCHeight = 
        ((height - getYOverlap())* (getVServers() - 1) + height)/ 
        (float)getHeight();

    bool   isVirtualPort = false;

    // duplicate viewports
    for(cv = 0, sv = 0; cv < getPort().size(); ++cv)
    {
        clientPort = getPort()[cv];

#if 0
        isVirtualPort = clientPort->getType().isDerivedFrom(FBOViewport::getClassType());

        if(isVirtualPort)
        {
            // TODO -- seems wrong to render this on all servers, though rendering
            // then transmitting the texture doesn't seem like a good idea either.
            if(serverWindow->getPort().size() <= sv)
            {
                serverPort = ViewportPtr::dcast(clientPort->shallowCopy());
                beginEditCP(serverWindow);
                serverWindow->addPort(serverPort);
                endEditCP(serverWindow);
            }
            else
            {
                serverPort = serverWindow->getPort()[sv];
                if(serverPort->getType() != clientPort->getType())
                {
                    // there is a viewport with the wrong type
                    subRefCP(serverWindow->getPort()[sv]);
                    serverPort = ViewportPtr::dcast(clientPort->shallowCopy());
                    beginEditCP(serverWindow);
                    {
                        serverWindow->getPort()[sv] = serverPort;
                    }
                    endEditCP(serverWindow);
                }
            }
            // update changed viewport fields
            updateViewport(serverPort,clientPort);
        }
        else
#endif
        {
            clientStereoPort = 
                dynamic_cast<StereoBufferViewportPtr>(clientPort);

            cleft   = (Int32)(clientPort->getPixelLeft()      * scaleCWidth)   ;
            cbottom = (Int32)(clientPort->getPixelBottom()    * scaleCHeight)  ;
            cright  = (Int32)((clientPort->getPixelRight()+1) * scaleCWidth) -1;
            ctop    = (Int32)((clientPort->getPixelTop()+1)   * scaleCHeight)-1;

            if(cright  < left   ||
               cleft   > right  ||
               ctop    < bottom ||
               cbottom > top      )
            {
                // invisible on this server screen
                continue;
            }

            // calculate overlapping viewport
            l = osgMax(cleft  ,left  ) - left;
            b = osgMax(cbottom,bottom) - bottom;
            r = osgMin(cright ,right ) - left;
            t = osgMin(ctop   ,top   ) - bottom;

            if(serverWindow->getPort().size() <= sv)
            {
                serverPort = 
                    dynamic_cast<ViewportPtr>(clientPort->shallowCopy());

                deco = TileCameraDecorator::create();

                serverWindow->addPort(serverPort);

                serverPort->setCamera(deco);
            }
            else
            {
                serverPort = serverWindow->getPort()[sv];
                
                deco = dynamic_cast<TileCameraDecoratorPtr>(
                    serverPort->getCamera());

                if(serverPort->getType() != clientPort->getType())
                {
                    // there is a viewport with the wrong type
                    serverPort =
                        dynamic_cast<ViewportPtr>(clientPort->shallowCopy());

                    if(deco == NULL)
                        deco = TileCameraDecorator::create();

                    serverPort->setCamera(deco);

                    serverWindow->replacePort(sv, serverPort);
                }
            }

            // update changed viewport fields
            updateViewport(serverPort,clientPort);

            // set viewport size
            serverPort->setSize(Real32(l),Real32(b),Real32(r),Real32(t));

            // use pixel even if pixel = 1
            if(serverPort->getLeft() == 1.0)
                serverPort->setLeft(1.0001);
            
            if(serverPort->getRight() == 1.0)
                serverPort->setRight(1.0001);
            
            if(serverPort->getTop() == 1.0)
                serverPort->setTop(1.0001);

            if(serverPort->getBottom() == 1.0)
                serverPort->setBottom(1.0001);

            // calculate tile parameters
            deco->setFullWidth ( cright-cleft );
            deco->setFullHeight( ctop-cbottom );
            deco->setSize( ( l+left-cleft     ) / (float)( cright-cleft ),
                           ( b+bottom-cbottom ) / (float)( ctop-cbottom ),
                           ( r+left-cleft     ) / (float)( cright-cleft ),
                           ( t+bottom-cbottom ) / (float)( ctop-cbottom ) );
            deco->setDecoratee( clientPort->getCamera() );
        }
        sv++;
    }

    // remove unused ports
    while(serverWindow->getPort().size()>sv)
    {
        serverWindow->subPort(sv);
    }

    Inherited::serverRender(serverWindow,id,action);
}
#endif

void MultiDisplayWindow::serverRender(Window           *window,
                                      UInt32            id,
                                      RenderActionBase *action)
{
    TileCameraDecoratorUnrecPtr deco;
    ViewportUnrecPtr serverPort;
    Viewport * clientPort;
    StereoBufferViewport *clientStereoPort;
    UInt32 sv,cv;
    Int32 l,r,t,b;
    Int32 cleft,cright,ctop,cbottom;

    if(!getHServers())
    {
        setHServers(getMFServers()->size());
    }
    if(!getVServers())
    {
        setVServers(1);
    }

    UInt32 row   =id/getHServers();
    UInt32 column=id%getHServers();

    // calculate width and height from local width and height
    UInt32 width  = window->getWidth() ;
    UInt32 height = window->getHeight();

    if(getWidth()==0)
    {
        setWidth( width*getHServers() );
    }
    if(getHeight()==0)
    {
        setHeight( height*getVServers() );
    }

    Int32 left   = column * width  - column * getXOverlap();
    Int32 bottom = row    * height - row    * getYOverlap();
    Int32 right  = left   + width  - 1;
    Int32 top    = bottom + height - 1;
    Real64 scaleCWidth  =
        ((width - getXOverlap()) * (getHServers() - 1) + width) /
        float(getWidth());
    Real64 scaleCHeight =
        ((height - getYOverlap())* (getVServers() - 1) + height)/
        float(getHeight());

    // duplicate viewports
    for(cv=0,sv=0;cv<getMFPort()->size();cv++)
    {
        clientPort = getPort(cv);

        clientStereoPort = dynamic_cast<StereoBufferViewport *>(clientPort);

        cleft   = Int32(clientPort->getPixelLeft()      * scaleCWidth)   ;
        cbottom = Int32(clientPort->getPixelBottom()    * scaleCHeight)  ;
        cright  = Int32((clientPort->getPixelRight()+1) * scaleCWidth) -1;
        ctop    = Int32((clientPort->getPixelTop()+1)   * scaleCHeight)-1;

        if(cright  < left   ||
           cleft   > right  ||
           ctop    < bottom ||
           cbottom > top      )
        {
            // invisible on this server screen
            continue;
        }

        // calculate overlapping viewport
        l = osgMax(cleft  ,left  ) - left;
        b = osgMax(cbottom,bottom) - bottom;
        r = osgMin(cright ,right ) - left;
        t = osgMin(ctop   ,top   ) - bottom;

        if(window->getMFPort()->size() <= sv)
        {
            serverPort = dynamic_pointer_cast<Viewport>(
                clientPort->shallowCopy());

            deco = TileCameraDecorator::create();

            window->addPort(serverPort);

            serverPort->setCamera(deco);
        }
        else
        {
            serverPort = window->getPort(sv);

            deco = dynamic_cast<TileCameraDecorator *>(
                serverPort->getCamera());

            if(window->getPort(sv)->getType() != clientPort->getType())
            {
                // there is a viewport with the wrong type
                serverPort =
                    dynamic_pointer_cast<Viewport>(clientPort->shallowCopy());

                window->replacePort(sv, 
                                    serverPort);//[sv] = serverPort;
                serverPort->setCamera(deco);
            }
            else
            {
                deco = dynamic_cast<TileCameraDecorator *>(
                    serverPort->getCamera());
            }
        }

        // update changed viewport fields
        updateViewport(serverPort, clientPort);

        // set viewport size
        serverPort->setSize(Real32(l),Real32(b),Real32(r),Real32(t));

        // use pixel even if pixel = 1
        if(serverPort->getLeft() == 1.0)
            serverPort->setLeft(1.0001f);

        if(serverPort->getRight() == 1.0)
            serverPort->setRight(1.0001f);

        if(serverPort->getTop() == 1.0)
            serverPort->setTop(1.0001f);

        if(serverPort->getBottom() == 1.0)
            serverPort->setBottom(1.0001f);

        // calculate tile parameters
        deco->setFullWidth ( cright-cleft );
        deco->setFullHeight( ctop-cbottom );
        deco->setSize( ( l+left-cleft     ) / float( cright-cleft ),
                       ( b+bottom-cbottom ) / float( ctop-cbottom ),
                       ( r+left-cleft     ) / float( cright-cleft ),
                       ( t+bottom-cbottom ) / float( ctop-cbottom ) );
        deco->setDecoratee( clientPort->getCamera() );

        sv++;
    }

    // remove unused ports
    while(window->getMFPort()->size()>sv)
    {
        window->subPort(sv);
    }

    Inherited::serverRender(window,id,action);
}

/*! swap server window
 */

void MultiDisplayWindow::serverSwap(Window *window, UInt32 id)
{
    Connection *connection;
    
    // clear command buffers
    UInt8 pixel[3];
    glReadPixels(0,0,
                 1,1,
                 GL_RGB,GL_UNSIGNED_BYTE,
                 pixel);
    glFinish();

#if !FAST_SYNC
    connection=getNetwork()->getMainConnection();
    if(!getInterleave())
    {
        // tell client that we are finish
        connection->signal();
        // wait for swap
        connection->wait();
    }
#endif

    Inherited::serverSwap(window,id);
}

/*----------------------------- client methods ----------------------------*/

/*! init client window
 *  
 *  If manageClientViewports is set, then all viewports from the
 *  cluster window are duplcated to the client window. 
 */

void MultiDisplayWindow::clientInit(void)
{
    bool      changed = false;
    Viewport *vp, *cvp;

    if(getManageClientViewports() == false ||
       getClientWindow         () == NULL)
    {
        return;
    }

    // check if something changed
    if(getMFPort()->size() == getClientWindow()->getMFPort()->size())
    {
        for(UInt32 v = 0 ; v < getMFPort()->size() && !changed ; v++)
        {
            vp  = getPort(v);

            cvp = getClientWindow()->getPort(v);

            if( vp->getRoot() != cvp->getRoot() ||
                vp->getLeft() != cvp->getLeft() ||
                vp->getRight() != cvp->getRight() ||
                vp->getBottom() != cvp->getBottom() ||
                vp->getTop() != cvp->getTop() ||
                vp->getBackground() != cvp->getBackground() ||
                vp->getMFForegrounds()->size() != 
                    cvp->getMFForegrounds()->size() )
            {
                changed = true;
            }
        }
    }
    else
    {
        changed = true;
    }

    if(changed)
    {
        // remove all viewports
#if 0
        while(getClientWindow()->getMFPort()-size())
        {
            vp = getClientWindow()->getPort(0);

            getClientWindow()->subPort(0U);
        }
#endif

        getClientWindow()->clearPorts();

        // duplicate viewports
        for(UInt32 v=0 ; v<getMFPort()->size() ;v++)
        {
            ViewportUnrecPtr pTmpPort = 
                dynamic_pointer_cast<Viewport>(getPort(v)->shallowCopy());

            getClientWindow()->addPort(pTmpPort);
        }
    }
}
    
/*! render client window
 */
void MultiDisplayWindow::clientSwap( void )
{
    Connection *connection = getNetwork()->getMainConnection();

#if FAST_SYNC
    connection->selectChannel();
#else
    if(!getInterleave())
    {
        // wait for all servers to finish
        connection->wait();
        // initiate swap
        connection->signal();
    }
#endif

    // show client window 
    Inherited::clientSwap();
}

/*-------------------------------------------------------------------------*/
/*                              helper                                     */

/*! update all changed viewport field from the client port
 */

void MultiDisplayWindow::updateViewport(Viewport *serverPort,
                                        Viewport *clientPort)
{
    bool equal;

    // Compare the pointers.
    if(serverPort == clientPort)
        return;

    if(serverPort == NULL || clientPort == NULL)
        return;

    if(serverPort->getType() != serverPort->getType())
        return;
    
    const FieldContainerType &type = serverPort->getType();

    UInt32 fcount = osgMin(serverPort->getType().getNumFieldDescs(),
                           clientPort->getType().getNumFieldDescs());
    
    for(UInt32 i = 1;i <= fcount; ++i)
    {
        const FieldDescriptionBase *fdesc = type.getFieldDesc(i);

        // ignore attachments
        if(strcmp(fdesc->getCName(), "parent"     ) == 0 ||
           strcmp(fdesc->getCName(), "camera"     ) == 0 ||
           strcmp(fdesc->getCName(), "attachments") == 0)
        {
            continue;
        }

        BitVector mask = fdesc->getFieldMask();
   
        mask &= serverPort->getFieldFlags()->_bClusterLocalFlags;

        if(!mask)
            continue;

        const FieldDescriptionBase *dst_desc = 
            serverPort->getType().getFieldDesc(i);

        const FieldDescriptionBase *src_desc = 
            clientPort->getType().getFieldDesc(i);


        GetFieldHandlePtr cdst_field = serverPort->getField(i);
        GetFieldHandlePtr src_field  = clientPort->getField(i);
    
        const FieldType &dst_ftype = dst_desc->getFieldType();
        const FieldType &src_ftype = src_desc->getFieldType();

        if(dst_ftype != src_ftype)
            continue;

        if(cdst_field == NULL || src_field == NULL)
            continue;

        equal = true;

        if(src_field->isPointerField() == true)
        {
            if(src_field->equal(cdst_field) == false)
            {
                EditFieldHandlePtr dst_field = serverPort->editField(i);

                dst_field->shareValues(src_field);
            }
        }
        else
        {
            if(src_field->equal(cdst_field) == false)
            {
                EditFieldHandlePtr dst_field = serverPort->editField(i);

                dst_field->copyValues(src_field);
            }
        }
    }
}
