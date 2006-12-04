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

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include <OSGGL.h>

#include <OSGAction.h>

#include <OSGStateChunk.h>
#include <OSGState.h>
#include <OSGMaterialChunk.h>

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
    if(_materialChunk == NullFC)
    {
        _materialChunk = MaterialChunk::create();

        addRef(_materialChunk);
    }

    if(_blendChunk == NullFC)
    {
        _blendChunk    = BlendChunk   ::create();

        _blendChunk->setSrcFactor (GL_SRC_ALPHA);
        _blendChunk->setDestFactor(GL_ONE_MINUS_SRC_ALPHA);

        addRef(_blendChunk);
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
    subRef(_materialChunk);
    subRef(_blendChunk   );    
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

SimpleMaterial::SimpleMaterial(void) :
     Inherited    (      ),
    _materialChunk(NullFC),
    _blendChunk   (NullFC)
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

void SimpleMaterial::changed(ConstFieldMaskArg whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

/*-------------------------- your_category---------------------------------*/

#ifdef OLD
StatePtr SimpleMaterial::makeState(void)
{
    StatePtr state = State::create();

    Color3f v3;
    Color4f v4;

    float alpha = 1.f - getTransparency();

    prepareLocalChunks();

    v3 = getAmbient(); 
    v4.setValuesRGBA(v3[0], v3[1], v3[2], alpha);
    
    _materialChunk->setAmbient(v4);

    v3 = getDiffuse(); 
    v4.setValuesRGBA(v3[0], v3[1], v3[2], alpha);
    
    _materialChunk->setDiffuse(v4);

    v3 = getSpecular(); 
    v4.setValuesRGBA(v3[0], v3[1], v3[2], alpha);
    
    _materialChunk->setSpecular(v4);

    _materialChunk->setShininess(getShininess());

    v3 = getEmission(); 
    v4.setValuesRGBA(v3[0], v3[1], v3[2], alpha);
    
    _materialChunk->setEmission(v4);
        
    _materialChunk->setLit(getLit());
    _materialChunk->setColorMaterial(getColorMaterial());

    state->addChunk(_materialChunk);

    if(isTransparent())
    {
        state->addChunk(_blendChunk);
    }

    for(MFStateChunkPtr::iterator i  = _mfChunks.begin();
                                  i != _mfChunks.end(); 
                                ++i)
    {
        state->addChunk(*i);
    }

    return state;
}
#endif

void SimpleMaterial::rebuildState(void)
{
	Color3r v3;
	Color4r v4;

	Real  alpha = 1.f - getTransparency();

    if(_pState != NullFC)
    {
        _pState->clearChunks();
    }
    else
    {
        SimpleMaterialPtr tmpPtr = 
            Inherited::constructPtr<SimpleMaterial>(this);

        _pState = State::create();

        _pState->setDefaultSortKey(getContainerId(tmpPtr));

        addRef(_pState);
    }

    prepareLocalChunks();

    v3 = getAmbient();
    v4.setValuesRGBA(v3[0], v3[1], v3[2], alpha);

    _materialChunk->setAmbient(v4);

    v3 = getDiffuse();
    v4.setValuesRGBA(v3[0], v3[1], v3[2], alpha);
    
    _materialChunk->setDiffuse(v4);
    
    v3 = getSpecular();
    v4.setValuesRGBA(v3[0], v3[1], v3[2], alpha);
    
    _materialChunk->setSpecular(v4);
    
    _materialChunk->setShininess(getShininess());
    
    v3 = getEmission();
    v4.setValuesRGBA(v3[0], v3[1], v3[2], alpha);
    
    _materialChunk->setEmission(v4);
    
    _materialChunk->setLit(getLit());
    _materialChunk->setColorMaterial(getColorMaterial());

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
    return ((getTransparency() > Eps) || (Inherited::isTransparent()));
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

    for(MFStateChunkPtr::const_iterator i = _mfChunks.begin();
            i != _mfChunks.end(); i++)
    {
        indentLog(uiIndent, PLOG);
        PLOG << "\t" << *i << std::endl;
    }

    uiIndent -= 4;

    indentLog(uiIndent, PLOG);
    PLOG << "}" << std::endl;
}

/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning(disable : 177)
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id$";
    static Char8 cvsid_hpp       [] = OSGSIMPLEMATERIAL_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGSIMPLEMATERIAL_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGSIMPLEMATERIALFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

