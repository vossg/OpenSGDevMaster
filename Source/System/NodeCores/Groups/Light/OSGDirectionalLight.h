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

#ifndef _OSGDIRECTIONALLIGHT_H_
#define _OSGDIRECTIONALLIGHT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGDirectionalLightBase.h"
#include "OSGStatIntElem.h"
#include "OSGStatElemDesc.h"

OSG_BEGIN_NAMESPACE

/*! \brief Directional light
    \ingroup GrpGroupLightObj
    \ingroup GrpLibOSGGroup
    \includebasedoc
 */

class OSG_GROUP_DLLMAPPING DirectionalLight : public DirectionalLightBase
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                  static stat elem                            */
    /*! \{                                                                 */

    static StatElemDesc<StatIntElem>  statNDirectionalLights;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Set                                    */
    /*! \{                                                                 */

    void setDirection(      Real32  rX, 
                            Real32  rY, 
                            Real32  rZ);
    void setDirection(const Vec3f  &direction);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin,
                         BitVector         detail);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Chunk                                   */
    /*! \{                                                                 */

    virtual void makeChunk(void);

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

    typedef DirectionalLightBase Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    DirectionalLight(void);
    DirectionalLight(const DirectionalLight &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~DirectionalLight(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Actions                                */
    /*! \{                                                                 */

    Action::ResultE renderEnter(Action *action);
    Action::ResultE renderLeave(Action *action);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class DirectionalLightBase;

    /*! \brief prohibit default function (move to 'public' if needed) */
    void operator =(const DirectionalLight &source);
};

typedef DirectionalLight *DirectionalLightP;

OSG_END_NAMESPACE

#include "OSGDirectionalLightBase.inl"
#include "OSGDirectionalLight.inl"

#endif /* _OSGDIRECTIONALLIGHT_H_ */

