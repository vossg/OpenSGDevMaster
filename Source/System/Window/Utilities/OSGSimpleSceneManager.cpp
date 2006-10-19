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
#include <OSGBaseFunctions.h>
#include <OSGImageFileType.h>
#include <OSGSolidBackground.h>
#include <OSGViewport.h>
#include <OSGLogoData.h>
#include <OSGSimpleStatisticsForeground.h>
//#include <OSGStatElemTypes.h>
//#include <OSGStatCollector.h>
#include <OSGDrawable.h>
#include <OSGPointLight.h>
#include <OSGSpotLight.h>
#include <OSGDirectionalLight.h>

#include "OSGSimpleSceneManager.h"

#if defined(OSG_WIN32_ICL) && !defined(OSG_CHECK_FIELDSETARG)
#pragma warning (disable : 383)
#endif


OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::SimpleSceneManager
    \ingroup GrpSystemWindow

    SimpleSceneManager manages the OpenSG components that are needed to do
    simple applications that just want to display some geometry. It takes the
    window to render into and the root node of the graph to display and takes
    care of creating the necessary additional OpenSG objects, like a viewport
    for the window,
 */


/*! \var SimpleSceneManager::MouseLeft
    The constant for the left mouse button.
 */

/*! \var SimpleSceneManager::MouseMiddle
    The constant for the middle mouse button.
 */

/*! \var SimpleSceneManager::MouseRight
    The constant for the right mouse button.
 */

/*! \var SimpleSceneManager::MouseUp
    The constant for the mouse wheel up (away from the hand) motion.
 */

/*! \var SimpleSceneManager::MouseDown
    The constant for the mouse wheel down (towards the hand) motion.
 */


/*! \var SimpleSceneManager::_win
    The managed window. Has to be set by the user.
 */

/*! \var SimpleSceneManager::_root
    The root node to be rendered. Has to be set by the user.
 */

/*! \var SimpleSceneManager::_highlight
    The Node to be highlighted (highlit? ;).  Has to be set by the user.
    May be NullFC (which is the default), in which case nothing is highlighted.
 */

/*! \var SimpleSceneManager::_highlightNode
    The node used to hold the actual highlight geometry.
 */

/*! \var SimpleSceneManager::_highlightPoints
    The highlight points geo property. These are adjusted to include the
    _highlight object for every rendered frame.
 */

/*! \var SimpleSceneManager::_internalRoot
    The real root used internally. It's the root for the light and has the
    camera beacon and the given root as children.
 */

/*! \var SimpleSceneManager::_headlight
    The core for the light source.
 */

/*! \var SimpleSceneManager::_foreground
    ImageForeground used by the logo.
 */

/*! \var SimpleSceneManager::_statstate
    Bool to indicate if statistics should be displayed or not.
 */

/*! \var SimpleSceneManager::_action
    The action used to render the scene.
 */

/*! \var SimpleSceneManager::_ownAction
    The action created by this SSM.
 */

/*! \var SimpleSceneManager::_cart
    The core of the camera beacon. Manipulated by the navigator.
 */

/*! \var SimpleSceneManager::_camera
    The camera used to view the scene.
 */

/*! \var SimpleSceneManager::_navigator
    The navigator for viewer manipulation.
 */

/*! \var SimpleSceneManager::_lastx
    The x position of the last mouse event, needed by the navigator.
 */

/*! \var SimpleSceneManager::_lasty
    The y position of the last mouse event, needed by the navigator.
 */

/*! \var SimpleSceneManager::_mousebuttons
    Storage for the actively pressed mouse buttons. Needed to do the right
    thing for mouse motions, as mouseMove() doesn't get them.
 */


/*! \var SimpleSceneManager::_highlightMaterial
    The material used by the highlight object.
 */
SimpleMaterialPtr SimpleSceneManager::_highlightMaterial;

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

/*! Constructor
 */

SimpleSceneManager::SimpleSceneManager(void) :
    _win            (NullFC),
    _root           (NullFC),
    _foreground     (NullFC),
    /*_statforeground (NullFC),*/
    _statstate      (false),

    /*_highlight      (NullFC),
    _highlightNode  (NullFC),
    _highlightPoints(NullFC),*/

    _internalRoot   (NullFC),
    _headlight      (NullFC),
    _action         (NULL  ),
    _ownAction      (NULL  ),
