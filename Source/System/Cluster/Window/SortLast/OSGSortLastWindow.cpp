/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
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

#include <OSGViewport.h>
#include <OSGStereoBufferViewport.h>
#include <OSGGeometry.h>
#include <OSGGeoPositionsFields.h>
#include <OSGGroup.h>
#include <OSGCamera.h>
#include <OSGProxyGroup.h>
#include <OSGMaterialGroup.h>
#include <OSGRemoteAspect.h>
#include <OSGImageComposer.h>
#include <OSGStatisticsForeground.h>
#include <OSGClusterNetwork.h>
#include <OSGDrawEnv.h>
#include <OSGRenderActionBase.h>

#include "OSGSortLastWindow.h"

OSG_USING_NAMESPACE

/*! \class osg::SortLastWindow
Cluster rendering configuration for sort first image composition
*/

/*----------------------------- static grouping functions -----------------*/

void SortLastWindow::buildGroups(void)
{
    UInt32            v          = 0;
    ViewportPtr       vp         = NullFC;
    NodePtr           root       = NullFC;
    DrawableListT     drawables;
    SortLastWindowPtr ptr        = this;
    UInt32            groupCount = 0;
    bool              rebuild    = false;

    // check for new nodes.
    FieldContainerFactoryBase *fcFactory = FieldContainerFactory::the();

    FieldContainerPtr fcPtr;

    ChangeList::ChangedStoreConstIt createdI;

    ChangeList *changeList = OSG::Thread::getCurrentChangeList();

    for(createdI  = changeList->beginCreated();
        createdI != changeList->endCreated(); 
        createdI++)
    {
        UInt32 uiId = (*createdI)->uiContainerId;

        fcPtr = fcFactory->getContainer(uiId);

        if(fcPtr != NullFC && dynamic_cast<NodePtr>(fcPtr) != NullFC)
            rebuild = true;
    }

    // is rebuild neccessary ?
    if(!rebuild && getGroupNodes().size())
        return;

    groupCount = getServers().size();

    if(getComposer() != NullFC)
    {
        groupCount = getComposer()->getUsableServers();
        if(getComposer()->getClientRendering())
            groupCount++;
    }

    // build groups for all viewports

    clearGroupNodes();
    editGroupLengths().clear();

    for(v = 0; v < getPort().size(); ++v)
    {
        ViewportPtr  vp         = getPort()[v];
        NodePtr      root       = vp->getRoot();

        drawables.clear();

        collectDrawables(root, drawables);

        if(drawables.size())
            splitDrawables(drawables, groupCount, false);
    }
}

/*----------------------------- server methods ----------------------------*/

/*! init composition
 */
void SortLastWindow::serverInit(WindowPtr serverWindow,
                                UInt32    id)
{
    // create default composer
    if(getComposer() == NullFC)
    {
/*
        FieldContainerPtr fcPtr = 
            FieldContainerFactory::the()->createFieldContainer("BinarySwapComposer");
        setComposer(ImageComposerPtr::dcast(fcPtr));
*/
    }

    if(getComposer() != NullFC)
    {
        // init composer
        ClusterWindowPtr clusterWindow = this;

        getComposer()->setup(false,
                             id,
                             serverWindow,
                             clusterWindow);

        getComposer()->open();
    }
}

/*! update server window
 */

