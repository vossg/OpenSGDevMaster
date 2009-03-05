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

    FieldDescriptionBase *pDesc;

    typedef SFMaterialPtrMap::Description SFDesc;

    pDesc = new SFDesc(
        SFMaterialPtrMap::getClassType(),
        "materialStore",
        "material store.",
        OSG_RC_FIELD_DESC(MaterialStore),
        false,
        Field::SFDefaultFlags,
        static_cast<FieldEditMethodSig>(&Self::editHandleMaterialStore),
        static_cast<FieldGetMethodSig >(&Self::getHandleMaterialStore ));

    oType.addInitialDesc(pDesc);
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
     Inherited      (),
    _sfMaterialStore()
{
}

VariantMaterial::VariantMaterial(const VariantMaterial &source) :
     Inherited      (source),
    _sfMaterialStore(      )
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

PrimeMaterial *VariantMaterial::finalize(MaterialMapKey oKey)
{
    return this->findMaterial(oKey);
}

/*------------------------------- dump ----------------------------------*/

void VariantMaterial::dump(      UInt32    OSG_CHECK_ARG(uiIndent),
                           const BitVector OSG_CHECK_ARG(bvFlags )) const
{
    SLOG << "VariantMaterial at " << this << std::endl;
    SLOG << "Chunks: " << std::endl;

    UInt32 i;
    
#if 0
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

UInt32 VariantMaterial::getBinSize(ConstFieldMaskArg whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (MaterialStoreFieldMask & whichField))
    {
        returnValue += _sfMaterialStore.getBinSize();
    }

    return returnValue;
}

void VariantMaterial::copyToBin(BinaryDataHandler  &pMem, 
                                ConstFieldMaskArg   whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (MaterialStoreFieldMask & whichField))
    {
        _sfMaterialStore.copyToBin(pMem);
    }
}

void VariantMaterial::copyFromBin(BinaryDataHandler &pMem, 
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (MaterialStoreFieldMask & whichField))
    {
        _sfMaterialStore.copyFromBin(pMem);
    }
}

void VariantMaterial::addMaterial(PrimeMaterial  * const pMaterial,
                                  MaterialMapKey         key)
{
    if(pMaterial == NULL)
        return;

    if(key == MapKeyPool::the()->getDefault())
    {
        setFallbackMaterial(pMaterial);
        return;
    }

    if(this->isMTLocal())
    {
        pMaterial->addReferenceRecorded();
    }
    else
    {
        pMaterial->addReferenceUnrecorded();
    }

#if 0
    pAttachment->linkParent(this, 
                            AttachmentsFieldId, 
                            Attachment::ParentsFieldId);
#endif

    Self::editSField(MaterialStoreFieldMask);

    MaterialPtrMapIt fcI = _sfMaterialStore.getValue().find(key);

    if(fcI != _sfMaterialStore.getValue().end())
    {
#if 0
        (*fcI).second->unlinkParent(this, 
                                    Attachment::ParentsFieldId);
#endif

        if(this->isMTLocal())
        {
            (*fcI).second->subReferenceRecorded();
        }
        else
        {
            (*fcI).second->subReferenceUnrecorded();
        }

        (*fcI).second = pMaterial;
    }
    else
    {
        _sfMaterialStore.getValue()[key] = pMaterial;
    }
}


void VariantMaterial::subMaterial(MaterialMapKey key)
{
    if(key == MapKeyPool::the()->getDefault())
    {
        setFallbackMaterial(NULL);
        return;
    }

    Self::editSField(MaterialStoreFieldMask);

    MaterialPtrMapIt fcI;

    fcI = _sfMaterialStore.getValue().find(key);

    if(fcI != _sfMaterialStore.getValue().end())
    {
#if 0
        (*fcI).second->unlinkParent(this, 
                                    Attachment::ParentsFieldId);
#endif

        if(this->isMTLocal())
        {
            (*fcI).second->subReferenceRecorded();
        }
        else
        {
            (*fcI).second->subReferenceUnrecorded();
        }

        _sfMaterialStore.getValue().erase(fcI);
    }
}

bool VariantMaterial::isTransparent(void) const
{
    return false;
}

const SFMaterialPtrMap *VariantMaterial::getSFMaterialStore(void) const
{
    return &_sfMaterialStore;
}

#ifdef OSG_MT_CPTR_ASPECT
void VariantMaterial::execSync(
          VariantMaterial   *pFrom,
          ConstFieldMaskArg  whichField,
          AspectOffsetStore &oOffsets,
          ConstFieldMaskArg  syncMode  ,
    const UInt32             uiSyncInfo)
{
    Inherited::execSync(pFrom, whichField, oOffsets, syncMode, uiSyncInfo);

    if(FieldBits::NoField != (MaterialStoreFieldMask & whichField))
    {
//        _sfAttachments.syncWith(pFrom->_sfAttachments);

        // needs optimizing

#if 1
        MaterialMap tmpMap;

        MaterialPtrMapIt fcI = pFrom->_sfMaterialStore.getValue().begin();
        MaterialPtrMapIt fcE = pFrom->_sfMaterialStore.getValue().end  ();
        
        while(fcI != fcE)
        {
            PrimeMaterial *pMat = convertToCurrentAspect((*fcI).second);

            if(pMat != NULL)
            {
                tmpMap[(*fcI).first] = pMat;

                pMat->addReferenceUnrecorded();
            }

            ++fcI;
        }

        fcI = _sfMaterialStore.getValue().begin();
        fcE = _sfMaterialStore.getValue().end  ();

        while(fcI != fcE)
        {
            if(this->isMTLocal())
            {
                (*fcI).second->subReferenceRecorded();
            }
            else
            {
                (*fcI).second->subReferenceUnrecorded();
            }
            
            ++fcI;
        }

        _sfMaterialStore.setValue(tmpMap);
#endif
    }
}
#endif

void VariantMaterial::resolveLinks(void)
{
    Inherited::resolveLinks();

    MaterialPtrMapIt fcI = _sfMaterialStore.getValue().begin();
    MaterialPtrMapIt fcE = _sfMaterialStore.getValue().end  ();

    while(fcI != fcE)
    {
#if 0
        (*fcI).second->unlinkParent(this, 
                                    Material::ParentsFieldId);
#endif

        if(this->isMTLocal())
        {
            (*fcI).second->subReferenceRecorded();
        }
        else
        {
            (*fcI).second->subReferenceUnrecorded();
        }

        ++fcI;
    }

    _sfMaterialStore.getValue().clear();
}

EditFieldHandlePtr VariantMaterial::editHandleMaterialStore(void) 
{
    SFMaterialPtrMap::EditHandlePtr returnValue(
        new  SFMaterialPtrMap::EditHandle(
             &_sfMaterialStore, 
             this->getType().getFieldDesc(MaterialStoreFieldId)));

    returnValue->setAddMethod(boost::bind(&VariantMaterial::addMaterial,
                                          this,
                                          _1,
                                          _2));

    editSField(MaterialStoreFieldMask);

    return returnValue;
}

GetFieldHandlePtr VariantMaterial::getHandleMaterialStore(void) const
{
    SFMaterialPtrMap::GetHandlePtr returnValue(
        new  SFMaterialPtrMap::GetHandle(
             &_sfMaterialStore, 
             this->getType().getFieldDesc(MaterialStoreFieldId)));

    return returnValue;
}

