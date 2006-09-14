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

template <class ContainerFactoryT>    
template <class ObjectT> inline
void CPtrConstructionFunctions<ContainerFactoryT>::newPtr(      
          typename ObjectT::ObjPtr &result, 
    const          ObjectT         *pPrototype)
{
    typedef ObjectT ObjectType;
    
    UInt8 *pTmp;
    
    result._containerSize = sizeof(ObjectType);
    
    pTmp        = 
        static_cast<UInt8 *>(operator new(
#ifdef OSG_ASPECT_REFCOUNT
            sizeof(Int32)      + // Aspect RefCount
#endif
            sizeof(Int32)      + // ReferenceCount
            sizeof(UInt32)     + // ContainerId
            sizeof(ObjectType) * ThreadManager::getNumAspects()));
    
#ifdef OSG_ASPECT_REFCOUNT
    *(reinterpret_cast<Int32 *>(pTmp)) = 0;
    
    pTmp += sizeof(Int32);
#endif

    *(reinterpret_cast<Int32 *>(pTmp)) = 0;
    
    pTmp += sizeof(Int32);
    
    result._storeP = (pTmp + sizeof(UInt32));

    *(reinterpret_cast<UInt32 *>(pTmp)) = 
        ContainerFactoryT::the()->registerContainer(result);
    
    Thread::getCurrentChangeList()->addCreated(
        *(reinterpret_cast<UInt32 *>(pTmp)));
    
    pTmp += sizeof(UInt32);
    
    ObjectType *aObject = reinterpret_cast<ObjectType *>(pTmp);

    for(UInt32 i = 0; i < ThreadManager::getNumAspects(); i++)
    {
        pTmp = 
            reinterpret_cast<UInt8 *>(new (pTmp) ObjectType(*pPrototype));
        
        pTmp += sizeof(ObjectType);
    }
    
    result->onCreate(pPrototype);

    for(UInt32 i = 0; i < ThreadManager::getNumAspects(); i++)
    {
        aObject[i].onCreateAspect(result.getCPtr(), pPrototype);
    }
}

template <class ContainerFactoryT>    
template <class ObjectT> inline
void CPtrConstructionFunctions<ContainerFactoryT>::newPtr(
    typename ObjectT::ObjPtr &result)
{
    typedef ObjectT ObjectType;
    
    UInt8 *pTmp;
    
    result._containerSize = sizeof(ObjectType);
    
    pTmp        =             
        static_cast<UInt8 *>(operator new(
#ifdef OSG_ASPECT_REFCOUNT
            sizeof(Int32)      + // Aspect RefCount
#endif
            sizeof(Int32)      + // ReferenceCount
            sizeof(UInt32)     + // ContainerId
            sizeof(ObjectType) * ThreadManager::getNumAspects()));
    
#ifdef OSG_ASPECT_REFCOUNT
    *(reinterpret_cast<Int32 *>(pTmp)) = 0;
    
    pTmp += sizeof(Int32);
#endif

    *(reinterpret_cast<Int32 *>(pTmp)) = 0;
    
    pTmp  += sizeof(Int32);
    
    result._storeP = (pTmp + sizeof(UInt32));
    
    *(reinterpret_cast<UInt32 *>(pTmp)) = 
        ContainerFactoryT::the()->registerContainer(result);
    
    Thread::getCurrentChangeList()->addCreated(
        *(reinterpret_cast<UInt32 *>(pTmp)));
    
    pTmp += sizeof(UInt32);
    
    ObjectType *aObject = reinterpret_cast<ObjectType *>(pTmp);

    for(UInt32 i = 0; i < ThreadManager::getNumAspects(); i++)
    {
        pTmp = reinterpret_cast<UInt8 *>(new (pTmp) ObjectType());
        
        pTmp += sizeof(ObjectType);
    }
    
    result->onCreate();
    
    for(UInt32 i = 0; i < ThreadManager::getNumAspects(); i++)
    {
        aObject[i].onCreateAspect(result.getCPtr());
    }
}

template <class ContainerFactoryT>    
template <class ObjectT> inline
typename ObjectT::ObjPtr 
    CPtrConstructionFunctions<ContainerFactoryT>::constructPtr(ObjectT *pObj)
{
    typedef typename ObjectT::ObjPtr Ptr;

    return Ptr(pObj, pObj->getContainerSize());
}

template <class ContainerFactoryT>    
template <class ObjectT> inline
typename ObjectT::ObjConstPtr 
    CPtrConstructionFunctions<ContainerFactoryT>::constructPtr(
        const ObjectT *pObj)
{
    typedef typename ObjectT::ObjConstPtr Ptr;

    return Ptr(pObj, pObj->getContainerSize());
}