#ifdef OSG_OLD_RENDER_ACTION
void SortLastWindow::serverRender(WindowPtr       serverWindow,
                                  UInt32          id,
                                  DrawActionBase *action      )
{
    ViewportPtr serverPort  = NullFC;
    ViewportPtr clientPort  = NullFC;
    UInt32      sv          = 0;
    UInt32      cv          = 0;
    UInt32      regionStart = 0;

    // duplicate viewports
    for(cv = 0, sv = 0; cv < getPort().size(); ++cv)
    {
        clientPort = getPort()[cv];

        if(serverWindow->getPort().size() <= sv)
        {
            // create new port
            serverPort = Viewport::create();

            serverWindow->addPort(serverPort);
        }
        else
        {
            serverPort = serverWindow->getPort()[sv];
        }

        // duplicate values

        if(getWidth() && getHeight())
        {
           serverPort->setSize(clientPort->getPixelLeft  (),
                               clientPort->getPixelBottom(),
                               clientPort->getPixelRight (),
                               clientPort->getPixelTop   ());
        }
        else
        {
            serverPort->setSize(0,0,0,0); 
        }
  
        serverPort->setCamera    (clientPort->getCamera    ());
        serverPort->setRoot      (clientPort->getRoot      ());
        serverPort->setBackground(clientPort->getBackground());

        // ignore statistics foreground
        serverPort->clearForegrounds();

        for(UInt32 f = 0 ; f < serverPort->getForegrounds().size(); ++f)
        {
            ForegroundPtr fg = clientPort->getForegrounds()[f];

            StatisticsForegroundPtr sfg = 
                dynamic_cast<StatisticsForegroundPtr>(fg);

            if(sfg == NullFC)
            {
                serverPort->addForeground(fg);
            }
        }

        serverPort->setTravMask(clientPort->getTravMask());

        sv++;
    }

    // remove unused ports
    while(serverWindow->getPort().size() > sv)
    {
        serverWindow->subPort(sv);
    }

    // setup visible nodes
    setupNodes(id);

    // render the viewports
    serverWindow->activate();
    serverWindow->frameInit();

    action->setWindow(serverWindow);

    if(getComposer() != NullFC)
        getComposer()->startFrame();

    for(sv = 0; sv < serverWindow->getPort().size(); ++sv)
    {
        ViewportPtr  vp         = serverWindow->getPort()[sv];
        NodePtr      root       = vp->getRoot();

        if(getComposer() != NullFC)
            getComposer()->startViewport(vp);

        // render
        vp->render(action);

        // compose single viewport
        if(getComposer() != NullFC)
            getComposer()->composeViewport(vp);
    }

    // compose whole window
    if(getComposer() != NullFC)
        getComposer()->composeWindow();
}
#endif

void SortLastWindow::serverRender(WindowPtr         serverWindow,
                                  UInt32            id,
                                  RenderActionBase *action      )
{
    ViewportUnrecPtr serverPort  = NullFC;
    ViewportPtr      clientPort  = NullFC;
    UInt32           sv          = 0;
    UInt32           cv          = 0;
    UInt32           regionStart = 0;

    // duplicate viewports
    for(cv = 0, sv = 0; cv < getPort().size(); ++cv)
    {
        clientPort = getPort()[cv];

        if(serverWindow->getPort().size() <= sv)
        {
            // create new port
            serverPort = Viewport::create();

            serverWindow->addPort(serverPort);
        }
        else
        {
            serverPort = serverWindow->getPort()[sv];
        }

        // duplicate values

        if(getWidth() && getHeight())
        {
           serverPort->setSize(clientPort->getPixelLeft  (),
                               clientPort->getPixelBottom(),
                               clientPort->getPixelRight (),
                               clientPort->getPixelTop   ());
        }
        else
        {
            serverPort->setSize(0,0,0,0); 
        }
  
        serverPort->setCamera    (clientPort->getCamera    ());
        serverPort->setRoot      (clientPort->getRoot      ());
        serverPort->setBackground(clientPort->getBackground());

        // ignore statistics foreground
        serverPort->clearForegrounds();

        for(UInt32 f = 0 ; f < serverPort->getForegrounds().size(); ++f)
        {
            ForegroundPtr fg = clientPort->getForegrounds()[f];

            StatisticsForegroundPtr sfg = 
                dynamic_cast<StatisticsForegroundPtr>(fg);

            if(sfg == NullFC)
            {
                serverPort->addForeground(fg);
            }
        }

        serverPort->setTravMask(clientPort->getTravMask());

        sv++;
    }

    // remove unused ports
    while(serverWindow->getPort().size() > sv)
    {
        serverWindow->subPort(sv);
    }

    // setup visible nodes
    setupNodes(id);

    // render the viewports
    serverWindow->activate();
    serverWindow->frameInit();

    action->setWindow(serverWindow);

    if(getComposer() != NullFC)
        getComposer()->startFrame();

    for(sv = 0; sv < serverWindow->getPort().size(); ++sv)
    {
        ViewportPtr  vp         = serverWindow->getPort()[sv];
        NodePtr      root       = vp->getRoot();

        if(getComposer() != NullFC)
            getComposer()->startViewport(vp);

        // render
        vp->render(action);

        // compose single viewport
        if(getComposer() != NullFC)
            getComposer()->composeViewport(vp);
    }

    // compose whole window
    if(getComposer() != NullFC)
        getComposer()->composeWindow();
}