#ifdef OSG_CLEANED_RENDERACTION
    _taction        (NULL  ),
#endif
    _cart           (NullFC),
    _camera         (NullFC),
    _navigator      (      ),

    _lastx          (TypeTraits<Int16>::getMax()),
    _lasty          (TypeTraits<Int16>::getMax()),
    _mousebuttons   (0                             ),
    _traversalAction(false                         )
{
}


/*! pseudo constructor. Standard interface for OpenSG object creation.
 */
SimpleSceneManager* SimpleSceneManager::create(void)
{
    return new SimpleSceneManager;
}

/*! Destructor
 */

SimpleSceneManager::~SimpleSceneManager(void)
{
    delete _ownAction;

    if(_action && _action != _ownAction)
        delete _action;

#ifdef OSG_CLEANED_RENDERACTION
    if(_taction)
        delete _taction;
#endif

    setRoot(NullFC); // sub root

    if(_internalRoot != NullFC)
        subRef(_internalRoot);

    if(_camera != NullFC)
        subRef(_camera);
}


/*! get the window to be used for display
 */
WindowPtr SimpleSceneManager::getWindow(void)
{
    return _win;
}

/*! get the root of the displayed tree
 */
NodePtr SimpleSceneManager::getRoot(void)
{
    return _root;
}

/*! get the navigator
 */
Navigator *SimpleSceneManager::getNavigator(void)
{
    return &_navigator;
}

/*! get the headlight state
 */
bool SimpleSceneManager::getHeadlightState(void)
{
    return _headlight->getOn();
}

/*! get the headlight
 */
DirectionalLightPtr SimpleSceneManager::getHeadlight(void)
{
    return _headlight;
}

/*! get the camera
 */
PerspectiveCameraPtr SimpleSceneManager::getCamera(void)
{
    return _camera;
}

/*! set the window to be used for display
 */
void SimpleSceneManager::setWindow(WindowPtr win)
{
    _win = win;
    if(_win->getMFPort()->size() > 0 && _win->getPort(0) != NullFC)
        _navigator.setViewport(_win->getPort(0));
}

/*! get the highlight object
 */
NodePtr SimpleSceneManager::getHighlight(void)
{
    return NullFC; //_highlight;
}

/*! get the action used to render the scene
 */
DrawActionBase *SimpleSceneManager::getAction(void)
{
    return _action;
}

#ifdef OSG_CLEANED_RENDERACTION
/*! get the traversal action used to render the scene
 */
RenderTraversalAction *SimpleSceneManager::getRenderTraversalAction(void)
{
    return _taction;
}
#endif

/*! set the action used to render the scene. Use NULL to set to
    internally created action.
 */

void SimpleSceneManager::setAction(RenderAction *action)
{
    bool statstate = _statstate;

    if(_action != NULL && statstate)
        setStatistics(false);

    if(action == NULL)
    {
        _action = _ownAction;
    }
    else
    {
        _action = action;
    }

    if(statstate)
        setStatistics(true);
}

#ifdef OSG_CLEANED_RENDERACTION
void SimpleSceneManager::setAction(RenderTraversalAction *action)
{
    bool statstate = _statstate;

    if(_taction != NULL)
    {
        if(statstate)
            setStatistics(false);
        delete _taction;
    }

    _taction = action;
    if(statstate)
        setStatistics(true);
}
#endif

/*! set the root of the displayed tree
 */
void SimpleSceneManager::setRoot(NodePtr root)
{
    if(_internalRoot == NullFC)
    {
        initialize();
    }

    if(_root != root)
    {
        if(_root != NullFC)
        {
            _internalRoot->subChild(_root);
        }

        _root = root;

        if(_root != NullFC)
        {
            _internalRoot->addChild(_root);
        }
    }
}

/*! set the headlight setting
 */
void SimpleSceneManager::setHeadlight(bool on)
{
    if(_internalRoot == NullFC)
    {
        initialize();
    }

    _headlight->setOn(on);
}

/*! turn headlight on.
 */
void SimpleSceneManager::turnHeadlightOn(void)
{
    setHeadlight(true);
}


void SimpleSceneManager::setUseTraversalAction(bool s)
{
    _traversalAction = s;
}

