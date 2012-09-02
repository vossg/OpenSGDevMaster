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
 **     class CSMQT4Window!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"




#include "OSGCSMQT4WindowBase.h"
#include "OSGCSMQT4Window.h"

#include <boost/bind.hpp>

#ifdef WIN32 // turn off 'this' : used in base member initializer list warning
#pragma warning(disable:4355)
#endif

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::CSMQT4Window
    
 */

/***************************************************************************\
 *                        Field Documentation                              *
\***************************************************************************/


/***************************************************************************\
 *                      FieldType/FieldTrait Instantiation                 *
\***************************************************************************/

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
PointerType FieldTraits<CSMQT4Window *, nsOSG>::_type(
    "CSMQT4WindowPtr", 
    "CSMWindowPtr", 
    CSMQT4Window::getClassType(),
    nsOSG);
#endif

OSG_FIELDTRAITS_GETTYPE_NS(CSMQT4Window *, nsOSG)

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField,
                           CSMQT4Window *,
                           nsOSG);

OSG_EXPORT_PTR_MFIELD_FULL(PointerMField,
                           CSMQT4Window *,
                           nsOSG);

/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

void CSMQT4WindowBase::classDescInserter(TypeObject &oType)
{
}


CSMQT4WindowBase::TypeObject CSMQT4WindowBase::_type(
    CSMQT4WindowBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    nsOSG, //Namespace
    reinterpret_cast<PrototypeCreateF>(&CSMQT4WindowBase::createEmptyLocal),
    CSMQT4Window::initMethod,
    CSMQT4Window::exitMethod,
    reinterpret_cast<InitalInsertDescFunc>(&CSMQT4Window::classDescInserter),
    false,
    0,
    "<?xml version=\"1.0\"?>\n"
    "\n"
    "<FieldContainer\n"
    "    name=\"CSMQT4Window\"\n"
    "    parent=\"CSMWindow\"\n"
    "    library=\"ContribCSM\"\n"
    "    pointerfieldtypes=\"both\"\n"
    "    structure=\"concrete\"\n"
    "    systemcomponent=\"true\"\n"
    "    parentsystemcomponent=\"true\"\n"
    "    decoratable=\"false\"\n"
    "    useLocalIncludes=\"false\"\n"
    "    isNodeCore=\"false\"\n"
    "    isBundle=\"true\"\n"
    ">\n"
    "</FieldContainer>\n",
    ""
    );

/*------------------------------ get -----------------------------------*/

FieldContainerType &CSMQT4WindowBase::getType(void)
{
    return _type;
}

const FieldContainerType &CSMQT4WindowBase::getType(void) const
{
    return _type;
}

UInt32 CSMQT4WindowBase::getContainerSize(void) const
{
    return sizeof(CSMQT4Window);
}

/*------------------------- decorator get ------------------------------*/






/*------------------------------ access -----------------------------------*/

SizeT CSMQT4WindowBase::getBinSize(ConstFieldMaskArg whichField)
{
    SizeT returnValue = Inherited::getBinSize(whichField);


    return returnValue;
}

void CSMQT4WindowBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

}

void CSMQT4WindowBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

}

//! create a new instance of the class
CSMQT4WindowTransitPtr CSMQT4WindowBase::createLocal(BitVector bFlags)
{
    CSMQT4WindowTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyLocal(bFlags);

        fc = dynamic_pointer_cast<CSMQT4Window>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class, copy the container flags
CSMQT4WindowTransitPtr CSMQT4WindowBase::createDependent(BitVector bFlags)
{
    CSMQT4WindowTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyDependent(bFlags);

        fc = dynamic_pointer_cast<CSMQT4Window>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class
CSMQT4WindowTransitPtr CSMQT4WindowBase::create(void)
{
    return createLocal();
}

CSMQT4Window *CSMQT4WindowBase::createEmptyLocal(BitVector bFlags)
{
    CSMQT4Window *returnValue;

    newPtr<CSMQT4Window>(returnValue, bFlags);

    returnValue->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

//! create an empty new instance of the class, do not copy the prototype
CSMQT4Window *CSMQT4WindowBase::createEmpty(void)
{
    return createEmptyLocal();
}


FieldContainerTransitPtr CSMQT4WindowBase::shallowCopyLocal(
    BitVector bFlags) const
{
    CSMQT4Window *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const CSMQT4Window *>(this), bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

FieldContainerTransitPtr CSMQT4WindowBase::shallowCopyDependent(
    BitVector bFlags) const
{
    CSMQT4Window *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const CSMQT4Window *>(this), ~bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask = bFlags;

    return returnValue;
}

FieldContainerTransitPtr CSMQT4WindowBase::shallowCopy(void) const
{
    return shallowCopyLocal();
}




/*------------------------- constructors ----------------------------------*/

CSMQT4WindowBase::CSMQT4WindowBase(void) :
    Inherited()
{
}

CSMQT4WindowBase::CSMQT4WindowBase(const CSMQT4WindowBase &source) :
    Inherited(source)
{
}


/*-------------------------- destructors ----------------------------------*/

CSMQT4WindowBase::~CSMQT4WindowBase(void)
{
}



#ifdef OSG_MT_CPTR_ASPECT
void CSMQT4WindowBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    CSMQT4Window *pThis = static_cast<CSMQT4Window *>(this);

    pThis->execSync(static_cast<CSMQT4Window *>(&oFrom),
                    whichField,
                    oOffsets,
                    syncMode,
                    uiSyncInfo);
}
#endif


#ifdef OSG_MT_CPTR_ASPECT
FieldContainer *CSMQT4WindowBase::createAspectCopy(
    const FieldContainer *pRefAspect) const
{
    CSMQT4Window *returnValue;

    newAspectCopy(returnValue,
                  dynamic_cast<const CSMQT4Window *>(pRefAspect),
                  dynamic_cast<const CSMQT4Window *>(this));

    return returnValue;
}
#endif

void CSMQT4WindowBase::resolveLinks(void)
{
    Inherited::resolveLinks();


}


OSG_END_NAMESPACE