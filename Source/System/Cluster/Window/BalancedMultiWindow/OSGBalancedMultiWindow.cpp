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

#include "OSGConfig.h"
#include "OSGBalancedMultiWindow.h"

#include "OSGClusterNetwork.h"
#include "OSGTransform.h"
#include "OSGPerspectiveCamera.h"
#include "OSGSolidBackground.h"
#include "OSGMatrixUtility.h"
#include "OSGRenderAction.h"

#include "OSGChunkMaterial.h"
#include "OSGProxyGroup.h"
#include "OSGGeometry.h"
#include "OSGSimpleSHLChunk.h"
#include "OSGTileCameraDecorator.h"

#include "OSGGLU.h"

OSG_BEGIN_NAMESPACE

/*! missing in matrix class
 */
static void multFullMatrixPnt4 (Matrix m, Pnt4f &p)
{
    Pnt4f tmp; 
    
    tmp[0] = m[0][0]*p[0] + m[1][0]*p[1] + m[2][0]*p[2] + m[3][0]*p[3];
    tmp[1] = m[0][1]*p[0] + m[1][1]*p[1] + m[2][1]*p[2] + m[3][1]*p[3];
    tmp[2] = m[0][2]*p[0] + m[1][2]*p[1] + m[2][2]*p[2] + m[3][2]*p[3];
    tmp[3] = m[0][3]*p[0] + m[1][3]*p[1] + m[2][3]*p[2] + m[3][3]*p[3];
    
    p[0] = tmp[0];
    p[1] = tmp[1];
    p[2] = tmp[2];
    p[3] = tmp[3];
}

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::BalancedMultiWindow
Load balanced sort first rendering for multiple windows
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void BalancedMultiWindow::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

BalancedMultiWindow::BalancedMultiWindow(void) :
     Inherited        (    ),
    _rebuildLoadGroups(true)
{
}

BalancedMultiWindow::BalancedMultiWindow(const BalancedMultiWindow &source) :
     Inherited        (source),
    _rebuildLoadGroups(true  )
{
}

BalancedMultiWindow::~BalancedMultiWindow(void)
{
}

void BalancedMultiWindow::resolveLinks(void)
{
    for(UInt32 i = 0; i < _cluster.rootNodes.size(); ++i)
    {
        _cluster.rootNodes[i] = NULL;
    }

    for(UInt32 i = 0; i < _cluster.loadGroups.size(); ++i)
    {
        _cluster.loadGroups[i].root = NULL;
        _cluster.loadGroups[i].node = NULL;
    }

    for(UInt32 i = 0; i < _cluster.servers.size(); ++i)
    {
        for(UInt32 j = 0; j < _cluster.servers[i].viewports.size(); ++j)
        {
            _cluster.servers[i].viewports[j].serverPort = NULL;
            _cluster.servers[i].viewports[j].root       = NULL;
        }
    }
}

/*----------------------------- class specific ----------------------------*/

void BalancedMultiWindow::changed(ConstFieldMaskArg whichField, 
                                  UInt32            origin,
                                  BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void BalancedMultiWindow::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump BalancedMultiWindow NI" << std::endl;
}


void BalancedMultiWindow::serverInit(Window *pServerWindow, UInt32 id)
{
    Inherited::serverInit(pServerWindow,id);
}

void BalancedMultiWindow::serverRender(Window           *pServerWindow,
                                       UInt32            id,
                                       RenderActionBase *action)
{
    if(!getBalance())
    {
        _rebuildLoadGroups = true;

        Inherited::serverRender(pServerWindow,id,action);

        return;
    }

    pServerWindow->activate ();
    pServerWindow->frameInit();

    // clear background
    glDisable(GL_SCISSOR_TEST);
    glViewport(0,0,
               pServerWindow->getWidth(), 
               pServerWindow->getHeight());
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT);

    // initialize
    if(_cluster.servers.size() == 0)
    {
        // reset server list
        _cluster.servers.resize(getMFServers()->size() + 1);
        _cluster.servers[id].id = id;

        getNetwork()->connectAllGroupToPoint(id,"StreamSock");

        // do not buffer any data
        for(UInt32 i=0 ; i <= getMFServers()->size() ; ++i)
            getNetwork()->getConnection(i)->forceDirectIO();

        _preloadCache = true;
    }

    UInt32 count,vp,vpcount,wpcount;
    Server &server = _cluster.servers[id];
    std::vector<WorkPackage>::iterator wI;
    std::vector<Area>::iterator aI;
    std::vector<Tile>::iterator tI;

    // set server window
    server.window = pServerWindow;

    // create load groups for all root nodes
    createLoadGroups();

    // preload texture and dlist cache
    preloadCache(pServerWindow,action);

    _loadTime = -getSystemTime();

    // collect visible viewports
    collectVisibleViewports(server);

    // create bboxes
    createBBoxes(server);

    _loadTime += getSystemTime();

    // send bboxes of all viewports to client
    Connection *conn = getNetwork()->getMainConnection();
    vpcount = server.viewports.size();
    conn->putValue(id);
    conn->putValue(vpcount);
    for(vp=0 ; vp<vpcount ; ++vp)
    {
        VPort &port = server.viewports[vp];
        conn->putValue(port.id);
        conn->putValue(port.load);
        conn->putValues(port.loadCenter,2);
        conn->putValues(port.rect,4);
        count = port.bboxes.size();
        conn->putValue(count);
        if(count)
            conn->put(&port.bboxes[0],count*sizeof(BBox));
    }
    conn->flush();
    
    // read workpackages
    conn->selectChannel();
    conn->getValue(wpcount);
    _cluster.workpackages.resize(wpcount);
    if(wpcount)
        conn->get(&_cluster.workpackages[0],wpcount*sizeof(WorkPackage));

    _cluster.areas.clear();
    drawSendAndRecv(pServerWindow,action,id);

    // send statistics
    if(getShowBalancing())
    {
        conn = getNetwork()->getMainConnection();
        conn->putValue(_triCount);
        conn->putValue(_drawTime);
        conn->putValue(_pixelTime);
        conn->putValue(_loadTime);
        conn->putValue(_netTime);
        conn->flush();
    }

#if 0
    // render bounding boxes
    glDisable(GL_SCISSOR_TEST);
    glViewport(0,0,
               pServerWindow->getWidth(),
               pServerWindow->getHeight());
    glPushMatrix();
      glLoadIdentity();
      glMatrixMode(GL_PROJECTION);
      glPushMatrix();
        glLoadIdentity();
        glOrtho(0, pServerWindow->getWidth(),
                0, pServerWindow->getHeight(), -1, 1);

        for(UInt32 v=0; v<_cluster.servers[id].viewports.size() ; ++v)
        {
            for(UInt32 b=0; b<_cluster.servers[id].viewports[v].bboxes.size() ; ++b)
            {
                BBox &bbox = _cluster.servers[id].viewports[v].bboxes[b];
                glBegin(GL_LINE_LOOP);
                glColor3f(1, 1, 0);
                glVertex2f(bbox.rect[LEFT],bbox.rect[BOTTOM]);
                glVertex2f(bbox.rect[RIGHT],bbox.rect[BOTTOM]);
                glVertex2f(bbox.rect[RIGHT],bbox.rect[TOP]);
                glVertex2f(bbox.rect[LEFT],bbox.rect[TOP]);
                glEnd();
            }
        }

      glPopMatrix();
      glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
#endif
}

void BalancedMultiWindow::clientInit(void)
{
    Inherited::clientInit();
}

void BalancedMultiWindow::clientPreSync(void)
{
    if(getHServers() * getVServers() == 0 && getClientWindow() != NULL)
    {
        if(getWidth () != getClientWindow()->getWidth () ||
           getHeight() != getClientWindow()->getHeight()) 
        {
            setWidth (getClientWindow()->getWidth ());
            setHeight(getClientWindow()->getHeight());
        }
    }
    Inherited::clientPreSync();
}

