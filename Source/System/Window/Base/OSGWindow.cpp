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

#include "OSGConfig.h"

#include <OSGGLU.h>

#if !defined(WIN32) && !defined(__APPLE__)
#include <GL/glx.h>
#endif

#if defined(OSG_WINCE)
#include <gles/egl.h>
#endif

#if defined(__sgi) || defined(__APPLE__) || defined(__linux)
#include <dlfcn.h>
#endif

#if defined(__APPLE__)
#include <mach-o/dyld.h>
#endif

#if defined(__sun)
#include <dlfcn.h>
#include <link.h>
#endif

#include <OSGBaseFunctions.h>
#include <OSGDrawEnv.h>

#include "OSGViewport.h"

#include "OSGBackground.h"
#include "OSGCamera.h"
#include "OSGWindow.h"

#include "OSGRenderActionBase.h"

#include "OSGStageValidator.h"

OSG_USING_NAMESPACE

#if defined(OSG_WIN32_ICL) && !defined(OSG_CHECK_FIELDSETARG)
#pragma warning (disable)
#endif

// Documentation for this class is emited in the
// OSGWindowBase.cpp file.
// To modify it, please change the .fcd file (OSGWindow.fcd) and
// regenerate the base file.

// Window-sytem specific virtual functions

/*! \fn void OSG::Window::init(void)
  
  Initialize the Window and its OpenGL context. This method needs to be
  called once after the Window has been created and its Window
  System-specific parameters are set.  
  
  It leaves the OpenGL context current to simplify modifying the OpenGL
  state. 
 */

/*! \fn void OSG::Window::activate(void)
  
  Activate the Window's OpenGL context, so that OpenGL can be called. 
 */

/*! \fn void OSG::Window::deactivate(void)
  
  Deativate the Window's OpenGL context. OpenGL calls are no longer possible
  after this call.
 */

/*! \fn void OSG::Window::swap(void)
  
  Swap the back and front buffers. 
  
  \warning The correct OpenGL context needs to be active for this to work!
 */

// only needed in dev docs

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)

/*! \enum OSG::Window::GLObjectStatusE
  Enumeration values for the status of the GL objects. This is primarily
  used to signal the object's callback functions what to do. See \ref
  PageSystemOGLObjects for a description.
 */

/*! \var OSG::Window::GLObjectStatusE Window::notused
  Object is not used at all right now.
 */

/*! \var OSG::Window::GLObjectStatusE Window::initialize
  The object is being initialized for the first time.
 */

/*! \var OSG::Window::GLObjectStatusE Window::reinitialize
  The object is being re-initialized, i.e. it has changed significantly.
 */

/*! \var OSG::Window::GLObjectStatusE Window::initialized
  The object is initialized and valid.
 */

/*! \var OSG::Window::GLObjectStatusE Window::needrefresh
  The object is initialized but needs a refresh.
 */

/*! \var OSG::Window::GLObjectStatusE Window::destroy
  The object is to be destroyed, i.e. removed from the current OpenGL context.
 */

/*! \var OSG::Window::GLObjectStatusE Window::finaldestroy
  The object has been removed from all OpenGL contexts and used ressources
  but be freed now.
 */

/*! \enum OSG::Window::invalidExtensionID
 */

/*! \enum OSG::Window::invalidFunctionID
 */

/*! \enum OSG::Window::statusShift
  Shift value to transform object id and status into  asingle int.
 */

/*! \enum OSG::Window::statusMask
  Mask value to transform object id and status into  asingle int.
 */

/*! \class OSG::Window::GLObject
  \ingroup GrpSystemWindow
  
  The GLObject class is used to keep track of the OpenGL objects registered 
  with the system. See \ref PageSystemOGLObjects for a description.
  
 */

#endif

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/*! The global window list, needed by Window::refreshGLObject. All Windows are 
  added here at creation time and removed at deletion. 
 */

std::vector<OSG::Window *> OSG::Window::_allWindows;
UInt32                     OSG::Window::_currentWindowId = 0;

// GLobject handling

#ifndef OSG_WINCE
/*! The lock used to mutex access of the GLObjects' reference count. One 
  should be enough for all of them, as they are pretty rarely changed, only 
  when they are used for the first time.
 */

Lock                                 *OSG::Window::_GLObjectLock = NULL;

/*! The lock used to mutex access of the Window's static elements to manage
  OpenGL extensions/functions/constants/objects.
 */

Lock                                 *OSG::Window::_staticWindowLock = NULL;
#endif

/*! Global list of all GL Objects used in the system. See \ref
  PageSystemOGLObjects for a description.
 */ 

std::vector<OSG::Window::GLObject *>  OSG::Window::_glObjects; 

// GL extension handling

// The name of the dynamic library for OpenGL extension functions
// By default it's NULL, which tries to find them in the current 
// executable
const Char8 *OSG::Window::_glLibraryName = NULL;    

std::vector<std::string            >  OSG::Window::_registeredExtensions;
std::vector<std::string            >  OSG::Window::_ignoredExtensions;
std::vector<bool                   >  OSG::Window::_commonExtensions;
std::vector<std::string            >  OSG::Window::_registeredFunctions;
std::vector<Int32                  >  OSG::Window::_registeredFunctionExts;
std::vector<UInt32                 >  OSG::Window::_registeredFunctionVersions;

// GL constant handling

std::vector<GLenum                 >  OSG::Window::_registeredConstants;


// Just a constant to indicate that the GL constant is unknown

const Real32 OSG::Window::unknownConstant =  TypeTraits<Real32>::getMax();

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*! initialize the static features of the class, e.g. action callbacks
*/

void OSG::Window::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);
}

