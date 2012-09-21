/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 * contact: Alexander Lang                                                   *
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

#ifndef _OSGDEPTHPEELINGSTAGEDATA_H_
#define _OSGDEPTHPEELINGSTAGEDATA_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGChunkMaterial.h"
#include "OSGFrameBufferObject.h"
#include "OSGDepthChunk.h"
#include "OSGShaderProgramVariableChunk.h"

#include "OSGDepthPeelingStageDataBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief DepthPeelingStageData class. See \ref
           PageDepthPeelingStageData for a description.
*/

class OSG_EFFECTGROUPS_DLLMAPPING DepthPeelingStageData : public DepthPeelingStageDataBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef DepthPeelingStageDataBase Inherited;
    typedef DepthPeelingStageData     Self;

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

    // Variables should all be in DepthPeelingStageDataBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    DepthPeelingStageData(void);
    DepthPeelingStageData(const DepthPeelingStageData &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~DepthPeelingStageData(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class DepthPeelingStageDataBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const DepthPeelingStageData &source);
};

typedef DepthPeelingStageData *DepthPeelingStageDataP;

OSG_END_NAMESPACE

#include "OSGDepthPeelingStageDataBase.inl"
#include "OSGDepthPeelingStageData.inl"

#endif /* _OSGDEPTHPEELINGSTAGEDATA_H_ */