/*! swap
 */
void SortLastWindow::serverSwap( WindowPtr window,
                                 UInt32 id)
{
    if(getComposer() == NullFC)
    {
        Connection *connection = getNetwork()->getMainConnection();
        // tell client that we are finish
        connection->signal();
        // wait for swap
        connection->wait();
    }
    Inherited::serverSwap(window,id);
}

/*----------------------------- client methods ----------------------------*/

/*! read server cababilities
 */
void SortLastWindow::clientInit( void )
{
    getNetwork()->getAspect()->addFieldFilter(Node::getClassType().getId(),
                                              Node::VolumeFieldMask);
    getNetwork()->getAspect()->addFieldFilter(Node::getClassType().getId(),
                                              Node::TravMaskFieldMask);

    // create default composer
    if(getComposer() == NullFC)
    {
/*
        FieldContainerPtr fcPtr = 
            FieldContainerFactory::the()->createFieldContainer("BinarySwapComposer");
        setComposer(ImageComposerPtr::dcast(fcPtr));
*/
    }
    if(getComposer() != NullFC)
    {
        SortLastWindowPtr clusterWindow(this);
        getComposer()->setup(true,
                             getServers().size(),
                             getClientWindow(),
                             clusterWindow);
        getComposer()->open();
        // build node groups
        buildGroups();
    }
}

/*! client frame init
 */
void SortLastWindow::clientPreSync( void )
{
    if(getClientWindow()!=NullFC)
    {
        UInt32 width =getClientWindow()->getWidth();
        UInt32 height=getClientWindow()->getHeight();
        if(width == 0)
            width = 2;
        if(height == 0)
            height = 2;
        if(width  != getWidth() ||
           height != getHeight())
        {
           setSize(width,height);
        }
    }
    
    Inherited::clientPreSync();

    // rebuild node groups
    buildGroups();
}

#ifdef OSG_OLD_RENDER_ACTION
/*! client rendering
 */
void SortLastWindow::clientRender(DrawActionBase *action)
{
    UInt32            p;
    UInt32            groupId = getServers().size();
    UInt32            l,b,r,t;
    UInt32            front,back;
    SortLastWindowPtr clusterWindow(this);

    if(getServers().size())
    {
        Connection *srcConnection=
            getNetwork()->getConnection(groupId);
        
        if(getClientWindow()!=NullFC)
        {
            setupNodes(groupId);
/*
            getClientWindow()->activate();
            getClientWindow()->frameInit();
*/
            action->setWindow(getClientWindow());

            if(getComposer() != NullFC)
                getComposer()->startFrame();

            DrawEnv oEnv;
            
            oEnv.setWindow(action->getWindow());

            // render all viewports
            for(p = 0; p < getPort().size() ; ++p)
            {
                ViewportPtr vp=getPort()[p];
                if(getComposer() != NullFC)
                {
                    getComposer()->startViewport(vp);

                    action->setCamera    (vp->getCamera    ());
                    action->setBackground(vp->getBackground());
                    action->setViewport  (vp                 );
                    action->setTravMask  (vp->getTravMask  ());

                    action->apply(vp->getRoot());

                    for(UInt16 i=0; i < vp->getForegrounds().size(); i++)
                    {
                        if(dynamic_cast<StatisticsForegroundPtr>(
                               vp->getForegrounds(i)) == NullFC)
                        {
                            vp->getForegrounds(i)->draw(&oEnv, vp);
                        }
                    }

                    getComposer()->composeViewport(vp);

                    for(UInt16 i=0; i < vp->getForegrounds().size(); i++)
                    {
                        if(dynamic_cast<StatisticsForegroundPtr>(
                               vp->getForegrounds(i)) != NullFC)
                        {
                            vp->getForegrounds(i)->draw(&oEnv, vp);
                        }
                    }

                }
                else
                {
                    vp->render(action);
                }
            }

            // compose whole window
            if(getComposer() != NullFC)
                getComposer()->composeWindow();
        }
    }
}
#endif

