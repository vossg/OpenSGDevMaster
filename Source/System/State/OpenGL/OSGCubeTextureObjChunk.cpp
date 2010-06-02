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
#include <boost/bind.hpp>

#include "OSGConfig.h"

#include "OSGGL.h"
#include "OSGGLU.h"
#include "OSGGLEXT.h"
#include "OSGDrawEnv.h"

#include "OSGCubeTextureObjChunk.h"

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGCubeTextureObjChunkBase.cpp file.
// To modify it, please change the .fcd file (OSGCubeTextureObjChunk.fcd) and
// regenerate the base file.

void CubeTextureObjChunk::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

CubeTextureObjChunk::CubeTextureObjChunk(void) :
    Inherited()
{
}

CubeTextureObjChunk::CubeTextureObjChunk(const CubeTextureObjChunk &source) :
    Inherited(source)
{
}

CubeTextureObjChunk::~CubeTextureObjChunk(void)
{
}

/*------------------------- Chunk Class Access ---------------------------*/

const StateChunkClass *CubeTextureObjChunk::getClass(void) const
{
    return TextureBaseChunk::getClass();
}

/*------------------------------- Sync -----------------------------------*/

bool CubeTextureObjChunk::isCubeTexture(void)
{
    return true;
}



void CubeTextureObjChunk::changed(ConstFieldMaskArg whichField, 
                                  UInt32            origin,
                                  BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

/*----------------------------- onCreate --------------------------------*/

void CubeTextureObjChunk::onCreate(const CubeTextureObjChunk *source)
{
    // skip TextureObjChunk::onCreate
    TextureBaseChunk::onCreate(source);

    if(GlobalSystemState == Startup)
        return;

    setGLId(               
        Window::registerGLObject(
            boost::bind(&CubeTextureObjChunk::handleGL, 
                        CubeTextureObjChunkMTUncountedPtr(this), 
                        _1, _2, _3, _4),
            &CubeTextureObjChunk::handleDestroyGL));
}

void CubeTextureObjChunk::onDestroy(UInt32 uiContainerId)
{
    if(getGLId() > 0)
        Window::destroyGLObject(getGLId(), 1);

    // skip TextureObjChunk::onDestroy
    TextureBaseChunk::onDestroy(uiContainerId);
}

/*------------------------------ Output ----------------------------------*/

void CubeTextureObjChunk::dump(      UInt32    , 
                               const BitVector ) const
{
    SLOG << "Dump CubeTextureObjChunk NI" << std::endl;
}


/*-------------------------------- GL ------------------------------------*/

UInt32 CubeTextureObjChunk::handleGL(DrawEnv                 *pEnv, 
                                     UInt32                   osgid, 
                                     Window::GLObjectStatusE  mode,
                                     UInt32                   uiOptions)
{
    GLuint  id;

    Window *win = pEnv->getWindow();

    // does the window support cubemaps?
    if(win->hasExtension(_arbCubeTex) == false)
        return 0;

    id = win->getGLObjectId(osgid);

    if(mode == Window::initialize || mode == Window::reinitialize)
    {
        if(mode == Window::initialize)
        {
            glGenTextures(1, &id);

            win->setGLObjectId(osgid, id);
        }

        handleTexture(win, id, 
                      GL_TEXTURE_CUBE_MAP_ARB, 
                      GL_TEXTURE_CUBE_MAP_ARB, 
                      GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB, 
                      mode, getImage());        
        handleTexture(win, id, 
                      GL_TEXTURE_CUBE_MAP_ARB, 
                      GL_NONE, 
                      GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB, 
                      Window::initialize, getPosZImage());        
        handleTexture(win, id, 
                      GL_TEXTURE_CUBE_MAP_ARB, 
                      GL_NONE, 
                      GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB, 
                      Window::initialize, getNegYImage());        
        handleTexture(win, id, 
                      GL_TEXTURE_CUBE_MAP_ARB, 
                      GL_NONE, 
                      GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB, 
                      Window::initialize, getPosYImage());        
        handleTexture(win, id, 
                      GL_TEXTURE_CUBE_MAP_ARB, 
                      GL_NONE, 
                      GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB, 
                      Window::initialize, getNegXImage());        
        handleTexture(win, id, 
                      GL_TEXTURE_CUBE_MAP_ARB, 
                      GL_NONE, 
                      GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB, 
                      Window::initialize, getPosXImage());        
    }
    else if(mode == Window::needrefresh)
    {
        handleTexture(win, id, 
                      GL_TEXTURE_CUBE_MAP_ARB, 
                      GL_TEXTURE_CUBE_MAP_ARB, 
                      GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB, 
                      mode, getImage());        
        handleTexture(win, id, 
                      GL_TEXTURE_CUBE_MAP_ARB, 
                      GL_NONE, 
                      GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB, 
                      mode, getPosZImage());        
        handleTexture(win, id, 
                      GL_TEXTURE_CUBE_MAP_ARB, 
                      GL_NONE, 
                      GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB, 
                      mode, getNegYImage());        
        handleTexture(win, id, 
                      GL_TEXTURE_CUBE_MAP_ARB, 
                      GL_NONE, 
                      GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB, 
                      mode, getPosYImage());        
        handleTexture(win, id, 
                      GL_TEXTURE_CUBE_MAP_ARB, 
                      GL_NONE, 
                      GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB, 
                      mode, getNegXImage());        
        handleTexture(win, id, 
                      GL_TEXTURE_CUBE_MAP_ARB, 
                      GL_NONE, 
                      GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB, 
                      mode, getPosXImage());        
    }
    else
    {
        SWARNING << "Win:" << win << "TextureObjChunk(" << this 
                 << "::handleGL: Illegal mode: "
                 << mode << " for id " << id << std::endl;
    }

    return 0;
}


void CubeTextureObjChunk::handleDestroyGL(DrawEnv                 *pEnv, 
                                          UInt32                   osgid, 
                                          Window::GLObjectStatusE  mode)
{
    GLuint  id;

    Window *win = pEnv->getWindow();

    // does the window support cubemaps?
    if(win->hasExtension(_arbCubeTex) == false)
        return;

    id = win->getGLObjectId(osgid);

    if(mode == Window::destroy)
    {
        glDeleteTextures(1, &id);
        win->setGLObjectId(osgid, 0);
    }
    else if(mode == Window::finaldestroy)
    {
        //SWARNING << "Last texture user destroyed" << std::endl;
    }
    else
    {
        SWARNING << "Win:" << win << "TextureObjChunk" 
                 << "::handleDestroyGL: Illegal mode: "
                 << mode << " for id " << id << std::endl;
    }
}


/*------------------------------ State ------------------------------------*/

void CubeTextureObjChunk::activate(DrawEnv *pEnv, UInt32 idx)
{   
    // does the window support cubemaps?
    if(pEnv->getWindow()->hasExtension(_arbCubeTex) == false)
        return;
        
    Window *win = pEnv->getWindow();
    
    Real32 nteximages, ntexcoords;

    if((nteximages = win->getConstantValue(GL_MAX_TEXTURE_IMAGE_UNITS_ARB)) ==
       Window::unknownConstant)
    {
        nteximages = win->getConstantValue(GL_MAX_TEXTURE_UNITS_ARB);

        // sgi doesn't support GL_MAX_TEXTURE_UNITS_ARB!
        if(nteximages == Window::unknownConstant)
            nteximages = 1.0f;
    }

    if((ntexcoords = win->getConstantValue(GL_MAX_TEXTURE_COORDS_ARB)) ==
       Window::unknownConstant)
    {
        ntexcoords = win->getConstantValue(GL_MAX_TEXTURE_UNITS_ARB);

        // sgi doesn't support GL_MAX_TEXTURE_UNITS_ARB!
        if(ntexcoords == Window::unknownConstant)
            ntexcoords = 1.0f;
    }

    if(idx >= static_cast<UInt32>(nteximages))
    {
#ifdef OSG_DEBUG
        FWARNING(("CubeTextureObjChunk::activate: Trying to bind image unit "
                  "%d, but Window %p only supports %lf!\n",
                  idx, win, nteximages));
#endif
        return;        
    }
    
    if(TextureBaseChunk::activateTexture(win, idx))
        return; // trying to use too many textures

    glErr("CubeTextureObjChunk::activate precheck");
    
    win->validateGLObject(getGLId(), pEnv);

  
    FDEBUG(("CubeTextureObjChunk::activate - %d\n", getGLId()));


    // Update the texture statistics
    StatCollectorP pColl = pEnv->getStatCollector();
    
    if(NULL != pColl)
    {
        pColl->getElem(TextureObjChunk::statNTextures)->inc(getGLId());

        if(getImage() != NULL)
        {
            pColl->getElem(TextureObjChunk::statNTexBytes)->add(
                getGLId(), 
                getImage()->getSize(true,true,true) * 6);
        }
    }

    glBindTexture(GL_TEXTURE_CUBE_MAP_ARB, win->getGLObjectId(getGLId()));

    pEnv->setActiveTexTarget(idx, GL_TEXTURE_CUBE_MAP_ARB);

    glEnable(GL_TEXTURE_CUBE_MAP_ARB);
    glErr("CubeTextureObjChunk::activate");
}

void CubeTextureObjChunk::changeFrom(DrawEnv    *pEnv, 
                                  StateChunk *old   , 
                                  UInt32      idx   )
{
    // does the window support cubemaps?
    if(pEnv->getWindow()->hasExtension(_arbCubeTex) == false)
        return;
        
    // change from me to me?
    // this assumes I haven't changed in the meantime. 
    // is that a valid assumption?
    if(old == this)
        return;
    
    // If the old one is not a cube texture chunk, deactivate it and
    // activate ourselves
    if(getTypeId() != old->getTypeId())
    {
        old->deactivate(pEnv, idx);
        activate(pEnv, idx);
        return;
    }

    Window *win = pEnv->getWindow();   

    Real32 nteximages, ntexcoords;

    glErr("CubeTextureObjChunk::changeFrom precheck");

    if((nteximages = win->getConstantValue(GL_MAX_TEXTURE_IMAGE_UNITS_ARB)) ==
       Window::unknownConstant)
    {
        nteximages = win->getConstantValue(GL_MAX_TEXTURE_UNITS_ARB);

        // sgi doesn't support GL_MAX_TEXTURE_UNITS_ARB!
        if(nteximages == Window::unknownConstant)
            nteximages = 1.0f;
    }

    if((ntexcoords = win->getConstantValue(GL_MAX_TEXTURE_COORDS_ARB)) ==
       Window::unknownConstant)
    {
        ntexcoords = win->getConstantValue(GL_MAX_TEXTURE_UNITS_ARB);

        // sgi doesn't support GL_MAX_TEXTURE_UNITS_ARB!
        if(ntexcoords == Window::unknownConstant)
            ntexcoords = 1.0f;
    }

    if(idx >= static_cast<UInt32>(nteximages))
    {
#ifdef OSG_DEBUG
        FWARNING(("TextureObjChunk::activate: Trying to bind image unit %d,"
                  " but Window %p only supports %lf!\n",
                  idx, win, nteximages));
#endif
        return;        
    }

    if(TextureBaseChunk::activateTexture(win, idx))
        return; // trying to use too many textures

    win->validateGLObject(getGLId(), pEnv);
    
    FDEBUG(("CubeTextureObjChunk::activate - %d\n", getGLId()));

    // Update the texture statistics
    StatCollectorP pColl = pEnv->getStatCollector();
    
    if(NULL != pColl)
    {
        pColl->getElem(TextureObjChunk::statNTextures)->inc(getGLId());

        if(getImage() != NULL)
        {
            pColl->getElem(TextureObjChunk::statNTexBytes)->add(
                getGLId(), 
                getImage()->getSize(true,true,true) * 6);
        }
    }

    glBindTexture(GL_TEXTURE_CUBE_MAP_ARB, win->getGLObjectId(getGLId()));

    pEnv->setActiveTexTarget(idx, GL_TEXTURE_CUBE_MAP_ARB);


    glErr("CubeTextureObjChunk::changeFrom");
}

void CubeTextureObjChunk::deactivate(DrawEnv *pEnv, UInt32 idx)
{
    // does the window support cubemaps?
    if(pEnv->getWindow()->hasExtension(_arbCubeTex) == false)
        return;
        
    Window *win = pEnv->getWindow();   

    Real32 nteximages, ntexcoords;
    if((nteximages = win->getConstantValue(GL_MAX_TEXTURE_IMAGE_UNITS_ARB)) ==
       Window::unknownConstant )
    {
        nteximages = win->getConstantValue(GL_MAX_TEXTURE_UNITS_ARB);

        // sgi doesn't support GL_MAX_TEXTURE_UNITS_ARB!
        if(nteximages == Window::unknownConstant)
            nteximages = 1.0f;
    }

    if((ntexcoords = win->getConstantValue(GL_MAX_TEXTURE_COORDS_ARB)) ==
       Window::unknownConstant )
    {
        ntexcoords = win->getConstantValue(GL_MAX_TEXTURE_UNITS_ARB);

        // sgi doesn't support GL_MAX_TEXTURE_UNITS_ARB!
        if(ntexcoords == Window::unknownConstant)
            ntexcoords = 1.0f;
    }

    if(idx >= static_cast<UInt32>(nteximages))
    {
#ifdef OSG_DEBUG
        FWARNING(("CubeTextureObjChunk::deactivate: Trying to bind image unit"
                  " %d, but Window %p only supports %lf!\n",
                  idx, win, nteximages));
#endif
        return;        
    }

    TextureBaseChunk::activateTexture(win, idx);

    glDisable(GL_TEXTURE_CUBE_MAP_ARB);

    pEnv->setActiveTexTarget(idx, GL_NONE);

    glErr("CubeTextureObjChunk::deactivate");
}

/*-------------------------- Comparison -----------------------------------*/

Real32 CubeTextureObjChunk::switchCost(StateChunk *OSG_CHECK_ARG(chunk))
{
    return 0;
}

bool CubeTextureObjChunk::operator < (const StateChunk &other) const
{
    return this < &other;
}

bool CubeTextureObjChunk::operator == (const StateChunk &other) const
{
    CubeTextureObjChunk const *tother = 
        dynamic_cast<CubeTextureObjChunk const*>(&other);

    if(!tother)
        return false;

    if(tother == this)
        return true;

    return  TextureBaseChunk::operator==(other)       &&
            getPosZImage()  == tother->getPosZImage() &&
            getPosYImage()  == tother->getPosYImage() &&
            getNegYImage()  == tother->getNegYImage() &&
            getPosXImage()  == tother->getPosXImage() &&
            getNegXImage()  == tother->getNegXImage();
}

bool CubeTextureObjChunk::operator != (const StateChunk &other) const
{
    return ! (*this == other);
}
