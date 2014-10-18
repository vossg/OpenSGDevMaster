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

#include <cstdlib>
#include <cstdio>
#include <boost/bind.hpp>

#include "OSGConfig.h"

#include "OSGGLFuncProtos.h"

#include "OSGGeometry.h"
#include "OSGGeoPumpGroup.h"

#include "OSGAction.h"
#include "OSGRenderAction.h"
#include "OSGIntersectAction.h"
#include "OSGDrawEnv.h"

//#include "OSGIntersectActor.h"

#include "OSGTriangleIterator.h"
#include "OSGPrimitiveIterator.h"
#include "OSGFaceIterator.h"
#include "OSGLineIterator.h"
#include "OSGEdgeIterator.h"
#include "OSGPointIterator.h"
#include "OSGDrawableStatsAttachment.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emited in the
// OSGGeometryBase.cpp file.
// To modify it, please change the .fcd file (OSGGeometry.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

Geometry::PumpGroupStorage Geometry::_pumps;

UInt32 Geometry::_arbVertexArrayObject       = Window::invalidExtensionID;
UInt32 Geometry::_arbTessellationShader      = Window::invalidExtensionID;
UInt32 Geometry::_arbDrawInstanced           = Window::invalidExtensionID;

UInt32 Geometry::FuncIdBindVertexArray       = Window::invalidFunctionID;
UInt32 Geometry::FuncIdDeleteVertexArrays    = Window::invalidFunctionID;
UInt32 Geometry::FuncIdGenVertexArrays       = Window::invalidFunctionID;
UInt32 Geometry::FuncPatchParameterI         = Window::invalidFunctionID;
UInt32 Geometry::FuncIdDrawElementsInstanced = Window::invalidFunctionID;
UInt32 Geometry::FuncIdDrawArraysInstanced   = Window::invalidFunctionID;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void Geometry::initMethod(InitPhase ePhase)
{
    if(ePhase == TypeObject::SystemPost)
    {
        IntersectAction::registerEnterDefault(
            getClassType(),
            reinterpret_cast<Action::Callback>(&Geometry::intersectEnter));

        RenderAction::registerEnterDefault(
            getClassType(),
            reinterpret_cast<Action::Callback>(
                &MaterialDrawable::renderEnter));
                
        RenderAction::registerLeaveDefault(
            getClassType(),
            reinterpret_cast<Action::Callback>(
                &MaterialDrawable::renderLeave));


#ifndef __APPLE__
        _arbVertexArrayObject = 
            Window::registerExtension("GL_ARB_vertex_array_object");

        FuncIdBindVertexArray    = 
            Window::registerFunction
            (OSG_DLSYM_UNDERSCORE"glBindVertexArray",
             _arbVertexArrayObject);

        FuncIdDeleteVertexArrays = 
            Window::registerFunction
            (OSG_DLSYM_UNDERSCORE"glDeleteVertexArrays",
             _arbVertexArrayObject);

        FuncIdGenVertexArrays    = 
            Window::registerFunction
            (OSG_DLSYM_UNDERSCORE"glGenVertexArrays",
             _arbVertexArrayObject);

#else
        _arbVertexArrayObject = 
            Window::registerExtension("GL_APPLE_vertex_array_object");

        FuncIdBindVertexArray    = 
            Window::registerFunction
            (OSG_DLSYM_UNDERSCORE"glBindVertexArrayAPPLE",
             _arbVertexArrayObject);

        FuncIdDeleteVertexArrays = 
            Window::registerFunction
            (OSG_DLSYM_UNDERSCORE"glDeleteVertexArraysAPPLE",
             _arbVertexArrayObject);

        FuncIdGenVertexArrays    = 
            Window::registerFunction
            (OSG_DLSYM_UNDERSCORE"glGenVertexArraysAPPLE",
             _arbVertexArrayObject);
#endif

        _arbTessellationShader = 
            Window::registerExtension("GL_ARB_tessellation_shader");

        _arbDrawInstanced = 
            Window::registerExtension("GL_ARB_draw_instanced");

        FuncPatchParameterI   = 
            Window::registerFunction
            (OSG_DLSYM_UNDERSCORE"glPatchParameteri",
             _arbTessellationShader);

        FuncIdDrawElementsInstanced = 
            Window::registerFunction
            (OSG_DLSYM_UNDERSCORE"glDrawElementsInstanced",
             _arbDrawInstanced);

        FuncIdDrawArraysInstanced   = 
            Window::registerFunction
            (OSG_DLSYM_UNDERSCORE"glDrawArraysInstanced",
             _arbDrawInstanced);
    }
}


