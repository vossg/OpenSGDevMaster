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

#include "OSGMaterialChunk.h"

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGMaterialChunkBase.cpp file.
// To modify it, please change the .fcd file (OSGMaterialChunk.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

StateChunkClass MaterialChunk::_class("Material");

volatile UInt16 MaterialChunk::_uiChunkCounter = 1;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void MaterialChunk::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

MaterialChunk::MaterialChunk(void) :
     Inherited( ),
    _uiChunkId(0)
{
}

MaterialChunk::MaterialChunk(const MaterialChunk &source) :
     Inherited(source),
    _uiChunkId(     0)
{
}

MaterialChunk::~MaterialChunk(void)
{
}


void MaterialChunk::onCreate(const MaterialChunk *source)
{
    Inherited::onCreate(source);

    if(GlobalSystemState == Startup)
        return;

    _uiChunkId = _uiChunkCounter++;
}

void MaterialChunk::onCreateAspect(const MaterialChunk *createAspect,
                                   const MaterialChunk *source      )
{
    Inherited::onCreateAspect(createAspect, source);

    _uiChunkId = createAspect->_uiChunkId;
}

/*------------------------- Chunk Class Access ---------------------------*/

const StateChunkClass *MaterialChunk::getClass(void) const
{
    return &_class;
}

/*------------------------------- Sync -----------------------------------*/

void MaterialChunk::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

UInt16 MaterialChunk::getChunkId(void)
{
    return _uiChunkId;
}

/*------------------------------ Output ----------------------------------*/

void MaterialChunk::dump(      UInt32    uiIndent,
                         const BitVector bvFlags  ) const
{
    Inherited::dump(uiIndent, bvFlags);

    if((bvFlags & DiffuseFieldMask) != 0)
    {
        indentLog(uiIndent, PLOG);
        PLOG << "diffuse " << _sfDiffuse.getValue() << "\n";
    }

    if((bvFlags & AmbientFieldMask) != 0)
    {
        indentLog(uiIndent, PLOG);
        PLOG << "ambient " << _sfAmbient.getValue() << "\n";
    }

    if((bvFlags & SpecularFieldMask) != 0)
    {
        indentLog(uiIndent, PLOG);
        PLOG << "specular " << _sfSpecular.getValue() << "\n";
    }

    if((bvFlags & EmissionFieldMask) != 0)
    {
        indentLog(uiIndent, PLOG);
        PLOG << "emission " << _sfEmission.getValue() << "\n";
    }

    if((bvFlags & ShininessFieldMask) != 0)
    {
        indentLog(uiIndent, PLOG);
        PLOG << "shininess " << _sfShininess.getValue() << "\n";
    }

    if((bvFlags & LitFieldMask) != 0)
    {
        indentLog(uiIndent, PLOG);
        PLOG << "lit " << _sfLit.getValue() << "\n";
    }

    if((bvFlags & ColorMaterialFieldMask) != 0)
    {
        indentLog(uiIndent, PLOG);
        PLOG << "colorMaterial "
             << GLDefineMapper::the()->toString(_sfColorMaterial.getValue())
             << "\n";
    }

    if((bvFlags & BackMaterialFieldMask) != 0)
    {
        indentLog(uiIndent, PLOG);
        PLOG << "backMaterial " << _sfBackMaterial.getValue() << "\n";
    }

    if((bvFlags & BackDiffuseFieldMask) != 0)
    {
        indentLog(uiIndent, PLOG);
        PLOG << "backDiffuse " << _sfBackDiffuse.getValue() << "\n";
    }

    if((bvFlags & BackAmbientFieldMask) != 0)
    {
        indentLog(uiIndent, PLOG);
        PLOG << "backAmbient " << _sfBackAmbient.getValue() << "\n";
    }

    if((bvFlags & BackSpecularFieldMask) != 0)
    {
        indentLog(uiIndent, PLOG);
        PLOG << "backSpecular " << _sfBackSpecular.getValue() << "\n";
    }

    if((bvFlags & BackEmissionFieldMask) != 0)
    {
        indentLog(uiIndent, PLOG);
        PLOG << "backEmission " << _sfBackEmission.getValue() << "\n";
    }

    if((bvFlags & BackShininessFieldMask) != 0)
    {
        indentLog(uiIndent, PLOG);
        PLOG << "backShininess " << _sfBackShininess.getValue() << "\n";
    }
}