bool SimpleSceneManager::getUseTraversalAction(void)
{
    return _traversalAction;
}


/*! turn headlight off.
 */
void SimpleSceneManager::turnHeadlightOff(void)
{
    setHeadlight(false);
}

/*! set the highlight object
 */
void SimpleSceneManager::setHighlight(NodePtr highlight)
{
#if 0 // amz
    _highlight = highlight;
    highlightChanged();
#endif
}

/*! set the statistics setting. Only works after the window has been created.
 */
void SimpleSceneManager::setStatistics(bool on)
{
#if 1 // amz
    if(_statforeground != NullFC && on != _statstate)
    {
        ViewportPtr vp = _win->getPort()[0];

        if(on)
        {
            vp->addForeground(_statforeground);
            _action->setStatistics(&_statforeground->editCollector());
        }
        else
        {
            vp->removeFromForegrounds(_statforeground);
            _action->setStatistics(NULL);
        }

        _statstate = on;
    }
#endif
}

/*-------------------------------------------------------------------------*/
/*                               Updates                                   */

/*! create the parts that the app needs: viewport, camera, base graph etc.
 */
void SimpleSceneManager::initialize(void)
{
    // the rendering action
    _ownAction = RenderAction::create();
    _action    = _ownAction;

#ifdef OSG_CLEANED_RENDERACTION
    _taction = RenderTraversalAction::create();
#endif

    // the camera and light beacon
    NodePtr cartN = Node::create();
    _cart = Transform::create();

    cartN->setCore(_cart);

    // the headlight
    _internalRoot = Node::create();
    _headlight    = DirectionalLight::create();

    addRef(_internalRoot);

    _internalRoot->setCore(_headlight);
    _internalRoot->addChild(cartN);


    _headlight->setAmbient  (.3, .3, .3, 1);
    _headlight->setDiffuse  ( 1,  1,  1, 1);
    _headlight->setSpecular ( 1,  1,  1, 1);
    _headlight->setDirection( 0,  0,  1);
    _headlight->setBeacon   (cartN);

    // the camera
    _camera = PerspectiveCamera::create();

    addRef(_camera);

    _camera->setBeacon(cartN);
    _camera->setFov   (osgDegree2Rad(60.f));
    _camera->setNear  (0.1f);
    _camera->setFar   (10000.f);

    // need a viewport?
    if(_win != NullFC && _win->getPort().size() == 0)
    {
        // I'd like this to be a gradient background, but it still has
        // problems on Linux/nVidia

        SolidBackgroundPtr bg = SolidBackground::create();

        bg->setColor(Color3f(0.2, 0.2, 0.2));

        _foreground = ImageForeground::create();

#if 1 // amz

        SimpleStatisticsForegroundPtr sf = SimpleStatisticsForeground::create();

        sf->setSize(25);
        sf->setColor(Color4f(0,1,0,0.7));
        sf->addElement(RenderAction::statDrawTime,      "Draw FPS: %r.3f");
        sf->addElement(RenderAction::statTravTime,      "Trav FPS: %r.3f");
        sf->addElement(DrawActionBase::statCullTestedNodes,
                           "%d Nodes culltested");
        sf->addElement(DrawActionBase::statCulledNodes,
                           "%d Nodes culled");
        sf->addElement(RenderAction::statNMaterials,
                           "%d material changes");
        sf->addElement(RenderAction::statNMatrices,
                           "%d matrix changes");
        sf->addElement(RenderAction::statNGeometries,
                           "%d Nodes drawn");
        sf->addElement(RenderAction::statNTransGeometries,
                           "%d transparent Nodes drawn");
#if 0 // not ready for primetime yet
        sf->addElement(PointLight::statNPointLights,
                           "%d active point lights");
        sf->addElement(DirectionalLight::statNDirectionalLights,
                           "%d active directional lights");
        sf->addElement(SpotLight::statNSpotLights,
                           "%d active spot lights");
#endif
        sf->addElement(Drawable::statNTriangles,    "%d triangles drawn");
        sf->addElement(Drawable::statNLines,        "%d lines drawn");
        sf->addElement(Drawable::statNPoints,       "%d points drawn");
        sf->addElement(Drawable::statNVertices,     "%d vertices transformed");
        sf->addElement(RenderAction::statNTextures, "%d textures used");
        sf->addElement(RenderAction::statNTexBytes, "%d bytes of texture used");

        // add optional elements
        sf->editCollector().getElem(Drawable::statNTriangles);

        _statforeground = sf;
#endif

        ViewportPtr vp = Viewport::create();

        vp->setCamera    (_camera);
        vp->setRoot      (_internalRoot);
        vp->setSize      (0,0, 1,1);
        vp->setBackground(bg);
        vp->addForeground(_foreground);

        _win->addPort(vp);
    }

    _navigator.setMode(Navigator::TRACKBALL);
    _navigator.setViewport(_win->getPort(0));
    _navigator.setCameraTransformation(cartN);
}

