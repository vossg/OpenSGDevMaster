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

#ifndef _OSGOSBELEMENTFACTORY_H_
#define _OSGOSBELEMENTFACTORY_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGFileIODef.h"
#include "OSGSingletonHolder.h"
#include "OSGOSBElementBase.h"

#include <map>
#include <string>

OSG_BEGIN_NAMESPACE

class OSBElementBase;
class OSBRootElement;

/*! \ingroup GrpFileIOOSB
    \nohierarchy
 */

struct OSG_FILEIO_DLLMAPPING OSBElementCreatorBase
{
    /*---------------------------------------------------------------------*/
    /*! \name Destructor                                                   */
    /*! \{                                                                 */

    virtual ~OSBElementCreatorBase(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Create/Destroy                                               */
    /*! \{                                                                 */

    virtual OSBElementBase *create(OSBRootElement *root) = 0;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
};

/*! \ingroup GrpFileIOOSB
    \nohierarchy
 */

template <class ElementTypeT>
struct OSBElementCreator : public OSBElementCreatorBase
{
    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
    /*! \{                                                                 */

    typedef ElementTypeT ElementType;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Destructor                                                   */
    /*! \{                                                                 */

    virtual ~OSBElementCreator(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Create/Destroy                                               */
    /*! \{                                                                 */

    virtual OSBElementBase *create(OSBRootElement *root);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
};

/*! \ingroup GrpFileIOOSB
    \nohierarchy
 */

class OSG_FILEIO_DLLMAPPING OSBElementFactorySingleton
{
    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
    /*! \{                                                                 */

    typedef std::map<std::string, OSBElementCreatorBase *> RegistryMap;
    typedef RegistryMap::iterator                          RegistryMapIt;
    typedef RegistryMap::const_iterator                    RegistryMapConstIt;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Registration                                                 */
    /*! \{                                                                 */

    bool registerElement  (const std::string            &typeName,
                                 OSBElementCreatorBase *creator  );
    bool unregisterElement(const std::string &typeName            );

    bool registerDefault  (      OSBElementCreatorBase *creator  );
    bool unregisterDefault(      void                             );

    const RegistryMap &getRegistryMap (void) const;
          RegistryMap &editRegistryMap(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Acquire/Release                                              */
    /*! \{                                                                 */

    inline OSBElementBase *acquire(const std::string     &typeName,
                                         OSBRootElement *root     );
    inline void            release(      OSBElementBase *element  );

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    /*---------------------------------------------------------------------*/
    /*! \name Constructor                                                  */
    /*! \{                                                                 */

    OSBElementFactorySingleton(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Destructor                                                   */
    /*! \{                                                                 */

    ~OSBElementFactorySingleton(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

    template <class SingletonT>
    friend class SingletonHolder;

    RegistryMap             _registry;
    OSBElementCreatorBase *_defaultCreator;
};

/*! \ingroup GrpFileIOOSB
 */

typedef SingletonHolder<OSBElementFactorySingleton> OSBElementFactory;

OSG_END_NAMESPACE

#include "OSGOSBElementFactory.inl"

#endif /* _OSGOSBELEMENTFACTORY_H_ */
