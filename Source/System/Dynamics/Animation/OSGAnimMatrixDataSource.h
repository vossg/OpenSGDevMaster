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

#ifndef _OSGANIMMATRIXDATASOURCE_H_
#define _OSGANIMMATRIXDATASOURCE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGAnimMatrixDataSourceBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief AnimMatrixDataSource class. See \ref
           PageDynamicsAnimMatrixDataSource for a description.
*/

class OSG_DYNAMICS_DLLMAPPING AnimMatrixDataSource : public AnimMatrixDataSourceBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef AnimMatrixDataSourceBase Inherited;
    typedef AnimMatrixDataSource     Self;

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

    void evaluate(Matrix &outValue, Real32 inValue);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in AnimMatrixDataSourceBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    AnimMatrixDataSource(void);
    AnimMatrixDataSource(const AnimMatrixDataSource &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~AnimMatrixDataSource(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Evaluation                                 */
    /*! \{                                                                 */

    void evalStep        (Matrix                         &outValue,
                          Real32                          inValue,
                          MFInValuesType::const_iterator  ivRIt    );
    void evalLinear      (Matrix                         &outValue,
                          Real32                          inValue,
                          MFInValuesType::const_iterator  ivRIt    );

    void extrapolateFront(Matrix &outValue, Real32 inValue);
    void extrapolateBack (Matrix &outValue, Real32 inValue);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class AnimMatrixDataSourceBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const AnimMatrixDataSource &source);
};

typedef AnimMatrixDataSource *AnimMatrixDataSourceP;

OSG_END_NAMESPACE

#include "OSGAnimMatrixDataSourceBase.inl"
#include "OSGAnimMatrixDataSource.inl"

#endif /* _OSGANIMMATRIXDATASOURCE_H_ */