void SortLastWindow::clientRender(RenderActionBase *action)
{
    UInt32            p;
    UInt32            groupId = getServers().size();
    UInt32            l,b,r,t;
    UInt32            front,back;
    SortLastWindowPtr clusterWindow(this);

    if(getServers().size())
    {
        Connection *srcConnection=
            getNetwork()->getConnection(groupId);
        
        if(getClientWindow()!=NullFC)
        {
            setupNodes(groupId);
/*
            getClientWindow()->activate();
            getClientWindow()->frameInit();
*/
            action->setWindow(getClientWindow());

            if(getComposer() != NullFC)
                getComposer()->startFrame();

            DrawEnv oEnv;
            
            oEnv.setWindow(action->getWindow());

            // render all viewports
            for(p = 0; p < getPort().size() ; ++p)
            {
                ViewportPtr vp=getPort()[p];
                if(getComposer() != NullFC)
                {
                    getComposer()->startViewport(vp);

                    action->setCamera    (vp->getCamera    ());
                    action->setBackground(vp->getBackground());
                    action->setViewport  (vp                 );
                    action->setTravMask  (vp->getTravMask  ());

                    action->apply(vp->getRoot());

                    for(UInt16 i=0; i < vp->getForegrounds().size(); i++)
                    {
                        if(dynamic_cast<StatisticsForegroundPtr>(
                               vp->getForegrounds(i)) == NullFC)
                        {
                            vp->getForegrounds(i)->draw(&oEnv, vp);
                        }
                    }

                    getComposer()->composeViewport(vp);

                    for(UInt16 i=0; i < vp->getForegrounds().size(); i++)
                    {
                        if(dynamic_cast<StatisticsForegroundPtr>(
                               vp->getForegrounds(i)) != NullFC)
                        {
                            vp->getForegrounds(i)->draw(&oEnv, vp);
                        }
                    }

                }
                else
                {
                    vp->render(action);
                }
            }

            // compose whole window
            if(getComposer() != NullFC)
                getComposer()->composeWindow();
        }
    }
}

/*! swap
 */
void SortLastWindow::clientSwap( void )
{
    if(getComposer() == NullFC)
    {
        Connection *connection=getNetwork()->getMainConnection();
        // wait for all servers to finish
        connection->wait();
        // initiate swap
        connection->signal();
    }
    Inherited::clientSwap();
}

/*----------------------- constructors & destructors ----------------------*/

SortLastWindow::SortLastWindow(void) :
    Inherited()
{
}

SortLastWindow::SortLastWindow(const SortLastWindow &source) :
    Inherited(source)
{
}

/*! close composer if there is any
 */
SortLastWindow::~SortLastWindow(void)
{
}

/*----------------------------- class specific ----------------------------*/

void SortLastWindow::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);
}

/*! changed field. Handle new groups
 */

void SortLastWindow::changed(ConstFieldMaskArg whichField, 
                             UInt32            origin,
                             BitVector         details)
{
    if(whichField & GroupNodesFieldMask)
        setGroupsChanged(true);

    Inherited::changed(whichField, origin, details);
}

void SortLastWindow::dump(      UInt32    , 
                          const BitVector ) const
{
    SLOG << "Dump SortLastWindow NI" << std::endl;
}

/*! Collext all drawable nodes
 */

