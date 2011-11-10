/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 * contact: David Kabala (djkabala@gmail.com)                                *
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

#ifndef _OSGPOSTSHADERSTAGEDATA_H_
#define _OSGPOSTSHADERSTAGEDATA_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGPostShaderStageDataBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief PostShaderStageData class. See \ref
           PageEffectGroupsPostShaderStageData for a description.
*/

class OSG_EFFECTGROUPS_DLLMAPPING PostShaderStageData : public PostShaderStageDataBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef PostShaderStageDataBase Inherited;
    typedef PostShaderStageData     Self;

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

    // Variables should all be in PostShaderStageDataBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    PostShaderStageData(void);
    PostShaderStageData(const PostShaderStageData &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~PostShaderStageData(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class PostShaderStageDataBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const PostShaderStageData &source);
};

typedef PostShaderStageData *PostShaderStageDataP;

OSG_END_NAMESPACE

#include "OSGChunkMaterial.h"
#include "OSGFrameBufferObject.h"
#include "OSGCamera.h"
#include "OSGTextureObjChunk.h"
#include "OSGPostShaderStageDataBase.inl"
#include "OSGPostShaderStageData.inl"

#endif /* _OSGPOSTSHADERSTAGEDATA_H_ */
