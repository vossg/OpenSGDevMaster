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

#include <OSGAction.h>

#include <OSGStateChunk.h>
#include <OSGState.h>
#include <OSGMaterialChunk.h>
#include <OSGImage.h>

#include "OSGSimpleTexturedMaterial.h"

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGSimpleTexturedMaterialBase.cpp file.
// To modify it, please change the .fcd file (OSGSimpleTexturedMaterial.fcd) and
// regenerate the base file.

/*----------------------- constructors & destructors ----------------------*/

SimpleTexturedMaterial::SimpleTexturedMaterial(void) :
     Inherited   (      ),
    _textureChunk(NullFC),
    _texGenChunk (NullFC),
    _texEnvChunk (NullFC)
{
}

SimpleTexturedMaterial::SimpleTexturedMaterial(
    const SimpleTexturedMaterial &source) :

    Inherited    (source              ),
    _textureChunk(source._textureChunk),
    _texGenChunk (source._texGenChunk ),
    _texEnvChunk (source._texEnvChunk )
{
}

SimpleTexturedMaterial::~SimpleTexturedMaterial(void)
{
}

/*----------------------------- class specific ----------------------------*/

void SimpleTexturedMaterial::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);
}

void SimpleTexturedMaterial::resolveLinks(void)
{
    Inherited::resolveLinks();

    subRefLocalVarX(_textureChunk);
    subRefLocalVarX(_texGenChunk );
    subRefLocalVarX(_texEnvChunk );
}

#if defined(OSG_WIN32_ICL) && !defined(OSG_CHECK_FIELDSETARG)
#pragma warning (disable : 383)
#endif

void SimpleTexturedMaterial::changed(ConstFieldMaskArg whichField, 
                                     UInt32            origin,
                                     BitVector         detail)
{
    prepareLocalChunks();

    // these two are very expensive, as they need to regenerate the
    // texture object, do only if really needed

    if(whichField & ImageFieldMask)
    {
        _textureChunk->setImage(getImage());
    }
    if(whichField & MinFilterFieldMask || whichField & MagFilterFieldMask)
    {
        _textureChunk->setMinFilter(getMinFilter());
        _textureChunk->setMagFilter(getMagFilter());
    }
    // this is not as expensive, but why do it more often then needed?
    if(whichField & EnvModeFieldMask)
    {
        _texEnvChunk->setEnvMode(getEnvMode());
    }
    if(whichField & EnvMapFieldMask)
    {
        if (getEnvMap())
        {
#ifndef OSG_WINCE
            _texGenChunk->setGenFuncS(GL_SPHERE_MAP);
            _texGenChunk->setGenFuncT(GL_SPHERE_MAP);
#endif
        }
        else
        {
            _texGenChunk->setGenFuncS(GL_NONE);
            _texGenChunk->setGenFuncT(GL_NONE);
        }
    }

    Inherited::changed(whichField, origin, detail);
}

#if defined(OSG_WIN32_ICL) && !defined(OSG_CHECK_FIELDSETARG)
#pragma warning (default : 383)
#endif

#ifdef OLD
StatePtr SimpleTexturedMaterial::makeState(void)
{
    StatePtr state = Inherited::makeState();

    prepareLocalChunks();

    state->addChunk(_textureChunk);
    state->addChunk(_texGenChunk );
    state->addChunk(_texEnvChunk );

    return state;
}
#endif

void SimpleTexturedMaterial::rebuildState(void)
{
    Inherited::rebuildState();

    prepareLocalChunks();

    _pState->addChunk(_textureChunk);
    _pState->addChunk(_texGenChunk );
    _pState->addChunk(_texEnvChunk );

    if(getImage  ()                    != NullFC &&
       getImage  ()->hasAlphaChannel() == true   && 
       getEnvMode()                    != GL_DECAL)
    {
        if(getImage()->isAlphaBinary())
        {
            if(_blendChunk->getSrcFactor() == GL_SRC_ALPHA)
            {
                _blendChunk->setSrcFactor(GL_ONE);
                _blendChunk->setDestFactor(GL_ZERO);
                _blendChunk->setAlphaFunc(GL_NOTEQUAL);
                _blendChunk->setAlphaValue(0);          
            }
        }
        else
        {
            if(_blendChunk->getSrcFactor() != GL_SRC_ALPHA)
            {
                _blendChunk->setSrcFactor(GL_SRC_ALPHA);
                _blendChunk->setDestFactor(GL_ONE_MINUS_SRC_ALPHA);
                _blendChunk->setAlphaFunc(GL_NONE);
                _blendChunk->setAlphaValue(0);          
            }
        }
    }
}

bool SimpleTexturedMaterial::isTransparent(void) const
{
    return Inherited::isTransparent() ||
           (getImage()!=NullFC &&
             (getImage()->hasAlphaChannel() && getEnvMode() != GL_DECAL)
          );
}

void SimpleTexturedMaterial::dump(     UInt32    OSG_CHECK_ARG(uiIndent),
                                  const BitVector OSG_CHECK_ARG(bvFlags)) const
{
    SLOG << "Dump SimpleTexturedMaterial NI" << std::endl;
}


/* Create the chunks needed by this Material, one for the material properties,
   one for the optional transparency blending.
*/

void SimpleTexturedMaterial::prepareLocalChunks(void)
{
    if(_textureChunk == NullFC)
    {
        _textureChunk = TextureObjChunk::create();

         addRefX(_textureChunk);
    }

    if(_texGenChunk == NullFC)
    {
        _texGenChunk  = TexGenChunk::create();

        addRefX(_texGenChunk);
    }

    if(_texEnvChunk == NullFC)
    {
        _texEnvChunk  = TextureEnvChunk::create();

        addRefX(_texEnvChunk);
    }
}

