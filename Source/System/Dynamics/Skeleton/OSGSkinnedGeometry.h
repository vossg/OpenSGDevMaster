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

#ifndef _OSGSKINNEDGEOMETRY_H_
#define _OSGSKINNEDGEOMETRY_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGSkinnedGeometryBase.h"
#include "OSGSkeleton.h"
#include "OSGSkeletonJoint.h"
#include "OSGShaderProgramChunk.h"
#include "OSGShaderProgramVariableChunk.h"
#include "OSGRenderAction.h"

OSG_BEGIN_NAMESPACE

/*! \brief SkinnedGeometry class. See \ref
           PageDynamicsSkinnedGeometry for a description.
*/

class OSG_DYNAMICS_DLLMAPPING SkinnedGeometry : public SkinnedGeometryBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef SkinnedGeometryBase Inherited;
    typedef SkinnedGeometry     Self;

    enum SkinnedGeoFlagsE
    {
        SGFlagHardware  = 0x0001,
        SGFlagDebug     = 0x0002,
        SGFlagUnskinned = 0x0004
    };

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin,
                         BitVector         details    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Flags                                   */
    /*! \{                                                                 */

    void addFlag (SkinnedGeoFlagsE flag);
    void subFlag (SkinnedGeoFlagsE flag);
    bool testFlag(SkinnedGeoFlagsE flag);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Render                                   */
    /*! \{                                                                 */

    Action::ResultE renderEnter(Action *action);
    Action::ResultE renderLeave(Action *action);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Drawable Specifics                           */
    /*! \{                                                                 */

    virtual void fill        (DrawableStatsAttachment *drawStats);
    virtual void adjustVolume(Volume                  &volume   );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in SkinnedGeometryBase.

    typedef std::vector<Pnt3f > PositionStore;
    typedef std::vector<UInt32> IndexStore;

    static const std::string _vpVertexSkinning;

    PositionStore _debugDrawPos;
    IndexStore    _debugDrawIdx;

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    SkinnedGeometry(void);
    SkinnedGeometry(const SkinnedGeometry &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SkinnedGeometry(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    Action::ResultE renderDebug   (RenderAction *ract);
    Action::ResultE renderHardware(RenderAction *ract);
    Action::ResultE renderSoftware(RenderAction *ract);

    Action::ResultE drawDebug     (DrawEnv      *drawEnv);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class SkinnedGeometryBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const SkinnedGeometry &source);
};

typedef SkinnedGeometry *SkinnedGeometryP;

OSG_END_NAMESPACE

#include "OSGSkinnedGeometryBase.inl"
#include "OSGSkinnedGeometry.inl"

#endif /* _OSGSKINNEDGEOMETRY_H_ */
