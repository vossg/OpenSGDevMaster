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

#ifndef _OSGFIELDCONTAINERFACTORY_H_
#define _OSGFIELDCONTAINERFACTORY_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGBaseTypes.h"
#include "OSGDeprecatedCPP.h"
#include "OSGSingletonHolder.h"
#include "OSGContainerForwards.h"
#include "OSGTypeBase.h"
#include "OSGContainerFactory.h"
#include "OSGAspectStore.h"
#include "OSGContainerIdMapper.h"


#include <deque>

OSG_BEGIN_NAMESPACE

class FieldContainerFactoryBase;

/*! \ingroup GrpBaseFieldContainerBase
    \ingroup GrpLibOSGBase
    \nohierarchy
 */
struct FieldContainerFactoryDesc
{
    typedef FieldContainerType        ContainerType;
    typedef FieldContainer           *ContainerPtr;
    typedef FieldContainerTransitPtr  ContainerTransitPtr;

    static const Char8 *getContainerFactoryLockName(void)
    {
        return "ContainerFactory::cflock";
    }
};

/*! \brief Accessible via #TypeFactory
    \ingroup GrpBaseBaseTypeSystem
    \ingroup GrpBaseBase
    \ingroup GrpLibOSGBase
    \nohierarchy
 */

class OSG_BASE_DLLMAPPING DerivedFieldContainerTypeIterator
{
  public:

    DerivedFieldContainerTypeIterator(
        const DerivedFieldContainerTypeIterator &source);

    FieldContainerType *operator->(void);
    FieldContainerType *operator *(void);

    void operator++ (void);

    bool operator ==(const DerivedFieldContainerTypeIterator &lhs);
    bool operator !=(const DerivedFieldContainerTypeIterator &lhs);

  protected:

    DerivedFieldContainerTypeIterator(void);
    DerivedFieldContainerTypeIterator(const FieldContainerType &oRef); 

    void operator =(const DerivedFieldContainerTypeIterator &source);

    const FieldContainerType *_pRef;
          UInt32              _uiCurrentType;
          FieldContainerType *_pCurrentType;

    friend class FieldContainerFactoryBase;
};

/*! \brief FieldContainerFactoryBase is the central class in OpenSG for 
           accessing, allocating, and mapping field containers allocated in
           the system. Accessible via #FieldContainerFactory
    \ingroup GrpBaseFieldContainerBase
    \ingroup GrpLibOSGBase
 */
class OSG_BASE_DLLMAPPING FieldContainerFactoryBase :
    public ContainerFactory<FieldContainerFactoryDesc>
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef FieldContainer                *ContainerPtr;
#ifdef OSG_MT_CPTR_ASPECT
    typedef AspectStoreP                   ContainerHandlerP;
#else
    typedef FieldContainer                *ContainerHandlerP;
#endif

    typedef OSG_HASH_MAP(UInt32, ContainerHandlerP)  ContainerStore;
    typedef ContainerStore::iterator                 ContainerStoreIt;
    typedef ContainerStore::const_iterator           ContainerStoreConstIt;

    /*---------------------------------------------------------------------*/
    /*! \name                      dcast                                   */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name        General Fieldcontainer Declaration                    */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    void setMapper(ContainerIdMapper *pMapper);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    UInt32            getNumLiveContainers (void                ) const;
    UInt32            getNumTotalContainers(void                ) const;

    ContainerPtr      getContainer         (UInt32 uiContainerId) const;
    ContainerHandlerP getContainerHandler  (UInt32 uiContainerId) const;

    ContainerPtr      getMappedContainer   (UInt32 uiContainerId) const;

    Int32             findContainer        (ContainerPtr ptr    ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    void                  lockStore  (void);
    void                  unlockStore(void);

    ContainerStoreConstIt beginStore (void) const;
    ContainerStoreConstIt endStore   (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Registration                                */
    /*! \{                                                                 */

    UInt32 registerContainer  (const ContainerPtr &pContainer   );
    bool   deregisterContainer(const UInt32        uiContainerId);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Set                                     */
    /*! \{                                                                 */

    void dump(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   your_category                              */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Container Access                             */
    /*! \{                                                                 */

    DerivedFieldContainerTypeIterator begin(const FieldContainerType &oRef);
    DerivedFieldContainerTypeIterator end  (      void                    );

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

    template <class SingletonT>
    friend class SingletonHolder;

    friend class FactoryControllerBase;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Fields                                  */
    /*! \{                                                                 */

    LockRefPtr         _pStoreLock;

    UInt32             _nextContainerId;
    ContainerStore     _containerStore;

    /*! Currently active field container mapper. */
    ContainerIdMapper *_pMapper;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    FieldContainerFactoryBase(void);
    FieldContainerFactoryBase(const Char8 *szFactoryName);

    virtual ~FieldContainerFactoryBase(void);

    virtual bool initialize           (void);
    virtual bool terminate            (void);

    virtual bool initializeFactoryPost(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Changed                                 */
    /*! \{                                                                 */

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

    typedef ContainerFactory<FieldContainerFactoryDesc> Inherited;


    /*!\brief prohibit default function (move to 'public' if needed) */
    FieldContainerFactoryBase(const FieldContainerFactoryBase &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const FieldContainerFactoryBase &source);
};

/*! \typedef OSG::SingletonHolder<OSG::FieldContainerFactoryBase> FieldContainerFactory;
    \ingroup GrpBaseFieldContainerBase
    \relatesalso OSG::FieldContainerFactoryBase
 */

typedef OSG::SingletonHolder<
            OSG::FieldContainerFactoryBase> FieldContainerFactory;

OSG_END_NAMESPACE

#include "OSGFieldContainerFactory.inl"

#endif /* _OSGFIELDCONTAINERFACTORY_H_ */
