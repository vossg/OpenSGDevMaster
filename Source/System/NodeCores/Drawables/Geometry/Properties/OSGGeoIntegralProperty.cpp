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

#include "OSGConfig.h"

#include "OSGGLEXT.h"
#include "OSGWindow.h"
#include "OSGGeoIntegralProperty.h"
#include "OSGDrawEnv.h"

#include "OSGGLFuncProtos.h"

#include "OSGConceptPropertyChecks.h"

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGGeoIntegralPropertyBase.cpp file.
// To modify it, please change the .fcd file (OSGGeoIntegralProperty.fcd) and
// regenerate the base file.

/*! \fn void GeoIntegralProperty::clear(void)
    Removes all values from this property.
 */

/*! \fn void GeoIntegralProperty::resize(size_t newsize)
    Changes the size of this property to \a newsize. If the new size is smaller
    than the current size, excessive elements are deleted; if the new is greater
    than the current size, new elements are default constructed.

    \param[in] newsize New size for this property.
 */

/*! \fn UInt32 GeoIntegralProperty::size(void) const
    \copydoc OSG::GeoProperty::size
 */

/*! \fn void GeoIntegralProperty::getGenericValue(MaxTypeT &val, const UInt32 index)
    Retrieves this properties value at index \a index in \a val through the
    most generic type available (MaxTypeT).
    The templated access functions will use this internally and then convert to
    the user specified type, thus the concrete properties derived from this
    need to override this method.

    \param[out] val The value stored at index \a index.
    \param[in] index The index of the value to retrieve.
 */

/*! \fn void GeoIntegralProperty::setGenericValue(const MaxTypeT &val, const UInt32 index)
    Stores the value \a val in this property at index \a index using the most
    generic type available (MaxTypeT).
    The templated access functions will use this internally and then convert to
    the user specified type, thus the concrete properties derived from this
    need to override this method.

    \param[in] val The value to store at index \a index.
    \param[in] index The index of the value to set.
 */

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

StateChunkClass GeoIntegralProperty::_class("GeoIntegralProperty", 1);

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void GeoIntegralProperty::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);
}

/*------------------------- Chunk Class Access ---------------------------*/

