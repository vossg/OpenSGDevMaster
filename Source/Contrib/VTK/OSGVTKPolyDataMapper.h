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

#ifndef _OSGVTKPOLYDATAMAPPER_H_
#define _OSGVTKPOLYDATAMAPPER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGVTKPolyDataMapperBase.h"
#include "OSGChunkMaterial.h"
#include "OSGMaterialChunk.h"
#include "OSGGeometry.h"

#ifdef OSG_WITH_VTK
#include <vtkTimeStamp.h>

class vtkActor;
class vtkCellArray;
#endif

#ifdef OSG_HAVE_ACTION //CHECK
#include "OSGActorBase.h"
#endif

OSG_BEGIN_NAMESPACE

class OSG_CONTRIBVTK_DLLMAPPING VTKPolyDataMapper : public VTKPolyDataMapperBase
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin,
                         BitVector         detail);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    void execute(void);

#ifdef OSG_WITH_VTK
    void setActor(vtkActor *pActor);
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    void adjustVolume(Volume &volume);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    virtual void dump(      UInt32    uiIndent = 0,
                      const BitVector bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef VTKPolyDataMapperBase Inherited;

#ifdef OSG_WITH_VTK
    vtkActor               *_pActor;
    vtkTimeStamp            _executeTime;
    vtkTimeStamp            _modifiedTime;
#endif

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    VTKPolyDataMapper(void);
    VTKPolyDataMapper(const VTKPolyDataMapper &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~VTKPolyDataMapper(void);

    virtual void resolveLinks(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Init                                       */
    /*! \{                                                                 */

    void initGeometries(void);

#ifdef OSG_WITH_VTK
    bool processPrimitive(OSG::GeoPnt3fProperty   *pPoints,
                          OSG::GeoColor4fProperty *pColors,
                          OSG::GeoVec3fProperty   *pNormals,
                          OSG::GeoUInt32Property  *pLengths,
                          OSG::GeoUInt8Property   *pTypes,
                          
                          vtkActor                *actor, 
                          vtkCellArray            *primArray,
                          int                      primType, 
                          int                      verbose   );
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Init                                       */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name              Intersect & Render                              */
    /*! \{                                                                 */

    Action::ResultE intersectEnter(Action    *action);
    Action::ResultE intersectLeave(Action    *action);

    Action::ResultE renderEnter   (Action    *action);
    Action::ResultE renderLeave   (Action    *action);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class VTKPolyDataMapperBase;

    /*---------------------------------------------------------------------*/

    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const VTKPolyDataMapper &source);
};

typedef VTKPolyDataMapper *VTKPolyDataMapperP;

OSG_END_NAMESPACE

#include "OSGVTKPolyDataMapperBase.inl"
#include "OSGVTKPolyDataMapper.inl"

#endif /* _OSGVTKPOLYDATAMAPPER_H_ */
