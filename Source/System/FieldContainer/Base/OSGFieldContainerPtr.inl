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

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*-------------------------------------------------------------------------*/
/*                         Get Memory Locations                            */

inline
UInt8 *FieldContainerPtrBase::getMemStart(void)
{
#ifdef OSG_ASPECT_REFCOUNT
    return (_storeP + ARefCountOffset);
#else
    return (_storeP + RefCountOffset);
#endif
}

inline
UInt8 *FieldContainerPtrBase::getMemStart(void) const
{
#ifdef OSG_ASPECT_REFCOUNT
    return (_storeP + ARefCountOffset);
#else
    return (_storeP + RefCountOffset);
#endif
}

inline
Int32 *FieldContainerPtrBase::getRefCountP(void)
{
    return (Int32 *) (_storeP + RefCountOffset);
}

inline
Int32 *FieldContainerPtrBase::getRefCountP(void) const
{
    return (Int32 *) (_storeP + RefCountOffset);
}

#ifdef OSG_ASPECT_REFCOUNT
inline
Int32 *FieldContainerPtrBase::getARefCountP(void)
{
    return (Int32 *) (_storeP + ARefCountOffset);
}

inline
Int32 *FieldContainerPtrBase::getARefCountP(void) const
{
    return (Int32 *) (_storeP + ARefCountOffset);
}
#endif

inline
UInt32 *FieldContainerPtrBase::getIdP(void)
{
    return (UInt32 *) (_storeP + IdOffset);
}

inline
UInt32 *FieldContainerPtrBase::getIdP(void) const
{
    return (UInt32 *) (_storeP + IdOffset);
}

inline
UInt8 *FieldContainerPtrBase::getElemP(UInt32 uiElemNum)
{
    return (_storeP + (_containerSize * uiElemNum));
}

inline
UInt8 *FieldContainerPtrBase::getElemP(UInt32 uiElemNum) const
{
    return (_storeP + (_containerSize * uiElemNum));
}

inline
UInt8 *FieldContainerPtrBase::getFirstElemP(void)
{
    return _storeP;
}

inline
UInt8 *FieldContainerPtrBase::getFirstElemP(void) const
{
    return _storeP;
}

/*-------------------------------------------------------------------------*/
/*                         Get Memory Offsets                              */

inline
Int32 FieldContainerPtrBase::getMemStartOff(void) const
{
#ifdef OSG_ASPECT_REFCOUNT
    return ARefCountOffset;
#else
    return RefCountOffset;
#endif
}

inline
Int32 FieldContainerPtrBase::getRefCountOff(void) const
{
    return RefCountOffset;
}

#ifdef OSG_ASPECT_REFCOUNT
inline
Int32 FieldContainerPtrBase::getRefACountOff(void) const
{
    return ARefCountOffset;
}
#endif

inline
Int32 FieldContainerPtrBase::getIdOff(void) const
{
    return IdOffset;
}

inline
Int32  FieldContainerPtrBase::getFirstElemOff(void) const
{
    return 0;
}

