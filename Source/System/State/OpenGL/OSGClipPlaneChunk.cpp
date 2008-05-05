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

#include <OSGGL.h>

#include <OSGCamera.h>
#include <OSGDrawEnv.h>

#include "OSGClipPlaneChunk.h"

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGClipPlaneChunkBase.cpp file.
// To modify it, please change the .fcd file (OSGClipPlaneChunk.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/
   
StateChunkClass ClipPlaneChunk::_class("ClipPlane", 6);

void ClipPlaneChunk::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/
   
/*----------------------- constructors & destructors ----------------------*/

ClipPlaneChunk::ClipPlaneChunk(void) :
    Inherited()
{
}

ClipPlaneChunk::ClipPlaneChunk(const ClipPlaneChunk &source) :
    Inherited(source)
{
}

ClipPlaneChunk::~ClipPlaneChunk(void)
{
}

/*----------------------- Chunk Class Access -----------------------------*/

const StateChunkClass *ClipPlaneChunk::getClass(void) const
{
     return &_class;
}

/*------------------------------- Sync -----------------------------------*/

void ClipPlaneChunk::changed(ConstFieldMaskArg whichField, 
                             UInt32            origin,
                             BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

/*------------------------------ Output ----------------------------------*/

void ClipPlaneChunk::dump(      UInt32    , 
                          const BitVector) const
{
    SLOG << "Dump ClipPlaneChunk NI" << std::endl;
}


/*------------------------------ State ------------------------------------*/

void ClipPlaneChunk::activate(DrawEnv *pEnv, UInt32 idx)
{
    Matrix beaconMat;

    Matrix cameraMat = pEnv->getCameraViewing();

    if(getBeacon() != NULL) 
    {
        getBeacon()->getToWorld(beaconMat);
    }
    else
    {
        beaconMat.setIdentity();

        SWARNING << "NO beacon" << std::endl;
    }

    cameraMat.mult(beaconMat);
    
    if(getEnable() == true)
    {
              GLdouble  glEq[4];
        const Vec4f    &eq = getEquation();

        glEq[0] = eq[0];
        glEq[1] = eq[1];
        glEq[2] = eq[2];
        glEq[3] = eq[3];
        
        glPushMatrix();
        glLoadMatrixf(cameraMat.getValues());
        
        glClipPlane( GL_CLIP_PLANE0 + idx, glEq);
        glEnable( GL_CLIP_PLANE0 + idx);
        
        glPopMatrix();
    }
}




void ClipPlaneChunk::changeFrom(DrawEnv    *pEnv, 
                                StateChunk *old_chunk, 
                                UInt32      idx)
{
    ClipPlaneChunk const *old = dynamic_cast<ClipPlaneChunk const*>(old_chunk);

    // change from me to me?
    // this assumes I haven't changed in the meantime. 
    // is that a valid assumption?

    if(old == this)
        return;

    Matrix beaconMat;

    Matrix cameraMat = pEnv->getCameraViewing();

    if(getBeacon() != NULL) 
    {
        getBeacon()->getToWorld(beaconMat);
    }
    else
    {
        beaconMat.setIdentity();

        SWARNING << "ClipPlaneChunk::changeFrom: NO beacon" << std::endl;
    }
    
    cameraMat.mult(beaconMat);
    
    if(getEnable() != old->getEnable() ||
       getBeacon() != old->getBeacon()  )
    {
        if(getEnable() == true)
        {
                  GLdouble  glEq[4];

            const Vec4f    &eq = getEquation();

            glEq[0] = eq[0];
            glEq[1] = eq[1];
            glEq[2] = eq[2];
            glEq[3] = eq[3];
            
            glPushMatrix();
            glLoadMatrixf(cameraMat.getValues());
            
            glClipPlane(GL_CLIP_PLANE0 + idx, glEq);
            glEnable   (GL_CLIP_PLANE0 + idx      );
            
            glPopMatrix();
        }
        else  
        {
            glDisable(GL_CLIP_PLANE0 + idx);
        }
    }
}


void ClipPlaneChunk::deactivate(DrawEnv *, UInt32 idx)
{
    if(getEnable() == true)
    {
        glDisable( GL_CLIP_PLANE0 + idx);
    }
}


/*-------------------------- Comparison -----------------------------------*/

Real32 ClipPlaneChunk::switchCost(StateChunk *OSG_CHECK_ARG(chunk))
{
    return 0;
}

bool ClipPlaneChunk::operator < (const StateChunk &other) const
{
    return this < &other;
}

bool ClipPlaneChunk::operator == (const StateChunk &other) const
{
    ClipPlaneChunk const *tother = dynamic_cast<ClipPlaneChunk const*>(&other);

    if(!tother)
        return false;

    if(getEnable() != tother->getEnable())
        return false;

    if(getEquation() != tother->getEquation())
        return false;

    if(getBeacon() != tother->getBeacon())
        return false;
    
    return true;
}

bool ClipPlaneChunk::operator != (const StateChunk &other) const
{
    return ! (*this == other);
}
