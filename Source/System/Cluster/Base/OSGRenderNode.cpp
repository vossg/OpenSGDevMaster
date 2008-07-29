/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2000-2002,2002 by the OpenSG Forum                *
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

#include <stdlib.h>
#include <stdio.h>

#include <vector>

#include <OSGConfig.h>
#include <OSGGL.h>
#include <OSGGLU.h>
#include <OSGBaseFunctions.h>
#include <OSGTime.h>
#include <OSGLog.h>
#include <OSGMatrix.h>
#include <OSGWindow.h>

#include "OSGRenderNode.h"

OSG_USING_NAMESPACE using namespace std;

/** \class OSG::RenderNode
 *  \ingroup GrpSystemCluster
 *  \brief cluster node information
 **/

RenderNode *RenderNode::            _predefined[] =
{
    // some nvidia cards
    new
    RenderNode
        (
            1.0 /   83495245, // GF 4 
            1.0 /   16750624,
            1.0 / 1161538447, 
            1.0 /   42022724, 
            1.0 /   83570644,
            "NVIDIA Corporation", "GeForce4 Ti 4600/AGP/3DNOW!"
        ),
    new
    RenderNode
        (
            1.0 /   83495245, // GF 4 
            1.0 /   16750624,
            1.0 / 1161538447, 
            1.0 /   42022724, 
            1.0 /   83570644,
            "NVIDIA Corporation", "GeForce4 Ti 4600/AGP/SSE/3DNOW!"
        ),
    new
    RenderNode
        (
            1.0 /   83455190, // GF 4 
            1.0 /   16881114,
            1.0 / 1061266770, 
            1.0 /   42022724, 
            1.0 /   83570644,
            "NVIDIA Corporation", "GeForce4 Ti 4800 SE/AGP/SSE/3DNOW!"
        ),
    new
    RenderNode
        (
            1.0 /  105725796, // GF 4 
            1.0 /   20313509,
            1.0 / 1168604741, 
            1.0 /   45037981, 
            1.0 /  107106583,
            "NVIDIA Corporation", "GeForce4 Ti 4600/AGP/SSE2"
        ),
    /*
    new RenderNode(1.0/  7598000,          // GF 256
                   1.0/  7597000,
                   1.0/110599000,
                   1.0/ 18896143,
                   1.0/ 26220918,
                   "NVIDIA Corporation",
                   "GeForce 256/AGP"),
    */
    new
    RenderNode
        (
            1.0 /  94383759, // GF 3 
            1.0 /  17733654, 
            1.0 / 897012437, 
            1.0 /  24905933, 
            1.0 /  45649003,
            "NVIDIA Corporation", "GeForce3/AGP/3DNOW!"
        ),
    new
    RenderNode
        (
            1.0 /  94383759, // GF 3 
            1.0 /  17733654, 
            1.0 / 897012437,
            1.0 /  24905933, 
            1.0 /  45649003,
            "NVIDIA Corporation", "GeForce3/AGP/SSE2"
        ),
    new
    RenderNode
        (
            1.0 /  87097434, // GF 2 MX 
            1.0 /  18473570, 
            1.0 / 172343128,
            1.0 /  49542156,
            1.0 /  77120245,
            "NVIDIA Corporation", "GeForce2 MX/AGP/3DNOW!"
        ),

    // some sgi cards
    new
    RenderNode
        (
            1.0 /  1428577, // O2 
            1.0 /   581803, 
            1.0 / 66498959, 
            1.0 /  4047028,
            1.0 /  1101353, 
            "SGI", "CRIME"
        ),
    new
    RenderNode
        (
            1.0 /  10121349, // IR2 
            1.0 /   7749685, 
            1.0 / 466657941, 
            1.0 /  38311070, 
            1.0 /  73507039, 
            "SGI", "IRL/M/2/64/4"
        ),
    new
    RenderNode
        (
            1.0 /  12237547, // ATI 
            1.0 /  12422953, 
            1.0 / 190803343, 
            1.0 /  41767062, 
            1.0 / 157129952, 
            "ATI Technologies Inc.", "Radeon 9700 PRO Pentium 4 (SSE2)"
        ),
    NULL
};

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

