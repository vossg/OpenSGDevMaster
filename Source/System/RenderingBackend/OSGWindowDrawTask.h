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
#include "OSGBarrier.h"

OSG_BEGIN_NAMESPACE

class Viewport;

class OSG_SYSTEM_DLLMAPPING WindowDrawTask : public DrawTask
{
    /*==========================  PUBLIC  =================================*/

  public:

    enum TaskType
    {
        Init        = 0x0001,
        Activate,
        FrameInit,
        FrameExit,
        Swap,
        WaitAtBarrier,
        EndThread
    };

    typedef boost::function<void (void)> GLInitFunctor;
    typedef DrawTask                     Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                   Statistic                                  */
    /*! \{                                                                 */

    WindowDrawTask(TaskType eType);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Access                                    */
    /*! \{                                                                 */

    virtual void execute(DrawEnv *pEnv);

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

    TaskType      _eTaskType;
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

typedef RefCountPtr<WindowDrawTask,
                    MemObjRefCountPolicy> WindowDrawTaskRefPtr;



class OSG_SYSTEM_DLLMAPPING ViewportDrawTask : public DrawTask
{
    /*==========================  PUBLIC  =================================*/

  public:

    enum TaskType
    {
        Foregrounds = 0x0001
    };

    typedef DrawTask Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                   Statistic                                  */
    /*! \{                                                                 */

    ViewportDrawTask(Viewport *pPort, TaskType eType);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Access                                    */
    /*! \{                                                                 */

    virtual void execute(DrawEnv *pEnv);

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

    TaskType  _eTaskType;
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

typedef RefCountPtr<ViewportDrawTask,
                    MemObjRefCountPolicy> ViewportDrawTaskRefPtr;

class OSG_SYSTEM_DLLMAPPING CallbackDrawTask : public DrawTask
{
    /*==========================  PUBLIC  =================================*/

  public:

    enum TaskType
    {
        Callback = 0x0001
    };

    typedef DrawTask Inherited;

    typedef boost::function<void (DrawEnv *)> CallbackFunctor;

    /*---------------------------------------------------------------------*/
    /*! \name                   Statistic                                  */
    /*! \{                                                                 */

    CallbackDrawTask(const CallbackFunctor &fCallback, TaskType eType);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Access                                    */
    /*! \{                                                                 */

    virtual void execute(DrawEnv *pEnv);

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

    TaskType        _eTaskType;
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

typedef RefCountPtr<CallbackDrawTask,
                    MemObjRefCountPolicy> CallbackDrawTaskRefPtr;


OSG_END_NAMESPACE

#include "OSGWindowDrawTask.inl"

#endif /* _OSGWINDOWDRAWTASK_H_ */
