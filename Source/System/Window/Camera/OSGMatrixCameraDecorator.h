/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
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

#ifndef _OSGMATRIXCAMERADECORATOR_H_
#define _OSGMATRIXCAMERADECORATOR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGMatrixCameraDecoratorBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief MatrixCameraDecorator class. See \ref 
           PageSystemCameraDecoratorsMatrix for a description.
    \ingroup GrpWindowCameraObj
    \ingroup GrpLibOSGWindow
    \includebasedoc
 */

class OSG_WINDOW_DLLMAPPING MatrixCameraDecorator : 
    public MatrixCameraDecoratorBase
{
  private:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef MatrixCameraDecoratorBase                          Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField, 
                         UInt32            origin,
                         BitVector         detail);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    access                                    */
    /*! \{                                                                 */

    virtual void getProjection           (Matrix &result, 
                                          UInt32  width, 
                                          UInt32  height);

    virtual void getProjectionTranslation(Matrix &result, 
                                          UInt32  width, 
                                          UInt32  height);

    virtual void getViewing              (Matrix &result, 
                                          UInt32  width, 
                                          UInt32  height);
 
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in MatrixCameraDecoratorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    MatrixCameraDecorator(void);
    MatrixCameraDecorator(const MatrixCameraDecorator &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~MatrixCameraDecorator(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class MatrixCameraDecoratorBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const MatrixCameraDecorator &source);
};

typedef MatrixCameraDecorator *MatrixCameraDecoratorP;

OSG_END_NAMESPACE

#include "OSGMatrixCameraDecoratorBase.inl"
#include "OSGMatrixCameraDecorator.inl"

#endif /* _OSGMATRIXCAMERADECORATOR_H_ */
