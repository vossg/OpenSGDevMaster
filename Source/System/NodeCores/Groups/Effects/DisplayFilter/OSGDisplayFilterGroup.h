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

#ifndef _OSGDISPLAYFILTERGROUP_H_
#define _OSGDISPLAYFILTERGROUP_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGDisplayFilterGroupBase.h"
#include "OSGDisplayFilter.h"
#include "OSGResolutionDisplayFilter.h"
#include "OSGDistortionDisplayFilter.h"
#include "OSGColorDisplayFilter.h"

OSG_BEGIN_NAMESPACE

/*! \brief DisplayFilterGroup class. See \ref
           PageEffectGroupsDisplayFilterGroup for a description.

    \ingroup GrpEffectsGroupsDisplayFilterObj
    \ingroup GrpLibOSGEffectsGroups
    \includebasedoc
 */

class OSG_EFFECTGROUPS_DLLMAPPING DisplayFilterGroup : 
    public DisplayFilterGroupBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef DisplayFilterGroupBase Inherited;
    typedef DisplayFilterGroup     Self;

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
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    bool matches(Int32 iDrawerId, Int32 iDrawableId) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in DisplayFilterGroupBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    DisplayFilterGroup(void);
    DisplayFilterGroup(const DisplayFilterGroup &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~DisplayFilterGroup(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class DisplayFilterGroupBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const DisplayFilterGroup &source);
};

typedef DisplayFilterGroup *DisplayFilterGroupP;

OSG_END_NAMESPACE

#include "OSGDisplayFilterGroupBase.inl"
#include "OSGDisplayFilterGroup.inl"

#endif /* _OSGDISPLAYFILTERGROUP_H_ */
