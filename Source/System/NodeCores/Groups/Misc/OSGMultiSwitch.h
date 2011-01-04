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

#ifndef _OSGMULTISWITCH_H_
#define _OSGMULTISWITCH_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGMultiSwitchBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief MultiSwitch class. See \ref
           PageSystemMultiSwitch for a description.
    \ingroup GrpGroupMiscObj
    \ingroup GrpLibOSGGroup
    \includebasedoc
 */

class OSG_GROUP_DLLMAPPING MultiSwitch : public MultiSwitchBase
{
  protected:

    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name                    Types                                     */
    /*! \{                                                                 */
    
    typedef MultiSwitchBase Inherited;
    typedef MultiSwitch     Self;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Constants                                   */
    /*! \{                                                                 */

    enum
    {
        ALL     = -3,
        NONE    = -2,
        CHOICES = -1
    };
    
    void setBitfield(BitVector childMask);
    
    /*! \}                                                                 */
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

    // Variables should all be in MultiSwitchBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    MultiSwitch(void);
    MultiSwitch(const MultiSwitch &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~MultiSwitch(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Draw                                       */
    /*! \{                                                                 */

    ActionBase::ResultE renderEnter(Action *action);
    ActionBase::ResultE renderLeave(Action *action);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Intersect                                    */
    /*! \{                                                                 */

    ActionBase::ResultE intersectEnter(Action *action);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class MultiSwitchBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const MultiSwitch &source);
};

typedef MultiSwitch *MultiSwitchP;

OSG_END_NAMESPACE

#include "OSGMultiSwitchBase.inl"
#include "OSGMultiSwitch.inl"

#endif /* _OSGMULTISWITCH_H_ */
