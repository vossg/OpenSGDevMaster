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

#ifndef _OSGCOMPUTEALGORITHM_H_
#define _OSGCOMPUTEALGORITHM_H_
#ifdef __sgi
#pragma once
#endif

#include <queue>

#include "OSGComputeAlgorithmBase.h"
#include "OSGAction.h"
#include "OSGDrawTask.h"

OSG_BEGIN_NAMESPACE

class DrawEnv;
class Action;

//! Stage
//! \ingroup GrpSystemNodeCoresMisc

class OSG_CONTRIBCOMPUTEBASE_DLLMAPPING ComputeAlgorithm : 
    public ComputeAlgorithmBase
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin,
                         BitVector         detail);

    /*---------------------------------------------------------------------*/
    /*! \name                      Execute                                 */
    /*! \{                                                                 */

    virtual Action::ResultE renderEnter(Action          *pAction ) = 0;
    virtual Action::ResultE renderLeave(Action          *pAction ) = 0;
    virtual void            execute    (HardwareContext *pContext, 
                                        DrawEnv         *pEnv    ) = 0;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    virtual void dump(      UInt32    uiIndent = 0,
                      const BitVector bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef ComputeAlgorithmBase Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    ComputeAlgorithm(void);
    ComputeAlgorithm(const ComputeAlgorithm &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ComputeAlgorithm(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Draw                                       */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class ComputeAlgorithmBase;

    /*---------------------------------------------------------------------*/
    /*! \name                   thread local                               */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    load thread                               */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const ComputeAlgorithm &source);
};

typedef ComputeAlgorithm *ComputeAlgorithmP;

class OSG_CONTRIBCOMPUTEBASE_DLLMAPPING ComputeAlgorithmDrawTask : 
    public DrawTask
{
    /*==========================  PUBLIC  =================================*/

  public:

    static const UInt32 Algorithm            = Inherited::LastType + 1;
    static const UInt32 AlgorithmWithBarrier = Inherited::LastType + 2;
    static const UInt32 LastType             = AlgorithmWithBarrier;

    typedef DrawTask Inherited;


    /*---------------------------------------------------------------------*/
    /*! \name                   Statistic                                  */
    /*! \{                                                                 */

    ComputeAlgorithmDrawTask(UInt32 uiType);
    ComputeAlgorithmDrawTask(ComputeAlgorithmP pAlgorithm, UInt32 uiType);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Access                                    */
    /*! \{                                                                 */

    virtual void execute(HardwareContext *pContext, DrawEnv *pEnv);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Access                                    */
    /*! \{                                                                 */

    void activateBarrier(bool              bVal      );
    void setAlgorithm   (ComputeAlgorithmP pAlgorithm);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Access                                    */
    /*! \{                                                                 */

    void waitForBarrier(void);

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

    ComputeAlgorithmUnrecPtr _pAlgorithm;
    BarrierRefPtr            _pBarrier;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~ComputeAlgorithmDrawTask(void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    /*! \brief prohibit default function (move to 'public' if needed) */
    ComputeAlgorithmDrawTask(const ComputeAlgorithmDrawTask &source);
    /*! \brief prohibit default function (move to 'public' if needed) */
    void operator =(const ComputeAlgorithmDrawTask &source);
};

typedef RefCountPtr<ComputeAlgorithmDrawTask,
                    MemObjRefCountPolicy   > ComputeAlgorithmDrawTaskRefPtr;

OSG_END_NAMESPACE

#include "OSGComputeAlgorithmBase.inl"
#include "OSGComputeAlgorithm.inl"

#endif /* _OSGCOMPUTEALGORITHM_H_ */
