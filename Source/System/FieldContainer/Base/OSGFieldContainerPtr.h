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

#ifndef _OSGFIELDCONTAINERPTR_H_
#define _OSGFIELDCONTAINERPTR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"

#ifdef OSG_MT_FIELDCONTAINERPTR

#include "OSGSystemDef.h"
#include "OSGBaseTypes.h"
#include "OSGBaseInitFunctions.h"
#include "OSGLock.h"
#include "OSGThread.h"
#include "OSGContainerBase.h"
#include "OSGChangeList.h"
#include "OSGReflexiveContainer.h"
#include "OSGThreadManager.h"

OSG_BEGIN_NAMESPACE

class NilFieldContainerPtr;
class FieldContainer;

struct CPointerFuncs;

template<class ContainerFactoryT>
struct CPtrConstructionFunctions;

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 444 )
#endif

//! Brief
//! \ingroup baselib

class OSG_SYSTEM_DLLMAPPING FieldContainerPtrBase 
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef UInt8 *FieldContainerPtrBase::*unspecified_bool_type;

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

    FieldContainerPtrBase(      void                         ); 
    FieldContainerPtrBase(const NilFieldContainerPtr  &      );
    FieldContainerPtrBase(const FieldContainerPtrBase &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    ~FieldContainerPtrBase(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    void   setParentFieldPos(UInt16 uiParentEPos);
    UInt16 getParentFieldPos(void               ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    UInt16 getContainerSize   (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Set                                     */
    /*! \{                                                                 */

    FieldContainer *getBaseCPtr  (void             ) const;
    FieldContainer *getAspectCPtr(UInt32 uiAspectId) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   your_category                              */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Container Access                             */
    /*! \{                                                                 */

#ifdef OSG_1_COMPAT
    Int32  getRefCount(void) const;
#endif

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

    void operator =(const NilFieldContainerPtr  &);
    void operator =(const FieldContainerPtrBase &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Comparison                                */
    /*! \{                                                                 */

    bool operator <  (const NilFieldContainerPtr  &     ) const;
    
    bool operator == (const NilFieldContainerPtr  &other) const;
    bool operator != (const NilFieldContainerPtr  &other) const;


    bool operator <  (const FieldContainerPtrBase &other) const;

    bool operator == (const FieldContainerPtrBase &other) const;
    bool operator != (const FieldContainerPtrBase &other) const;

    bool operator !  (void                              ) const;

         operator unspecified_bool_type(void            ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    void dump(void);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    static       StaticInitFuncWrapper  _initFuncWrapper;
    static       LockPool              *_pRefCountLock;

#ifdef OSG_ASPECT_REFCOUNT
    static const Int32                   ARefCountOffset = - (Int32)
							     (sizeof(Int32) + 
                                                              sizeof(Int32) +
                                                              sizeof(UInt32));
#endif

    static const Int32                   RefCountOffset  = - (Int32)
							     (sizeof(Int32) + 
                                                              sizeof(UInt32));

    static const Int32                   IdOffset        = - (Int32)
							     (sizeof(UInt32));

    /*---------------------------------------------------------------------*/
    /*! \name                  Type information                            */
    /*! \{                                                                 */

    static bool addFCPtrInit(void);

    static bool initialize  (void);
    static bool terminate   (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Fields                                  */
    /*! \{                                                                 */

    UInt16           _containerSize;
    UInt16           _uiParentEPos;
    UInt8           *_storeP;

#ifdef OSG_FCPTR_TYPED_STORE
    FieldContainer *_typedStoreP;
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    FieldContainerPtrBase(const FieldContainer &source,
                          const UInt16          uiSize);
    FieldContainerPtrBase(const FieldContainer *source,
                          const UInt16          uiSize);

    FieldContainerPtrBase(const FieldContainer *source,
                          const UInt16          uiSize,
                          const UInt16          uiParentEPos);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Changed                                 */
    /*! \{                                                                 */

    UInt8  *getMemStart  (void            );
    UInt8  *getMemStart  (void            ) const;

    Int32  *getRefCountP (void            );
    Int32  *getRefCountP (void            ) const;

#ifdef OSG_ASPECT_REFCOUNT
    Int32  *getARefCountP(void            );
    Int32  *getARefCountP(void            ) const;
#endif
    
    UInt32 *getIdP       (void            );    
    UInt32 *getIdP       (void            ) const;    
    
    UInt8  *getFirstElemP(void            );
    UInt8  *getFirstElemP(void            ) const;
    
    UInt8  *getElemP     (UInt32 uiElemNum);
    UInt8  *getElemP     (UInt32 uiElemNum) const;


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   MT Destruction                             */
    /*! \{                                                                 */

    Int32  getMemStartOff  (void            ) const;
    Int32  getRefCountOff  (void            ) const;
#ifdef OSG_ASPECT_REFCOUNT
    Int32  getRefACountOff (void            ) const;
#endif
    Int32  getIdOff        (void            ) const;
    Int32  getFirstElemOff (void            ) const;
    Int32  getElemOff      (UInt32 uiElemNum) const;

    UInt32 getContainerId  (void            ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

    void addReference (void) const;
    void subReference (void) const;

#ifdef OSG_ASPECT_REFCOUNT
    void addAReference(void) const;
    void subAReference(void) const;
#endif

    void setNil(void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class  ChangeList;

    friend struct CPointerFuncs;

    template<class ContainerFactoryT>
    friend struct CPtrConstructionFunctions;
};




//! Brief
//! \ingroup baselib

class OSG_SYSTEM_DLLMAPPING FieldContainerPtr : public FieldContainerPtrBase
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                      dcast                                   */
    /*! \{                                                                 */

    typedef FieldContainer        StoredObject;
    typedef FieldContainerPtr     Self;

    typedef FieldContainerPtrBase Inherited;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name        General Fieldcontainer Declaration                    */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    FieldContainerPtr(      void                        );
    FieldContainerPtr(const NilFieldContainerPtr &      );
    FieldContainerPtr(const FieldContainerPtr    &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */
 
    ~FieldContainerPtr(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    FieldContainer *operator->(void);
    FieldContainer *operator->(void) const;

    FieldContainer &operator *(void);
    FieldContainer &operator *(void) const;
 
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    void operator =(const NilFieldContainerPtr &      );
    void operator =(const FieldContainerPtr    &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Set                                     */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   your_category                              */
    /*! \{                                                                 */

#ifdef OSG_1_COMPAT
    FieldContainer *getCPtr   (void);
    FieldContainer *getCPtr   (void) const;
#endif

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

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Fields                                  */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    FieldContainerPtr(const FieldContainer &source,
                      const UInt16          uiSize);
    FieldContainerPtr(const FieldContainer *source,
                      const UInt16          uiSize);

    FieldContainerPtr(const FieldContainer *source,
                      const UInt16          uiSize,
                      const UInt16          uiParentEPos);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Changed                                 */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   MT Destruction                             */
    /*! \{                                                                 */

#ifndef OSG_1_COMPAT
    FieldContainer *getCPtr   (void);
    FieldContainer *getCPtr   (void) const;
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend struct CPointerFuncs;

    template<class PointerT> 
    friend PointerT cast_dynamic(const FieldContainerPtr in);

    template<class ContainerFactoryT>
    friend struct CPtrConstructionFunctions;
};




/*! ConstFieldContainerPtr, read FieldContainer const * pFieldContainer
    NOT FieldContainer * const pFieldContainer
   \ingroup GrpSystemFieldContainer
 */

class OSG_SYSTEM_DLLMAPPING FieldContainerConstPtr : 
    public FieldContainerPtrBase
{
    /*==========================  PUBLIC  =================================*/
  public:

    typedef FieldContainer        StoredObject;
    typedef FieldContainerPtr     Self;

    typedef FieldContainerPtrBase Inherited;

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

    FieldContainerConstPtr(      void                          );
    FieldContainerConstPtr(const NilFieldContainerPtr   &      );
    FieldContainerConstPtr(const FieldContainerPtr      &source);
    FieldContainerConstPtr(const FieldContainerConstPtr &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    ~FieldContainerConstPtr(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    const FieldContainer *operator->(void);
    const FieldContainer *operator->(void) const;

    const FieldContainer &operator *(void);
    const FieldContainer &operator *(void) const;
 
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

    void operator =(const NilFieldContainerPtr   &       );
    void operator =(const FieldContainerPtr      &source);
    void operator =(const FieldContainerConstPtr &source);

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

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Fields                                  */
    /*! \{                                                                 */

    FieldContainerConstPtr(const FieldContainer &source,
                           const UInt16          uiSize);
    FieldContainerConstPtr(const FieldContainer *source,
                           const UInt16          uiSize);

    FieldContainerConstPtr(const FieldContainer *source,
                           const UInt16          uiSize,
                           const UInt16          uiParentEPos);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Changed                                 */
    /*! \{                                                                 */

    const FieldContainer *getCPtr   (void);
    const FieldContainer *getCPtr   (void) const;

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
};

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 488 )
#endif

template<class PointerT> inline
PointerT cast_dynamic(const FieldContainerPtr in);

#ifdef OSG_LINUX_ICC
#pragma warning( default : 488 )
#endif

//! Brief
//! \ingroup baselib

template <class ParentPtrTypeT, class FieldContainerTypeT> 
class FCPtr : public ParentPtrTypeT
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef ParentPtrTypeT             Inherited;

    typedef FieldContainerTypeT        StoredObject;

    typedef FCPtr<ParentPtrTypeT,
                  FieldContainerTypeT> Self;

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

    FCPtr(      void                        ); 
    FCPtr(const NilFieldContainerPtr &      );
    FCPtr(const FCPtr                &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    ~FCPtr(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    StoredObject *operator->(void);
    StoredObject *operator->(void) const;

    StoredObject &operator *(void);
    StoredObject &operator *(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Set                                     */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   your_category                              */
    /*! \{                                                                 */

#ifdef OSG_1_COMPAT
    template <class InTypeT> inline
    static FCPtr dcast(const InTypeT oIn) 
    {
        return FCPtr(
            (dynamic_cast<const typename FCPtr::StoredObject *>(
                oIn.getCPtr())),
            oIn.getContainerSize(),
            oIn.getParentFieldPos());
    }

    StoredObject *getCPtr   (void);
    StoredObject *getCPtr   (void) const;
#endif


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

    void operator =(const Self                 &source);
    void operator =(const NilFieldContainerPtr &      );

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

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Fields                                  */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    FCPtr(const FieldContainerTypeT &source,
          const UInt16               uiSize);
    FCPtr(const FieldContainerTypeT *source,
          const UInt16               uiSize);
    FCPtr(const FieldContainerTypeT *source,
          const UInt16               uiSize,
          const UInt16               uiParentPos);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Changed                                 */
    /*! \{                                                                 */

#ifndef OSG_1_COMPAT
    StoredObject *getCPtr   (void);
    StoredObject *getCPtr   (void) const;
#endif

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

    friend struct CPointerFuncs;

    template<class ContainerFactoryT>
    friend struct CPtrConstructionFunctions;

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 488 )
#endif
    template<class PointerT> 
    friend PointerT cast_dynamic(const FieldContainerPtr in);
#ifdef OSG_LINUX_ICC
#pragma warning( default : 488 )
#endif

};



//! Brief
//! \ingroup baselib

template <class ParentPtrTypeT, class FieldContainerTypeT> 
class FCConstPtr : public ParentPtrTypeT
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef ParentPtrTypeT                                        Inherited;

    typedef FieldContainerTypeT                                   StoredObject;


    typedef FCPtr<typename FieldContainerTypeT::ObjPtr::Inherited,
                           FieldContainerTypeT                   > NonConstPtr;

    typedef FCConstPtr<ParentPtrTypeT,
                       FieldContainerTypeT>                        Self;

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

    FCConstPtr(      void                        ); 
    FCConstPtr(const NilFieldContainerPtr &      );
    FCConstPtr(const NonConstPtr          &source);
    FCConstPtr(const FCConstPtr           &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    ~FCConstPtr(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    const StoredObject *operator->(void);
    const StoredObject *operator->(void) const;

    const StoredObject &operator *(void);
    const StoredObject &operator *(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Set                                     */
    /*! \{                                                                 */

#ifdef OSG_1_COMPAT
    const StoredObject *getCPtr   (void);
    const StoredObject *getCPtr   (void) const;
#endif

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

    void operator =(const NonConstPtr          &      );
    void operator =(const FCConstPtr           &source);
    void operator =(const NilFieldContainerPtr &source);

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

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Fields                                  */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    FCConstPtr(const FieldContainerTypeT &source,
               const UInt16               uiSize);
    FCConstPtr(const FieldContainerTypeT *source,
               const UInt16               uiSize);
    FCConstPtr(const FieldContainerTypeT *source,
               const UInt16               uiSize,
               const UInt16               uiParentPos);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Changed                                 */
    /*! \{                                                                 */

#ifndef OSG_1_COMPAT
    const StoredObject *getCPtr   (void);
    const StoredObject *getCPtr   (void) const;
#endif

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

    template<class ContainerFactoryT>
    friend struct CPtrConstructionFunctions;
};




//! Brief
//! \ingroup baselib

class OSG_SYSTEM_DLLMAPPING NilFieldContainerPtr : public FieldContainerPtr
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef FieldContainerPtr    Inherited;
    typedef NilFieldContainerPtr Self;

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

    NilFieldContainerPtr(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    ~NilFieldContainerPtr(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

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

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Fields                                  */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

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

    /*!\brief prohibit default function (move to 'public' if needed) */
    NilFieldContainerPtr(const NilFieldContainerPtr &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const NilFieldContainerPtr &source);
};

#ifdef OSG_LINUX_ICC
#pragma warning( default : 444 )
#endif

extern OSG_SYSTEM_DLLMAPPING const NilFieldContainerPtr NullFC;

OSG_SYSTEM_DLLMAPPING
std::ostream &operator <<(      std::ostream      &os,
                          const FieldContainerPtr &fc);

OSG_END_NAMESPACE

#define OSGFIELDCONTAINERPTR_HEADER_CVSID "@(#)$Id: $"

#include "OSGFieldContainerPtr.inl"

#else
#include "OSGContainerForwards.h"
#endif

#include "OSGRefPtr.h"

#endif /* _OSGFIELDCONTAINERPTR_H_ */

