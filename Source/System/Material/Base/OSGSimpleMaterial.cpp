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
 * MERCHANTABILITY or FITNESS forA PARTICULAR PURPOSE.  See the GNU         *
 * Library General Public License formore details.                          *
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

#include "OSGAction.h"

#include "OSGStateChunk.h"
#include "OSGState.h"
#include "OSGMaterialChunk.h"

#include "OSGSimpleMaterial.h"

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGSimpleMaterialBase.cpp file.
// To modify it, please change the .fcd file (OSGSimpleMaterial.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/* Create the chunks needed by this Material, one for the material properties,
   one for the optional transparency blending.
 */

void SimpleMaterial::prepareLocalChunks(void)
{
    if(_materialChunk == NULL)
    {
        _materialChunk = MaterialChunk::createLocal();
    }

    if(_blendChunk == NULL)
    {
        _blendChunk    = BlendChunk   ::createLocal();

        _blendChunk->setSrcFactor (GL_SRC_ALPHA);
        _blendChunk->setDestFactor(GL_ONE_MINUS_SRC_ALPHA);
    }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

void SimpleMaterial::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);
}

void SimpleMaterial::resolveLinks(void)
{
    Inherited::resolveLinks();

    _materialChunk = NULL;

    _blendChunk = NULL;
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

SimpleMaterial::SimpleMaterial(void) :
     Inherited    (    ),
    _materialChunk(NULL),
    _blendChunk   (NULL)
{
}

SimpleMaterial::SimpleMaterial(const SimpleMaterial &source) :
     Inherited    (source               ),
    _materialChunk(source._materialChunk),
    _blendChunk   (source._blendChunk   )
{
}

SimpleMaterial::~SimpleMaterial(void)
{
}

void SimpleMaterial::changed(ConstFieldMaskArg whichField, 
                             UInt32            origin,
                             BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

/*-------------------------- your_category---------------------------------*/


void SimpleMaterial::rebuildState(void)
{
	Color3f v3;
	Color4f v4;

	Real32  alpha = 1.f - _sfTransparency.getValue();

    if(_pState != NULL)
    {
        _pState->clearChunks();
    }
    else
    {
        _pState = State::createLocal();

        _pState->setDefaultSortKey(this->getId());
    }

    prepareLocalChunks();

    v3 = _sfAmbient.getValue();
    v4.setValuesRGBA(v3[0], v3[1], v3[2], alpha);

    _materialChunk->setAmbient(v4);

    v3 = _sfDiffuse.getValue();
    v4.setValuesRGBA(v3[0], v3[1], v3[2], alpha);
    
    _materialChunk->setDiffuse(v4);
    
    v3 = _sfSpecular.getValue();
    v4.setValuesRGBA(v3[0], v3[1], v3[2], alpha);
    
    _materialChunk->setSpecular(v4);
    
    _materialChunk->setShininess(_sfShininess.getValue());
    
    v3 = _sfEmission.getValue();
    v4.setValuesRGBA(v3[0], v3[1], v3[2], alpha);
    
    _materialChunk->setEmission(v4);
    
    _materialChunk->setLit          (_sfLit          .getValue());
    _materialChunk->setColorMaterial(_sfColorMaterial.getValue());

    _pState->addChunk(_materialChunk);

    if(isTransparent())
    {
        _pState->addChunk(_blendChunk);
    }

    // XXX DR This is a hack. Should call Inherited ?? GV
    Inherited::addChunks(_pState); 
}

bool SimpleMaterial::isTransparent(void) const
{
    return ((getTransparency() > TypeTraits<Real32>::getDefaultEps()) || 
            (Inherited::isTransparent()                             )   );
}

/*------------------------------- dump ----------------------------------*/

void SimpleMaterial::dump(      UInt32    uiIndent,
                          const BitVector OSG_CHECK_ARG(bvFlags )) const
{
    indentLog(uiIndent, PLOG);
    PLOG << "SimpleMaterial at " << this << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "{" << std::endl;

    uiIndent += 4;

    indentLog(uiIndent, PLOG);
    PLOG << "\tambient: " << getAmbient() << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "\tdiffuse: " << getDiffuse()  << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "\tspecular: " << getSpecular()  << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "\tshininess: " << getShininess()  << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "\temission: " << getEmission()  << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "\ttransparency: " << getTransparency()  << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "\tlit: " << getLit() << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "\tChunks: " << std::endl;

    for(MFUnrecStateChunkPtr::const_iterator i = _mfChunks.begin();
            i != _mfChunks.end(); ++i)
    {
        indentLog(uiIndent, PLOG);
        PLOG << "\t" << *i << std::endl;
    }

    uiIndent -= 4;

    indentLog(uiIndent, PLOG);
    PLOG << "}" << std::endl;
}
