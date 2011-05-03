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
#include "OSGLog.h"

#if defined(OSG_USE_SPROC)
#include <ulocks.h>
#endif

#include <map>

#include "OSGBaseThread.h"
#include "OSGBarrier.h"
#include "OSGCondVar.h"
#include "OSGLock.h"
#include "OSGSemaphore.h"

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpBaseMultiThreading
    \ingroup GrpLibOSGBase
    \nohierarchy
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
                            const Char8    *szTypeName,
                                  bool      bGlobal   );

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

    typedef std::map<std::string, MPFieldType   *>  MPFieldTypeMap;
    typedef typename MPFieldTypeMap::iterator       MPFieldTypeMapIt;

    typedef typename MPFieldTypeMap::const_iterator MPFieldTypeMapCIt;

    typedef std::map<std::string, MPFieldT      *>  MPFieldMap;
    typedef typename MPFieldMap::iterator           MPFieldMapIt;

    typedef typename MPFieldMap::const_iterator     MPFieldMapCIt;

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

/*! \ingroup GrpBaseMultiThreading
    \ingroup GrpLibOSGBase
    \nohierarchy
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
    typedef MPFieldStore<Semaphore > SemaphoreStore;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Set / Get                               */
    /*! \{                                                                 */

    static void           setAppThreadType(const Char8  *szAppThreadType);

    static ThreadManager *the             (      void                   );

    static BaseThread    *getAppThread    (      void                   );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name               Create Threading Element                       */
    /*! \{                                                                 */

    // bGlobal is passed as UInt32 because Char8 * gets autoconverted to
    // bool and that would allow existing code to silently compile

    BaseThreadTransitPtr getThread    (const Char8 *szName,
                                             UInt32 bGlobal,
                                       const Char8 *szTypeName = "OSGThread");
    BarrierTransitPtr    getBarrier   (const Char8 *szName,
                                             UInt32 bGlobal,
                                       const Char8 *szTypeName = "OSGBarrier");
    CondVarTransitPtr    getCondVar   (const Char8 *szName,
                                             UInt32 bGlobal,
                                       const Char8 *szTypeName = "OSGCondVar");
    LockTransitPtr       getLock      (const Char8 *szName,
                                             UInt32 bGlobal,
                                       const Char8 *szTypeName = "OSGLock");
    LockPoolTransitPtr   getLockPool  (const Char8 *szName,
                                             UInt32 bGlobal,
                                       const Char8 *szTypeName = "OSGLockPool");
    SemaphoreTransitPtr  getSemaphore (const Char8 *szName,
                                             UInt32 bGlobal,
                                       const Char8 *szTypeName ="OSGSemaphore");

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Debug                                 */
    /*! \{                                                                 */

    BaseThread *findThread   (const Char8 *szName);
    Barrier    *findBarrier  (const Char8 *szName);
    CondVar    *findCondVar  (const Char8 *szName);
    Lock       *findLock     (const Char8 *szName);
    LockPool   *findLockPool (const Char8 *szName);
    Semaphore  *findSemaphore(const Char8 *szName);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Debug                                 */
    /*! \{                                                                 */

    void remove(BaseThread *pThread   );
    void remove(Barrier    *pBarrier  );
    void remove(CondVar    *pCondVar  );
    void remove(Lock       *pLock     );
    void remove(LockPool   *pLockPool );
    void remove(Semaphore  *pSemaphore);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Debug                                 */
    /*! \{                                                                 */

    void dump(void);

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

    static bool   initialize           (void                      ) ;
    static bool   terminate            (void                      );

           UInt32 registerThreadType   (MPThreadType    *pType    );
           UInt32 registerBarrierType  (MPBarrierType   *pType    );
           UInt32 registerCondVarType  (MPCondVarType   *pType    );
           UInt32 registerLockType     (MPLockType      *pType    );
           UInt32 registerLockPoolType (MPLockPoolType  *pType    );
           UInt32 registerSemaphoreType(MPSemaphoreType *pType    );

           bool   init                 (void                      );
           bool   shutdown             (void                      );

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
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

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
    friend class MPSemaphoreType;

    friend class BaseThread;
    friend class Barrier;
    friend class CondVar;
    friend class Lock;
    friend class LockPool;
    friend class Semaphore;

    friend OSG_BASE_DLLMAPPING bool osgDoInit(Int32   argc, 
                                              Char8 **argv,
                                              UInt16  major, 
                                              UInt16  minor, 
                                              UInt16  release,
                                              bool    debug, 
                                              bool    dll, 
                                              bool    mt     );
    friend OSG_BASE_DLLMAPPING bool osgExit  (void           );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Class Variable                             */
    /*! \{                                                                 */

    static ThreadManager    *_pThreadManager;
    static BaseThreadRefPtr  _pAppThread;

    static bool              _bShutdownInProgress;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                Instance Variables                            */
    /*! \{                                                                 */

           ThreadStore    _sThreadStore;
           BarrierStore   _sBarrierStore;
           CondVarStore   _sCondVarStore;
           LockStore      _sLockStore;
           LockPoolStore  _sLockPoolStore;
           SemaphoreStore _sSemaphoreStore;

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

#endif /* _OSGTHREADMANAGER_H_ */


