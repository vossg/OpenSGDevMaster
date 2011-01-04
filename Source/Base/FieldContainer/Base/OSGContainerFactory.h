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

#ifndef _OSGCONTAINERFACTORY_H_
#define _OSGCONTAINERFACTORY_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGBaseTypes.h"
#include "OSGFactoryController.h"
#include "OSGFactoryBase.h"
#include "OSGLock.h"
#include "OSGThreadManager.h"
#include "OSGLog.h"
#include "OSGContainerForwards.h"

#include "map"
#include "vector"

#ifdef OSG_ENABLE_VALGRIND_CHECKS
#include <valgrind/memcheck.h>
#endif

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpBaseFieldContainerBase
    \ingroup GrpLibOSGBase
 */
template <class DescT>
class ContainerFactory : public FactoryBase
{
    /*==========================  PRIVATE  ================================*/

  private:

    typedef FactoryBase Inherited;

    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                      dcast                                   */
    /*! \{                                                                 */

    typedef DescT                                   Desc;
    typedef ContainerFactory<DescT>                 Self;

    typedef typename Desc     ::ContainerType       ContainerType;
    typedef typename Desc     ::ContainerPtr        ContainerPtr;
    typedef typename Desc     ::ContainerTransitPtr ContainerTransitPtr;
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name        General Fieldcontainer Declaration                    */
    /*! \{                                                                 */

          UInt16  findGroupId  (const Char8  *szName   ) const;
    const Char8  *findGroupName(      UInt16  uiGroupId) const;

          UInt32  getNumGroups (      void             ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    void   registerType (      ContainerType *pType      );
    UInt16 registerGroup(const Char8         *szGroupName);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    ContainerType *findType   (      UInt32  uiTypeId) const;
    ContainerType *findType   (const Char8  *szName  ) const;
    UInt32         getNumTypes(      void            ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    ContainerTransitPtr createContainer(const Char8 *szName);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

#ifdef OSG_1_COMPAT
    ContainerTransitPtr createFieldContainer(const Char8 *szName);
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Set                                     */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   your_category                              */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Container Access                             */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Binary Access                              */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   your_operators                             */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Assignment                                */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Comparison                                */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                  Type information                            */
    /*! \{                                                                 */

    typedef std::map   <UInt32,       ContainerType *>    TypeIdMap;
    typedef std::map   <std::string,  ContainerType *>    TypeNameMap;
    typedef std::map   <std::string,  UInt16         >    GroupMap;

    typedef std::vector<              ContainerType *>    UninitTypeStore;

    typedef typename TypeIdMap      ::iterator            TypeIdMapIt;
    typedef typename TypeNameMap    ::iterator            TypeNameMapIt;
    typedef typename UninitTypeStore::iterator            UninitTypeStoreIt;
    typedef typename GroupMap       ::iterator            GroupMapIt;

    typedef typename TypeIdMap      ::const_iterator      TypeIdMapConstIt;
    typedef typename TypeNameMap    ::const_iterator      TypeNameMapCnstIt;
    typedef typename GroupMap       ::const_iterator      GroupMapConstIt;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Fields                                  */
    /*! \{                                                                 */

    bool             _bInitialized;
    TypeIdMap        _mTypeIdMap;
    TypeNameMap      _mTypeNameMap;

    GroupMap         _mGroupMap;

    UninitTypeStore  _vUnitTypesStore;
    UninitTypeStore  _vPostUnitTypes;

    LockRefPtr       _pLock;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    ContainerFactory(const Char8 *szFactoryName);

    virtual ~ContainerFactory(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Changed                                 */
    /*! \{                                                                 */

    virtual bool initializePendingElements(void);

    virtual bool initialize(void);
    virtual bool terminate (void);

    virtual bool initializeFactoryPost               (void);
    virtual bool initializePendingElementsFactoryPost(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   MT Destruction                             */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    /*!\brief prohibit default function (move to 'public' if needed) */
    ContainerFactory(const ContainerFactory &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const ContainerFactory &source);
};

OSG_END_NAMESPACE

#include "OSGContainerFactory.inl"

#endif /* _OSGCONTAIENRFACTORY_H_ */
