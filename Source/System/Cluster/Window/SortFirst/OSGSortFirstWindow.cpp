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
#include <OSGConfig.h>
#include <OSGGL.h>
#include <OSGTileCameraDecorator.h>
#include <OSGViewport.h>
#include <OSGGeometry.h>
#include <OSGStereoBufferViewport.h>
#include "OSGSortFirstWindow.h"
#include "OSGClusterViewBuffer.h"
#include "OSGConnection.h"
#include "OSGRenderNode.h"
#include "OSGTileGeometryLoad.h"
#include "OSGClusterNetwork.h"
#include "OSGRenderActionBase.h"

OSG_USING_NAMESPACE

ClusterViewBuffer SortFirstWindow::_bufferHandler;

// #define USE_VPORT_SLICES

/*! \class OSG::SortFirstWindow
    \ingroup GrpSystemCluster
    Cluster rendering configuration for sort first image composition
*/

/*----------------------- constructors & destructors ----------------------*/

//! Constructor

SortFirstWindow::SortFirstWindow(void) :
    Inherited(),
    _tileLoadBalancer(NULL),
    _renderNode(NULL)
{
}

//! Copy Constructor

SortFirstWindow::SortFirstWindow(const SortFirstWindow &source) :
    Inherited(source),
    _tileLoadBalancer(NULL),
    _renderNode(NULL)
{
}

//! Destructor

SortFirstWindow::~SortFirstWindow(void)
{
    if(_tileLoadBalancer)
        delete _tileLoadBalancer;
    if(_renderNode)
        delete _renderNode;
}

/*----------------------------- class specific ----------------------------*/

//! initialize the static features of the class, e.g. action callbacks

void SortFirstWindow::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);
}

//! react to field changes

