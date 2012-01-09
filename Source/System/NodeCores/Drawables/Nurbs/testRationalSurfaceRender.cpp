// OpenSG NURBS example: testRationalSurfaceRender.cpp
//
// Shows how to render rational NURBS surfaces
//
// In OpenSG, similarly to OpenGL and OpenInventor rational
// control points are expected in homogenious coordinates
// (as opposed to Euclidian coordinates) that is a rational
// control point is [xw yw zw w] for surfaces, and
// [xw yw w] for trimming curves where [x y z] (or [x y]) are
// the Euclidian coordinates of the control point.
//
// Although this is not enforced, negative weights are
// not allowed, if a surface/curve has negative weights
// the behaviour of the tessellator is undefined.
//
// Zero weights are allowed, but only for inner control points.
// In other words, the first and last control points of a trimming 
// curve (or the four corner control points of a surface) must all 
// have positive weights.
//
// Press the keys '1', '2' and '3' in order to switch between
// the different example objects. Note that especially in the 
// case of the torus and the teapot, tessellation takes some
// time so expect some delay when switching to the objects for
// the first time.

#include "OSGGLUT.h"
#include "OSGConfig.h"
#include "OSGSimpleSceneManager.h"
#include "OSGSimpleMaterial.h"
#include "OSGGLUTWindow.h"
#include "OSGSolidBackground.h"
#include "OSGSurface.h"
#include "OSGSwitch.h"
#include "OSGCoredNodePtr.h"
#include "OSGSceneFileHandler.h"


OSG::SimpleSceneManagerRefPtr  g_mgr   = NULL;
OSG::NodeRefPtr                g_scene = NULL;
std::vector<OSG::Surface *>    g_teapotSurfaces;
std::vector<OSG::Surface *>    g_torusSurfaces;
std::vector<OSG::Surface *>    g_cylinderSurfaces;
std::vector<OSG::Surface *>   *g_currentSurfaces;

// redraw the window
void display(void)
{
    // render
    g_mgr->redraw();

}

// react to size changes
void reshape(int w, int h)
{
    g_mgr->resize(w,h);
    glutPostRedisplay();
}

// react to mouse button presses
void mouse(int button, int state, int x, int y)
{
    if (state)
        g_mgr->mouseButtonRelease(button, x, y);
    else
        g_mgr->mouseButtonPress(button, x, y);
        
    glutPostRedisplay();
}

// react to mouse motions with pressed buttons
void motion(int x, int y)
{
    g_mgr->mouseMove(x, y);
    glutPostRedisplay();
}


void setModel(OSG::Int32 which)
{
    OSG::Switch *s = dynamic_cast<OSG::Switch *>(g_scene->getCore());
    s->setChoice(which);

    switch(which)
    {
    case 0:   g_currentSurfaces = &g_teapotSurfaces;
              break;

    case 1:   g_currentSurfaces = &g_torusSurfaces;
              break;

    case 2:   g_currentSurfaces = &g_cylinderSurfaces;
              break;

    default: std::cerr << "setModel [" << which << "] out of range."
                       << std::endl;
             break;
    }

    if(g_mgr != NULL)
        g_mgr->showAll();
}

// react to keys
void keyboard(unsigned char k, int, int)
{
    switch(k)
    {
    case 27:    g_mgr   = NULL;
                g_scene = NULL;
                exit(1);
    case 'y':
    case 'z':
                glPolygonMode( GL_FRONT_AND_BACK, GL_POINT);
                std::cerr << "PolygonMode: Point." << std::endl;
                break;
    case 'x':   glPolygonMode( GL_FRONT_AND_BACK, GL_LINE);
                std::cerr << "PolygonMode: Line." << std::endl;
                break;
    case 'c':   glPolygonMode( GL_FRONT_AND_BACK, GL_FILL);
                std::cerr << "PolygonMode: Fill." << std::endl;
                break;
    case '1':   std::cerr<<"Model: teapot."<<std::endl;
                setModel(0);
                break;
    case '2':   std::cerr<<"Model: torus."<<std::endl;
                setModel(1);
                break;
    case '3':   std::cerr<<"Model: trimmed cylinder."<<std::endl;
                setModel(2);
                break;
    case 'o':   OSG::SceneFileHandler::the()->write(g_scene, "out.osb");
                break;

    case 'f':   for(OSG::UInt32 i = 0; i < g_currentSurfaces->size(); ++i)
                {
                    g_currentSurfaces->at(i)->setError(
                        2 * g_currentSurfaces->at(i)->getError());
                }
                break;

    case 'g':   for(OSG::UInt32 i = 0; i < g_currentSurfaces->size(); ++i)
                {
                    g_currentSurfaces->at(i)->setError(
                        g_currentSurfaces->at(i)->getError() / 2);
                }
                break;

    default:    break;
    }
}

