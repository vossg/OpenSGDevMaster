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

#include <functional>

#include <OSGGLU.h>

#include <algorithm>
#include <OSGConfig.h>
#include <OSGGeometry.h>
#include <OSGSimpleGeometry.h>

#include "OSGTileLoadBalancer.h"

OSG_USING_NAMESPACE

/** \class osg::TileLoadBalancer
 *  \ingroup Cluster
 *  \brief Manages geometry load
 *
 *
 *
 *
 *
 **/

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

/*! Constructor
 */
TileLoadBalancer::TileLoadBalancer(bool useFaceDistribution,
                                   bool cutBestDirection):
    _useFaceDistribution(useFaceDistribution),
    _cutBestDirection(cutBestDirection)
{
}

/*! Copy Constructor
 */
TileLoadBalancer::TileLoadBalancer(const TileLoadBalancer &source):
    _tileGeometryLoad(source._tileGeometryLoad),
    _renderNode(source._renderNode),
    _useFaceDistribution(source._useFaceDistribution),
    _cutBestDirection(source._cutBestDirection)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

/*! Destructor documentation
 */
TileLoadBalancer::~TileLoadBalancer(void)
{
}

/*-------------------------------------------------------------------------*/
/*                             Assignment                                  */

/*! assignment
 */
TileLoadBalancer& TileLoadBalancer::operator = (const TileLoadBalancer &source)
{
    if(this == &source)
        return *this;
    _tileGeometryLoad = source._tileGeometryLoad;
    _renderNode = source._renderNode;
    _useFaceDistribution = source._useFaceDistribution;
    _cutBestDirection = source._cutBestDirection;
    return *this;
}


/** Update the load balancing information
 **/
void TileLoadBalancer::update(NodePtr node)
{
    TileGeometryLoadMapT loadMap;

    // collect old load objects
    for(TileGeometryLoadLstT::iterator gI=_tileGeometryLoad.begin();gI!=_tileGeometryLoad.end();++gI)
    {
        if(gI->getNode() != NullFC)
            loadMap[gI->getNode()->getId()] = gI;
        else
            gI->setValid(false);
    }

    updateSubtree(node,loadMap);

    // mark unused load objects as invalid.
    for(TileGeometryLoadMapT::iterator mI=loadMap.begin();mI!=loadMap.end();++mI)
        mI->second->setValid(false);

    // remove all invalid objects.
    _tileGeometryLoad.erase(std::remove_if(_tileGeometryLoad.begin(), _tileGeometryLoad.end(),
                            std::mem_fun_ref(&TileGeometryLoad::isInvalid)), _tileGeometryLoad.end());
}

/** load balance
 *
 *  \param vp        current viewport
 *  \param shrink    shrink to max area of visible objects
 *  \param result    resulting regions
 *
 **/
void TileLoadBalancer::balance(ViewportPtr    vp,
                               bool           shrink,
                               ResultT       &result)
{
    Matrix                   projection,viewing;
    RegionLoadVecT           visible;
    RegionLoadVecT::iterator vi;
    Int32                    width =vp->getPixelWidth();
    Int32                    height=vp->getPixelHeight();
    Int32                    wmin[2]={width,height};
    Int32                    wmax[2]={0    ,0     };
    Real32                   rNear=vp->getCamera()->getNear();

    result.clear();
    vp->getCamera()->getViewing   ( viewing   ,width,height );
    vp->getCamera()->getProjection( projection,width,height );
    visible.reserve(_tileGeometryLoad.size());
    for(TileGeometryLoadLstT::iterator l=_tileGeometryLoad.begin() ; l!=_tileGeometryLoad.end() ; ++l)
    {
        // update view dependent values
        l->updateView(viewing,
                      projection,
                      rNear,
                      width,
                      height);
        // sort by min values
        if(l->isVisible())
        {
            // collect visible geometries
            visible.push_back(RegionLoad(&(*l)));
            if(shrink)
            {
                if(l->getMin()[0] < wmin[0])
                    wmin[0]=l->getMin()[0];
                if(l->getMin()[1] < wmin[1])
                    wmin[1]=l->getMin()[1];
                if(l->getMax()[0] > wmax[0])
                    wmax[0]=l->getMax()[0];
                if(l->getMax()[1] > wmax[1])
                    wmax[1]=l->getMax()[1];
            }
        }
    }
    if(shrink)
    {
        // handle invisible area
        if(wmax[0]<wmin[0] ||
           wmax[1]<wmin[1] )
            wmin[0]=wmax[0]=wmin[1]=wmax[1]=0;
        // clamp to viewable area
        if(wmin[0]<0)
            wmin[0]=0;
        if(wmin[1]<0)
            wmin[1]=0;
        if(wmax[0]>=width )
            wmax[0]=width -1;
        if(wmax[1]>=height)
            wmax[1]=height-1;
    }
    else
    {
        wmin[0]=wmin[1]=0;
        wmax[0]=width-1;
        wmax[1]=height-1;
    }
    // calculate region cost
    for(vi=visible.begin();vi!=visible.end();vi++)
    {
        vi->updateCost(wmin,wmax);
    }
    if(_renderNode.size()>1)
    {
        splitRegion(0,_renderNode.size()-1,
                    visible,
                    wmin,
                    wmax,
                    0,
                    result);
    }
    else
    {
        Region region;
        region.x1=wmin[0];
        region.y1=wmin[1];
        region.x2=wmax[0];
        region.y2=wmax[1];
        result.push_back(region);
    }
}

