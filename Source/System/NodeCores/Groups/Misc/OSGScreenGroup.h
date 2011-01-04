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

#ifndef _OSGSCREENGROUP_H_
#define _OSGSCREENGROUP_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGScreenGroupBase.h"

OSG_BEGIN_NAMESPACE

class RenderAction;

/*! \brief ScreenGroup class. See \ref 
           PageSystemScreenGroup for a description.
    \ingroup GrpGroupMiscObj
    \ingroup GrpLibOSGGroup
    \includebasedoc
 */

class OSG_GROUP_DLLMAPPING ScreenGroup : public ScreenGroupBase
{
  private:

    typedef ScreenGroupBase Inherited;

    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg  whichField, 
                         UInt32             origin,
                         BitVector          detail    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in ScreenGroupBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ScreenGroup(void);
    ScreenGroup(const ScreenGroup &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ScreenGroup(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Init                                       */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name               calc the model matrix                          */
    /*! \{                                                                 */

    void calcMatrix(      RenderAction *pAction, 
                    const Matrix       &mToWorld,
                          Matrix       &mResult );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Transformation                              */
    /*! \{                                                                 */

    virtual void accumulateMatrix(Matrix &result);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      NodeCore Specific                       */
    /*! \{                                                                 */

    void adjustVolume(Volume &volume);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name              Draw & Intersect & Render                       */
    /*! \{                                                                 */

    Action::ResultE intersectEnter(Action *action);
    Action::ResultE intersectLeave(Action *action);

    Action::ResultE renderEnter   (Action *action);
    Action::ResultE renderLeave   (Action *action);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    Matrix _camTransform;

    friend class FieldContainer;
    friend class ScreenGroupBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ScreenGroup &source);
};

typedef ScreenGroup *ScreenGroupP;

OSG_END_NAMESPACE

#include "OSGScreenGroupBase.inl"
#include "OSGScreenGroup.inl"

#endif /* _OSGSCREENGROUP_H_ */
