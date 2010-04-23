/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *              Copyright (C) 2010 by the OpenSG Forum                       *
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

/*---------------------------------------------------------------------------*/
/*  RecordedRefCountPolicy                                                   */

inline void
RecordedRefCountPolicy::addRef(FieldContainer * const pObject)
{
    if(pObject != NULL)
        pObject->addReferenceRecorded();
}

inline void
RecordedRefCountPolicy::subRef(FieldContainer * const pObject)
{
    if(pObject != NULL)
        pObject->subReferenceRecorded();
}

template <class DestT, class SourceT>
inline void
RecordedRefCountPolicy::setRefd(DestT *&pDest, SourceT *pSource)
{
    RecordedRefCountPolicy::addRef(pSource);
    RecordedRefCountPolicy::subRef(pDest  );
    
    pDest = pSource;
}

template <class ObjT>
inline ObjT *
RecordedRefCountPolicy::validate(ObjT *pObject)
{
    return pObject;
}

template <class ObjT>
inline ObjT &
RecordedRefCountPolicy::dereference(ObjT *pObject)
{
    return *pObject;
}

template <class DestT, class SourceT>
inline void
RecordedRefCountPolicy::convertTransitPtr(DestT *&pDest, SourceT *&pSource)
{
    RecordedRefCountPolicy::subRef(pDest);

    pDest   = pSource;
    pSource = NULL;

    if(pDest != NULL)
    {
        Thread::getCurrentChangeList()->addAddRefd(pDest->getId());
    }
}


/*---------------------------------------------------------------------------*/
/*  UnrecordedRefCountPolicy                                                 */

inline void
UnrecordedRefCountPolicy::addRef(FieldContainer * const pObject)
{
    if(pObject != NULL)
        pObject->addReferenceUnrecorded();
}

inline void
UnrecordedRefCountPolicy::subRef(FieldContainer * const pObject)
{
    if(pObject != NULL)
        pObject->subReferenceUnrecorded();
}

template <class DestT, class SourceT>
inline void
UnrecordedRefCountPolicy::setRefd(DestT *&pDest, SourceT *pSource)
{
    UnrecordedRefCountPolicy::addRef(pSource);
    UnrecordedRefCountPolicy::subRef(pDest  );
    
    pDest = pSource;
}

template <class ObjT>
inline ObjT *
UnrecordedRefCountPolicy::validate(ObjT *pObject)
{
    return pObject;
}

template <class ObjT>
inline ObjT &
UnrecordedRefCountPolicy::dereference(ObjT *pObject)
{
    return *pObject;
}

template <class DestT, class SourceT>
inline void
UnrecordedRefCountPolicy::convertTransitPtr(DestT *&pDest, SourceT *&pSource)
{
    UnrecordedRefCountPolicy::subRef(pDest);

    pDest   = pSource;
    pSource = NULL;
}


/*---------------------------------------------------------------------------*/
/*  WeakRefCountPolicy                                                       */

inline void
WeakRefCountPolicy::addRef(FieldContainer * const pObject)
{
    if(pObject != NULL)
        pObject->addWeakReference();
}

inline void
WeakRefCountPolicy::subRef(FieldContainer * const pObject)
{
    if(pObject != NULL)
        pObject->subWeakReference();
}

template <class DestT, class SourceT>
inline void
WeakRefCountPolicy::setRefd(DestT *&pDest, SourceT *pSource)
{
    WeakRefCountPolicy::addRef(pSource);
    WeakRefCountPolicy::subRef(pDest  );
    
    pDest = pSource;
}

template <class ObjT>
inline ObjT *
WeakRefCountPolicy::validate(ObjT *pObject)
{
    if(pObject == NULL)
    {
        return NULL;
    }
    else
    {
        return (pObject->getRefCount() > 0) ? pObject : NULL;
    }
}

template <class ObjT>
inline ObjT &
WeakRefCountPolicy::dereference(ObjT *pObject)
{
    ObjT *retVal = validate(pObject);

    OSG_ASSERT(retVal != NULL);

    return *retVal;
}

template <class DestT, class SourceT>
inline void
WeakRefCountPolicy::convertTransitPtr(DestT *&pDest, SourceT *&pSource)
{
    OSG_ASSERT(false);
}

OSG_END_NAMESPACE
