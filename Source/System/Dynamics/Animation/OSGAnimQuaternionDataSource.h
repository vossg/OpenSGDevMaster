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

#ifndef _OSGANIMQUATERNIONDATASOURCE_H_
#define _OSGANIMQUATERNIONDATASOURCE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGAnimQuaternionDataSourceBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief AnimQuaternionDataSource class. See \ref
           PageDynamicsAnimQuaternionDataSource for a description.
*/

class OSG_DYNAMICS_DLLMAPPING AnimQuaternionDataSource : public AnimQuaternionDataSourceBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef AnimQuaternionDataSourceBase Inherited;
    typedef AnimQuaternionDataSource     Self;

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

    virtual AnimChannelTransitPtr createChannel(void) const;
    virtual AnimBlenderTransitPtr createBlender(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Evaluation                                 */
    /*! \{                                                                 */

    void evaluate(Quaternion &outValue, Real32 inValue);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in AnimQuaternionDataSourceBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    AnimQuaternionDataSource(void);
    AnimQuaternionDataSource(const AnimQuaternionDataSource &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~AnimQuaternionDataSource(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Evaluation                                 */
    /*! \{                                                                 */

    void evalStep        (Quaternion                     &outValue,
                          Real32                          inValue,
                          MFInValuesType::const_iterator  ivRIt    );
    void evalLinear      (Quaternion                     &outValue, 
                          Real32                          inValue,
                          MFInValuesType::const_iterator  ivRIt    );

    void extrapolateFront(Quaternion &outValue, Real32 inValue);
    void extrapolateBack (Quaternion &outValue, Real32 inValue);

    void checkDataConsistency(void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class AnimQuaternionDataSourceBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const AnimQuaternionDataSource &source);
};

typedef AnimQuaternionDataSource *AnimQuaternionDataSourceP;

OSG_END_NAMESPACE

#include "OSGAnimQuaternionDataSourceBase.inl"
#include "OSGAnimQuaternionDataSource.inl"

#endif /* _OSGANIMQUATERNIONDATASOURCE_H_ */