/*! show the whole scene: move out far enough  to see everything
 */
void SimpleSceneManager::showAll(void)
{
    if(_root == NullFC)
        return;

    _root->updateVolume();

    Vec3f min,max;
    _root->getVolume().getBounds( min, max );
    Vec3f d = max - min;

    if(d.length() < Eps) // Nothing loaded? Use a unity box
    {
        min.setValues(-1.f,-1.f,-1.f);
        max.setValues( 1.f, 1.f, 1.f);
        d = max - min;
    }

    Real32 dist = osgMax(d[0],d[1]) / (2 * osgTan(_camera->getFov() / 2.f));

    Vec3f up(0,1,0);
    Pnt3f at((min[0] + max[0]) * .5f,(min[1] + max[1]) * .5f,(min[2] + max[2]) * .5f);
    Pnt3f from=at;
    from[2]+=(dist+fabs(max[2]-min[2])*0.5f);

    _navigator.set(from,at,up);

    // adjust the translation factors so that motions are sort of scaled
    _navigator.setMotionFactor((d[0] + d[1] + d[2]) / 100.f);

    // set the camera to go from 1% of the object to twice its size
    Real32 diag = osgMax(osgMax(d[0], d[1]), d[2]);

    _camera->setNear (diag / 100.f);
    _camera->setFar  (10 * diag);
}

/*! add the "Powered by OpenSG" logo to the lower left corner
 */
void SimpleSceneManager::useOpenSGLogo(void)
{
    ImagePtr lo = Image::create();
    ImageFileType::restore( lo, (UChar8*)LogoData, -1 );

    _foreground->addImage( lo, Pnt2f( 0,0 ) );
}

/*! Sets the navigation mode
 */
void SimpleSceneManager::setNavigationMode (Navigator::Mode new_mode)
{
    Matrix m=_navigator.getMatrix();
    _navigator.setMode(new_mode);
    _navigator.set(m);
}


/*! Draw the next frame, update if needed.
 */
void SimpleSceneManager::idle(void)
{
    _navigator.idle(_mousebuttons,_lastx, _lasty);
}

/*! Update data needed for rendering.
 */
void SimpleSceneManager::update(void)
{
    if (_internalRoot == NullFC)
    {
        initialize();
        showAll();
    }

//    _cart->getSFMatrix()->setValue(_navigator.getMatrix());
    _navigator.updateCameraTransformation();

    updateHighlight();

    Thread::getCurrentChangeList()->commitChanges();
}

/*! Draw the next frame, update if needed.
 */
void SimpleSceneManager::redraw(void)
{
    update();

    if(!_traversalAction)
        _win->render(_action);
#ifdef OSG_CLEANED_RENDERACTION
    else
        _win->render(_taction);
#endif
}

/*! Adjust the highlight to a changed object. Also initializes the highlight
   statics if called the first time.
 */
