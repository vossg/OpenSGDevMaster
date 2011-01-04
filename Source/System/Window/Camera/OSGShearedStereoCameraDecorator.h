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

#ifndef _OSGSHEAREDSTEREOCAMERADECORATOR_H_
#define _OSGSHEAREDSTEREOCAMERADECORATOR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGShearedStereoCameraDecoratorBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief Camera Decorator for standard sheared stereo, see \ref
           PageSystemWindowCameraDecoratorsStereoSheared for a description.
    \ingroup GrpWindowCameraObj
    \ingroup GrpLibOSGWindow
    \includebasedoc
 */

class OSG_WINDOW_DLLMAPPING ShearedStereoCameraDecorator : 
    public ShearedStereoCameraDecoratorBase
{
  private:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef ShearedStereoCameraDecoratorBase               Inherited;

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
 
    virtual void getProjection(Matrix &result, 
                               UInt32  width, 
                               UInt32  height);
    
  	virtual void getDecoration(Matrix &result, 
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

    // Variables should all be in ShearedStereoCameraDecoratorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ShearedStereoCameraDecorator(void);
    ShearedStereoCameraDecorator(const ShearedStereoCameraDecorator &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ShearedStereoCameraDecorator(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class ShearedStereoCameraDecoratorBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ShearedStereoCameraDecorator &source);
};

typedef ShearedStereoCameraDecorator *ShearedStereoCameraDecoratorP;

OSG_END_NAMESPACE

#include "OSGShearedStereoCameraDecoratorBase.inl"
#include "OSGShearedStereoCameraDecorator.inl"

#endif /* _OSGSHEAREDSTEREOCAMERADECORATOR_H_ */