/*------------------------------ State ------------------------------------*/

#if OSG_GL_ES_VERSION == 100
void MaterialChunk::activate(DrawEnv *, UInt32)
{
	glErr("material:activate:precheck");

    GLenum target;

    target = GL_FRONT_AND_BACK;

    if(getColorMaterial() == GL_NONE)
    {
        glDisable(GL_COLOR_MATERIAL);
    }
    else
    {
//        glColorMaterial(GL_FRONT_AND_BACK, getColorMaterial());
        glEnable(GL_COLOR_MATERIAL);
    }
        
	glColor4fv(_sfDiffuse.getValue().getValuesRGBA());

    if(getLit())
    {
        glMaterialfv(target, GL_DIFFUSE,
                     _sfDiffuse.getValue().getValuesRGBA());
        glMaterialfv(target, GL_AMBIENT,
                     _sfAmbient.getValue().getValuesRGBA());
        glMaterialfv(target, GL_SPECULAR,
                     _sfSpecular.getValue().getValuesRGBA());
        glMaterialfv(target, GL_EMISSION,
                     _sfEmission.getValue().getValuesRGBA());
        glMaterialf (target, GL_SHININESS, _sfShininess.getValue());
        
        glEnable(GL_LIGHTING);
    }
    else
    {
        glDisable(GL_LIGHTING);
    }

	glErr("material:activate:postcheck");
}

