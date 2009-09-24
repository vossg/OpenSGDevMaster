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

#ifndef _OSGANIMKEYFRAMEDATASOURCE_H_
#define _OSGANIMKEYFRAMEDATASOURCE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGAnimKeyFrameDataSourceBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief AnimKeyFrameDataSource class. See \ref
           PageDynamicsAnimKeyFrameDataSource for a description.
*/

class OSG_DYNAMICS_DLLMAPPING AnimKeyFrameDataSource : public AnimKeyFrameDataSourceBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef AnimKeyFrameDataSourceBase Inherited;
    typedef AnimKeyFrameDataSource     Self;

    enum InterpolationModeE
    {
        IM_Step,
        IM_Linear,
        IM_Bezier,
        IM_Hermite
    };

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin,
                         BitVector         details    );


    virtual Real32 getLength(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in AnimKeyFrameDataSourceBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    AnimKeyFrameDataSource(void);
    AnimKeyFrameDataSource(const AnimKeyFrameDataSource &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~AnimKeyFrameDataSource(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class AnimKeyFrameDataSourceBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const AnimKeyFrameDataSource &source);
};

typedef AnimKeyFrameDataSource *AnimKeyFrameDataSourceP;

OSG_END_NAMESPACE

#include "OSGAnimKeyFrameDataSourceBase.inl"
#include "OSGAnimKeyFrameDataSource.inl"

#endif /* _OSGANIMKEYFRAMEDATASOURCE_H_ */
