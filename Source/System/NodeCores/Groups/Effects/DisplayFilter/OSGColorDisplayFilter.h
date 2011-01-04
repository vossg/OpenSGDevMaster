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

#ifndef _OSGCOLORDISPLAYFILTER_H_
#define _OSGCOLORDISPLAYFILTER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGColorDisplayFilterBase.h"
#include "OSGImage.h"
#include "OSGSimpleSHLChunk.h"

OSG_BEGIN_NAMESPACE

class DisplayFilterStageData;
class DrawEnv;

/*! \brief ColorDisplayFilter class. See \ref
           PageEffectGroupsColorDisplayFilter for a description.

    \ingroup GrpEffectsGroupsDisplayFilterObj
    \ingroup GrpLibOSGEffectsGroups
    \includebasedoc
 */

class OSG_EFFECTGROUPS_DLLMAPPING ColorDisplayFilter : 
    public ColorDisplayFilterBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef ColorDisplayFilterBase Inherited;
    typedef ColorDisplayFilter     Self;

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

           void process   (DisplayFilterStageData *pData);
    static void deactivate(DisplayFilterStageData *pData);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in ColorDisplayFilterBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ColorDisplayFilter(void);
    ColorDisplayFilter(const ColorDisplayFilter &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ColorDisplayFilter(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                MT Construction                               */
    /*! \{                                                                 */

    void onCreate(const ColorDisplayFilter *source = NULL);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class ColorDisplayFilterBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ColorDisplayFilter &source);
};

typedef ColorDisplayFilter *ColorDisplayFilterP;

OSG_END_NAMESPACE

#include "OSGColorDisplayFilterBase.inl"
#include "OSGColorDisplayFilter.inl"

#endif /* _OSGCOLORDISPLAYFILTER_H_ */