void MaterialChunk::changeFrom(DrawEnv    *, 
                               StateChunk * old_chunk, 
                               UInt32                )
{
	glErr("material:changed:precheck");

    MaterialChunk const *old = dynamic_cast<MaterialChunk const*>(old_chunk);

    // change from me to me?
    // this assumes I haven't changed in the meantime. is that a valid 
    // assumption?

    if(old == this)
    {
        // Reset it, as Geometry colors might have changed it
        if(getColorMaterial() != GL_NONE)
		{
            glColor4fv(_sfDiffuse.getValue().getValuesRGBA());
        }

        return;
    }

    if(getColorMaterial() != old->getColorMaterial())
    {
        if(getColorMaterial() == GL_NONE)
        {
            glDisable(GL_COLOR_MATERIAL);
        }
        else
        {
            //glColorMaterial(GL_FRONT_AND_BACK, getColorMaterial());
            glEnable(GL_COLOR_MATERIAL);
        }
    }
    
    if(getColorMaterial() != GL_NONE)
        glColor4fv(_sfDiffuse.getValue().getValuesRGBA());

    if(getLit() && ! old->getLit())
        glEnable(GL_LIGHTING);

    else if(! getLit() && old->getLit())
        glDisable(GL_LIGHTING);

    if(getLit())
    {
        GLenum target;

        target = GL_FRONT_AND_BACK;
        
        glMaterialfv(target, GL_DIFFUSE,
                     _sfDiffuse.getValue().getValuesRGBA());
        glMaterialfv(target, GL_AMBIENT,
                     _sfAmbient.getValue().getValuesRGBA());
        glMaterialfv(target, GL_SPECULAR,
                     _sfSpecular.getValue().getValuesRGBA());
        glMaterialfv(target, GL_EMISSION,
                     _sfEmission.getValue().getValuesRGBA());

        // adjust shininess only if it differs enough
        if(osgAbs(_sfShininess.getValue() - old->getShininess()) > 1e-4f)
        {
            glMaterialf(target, GL_SHININESS, 
                        _sfShininess.getValue());
        }
    }

	glErr("material:changed:precheck");
}
#else
void MaterialChunk::activate(DrawEnv *, UInt32)
{
	glErr("material:activate:precheck");

    GLenum target;

    if(getBackMaterial())
    {
        target = GL_FRONT;

        if(getColorMaterial() == GL_NONE && getBackColorMaterial() == GL_NONE)
        {
            glDisable(GL_COLOR_MATERIAL);
        }
        else if(getColorMaterial() == GL_NONE)
        {
            glColorMaterial(GL_BACK, getBackColorMaterial());
            glEnable(GL_COLOR_MATERIAL);
        }
        else if(getBackColorMaterial() == GL_NONE)
        {
            glColorMaterial(GL_FRONT, getColorMaterial());
            glEnable(GL_COLOR_MATERIAL);
        }
        else if(getColorMaterial() != getBackColorMaterial())
        {
            FWARNING(("MaterialChunk::activate: can't have different "
                "back and front colorMaterial types!\n"));
            glEnable(GL_COLOR_MATERIAL);
        }
        else
        {
            glColorMaterial(GL_FRONT_AND_BACK, getColorMaterial());
            glEnable(GL_COLOR_MATERIAL);
        }
    }
    else
    {
        target = GL_FRONT_AND_BACK;

        if(getColorMaterial() == GL_NONE)
        {
            glDisable(GL_COLOR_MATERIAL);
        }
        else
        {
            glColorMaterial(GL_FRONT_AND_BACK, getColorMaterial());
            glEnable(GL_COLOR_MATERIAL);
        }
    }
        
    glColor4fv(_sfDiffuse.getValue().getValuesRGBA());

    if(getLit())
    {
        glMaterialfv(target, GL_DIFFUSE,
                      _sfDiffuse.getValue().getValuesRGBA());
        glMaterialfv(target, GL_AMBIENT,
                      _sfAmbient.getValue().getValuesRGBA());
        glMaterialfv(target, GL_SPECULAR,
                      _sfSpecular.getValue().getValuesRGBA());
        glMaterialfv(target, GL_EMISSION,
                      _sfEmission.getValue().getValuesRGBA());
        glMaterialf (target, GL_SHININESS, _sfShininess.getValue());

        if(getBackMaterial())
        {
            glMaterialfv(GL_BACK, GL_DIFFUSE,
                          _sfBackDiffuse.getValue().getValuesRGBA());
            glMaterialfv(GL_BACK, GL_AMBIENT,
                          _sfBackAmbient.getValue().getValuesRGBA());
            glMaterialfv(GL_BACK, GL_SPECULAR,
                          _sfBackSpecular.getValue().getValuesRGBA());
            glMaterialfv(GL_BACK, GL_EMISSION,
                          _sfBackEmission.getValue().getValuesRGBA());
            glMaterialf (GL_BACK, GL_SHININESS, _sfBackShininess.getValue());
        }
        
        glEnable(GL_LIGHTING);
    }
    else
    {
        glDisable(GL_LIGHTING);
    }

	glErr("material:activate:postcheck");
}

