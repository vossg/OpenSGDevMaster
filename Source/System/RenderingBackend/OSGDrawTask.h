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

#include "OSGMemoryObject.h"
#include "OSGTransitPtr.h"
#include "OSGSystemDef.h"
#include "OSGLock.h"
#include "OSGSemaphore.h"
#include "OSGMField.h"

#include <deque>

OSG_BEGIN_NAMESPACE

class DrawEnv;

/*! \ingroup GrpSystemRenderingBackend
*/

class OSG_SYSTEM_DLLMAPPING DrawTask : public MemoryObject
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef MemoryObject Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                   Statistic                                  */
    /*! \{                                                                 */

    virtual void execute(DrawEnv *pEnv) = 0;

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
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    DrawTask(void);

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
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~DrawTask(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    /*! \brief prohibit default function (move to 'public' if needed) */
    DrawTask(const DrawTask &source);
    /*! \brief prohibit default function (move to 'public' if needed) */
    void operator =(const DrawTask &source);
};

typedef RefCountPtr<DrawTask,
                    MemObjRefCountPolicy> DrawTaskRefPtr;

typedef TransitPtr<DrawTask> DrawTaskTransitPtr;

template <>
struct FieldTraits<DrawTaskRefPtr, 0> : 
    public FieldTraitsTemplateBase<DrawTaskRefPtr, 0>
{
    static  DataType                       _type;                       
    typedef FieldTraits<DrawTaskRefPtr, 0>  Self;

    enum { Convertible = Self::NotConvertible };

    OSG_SYSTEM_DLLMAPPING
    static DataType &getType (void);

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

typedef MField<DrawTaskRefPtr, 0> MFDrawTask;

/*! \ingroup GrpSystemRenderingBackend
*/

class OSG_SYSTEM_DLLMAPPING DrawTaskQueue
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Statistic                                  */
    /*! \{                                                                 */

    void               queueTask     (DrawTask *pTask);
    void               queueTaskFront(DrawTask *pTask);
    DrawTaskTransitPtr popTask       (void           );

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

    DrawTaskQueue(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~DrawTaskQueue(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Debugging                                  */
    /*! \{                                                                 */

    void dumpQueue       (void         );
    void runAndClearQueue(DrawEnv *pEnv);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef std::deque<DrawTaskRefPtr> TaskStore;

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
    DrawTaskQueue(const DrawTaskQueue &source);
    /*! \brief prohibit default function (move to 'public' if needed) */
    void operator =(const DrawTaskQueue &source);
};


OSG_END_NAMESPACE

#include "OSGDrawTask.inl"

#endif /* _OSGDRAWTASK_H_ */
