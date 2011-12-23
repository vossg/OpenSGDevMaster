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
#include "OSGGeoVectorProperty.h"
#include "OSGDrawEnv.h"

#include "OSGGLFuncProtos.h"

#include "OSGConceptPropertyChecks.h"

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGGeoVectorPropertyBase.cpp file.
// To modify it, please change the .fcd file (OSGGeoVectorProperty.fcd) and
// regenerate the base file.

/*! \fn bool GeoVectorProperty::getNormalize(void)
    Returns if this property stores normalized vector data.
 */

/*! \fn void GeoVectorProperty::clear(void)
    Removes all values from this property.
 */

/*! \fn void GeoVectorProperty::resize(size_t newsize)
    Changes the size of this property to \a newsize. If the new size is smaller
    than the current size, excessive elements are deleted; if the new is greater
    than the current size, new elements are default constructed.

    \param[in] newsize New size for this property.
 */

/*! \fn UInt32 GeoIntegralProperty::size(void) const
    \copydoc OSG::GeoProperty::size
 */

/*! \fn void GeoVectorProperty::getGenericValue(MaxTypeT &val, const UInt32 index)
    Retrieves this properties value at index \a index in \a val through the
    most generic type available (MaxTypeT).
    The templated access functions will use this internally and then convert to
    the user specified type, thus the concrete properties derived from this
    need to override this method.

    \param[out] val The value stored at index \a index.
    \param[in] index The index of the value to retrieve.
 */

/*! \fn void GeoVectorProperty::setGenericValue(const MaxTypeT &val, const UInt32 index)
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

// extension indices for used extensions;
UInt32 GeoVectorProperty::_extSecondaryColor;
UInt32 GeoVectorProperty::_extMultitexture;

// extension indices for used fucntions;
UInt32 GeoVectorProperty::_funcglSecondaryColorPointer;
UInt32 GeoVectorProperty::_funcglClientActiveTextureARB;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void GeoVectorProperty::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        _extSecondaryColor      =
            Window::registerExtension("GL_EXT_secondary_color");
        
        _funcglSecondaryColorPointer  = Window::registerFunction(
            OSG_DLSYM_UNDERSCORE"glSecondaryColorPointerEXT",
            _extSecondaryColor);
        
        _extMultitexture        =
            Window::registerExtension("GL_ARB_multitexture");

        _funcglClientActiveTextureARB = Window::registerFunction(
            OSG_DLSYM_UNDERSCORE"glClientActiveTextureARB",
            _extMultitexture);
    }
}

/*------------------------- Chunk Class Access ---------------------------*/

const StateChunkClass *GeoVectorProperty::getClass(void) const
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

GeoVectorProperty::GeoVectorProperty(void) :
    Inherited()
{
 }

GeoVectorProperty::GeoVectorProperty(const GeoVectorProperty &source) :
    Inherited(source)
{
}

GeoVectorProperty::~GeoVectorProperty(void)
{
}

/*! State Chunk handling */

GLenum GeoVectorProperty::getBufferType(void)
{
    return GL_ARRAY_BUFFER_ARB;
}

