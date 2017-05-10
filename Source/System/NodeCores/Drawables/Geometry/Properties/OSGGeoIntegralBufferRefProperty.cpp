/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
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

#include "OSGGeoIntegralBufferRefProperty.h"

#include "OSGGLFuncProtos.h"

#include "OSGConceptPropertyChecks.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGGeoIntegralBufferRefPropertyBase.cpp file.
// To modify it, please change the .fcd file
// (OSGGeoIntegralBufferRefProperty.fcd) and regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void GeoIntegralBufferRefProperty::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

GeoIntegralBufferRefProperty::GeoIntegralBufferRefProperty(void) :
    Inherited()
{
}

GeoIntegralBufferRefProperty::GeoIntegralBufferRefProperty(
    const GeoIntegralBufferRefProperty &source) :

    Inherited(source)
{
}

GeoIntegralBufferRefProperty::~GeoIntegralBufferRefProperty(void)
{
}

/*----------------------------- class specific ----------------------------*/

void GeoIntegralBufferRefProperty::changed(ConstFieldMaskArg whichField, 
                                           UInt32            origin,
                                           BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void GeoIntegralBufferRefProperty::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump GeoIntegralBufferRefProperty NI" << std::endl;
}

/*------------------------------ tools --------------------------------------*/

void GeoIntegralBufferRefProperty::validate(DrawEnv *pEnv)
{
    pEnv->getWindow()->validateGLObject(this->getGLId(),
                                        pEnv           );
}

Int32 GeoIntegralBufferRefProperty::getOpenGLId(DrawEnv *pEnv)
{
    return pEnv->getWindow()->getGLObjectId(this->getGLId());
}

void GeoIntegralBufferRefProperty::activate(DrawEnv *pEnv, UInt32 slot)
{
    Window *pWin = pEnv->getWindow();

    if(!pWin->hasExtOrVersion(_extVertexBufferObject, 0x0105, 0x0200))
        return;

    if(getGLId() != 0 && getUseVBO()) // Do we have a VBO?
    {
        validate(pEnv);

        GLuint id = pWin->getGLObjectId(getGLId());

        OSGGETGLFUNCBYID_GL3_ES( glBindBuffer, 
                                 osgGlBindBuffer,
                                _funcBindBuffer, 
                                 pWin);

        osgGlBindBuffer(GL_ELEMENT_ARRAY_BUFFER_ARB, id);
    }
}

void GeoIntegralBufferRefProperty::changeFrom(DrawEnv    *pEnv, 
                                              StateChunk *old, 
                                              UInt32      slot)
{
    // change from me to me?
    // this assumes I haven't changed in the meantime.
    if(old == this)
        return;

    Window *pWin = pEnv->getWindow();

    GeoIntegralProperty *o = dynamic_cast<GeoIntegralProperty*>(old);
    
    if(!pWin->hasExtOrVersion(_extVertexBufferObject, 0x0105, 0x0200))
        return;

    OSGGETGLFUNCBYID_GL3_ES( glBindBuffer, 
                             osgGlBindBuffer,
                            _funcBindBuffer, 
                             pWin);

    if(getGLId() != 0 && getUseVBO()) // Do we have a VBO?
    {
        validate(pEnv);

        GLuint id = pWin->getGLObjectId(getGLId());

        osgGlBindBuffer(GL_ELEMENT_ARRAY_BUFFER_ARB, id);
    }
    else if(o != NULL && o->getGLId() != 0 && o->getUseVBO())
    {
        osgGlBindBuffer(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);            
    }
}

void *GeoIntegralBufferRefProperty::mapBuffer(GLenum eAccess, DrawEnv *pEnv)
{
    void *returnValue = NULL;

    if((getUseVBO() == true) && (getGLId() != 0))
    {
        Window *pWin = pEnv->getWindow();

        validate(pEnv);

        GLuint id = pWin->getGLObjectId(getGLId());

        osgSinkUnusedWarning(pWin);

        OSGGETGLFUNCBYID_GL3_ES( glBindBuffer, 
                                 osgGlBindBuffer,
                                _funcBindBuffer, 
                                 pWin);

        OSGGETGLFUNCBYID_GL3   ( glMapBuffer, 
                                 osgGlMapBuffer,
                                _funcMapBuffer, 
                                 pWin);
      
        osgGlBindBuffer(GL_ELEMENT_ARRAY_BUFFER_ARB, id);

        returnValue = osgGlMapBuffer(GL_ELEMENT_ARRAY_BUFFER_ARB, eAccess);

        osgGlBindBuffer(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);
    }

    return returnValue;
}

bool GeoIntegralBufferRefProperty::unmapBuffer(DrawEnv *pEnv)
{
    bool returnValue = true;

    if((getUseVBO() == true) && (getGLId() != 0))
    {
        Window *pWin = pEnv->getWindow();

        validate(pEnv);

        GLuint id = pWin->getGLObjectId(getGLId());

        osgSinkUnusedWarning(pWin);

        OSGGETGLFUNCBYID_GL3_ES( glBindBuffer, 
                                 osgGlBindBuffer,
                                _funcBindBuffer, 
                                 pWin);

        OSGGETGLFUNCBYID_GL3   ( glUnmapBuffer, 
                                 osgGlUnmapBuffer,
                                _funcUnmapBuffer, 
                                 pWin);

        osgGlBindBuffer(GL_ELEMENT_ARRAY_BUFFER_ARB, id);

        returnValue = osgGlUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER_ARB) != 0;

        osgGlBindBuffer(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);
    }
    
    return returnValue;
}

void GeoIntegralBufferRefProperty::onCreate(
    const GeoIntegralBufferRefProperty *p)
{
    GeoIntegralProperty::onCreate(p);
}

void GeoIntegralBufferRefProperty::onDestroy(UInt32 uiContainerId)
{
    GeoIntegralProperty::onDestroy(uiContainerId);
}

OSG_END_NAMESPACE
