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

#ifndef _OSGPOINTLIGHT_H_
#define _OSGPOINTLIGHT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGPointLightBase.h"
#include "OSGStatIntElem.h"
#include "OSGStatElemDesc.h"

OSG_BEGIN_NAMESPACE

/*! \brief Point Light
    \ingroup GrpGroupLightObj
    \ingroup GrpLibOSGGroup
    \includebasedoc
 */

class OSG_GROUP_DLLMAPPING PointLight : public PointLightBase
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                  static stat elem                            */
    /*! \{                                                                 */

    static StatElemDesc<StatIntElem>  statNPointLights;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Access Fields                            */
    /*! \{                                                                 */

    void setPosition   (      Real32  rX,
                              Real32  rY, 
                              Real32  rZ        );
    void setPosition   (const Pnt3f  &pos       );

    void setAttenuation(      Real32  rConstant ,
                              Real32  rLinear   ,
                              Real32  rQuadratic);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Chunk                                   */
    /*! \{                                                                 */

    virtual void makeChunk(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin,
                         BitVector         detail);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  LightEngine                                 */
    /*! \{                                                                 */

    virtual void callLightEngineEnter(RenderAction *ract);
    virtual void callLightEngineLeave(RenderAction *ract);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Dump                                    */
    /*! \{                                                                 */

    virtual void dump(      UInt32    uiIndent = 0,
                      const BitVector bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef PointLightBase Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    PointLight(void);
    PointLight(const PointLight &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~PointLight(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Actions                                  */
    /*! \{                                                                 */

    Action::ResultE renderEnter(Action *action);
    Action::ResultE renderLeave(Action *action);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class PointLightBase;

    /*! \brief prohibit default function (move to 'public' if needed) */
    void operator =(const PointLight &source);
};

typedef PointLight *PointLightP;

OSG_END_NAMESPACE

#include "OSGPointLightBase.inl"
#include "OSGPointLight.inl"

#endif /* _OSGPOINTLIGHT_H_ */
