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

#ifndef _OSGDISPLAYFILTERSTAGE_H_
#define _OSGDISPLAYFILTERSTAGE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGDisplayFilterStageBase.h"
#include "OSGDisplayFilterGroup.h"
#include "OSGDisplayFilterStageData.h"

OSG_BEGIN_NAMESPACE

/*! \brief DisplayFilterStage class. See \ref
           PageEffectGroupsDisplayFilterStage for a description.

    \ingroup GrpEffectsGroupsDisplayFilterObj
    \ingroup GrpLibOSGEffectsGroups
    \includebasedoc
 */

class OSG_EFFECTGROUPS_DLLMAPPING DisplayFilterStage : 
    public DisplayFilterStageBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef DisplayFilterStageBase Inherited;
    typedef DisplayFilterStage     Self;

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
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in DisplayFilterStageBase.
    typedef DisplayFilterStageDataTransitPtr StageDataTransitPtr;

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    DisplayFilterStage(void);
    DisplayFilterStage(const DisplayFilterStage &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~DisplayFilterStage(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Draw                                       */
    /*! \{                                                                 */

    ActionBase::ResultE renderEnter(Action *action);
    ActionBase::ResultE renderLeave(Action *action);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Draw                                       */
    /*! \{                                                                 */

    void postProcess(DrawEnv *pEnv);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Draw                                       */
    /*! \{                                                                 */

    StageDataTransitPtr setupStageData (Int32                   iPixelWidth,
                                        Int32                   iPixelHeight);

    void                resizeStageData(DisplayFilterStageData *pData,
                                        Int32                   iPixelWidth,
                                        Int32                   iPixelHeight);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class DisplayFilterStageBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const DisplayFilterStage &source);
};

typedef DisplayFilterStage *DisplayFilterStageP;

OSG_END_NAMESPACE

#include "OSGDisplayFilterStageBase.inl"
#include "OSGDisplayFilterStage.inl"

#endif /* _OSGDISPLAYFILTERSTAGE_H_ */
