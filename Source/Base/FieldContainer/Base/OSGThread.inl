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

/*-------------------------------------------------------------------------*/
/*                                Get                                      */

inline
UInt32 ThreadCommonBase::getAspect(void)
{
    return _uiAspectId;
}

inline
ChangeList *ThreadCommonBase::getChangeList(void)
{
    return _pChangeList;
}

inline
BitVector ThreadCommonBase::getNamespaceMask(void)
{
    return _bNamespaceMask;
}

inline
BitVector ThreadCommonBase::getLocalFlags(void)
{
    return _bLocalFlags;
}

inline
void ThreadCommonBase::setFallbackAspectId(UInt32 uiId)
{
    _uiFallbackAspectId = uiId;
}

inline
void ThreadCommonBase::setAspect(UInt32 uiAspectId)
{
    _uiAspectId = uiAspectId;
}

inline
void ThreadCommonBase::setNamespaceMask(BitVector bNamespaceMask)
{
    _bNamespaceMask = bNamespaceMask; 
}

inline
void ThreadCommonBase::setLocalFlags(BitVector bFlags)
{
    _bLocalFlags = bFlags;
}

#if defined (OSG_USE_PTHREADS)

/*-------------------------------------------------------------------------*/
/*                                Get                                      */

#if 0
inline
UInt32 PThreadBase::getCurrentAspect(void)
{
#if defined(OSG_PTHREAD_ELF_TLS)
    return _uiTLSAspectId;
#else
    UInt32 *pUint;

    pUint = (UInt32 *) pthread_getspecific(_aspectKey);

    return *pUint;
#endif

}

inline
ChangeList *PThreadBase::getCurrentChangeList(void)
{
#if defined(OSG_PTHREAD_ELF_TLS)
    return _pTLSChangeList;
#else
    ChangeList **pCList;

    pCList = (ChangeList **) pthread_getspecific(_changeListKey);

    return *pCList;
#endif
}

inline
void PThreadBase::setAspectTo(UInt32 uiNewAspect)
{
#if defined(OSG_PTHREAD_ELF_TLS)
    _uiTLSAspectId = uiNewAspect;
#else
    UInt32 *pUint;

    pUint = (UInt32 *) pthread_getspecific(_aspectKey);

    *pUint = uiNewAspect;
#endif
}
#endif

#endif


#if defined (OSG_USE_SPROC)

/*-------------------------------------------------------------------------*/
/*                                Get                                      */

inline
UInt32 SprocBase::getCurrentAspect(void)
{
    return ((OSGProcessData *) PRDA->usr_prda.fill)->_uiAspectId;
}

inline
ChangeList *SprocBase::getCurrentChangeList(void)
{
    return ((OSGProcessData *) PRDA->usr_prda.fill)->_pChangeList;
}

inline
void SprocBase::setAspectTo(UInt32 uiNewAspect)
{
    ((OSGProcessData *) PRDA->usr_prda.fill)->_uiAspectId = uiNewAspect;
}

#endif


#if defined (OSG_USE_WINTHREADS)

/*-------------------------------------------------------------------------*/
/*                                Get                                      */

#if 0
inline
UInt32 WinThreadBase::getCurrentAspect(void)
{
#ifdef OSG_WIN32_ASPECT_USE_LOCALSTORAGE
    UInt32 *pUint;

    pUint = (UInt32 *) TlsGetValue(_aspectKey);

    return *pUint;
#else
    return _uiAspectLocal;
#endif
}

inline
ChangeList *WinThreadBase::getCurrentChangeList(void)
{
#ifdef OSG_WIN32_ASPECT_USE_LOCALSTORAGE
    ChangeList **pCList;

    pCList = (ChangeList **) TlsGetValue(_changeListKey);

    return *pCList;
#else
    return _pChangeListLocal;
#endif
}

inline
BitVector WinThreadBase::getCurrentNamespaceMask(void)
{
#ifdef OSG_WIN32_ASPECT_USE_LOCALSTORAGE
    BitVector *pBitVec;

    pBitVec = (BitVector *) TlsGetValue(_namespaceMaskKey);

    return *pBitVec;
#else
    return _bNamespaceMaskLocal;
#endif
}