void SortLastWindow::collectDrawables(NodePtrConstArg  node,
                                      DrawableListT   &drawables)
{
    MaterialPtr mat  = NullFC;
    NodeCorePtr core = node->getCore();

    if(core != NullFC)
    {
        // handle material groups
        MaterialGroupPtr matGrp = dynamic_cast<MaterialGroupPtr>(core);

        if(matGrp != NullFC)
        {
            mat = matGrp->getMaterial();

            // ignore transparent material groups
            if(mat != NullFC && mat->isTransparent())
                return;
        }

        // handle geometries
        GeometryPtr geo = dynamic_cast<GeometryPtr>(core);

        if(geo != NullFC)
        {
            mat = geo->getMaterial();
            // ignore transparent materials

            if(mat == NullFC || mat->isTransparent() == false)
            {
                DrawableInfo drawableInfo;

                drawableInfo.node = node;

                // get transformed volume
                node->updateVolume();

                DynamicVolume volume;
                node->getWorldVolume(volume);

                // get min,max
                volume.getBounds(drawableInfo.bMin, drawableInfo.bMax);

                // num of indices
                drawableInfo.load = 0;

                GeoIntegralPropertyPtr indicesPtr = 
                    geo->getIndex(Geometry::PositionsIndex);

                if(indicesPtr != NullFC)
                    drawableInfo.load = indicesPtr->getSize();

                // put to list
                drawables.push_back(drawableInfo);
            }
        }

        // handle poxy groups
        ProxyGroupPtr proxy = dynamic_cast<ProxyGroupPtr>(core);

        if(proxy != NullFC)
        {
            DrawableInfo drawableInfo;

            drawableInfo.node = node;

            // get transformed volume
            node->updateVolume();

            DynamicVolume volume;
            node->getWorldVolume(volume);

            // get min,max
            volume.getBounds(drawableInfo.bMin, drawableInfo.bMax);

            // num of indices
            drawableInfo.load = proxy->getIndices();

            // put to list
            drawables.push_back(drawableInfo);
        }
    }
    
    for(MFNodePtr::const_iterator nI  = node->getMFChildren()->begin();
                                  nI != node->getMFChildren()->end();
                                ++nI)
    {
        collectDrawables(*nI, drawables);
    }
}

/*! Split drawables in as many groups as we have servers 
 *  Try to get clustered nodes
 */

void SortLastWindow::splitDrawables(DrawableListT &src,
                                    UInt32         groups,
                                    bool           cut)
{
    BoxVolume                vol;
//    Real32                   srcLoad=0;
    Real32                   dst1Load = 0;
    Real32                   dst2Load = 0;
    DrawableListT::iterator  dI;
    UInt32                   dIFront  = 0;
    UInt32                   dIBack   = 0;
    UInt32                   axis     = 0;
    Vec3f                    size;
    DrawableListT            dst1;
    DrawableListT            dst2;
    UInt32                   groups1  = 0;
    UInt32                   groups2  = 0;

    // no group
    if(groups == 0)
        return;

    // only one group
    if(groups == 1)
    {
        editGroupLengths().push_back(src.size());

        for(dI = src.begin() ; dI != src.end() ; ++dI)
        {
            pushToGroupNodes(dI->node);
//            srcLoad+=dI->load;
        }
//        printf("load:%f\n",srcLoad);
        return;
    }

    groups1 = groups / 2;
    groups2 = groups - groups1;

    // collect all load and get summed volume
    for(dI = src.begin() ; dI != src.end() ; ++dI)
    {
        vol.extendBy(dI->bMin);
        vol.extendBy(dI->bMax);
    }

    // get longes axis
    vol.getSize(size);

    if(size[0] > size[1])
    {
        if(size[0] > size[2])
            axis=0;
        else
            axis=2;
    }
    else
    {
        if(size[1] > size[2])
            axis=1;
        else
            axis=2;
    }

    // sort by volume
    if(axis == 0)
    {
        std::sort(src.begin(),src.end(), DrawableInfo::MaxXOrder());
    }
    else
    {
        if(axis == 1)
            std::sort(src.begin(),src.end(), DrawableInfo::MaxYOrder());
        else
            std::sort(src.begin(),src.end(), DrawableInfo::MaxZOrder());
    }

    // split group
    if(src.size())
    {
        dIFront  = 0;
        dIBack   = src.size()-1;
        do
        {
//            printf("f %d  b %d\n",dIFront,dIBack);
            if(dst2Load < dst1Load)
            {
                dst2.push_back(src[dIBack]);

                dst2Load += src[dIBack].load*groups/(float)groups2;

                dIBack--;
            }
            else
            {
                dst1.push_back(src[dIFront]);

                dst1Load += src[dIFront].load*groups/(float)groups1;

                dIFront++;
            }
        } while(dIFront <= dIBack);
    }        
    // recourse
    splitDrawables(dst1, groups1, cut);
    splitDrawables(dst2, groups2, cut);
}