/*! Constructor 
 */
RenderNode::RenderNode(      Real32       invisibleFaceCost,
                             Real32       visibleFaceCost,
                             Real32       drawPixelCost, 
                             Real32       readPixelCost,
                             Real32       writePixelCost, 
                       const std::string &vendor,
                       const std::string &renderer) :
    _visibleFaceCost  (visibleFaceCost  ),
    _invisibleFaceCost(invisibleFaceCost),
    _drawPixelCost    (drawPixelCost    ),
    _readPixelCost    (readPixelCost    ),
    _writePixelCost   (writePixelCost   ),
    _vendor           (vendor           ),
    _renderer         (renderer         )
{
}

/*! copy constructor
 */
RenderNode::RenderNode(const RenderNode &source) :
    _visibleFaceCost  (source._visibleFaceCost  ),
    _invisibleFaceCost(source._invisibleFaceCost),
    _drawPixelCost    (source._drawPixelCost    ),
    _readPixelCost    (source._readPixelCost    ),
    _writePixelCost   (source._writePixelCost   ),
    _vendor           (source._vendor           ),
    _renderer         (source._renderer         )
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

/*! Destructor documentation
 */
RenderNode::~RenderNode(void)
{
}

/*-------------------------------------------------------------------------*/
/*                             Assignment                                  */

/*! assignment
 */
RenderNode &RenderNode::operator=(const RenderNode &source)
{
    if(this == &source)
        return *this;

    _visibleFaceCost   = source._visibleFaceCost;
    _invisibleFaceCost = source._invisibleFaceCost;
    _drawPixelCost     = source._drawPixelCost;
    _readPixelCost     = source._readPixelCost;
    _writePixelCost    = source._writePixelCost;
    _vendor            = source._vendor;
    _renderer          = source._renderer;

    return *this;
}

/*-------------------------------------------------------------------------*/
/*                             Performance analysis                        */

/*! This is a rough estimation of rendering costst for visible faces,
 *  faces outside the viewport and fill rate.
 *  <pre>
 *  // face cost calculation
 *  cost = invisible * invisibleFaceCost +
 *         max( visible * visibleFaceCost , pixel * pixelCost)
 *  </pre>
 */
void RenderNode::determinePerformance(Window *window)
{
    int     c;
    double  t;
    UInt32  width, height;

    setVendor  (reinterpret_cast<const char *>(glGetString(GL_VENDOR)));
    setRenderer(reinterpret_cast<const char *>(glGetString(GL_RENDERER)));

    // try to find precalculated values
    for(c = 0; _predefined[c] != NULL; ++c)
    {
        if(_predefined[c]->getVendor() == getVendor() &&
           _predefined[c]->getRenderer() == getRenderer())
        {
            SLOG << "Predefined performance values used." << endl;
            *this = *_predefined[c];
            return;
        }
    }

    SLOG << "Start rendering benchmark" << endl;
    window->activate();

    // set viewport
    glViewport(0, 0, window->getWidth(), window->getHeight());

    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glDisable(GL_SCISSOR_TEST);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glDepthFunc(GL_LEQUAL);
    for(int i = 0; i < 8; ++i)
        glDisable(GL_LIGHT0 + i);
    glEnable(GL_LIGHT0);

    double  a1, a2, b, r;
    a1 = runFaceBench(1, 1);
    a2 = runFaceBench(4, 1);
    b = (a2 - .25 * a1) / .75;
    r = runRasterBench();

    _visibleFaceCost = Real32(1.0 / a1);
    _invisibleFaceCost = Real32(1.0 / b);
    _drawPixelCost = Real32(1.0 / r);

    // test write performance
    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    vector<UInt8>   pixels;
    width = window->getWidth();
    height = window->getHeight();
    pixels.resize(width * height * 4);
    glFinish();
    t = -getSystemTime();
    for(c = 0; c < 2; ++c)
    {
        glReadPixels(0, 
                     0, 
                     width, 
                     height, 
                     GL_RGB, 
                     GL_UNSIGNED_BYTE, 
                     &pixels[0]);
    }

    glFinish();
    t += getSystemTime();
    _readPixelCost = Real32(t / (c * width * height));

    // test write performance
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, width, 0, height);
    glRasterPos2i(0, 0);
    glDisable(GL_DEPTH_TEST);
    glFinish();
    t = -getSystemTime();
    for(c = 0; c < 2; ++c)
    {
        glDrawPixels(width, height, GL_RGB, GL_UNSIGNED_BYTE, &pixels[0]);
    }
    glFinish();
    t += getSystemTime();
    _writePixelCost = Real32(t / (c * width * height));
    glEnable(GL_DEPTH_TEST);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    SLOG << "End rendering benchmark" << endl;

    glPopAttrib();
}

