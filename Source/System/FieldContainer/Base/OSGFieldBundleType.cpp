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

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#include "OSGFieldBundleType.h"
#include "OSGContainerPtrFuncs.h"
#include "OSGFieldBundleFactory.h"

OSG_USING_NAMESPACE

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

FieldBundleType::FieldBundleType(bool foo,
    const Char8                *szName,
    const Char8                *szParentName,
    const Char8                *szGroupName,
    const UInt32                uiNameSpace,
          ProtoBundleCreateF    fPrototypeCreate,
          InitBundleF           fInitMethod,
          InitalInsertDescFunc  descInsertFunc,
          bool                  bDescsAddable) :

     Inherited       (foo, szName,
                      szParentName,
                      szGroupName,
                      uiNameSpace,
                      descInsertFunc,
                      bDescsAddable    ),
    

    _pPrototype      (NULL             ),
    _fPrototypeCreate(fPrototypeCreate )
{
    registerType();

    if(fInitMethod != NULL)
        fInitMethod(Static);
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

FieldBundleType::~FieldBundleType(void)
{
}


bool FieldBundleType::initialize(void)
{
    if(_bInitialized == true)
        return true;

    _bInitialized = Inherited::initialize();

    if(_bInitialized == false)
        return false;

    _bInitialized = initPrototype   ();

    return _bInitialized;
}

void FieldBundleType::terminate(void)
{
    subRef(_pPrototype);
}

bool FieldBundleType::initialize(InitPhase ePhase)
{
//    if(_fInitMethod != NULL)
//        _fInitMethod(ePhase);

    return true;
}

bool FieldBundleType::initPrototype(void)
{
    if(_fPrototypeCreate != NULL)
    {
        _pPrototype = _fPrototypeCreate();

        addRef(_pPrototype);
    }

    return true;
}

void FieldBundleType::registerType(void)
{
    FieldBundleFactory::the()->registerType(this);

    _uiGroupId = FieldBundleFactory::the()->registerGroup(
        _szGroupName.str() != NULL ? _szGroupName.str() : _szName.str());
}

FieldBundleP FieldBundleType::createContainer(void) const
{
    FieldBundleP fp = NilP;

    if(isAbstract() == false)
    {
        fp = _pPrototype->shallowCopy();
    }

    return fp;
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
    static Char8 cvsid_hpp[] = OSGFIELDBUNDLETYPE_HEADER_CVSID;
    static Char8 cvsid_inl[] = OSGFIELDBUNDLETYPE_INLINE_CVSID;
}

