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

#ifndef _OSGANIMATION_H_
#define _OSGANIMATION_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGAnimationBase.h"
#include "OSGAnimChannel.h"
#include "OSGAnimTemplate.h"
#include "OSGAnimTimeSensor.h"

OSG_BEGIN_NAMESPACE

/*! \brief Animation class. See \ref
           PageDynamicsAnimation for a description.
*/

class OSG_DYNAMICS_DLLMAPPING Animation : public AnimationBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef AnimationBase Inherited;
    typedef Animation     Self;

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin,
                         BitVector         details    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Time Sensor                                */
    /*! \{                                                                 */

    void            setTimeSensor(AnimTimeSensor *value);
    AnimTimeSensor *getTimeSensor(void                 ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Playback                                 */
    /*! \{                                                                 */

    const std::string &getName  (void) const;
    Real32             getLength(void) const;
    bool               isPlaying(void) const;


    void start    (Time startTime);
    void startLoop(Time startTime);

    void reset    (void          );

    void stop     (void          );

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in AnimationBase.
    
    mutable Real32 _animLength;

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    Animation(void);
    Animation(const Animation &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~Animation(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                Time Sensor Change                            */
    /*! \{                                                                 */

    void timeSensorChanged(FieldContainer *fc,
                           BitVector       whichField);

    void calcLength(void) const;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class AnimationBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const Animation &source);
};

typedef Animation *AnimationP;

OSG_END_NAMESPACE

#include "OSGAnimationBase.inl"
#include "OSGAnimation.inl"

#endif /* _OSGANIMATION_H_ */
