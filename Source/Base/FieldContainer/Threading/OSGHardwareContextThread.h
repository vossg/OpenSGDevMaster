/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
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

#ifndef _OSGHARDWARECONTEXTTHREAD_H_
#define _OSGHARDWARECONTEXTTHREAD_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGBaseDef.h"
#include "OSGThread.h"
#include "OSGHardwareContextTask.h"

OSG_BEGIN_NAMESPACE

class HardwareContext;

/*! \ingroup GrpBaseMemoryObjectsBase
    \ingroup GrpBaseHardwareContext
    \ingroup GrpLibOSGBase
*/

class OSG_BASE_DLLMAPPING HardwareContextThread : public Thread
{

    /*==========================  PUBLIC  =================================*/

  public:

    OSG_GEN_INTERNAL_MEMOBJPTR(HardwareContextThread);

    /*---------------------------------------------------------------------*/
    /*! \name                 Reference Counting                           */
    /*! \{                                                                 */

    static ObjTransitPtr          get (Char8 *szName, bool bGlobal);
    static HardwareContextThread *find(Char8 *szName              );

    /*---------------------------------------------------------------------*/
    /*! \name                 Reference Counting                           */
    /*! \{                                                                 */

    bool isRunning (void           );
    void endRunning(void           );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    void queueTask     (HardwareContextTask *pTask);
    void queueTaskFront(HardwareContextTask *pTask);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Debugging, don't use                         */
    /*! \{                                                                 */

    void dumpTasks(void);
    void runTasks (void);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef Thread             Inherited;

    static  MPThreadType      _type;

    bool                      _bRunning;
    DrawEnv                  *_pEnv;
    HardwareContextTaskQueue  _qTaskQueue;
    HardwareContext          *_pContext;

    /*---------------------------------------------------------------------*/
    /*! \name                 Reference Counting                           */
    /*! \{                                                                 */

    static BaseThread *create(const Char8  *szName, 
                                    UInt32  uiId,
                                    bool    bGlobal);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */
 
    HardwareContextThread(const Char8 *szName, UInt32 uiId, bool bGlobal);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~HardwareContextThread(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual void workProc(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    void setContext(HardwareContext *pContext);

    /*! \}                                                                 */
   /*==========================  PRIVATE  ================================*/

  private:

    friend class HardwareContext;

    /*!\brief prohibit default function (move to 'public' if needed) */
    HardwareContextThread(const HardwareContextThread &source);
    void operator =(const HardwareContextThread &source);
};

OSG_GEN_MEMOBJPTR(HardwareContextThread);

OSG_END_NAMESPACE

#include "OSGHardwareContextThread.inl"

#endif /* _OSGHARDWARECONTEXTTHREAD_H_ */