inline
BitVector WinThreadBase::getCurrentLocalFlags(void)
{
#ifdef OSG_WIN32_ASPECT_USE_LOCALSTORAGE
    BitVector *pBitVec;

    pBitVec = (BitVector *) TlsGetValue(_localFlagsKey);

    return *pBitVec;
#else
    return _bLocalFlagsLocal;
#endif
}
#endif

inline
void WinThreadBase::setAspectTo(UInt32 uiNewAspect)
{
#ifdef OSG_WIN32_ASPECT_USE_LOCALSTORAGE
    UInt32 *pUint;

    pUint = (UInt32 *) TlsGetValue(_aspectKey);

    *pUint = uiNewAspect;
#else
    _uiAspectLocal = uiNewAspect;
#endif
}

inline
void WinThreadBase::setNamespaceMaskTo(BitVector bNamespaceMask)
{
#ifdef OSG_WIN32_ASPECT_USE_LOCALSTORAGE
    BitVector *pBitVec;

    pBitVec = (BitVector *) TlsGetValue(_namespaceMaskKey);

    *pBitVec = bNamespaceMask;
#else
    _bNamespaceMaskLocal = bNamespaceMask;
#endif
}

inline
void WinThreadBase::setLocalFlagsTo(BitVector bLocalFlags)
{
#ifdef OSG_WIN32_ASPECT_USE_LOCALSTORAGE
    BitVector *pBitVec;

    pBitVec = (BitVector *) TlsGetValue(_localFlagsKey);

    *pBitVec = bLocalFlags;
#else
    _bLocalFlagsLocal = bLocalFlags;
#endif
}

#ifdef OSG_THREAD_DEBUG_SETASPECTTO
inline
void WinThreadBase::setChangelistTo(ChangeList *pNewList)
{
#ifdef OSG_WIN32_ASPECT_USE_LOCALSTORAGE
    ChangeList **pChangeList = NULL;

    pChangeList = (ChangeList **) TlsGetValue(_namespaceMaskKey);

    *pChangeList = pNewList;
#else
    _pChangeListLocal = pNewList;
#endif
}
#endif

#endif

inline
UInt32 Thread::getCurrentAspect(void)
{
    return Inherited::getCurrentAspect();
}

inline
ChangeList *Thread::getCurrentChangeList(void)
{
    return Inherited::getCurrentChangeList();
}

inline
BitVector Thread::getCurrentNamespaceMask(void)
{
    return Inherited::getCurrentNamespaceMask();
}

inline
void Thread::setCurrentNamespaceMask(BitVector bMask)
{
    Inherited::setNamespaceMaskTo(bMask);

    Self::getCurrent()->setNamespaceMask(bMask);
}

inline
void Thread::setCurrentLocalFlags(BitVector  bFlags)
{
    Inherited::setLocalFlagsTo(bFlags);

    Self::getCurrent()->setLocalFlags(bFlags);
}

inline
void Thread::resetCurrentLocalFlags(void)
{
    Inherited::setLocalFlagsTo(TypeTraits<BitVector>::BitsClear);

    Self::getCurrent()->setLocalFlags(TypeTraits<BitVector>::BitsClear);
}

inline
BitVector Thread::getCurrentLocalFlags(void)
{
    return Inherited::getCurrentLocalFlags();
}

inline
ThreadBase *Thread::getCurrent(void)
{
    return static_cast<ThreadBase *>(Inherited::getCurrent());
}

#ifdef OSG_THREAD_DEBUG_SETASPECTTO
inline
void Thread::setAspectTo(UInt32 uiNewAspect)
{
    Inherited::setAspectTo(uiNewAspect);

    Self::getCurrent()->setAspect(uiNewAspect);
}

inline
void Thread::setChangelistTo(ChangeList *pNewList)
{
    Inherited::setChangelistTo(pNewList);

    Self::getCurrent()->replaceChangelist(pNewList);
}
#endif

OSG_END_NAMESPACE

