/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2013 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 * contact: dirk@opensg.org, gerrit.voss@vossg.org, carsten_neumann@gmx.net  *
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

#ifndef _OSGHEADTRACKEDSTEREOCAMERADECORATOR_H_
#define _OSGHEADTRACKEDSTEREOCAMERADECORATOR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGHeadTrackedStereoCameraDecoratorBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief HeadTrackedStereoCameraDecorator class. See \ref
           PageWindowHeadTrackedStereoCameraDecorator for a description.
*/

class OSG_WINDOW_DLLMAPPING HeadTrackedStereoCameraDecorator : public HeadTrackedStereoCameraDecoratorBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef HeadTrackedStereoCameraDecoratorBase Inherited;
    typedef HeadTrackedStereoCameraDecorator     Self;

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin,
                         BitVector         details    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    access                                    */
    /*! \{                                                                 */

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

    // Variables should all be in HeadTrackedStereoCameraDecoratorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    HeadTrackedStereoCameraDecorator(void);
    HeadTrackedStereoCameraDecorator(const HeadTrackedStereoCameraDecorator &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~HeadTrackedStereoCameraDecorator(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class HeadTrackedStereoCameraDecoratorBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const HeadTrackedStereoCameraDecorator &source);
};

typedef HeadTrackedStereoCameraDecorator *HeadTrackedStereoCameraDecoratorP;

OSG_END_NAMESPACE

#include "OSGHeadTrackedStereoCameraDecoratorBase.inl"
#include "OSGHeadTrackedStereoCameraDecorator.inl"

#endif /* _OSGHEADTRACKEDSTEREOCAMERADECORATOR_H_ */
