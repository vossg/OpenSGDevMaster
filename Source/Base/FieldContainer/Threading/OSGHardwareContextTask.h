/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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

#ifndef _OSGHARDWARECONTEXTTASK_H_
#define _OSGHARDWARECONTEXTTASK_H_

#ifdef __sgi
#pragma once
#endif

#include "OSGMemoryObject.h"
#include "OSGTransitPtr.h"
#include "OSGBaseDef.h"
#include "OSGLock.h"
#include "OSGSemaphore.h"
#include "OSGBarrier.h"
#include "OSGMField.h"

#include <deque>

OSG_BEGIN_NAMESPACE

class DrawEnv;
class HardwareContext;

/*! \ingroup GrpBaseMemoryObjectsBase
    \ingroup GrpBaseHardwareContext
    \ingroup GrpLibOSGBase
*/

class OSG_BASE_DLLMAPPING HardwareContextTask : public MemoryObject
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef MemoryObject Inherited;

    static const UInt32 EndThread = 0x0001;
    static const UInt32 LastType  = 0x0001;

    /*---------------------------------------------------------------------*/
    /*! \name                   Statistic                                  */
    /*! \{                                                                 */

    virtual void execute(HardwareContext *pContext, DrawEnv *pEnv) = 0;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Access                                    */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Access                                    */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Access                                    */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Access                                    */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Debugging                                  */
    /*! \{                                                                 */

    virtual void dump(UInt32 uiIndent) = 0;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    UInt32 _uiTypeTask;

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    HardwareContextTask(UInt32 uiTaskType);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~HardwareContextTask(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    /*! \brief prohibit default function (move to 'public' if needed) */
    HardwareContextTask(const HardwareContextTask &source);
    /*! \brief prohibit default function (move to 'public' if needed) */
    void operator =(const HardwareContextTask &source);
};

/*! \ingroup GrpBaseMemoryObjectsBase
    \ingroup GrpBaseHardwareContext
    \ingroup GrpLibOSGBase
*/

class OSG_BASE_DLLMAPPING BlockingTask : public HardwareContextTask
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef HardwareContextTask Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                   Statistic                                  */
    /*! \{                                                                 */

    void activateBarrier(bool bVal);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Access                                    */
    /*! \{                                                                 */

    void setNumWaitFor (UInt32 uiWaitees);
    void waitForBarrier(void            );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Access                                    */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Access                                    */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Access                                    */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Debugging                                  */
    /*! \{                                                                 */

    virtual void dump(UInt32 uiIndent) = 0;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    bool          _bBarrierActive;
    BarrierRefPtr _pBarrier;

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    BlockingTask(UInt32 uiTaskType);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~BlockingTask(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    /*! \brief prohibit default function (move to 'public' if needed) */
    BlockingTask(const BlockingTask &source);
    /*! \brief prohibit default function (move to 'public' if needed) */
    void operator =(const BlockingTask &source);
};

/*! \ingroup GrpBaseMemoryObjectsBase
    \ingroup GrpBaseHardwareContext
    \ingroup GrpLibOSGBase
*/

class OSG_BASE_DLLMAPPING CallbackTask : public BlockingTask
{
    /*==========================  PUBLIC  =================================*/

  public:

    static const UInt32 Callback            = Inherited::LastType + 1;
    static const UInt32 LastType            = Callback;

    typedef BlockingTask Inherited;

    typedef boost::function<void (HardwareContext *, 
                                  DrawEnv         *)> CallbackFunctor;

    /*---------------------------------------------------------------------*/
    /*! \name                   Statistic                                  */
    /*! \{                                                                 */

    CallbackTask(UInt32 uiType);
    CallbackTask(const CallbackFunctor &fCallback, UInt32 uiType);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Access                                    */
    /*! \{                                                                 */

    virtual void execute(HardwareContext *pContext, DrawEnv *pEnv);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Access                                    */
    /*! \{                                                                 */

    void setCallback(const CallbackFunctor &fCallback);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Access                                    */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Access                                    */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Access                                    */
    /*! \{                                                                 */