void BalancedMultiWindow::clientRender(RenderActionBase *action)
{
    if(!getBalance())
    {
        _rebuildLoadGroups = true;
        Inherited::clientRender(action);
        return;
    }
    Connection::Channel channel;
    UInt32 bbcount,id,vp,vpcount,wpcount;
    double frameTime = -getSystemTime();

    if(_cluster.servers.size() == 0)
    {
        // reset server list
        _cluster.servers.resize(getMFServers()->size()+1);

        for(UInt32 id=0 ; id < getMFServers()->size()+1 ; ++id)
            _cluster.servers[id].id = id;

        getNetwork()->connectAllGroupToPoint(getMFServers()->size(),
                                             "StreamSock");

        // do not buffer any data
        for(UInt32 i=0 ; i <= getMFServers()->size() ; ++i)
            getNetwork()->getConnection(i)->forceDirectIO();

        _preloadCache = true;
    }

    // create load groups for all root nodes
    createLoadGroups();

    // local visualization
    _loadTime = 0;
    if(getHServers() * getVServers() == 0 &&
        getClientWindow() != NULL)
    {
        _loadTime = -getSystemTime();

        Server &server = _cluster.servers[getMFServers()->size()];

        // set client window
        server.window = getClientWindow();

        // collect visible viewports
        collectVisibleViewports(server);

        // create bboxes
        createBBoxes(server);
        _loadTime += getSystemTime();

        for(vp=0 ; vp < server.viewports.size() ; ++vp)
            server.load += server.viewports[vp].load;

        // preload texture and dlist cache
        preloadCache(getClientWindow(),action);
    }

    _netTime = 0;
    // read bboxes from all servers
    GroupConnection *conn = getNetwork()->getMainGroupConnection();
    while(conn->getSelectionCount())
    {
        channel = conn->selectChannel();
        conn->subSelection(channel);
        conn->getValue(id);
        conn->getValue(vpcount);
        Server &server = _cluster.servers[id];
        server.viewports.resize(vpcount);
        server.load = 0;
//        printf("Server %d\n",id);
        for(vp=0 ; vp < vpcount ; ++vp)
        {
            VPort &port = server.viewports[vp];
            port.serverId = id;
            conn->getValue(port.id);
            conn->getValue(port.load);
            conn->getValues(port.loadCenter,2);
            conn->getValues(port.rect,4);
            conn->getValue(bbcount);
            port.bboxes.resize(bbcount);
/*
            printf("Port %d %f\n",port.id,port.load);
            printf("%d %d %d %d\n",
                   port.rect[0],
                   port.rect[1],
                   port.rect[2],
                   port.rect[3]);
*/
            if(bbcount)
                conn->get(&port.bboxes[0],bbcount*sizeof(BBox));
            server.load += port.load;
        }
    }
    conn->resetSelection();
    // do load balancing
    _balanceTime = -getSystemTime();
    balanceServer();
    _balanceTime += getSystemTime();
    // send work packages
    wpcount = _cluster.workpackages.size();
    conn->putValue(wpcount);
    conn->put(&_cluster.workpackages[0],wpcount*sizeof(WorkPackage));
    conn->flush();
    // client rendering ?
//    if(getHServers() * getVServers() == 0)

    drawSendAndRecv(getClientWindow(),action,getMFServers()->size());

    // do local rendering if not switched off and no parallel 
    // rendering to local window
    if(getHServers() * getVServers() != 0 &&
       getClientWindow() != NULL)
    {
        getClientWindow()->renderAllViewports( action );
    }

    // statistics
    UInt32 triCount;
    Real64 drawTime;
    Real64 pixelTime;
    Real64 loadTime;
    Real64 netTime;
    if(getShowBalancing())
    {
        printf("Statistics:\n");
        conn = getNetwork()->getMainGroupConnection();
        while(conn->getSelectionCount())
        {
            channel = conn->selectChannel();
            conn->subSelection(channel);
            conn->getValue(triCount);
            conn->getValue(drawTime);
            conn->getValue(pixelTime);
            conn->getValue(loadTime);
            conn->getValue(netTime);
            printf("Srv %4d L:%2.6lf T:%10d D:%2.6lf P:%2.6lf N:%2.6lf\n",channel,loadTime,triCount,drawTime,pixelTime,netTime);
        }
        conn->resetSelection();
        frameTime += getSystemTime();
        printf("Cli %4d L:%2.6lf T:%10d D:%2.6lf P:%2.6lf N:%2.6lf B:%2.6lf F:%2.6lf\n",
               getMFServers()->size(),
               _loadTime,
               _triCount,
               _drawTime,
               _pixelTime,
               _netTime,
               _balanceTime,
               frameTime);
        printf("end\n");
    }    
#if 0
    for(unsigned int p=0;p<_cluster.workpackages.size() ; ++p) {
        printf("from %d to %d    %d %d %d %d\n",
               _cluster.workpackages[p].drawServer,
               _cluster.workpackages[p].sendToServer,
               _cluster.workpackages[p].rect[0],
               _cluster.workpackages[p].rect[1],
               _cluster.workpackages[p].rect[2],
               _cluster.workpackages[p].rect[3]);
    }
#endif
}


/*! get number of tiles for the given area
 */
UInt32 BalancedMultiWindow::calcTileCount(Int32 const (&rect)[4])
{
    UInt32 x = (rect[RIGHT] - rect[LEFT  ]) / MW_TILE_SIZE + 1;
    UInt32 y = (rect[TOP  ] - rect[BOTTOM]) / MW_TILE_SIZE + 1;
    return x*y;
}

/*! project group and get bounding box
 */
