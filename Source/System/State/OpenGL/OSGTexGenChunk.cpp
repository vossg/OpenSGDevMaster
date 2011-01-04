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

#include "OSGGL.h"
#include "OSGGLU.h"

#include "OSGDrawEnv.h"

#include "OSGTextureBaseChunk.h"

#include "OSGTexGenChunk.h"
#include "OSGCamera.h"
#include "OSGViewport.h"

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGTexGenChunkBase.cpp file.
// To modify it, please change the .fcd file (OSGTexGenChunk.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

StateChunkClass TexGenChunk::_class("TexGen", osgMaxTexCoords, 20);

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void TexGenChunk::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

TexGenChunk::TexGenChunk(void) :
    Inherited()
{
    _sfEyeModelViewMatrix.getValue().setIdentity();
}

TexGenChunk::TexGenChunk(const TexGenChunk &source) :
    Inherited(source)
{
}

TexGenChunk::~TexGenChunk(void)
{
}

/*------------------------- Chunk Class Access ---------------------------*/

const StateChunkClass *TexGenChunk::getClass(void) const
{
    return &_class;
}

/*------------------------------- Sync -----------------------------------*/

void TexGenChunk::changed(ConstFieldMaskArg whichField, 
                          UInt32            origin,
                          BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

/*------------------------------ Output ----------------------------------*/

void TexGenChunk::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump TexGenChunk NI" << std::endl;
}


/*------------------------------ State ------------------------------------*/