void TileLoadBalancer::setRegionStatistics(ViewportPtr     vp,
                                           ResultT        &result)
{
    Matrix                         projection,viewing;
    Int32                          width =vp->getPixelWidth();
    Int32                          height=vp->getPixelHeight();
    Real32                         rNear=vp->getCamera()->getNear();
    ResultT::iterator              resultI;
    TileGeometryLoadLstT::iterator l;

    vp->getCamera()->getViewing   ( viewing   ,width,height );
    vp->getCamera()->getProjection( projection,width,height );
    for(resultI=result.begin();
        resultI!=result.end();
        ++resultI)
    {
        resultI->culledNodes=0;
        resultI->faces=0;
        resultI->culledFaces=0;
        resultI->pixel=0;
    }
    for(l=_tileGeometryLoad.begin() ;
        l!=_tileGeometryLoad.end() ;
        ++l)
    {
        l->updateView(viewing,
                      projection,
                      rNear,
                      width,
                      height);
        for(resultI=result.begin();
            resultI!=result.end();
            ++resultI)
        {
            if(!l->isVisible())
                resultI->culledNodes++;
            else
            {
                Int32 wmin[2];
                Int32 wmax[2];
                Int32 vismin[2];
                Int32 vismax[2];
                wmin[0]=resultI->x1;
                wmin[1]=resultI->y1;
                wmax[0]=resultI->x2;
                wmax[1]=resultI->y2;
                Real32 visible=l->getVisibleFraction(wmin,wmax,vismin,vismax)*
                    l->getFaces();
                if(visible==0)
                    resultI->culledNodes++;
                else
                {
                    resultI->faces+=visible;
                    resultI->culledFaces+= l->getFaces()-visible;
                    resultI->pixel+=
                        (vismax[0] - vismin[0] + 1)*
                        (vismax[1] - vismin[1] + 1);
                }
            }
        }
    }
}

/** Add new render node
 *
 **/
void TileLoadBalancer::addRenderNode(const RenderNode &rn,UInt32 id)
{
    while(_renderNode.size()<=id)
        _renderNode.push_back(RenderNode());
    _renderNode[id]=rn;
}

/** Draw recangular volume projection
 *
 **/
void TileLoadBalancer::drawVolumes(WindowPtr win)
{
    glPushMatrix();
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glViewport(0,0,win->getWidth(),win->getHeight());
    gluOrtho2D(0,win->getWidth(),
               0,win->getHeight());
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    for(TileGeometryLoadLstT::iterator l=_tileGeometryLoad.begin() ; l!=_tileGeometryLoad.end() ; ++l)
    {
        if(l->isVisible())
        {
            glBegin(GL_LINE_LOOP);
            glColor3f(0, 1, 0);
            glVertex3i(l->getMin()[0],l->getMin()[1],0);
            glVertex3i(l->getMax()[0],l->getMin()[1],0);
            glVertex3i(l->getMax()[0],l->getMax()[1],0);
            glVertex3i(l->getMin()[0],l->getMax()[1],0);
            glEnd();
        }
    }
    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_DEPTH_TEST);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

/** Add all geometry nodes in the given tree
 **/
void TileLoadBalancer::updateSubtree(const NodePtr node,TileGeometryLoadMapT &loadMap)
{
    // is nodecore a geometry?
    if(node->getCore() != NullFC &&
       dynamic_cast<GeometryPtr>(node->getCore()) != NullFC)
    {
        // is this a new node
        TileGeometryLoadMapT::iterator mI=loadMap.find(node->getId());
        if(mI==loadMap.end())
        {
            _tileGeometryLoad.push_back(TileGeometryLoad(node->getId(),
                                                         _useFaceDistribution));
        }
        else
        {
            loadMap.erase(mI);
        }
    }
    // handle all childs
    for(MFUnrecChildNodePtr::const_iterator n = node->getMFChildren()->begin();
                                            n !=node->getMFChildren()->end();
                                          ++n)
    {
        updateSubtree(*n,loadMap);
    }
}

/** Splitupt region
 **/