bool BalancedMultiWindow::calculateProjectedBBox(VPort &port,
                                                 LoadGroup &group,
                                                 BBox &bbox,
                                                 Matrix &proj)
{
    Pnt3f vol[2];
    Pnt3f pnt3;
    Real32 minx=0,miny=0;
    Real32 maxx=0,maxy=0;

    Int32 width = port.serverPort->getPixelWidth();
    Int32 height = port.serverPort->getPixelHeight();
#if 1
    Matrix trans = group.node->getToWorld();
    trans.multLeft(proj);

    Pnt4f pnt[8];
    Int32 cl=0, cb=0, cr=0, ct=0, cn=0, cf=0;
    Int32 bit = 1;

    // get local volume
    BoxVolume volume = group.node->getVolume();
#else
    Matrix trans = proj;

    Pnt4f pnt[8];
    Int32 cl=0, cb=0, cr=0, ct=0, cn=0, cf=0;
    Int32 bit = 1;

    // get local volume
    BoxVolume volume = group.node->getVolume();
    volume.transform(group.node->getToWorld());

#endif
    volume.getBounds (vol[0], vol[1]);

    for(int i=0;i<8;++i)
    {
        pnt[i] = Pnt4f (vol[ (i   )&1 ][0], 
                        vol[ (i>>1)&1 ][1],
                        vol[ (i>>2)&1 ][2], 
                        1.0);

        multFullMatrixPnt4 (trans, pnt[i]);

        // fill bit fields with clipping data
        if (pnt[i][0] >= -pnt[i][3]) cl += bit;
        if (pnt[i][0] <=  pnt[i][3]) cr += bit;
        if (pnt[i][1] >= -pnt[i][3]) cb += bit;
        if (pnt[i][1] <=  pnt[i][3]) ct += bit;
        if (pnt[i][2] >= -pnt[i][3]) cn += bit;
        if (pnt[i][2] <=  pnt[i][3]) cf += bit;

        bit *= 2;
    }

    // whole bounding box clipped
    if ((cl == 0) || (cb == 0) || (cr == 0) ||
        (ct == 0) || (cn == 0) || (cf == 0)) 
    {
        return false;
    }

    // bounding box on near plane !!!
    if (cn < 255) 
    {
        bit = 1;

        for (int i = 0; i < 8; ++i)
        {
            // point behind nearplane? -> point to corner
            if ((cn & bit) == 0)
            {
                pnt[i][0] = pnt[i][0] < 0 ? -1 : 1;
                pnt[i][1] = pnt[i][1] < 0 ? -1 : 1;
                pnt[i][2] = -1;
                pnt[i][3] = 1;
            }

            bit *= 2;
        }
    }

    for (int i = 0; i < 8; ++i)
    {
        // switch to normal coordinate system
        pnt[i][0] /= pnt[i][3];
        pnt[i][1] /= pnt[i][3];

        // scale to window coordinates
        pnt[i][0] = (pnt[i][0] + 1) * width / 2.0;
        pnt[i][1] = (pnt[i][1] + 1) * height / 2.0;

        if (i > 0)
        {
            if (minx > pnt[i][0]) minx = pnt[i][0];
            if (miny > pnt[i][1]) miny = pnt[i][1];
            if (maxx < pnt[i][0]) maxx = pnt[i][0];
            if (maxy < pnt[i][1]) maxy = pnt[i][1];
        }
        else
        {
            maxx = minx = pnt[i][0];
            maxy = miny = pnt[i][1];
        }                    
    }
/*
    bbox.rect[LEFT]   = (Int32)osgfloor(minx + port.serverPort->getPixelLeft ());
    bbox.rect[RIGHT]  = (Int32)osgceil (maxx + port.serverPort->getPixelLeft ());
    bbox.rect[BOTTOM] = (Int32)osgfloor(miny + port.serverPort->getPixelBottom ());
    bbox.rect[TOP]    = (Int32)osgceil (maxy + port.serverPort->getPixelBottom ());
*/
    bbox.rect[LEFT]   = Int32(minx + port.serverPort->getPixelLeft ());
    bbox.rect[RIGHT]  = Int32(maxx + port.serverPort->getPixelLeft ());
    bbox.rect[BOTTOM] = Int32(miny + port.serverPort->getPixelBottom ());
    bbox.rect[TOP]    = Int32(maxy + port.serverPort->getPixelBottom ());

#if 0
    // draw bounding boxes
    glViewport(0,0,
               port.serverPort->getParent()->getWidth(),
               port.serverPort->getParent()->getHeight());
    glPushMatrix();
      glLoadIdentity();
      glMatrixMode(GL_PROJECTION);
      glPushMatrix();
        glLoadIdentity();
        glOrtho(0, port.serverPort->getParent()->getWidth(),
                0, port.serverPort->getParent()->getHeight(), -1, 1);
        glBegin(GL_LINE_LOOP);
        glColor3f(1, 1, 0);
        glVertex2f(bbox.rect[LEFT],bbox.rect[BOTTOM]);
        glVertex2f(bbox.rect[RIGHT],bbox.rect[BOTTOM]);
        glVertex2f(bbox.rect[RIGHT],bbox.rect[TOP]);
        glVertex2f(bbox.rect[LEFT],bbox.rect[TOP]);
        glEnd();
      glPopMatrix();
      glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
#endif
    return true;
}



/*! Create load groups for all root nodes. Each viewport can have its
    own root node. Seach all viewports for all different root nodes
    and collect load in each tree;
 */
void BalancedMultiWindow::createLoadGroups(void)
{
    Viewport *viewport;
    Node     *root;
    UInt32    v;

    if(!_rebuildLoadGroups)
    {
        // only if something changed
        ChangeList *changeList = OSG::Thread::getCurrentChangeList();

        if(changeList->getNumCreated() == 0)
        {
            _rebuildLoadGroups = false;
        }
        else
        {
            _rebuildLoadGroups = true;
        }
    }

    if(!_rebuildLoadGroups)
        return;

    _preloadCache = true;

    // reset all;
    _cluster.rootNodes.clear();
    _cluster.loadGroups.clear();
    // loop over all viewports
    for(v = 0 ; v  < getMFPort()->size() ; ++v )
    {
        viewport = getPort(v);
        root = viewport->getRoot();

#ifdef __sun
        UInt32 uiCount;

        std::count(_cluster.rootNodes.begin(),
                   _cluster.rootNodes.end(),
                   root,
                   uiCount);

        if(uiCount)
            continue;
#else
        // ignore multiple viewports with same root 
        if(std::count(_cluster.rootNodes.begin(),
                      _cluster.rootNodes.end(),
                      root))
            continue;
#endif
        _cluster.rootNodes.push_back(root);
        // recousiveley collect groups
        collectLoadGroups(root,root);
    }
    _rebuildLoadGroups = false;
}


/*! collect load for a subtree and write it to the group list. This method
    is called for the client and the server. The palancing expects that
    the loadGroup vector is equal on client and server
 */
void BalancedMultiWindow::collectLoadGroups(Node *node, Node *root)
{
    LoadGroup load;
#if 0    
    UInt32 lastSize;
#endif    

    MFUnrecChildNodePtr::const_iterator child;

    // ignore null node
    if(node == NULL)
        return;
    
    NodeCore *core = node->getCore();
    if(core != NULL)
    {
        Geometry      *geo   = NULL;
        ProxyGroup    *proxy = NULL;

        load.root = root;
        load.constant = 0;
        load.pixel = 0;
        load.ratio = 0;
        load.node = node;

        // handle poxy groups
        proxy = dynamic_cast<ProxyGroup *>(core);
        if(proxy != NULL)
        {
            load.constant = proxy->getIndices() / MW_INDICES_PER_SEC;
            load.ratio    = proxy->getIndices() / MW_VISIBLE_INDICES_PER_SEC;
        }
        geo = dynamic_cast<Geometry *>(core);
        if(geo != NULL)
        {
            GeoIntegralProperty *indices = 
                geo->getIndex(Geometry::PositionsIndex);

            GeoVectorProperty *positions = geo->getPositions();

            ChunkMaterial *mat = 
                dynamic_cast<ChunkMaterial *> (geo->getMaterial ());

            // constant geometry setup cost
            if ((indices != NULL)) 
            {
                load.constant = indices->getSize() / MW_INDICES_PER_SEC;
                load.ratio    = indices->getSize() / MW_VISIBLE_INDICES_PER_SEC;
            }
            else
                if(positions != NULL) 
                {
                    load.constant = positions->getSize() / MW_INDICES_PER_SEC;
                    load.ratio    = positions->getSize() / MW_VISIBLE_INDICES_PER_SEC;
                }
            // pixel cost for shaders
            if (mat != NULL && mat->find (SimpleSHLChunk::getClassType ()) != NULL)
                load.pixel =  1.0f / Real32(MW_SHADED_PIXEL_PER_SEC);
            else
                load.pixel = 1.0f / Real32(MW_PIXEL_PER_SEC);
//                load.pixel = 0;
        }
        if(load.pixel > 0 || load.constant > 0)
            _cluster.loadGroups.push_back(load);
    }

#if 0    
    lastSize = _cluster.loadGroups.size();
#endif
    // loop over all child nodes
    for(child = node->getMFChildren()->begin() ;
        child != node->getMFChildren()->end() ;
        ++child)
    {
        collectLoadGroups(*child,root);
    }
#if 0
    if(lastSize + 1 < _cluster.loadGroups.size())
    {
        load.root = root;
        load.constant = 0;
        load.pixel = 0;
        load.node = node;
        // calculate summed group
        for(l = lastSize ; l < _cluster.loadGroups.size() ; ++l)
        {
            load.constant     += _cluster.loadGroups[l].constant;
            load.pixel        += _cluster.loadGroups[l].pixel;
            load.root          = root;
        }
        // merge small grops
        if(load.constant < 500.0 / MW_INDICES_PER_SEC &&
           load.pixel <= 1.0 / Real32(MW_PIXEL_PER_SEC))
        {
            _cluster.loadGroups.resize(lastSize);
            _cluster.loadGroups.push_back(load);
        }
    }
#endif
}


/*! collect visible viewports
 */
void BalancedMultiWindow::collectVisibleViewports(Server &server)
{
    UInt32 cv,sv=0;

    for(cv = 0 ; cv < getMFPort()->size() ; cv++)
    {
        if(server.viewports.size() <= sv)
            server.viewports.resize(sv+1); 

        VPort &port = server.viewports[sv];

        port.id = cv;
        port.serverId = server.id;
        port.root = getPort(cv)->getRoot();
        if(calculateServerPort(port,port.rect))
            sv++;
    }

    server.viewports.resize(sv); 
}


