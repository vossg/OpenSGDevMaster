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

#ifndef _OSGSIMPLESHADOWMAPENGINEDATA_H_
#define _OSGSIMPLESHADOWMAPENGINEDATA_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGSimpleShadowMapEngineDataBase.h"
#include "OSGFrameBufferObject.h"
#include "OSGTextureObjChunk.h"
#include "OSGTextureBuffer.h"
#include "OSGBlendChunk.h"
#include "OSGTexGenChunk.h"
#include "OSGPolygonChunk.h"
#include "OSGLightChunk.h"

OSG_BEGIN_NAMESPACE

/*! \brief SimpleShadowMapEngineData class. See \ref
           PageGroupSimpleShadowMapEngineData for a description.
    \ingroup GrpGroupLightShadowEnginesObj
    \ingroup GrpLibOSGGroup
    \includebasedoc
 */

class OSG_GROUP_DLLMAPPING SimpleShadowMapEngineData : 
    public SimpleShadowMapEngineDataBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef SimpleShadowMapEngineDataBase Inherited;
    typedef SimpleShadowMapEngineData     Self;

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

    // Variables should all be in SimpleShadowMapEngineDataBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    SimpleShadowMapEngineData(void);
    SimpleShadowMapEngineData(const SimpleShadowMapEngineData &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SimpleShadowMapEngineData(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class SimpleShadowMapEngineDataBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const SimpleShadowMapEngineData &source);
};

OSG_END_NAMESPACE

#include "OSGSimpleShadowMapEngineDataBase.inl"
#include "OSGSimpleShadowMapEngineData.inl"

#endif /* _OSGSIMPLESHADOWMAPENGINEDATA_H_ */
