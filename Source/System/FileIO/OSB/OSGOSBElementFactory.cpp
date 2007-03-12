/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                   Copyright (C) 2006 by the OpenSG Forum                  *
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

#include "OSGOSBElementFactory.h"

#include "OSGSingletonHolder.ins"

OSG_USING_NAMESPACE

OSG_BEGIN_NAMESPACE

OSG_SINGLETON_INST(OSG::OSBElementFactorySingleton)

template class SingletonHolder<OSG::OSBElementFactorySingleton>;

OSG_END_NAMESPACE

/*-------------------------------------------------------------------------*/
/* OSBElementCreatorBase                                                  */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

OSBElementCreatorBase::~OSBElementCreatorBase(void)
{
};

/*-------------------------------------------------------------------------*/
/* OSBElementFactorySingleton                                             */
/*-------------------------------------------------------------------------*/

/*! \class OSG::OSBElementFactory

    Singleton registry of the read and write objects for specific object types.
    Maps a type name (usually a field container type name) to an object derived
    from OSBElementCreatorBase. The object is then used to create an object
    derived from OSBElementBase that handles the reading/writing.

    \dev
    OSBElementFactory is only a typedef for
    SingletonHolder\<OSBElementFactorySingleton\> which generates the
    boilerplate code for the singleton.
    \enddev
 */

/*-------------------------------------------------------------------------*/
/* Registration                                                            */

bool
OSBElementFactorySingleton::registerElement(
    const std::string &typeName, OSBElementCreatorBase *creator)
{
    bool          returnValue = true;
    RegistryMapIt it          = _registry.find(typeName);

    if(it != _registry.end())
    {
        FWARNING(("OSBElementFactorySingleton::registerElement: "
                  "typeName: '%s' Registration failed, "
                  "an entry for this type already exists.\n",
                  typeName.c_str()                                ));
        returnValue = false;
    }
    else
    {
        _registry.insert(it, RegistryMap::value_type(typeName, creator));
    }

    return returnValue;
}

bool
OSBElementFactorySingleton::unregisterElement(const std::string &typeName)
{
    bool          returnValue = true;
    RegistryMapIt it          = _registry.find(typeName);

    if(it != _registry.end())
    {
        delete it->second;
        _registry.erase(it);
    }
    else
    {
        FWARNING(("OSBElementFactorySingleton::unregisterElement: "
                  "typeName: '%s' Attempt to unregister an unknown type.\n",
                  typeName.c_str()                                          ));
        returnValue = false;
    }

    return returnValue;
}

bool
OSBElementFactorySingleton::registerDefault(OSBElementCreatorBase *creator)
{
    bool returnValue = true;

    if(_defaultCreator != 0)
    {
        FWARNING(("OSBElementFactorySingleton::registerDefault: "
                  "Registration failed, a default creator exists already.\n"));
        returnValue = false;
    }
    else
    {
        _defaultCreator = creator;
    }

    return returnValue;
}

bool
OSBElementFactorySingleton::unregisterDefault(void)
{
    bool returnValue = true;

    if(_defaultCreator == 0)
    {
        FWARNING(("OSBElementFactorySingleton::unregisterDefault: "
                  "Attempt to unregister empty default creator.\n"));
        returnValue = false;
    }
    else
    {
        delete _defaultCreator;
        _defaultCreator = 0;
    }
    return returnValue;
}

const OSBElementFactorySingleton::RegistryMap &
OSBElementFactorySingleton::getRegistryMap(void) const
{
    return _registry;
}

OSBElementFactorySingleton::RegistryMap &
OSBElementFactorySingleton::editRegistryMap(void)
{
    return _registry;
}

/*-------------------------------------------------------------------------*/
/* Constructor                                                             */

OSBElementFactorySingleton::OSBElementFactorySingleton(void)
    : _registry      ( ),
      _defaultCreator(0)
{
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

OSBElementFactorySingleton::~OSBElementFactorySingleton(void)
{
    // deleting 0 is harmless
    delete _defaultCreator;
}