/*! calculate server port for a given VPort. Retruns true, if viewport
    is visible
 */
bool BalancedMultiWindow::calculateServerPort(VPort &port,
                                              Int32 const (&rect)[4])
{
    Int32 cleft,cright,ctop,cbottom;
    Viewport *serverPort, *clientPort;
    TileCameraDecoratorUnrecPtr deco;
//    UInt32 cv,sv=0;

    // calculate visible area;
    UInt32 row;
    UInt32 column;
    UInt32 width;
    UInt32 height;
    UInt32 rows,cols;

    if(getHServers() * getVServers() == 0)
    {
        if(port.serverId != getMFServers()->size())
            return false;
        // balanced client rendering
        rows = 1;
        cols = 1;
        row = 0;
        column = 0;
    }
    else
    {
        rows = getVServers();
        cols = getHServers();
        row = port.serverId/cols;
        column = port.serverId%cols;
    }
    width = getWidth() / cols;
    height = getHeight() / rows;

    Int32 left   = column * width  - column * getXOverlap();
    Int32 bottom = row    * height - row    * getYOverlap();
    Int32 right  = left   + width  - 1;
    Int32 top    = bottom + height - 1;
    Real32 scaleCWidth  = ((width - getXOverlap()) * (cols - 1) + width) / 
        Real32(getWidth());
    Real32 scaleCHeight = ((height - getYOverlap())* (rows - 1) + height)/ 
        Real32(getHeight());
    
    clientPort = getPort(port.id);
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
        return false;
    }
    // visible rectangle on server window
    port.rect[LEFT]   = osgMax(cleft  ,left  ) - left;
    port.rect[BOTTOM] = osgMax(cbottom,bottom) - bottom;
    port.rect[RIGHT]  = osgMin(cright ,right ) - left;
    port.rect[TOP]    = osgMin(ctop   ,top   ) - bottom;

    // verify if the viewport type has changed
    if(port.serverPort != NULL)
    {
        if(port.serverPort->getType().getId() != getPort(port.id)->getType().getId())
        {
            // this must not happen very frequently, otherwise, memory leak may occur
            //subRefX(port.serverPort->getCamera());
            //subRefX(port.serverPort);
            port.serverPort = NULL;
        }

    }

    // create port and deco for visualization, only if necessary
    if(port.serverPort == NULL)
    {
        ViewportUnrecPtr pTmpPort = 
            dynamic_pointer_cast<Viewport>(getPort(port.id)->shallowCopy());

        port.serverPort = pTmpPort;

        deco = TileCameraDecorator::create();
        port.serverPort->setCamera(deco);
    }
    else
    {
        deco = 
            dynamic_cast<TileCameraDecorator *>(port.serverPort->getCamera());
    }
    // decorate client camera
    deco->setDecoratee( clientPort->getCamera() );

    serverPort = port.serverPort;
    
    // duplicate values
    serverPort->setSize(Real32(rect[LEFT]),
                        Real32(rect[BOTTOM]),
                        Real32(rect[RIGHT]),
                        Real32(rect[TOP]));
    // use pixel even if pixel = 1
    if(serverPort->getLeft() == 1.0)
        serverPort->setLeft(1.0001f);
    if(serverPort->getRight() == 1.0)
        serverPort->setRight(1.0001f);
    if(serverPort->getTop() == 1.0)
        serverPort->setTop(1.0001f);
    if(serverPort->getBottom() == 1.0)
        serverPort->setBottom(1.0001f);
    serverPort->setRoot      ( clientPort->getRoot()       );
    serverPort->setBackground( clientPort->getBackground() );
    serverPort->assignForegrounds(*(clientPort->getMFForegrounds()) );
    serverPort->setTravMask  ( clientPort->getTravMask()   );
    
    // calculate tile parameters
#if 0
    deco->setFullWidth ( cright-cleft);
    deco->setFullHeight( ctop-cbottom);
    deco->setSize( ( rect[LEFT]+left-cleft       ) / (float)( cright-cleft ),
                   ( rect[BOTTOM]+bottom-cbottom ) / (float)( ctop-cbottom ),
                   ( rect[RIGHT]+left-cleft      ) / (float)( cright-cleft ),
                   ( rect[TOP]+bottom-cbottom    ) / (float)( ctop-cbottom ) );
#else
    deco->setFullWidth ( cright-cleft + 1 );
    deco->setFullHeight( ctop-cbottom + 1 );
    deco->setSize( ( -(rect[LEFT]+left-cleft)       ),
                   ( -(rect[BOTTOM]+bottom-cbottom) ),
                   ( -(rect[RIGHT]+left-cleft+1)    ),
                   ( -(rect[TOP]+bottom-cbottom+1)  ) );
#endif
    deco->setDecoratee( clientPort->getCamera() );
    
    return true;
}



/*! Ccreate view dependent bboxes for all visible viewports
 */
void BalancedMultiWindow::createBBoxes(Server &server)
{
    std::vector<VPort>::iterator vI;
    UInt32 gI;
    server.load = 0;
    UInt32 bbcount=0;
    Real32 load,sumLoad;
    Int32  bbmin[2];
    Int32  bbmax[2];

    for(vI = server.viewports.begin() ; vI != server.viewports.end() ; ++vI)
    {
        bbmin[0] = vI->rect[RIGHT];
        bbmin[1] = vI->rect[TOP];
        bbmax[0] = vI->rect[LEFT];
        bbmax[1] = vI->rect[BOTTOM];

        // add port to get pixel values
        server.window->addPort(vI->serverPort);

        // projection matrix
        Matrix viewing,projection,projectionTrans;
        Int32 width = vI->serverPort->getPixelWidth();
        Int32 height = vI->serverPort->getPixelHeight();
        vI->serverPort->getCamera()->getViewing (viewing, width, height);
        vI->serverPort->getCamera()->getProjection (projection, width, height);
        vI->serverPort->getCamera()->getProjectionTranslation( projectionTrans, width, height);
        projection.mult(projectionTrans);
        projection.mult(viewing);

        sumLoad = 0;
        vI->loadCenter[0] = vI->loadCenter[1] = 0;
        for(gI = 0 ; gI != _cluster.loadGroups.size() ; ++gI)
        {
            LoadGroup &group = _cluster.loadGroups[gI];
            if(group.root == vI->root)
            {
                if(vI->bboxes.size() <= bbcount)
                    vI->bboxes.resize(bbcount+1);
                // new group
                BBox &bbox = vI->bboxes[bbcount];
                bbox.groupId = gI;
                // get bbox
                if(calculateProjectedBBox(*vI,group,bbox,projection))
                {
                    // calculate load
                    load = getVisibleLoad(vI->rect,bbox);
                    sumLoad += load;
                    vI->loadCenter[0] += load*(bbox.rect[0]+bbox.rect[2])/2;
                    vI->loadCenter[1] += load*(bbox.rect[1]+bbox.rect[3])/2;
                    bbcount++;
                    if(bbox.rect[LEFT] < bbmin[0])
                        bbmin[0] = bbox.rect[LEFT];
                    if(bbox.rect[BOTTOM] < bbmin[1])
                        bbmin[1] = bbox.rect[BOTTOM];
                    if(bbox.rect[RIGHT] > bbmax[0])
                        bbmax[0] = bbox.rect[RIGHT];
                    if(bbox.rect[TOP] > bbmax[1])
                        bbmax[1] = bbox.rect[TOP];
                }
            }
        }
        vI->load = sumLoad;
        vI->bboxes.resize(bbcount);
        if(sumLoad)
        {
            vI->loadCenter[0] /= sumLoad;
            vI->loadCenter[1] /= sumLoad;
        }

        if(bbmin[0] <= bbmax[0])
        {
            if(bbmin[0] > vI->rect[LEFT])
                vI->rect[LEFT] = bbmin[0];
            if(bbmax[0] < vI->rect[RIGHT])
                vI->rect[RIGHT] = bbmax[0];
        } 
        if(bbmin[1] <= bbmax[1])
        {
            if(bbmin[1] > vI->rect[BOTTOM])
                vI->rect[BOTTOM] = bbmin[1];
            if(bbmax[1] < vI->rect[TOP])
                vI->rect[TOP] = bbmax[1];
        } 

        // sub port
        server.window->subPortByObj(vI->serverPort);
    }
}