/*! Write class contents to the given data stream
 */
void RenderNode::copyToBin(BinaryDataHandler &handle)
{
    handle.putValue(_invisibleFaceCost);
    handle.putValue(_visibleFaceCost);
    handle.putValue(_drawPixelCost);
    handle.putValue(_readPixelCost);
    handle.putValue(_writePixelCost);
}

/*! Read class contents from the given data stream
 */
void RenderNode::copyFromBin(BinaryDataHandler &handle)
{
    handle.getValue(_invisibleFaceCost);
    handle.getValue(_visibleFaceCost);
    handle.getValue(_drawPixelCost);
    handle.getValue(_readPixelCost);
    handle.getValue(_writePixelCost);
}

/*! Set render performance values for a group of render nodes. The
 *  parameter <code>begin</code> points to the first and the parameter 
 *  <code>end</code> points behind the last member of the group.
 *
 *  It is assumed the a render group is as fast as all its members together.
 *  Render costs of culled faces are handled different. In the worst case
 *  invisible faces have to be culled by each render node. To take this
 *  into account, we set the group speed to process culled faces to the
 *  average of all group members.
 */
void RenderNode::setGroup(const RenderNode *begin, const RenderNode *end)
{
    const RenderNode    *i;
    Real32              invisibleFaces = 0;
    Real32              visibleFaces = 0;
    Real32              drawPixels = 0;
    Real32              readPixels = 0;
    Real32              writePixels = 0;
    UInt32              count = 0;

    for(count = 0, i = begin; i != end; ++i, count++)
    {
        invisibleFaces += 1.f / i->_invisibleFaceCost;
        visibleFaces += 1.f / i->_visibleFaceCost;
        drawPixels += 1.f / i->_drawPixelCost;
        readPixels += 1.f / i->_readPixelCost;
        writePixels += 1.f / i->_writePixelCost;
    }

    _invisibleFaceCost = (1.f / invisibleFaces);
    _visibleFaceCost = (1.f / visibleFaces);
    _drawPixelCost = (1.f / drawPixels);
    _readPixelCost = (1.f / readPixels);
    _writePixelCost = (1.f / writePixels);
}

/*! Dump class contents
 */
void RenderNode::dump(void) const
{
    FLOG(("Vendor           : %s\n", _vendor.c_str()));
    FLOG(("Rnderer          : %s\n", _renderer.c_str()));
    FLOG(("Culled Faces/s   : %20.5f\n", 1.0 / _invisibleFaceCost));
    FLOG(("Faces/s          : %20.5f\n", 1.0 / _visibleFaceCost));
    FLOG(("Pixel/s          : %20.5f\n", 1.0 / _drawPixelCost));
    FLOG(("Read pixel/s     : %20.5f\n", 1.0 / _readPixelCost));
    FLOG(("Write pixel/s    : %20.5f\n", 1.0 / _writePixelCost));
}

