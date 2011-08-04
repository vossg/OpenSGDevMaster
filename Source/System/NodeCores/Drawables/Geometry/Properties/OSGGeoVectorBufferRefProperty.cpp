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

#include "OSGGeoVectorBufferRefProperty.h"

#include "OSGGLFuncProtos.h"

#include "OSGConceptPropertyChecks.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGGeoVectorBufferRefPropertyBase.cpp file.
// To modify it, please change the .fcd file
// (OSGGeoVectorBufferRefProperty.fcd) and regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void GeoVectorBufferRefProperty::initMethod(InitPhase ePhase)
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

GeoVectorBufferRefProperty::GeoVectorBufferRefProperty(void) :
    Inherited()
{
}

GeoVectorBufferRefProperty::GeoVectorBufferRefProperty(
    const GeoVectorBufferRefProperty &source) :

    Inherited(source)
{
}

GeoVectorBufferRefProperty::~GeoVectorBufferRefProperty(void)
{
}

/*----------------------------- class specific ----------------------------*/

void GeoVectorBufferRefProperty::changed(ConstFieldMaskArg whichField, 
                                         UInt32            origin,
                                         BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void GeoVectorBufferRefProperty::dump(      UInt32    ,
                                      const BitVector ) const
{
    SLOG << "Dump GeoVectorBufferRefProperty NI" << std::endl;
}

void GeoVectorBufferRefProperty::activate(DrawEnv *pEnv, UInt32 slot)
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
            OSGGETGLFUNCBYID_GL3_ES( glBindBuffer, 
                                     osgGlBindBuffer,
                                    _funcBindBuffer, 
                                     pWin);
            
            osgGlBindBuffer(GL_ARRAY_BUFFER_ARB,
                            getGLId());
            
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
            osgGlBindBuffer(GL_ARRAY_BUFFER_ARB,
                            getGLId());
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
                if (pWin->hasExtOrVersion(_extSecondaryColor, 0x0104))
                {
                    OSGGETGLFUNCBYID_EXT( glSecondaryColorPointer,
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

void *GeoVectorBufferRefProperty::mapBuffer(GLenum eAccess, DrawEnv *pEnv)
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
       
        osgGlBindBuffer(GL_ARRAY_BUFFER_ARB,
                        getGLId());

        returnValue = osgGlMapBuffer(GL_ARRAY_BUFFER_ARB, eAccess);

        osgGlBindBuffer(GL_ARRAY_BUFFER_ARB, 0);
    }

    return returnValue;
}

bool GeoVectorBufferRefProperty::unmapBuffer(DrawEnv *pEnv)
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
                        getGLId());

        returnValue = osgGlUnmapBuffer(GL_ARRAY_BUFFER_ARB);

        osgGlBindBuffer(GL_ARRAY_BUFFER_ARB, 0);
    }
    
    return returnValue;
}


void GeoVectorBufferRefProperty::onCreate(const GeoVectorBufferRefProperty *p)
{
    GeoVectorProperty::onCreate(p);
}

void GeoVectorBufferRefProperty::onDestroy(UInt32 uiContainerId)
{
    GeoVectorProperty::onDestroy(uiContainerId);
}

OSG_END_NAMESPACE
