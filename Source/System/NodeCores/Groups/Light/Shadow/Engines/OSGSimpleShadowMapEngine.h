/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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

#ifndef _OSGSIMPLESHADOWMAPENGINE_H_
#define _OSGSIMPLESHADOWMAPENGINE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGSimpleShadowMapEngineBase.h"

#include "OSGSimpleShadowMapEngineData.h"

#include "OSGDirectionalLight.h"
#include "OSGPointLight.h"

OSG_BEGIN_NAMESPACE

/*! \brief ShadowEngine is the basic NodeCore for inner nodes in the tree.
    \ingroup GrpGroupLightShadowEnginesObj
    \ingroup GrpLibOSGGroup
    \includebasedoc
*/

class OSG_GROUP_DLLMAPPING SimpleShadowMapEngine : 
    public SimpleShadowMapEngineBase
{
    /*==========================  PUBLIC  =================================*/

  public:
    
    typedef SimpleShadowMapEngineData          EngineData;
    typedef SimpleShadowMapEngineData         *EngineDataPtr;
    typedef SimpleShadowMapEngineDataUnrecPtr  EngineDataUnrecPtr;

    /*---------------------------------------------------------------------*/
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin,
                         BitVector         detail);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Render                                 */
    /*! \{                                                                 */

    virtual ActionBase::ResultE runOnEnter(Light        *pLight,
                                           LightTypeE    eType,
                                           RenderAction *pAction);
    virtual ActionBase::ResultE runOnLeave(Light        *pLight,
                                           LightTypeE    eType,
                                           RenderAction *pAction);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Helper                                */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    virtual void dump(      UInt32    uiIndent = 0,
                      const BitVector bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef SimpleShadowMapEngineBase Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    SimpleShadowMapEngine(void);
    SimpleShadowMapEngine(const SimpleShadowMapEngine &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SimpleShadowMapEngine(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Init                                  */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Action Callbacks                       */
    /*! \{                                                                 */

    void lightRenderEnter(Light         *pLight,
                          RenderAction  *pAction);
    
    void setupCamera     (Light         *pLight,
                          LightTypeE     eType,
                          RenderAction  *pAction,
                          EngineDataPtr  pEngineData);
    void setupLightChunk (Light         *pLight,
                          LightTypeE     eType,
                          RenderAction  *pAction,
                          EngineDataPtr  pEngineData);

    void doLightPass     (Light         *pLight,
                          RenderAction  *pAction,
                          EngineDataPtr  pEngineData);
    void doAmbientPass   (Light         *pLight,
                          RenderAction  *pAction,
                          EngineDataPtr  pEngineData);
    void doFinalPass     (Light         *pLight,
                          RenderAction  *pAction,
                          EngineDataPtr  pEngineData);
                     
    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class SimpleShadowMapEngineBase;

    /*---------------------------------------------------------------------*/

    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const SimpleShadowMapEngine &source);
};

typedef SimpleShadowMapEngine              *SimpleShadowMapEngineP;

OSG_END_NAMESPACE

#include "OSGSimpleShadowMapEngineBase.inl"
#include "OSGSimpleShadowMapEngine.inl"

#endif /* _OSGSIMPLESHADOWMAPENGINE_H_ */
