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

#ifndef _OSGSCREENLOD_H_
#define _OSGSCREENLOD_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGScreenLODBase.h"
#include "OSGAction.h"
#include "OSGCamera.h"
#include "OSGViewport.h"
#include "OSGDrawEnv.h"
#include "OSGDrawActionBase.h"
#include "OSGGeoStatsAttachment.h"

OSG_BEGIN_NAMESPACE

/*! \brief ScreenLOD class. See \ref 
           PageGroupScreenLOD for a description.
*/

class OSG_RENDERTRAV_DLLMAPPING ScreenLOD : public ScreenLODBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef ScreenLODBase Inherited;
    typedef ScreenLOD     Self;

    typedef PointerBuilder<ScreenLOD>::ObjPtr           ObjPtr;
    typedef PointerBuilder<ScreenLOD>::ObjPtrConst      ObjPtrConst;

    typedef PointerBuilder<ScreenLOD>::ObjConstPtr      ObjConstPtr;
    typedef PointerBuilder<ScreenLOD>::ObjConstPtrConst ObjConstPtrConst;

    typedef PointerBuilder<ScreenLOD>::ObjPtrArg        ObjPtrArg;
    typedef PointerBuilder<ScreenLOD>::ObjPtrConstArg   ObjPtrConstArg;

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField, 
                         UInt32            origin    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in ScreenLODBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ScreenLOD(void);
    ScreenLOD(const ScreenLOD &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ScreenLOD(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Draw                                       */
    /*! \{                                                                 */
    
    ActionBase::ResultE renderEnter( Action* action );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class ScreenLODBase;

    template<class ContainerFactoryT>
    friend struct CPtrConstructionFunctions;

    template<class ContainerFactoryT>
    friend struct PtrConstructionFunctions;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ScreenLOD &source);
};

typedef ScreenLOD *ScreenLODP;

typedef ScreenLOD::ObjPtr           ScreenLODPtr;
typedef ScreenLOD::ObjPtrConst      ScreenLODPtrConst;

typedef ScreenLOD::ObjConstPtr      ScreenLODConstPtr;
typedef ScreenLOD::ObjConstPtrConst ScreenLODConstPtrConst;

typedef ScreenLOD::ObjPtrArg        ScreenLODPtrArg;
typedef ScreenLOD::ObjPtrConstArg   ScreenLODPtrConstArg;

OSG_END_NAMESPACE

#include "OSGScreenLODBase.inl"
#include "OSGScreenLOD.inl"

#define OSGSCREENLOD_HEADER_CVSID "@(#)$Id: FCTemplate_h.h 106 2006-09-14 03:15:53Z dirk $"

#endif /* _OSGSCREENLOD_H_ */
