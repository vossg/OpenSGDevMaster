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

OSG_BEGIN_NAMESPACE

/*-------------------------------------------------------------------------*/
/* OSBElementCreator<ElementTypeT>                                         */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

template <class ElementTypeT>
OSBElementCreator<ElementTypeT>::~OSBElementCreator(void)
{
}

/*-------------------------------------------------------------------------*/
/* Create                                                                  */

template <class ElementTypeT>
OSBElementBase *
OSBElementCreator<ElementTypeT>::create(OSBRootElement *root)
{
    return new ElementType(root);
}

/*-------------------------------------------------------------------------*/
/* OSBElementFactory                                                       */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/* Acquire/Release                                                         */

inline OSBElementBase *
OSBElementFactorySingleton::acquire(
    const std::string &typeName, OSBRootElement *root)
{
    OSBElementBase    *returnValue = 0;
    RegistryMapConstIt  it          = _registry.find(typeName);

    if(it != _registry.end())
    {
        returnValue = it->second->create(root);
    }
    else if(_defaultCreator != 0)
    {
        returnValue = _defaultCreator->create(root);
    }
    else
    {
        FWARNING(("OSBElementFactorySingleton::acquire: No suitable element "
                  "registered for type name: '%s'.\n", typeName.c_str()));
    }

    return returnValue;
}

inline void
OSBElementFactorySingleton::release(OSBElementBase *element)
{
    delete element;
}

OSG_END_NAMESPACE
