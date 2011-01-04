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

#ifndef _OSGWINDOWDRAWTASK_H_
#define _OSGWINDOWDRAWTASK_H_

#ifdef __sgi
#pragma once
#endif

#include "OSGDrawTask.h"

OSG_BEGIN_NAMESPACE

class Viewport;

/*! \ingroup GrpSystemMemoryObjects
    \ingroup GrpSystemRenderingBackendTasks
    \ingroup GrpLibOSGSystem
 */

class OSG_SYSTEM_DLLMAPPING WindowDrawTask : public DrawTask
{
    /*==========================  PUBLIC  =================================*/

  public:

    static const UInt32 Init              = Inherited::LastType + 1;
    static const UInt32 Activate          = Inherited::LastType + 2;
    static const UInt32 FrameInit         = Inherited::LastType + 3;
    static const UInt32 FrameExit         = Inherited::LastType + 4;
    static const UInt32 Swap              = Inherited::LastType + 5;
    static const UInt32 WaitAtBarrier     = Inherited::LastType + 6;
    static const UInt32 DeactivateAndWait = Inherited::LastType + 7;
    static const UInt32 LastType          = DeactivateAndWait;

    typedef boost::function<void (void)> GLInitFunctor;
    typedef DrawTask                     Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                   Statistic                                  */
    /*! \{                                                                 */

    WindowDrawTask(UInt32 uiType);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Access                                    */
    /*! \{                                                                 */

    virtual void execute(HardwareContext *pContext, DrawEnv *pEnv);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Access                                    */
    /*! \{                                                                 */

    void waitForBarrier(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Access                                    */
    /*! \{                                                                 */

    void setInitFunc            (GLInitFunctor oFunc);
    void setReinitExtFunctions  (bool          bVal );
    void setCreatePrivateContext(bool          bVal );

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

    BarrierRefPtr _pBarrier;
    GLInitFunctor _oInitFunc;

    bool          _bCreatePrivateContext;
    bool          _bReinitExtFunctions;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~WindowDrawTask(void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    /*! \brief prohibit default function (move to 'public' if needed) */
    WindowDrawTask(const WindowDrawTask &source);
    /*! \brief prohibit default function (move to 'public' if needed) */
    void operator =(const WindowDrawTask &source);
};

/*! \ingroup GrpSystemRenderingBackend
 */

typedef RefCountPtr<WindowDrawTask,
                    MemObjRefCountPolicy> WindowDrawTaskRefPtr;


/*! \ingroup GrpSystemMemoryObjects
    \ingroup GrpSystemRenderingBackendTasks
    \ingroup GrpLibOSGSystem
 */

class OSG_SYSTEM_DLLMAPPING ViewportDrawTask : public DrawTask
{
    /*==========================  PUBLIC  =================================*/

  public:

    static const UInt32 Foregrounds = Inherited::LastType + 1;
    static const UInt32 LastType    = Foregrounds;

    typedef DrawTask Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                   Statistic                                  */
    /*! \{                                                                 */

    ViewportDrawTask(Viewport *pPort, UInt32 uiType);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Access                                    */
    /*! \{                                                                 */

    virtual void execute(HardwareContext *pContext, DrawEnv *pEnv);

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

    Viewport *_pPort;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~ViewportDrawTask(void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    /*! \brief prohibit default function (move to 'public' if needed) */
    ViewportDrawTask(const ViewportDrawTask &source);
    /*! \brief prohibit default function (move to 'public' if needed) */
    void operator =(const ViewportDrawTask &source);
};

/*! \ingroup GrpSystemRenderingBackendTasks
 */

typedef RefCountPtr<ViewportDrawTask,
                    MemObjRefCountPolicy> ViewportDrawTaskRefPtr;

/*! \ingroup GrpSystemMemoryObjects
    \ingroup GrpSystemRenderingBackendTasks
    \ingroup GrpLibOSGSystem
 */

class OSG_SYSTEM_DLLMAPPING CallbackDrawTask : public BlockingDrawTask
{
    /*==========================  PUBLIC  =================================*/

  public:

    static const UInt32 Callback            = Inherited::LastType + 1;
    static const UInt32 LastType            = Callback;

    typedef BlockingDrawTask Inherited;

    typedef boost::function<void (HardwareContext *, 
                                  DrawEnv         *)> CallbackFunctor;

    /*---------------------------------------------------------------------*/
    /*! \name                   Statistic                                  */
    /*! \{                                                                 */

    CallbackDrawTask(UInt32 uiType);
    CallbackDrawTask(const CallbackFunctor &fCallback, UInt32 uiType);

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

    virtual ~CallbackDrawTask(void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    /*! \brief prohibit default function (move to 'public' if needed) */
    CallbackDrawTask(const CallbackDrawTask &source);
    /*! \brief prohibit default function (move to 'public' if needed) */
    void operator =(const CallbackDrawTask &source);
};

/*! \ingroup GrpSystemRenderingBackendTasks
 */

typedef RefCountPtr<CallbackDrawTask,
                    MemObjRefCountPolicy> CallbackDrawTaskRefPtr;


OSG_END_NAMESPACE

#include "OSGWindowDrawTask.inl"

#endif /* _OSGWINDOWDRAWTASK_H_ */
