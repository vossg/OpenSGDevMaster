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

#ifndef _OSGCUBEMAPGENERATOR_H_
#define _OSGCUBEMAPGENERATOR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGCubeMapGeneratorBase.h"
#include "OSGCubeMapGeneratorStageDataFields.h"
#include "OSGTextureObjChunk.h"

OSG_BEGIN_NAMESPACE

class RenderActionBase;

/*! \brief CubeMapGenerator class. See \ref
           PageGroupCubeMapGenerator for a description.
    \ingroup GrpGroupDynamicStateGeneratorsObj
    \ingroup GrpLibOSGGroup
    \includebasedoc
 */

class OSG_GROUP_DLLMAPPING CubeMapGenerator : public CubeMapGeneratorBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef CubeMapGeneratorBase Inherited;
    typedef CubeMapGenerator     Self;

    enum SetupMode
    {
        NoSetup      = 0x0000,
        SetupTexture = 0x0001,
        SetupTexEnv  = 0x0002,
        SetupTexGen  = 0x0004,
        
        OverrideTex  = 0x0010,
        AutoTexture  = 0x0011,

        SetupAll     = 0x0017
    };

    enum OriginMode
    {
        UseStoredValue         = 0x0001,
        UseBeacon              = 0x0002,
        UseCurrentVolumeCenter = 0x0003,
        UseParentsVolumeCenter = 0x0004
    };

    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    CubeMapGeneratorStageData *initData(RenderActionBase *pAction);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    void   setSize  (UInt16 uiWidth, 
                     UInt16 uiHeight);

    UInt16 getWidth (void);
    UInt16 getHeight(void);

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

    // Variables should all be in CubeMapGeneratorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    CubeMapGenerator(void);
    CubeMapGenerator(const CubeMapGenerator &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~CubeMapGenerator(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Draw                                       */
    /*! \{                                                                 */

    ActionBase::ResultE renderEnter(Action *action);
    ActionBase::ResultE renderLeave(Action *action);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    CubeMapGeneratorStageDataTransitPtr setupStageData(
        RenderActionBase *pAction);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class CubeMapGeneratorBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const CubeMapGenerator &source);
};

typedef CubeMapGenerator *CubeMapGeneratorP;

OSG_END_NAMESPACE

#include "OSGCubeMapGeneratorBase.inl"
#include "OSGCubeMapGenerator.inl"

#endif /* _OSGCUBEMAPGENERATOR_H_ */