// Helper function to create an untrimmed rational OSG::Surface Core+Node
// from the controlpoints, dimensions in U & V,
// knotvectors in U & V and the desired error and material.
OSG::NodeTransitPtr makeSurface(const int numcps, const float xyzw[][4],
                                const int dimU, const int dimV,
                                const int numknotsU, const float *knotsU,
                                const int numknotsV, const float *knotsV,
                                const float error, OSG::Material *mat)
{
    OSG::SurfaceRefPtr surface;
    OSG::NodeTransitPtr         ret = 
        OSG::makeCoredNode<OSG::Surface>(&surface); 
    OSG::GeoPnt4fPropertyRefPtr cps = OSG::GeoPnt4fProperty::create();
    int i;

    cps->clear();
    for (i = 0; i < numcps; ++i)
    {
        cps->editField().push_back(OSG::Pnt4f(xyzw[i][0], xyzw[i][1], 
                                              xyzw[i][2], xyzw[i][3]));
    }

    // let's clear the trimming
    surface->removeCurves();
    // set up dimensions and knot vectors:
    surface->setDimU( dimU );
    surface->setDimV( dimV );
    surface->editMFKnotsU()->clear();
    for (i = 0; i < numknotsU; ++i)
    {
        surface->editMFKnotsU()->push_back(knotsU[i]);
    }

    surface->editMFKnotsV()->clear();
    for (i = 0; i < numknotsV; ++i)
    {
        surface->editMFKnotsV()->push_back(knotsV[i]);
    }
    // set control points
    surface->setControlPoints(cps);
    // set error
    surface->setError(error);
    // and finally set the material
    surface->setMaterial(mat);

    return ret;
}

// Helper function to add a polynomial trimcurve to an OSG::Surface NodeCore
void addTrimCurve(OSG::Surface *surf, const int numcps, const float xy[][2],
                  const int dim, const int numknots, const float *knots,
                  bool startnewloop = false)
{
    std::vector<OSG::Real64> knotv;
    std::vector<OSG::Pnt2f> cps;
    int i;
    for (i = 0; i < numcps; ++i)
    {
        cps.push_back(OSG::Pnt2f(xy[i][0], xy[i][1]));
    }
    for (i = 0; i < numknots; ++i)
    {
        knotv.push_back(knots[i]);
    }

    surf->addCurve(dim, knotv, cps, startnewloop);
}

// Helper function to add a rational trimcurve to an OSG::Surface NodeCore
void addTrimCurve(OSG::Surface *surf, const int numcps, const float xyw[][3],
                  const int dim, const int numknots, const float *knots,
                  bool startnewloop = false)
{
    std::vector<OSG::Real64> knotv;
    std::vector<OSG::Pnt3f> cps;
    int i;
    for (i = 0; i < numcps; ++i)
    {
        cps.push_back(OSG::Pnt3f(xyw[i][0], xyw[i][1], xyw[i][2]));
    }
    for (i = 0; i < numknots; ++i)
    {
        knotv.push_back(knots[i]);
    }

    surf->addCurve(dim, knotv, cps, startnewloop);
}