void GeoVectorProperty::activate(DrawEnv *pEnv, UInt32 slot)
{
    Window *pWin = pEnv->getWindow();

    bool isGeneric = (slot >= 16);  // !!!HACK. needs to be replaced for 2.0
    slot &= 15;

    bool hasVBO = pWin->hasExtOrVersion(_extVertexBufferObject, 0x0105, 0x0200);

    osgSinkUnusedWarning(pWin);

    if(hasVBO && isGeneric == true)
    {
        OSGGETGLFUNCBYID_GL3_ES( glVertexAttribPointer, 
                                 osgGlVertexAttribPointer,
                                _funcglVertexAttribPointerARB,
                                 pWin);

        if(getGLId() != 0 && getUseVBO()) // Do we have a VBO?
        {
            pWin->validateGLObject(getGLId(), pEnv);
            
            OSGGETGLFUNCBYID_GL3_ES(  glBindBuffer, 
                                      osgGlBindBuffer,
                                     _funcBindBuffer, 
                                      pWin);
            
            osgGlBindBuffer(GL_ARRAY_BUFFER_ARB,
                            pWin->getGLObjectId(getGLId()));
            
            osgGlVertexAttribPointer(slot, 
                                     getDimension(),
                                     getFormat   (),
                                     getNormalize(),
                                     getStride   (), 
                                     0);
            
            osgGlBindBuffer(GL_ARRAY_BUFFER_ARB, 0);
        }
        else
        {
            osgGlVertexAttribPointer(slot, 
                                     getDimension(),
                                     getFormat   (), 
                                     getNormalize(),
                                     getStride   (), 
                                     getData     ());
        }
        
        OSGGETGLFUNCBYID_GL3_ES( glEnableVertexAttribArray,
                                 osgGlEnableVertexAttribArray,
                                _funcglEnableVertexAttribArrayARB,
                                 pWin);
        
        osgGlEnableVertexAttribArray(slot);
    }
    else 
    {        
#if !defined(OSG_OGL_COREONLY) || defined(OSG_CHECK_COREONLY)
        const void *pData = NULL;

        OSGGETGLFUNCBYID_GL3_ES( glBindBuffer, 
                                 osgGlBindBuffer,
                                _funcBindBuffer, 
                                 pWin);

        hasVBO &= getUseVBO() && (getGLId() != 0);

        if(hasVBO == true) // Do we have a VBO?
        {
            pWin->validateGLObject(getGLId(), pEnv);                

            osgGlBindBuffer(GL_ARRAY_BUFFER_ARB,
                            pWin->getGLObjectId(getGLId()));
        }
        else
        {
            pData = getData();
        }
        
        switch(slot)
        {
            case 0:     
                glVertexPointer(getDimension(), 
                                getFormat   (),
                                getStride   (),
                                pData         );

                glEnableClientState(GL_VERTEX_ARRAY);
                break;

            case 2:     
                glNormalPointer(getFormat(),
                                getStride(),
                                pData      );

                glEnableClientState(GL_NORMAL_ARRAY);
                break;

            case 3:   
                glColorPointer(getDimension(), 
                               getFormat   (),
                               getStride   (), 
                               pData         );

                glEnableClientState(GL_COLOR_ARRAY);
                break;

            case 4:   
                if(pWin->hasExtOrVersion(_extSecondaryColor, 0x0104))
                {
                    OSGGETGLFUNCBYID_GL3( glSecondaryColorPointer,
                                          osgGlSecondaryColorPointer,
                                         _funcglSecondaryColorPointer,
                                          pWin);

                    osgGlSecondaryColorPointer(getDimension(),
                                               getFormat   (),
                                               getStride   (), 
                                               pData         );

                    glEnableClientState(GL_SECONDARY_COLOR_ARRAY_EXT);
                }
                else
                {
                    FWARNING(("GeoVectorProperty::activate: Window "
                              "has no Secondary Color extension\n"));
                }
                break;

            case 8:  
            case 9:
            case 10: 
            case 11:
            case 12: 
            case 13:
            case 14: 
            case 15:
            {
                if(pWin->hasExtOrVersion(_extMultitexture, 0x0103, 0x0200))
                {
                    OSGGETGLFUNCBYID_GL3_ES( glClientActiveTexture,
                                             osgGlClientActiveTexture,
                                            _funcglClientActiveTextureARB,
                                             pWin);

                    osgGlClientActiveTexture(GL_TEXTURE0_ARB + slot - 8);

                    glTexCoordPointer(getDimension(),
                                      getFormat   (),
                                      getStride   (),
                                      pData         );

                    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
                }
                else if(slot == 8)
                {
                    glTexCoordPointer(getDimension(),
                                      getFormat   (),
                                      getStride   (),
                                      pData         );

                    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
                }
                else
                {
                    SWARNING << "GeoVectorProperty::activate: Window "
                             << "has no Multi Texture extension" << std::endl;
                }
            }
            break;

            default:    FWARNING(("GeoVectorProperty::activate: Non-Generic"
                                  " attribute nr. %d unknown!\n", slot));
                break;

        }
        if(hasVBO == true) // Do we have a VBO?
        {
            osgGlBindBuffer(GL_ARRAY_BUFFER_ARB, 0);
        }
#endif
    }
}

