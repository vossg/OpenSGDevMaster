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

/*****************************************************************************\
 *****************************************************************************
 **                                                                         **
 **                  This file is automatically generated.                  **
 **                                                                         **
 **          Any changes made to this file WILL be lost when it is          **
 **           regenerated, which can become necessary at any time.          **
 **                                                                         **
 **     Do not change this file, changes should be done in the derived      **
 **     class ChunkMaterial!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#define OSG_COMPILECHUNKMATERIALINST

#include <stdlib.h>
#include <stdio.h>
#include <boost/assign/list_of.hpp>

#include <OSGConfig.h>



#include <OSGStateChunk.h> // Chunks Class

#include "OSGChunkMaterialBase.h"
#include "OSGChunkMaterial.h"

OSG_USING_NAMESPACE

// Field descriptions

/*! \var StateChunkPtr ChunkMaterialBase::_mfChunks
    
*/
/*! \var Int32 ChunkMaterialBase::_mfSlots
    
*/

void ChunkMaterialBase::classDescInserter(TypeObject &oType)
{
    FieldDescriptionBase *pDesc = NULL; 


    pDesc = new MFStateChunkPtr::Description(
        MFStateChunkPtr::getClassType(), 
        "chunks", 
        "",
        ChunksFieldId, ChunksFieldMask,
        false,
        Field::MFDefaultFlags,
        static_cast     <FieldEditMethodSig>(&ChunkMaterialBase::invalidEditField),
        reinterpret_cast<FieldGetMethodSig >(&ChunkMaterialBase::getMFChunks));

    oType.addInitialDesc(pDesc);

#ifdef OSG_1_COMPAT
    typedef const MFInt32 *(ChunkMaterialBase::*GetMFSlotsF)(void) const;

    GetMFSlotsF GetMFSlots = &ChunkMaterialBase::getMFSlots;
#endif

    pDesc = new MFInt32::Description(
        MFInt32::getClassType(), 
        "slots", 
        "",
        SlotsFieldId, SlotsFieldMask,
        false,
        Field::MFDefaultFlags,
        reinterpret_cast<FieldEditMethodSig>(&ChunkMaterialBase::editMFSlots),
#ifdef OSG_1_COMPAT
        reinterpret_cast<FieldGetMethodSig >(GetMFSlots));
#else
        reinterpret_cast<FieldGetMethodSig >(&ChunkMaterialBase::getMFSlots));
#endif

    oType.addInitialDesc(pDesc);
}


ChunkMaterialBase::TypeObject ChunkMaterialBase::_type(true,
    ChunkMaterialBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    0,
    (PrototypeCreateF) &ChunkMaterialBase::createEmpty,
    ChunkMaterial::initMethod,
    (InitalInsertDescFunc) &ChunkMaterialBase::classDescInserter,
    false,
    "<?xml version=\"1.0\" ?>\n"
"\n"
"<FieldContainer\n"
"	name=\"ChunkMaterial\"\n"
"	parent=\"Material\"\n"
"	library=\"System\"\n"
"	structure=\"concrete\"\n"
"	pointerfieldtypes=\"both\"\n"
"	systemcomponent=\"true\"\n"
"	parentsystemcomponent=\"true\"\n"
">\n"
"	<Field\n"
"		name=\"chunks\"\n"
"		type=\"StateChunkPtr\"\n"
"		cardinality=\"multi\"\n"
"		visibility=\"external\"\n"
"        clearField=\"clearChunks\"\n"
"	>\n"
"	</Field>\n"
"	<Field\n"
"		name=\"slots\"\n"
"		type=\"Int32\"\n"
"		cardinality=\"multi\"\n"
"		visibility=\"external\"\n"
"	>\n"
"	</Field>\n"
"</FieldContainer>\n"
,
    "" 
    );

/*------------------------------ get -----------------------------------*/

FieldContainerType &ChunkMaterialBase::getType(void) 
{
    return _type; 
} 

const FieldContainerType &ChunkMaterialBase::getType(void) const 
{
    return _type;
} 

UInt32 ChunkMaterialBase::getContainerSize(void) const 
{ 
    return sizeof(ChunkMaterial); 
}

/*------------------------- decorator get ------------------------------*/


//! Get the ChunkMaterial::_mfChunks field.
const MFStateChunkPtr *ChunkMaterialBase::getMFChunks(void) const
{
    return &_mfChunks;
}