// This function creates the classic Utah teapot from 4 NURBS
// surfaces: one surface each for the lid, body, handle and spout.
// The "classic" representation is using 18 rational Bezier patches,
// but in order to show the construction of more complex surfaces
// these have been combined into as few NURBS surfaces as possible.
OSG::NodeTransitPtr makeTeapot(void)
{
    OSG::SimpleMaterialRefPtr teapotmat =  OSG::SimpleMaterial::create();

    teapotmat->setDiffuse(  OSG::Color3f(0.8, 0.8, 0.8));
    teapotmat->setAmbient(  OSG::Color3f(0.2, 0.2, 0.2));
    teapotmat->setEmission( OSG::Color3f(0.02, 0.02, 0.02) );
    teapotmat->setSpecular( OSG::Color3f(0.78, 0.78, 0.78) );
    teapotmat->setShininess( 128 );

    OSG::NodeTransitPtr teapotroot = OSG::makeCoredNode<OSG::Group>();
    float knots11[11] = {0, 0, 0, 0, 0.5, 0.5, 0.5, 1, 1, 1, 1};
    float knots14[14] = {0, 0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 3};
    float knots_circle[8] = {0, 0, 0, 0.5, 0.5, 1, 1, 1};
    float lidcps[35][4] = {
        { 0.0000, 4.0000, 0.0000, 1.0000},
        { 0.0000, 4.0000, 0.8000, 1.0000},
        { 0.0000, 3.6000, 0.0000, 1.0000},
        { 0.0000, 3.4000, 0.2000, 1.0000},
        { 0.0000, 3.2000, 0.4000, 1.0000},
        { 0.0000, 3.2000, 1.3000, 1.0000},
        { 0.0000, 3.0000, 1.3000, 1.0000},
    
        {-0.0000, 0.0000, 0.0000, 0.0000},
        {-0.8000, 0.0000, 0.0000, 0.0000},
        {-0.0000, 0.0000, 0.0000, 0.0000},
        {-0.2000, 0.0000, 0.0000, 0.0000},
        {-0.4000, 0.0000, 0.0000, 0.0000},
        {-1.3000, 0.0000, 0.0000, 0.0000},
        {-1.3000, 0.0000, 0.0000, 0.0000},
    
        { 0.0000, 4.0000,-0.0000, 1.0000},
        { 0.0000, 4.0000,-0.8000, 1.0000},
        { 0.0000, 3.6000,-0.0000, 1.0000},
        { 0.0000, 3.4000,-0.2000, 1.0000},
        { 0.0000, 3.2000,-0.4000, 1.0000},
        { 0.0000, 3.2000,-1.3000, 1.0000},
        { 0.0000, 3.0000,-1.3000, 1.0000},
    
        { 0.0000, 0.0000, 0.0000, 0.0000},
        { 0.8000, 0.0000, 0.0000, 0.0000},
        { 0.0000, 0.0000, 0.0000, 0.0000},
        { 0.2000, 0.0000, 0.0000, 0.0000},
        { 0.4000, 0.0000, 0.0000, 0.0000},
        { 1.3000, 0.0000, 0.0000, 0.0000},
        { 1.3000, 0.0000, 0.0000, 0.0000},
    
        { 0.0000, 4.0000, 0.0000, 1.0000},
        { 0.0000, 4.0000, 0.8000, 1.0000},
        { 0.0000, 3.6000, 0.0000, 1.0000},
        { 0.0000, 3.4000, 0.2000, 1.0000},
        { 0.0000, 3.2000, 0.4000, 1.0000},
        { 0.0000, 3.2000, 1.3000, 1.0000},
        { 0.0000, 3.0000, 1.3000, 1.0000},
    };
    OSG::NodeRefPtr lid = makeSurface(35, lidcps, 2, 3, 8, knots_circle,
                                      11, knots11, 0.005, teapotmat);

    g_teapotSurfaces.push_back(dynamic_cast<OSG::Surface *>(lid->getCore()));

    float bodycps[50][4] = {
        { 0.0000, 3.0000, 1.4000, 1.0000},
        { 0.0000, 3.1750, 1.3375, 1.0000},
        { 0.0000, 3.1750, 1.4375, 1.0000},
        { 0.0000, 3.0000, 1.5000, 1.0000},
        { 0.0000, 2.3000, 1.7500, 1.0000},
        { 0.0000, 1.6000, 2.0000, 1.0000},
        { 0.0000, 1.0000, 2.0000, 1.0000},
        { 0.0000, 0.4000, 2.0000, 1.0000},
        { 0.0000, 0.2000, 1.5000, 1.0000},
        { 0.0000, 0.0000, 1.5000, 1.0000},
    
        {-1.4000, 0.0000, 0.0000, 0.0000},
        {-1.3375, 0.0000, 0.0000, 0.0000},
        {-1.4375, 0.0000, 0.0000, 0.0000},
        {-1.5000, 0.0000, 0.0000, 0.0000},
        {-1.7500, 0.0000, 0.0000, 0.0000},
        {-2.0000, 0.0000, 0.0000, 0.0000},
        {-2.0000, 0.0000, 0.0000, 0.0000},
        {-2.0000, 0.0000, 0.0000, 0.0000},
        {-1.5000, 0.0000, 0.0000, 0.0000},
        {-1.5000, 0.0000, 0.0000, 0.0000},
    
        { 0.0000, 3.0000,-1.4000, 1.0000},
        { 0.0000, 3.1750,-1.3375, 1.0000},
        { 0.0000, 3.1750,-1.4375, 1.0000},
        { 0.0000, 3.0000,-1.5000, 1.0000},
        { 0.0000, 2.3000,-1.7500, 1.0000},
        { 0.0000, 1.6000,-2.0000, 1.0000},
        { 0.0000, 1.0000,-2.0000, 1.0000},
        { 0.0000, 0.4000,-2.0500, 1.0000},
        { 0.0000, 0.2000,-1.5000, 1.0000},
        { 0.0000, 0.0000,-1.5000, 1.0000},
    
        { 1.4000, 0.0000, 0.0000, 0.0000},
        { 1.3375, 0.0000, 0.0000, 0.0000},
        { 1.4375, 0.0000, 0.0000, 0.0000},
        { 1.5000, 0.0000, 0.0000, 0.0000},
        { 1.7500, 0.0000, 0.0000, 0.0000},
        { 2.0000, 0.0000, 0.0000, 0.0000},
        { 2.0000, 0.0000, 0.0000, 0.0000},
        { 2.0000, 0.0000, 0.0000, 0.0000},
        { 1.5000, 0.0000, 0.0000, 0.0000},
        { 1.5000, 0.0000, 0.0000, 0.0000},
    
        { 0.0000, 3.0000, 1.4000, 1.0000},
        { 0.0000, 3.1750, 1.3375, 1.0000},
        { 0.0000, 3.1750, 1.4375, 1.0000},
        { 0.0000, 3.0000, 1.5000, 1.0000},
        { 0.0000, 2.3000, 1.7500, 1.0000},
        { 0.0000, 1.6000, 2.0000, 1.0000},
        { 0.0000, 1.0000, 2.0000, 1.0000},
        { 0.0000, 0.4000, 2.0000, 1.0000},
        { 0.0000, 0.2000, 1.5000, 1.0000},
        { 0.0000, 0.0000, 1.5000, 1.0000},

    };
    OSG::NodeRefPtr body = makeSurface(50, bodycps, 2, 3, 8, knots_circle,
                                       14, knots14, 0.005, teapotmat);

    g_teapotSurfaces.push_back(dynamic_cast<OSG::Surface *>(body->getCore()));

    float handlecps[35][4] = {
        { 1.5000, 2.8000, 0.0000, 1.0000},
        { 2.5000, 2.8000, 0.0000, 1.0000},
        { 3.0000, 2.8000, 0.0000, 1.0000},
        { 3.0000, 2.2000, 0.0000, 1.0000},
        { 3.0000, 1.6000, 0.0000, 1.0000},
        { 2.6500, 1.0500, 0.0000, 1.0000},
        { 1.9000, 0.6000, 0.0000, 1.0000},
    
        { 0.0000, 0.0000, 0.3000, 0.0000},
        { 0.0000, 0.0000, 0.3000, 0.0000},
        { 0.0000, 0.0000, 0.3000, 0.0000},
        { 0.0000, 0.0000, 0.3000, 0.0000},
        { 0.0000, 0.0000, 0.3000, 0.0000},
        { 0.0000, 0.0000, 0.3000, 0.0000},
        { 0.0000, 0.0000, 0.3000, 0.0000},
    
        { 1.6000, 2.5000, 0.0000, 1.0000},
        { 2.3000, 2.5000, 0.0000, 1.0000},
        { 2.7000, 2.5000, 0.0000, 1.0000},
        { 2.7000, 2.2000, 0.0000, 1.0000},
        { 2.7000, 1.9000, 0.0000, 1.0000},
        { 2.5000, 1.5000, 0.0000, 1.0000},
        { 2.0000, 1.0000, 0.0000, 1.0000},
    
        { 0.0000, 0.0000,-0.3000, 0.0000},
        { 0.0000, 0.0000,-0.3000, 0.0000},
        { 0.0000, 0.0000,-0.3000, 0.0000},
        { 0.0000, 0.0000,-0.3000, 0.0000},
        { 0.0000, 0.0000,-0.3000, 0.0000},
        { 0.0000, 0.0000,-0.3000, 0.0000},
        { 0.0000, 0.0000,-0.3000, 0.0000},
    
        { 1.5000, 2.8000, 0.0000, 1.0000},
        { 2.5000, 2.8000, 0.0000, 1.0000},
        { 3.0000, 2.8000, 0.0000, 1.0000},
        { 3.0000, 2.2000, 0.0000, 1.0000},
        { 3.0000, 1.6000, 0.0000, 1.0000},
        { 2.6500, 1.0500, 0.0000, 1.0000},
        { 1.9000, 0.6000, 0.0000, 1.0000},
    };
    
    OSG::NodeRefPtr handle = makeSurface(35, handlecps, 2, 3, 8, knots_circle,
                                         11, knots11, 0.005, teapotmat);

    g_teapotSurfaces.push_back(dynamic_cast<OSG::Surface *>(handle->getCore()));

    float spoutcps[35][4] = {
        {-1.7000, 0.6000, 0.0000, 1.0000},
        {-3.1000, 0.9000, 0.0000, 1.0000},
        {-2.4000, 2.6000, 0.0000, 1.0000},
        {-3.3000, 3.0000, 0.0000, 1.0000},
        {-3.5250, 3.1250, 0.0000, 1.0000},
        {-3.4500, 3.1500, 0.0000, 1.0000},
        {-3.2000, 3.0000, 0.0000, 1.0000},
    
        { 0.0000, 0.0000, 0.6600, 0.0000},
        { 0.0000, 0.0000, 0.6600, 0.0000},
        { 0.0000, 0.0000, 0.2500, 0.0000},
        { 0.0000, 0.0000, 0.2500, 0.0000},
        { 0.0000, 0.0000, 0.2500, 0.0000},
        { 0.0000, 0.0000, 0.1500, 0.0000},
        { 0.0000, 0.0000, 0.1500, 0.0000},
    
        {-1.7000, 1.7000, 0.0000, 1.0000},
        {-2.6000, 1.7000, 0.0000, 1.0000},
        {-2.3000, 2.6000, 0.0000, 1.0000},
        {-2.7000, 3.0000, 0.0000, 1.0000},
        {-2.8000, 3.1000, 0.0000, 1.0000},
        {-2.9000, 3.1000, 0.0000, 1.0000},
        {-2.8000, 3.0000, 0.0000, 1.0000},
    
        { 0.0000, 0.0000,-0.6600, 0.0000},
        { 0.0000, 0.0000,-0.6600, 0.0000},
        { 0.0000, 0.0000,-0.2500, 0.0000},
        { 0.0000, 0.0000,-0.2500, 0.0000},
        { 0.0000, 0.0000,-0.2500, 0.0000},
        { 0.0000, 0.0000,-0.1500, 0.0000},
        { 0.0000, 0.0000,-0.1500, 0.0000},
    
        {-1.7000, 0.6000, 0.0000, 1.0000},
        {-3.1000, 0.9000, 0.0000, 1.0000},
        {-2.4000, 2.6000, 0.0000, 1.0000},
        {-3.3000, 3.0000, 0.0000, 1.0000},
        {-3.5250, 3.1250, 0.0000, 1.0000},
        {-3.4500, 3.1500, 0.0000, 1.0000},
        {-3.2000, 3.0000, 0.0000, 1.0000},
    };
    OSG::NodeRefPtr spout = makeSurface(35, spoutcps, 2, 3, 8, knots_circle,
                                        11, knots11, 0.005, teapotmat);

    g_teapotSurfaces.push_back(dynamic_cast<OSG::Surface *>(spout->getCore()));
    
    teapotroot->addChild(lid);
    teapotroot->addChild(body);
    teapotroot->addChild(handle);
    teapotroot->addChild(spout);

    return teapotroot;
}