template <class ContainerFactoryT>    
template <class ObjectT> inline
void PtrConstructionFunctions<ContainerFactoryT>::newPtr(      
          typename ObjectT::ObjPtr &result, 
    const          ObjectT        *pPrototype)
{
    result = new ObjectT(*pPrototype);

#ifdef OSG_MT_CPTR_ASPECT
    result->setupAspectStore();
#endif

    result->setId(ContainerFactoryT::the()->registerContainer(result));
    
    Thread::getCurrentChangeList()->addCreated(result->getId());

    result->onCreate      (        pPrototype);
    result->onCreateAspect(result, pPrototype);
}

template <class ContainerFactoryT>    
template <class ObjectT> inline
void PtrConstructionFunctions<ContainerFactoryT>::newPtr(
    typename ObjectT::ObjPtr &result)
{
    result = new ObjectT;

#ifdef OSG_MT_CPTR_ASPECT
    result->setupAspectStore();
#endif

    result->setId(ContainerFactoryT::the()->registerContainer(result));
    
    Thread::getCurrentChangeList()->addCreated(result->getId());

    result->onCreate      (      );
    result->onCreateAspect(result);
}


#ifdef OSG_MT_CPTR_ASPECT
template <class ContainerFactoryT>    
template <class ObjectT> inline
void PtrConstructionFunctions<ContainerFactoryT>::newAspectCopy(      
          typename ObjectT::ObjPtr &result, 
    const          ObjectT        *pPrototype)
{
    result = new ObjectT(*pPrototype);

    fprintf(stderr, "BARR\n");

    result->onCreateAspect(result, pPrototype);
}
#endif

template <class ContainerFactoryT>    
template <class ObjectT          > inline
ObjectT *PtrConstructionFunctions<ContainerFactoryT>::constructPtr(
    ObjectT *pObj)
{
    return pObj;
}

template <class ContainerFactoryT>    
template <class ObjectT          > inline
const ObjectT *PtrConstructionFunctions<ContainerFactoryT>::constructPtr(
    const ObjectT *pObj)
{
    return pObj;
}

template <class ParentT>
template <class ObjectT> inline
void PtrCreateMixin<ParentT>::newPtr(     typename ObjectT::ObjPtr &result, 
                                     const         ObjectT         *pPrototype)
{
    typedef typename ObjectT::ObjPtr ObjPtr;

    typedef typename osgIF<isPtr<ObjPtr>::result,
                           PtrConstructionFuncs,
                           CPtrConstructionFuncs>::_IRet Functions;
   
    Functions::template newPtr<ObjectT>(result, pPrototype);
}

template <class ParentT>
template <class ObjectT> inline
void PtrCreateMixin<ParentT>::newPtr(typename ObjectT::ObjPtr &result)
{
    typedef typename ObjectT::ObjPtr ObjPtr;

    typedef typename osgIF<isPtr<ObjPtr>::result,
                           PtrConstructionFuncs,
                           CPtrConstructionFuncs>::_IRet Functions;
   
    Functions::template newPtr<ObjectT>(result);
}

#ifdef OSG_MT_CPTR_ASPECT
template <class ParentT>
template <class ObjectT> inline
void PtrCreateMixin<ParentT>::newAspectCopy(
         typename ObjectT::ObjPtr &result, 
    const         ObjectT         *pPrototype)
{
    typedef typename ObjectT::ObjPtr ObjPtr;

    PtrConstructionFuncs::template newAspectCopy<ObjectT>(result, pPrototype);
}
#endif

template <class ParentT> 
template <class ObjectT> inline
typename ObjectT::ObjPtr PtrCreateMixin<ParentT>::constructPtr(ObjectT *pObj)
{
    typedef typename ObjectT::ObjPtr ObjPtr;

    typedef typename osgIF<isPtr<ObjPtr>::result,
                           PtrConstructionFuncs,
                           CPtrConstructionFuncs>::_IRet Functions;
   
    return Functions::template constructPtr<ObjectT>(pObj);
}


template <class ParentT> 
template <class ObjectT> inline
typename ObjectT::ObjConstPtr PtrCreateMixin<ParentT>::constructPtr(
    const ObjectT *pObj)
{
    typedef typename ObjectT::ObjPtr ObjPtr;

    typedef typename osgIF<isPtr<ObjPtr>::result,
                           PtrConstructionFuncs,
                           CPtrConstructionFuncs>::_IRet Functions;
   
    return Functions::template constructPtr<ObjectT>(pObj);
}


template <class ParentT> inline
PtrCreateMixin<ParentT>::PtrCreateMixin(void) :
    Inherited()
{
}

template <class ParentT> inline
PtrCreateMixin<ParentT>::PtrCreateMixin(const PtrCreateMixin &source) :
    Inherited(source)
{
}

template <class ParentT> inline
PtrCreateMixin<ParentT>::~PtrCreateMixin(void)
{
}

OSG_END_NAMESPACE

#define OSGCONTAINERCREATEMIXIN_INLINE_CVSID "@(#)$Id$"

