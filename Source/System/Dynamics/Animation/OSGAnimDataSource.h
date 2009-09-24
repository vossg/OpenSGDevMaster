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

#ifndef _OSGANIMDATASOURCE_H_
#define _OSGANIMDATASOURCE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGAnimDataSourceBase.h"

OSG_BEGIN_NAMESPACE

// forward decl
class AnimChannel;
OSG_GEN_CONTAINERPTR(AnimChannel);

class AnimBlender;
OSG_GEN_CONTAINERPTR(AnimBlender);

/*! \brief AnimDataSource class. See \ref
           PageDynamicsAnimDataSource for a description.
*/

class OSG_DYNAMICS_DLLMAPPING AnimDataSource : public AnimDataSourceBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef AnimDataSourceBase Inherited;
    typedef AnimDataSource     Self;

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin,
                         BitVector         details    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Factory                                  */
    /*! \{                                                                 */

    virtual AnimChannelTransitPtr createChannel(void) const = 0;
    virtual AnimBlenderTransitPtr createBlender(void) const = 0;


    virtual Real32 getLength(void) const = 0;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in AnimDataSourceBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    AnimDataSource(void);
    AnimDataSource(const AnimDataSource &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~AnimDataSource(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class AnimDataSourceBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const AnimDataSource &source);
};

typedef AnimDataSource *AnimDataSourceP;

OSG_END_NAMESPACE

#include "OSGAnimDataSourceBase.inl"
#include "OSGAnimDataSource.inl"

#endif /* _OSGANIMDATASOURCE_H_ */
