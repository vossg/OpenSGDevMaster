/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2003 by the OpenSG Forum                          *
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

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include "OSGFieldContainerType.h"
#include "OSGContainerPtrFuncs.h"
#include "OSGFieldContainerFactory.h"
#include "OSGFieldDescriptionBase.h"

#include "OSGNodeCore.h"
#include "OSGNode.h"

OSG_USING_NAMESPACE

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

FieldContainerType::FieldContainerType(bool foo,
    const Char8                *szName,
    const Char8                *szParentName,
    const Char8                *szGroupName,
    const UInt32                uiNameSpace,
          PrototypeCreateF      fPrototypeCreate,
          InitContainerF        fInitMethod,
          InitalInsertDescFunc  descInsertFunc,
          bool                  bDescsAddable) :

     Inherited       (foo, szName,
                      szParentName,
                      szGroupName,
                      uiNameSpace,
                      descInsertFunc,
                      bDescsAddable    ),
    

    _baseType        (IsFieldContainer ),
    _pPrototype      (NullFC           ),
    _fPrototypeCreate(fPrototypeCreate ),
    _fInitMethod     (fInitMethod      )
{
    registerType();

    if(fInitMethod != NULL)
        fInitMethod(Static);
}

FieldContainerType::FieldContainerType(const FieldContainerType &source) :

    Inherited(source),

    _baseType        (source._baseType        ),
    _pPrototype      (source._pPrototype      ),
    _fPrototypeCreate(source._fPrototypeCreate)
{
    if(_pPrototype != NullFC)
        addRef(_pPrototype);
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

FieldContainerType::~FieldContainerType(void)
{
}

FieldContainerPtr FieldContainerType::createContainer(void) const
{
    FieldContainerPtr fc = NullFC;

    if(isAbstract() == false)
    {
        fc = _pPrototype->shallowCopy();
    }

    return fc;
}

#ifdef OSG_MT_CPTR_ASPECT
FieldContainerPtr FieldContainerType::createAspectCopy(void) const
{
    FieldContainerPtr fc = NullFC;

    if(isAbstract() == false)
    {
        fc = _pPrototype->createAspectCopy();
    }

    return fc;
}
#endif

bool FieldContainerType::initialize(void)
{
    if(_bInitialized == true)
        return true;

    if(_fInitMethod != NULL)
        _fInitMethod(SystemPre);

    _bInitialized = Inherited::initialize();

    if(_bInitialized == false)
        return false;

    _bInitialized = initPrototype   ();

    if(_bInitialized == false)
        return false;

    _bInitialized = initBaseType    ();

    if(_fInitMethod != NULL)
        _fInitMethod(SystemPost);

    return _bInitialized;
}

void FieldContainerType::terminate(void)
{
    subRef(_pPrototype);
}

bool FieldContainerType::initialize(InitPhase ePhase)
{
    if(_fInitMethod != NULL)
        _fInitMethod(ePhase);

    return true;
}

bool FieldContainerType::initPrototype(void)
{
    if(_fPrototypeCreate != NULL && _pPrototype == NullFC)
    {
        _pPrototype = _fPrototypeCreate();

        addRef(_pPrototype);
    }

    return true;
}

bool FieldContainerType::initBaseType(void)
{

    if     (isDerivedFrom(NodeCore::getClassType())   == true)
    {
        _baseType = IsNodeCore;
    }
//    else if(isDerivedFrom(Attachment::getClassType()) == true)
//    {
//        _baseType = IsAttachment;
//    }
    else if(isDerivedFrom(Node::getClassType())       == true)
    {
        _baseType = IsNode;
    }

    return true;
}

void FieldContainerType::registerType(void)
{
    FieldContainerFactory::the()->registerType(this);

    _uiGroupId = FieldContainerFactory::the()->registerGroup(
        _szGroupName.str() != NULL ? _szGroupName.str() : _szName.str());
}

/*-------------------------------------------------------------------------*/
/*                                Dump                                     */

void FieldContainerType::dump(      UInt32    OSG_CHECK_ARG(uiIndent),
                              const BitVector OSG_CHECK_ARG(bvFlags )) const
{
    SLOG << "FieldContainerType: "
         << getCName()
         << ", Id: "       
         << getId()
         << ", parentP: " 
         << (_pParentType ? _pParentType->getCName() : "NONE")
         << ", groupId: "  
         << _uiGroupId
         << ", abstract: "
         << ((_pPrototype != NullFC) ? "false" : "true")
         << " "
         << _vDescVec.size()
         << std::endl;

    for(UInt32 i = 0; i < _vDescVec.size(); i++)
    {
        SLOG << "Desc : " << _vDescVec[i]->getCName() << std::endl;
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
    static Char8 cvsid_hpp[] = OSGFIELDCONTAINERTYPE_HEADER_CVSID;
    static Char8 cvsid_inl[] = OSGFIELDCONTAINERTYPE_INLINE_CVSID;
}