inline
Int32  FieldContainerPtrBase::getElemOff(UInt32 uiElemNum) const
{
    return (_containerSize * uiElemNum);
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

inline 
FieldContainerPtrBase::FieldContainerPtrBase(void) :
    _containerSize(0               ),
    _uiParentEPos(InvalidParentEPos),
    _storeP      (NULL             ) 
#ifdef OSG_FCPTR_TYPED_STORE
    ,_typedStoreP(NULL)
#endif
{
}

inline
FieldContainerPtrBase::FieldContainerPtrBase(
    const NilFieldContainerPtr &) :

    _containerSize(0                ),
    _uiParentEPos (InvalidParentEPos),
    _storeP       (NULL             )
#ifdef OSG_FCPTR_TYPED_STORE
    , _typedStoreP(NULL             )
#endif
{
}

inline
FieldContainerPtrBase::FieldContainerPtrBase(
    const FieldContainerPtrBase &source) :

    _containerSize(source._containerSize),
    _uiParentEPos (source._uiParentEPos ),
    _storeP       (source._storeP       )
#ifdef OSG_FCPTR_TYPED_STORE
    , _typedStoreP(NULL                 )
#endif
{
#ifdef OSG_FCPTR_TYPED_STORE
    _typedStoreP = reinterpret_cast<FieldContainer *>(
        getElemP(Thread::getCurrentAspect()));
#endif   
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

inline
FieldContainerPtrBase::~FieldContainerPtrBase(void)
{
#ifdef OSG_DEBUG
    _containerSize = 0;
    _uiParentEPos  = InvalidParentEPos;
    _storeP        = NULL;
#ifdef OSG_FCPTR_TYPED_STORE
    _typedStoreP   = NULL;
#endif
#endif
}

/*-------------------------------------------------------------------------*/
/*                         Parent Field Pos                                */

inline
void FieldContainerPtrBase::setParentFieldPos(UInt16 uiParentEPos)
{
    _uiParentEPos = uiParentEPos;
}

inline
UInt16 FieldContainerPtrBase::getParentFieldPos(void) const
{
    return _uiParentEPos;
}

/*-------------------------------------------------------------------------*/
/*                                Get                                      */

inline
UInt32 FieldContainerPtrBase::getContainerId(void) const
{
    return (*getIdP());
}

inline
UInt16 FieldContainerPtrBase::getContainerSize(void) const
{
    return _containerSize;
}

inline
FieldContainer *FieldContainerPtrBase::getBaseCPtr(void) const
{
    return reinterpret_cast<FieldContainer *>(getFirstElemP());
}

inline
FieldContainer *FieldContainerPtrBase::getAspectCPtr(UInt32 uiAspectId) const
{
    return reinterpret_cast<FieldContainer *>(getElemP(uiAspectId));
}

#ifdef OSG_1_COMPAT
inline
Int32  FieldContainerPtrBase::getRefCount(void) const
{
    return *getRefCountP();
}
#endif

/*-------------------------------------------------------------------------*/
/*                             Assignment                                  */

inline
void FieldContainerPtrBase::operator =(const NilFieldContainerPtr &)
{
    _containerSize = 0;
    _uiParentEPos  = InvalidParentEPos;
    _storeP        = NULL;
#ifdef OSG_FCPTR_TYPED_STORE
    _typedStoreP   = NULL;
#endif
}

inline
void FieldContainerPtrBase::operator =(const FieldContainerPtrBase &source)
{
    if (this == &source)
        return;

    _containerSize = source._containerSize;
    _uiParentEPos  = source._uiParentEPos;
    _storeP        = source._storeP;

#ifdef OSG_FCPTR_TYPED_STORE
    _typedStoreP = reinterpret_cast<FieldContainer *>(
        getElemP(Thread::getCurrentAspect()));
#endif
}

/*-------------------------------------------------------------------------*/
/*                             Comparison                                  */

inline
bool FieldContainerPtrBase::operator < (
    const NilFieldContainerPtr &) const
{
    return false;
}

inline
bool FieldContainerPtrBase::operator ==(
    const NilFieldContainerPtr &) const
{
    return _storeP == NULL;
}

inline
bool FieldContainerPtrBase::operator !=(
    const NilFieldContainerPtr &) const
{
    return _storeP != NULL;
}


inline
bool FieldContainerPtrBase::operator < (
    const FieldContainerPtrBase &other)const
{
    return _storeP < other._storeP;
}

inline
bool FieldContainerPtrBase::operator ==(
    const FieldContainerPtrBase &other) const
{
    return _storeP == other._storeP;
}

inline
bool FieldContainerPtrBase::operator !=(
    const FieldContainerPtrBase &other) const
{
    return ! (*this == other);
}

inline
bool FieldContainerPtrBase::operator ! (void) const
{
    return _storeP == NULL;
}

inline
FieldContainerPtrBase::operator FieldContainerPtrBase::unspecified_bool_type(
    void) const
{
    return (_storeP == NULL) ? 0 : &FieldContainerPtrBase::_storeP;
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

inline
FieldContainerPtrBase::FieldContainerPtrBase(
    const FieldContainer *source,
    const UInt16          uiSize,
    const UInt16          uiParentEPos) :

    _containerSize(uiSize                                          ),
    _uiParentEPos (uiParentEPos                                    ),
    _storeP       ((UInt8 *) (const_cast<FieldContainer *>(source)))
#ifdef OSG_FCPTR_TYPED_STORE
    , _typedStoreP(NULL                                            )
#endif
{
    if(source != NULL)
    {
        _storeP -= getElemOff(Thread::getCurrentAspect());
#ifdef OSG_FCPTR_TYPED_STORE
        _typedStoreP = reinterpret_cast<FieldContainer *>(
            getElemP(Thread::getCurrentAspect()));
#endif
    }
}

inline
FieldContainerPtrBase::FieldContainerPtrBase(const FieldContainer &source,
                                             const UInt16          uiSize) :
    _containerSize(uiSize                                           ),
    _uiParentEPos (InvalidParentEPos                                ),
    _storeP       ((UInt8 *) (const_cast<FieldContainer *>(&source)))
#ifdef OSG_FCPTR_TYPED_STORE
    , _typedStoreP(NULL                                             )
#endif
{
    _storeP -= getElemOff(Thread::getCurrentAspect());
#ifdef OSG_FCPTR_TYPED_STORE
    _typedStoreP = reinterpret_cast<FieldContainer *>(
        getElemP(Thread::getCurrentAspect()));
#endif
}
                   
inline
FieldContainerPtrBase::FieldContainerPtrBase(const FieldContainer *source,
                                             const UInt16          uiSize) :
    _containerSize(uiSize                                          ),
    _uiParentEPos (InvalidParentEPos                               ),
    _storeP       ((UInt8 *) (const_cast<FieldContainer *>(source)))
#ifdef OSG_FCPTR_TYPED_STORE
    , _typedStoreP(NULL                                            )
#endif
{
    if(_storeP != NULL)
    {
        _storeP -= getElemOff(Thread::getCurrentAspect());
#ifdef OSG_FCPTR_TYPED_STORE
        _typedStoreP = reinterpret_cast<FieldContainer *>(
            getElemP(Thread::getCurrentAspect()));
#endif
    }
}

inline
void FieldContainerPtrBase::addReference(void) const
{
    _pRefCountLock->acquire(_storeP);

    (*getRefCountP())++;

    _pRefCountLock->release(_storeP);

    Thread::getCurrentChangeList()->addAddRefd(*(getIdP()));
}

#ifdef OSG_ASPECT_REFCOUNT
inline
void FieldContainerPtrBase::addAReference(void) const
{
    _pRefCountLock->acquire(_storeP);

    (*getARefCountP())++;

    _pRefCountLock->release(_storeP);
}
#endif

inline
void FieldContainerPtrBase::subReference(void) const
{
    Thread::getCurrentChangeList()->addSubRefd(*(getIdP()));

    Thread::getCurrentChangeList()->incSubRefLevel();

    _pRefCountLock->acquire(_storeP);

    (*getRefCountP())--;

    if((*getRefCountP()) <= 0)
    {
        _pRefCountLock->release(_storeP);

        UInt8 *pTmp = getFirstElemP();

        ReflexiveContainer *pRC = 
            reinterpret_cast<ReflexiveContainer *>(
                getElemP(Thread::getCurrentAspect()));

        pRC->onDestroy   (*(getIdP()));
        pRC->resolveLinks(           );

#ifdef OSG_ASPECT_REFCOUNT
        if((*getARefCountP()) <= 0)
        {
#endif
            if(((ReflexiveContainer *) pTmp)->deregister(*(getIdP())) == true)
            {
                // Clean up a little.
                const_cast<FieldContainerPtrBase *>(this)->_storeP = NULL;

                return;
            }

            for(UInt32 i = 0; i < ThreadManager::getNumAspects(); i++)
            {
                ((ReflexiveContainer *) pTmp)->onDestroyAspect(*(getIdP()), i);
                
                ((ReflexiveContainer *) pTmp)->~ReflexiveContainer();
                
                pTmp += _containerSize;
            }
    
            operator delete(_storeP + getMemStartOff());
#ifdef OSG_ASPECT_REFCOUNT
        }
#endif

         // Clean up a little.
        const_cast<FieldContainerPtrBase *>(this)->_storeP = NULL;
    }
    else
    {
        _pRefCountLock->release(_storeP);
    }

    Thread::getCurrentChangeList()->decSubRefLevel();
}

#ifdef OSG_ASPECT_REFCOUNT
inline
void FieldContainerPtrBase::subAReference(void) const
{
    _pRefCountLock->acquire(_storeP);

    (*getARefCountP())--;

    if((*getRefCountP()) <= 0 && (*getARefCountP()) <= 0)
    {
        _pRefCountLock->release(_storeP);

        UInt8 *pTmp = getFirstElemP();

        for(UInt32 i = 0; i < ThreadManager::getNumAspects(); i++)
        {
            ((ReflexiveContainer *) pTmp)->onDestroyAspect(*(getIdP()), i);

            ((ReflexiveContainer *) pTmp)->~ReflexiveContainer();
            
            pTmp += _containerSize;
        }
    
        operator delete(_storeP + getMemStartOff());
    }
    else
    {
        _pRefCountLock->release(_storeP);
    }
}
#endif

inline
void FieldContainerPtrBase::setNil(void)
{
    _containerSize = 0;
    _uiParentEPos  = InvalidParentEPos;
    _storeP        = NULL;
#ifdef OSG_FCPTR_TYPED_STORE
    _typedStoreP   = NULL; 
#endif
}



//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------


/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

inline
FieldContainerPtr::FieldContainerPtr(void) :
    Inherited()
{
}

inline
FieldContainerPtr::FieldContainerPtr(const NilFieldContainerPtr &) :
    Inherited()
{
}

inline
FieldContainerPtr::FieldContainerPtr(const FieldContainerPtr &source) :
    Inherited(source)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

inline
FieldContainerPtr::~FieldContainerPtr(void)
{
}


/*-------------------------------------------------------------------------*/
/*                        Container Access                                 */

inline
FieldContainer *FieldContainerPtr::operator->(void)
{
    return (FieldContainer *) (getElemP(Thread::getCurrentAspect()));
}

inline
FieldContainer *FieldContainerPtr::operator->(void) const
{
    return (FieldContainer *) (getElemP(Thread::getCurrentAspect()));
}

inline
FieldContainer &FieldContainerPtr::operator *(void)
{ 
    return *((FieldContainer *) (getElemP(Thread::getCurrentAspect())));
}

inline
FieldContainer &FieldContainerPtr::operator *(void) const
{
    return *((FieldContainer *) (getElemP(Thread::getCurrentAspect())));
}

inline
FieldContainer *FieldContainerPtr::getCPtr(void)
{
    return (FieldContainer *) (getElemP(Thread::getCurrentAspect()));
}

inline
FieldContainer *FieldContainerPtr::getCPtr(void) const
{
    return (FieldContainer *) (getElemP(Thread::getCurrentAspect()));
}

/*-------------------------------------------------------------------------*/
/*                             Assignment                                  */

inline
void FieldContainerPtr::operator =(const NilFieldContainerPtr &)
{
    setNil();
}

inline
void FieldContainerPtr::operator =(const FieldContainerPtr &source)
{
    *(static_cast<Inherited *>(this)) = source;
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

inline
FieldContainerPtr::FieldContainerPtr(const FieldContainer &source,
                                     const UInt16          uiSize) :
    Inherited(source, uiSize)
{
}

inline
FieldContainerPtr::FieldContainerPtr(const FieldContainer *source,
                                     const UInt16          uiSize) :
    Inherited(source, uiSize)
{
}

inline
FieldContainerPtr::FieldContainerPtr(const FieldContainer *source,
                                     const UInt16          uiSize,
                                     const UInt16          uiParentEPos) :
    Inherited(source, uiSize, uiParentEPos)
{
}




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

inline
FieldContainerConstPtr::FieldContainerConstPtr(void) :
    Inherited()
{
}

inline
FieldContainerConstPtr::FieldContainerConstPtr(
    const NilFieldContainerPtr &) :

    Inherited()
{
}

inline
FieldContainerConstPtr::FieldContainerConstPtr(
    const FieldContainerPtr &source) :

    Inherited(source)
{
}

inline
FieldContainerConstPtr::FieldContainerConstPtr(
    const FieldContainerConstPtr &source):

    Inherited(source)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

inline
FieldContainerConstPtr::~FieldContainerConstPtr(void)
{
}

/*-------------------------------------------------------------------------*/
/*                           Container Access                              */

inline
const FieldContainer *FieldContainerConstPtr::operator->(void)
{
    return (const FieldContainer *) (getElemP(Thread::getCurrentAspect()));
}

inline
const FieldContainer *FieldContainerConstPtr::operator->(void) const
{
    return (const FieldContainer *) (getElemP(Thread::getCurrentAspect()));
}

inline
const FieldContainer &FieldContainerConstPtr::operator *(void)
{
    return *((const FieldContainer *) (getElemP(Thread::getCurrentAspect())));
}

inline
const FieldContainer &FieldContainerConstPtr::operator *(void) const
{
    return *((const FieldContainer *) (getElemP(Thread::getCurrentAspect())));
}

inline
const FieldContainer *FieldContainerConstPtr::getCPtr(void)
{
    return (const FieldContainer *) (getElemP(Thread::getCurrentAspect()));
}

inline
const FieldContainer *FieldContainerConstPtr::getCPtr(void) const
{
    return (const FieldContainer *) (getElemP(Thread::getCurrentAspect()));
}

/*-------------------------------------------------------------------------*/
/*                             Assignment                                  */

inline
void FieldContainerConstPtr::operator =(const NilFieldContainerPtr &)
{
    setNil();
}

inline
void FieldContainerConstPtr::operator =(const FieldContainerPtr &source)
{
    *(static_cast<Inherited *>(this)) = source;
}

inline
void FieldContainerConstPtr::operator =(const FieldContainerConstPtr &source)
{
    *(static_cast<Inherited *>(this)) = source;
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

inline
FieldContainerConstPtr::FieldContainerConstPtr(const FieldContainer &source,
                                               const UInt16          uiSize) :
    Inherited(source, uiSize)
{
}

inline
FieldContainerConstPtr::FieldContainerConstPtr(const FieldContainer *source,
                                               const UInt16          uiSize) :
    Inherited(source, uiSize)
{
}

inline
FieldContainerConstPtr::FieldContainerConstPtr(
    const FieldContainer *source,
    const UInt16          uiSize,
    const UInt16          uiParentEPos) :

    Inherited(source, uiSize, uiParentEPos)
{
}




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

template <class ParentPtrTypeT, class FieldContainerTypeT> inline
FCPtr<ParentPtrTypeT, FieldContainerTypeT>::FCPtr(void) :
    Inherited()
{
}

template <class ParentPtrTypeT, class FieldContainerTypeT> inline
FCPtr<ParentPtrTypeT, FieldContainerTypeT>::FCPtr(const FCPtr &source):
    Inherited(source)
{
}

template <class ParentPtrTypeT, class FieldContainerTypeT> inline
FCPtr<ParentPtrTypeT, 
      FieldContainerTypeT>::FCPtr(const NilFieldContainerPtr &) :

    Inherited()
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

template <class ParentPtrTypeT, class FieldContainerTypeT> inline
FCPtr<ParentPtrTypeT, FieldContainerTypeT>::~FCPtr(void)
{
}

/*-------------------------------------------------------------------------*/
/*                            Container Access                             */

template <class ParentPtrTypeT, class FieldContainerTypeT> inline
typename FCPtr<ParentPtrTypeT, FieldContainerTypeT>::StoredObject *
    FCPtr<ParentPtrTypeT, FieldContainerTypeT>::operator ->(void)
{
    return (StoredObject *) Self::getElemP(Thread::getCurrentAspect());
}

template <class ParentPtrTypeT, class FieldContainerTypeT> inline
typename FCPtr<ParentPtrTypeT, FieldContainerTypeT>::StoredObject *
    FCPtr<ParentPtrTypeT, FieldContainerTypeT>::operator ->(void) const
{
    return (StoredObject *) Self::getElemP(Thread::getCurrentAspect());
}

template <class ParentPtrTypeT, class FieldContainerTypeT> inline
typename FCPtr<ParentPtrTypeT, FieldContainerTypeT>::StoredObject &
    FCPtr<ParentPtrTypeT, FieldContainerTypeT>::operator *(void)
{
    return *((StoredObject *) Self::getElemP(Thread::getCurrentAspect()));
}

template <class ParentPtrTypeT, class FieldContainerTypeT> inline
typename FCPtr<ParentPtrTypeT, FieldContainerTypeT>::StoredObject &
    FCPtr<ParentPtrTypeT, FieldContainerTypeT>::operator *(void) const
{
    return *((StoredObject *) Self::getElemP(Thread::getCurrentAspect()));
}

template <class ParentPtrTypeT, class FieldContainerTypeT> inline
typename FCPtr<ParentPtrTypeT, FieldContainerTypeT>::StoredObject *
    FCPtr<ParentPtrTypeT, FieldContainerTypeT>::getCPtr(void)

{
    return (StoredObject *) Self::getElemP(Thread::getCurrentAspect());
}

template <class ParentPtrTypeT, class FieldContainerTypeT> inline
typename FCPtr<ParentPtrTypeT, FieldContainerTypeT>::StoredObject *
    FCPtr<ParentPtrTypeT, FieldContainerTypeT>::getCPtr(void) const
{
    return (StoredObject *) Self::getElemP(Thread::getCurrentAspect());
}

/*-------------------------------------------------------------------------*/
/*                             Assignment                                  */

template <class ParentPtrTypeT, class FieldContainerTypeT> inline
void FCPtr<ParentPtrTypeT, 
           FieldContainerTypeT>::operator = (const Self &source)
{
    // copy parts inherited from parent
    *(static_cast<Inherited *>(this)) = source;
}

template <class ParentPtrTypeT, class FieldContainerTypeT> inline
void FCPtr<ParentPtrTypeT, FieldContainerTypeT>::operator = (
    const NilFieldContainerPtr &)
{
    Self::setNil();
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

template <class ParentPtrTypeT, class FieldContainerTypeT> inline
FCPtr<ParentPtrTypeT, 
      FieldContainerTypeT>::FCPtr(const FieldContainerTypeT &source,
                                  const UInt16               uiSize) :

    Inherited(source, uiSize)
{
}

template <class ParentPtrTypeT, class FieldContainerTypeT> inline
FCPtr<ParentPtrTypeT, 
      FieldContainerTypeT>::FCPtr(const FieldContainerTypeT *source,
                                  const UInt16               uiSize) :

    Inherited(source, uiSize)
{
}

template <class ParentPtrTypeT, class FieldContainerTypeT> inline
FCPtr<ParentPtrTypeT, 
      FieldContainerTypeT>::FCPtr(const FieldContainerTypeT *source,
                                  const UInt16               uiSize,
                                  const UInt16               uiParentEPos) :

    Inherited(source, uiSize, uiParentEPos)
{
}




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

template <class ParentPtrTypeT, class FieldContainerTypeT> inline
FCConstPtr<ParentPtrTypeT, FieldContainerTypeT>::FCConstPtr(void) :
    Inherited()
{
}

template <class ParentPtrTypeT, class FieldContainerTypeT> inline
FCConstPtr<ParentPtrTypeT, FieldContainerTypeT>::FCConstPtr(
    const NilFieldContainerPtr &) :

    Inherited()
{
}

template <class ParentPtrTypeT, class FieldContainerTypeT> inline
FCConstPtr<ParentPtrTypeT, FieldContainerTypeT>::FCConstPtr(
    const NonConstPtr &source) :

    Inherited(source)
{
}

template <class ParentPtrTypeT, class FieldContainerTypeT> inline
FCConstPtr<ParentPtrTypeT, FieldContainerTypeT>::FCConstPtr(
    const FCConstPtr &source) :

    Inherited(source)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

template <class ParentPtrTypeT, class FieldContainerTypeT> inline
FCConstPtr<ParentPtrTypeT, FieldContainerTypeT>::~FCConstPtr(void)
{
}

/*-------------------------------------------------------------------------*/
/*                        Container Access                                 */

template <class ParentPtrTypeT, class FieldContainerTypeT> inline
const typename FCConstPtr<ParentPtrTypeT, FieldContainerTypeT>::StoredObject *
    FCConstPtr<ParentPtrTypeT, FieldContainerTypeT>::operator ->(void)
{
    return (const StoredObject *) Self::getElemP(Thread::getCurrentAspect());
}

template <class ParentPtrTypeT, class FieldContainerTypeT> inline
const typename FCConstPtr<ParentPtrTypeT, FieldContainerTypeT>::StoredObject *
    FCConstPtr<ParentPtrTypeT, FieldContainerTypeT>::operator ->(void) const
{
    return (const StoredObject *) Self::getElemP(Thread::getCurrentAspect());
}

template <class ParentPtrTypeT, class FieldContainerTypeT> inline
const typename FCConstPtr<ParentPtrTypeT, FieldContainerTypeT>::StoredObject &
    FCConstPtr<ParentPtrTypeT, FieldContainerTypeT>::operator *(void)
{
   return *((const StoredObject *) Self::getElemP(Thread::getCurrentAspect()));
}

template <class ParentPtrTypeT, class FieldContainerTypeT> inline
const typename FCConstPtr<ParentPtrTypeT, FieldContainerTypeT>::StoredObject &
    FCConstPtr<ParentPtrTypeT, FieldContainerTypeT>::operator *(void) const
{
   return *((const StoredObject *) Self::getElemP(Thread::getCurrentAspect()));
}


template <class ParentPtrTypeT, class FieldContainerTypeT> inline
const typename FCConstPtr<ParentPtrTypeT, FieldContainerTypeT>::StoredObject *
    FCConstPtr<ParentPtrTypeT, FieldContainerTypeT>::getCPtr(void)

{
    return (const StoredObject *) Self::getElemP(Thread::getCurrentAspect());
}

template <class ParentPtrTypeT, class FieldContainerTypeT> inline
const typename FCConstPtr<ParentPtrTypeT, FieldContainerTypeT>::StoredObject *
    FCConstPtr<ParentPtrTypeT, FieldContainerTypeT>::getCPtr(void) const
{
    return (const StoredObject *) Self::getElemP(Thread::getCurrentAspect());
}

/*-------------------------------------------------------------------------*/
/*                             Assignment                                  */

template <class ParentPtrTypeT, class FieldContainerTypeT> inline
void FCConstPtr<ParentPtrTypeT, 
                FieldContainerTypeT>::operator = (const NonConstPtr &source)
{
    // copy parts inherited from parent
    *(static_cast<Inherited *>(this)) = source;
}

template <class ParentPtrTypeT, class FieldContainerTypeT> inline
void FCConstPtr<ParentPtrTypeT, 
                FieldContainerTypeT>::operator = (const FCConstPtr &source)
{
    // copy parts inherited from parent
    *(static_cast<Inherited *>(this)) = source;
}

template <class ParentPtrTypeT, class FieldContainerTypeT> inline
void FCConstPtr<ParentPtrTypeT, FieldContainerTypeT>::operator = (
    const NilFieldContainerPtr &)
{
    Self::setNil();
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

template <class ParentPtrTypeT, class FieldContainerTypeT> inline
FCConstPtr<ParentPtrTypeT, 
           FieldContainerTypeT>::FCConstPtr(const FieldContainerTypeT &source,
                                            const UInt16               uiSize):

    Inherited(source, uiSize)
{
}

template <class ParentPtrTypeT, class FieldContainerTypeT> inline
FCConstPtr<ParentPtrTypeT, 
           FieldContainerTypeT>::FCConstPtr(const FieldContainerTypeT *source,
                                            const UInt16               uiSize):

    Inherited(source, uiSize)
{
}

template <class ParentPtrTypeT, class FieldContainerTypeT> inline
FCConstPtr<ParentPtrTypeT, FieldContainerTypeT>::FCConstPtr(
    const FieldContainerTypeT *source,
    const UInt16               uiSize,
    const UInt16               uiParentEPos) :

    Inherited(source, uiSize, uiParentEPos)
{
}




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

inline
NilFieldContainerPtr::NilFieldContainerPtr(void) : 
    Inherited()
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

inline
NilFieldContainerPtr::~NilFieldContainerPtr(void)
{
}


OSG_END_NAMESPACE

#define OSGFIELDCONTAINERPTR_INLINE_CVSID "@(#)$Id: $"

