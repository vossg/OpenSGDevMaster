/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2003 by the OpenSG Forum                   *
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

#ifndef _OSGTHREADMANAGER_H_
#define _OSGTHREADMANAGER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGBaseFunctions.h"
#include "OSGIDStringLink.h"
#include "OSGLog.h"

#if defined(OSG_USE_SPROC)
#include <ulocks.h>
#endif

#include <map>

#include "OSGBaseThread.h"
#include "OSGBarrier.h"
#include "OSGCondVar.h"
#include "OSGLock.h"

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpBaseBaseMultiThreading
    \hideinhierarchy
 */

template <class MPFieldT>
class MPFieldStore
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef typename MPFieldT::Type MPFieldType;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructor                                */
    /*! \{                                                                 */

    MPFieldStore(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~MPFieldStore(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Get                                      */
    /*! \{                                                                 */

    MPFieldT *getMPField   (const Char8    *szName,
                            const Char8    *szTypeName);

    MPFieldT *findMPField  (const Char8    *szName);

    void      removeMPField(      MPFieldT *pField);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    void clear(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Find                                   */
    /*! \{                                                                 */

    MPFieldType *findMPFieldType(const Char8 *szName) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                      Types                                   */
    /*! \{                                                                 */

    typedef std::map<IDStringLink, MPFieldType  *>  MPFieldTypeMap;
    typedef typename MPFieldTypeMap::iterator       MPFieldTypeMapIt;

    typedef typename MPFieldTypeMap::const_iterator MPFieldTypeMapCIt;

    typedef std::map<IDStringLink, MPFieldT     *>  MPFieldMap;
    typedef typename MPFieldMap::iterator           MPFieldMapIt;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

    MPFieldTypeMap _mFieldTypeMap;
    MPFieldMap     _mFieldMap;

    UInt32 registerMPType(MPFieldType *pType);

    /*==========================  PRIVATE  ================================*/

  private:

    friend class ThreadManager;

    /*!\brief prohibit default function (move to 'public' if needed) */
    MPFieldStore   (const MPFieldStore &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const MPFieldStore &source);
};




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpBaseBaseMultiThreading
 */

class OSG_BASE_DLLMAPPING ThreadManager
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                      Types                                   */
    /*! \{                                                                 */

    typedef MPFieldStore<BaseThread> ThreadStore;
    typedef MPFieldStore<Barrier   > BarrierStore;
    typedef MPFieldStore<CondVar   > CondVarStore;
    typedef MPFieldStore<Lock      > LockStore;
    typedef MPFieldStore<LockPool  > LockPoolStore;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Set / Get                               */
    /*! \{                                                                 */

    static void           setAppThreadType(const Char8  *szAppThreadType);

    static ThreadManager *the             (      void                   );

    static BaseThread    *getAppThread    (      void                   );

    static void           setNumAspects   (      UInt32  uiNumApects    );
    static UInt32         getNumAspects   (      void                   );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name               Create Threading Element                       */
    /*! \{                                                                 */

    BaseThread   *getThread   (const Char8 *szName,
                               const Char8 *szTypeName = "OSGThread");
    Barrier      *getBarrier  (const Char8 *szName,
                               const Char8 *szTypeName = "OSGBarrier");
    CondVar      *getCondVar  (const Char8 *szName,
                               const Char8 *szTypeName = "OSGCondVar");
    Lock         *getLock     (const Char8 *szName,
                               const Char8 *szTypeName = "OSGLock");
    LockPool     *getLockPool (const Char8 *szName,
                               const Char8 *szTypeName = "OSGLockPool");

    BaseThread   *findThread  (const Char8 *szName);
    Barrier      *findBarrier (const Char8 *szName);
    CondVar      *findCondVar (const Char8 *szName);
    Lock         *findLock    (const Char8 *szName);
    LockPool     *findLockPool(const Char8 *szName);

#if defined(OSG_USE_SPROC)
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Set / Get                               */
    /*! \{                                                                 */

    usptr_t *getArena(void);
#endif

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    static bool   initialize          (void                     );
    static bool   terminate           (void                     );

           void   removeThread        (BaseThread     *pThread  );
           void   removeBarrier       (Barrier        *pBarrier );
           void   removeCondVar       (CondVar        *pCondVar );
           void   removeLock          (Lock           *pLock    );
           void   removeLockPool      (LockPool       *pLockPool);

           UInt32 registerThreadType  (MPThreadType   *pType    );
           UInt32 registerBarrierType (MPBarrierType  *pType    );
           UInt32 registerCondVarType (MPCondVarType  *pType    );
           UInt32 registerLockType    (MPLockType     *pType    );
           UInt32 registerLockPoolType(MPLockPoolType *pType    );

           bool   init                (void                     );
           bool   shutdown            (void                     );

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    ThreadManager(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~ThreadManager(void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    /*---------------------------------------------------------------------*/
    /*! \name                  Friend Classes                              */
    /*! \{                                                                 */

    friend class MPThreadType;
    friend class MPBarrierType;
    friend class MPCondVarType;
    friend class MPLockType;
    friend class MPLockPoolType;

    friend class BaseThread;
    friend class Barrier;
    friend class CondVar;
    friend class Lock;
    friend class LockPool;

    friend OSG_BASE_DLLMAPPING bool osgInit(Int32   argc, 
                                            Char8 **argv,
                                            UInt16  major, 
                                            UInt16  minor, 
                                            UInt16  release,
                                            bool    debug, 
                                            bool    dll, 
                                            bool    mt     );
    friend OSG_BASE_DLLMAPPING bool osgExit(void           );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Class Variable                             */
    /*! \{                                                                 */

    static ThreadManager   *_pThreadManager;
    static BaseThread      *_pAppThread;

    static bool             _bShutdownInProgress;

    static UInt32          _uiNumAspects;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                Instance Variables                            */
    /*! \{                                                                 */

           ThreadStore    _sThreadStore;
           BarrierStore   _sBarrierStore;
           CondVarStore   _sCondVarStore;
           LockStore      _sLockStore;
           LockPoolStore  _sLockPoolStore;

           Lock          *_storePLock;

    static Char8         *_szAppThreadType;

#if defined(OSG_USE_SPROC)
    usptr_t *_pArena;
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

    /*!\brief prohibit default function (move to 'public' if needed) */
    ThreadManager  (const ThreadManager &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const ThreadManager &source);
};

OSG_END_NAMESPACE

#include "OSGThreadManager.inl"

#define OSGTHREADMANAGER_HEADER_CVSID "@(#)$Id$"

#endif /* _OSGTHREADMANAGER_H_ */


