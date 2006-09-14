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

#define OSG_COMPILE_FIELDBUNDLEFACTORY

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include "OSGSingletonHolder.h"
#include "OSGSingletonHolder.ins"

#include "OSGFieldBundleType.h"
#include "OSGFieldBundleFactory.h"

OSG_USING_NAMESPACE

OSG_BEGIN_NAMESPACE

OSG_SINGLETON_INST(FieldBundleFactoryBase)

template class SingletonHolder<FieldBundleFactoryBase>;

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

FieldBundleFactoryBase::FieldBundleFactoryBase(void) :
    Inherited("FieldBundleFactory")
{
}

FieldBundleFactoryBase::FieldBundleFactoryBase(const Char8 *szFactoryName) :
    Inherited(szFactoryName)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

FieldBundleFactoryBase::~FieldBundleFactoryBase(void)
{
}

/*-------------------------------------------------------------------------*/
/*                             Assignment                                  */

bool FieldBundleFactoryBase::initialize(void)
{
    return Inherited::initialize();
}

bool FieldBundleFactoryBase::terminate(void)
{
    return Inherited::terminate();
}

bool FieldBundleFactoryBase::initializeFactoryPost(void)
{
    return Inherited::initializeFactoryPost();
}

/*-------------------------------------------------------------------------*/
/*                             Comparison                                  */


OSG_END_NAMESPACE

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
    static Char8 cvsid_hpp[] = OSGFIELDBUNDLEFACTORY_HEADER_CVSID;
    static Char8 cvsid_inl[] = OSGFIELDBUNDLEFACTORY_INLINE_CVSID;
}

