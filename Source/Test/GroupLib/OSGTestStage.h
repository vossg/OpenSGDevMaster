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

#ifndef _OSGTESTSTAGE_H_
#define _OSGTESTSTAGE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGTestStageBase.h"

OSG_BEGIN_NAMESPACE

class DrawEnv;

/*! \brief TestStage class. See \ref
           PageGroupTestStage for a description.
*/

class OSG_GROUP_DLLMAPPING TestStage : public TestStageBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef TestStageBase Inherited;
    typedef TestStage     Self;

    typedef PointerBuilder<TestStage>::ObjPtr           ObjPtr;
    typedef PointerBuilder<TestStage>::ObjPtrConst      ObjPtrConst;

    typedef PointerBuilder<TestStage>::ObjConstPtr      ObjConstPtr;
    typedef PointerBuilder<TestStage>::ObjConstPtrConst ObjConstPtrConst;

    typedef PointerBuilder<TestStage>::ObjPtrArg        ObjPtrArg;
    typedef PointerBuilder<TestStage>::ObjPtrConstArg   ObjPtrConstArg;

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    void enterCB(DrawEnv *pEnv);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in TestStageBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    TestStage(void);
    TestStage(const TestStage &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~TestStage(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class TestStageBase;

    template<class ContainerFactoryT>
    friend struct CPtrConstructionFunctions;

    template<class ContainerFactoryT>
    friend struct PtrConstructionFunctions;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const TestStage &source);
};

typedef TestStage *TestStageP;

typedef TestStage::ObjPtr           TestStagePtr;
typedef TestStage::ObjPtrConst      TestStagePtrConst;

typedef TestStage::ObjConstPtr      TestStageConstPtr;
typedef TestStage::ObjConstPtrConst TestStageConstPtrConst;

typedef TestStage::ObjPtrArg        TestStagePtrArg;
typedef TestStage::ObjPtrConstArg   TestStagePtrConstArg;

OSG_END_NAMESPACE

#include "OSGTestStageBase.inl"
#include "OSGTestStage.inl"

#endif /* _OSGTESTSTAGE_H_ */
