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

#define OSG_COMPILE_FIELDCONTAINERFACTORY

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#include "OSGFieldContainerFactory.h"
#include "OSGSingletonHolder.ins"
#include "OSGFieldContainerType.h"

OSG_USING_NAMESPACE

OSG_BEGIN_NAMESPACE

OSG_SINGLETON_INST(FieldContainerFactoryBase)

template class SingletonHolder<FieldContainerFactoryBase>;

/*! \class OSG::FieldContainerFactoryBase

This class is a singleton.  It should be accessed using the typedef
for OSG::FieldContainerFactory.
*/


/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

FieldContainerFactoryBase::FieldContainerFactoryBase(void) :
     Inherited      ("FieldContainerFactory"),
    _pStoreLock     (NULL                   ),
    _vContainerStore(                       ),
    _pMapper        (NULL                   )
{
}

FieldContainerFactoryBase::FieldContainerFactoryBase(
    const Char8 *szFactoryName) :

     Inherited      (szFactoryName),
    _pStoreLock     (NULL         ),
    _vContainerStore(             ),
    _pMapper        (NULL         )
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

FieldContainerFactoryBase::~FieldContainerFactoryBase(void)
{
}

/*-------------------------------------------------------------------------*/
/*                             Assignment                                  */

bool FieldContainerFactoryBase::initialize(void)
{
    if(this->_bInitialized == true)
        return true;

#ifndef OSG_WINCE
    _pStoreLock = ThreadManager::the()->getLock("ContainerFactory::slock");

    addRef(_pStoreLock);

    PINFO << "Got store lock " << _pStoreLock << std::endl;

    if(_pStoreLock == NULL)
    {
        return false;
    }
    else
    {
#endif
        return Inherited::initialize();
#ifndef OSG_WINCE
    }
#endif
}

bool FieldContainerFactoryBase::terminate(void)
{
    bool returnValue = Inherited::terminate();

#ifndef OSG_WINCE
    subRef(_pStoreLock);
#endif

    this->_bInitialized = false;

    return returnValue;
}

bool FieldContainerFactoryBase::initializeFactoryPost(void)
{
    return Inherited::initializeFactoryPost();
}

/*-------------------------------------------------------------------------*/
/*                             Comparison                                  */



OSG_END_NAMESPACE