void SortLastWindow::setupNodes(UInt32 groupId)
{
    UInt32  v             = 0;
    NodePtr root          = NullFC;
    UInt32  p             = 0;
    UInt32  nI            = 0;
    UInt32  gnI           = 0;
    UInt32  gI            = 0;
    UInt32  group         = 0;
    UInt32  groupCount    = 0;
    UInt32  usableServers = getServers().size();

    if(!getGroupsChanged())
        return;

    // client and no client rendering 
    if(getServers().size() == groupId &&
       (getComposer() == NullFC ||
        !getComposer()->getClientRendering()))
    {
        for(nI = 0 ; nI < getGroupNodes().size() ; ++nI)
        {
            if(getGroupNodes()[nI]->getTravMask())
            {
                getGroupNodes()[nI]->setTravMask(0);
                getGroupNodes()[nI]->invalidateVolume();
            }
        }

        return;
    }

    if(getComposer() != NullFC)
        usableServers = getComposer()->getUsableServers();

    // server but not usable, then invalidate all nodes
    if((getServers().size() > groupId && usableServers <= groupId))
    {
        for(v = 0; v < getPort().size(); ++v)
        {
            root = getPort(v)->getRoot();

            root->setTravMask(0);
            root->invalidateVolume();
        }

        setGroupsChanged(false);
        return;
    }        

    groupCount = usableServers;

    if(getComposer() != NullFC) 
    {
        groupCount = getComposer()->getUsableServers();

        if(getComposer()->getClientRendering())
        {
            groupCount++;
        }
    }

    if(getServers().size() == groupId)
        groupId = usableServers;

    // setup nodes
    for(nI = 0,gnI = 0,gI = 0,group = 0 ; nI < getGroupNodes().size() ; ++nI)
    {
        while(nI >= gnI)
        {
            gnI += getGroupLengths()[group]; 
            gI++;
            group = gI % groupCount;
        }
        if(group == groupId)
        {
            if(getGroupNodes()[nI]->getTravMask() != 
               TypeTraits<UInt32>::getMax())
            {
                getGroupNodes()[nI]->setTravMask(TypeTraits<UInt32>::getMax());
                getGroupNodes()[nI]->invalidateVolume();
            }
        }
        else
        {
            if(getGroupNodes()[nI]->getTravMask())
            {
                getGroupNodes()[nI]->setTravMask(0);
                getGroupNodes()[nI]->invalidateVolume();
            }
        }

        getGroupNodes()[nI]->updateVolume();
    }

    setGroupsChanged(false);
}

/*------------------------------------------------------------------------*/
/*                           constructor / destructor                     */

/*! constructor
 */
SortLastWindow::DrawableInfo::DrawableInfo():
    node()
{
}

/*! copy constructor 
 */

SortLastWindow::DrawableInfo::DrawableInfo(const DrawableInfo &source) :
    node(source.node),
    bMin(source.bMin),
    bMax(source.bMax),
    load(source.load)
{
}

/*! assignment
 */
const SortLastWindow::DrawableInfo &SortLastWindow::DrawableInfo::operator =(
    const DrawableInfo &source)
{
    node = source.node;
    bMin = source.bMin;
    bMax = source.bMax;
    load = source.load;

    return *this;
}

/*! compare max x in bounding volume
 */

bool SortLastWindow::DrawableInfo::MaxXOrder::operator()
    (const DrawableInfo &a, const DrawableInfo &b)
{
    return a.bMax[0] < b.bMax[0];
}

/*! compare max y in bounding volume
 */

bool SortLastWindow::DrawableInfo::MaxYOrder::operator()
    (const DrawableInfo &a, const DrawableInfo &b)
{
    return a.bMax[1] < b.bMax[1];
}
        
/*! compare max z in bounding volume
 */

bool SortLastWindow::DrawableInfo::MaxZOrder::operator()
    (const DrawableInfo &a, const DrawableInfo &b)
{
    return a.bMax[2] < b.bMax[2];
}