bool OSG::Window::terminate(void)
{
#ifndef OSG_WINCE
    if(_staticWindowLock != NULL)
    {
        OSG::subRef(_staticWindowLock);
    }

    if(_GLObjectLock != NULL)
    {
        OSG::subRef(_GLObjectLock);
    }
#endif

    for(UInt32 i = 0; i < _glObjects.size(); ++i)
    {
        delete _glObjects[i];
    }

    return true;
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


/*------------- constructors & destructors --------------------------------*/

/*! Constructor
 */

OSG::Window::Window(void) :
     Inherited      (    ),
    _windowId       (   0),
    _initNeeded     (true),
    _pStageValidator(NULL)
{
    // only called for prototypes, no need to init them
}

/*! Copy Constructor
 */

OSG::Window::Window(const Window &source) :
    Inherited           (source                        ),
    _glObjectDestroyList(source._glObjectDestroyList   ),
    _lastValidate       (source._lastValidate.size(), 0),
    _ids                (source._ids.size(),          0),
    _extensions         (                              ),
    _availExtensions    (                              ),
    _extFunctions       (                              ),
    _availConstants     (                              ),
    _numAvailConstants  (                             0),
    _windowId           (                             0),
    _initNeeded         (                          true),
    _pStageValidator    (NULL                          )
{       
}

/*! Destructor
*/

OSG::Window::~Window(void)
{
    // delete the ports and the context
}


/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*! Instance initialisation
*/

void OSG::Window::onCreate(const Window *source)
{
    Inherited::onCreate(source);

    // Don't add the prototype instances to the list
    if(GlobalSystemState != Running)
        return;
   
    if(source != NULL)
    {
        // mark all GL objects as not yet initialized
        doInitRegisterGLObject(1, _glObjects.size() - 1);
    }

    _allWindows.push_back(this); 

    _windowId = ++_currentWindowId;
}

void OSG::Window::onCreateAspect(const Window *createAspect, 
                                 const Window *source)
{
    Inherited::onCreateAspect(createAspect, source);

    // Don't add the prototype instances to the list
    if(GlobalSystemState != Running)
        return;

    _windowId = _currentWindowId;

    _pStageValidator = new StageValidator;
}

/*! instance deletion
*/

void OSG::Window::onDestroy(UInt32 uiContainerId)
{
    // decrement GLObjects reference counter.
    for(UInt32 i = 1; i < _glObjects.size(); ++i)
    {
        GLObject *obj = _glObjects[i];

        if(obj == NULL)
        {
            FDEBUG(("Window::onDestroy: object %u already destroyed!\n", i));
            continue;
        }

        // has the object been used in this context at all?
        if(i < getMFGlObjectLastReinitialize()->size() && 
           getGlObjectLastReinitialize(i) != 0)
        {
            obj->decRefCounter();
            // we can't call here the destroy callbacks because the
            // gl context is not guaranteed to be current, but destroying
            // the context should delete all gl objects.
        }
    }

    std::vector<Window *>::iterator it;

    it = std::find(_allWindows.begin(), 
                   _allWindows.end  (), 
                   this);
    
    // prototype window are not added to the list, so they might not be found.

    if(it != _allWindows.end()) 
        _allWindows.erase( it );

    Inherited::onDestroy(uiContainerId);
}

void OSG::Window::onDestroyAspect(UInt32  uiContainerId,
                                  UInt32  uiAspect     )
{
    delete _pStageValidator;

    _pStageValidator = NULL;

    Inherited::onDestroyAspect(uiContainerId, uiAspect);
}

void OSG::Window::staticAcquire(void)
{
    // Is the ThreadManager initialized yet?
    if(GlobalSystemState != Running)
        return;
        
#ifndef OSG_WINCE
    if(_staticWindowLock == NULL)
    {
        _staticWindowLock = ThreadManager::the()->getLock(NULL);

        addPostFactoryExitFunction(&Window::terminate);
    }
    _staticWindowLock->acquire();
#endif
}

void OSG::Window::staticRelease(void)
{
    // Is the ThreadManager initialized yet?
    if(GlobalSystemState != Running)
        return;
        
#ifndef OSG_WINCE
    _staticWindowLock->release();
#endif
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*! react to field changes
*/

void OSG::Window::changed(ConstFieldMaskArg whichField, 
                          UInt32            origin,
                          BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

/*------------------------------ access -----------------------------------*/

#if 0
void OSG::Window::addPort(const ViewportPtr &portP)
{
    if(portP != NullFC)
    {
        editMField(PortFieldMask, _mfPort);

        _mfPort.push_back(portP);

        _mfPort.back()->setParent(this);
    }
}

void OSG::Window::insertPort(UInt32 portIndex, const ViewportPtr &portP)
{    
    if(portP != NullFC)
    {
        editMField(PortFieldMask, _mfPort);

        MFViewportPtr::iterator portIt = _mfPort.begin();

        portIt += portIndex;
  
        (*(_mfPort.insert(portIt, portP)))->setParent(
            this);
    }
}


void OSG::Window::replacePort(UInt32 portIndex, const ViewportPtr &portP)
{
    if(portP != NullFC)
    {
        editMField(PortFieldMask, _mfPort);
        
        _mfPort[portIndex]->setParent(NullFC);
        _mfPort[portIndex] = portP;

        _mfPort[portIndex]->setParent(
            this);
    }
}

void OSG::Window::replacePortBy(const ViewportPtr &portP, 
                             const ViewportPtr &newportP)
{
    if(newportP != NullFC)
    {
        editMField(PortFieldMask, _mfPort);

        MFViewportPtr::iterator portIt = _mfPort.find(portP);

        if(portIt != _mfPort.end())
        {
            (*portIt)->setParent(NullFC);
            (*portIt) = newportP;
            (*portIt)->setParent(this);
        }
    }
}

void OSG::Window::subPort(const ViewportPtr &portP)
{
    editMField(PortFieldMask, _mfPort);
    
    MFViewportPtr::iterator portIt = _mfPort.find(portP);

    if(portIt != _mfPort.end())
    {
        (*portIt)->setParent(NullFC);

        _mfPort.erase(portIt);
    }

}

void OSG::Window::subPort(UInt32  portIndex)
{
    editMField(PortFieldMask, _mfPort);

    MFViewportPtr::iterator portIt = _mfPort.begin();

    portIt += portIndex;

    if(portIt != _mfPort.end())
    {
        (*portIt)->setParent(NullFC);

        _mfPort.erase(portIt);
    }
}
#endif

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_EXT)

/*------------------------ GL object handling -----------------------------*/

/*! Register a number of OpenGL objects. By default the number is 1, but more
    can be necessary for things like text. It returns the first id of the
    contiguous reserved ID block.

    See \ref PageSystemOGLObjects for a description of the OpenGL object
    concept. 
*/

UInt32 OSG::Window::registerGLObject(GLObjectFunctor functor, 
                                     GLObjectFunctor destroy, 
                                     UInt32          num)
{
    UInt32    osgId, i; 
    GLObject *pGLObject;

    staticAcquire();
    
    // reserve index 0, illegal for most OpenGL functions
    if(_glObjects.empty())
        _glObjects.push_back(NULL);

    osgId     = _glObjects.size();
    pGLObject = new GLObject(functor, destroy);
    
    // does the requested block fit into the capacity?
    
    if(_glObjects.capacity() >= osgId + num)
    {
        _glObjects.insert(_glObjects.end(), num, pGLObject );
        
        initRegisterGLObject(osgId, num);

        staticRelease();

        return osgId;
    }
    
    // doesn't fit, try to find a block in the middle
    
    UInt32 cnt = 0;

    // start searching at 1, id 0 is reserved for GL
    for(i = 1; i < _glObjects.size(); ++i)
    {       
        if(_glObjects[i] == NULL) 
        {
            if(cnt == 0)
            {
                osgId = i;
            }

            ++cnt;

            if(cnt == num) 
            {
                // block of unused entries found ...
                        
                while(i >= osgId) 
                {
                    _glObjects[i] = pGLObject;
                    i = i - 1;
                } 
                
                initRegisterGLObject(osgId, num);

                staticRelease();

                return osgId;
            }
        }
        else
        {
            cnt   = 0;
            osgId = 0;
        }
    }
    
    // no block found, add at the end
    
    if(osgId > 0) // ok the last entries in the vector were empty
    {
        // fill the empty slots at the end 
        i = osgId + cnt - 1;

        while(i >= osgId)
        {
            _glObjects[i] = pGLObject;

            i = i - 1;
        }
    }
    else
    {
        // we found no empty entries so the new id is the size of the vector.
        osgId = _glObjects.size();
    }

    // expand the vector for the rest 
    for(i = 1; i <= num - cnt; i++) 
    {       
        _glObjects.push_back(pGLObject);
    }
                
    initRegisterGLObject(osgId, num);
    
    staticRelease();
    
    return osgId;
}

/*! Validate the given object, i.e. make sure it is up-to-date in the current
    context.

    See \ref PageSystemOGLObjects for a description of the OpenGL object
    concept. 
*/
void OSG::Window::validateGLObject(UInt32 osgId, DrawEnv *pEnv)
{
    if ( osgId == 0 )
    {
        SWARNING << "Window::validateGLObject: id is 0!" << std::endl;
        return;
    }
    
    GLObject *obj = _glObjects[osgId];
    
    if(obj == NULL)
    {
        SWARNING << "Window::validateGLObject: obj with id " << osgId 
                 <<" is NULL!" << std::endl;
        return;
    }

    if(osgId >= _lastValidate.size()) // can happen if multi-threading
    {
        _lastValidate.insert(_lastValidate.end(), 
                             osgId + 1 - _lastValidate.size(),
                             0);
    }
    
    FDEBUG(("Window 0x%p (event %d,ri:%d,rf:%d): "
            "Validating object %d: last reinit:%d, last validate:"
            "%d last refresh: %d => %s\n", 
            this, getGlObjectEventCounter(), 
            _mfGlObjectLastReinitialize.size(),
            _mfGlObjectLastRefresh.size(),
            osgId, 
            (_mfGlObjectLastReinitialize.size() > osgId)?
                _mfGlObjectLastReinitialize[osgId]:0xffffffff,
            _lastValidate[osgId],
            (_mfGlObjectLastRefresh.size() > osgId)?
                _mfGlObjectLastRefresh[osgId]:0xffffffff,
            (_mfGlObjectLastReinitialize[osgId] == 0)?"init":
            ((_mfGlObjectLastReinitialize[osgId] > _lastValidate[osgId])?"reinit":
            ((_mfGlObjectLastRefresh[osgId] > _lastValidate[osgId])?"refresh":
            "up-to-date"))
          ));
    
    if(_mfGlObjectLastReinitialize[osgId] == 0)
    {
        editMField( GlObjectLastReinitializeFieldId, 
                   _mfGlObjectLastReinitialize     );

        obj->incRefCounter();
        obj->getFunctor()(pEnv, osgId, initialize);
        _mfGlObjectLastReinitialize[osgId] = 1;
        _lastValidate[osgId] = getGlObjectEventCounter();
    }
    else if(_mfGlObjectLastReinitialize[osgId] > _lastValidate[osgId])
    {
        obj->getFunctor()(pEnv, osgId, reinitialize);
        _lastValidate[osgId] = getGlObjectEventCounter();
    }
    else if(_mfGlObjectLastRefresh[osgId] > _lastValidate[osgId])
    {
        obj->getFunctor()(pEnv, osgId, needrefresh);
        _lastValidate[osgId] = getGlObjectEventCounter();
    }
}

/*! Validate all existing GL objects. Use with care, and only if the correct
    OpenGL context is active.

    See \ref PageSystemOGLObjects for a description of the OpenGL object
    concept. 
*/
void OSG::Window::validateAllGLObjects(DrawEnv *pEnv)
{
    activate();
    frameInit();

    for (UInt32 i = 1; i < _glObjects.size(); ++i)
        validateGLObject(i, pEnv);
    
    frameExit();
}   

/*! Mark the given object for refresh. The next time it is validated the
    registered callback function will be called for a refresh action.

    See \ref PageSystemOGLObjects for a description of the OpenGL object
    concept. 
 */

void OSG::Window::refreshGLObject( UInt32 osgId )
{
    if(osgId == 0)
    {
        SWARNING << "Window::refreshGLObject: id is 0!" << std::endl;
        return;
    }

    std::vector<Window *>::iterator winIt;

    for(winIt = _allWindows.begin(); winIt != _allWindows.end(); ++winIt)
    {
        Window *pWin = convertToCurrentAspect(*winIt);

        if(pWin == NULL)
            continue;

        pWin->editMField(GlObjectLastRefreshFieldMask,
                         pWin->_mfGlObjectLastRefresh);

        UInt32    lastinv = pWin->getGlObjectEventCounter() + 1;

        MFUInt32 &field   = pWin->_mfGlObjectLastRefresh;

        if(field.size() <= osgId)
        {
            field.getValues().insert(field.end(), 
                                     osgId - field.size() + 1, 0 );
        }

        field[osgId] = lastinv;

        pWin->setGlObjectEventCounter(lastinv);
    }
}

/*! Refresh all existing GL objects.

    See \ref PageSystemOGLObjects for a description of the OpenGL object
    concept. 
*/
void OSG::Window::refreshAllGLObjects(void)
{
    for(UInt32 i = 1; i < _glObjects.size(); ++i)
        refreshGLObject(i);
}

/*! Mark the given object for reinitialisation. The next time it is validated
  the
  registered callback function will be called for a reinit action.
  
  See \ref PageSystemOGLObjects for a description of the OpenGL object
  concept. 
 */

void OSG::Window::reinitializeGLObject(UInt32 osgId)
{
    if ( osgId == 0 )
    {
        SWARNING << "Window::reinitializeGLObject: id is 0!" << std::endl;
        return;
    }

    std::vector<Window *>::iterator winIt;

    for(winIt = _allWindows.begin(); winIt != _allWindows.end(); ++winIt)
    {
        Window *pWin = convertToCurrentAspect(*winIt);

        if(pWin == NULL)
            continue;

        pWin->editMField(GlObjectLastReinitializeFieldMask,
                         pWin->_mfGlObjectLastReinitialize);

        UInt32    lastinv = pWin->getGlObjectEventCounter() + 1;

        MFUInt32 &field   = pWin->_mfGlObjectLastReinitialize;

        if(field.size() <= osgId)
            field.getValues().insert(field.end(), osgId - field.size() + 1, 0 );

        // is it already validated?
        if(field[osgId] == 0)
            continue;

        field[osgId] = lastinv;

        pWin->setGlObjectEventCounter(lastinv);
    }
}

/*! Reinitialize all existing GL objects.

    See \ref PageSystemOGLObjects for a description of the OpenGL object
    concept. 
*/
void OSG::Window::reinitializeAllGLObjects(void)
{
    for(UInt32 i = 1; i < _glObjects.size(); ++i)
        reinitializeGLObject(i);
}

/*! Initialize the GL object registration for the given objects in all
    Windows.

    See \ref PageSystemOGLObjects for a description of the OpenGL object
    concept. 
 */

void OSG::Window::initRegisterGLObject(UInt32 osgId, UInt32 num)
{
    if ( osgId == 0 )
    {
        SWARNING << "Window::initRegisterGLObject: id is 0!" << std::endl;
        return;
    }

    std::vector<Window *>::iterator winIt;

    for(winIt = _allWindows.begin(); winIt != _allWindows.end(); ++winIt)
    {
        Window *pWin = convertToCurrentAspect(*winIt);

        if(pWin == NULL)
            continue;

        pWin->doInitRegisterGLObject(osgId, num);
    }
}

/*! Initialize the GL object registration for the given objects in the given
    Window.

    See \ref PageSystemOGLObjects for a description of the OpenGL object
    concept. 
 */

void OSG::Window::doInitRegisterGLObject(UInt32 osgId, UInt32 num)
{
    editMField(GlObjectLastReinitializeFieldMask, _mfGlObjectLastReinitialize);
    editMField(GlObjectLastRefreshFieldMask,      _mfGlObjectLastRefresh     );


    if(_mfGlObjectLastReinitialize.size() < osgId + num)
        _mfGlObjectLastReinitialize.resize(osgId + num);

    if(_mfGlObjectLastRefresh.size() < osgId + num)
        _mfGlObjectLastRefresh.resize(osgId + num);

    if(_lastValidate.size() < osgId + num)
        _lastValidate.resize(osgId + num);

    for(UInt32 i = osgId; i < osgId + num; ++i)
    {
        _mfGlObjectLastReinitialize[i] = 0;
        _mfGlObjectLastRefresh     [i] = 0;
        _lastValidate              [i] = 0;
   }
}

/*! Mark the given objects for destruction. The actual destruction will happen
    later.

    See \ref PageSystemOGLObjects for a description of the OpenGL object
   concept. 
 */

void OSG::Window::destroyGLObject(UInt32 osgId, UInt32 num)
{
#ifdef OSG_DEBUG
    if(osgId >= _glObjects.size() || _glObjects[osgId] == NULL)
    {
        FWARNING(("Window::destroyGLObject: object %d is NULL!\n", osgId));
        return;
    }
#endif

    // Has this object ever been used?
    if(_glObjects[osgId] && _glObjects[osgId]->getRefCounter() == 0)
    {
        if(_glObjects[osgId])
            delete _glObjects[osgId];
        
        for(UInt32 j = 0; j < num ; j++)
        {
            _glObjects[osgId + j] = NULL;
        }

        return;
    }

    std::vector<Window *>::iterator winIt;

    for(winIt = _allWindows.begin(); winIt != _allWindows.end(); ++winIt)
    {
        Window *pWin = convertToCurrentAspect(*winIt);

        if(pWin == NULL)
            continue;

#ifdef OSG_DEBUG
        if(osgId + num > pWin->_mfGlObjectLastReinitialize.size())
        {
            FWARNING(("Window::destroyGLObject: id %d + num %d exceed"
                      "registered objects size %d!\n", osgId, num, 
                      pWin->_mfGlObjectLastReinitialize.size()));
            return;
        }
#endif

        // has the object been used in this context at all?
        if(pWin->getGlObjectLastReinitialize(osgId) != 0) 
            pWin->_glObjectDestroyList.push_back(DestroyEntry(osgId,num));
    }
}


/*----------------------- GL extension handling ---------------------------*/


/*! Register a new OpenGL extension. See \ref PageSystemOGLExt for details. 
    Ignores NULL strings. 
*/
UInt32 OSG::Window::registerExtension(const Char8 *s)
{
    FDEBUG(("Window::registerExtension: register '%s': ", s));

    staticAcquire();
   
    if(s == NULL)
    {
        staticRelease();
        return TypeTraits<UInt32>::getMax();
    }
    
    std::vector<std::string>::iterator i;
    
    i = std::find(_registeredExtensions.begin(), _registeredExtensions.end(), 
                  s);
    
    if(i < _registeredExtensions.end())
    {
        staticRelease();
        FPDEBUG(("reusing id %d\n", i - _registeredExtensions.begin()));
        return i - _registeredExtensions.begin();
    }
        
    UInt32 r = _registeredExtensions.size();
    _registeredExtensions.push_back(s);
    
    FPDEBUG(("new id %d\n", r));
    
    staticRelease();
    return r;
}

/*! Check if the Window supports the given extension. 
  Should be used for initialisation checks only, for checks done often it's
  recommended to register the extensions and use hasExtension(UInt32)
  instead.  
 */

bool OSG::Window::hasExtension(const Char8 *s)
{
    if(std::find(_ignoredExtensions.begin(),
                 _ignoredExtensions.end(),
                 s)                         != _ignoredExtensions.end())
    {
        return false;
    }
    
    if(std::find(_extensions.begin(),
                 _extensions.end(),
                 s)                         != _extensions.end())
    {
        return true;
    }
    
    return false;
}

/*! Register new OpenGL extensions to ignore. See \ref PageSystemOGLExt 
  for details. 
 */

void OSG::Window::ignoreExtensions(const Char8 *s)
{    
    FDEBUG(("Window:: Ignoring extensions '%s'\n", s));

    staticAcquire();
    
    std::back_insert_iterator< std::vector<std::string> > 
            extension_back_inserter(_ignoredExtensions);

    std::string toex(s);
    
    for(string_token_iterator ignit = string_token_iterator(toex, ",. ");
        ignit != string_token_iterator(); ++ignit)
    {          
        std::string ignore = *ignit;

        FDEBUG(("Ignoring '%s':", ignore.c_str()));
        
        if(std::find(_ignoredExtensions.begin(),
                     _ignoredExtensions.end(),
                     ignore.c_str())            != _ignoredExtensions.end())
        {
            FPDEBUG((" already ignored.\n"));
            continue;
        }
        
        _ignoredExtensions.push_back(ignore);
        
        std::vector<std::string>::iterator regit;
        
        // if extension is registered, disable it on all existing Windows
        
        regit = std::find(_registeredExtensions.begin(),
                          _registeredExtensions.end(),
                          ignore.c_str());                                 
        
        Int32 ind = -1;
        
        if(regit != _registeredExtensions.end())
        {
            ind = regit - _registeredExtensions.begin();
            FPDEBUG(("(reg as %d)", ind));
        }

        // Walk all existing windows and remove the ignored extension 
        // from the _extensions vector. Disable it if it was a registered one.
        
        std::vector<Window *>::iterator winit;

        for(winit = _allWindows.begin(); winit != _allWindows.end(); ++winit)
        {
            FPDEBUG((" %p:", (*winit)));
            
            std::vector<std::string>::iterator extit;
            
            extit = std::find((*winit)->_extensions.begin(),
                              (*winit)->_extensions.end(),
                              ignore.c_str()); 
                                                                     
            if(extit != (*winit)->_extensions.end())
            {
                FPDEBUG((" removed"));
                (*winit)->_extensions.erase(extit);
            }
            else
            {
                FPDEBUG((" nonsupp"));            
            }
                        
            if(ind >= 0)
            {
                if((*winit)->_availExtensions.size() > UInt32(ind))
                {
                    (*winit)->_availExtensions[ind] = false;
                    FPDEBUG((" disabled"));            
                }
                if((*winit)->_commonExtensions.size() > UInt32(ind))
                {
                    (*winit)->_commonExtensions[ind] = false;
                    FPDEBUG((" uncommoned"));            
                }
            }
        }
        FPDEBUG(("\n"));    
    }

    std::sort(_ignoredExtensions.begin(), _ignoredExtensions.end());
    
    staticRelease();
}

/*! Register a new OpenGL extension function. See \ref PageSystemOGLExt for 
    details. Ignores NULL strings.
 */

UInt32 OSG::Window::registerFunction(const Char8 *s, 
                                           Int32  ext,
                                           UInt32 version)
{
    if(s == NULL)
        return TypeTraits<UInt32>::getMax();

    FDEBUG(("Window::registerFunction: register '%s': ", s));

    staticAcquire();
    
    std::vector<std::string>::iterator i;
    
    i = std::find(_registeredFunctions.begin(), _registeredFunctions.end(), 
                  s);
    
    if(i < _registeredFunctions.end())
    {
        staticRelease();
        FPDEBUG(("reusing id %d\n", i - _registeredFunctions.begin()));
        return i - _registeredFunctions.begin();
    }
            
    UInt32 r=_registeredFunctions.size();

    _registeredFunctions       .push_back(s);
    _registeredFunctionExts    .push_back(ext);
    _registeredFunctionVersions.push_back(version);

    FPDEBUG(("new id %d\n", r));
    
    staticRelease();
    return r;
}

/*! Register a new OpenGL constant. See \ref PageSystemOGLExt for 
    details.
 */

void OSG::Window::registerConstant(GLenum val)
{
    staticAcquire();
   
    if(std::find(_registeredConstants.begin(), 
                 _registeredConstants.end  (),
                 val                        ) ==  _registeredConstants.end())
    {
        _registeredConstants.push_back(val);
    }

    staticRelease();
}

#endif // remove the OpenGL object handling from user docs

/*! Dump all the registered extensions to std::cout.

    See \ref PageSystemOGLObjects for a description of the OpenGL object
    concept. 
 */

void OSG::Window::dumpExtensions(void)
{   
    std::vector<std::string>::iterator it;
    std::cout << "GL Extensions: ";

    for(it = _extensions.begin(); it != _extensions.end(); ++it)
    {
        std::cout << it->c_str() << ", ";
    }

    std::cout << std::endl;       
}


/*! Do everything that needs to be done before the Window is redrawn. This
    function has to be called for every frame the Window is drawn. 
    
    The convenience functions render and draw take care of it, if they are
    used.
    
    The main task currently is checking and updating OpenGL extensions.
 */

void OSG::Window::frameInit(void)
{
    static bool ignoreEnvDone = false;
    
    if(!ignoreEnvDone)
    {
        ignoreEnvDone = true;

#ifndef OSG_WINCE
        Char8 *p = getenv("OSG_IGNORE_EXTENSIONS");
        
        if(p)
            ignoreExtensions(p);
#endif
    }
    
    // Do we need to call init()
    if(_initNeeded)
    {
        _initNeeded = false;
        
        init();
    }
    
    // get version/extensions and split them
    if(_extensions.empty())
    {
        const char *version = 
                reinterpret_cast<const char *>(glGetString(GL_VERSION));
        
        int major = atoi(version);
        int minor = atoi(strchr(version, '.') + 1);
        
        _glVersion = (major << 8) + minor;
        
        FDEBUG(("Window %p: GL Version: %4x ('%s')\n", this, 
                _glVersion, glGetString(GL_VERSION) ));

        FDEBUG(("Window %p: GL Extensions: %s\n", this, 
                glGetString(GL_EXTENSIONS) ));

        std::string foo(reinterpret_cast<const char*>
                        (glGetString(GL_EXTENSIONS)));

        FDEBUG(("Window %p: Ignored: ", this));

        for(string_token_iterator it = string_token_iterator(foo, ",. ");
            it != string_token_iterator(); ++it)
        {          
            if(! std::binary_search(_ignoredExtensions.begin(),
                                    _ignoredExtensions.end(),
                                    *it))
            {
                _extensions.push_back(*it);
            }
            else
            {
                FPDEBUG(("%s ", (*it).c_str()));
            }
        }
        FPDEBUG(("\n"));
        std::sort(_extensions.begin(), _extensions.end());
                 
        // if we don't have any extensions, add something anyway
        if(_extensions.empty())
            _availExtensions.resize(_registeredExtensions.size(), false);
    }
    
    // any new extension registered ? 
    if(_registeredExtensions.size() > _availExtensions.size())
    {
        staticAcquire();
        FDEBUG(("Window %p: exts: ", this));

        while(_registeredExtensions.size() > _availExtensions.size())
        {                          
            UInt32 s = _availExtensions.size();

            /* perform a binary search over the retrieved extension strings.
               Push back the result as an availability flag for the extension
               requested by the application */         
            bool supported = std::binary_search( 
                                _extensions.begin(),
                                _extensions.end(),
                                _registeredExtensions[s]);

            /* Is this extension ignored? */
            bool ignored   = std::binary_search( 
                                _ignoredExtensions.begin(),
                                _ignoredExtensions.end(),
                                _registeredExtensions[s]);

            _availExtensions.push_back(supported && !ignored);

            FPDEBUG(("%s:", _registeredExtensions[s].c_str()));

            if(_commonExtensions.size() <= s)
            {
                _commonExtensions.push_back(supported && !ignored);

                if(supported && !ignored)
                {
                    FPDEBUG(("ok "));
                }
                else if(!supported)
                {
                    FPDEBUG(("NF "));
                }
                else
                {
                    FPDEBUG(("IGN "));
                }
            }
            else if (!supported)
            {
                _commonExtensions[s] = false;
                FPDEBUG(("NF "));
            }
            else
            {
                _commonExtensions[s] = false;
                FPDEBUG(("IGN "));
            }
        }
        FPDEBUG(("\n"));
        staticRelease();
    }
    
    // any new functions registered ? 
    while(_registeredFunctions.size() > _extFunctions.size())
    {   
        const Char8 *s    = _registeredFunctions[_extFunctions.size()].c_str();

        Int32        ext  = _registeredFunctionExts    [_extFunctions.size()];
        UInt32       ver  = _registeredFunctionVersions[_extFunctions.size()];

        GLExtensionFunction func = NULL;
        
        if(ext == -1 || _availExtensions[ext] == true || _glVersion >= ver)
            func = getFunctionByName(s);

        _extFunctions.push_back(func);
    }

#ifndef OSG_WINCE
    // any new constants registered ? 
    while(_registeredConstants.size() > _numAvailConstants)
    {   
        for(std::vector<GLenum>::iterator it = _registeredConstants.begin() + 
                                               _numAvailConstants;
            it != _registeredConstants.end();
            ++it)
        {
            Vec2f val(unknownConstant, unknownConstant); 
            glGetFloatv(*it, static_cast<GLfloat*>(val.getValues()));
            _availConstants[*it] = val;
            FDEBUG(("Window(%p): Constant 0x%x value is %.3f %.3f\n", this,
                    *it, val[0], val[1]));
        }
        _numAvailConstants = _registeredConstants.size();

        glGetError(); // clear the error flag 
    }
#endif

    _pStageValidator->incEventCounter();
}

/*! Do everything that needs to be done after the Window is redrawn. This
    function has to be called for every frame the Window is drawn. 
    
    The convenience functions render and draw take care of it, if they are
    used.

    The main task currently is deleting OpenGL objects.
 */

void OSG::Window::frameExit(void)
{   
    std::list<DestroyEntry>::iterator st,en;

    st = _glObjectDestroyList.begin();
    en = _glObjectDestroyList.end  ();

    DrawEnv oEnv;

    oEnv.setWindow(this);

    while(st != en)
    {
        UInt32 i = st->first, n = st->second;

        GLObject *obj = _glObjects[i];
        
        if(obj == NULL)
        {
            FDEBUG(("Window::frameExit: objects %d (%d) already destroyed ?\n",
                    i, n));
            ++st;
            continue;
        }
           
        UInt32 rc = obj->getRefCounter();

        // has the object been used in this context at all?
        if(getGlObjectLastReinitialize(i) != 0) 
        {                  
            _glObjects[i]->getDestroyFunctor()(&oEnv, i, destroy);

            if((rc = _glObjects[ i ]->decRefCounter()) <= 0)
            {           
                // call functor with the final-flag
                _glObjects[i]->getDestroyFunctor()(&oEnv, i, finaldestroy);
            }
        }

        // if the GLObject is removed from each GL-Context, free GLObject-IDs.
        if(rc <= 0)
        {
            delete _glObjects[i];

            for(UInt32 j = 0; j < n ; j++)
            {
                _glObjects[i+j] = NULL;
            }   
        }

        ++st;
    }

    _glObjectDestroyList.clear();

    // Test for OpenGL errors. Just a little precaution to catch
    // stray errors. This is the only OpenGL error test in opt mode
    // and it needs to be enabled using the OSG_TEST_GL_ERRORS envvar.
    // In debug mode it is always on.
 
    static bool inited = false;
#ifndef OSG_DEBUG
    static bool testGLErrors = false;
#else
    static bool testGLErrors = true;
#endif

    if(!inited)
    {
        inited = true;
        char *p = getenv("OSG_DEBUG");
        if(p)
            testGLErrors = true;
    }
 
    if(testGLErrors)
    {
        GLenum glerr;
        
        while((glerr = glGetError()) != GL_NO_ERROR)
        {
#ifndef OSG_WINCE
            FWARNING(("Window::frameExit: Caught stray OpenGL "
                      "error %s (%#x).\n",
                      gluErrorString(glerr),
                      glerr));
#else
            FWARNING(("Window::frameExit: Caught stray OpenGL error %#x.\n",
                      glerr));
#endif

#ifndef OSG_DEBUG
            FWARNING(("Rerun with debug-libraries to get more accurate "
                      "information.\n"));
#endif
        }
    }
    
}


// Query for a GL extension function
// Yes, this is system dependent, but the system dependent parts are 
// #ifdefed anyway, and very similar code would show up in a number of places,
// making maintaining it unnecessarily hard
// Note: the order of the cases is important, do not change it!

/*! Query OpenGL for the pointer to an extension function. 

    This is called internally when extension functions are first cached. 
 */

OSG::Window::GLExtensionFunction OSG::Window::getFunctionByName(
    const Char8 *s)
{
    GLExtensionFunction retval = NULL;

#if defined(__APPLE__)

    if (NSIsSymbolNameDefined(s))
    {
        NSSymbol symbol = NSLookupAndBindSymbol(s);

        if(symbol != 0)
            retval = GLExtensionFunction(NSAddressOfSymbol(symbol));
    }
#elif defined(OSG_WINCE)

	retval = (void(__cdecl*)(void)) eglGetProcAddress(s);

#elif defined(WIN32)

    retval = (void(__cdecl*)(void)) wglGetProcAddress(s);
    
#elif defined(__sgi)   || defined(__hpux) || \
      defined(__linux) || defined(__sun)

    /* Workaround for multiple nVidia/Linux installation bugs, based on 
       code by
       Manfred Weiler (Patch 783637) 
     */
    
    static void (*(*__GetProcAddress)(const GLubyte *))(void) = NULL; 

    static void *libHandle = NULL; 

    if(libHandle == NULL) 
    { 
        libHandle = dlopen(_glLibraryName, RTLD_NOW | RTLD_LOCAL); 

        if(!libHandle) 
        { 
            FWARNING(("Error in dlopen: %s\n",dlerror())); 
            abort(); 
        } 
        else
        {
            FDEBUG(("Opened lib %s for GL extension handling.\n", 
                    (_glLibraryName==NULL) ? "(executable)" : _glLibraryName));
        }
    } 

    if(__GetProcAddress == NULL) 
    { 
        __GetProcAddress = 
#if __GNUC__ < 4
            (void (*(*)(const GLubyte*))())
#else
            reinterpret_cast<void (*(*)(const GLubyte*))()>
#endif
                (dlsym(libHandle, 
                      "glXGetProcAddressARB")); 

        if(__GetProcAddress == NULL) 
        { 
            __GetProcAddress = 
#if __GNUC__ < 4
                (void (*(*)(const GLubyte*))())
#else
                reinterpret_cast<void (*(*)(const GLubyte*))()>
#endif
                    (dlsym(libHandle, 
                          "glXGetProcAddress")); 

            if(__GetProcAddress == NULL) 
            {
                // Couldn't find it linked to the executable. Try to open
                // libGL.so directly.
                
                dlclose(libHandle);
                
                libHandle = dlopen("libGL.so", RTLD_NOW | RTLD_GLOBAL); 

                if(!libHandle) 
                { 
                    FWARNING(("Error in dlopen: %s\n",dlerror())); 
                    abort(); 
                } 
                else
                {
                    FDEBUG(("Opened libGL.so for GL extension handling.\n"));
                }
                
                __GetProcAddress = 
#if __GNUC__ < 4
                    (void (*(*)(const GLubyte*))())
#else
                    reinterpret_cast<void (*(*)(const GLubyte*))()>
#endif
                        (dlsym(libHandle, "glXGetProcAddressARB")); 

                if(__GetProcAddress == NULL) 
                { 
                    __GetProcAddress = 
#if __GNUC__ < 4
                        (void (*(*)(const GLubyte*))())
#else
                        reinterpret_cast<void (*(*)(const GLubyte*))()>
#endif
                            (dlsym(libHandle, "glXGetProcAddress")); 
                }


                if(__GetProcAddress == NULL) 
                {
                    FWARNING(("Neither glXGetProcAddress nor "
                              "glXGetProcAddressARB found! Disabling all "
                              " extensions for Window %p!\n")); 
                    
                    _availExtensions.clear();
                    _availExtensions.resize(_registeredExtensions.size(), 
                                            false);
                }
            } 
            else
            {
                FDEBUG(("Using glXGetProcAddress for GL "
                        "extension handling.\n"));
            }
        } 
        else
        {
            FDEBUG(("Using glXGetProcAddressARB for GL "
                    "extension handling.\n"));
        }
    } 

    if(__GetProcAddress != NULL) 
    { 
        retval = 
            reinterpret_cast<GLExtensionFunction>(
                __GetProcAddress(reinterpret_cast<const GLubyte*>(s))); 
    } 
    else 
    { 
        retval = 
#if __GNUC__ < 4
            (GLExtensionFunction)
#else
            reinterpret_cast<GLExtensionFunction>
#endif
                (dlsym(libHandle, s)); 
    } 

#else

    FWARNING(("Window::getFunctionByName: couldn't find implementation!\n"
              "Please contact the developers at info@opensg.org.\n"));

    retval = NULL;
#endif

    if(retval == NULL)
    {
        FWARNING(("Window::getFunctionByName: Couldn't get function '%s' for "
                 "Window %p.\n", s, this));
    }
    else
    {
        FDEBUG(("Window::getFunctionByName: got function '%s' for "
                 "Window %p at %p.\n", s, this, retval));
    }

    return retval;
}


/*! Return the value of the registered constant, (Inf, Inf) if not
    registered or no value received yet.
*/
const Vec2f& OSG::Window::getConstantValuev(GLenum val)
{
    static Vec2f inf(Inf, Inf);

    ConstHash::iterator it = _availConstants.find(val);

    if(it != _availConstants.end())
        return _availConstants[val];

    return inf;
}


/*! Initialize the OpenGL state OpenSG expects. This should be called once
    whenever a new Window is opened.
    
    Don't call it directly, call the Window System-specific init() method
    instead.
 */

void OSG::Window::setupGL( void )
{   
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glPixelStorei(GL_PACK_ALIGNMENT,   1);
    
    glDepthFunc(GL_LEQUAL    );
    glEnable   (GL_DEPTH_TEST);
    
    glEnable   (GL_NORMALIZE );
    
    // switch off default light
    Real nul[4]={0.f,0.f,0.f,0.f};

    GLP::glLightfv(GL_LIGHT0, GL_DIFFUSE,  nul);
    GLP::glLightfv(GL_LIGHT0, GL_SPECULAR, nul);
    
    frameInit();    // call it to setup extensions
}

/*-------------------------- your_category---------------------------------*/
    
#ifdef OSG_OLD_RENDER_ACTION

/*! Render the Window using the given RenderAction. 

    It takes care of all initialisation and cleanup functions and contains just
    5 lines of code. If you know that the correct context is active or you want
    to delay swaps you can just copy and manipulate it.
 */   
void OSG::Window::render(DrawActionBase *action)
{
    activate ();
    frameInit();    // query recently registered GL extensions
    
    renderAllViewports(action);

    swap     ();
    frameExit();    // after frame cleanup: delete GL objects, if needed
}
    

/*! Render all the Viewports of the Window using the given RenderAction. 

    A simple convenience function that loops all Viewports and call their draw
    method.
 */   

void OSG::Window::renderAllViewports(DrawActionBase *action)
{
    MFViewportPtr::const_iterator portIt  = _mfPort.begin();
    MFViewportPtr::const_iterator portEnd = _mfPort.end();

    if(action != NULL)
    {
        action->setWindow(this);
        
        while(portIt != portEnd)
        {
            (*portIt)->render(action);
            ++portIt;
        }
    }
    else
    {
        SWARNING << "Window::renderAllViewports: no action!" << std::endl;
    }
}
#endif

/*! Render the Window using the given RenderAction. 

    It takes care of all initialisation and cleanup functions and contains just
    5 lines of code. If you know that the correct context is active or you want
    to delay swaps you can just copy and manipulate it.
 */   
void OSG::Window::render(RenderActionBase *action)
{
    activate ();
    frameInit();    // query recently registered GL extensions
    
    renderAllViewports(action);

    swap     ();
    frameExit();    // after frame cleanup: delete GL objects, if needed
}
    

/*! Render all the Viewports of the Window using the given RenderAction. 

    A simple convenience function that loops all Viewports and call their draw
    method.
 */   

void OSG::Window::renderAllViewports(RenderActionBase *action)
{
    MFUnrecChildViewportPtr::const_iterator portIt  = _mfPort.begin();
    MFUnrecChildViewportPtr::const_iterator portEnd = _mfPort.end();

    if(action != NULL)
    {
        action->setWindow(this);
        
        while(portIt != portEnd)
        {
            (*portIt)->render(action);
            ++portIt;
        }
    }
    else
    {
        SWARNING << "Window::renderAllViewports: no action!" << std::endl;
    }
}

/*! Resize notifier function. 

    As OpenSG does not do Window System event management it needs to be
    notified whenever the size of a Window changes. 
 */   

void OSG::Window::resize( int width, int height )
{
    setWidth        (width );
    setHeight       (height);
    setResizePending(true  );
}
    

/*! Resize function. 

    This function needs to be called before a Window's Viewports are rendered,
    to ensure that eventual pending resizes are handled correctly. 
 */   

void OSG::Window::resizeGL( void )
{
    if(isResizePending() == true)
    {
        glViewport(0, 0, getWidth(), getHeight());

        setResizePending(false);
    }
}

/*-------------------------- assignment -----------------------------------*/

#if 0 // This is wrong, the vp parents are not setup correctly
/*! Assignment
*/

OSG::Window& OSG::Window::operator = (const OSG::Window &source)
{
    if(this == &source)
        return *this;

    // copy 

    setWidth (source.getWidth());
    setHeight(source.getHeight());

    editMField(PortFieldMask, _mfPort);

    _mfPort.resize(source._mfPort.size());

    for(UInt32 i = 0; i < source._mfPort.size(); ++i)
    {
        setRefd(_mfPort[i], source._mfPort[i]);
    }
    
    // mark all GL objects as not yet initialized
    doInitRegisterGLObject(1, _glObjects.size() - 1);
    
    return *this;
}
#endif

/*------------------------------- dump ----------------------------------*/

/*! output the instance for debug purposes
*/
void OSG::Window::dump(      UInt32    OSG_CHECK_ARG(uiIndent), 
                       const BitVector OSG_CHECK_ARG(bvFlags )) const
{
    SLOG << "Dump Window NI" << std::endl;
}

