/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  Johannes Brunen                                               *
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

#include "OSGMaterialChunkOverrideGroup.h"
#include "OSGRenderAction.h"
#include "OSGChunkMaterial.h"
#include "OSGStateChunk.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGMaterialChunkOverrideGroupBase.cpp file.
// To modify it, please change the .fcd file (OSGMaterialChunkOverrideGroup.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void MaterialChunkOverrideGroup::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        RenderAction::registerEnterDefault(
            MaterialChunkOverrideGroup::getClassType(), 
            reinterpret_cast<Action::Callback>(
                &MaterialChunkOverrideGroup::renderEnter));
        
        RenderAction::registerLeaveDefault(
            MaterialChunkOverrideGroup::getClassType(), 
            reinterpret_cast<Action::Callback>(
                &MaterialChunkOverrideGroup::renderLeave));
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

MaterialChunkOverrideGroup::MaterialChunkOverrideGroup(void) :
    Inherited()
{
}

MaterialChunkOverrideGroup::MaterialChunkOverrideGroup(
    const MaterialChunkOverrideGroup &source) :

    Inherited(source)
{
}

MaterialChunkOverrideGroup::~MaterialChunkOverrideGroup(void)
{
}

/*----------------------------- class specific ----------------------------*/

void MaterialChunkOverrideGroup::changed(ConstFieldMaskArg whichField, 
                                         UInt32            origin,
                                         BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void MaterialChunkOverrideGroup::dump(      UInt32    ,
                                      const BitVector ) const
{
    SLOG << "Dump MaterialChunkOverrideGroup NI" << std::endl;
}

/*-------------------------------------------------------------------------*/
/*                               Render                                    */

ActionBase::ResultE MaterialChunkOverrideGroup::renderEnter(Action *action)
{
    RenderAction *pAction   = dynamic_cast<RenderAction *>(action);
    Material     *pMaterial = this->getMaterial();

    if(pAction != NULL && pMaterial != NULL)
    {
        pMaterial = pMaterial->finalize(pAction->getRenderProperties(),
                                        pAction->getWindow          ());

        if(pMaterial) 
        {
            ChunkMaterial *pChunkMaterial = 
                dynamic_cast<ChunkMaterial*>(pMaterial);

            if(pChunkMaterial != NULL) 
            {
                const MFUnrecStateChunkPtr *chunks = 
                    pChunkMaterial->getMFChunks();

                const MFInt32              *slots  = 
                    pChunkMaterial->getMFSlots();

                for(unsigned int i = 0; i < chunks->size(); ++i) 
                {
                    int slot = i < slots->size() ? 
                        (*slots)[i] : 
                        State::AutoSlotReplace;
                    
                    StateChunk *chunk = (*chunks)[i];
                    
                    if(chunk != NULL)
                        this->addChunk(chunk, slot);
                }

                return Inherited::renderEnter(action);
            } 
            else 
            {
                Action::ResultE r = Group::renderEnter(action);

                // ok all children are culled away so we leave
                // immediately and don't set the material!
                if(r == Action::Skip)
                    return r;

                pAction->overrideMaterial(pMaterial, pAction->getActNode());

                return r;
            }
        }
    }

    return Group::renderEnter(action);
}

ActionBase::ResultE MaterialChunkOverrideGroup::renderLeave(Action *action)
{
    RenderAction *pAction   = dynamic_cast<RenderAction *>(action);
    Material     *pMaterial = this->getMaterial();

    if(pAction != NULL && pMaterial != NULL)
    {
        pMaterial = pMaterial->finalize(pAction->getRenderProperties(),
                                        pAction->getWindow          ());

        if(pMaterial != NULL) 
        {
            ChunkMaterial *pChunkMaterial = 
                dynamic_cast<ChunkMaterial*>(pMaterial);

            if(pChunkMaterial != NULL) 
            {
                ChunkBlockUnrecPtr pBlock = this->finalize(0x0000);

                if(pBlock != NULL)
                    pBlock->clearChunks();
            }

            return Inherited::renderLeave(action);
        } 
        else 
        {
            pAction->overrideMaterial(NULL, pAction->getActNode());
        }
    }

    return Group::renderLeave(action);
}

OSG_END_NAMESPACE
