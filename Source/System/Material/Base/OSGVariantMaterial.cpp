/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright(C) 2000-2002 by the OpenSG Forum                   *
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

#include <OSGGL.h>

#include <OSGState.h>
#include <OSGMaterialDrawable.h>

#include "OSGVariantMaterial.h"

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGVariantMaterialBase.cpp file.
// To modify it, please change the .fcd file (OSGVariantMaterial.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

void VariantMaterial::classDescInserter(TypeObject &oType)
{
    Inherited::classDescInserter(oType);
}

void VariantMaterial::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*------------- constructors & destructors --------------------------------*/

VariantMaterial::VariantMaterial(void) :
    Inherited()
{
}

VariantMaterial::VariantMaterial(const VariantMaterial &source) :
    Inherited(source)
{
}

VariantMaterial::~VariantMaterial(void)
{
}

void VariantMaterial::changed(ConstFieldMaskArg whichField, 
                              UInt32            origin,
                              BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}


/*-------------------------- your_category---------------------------------*/

/*------------------------------- dump ----------------------------------*/

void VariantMaterial::dump(      UInt32    OSG_CHECK_ARG(uiIndent),
                           const BitVector OSG_CHECK_ARG(bvFlags )) const
{
    SLOG << "VariantMaterial at " << this << std::endl;
    SLOG << "Chunks: " << std::endl;
   
#if 0
    UInt32 i;

    for(i = 0; i < _mfChunks.size(); ++i)
    {
        SLOG << _mfChunks[i] << " "
             << static_cast<Int32>((i < _mfSlots.size()) 
                                   ? _mfSlots[i]
                                   :   State::AutoSlotReplace)
             << std::endl;
    }
#endif
}


/*-------------------------------------------------------------------------*/
/* Binary access                                                           */

void VariantMaterial::addMaterial(PrimeMaterial  * const pMaterial,
                                  MaterialMapKey         key)
{
    Inherited::addElement(pMaterial, key);
}


void VariantMaterial::subMaterial(MaterialMapKey key)
{
    Inherited::subElement(key);
}

bool VariantMaterial::isTransparent(void) const
{
    return false;
}

const SFMaterialPtrMap *VariantMaterial::getSFMaterialStore(void) const
{
    return Inherited::getMapCacheField();
}
