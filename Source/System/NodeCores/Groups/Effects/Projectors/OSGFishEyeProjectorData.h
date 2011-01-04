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

#ifndef _OSGFISHEYEPROJECTORDATA_H_
#define _OSGFISHEYEPROJECTORDATA_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGFishEyeProjectorDataBase.h"
#include "OSGTextureObjChunk.h"

OSG_BEGIN_NAMESPACE

/*! \brief FishEyeProjectorData class. See \ref
           PageGroupFishEyeProjectorData for a description.

    \ingroup GrpEffectsGroupsProjectorsObj
    \ingroup GrpLibOSGEffectsGroups
    \includebasedoc
 */

class OSG_EFFECTGROUPS_DLLMAPPING FishEyeProjectorData : 
    public FishEyeProjectorDataBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef FishEyeProjectorDataBase Inherited;
    typedef FishEyeProjectorData     Self;

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
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in FishEyeProjectorDataBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    FishEyeProjectorData(void);
    FishEyeProjectorData(const FishEyeProjectorData &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~FishEyeProjectorData(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class FishEyeProjectorDataBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const FishEyeProjectorData &source);
};

OSG_END_NAMESPACE

#include "OSGFishEyeProjectorDataBase.inl"
#include "OSGFishEyeProjectorData.inl"

#endif /* _OSGFishEyeProjectorDATA_H_ */
