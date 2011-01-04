/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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

#ifndef _OSGPROJECTIONCAMERADECORATOR_H_
#define _OSGPROJECTIONCAMERADECORATOR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGProjectionCameraDecoratorBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief Camera Decorator for head-tracked stereo setups, see \ref
           PageSystemWindowCameraDecorators for a description.
    \ingroup GrpWindowCameraObj
    \ingroup GrpLibOSGWindow
    \includebasedoc
 */

class OSG_WINDOW_DLLMAPPING ProjectionCameraDecorator : 
    public ProjectionCameraDecoratorBase
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef ProjectionCameraDecoratorBase               Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField, 
                         UInt32            origin,
                         BitVector         detail);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    access                                    */
    /*! \{                                                                 */
 
    virtual void getViewing              (Matrix &result, 
                                          UInt32  width, 
                                          UInt32  height);
 
    virtual void getProjection           (Matrix &result, 
                                          UInt32  width, 
                                          UInt32  height);
 
    virtual void getProjectionTranslation(Matrix &result, 
                                          UInt32  width, 
                                          UInt32  height);
 
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in ProjectionCameraDecoratorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ProjectionCameraDecorator(void);
    ProjectionCameraDecorator(const ProjectionCameraDecorator &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ProjectionCameraDecorator(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   internal                                   */
    /*! \{                                                                 */
 
    void updateData(void);
 
    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class ProjectionCameraDecoratorBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ProjectionCameraDecorator &source);
};

typedef ProjectionCameraDecorator       *ProjectionCameraDecoratorP;

OSG_END_NAMESPACE

#include "OSGProjectionCameraDecoratorBase.inl"
#include "OSGProjectionCameraDecorator.inl"

#endif /* _OSGPROJECTIONCAMERADECORATOR_H_ */
