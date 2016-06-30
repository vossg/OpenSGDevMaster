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

#ifndef _OSGHDR2STAGEDATA_H_
#define _OSGHDR2STAGEDATA_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGHDR2StageDataBase.h"

OSG_BEGIN_NAMESPACE

class TextureObjChunk;

/*! \brief HDR2StageData class. See \ref
           PageEffectGroupsHDR2StageData for a description.
*/

class OSG_EFFECTGROUPS_DLLMAPPING HDR2StageData : public HDR2StageDataBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef HDR2StageDataBase Inherited;
    typedef HDR2StageData     Self;

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
    /*! \name                   Convenience                                */
    /*! \{                                                                 */
    TextureObjChunk*    getSceneTexObjChunk             () const;
    TextureObjChunk*    getDepthTexObjChunk             () const;
    TextureObjChunk*    getLuminanceTexObjChunk         () const;
    TextureObjChunk*    getAdaptLuminanceTexObjChunk    (UInt32 idx) const;
    TextureObjChunk*    getThresholdTexObjChunk         () const;
    TextureObjChunk*    getScaleTexObjChunk             (UInt32 idx) const;
    TextureObjChunk*    getBlurHorizTexObjChunk         () const;
    TextureObjChunk*    getBlurVertTexObjChunk          () const;
    TextureObjChunk*    getCompositeTexObjChunk         () const;
    TextureObjChunk*    getExposureTexObjChunk          () const;

    Real32              getTimeDeltaInSeconds           () const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in HDR2StageDataBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    HDR2StageData(void);
    HDR2StageData(const HDR2StageData &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~HDR2StageData(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class HDR2StageDataBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const HDR2StageData &source);
};

typedef HDR2StageData *HDR2StageDataP;

OSG_END_NAMESPACE

#include "OSGHDR2StageDataBase.inl"
#include "OSGHDR2StageData.inl"

#endif /* _OSGHDR2STAGEDATA_H_ */
