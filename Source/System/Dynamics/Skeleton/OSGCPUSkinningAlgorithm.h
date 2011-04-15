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

#ifndef _OSGCPUSKINNINGALGORITHM_H_
#define _OSGCPUSKINNINGALGORITHM_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGCPUSkinningAlgorithmBase.h"

OSG_BEGIN_NAMESPACE

class CPUSkinningDataAttachment;
class IntersectAction;

/*! \brief CPUSkinningAlgorithm class. See \ref
           PageDynamicsCPUSkinningAlgorithm for a description.
*/

class OSG_DYNAMICS_DLLMAPPING CPUSkinningAlgorithm : public CPUSkinningAlgorithmBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef CPUSkinningAlgorithmBase      Inherited;
    typedef CPUSkinningAlgorithm          Self;

    typedef SkinnedGeometry::RenderModeE  RenderModeE;

    /*---------------------------------------------------------------------*/
    /*! \name                      Execute                                 */
    /*! \{                                                                 */

    virtual void                adjustVolume  (Volume  &volume );

    virtual ActionBase::ResultE renderEnter   (Action  *action );
    virtual ActionBase::ResultE renderLeave   (Action  *action );

    virtual ActionBase::ResultE intersectEnter(Action  *action );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Access                                                       */
    /*! \{                                                                 */

    virtual RenderModeE getRenderMode(void) const;

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

    // Variables should all be in CPUSkinningAlgorithmBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    CPUSkinningAlgorithm(void);
    CPUSkinningAlgorithm(const CPUSkinningAlgorithm &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~CPUSkinningAlgorithm(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Transform                                  */
    /*! \{                                                                 */

    void transformGeometry(SkinnedGeometry           *skinGeo,
                           Skeleton                  *skel,
                           CPUSkinningDataAttachment *data );
    void transformObjectSpaceProperty (const MFMatrix            *jointMat,
                                       const GeoVec4fProperty    *jointIdx,
                                       const GeoVec4fProperty    *jointWeight,
                                       const GeoIntegralProperty *origIdx,
                                       const GeoVectorProperty   *origProp,
                                             GeoVectorProperty   *prop        );
    void transformTangentSpaceProperty(const MFMatrix            *jointMat,
                                       const GeoVec4fProperty    *jointIdx,
                                       const GeoVec4fProperty    *jointWeight,
                                       const GeoIntegralProperty *origIdx,
                                       const GeoVectorProperty   *origProp,
                                             GeoVectorProperty   *prop        );

    void renderGeometry(RenderAction              *ract,
                        SkinnedGeometry           *skinGeo,
                        CPUSkinningDataAttachment *data    );
    void drawPrimitives(SkinnedGeometry           *skinGeo,
                        CPUSkinningDataAttachment *data,
                        DrawEnv                   *pEnv    );

    void intersectGeometry(IntersectAction           *iact,
                           SkinnedGeometry           *skinGeo,
                           CPUSkinningDataAttachment *data);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Skeleton Change                             */
    /*! \{                                                                 */

    void skeletonChanged(FieldContainer *fc, ConstFieldMaskArg whichField);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

    virtual void resolveLinks(void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class CPUSkinningAlgorithmBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const CPUSkinningAlgorithm &source);
};

typedef CPUSkinningAlgorithm *CPUSkinningAlgorithmP;

OSG_END_NAMESPACE

#include "OSGCPUSkinningAlgorithmBase.inl"
#include "OSGCPUSkinningAlgorithm.inl"

#endif /* _OSGCPUSKINNINGALGORITHM_H_ */
