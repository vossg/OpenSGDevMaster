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

#ifndef _OSGANIMQUATERNIONCHANNEL_H_
#define _OSGANIMQUATERNIONCHANNEL_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGAnimQuaternionChannelBase.h"
#include "OSGAnimQuaternionDataSource.h"

OSG_BEGIN_NAMESPACE

/*! \brief AnimQuaternionChannel class. See \ref
           PageDynamicsAnimQuaternionChannel for a description.
*/

class OSG_DYNAMICS_DLLMAPPING AnimQuaternionChannel : public AnimQuaternionChannelBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef AnimQuaternionChannelBase Inherited;
    typedef AnimQuaternionChannel     Self;

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin,
                         BitVector         details    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Evaluation                                 */
    /*! \{                                                                 */

    virtual void evaluate(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in AnimQuaternionChannelBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    AnimQuaternionChannel(void);
    AnimQuaternionChannel(const AnimQuaternionChannel &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~AnimQuaternionChannel(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class AnimQuaternionChannelBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const AnimQuaternionChannel &source);
};

typedef AnimQuaternionChannel *AnimQuaternionChannelP;

OSG_END_NAMESPACE

#include "OSGAnimQuaternionChannelBase.inl"
#include "OSGAnimQuaternionChannel.inl"

#endif /* _OSGANIMQUATERNIONCHANNEL_H_ */