void SimpleSceneManager::highlightChanged(void)
{

  // FDEBUG (("SimpleSceneManager::updateHightlight() called\n"));
#if 0 // amz
    // init as needed
    if(_highlightMaterial == NullFC)
    {
        _highlightMaterial = SimpleMaterial::create();

        beginEditCP(_highlightMaterial);
        _highlightMaterial->setDiffuse (Color3f(0,1,0));
        _highlightMaterial->setLit     (false);
        endEditCP(_highlightMaterial);
    }
    if(_highlightNode == NullFC)
    {
        GeoPTypesPtr type = GeoPTypesUI8::create();
        beginEditCP(type);
        type->push_back(GL_LINE_STRIP);
        type->push_back(GL_LINES);
        endEditCP(type);

        GeoPLengthsPtr lens = GeoPLengthsUI32::create();
        beginEditCP(lens);
        lens->push_back(10);
        lens->push_back(6);
        endEditCP(lens);

        GeoIndicesUI32Ptr index = GeoIndicesUI32::create();
        beginEditCP(index);
        index->getFieldPtr()->push_back(0);
        index->getFieldPtr()->push_back(1);
        index->getFieldPtr()->push_back(3);
        index->getFieldPtr()->push_back(2);
        index->getFieldPtr()->push_back(0);
        index->getFieldPtr()->push_back(4);
        index->getFieldPtr()->push_back(5);
        index->getFieldPtr()->push_back(7);
        index->getFieldPtr()->push_back(6);
        index->getFieldPtr()->push_back(4);

        index->getFieldPtr()->push_back(1);
        index->getFieldPtr()->push_back(5);
        index->getFieldPtr()->push_back(2);
        index->getFieldPtr()->push_back(6);
        index->getFieldPtr()->push_back(3);
        index->getFieldPtr()->push_back(7);
        endEditCP(index);

        _highlightPoints = GeoPositions3f::create();
        beginEditCP(_highlightPoints);
        _highlightPoints->push_back(Pnt3f(-1, -1, -1));
        _highlightPoints->push_back(Pnt3f( 1, -1, -1));
        _highlightPoints->push_back(Pnt3f(-1,  1, -1));
        _highlightPoints->push_back(Pnt3f( 1,  1, -1));
        _highlightPoints->push_back(Pnt3f(-1, -1,  1));
        _highlightPoints->push_back(Pnt3f( 1, -1,  1));
        _highlightPoints->push_back(Pnt3f(-1,  1,  1));
        _highlightPoints->push_back(Pnt3f( 1,  1,  1));
        endEditCP(_highlightPoints);

        GeometryPtr geo=Geometry::create();
        beginEditCP(geo);
        geo->setTypes     (type);
        geo->setLengths   (lens);
        geo->setIndices   (index);
        geo->setPositions (_highlightPoints);
        geo->setMaterial  (_highlightMaterial);
        endEditCP(geo);
        addRef(geo);

        _highlightNode = Node::create();
        beginEditCP(_highlightNode);
        _highlightNode->setCore(geo);
        endEditCP(_highlightNode);
        addRef(_highlightNode);
    }

    // attach the hightlight node to the root if the highlight is active
    if(getHighlight() != NullFC)
    {
        if(_highlightNode->getParent() == NullFC)
        {
            beginEditCP(_internalRoot);
            _internalRoot->addChild(_highlightNode);
            endEditCP(_internalRoot);
        }
    }
    else
    {
        if(_highlightNode->getParent() != NullFC)
        {
            beginEditCP(_internalRoot);
            _internalRoot->subChild(_highlightNode);
            endEditCP(_internalRoot);
        }

    }
    // update the highlight geometry
    updateHighlight();
#endif
}

/*! Update the highlight for a moved object. Does not handle changing the
    object, this is done by highlightChanged().
 */
void SimpleSceneManager::updateHighlight(void)
{
#if 0
    if(_highlight==NullFC)
        return;

    // FDEBUG (("SimpleSceneManager::updateHightlight() called\n"));

    // calc the world bbox of the highlight object
    DynamicVolume vol;
    _highlight->getWorldVolume(vol);

    Pnt3f min,max;
    vol.getBounds(min, max);

    beginEditCP(_highlightPoints);
    _highlightPoints->setValue(Pnt3f(min[0], min[1], min[2]), 0);
    _highlightPoints->setValue(Pnt3f(max[0], min[1], min[2]), 1);
    _highlightPoints->setValue(Pnt3f(min[0], max[1], min[2]), 2);
    _highlightPoints->setValue(Pnt3f(max[0], max[1], min[2]), 3);
    _highlightPoints->setValue(Pnt3f(min[0], min[1], max[2]), 4);
    _highlightPoints->setValue(Pnt3f(max[0], min[1], max[2]), 5);
    _highlightPoints->setValue(Pnt3f(min[0], max[1], max[2]), 6);
    _highlightPoints->setValue(Pnt3f(max[0], max[1], max[2]), 7);
    endEditCP(_highlightPoints);

    beginEditCP(_highlightNode->getCore(), Geometry::PositionsFieldMask);
    endEditCP  (_highlightNode->getCore(), Geometry::PositionsFieldMask);
#endif
}