    virtual void dump(UInt32 uiIndent);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    CallbackFunctor _fCallback;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~CallbackTask(void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    /*! \brief prohibit default function (move to 'public' if needed) */
    CallbackTask(const CallbackTask &source);
    /*! \brief prohibit default function (move to 'public' if needed) */
    void operator =(const CallbackTask &source);
};

/*! \ingroup GrpBaseHardwareContext
 */

typedef RefCountPtr<HardwareContextTask,
                    MemObjRefCountPolicy> HardwareContextTaskRefPtr;

/*! \ingroup GrpBaseHardwareContext
 */

typedef RefCountPtr<BlockingTask,
                    MemObjRefCountPolicy> BlockingTaskRefPtr;

/*! \ingroup GrpBaseHardwareContext
 */

typedef RefCountPtr<CallbackTask,
                    MemObjRefCountPolicy> CallbackTaskRefPtr;


/*! \ingroup GrpBaseHardwareContext
 */

typedef TransitPtr<HardwareContextTask> HardwareContextTaskTransitPtr;

/*! \ingroup GrpBaseHardwareContext
 */

typedef TransitPtr<BlockingTask>        BlockingTaskTransitPtr;

/*! \ingroup GrpBaseHardwareContext
 */

typedef TransitPtr<CallbackTask>        CallbackTaskTransitPtr;

/*! \ingroup GrpBaseHardwareContextFieldTraits
    \ingroup GrpLibOSGBase
 */

template <>
struct FieldTraits<HardwareContextTaskRefPtr> : 
    public FieldTraitsTemplateBase<HardwareContextTaskRefPtr>
{
  private:

    static  DataType                               _type;

  public:

    typedef FieldTraits<HardwareContextTaskRefPtr>  Self;

    enum { Convertible = Self::NotConvertible };

    OSG_BASE_DLLMAPPING
    static DataType &getType (void);

    static const char *getMName(void) { return "MFHardwareContextTask"; }

    static UInt32 getBinSize(const HardwareContextTaskRefPtr *,
                                   UInt32          )
    {
        return 0;
    }

    static void copyToBin(      BinaryDataHandler         &,
                          const HardwareContextTaskRefPtr *,
                                UInt32                     )
    {
        SWARNING << "FieldTraits<HardwareContextTaskRefPtr>::copyToBin: "
                 << "Not supported."
                 << std::endl;
    }

    static void copyFromBin(BinaryDataHandler         &,
                            HardwareContextTaskRefPtr *,
                            UInt32                     )
    {
        SWARNING << "FieldTraits<HardwareContextTaskRefPtr>::copyFromBin: "
                 << "Not supported."
                 << std::endl;
    }
};

#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpBaseHardwareContextFieldMFields */
typedef MField<HardwareContextTaskRefPtr, 0> MFHardwareContextTask;
#else // these are the doxygen hacks
/*! \ingroup GrpBaseHardwareContextFieldMFields */
typedef MFHardwareContextTask : public MField<HardwareContextTaskRefPtr, 0> {};
#endif // these are the doxygen hacks

/*! \ingroup GrpBaseMemoryObjectsBase
    \ingroup GrpBaseHardwareContext
    \ingroup GrpLibOSGBase
    \nohierarchy
*/

class OSG_BASE_DLLMAPPING HardwareContextTaskQueue
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Statistic                                  */
    /*! \{                                                                 */

    void                          queueTask     (HardwareContextTask *pTask);
    void                          queueTaskFront(HardwareContextTask *pTask);
    HardwareContextTaskTransitPtr popTask       (void           );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    HardwareContextTaskQueue(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~HardwareContextTaskQueue(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Debugging                                  */
    /*! \{                                                                 */

    // Implementation in OSGWindow.inl
    void dumpQueue       (void                     );
    void runAndClearQueue(HardwareContext *pContext, 
                          DrawEnv         *pEnv    );

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef std::deque<HardwareContextTaskRefPtr> TaskStore;

    TaskStore       _qTaskStore;
    LockRefPtr      _pStoreLock;
    SemaphoreRefPtr _pStoreSema;

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    /*! \brief prohibit default function (move to 'public' if needed) */
    HardwareContextTaskQueue(const HardwareContextTaskQueue &source);
    /*! \brief prohibit default function (move to 'public' if needed) */
    void operator =(const HardwareContextTaskQueue &source);
};


OSG_END_NAMESPACE

#include "OSGHardwareContextTask.inl"

#endif /* _OSGHARDWARECONTEXTTASK_H_ */