MFInt32 *ChunkMaterialBase::editMFSlots(void)
{
    editMField(SlotsFieldMask, _mfSlots);

    return &_mfSlots;
}

const MFInt32 *ChunkMaterialBase::getMFSlots(void) const
{
    return &_mfSlots;
}

#ifdef OSG_1_COMPAT
MFInt32 *ChunkMaterialBase::getMFSlots(void)
{
    return this->editMFSlots();
}
#endif


void ChunkMaterialBase::pushToField(      FieldContainerPtrConstArg pNewElement,
                                    const UInt32                    uiFieldId  )
{
    Inherited::pushToField(pNewElement, uiFieldId);

    if(uiFieldId == ChunksFieldId)
    {
        static_cast<ChunkMaterial *>(this)->pushToChunks(
            cast_dynamic<StateChunkPtr>(pNewElement));
    }
}

void ChunkMaterialBase::insertIntoMField(const UInt32                    uiIndex,
                                               FieldContainerPtrConstArg pNewElement,
                                         const UInt32                    uiFieldId  )
{
    Inherited::insertIntoMField(uiIndex, pNewElement, uiFieldId);

    if(uiFieldId == ChunksFieldId)
    {
        static_cast<ChunkMaterial *>(this)->insertIntoChunks(
            uiIndex,
            cast_dynamic<StateChunkPtr>(pNewElement));
    }
}

void ChunkMaterialBase::replaceInMField (const UInt32                    uiIndex,
                                               FieldContainerPtrConstArg pNewElement,
                                         const UInt32                    uiFieldId)
{
    Inherited::replaceInMField(uiIndex, pNewElement, uiFieldId);

    if(uiFieldId == ChunksFieldId)
    {
        static_cast<ChunkMaterial *>(this)->replaceInChunks(
            uiIndex,
            cast_dynamic<StateChunkPtr>(pNewElement));
    }
}

void ChunkMaterialBase::replaceInMField (      FieldContainerPtrConstArg pOldElement,
                                               FieldContainerPtrConstArg pNewElement,
                                         const UInt32                    uiFieldId  )
{
    Inherited::replaceInMField(pOldElement, pNewElement, uiFieldId);

    if(uiFieldId == ChunksFieldId)
    {
        static_cast<ChunkMaterial *>(this)->replaceInChunks(
            cast_dynamic<StateChunkPtr>(pOldElement),
            cast_dynamic<StateChunkPtr>(pNewElement));
    }
}

void ChunkMaterialBase::removeFromMField(const UInt32 uiIndex,
                                         const UInt32 uiFieldId)
{
    Inherited::removeFromMField(uiIndex, uiFieldId);

    if(uiFieldId == ChunksFieldId)
    {
        static_cast<ChunkMaterial *>(this)->removeFromChunks(
            uiIndex);
    }
}

void ChunkMaterialBase::removeFromMField(      FieldContainerPtrConstArg pElement,
                                         const UInt32                    uiFieldId)
{
    Inherited::removeFromMField(pElement, uiFieldId);

    if(uiFieldId == ChunksFieldId)
    {
        static_cast<ChunkMaterial *>(this)->removeFromChunks(
            cast_dynamic<StateChunkPtr>(pElement));
    }
}

void ChunkMaterialBase::clearField(const UInt32 uiFieldId)
{
    Inherited::clearField(uiFieldId);

    if(uiFieldId == ChunksFieldId)
    {
        static_cast<ChunkMaterial *>(this)->clearChunks();
    }
}

void ChunkMaterialBase::pushToChunks(StateChunkPtrConstArg value)
{
    if(value == NullFC)
        return;

    editMField(ChunksFieldMask, _mfChunks);

    addRef(value);

    _mfChunks.push_back(value);
}

void ChunkMaterialBase::insertIntoChunks(UInt32                uiIndex,
                                             StateChunkPtrConstArg value   )
{
    if(value == NullFC)
        return;

    editMField(ChunksFieldMask, _mfChunks);

    MFStateChunkPtr::iterator fieldIt = _mfChunks.begin();

    addRef(value);

    fieldIt += uiIndex;

    _mfChunks.insert(fieldIt, value);
}

void ChunkMaterialBase::replaceInChunks(UInt32                uiIndex,
                                                 StateChunkPtrConstArg value   )
{
    if(value == NullFC)
        return;

    if(uiIndex >= _mfChunks.size())
        return;

    editMField(ChunksFieldMask, _mfChunks);

    addRef(value);

    subRef(_mfChunks[uiIndex]);

    _mfChunks[uiIndex] = value;
}