static inline void setGenFunc(      GLenum   coord, 
                                    GLenum   gen, 
                                    GLenum   func, 
                              const Vec4f   &plane, 
                                    Node    *beacon, 
                                    Matrix  &cameraMat,
                                    UInt32   eyeMode,
                                    Matrix  &eyeMatrix)
{
	if(beacon != NULL)
    {
        Matrix beaconMat;
        beacon->getToWorld(beaconMat);
        beaconMat.multLeft(cameraMat);
        glPushMatrix();
        glLoadMatrixf(beaconMat.getValues());
        glTexGenfv(coord, 
                   GL_EYE_PLANE, 
                   const_cast<GLfloat *>(plane.getValues()));
        glTexGeni(coord, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
        glPopMatrix();
        glEnable(gen);
    }        
    else if(func == GL_EYE_LINEAR)
    {
        glPushMatrix();
  
        switch(eyeMode)
        {
            case TexGenChunk::EyeModelViewIdentity:
                glLoadIdentity();
                break;
                
            case TexGenChunk::EyeModelViewStored:
                glLoadMatrixf(eyeMatrix.getValues());
                break;

            case TexGenChunk::EyeModelViewCamera:
                glLoadMatrixf(cameraMat.getValues());
                break;

            default:
                break;
        }

        glTexGenfv(coord, 
                   GL_EYE_PLANE, 
                   const_cast<GLfloat *>(plane.getValues()));

        glTexGeni(coord, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);

        glPopMatrix();

        glEnable(gen);
    }        
    else if(func != GL_NONE)                                         
    {                                                                   
        glTexGeni(coord, GL_TEXTURE_GEN_MODE, func);
        
        if(func == GL_OBJECT_LINEAR)
        {
            glTexGenfv(coord, 
                       GL_OBJECT_PLANE, 
                       const_cast<GLfloat *>(plane.getValues()));
        }

        glEnable(gen);
    }
}

void TexGenChunk::activate(DrawEnv *pEnv, UInt32 idx)
{
    glErr("TexGenChunk::activate precheck");

    Window *win = pEnv->getWindow();   

    Real32 ntexcoords;
    if((ntexcoords = win->getConstantValue(GL_MAX_TEXTURE_COORDS_ARB)) ==
       Window::unknownConstant
      )
    {
        ntexcoords = win->getConstantValue(GL_MAX_TEXTURE_UNITS_ARB);
        // sgi doesn't support GL_MAX_TEXTURE_UNITS_ARB!
        if(ntexcoords == Window::unknownConstant)
            ntexcoords = 1.0f;
    }

    if(idx >= static_cast<UInt32>(ntexcoords))
    {
#ifdef OSG_DEBUG
        FWARNING(("TexGenChunk::activate: Trying to bind texcoord unit %d,"
                  " but Window %p only supports %lf!\n",
                  idx, win, ntexcoords));
#endif
        return;        
    }
        
    TextureBaseChunk::activateTexture(win, idx);

    FDEBUG(("TexGenChunk::activate\n"));

    Matrix cameraMat = pEnv->getCameraViewing(); 
  
#if OLD_DA
    Viewport *vp = pEnv->getViewport();
	if(vp != NULL)
	{
		pEnv->getCamera()->getViewing(cameraMat, 
                                      vp->getPixelWidth(), 
                                      vp->getPixelHeight());
	}
#endif

    // genfuncs
    setGenFunc(GL_S, GL_TEXTURE_GEN_S, getGenFuncS(), getGenFuncSPlane(),
               getSBeacon(), cameraMat, _sfEyeModelViewMode.getValue(),
               _sfEyeModelViewMatrix.getValue());
    glErr("TexGenChunk::activateS");
    setGenFunc(GL_T, GL_TEXTURE_GEN_T, getGenFuncT(), getGenFuncTPlane(),
                getTBeacon(), cameraMat, _sfEyeModelViewMode.getValue(),
               _sfEyeModelViewMatrix.getValue());
    glErr("TexGenChunk::activateT");
    setGenFunc(GL_R, GL_TEXTURE_GEN_R, getGenFuncR(), getGenFuncRPlane(),
                getRBeacon(), cameraMat, _sfEyeModelViewMode.getValue(),
               _sfEyeModelViewMatrix.getValue());
    glErr("TexGenChunk::activateR");
    setGenFunc(GL_Q, GL_TEXTURE_GEN_Q, getGenFuncQ(), getGenFuncQPlane(),
                getQBeacon(), cameraMat, _sfEyeModelViewMode.getValue(),
               _sfEyeModelViewMatrix.getValue());
	glErr("TexGenChunk::activateQ");
}


static inline void changeGenFunc(      GLenum   oldfunc, 
                                       Node    *oldbeacon, 
                                       GLenum   coord, 
                                       GLenum   gen, 
                                       GLenum   func, 
                                 const Vec4f   &plane, 
                                       Node    *beacon, 
                                       Matrix  &cameraMat,
                                       UInt32   eyeMode,
                                       Matrix  &eyeMatrix)
{
	if(beacon != NULL)
    {
        Matrix beaconMat;
        beacon->getToWorld(beaconMat);
        beaconMat.multLeft(cameraMat);
        glPushMatrix();
        glLoadMatrixf(beaconMat.getValues());
        glTexGenfv(coord, 
                   GL_EYE_PLANE, 
                   const_cast<GLfloat *>(plane.getValues()));
        glTexGeni(coord, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
        glPopMatrix();
        if(oldfunc == GL_NONE && oldbeacon == NULL) 
            glEnable(gen);
    }
    else if(func == GL_EYE_LINEAR)
    {
        glPushMatrix();

        switch(eyeMode)
        {
            case TexGenChunk::EyeModelViewIdentity:
                glLoadIdentity();
                break;
                
            case TexGenChunk::EyeModelViewStored:
                glLoadMatrixf(eyeMatrix.getValues());
                break;

            case TexGenChunk::EyeModelViewCamera:
                glLoadMatrixf(cameraMat.getValues());
                break;

            default:
                break;
        }

        glTexGenfv(coord, 
                   GL_EYE_PLANE, 
                   const_cast<GLfloat *>(plane.getValues()));

        glTexGeni(coord, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);

        glPopMatrix();

        if(oldfunc == GL_NONE && oldbeacon == NULL) 
            glEnable(gen);
    }        
    else if(func != GL_NONE)                                         
    {                                                                   
        glTexGeni(coord, GL_TEXTURE_GEN_MODE, func);        
        
        if(func == GL_OBJECT_LINEAR)
        {
            glTexGenfv(coord, 
                       GL_OBJECT_PLANE, 
                       const_cast<GLfloat *>(plane.getValues()));
        }
            
        if(oldfunc == GL_NONE && oldbeacon == NULL) 
            glEnable(gen);
    }
    else if(oldfunc != GL_NONE || oldbeacon != NULL) 
    {
        glDisable(gen);  
    }
}

void TexGenChunk::changeFrom(DrawEnv    *pEnv, 
                             StateChunk *old   , 
                             UInt32      idx)
{
    // change from me to me?
    // this assumes I haven't changed in the meantime. 
    // is that a valid assumption?
    // No, for TexGen it's not, as TexGen depends on the current 
    // toWorld matrix!!!
    // if(old == this)
    //     return;
    TexGenChunk *oldp      = dynamic_cast<TexGenChunk *>(old);
    
    // If the old one is not a texgen chunk, deactivate it and activate
    // ourselves
    if(!oldp)
    {
        old->deactivate(pEnv, idx);
        activate(pEnv, idx);
        return;
    }

    glErr("TexGenChunk::changeFrom precheck");

    Window *win = pEnv->getWindow();   

    Real32 ntexcoords;
    if((ntexcoords = win->getConstantValue(GL_MAX_TEXTURE_COORDS_ARB)) ==
       Window::unknownConstant
      )
    {
        ntexcoords = win->getConstantValue(GL_MAX_TEXTURE_UNITS_ARB);
        // sgi doesn't support GL_MAX_TEXTURE_UNITS_ARB!
        if(ntexcoords == Window::unknownConstant)
            ntexcoords = 1.0f;
    }

    if(idx >= static_cast<UInt32>(ntexcoords))
    {
#ifdef OSG_DEBUG
        FWARNING(("TexGenChunk::changeFrom: Trying to bind texcoord unit "
                  "%d, but Window %p only supports %lf!\n",
                  idx, win, ntexcoords));
#endif
        return;        
    }
 
    Matrix cameraMat = pEnv->getCameraViewing();   

#ifdef OLD_DA
    Viewport *vp = pEnv->getViewport();
	if(vp != NULL)
	{
		pEnv->getCamera()->getViewing(cameraMat, 
                                      vp->getPixelWidth(), 
                                      vp->getPixelHeight());
	}
#endif
   
    TextureBaseChunk::activateTexture(win, idx);

    changeGenFunc(oldp->getGenFuncS(), 
                  oldp->getSBeacon(), 
                  GL_S, 
                  GL_TEXTURE_GEN_S, 
                  getGenFuncS(), 
                  getGenFuncSPlane(), 
                  getSBeacon(), 
                  cameraMat, 
                  _sfEyeModelViewMode.getValue(),
                  _sfEyeModelViewMatrix.getValue());

    changeGenFunc(oldp->getGenFuncT(), oldp->getTBeacon(), GL_T, 
                  GL_TEXTURE_GEN_T, 
                  getGenFuncT(), getGenFuncTPlane(), getTBeacon(), cameraMat, 
                  _sfEyeModelViewMode.getValue(),
                  _sfEyeModelViewMatrix.getValue());

    changeGenFunc(oldp->getGenFuncR(), oldp->getRBeacon(), GL_R, 
                  GL_TEXTURE_GEN_R, 
                  getGenFuncR(), getGenFuncRPlane(), getRBeacon(), cameraMat, 
                  _sfEyeModelViewMode.getValue(),
                  _sfEyeModelViewMatrix.getValue());

    changeGenFunc(oldp->getGenFuncQ(), oldp->getQBeacon(), GL_Q, 
                  GL_TEXTURE_GEN_Q, 
                  getGenFuncQ(), getGenFuncQPlane(), getQBeacon(), cameraMat, 
                  _sfEyeModelViewMode.getValue(),
                  _sfEyeModelViewMatrix.getValue());

    glErr("TexGenChunk::changeFrom");
}

void TexGenChunk::deactivate(DrawEnv *pEnv, UInt32 idx)
{
    glErr("TexGenChunk::deactivate precheck");

    Window *win = pEnv->getWindow();   

    Real32 ntexcoords;
    if((ntexcoords = win->getConstantValue(GL_MAX_TEXTURE_COORDS_ARB)) ==
       Window::unknownConstant
      )
    {
        ntexcoords = win->getConstantValue(GL_MAX_TEXTURE_UNITS_ARB);
        // sgi doesn't support GL_MAX_TEXTURE_UNITS_ARB!
        if(ntexcoords == Window::unknownConstant)
            ntexcoords = 1.0f;
    }

    if(idx >= static_cast<UInt32>(ntexcoords))
    {
#ifdef OSG_DEBUG
        FWARNING(("TexGenChunk::deactivate: Trying to bind texcoord unit %d,"
                  " but Window %p only supports %lf!\n",
                  idx, win, ntexcoords));
#endif
        return;        
    }

    TextureBaseChunk::activateTexture(win, idx);

    if(getGenFuncS() != GL_NONE || getSBeacon() != NULL)
        glDisable(GL_TEXTURE_GEN_S);

    if(getGenFuncT() != GL_NONE || getTBeacon() != NULL)
        glDisable(GL_TEXTURE_GEN_T);

    if(getGenFuncR() != GL_NONE || getRBeacon() != NULL)
        glDisable(GL_TEXTURE_GEN_R);

    if(getGenFuncQ() != GL_NONE || getQBeacon() != NULL)
        glDisable(GL_TEXTURE_GEN_Q);

    glErr("TexGenChunk::deactivate");
}

/*-------------------------- Comparison -----------------------------------*/

Real32 TexGenChunk::switchCost(StateChunk *OSG_CHECK_ARG(chunk))
{
    return 0;
}

bool TexGenChunk::operator < (const StateChunk &other) const
{
    return this < &other;
}

bool TexGenChunk::operator == (const StateChunk &other) const
{
    TexGenChunk const *tother = dynamic_cast<TexGenChunk const*>(&other);

    if(!tother)
        return false;

    if(tother == this)
        return true;

    return  getGenFuncS()   == tother->getGenFuncS() &&
            getGenFuncT()   == tother->getGenFuncT() &&
            getGenFuncR()   == tother->getGenFuncR() &&
            getGenFuncQ()   == tother->getGenFuncQ() &&
            // not quite right. needs only to be tested for genfuncs using them
            getGenFuncSPlane()  == tother->getGenFuncSPlane() &&
            getGenFuncTPlane()  == tother->getGenFuncTPlane() &&
            getGenFuncRPlane()  == tother->getGenFuncRPlane() &&
            getGenFuncQPlane()  == tother->getGenFuncQPlane() ;
}

bool TexGenChunk::operator != (const StateChunk &other) const
{
    return ! (*this == other);
}

