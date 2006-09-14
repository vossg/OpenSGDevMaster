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
#include "OSGSystemDef.h"
#include "OSGSingletonHolder.h"
#include "OSGContainerForwards.h"
#include "OSGContainerFactoryMixins.h"
#include "OSGFieldContainerPtr.h"
#include "OSGAspectStore.h"

#ifdef OSG_MT_CPTR_ASPECT
#include "OSGFieldContainer.h"
#endif

OSG_BEGIN_NAMESPACE

struct OSG_SYSTEM_DLLMAPPING FieldContainerMapper
{
    virtual ~FieldContainerMapper();

    virtual UInt32 map(UInt32 uiId) = 0;
};

#ifdef OSG_MT_CPTR_ASPECT
struct HandledFieldContainerFactoryDesc
{
    typedef FieldContainerType ContainerType;
    typedef FieldContainerPtr  ContainerPtr;
    typedef AspectStoreP       ContainerHandler;

    static Char8 *getContainerFactoryLockName(void)
    {
        return "ContainerFactory::cflock";
    }

    static Char8 *getStoreLockName(void)
    {
        return "ContainerFactoryFactory::slock";
    }

    static NilFieldContainerReturnType getNilPtr(void)
    {
        return NULL;
    }

    static AspectStoreP getHandler(const FieldContainerPtr pContainer)
    {
        if(pContainer == NULL)
        {
            return NULL;
        }
        else
        {
            return pContainer->getAspectStore();
        }
    }
};
#else
struct FieldContainerFactoryDesc
{
    typedef FieldContainerType ContainerType;
    typedef FieldContainerPtr  ContainerPtr;

    static Char8 *getContainerFactoryLockName(void)
    {
        return "ContainerFactory::cflock";
    }

    static Char8 *getStoreLockName(void)
    {
        return "ContainerFactoryFactory::slock";
    }

    static NilFieldContainerReturnType getNilPtr(void)
    {
        return NullFC;
    }
};
#endif

/*! \ingroup GrpSystemFieldContainer
 */

class OSG_SYSTEM_DLLMAPPING FieldContainerFactoryBase : 
    public FieldContainerFactoryParent
{
    /*==========================  PUBLIC  =================================*/

  public:

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

    void              setMapper         (FieldContainerMapper *pMapper);
        
    FieldContainerPtr getMappedContainer(UInt32 uiContainerId) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

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

    template <class SingletonT>
    friend class SingletonHolder;

    friend class FactoryControllerBase;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Fields                                  */
    /*! \{                                                                 */

    FieldContainerMapper *_pMapper;

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

    typedef FieldContainerFactoryParent Inherited;


    /*!\brief prohibit default function (move to 'public' if needed) */
    FieldContainerFactoryBase(const FieldContainerFactoryBase &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const FieldContainerFactoryBase &source);
};

#if defined(WIN32)
#    if !defined(OSG_COMPILE_FIELDCONTAINERFACTORY)
//OSG_SYSTEM_EXPIMP_TMPL 
//template 
//class OSG_SYSTEM_DLLMAPPING SingletonHolder<FieldContainerFactoryBase>;
#    endif
#endif

typedef SingletonHolder<FieldContainerFactoryBase> FieldContainerFactory;

OSG_END_NAMESPACE

#define OSGFIELDCONTAINERFACTORY_HEADER_CVSID "@(#)$Id$"

#include "OSGFieldContainerFactory.inl"

#endif /* _OSGFIELDCONTAINERFACTORY_H_ */
