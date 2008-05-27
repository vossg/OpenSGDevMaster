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

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#include <OSGGL.h>

#include <OSGIntersectAction.h>
#include <OSGRenderAction.h>

#ifdef OSG_HAVE_ACTION //CHECK
#include <OSGIntersectActor.h>
#endif

#include "OSGVTKPolyDataMapper.h"
#include "OSGVolume.h"
#include "OSGGeometry.h"
#include "OSGChunkMaterial.h"
#include "OSGMaterialChunk.h"
#include "OSGTwoSidedLightingChunk.h"

#ifdef OSG_WITH_VTK
#include "vtkDataSetReader.h"
#include "vtkPointSource.h"
#include "vtkStreamTracer.h"
#include "vtkStructuredGrid.h"
#include "vtkPolyData.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkPointData.h"
#include "vtkPolyDataMapper.h"
#include "vtkCellArray.h"
#include "vtkActor.h"
#include "vtkProperty.h"
#include "vtkDataArray.h"
#include "vtkCellData.h"
#endif

#include <typeinfo>

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGVTKPolyDataMapperBase.cpp file.
// To modify it, please change the .fcd file (OSGVTKPolyDataMapper.fcd) and
// regenerate the base file.

/*-------------------------------------------------------------------------*/
/*                               Sync                                      */

