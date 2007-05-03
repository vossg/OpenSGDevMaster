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

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#include <OSGRenderAction.h>
#include <OSGIntersectAction.h>

#include "OSGShadowMapEngine.h"
#include "OSGPassMaskPool.h"
#include "OSGChunkMaterial.h"
#include "OSGMaterialChunk.h"
#include "OSGDataSlotPool.h"

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGShadowMapEngineBase.cpp file.
// To modify it, please change the .fcd file (OSGShadowMapEngine.fcd) and
// regenerate the base file.

BitVector ShadowMapEngine::bvLightPassMask   = 0;
BitVector ShadowMapEngine::bvAmbientPassMask = 0;
BitVector ShadowMapEngine::bvDiffusePassMask = 0;

ChunkMaterialPtr ShadowMapEngine::_pLightPassMat = NullFC;

/*-------------------------------------------------------------------------*/
/*                               Sync                                      */

void ShadowMapEngine::changed(ConstFieldMaskArg whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

/*-------------------------------------------------------------------------*/
/*                               Dump                                      */

void ShadowMapEngine::dump(      UInt32    uiIndent, 
                           const BitVector bvFlags) const
{
   Inherited::dump(uiIndent, bvFlags);
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

ShadowMapEngine::ShadowMapEngine(void) :
     Inherited  (  ),
    _iDataSlotId(-1)

{
}

ShadowMapEngine::ShadowMapEngine(const ShadowMapEngine &source) :
     Inherited  (source),
    _iDataSlotId(    -1)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

ShadowMapEngine::~ShadowMapEngine(void)
{
}

/*-------------------------------------------------------------------------*/
/*                                Init                                     */

void ShadowMapEngine::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);


    if(ePhase == TypeObject::SystemPost)
    {
        bvLightPassMask   = 
            PassMaskPool::the()->get("shadowMapEngine::LightPass");
        bvAmbientPassMask = 
            PassMaskPool::the()->get("shadowMapEngine::AmbientPass");
        bvDiffusePassMask = 
            PassMaskPool::the()->get("shadowMapEngine::DiffusePass");
    }
    else if(ePhase == TypeObject::FactoryPost)
    {
        if(_pLightPassMat == NullFC)
        {
            _pLightPassMat = ChunkMaterial::create();

            MaterialChunkPtr pMatChunk = MaterialChunk::create();

            pMatChunk->setLit          (false  );
            pMatChunk->setColorMaterial(GL_NONE);

            _pLightPassMat->addChunk(pMatChunk);

            _pLightPassMat->changed(FieldBits::AllFields,
                                    ChangedOrigin::Commit);
        }
    }
}

void ShadowMapEngine::onCreateAspect(const ShadowMapEngine *createAspect,
                                     const ShadowMapEngine *source)
{
    Inherited::onCreateAspect(createAspect, source);

    // avoid prototype
    if(GlobalSystemState == Running)
    {
        _iDataSlotId = createAspect->_iDataSlotId;
    }
}

void ShadowMapEngine::onCreate(const ShadowMapEngine *source)
{
    Inherited::onCreate(source);

    // avoid prototype
    if(GlobalSystemState == Running)
    {
        _iDataSlotId = ActionDataSlotPool::the()->create();
        
        fprintf(stderr, "Got data slot %d\n", _iDataSlotId);
    }
}

void ShadowMapEngine::onDestroy(UInt32 uiContainerId)
{
    Inherited::onDestroy(uiContainerId);

    if(GlobalSystemState == Running)
    {
        ActionDataSlotPool::the()->release(_iDataSlotId);
    }
}

/*-------------------------------------------------------------------------*/
/*                              cvs id's                                   */

#ifdef __sgi
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp[] = "@(#)$Id$";
    static Char8 cvsid_hpp[] = OSGSHADOWMAPENGINE_HEADER_CVSID;
    static Char8 cvsid_inl[] = OSGSHADOWMAPENGINE_INLINE_CVSID;
}





