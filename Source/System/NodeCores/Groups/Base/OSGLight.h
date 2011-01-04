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

#ifndef _OSGLIGHT_H_
#define _OSGLIGHT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGLightBase.h"
#include "OSGAction.h"
#include "OSGLightChunk.h"
#include "OSGStatCollector.h"
#include "OSGLightEngine.h"

OSG_BEGIN_NAMESPACE

/*! \brief Lights Base class

    \ingroup GrpSystemNodeCoreGroupsCores
    \ingroup GrpLibOSGSystem
    \includebasedoc
 */

class OSG_SYSTEM_DLLMAPPING Light : public LightBase
{
    /*==========================  PUBLIC  =================================*/

  public:

    enum
    {
        CAST_SHADOW_AUTO    = 0,
        CAST_SHADOW_ON      = 1,
        CAST_SHADOW_OFF     = 2
    };

    /*---------------------------------------------------------------------*/
    /*! \name                       Set                                    */
    /*! \{                                                                 */

    void setAmbient (      Real32   rRed, 
                           Real32   rGreen, 
                           Real32   rBlue, 
                           Real32   rAlpha);
    void setDiffuse (      Real32   rRed, 
                           Real32   rGreen, 
                           Real32   rBlue, 
                           Real32   rAlpha);
    void setSpecular(      Real32   rRed, 
                           Real32   rGreen, 
                           Real32   rBlue, 
                           Real32   rAlpha);
    
    void setAmbient (const Color4f &col);
    void setDiffuse (const Color4f &col);
    void setSpecular(const Color4f &col);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Chunk                                   */
    /*! \{                                                                 */

            LightChunk *getChunk (void) const;
    virtual void        makeChunk(void);

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

    virtual void callLightEngineEnter(RenderAction *ract) = 0;
    virtual void callLightEngineLeave(RenderAction *ract) = 0;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Dump                                    */
    /*! \{                                                                 */

    virtual void dump(      UInt32    uiIndent = 0,
                      const BitVector bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef LightBase           Inherited;

            LightChunkUnrecPtr _pChunk;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    Light(void);
    Light(const Light &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~Light(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Actions                                  */
    /*! \{                                                                 */
   
    Action::ResultE renderEnter(LightEngine::LightTypeE  eType,
                                RenderAction            *action);
                                
    Action::ResultE renderLeave(LightEngine::LightTypeE  eType,
                                Action                  *action);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    virtual void resolveLinks(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class LightBase;

    /*! \brief prohibit default function (move to 'public' if needed) */
    void operator =(const Light &source);
};

OSG_END_NAMESPACE

#include "OSGLightBase.inl"
#include "OSGLight.inl"

#endif /* _OSGLIGHT_H_ */