void VTKPolyDataMapper::changed(ConstFieldMaskArg whichField, 
                                UInt32            origin,
                                BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

/*-------------------------------------------------------------------------*/
/*                               Helper                                    */

void VTKPolyDataMapper::initGeometries(void)
{
    NodeUnrecPtr pRoot = Node::create();
    
    pRoot->setCore(Group::create());

    setRoot(pRoot);

    for(UInt32 i = 0; i < 4; ++i)
    {
        GeometryUnrecPtr           pGeo      = Geometry::create();
    
        ChunkMaterialUnrecPtr      pMat      = ChunkMaterial::create();
        MaterialChunkUnrecPtr      pMatChunk = MaterialChunk::create();
        
        GeoPnt3fPropertyUnrecPtr   pPoints   = GeoPnt3fProperty  ::create();
        GeoUInt32PropertyUnrecPtr  pLengths  = GeoUInt32Property ::create();
        GeoUInt8PropertyUnrecPtr   pTypes    = GeoUInt8Property  ::create();
        GeoColor4fPropertyUnrecPtr pColors   = GeoColor4fProperty::create();
        GeoVec3fPropertyUnrecPtr   pNormals  = GeoVec3fProperty  ::create();

        if(i < 2)
        {
            pMatChunk->setLit(false);
        }
        
        pMatChunk->setDiffuse  (OSG::Color4f(1.0, 1.0, 1.0, 1.0));
        pMatChunk->setSpecular (OSG::Color4f(0.0, 0.0, 0.0, 1.0));
        pMatChunk->setShininess(10.0f);
        
        pMat->addChunk(pMatChunk);

        TwoSidedLightingChunkUnrecPtr pTSLChunk = 
            TwoSidedLightingChunk::create();
            
        pMat->addChunk(pTSLChunk);

        pGeo->setDlistCache(false   );
        
        pGeo->setMaterial  (pMat    );
        pGeo->setPositions (pPoints );
        pGeo->setLengths   (pLengths);
        pGeo->setTypes     (pTypes  );
        pGeo->setColors    (pColors );

        if(i > 1)
        {
            pGeo->setNormals(pNormals);
        }

        OSG::NodeUnrecPtr pGeoRoot = OSG::Node::create();
        
        pGeoRoot->setCore    (pGeo);
        pGeoRoot->setTravMask(0   );

        pRoot->addChild(pGeoRoot);

        this->pushToGeometries    (pGeo     );
        this->pushToMaterials     (pMat     );
        this->pushToMaterialChunks(pMatChunk);
        this->pushToPositions     (pPoints  );
        this->pushToLength        (pLengths );
        this->pushToTypes         (pTypes   );
        this->pushToColors        (pColors  );
        this->pushToNormals       (pNormals );
        this->pushToGeoRoots      (pGeoRoot );
    }
}

#ifdef OSG_WITH_VTK
typedef double vtkReal;

bool VTKPolyDataMapper::processPrimitive(
    OSG::GeoPnt3fProperty   *pPoints,
    OSG::GeoColor4fProperty *pColors,
    OSG::GeoVec3fProperty   *pNormals,
    OSG::GeoUInt32Property  *pLengths,
    OSG::GeoUInt8Property   *pTypes,
    
    vtkActor                *actor, 
    vtkCellArray            *primArray,
    int                      primType, 
    int                      verbose) 
{

  // get polyData from vtkActor

    vtkPolyData *polyData = 
        static_cast<vtkPolyData *>(actor->GetMapper()->GetInput());
    
    int numPrimitives = primArray->GetNumberOfCells();
    
    if(numPrimitives == 0) 
        return false;

    OSG::GeoUInt32Property::StoredFieldType   *pLengthField = 
        pLengths->editFieldPtr();

    OSG::GeoUInt8Property::StoredFieldType    *pTypeField   = 
        pTypes  ->editFieldPtr();

    OSG::GeoPnt3fProperty::StoredFieldType    *pPointField  = 
        pPoints ->editFieldPtr();
    
    OSG::GeoColor4fProperty::StoredFieldType  *pColorField  = 
        pColors ->editFieldPtr();

    OSG::GeoVec3fProperty::StoredFieldType    *pNormalField = 
        pNormals->editFieldPtr();

    // get number of indices in the vtk prim array. Each vtkCell has the length
    // (not counted), followed by the indices.
    int primArraySize = primArray->GetNumberOfConnectivityEntries();
    int numIndices    = primArraySize - numPrimitives;

    pTypeField  ->clear();
    pLengthField->clear();
    pPointField ->clear();
    pColorField ->clear();
    pNormalField->clear();
    
    pLengthField->resize(numPrimitives);
    pTypeField  ->resize(numPrimitives);

    pPointField ->resize(numIndices   );

    // get the data
    UInt32        normalPerVertex = 0;
    UInt32        normalPerCell   = 0;
    vtkDataArray *normalArray     = polyData->GetPointData()->GetNormals();
        
    if(actor->GetProperty()->GetInterpolation() == VTK_FLAT)
    {
        normalArray = NULL;
    }
    
    if(normalArray != NULL)
    {
        normalPerVertex = 1;
    }
    else 
    {
        normalArray = polyData->GetCellData()->GetNormals();
        
        if(normalArray != NULL)
        {
            normalPerCell = 1;
        }
    }
    
    UInt32             colorPerCell   = 0;
    UInt32             colorPerVertex = 0;
    UInt32             colorPerObject = 0;
    Real64            *objectColor    = NULL;

    vtkUnsignedCharArray *colorArray = actor->GetMapper()->MapScalars(1.0);
    
    if(actor->GetMapper()->GetScalarVisibility() && colorArray != NULL) 
    {
        int scalarMode = actor->GetMapper()->GetScalarMode();
        
        if(scalarMode == VTK_SCALAR_MODE_USE_CELL_DATA ||
           !polyData->GetPointData()->GetScalars()) // no point data
        {
            colorPerCell = 1;
        }
        else
        {
            colorPerVertex = 1;
        }
    }
    else
    {
        colorPerObject = 1;

        objectColor = actor->GetProperty()->GetColor();
    }

    fprintf(stderr, "Got normals %d %d %p\n",  
            normalPerCell, 
            normalPerVertex,
            normalArray);
    
    fprintf(stderr, "Got colors %d %d %d %p %p\n",  
            colorPerCell, 
            colorPerVertex,
            colorPerObject,
            colorArray,
            objectColor);
    
    if(normalPerCell == 1 || normalPerVertex == 1)
    {           
        pNormalField->resize(numIndices);
    }
    
    pColorField ->resize(numIndices);
    
    int prim = 0, vert = 0;
    vtkIdType i, npts, *pts;
    int transparentFlag = 0;
    
    unsigned char *aColor  = NULL;
    vtkReal       *aNormal = NULL;
    
    for(primArray->InitTraversal(); 
        primArray->GetNextCell(npts, pts); 
        prim++) 
    { 
        (*pTypeField  )[prim] = primType;
        (*pLengthField)[prim] = npts;
        
        if(colorPerCell == 1) 
        {
            aColor = colorArray->GetPointer(4 * prim);
        }
        
        if(normalPerCell == 1) 
        {
            aNormal = normalArray->GetTuple(prim);
        }
        
        for(i = 0; i < npts; i++) 
        {
            vtkReal *aVertex = polyData->GetPoint(pts[i]);
            
            (*pPointField)[vert].setValues(
                Real32(aVertex[0]), 
                Real32(aVertex[1]), 
                Real32(aVertex[2]));
            
            if(colorPerVertex == 1 && colorArray != NULL)
            {
                aColor = colorArray->GetPointer(4 * pts[i]);
            }
            
            if(aColor != NULL)
            {
                (*pColorField)[vert].setValuesRGBA(
                    aColor[0]/255.0f, 
                    aColor[1]/255.0f,
                    aColor[2]/255.0f,
                    aColor[3]/255.0f);
            }
            else
            {
                if(colorPerObject == 1 && objectColor != NULL)
                {
                    (*pColorField)[vert].setValuesRGBA(objectColor[0],
                                                       objectColor[1],
                                                       objectColor[2],
                                                       1.f);
                }
                else
                {
                    (*pColorField)[vert].setValuesRGBA(
                        1.0f, 1.0f, 1.0f, 1.0f);
                }
            }
            
            if(normalPerVertex == 1 && normalArray != NULL)
            {
                aNormal = normalArray->GetTuple(pts[i]);
            }
            
            if(aNormal != NULL)
            {
                (*pNormalField)[vert].setValues(Real32(aNormal[0]), 
                                                Real32(aNormal[1]), 
                                                Real32(aNormal[2]));
            }
            
            vert++;
        }
    }

    return true;
}
#endif

void VTKPolyDataMapper::execute(void)
{
#ifdef OSG_WITH_VTK
    if(_pActor == NULL)
    {
        return;
    }

    vtkMapper *pMapper = _pActor->GetMapper();
    
    if(pMapper == NULL)
        return;

    pMapper->GetInput()->Update();
    
    if( (_pActor ->            GetMTime() < this->_executeTime) && 
        ( pMapper->            GetMTime() < this->_executeTime) &&
        ( pMapper->GetInput()->GetMTime() < this->_executeTime) &&
        ( this->_modifiedTime             < this->_executeTime)  )
    {
        return;
    }
    else
    {
        fprintf(stderr, "%ld %ld | %ld %ld %ld\n",
                _executeTime.GetMTime(),
                _modifiedTime.GetMTime(),
                _pActor->GetMTime(),
                _pActor->GetMapper()->GetMTime(),
                _pActor->GetMapper()->GetInput()->GetMTime());
    }

    if(_sfRoot.getValue() == NULL)
    {
        initGeometries();
    }

    fprintf(stderr, "Mapper::execute %p\n", _pActor);

    // get poly data
    vtkPolyData *polyData = 
        static_cast<vtkPolyData *>(_pActor->GetMapper()->GetInput());

    if(polyData == NULL)
    {
        fprintf(stderr, "Strange no data\n");
        return;
    }

    // get primitive arrays
    vtkCellArray *points, *lines, *polys, *strips;
    
    points = polyData->GetVerts();
    lines  = polyData->GetLines();
    polys  = polyData->GetPolys();
    strips = polyData->GetStrips();
    
    int numPts    = points->GetNumberOfCells();
    int numLines  = lines ->GetNumberOfCells();
    int numPolys  = polys ->GetNumberOfCells();
    int numStrips = strips->GetNumberOfCells();

    fprintf(stderr, "P : %d | L : %d | Poly : %d | S : %d\n",
            numPts,
            numLines,
            numPolys,
            numStrips);    



    if(numPts != 0)
    {
        bool rc = processPrimitive(_mfPositions[0],
                                   _mfColors   [0],
                                   _mfNormals  [0],
                                   _mfLength   [0],
                                   _mfTypes    [0],

                                    _pActor,
                                     points,
                                     GL_POINTS,
                                     true);
   
        if(rc == true)
        {
            _mfGeoRoots[0]->setTravMask(OSG::TypeTraits<OSG::UInt32>::BitsSet);

            _mfGeoRoots[0]->invalidateVolume();
        }
    }

    if(numLines != 0)
    {
        bool rc = processPrimitive(_mfPositions[1],
                                   _mfColors   [1],
                                   _mfNormals  [1],
                                   _mfLength   [1],
                                   _mfTypes    [1],

                                   _pActor,
                                    lines,
                                    GL_LINE_STRIP,
                                    true);
   
        if(rc == true)
        {
            _mfGeoRoots[1]->setTravMask(OSG::TypeTraits<OSG::UInt32>::BitsSet);
            _mfGeoRoots[1]->invalidateVolume();
        }
    }


    if(numPolys != 0)
    {
        bool rc = processPrimitive(_mfPositions[2],
                                   _mfColors   [2],
                                   _mfNormals  [2],
                                   _mfLength   [2],
                                   _mfTypes    [2],
 
                                   _pActor,
                                    polys,
                                    GL_POLYGON,
                                    true);
   
        if(rc == true)
        {
            _mfGeoRoots[2]->setTravMask(OSG::TypeTraits<OSG::UInt32>::BitsSet);
            _mfGeoRoots[2]->invalidateVolume();
        }
    }

    if(numStrips != 0)
    {
        bool rc = processPrimitive(_mfPositions[3],
                                   _mfColors   [3],
                                   _mfNormals  [3],
                                   _mfLength   [3],
                                   _mfTypes    [3],
 
                                   _pActor,
                                    strips,
                                    GL_TRIANGLE_STRIP,
                                    true);
   
        if(rc == true)
        {
            _mfGeoRoots[3]->setTravMask(OSG::TypeTraits<OSG::UInt32>::BitsSet);
            _mfGeoRoots[3]->invalidateVolume();
        }
    }

    _sfRoot.getValue()->updateVolume();

    this->_executeTime.Modified();
        
    OSG::Thread::getCurrentChangeList()->commitChanges();
#endif
}

#ifdef OSG_WITH_VTK
void VTKPolyDataMapper::setActor(vtkActor *pActor)
{
    if(_pActor != NULL)
        _pActor->UnRegister(NULL);

    _pActor = pActor;

    if(_pActor != NULL)
        _pActor->Register(NULL);

    this->_modifiedTime.Modified();
}
#endif


void VTKPolyDataMapper::adjustVolume(Volume &volume)
{
    this->execute();

    if(_sfRoot.getValue() != NULL)
    {
        _sfRoot.getValue()->updateVolume();
        
        volume.extendBy(_sfRoot.getValue()->getVolume());
    }
}

/*-------------------------------------------------------------------------*/
/*                                Dump                                     */

void VTKPolyDataMapper::dump(      UInt32    uiIndent, 
                             const BitVector bvFlags ) const
{
   Inherited::dump(uiIndent, bvFlags);

   indentLog(uiIndent, PLOG);
   PLOG << "{" << std::endl;

   indentLog(uiIndent + 4, PLOG);
   PLOG << "Root" << std::endl;

   if(_sfRoot.getValue() != NULL)
   {
       _sfRoot.getValue()->dump(uiIndent + 8, bvFlags);
   }
   else
   {
       indentLog(uiIndent + 8, PLOG);
       PLOG << "(NULL)" << std::endl;
   }

    indentLog(uiIndent, PLOG);
    PLOG << "}" << std::endl;
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

VTKPolyDataMapper::VTKPolyDataMapper(void) :
     Inherited   (    )
#ifdef OSG_WITH_VTK
   ,_pActor      (NULL),
    _executeTime (    ),
    _modifiedTime(    )
#endif
{
}

VTKPolyDataMapper::VTKPolyDataMapper(const VTKPolyDataMapper &source) :
     Inherited   (source)
#ifdef OSG_WITH_VTK
   ,_pActor      (NULL  ),
    _executeTime (      ),
    _modifiedTime(      )
#endif
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

VTKPolyDataMapper::~VTKPolyDataMapper(void)
{
}

void VTKPolyDataMapper::resolveLinks(void)
{
    Inherited::resolveLinks();

#ifdef OSG_WITH_VTK
    if(_pActor != NULL)
        _pActor->UnRegister(NULL);
#endif
}

/*-------------------------------------------------------------------------*/
/*                                Render                                   */

ActionBase::ResultE VTKPolyDataMapper::renderEnter(Action *action)
{
    RenderAction *pAction = dynamic_cast<RenderAction *>(action);
    
    this->execute();


    if(pAction == NULL)
        return ActionBase::Skip;

    if(pAction!= NULL)
    {
        pAction->useNodeList();

//    if(pAction->isVisible(getCPtr(_sfRoot.getValue())))
        {
            pAction->addNode(_sfRoot.getValue());
        }
    }

    return ActionBase::Continue;
}

ActionBase::ResultE VTKPolyDataMapper::renderLeave(Action *action)
{
    RenderAction *pAction = dynamic_cast<RenderAction *>(action);

    return ActionBase::Continue;
}


/*-------------------------------------------------------------------------*/
/*                            Intersect                                    */

ActionBase::ResultE VTKPolyDataMapper::intersectEnter(Action *action)
{
/*
    IntersectAction *ia = dynamic_cast<IntersectAction *>(action);
    Matrix           m  = this->getMatrix();

    m.invert();
    
    Pnt3f pos;
    Vec3f dir;

    m.multFullMatrixPnt(ia->getLine().getPosition (), pos);
    m.multMatrixVec    (ia->getLine().getDirection(), dir);
    
    ia->setLine(Line(pos, dir), ia->getMaxDist());
    ia->scale(dir.length());
 */
    
    return ActionBase::Continue; 
}

ActionBase::ResultE VTKPolyDataMapper::intersectLeave(Action *action)
{
/*
    IntersectAction *ia = dynamic_cast<IntersectAction *>(action);
    Matrix           m  = this->getMatrix();
    
    Pnt3f pos;
    Vec3f dir;

    m.multFullMatrixPnt(ia->getLine().getPosition (), pos);
    m.multMatrixVec    (ia->getLine().getDirection(), dir);
    
    ia->setLine(Line(pos, dir), ia->getMaxDist());
    ia->scale(dir.length());
 */

    return ActionBase::Continue;
}



/*-------------------------------------------------------------------------*/
/*                                Init                                     */

void VTKPolyDataMapper::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        IntersectAction::registerEnterDefault( 
            getClassType(), 
            reinterpret_cast<
                Action::Callback>(&VTKPolyDataMapper::intersectEnter));
        
        IntersectAction::registerLeaveDefault( 
            getClassType(), 
            reinterpret_cast<
                Action::Callback>(&VTKPolyDataMapper::intersectLeave));
        
        
        RenderAction::registerEnterDefault(
            getClassType(), 
            reinterpret_cast<
                Action::Callback>(&VTKPolyDataMapper::renderEnter));
        
        RenderAction::registerLeaveDefault(
            getClassType(), 
            reinterpret_cast<
                Action::Callback>(&VTKPolyDataMapper::renderLeave));
    }
}