/*! A little helper function to map the OpenGL primitive type to a name.
*/
const char *Geometry::mapType(UInt8 type)
{
    switch(type)
    {
        case GL_POINTS:                       return "Points";
        case GL_LINES:                        return "Lines";
        case GL_LINE_LOOP:                    return "LineLoop";
        case GL_LINE_STRIP:                   return "LineStrip";
        case GL_TRIANGLES:                    return "Triangles";
        case GL_TRIANGLE_STRIP:               return "TriangleStrip";
        case GL_TRIANGLE_FAN:                 return "TriangleFan";
        case GL_QUADS:                        return "Quads";
        case GL_QUAD_STRIP:                   return "QuadStrip";
        case GL_POLYGON:                      return "Polygon";
        case GL_PATCHES:                      return "Patches";
        case GL_LINES_ADJACENCY_EXT:          return "LinesAdjacency";
        case GL_LINE_STRIP_ADJACENCY_EXT:     return "LineStripAdjacency";
        case GL_TRIANGLES_ADJACENCY_EXT:      return "TrianglesAdjacency";
        case GL_TRIANGLE_STRIP_ADJACENCY_EXT: return "TriangleStripAdjacency";
    }

    return "Unknown Primitive";
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

Geometry::Geometry(void) :
     Inherited  (),
    _volumeCache()
{
}

Geometry::Geometry(const Geometry &source) :
     Inherited  (source             ),
    _volumeCache(source._volumeCache)
{
}

Geometry::~Geometry(void)
{
}

void Geometry::onCreate(const Geometry *source)
{
    Inherited::onCreate(source);

    // if we're in startup this is the prototype, which shouldn't have an id
    if(GlobalSystemState == Startup)
        return;

#if !defined(OSG_OGL_COREONLY)
    setClassicGLId(               
        Window::registerGLObject(
            boost::bind(&Geometry::handleClassicGL,
                        GeometryMTUncountedPtr(this), 
                        _1, _2, _3, _4),
            &Geometry::handleClassicDestroyGL));
#endif

    setAttGLId(               
        Window::registerGLObject(
            boost::bind(&Geometry::handleAttGL,
                        GeometryMTUncountedPtr(this), 
                        _1, _2, _3, _4),
            &Geometry::handleAttDestroyGL));

    setClassicVaoGLId(               
        Window::registerGLObject(
            boost::bind(&Geometry::handleVAOGL,
                        GeometryMTUncountedPtr(this), 
                        _1, _2, _3, _4),
            &Geometry::handleVAODestroyGL));
    setAttribVaoGLId(               
        Window::registerGLObject(
            boost::bind(&Geometry::handleVAOGL,
                        GeometryMTUncountedPtr(this), 
                        _1, _2, _3, _4),
            &Geometry::handleVAODestroyGL));
}

void Geometry::onDestroy(UInt32 uiContainerId)
{
#if !defined(OSG_OGL_COREONLY)
    if(getClassicGLId() > 0)
        Window::destroyGLObject(getClassicGLId(), 1);
#endif

    if(getAttGLId() > 0)
        Window::destroyGLObject(getAttGLId(), 1);

    if(getClassicVaoGLId() > 0)
        Window::destroyGLObject(getClassicVaoGLId(), 1);

    if(getAttribVaoGLId() > 0)
        Window::destroyGLObject(getAttribVaoGLId(), 1);

    Inherited::onDestroy(uiContainerId);
}


/*------------------------------ access -----------------------------------*/

void Geometry::adjustVolume(Volume & volume)
{
    if(!_volumeCache.isEmpty())
    {
        // use cached volume.
        volume.setValid();
        volume.extendBy(_volumeCache);

        return;
    }

    GeoVectorProperty *pos = getPositions();

    if(pos == NULL)
        return;                  // Node has no points, no volume

    _volumeCache.setValid();
    
    PrimitiveIterator it  = this->beginPrimitives();
    PrimitiveIterator end = this->endPrimitives  ();

    for(; it != end; ++it)
    {
        for(UInt32 v = 0; v < it.getLength(); ++v)
        {
            _volumeCache.extendBy(it.getPosition(v));
        }
    }

    volume.extendBy(_volumeCache);
}

/*! OpenGL object handler. Used for DisplayList caching.
*/

UInt32 Geometry::handleClassicGL(DrawEnv                 *pEnv, 
                                 UInt32                   id, 
                                 Window::GLObjectStatusE  mode,
                                 UInt64                   uiOptions)
{
#if !defined(OSG_OGL_COREONLY) || defined(OSG_CHECK_COREONLY)
    UInt32                   glid;
    Window                  *pWin      = pEnv->getWindow();
    GLHandlerOptions         glOptions = { uiOptions };

#ifdef OSG_DEBUG
    Geometry *pAspectGeo = Aspect::convertToCurrent<Geometry *>(this);
    OSG_ASSERT(pAspectGeo == this);
#endif

    if(mode == Window::initialize || mode == Window::needrefresh ||
       mode == Window::reinitialize)
    {
        if(mode == Window::initialize)
        {
            glid = glGenLists(1);
            pWin->setGLObjectId(id, glid);
        }
        else
        {
            glid = pWin->getGLObjectId(id);
        }

        GeoPumpGroup::PropertyCharacteristics prop = glOptions.uiOptions;

        if(((prop & (GeoPumpGroup::SingleIndexed | 
                     GeoPumpGroup::NonIndexed    )) == 0x0000))
        {
            GeoPumpGroup::GeoPump pump = GeoPumpGroup::findGeoPump(pEnv, prop);

            glNewList(glid, GL_COMPILE);

            if(pump)
            {
                pump(pEnv,
                     getLengths(),      getTypes(),
                     getMFProperties(), getMFPropIndices(),
                     glOptions.uiNumInstances             );
            }
            else
            {
                SWARNING << "Geometry::handleClassicGL: no Pump found for "
                         << "geometry "
                         << this
                         << std::endl;
            }

            glEndList();
        }
        else if(_sfUseVAO.getValue() == false ||
            !pWin->hasExtension(_arbVertexArrayObject) ||
            (prop &   GeoPumpGroup::AllVAOMask) != GeoPumpGroup::AllVAOMask)
        {
            GeoPumpGroup::SplitGeoPump pump = 
                GeoPumpGroup::findSplitGeoPump(pEnv,
                                               prop);

            if(pump.drawPump != NULL)
            {
                glNewList(glid, GL_COMPILE);

                pump.drawPump(pEnv,
                              getLengths(),      getTypes(),
                              getMFProperties(), getMFPropIndices(),
                              glOptions.uiNumInstances             );

                glEndList();
            }
            else
            {
                SWARNING << "Geometry::handleClassicGL: no Pump found for "
                         << "geometry "
                         << this
                         << std::endl;
            }
        }
        else
        {
            Int32 vaoGlid = 
                (glOptions.value & 
                 GeoPumpGroup::UsesShader) ? getAttribVaoGLId () : 
                                             getClassicVaoGLId();

            pWin->validateGLObject(vaoGlid, pEnv, glOptions.value);
        
            UInt32 uiValidVAO = pWin->getGLObjectInfo(vaoGlid) & ValidVAO;

            if(uiValidVAO != 0)
            {
                GeoPumpGroup::SplitGeoPump pump = 
                    GeoPumpGroup::findSplitGeoPump(pEnv,
                                                   prop);

                if(pump.drawPump != NULL)
                {
                    OSGGETGLFUNCBYID_GL3(glBindVertexArray,
                                         osgGlBindVertexArray,
                                         FuncIdBindVertexArray,
                                         pWin);
                    
                    osgGlBindVertexArray(pWin->getGLObjectId(vaoGlid));
                    
                    glNewList(glid, GL_COMPILE);

                    pump.drawPump(pEnv,
                                  getLengths(),      getTypes(),
                                  getMFProperties(), getMFPropIndices(),
                                  glOptions.uiNumInstances             );
                    
                    glEndList();

                    osgGlBindVertexArray(0);
                }
                else
                {
                    SWARNING << "Geometry::handleClassicGL: no Pump found for "
                             << "geometry "
                             << this
                             << std::endl;
                }
            }
        }
    }
    else
    {
        SWARNING << "Geometry(" << this << ")::handleClassicGL: Illegal mode: "
                 << mode << " for id " << id << std::endl;
    }
#endif

    return 0;
}

void Geometry::handleClassicDestroyGL(DrawEnv                 *pEnv, 
                                      UInt32                   id, 
                                      Window::GLObjectStatusE  mode)
{
#if !defined(OSG_OGL_COREONLY) || defined(OSG_CHECK_COREONLY)
    UInt32                   glid;
    Window                  *pWin = pEnv->getWindow();

    if(mode == Window::destroy)
    {
        glid = pWin->getGLObjectId(id);

        glDeleteLists(glid, 1);
    }
    else if(mode == Window::finaldestroy)
    {
        //SWARNING << "Last geometry user destroyed" << std::endl;
    }
    else
    {
        SWARNING << "Geometry::handleClassicDestroyGL: Illegal mode: "
                 << mode << " for id " << id << std::endl;
    }
#endif
}

UInt32 Geometry::handleAttGL(DrawEnv                 *pEnv, 
                             UInt32                   id, 
                             Window::GLObjectStatusE  mode,
                             UInt64                   uiOptions)
{
#if !defined(OSG_OGL_COREONLY) || defined(OSG_CHECK_COREONLY)
    UInt32            glid;
    Window           *pWin = pEnv->getWindow();
    GLHandlerOptions  glOptions = { uiOptions };

    if(mode == Window::initialize || mode == Window::needrefresh ||
       mode == Window::reinitialize)
    {
        if(mode == Window::initialize)
        {
            glid = glGenLists(1);
            pWin->setGLObjectId(id, glid);
        }
        else
        {
            glid = pWin->getGLObjectId(id);
        }

        GeoPumpGroup::PropertyCharacteristics prop = glOptions.uiOptions;

        if(((prop & (GeoPumpGroup::SingleIndexed | 
                     GeoPumpGroup::NonIndexed    )) == 0x0000))
        {
            GeoPumpGroup::GeoPump pump = GeoPumpGroup::findGeoPump(pEnv, 
                                                                   prop);
            glNewList(glid, GL_COMPILE);

            if(pump != NULL)
            {
                pump(pEnv,
                     getLengths(),      getTypes(),
                     getMFProperties(), getMFPropIndices(),
                     glOptions.uiNumInstances             );
            }
            else
            {
                SWARNING << "Geometry::handleAttGL: no Pump found for "
                         << "geometry "
                         << this
                         << std::endl;
            }

            glEndList();
        }
        else if(_sfUseVAO.getValue() == false ||
            !pWin->hasExtension(_arbVertexArrayObject) ||
            (prop &   GeoPumpGroup::AllVAOMask) != GeoPumpGroup::AllVAOMask)
        {
            GeoPumpGroup::SplitGeoPump pump = 
                GeoPumpGroup::findSplitGeoPump(pEnv, 
                                               prop);

            if(pump.drawPump != NULL)
            {
                glNewList(glid, GL_COMPILE);

                pump.drawPump(pEnv,
                              getLengths(),      getTypes(),
                              getMFProperties(), getMFPropIndices(),
                              glOptions.uiNumInstances             );

                glEndList();
            }
            else
            {
                SWARNING << "Geometry::handleAttGL: no Pump found for "
                         << "geometry "
                         << this
                         << std::endl;
            }
        }
        else
        {
            Int32 vaoGlid = 
                (glOptions.value & 
                 GeoPumpGroup::UsesShader) ? getAttribVaoGLId () : 
                                             getClassicVaoGLId();

            pWin->validateGLObject(vaoGlid, pEnv, glOptions.value);
        
            UInt32 uiValidVAO = pWin->getGLObjectInfo(vaoGlid) & ValidVAO;

            if(uiValidVAO != 0)
            {
                GeoPumpGroup::SplitGeoPump pump = 
                    GeoPumpGroup::findSplitGeoPump(pEnv,
                                                   prop);

                if(pump.drawPump != NULL)
                {
                    OSGGETGLFUNCBYID_GL3(glBindVertexArray,
                                         osgGlBindVertexArray,
                                         FuncIdBindVertexArray,
                                         pWin);
                    
                    osgGlBindVertexArray(pWin->getGLObjectId(vaoGlid));
                    
                    glNewList(glid, GL_COMPILE);

                    pump.drawPump(pEnv,
                                  getLengths(),      getTypes(),
                                  getMFProperties(), getMFPropIndices(),
                                  glOptions.uiNumInstances             );
                    
                    glEndList();

                    osgGlBindVertexArray(0);
                }
                else
                {
                    SWARNING << "Geometry::handleAttGL: no Pump found for "
                             << "geometry "
                             << this
                             << std::endl;
                }
            }
        }
    }
    else
    {
        SWARNING << "Geometry(" << this << ")::handleAttGL: Illegal mode: "
                 << mode << " for id " << id << std::endl;
    }
#endif

    return 0;
}

void Geometry::handleAttDestroyGL(DrawEnv                 *pEnv, 
                                  UInt32                   id, 
                                  Window::GLObjectStatusE  mode)
{
#if !defined(OSG_OGL_COREONLY) || defined(OSG_CHECK_COREONLY)
    UInt32            glid;
    Window           *pWin      = pEnv->getWindow();

    if(mode == Window::destroy)
    {
        glid = pWin->getGLObjectId(id);

        glDeleteLists(glid, 1);
    }
    else if(mode == Window::finaldestroy)
    {
        //SWARNING << "Last geometry user destroyed" << std::endl;
    }
    else
    {
        SWARNING << "Geometry::handleAttDestroyGL: Illegal mode: "
                 << mode << " for id " << id << std::endl;
    }
#endif
}

UInt32 Geometry::handleVAOGL(DrawEnv                 *pEnv, 
                             UInt32                   id, 
                             Window::GLObjectStatusE  mode,
                             UInt64                   uiOptions)
{
    UInt32            glid;
    Window           *pWin      = pEnv->getWindow();
    GLHandlerOptions  glOptions = { uiOptions };

    if(!pWin->hasExtension(_arbVertexArrayObject))
    {
        SWARNING << "Geometry::handleVAOGL: Extension "
                 << "'GL_ARB_vertex_array_object' not supported by window "
                 << pWin << std::endl;
        return 0;
    }

    if(mode == Window::initialize || mode == Window::needrefresh ||
       mode == Window::reinitialize)
    {
        if(mode == Window::initialize)
        {
            OSGGETGLFUNCBYID_GL3_ES(glGenVertexArrays,
                                    osgGlGenVertexArrays,
                                    FuncIdGenVertexArrays,
                                    pWin);

            osgGlGenVertexArrays(1, &glid);

            pWin->setGLObjectId(id, glid);
        }
        else
        {
            glid = pWin->getGLObjectId(id);
        }

        GeoPumpGroup::PropertyCharacteristics prop = glOptions.uiOptions;

        GeoPumpGroup::SplitGeoPump pump = GeoPumpGroup::findSplitGeoPump(pEnv, 
                                                                         prop);
        if(pump.setupPump != NULL)
        {
            OSGGETGLFUNCBYID_GL3_ES(glBindVertexArray,
                                    osgGlBindVertexArray,
                                    FuncIdBindVertexArray,
                                    pWin);

            osgGlBindVertexArray(glid);

            bool rc = pump.setupPump(pEnv,
                                     getLengths(),      getTypes(),
                                     getMFProperties(), getMFPropIndices(),
                                     false                                );

            UInt32 uiObjInfo = rc ? ValidVAO : 0x00;
            
            uiObjInfo |= (prop & GeoPumpGroup::UsesShader);

            pWin->setGLObjectInfo(id, uiObjInfo);

            osgGlBindVertexArray(0);
        }
        else
        {
            SWARNING << "Geometry::handleVAOGL: no Pump found for geometry "
                     << this
                     << std::endl;
        }
    }
    else
    {
        SWARNING << "Geometry(" << this << ")::handleVAOGL: Illegal mode: "
                 << mode << " for id " << id << std::endl;
    }

    return 0;
}

void Geometry::handleVAODestroyGL(DrawEnv                 *pEnv, 
                                  UInt32                   id, 
                                  Window::GLObjectStatusE  mode)
{
    UInt32                   glid;
    Window                  *pWin = pEnv->getWindow();

    if(!pWin->hasExtension(_arbVertexArrayObject))
    {
        SWARNING << "Geometry::handleVAODestroyGL: Extension "
                 << "'GL_ARB_vertex_array_object' not supported by window "
                 << pWin
                 << std::endl;
        return;
    }

    if(mode == Window::destroy)
    {
        OSGGETGLFUNCBYID_GL3_ES(glDeleteVertexArrays,
                                osgGlDeleteVertexArrays,
                                FuncIdDeleteVertexArrays,
                                pWin);

        glid = pWin->getGLObjectId(id);

        osgGlDeleteVertexArrays(1, &glid);
    }
    else if(mode == Window::finaldestroy)
    {
        //SWARNING << "Last geometry user destroyed" << std::endl;
    }
    else
    {
        SWARNING << "Geometry::handleVAODestroyGL: Illegal mode: "
                 << mode << " for id " << id << std::endl;
    }
}

void Geometry::drawPrimitives(DrawEnv *pEnv)
{
    this->drawPrimitives(pEnv, 1);
}

void Geometry::drawPrimitives(DrawEnv *pEnv, UInt32 uiNumInstances)
{
    Window *pWin       = pEnv->getWindow();
    bool    usesShader = false;

    if(!pWin->hasExtOrVersion(_arbDrawInstanced, 0x0300, 0x0200))
    {
        uiNumInstances = 1;
    }

    // Quick solution must be cleaned up.
    if(_sfUseAttribCalls.getValue() == true)
    {
        usesShader = true;
    }
    else
    {
        if(pEnv->getActiveShader() != 0)
        {
            if((pEnv->getRequiredOGLFeature() & 
                HardwareContext::HasAttribAliasing) == 0x0000)
            {
                usesShader = true;
            }
            else
            {
                usesShader = (pEnv->getWindow()->getOGLFeatures() &
                              HardwareContext::HasAttribAliasing   ) != 0x0000;
            }
        }
    }

    GeoPumpGroup::PropertyCharacteristics prop;

    prop = GeoPumpGroup::characterizeGeometry(this);

    if(usesShader)
        prop |= GeoPumpGroup::UsesShader;

    GLHandlerOptions glOptions;

    glOptions.uiOptions      = prop;
    glOptions.uiNumInstances = uiNumInstances;

#if !defined(OSG_OGL_COREONLY) || defined(OSG_CHECK_COREONLY)
    // store glColor.
    Color4f color;

    if(getColors() != NULL)
        glGetFloatv(GL_CURRENT_COLOR, color.getValuesRGBA());
#endif

    if(_sfPatchVertices.getValue() != 0)
    {
        OSGGETGLFUNCBYID_GL3(glPatchParameteri,
                             osgGlPatchParameteri,
                             Geometry::FuncPatchParameterI,
                             pWin                         );

        osgGlPatchParameteri(GL_PATCH_VERTICES, _sfPatchVertices.getValue());
    }

    if(((prop & (GeoPumpGroup::SingleIndexed | 
                 GeoPumpGroup::NonIndexed    )) == 0x0000)) // ||
//       (prop &   GeoPumpGroup::AllVAOMask     ) != GeoPumpGroup::AllVAOMask)
    {
#if !defined(OSG_OGL_COREONLY) || defined(OSG_CHECK_COREONLY)
        if(getDlistCache() == true)
        {
            Int32 glid;

            if(usesShader)
            {
                glid = getAttGLId();
            }
            else
            {
                glid = getClassicGLId();
            }

            pWin->validateGLObject(glid, pEnv, glOptions.value);
            
            glCallList(pEnv->getWindow()->getGLObjectId(glid));
        }
        else
#endif
        {
            GeoPumpGroup::GeoPump pump = GeoPumpGroup::findGeoPump(pEnv, 
                                                                   prop);
            if(pump != NULL)
            {
                pump(pEnv,
                     getLengths(),      getTypes(),
                     getMFProperties(), getMFPropIndices(),
                     uiNumInstances                       );
            }
            else
            {
                SWARNING << "Geometry::drawPrimitives: no Pump found for "
                         << "geometry "
                         << this
                         << std::endl;
            }
        }
    }
    else if( _sfUseVAO.getValue() == false ||
            !pWin->hasExtension(_arbVertexArrayObject) ||
            (prop &   GeoPumpGroup::AllVAOMask) != GeoPumpGroup::AllVAOMask)
    {
#if (!defined(OSG_OGL_COREONLY) || defined(OSG_CHECK_COREONLY)) &&  \
    !defined(__APPLE__)
        if(getDlistCache() == true && uiNumInstances == 1)
        {
            Int32 glid;

            if(usesShader)
            {
                glid = getAttGLId();
            }
            else
            {
                glid = getClassicGLId();
            }
            
            GeoPumpGroup::SplitGeoPump pump = 
                GeoPumpGroup::findSplitGeoPump(pEnv,
                                               prop);

            if(pump.setupPump != NULL)
            {
                bool rc = pump.setupPump(pEnv,
                                         getLengths(),      
                                         getTypes(),
                                         getMFProperties(), 
                                         getMFPropIndices(),
                                         true              );
                
                if(rc == true)
                {
                    pWin->validateGLObject(glid, pEnv, glOptions.value);
                
                    glCallList(pEnv->getWindow()->getGLObjectId(glid));
                
                    pump.shutdownPump(pEnv,
                                      getLengths(),      
                                      getTypes(),
                                      getMFProperties(), 
                                      getMFPropIndices());
                }
                else // fallback 
                {
                    GeoPumpGroup::GeoPump pump = 
                        GeoPumpGroup::findGeoPump(pEnv, 
                                                  prop);
                    if(pump != NULL)
                    {
                        pump(pEnv,
                             getLengths(),      getTypes(),
                             getMFProperties(), getMFPropIndices(),
                             uiNumInstances                       );
                    }
                }
            }
        }
        else
#endif
        {
            GeoPumpGroup::GeoPump pump = GeoPumpGroup::findGeoPump(pEnv, 
                                                                   prop);
            if(pump != NULL)
            {
                pump(pEnv,
                     getLengths(),      getTypes(),
                     getMFProperties(), getMFPropIndices(),
                     uiNumInstances                       );
            }
            else
            {
                SWARNING << "Geometry::drawPrimitives: no Pump found for "
                         << "geometry "
                         << this
                         << std::endl;
            }
        }
    }
    else
    {
        Int32 vaoGlid = 
                (glOptions.value & 
                 GeoPumpGroup::UsesShader) ? getAttribVaoGLId () : 
                                             getClassicVaoGLId();
        
        pWin->validateGLObject(vaoGlid, pEnv, glOptions.value);
        
        UInt32 uiVAOInfo = pWin->getGLObjectInfo(vaoGlid);

#ifdef OSG_DEBUG
        if((prop      & GeoPumpGroup::UsesShader) != 
           (uiVAOInfo & GeoPumpGroup::UsesShader)   )
        {
            fprintf(stderr, "vao shader settings not equal : %04x | %04x\n",
                    (prop      & GeoPumpGroup::UsesShader),
                    (uiVAOInfo & GeoPumpGroup::UsesShader));
        }
#endif

        if((uiVAOInfo & ValidVAO) != 0)
        {
            GeoPumpGroup::SplitGeoPump pump = 
                GeoPumpGroup::findSplitGeoPump(pEnv,
                                               prop);

            if(pump.drawPump != NULL)
            {
                OSGGETGLFUNCBYID_GL3(glBindVertexArray,
                                     osgGlBindVertexArray,
                                     FuncIdBindVertexArray,
                                     pWin);

#if (!defined(OSG_OGL_COREONLY) || defined(OSG_CHECK_COREONLY)) && \
    !defined(__APPLE__)
                if(getDlistCache() == true && uiNumInstances == 1 &&
                   pWin->hasVAODListProblems() == false)
                {
                    Int32 glid;
                    
                    if(usesShader)
                    {
                        glid = getAttGLId();
                    }
                    else
                    {
                        glid = getClassicGLId();
                    }

                    pWin->validateGLObject(glid, pEnv, glOptions.value);

                    osgGlBindVertexArray(
                        pEnv->getWindow()->getGLObjectId(vaoGlid));

                    glCallList(pEnv->getWindow()->getGLObjectId(glid));

                    osgGlBindVertexArray(0);
                }
                else
#endif
                {
                    osgGlBindVertexArray(
                        pEnv->getWindow()->getGLObjectId(vaoGlid));

                    pump.drawPump(pEnv,
                                  getLengths(),      
                                  getTypes(),
                                  getMFProperties(), 
                                  getMFPropIndices(),
                                  uiNumInstances    );

                    osgGlBindVertexArray(0);
                }
            }
            else
            {
                SWARNING << "Geometry::drawPrimitives: no Pump found "
                         << "for geometry "
                         << this
                         << std::endl;
            }
        }
    }


#if !defined(OSG_OGL_COREONLY) || defined(OSG_CHECK_COREONLY)
    // restore glColor.
    if(getColors() != NULL)
        glColor4fv(color.getValuesRGBA());
#endif
}

/*! The IntersectAction callback for Geometry. It computes if the ray used in
    the IntersectAction \a action hits this object and if that is the case,
    which triangle is hit.

    \param[in] action IntersectAction performing the intersect test.
    \return Action result code, \see OSG::Action.

    \note This method is registered with the IntersectAction and automatically
    called from there, you probably never have to call it manually.
*/

Action::ResultE Geometry::intersectEnter(Action * action)
{
    IntersectAction      *ia = dynamic_cast<IntersectAction*>(action);
   
    ia->getActNode()->updateVolume();
    const BoxVolume      &bv = ia->getActNode()->getVolume();

    if(bv.isValid() && !bv.intersect(ia->getLine()))
    {
        return Action::Skip; //bv missed -> can not hit children
    }

    UInt32           numTris = 0;
    TriangleIterator it      = this->beginTriangles();
    TriangleIterator end     = this->endTriangles  ();
    Real32           t;
    Vec3f            norm;
    const Line      &ia_line = ia->getLine();

    for(; it != end; ++it)
    {
        ++numTris;

        if(ia_line.intersect(it.getPosition(0),
                             it.getPosition(1),
                             it.getPosition(2), t, &norm))
        {
            ia->setHit(t, ia->getActNode(), it.getIndex(), norm, -1);
        }
    }

    // If we need to test lines, iterate over lines and test for
    // lines that are within width distance from the line
    if(ia->getTestLines())
    {
        Real32 range_sq  = ia->getTestLineWidth();
        range_sq         = range_sq * range_sq;
        LineIterator it  = this->beginLines();
        LineIterator end = this->endLines  ();
        Pnt3f  pt1, pt2;
        OSG::Vec3f  norm;

        // Find closest points and if they are within the range, then add a hit
        for(; it != end; ++it)
        {
            Line cur_line(it.getPosition(0), it.getPosition(1));
            ia_line.getClosestPoints(cur_line, pt1, pt2);
            Real32 dist_sq( pt1.dist2(pt2) );

            if (dist_sq <= range_sq)
            {
                t = ia_line.getPosition().dist(pt1);
                ia->setHit(t, ia->getActNode(), -1, norm, it.getIndex());
            }
        }
    }

    ia->getStatCollector()->getElem(IntersectAction::statNTriangles)->add(numTris);

    return Action::Continue;
}

/*----------------------------- class specific ----------------------------*/
void Geometry::changed(ConstFieldMaskArg whichField, 
                       UInt32            origin,
                       BitVector         details)
{
#if !defined(OSG_OGL_COREONLY)
    // Handle change to the display list cache field.
    if(whichField & DlistCacheFieldMask)
    {
        if(getDlistCache())
        {
            // Ensure that we have OpenGL objects for display list.
            if(getClassicGLId() == 0)
            {
                setClassicGLId(               
                    Window::registerGLObject(
                        boost::bind(&Geometry::handleClassicGL, 
                                    GeometryMTUncountedPtr(this), 
                                    _1, _2, _3, _4),
                        &Geometry::handleClassicDestroyGL));
            }
            if(getAttGLId() == 0)
            {
                setAttGLId(               
                    Window::registerGLObject(
                        boost::bind(&Geometry::handleAttGL, 
                                    GeometryMTUncountedPtr(this), 
                                    _1, _2, _3, _4),
                        &Geometry::handleAttDestroyGL));
            }
        }
        else
        {
            // Delete old display list objects.
            if(getClassicGLId() != 0)
            {
                Window::destroyGLObject(getClassicGLId(), 1);

                setClassicGLId(0);
            }
            if(getAttGLId() != 0)
            {
                Window::destroyGLObject(getAttGLId(), 1);

                setAttGLId(0);
            }
        }
    }
#endif

    // If something changed inside the geometry fields and we are using
    // display lists, refresh them.
    if(whichField & (TypesFieldMask | LengthsFieldMask |
                     PropertiesFieldMask | PropIndicesFieldMask))
    {
        if(this->getDlistCache() == true)
        {
#if !defined(OSG_OGL_COREONLY)
            Window::refreshGLObject(getClassicGLId());
#endif
            Window::refreshGLObject(getAttGLId    ());
        }

        if(this->getUseVAO() == true)
        {
            Window::refreshGLObject(getClassicVaoGLId());
            Window::refreshGLObject(getAttribVaoGLId ());
        }
    }

    if(whichField & PropertiesFieldMask)
    {
        for(UInt32 i = 0; i < _mfParents.size(); i++)
        {
            _mfParents[i]->invalidateVolume();
        }

        _volumeCache.setValid();
        _volumeCache.setEmpty();
    }

    Inherited::changed(whichField, origin, details);
}

void Geometry::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump Geometry NI" << std::endl;
}

