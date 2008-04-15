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

#ifndef _OSGVTKMAPPER_H_
#define _OSGVTKMAPPER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGVTKMapperBase.h"
#include "OSGMaterialChunk.h"

#ifdef OSG_WITH_VTK
#include <vtkTimeStamp.h>

class vtkActor;
class vtkCellArray;
#endif

#ifdef OSG_HAVE_ACTION //CHECK
#include "OSGActorBase.h"
#endif

OSG_BEGIN_NAMESPACE

class OSG_CONTRIBVTK_DLLMAPPING VTKMapper : public VTKMapperBase
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

    typedef VTKMapperBase Inherited;

#ifdef OSG_WITH_VTK
    vtkActor               *_pActor;
    vtkTimeStamp            _executeTime;
    vtkTimeStamp            _modifiedTime;
#endif

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    VTKMapper(void);
    VTKMapper(const VTKMapper &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~VTKMapper(void);

    virtual void resolveLinks(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Init                                       */
    /*! \{                                                                 */

    void initGeometries(void);

#ifdef OSG_WITH_VTK
    bool processPrimitive(OSG::GeoPnt3fPropertyPtr   pPoints,
                          OSG::GeoColor4fPropertyPtr pColors,
                          OSG::GeoVec3fPropertyPtr   pNormals,
                          OSG::GeoUInt32PropertyPtr  pLengths,
                          OSG::GeoUInt8PropertyPtr   pTypes,
                          
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

    ActionBase::ResultE     intersectEnter(Action    *action);
    ActionBase::ResultE     intersectLeave(Action    *action);

    ActionBase::ResultE     renderEnter   (Action    *action);
    ActionBase::ResultE     renderLeave   (Action    *action);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class VTKMapperBase;

    /*---------------------------------------------------------------------*/

    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const VTKMapper &source);
};

typedef VTKMapper *VTKMapperP;

typedef VTKMapper::ObjPtr      VTKMapperPtr;
typedef VTKMapper::ObjConstPtr VTKMapperConstPtr;

OSG_END_NAMESPACE

#include "OSGVTKMapperBase.inl"
#include "OSGVTKMapper.inl"

#endif /* _OSGVTKMAPPER_H_ */
