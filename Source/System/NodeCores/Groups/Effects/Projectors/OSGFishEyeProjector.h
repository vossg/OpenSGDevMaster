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

#ifndef _OSGFISHEYEPROJECTOR_H_
#define _OSGFISHEYEPROJECTOR_H_
#ifdef __sgi
#pragma once
#endif

#include <queue>

#include "OSGFishEyeProjectorBase.h"
#include "OSGAction.h"
#include "OSGFishEyeProjectorDataFields.h"
#include "OSGGeometry.h"

OSG_BEGIN_NAMESPACE

class DrawEnv;
class RenderActionBase;

/*! Stage
    \ingroup GrpEffectsGroupsProjectorsObj
    \ingroup GrpLibOSGEffectsGroups
    \includebasedoc
 */

class OSG_EFFECTGROUPS_DLLMAPPING FishEyeProjector : 
    public FishEyeProjectorBase
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef FishEyeProjectorBase                           Inherited;

    enum ProjectionMode
    {
        TruncateBottom = 0x0001,
        TruncateTop    = 0x0002,
        DomeVertical   = 0x0003,
        DomeHorizontal = 0x0004,
        WarpMap        = 0x0005,
        MirrorDome     = 0x0006
    };

    /*---------------------------------------------------------------------*/
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin,
                         BitVector         detail);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    void postProcess(DrawEnv *);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
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

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    FishEyeProjector(void);
    FishEyeProjector(const FishEyeProjector &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~FishEyeProjector(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                         GL                                   */
    /*! \{                                                                 */

    static UInt32 _uiFramebuffer_object_extension;
    static UInt32 _uiFuncDrawBuffers;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Draw                                       */
    /*! \{                                                                 */

    ActionBase::ResultE renderEnter(Action *action);
    ActionBase::ResultE renderLeave(Action *action);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Draw                                       */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Draw                                       */
    /*! \{                                                                 */


    void resizeStageData(FishEyeProjectorData *pData,
                         Int32                 iPixelWidth,
                         Int32                 iPixelHeight);


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Draw                                       */
    /*! \{                                                                 */

    void  EstimateWarp     (Real64  u, Real64  v, 
                            Real64 &x, Real64 &z, 
                            Real64 &br          );

    Int32 MirrorPosition   (Vec3d   c, 
                            Real64  r, 
                            Vec3d   p1, 
                            Vec3d   p2, 
                            Vec3d  &p0          );


    void  warpData         (Geometry *pGeo      );

    void  flattenVertex    (Vec3d    &oVertex, 
                            Real64    aperture  );

    void  splitFaces       (MFVec2d  &oUV,
                            MFVec3d  &oPos,
                            UInt32   &uiNumTries);

    void  initTopMesh      (Geometry *pGeo      );
    void  initBottomMesh   (Geometry *pGeo      );
    void  initLeftMesh     (Geometry *pGeo      );
    void  initRightMesh    (Geometry *pGeo      );
    void  updateMesh       (Geometry *pGeo      );
    void  rebuildGeometries(void                );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Draw                                       */
    /*! \{                                                                 */

    FishEyeProjectorData           *initData      (RenderActionBase *pAction);
    FishEyeProjectorDataTransitPtr  setupStageData(RenderActionBase *pAction);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class FishEyeProjectorBase;

    /*---------------------------------------------------------------------*/
    /*! \name                   thread local                               */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    load thread                               */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const FishEyeProjector &source);
};

typedef FishEyeProjector              *FishEyeProjectorP;

OSG_END_NAMESPACE

#include "OSGFishEyeProjectorBase.inl"
#include "OSGFishEyeProjector.inl"

#endif /* _OSGFISHEYEPROJECTOR_H_ */