UInt32 Geometry::indexOccurrence(GeoIntegralProperty * const value) const
{
    UInt32 returnValue = 0;

    for(UInt32 i = 0; i < _mfPropIndices.size(); ++i)
    {
        if(_mfPropIndices[i] != NULL && _mfPropIndices[i] == value)
        {
            ++returnValue;
        }
    }

    return returnValue;
}

bool Geometry::isSingleIndex(void) const
{
    bool returnValue = true;

    for(UInt32 i = PositionsIndex; i < _mfPropIndices.size(); ++i)
    {
        if(_mfPropIndices[i] != NULL                           &&
           _mfPropIndices[i] != _mfPropIndices[PositionsIndex]   )
        {
            returnValue = false;
            break;
        }
    }

    return returnValue;
}

/*! Returns the indices properties of this geometry together with information
    for which properties they are used.
    Each element of the returned vector holds a pointer to an indices property
    and a vector indicating which properties are indexed by it.
*/
Geometry::IndexBag Geometry::getUniqueIndexBag(void) const
{
    typedef IndexBag::value_type IndexBagEntry;

    IndexBag returnValue;
    UInt32   i;

    // Find the first valid prop
    for(i = 0; i < _mfPropIndices.size(); ++i)
    {
        if(_mfPropIndices[i] != NULL)
        {
            break;
        }
    }

    if(i == _mfPropIndices.size())
        return returnValue;

    IndexBagEntry oEntry;

    oEntry.first = _mfPropIndices[i];
    oEntry.second.push_back(i);
    
    returnValue.push_back(oEntry);

    bool bFoundProp;

    for(UInt32 j = i + 1; j < _mfPropIndices.size(); ++j)
    {
        bFoundProp = false;

        for(UInt32 k = 0; k < returnValue.size() && bFoundProp == false; ++k)
        {
            if(_mfPropIndices[j] == returnValue[k].first)
            {
                returnValue[k].second.push_back(j);

                bFoundProp = true;
            }            
        }

        if(bFoundProp == false && _mfPropIndices[j] != NULL)
        {
            IndexBagEntry oEntry;

            oEntry.first = _mfPropIndices[j];
            oEntry.second.push_back(j);
            
            returnValue.push_back(oEntry);
        }
    }

    return returnValue;
}