/*! do load balancing
 */
void BalancedMultiWindow::balanceServer(void)
{
    Worker wo;
    Int32 low,heigh;
    UInt32 serverId;
    UInt32 vI;
    Real32 tooMuch,medLoad,load=0;
    std::vector<Server*> server;
    std::vector<Worker>  worker;
    ServerComp comp;
    Real32 tolerance;
    WorkPackage wp;
    UInt32 count;

    if(getHServers()*getVServers() == 0)
        count = getMFServers()->size() + 1;
    else
        count = getMFServers()->size();

    // clear work packages
    _cluster.workpackages.clear();
    // min 2 servers
/*
    if(count < 2)
        return;
*/
    // collect and sort server load
    for(serverId = 0 ; serverId < count ; ++serverId)
    {
//        printf("id %d load %f\n",serverId,_cluster.servers[serverId].load);
        server.push_back(&_cluster.servers[serverId]);
        load += _cluster.servers[serverId].load;
    }
    // sort
    std::sort(server.begin(),server.end(),comp);
    // median load
    medLoad = load / count;
    low = 0;
    heigh = server.size() - 1;
    tolerance = medLoad * 0.1;
//    tolerance = medLoad * .8;
    while(low < heigh && server[heigh]->load - tolerance > medLoad)
    {
        worker.clear();

        // find some servers to take load
        tooMuch = server[heigh]->load - medLoad;
#if 0
        // client does no rendering TEST TEST
        if(server[heigh]->id == getServers().size())
            tooMuch = server[heigh]->load;
#endif
        while(tooMuch > tolerance &&
              server[low]->load + tolerance < medLoad)
        {
            // create new worker
            wo.serverId = server[low]->id;
            wo.takeLoad = osgMin(tooMuch,medLoad - server[low]->load);
            worker.push_back(wo);
            tooMuch -= wo.takeLoad;
            server[heigh]->load -= wo.takeLoad;
            server[low]->load   += wo.takeLoad;
            if(server[low]->load + tolerance >= medLoad)
                low++;
        }
        if(worker.size()) 
        {
            // remaining self rendering
            wo.serverId = server[heigh]->id;
            wo.takeLoad = server[heigh]->load;
            worker.push_back(wo);
            for(vI = 0 ; vI < _cluster.servers[wo.serverId].viewports.size() ; ++vI)
            {
                VPort &port = _cluster.servers[wo.serverId].viewports[vI];
                splitViewport(worker,port,port.rect,port.load);
#if 0
                for(int i=0 ; i<worker.size() ; ++i)
                {
                    printf("%10.6f %10.6f\n",
                           worker[i].takeLoad,
                           worker[i].assignedLoad);
                    server[worker[i].serverId]->load -= worker[i].takeLoad;
                    server[worker[i].serverId]->load += worker[i].assignedLoad;
                }
#endif
            }
        } else {
            // stop no further spilt possible
            break;
        }
#if 0
        if(server[low]->load + tolerance >= medLoad)
        {
            printf("Avoid overload\n");
            low++;
        }
#endif
        heigh--;
    }
    // others should render there whole viewport
    while(heigh >= 0)
    {
        for(vI = 0 ; vI < _cluster.servers[server[heigh]->id].viewports.size() ; ++vI)
        {
            VPort &port = _cluster.servers[server[heigh]->id].viewports[vI];
            wp.viewportId   = port.id;
            wp.drawServer   = server[heigh]->id;
            wp.sendToServer = server[heigh]->id;
            for(int i=0 ; i<4 ; ++i)
                wp.rect[i]  = port.rect[i];
            _cluster.workpackages.push_back(wp);
        }
        heigh--;
    }        
#if 0
    for(int j=0;j<_cluster.workpackages.size() ; ++j)
    {
        printf("vp          %d\n",_cluster.workpackages[j].viewportId);
        printf("render      %d\n",_cluster.workpackages[j].drawServer);
        printf("display     %d\n",_cluster.workpackages[j].sendToServer);
        printf("rect        %d %d %d %d\n",
               _cluster.workpackages[j].rect[0],
               _cluster.workpackages[j].rect[1],
               _cluster.workpackages[j].rect[2],
               _cluster.workpackages[j].rect[3]);
    }
#endif
}


/*!  split viewport
 */
void BalancedMultiWindow::splitViewport(std::vector<Worker> &allWorker,
                                        VPort &port,
                                        Int32 const (&rect)[4],
                                        Real32 portLoad)
{
    UInt32 i;
    WorkPackage wp;
    std::vector<Worker>::iterator wI;
    Real32 load[2] = {0,0};
    std::vector<Worker> worker[2];
    Int32  localWorkerSide,side;
    Int32  localWorkerSideTry[2];
    Real32 resultLoad[2];
    Int32  resultRect[2][4];
    Real32 resultLoadTry[2][2];
    Int32  resultRectTry[2][2][4];
    UInt32 axis;
//    Real32 threshold;
//    Real32 maxLoad1,maxLoad2;
    UInt32 fromAxis,toAxis;
    bool bestCut=getBestCut();

    if(rect[2] - rect[0] == 0 ||
       rect[3] - rect[1] == 0)
    {
        bestCut = false;
    }

    localWorkerSide = -1;
    for(wI = allWorker.begin() ; wI != allWorker.end() ; ++wI)
    {
        if(load[0] <= load[1])
            side = 0;
        else
            side = 1;
        // add load
        load[side] += wI->takeLoad;
        worker[side].push_back(*wI);
        // local worker
        if(wI->serverId == port.serverId) 
        {
            localWorkerSide = side;
        }
    }

    // scale load
    Real32 scale = portLoad / (load[0] + load[1]); 
    load[0] *= scale;
    load[1] *= scale;

    if(bestCut)
    {
        // check both axis for best cut
        fromAxis=0;
        toAxis=1;
    }
    else
    {
        // check for axis and split direction
        if(rect[RIGHT] - rect[LEFT  ] >
           rect[TOP  ] - rect[BOTTOM])
            fromAxis = toAxis = 0;
        else
            fromAxis = toAxis = 1;
    }

    for(axis = fromAxis ; axis <= toAxis ; ++axis)
    {
        if(localWorkerSide >= 0)
        { 
            if(fabs(port.loadCenter[axis] - rect[LEFT +axis]) >
               fabs(port.loadCenter[axis] - rect[RIGHT+axis]))
                // most load is right, so do local rendering left
                localWorkerSideTry[axis] = 0;
            else
                // most load is left, so do local rendering right
                localWorkerSideTry[axis] = 1;
            // change sides
            if(localWorkerSide != localWorkerSideTry[axis])
            {
                std::vector<Worker> w = worker[1];
                worker[1] = worker[0];
                worker[0] = w;
                Real32 l = load[1];
                load[1] = load[0];
                load[0] = l;
                localWorkerSide = localWorkerSideTry[axis];
            }
        }
        else
            localWorkerSideTry[axis] = localWorkerSide;
        // split
        splitAxis(load,port,rect,axis,resultLoadTry[axis],resultRectTry[axis]);
    }

    // find best cut
    if(bestCut)
    {
        if(osgMax(resultLoadTry[0][0],resultLoadTry[0][1]) <
           osgMax(resultLoadTry[1][0],resultLoadTry[1][1])) 
            axis = 0;
        else
            axis = 1;
/*
        printf("best %d: %f %f    %f %f\n",axis,
               resultLoadTry[0][0],resultLoadTry[0][1],
               resultLoadTry[1][0],resultLoadTry[1][1]);
*/
    }
    else
        axis = fromAxis;

    // take best load
    if(localWorkerSideTry[axis] != localWorkerSide) 
    {
        std::vector<Worker> w = worker[1];
        worker[1] = worker[0];
        worker[0] = w;
        Real32 l = load[1];
        load[1] = load[0];
        load[0] = l;
        localWorkerSide = localWorkerSideTry[axis];
    }
    resultLoad[0] = resultLoadTry[axis][0];
    resultLoad[1] = resultLoadTry[axis][1];
    for(i=0 ; i<4 ; ++i)
    {
        resultRect[0][i] = resultRectTry[axis][0][i];
        resultRect[1][i] = resultRectTry[axis][1][i];
    }

    // dont cut if only 1 percent is taken from load
//    threshold = (load[0] + load[1]) * 0.0001;

    // take full viewport, if the split is not performance relevant
    // This makes only sense if one of the sides contain a local 
    // renderer
    if( (worker[0].size() == 1                             &&
         worker[1].size() == 1)                               &&
#if 1
        (resultLoad[0] == 0.0 || resultLoad[1] == 0.0)
#else
        ((resultLoad[0] + threshold) > (load[0] + load[1]) ||
         (resultLoad[1] + threshold) > (load[0] + load[1]))
#endif
        )
    {
        bool toLeft  = false;
        bool toRight = false;
        
        if(localWorkerSide == 0)
            toLeft  = true;
        else
            if(localWorkerSide == 1)
                toRight = true;
            else
                if(load[0] > load[1])
                    toLeft = true;
                else
                    if(load[0] <= load[1])
                        toRight = true;
        if(toLeft)
        {
            resultLoad[0] = load[0] + load[1];
            resultLoad[1] = 0;
            resultRect[0][axis+2] = rect[axis+2];
            resultRect[1][axis]   = rect[axis+2] + 1;
        }
        if(toRight)
        {
            resultLoad[0] = 0;
            resultLoad[1] = load[0] + load[1];
            resultRect[0][axis+2] = rect[axis] - 1;
            resultRect[1][axis]   = rect[axis];
        }
    }
    // next recoursion stop
    for(int g=0 ; g<2 ; ++g)
    {
        // ignore nonsense cut
        if(resultRect[g][RIGHT] >= resultRect[g][LEFT] &&
           resultRect[g][TOP] >= resultRect[g][BOTTOM])
        {
            if(worker[g].size() > 1)
                splitViewport(worker[g],port,resultRect[g],resultLoad[g]);
            else
            {
                // assigned load
                worker[g][0].assignedLoad = resultLoad[g];
                // end of recoursion
                wp.viewportId   = port.id;
                wp.drawServer   = worker[g][0].serverId;
                wp.sendToServer = port.serverId;
                for(i=0 ; i<4 ; ++i)
                    wp.rect[i]  = resultRect[g][i];
                _cluster.workpackages.push_back(wp);
/*
                printf("work server %d -> %d   %f\n",
                       worker[g][0].serverId,
                       port.serverId,resultLoad[g]);
*/               
            }
        }
    }

    allWorker.clear();
    allWorker.reserve(worker[0].size() + worker[1].size());
    allWorker.assign(worker[0].begin(), worker[0].end());
    std::copy(worker[1].begin(), worker[1].end(),
              std::back_insert_iterator<std::vector<Worker> >(allWorker));

    /*
    allWorker.insert(allWorker.end(),worker[0].begin(),worker[0].end());
    allWorker.insert(allWorker.end(),worker[1].begin(),worker[1].end());
    */
}