// This function creates a torus from a single NURBS surface
// using only 25 control points (of which 12 are unique).
// Similarly to the teapot, this uses the half-circle
// constructed from 3 control points (of which the middle point
// is infinite) which is then mirrored to form a full circle.
// (See the NURBS book [Piegl and Tiller], pp. 296, Ex7.1 (Figure 7.15)
// for details on the half-circle.)
OSG::NodeTransitPtr makeTorus(void)
{
    OSG::SimpleMaterialRefPtr torusmat =  OSG::SimpleMaterial::create();

    torusmat->setDiffuse(  OSG::Color3f(1.0, 0.0, 0.2));
    torusmat->setAmbient(  OSG::Color3f(0.2, 0.2, 0.2));
    torusmat->setEmission( OSG::Color3f(0.02, 0.02, 0.02) );
    torusmat->setSpecular( OSG::Color3f(0.78, 0.78, 0.78) );
    torusmat->setShininess( 128 );

    float knots_circle[8] = {0, 0, 0, 0.5, 0.5, 1, 1, 1};
    float toruscps[25][4] = {    
        { 1.00,     0,  .75, 1}, //
        {  .25,     0,    0, 0}, //
        { 1.00,     0, 1.25, 1}, // 
        { -.25,     0,    0, 0}, //
        { 1.00,     0,  .75, 1},
        {    0,  1.00,    0, 0}, //
        {    0,   .25,    0, 0}, //
        {    0,  1.00,    0, 0},
        {    0,  -.25,    0, 0}, //
        {    0,  1.00,    0, 0},
        {-1.00,     0,  .75, 1}, //
        { -.25,     0,    0, 0}, //
        {-1.00,     0, 1.25, 1}, //
        {  .25,     0,    0, 0}, //
        {-1.00,     0,  .75, 1},
        {    0, -1.00,    0, 0}, //
        {    0,  -.25,    0, 0}, 
        {    0, -1.00,    0, 0},
        {    0,   .25,    0, 0},
        {    0, -1.00,    0, 0},
        { 1.00,     0,  .75, 1},
        {  .25,     0,    0, 0},
        { 1.00,     0, 1.25, 1},
        { -.25,     0,    0, 0},
        { 1.00,     0,  .75, 1},
    };

    OSG::NodeTransitPtr torus = makeSurface(25, toruscps, 2, 2, 8, knots_circle,
                                            8, knots_circle, 0.005, torusmat);
    g_torusSurfaces.push_back(dynamic_cast<OSG::Surface *>(torus->getCore()));

    return torus;
}