void Geometry::fill(DrawableStatsAttachment *pStat)
{
    if(pStat == NULL)
    {
        FINFO(("Geometry::fill(DrawableStatsAttachment *): "
               "No attachment given.\n"));

        return;
    }

    // Att Bytes
    UInt32 storedAttBytes    = 0;
    UInt32 attBytesPerVertex = 0;

    for(UInt16 i = 0; i < Geometry::MaxAttribs; ++i)
    {
        if(this->getProperty(i) == NULL)
            continue;

        attBytesPerVertex += this->getProperty(i)->getFormatSize() *
                             this->getProperty(i)->getDimension();
        storedAttBytes    += this->getProperty(i)->getFormatSize() *
                             this->getProperty(i)->getDimension()  *
                             this->getProperty(i)->size32();
    }


    GeoIntegralProperty *geoTypePtr = this->getTypes();
    GeoIntegralProperty *lensPtr    = this->getLengths();

    UInt32 lN, tN, len, type;

    lN = (lensPtr    == NULL) ? 0 : lensPtr   ->size32();
    tN = (geoTypePtr == NULL) ? 0 : geoTypePtr->size32();

    if((tN == 0) || (lN != 0 && tN != lN) || (lN == 0 && tN != 1))
    {
        FINFO(("GeoStatsAttachment::calc: "
               "Lengths and Types information mismatch.\n"));
        return;
    }

    UInt32 triangle = 0, line = 0, point = 0, vertices = 0, patches = 0,
           procAttBytes = 0;

    for(UInt32 i = 0; i < tN; ++i)
    {
        geoTypePtr->getValue(type, i);

        if(lN != 0)
        {
            lensPtr->getValue(len, i);
        }
        else
        {
            GeoVectorProperty *pos = this->getPositions();

            if(pos == NULL)
            {
                FINFO(("GeoStatsAttachment::calc: No Positions!\n"));
                return;
            }

            len = pos->size32();
        }

        vertices     += len;
        procAttBytes += len * attBytesPerVertex;

        switch(type)
        {
            case GL_POINTS:
                point += len;
                break;
            case GL_LINES:
                line += len / 2;
                break;
            case GL_LINE_LOOP:
                line += len;
                break;
            case GL_LINE_STRIP:
                line += len - 1;
                break;
            case GL_TRIANGLES:
                triangle += len / 3;
                break;
            case GL_TRIANGLE_STRIP:
                triangle += len - 2;
                break;
            case GL_TRIANGLE_FAN:
                triangle += len - 2;
                break;
            case GL_QUADS:
                triangle += len / 2;
                break;
            case GL_QUAD_STRIP:
                triangle += len - 2;
                break;
            case GL_POLYGON:
                triangle += len - 2;
                break;
            case GL_PATCHES:
                patches += 1;
                break;
            case GL_LINES_ADJACENCY_EXT:
                line += len / 4;
                break;
            case GL_LINE_STRIP_ADJACENCY_EXT:
                line += len - 3;
                break;
            case GL_TRIANGLES_ADJACENCY_EXT:
                triangle += len / 6;
                break;
            case GL_TRIANGLE_STRIP_ADJACENCY_EXT:
                triangle += len / 2 - 2;
                break;
            default:
                FWARNING(("GeoStatsAttachment::calc: Invalid geoType: %d\n",
                          type));
                break;
        }
    }

    pStat->setVertices(vertices);
    pStat->setPoints(point);
    pStat->setLines(line);
    pStat->setTriangles(triangle);
    pStat->setPatches(patches);
    pStat->setStoredAttributeBytes(storedAttBytes);
    pStat->setProcessedAttributeBytes(procAttBytes);
    pStat->setValid(true);
}

