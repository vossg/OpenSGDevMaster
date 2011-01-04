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

#ifndef _OSGDRAWTASK_H_
#define _OSGDRAWTASK_H_

#ifdef __sgi
#pragma once
#endif

#include "OSGSystemDef.h"
#include "OSGHardwareContextTask.h"

#include <deque>

OSG_BEGIN_NAMESPACE

class DrawEnv;
class Window;

/*! \ingroup GrpSystemMemoryObjects
    \ingroup GrpSystemRenderingBackendTasks
    \ingroup GrpLibOSGSystem
*/

class OSG_SYSTEM_DLLMAPPING DrawTask : public HardwareContextTask
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef HardwareContextTask Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                   Statistic                                  */
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

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    DrawTask(UInt32 uiTaskType);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~DrawTask(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    void setupContext   (Window *pWin);
    void finalizeContext(Window *pWin);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    /*! \brief prohibit default function (move to 'public' if needed) */
    DrawTask(const DrawTask &source);
    /*! \brief prohibit default function (move to 'public' if needed) */
    void operator =(const DrawTask &source);
};


/*! \ingroup GrpSystemMemoryObjects
    \ingroup GrpSystemRenderingBackendTasks
    \ingroup GrpLibOSGSystem
 */

class OSG_SYSTEM_DLLMAPPING BlockingDrawTask : public DrawTask
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef DrawTask Inherited;

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

    BlockingDrawTask(UInt32 uiTaskType);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~BlockingDrawTask(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    /*! \brief prohibit default function (move to 'public' if needed) */
    BlockingDrawTask(const BlockingDrawTask &source);
    /*! \brief prohibit default function (move to 'public' if needed) */
    void operator =(const BlockingDrawTask &source);
};

/*! \ingroup GrpSystemRenderingBackendTasks
 */

typedef RefCountPtr<DrawTask,
                    MemObjRefCountPolicy> DrawTaskRefPtr;

/*! \ingroup GrpSystemRenderingBackendTasks
 */

typedef RefCountPtr<BlockingDrawTask,
                    MemObjRefCountPolicy> BlockingDrawTaskRefPtr;

/*! \ingroup GrpSystemRenderingBackendTasks
 */

typedef TransitPtr<DrawTask        > DrawTaskTransitPtr;

/*! \ingroup GrpSystemRenderingBackendTasks
 */

typedef TransitPtr<BlockingDrawTask> BlockingDrawTaskTransitPtr;

/*! \ingroup GrpSystemRenderingBackendFieldTraits
 */

template <>
struct FieldTraits<DrawTaskRefPtr, 0> : 
    public FieldTraitsTemplateBase<DrawTaskRefPtr, 0>
{
    static  DataType                       _type;                       
    typedef FieldTraits<DrawTaskRefPtr, 0>  Self;

    enum { Convertible = Self::NotConvertible };

    static OSG_SYSTEM_DLLMAPPING DataType &getType (void);

    static const char *getMName(void) { return "MFDrawTask"; }

    static UInt32 getBinSize(const DrawTaskRefPtr *,
                                   UInt32          )
    {
        return 0;
    }

    static void copyToBin(      BinaryDataHandler &,
                          const DrawTaskRefPtr    *,
                                UInt32             )
    {
        SWARNING << "FieldTraits<DrawTaskRefPtr>::copyToBin: Not supported."
                 << std::endl;
    }

    static void copyFromBin(BinaryDataHandler &,
                            DrawTaskRefPtr    *,
                            UInt32             )
    {
        SWARNING << "FieldTraits<DrawTaskRefPtr>::copyFromBin: Not supported."
                 << std::endl;
    }
};

#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpSystemRenderingBackendFieldMFields */
typedef MField<DrawTaskRefPtr, 0> MFDrawTask;
#else
/*! \ingroup GrpSystemRenderingBackendFieldMFields */
struct  MFDrawTask : public MField<DrawTaskRefPtr, 0> {};
#endif

OSG_END_NAMESPACE

#include "OSGDrawTask.inl"

#endif /* _OSGDRAWTASK_H_ */