void TileLoadBalancer::splitRegion(UInt32          rnFrom,
                                   UInt32          rnTo,
                                   RegionLoadVecT &visible,
                                   Int32           wmin[2],
                                   Int32           wmax[2],
                                   UInt32          depth,
                                   ResultT        &result)
{
    Int32  axis,cut;
    Int32  maxA[2];
    Int32  minB[2];
    RegionLoadVecT visibleA;
    RegionLoadVecT visibleB;
    RegionLoadVecT::iterator vi;
    UInt32 rnToA,rnFromB;
    RenderNode groupRegionA,groupRegionB;
    RenderNode *renderNodeA,*renderNodeB;

    // create group render node if neccessary
    rnToA  =(rnTo+rnFrom)>>1;
    rnFromB=rnToA+1;
    if(rnFrom != rnToA)
    {
        groupRegionA.setGroup(&_renderNode[rnFrom],&_renderNode[rnToA+1]);
        renderNodeA=&groupRegionA;
    }
    else
    {
        renderNodeA=&_renderNode[rnFrom];
    }
    if(rnFromB != rnTo)
    {
        groupRegionB.setGroup(&_renderNode[rnFromB],&_renderNode[rnTo+1]);
        renderNodeB=&groupRegionB;
    }
    else
    {
        renderNodeB=&_renderNode[rnFromB];
    }
#if 0
    if((rnToA-rnFrom) != (rnTo-rnFromB))
    {
        renderNodeB->setInvisibleFaceCost(renderNodeA->getInvisibleFaceCost());
    }
#endif
    // do we check both axis?
    if(_cutBestDirection)
        axis=-1;
    else
        axis=depth&1;
    // search for best cut
    findBestCut(*renderNodeA,*renderNodeB,
                visible,wmin,wmax,axis,cut);
    // create new regions
    maxA[axis  ]=cut;
    maxA[axis^1]=wmax[axis^1];
    minB[axis  ]=cut+1;
    minB[axis^1]=wmin[axis^1];
    visibleA.reserve(visible.size());
    visibleB.reserve(visible.size());

    // split regions
    if(rnFrom != rnToA || rnFromB != rnTo)
    {
        // split visible regions
        for(vi=visible.begin();vi!=visible.end();vi++)
        {
            if(vi->getLoad()->getMax()[axis] <= cut)
                visibleA.push_back(*vi);
            else
                if(vi->getLoad()->getMin()[axis] > cut)
                    visibleB.push_back(*vi);
                else
                {
                    visibleA.push_back(*vi);
                    visibleB.push_back(*vi);
                    visibleA.rbegin()->updateCost(wmin,maxA);
                    visibleB.rbegin()->updateCost(minB,wmax);
                }
        }
    }
    if(rnFrom != rnToA)
        splitRegion(rnFrom,rnToA,visibleA,wmin,maxA,depth+1,result);
    else
    {
        Region region;
        region.x1=wmin[0];
        region.y1=wmin[1];
        region.x2=maxA[0];
        region.y2=maxA[1];
        result.push_back(region);
    }
    if(rnFromB != rnTo)
        splitRegion(rnFromB,rnTo,visibleB,minB,wmax,depth+1,result);
    else
    {
        Region region;
        region.x1=minB[0];
        region.y1=minB[1];
        region.x2=wmax[0];
        region.y2=wmax[1];
        result.push_back(region);
    }
}

/** Find best cut through the geometries
 **/
Real32 TileLoadBalancer::findBestCut (const RenderNode &renderNodeA,
                                      const RenderNode &renderNodeB,
                                      RegionLoadVecT &visible,
                                      Int32           wmin[2],
                                      Int32           wmax[2],
                                      Int32          &bestAxis,
                                      Int32          &bestCut)
{
    RegionLoadVecT::iterator vi;
    Int32 a,f,t,newCut;
    Int32 minB[2];
    Int32 maxA[2];
    Real32 costA=0,costB=0;
    Real32 newCost;
    Real32 bestCost;
    Int32 checkAxisFrom,checkAxisTo;
    bestCost=1e22;

    if(bestAxis>=0)
    {
        // only check given axis
        checkAxisFrom=checkAxisTo=bestAxis;
    }
    else
    {
        // check x and y cut
        checkAxisFrom=0;
        checkAxisTo=1;
    }
    for(a=checkAxisFrom;a<=checkAxisTo;++a)
    {
        f=wmin[a];
        t=wmax[a];
        maxA[0]=wmax[0];;
        maxA[1]=wmax[1];;
        minB[0]=wmin[0];;
        minB[1]=wmin[1];;
        do
        {
            newCut=(f+t)/2;
            maxA[a]=newCut;
            minB[a]=newCut+1;
            costA=costB=0;
            for(vi=visible.begin();vi!=visible.end();vi++)
            {
                if(vi->getLoad()->getMax()[a] <= newCut)
                {
                    costA+=vi->getCost(renderNodeA);
                }
                else
                    if(vi->getLoad()->getMin()[a] > newCut)
                    {
                        costB+=vi->getCost(renderNodeB);
                    }
                    else
                    {
                        costA+=vi->getCost(renderNodeA,wmin,maxA);
                        costB+=vi->getCost(renderNodeB,minB,wmax);
                    }

            }
            newCost= osgMax( costA, costB );
            if(newCost<bestCost)
            {
                bestCut=newCut;
                bestCost=newCost;
                bestAxis=a;
            }
            // walk into direction of inbalance
            if(costA>costB)
                t=newCut;
            else
                f=newCut;
        }
        while(t-f > 2);
    }
    return bestCost;
}

