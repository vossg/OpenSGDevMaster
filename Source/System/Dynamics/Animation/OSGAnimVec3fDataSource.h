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

#ifndef _OSGANIMVEC3FDATASOURCE_H_
#define _OSGANIMVEC3FDATASOURCE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGAnimVec3fDataSourceBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief AnimVec3fDataSource class. See \ref
           PageDynamicsAnimVec3fDataSource for a description.
*/

class OSG_DYNAMICS_DLLMAPPING AnimVec3fDataSource : public AnimVec3fDataSourceBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef AnimVec3fDataSourceBase Inherited;
    typedef AnimVec3fDataSource     Self;

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

    void evaluate(Vec3f &outValue, Real32 inValue);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in AnimVec3fDataSourceBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    AnimVec3fDataSource(void);
    AnimVec3fDataSource(const AnimVec3fDataSource &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~AnimVec3fDataSource(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Evaluation                                 */
    /*! \{                                                                 */

    void evalStep        (Vec3f                          &outValue,
                          Real32                          inValue,
                          MFInValuesType::const_iterator  ivRIt    );
    void evalLinear      (Vec3f                          &outValue, 
                          Real32                          inValue,
                          MFInValuesType::const_iterator  ivRIt    );

    void extrapolateFront(Vec3f &outValue, Real32 inValue);
    void extrapolateBack (Vec3f &outValue, Real32 inValue);

    void checkDataConsistency(void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class AnimVec3fDataSourceBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const AnimVec3fDataSource &source);
};

typedef AnimVec3fDataSource *AnimVec3fDataSourceP;

OSG_END_NAMESPACE

#include "OSGAnimVec3fDataSourceBase.inl"
#include "OSGAnimVec3fDataSource.inl"

#endif /* _OSGANIMVEC3FDATASOURCE_H_ */