/*-------------------------------------------------------------------------*/
/*                        Interaction handling                             */

/*! resize
 */
void SimpleSceneManager::resize(UInt16 width, UInt16 height)
{
    _win->resize(width, height);
}

/*! motion
 */
void SimpleSceneManager::mouseMove(Int16 x, Int16 y)
{
    if ( _mousebuttons) _navigator.moveTo(x,y);
    _lastx = x;
    _lasty = y;

}

/*! call when a mouse button is pressed. button is the number of the pressed
    button, starting at 0, ordered from left to right. A wheel should be
    mapped to buttons 3 and 4. The position is in pixel, starting at the
    upper left corner.
 */

void SimpleSceneManager::mouseButtonPress(UInt16 button, Int16 x, Int16 y)
{
    switch (button)
    {
    case MouseLeft:    _navigator.buttonPress(Navigator::LEFT_MOUSE,x,y);
      break;
    case MouseMiddle:  _navigator.buttonPress(Navigator::MIDDLE_MOUSE,x,y);
      break;
    case MouseRight:   _navigator.buttonPress(Navigator::RIGHT_MOUSE,x,y);
      break;
    case MouseUp:      _navigator.buttonPress(Navigator::UP_MOUSE,x,y);
      break;
    case MouseDown:    _navigator.buttonPress(Navigator::DOWN_MOUSE,x,y);
      break;
    }

    _mousebuttons |= 1 << button;
    _lastx = x;
    _lasty = y;
}


/*! call when a mouse button is released. button is the number of the pressed
    button, starting at 0, ordered from left to right. A wheel should be
    mapped to buttons 3 and 4. The position is in pixel, starting at the
    upper left corner.
 */
void SimpleSceneManager::mouseButtonRelease(UInt16 button, Int16 x, Int16 y)
{
    switch (button)
    {
    case MouseLeft:     _navigator.buttonRelease(Navigator::LEFT_MOUSE,x,y);
                        break;
    case MouseMiddle:   _navigator.buttonRelease(Navigator::MIDDLE_MOUSE,x,y);
                        break;
    case MouseRight:    _navigator.buttonRelease(Navigator::RIGHT_MOUSE,x,y);
                        break;
    case MouseUp:       _navigator.buttonRelease(Navigator::UP_MOUSE,x,y);
                        break;
    case MouseDown:     _navigator.buttonRelease(Navigator::DOWN_MOUSE,x,y);
                        break;
    }
    _mousebuttons &= ~(1 << button);
    _lastx = x;
    _lasty = y;
}

void SimpleSceneManager::key(UChar8 key, Int16 x, Int16 y)
{
    switch ( key )
    {
        case 'j': _navigator.keyPress(Navigator::LEFT,x,y); break;
        case 'g': _navigator.keyPress(Navigator::RIGHT,x,y); break;
        case 'u': _navigator.keyPress(Navigator::LEFTROT,x,y); break;
        case 't': _navigator.keyPress(Navigator::RIGHTROT,x,y); break;
        case 'y': _navigator.keyPress(Navigator::FORWARDS,x,y); break;
        case 'h': _navigator.keyPress(Navigator::BACKWARDS,x,y); break;
    }
}

/*! Calculate a ray that starts at the eye and goes through the position on the
    screen given by x,y.
 */

Line SimpleSceneManager::calcViewRay(Int16 x, Int16 y)
{
    Line l;

    _camera->calcViewRay(l, x, y, *_win->getPort()[0]);

    return l;
}

/*------------------------------ access -----------------------------------*/

/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/

/*-------------------------- assignment -----------------------------------*/

/*-------------------------- comparison -----------------------------------*/

/*! less
 */

bool SimpleSceneManager::operator < (const SimpleSceneManager &other) const
{
    return this < &other;
}


/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp[] = "@(#)$Id$";
    static Char8 cvsid_hpp[] = OSGSIMPLESCENEMANAGER_HEADER_CVSID;
    static Char8 cvsid_inl[] = OSGSIMPLESCENEMANAGER_INLINE_CVSID;
}
