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

#include <OSGConfig.h>
#include <OSGCamera.h>

#include "OSGImageComposer.h"

OSG_USING_NAMESPACE

/** \class OSG::ImageComposer
 *  \ingroup GrpSystemCluster
 *  \brief Cluster image composition implementation
 *
 * An ImageComposer class is used to compose multiple images into
 * a final image. Each cluster server produces one part of the 
 * image. This class is abstract. Derived classes should implement
 * composition over network or other cluster interconnects.
 *
 **/

/*-------------------------------------------------------------------------*/
/*                          window functions                               */

void ImageComposer::initMethod(InitPhase ePhase)
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

ImageComposer::ImageComposer(void) :
    Inherited()
{
}

ImageComposer::ImageComposer(const ImageComposer &source) :
    Inherited(source)
{
}

ImageComposer::~ImageComposer(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ImageComposer::changed(ConstFieldMaskArg whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void ImageComposer::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump ImageComposer NI" << std::endl;
}

/*----------------------------- setup ------------------------------------*/

/*! initialize the composer
 */
void ImageComposer::setup(bool             isClient,
                          UInt32           clusterId,
                          WindowPtr        localWindow, 
                          ClusterWindowPtr clusterWindow)
{
    _isClient      = isClient;
    _clusterId     = clusterId;
    _localWindow   = localWindow;
    _clusterWindow = clusterWindow;
    _clusterSize   = clusterWindow->getServers().size()+1;
    _serverCount   = clusterWindow->getServers().size();
}

/*----------------------------- composition ------------------------------*/

/*! open composer 
 */
void ImageComposer::open(void)
{
}

/*! compose singel viewport
 */
void ImageComposer::composeViewport(ViewportPtr port)
{
}

/*! compose whole window
 */
void ImageComposer::composeWindow(void)
{
}

/*! close composer
 */
void ImageComposer::close(void)
{
}

/*----------------------------- features ---------------------------------*/

/*! The default is that the cluster window should render on the 
    client side. Overload this method if the composer is not
    able to handle client rendering.
 */

bool ImageComposer::getClientRendering(void)
{
    return true;
}

/*! Return the number of Servers that can be uses by the composer
 */

UInt32 ImageComposer::getUsableServers(void)
{
    return serverCount();
}

/*----------------------------- helpers ----------------------------------*/

/*! get screen aligned bounding box of the given geometrie. 
    width and hight are given in pixels. depth is given as
    uint32. Returns false if the node is invisible
 */
bool ImageComposer::getScreenAlignedBBox(NodePtr      node,
                                         ViewportPtr  vp,
                                         UInt32      &l,
                                         UInt32      &b,
                                         UInt32      &r,
                                         UInt32      &t,
                                         UInt32      &front,
                                         UInt32      &back)
{
    UInt32 width     = vp->getPixelWidth();
    UInt32 height    = vp->getPixelHeight();
    Matrix viewing;
    Matrix projection;
    Real32 rNear     = vp->getCamera()->getNear();
    Vec3f              vol[2];
    Pnt3f              pnt;
    Real32             minx=0,miny=0,minz=0;
    Real32             maxx=0,maxy=0,maxz=0;
    Matrix            *p;

    vp->getCamera()->getViewing   (viewing,width,height);
    vp->getCamera()->getProjection(projection,width,height);

    // default
    l=b=r=t=0;
    // get whole transformation
    Matrix m=node->getToWorld();
    m.multLeft(viewing);
    // get transformed volume
    node->updateVolume();
    DynamicVolume volume=node->getVolume();
    // bug in osg base
    /*
    if(volume.isEmpty())
    {
        _visible=false;
        return;
    }
    */
    volume.transform(m);
    // get min,max
    volume.getBounds(vol[0], vol[1]);
    // min < rNear
    if(vol[0][2] > -rNear)
        return false;
    if(vol[1][2] > -rNear)
    {
        // volume lays on the fron clipping plane
        vol[1][2] = -rNear;
        p=&projection;
    }
    else
    {
        // volume lays on the visible side of the clipping plane
        node->getVolume().getBounds(vol[0], vol[1]);
        m.multLeft(projection);
        p=&m;
    }
    // create corners of a bounding box
    for(int i=0;i<8;++i)
    {
        p->multFullMatrixPnt(Pnt3f( vol[ (i   )&1 ][0] ,
                                    vol[ (i>>1)&1 ][1] ,
                                    vol[ (i>>2)&1 ][2]) , pnt);
        if(i>0)
        {
            if(minx > pnt[0]) minx = pnt[0];
            if(miny > pnt[1]) miny = pnt[1];
            if(minz > pnt[2]) minz = pnt[2];
            if(maxx < pnt[0]) maxx = pnt[0];
            if(maxy < pnt[1]) maxy = pnt[1];
            if(maxz < pnt[2]) maxz = pnt[2];
        }
        else
        {
            maxx = minx = pnt[0];
            maxy = miny = pnt[1];
            maxz = minz = pnt[2];
        }
    }

    // visible ?
    if(maxx<-1 || maxy<-1 ||
       minx> 1 || miny> 1)
    {
        return false;
    }
    else
    {
        minx=width  * ( minx + 1.0 ) / 2.0 - .5;
        maxx=width  * ( maxx + 1.0 ) / 2.0 + .5;
        miny=height * ( miny + 1.0 ) / 2.0 - .5;
        maxy=height * ( maxy + 1.0 ) / 2.0 + .5;

        if(minx <  0     ) minx = 0;
        if(maxx >= width ) maxx = width-1;

        if(miny <  0     ) miny = 0;
        if(maxy >= height) maxy = height-1;

        l=(Int32)minx;
        b=(Int32)miny;
        r=(Int32)maxx;
        t=(Int32)maxy;

/*
        maxz = 1 / (2.0 / (maxz+1));
        minz = 1 / (2.0 / (minz+1));
*/

        front = (UInt32)( (double)(((UInt64)1)<<32) * (minz+1) / 2);
        back  = (UInt32)( (double)(((UInt64)1)<<32) * (maxz+1) / 2);
    }

#if 0
        glPushMatrix();
        glLoadIdentity();
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        glOrtho(0,width,
                0,height,
                -1,1);
        glDisable(GL_DEPTH_TEST);
        glEnable(GL_COLOR_MATERIAL);
        glBegin(GL_LINE_LOOP);
        glColor3f(1, 1, 0);
        glVertex2f(l,b);
        glVertex2f(r,b);
        glVertex2f(r,t);
        glVertex2f(l,t);
        glEnd();
        glDisable(GL_COLOR_MATERIAL);
        glEnable(GL_DEPTH_TEST);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();
        glPopAttrib();
#endif

    return true;
}