void SortFirstWindow::changed(ConstFieldMaskArg whichField, 
                              UInt32            origin,
                              BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

//! output the instance for debug purposes

void SortFirstWindow::dump(      UInt32    , 
                           const BitVector ) const
{
    SLOG << "Dump SortFirstWindow NI" << std::endl;
}

/*----------------------------- server methods ----------------------------*/

/** transfer server cababilities to the client
 *
 **/
void SortFirstWindow::serverInit(Window *serverWindow,
                                 UInt32   id)
{
#if USE_VPORT_SLICES

#else
    UInt32 sync;
    RenderNode renderNode;
    Connection *connection=getNetwork()->getMainConnection();

    // create cluster node information
    // get performance
    renderNode.determinePerformance(serverWindow);
    renderNode.dump();
    // transfer to client for load balancing
    connection->putValue(id);
    renderNode.copyToBin(*connection);
    connection->flush();
    connection->selectChannel();
    connection->getValue(sync);
#endif
}

#ifdef OSG_OLD_RENDER_ACTION
/** update server window
 *
 * todo: enamble frustum culling if error is removed
 **/
void SortFirstWindow::serverRender( Window *serverWindow,
                                    UInt32 id,
                                    DrawActionBase *action )
{
    TileCameraDecoratorPtr deco;
    ViewportPtr serverPort;
    ViewportPtr clientPort;
    UInt32 sv,cv,regionStart;
    UInt32 vpWidth;
    UInt32 vpHeight;

    // duplicate viewports
    for(cv=0,sv=0;cv<getPort().size();cv++)
    {
        clientPort = getPort()[cv];
        if(serverWindow->getPort().size() <= sv)
        {
            // create new port
            //serverPort = StereoBufferViewport::create();
            serverPort = dynamic_cast<ViewportPtr>(clientPort->shallowCopy());
            deco=TileCameraDecorator::create();

            serverWindow->addPort(serverPort);
            serverPort->setCamera(deco);
        }
        else
        {
            serverPort = serverWindow->getPort()[sv];
            deco=dynamic_cast<TileCameraDecoratorPtr>(serverPort->getCamera());
            if(serverWindow->getPort()[sv]->getType() != 
               clientPort->getType())
            {
                // there is a viewport with the wrong type
                serverPort = dynamic_cast<ViewportPtr>(clientPort->shallowCopy());
                serverWindow->replacePort(sv, serverPort);//[sv] = serverPort;
                serverPort->setCamera(deco);
            }
            else
            {
                deco=dynamic_cast<TileCameraDecoratorPtr>(serverPort->getCamera());
            }
            //serverPort = serverWindow->getPort()[sv];
            //deco=TileCameraDecoratorPtr::dcast(serverPort->getCamera());
        }

        // duplicate values
        regionStart=cv * getServers().size() * 4 + id * 4;
        serverPort->setSize( 
            Real32(getRegion()[regionStart+0] + clientPort->getPixelLeft()),
            Real32(getRegion()[regionStart+1] + clientPort->getPixelBottom()),
            Real32(getRegion()[regionStart+2] + clientPort->getPixelLeft()),
            Real32(getRegion()[regionStart+3] + clientPort->getPixelBottom()));

        serverPort->setRoot      ( clientPort->getRoot()       );
        serverPort->setBackground( clientPort->getBackground() );

        serverPort->assignForegrounds(clientPort->getForegrounds());

        serverPort->setTravMask  ( clientPort->getTravMask()   );

        // calculate tile parameters
        vpWidth =clientPort->getPixelWidth();
        vpHeight=clientPort->getPixelHeight();

        deco->setFullWidth ( vpWidth );
        deco->setFullHeight( vpHeight );
        deco->setSize( getRegion()[ regionStart+0 ]/(float)vpWidth,
                       getRegion()[ regionStart+1 ]/(float)vpHeight,
                       getRegion()[ regionStart+2 ]/(float)vpWidth,
                       getRegion()[ regionStart+3 ]/(float)vpHeight );
        deco->setDecoratee( clientPort->getCamera() );

        sv++;
    }
    // remove unused ports
    while(serverWindow->getPort().size()>sv)
    {
        serverWindow->subPort(sv);
    }

    Inherited::serverRender(serverWindow,id,action);

    // compression type
    if(getCompose())
    {
        if(getCompression().empty())
        {
            _bufferHandler.setImgTransType(NULL);
        }
        else
        {
            _bufferHandler.setImgTransType(getCompression().c_str());
        }
        if(getSubtileSize())
        {
            _bufferHandler.setSubtileSize(getSubtileSize());
        }
    }

#if 1
    glDisable(GL_SCISSOR_TEST);
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT);
#endif

    // render the viewports
    serverWindow->activate();
    serverWindow->frameInit();
    action->setWindow( serverWindow );
    for(sv=0;sv<serverWindow->getPort().size();++sv)
    {
        ViewportPtr vp=serverWindow->getPort()[sv];
        vp->render( action );

        // send resulting image
        if(getCompose())
        {
            // activate the appropriate viewport to retrieve image
            vp->activate();

            // send image
            _bufferHandler.send(
                *getNetwork()->getMainPointConnection(),
                ClusterViewBuffer::RGB,
                vp->getPixelLeft(),
                vp->getPixelBottom(),
                vp->getPixelRight(),
                vp->getPixelTop(),
                0,0);

            // deactivate the viewport
            vp->deactivate();
        }
    }
}
#endif

