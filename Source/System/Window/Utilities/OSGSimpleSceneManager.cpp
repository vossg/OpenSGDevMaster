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

#include <cstdlib>
#include <cstdio>

#include <OSGConfig.h>
#include <OSGBaseFunctions.h>
#include <OSGImageFileType.h>
#include <OSGSolidBackground.h>
#include <OSGViewport.h>
#include <OSGLogoData.h>
#include <OSGSimpleStatisticsForeground.h>
//#include <OSGStatElemTypes.h>
//#include <OSGStatCollector.h>
#include <OSGTypedGeoIntegralProperty.h>
#include <OSGTypedGeoVectorProperty.h>
#include <OSGDrawable.h>
#include <OSGPointLight.h>
#include <OSGSpotLight.h>
#include <OSGDirectionalLight.h>
#include <OSGTextureObjChunk.h>
#include <OSGPerspectiveCamera.h>
#include <OSGOrthographicCamera.h>

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
    May be NULL (which is the default), in which case nothing is highlighted.
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


/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

/*! Constructor
 */

SimpleSceneManager::SimpleSceneManager(void) :
    _win            (NULL  ),
    _root           (NULL  ),
    _foreground     (NULL  ),
    _statforeground (NULL  ),
    _statstate      (false),

    _highlight      (NULL  ),
    _highlightNode  (NULL  ),
    _highlightPoints(NULL  ),

    _internalRoot   (NULL  ),
    _headlight      (NULL  ),
#ifdef OSG_OLD_RENDER_ACTION
    _renderAction   (NULL  ),
    _ownAction      (NULL  ),
#endif
    _rtaction       (NULL  ),
    _cart           (NULL  ),
    _camera         (NULL  ),
    _navigator      (      ),

    _lastx          (TypeTraits<Int16>::getMax()),
    _lasty          (TypeTraits<Int16>::getMax()),
    _mousebuttons   (0                             ),
    _traversalAction(true                         ),
    _highlightMaterial(NULL)
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
#ifdef OSG_OLD_RENDER_ACTION
    delete _ownAction;

    if(_renderAction && _renderAction != _ownAction)
        delete _renderAction;
#endif

    if(_rtaction)
        delete _rtaction;

    setRoot(NULL); // sub root

    _internalRoot      = NULL;

    _camera            = NULL;
    _cart              = NULL;
    _headlight         = NULL;
    _statforeground    = NULL;
    _foreground        = NULL;
    _highlightMaterial = NULL;
    _highlightPoints   = NULL;
    _highlightNode     = NULL;
    _highlight         = NULL;
    _win               = NULL;
    _root              = NULL;
}



/*! get the window to be used for display
 */
Window *SimpleSceneManager::getWindow(void)
{
    return _win;
}

/*! get the root of the displayed tree
 */
Node *SimpleSceneManager::getRoot(void)
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
DirectionalLight *SimpleSceneManager::getHeadlight(void)
{
    return _headlight;
}

/*! get the camera
 */
Camera *SimpleSceneManager::getCamera(void)
{
    return _camera;
}

/*! set the window to be used for display
 */
void SimpleSceneManager::setWindow(Window *win)
{
    _win = win;
    if(_win->getMFPort()->size() > 0 && _win->getPort(0) != NULL)
        _navigator.setViewport(_win->getPort(0));
}

/*! get the highlight object
 */
Node *SimpleSceneManager::getHighlight(void)
{
    return _highlight;
}

#ifdef OSG_OLD_RENDER_ACTION
/*! get the action used to render the scene
 */
DrawActionBase *SimpleSceneManager::getAction(void)
{
    return _renderAction;
}
#endif

/*! get the traversal action used to render the scene
 */
RenderAction *SimpleSceneManager::getRenderAction(void)
{
    return _rtaction;
}

#ifdef OSG_OLD_RENDER_ACTION
/*! set the action used to render the scene. Use NULL to set to
    internally created action.
 */

void SimpleSceneManager::setAction(RenderAction *action)
{
    bool statstate = _statstate;

    if(_renderAction != NULL && statstate)
        setStatistics(false);

    if(action == NULL)
    {
        _renderAction = _ownAction;
    }
    else
    {
        _renderAction = action;
    }

    if(statstate)
        setStatistics(true);
}
#endif

void SimpleSceneManager::setAction(RenderAction *action)
{
    bool statstate = _statstate;

    if(_rtaction != NULL)
    {
        if(statstate)
            setStatistics(false);
        delete _rtaction;
    }

    _rtaction = action;

    if(statstate)
        setStatistics(true);
}

/*! set the root of the displayed tree
 */