/*! sort bboxes
 */
void BalancedMultiWindow::sortBBoxes(VPort &port,UInt32 axis,
                                     Int32 const (&rect)[4])
{
    std::vector<BBox>::iterator     bI;
    BBoxList                       *freeList;
    Int32  pos,from,to;
    Real32 constant,pixel;
    UInt32 otherAxis = axis^1;
    Int32  t,b;
    Real32 area;

    // list of opened groups
    if(Int32(_groupOpen.size()) < rect[axis+2] + 1)
        _groupOpen.resize(rect[axis+2] + 1);

    // list of closed groups
    if(Int32(_groupClose.size()) < rect[axis+2] + 1)
        _groupClose.resize(rect[axis+2] + 1);

    // free bboxlist nodes
    if(_bboxlist.size() < port.bboxes.size() * 2)
        _bboxlist.resize(port.bboxes.size() * 2);

    // init lists
    for(pos = rect[axis] ; pos <= rect[axis+2] ; ++pos)
        _groupOpen[pos] = _groupClose[pos] = NULL;

    freeList = &_bboxlist.front();
    for(bI = port.bboxes.begin() ; bI != port.bboxes.end() ; ++bI)
    {
        // ignore invisible groups
        if(bI->rect[LEFT  ] > rect[RIGHT ] ||
           bI->rect[BOTTOM] > rect[TOP   ] ||
           bI->rect[RIGHT ] < rect[LEFT  ] ||
           bI->rect[TOP   ] < rect[BOTTOM])
           continue;
        from = bI->rect[axis];
        to   = bI->rect[axis+2];

        // orriginal bbox size
        area = ( bI->rect[2] - bI->rect[0] + 1 ) *
               ( bI->rect[3] - bI->rect[1] + 1 );

        // clip to visible 
        if(from < rect[axis  ])
            from = rect[axis];
        if(to   > rect[axis+2])
            to   = rect[axis+2];

        // size of other axis
        b = bI->rect[otherAxis];
        t = bI->rect[otherAxis+2];
        if(b < rect[otherAxis])
            b = rect[otherAxis];
        if(t > rect[otherAxis+2])
            t = rect[otherAxis+2];
        
        // cost
        LoadGroup &group = _cluster.loadGroups[bI->groupId];
        constant = group.constant;
        pixel    = (t-b+1) * ( group.pixel + group.ratio / area );

        // insert into open list
        freeList->next     = _groupOpen[from];
        freeList->constant = constant;
        freeList->pixel    = pixel;
        _groupOpen[from] = freeList++;

        // insert into close list
        freeList->next     = _groupClose[to];
        freeList->constant = constant;
        freeList->pixel    = pixel;
        _groupClose[to] = freeList++;

//        printf("from %d to %d\n",from,to);
    }
}

/*! split viewport
 */