void SortFirstWindow::serverRender( Window           *serverWindow,
                                    UInt32            id,
                                    RenderActionBase *action )
{
    TileCameraDecoratorUnrecPtr deco;
    ViewportUnrecPtr serverPort;
    Viewport *clientPort;
    UInt32 sv,cv,regionStart;
    UInt32 vpWidth;
    UInt32 vpHeight;

    // duplicate viewports
    for(cv=0,sv=0;cv<getMFPort()->size();cv++)
    {
        clientPort = getPort(cv);
        if(serverWindow->getMFPort()->size() <= sv)
        {
            // create new port
            //serverPort = StereoBufferViewport::create();
            serverPort = 
                dynamic_pointer_cast<Viewport>(clientPort->shallowCopy());
            deco=TileCameraDecorator::create();

            serverWindow->addPort(serverPort);
            serverPort->setCamera(deco);
        }
        else
        {
            serverPort = serverWindow->getPort(sv);
            deco=dynamic_cast<TileCameraDecorator *>(serverPort->getCamera());
            if(serverWindow->getPort(sv)->getType() != 
               clientPort->getType())
            {
                // there is a viewport with the wrong type
                serverPort = dynamic_pointer_cast<Viewport>(
                    clientPort->shallowCopy());

                serverWindow->replacePort(sv, 
                                          serverPort);//[sv] = serverPort;
                serverPort->setCamera(deco);
            }
            else
            {
                deco=dynamic_cast<TileCameraDecorator *>(
                    serverPort->getCamera());
            }
            //serverPort = serverWindow->getPort()[sv];
            //deco=TileCameraDecoratorPtr::dcast(serverPort->getCamera());
        }

        // duplicate values
        regionStart=cv * getMFServers()->size() * 4 + id * 4;
        serverPort->setSize( 
            Real32(getRegion(regionStart+0) + clientPort->getPixelLeft()),
            Real32(getRegion(regionStart+1) + clientPort->getPixelBottom()),
            Real32(getRegion(regionStart+2) + clientPort->getPixelLeft()),
            Real32(getRegion(regionStart+3) + clientPort->getPixelBottom()));

        serverPort->setRoot      ( clientPort->getRoot()       );
        serverPort->setBackground( clientPort->getBackground() );

        serverPort->assignForegrounds(*(clientPort->getMFForegrounds()));

        serverPort->setTravMask  ( clientPort->getTravMask()   );

        // calculate tile parameters
        vpWidth =clientPort->getPixelWidth();
        vpHeight=clientPort->getPixelHeight();

        deco->setFullWidth ( vpWidth );
        deco->setFullHeight( vpHeight );
        deco->setSize( getRegion( regionStart+0 )/Real32(vpWidth),
                       getRegion( regionStart+1 )/Real32(vpHeight),
                       getRegion( regionStart+2 )/Real32(vpWidth),
                       getRegion( regionStart+3 )/Real32(vpHeight) );
        deco->setDecoratee( clientPort->getCamera() );

        sv++;
    }
    // remove unused ports
    while(serverWindow->getMFPort()->size()>sv)
    {
        serverWindow->subPort(sv);
    }

    Inherited::serverRender(serverWindow,id,action);

    // compression type
    if(getCompose())
    {
        if(getCompression().empty())
        {
            _bufferHandler.setImgTransType(NULL);
        }
        else
        {
            _bufferHandler.setImgTransType(getCompression().c_str());
        }
        if(getSubtileSize())
        {
            _bufferHandler.setSubtileSize(getSubtileSize());
        }
    }

#if 1
    glDisable(GL_SCISSOR_TEST);
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT);
#endif

    // render the viewports
    serverWindow->activate();
    serverWindow->frameInit();
    action->setWindow( serverWindow );
    for(sv=0;sv<serverWindow->getMFPort()->size();++sv)
    {
        Viewport *vp=serverWindow->getPort(sv);
        vp->render( action );

        // send resulting image
        if(getCompose())
        {
            // activate the appropriate viewport to retrieve image
            vp->activate();

            // send image
            _bufferHandler.send(
                *getNetwork()->getMainPointConnection(),
                ClusterViewBuffer::RGB,
                vp->getPixelLeft(),
                vp->getPixelBottom(),
                vp->getPixelRight(),
                vp->getPixelTop(),
                0,0);

            // deactivate the viewport
            vp->deactivate();
        }
    }
}

/*! send image to client
 */
