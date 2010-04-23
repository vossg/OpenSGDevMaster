/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                  Copyright (C) 2010 by the OpenSG Forum                   *
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
/*  NoRefCountPolicy                                                         */

template <class ObjT>
inline void
NoRefCountPolicy::addRef(ObjT * const)
{
    // nothing to do
}

inline void
NoRefCountPolicy::addRef(FieldContainer * const)
{
    // nothing to do
}

template <class ObjT>
inline void
NoRefCountPolicy::subRef(ObjT * const)
{
    // nothing to do
}

inline void
NoRefCountPolicy::subRef(FieldContainer * const)
{
    // nothing to do
}

template <class DestT, class SourceT>
inline void
NoRefCountPolicy::setRefd(DestT *&pDest, SourceT *pSource)
{
    pDest = pSource;
}

template <class ObjT>
inline ObjT *
NoRefCountPolicy::validate(ObjT * const pObject)
{
    return pObject;
}

template <class ObjT>
inline ObjT &
NoRefCountPolicy::dereference(ObjT * const pObject)
{
    return *pObject;
}

template <class DestT, class SourceT>
inline void
NoRefCountPolicy::convertTransitPtr(DestT *&, SourceT *&)
{
    OSG_ASSERT(false);
}

/*---------------------------------------------------------------------------*/
/*  MemObjRefCountPolicy                                                     */

template <class ObjT>
inline void
MemObjRefCountPolicy::addRef(ObjT * const pObject)
{
    if(pObject != NULL)
        pObject->addRef();
}

inline void
MemObjRefCountPolicy::addRef(MemoryObject * const pObject)
{
    if(pObject != NULL)
        pObject->addRef();
}

template <class ObjT>
inline void
MemObjRefCountPolicy::subRef(ObjT * const pObject)
{
    if(pObject != NULL)
        pObject->subRef();
}

inline void
MemObjRefCountPolicy::subRef(MemoryObject * const pObject)
{
    if(pObject != NULL)
        pObject->subRef();
}

template <class DestT, class SourceT>
inline void
MemObjRefCountPolicy::setRefd(DestT *&pDest, SourceT *pSource)
{
    MemObjRefCountPolicy::addRef(pSource);
    MemObjRefCountPolicy::subRef(pDest  );

    pDest = pSource;
}

template <class ObjT>
inline ObjT *
MemObjRefCountPolicy::validate(ObjT * const pObject)
{
    return pObject;
}

template <class ObjT>
inline ObjT &
MemObjRefCountPolicy::dereference(ObjT * const pObject)
{
    return *pObject;
}

template <class DestT, class SourceT>
inline void
MemObjRefCountPolicy::convertTransitPtr(DestT *&pDest, SourceT *&pSource)
{
    MemObjRefCountPolicy::subRef(pDest);

    pDest   = pSource;
    pSource = NULL;
}

OSG_END_NAMESPACE
