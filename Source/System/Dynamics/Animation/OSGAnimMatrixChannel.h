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

#ifndef _OSGANIMMATRIXCHANNEL_H_
#define _OSGANIMMATRIXCHANNEL_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGAnimMatrixChannelBase.h"
#include "OSGAnimMatrixDataSource.h"

OSG_BEGIN_NAMESPACE

/*! \brief AnimMatrixChannel class. See \ref
           PageDynamicsAnimMatrixChannel for a description.
*/

class OSG_DYNAMICS_DLLMAPPING AnimMatrixChannel : public AnimMatrixChannelBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef AnimMatrixChannelBase Inherited;
    typedef AnimMatrixChannel     Self;

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

    // Variables should all be in AnimMatrixChannelBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    AnimMatrixChannel(void);
    AnimMatrixChannel(const AnimMatrixChannel &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~AnimMatrixChannel(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class AnimMatrixChannelBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const AnimMatrixChannel &source);
};

typedef AnimMatrixChannel *AnimMatrixChannelP;

OSG_END_NAMESPACE

#include "OSGAnimMatrixChannelBase.inl"
#include "OSGAnimMatrixChannel.inl"

#endif /* _OSGANIMMATRIXCHANNEL_H_ */
