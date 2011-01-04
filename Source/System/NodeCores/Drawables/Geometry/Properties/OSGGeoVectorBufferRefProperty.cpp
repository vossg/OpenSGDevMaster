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
    Window *win = pEnv->getWindow();

    bool isGeneric = (slot >= 16);  // !!!HACK. needs to be replaced for 2.0
    slot &= 15;

    bool hasVBO = win->hasExtension(_extVertexBufferObject);

    if(hasVBO && isGeneric == true)
    {
        OSGGETGLFUNCBYID( OSGglVertexAttribPointerARB, 
                          osgGlVertexAttribPointerARB,
                         _funcglVertexAttribPointerARB,
                          win);

        if(getGLId() != 0 && getUseVBO()) // Do we have a VBO?
        {
            OSGGETGLFUNCBYID( OSGglBindBufferARB, 
                              osgGlBindBufferARB,
                             _funcBindBuffer, 
                              win);
            
            osgGlBindBufferARB(GL_ARRAY_BUFFER_ARB,
                               getGLId());
            
            osgGlVertexAttribPointerARB(slot, 
                                        getDimension(),
                                        getFormat   (),
                                        getNormalize(),
                                        getStride   (), 
                                        0);
            
            osgGlBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
        }
        else
        {
            osgGlVertexAttribPointerARB(slot, 
                                        getDimension(),
                                        getFormat   (), 
                                        getNormalize(),
                                        getStride   (), 
                                        getData     ());
        }
        
        OSGGETGLFUNCBYID( OSGglEnableVertexAttribArrayARB,
                          osgGlEnableVertexAttribArrayARB,
                         _funcglEnableVertexAttribArrayARB,
                          win);
        
        osgGlEnableVertexAttribArrayARB(slot);
    }
    else 
    {        
        const void *pData = NULL;

        OSGGETGLFUNCBYID( OSGglBindBufferARB, 
                          osgGlBindBufferARB,
                         _funcBindBuffer, 
                          win);

        hasVBO &= getUseVBO() && (getGLId() != 0);

        if(hasVBO == true) // Do we have a VBO?
        {
            osgGlBindBufferARB(GL_ARRAY_BUFFER_ARB,
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
                if (win->hasExtension(_extSecondaryColor))
                {
                    OSGGETGLFUNCBYID( OSGglSecondaryColorPointerEXT,
                                      osgGlSecondaryColorPointerEXT,
                                     _funcglSecondaryColorPointer,
                                      win);

                    osgGlSecondaryColorPointerEXT(getDimension(),
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
                OSGGETGLFUNCBYID( OSGglClientActiveTextureARB,
                                  osgGlClientActiveTextureARB,
                                 _funcglClientActiveTextureARB,
                                  win);

                osgGlClientActiveTextureARB(GL_TEXTURE0_ARB + slot - 8);

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
            osgGlBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
        }
    }
}

void *GeoVectorBufferRefProperty::mapBuffer(GLenum eAccess, DrawEnv *pEnv)
{
    void *returnValue = NULL;

    if((getUseVBO() == true) && (getGLId() != 0))
    {
        Window *pWin = pEnv->getWindow();

        OSGGETGLFUNCBYID( OSGglBindBufferARB, 
                          osgGlBindBufferARB,
                         _funcBindBuffer, 
                          pWin);

        OSGGETGLFUNCBYID( OSGglMapBufferARB, 
                          osgGlMapBufferARB,
                         _funcMapBuffer, 
                          pWin);
       
        osgGlBindBufferARB(GL_ARRAY_BUFFER_ARB,
                           getGLId());

        returnValue = osgGlMapBufferARB(GL_ARRAY_BUFFER_ARB, eAccess);

        osgGlBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
    }

    return returnValue;
}

bool GeoVectorBufferRefProperty::unmapBuffer(DrawEnv *pEnv)
{
    bool returnValue = true;

    if((getUseVBO() == true) && (getGLId() != 0))
    {
        Window *pWin = pEnv->getWindow();

        OSGGETGLFUNCBYID( OSGglBindBufferARB, 
                          osgGlBindBufferARB,
                         _funcBindBuffer, 
                          pWin);

        OSGGETGLFUNCBYID( OSGglUnmapBufferARB, 
                          osgGlUnmapBufferARB,
                         _funcUnmapBuffer, 
                          pWin);

        osgGlBindBufferARB(GL_ARRAY_BUFFER_ARB,
                           getGLId());

        returnValue = osgGlUnmapBufferARB(GL_ARRAY_BUFFER_ARB);

        osgGlBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
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
