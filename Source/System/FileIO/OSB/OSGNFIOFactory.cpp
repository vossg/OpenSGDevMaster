/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2000,2001,2002 by the OpenSG Forum                *
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

#include <OSGConfig.h>
#include "OSGNFIOFactory.h"

#include <OSGLog.h>

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::NFIOFactory

           Singleton registry of the read or write objects for specific object type.
           Maps a name (usually FC type name) to an instance of OSGNFIOBase
           that should handle that type.
 */

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/
/*! Singleton instance method.
* Returns the instance of NFIOFactory.
*/
NFIOFactory &NFIOFactory::the(void)
{
    static NFIOFactory factory;
    return factory;
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*------------------------------ constructors -------------------------------*/

NFIOFactory::NFIOFactory(void)
{
}

/*------------------------------ access --------------------------------------*/

void NFIOFactory::add(const std::string &name, NFIOBase *base)
{
    _registry[name] = base;
}

void NFIOFactory::sub(const NFIOBase *base)
{
    std::map<std::string, NFIOBase *>::iterator it;
    for(it=_registry.begin(); it !=_registry.end();++it)
    {
        if(it->second == base)
        {
            _registry.erase(it);
            break;
        }
    }
}

/*! Return NFIOBase that can handle the given type.
* If not found in map, return the generic handler.
*/
NFIOBase *NFIOFactory::get(const std::string &name)
{
    // generic reader/writer.
    static NFIOBase *generic = _registry[""];

    std::map<std::string, NFIOBase *>::iterator it = _registry.find(name);
    if(it != _registry.end())
        return (*it).second;

    return generic;
}

NFIOFactory::registryMap &NFIOFactory::getMap(void)
{
    return _registry;
}