// This function creates a cylinder similarly to the teapot 
// and the torus above. This time the cylinder is trimmed with 
// a circle defined by 9 square-based control points to show 
// an example of defining a circle without using infinite control 
// points (see [Piegl and Tiller], pp. 299, Ex7.2 (Figure 7.16)) as
// well as to show how to define a rational trimming curve.
OSG::NodeTransitPtr makeTrimmedCylinder(void)
{
    OSG::SimpleMaterialRefPtr cylmat =  OSG::SimpleMaterial::create();

    cylmat->setDiffuse(  OSG::Color3f(0.0, 0.8, 0.7));
    cylmat->setAmbient(  OSG::Color3f(0.2, 0.2, 0.2));
    cylmat->setEmission( OSG::Color3f(0.02, 0.02, 0.02) );
    cylmat->setSpecular( OSG::Color3f(0.78, 0.78, 0.78) );
    cylmat->setShininess( 128 );

    float knots4[4] = {0, 0, 1, 1};
    float knots_circle[8] = {0, 0, 0, 0.5, 0.5, 1, 1, 1};
    float knots_outertrim[7] = {0, 0, 1, 2, 3, 4, 4};
    float knots_trimcircle[12] = {0, 0, 0, 0.25, 0.25, 0.5, 
                                  0.5, 0.75, 0.75, 1, 1, 1};
    float cylcps[10][4] = {    
        { 1.00,     0, -.50, 1},
        { 1.00,     0,  .50, 1},
        {    0,  1.00,    0, 0},
        {    0,  1.00,    0, 0},
        {-1.00,     0, -.50, 1},
        {-1.00,     0,  .50, 1},
        {    0, -1.00,    0, 0},
        {    0, -1.00,    0, 0},
        { 1.00,     0, -.50, 1},
        { 1.00,     0,  .50, 1},
    };
    float outertrim_cps[5][2] = {
        {0, 0},
        {1, 0},
        {1, 1},
        {0, 1},
        {0, 0},
    };
    float trimcircle_cps[9][3] = {
        {0.541667, 0.5,      1},
        {0.383016, 0.235702, 0.707107},
        {0.5,      0.333333, 1},
        {0.324091, 0.235702, 0.707107},
        {0.458333, 0.5,      1},
        {0.324091, 0.471405, 0.707107},
        {0.5,      0.666667, 1},
        {0.383016, 0.471405, 0.707107},
        {0.541667, 0.5,      1},
    };
    OSG::NodeTransitPtr cylnode = makeSurface(10, cylcps, 2, 1, 8, knots_circle,
                                              4, knots4, 0.001, cylmat);
    OSG::Surface *s = dynamic_cast<OSG::Surface *>(cylnode->getCore());
    // add outer trimming around the domain
    addTrimCurve(s, 5, outertrim_cps, 1, 7, knots_outertrim, true);
    // add inside circle trimming
    addTrimCurve(s, 9, trimcircle_cps, 2, 12, knots_trimcircle, true);

    g_cylinderSurfaces.push_back(
        dynamic_cast<OSG::Surface *>(cylnode->getCore()));

    return cylnode;
}