void GeoVectorProperty::changeFrom(DrawEnv    *pEnv,
                                   StateChunk *old,
                                   UInt32      slot)
{
    // change from me to me?
    // this assumes I haven't changed in the meantime.
    if(old == this)
        return;

    // The activation will overwrite the previous activation fully,
    // so no need to deactivate

    activate(pEnv, slot);
}

void GeoVectorProperty::deactivate(DrawEnv *pEnv, UInt32 slot)
{
    Window *pWin   = pEnv->getWindow();

    bool isGeneric = (slot >= 16);  // !!!HACK. needs to be replaced for 2.0

    slot &= 15;

    osgSinkUnusedWarning(pWin);

    if(pWin->hasExtOrVersion(_extVertexBufferObject, 
                             0x0105, 
                             0x0200                ) && isGeneric)
    {
        OSGGETGLFUNCBYID_GL3_ES( glDisableVertexAttribArray,
                                 osgGlDisableVertexAttribArray,
                                _funcglDisableVertexAttribArrayARB,
                                 pWin);

        osgGlDisableVertexAttribArray(slot);
    }
    else
    {
#if !defined(OSG_OGL_COREONLY) || defined(OSG_CHECK_COREONLY)
        switch(slot)
        {
            case 0:
                glDisableClientState(GL_VERTEX_ARRAY);
                break;

            case 2: 
                glDisableClientState(GL_NORMAL_ARRAY);
                break;

            case 3: 
                glDisableClientState(GL_COLOR_ARRAY);
                break;

            case 4: 
                glDisableClientState(GL_SECONDARY_COLOR_ARRAY_EXT);
                break;

            case 8:  
            case 9:
            case 10: 
            case 11:
            case 12: 
            case 13:
            case 14: 
            case 15:
            {
                if(pWin->hasExtOrVersion(_extMultitexture, 0x0103, 0x0200))
                {
                    OSGGETGLFUNCBYID_GL3_ES( glClientActiveTexture,
                                             osgGlClientActiveTexture,
                                            _funcglClientActiveTextureARB,
                                             pWin);
                
                    osgGlClientActiveTexture(GL_TEXTURE0_ARB + slot - 8);

                    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
                }
                else if(slot == 8)
                {
                    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
                }
                else
                {
                    SWARNING << "GeoVectorProperty::deactivate: Window "
                             << "has no Multi Texture extension" << std::endl;
                }
            }
            break;

            default:    
                FWARNING(("GeoVectorProperty::deactivate: Non-Generic"
                          " attribute nr. %d unknown!\n", slot));
                break;
        }
#endif
    }
}


void *GeoVectorProperty::mapBuffer(GLenum eAccess, DrawEnv *pEnv)
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
        
        osgGlBindBuffer(GL_ARRAY_BUFFER_ARB,
                        pWin->getGLObjectId(getGLId()));

        returnValue = osgGlMapBuffer(GL_ARRAY_BUFFER_ARB, eAccess);

        osgGlBindBuffer(GL_ARRAY_BUFFER_ARB, 0);
    }

    return returnValue;
}

bool GeoVectorProperty::unmapBuffer(DrawEnv *pEnv)
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

        osgGlBindBuffer(GL_ARRAY_BUFFER_ARB,
                        pWin->getGLObjectId(getGLId()));

        returnValue = (osgGlUnmapBuffer(GL_ARRAY_BUFFER_ARB) != 0);

        osgGlBindBuffer(GL_ARRAY_BUFFER_ARB, 0);
    }
    
    return returnValue;
}


/*----------------------------- class specific ----------------------------*/

void GeoVectorProperty::changed(ConstFieldMaskArg whichField, 
                                UInt32            origin,
                                BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void GeoVectorProperty::dump(      UInt32    ,
                             const BitVector ) const
{
    SLOG << "Dump GeoVectorProperty NI" << std::endl;
}
