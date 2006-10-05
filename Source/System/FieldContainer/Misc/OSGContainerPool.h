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

#ifndef _OSGCONTAINERPOOL_H_
#define _OSGCONTAINERPOOL_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGContainerPoolBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief ContainerPool class. See \ref 
           PageSystemContainerPool for a description.
*/

class OSG_SYSTEM_DLLMAPPING ContainerPool : public ContainerPoolBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef ContainerPoolBase Inherited;
    typedef ContainerPool     Self;

    typedef PointerBuilder<ContainerPool>::ObjPtr           ObjPtr;
    typedef PointerBuilder<ContainerPool>::ObjPtrConst      ObjPtrConst;

    typedef PointerBuilder<ContainerPool>::ObjConstPtr      ObjConstPtr;
    typedef PointerBuilder<ContainerPool>::ObjConstPtrConst ObjConstPtrConst;

    typedef PointerBuilder<ContainerPool>::ObjPtrArg        ObjPtrArg;
    typedef PointerBuilder<ContainerPool>::ObjPtrConstArg   ObjPtrConstArg;

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField, 
                         UInt32            origin    );

    /*! \}
    /*---------------------------------------------------------------------*/
    /*! \name                    Access                                    */
    /*! \{                                                                 */

    void addContainer(FieldContainerPtr container);
    bool subContainer(FieldContainerPtr container);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in ContainerPoolBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ContainerPool(void);
    ContainerPool(const ContainerPool &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ContainerPool(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class ContainerPoolBase;

    template<class ContainerFactoryT>
    friend struct CPtrConstructionFunctions;

    template<class ContainerFactoryT>
    friend struct PtrConstructionFunctions;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ContainerPool &source);
};

typedef ContainerPool *ContainerPoolP;

typedef ContainerPool::ObjPtr           ContainerPoolPtr;
typedef ContainerPool::ObjPtrConst      ContainerPoolPtrConst;

typedef ContainerPool::ObjConstPtr      ContainerPoolConstPtr;
typedef ContainerPool::ObjConstPtrConst ContainerPoolConstPtrConst;

typedef ContainerPool::ObjPtrArg        ContainerPoolPtrArg;
typedef ContainerPool::ObjPtrConstArg   ContainerPoolPtrConstArg;

OSG_END_NAMESPACE

#include "OSGContainerPoolBase.inl"
#include "OSGContainerPool.inl"

#define OSGCONTAINERPOOL_HEADER_CVSID "@(#)$Id: FCTemplate_h.h 106 2006-09-14 03:15:53Z dirk $"

#endif /* _OSGCONTAINERPOOL_H_ */