const StateChunkClass *GeoIntegralProperty::getClass(void) const
{
    return GeoProperty::getClass();
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

GeoIntegralProperty::GeoIntegralProperty(void) :
    Inherited()
{
}

GeoIntegralProperty::GeoIntegralProperty(const GeoIntegralProperty &source) :
    Inherited(source)
{
    // for some reason using VBo for elemnts doesn't work right now, disable it
    _sfUseVBO.setValue(false);
}

GeoIntegralProperty::~GeoIntegralProperty(void)
{
}


/*! State Chunk handling */

GLenum GeoIntegralProperty::getBufferType(void)
{
    return GL_ELEMENT_ARRAY_BUFFER_ARB;
}

void GeoIntegralProperty::activate(DrawEnv *pEnv, UInt32 slot)
{
    Window *pWin = pEnv->getWindow();
    
    if(!pWin->hasExtOrVersion(_extVertexBufferObject, 0x0105, 0x0200))
        return;

    osgSinkUnusedWarning(pWin);

    if(getGLId() != 0 && getUseVBO()) // Do we have a VBO?
    {
        pWin->validateGLObject(getGLId(), pEnv);

        OSGGETGLFUNCBYID_GL3_ES( glBindBuffer, 
                                 osgGlBindBuffer,
                                _funcBindBuffer, 
                                 pWin);

        osgGlBindBuffer(GL_ELEMENT_ARRAY_BUFFER_ARB, 
                        pWin->getGLObjectId(getGLId()));
    }
}

void GeoIntegralProperty::changeFrom(DrawEnv    *pEnv, 
                                     StateChunk *old, 
                                     UInt32      slot)
{
    // change from me to me?
    // this assumes I haven't changed in the meantime.
    if(old == this)
        return;

    Window              *pWin = pEnv->getWindow();
    GeoIntegralProperty *o    = dynamic_cast<GeoIntegralProperty*>(old);
    
    osgSinkUnusedWarning(pWin);

    if(!pWin->hasExtOrVersion(_extVertexBufferObject, 0x0105, 0x0200))
        return;

    OSGGETGLFUNCBYID_GL3_ES( glBindBuffer, 
                             osgGlBindBuffer,
                            _funcBindBuffer, 
                             pWin);

    if(getGLId() != 0 && getUseVBO()) // Do we have a VBO?
    {
        pWin->validateGLObject(getGLId(), pEnv);

        osgGlBindBuffer(GL_ELEMENT_ARRAY_BUFFER_ARB, 
                        pWin->getGLObjectId(getGLId()));
    }
    else if(o != NULL && o->getGLId() != 0 && o->getUseVBO())
    {
        osgGlBindBuffer(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);            
    }
}

void GeoIntegralProperty::deactivate(DrawEnv *pEnv, UInt32 slot)
{
    Window *pWin = pEnv->getWindow();

    osgSinkUnusedWarning(pWin);
     
    if(!pWin->hasExtOrVersion(_extVertexBufferObject, 0x0105, 0x0200))
        return;
   
    if(getGLId() != 0 && getUseVBO()) // Do we have a VBO?
    {
        OSGGETGLFUNCBYID_GL3_ES( glBindBuffer, 
                                 osgGlBindBuffer,
                                _funcBindBuffer, 
                                 pWin);

        osgGlBindBuffer(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);
    }
}

bool GeoIntegralProperty::isInVBO(DrawEnv *pEnv)
{
//    Window *win = pEnv->getWindow();
    
    if(getGLId() != 0 && getUseVBO()) // Do we have a VBO?
    {
        return true;
    }
    
    return false;    
}

void *GeoIntegralProperty::mapBuffer(GLenum eAccess, DrawEnv *pEnv)
{
    void *returnValue = NULL;

    if((getUseVBO() == true) && (getGLId() != 0))
    {
        Window *pWin = pEnv->getWindow();

        osgSinkUnusedWarning(pWin);

        OSGGETGLFUNCBYID_GL3_ES( glBindBuffer, 
                                 osgGlBindBuffer,
                                _funcBindBuffer, 
                                 pWin);

        OSGGETGLFUNCBYID_GL3   ( glMapBuffer, 
                                 osgGlMapBuffer,
                                _funcMapBuffer, 
                                 pWin);

        pWin->validateGLObject(getGLId(), pEnv);                
        
        osgGlBindBuffer(GL_ELEMENT_ARRAY_BUFFER_ARB,
                        pWin->getGLObjectId(getGLId()));

        returnValue = osgGlMapBuffer(GL_ELEMENT_ARRAY_BUFFER_ARB, eAccess);

        osgGlBindBuffer(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);
    }

    return returnValue;
}

bool GeoIntegralProperty::unmapBuffer(DrawEnv *pEnv)
{
    bool returnValue = true;

    if((getUseVBO() == true) && (getGLId() != 0))
    {
        Window *pWin = pEnv->getWindow();

        osgSinkUnusedWarning(pWin);

        OSGGETGLFUNCBYID_GL3_ES( glBindBuffer, 
                                 osgGlBindBuffer,
                                _funcBindBuffer, 
                                 pWin);

        OSGGETGLFUNCBYID_GL3   ( glUnmapBuffer, 
                                 osgGlUnmapBuffer,
                                _funcUnmapBuffer, 
                                 pWin);

        osgGlBindBuffer(GL_ELEMENT_ARRAY_BUFFER_ARB,
                        pWin->getGLObjectId(getGLId()));

        returnValue = osgGlUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER_ARB);

        osgGlBindBuffer(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);
    }
    
    return returnValue;
}


/*----------------------------- class specific ----------------------------*/

void GeoIntegralProperty::changed(ConstFieldMaskArg whichField, 
                                  UInt32            origin,
                                  BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void GeoIntegralProperty::dump(      UInt32    i, 
                               const BitVector v) const
{
    Inherited::dump(i,v);
}