OSG::NodeTransitPtr makeScene(void)
{
    OSG::NodeTransitPtr root = OSG::makeCoredNode<OSG::Switch>();

    root->addChild(makeTeapot());
    root->addChild(makeTorus());
    root->addChild(makeTrimmedCylinder());

    return root;
}

int main(int argc, char **argv)
{
    printf("Press the keys '1', '2' and '3' in order to switch between "
           "the different example objects.\n");

    OSG::osgInit(argc,argv);
    // GLUT init
    glutInit(&argc, argv);
    glutInitWindowSize(800,600);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    int winid = glutCreateWindow("OpenSG");
    
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);

    {
        OSG::GLUTWindowRefPtr gwin = OSG::GLUTWindow::create();
        gwin->setGlutId(winid);
        gwin->init();
    
        // create the scene
        g_scene = makeScene();
        setModel(0);
        
        if ( g_scene == NULL )
        {
            std::cerr<<"makeScene returned NullFC, exiting..."<<std::endl;
            return -1;
        }
    
        // create the SimpleSceneManager helper
        g_mgr = OSG::SimpleSceneManager::create();
    
        // create the window and initial camera/viewport
        g_mgr->setWindow( gwin );
        // tell the manager what to manage
        g_mgr->setRoot  ( g_scene );
        
        // show the whole scene
        g_mgr->showAll();
        g_mgr->redraw();
        OSG::SolidBackgroundRefPtr bgr = OSG::SolidBackground::create();
        bgr->setColor(OSG::Color3f( 0.7, 0.7, 0.7 ));
        g_mgr->getWindow()->getPort(0)->setBackground(bgr);
    }
    
    // GLUT main loop
    glutMainLoop();

    return 0;
}