void SortFirstWindow::serverSwap( Window *window,
                                  UInt32 )
{
    if(!getCompose())
    {
        Connection *connection=getNetwork()->getMainConnection();
        connection->signal();
        connection->wait();
    }
    window->swap();
}

/*----------------------------- client methods ----------------------------*/

/*! read server cababilities
 */

void SortFirstWindow::clientInit( void )
{
#if USE_VPORT_SLICES

#else
    UInt32               id;
    RenderNode           renderNode;
    GroupConnection     *connection = getNetwork()->getMainGroupConnection();
    Connection::Channel  channel;

    _tileLoadBalancer=new TileLoadBalancer(getUseFaceDistribution());
    // read all node infos
    for(UInt32 i=0;i<connection->getChannelCount();++i)
    {
        printf("%d\n",i);
        channel = connection->selectChannel();
        connection->subSelection(channel);
        connection->getValue(id);
        renderNode.copyFromBin(*connection);
        renderNode.dump();
        _tileLoadBalancer->addRenderNode(renderNode,id);    
    }
    connection->resetSelection();
    printf("end\n");
    // sync servers
    connection->putValue(id);
    connection->flush();
#endif

    Inherited::clientInit();
}

/*! client frame init
 */

void SortFirstWindow::clientPreSync( void )
{
    SortFirstWindow *ptr=this;
    if(getCompose())
    {
        // get window size from client window
        if(getClientWindow() != NULL)
        {
            if(getWidth()  != getClientWindow()->getWidth() ||
               getHeight() != getClientWindow()->getHeight())
            {
                setSize(getClientWindow()->getWidth(),
                        getClientWindow()->getHeight());
            }
        }
    }
#if 0
    else
    {
        setSize(1280,
                1024);
    }
#endif
    UInt32 i;
    UInt32 cv;
    TileLoadBalancer::ResultT region;
    
    editMFRegion()->clear();
#if USE_VPORT_SLICES
    for(cv=0;cv<getPort().size();cv++)
    {
        int s=getServers().size();
        for(i=0;i<s;i++)
        {
            editRegion().push_back(i/float(s)*getWidth());
            editRegion().push_back(0);
            editRegion().push_back((i+1)/float(s)*getWidth());
            editRegion().push_back(1*getHeight());
        }
    }
#else
    for(cv=0;cv<getMFPort()->size();cv++)
    {
        _tileLoadBalancer->update( getPort(cv)->getRoot() );
        _tileLoadBalancer->balance(getPort(cv),
                              false,
                              region);
        for(i=0;i<getMFServers()->size();i++)
        {
            editMFRegion()->push_back(region[i].x1);
            editMFRegion()->push_back(region[i].y1);
            editMFRegion()->push_back(region[i].x2);
            editMFRegion()->push_back(region[i].y2);
        }
    }
#endif

    Inherited::clientPreSync();
}

#ifdef OSG_OLD_RENDER_ACTION
/*! client rendering
 *  
 *  one tile is rendered by the client
 */

void SortFirstWindow::clientRender( RenderActionBase *  /* action */ )
{
//    Inherited::clientRender(action);
}
#endif

void SortFirstWindow::clientRender(RenderActionBase *  /* action */)
{
//    Inherited::clientRender(action);
}

/*! show data
 */

void SortFirstWindow::clientSwap( void )
{
    UInt32 cv;
    GroupConnection *connection=getNetwork()->getMainGroupConnection();
    if(getCompose())
    {
        if(getClientWindow()!=NULL)
        {
            // receive all viewports
            for(cv=0;cv<getMFPort()->size();++cv)
            {
                Viewport *vp=getPort(cv);

                // activate the appropriate viewport to receive image
                vp->activate();

                // receive image
                _bufferHandler.recv(*connection);

                // deactivate the viewport
                vp->deactivate();
            }
            Inherited::clientSwap();
        }
    }
    else
    {
        connection->wait();
        connection->signal();
    }
}