void SimpleSceneManager::setRoot(Node *root)
{
    if(_internalRoot == NULL)
    {
        initialize();
    }

    if(_root != root)
    {
        if(_root != NULL)
        {
            _internalRoot->subChild(_root);
        }

        _root = root;

        if(_root != NULL)
        {
            _internalRoot->addChild(_root);
        }
    }
}

/*! set the headlight setting
 */
void SimpleSceneManager::setHeadlight(bool on)
{
    if(_internalRoot == NULL)
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

void SimpleSceneManager::setCamera(Camera *camera)
{
    if(camera == NULL)
        return;

    camera->setBeacon(_camera->getBeacon());

    PerspectiveCamera *oldPer  = 
        dynamic_pointer_cast<PerspectiveCamera>(_camera);
    PerspectiveCamera *newPer  = 
        dynamic_cast<PerspectiveCamera *>(camera);

    OrthographicCamera *oldOrt =
        dynamic_pointer_cast<OrthographicCamera>(_camera);

    OrthographicCamera *newOrt = dynamic_cast<OrthographicCamera *>(camera);


    if (oldPer && newPer) {
        newPer->setFov(oldPer->getFov());
    }
    else if (oldOrt && newOrt) {
        newOrt->setVerticalSize(oldOrt->getVerticalSize());
    }
    else {
        FWARNING(("SimpleSceneManager::setCamera: some of the old camera's "
                  " params could not be copied to the new camera, because of "
                  " different or unsupported camera types!\n"));
    }

    camera->setNear(_camera->getNear());
    camera->setFar (_camera->getFar());


    for(UInt32 i=0;i<_win->getMFPort()->size();++i)
    {
        Viewport *vp = _win->getPort(i);

        if(vp != NULL)
        {
            vp->setCamera(camera);
        }
    }

    // destroy old camera.
//    addRefX( camera);
//    subRefX(_camera);

    _camera = camera;
}

/*! set the highlight object
 */
void SimpleSceneManager::setHighlight(Node *highlight)
{
    _highlight = highlight;
    highlightChanged();
}

/*! set the statistics setting. Only works after the window has been created.
 */
void SimpleSceneManager::setStatistics(bool on)
{
    if(_statforeground != NULL && on != _statstate)
    {
        Viewport *vp = _win->getPort(0);

        if(on)
        {
            vp->addForeground(_statforeground);

#ifdef OSG_OLD_RENDER_ACTION
            _renderAction->setStatCollector(_statforeground->getCollector());
#endif
            _rtaction    ->setStatCollector(_statforeground->getCollector());
        }
        else
        {
            vp->removeFromForegrounds(_statforeground);

#ifdef OSG_OLD_RENDER_ACTION
            _renderAction->setStatCollector(NULL);
#endif
            _rtaction    ->setStatCollector(NULL);
        }

        _statstate = on;
    }
}

/*! Return true if stats are currently enabled. */
bool SimpleSceneManager::getStatistics(void)
{
   return _statstate;
}

/*-------------------------------------------------------------------------*/
/*                               Updates                                   */

/*! create the parts that the app needs: viewport, camera, base graph etc.
 */
void SimpleSceneManager::initialize(void)
{
    // Check necessary stuff
    if(_win == NULL)
    {
        FWARNING(("SimpleSceneManager::initialize: window not set, "
                  "ignoring!\n"));
        return;
    }

    // the rendering action
#ifdef OSG_OLD_RENDER_ACTION
    _ownAction    = RenderAction::create();
    _renderAction = _ownAction;
#endif

    _rtaction = RenderAction::create();

    // the camera and light beacon
    NodeUnrecPtr cartN = Node::create();
    _cart = Transform::create();

    cartN->setCore(_cart);

    // the headlight
    _internalRoot = Node::create();
    _headlight    = DirectionalLight::create();

//    addRefX(_internalRoot);

    _internalRoot->setCore(_headlight);
    _internalRoot->addChild(cartN);


    _headlight->setAmbient  (.3, .3, .3, 1);
    _headlight->setDiffuse  ( 1,  1,  1, 1);
    _headlight->setSpecular ( 1,  1,  1, 1);
    _headlight->setDirection( 0,  0,  1);
    _headlight->setBeacon   (cartN);

    // the camera
    _camera = PerspectiveCamera::create();

//    addRefX(_camera);

    _camera->setBeacon(cartN);

    PerspectiveCamera *pPerspCam = 
        dynamic_pointer_cast<PerspectiveCamera>(_camera);

    if(pPerspCam != NULL)
        pPerspCam->setFov(osgDegree2Rad(60.f));

    _camera->setNear (0.1f);
    _camera->setFar  (10000.f);

    // need a viewport?
    if(_win->getMFPort()->size() == 0)
    {
        SolidBackgroundUnrecPtr bg = SolidBackground::create();

        bg->setColor(Color3f(0.2, 0.2, 0.2));

        _foreground = ImageForeground::create();

        SimpleStatisticsForegroundUnrecPtr sf = 
            SimpleStatisticsForeground::create();

        sf->setSize(25);
        sf->setColor(Color4f(0,1,0,0.7));


        // Render traversal stats action
        sf->addElement(RenderAction::statDrawTime,  
                       "Draw FPS: %r.3f");
        sf->addElement(RenderAction::statTravTime,     
                       "Trav FPS: %r.3f");
        sf->addElement(RenderAction::statNStates,       
                       " State changes: %d");
        sf->addElement(RenderAction::statNShaders,
                       "Shader changes: %d");
        sf->addElement(RenderAction::statNShaderParams, 
                       "Shader param changes: %d");
        sf->addElement(TextureObjChunk::statNTextures, 
                       "Textures: %d");
        sf->addElement(TextureObjChunk::statNTexBytes, 
                       " Tex Mem: %MB MB");

        sf->addElement(RenderAction::statNGeometries,   
                       "    Geom nodes: %d");
        sf->addElement(RenderAction::statNMatrices,     
                       "Matrix changes: %d");
        sf->addElement(RenderAction::statNTriangles,
                       "     Triangles: %d");

        sf->addElement(PointLight::statNPointLights,
                           "%d active point lights");
        sf->addElement(DirectionalLight::statNDirectionalLights,
                           "%d active directional lights");
        sf->addElement(SpotLight::statNSpotLights,
                           "%d active spot lights");

        sf->addText   ("Drawables: (drawn)");

        sf->addElement(Drawable::statNTriangles,    "  tris: %d");
        sf->addElement(Drawable::statNLines,        " lines: %d");
        sf->addElement(Drawable::statNPoints,       "points: %d");
        sf->addElement(Drawable::statNVertices,     " verts: %d");
        
        if(sf->getCollector() != NULL)
        {
            // add optional elements
            sf->getCollector()->getElem(Drawable::statNTriangles);
        }

        sf->addText   ("ChangeList: ");
        sf->addElement(ChangeList::statNChangedStoreSize, 
                       "    %d entries in changedStore");
        sf->addElement(ChangeList::statNCreatedStoreSize, 
                       "    %d entries in createdStore");
        sf->addElement(ChangeList::statNUnCommittedStoreSize, 
                       "    %d entries in uncommitedStore");
        sf->addElement(ChangeList::statNPoolSize, 
                       "    %d entries in pool");


#if 0
        // Render action
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
        if(sf->getCollector() != NULL)
        {
            // add optional elements
            sf->editCollector()->getElem(Drawable::statNTriangles);
        }
#endif

        _statforeground = sf;
//        addRefX(_statforeground);

        ViewportUnrecPtr vp = Viewport::create();

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
    if(_root == NULL)
        return;

    OSG::commitChanges();      // Commit the changes so the volumes are up to date.

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

    PerspectiveCamera *perCam = 
        dynamic_pointer_cast<PerspectiveCamera>(_camera);

    OrthographicCamera *ortCam =
        dynamic_pointer_cast<OrthographicCamera>(_camera);

    Real32 dist = osgMax(d[0],d[1]);

    if (perCam) {
        dist /= (2 * osgTan(perCam->getFov()/2.f));
    }
    else if (ortCam) {
        ortCam->setVerticalSize(dist);
    }
    else {
        FWARNING(("SimpleSceneManager::showAll: unsupported camera type, "
                  "may not work properly!\n"));
    }

    Vec3f up(0,1,0);
    Pnt3f at((min[0]+max[0])*.5f,(min[1]+max[1])*.5f,(min[2]+max[2])*.5f);
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
    ImageUnrecPtr lo = Image::create();

    ImageFileType::restore( lo, static_cast<UChar8 *>(LogoData), -1 );

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
    if (_internalRoot == NULL)
    {
        initialize();
        showAll();
    }

//    _cart->getSFMatrix()->setValue(_navigator.getMatrix());
    _navigator.updateCameraTransformation();

    updateHighlight();

    Thread::getCurrentChangeList()->fillStatistic(
        _rtaction->getStatCollector()); 

    Thread::getCurrentChangeList()->commitChanges();
}

/*! Draw the next frame, update if needed.
 */
void SimpleSceneManager::redraw(void)
{
    update();

#ifdef OSG_OLD_RENDER_ACTION
    if(!_traversalAction)
    {  _win->render(_renderAction); }
    else
#endif
    {  _win->render(_rtaction); }
}

/*! Adjust the highlight to a changed object. Also initializes the highlight
   statics if called the first time.
 */
void SimpleSceneManager::highlightChanged(void)
{
  // FDEBUG (("SimpleSceneManager::updateHightlight() called\n"));
    // init as needed
    if(_highlightMaterial == NULL)
    {
        _highlightMaterial = SimpleMaterial::create();
        _highlightMaterial->setDiffuse (Color3f(0,1,0));
        _highlightMaterial->setLit     (false);
    }
    if(_highlightNode == NULL)
    {
        GeoUInt8PropertyUnrecPtr type = GeoUInt8Property::create();
        GeoUInt8Property::StoredFieldType* t = type->editFieldPtr();
        t->push_back(GL_LINE_STRIP);
        t->push_back(GL_LINES);

        GeoUInt32PropertyUnrecPtr lens = GeoUInt32Property::create();
        GeoUInt32Property::StoredFieldType* l = lens->editFieldPtr();
        l->push_back(10);
        l->push_back(6);

        GeoUInt32PropertyUnrecPtr index = OSG::GeoUInt32Property::create();
        GeoUInt32Property::StoredFieldType* idx = index->editFieldPtr();
        idx->push_back(0);
        idx->push_back(1);
        idx->push_back(3);
        idx->push_back(2);
        idx->push_back(0);
        idx->push_back(4);
        idx->push_back(5);
        idx->push_back(7);
        idx->push_back(6);
        idx->push_back(4);

        idx->push_back(1);
        idx->push_back(5);
        idx->push_back(2);
        idx->push_back(6);
        idx->push_back(3);
        idx->push_back(7);

        _highlightPoints = OSG::GeoPnt3fProperty::create();
        OSG::GeoPnt3fProperty::StoredFieldType*  p = _highlightPoints->editFieldPtr();
        p->push_back(Pnt3f(-1, -1, -1));
        p->push_back(Pnt3f( 1, -1, -1));
        p->push_back(Pnt3f(-1,  1, -1));
        p->push_back(Pnt3f( 1,  1, -1));
        p->push_back(Pnt3f(-1, -1,  1));
        p->push_back(Pnt3f( 1, -1,  1));
        p->push_back(Pnt3f(-1,  1,  1));
        p->push_back(Pnt3f( 1,  1,  1));

        GeometryUnrecPtr geo = Geometry::create();
        geo->setTypes     (type);
        geo->setLengths   (lens);
        geo->setIndices   (index);
        geo->setPositions (_highlightPoints);
        geo->setMaterial  (_highlightMaterial);
//        addRefX(geo);

        _highlightNode = Node::create();
        _highlightNode->setCore(geo);
//        addRefX(_highlightNode);
    }

    // attach the hightlight node to the root if the highlight is active
    if(getHighlight() != NULL)
    {
        if(_highlightNode->getParent() == NULL)
        {
            _internalRoot->addChild(_highlightNode);
        }
    }
    else
    {
        if(_highlightNode->getParent() != NULL)
        {
            _internalRoot->subChild(_highlightNode);
        }

    }
    // update the highlight geometry
    updateHighlight();
}

/*! Update the highlight for a moved object. Does not handle changing the
    object, this is done by highlightChanged().
 */
void SimpleSceneManager::updateHighlight(void)
{
    if(_highlight == NULL)
        return;

    // FDEBUG (("SimpleSceneManager::updateHightlight() called\n"));

    // calc the world bbox of the highlight object
    DynamicVolume vol;
    _highlight->getWorldVolume(vol);

    Pnt3f min,max;
    vol.getBounds(min, max);

    _highlightPoints->setValue(Pnt3f(min[0], min[1], min[2]), 0);
    _highlightPoints->setValue(Pnt3f(max[0], min[1], min[2]), 1);
    _highlightPoints->setValue(Pnt3f(min[0], max[1], min[2]), 2);
    _highlightPoints->setValue(Pnt3f(max[0], max[1], min[2]), 3);
    _highlightPoints->setValue(Pnt3f(min[0], min[1], max[2]), 4);
    _highlightPoints->setValue(Pnt3f(max[0], min[1], max[2]), 5);
    _highlightPoints->setValue(Pnt3f(min[0], max[1], max[2]), 6);
    _highlightPoints->setValue(Pnt3f(max[0], max[1], max[2]), 7);
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

    _camera->calcViewRay(l, x, y, *_win->getPort(0));

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