void MaterialChunk::changeFrom(DrawEnv    *, 
                               StateChunk * old_chunk, 
                               UInt32                )
{
	glErr("material:changed:precheck");

    MaterialChunk const *old = dynamic_cast<MaterialChunk const*>(old_chunk);

    // change from me to me?
    // this assumes I haven't changed in the meantime. is that a valid 
    // assumption?

    if(old == this)
    {
        // Reset it, as Geometry colors might have changed it
        if(getColorMaterial() != GL_NONE || 
           (getBackMaterial() && getBackColorMaterial() != GL_NONE)
          )
        {
            glColor4fv(_sfDiffuse.getValue().getValuesRGBA());
        }

        return;
    }

    if(getColorMaterial()     != old->getColorMaterial() || 
       getBackColorMaterial() != old->getBackColorMaterial()
      )
    {
        if(getBackMaterial())
        {
            if(getColorMaterial() == GL_NONE && getBackColorMaterial() == GL_NONE)
            {
                glDisable(GL_COLOR_MATERIAL);
            }
            else if(getColorMaterial() == GL_NONE)
            {
                glColorMaterial(GL_BACK, getBackColorMaterial());
                glEnable(GL_COLOR_MATERIAL);
            }
            else if(getBackColorMaterial() == GL_NONE)
            {
                glColorMaterial(GL_FRONT, getColorMaterial());
                glEnable(GL_COLOR_MATERIAL);
            }
            else if(getColorMaterial() != getBackColorMaterial())
            {
                FWARNING(("MaterialChunk::changeFrom: can't have different "
                    "back and front colorMaterial types!\n"));
                glEnable(GL_COLOR_MATERIAL);
            }
            else
            {
                glColorMaterial(GL_FRONT_AND_BACK, getColorMaterial());
                glEnable(GL_COLOR_MATERIAL);
            }
        }
        else
        {
            if(getColorMaterial() == GL_NONE)
            {
                glDisable(GL_COLOR_MATERIAL);
            }
            else
            {
                glColorMaterial(GL_FRONT_AND_BACK, getColorMaterial());
                glEnable(GL_COLOR_MATERIAL);
            }
        }
    }
    
    if(getColorMaterial() != GL_NONE || getBackColorMaterial() != GL_NONE)
        glColor4fv(_sfDiffuse.getValue().getValuesRGBA());

    if(getLit() && ! old->getLit())
        glEnable(GL_LIGHTING);
    else if(! getLit() && old->getLit())
        glDisable(GL_LIGHTING);

    if(getLit())
    {
        GLenum target;

        if(getBackMaterial())
        {
            target = GL_FRONT;
        }
        else
        {
            target = GL_FRONT_AND_BACK;
        }
        
        glMaterialfv(target, GL_DIFFUSE,
                      _sfDiffuse.getValue().getValuesRGBA());
        glMaterialfv(target, GL_AMBIENT,
                      _sfAmbient.getValue().getValuesRGBA());
        glMaterialfv(target, GL_SPECULAR,
                      _sfSpecular.getValue().getValuesRGBA());
        glMaterialfv(target, GL_EMISSION,
                      _sfEmission.getValue().getValuesRGBA());
        // adjust shininess only if it differs enough
        if(osgAbs(_sfShininess.getValue() - old->getShininess()) > 1e-4)
            glMaterialf( target, GL_SHININESS, _sfShininess.getValue());
        
        if(getBackMaterial())
        {
            glMaterialfv(GL_BACK, GL_DIFFUSE,
                          _sfBackDiffuse.getValue().getValuesRGBA());
            glMaterialfv(GL_BACK, GL_AMBIENT,
                          _sfBackAmbient.getValue().getValuesRGBA());
            glMaterialfv(GL_BACK, GL_SPECULAR,
                          _sfBackSpecular.getValue().getValuesRGBA());
            glMaterialfv(GL_BACK, GL_EMISSION,
                          _sfBackEmission.getValue().getValuesRGBA());
            // adjust shininess only if it differs enough
            if(osgAbs(_sfBackShininess.getValue() - 
                      old->getBackShininess()
                     ) > 1e-4)
                glMaterialf( GL_BACK, GL_SHININESS, _sfBackShininess.getValue());
        }
    }

	glErr("material:changed:postcheck");
}
#endif

void MaterialChunk::deactivate(DrawEnv *, UInt32)
{
    if(getLit())
        glDisable(GL_LIGHTING);

    if(getColorMaterial() != GL_NONE)
        glDisable(GL_COLOR_MATERIAL);
}


/*-------------------------- Comparison -----------------------------------*/

Real32 MaterialChunk::switchCost(StateChunk *OSG_CHECK_ARG(chunk))
{
    return 0;
}

bool MaterialChunk::isTransparent(void) const
{
    return(getDiffuse()[3] <(1.f - TypeTraits<Real32>::getDefaultEps()));
}


bool MaterialChunk::operator <(const StateChunk &other) const
{
    return this < &other;
}

bool MaterialChunk::operator ==(const StateChunk &other) const
{
    MaterialChunk const *tother = dynamic_cast<MaterialChunk const*>(&other);

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
       !getEmission ().equals(tother->getEmission (),
                              TypeTraits<Real32>::getDefaultEps()) ||
        getShininess()     != tother->getShininess()             ||
        getLit()           != tother->getLit()                   ||
        getColorMaterial() != tother->getColorMaterial()
      )
        return false;

    return true;
}

bool MaterialChunk::operator !=(const StateChunk &other) const
{
    return !(*this == other);
}