void ChunkMaterialBase::replaceInChunks(StateChunkPtrConstArg pOldElem,
                                                  StateChunkPtrConstArg pNewElem)
{
    if(pNewElem == NullFC)
        return;

    Int32  elemIdx = _mfChunks.findIndex(pOldElem);

    if(elemIdx != -1)
    {
        editMField(ChunksFieldMask, _mfChunks);

        MFStateChunkPtr::iterator fieldIt = _mfChunks.begin();

        fieldIt += elemIdx;

        addRef(pNewElem);
        subRef(pOldElem);

        (*fieldIt) = pNewElem;
    }
}

void ChunkMaterialBase::removeFromChunks(UInt32 uiIndex)
{
    if(uiIndex < _mfChunks.size())
    {
        editMField(ChunksFieldMask, _mfChunks);

        MFStateChunkPtr::iterator fieldIt = _mfChunks.begin();

        fieldIt += uiIndex;

        subRef(*fieldIt);

        _mfChunks.erase(fieldIt);
    }
}

void ChunkMaterialBase::removeFromChunks(StateChunkPtrConstArg value)
{
    Int32 iElemIdx = _mfChunks.findIndex(value);

    if(iElemIdx != -1)
    {
        editMField(ChunksFieldMask, _mfChunks);

        MFStateChunkPtr::iterator fieldIt = _mfChunks.begin();

        fieldIt += iElemIdx;

        subRef(*fieldIt);

        _mfChunks.erase(fieldIt);
    }
}



/*********************************** Non-ptr code ********************************/
void ChunkMaterialBase::pushToSlots(const Int32& value)
{
    editMField(SlotsFieldMask, _mfSlots);
    _mfSlots.push_back(value);
}

void ChunkMaterialBase::insertIntoSlots(UInt32                uiIndex,
                                             const Int32& value   )
{
    editMField(SlotsFieldMask, _mfSlots);

    MFInt32::iterator fieldIt = _mfSlots.begin();

    fieldIt += uiIndex;

    _mfSlots.insert(fieldIt, value);
}

void ChunkMaterialBase::replaceInSlots(UInt32                uiIndex,
                                                 const Int32& value   )
{
    if(uiIndex >= _mfSlots.size())
        return;

    editMField(SlotsFieldMask, _mfSlots);

    _mfSlots[uiIndex] = value;
}

void ChunkMaterialBase::replaceInSlots(const Int32& pOldElem,
                                                  const Int32& pNewElem)
{
    Int32  elemIdx = _mfSlots.findIndex(pOldElem);

    if(elemIdx != -1)
    {
        editMField(SlotsFieldMask, _mfSlots);

        MFInt32::iterator fieldIt = _mfSlots.begin();

        fieldIt += elemIdx;

        (*fieldIt) = pNewElem;
    }
}

void ChunkMaterialBase::removeFromSlots(UInt32 uiIndex)
{
    if(uiIndex < _mfSlots.size())
    {
        editMField(SlotsFieldMask, _mfSlots);

        MFInt32::iterator fieldIt = _mfSlots.begin();

        fieldIt += uiIndex;
        _mfSlots.erase(fieldIt);
    }
}

void ChunkMaterialBase::removeFromSlots(const Int32& value)
{
    Int32 iElemIdx = _mfSlots.findIndex(value);

    if(iElemIdx != -1)
    {
        editMField(SlotsFieldMask, _mfSlots);

        MFInt32::iterator fieldIt = _mfSlots.begin();

        fieldIt += iElemIdx;

        _mfSlots.erase(fieldIt);
    }
}
void ChunkMaterialBase::clearSlots(void)
{
    editMField(SlotsFieldMask, _mfSlots);

    _mfSlots.clear();
}









/*------------------------------ access -----------------------------------*/

UInt32 ChunkMaterialBase::getBinSize(ConstFieldMaskArg whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (ChunksFieldMask & whichField))
    {
        returnValue += _mfChunks.getBinSize();
    }
    if(FieldBits::NoField != (SlotsFieldMask & whichField))
    {
        returnValue += _mfSlots.getBinSize();
    }

    return returnValue;
}

void ChunkMaterialBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (ChunksFieldMask & whichField))
    {
        _mfChunks.copyToBin(pMem);
    }
    if(FieldBits::NoField != (SlotsFieldMask & whichField))
    {
        _mfSlots.copyToBin(pMem);
    }
}

void ChunkMaterialBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (ChunksFieldMask & whichField))
    {
        _mfChunks.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (SlotsFieldMask & whichField))
    {
        _mfSlots.copyFromBin(pMem);
    }
}

//! create an empty new instance of the class, do not copy the prototype
ChunkMaterialPtr ChunkMaterialBase::createEmpty(void) 
{ 
    ChunkMaterialPtr returnValue; 
    
    newPtr<ChunkMaterial>(returnValue); 

    return returnValue; 
}

FieldContainerPtr ChunkMaterialBase::shallowCopy(void) const 
{ 
    ChunkMaterialPtr returnValue; 

    newPtr(returnValue, dynamic_cast<const ChunkMaterial *>(this)); 

    return returnValue; 
}



/*------------------------- constructors ----------------------------------*/

ChunkMaterialBase::ChunkMaterialBase(void) :
    Inherited(),
    _mfChunks(),
    _mfSlots()
{
}

ChunkMaterialBase::ChunkMaterialBase(const ChunkMaterialBase &source) :
    Inherited(source),
    _mfChunks(),
    _mfSlots(source._mfSlots)
{
}

/*-------------------------- destructors ----------------------------------*/

ChunkMaterialBase::~ChunkMaterialBase(void)
{
}

void ChunkMaterialBase::onCreate(const ChunkMaterial *source)
{
    Inherited::onCreate(source);

    if(source != NULL)
    {

        MFStateChunkPtr::const_iterator ChunksIt  = 
            source->_mfChunks.begin();
        MFStateChunkPtr::const_iterator ChunksEnd = 
            source->_mfChunks.end  ();

        while(ChunksIt != ChunksEnd)
        {
            this->pushToChunks(*ChunksIt);

            ++ChunksIt;
        }
    }
}

#ifdef OSG_MT_FIELDCONTAINERPTR
void ChunkMaterialBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        ConstFieldMaskArg  syncMode  ,
                                  const UInt32             uiSyncInfo,
                                        UInt32             uiCopyOffset)
{
    this->execSync(static_cast<ChunkMaterialBase *>(&oFrom),
                   whichField, 
                   syncMode, 
                   uiSyncInfo,
                   uiCopyOffset);
}
#endif

#ifdef OSG_MT_CPTR_ASPECT
void ChunkMaterialBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode  ,
                                  const UInt32             uiSyncInfo)
{
    this->execSync(static_cast<ChunkMaterialBase *>(&oFrom), 
                   whichField,
                   oOffsets,
                   syncMode,
                   uiSyncInfo);
}
#endif

#if 0
void ChunkMaterialBase::execBeginEditV(ConstFieldMaskArg whichField,
                                       UInt32            uiAspect,
                                       UInt32            uiContainerSize)
{
    this->execBeginEdit(whichField, uiAspect, uiContainerSize);
}
#endif

#ifdef OSG_MT_CPTR_ASPECT
FieldContainerPtr ChunkMaterialBase::createAspectCopy(void) const
{
    ChunkMaterialPtr returnValue; 

    newAspectCopy(returnValue, 
                  dynamic_cast<const ChunkMaterial *>(this)); 

    return returnValue; 
}
#endif

void ChunkMaterialBase::resolveLinks(void)
{
    Inherited::resolveLinks();

    static_cast<ChunkMaterial *>(this)->clearChunks();
}


#include "OSGSField.ins"
#include "OSGMField.ins"

#if defined(OSG_TMPL_STATIC_MEMBER_NEEDS_FUNCTION_INSTANTIATION) || \
    defined(OSG_TMPL_STATIC_MEMBER_NEEDS_CLASS_INSTANTIATION   )

#include "OSGSFieldFuncs.ins"
#include "OSGMFieldFuncs.ins"
#endif

OSG_BEGIN_NAMESPACE

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
DataType FieldTraits<ChunkMaterialPtr>::_type("ChunkMaterialPtr", "MaterialPtr");
#endif

OSG_FIELDTRAITS_GETTYPE(ChunkMaterialPtr)

OSG_FIELD_DLLEXPORT_DEF1(SField, ChunkMaterialPtr);
OSG_FIELD_DLLEXPORT_DEF1(MField, ChunkMaterialPtr);

OSG_END_NAMESPACE


/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id$";
    static Char8 cvsid_hpp       [] = OSGCHUNKMATERIALBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGCHUNKMATERIALBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGCHUNKMATERIALFIELDS_HEADER_CVSID;
}
