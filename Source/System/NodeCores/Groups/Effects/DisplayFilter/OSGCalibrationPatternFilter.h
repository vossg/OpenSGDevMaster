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

#ifndef _OSGCALIBRATIONPATTERNFILTER_H_
#define _OSGCALIBRATIONPATTERNFILTER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGCalibrationPatternFilterBase.h"

OSG_BEGIN_NAMESPACE

class DisplayFilterStageData;
class DrawEnv;

/*! \brief CalibrationPatternFilter class. See \ref
           PageEffectGroupsColorDisplayFilter for a description.

    \ingroup GrpEffectsGroupsDisplayFilterObj
    \ingroup GrpLibOSGEffectsGroups
    \includebasedoc
 */

class OSG_EFFECTGROUPS_DLLMAPPING CalibrationPatternFilter : 
    public CalibrationPatternFilterBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef CalibrationPatternFilterBase Inherited;
    typedef CalibrationPatternFilter     Self;

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

    virtual void processActive  (DisplayFilterStageData *pData, 
                                 DrawEnv                *pEnv);
    virtual void processInactive(DisplayFilterStageData *pData, 
                                 DrawEnv                *pEnv);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in CalibrationPatternFilterBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    CalibrationPatternFilter(void);
    CalibrationPatternFilter(const CalibrationPatternFilter &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~CalibrationPatternFilter(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                MT Construction                               */
    /*! \{                                                                 */

    void onCreate(const CalibrationPatternFilter *source = NULL);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class CalibrationPatternFilterBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const CalibrationPatternFilter &source);
};

typedef CalibrationPatternFilter *CalibrationPatternFilterP;

OSG_END_NAMESPACE

#include "OSGCalibrationPatternFilterBase.inl"
#include "OSGCalibrationPatternFilter.inl"

#endif /* _OSGCALIBRATIONPATTERNFILTER_H_ */
