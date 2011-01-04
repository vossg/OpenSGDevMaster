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

#include "OSGDSLightChunk.h"

#include "OSGGL.h"
#include "OSGGLU.h"

#include "OSGDrawEnv.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGDSLightChunkBase.cpp file.
// To modify it, please change the .fcd file (OSGDSLightChunk.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

StateChunkClass DSLightChunk::_class("DSLight", 1);

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void DSLightChunk::initMethod(InitPhase ePhase)
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

DSLightChunk::DSLightChunk(void) :
    Inherited()
{
}

DSLightChunk::DSLightChunk(const DSLightChunk &source) :
    Inherited(source)
{
}

DSLightChunk::~DSLightChunk(void)
{
}

/*----------------------------- class specific ----------------------------*/

const StateChunkClass *DSLightChunk::getClass(void) const
{
    return &_class;
}

void DSLightChunk::changed(ConstFieldMaskArg whichField,
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void DSLightChunk::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump DSLightChunk NI" << std::endl;
}

/*--------------------------------- State --------------------------------*/

void DSLightChunk::activate(DrawEnv *drawEnv, UInt32 index)
{
    glErr("dslight:activate:precheck");

    Matrix matMV;
    calcModelView(drawEnv, matMV);

    glPushMatrix();
    glLoadMatrixf(matMV.getValues());

    glLightfv( GL_LIGHT0 + index, 
               GL_DIFFUSE,
              _sfDiffuse.getValue().getValuesRGBA());

    glLightfv( GL_LIGHT0 + index, 
               GL_AMBIENT,
              _sfAmbient.getValue().getValuesRGBA());

    glLightfv( GL_LIGHT0 + index, 
               GL_SPECULAR,
              _sfSpecular.getValue().getValuesRGBA());
    glLightfv( GL_LIGHT0 + index, 
               GL_POSITION,
              _sfPosition.getValue().getValues());

    glLightf ( GL_LIGHT0 + index, 
               GL_CONSTANT_ATTENUATION,
              _sfConstantAttenuation.getValue());

    glLightf ( GL_LIGHT0 + index, 
               GL_LINEAR_ATTENUATION,
              _sfLinearAttenuation.getValue());

    glLightf ( GL_LIGHT0 + index, 
               GL_QUADRATIC_ATTENUATION,
              _sfQuadraticAttenuation.getValue());

    glLightf( GL_LIGHT0 + index, 
              GL_SPOT_CUTOFF, 
             _sfCutoff.getValue());

    if(_sfCutoff.getValue() < 180.f)
    {
        glLightfv( GL_LIGHT0 + index, 
                   GL_SPOT_DIRECTION,
                  _sfDirection.getValue().getValues());

        glLightf( GL_LIGHT0 + index, 
                  GL_SPOT_EXPONENT, 
                 _sfExponent.getValue());
    }

    glEnable(GL_LIGHT0 + index);

    glPopMatrix();

    glErr("dslight:activate:postcheck");
}

void DSLightChunk::changeFrom(DrawEnv *drawEnv, StateChunk *old, UInt32 index)
{
    glErr("dslight:change:precheck");

    const DSLightChunk *oldChunk = dynamic_cast<const DSLightChunk *>(old);

    // change from me to me?
    // this assumes I haven't changed in the meantime. is that a valid 
    // assumption?

    if(oldChunk == this)
        return;

    Matrix matMV;
    calcModelView(drawEnv, matMV);

    glPushMatrix();
    glLoadMatrixf(matMV.getValues());

    // it could theoretically be more efficient to turn the light off before
    // changing its parameters, have to try that sometime

    glLightfv( GL_LIGHT0 + index, 
               GL_DIFFUSE,
              _sfDiffuse.getValue().getValuesRGBA());

    glLightfv( GL_LIGHT0 + index, 
               GL_AMBIENT,
              _sfAmbient.getValue().getValuesRGBA());

    glLightfv( GL_LIGHT0 + index, 
               GL_SPECULAR,
              _sfSpecular.getValue().getValuesRGBA());

    glLightfv( GL_LIGHT0 + index, 
               GL_POSITION,
              _sfPosition.getValue().getValues());

    glLightf ( GL_LIGHT0 + index, 
               GL_CONSTANT_ATTENUATION,
              _sfConstantAttenuation.getValue());

    glLightf ( GL_LIGHT0 + index, 
               GL_LINEAR_ATTENUATION,
              _sfLinearAttenuation.getValue());

    glLightf ( GL_LIGHT0 + index, 
               GL_QUADRATIC_ATTENUATION,
              _sfQuadraticAttenuation.getValue());

    glLightf( GL_LIGHT0 + index, 
              GL_SPOT_CUTOFF,
             _sfCutoff.getValue());

    if(_sfCutoff.getValue() < 180.f)
    {
        glLightfv( GL_LIGHT0 + index, 
                   GL_SPOT_DIRECTION,
                  _sfDirection.getValue().getValues());

        glLightf( GL_LIGHT0 + index, 
                  GL_SPOT_EXPONENT, 
                 _sfExponent.getValue());
    }

    glPopMatrix();

    glErr("dslight:change:postcheck");
}

void DSLightChunk::deactivate(DrawEnv *drawEnv, UInt32 index)
{
    glDisable(GL_LIGHT0 + index);
}

/*-------------------------- Comparison -----------------------------------*/

Real32 DSLightChunk::switchCost(StateChunk *OSG_CHECK_ARG(chunk))
{
    return 0;
}

bool DSLightChunk::operator < (const StateChunk &other) const
{
    return this < &other;
}

bool DSLightChunk::operator == (const StateChunk &other) const
{
    const DSLightChunk *tother = dynamic_cast<const DSLightChunk *>(&other);

    if(!tother)
        return false;

    if(tother == this)
        return true;

    if(!getAmbient  ().equals(tother->getAmbient  (),
                              TypeTraits<Real32>::getDefaultEps()) ||
       !getDiffuse  ().equals(tother->getDiffuse  (),
                              TypeTraits<Real32>::getDefaultEps()) ||
       !getSpecular ().equals(tother->getSpecular (),
                              TypeTraits<Real32>::getDefaultEps()) ||
       !getPosition ().equals(tother->getPosition (),
                              TypeTraits<Real32>::getDefaultEps()) ||
       !getDirection().equals(tother->getDirection(),
                              TypeTraits<Real32>::getDefaultEps()) ||

        getConstantAttenuation () != tother->getConstantAttenuation () ||
        getLinearAttenuation   () != tother->getLinearAttenuation   () ||
        getQuadraticAttenuation() != tother->getQuadraticAttenuation() ||
        getCutoff              () != tother->getCutoff              () ||
        getExponent            () != tother->getExponent            ()
      )
    {
        return false;
    }

    return true;
}

bool DSLightChunk::operator != (const StateChunk &other) const
{
    return ! (*this == other);
}

/*-------------------------------- Helper --------------------------------*/

void DSLightChunk::calcModelView(DrawEnv *drawEnv, Matrix &result)
{
    result = drawEnv->getVPCameraViewing();

    Matrix toWorld;

    if(_sfBeacon.getValue() != NULL)
    {
        _sfBeacon.getValue()->getToWorld(toWorld);
    }
    else
    {
        toWorld.setIdentity();
    }

    result.mult(toWorld);
}

OSG_END_NAMESPACE