// Iterators


/*-------------------------- Primitive Iterator --------------------------------*/

/*! Return a PrimitiveIterator poiting to the beginning of the Geometry.
*/
PrimitiveIterator Geometry::beginPrimitives(void) const
{
    PrimitiveIterator it(this);

    it.setToBegin();

    return it;
}

/*! Return a PrimitiveIterator poiting to the end of the Geometry.
*/
PrimitiveIterator Geometry::endPrimitives(void) const
{
    PrimitiveIterator it(this);

    it.setToEnd();

    return it;
}

/*! Return a TriangleIterator poiting to the beginning of the Geometry.
*/
TriangleIterator Geometry::beginTriangles(void) const
{
    TriangleIterator it(this);

    it.setToBegin();

    return it;
}

/*! Return a TriangleIterator poiting to the end of the Geometry.
*/
TriangleIterator Geometry::endTriangles(void) const
{
    TriangleIterator it(this);

    it.setToEnd();

    return it;
}

/*! Return a FaceIterator poiting to the beginning of the Geometry.
*/
FaceIterator Geometry::beginFaces(void) const
{
    FaceIterator it(this);

    it.setToBegin();

    return it;
}

/*! Return a FaceIterator poiting to the end of the Geometry.
*/
FaceIterator Geometry::endFaces(void) const
{
    FaceIterator it(this);

    it.setToEnd();

    return it;
}

/*! Return a LineIterator poiting to the beginning of the Geometry.
*/
LineIterator Geometry::beginLines(void) const
{
    LineIterator it(this);

    it.setToBegin();

    return it;
}

/*! Return a LineIterator poiting to the end of the Geometry.
*/
LineIterator Geometry::endLines(void) const
{
    LineIterator it(this);

    it.setToEnd();

    return it;
}

/*! Return a EdgeIterator poiting to the beginning of the Geometry.
*/
EdgeIterator Geometry::beginEdges(void) const
{
    EdgeIterator it(this);

    it.setToBegin();

    return it;
}

/*! Return a EdgeIterator pointing to the end of the Geometry.
*/
EdgeIterator Geometry::endEdges(void) const
{
    EdgeIterator it(this);

    it.setToEnd();

    return it;
}

/*! Return a PointIterator pointing to the beginning of the Geometry.
*/
PointIterator Geometry::beginPoints(void) const
{
    PointIterator it(this);

    it.setToBegin();

    return it;
}

/*! Return a PointIterator pointing to the end of the Geometry.
*/
PointIterator Geometry::endPoints(void) const
{
    PointIterator it(this);

    it.setToEnd();

    return it;
}

OSG_END_NAMESPACE