void BalancedMultiWindow::splitAxis(Real32 const (&load)[2],
                                    VPort &port,
                                    Int32 const (&rect)[4],
                                    int axis,
                                    Real32 (&resultLoad)[2],
                                    Int32 (&resultRect)[2][4])
{
    Int32 from,to,cut; // ,lastCut;
    BBoxList *bl;
    Real64 leftLoad  = 0;
    Real64 rightLoad = load[0] + load[1];
    Real64 openPixel=0;
    UInt32 otherAxis = axis^1;
    Real64 scaleLeft  = 1 / load[0];
    Real64 scaleRight = 1 / load[1];
    Real64 lastLeft;
    Real64 lastRight;
#if 0
    if(load[0] >= load[1] &&
       load[0] / load[1] < 1.4)
        scaleLeft = scaleRight = 1.0;
    if(load[1] >= load[0] &&
       load[1] / load[0] < 1.4)
        scaleLeft = scaleRight = 1.0;
#endif
    // sort visible bboxes and calculate costs
    sortBBoxes(port,axis,rect);

    for(from  = rect[axis] ; 
        from <= rect[axis+2] &&
            _groupOpen[from] == NULL &&
            _groupClose[from] == NULL
            ; ++from) ;
    for(to  = rect[axis+2] ; 
        to >= from &&
            _groupOpen[to] == NULL &&
            _groupClose[to] == NULL
            ; --to) ;

    // loop through all points
    //lastCut = from-1;
    lastLeft = 0;
    lastRight = rightLoad;
    for(cut = from ; cut < to ; ++cut)
    {
        // loop through open list
        bl = _groupOpen[cut];
        while(bl)
        {
            openPixel += bl->pixel;
            leftLoad  += bl->constant;
            bl = bl->next;
        }
        leftLoad  += openPixel;
        rightLoad -= openPixel;
        // loop through open list
        bl = _groupClose[cut];
        while(bl)
        {
            openPixel -= bl->pixel;
            rightLoad -= bl->constant;
            bl = bl->next;
        }
//        rightLoad -= openPixel;
/*
        printf("A %d %.10f %.10f\n",cut,leftLoad,rightLoad);
        printf("B %d %.10f %.10f\n",cut,leftLoad*scaleLeft,rightLoad*scaleRight);
*/

//        if(leftLoad * scaleLeft + 1e-6 >= rightLoad * scaleRight)
        // take best ob last and current cut
        if(leftLoad * scaleLeft >= rightLoad * scaleRight)
        {
            break;
        }

        lastLeft = leftLoad;
        lastRight = rightLoad;
    }
    if((osgMax(leftLoad*scaleLeft,rightLoad*scaleRight) >
        osgMax(lastLeft*scaleLeft,lastRight*scaleRight) &&
        cut > from) ||
       (cut > from && cut == to))
    {
        cut--;
        leftLoad = lastLeft;
        rightLoad = lastRight;
    } 

    // new left
    resultLoad[0] = leftLoad;
    resultRect[0][axis]        = from;
    resultRect[0][otherAxis]   = rect[otherAxis];
    resultRect[0][axis+2]      = cut;
    resultRect[0][otherAxis+2] = rect[otherAxis+2];

    // new right
    resultLoad[1] = rightLoad;
    resultRect[1][axis]        = cut+1;
    resultRect[1][otherAxis]   = rect[otherAxis];
    resultRect[1][axis+2]      = to;
    resultRect[1][otherAxis+2] = rect[otherAxis+2];

//    printf("AA %d %d %d\n",rect[axis],resultRect[0][axis+2],rect[axis+2]);
#if 0
    for(cut = rect[axis] ; 
        cut <= rect[axis+2] &&
            _groupOpen[cut] == NULL &&
            _groupClose[cut] == NULL
            ; ++cut)
        resultRect[0][axis]++;

    for(cut = rect[axis+2] ; 
        cut >= rect[axis] &&
            _groupOpen[cut] == NULL &&
            _groupClose[cut] == NULL
            ; --cut)
        resultRect[1][axis+2]--;
#endif
}



/*! render part of a viewport viewport 
 */
void BalancedMultiWindow::renderViewport(Window           *serverWindow,
                                         UInt32            id,
                                         RenderActionBase *action,
                                         UInt32            portId,
                                         Int32 const (&rect)[4])
{
    // create temporary viewport
    _foreignPort.id         = portId;
    _foreignPort.serverId   = id;
    _foreignPort.root       = getPort(portId)->getRoot();
    // calculate valid viewport
    calculateServerPort(_foreignPort,rect);
    // add to window
    serverWindow->addPort(_foreignPort.serverPort);

    if(_foreignPort.serverPort->getPixelLeft() <= 
       _foreignPort.serverPort->getPixelRight()   &&
       _foreignPort.serverPort->getPixelBottom() <= 
       _foreignPort.serverPort->getPixelTop())
    {
        // do rendering
        action->setWindow(serverWindow);
        _foreignPort.serverPort->render(action);
/*
        GLint glvp[4];
        glGetIntegerv( GL_VIEWPORT, glvp );
        printf("%d %d %d %d\n",glvp[0],
               glvp[1],
               glvp[2],
               glvp[3]);
*/
        action->setFrustumCulling(true);
    }

    // sub viewport from window
    serverWindow->subPortByObj(_foreignPort.serverPort);
}

/*! clear port with background
 */
// clear local ports
void BalancedMultiWindow::clearViewports(Window           *serverWindow,
                                         UInt32            id,
                                         RenderActionBase *action)
{
    UInt32 vp;
    UInt32 travMask;

    // clear with black, if no local viewports
    if(_cluster.servers[id].viewports.size() == 0)
    {
        glViewport(0,0,
                   serverWindow->getWidth(), 
                   serverWindow->getHeight());
        glClearColor(0,0,0,0);
        // glClear(GL_COLOR_BUFFER_BIT);
    }

    for(vp=0 ; vp<_cluster.servers[id].viewports.size() ; ++vp)
    {
        VPort &port = _cluster.servers[id].viewports[vp];

        // don't render scene
        travMask = port.root->getTravMask();
        port.root->setTravMask(0);

        // calculate valid viewport
        calculateServerPort(port,port.rect);

        // add to window
        serverWindow->addPort(port.serverPort);

        // do rendering
        action->setWindow(serverWindow);
        port.serverPort->render(action);
        
        // sub viewport from window
        serverWindow->subPortByObj(port.serverPort);
        
        port.root->setTravMask(travMask);
    }
}


/*! store viewport
 */
void BalancedMultiWindow::storeViewport(Area &area,Viewport *vp,
                                        Int32 const (&rect)[4])
{
    Int32 x,y,w,h;
    UInt32 tI=0; 
/*
    printf("vport pos %d %d\n",vp->getPixelLeft(),vp->getPixelBottom());
    printf("rect  pos %d %d\n",rect[0],rect[1]);
*/
    vp->activate();

    area.tiles.resize(calcTileCount(rect));

    for(y = rect[BOTTOM] ; y <= rect[TOP] ; y += MW_TILE_SIZE)
    {
        for(x = rect[LEFT] ; x <= rect[RIGHT] ; x += MW_TILE_SIZE)
        {
            w = osgMin(Int32(MW_TILE_SIZE),rect[RIGHT] - x + 1);
            h = osgMin(Int32(MW_TILE_SIZE),rect[TOP]   - y + 1);

            area.tiles[tI].header.x      = x;
            area.tiles[tI].header.y      = y;
            area.tiles[tI].header.width  = w;
            area.tiles[tI].header.height = h;
            area.tiles[tI].header.last  = false;

            if(getShort())
            {
                glReadPixels(area.tiles[tI].header.x,
                             area.tiles[tI].header.y,
                             w, h, GL_RGB, GL_UNSIGNED_SHORT_5_6_5,
                             area.tiles[tI].pixel);
            }
            else
            {
                glReadPixels(area.tiles[tI].header.x,
                             area.tiles[tI].header.y,
                             w, h, GL_RGB, GL_UNSIGNED_BYTE,
                             area.tiles[tI].pixel);
            }
            tI++;
        }
    }
    area.tiles[tI-1].header.last = true;

    vp->deactivate();
}