/*! Render small faces as triangle stripes. With the parameter w
 *  it is possible to set the amount of visible faces. If w=1
 *  then all faces are visible. If w=2 then 1/2 of the faces are
 *  visible. The function returns the number of faces that could
 *  be rendered in one second. We are using triangle stripes with
 *  8 faces to run the benchmark.
 */
double RenderNode::runFaceBench(float w, int size)
{
    int     c;
    int     faces = 0;

    // vp size
    GLint   view[4];
    glGetIntegerv(GL_VIEWPORT, view);

    int vw = view[2], vh = view[3];

    // set projection
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, vw, 0, vh);
    glMatrixMode(GL_MODELVIEW);

    // create display list
    GLuint  dList = glGenLists(1);
    glNewList(dList, GL_COMPILE);
    glBegin(GL_TRIANGLE_STRIP);
    for(int x = 0; x <= (vw * w); x += size)
    {
        glNormal3f(0, 0, 1);
        glVertex3i(x, 0, 1);
        glNormal3f(0, 0, 1);
        glVertex3i(x, size, 1);
        if(((x & 3) == 3) && (x != (vw * w)))
        {
            glEnd();
            glBegin(GL_TRIANGLE_STRIP);
            glNormal3f(0, 0, 1);
            glVertex3i(x, 0, 1);
            glNormal3f(0, 0, 1);
            glVertex3i(x, size, 1);
        }
    }

    glEnd();
    glEndList();
    glFinish();

    // run test
    Time    t = 0;
    c = 0;
    glPushMatrix();
    do
    {
        glLoadIdentity();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glFinish();
        t -= getSystemTime();
        for(int y = 0; y < vh; y += size)
        {
            glCallList(dList);
            glTranslatef(0, GLfloat(size), 0);
        }

        glFinish();
        t += getSystemTime();
        c++;
    } while(t < .5);
    glPopMatrix();
    faces = Int32(((vw * w * 2) / size) * (vh / size) * c);

    // reset projection
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);

    glDeleteLists(dList, 1);
    return faces / t;
}

/*! Render one large face over the whole viewport. The returned value
 *  is the number of pixels that could be rendered in one second.
 */
double RenderNode::runRasterBench(void)
{
    int     c;

    // vp size
    GLint   view[4];
    glGetIntegerv(GL_VIEWPORT, view);

    int vw = view[2], vh = view[3];

    // set projection
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, vw, 0, vh);

    // create display list
    GLuint  dList = glGenLists(1);
    glNewList(dList, GL_COMPILE);
    glBegin(GL_QUADS);
    glVertex3i(0, 0, 1);
    glNormal3f(0, 0, 1);
    glVertex3i(0, vh - 1, 1);
    glNormal3f(0, 0, 1);
    glVertex3i(vw - 1, vh - 1, 1);
    glNormal3f(0, 0, 1);
    glVertex3i(vw - 1, 0, 1);
    glNormal3f(0, 0, 1);
    glEnd();
    glEndList();
    glFinish();

    // run test
    Time    t = 0;
    c = 0;
    do
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glFinish();
        t -= getSystemTime();
        glCallList(dList);
        glFinish();
        t += getSystemTime();
        c++;
    } 
    while(t < .5);

    // reset projection
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);

    glDeleteLists(dList, 1);
    return (vw * vh * c) / t;
}

bool RenderNode::cleanPredefined(void)
{
    for(UInt32 c = 0; _predefined[c] != NULL; ++c)
    {
        delete _predefined[c];

        _predefined[c] = NULL;
    }

    return true;
}

bool RenderNode::registerCleanup(void)
{
    addPreMPExitFunction(&RenderNode::cleanPredefined);

    return true;
}

StaticInitFuncWrapper RenderNode::RenderNodeInitCleanup(
    &RenderNode::registerCleanup);
