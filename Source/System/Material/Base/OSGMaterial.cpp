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
#include "OSGMaterial.h"
#include "OSGSimpleMaterial.h"

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGMaterialBase.cpp file.
// To modify it, please change the .fcd file (OSGMaterial.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

const Int32 Material::NoStateSorting               = 0x7fffffff;
const Int32 Material::TransparencyAutoDetection    = 0;
const Int32 Material::TransparencyForceTransparent = 1;
const Int32 Material::TransparencyForceOpaque      = 2;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

void Material::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);
}

void Material::resolveLinks(void)
{
    Inherited::resolveLinks();
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/


/*------------- constructors & destructors --------------------------------*/

Material::Material(void) :
    Inherited()
{
}

Material::Material(const Material &source) :
     Inherited(source)
{
}

Material::~Material(void)
{
}


void Material::changed(ConstFieldMaskArg whichField, 
                       UInt32            origin,
                       BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

/*------------------------------- dump ----------------------------------*/

void Material::dump(      UInt32    ,
                    const BitVector ) const
{
    SLOG << "Material::dump called: NIY!" << std::endl;
//   Inherited::dump(uiIndent, bvFlags);
}

ActionBase::ResultE Material::renderEnter(NodeCore * const pCore,
                                          Action   *       pAction)
{
    return Action::Continue;
}

ActionBase::ResultE Material::renderLeave(NodeCore * const pCore,
                                          Action   *       pAction)
{
    return Action::Continue;
}

/*-------------------------- comparison -----------------------------------*/

#if 0
bool Material::operator < (const Material &other) const
{
    return this < &other;
}

bool Material::operator == (const Material &other) const
{   
    return _pState == other._pState;
}

bool Material::operator != (const Material &other) const
{
    return ! (*this == other);
}
#endif


/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

#if defined(OSG_WIN32_ICL) && !defined(OSG_CHECK_FIELDSETARG)
#pragma warning (disable : 383)
#endif

OSG_BEGIN_NAMESPACE

static bool subRefDefaultMaterial     (void);
static bool subRefDefaultUnlitMaterial(void);


/*! \ingroup GrpSystemDrawablesGeometrySimpleGeometry
    Stores the default material used by the Simple Geometry.
*/
static SimpleMaterialMTRecPtr _defaultMaterial;

/*! \ingroup GrpSystemDrawablesGeometrySimpleGeometry
    Access the default Material for Simple Geometry. Also useful whenever 
    an arbitrary material is needed.
*/

PrimeMaterial *getDefaultMaterial(void)
{
    if(_defaultMaterial == NULL)
    {
        _defaultMaterial = SimpleMaterial::create();

        _defaultMaterial->setDiffuse  (Color3f(.7f,.7f,.5f));
        _defaultMaterial->setAmbient  (Color3f(0.1f,0.1f,0.1f));
        _defaultMaterial->setSpecular (Color3f(1.f,1.f,1.f));
        _defaultMaterial->setShininess(20.f);

        addPreFactoryExitFunction(subRefDefaultMaterial);

        _defaultMaterial->rebuildState();
    }
    
    return _defaultMaterial;
}

/*! \ingroup GrpSystemDrawablesGeometrySimpleGeometry
    Stores the default unlit material.
*/
static SimpleMaterialMTRecPtr _defaultUnlitMaterial;

/*! \ingroup GrpSystemDrawablesGeometrySimpleGeometry
    Access the default unlit Material. Useful whenever 
    an arbitrary unlit material is needed.
*/

PrimeMaterial *getDefaultUnlitMaterial(void)
{
    if(_defaultUnlitMaterial == NULL)
    {
        _defaultUnlitMaterial = SimpleMaterial::create();

        _defaultUnlitMaterial->setDiffuse(Color3f(1.f,1.f,.5f));
        _defaultUnlitMaterial->setLit(false);

        addPreFactoryExitFunction(subRefDefaultUnlitMaterial);

        _defaultUnlitMaterial->rebuildState();
    }
    
    return _defaultUnlitMaterial;
}

bool subRefDefaultMaterial     (void)
{
//    _defaultMaterial = NULL;
    _defaultMaterial.shutdownSetNull();

    return true;
}

bool subRefDefaultUnlitMaterial(void)
{
//    _defaultUnlitMaterial = NULL;
    _defaultUnlitMaterial.shutdownSetNull();

    return true;
}

OSG_END_NAMESPACE
 