void BalancedMultiWindow::drawSendAndRecv(Window           *window,
                                          RenderActionBase *action,
                                          UInt32            id)
{
    UInt16 wpId;
    UInt32 sendCount;
    GroupConnection *groupConn;
//    UInt32 count,vp,vpcount,wpcount;
//    Server &server = _cluster.servers[id];
    std::vector<WorkPackage>::iterator wI;
    std::vector<Area>::iterator aI;
    std::vector<Tile>::iterator tI;
    Tile tile;
    Connection::Channel channel=0;

    _triCount = 0;
    _drawTime = 0;
    _pixelTime = 0;
    _netTime = 0;

#ifdef CHECK
    // prepare statistics
    if(action->getStatistics() == NULL) 
    {
        action->setStatistics(new StatCollector());
        action->getStatistics()->getElem( Drawable::statNTriangles )->getValue();
    }
#endif

    Connection *conn = getNetwork()->getMainConnection();

    // start rendering
    if(window != NULL)
    {
        window->activate ();
        window->frameInit();

        // render viewport for others
        for(wI  = _cluster.workpackages.begin(), wpId=0; 
            wI != _cluster.workpackages.end() ;
            ++wI, ++wpId)
        {
            if(wI->drawServer == id &&
               wI->sendToServer != id)
            {
                // new area
                _cluster.areas.resize(_cluster.areas.size()+1);
                _cluster.areas.back().workpackageId = wpId;
                renderViewport(window,
                               wI->sendToServer,
                               action,
                               wI->viewportId,
                               wI->rect);
                glFinish();
                _pixelTime -= getSystemTime();
                storeViewport (_cluster.areas.back(),
                               getPort(wI->viewportId),
                               wI->rect);
                _pixelTime += getSystemTime();

#ifdef CHECK
                _triCount += (UInt32)action->getStatistics()->getElem( Drawable::statNTriangles )->getValue();
                _drawTime += action->getStatistics()->getElem( RenderAction::statDrawTime )->getValue();
#endif
            }
        }

        // clear viewports with background
        clearViewports(window,id,action);

        // render own viewports
        for(wI  = _cluster.workpackages.begin() ; 
            wI != _cluster.workpackages.end() ;
            ++wI)
        {
            if(wI->drawServer == id &&
               wI->sendToServer == id)
            {
                // render local viewport
                renderViewport(window,
                               id,
                               action,
                               wI->viewportId,
                               wI->rect);
#ifdef CHECK
                _triCount += (UInt32)action->getStatistics()->getElem( Drawable::statNTriangles )->getValue();
                _drawTime += action->getStatistics()->getElem( RenderAction::statDrawTime )->getValue();
#endif
            }
        }
        // send tiles
        sendCount = _cluster.areas.size();
        groupConn = getNetwork()->getGroupConnection(id);
        while(sendCount)
        {
            groupConn->selectChannel();
            groupConn->getValue(wpId);
            for(aI = _cluster.areas.begin() ; aI != _cluster.areas.end() ; ++aI)
            {
                if(wpId == aI->workpackageId)
                {
                    conn = getNetwork()->getConnection(_cluster.workpackages[wpId].sendToServer);
                    for(tI = aI->tiles.begin() ; tI != aI->tiles.end() ; ++tI)
                    {
                        if(getShort())
                            conn->put(&(*tI),UInt32(osgAbs(tI->header.width)) * tI->header.height * 2 + sizeof(Tile::Header));
                        else
                            conn->put(&(*tI),UInt32(osgAbs(tI->header.width)) * tI->header.height * 3 + sizeof(Tile::Header));
                    }
                    conn->flush();
                    sendCount--;
                    break;
                }
            }
        }

        _netTime -= getSystemTime();
        // receive and paint tiles from others
        glPushMatrix();
        glLoadIdentity();
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        gluOrtho2D(0, window->getWidth(), 0, window->getHeight());
        glDisable(GL_DEPTH_TEST);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        groupConn = getNetwork()->getGroupConnection(id);
        wpId = 0;
        wI = _cluster.workpackages.begin();
        while(wI != _cluster.workpackages.end() &&
              (wI->drawServer == id || wI->sendToServer != id))
        {   
            ++wI; ++wpId;
        }
        if(wI != _cluster.workpackages.end())
        {
            conn = getNetwork()->getConnection(wI->drawServer);
            conn->putValue(wpId);
            conn->flush();
        }
        while(wI != _cluster.workpackages.end())
        {
            Viewport *vp = getPort(wI->viewportId);
            // the activate is only called for buffer activation.
            vp->activate();

            // overwrite viewport activate dimension and scissor test.
            glViewport(0, 0,
                       window->getWidth(), window->getHeight());
            glDisable(GL_SCISSOR_TEST);

            channel = groupConn->selectChannel();
            do
            {
                groupConn->get(&tile,sizeof(Tile::Header));
                if(tile.header.last)
                {
                    ++wI; ++wpId;
                    // we got last tile, request from next server
                    while(wI != _cluster.workpackages.end() &&
                          (wI->drawServer == id || wI->sendToServer != id))
                    {
                        ++wI; ++wpId;
                    }
                    if(wI != _cluster.workpackages.end())
                    {
                        conn = getNetwork()->getConnection(wI->drawServer);
                        conn->putValue(wpId);
                        conn->flush();
                    }
                }
                if(getShort())
                    groupConn->get(&tile.pixel,tile.header.width*tile.header.height*2);
                else
                    groupConn->get(&tile.pixel,tile.header.width*tile.header.height*3);
                _netTime += getSystemTime();
                _pixelTime -= getSystemTime();
                glRasterPos2i (tile.header.x,tile.header.y);
                if(getShort())
                    glDrawPixels(tile.header.width,tile.header.height, 
                                 GL_RGB, GL_UNSIGNED_SHORT_5_6_5,
                                 &(tile.pixel[0]));
                else
                    glDrawPixels(tile.header.width,tile.header.height, 
                                 GL_RGB, GL_UNSIGNED_BYTE,
                                 &(tile.pixel[0]));

                if(getShowBalancing())
                {
#if 1
                    static Real32 col[16][3] = {
                        {1,0,0},
                        {0,1,0},
                        {0,0,1},
                        {1,1,0},
                        {1,0,1},
                        {0,1,1},
                        {1,1,1},
                        {1,.5,0},
                        {.5,0,0},
                        {0,.5,0},
                        {0,0,.5},
                        {.5,.5,0},
                        {.5,0,1},
                        {0,.5,1},
                        {1,1,.5},
                        {.5,.5,0}
                    };
                    glEnable(GL_BLEND);
                    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
                    glBegin(GL_QUADS);
                    glColor4f(col[channel%16][0],
                              col[channel%16][1],
                              col[channel%16][2],
                              .3f);
                    glVertex2i(tile.header.x                  , tile.header.y);
                    glVertex2i(tile.header.x                  , tile.header.y+tile.header.height);
                    glVertex2i(tile.header.x+tile.header.width, tile.header.y+tile.header.height);
                    glVertex2i(tile.header.x+tile.header.width, tile.header.y);
                    glEnd();
                    glDisable(GL_BLEND);
#endif
                }
                _pixelTime += getSystemTime();
                _netTime -= getSystemTime();
            } 
            while(!tile.header.last);

            vp->deactivate();
/*
            _pixelTime -= getSystemTime();
            glFinish();
            _pixelTime += getSystemTime();
*/
        }
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();
        glEnable(GL_DEPTH_TEST);
    }
    _netTime += getSystemTime();
}

/*! preload display lists and textures
 */
void BalancedMultiWindow::preloadCache(Window           *window,
                                       RenderActionBase *action)
{
    Node   *root = NULL;
    UInt32  v;

    if(!_preloadCache)
        return;

    _preloadCache = false;

    window->activate();
    window->frameInit();

    // loop over all viewports
    for(v = 0 ; v  < getMFPort()->size() ; ++v )
    {
        Viewport *viewport = getPort(v);

        if(root == viewport->getRoot())
            continue;

        root = viewport->getRoot();

        if(root == NULL)
            continue;

        root->updateVolume();
        window->activate();
        window->frameInit();

        // create cart
        NodeUnrecPtr      cartN = Node::create();
        TransformUnrecPtr cart = Transform::create();

        cartN->setCore(cart);

        root->addChild(cartN);

        // create camera
        PerspectiveCameraUnrecPtr cam = PerspectiveCamera::create();

        cam->setBeacon( cartN );
        cam->setFov   ( osgDegree2Rad( 60 ) );

        // background
        SolidBackgroundUnrecPtr bkgnd = SolidBackground::create();

        // create viewport
        ViewportUnrecPtr vp = Viewport::create();

        vp->setCamera( cam );
        vp->setBackground( bkgnd );
        vp->setRoot( root );
        vp->setSize( 0,0, 1,1 );

        // add to window
        window->addPort(vp);

        // calc viewing matrix
        Vec3f min,max;
        root->getVolume().getBounds( min, max );
        Vec3f d = max - min;
        Real32 dist = osgMax(d[0],d[1]) / (2 * osgTan(cam->getFov() / 2.f));
        Vec3f up(0,1,0);
        Pnt3f at((min[0] + max[0]) * .5f,
                 (min[1] + max[1]) * .5f,
                 (min[2] + max[2]) * .5f);
        Pnt3f from=at;
        from[2]+=(dist*3); 

        Matrix &matrix = cart->editMatrix();
        MatrixLookAt(matrix, from, at, up);

        // set the camera to go from 1% of the object to twice its size
        Real32 diag = osgMax(osgMax(d[0], d[1]), d[2]);

        cam->setNear (diag / 100.f);
        cam->setFar  (10 * dist);

        // do rendering
        action->setWindow(window);
        vp->render(action);

        // remove port
        window->subPortByObj(vp);
        root->subChild(cartN);
    }
}

OSG_END_NAMESPACE
