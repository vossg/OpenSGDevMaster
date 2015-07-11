/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                Copyright (C) 2011 by the OpenSG Forum                     *
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

#include "OSGOFPrimaryRecords.h"

#include "OSGBlendChunk.h"
#include "OSGChunkMaterial.h"
#include "OSGDepthChunk.h"
#include "OSGGeometry.h"
#include "OSGGeoFunctions.h"
#include "OSGGroup.h"
#include "OSGPolygonChunk.h"
#include "OSGRangeLOD.h"
#include "OSGSceneFileHandler.h"
#include "OSGTextureEnvChunk.h"

#include "OSGOFAncillaryRecords.h"
#include "OSGOFDatabase.h"
#include "OSGOpenFlightSceneFileType.h"
#include "OSGOpenFlightLog.h"


OSG_BEGIN_NAMESPACE

// constants for Faces and Meshes
namespace
{
    // Flags
    const Int32  FlagTerrain             = 0x80000000;
    const Int32  FlagNoColor             = 0x40000000;
    const Int32  FlagNoAltColor          = 0x20000000;
    const Int32  FlagPackedColor         = 0x10000000;
    const Int32  FlagTerrainFootprint    = 0x08000000;
    const Int32  FlagHidden              = 0x04000000;
    const Int32  FlagRoofline            = 0x02000000;

    // DrawType constants
    const Int8   DTSolidCullBack         =  0;
    const Int8   DTSolid                 =  1;
    const Int8   DTWireframeClosed       =  2;
    const Int8   DTWireframe             =  3;
    const Int8   DTWireframeSurround     =  4;
    const Int8   DTOmnidirectionalLight  =  8;
    const Int8   DTUnidirectionalLight   =  9;
    const Int8   DTBidirectionalLight    = 10;

    // LightMode constants
    const UInt8  LMFaceColor             =  0;  // used in FaceRecord
    const UInt8  LMMeshColor             =  0;  // used in MeshRecord
    const UInt8  LMVertexColor           =  1;
    const UInt8  LMFaceColorLit          =  2;  // used in FaceRecord
    const UInt8  LMMeshColorLit          =  2;  // used in MeshRecord
    const UInt8  LMVertexColorLit        =  3;

    Real32 unitToMetersScale(OFDatabase::VertexUnits unit);



    Real32 unitToMetersScale(OFDatabase::VertexUnits unit)
    {
        Real32 returnValue = 1.f;

        switch(unit)
        {
        case OFDatabase::VU_Meters:
            returnValue = 1.f;
            break;

        case OFDatabase::VU_Kilometers:
            returnValue = 1000.f;
            break;

        case OFDatabase::VU_Feet:
            returnValue = 0.3048f;
            break;

        case OFDatabase::VU_Inches:
            returnValue = 0.0254f;
            break;

        case OFDatabase::VU_NauticalMiles:
            returnValue = 1852.f;
            break;
        }

        return returnValue;
    }

} // namespace


//---------------------------------------------------------------------
// OFHeaderRecord
//---------------------------------------------------------------------

OFHeaderRecord::OFHeaderRecord(const OFRecordHeader &oHeader,
                                     OFDatabase     &oDB     ) :
  Inherited(oHeader, oDB)
{
}

OFHeaderRecord::~OFHeaderRecord(void)
{
}

/* static */
OFRecordTransitPtr OFHeaderRecord::create(const OFRecordHeader &oHeader,
                                                OFDatabase     &oDB     )
{
    return OFRecordTransitPtr(new OFHeaderRecord(oHeader, oDB));
}

bool OFHeaderRecord::read(std::istream &is)
{
    OSG_OPENFLIGHT_LOG(("OFHeaderRecord::read len [%u]\n", _sLength));

    Char8 szAsciiId[8];      Inherited::readChar8(is, szAsciiId, 8);
    Int32 formatRev;         Inherited::readVal(is, formatRev);
    Int32 editRev;           Inherited::readVal(is, editRev);
    Char8 lastEditTime[32];  Inherited::readChar8(is, lastEditTime, 32);
    Int16 nextGroupNodeId;   Inherited::readVal(is, nextGroupNodeId);
    Int16 nextLODNodeId;     Inherited::readVal(is, nextLODNodeId);
    Int16 nextObjectNodeId;  Inherited::readVal(is, nextObjectNodeId);
    Int16 nextFaceNodeId;    Inherited::readVal(is, nextFaceNodeId);
    Int16 unitMult;          Inherited::readVal(is, unitMult);
    Int8  vertUnits;         Inherited::readVal(is, vertUnits);
    Int8  faceTexWhite;      Inherited::readVal(is, faceTexWhite);
    Int32 flags;             Inherited::readVal(is, flags);

#if 0
    OSG_OPENFLIGHT_LOG(("OFHeaderRecord::read szAsciiId        [%s]\n", szAsciiId));
    OSG_OPENFLIGHT_LOG(("OFHeaderRecord::read formatRev        [%u]\n", formatRev));
    OSG_OPENFLIGHT_LOG(("OFHeaderRecord::read editRev          [%u]\n", editRev));
    OSG_OPENFLIGHT_LOG(("OFHeaderRecord::read lastEditTime     [%s]\n", lastEditTime));
    OSG_OPENFLIGHT_LOG(("OFHeaderRecord::read nextGroupNodeId  [%u]\n", nextGroupNodeId));
    OSG_OPENFLIGHT_LOG(("OFHeaderRecord::read nextLODNodeId    [%u]\n", nextLODNodeId));
    OSG_OPENFLIGHT_LOG(("OFHeaderRecord::read nextObjectNodeId [%u]\n", nextObjectNodeId));
    OSG_OPENFLIGHT_LOG(("OFHeaderRecord::read nextFaceNodeId   [%u]\n", nextFaceNodeId));
    OSG_OPENFLIGHT_LOG(("OFHeaderRecord::read unitMult         [%u]\n", unitMult));
    OSG_OPENFLIGHT_LOG(("OFHeaderRecord::read vertUnits        [%u]\n", vertUnits));
    OSG_OPENFLIGHT_LOG(("OFHeaderRecord::read faceTexWhite     [%u]\n", faceTexWhite));
    OSG_OPENFLIGHT_LOG(("OFHeaderRecord::read flags            [%x]\n", flags));
#endif

    OFDatabase::VertexUnits fileUnits =
        static_cast<OFDatabase::VertexUnits>(vertUnits);
    Real32                  unitScale = unitToMetersScale(fileUnits) /
                                        unitToMetersScale(_oDB.getTargetUnits());
    _oDB.setUnitScale(unitScale);

    // read and discard remainder of header record
    std::vector<char> tmpBuf;

    tmpBuf.resize(_sLength);

    is.read(&(tmpBuf.front()), _sLength - 68);

    return is.good();
}

NodeTransitPtr OFHeaderRecord::convertToNode(void)
{
    NodeUnrecPtr returnValue(NULL);

    if(_primaryChildren.empty() == false)
    {
        returnValue = makeCoredNode<Group>();

        for(UInt32 i = 0; i < _primaryChildren.size(); ++i)
        {
            NodeTransitPtr pChild = _primaryChildren[i]->convertToNode();

            if(pChild != NULL)
            {
                returnValue->addChild(pChild);
            }
            else
            {
                FFATAL(("OFHeaderRecord::convertToNode: "
                        "No child created for record [%u - %s].\n",
                        _primaryChildren[i]->getOpCode(),
                        getOpCodeString(_primaryChildren[i]->getOpCode())));
            }
        }
    }

    return NodeTransitPtr(returnValue);
}

bool OFHeaderRecord::addChild(OFRecord *pChild)
{
    if(pChild == NULL)
        return false;

    bool returnValue = false;

    switch(pChild->getOpCode())
    {
    case OFColorPaletteRecord::OpCode:
    {
        OFColorPaletteRecord *pCol =
            dynamic_cast<OFColorPaletteRecord *>(pChild);

        _oDB.addColorPaletteRecord(pCol);

        returnValue = true;
    }
    break;

    case OFTexturePaletteRecord::OpCode:
    {
        OFTexturePaletteRecord *pTex =
            dynamic_cast<OFTexturePaletteRecord *>(pChild);

        _oDB.addTexturePaletteRecord(pTex);

        returnValue = true;
    }
    break;

    case OFVertexPaletteRecord::OpCode:
    {
        OFVertexPaletteRecord *pVert =
            dynamic_cast<OFVertexPaletteRecord *>(pChild);

        _oDB.addVertexPaletteRecord(pVert);

        returnValue = true;
    }
    break;

    case OFMaterialPaletteRecord::OpCode:
    {
        OFMaterialPaletteRecord *pMat =
            dynamic_cast<OFMaterialPaletteRecord *>(pChild);

        _oDB.addMaterialPaletteRecord(pMat);

        returnValue = true;
    }
    break;

    default:
        break;
    }

    if(returnValue == false)
        returnValue = Inherited::addChild(pChild);

    return returnValue;
}

UInt16 OFHeaderRecord::getOpCode(void) const
{
    return OpCode;
}

void OFHeaderRecord::dump(UInt32 uiIndent) const
{
    indentLog(uiIndent, PLOG);
    PLOG << "HeaderRecord" << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "{" << std::endl;

    uiIndent += 2;

    if(_oDB.getColorPalette() != NULL)
        _oDB.getColorPalette()->dump(uiIndent);

    if(_oDB.getVertexPalette() != NULL)
        _oDB.getVertexPalette()->dump(uiIndent);

    uiIndent -= 2;

    indentLog(uiIndent, PLOG);
    PLOG << "}" << std::endl;

    Inherited::dump(uiIndent);
}

//---------------------------------------------------------------------
// OFGroupRecord
//---------------------------------------------------------------------

OFRecordTransitPtr OFGroupRecord::create(const OFRecordHeader &oHeader,
                                               OFDatabase     &oDB     )
{
    return OFRecordTransitPtr(new OFGroupRecord(oHeader, oDB));
}

OFGroupRecord::OFGroupRecord(const OFRecordHeader &oHeader,
                                   OFDatabase     &oDB     ) :
    Inherited(oHeader, oDB)
{
}

OFGroupRecord::~OFGroupRecord(void)
{
}

bool OFGroupRecord::read(std::istream &is)
{
    OSG_OPENFLIGHT_LOG(("OFGroupRecord::read len [%u]\n",
                        _sLength));

    Inherited::readChar8(is, szASCIIId, 8);

    is.ignore(_sLength - 12); // skip rest of record

    return is.good();
}

NodeTransitPtr OFGroupRecord::convertToNode(void)
{
    NodeUnrecPtr returnValue(NULL);

    if(_primaryChildren.empty() == false)
    {
        if(_primaryChildren.size() > 1)
        {
            returnValue = makeCoredNode<Group>();

            for(UInt32 i = 0; i < _primaryChildren.size(); ++i)
            {
                NodeTransitPtr pChild = _primaryChildren[i]->convertToNode();

                if(pChild != NULL)
                {
                    returnValue->addChild(pChild);
                }
            }
        }
        else
        {
            returnValue = _primaryChildren[0]->convertToNode();
        }
    }

    returnValue = convertAncillaryChildren(returnValue);

    return NodeTransitPtr(returnValue);
}

UInt16 OFGroupRecord::getOpCode(void) const
{
    return OpCode;
}

void OFGroupRecord::dump(UInt32 uiIndent) const
{
    indentLog(uiIndent, PLOG);
    PLOG << "GroupRecord" << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "{" << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "}" << std::endl;

    Inherited::dump(uiIndent);
}

NodeTransitPtr OFGroupRecord::convertAncillaryChildren(Node *pNode)
{
    NodeUnrecPtr returnValue(pNode);

    for(UInt32 i = 0; i < _ancillaryChildren.size(); ++i)
    {
        returnValue = _ancillaryChildren[i]->convert(returnValue);
    }

    return NodeTransitPtr(returnValue);
}

OFRecordFactoryBase::RegisterRecord OFGroupRecord::_regHelper(
    &OFGroupRecord::create,
    OFGroupRecord::OpCode);


//---------------------------------------------------------------------
// OFObjectRecord
//---------------------------------------------------------------------

OFRecordTransitPtr OFObjectRecord::create(const OFRecordHeader &oHeader,
                                                OFDatabase     &oDB     )
{
    return OFRecordTransitPtr(new OFObjectRecord(oHeader, oDB));
}

OFObjectRecord::OFObjectRecord(const OFRecordHeader &oHeader,
                                     OFDatabase     &oDB     ) :
    Inherited     (oHeader, oDB),
    szASCIIId     (),
    flags         (0),
    relPriority   (0),
    transparency  (0),
    specialEffect1(0),
    specialEffect2(0),
    significance  (0),
    reserved      (0),
    _vFaces       (),
    _vMeshes      ()
{
}

OFObjectRecord::~OFObjectRecord(void)
{
}

void OFObjectRecord::dump(UInt32 uiIndent) const
{
    indentLog(uiIndent, PLOG);
    PLOG << "ObjectRecord" << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "{" << std::endl;

    uiIndent += 2;

    indentLog(uiIndent, PLOG);
    PLOG << "#Faces " << _vFaces.size() << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "[" << std::endl;

    uiIndent += 2;

    for(UInt32 i = 0; i < _vFaces.size(); ++i)
    {
        _vFaces[i]->dump(uiIndent);
    }

    uiIndent -= 2;

    indentLog(uiIndent, PLOG);
    PLOG << "]" << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "#Meshes " << _vMeshes.size() << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "[" << std::endl;

    uiIndent += 2;

    for(UInt32 i = 0; i < _vMeshes.size(); ++i)
    {
        _vMeshes[i]->dump(uiIndent);
    }

    uiIndent -= 2;

    indentLog(uiIndent, PLOG);
    PLOG << "]" << std::endl;

    uiIndent -= 2;

    indentLog(uiIndent, PLOG);
    PLOG << "}" << std::endl;

    Inherited::dump(uiIndent);
}

bool OFObjectRecord::read(std::istream &is)
{
    OSG_OPENFLIGHT_LOG(("OFObjectRecord::read len [%u]\n", _sLength));

    Inherited::readChar8(is, szASCIIId, 8);
    Inherited::readVal  (is, flags);
    Inherited::readVal  (is, relPriority);
    Inherited::readVal  (is, transparency);
    Inherited::readVal  (is, specialEffect1);
    Inherited::readVal  (is, specialEffect2);
    Inherited::readVal  (is, significance);
    Inherited::readVal  (is, reserved);

    return is.good();
}


bool OFObjectRecord::addChild(OFRecord *pChild)
{
    if(pChild == NULL)
        return false;

    bool returnValue = false;

    switch(pChild->getOpCode())
    {
    case OFFaceRecord::OpCode:
    {
        _vFaces.push_back(dynamic_cast<OFFaceRecord *>(pChild));

        returnValue = true;
    }
    break;

    case OFMeshRecord::OpCode:
    {
        _vMeshes.push_back(dynamic_cast<OFMeshRecord *>(pChild));

        returnValue = true;
    }
    break;

    case OFLocalVertexPoolRecord::OpCode:
    {
        _vMeshes.back()->addChild(pChild);

        returnValue = true;
    }
    break;

    default:
        break;
    }

    if(returnValue == false)
        returnValue = Inherited::addChild(pChild);

    return returnValue;
}

UInt16 OFObjectRecord::getOpCode(void) const
{
    return OpCode;
}

NodeTransitPtr OFObjectRecord::convertToNode(void)
{
    NodeTransitPtr returnValue(NULL);

    NodeUnrecPtr   pGeo = convertGeometry();

    returnValue = convertAncillaryChildren(pGeo);

    return returnValue;
}

void OFObjectRecord::groupFaces(
    std::vector< std::vector<OFFaceRecord *> > &vFaceGroups)
{
    if(_vFaces.size() == 0)
        return;

    vFaceGroups.clear();

    std::vector<OFFaceRecord *> tmpVec;
    tmpVec.push_back(_vFaces[0]);

    vFaceGroups.push_back(tmpVec);

    UInt32 j = 0;

    for(UInt32 i = 1; i < _vFaces.size(); ++i)
    {
        for(j = 0; j < vFaceGroups.size(); ++j)
        {
            if(*(_vFaces[i]) == *(vFaceGroups[j][0]))
            {
                vFaceGroups[j].push_back(_vFaces[i]);
                break;
            }
        }

        if(j == vFaceGroups.size())
        {
            tmpVec.clear();
            tmpVec.push_back(_vFaces[i]);

            vFaceGroups.push_back(tmpVec);
        }
    }
}

NodeTransitPtr OFObjectRecord::convertFaceGroup(
    std::vector<OFFaceRecord *> &vFaceGroup)
{
    NodeTransitPtr returnValue(NULL);

    if(vFaceGroup.size() == 0)
        return returnValue;

    typedef OFVertexPaletteRecord::VertexInfo VertexInfo;

                     returnValue = Node    ::create();
    GeometryUnrecPtr pGeo        = Geometry::create();

    returnValue->setCore(pGeo);

    GeoUInt32PropertyUnrecPtr  pindex = GeoUInt32Property::create();
    GeoUInt32PropertyUnrecPtr  nindex = NULL;
    GeoUInt32PropertyUnrecPtr  tindex = NULL;
    GeoUInt32PropertyUnrecPtr  lens   = GeoUInt32Property::create();
    GeoUInt8PropertyUnrecPtr   types  = GeoUInt8Property ::create();

    GeoUInt32Property::StoredFieldType *pPI = pindex->editFieldPtr();
    GeoUInt32Property::StoredFieldType *pNI = NULL;
    GeoUInt32Property::StoredFieldType *pTI = NULL;
    GeoUInt32Property::StoredFieldType *pL  = lens ->editFieldPtr();
    GeoUInt8Property ::StoredFieldType *pT  = types->editFieldPtr();

    const OFVertexPaletteRecord *pVertexPal = _oDB.getVertexPalette();

    UInt32 uiNumValid;

    GeoPnt3fPropertyUnrecPtr  pnts  = GeoPnt3fProperty ::create();
    GeoVec3fPropertyUnrecPtr  norms = NULL;
    GeoVec2fPropertyUnrecPtr  tex   = NULL;

    GeoPnt3fProperty::StoredFieldType *pPos  = pnts ->editFieldPtr();
    GeoVec3fProperty::StoredFieldType *pNorm = NULL;
    GeoVec2fProperty::StoredFieldType *pTX   = NULL;

    UInt16 uiFirstVType = 0;
    bool   bSingleIdx   = true;

    for(UInt32 i = 0; i < vFaceGroup.size(); ++i)
    {
        OFFaceRecord       *pFace  = vFaceGroup[i];
        OFVertexListRecord *pVList = vFaceGroup[i]->getVertexList();

        if(pVList != NULL)
        {
            const std::vector<Int32> &vIndices = pVList->getIndices();

            uiNumValid = 0;

            for(UInt32 j = 0; j < vIndices.size(); ++j)
            {
                const VertexInfo *vInfo        =
                    pVertexPal->getVertexInfo(vIndices[j]);
                UInt16            uiVType      = 0;

                if(vInfo != NULL)
                {
                    uiVType = vInfo->uiType;

                    if(pFace->getLightMode() == 0 ||
                       pFace->getLightMode() == 1   )
                    {
                        uiVType &= ~OFVertexPaletteRecord::HasNorm;
                    }

                    // First Vertex
                    if(i == 0 && j == 0)
                    {
                        uiFirstVType = uiVType;

                        if(uiFirstVType & OFVertexPaletteRecord::HasNorm)
                        {
                            norms  = GeoVec3fProperty ::create();
                            pNorm  = norms->editFieldPtr();

                            nindex = GeoUInt32Property::create();
                            pNI    = nindex->editFieldPtr();
                        }

                        if(uiFirstVType & OFVertexPaletteRecord::HasTexCoord)
                        {
                            tex    = GeoVec2fProperty ::create();
                            pTX    = tex ->editFieldPtr();

                            tindex = GeoUInt32Property::create();
                            pTI    = tindex->editFieldPtr();
                       }
                    }

                    if(uiFirstVType != uiVType)
                    {
                        FWARNING(("OFObjectRecord::convertFaceGroup: "
                                  "Found different vtypes - first [0x%x] "
                                  "current [0x%x] face [%u/%" PRIUSize "] "
                                  "vert [%u]\n",
                                  uiFirstVType, uiVType,
                                  i, vFaceGroup.size(), j));
                    }

                    UInt32 uiPosIdx =
                        vInfo->uiIdx[OFVertexPaletteRecord::PosIdx];

                    pPI->push_back(pPos->size32());

                    pPos->push_back(pVertexPal->getPos(uiPosIdx));

                    if(uiFirstVType & OFVertexPaletteRecord::HasNorm)
                    {
                        // XXX TODO:
                        // there are models where some vertices have normals
                        // and others don't.
                        // For now we insert a dummy normal

                        if((uiVType & OFVertexPaletteRecord::HasNorm) != 0)
                        {
                            UInt32 uiNormIdx =
                                vInfo->uiIdx[OFVertexPaletteRecord::NormIdx];

                            pNI->push_back(pNorm->size32());

                            pNorm->push_back(pVertexPal->getNormal(uiNormIdx));

                            if(uiNormIdx != uiPosIdx)
                            {
                                bSingleIdx = false;
                            }
                        }
                        else
                        {
                            pNI->push_back(pNorm->size32());
                            pNorm->push_back(Vec3f(0.f, 0.f, 1.f));

                            bSingleIdx = false;
                        }
                    }

                    if(uiFirstVType & OFVertexPaletteRecord::HasTexCoord)
                    {
                        UInt32 uiTXIdx =
                            vInfo->uiIdx[OFVertexPaletteRecord::TexCoordIdx];

                        pTI->push_back(pTX->size32());

                        pTX->push_back(pVertexPal->getTexCoord(uiTXIdx));

                        if(uiTXIdx != uiPosIdx)
                        {
                            bSingleIdx = false;
                        }
                    }

                    ++uiNumValid;
                }
            }

            pL->push_back(uiNumValid);
            pT->push_back(GL_POLYGON);
        }
    }

    pGeo->setIndex   (pindex, Geometry::PositionsIndex);
    pGeo->setProperty(pnts,   Geometry::PositionsIndex);

    if(norms != NULL)
    {
        if(bSingleIdx == true)
        {
            pGeo->setIndex(pindex, Geometry::NormalsIndex);
        }
        else
        {
            pGeo->setIndex(nindex, Geometry::NormalsIndex);
        }

        pGeo->setProperty(norms, Geometry::NormalsIndex);
    }

    if(tex != NULL)
    {
        if(bSingleIdx == true)
        {
            pGeo->setIndex(pindex, Geometry::TexCoordsIndex);
        }
        else
        {
            pGeo->setIndex(tindex, Geometry::TexCoordsIndex);
        }

        pGeo->setProperty(tex, Geometry::TexCoordsIndex);
    }

    pGeo->setTypes  (types);
    pGeo->setLengths(lens );

    ChunkMaterialUnrecPtr pChunkMat = ChunkMaterial::create();

    if(vFaceGroup[0]->getTextureWhite() &&
       vFaceGroup[0]->getTexIdx      () != -1)
    {
        MaterialChunkUnrecPtr pMatChunk = MaterialChunk::create();
        Color4f               colDiffuse(1.f, 1.f, 1.f, 1.f);

        pMatChunk->setDiffuse(colDiffuse);

        pChunkMat->addChunk(pMatChunk);
    }
    else if(vFaceGroup[0]->getMatIdx() != -1)
    {
        const OFMaterialPaletteRecord *pMatRec   =
            _oDB.getMatRecord(vFaceGroup[0]->getMatIdx());

        if(pMatRec != NULL)
        {
            MaterialChunkUnrecPtr      pMatChunk = MaterialChunk::create();

            if((vFaceGroup[0]->getFlags() & FlagNoColor) != 0)
            {
                // use material only
                Color4f colMat;

                pMatChunk->setAmbient(pMatRec->getAmbient());

                colMat    = pMatRec->getDiffuse();
                colMat[3] = pMatRec->getAlpha() * (1.f - (vFaceGroup[0]->getTransparency() / 65535.f));
                pMatChunk->setDiffuse(colMat);

                pMatChunk->setSpecular (pMatRec->getSpecular ());
                pMatChunk->setShininess(pMatRec->getShininess());
                pMatChunk->setEmission (pMatRec->getEmissive ());

                pChunkMat->addChunk(pMatChunk);
            }
            else
            {
                // use uiPackedPrimCol/uiPrimColIdx and material
                Color4f colGeo;
                Color4f colMat;

                colGeo    = vFaceGroup[0]->getPrimColor();

                colMat    = pMatRec->getAmbient();
                colMat[0] = colMat[0] * colGeo[0];
                colMat[1] = colMat[1] * colGeo[1];
                colMat[2] = colMat[2] * colGeo[2];

                pMatChunk->setAmbient(colMat);

                colMat    = pMatRec->getDiffuse();
                colMat[0] = colMat[0] * colGeo[0];
                colMat[1] = colMat[1] * colGeo[1];
                colMat[2] = colMat[2] * colGeo[2];
                colMat[3] = pMatRec->getAlpha() * (1.f - (vFaceGroup[0]->getTransparency() / 65535.f));

                OSG_OPENFLIGHT_LOG(("OFObjectRecord::convertFaceGroup: "
                                    "PC pMatRec->getAlpha() [%f] "
                                    "Transparency [%f] colMat[3] [%f]\n",
                                    pMatRec->getAlpha(),
                                    vFaceGroup[0]->getTransparency(),
                                    colMat[3]));

                pMatChunk->setDiffuse  (colMat                 );
                pMatChunk->setSpecular (pMatRec->getSpecular ());
                pMatChunk->setShininess(pMatRec->getShininess());
                pMatChunk->setEmission (pMatRec->getEmissive ());

                pChunkMat->addChunk(pMatChunk);
            }

            if(pMatChunk->isTransparent() &&
               pChunkMat->find(BlendChunk::getClassType()) == NULL)
            {
                BlendChunkUnrecPtr pBlendChunk = BlendChunk::create();

                pBlendChunk->setSrcFactor (GL_SRC_ALPHA          );
                pBlendChunk->setDestFactor(GL_ONE_MINUS_SRC_ALPHA);

                pChunkMat->addChunk(pBlendChunk);
            }
        }
        else
        {
            FWARNING(("OFObjectRecord::convertFaceGroup: "
                      "No material record for index [%u].\n",
                      vFaceGroup[0]->getMatIdx()));
        }
    }

    if(vFaceGroup[0]->getTexIdx() != -1)
    {
        const OFTexturePaletteRecord *pTexRec =
            _oDB.getTexRecord(vFaceGroup[0]->getTexIdx());

        if(pTexRec != NULL)
        {
            TextureObjChunk *pTexObj = pTexRec->getTexObj();
            TextureEnvChunk *pTexEnv = pTexRec->getTexEnv();

            if(pTexObj != NULL)
            {
                pChunkMat->addChunk(pTexObj);

                if(pTexObj->getImage()->hasAlphaChannel() &&
                   pChunkMat->find(BlendChunk::getClassType()) == NULL)
                {
                    BlendChunkUnrecPtr pBlendChunk = BlendChunk::create();

                    pBlendChunk->setSrcFactor (GL_SRC_ALPHA          );
                    pBlendChunk->setDestFactor(GL_ONE_MINUS_SRC_ALPHA);

                    pChunkMat->addChunk(pBlendChunk);
                }
            }

            if(pTexEnv != NULL)
            {
                pChunkMat->addChunk(pTexEnv);
            }
            else
            {
                TextureEnvChunkUnrecPtr pTexEnv = TextureEnvChunk::create();

                pTexEnv->setEnvMode(GL_MODULATE);

                pChunkMat->addChunk(pTexEnv);
            }
        }
        else
        {
            FFATAL(("OFObjectRecord::convertFaceGroup: "
                    "No texture record for index [%d].\n", vFaceGroup[0]->getTexIdx()));
        }
    }

    if(vFaceGroup[0]->getLightMode() == LMMeshColor ||
       vFaceGroup[0]->getLightMode() == LMMeshColorLit )
    {
        MaterialChunk *pMatChunk = dynamic_cast<MaterialChunk *>(
            pChunkMat->find(MaterialChunk::getClassType()));

        if(pMatChunk != NULL)
        {
            pMatChunk->setColorMaterial(GL_NONE);

            if(vFaceGroup[0]->getLightMode() == LMMeshColor)
                pMatChunk->setLit(false);
        }
    }

    if(vFaceGroup[0]->getLightMode() == LMMeshColorLit ||
       vFaceGroup[0]->getLightMode() == LMVertexColorLit )
    {
        if(pGeo->getProperty(Geometry::NormalsIndex) == NULL)
            calcVertexNormals(pGeo);
    }

    switch(vFaceGroup[0]->getDrawType())
    {
        case DTSolidCullBack:
        {
            PolygonChunkUnrecPtr pPolyChunk = PolygonChunk::create();
            pPolyChunk->setCullFace(GL_BACK);

            pChunkMat->addChunk(pPolyChunk);
            break;
        }

        case DTSolid:
        {
        // nothing to do
            break;
        }

        case DTWireframeClosed:
        case DTWireframe:
        {
            PolygonChunkUnrecPtr pPolyChunk = PolygonChunk::create();
            pPolyChunk->setFrontMode(GL_LINE);
            pPolyChunk->setBackMode (GL_LINE);

            pChunkMat->addChunk(pPolyChunk);
            break;
        }

        default:
        {
            FWARNING(("OFMeshRecord::convertToNode: Unhandled draw "
                      "type [%d].\n", vFaceGroup[0]->getDrawType()));
            break;
        }
    }

    pGeo->setMaterial(pChunkMat);

    return returnValue;
}

NodeTransitPtr OFObjectRecord::convertGeometry(void)
{
    NodeTransitPtr returnValue(NULL);

    std::vector< std::vector<OFFaceRecord *> > vFaceGroups;

    groupFaces(vFaceGroups);

    if(vFaceGroups.size() == 1 && _vMeshes.size() == 0)
    {
        returnValue = convertFaceGroup(vFaceGroups[0]);
    }
    else if(vFaceGroups.size() == 0 && _vMeshes.size() == 1)
    {
        returnValue = _vMeshes[0]->convertToNode();
    }
    else if(vFaceGroups.size() > 0 || _vMeshes.size() > 0)
    {
        returnValue = Node::create();
        returnValue->setCore(Group::create());

        for(UInt32 i = 0; i < vFaceGroups.size(); ++i)
        {
            returnValue->addChild(convertFaceGroup(vFaceGroups[i]));
        }

        for(UInt32 i = 0; i < _vMeshes.size(); ++i)
        {
            returnValue->addChild(_vMeshes[i]->convertToNode());
        }
    }

    return returnValue;
}

NodeTransitPtr OFObjectRecord::convertAncillaryChildren(Node *pNode)
{
    NodeUnrecPtr returnValue(pNode);

    for(UInt32 i = 0; i < _ancillaryChildren.size(); ++i)
    {
        returnValue = _ancillaryChildren[i]->convert(returnValue);
    }

    return NodeTransitPtr(returnValue);
}

OFRecordFactoryBase::RegisterRecord OFObjectRecord::_regHelper(
    &OFObjectRecord::create,
    OFObjectRecord::OpCode);

//---------------------------------------------------------------------
// OFLocalVertexPoolRecord
//---------------------------------------------------------------------

OFLocalVertexPoolRecord::OFLocalVertexPoolRecord(
    const OFRecordHeader &oHeader, OFDatabase &oDB) :

    Inherited    (oHeader, 
                  oDB    ),
     uiNumVerts  (0      ),
     uiAttribMask(0      ),
    _pPositions  (NULL   ),
    _pColors     (NULL   ),
    _pNormals    (NULL   ),
    _texCoords   (       ),
    _vTriStrips  (       ),
    _vTriFans    (       ),
    _vQuadStrips (       ),
    _vPolygons   (       )
{
    for(UInt32 i = 0; i < 8; ++i)
        _texCoords[i] = NULL;
}

OFLocalVertexPoolRecord::~OFLocalVertexPoolRecord(void)
{
}

OFRecordTransitPtr OFLocalVertexPoolRecord::create(
    const OFRecordHeader &oHeader, OFDatabase &oDB)
{
    return OFRecordTransitPtr(new OFLocalVertexPoolRecord(oHeader, oDB));
}

bool OFLocalVertexPoolRecord::read(std::istream &is)
{
    OSG_OPENFLIGHT_LOG(("OFLocalVertexPoolRecord::read len [%u]\n",
                        _sLength));

    Inherited::readVal(is, uiNumVerts  );
    Inherited::readVal(is, uiAttribMask);

    return readContinue(is, _sLength - 12);
}

bool OFLocalVertexPoolRecord::readContinue(
    std::istream &is, UInt16 uiLength)
{
    OSG_OPENFLIGHT_LOG(("OFLocalVertexPoolRecord::readContinue len [%u] "
                        "cont len [%u]\n", _sLength, uiLength));

    if((uiAttribMask & AMHasColorIndex) != 0)
    {
        FWARNING(("OFLocalVertexPoolRecord::readContinue: "
                  "Color Index mode not supported.\n"));
    }

    // make sure the needed properties exist
    if((uiAttribMask & AMHasPosition) != 0 && _pPositions == NULL)
        _pPositions = GeoPnt3dProperty::create();

    if((uiAttribMask & AMHasColorValue) != 0 && _pColors == NULL)
        _pColors = GeoColor4ubProperty::create();

    if((uiAttribMask & AMHasNormal) != 0 && _pNormals == NULL)
        _pNormals = GeoVec3fProperty::create();

    for(UInt32 i = 0; i < 8; ++i)
    {
        if((uiAttribMask & AMHasTexCoords[i]) != 0 && _texCoords[i] == NULL)
            _texCoords[i] = GeoVec2fProperty::create();
    }

    // read data
    for(Int32 bytesLeft = uiLength; bytesLeft > 0;)
    {
        if((uiAttribMask & AMHasPosition) != 0)
        {
            Pnt3d tmpPnt;
            Inherited::readVal(is, tmpPnt[0]);
            Inherited::readVal(is, tmpPnt[1]);
            Inherited::readVal(is, tmpPnt[2]);

            _pPositions->push_back(tmpPnt);

            bytesLeft -= 3 * 8;
        }

        if((uiAttribMask & AMHasColorIndex) != 0)
        {
            UInt32 tmpVal;
            Inherited::readVal(is, tmpVal);

            // TODO fetch the actual color from the palette

            bytesLeft -= 4;
        }

        if((uiAttribMask & AMHasColorValue) != 0)
        {
            Color4ub tmpVal;
            Inherited::readVal(is, tmpVal[3]);
            Inherited::readVal(is, tmpVal[0]);
            Inherited::readVal(is, tmpVal[1]);
            Inherited::readVal(is, tmpVal[2]);

            _pColors->push_back(tmpVal);

            bytesLeft -= 4;
        }

        if((uiAttribMask & AMHasNormal) != 0)
        {
            Vec3f tmpVec;
            Inherited::readVal(is, tmpVec[0]);
            Inherited::readVal(is, tmpVec[1]);
            Inherited::readVal(is, tmpVec[2]);

            tmpVec.normalize();

            _pNormals->push_back(tmpVec);

            bytesLeft -= 3 * 4;
        }

        for(UInt32 i = 0; i < 8; ++i)
        {
            if((uiAttribMask & AMHasTexCoords[i]) != 0)
            {
                Vec2f tmpVal;
                Inherited::readVal(is, tmpVal[0]);
                Inherited::readVal(is, tmpVal[1]);

                _texCoords[i]->push_back(tmpVal);

                bytesLeft -= 2 * 4;
            }
        }
    }

    return is.good();
}

bool OFLocalVertexPoolRecord::addChild(OFRecord *pChild)
{
    if(pChild == NULL)
        return false;

    bool rc = false;

    switch(pChild->getOpCode())
    {
    case OFMeshPrimitiveRecord::OpCode:
    {
        OFMeshPrimitiveRecord *pPrim =
            dynamic_cast<OFMeshPrimitiveRecord *>(pChild);

        rc = true;

        switch(pPrim->uiPrimType)
        {
        case OFMeshPrimitiveRecord::PTTriStrip:
        {
            _vTriStrips.push_back(pPrim);
            break;
        }

        case OFMeshPrimitiveRecord::PTTriFan:
        {
            _vTriFans.push_back(pPrim);
            break;
        }

        case OFMeshPrimitiveRecord::PTQuadStrip:
        {
            _vQuadStrips.push_back(pPrim);
            break;
        }

        case OFMeshPrimitiveRecord::PTPolygon:
        {
            _vPolygons.push_back(pPrim);
            break;
        }

        default:
        {
            FWARNING(("OFMeshRecord::addChild: Unexpected primitive type [%u] "
                      "for MeshPrimitiveRecord.\n", pPrim->uiPrimType));
            rc =  Inherited::addChild(pChild);
            break;
        }
        }
        break;
    }

    default:
    {
        FWARNING(("OFMeshRecord::addChild: Unexpected child type [%u - %s].\n",
                  pChild->getOpCode(), getOpCodeString(pChild->getOpCode())));
        rc = Inherited::addChild(pChild);
        break;
    }
    }

    return rc;
}

UInt16 OFLocalVertexPoolRecord::getOpCode(void) const
{
    return OpCode;
}

void OFLocalVertexPoolRecord::dump(UInt32 uiIndent) const
{
    indentLog(uiIndent, PLOG);
    PLOG << "LocalVertexPoolRecord : " << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "{" << std::endl;

    uiIndent += 2;

    indentLog(uiIndent, PLOG);
    PLOG << "NumVerts : " << uiNumVerts << std::endl;

    PLOG.setf (std::ios::hex, std::ios::basefield);

    indentLog(uiIndent, PLOG);
    PLOG << "FullAttribMask : " << uiAttribMask << std::endl;

    PLOG.setf (std::ios::dec, std::ios::basefield);

    indentLog(uiIndent, PLOG);
    PLOG << "AttribMask P:" << ((uiAttribMask & AMHasPosition    ) >> 31)
         <<          " Ci:" << ((uiAttribMask & AMHasColorIndex  ) >> 30)
         <<          " Cv:" << ((uiAttribMask & AMHasColorValue  ) >> 29)
         <<           " N:" << ((uiAttribMask & AMHasNormal      ) >> 28)
         <<         " UV0:" << ((uiAttribMask & AMHasTexCoords[0]) >> 27)
         <<         " UV1:" << ((uiAttribMask & AMHasTexCoords[1]) >> 26)
         <<         " UV2:" << ((uiAttribMask & AMHasTexCoords[2]) >> 25)
         <<         " UV3:" << ((uiAttribMask & AMHasTexCoords[3]) >> 24)
         <<         " UV4:" << ((uiAttribMask & AMHasTexCoords[4]) >> 23)
         <<         " UV5:" << ((uiAttribMask & AMHasTexCoords[5]) >> 22)
         <<         " UV6:" << ((uiAttribMask & AMHasTexCoords[6]) >> 21)
         <<         " UV7:" << ((uiAttribMask & AMHasTexCoords[7]) >> 20)
         << std::endl;

    uiIndent -= 2;

    indentLog(uiIndent, PLOG);
    PLOG << "}" << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "[" << std::endl;

    uiIndent += 2;

    for(UInt32 i = 0; i < _vTriStrips.size(); ++i)
        _vTriStrips[i]->dump(uiIndent);

    for(UInt32 i = 0; i < _vTriFans.size(); ++i)
        _vTriFans[i]->dump(uiIndent);

    for(UInt32 i = 0; i < _vQuadStrips.size(); ++i)
        _vQuadStrips[i]->dump(uiIndent);

    for(UInt32 i = 0; i < _vPolygons.size(); ++i)
        _vPolygons[i]->dump(uiIndent);

    uiIndent -= 2;

    indentLog(uiIndent, PLOG);
    PLOG << "]" << std::endl;
}

void OFLocalVertexPoolRecord::convertPrimitives(Geometry *pGeo)
{
    GeoUInt32PropertyUnrecPtr pInd = GeoUInt32Property::create();

    for(UInt32 i = 0; i < _vTriStrips.size(); ++i)
    {
        pGeo->getTypes  ()->push_back(GL_TRIANGLE_STRIP            );
        pGeo->getLengths()->push_back(_vTriStrips[i]->uiVertexCount);

        for(UInt32 j = 0; j < _vTriStrips[i]->_vIndices.size(); ++j)
        {
            pInd->push_back(_vTriStrips[i]->_vIndices[j]);
        }
    }

    for(UInt32 i = 0; i < _vTriFans.size(); ++i)
    {
        pGeo->getTypes  ()->push_back(GL_TRIANGLE_FAN            );
        pGeo->getLengths()->push_back(_vTriFans[i]->uiVertexCount);

        for(UInt32 j = 0; j < _vTriFans[i]->_vIndices.size(); ++j)
        {
            pInd->push_back(_vTriFans[i]->_vIndices[j]);
        }
    }

    for(UInt32 i = 0; i < _vQuadStrips.size(); ++i)
    {
        pGeo->getTypes  ()->push_back(GL_QUAD_STRIP                 );
        pGeo->getLengths()->push_back(_vQuadStrips[i]->uiVertexCount);

        for(UInt32 j = 0; j < _vQuadStrips[i]->_vIndices.size(); ++j)
        {
            pInd->push_back(_vQuadStrips[i]->_vIndices[j]);
        }
    }

    for(UInt32 i = 0; i < _vPolygons.size(); ++i)
    {
        pGeo->getTypes  ()->push_back(GL_POLYGON                  );
        pGeo->getLengths()->push_back(_vPolygons[i]->uiVertexCount);

        for(UInt32 j = 0; j < _vPolygons[i]->_vIndices.size(); ++j)
        {
            pInd->push_back(_vPolygons[i]->_vIndices[j]);
        }
    }

    if((uiAttribMask & AMHasPosition) != 0)
    {
        pGeo->setProperty(_pPositions, Geometry::PositionsIndex);
        pGeo->setIndex   (pInd,        Geometry::PositionsIndex);
    }

    if((uiAttribMask & AMHasColorIndex) != 0)
    {
        ; // TODO
    }

    if((uiAttribMask & AMHasColorValue) != 0)
    {
        pGeo->setProperty(_pColors, Geometry::ColorsIndex);
        pGeo->setIndex   (pInd,     Geometry::ColorsIndex);
    }

    if((uiAttribMask & AMHasNormal) != 0)
    {
        pGeo->setProperty(_pNormals, Geometry::NormalsIndex);
        pGeo->setIndex   (pInd,      Geometry::NormalsIndex);
    }

    for(UInt32 i = 0; i < 8; ++i)
    {
        if((uiAttribMask & AMHasTexCoords[i]) != 0)
        {
            pGeo->setProperty(_texCoords[i], Geometry::TexCoordsIndex + i);
            pGeo->setIndex   (pInd,          Geometry::TexCoordsIndex + i);
        }
    }
}

GeoPnt3dProperty *OFLocalVertexPoolRecord::getPositions(void) const
{
    return _pPositions;
}

GeoColor4ubProperty *OFLocalVertexPoolRecord::getColors(void) const
{
    return _pColors;
}

GeoVec3fProperty *OFLocalVertexPoolRecord::getNormals(void) const
{
    return _pNormals;
}

GeoVec2fProperty *OFLocalVertexPoolRecord::getTexCoords(UInt32 idx) const
{
    return _texCoords[idx];
}

OFRecordFactoryBase::RegisterRecord OFLocalVertexPoolRecord::_regHelper(
    &OFLocalVertexPoolRecord::create,
    OFLocalVertexPoolRecord::OpCode  );

const UInt32 OFLocalVertexPoolRecord::AMHasPosition     = 0x80000000;
const UInt32 OFLocalVertexPoolRecord::AMHasColorIndex   = 0x40000000;
const UInt32 OFLocalVertexPoolRecord::AMHasColorValue   = 0x20000000;
const UInt32 OFLocalVertexPoolRecord::AMHasNormal       = 0x10000000;
const UInt32 OFLocalVertexPoolRecord::AMHasTexCoords[8] =
{
    0x08000000,
    0x04000000,
    0x02000000,
    0x01000000,
    0x00800000,
    0x00400000,
    0x00200000,
    0x00100000
};

//---------------------------------------------------------------------
// OFMeshPrimitiveRecord
//---------------------------------------------------------------------

OFMeshPrimitiveRecord::OFMeshPrimitiveRecord(const OFRecordHeader &oHeader,
                                                   OFDatabase     &oDB     ) :
    Inherited    (oHeader, oDB),
    uiPrimType   (),
    uiIndexSize  (),
    uiVertexCount(),
    _vIndices    ()
{
}

OFMeshPrimitiveRecord::~OFMeshPrimitiveRecord(void)
{
}

OFRecordTransitPtr OFMeshPrimitiveRecord::create(
    const OFRecordHeader &oHeader, OFDatabase &oDB)
{
    return OFRecordTransitPtr(new OFMeshPrimitiveRecord(oHeader, oDB));
}

bool OFMeshPrimitiveRecord::read(std::istream &is)
{
    OSG_OPENFLIGHT_LOG(("OFMeshPrimitiveRecord::read len [%u]\n",
                        _sLength));

    Inherited::readVal(is, uiPrimType   );
    Inherited::readVal(is, uiIndexSize  );
    Inherited::readVal(is, uiVertexCount);

    return readContinue(is, _sLength - 12);
}

bool OFMeshPrimitiveRecord::readContinue(
    std::istream &is, UInt16 uiLength)
{
    switch(uiIndexSize)
    {
    case 1:
    {
        for(Int32 bytesLeft = uiLength; bytesLeft > 0; bytesLeft -= 1)
        {
            UInt8 tmpIdx;
            Inherited::readVal(is, tmpIdx);

            _vIndices.push_back(tmpIdx);
        }
        break;
    }

    case 2:
    {
        for(Int32 bytesLeft = uiLength; bytesLeft > 0; bytesLeft -= 2)
        {
            UInt16 tmpIdx;
            Inherited::readVal(is, tmpIdx);

            _vIndices.push_back(tmpIdx);
        }
        break;
    }

    case 4:
    {
        for(Int32 bytesLeft = uiLength; bytesLeft > 0; bytesLeft -= 4)
        {
            UInt32 tmpIdx;
            Inherited::readVal(is, tmpIdx);

            _vIndices.push_back(tmpIdx);
        }
        break;
    }

    default:
    {
        FWARNING(("OFMeshPrimitiveRecord::readContinue: IndexSize has "
                  "unrecognized value [%u].\n", uiIndexSize));

        return Inherited::readContinue(is, uiLength);
    }
    }

    return is.good();
}

UInt16 OFMeshPrimitiveRecord::getOpCode(void) const
{
    return OpCode;
}

void OFMeshPrimitiveRecord::dump(UInt32 uiIndent) const
{
    indentLog(uiIndent, PLOG);
    PLOG << "MeshPrimitiveRecord : " << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "{" << std::endl;

    uiIndent += 2;

    indentLog(uiIndent, PLOG);
    PLOG << "PrimType : " << uiPrimType << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "IndexSize : " << uiIndexSize << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "VertexCount : " << uiVertexCount << std::endl;

    uiIndent -= 2;

    indentLog(uiIndent, PLOG);
    PLOG << "}" << std::endl;
}

OFMeshPrimitiveRecord::IndexStore &OFMeshPrimitiveRecord::editIndices(void)
{
    return _vIndices;
}

const OFMeshPrimitiveRecord::IndexStore &OFMeshPrimitiveRecord::getIndices(
    void) const
{
    return _vIndices;
}

OFRecordFactoryBase::RegisterRecord OFMeshPrimitiveRecord::_regHelper(
    &OFMeshPrimitiveRecord::create,
    OFMeshPrimitiveRecord::OpCode  );

//---------------------------------------------------------------------
// OFMeshRecord
//---------------------------------------------------------------------

OFMeshRecord::OFMeshRecord(const OFRecordHeader &oHeader,
                                 OFDatabase     &oDB     ) :
     Inherited        (oHeader, 
                       oDB    ),
     iPad1            (0      ),
     iIRColorCode     (0      ),
     iRelPrio         (0      ),
     iDrawType        (0      ),
     iTextureWhite    (0      ),
     uiColorNameIdx   (0      ),
     uiAltColorNameIdx(0      ),
     iPad2            (0      ),
     iTemplate        (0      ),
     iDetailTexIdx    (0      ),
     iTexIdx          (0      ),
     iMatIdx          (0      ),
     iSurfMatCode     (0      ),
     iFeatureId       (0      ),
     iIRMatCode       (0      ),
     uiTransparency   (0      ),
     uiLODGenControl  (0      ),
     uiLineStyle      (0      ),
     iFlags           (0      ),
     uiLightMode      (0      ),
     uiPackedPrimCol  (0      ),
     uiPackedAltCol   (0      ),
     iTexMapIdx       (0      ),
     iPad4            (0      ),
     uiPrimColIdx     (0      ),
     uiAltColIdx      (0      ),
     iPad5            (0      ),
     iShaderIdx       (0      ),
    _pVertexPool      (NULL   )
{
}

OFMeshRecord::~OFMeshRecord(void)
{
}

OFRecordTransitPtr OFMeshRecord::create(const OFRecordHeader &oHeader,
                                              OFDatabase     &oDB     )
{
    return OFRecordTransitPtr(new OFMeshRecord(oHeader, oDB));
}

bool OFMeshRecord::read(std::istream &is)
{
    OSG_OPENFLIGHT_LOG(("OFMeshRecord::read len [%u]\n",
                        _sLength));

    Inherited::readChar8(is, szASCIIId, 8     );
    Inherited::readVal  (is, iPad1            );
    Inherited::readVal  (is, iIRColorCode     );
    Inherited::readVal  (is, iRelPrio         );
    Inherited::readVal  (is, iDrawType        );
    Inherited::readVal  (is, iTextureWhite    );
    Inherited::readVal  (is, uiColorNameIdx   );
    Inherited::readVal  (is, uiAltColorNameIdx);
    Inherited::readVal  (is, iPad2            );
    Inherited::readVal  (is, iTemplate        );
    Inherited::readVal  (is, iDetailTexIdx    );
    Inherited::readVal  (is, iTexIdx          );
    Inherited::readVal  (is, iMatIdx          );
    Inherited::readVal  (is, iSurfMatCode     );
    Inherited::readVal  (is, iFeatureId       );
    Inherited::readVal  (is, iIRMatCode       );
    Inherited::readVal  (is, uiTransparency   );
    Inherited::readVal  (is, uiLODGenControl  );
    Inherited::readVal  (is, uiLineStyle      );
    Inherited::readVal  (is, iFlags           );
    Inherited::readVal  (is, uiLightMode      );
    Inherited::readChar8(is, szPad3, 7        );
    Inherited::readVal  (is, uiPackedPrimCol  );
    Inherited::readVal  (is, uiPackedAltCol   );
    Inherited::readVal  (is, iTexMapIdx       );
    Inherited::readVal  (is, iPad4            );
    Inherited::readVal  (is, uiPrimColIdx     );
    Inherited::readVal  (is, uiAltColIdx      );
    Inherited::readVal  (is, iPad5            );
    Inherited::readVal  (is, iShaderIdx       );

    return is.good();
}

bool OFMeshRecord::addChild(OFRecord *pChild)
{
    if(pChild == NULL)
        return false;

    bool rc = false;

    switch(pChild->getOpCode())
    {
    case OFLocalVertexPoolRecord::OpCode:
    {
        if(_pVertexPool != NULL)
            FWARNING(("OFMeshRecord::addChild: VertexPool already set.\n"));

        _pVertexPool = dynamic_cast<OFLocalVertexPoolRecord *>(pChild);
        rc           = true;
        break;
    }

    default:
    {
        FWARNING(("OFMeshRecord::addChild: Unexpected child type [%u - %s].\n",
                  pChild->getOpCode(), getOpCodeString(pChild->getOpCode())));
        rc = Inherited::addChild(pChild);
        break;
    }
    }

    return rc;
}

UInt16 OFMeshRecord::getOpCode(void) const
{
    return OpCode;
}

void OFMeshRecord::dump(UInt32 uiIndent) const
{
    indentLog(uiIndent, PLOG);
    PLOG << "MeshRecord : " << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "{" << std::endl;

    uiIndent += 2;

    indentLog(uiIndent, PLOG);
    PLOG << "ASCIIId : " << szASCIIId << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "TextureWhite : " << static_cast<UInt32>(iTextureWhite) << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "Template : " << static_cast<UInt32>(iTemplate) << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "Transparency : " << uiTransparency << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "DetailTexIdx : " << iDetailTexIdx << std::endl;
    indentLog(uiIndent, PLOG);
    PLOG << "TexIdx       : " << iTexIdx << std::endl;
    indentLog(uiIndent, PLOG);
    PLOG << "TexMapIdx    : " << iTexMapIdx << std::endl;
    indentLog(uiIndent, PLOG);
    PLOG << "MatIdx       : " << iMatIdx << std::endl;

    PLOG.setf (std::ios::hex, std::ios::basefield);

    indentLog(uiIndent, PLOG);
    PLOG << "FullFlags : " << iFlags << std::endl;

    PLOG.setf (std::ios::dec, std::ios::basefield);

    indentLog(uiIndent, PLOG);
    PLOG << "Flags : "
            << "(T : "   << ((iFlags & 0x80000000) >> 31) << ") "
            << "(NC : "  << ((iFlags & 0x40000000) >> 30) << ") "
            << "(NAC : " << ((iFlags & 0x20000000) >> 29) << ") "
            << "(PC  : " << ((iFlags & 0x10000000) >> 28) << ") "
            << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "LightMode    : " << UInt32(uiLightMode) << std::endl;

    if(uiLightMode == 0 || uiLightMode == 2)
    {
        PLOG.setf (std::ios::hex, std::ios::basefield);

        indentLog(uiIndent, PLOG);
        PLOG << "ColorPacked : " << uiPackedPrimCol << std::endl;

        indentLog(uiIndent, PLOG);
        PLOG << "Color    : B : "
                << (uiPackedPrimCol & 0x000000FF)
                << " G : "
                << ((uiPackedPrimCol & 0x0000FF00) >> 8)
                << " R : "
                << ((uiPackedPrimCol & 0x00FF0000) >> 16)
                << std::endl;

        PLOG.setf (std::ios::dec, std::ios::basefield);

        indentLog(uiIndent, PLOG);
        PLOG << "ColorIdx    : " << uiPrimColIdx << std::endl;
    }

    uiIndent -= 2;

    indentLog(uiIndent, PLOG);
    PLOG << "}" << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "[" << std::endl;

    uiIndent += 2;

    if(_pVertexPool != NULL)
        _pVertexPool->dump(uiIndent);

    uiIndent -= 2;

    indentLog(uiIndent, PLOG);
    PLOG << "]" << std::endl;
}

NodeTransitPtr OFMeshRecord::convertToNode(void)
{
    NodeUnrecPtr returnValue(NULL);

    if(_pVertexPool == NULL)
        return NodeTransitPtr(returnValue);

                              returnValue = Node             ::create();
    GeometryUnrecPtr          pGeo        = Geometry         ::create();
    GeoUInt8PropertyUnrecPtr  pTypes      = GeoUInt8Property ::create();
    GeoUInt32PropertyUnrecPtr pLengths    = GeoUInt32Property::create();

    pGeo->setTypes  (pTypes  );
    pGeo->setLengths(pLengths);

    returnValue->setCore(pGeo);

    _pVertexPool->convertPrimitives(pGeo);

    ChunkMaterialUnrecPtr pChunkMat = ChunkMaterial::create();

    if(iTextureWhite && iTexIdx != -1)
    {
        MaterialChunkUnrecPtr pMatChunk = MaterialChunk::create();
        Color4f               colDiffuse(1.f, 1.f, 1.f, 1.f);

        pMatChunk->setDiffuse(colDiffuse);

        pChunkMat->addChunk(pMatChunk);
    }
    else if(iMatIdx != -1)
    {
        const OFMaterialPaletteRecord *pMatRec   = _oDB.getMatRecord(iMatIdx);

        if(pMatRec != NULL)
        {
            MaterialChunkUnrecPtr      pMatChunk = MaterialChunk::create();

            if((iFlags & FlagNoColor) != 0)
            {
                // use material only
                Color4f colMat;

                pMatChunk->setAmbient(pMatRec->getAmbient());

                colMat    = pMatRec->getDiffuse();
                colMat[3] = pMatRec->getAlpha() * (1.f - (uiTransparency / 65535.f));
                pMatChunk->setDiffuse(colMat);

                pMatChunk->setSpecular (pMatRec->getSpecular ());
                pMatChunk->setShininess(pMatRec->getShininess());
                pMatChunk->setEmission (pMatRec->getEmissive ());

                pChunkMat->addChunk(pMatChunk);
            }
            else if((iFlags & FlagPackedColor) != 0)
            {
                // use uiPackedPrimCol and material
                Color4f colGeo;
                Color4f colMat;

                colGeo[0] = ((uiPackedPrimCol & 0x00FF0000) >> 16) / 255.f;
                colGeo[1] = ((uiPackedPrimCol & 0x0000FF00) >>  8) / 255.f;
                colGeo[2] = ((uiPackedPrimCol & 0x000000FF)      ) / 255.f;
                colGeo[3] = 1.f;

                colMat    = pMatRec->getAmbient();
                colMat[0] = colMat[0] * colGeo[0];
                colMat[1] = colMat[1] * colGeo[1];
                colMat[2] = colMat[2] * colGeo[2];

                pMatChunk->setAmbient(colMat);

                colMat    = pMatRec->getDiffuse();
                colMat[0] = colMat[0] * colGeo[0];
                colMat[1] = colMat[1] * colGeo[1];
                colMat[2] = colMat[2] * colGeo[2];
                colMat[3] = pMatRec->getAlpha() * (1.f - (uiTransparency / 65535.f));

                pMatChunk->setDiffuse  (colMat                 );
                pMatChunk->setSpecular (pMatRec->getSpecular ());
                pMatChunk->setShininess(pMatRec->getShininess());
                pMatChunk->setEmission (pMatRec->getEmissive ());

                pChunkMat->addChunk(pMatChunk);
            }
            else
            {
                // TODO: use uiPrimColIdx
            }

            if(pMatChunk->isTransparent() &&
               pChunkMat->find(BlendChunk::getClassType()) == NULL)
            {
                BlendChunkUnrecPtr pBlendChunk = BlendChunk::create();

                pBlendChunk->setSrcFactor (GL_SRC_ALPHA          );
                pBlendChunk->setDestFactor(GL_ONE_MINUS_SRC_ALPHA);

                pChunkMat->addChunk(pBlendChunk);
            }
        }
    }

    if(iTexIdx != -1)
    {
        const OFTexturePaletteRecord *pTexRec = _oDB.getTexRecord(iTexIdx);

        if(pTexRec != NULL)
        {
            TextureObjChunk *pTexObj = pTexRec->getTexObj();
            TextureEnvChunk *pTexEnv = pTexRec->getTexEnv();

            if(pTexObj != NULL)
            {
                pChunkMat->addChunk(pTexObj);

                if(pTexObj->getImage()->hasAlphaChannel() &&
                   pChunkMat->find(BlendChunk::getClassType()) == NULL)
                {
                    BlendChunkUnrecPtr pBlendChunk = BlendChunk::create();

                    pBlendChunk->setSrcFactor (GL_SRC_ALPHA          );
                    pBlendChunk->setDestFactor(GL_ONE_MINUS_SRC_ALPHA);

                    pChunkMat->addChunk(pBlendChunk);
                }
            }

            if(pTexEnv != NULL)
            {
                pChunkMat->addChunk(pTexEnv);
            }
            else
            {
                TextureEnvChunkUnrecPtr pTexEnv = TextureEnvChunk::create();

                pTexEnv->setEnvMode(GL_MODULATE);

                pChunkMat->addChunk(pTexEnv);
            }
        }
        else
        {
            FFATAL(("OFMeshRecord::convertToNode: "
                    "No texture record for index [%d].\n", iTexIdx));
        }
    }

    if(uiLightMode == LMMeshColor || uiLightMode == LMMeshColorLit)
    {
        MaterialChunk *pMatChunk = dynamic_cast<MaterialChunk *>(
            pChunkMat->find(MaterialChunk::getClassType()));

        if(pMatChunk != NULL)
        {
            pMatChunk->setColorMaterial(GL_NONE);

            if(uiLightMode == LMMeshColor)
                pMatChunk->setLit(false);
        }
    }

    if(uiLightMode == LMMeshColorLit || uiLightMode == LMVertexColorLit)
    {
        if(pGeo->getProperty(Geometry::NormalsIndex) == NULL)
            calcVertexNormals(pGeo);
    }

    switch(iDrawType)
    {
    case DTSolidCullBack:
    {
        PolygonChunkUnrecPtr pPolyChunk = PolygonChunk::create();
        pPolyChunk->setCullFace(GL_BACK);

        pChunkMat->addChunk(pPolyChunk);
        break;
    }

    case DTSolid:
    {
        // nothing to do
        break;
    }

    case DTWireframeClosed:
    case DTWireframe:
    {
        PolygonChunkUnrecPtr pPolyChunk = PolygonChunk::create();
        pPolyChunk->setFrontMode(GL_LINE);
        pPolyChunk->setBackMode (GL_LINE);

        pChunkMat->addChunk(pPolyChunk);
        break;
    }

    default:
    {
        FWARNING(("OFMeshRecord::convertToNode: Unhandled draw "
                  "type [%d].\n", iDrawType));
        break;
    }
    }


    pGeo->setMaterial(pChunkMat);

    return NodeTransitPtr(returnValue);
}

OFRecordFactoryBase::RegisterRecord OFMeshRecord::_regHelper(
    &OFMeshRecord::create,
     OFMeshRecord::OpCode  );

//---------------------------------------------------------------------
// OFFaceRecord
//---------------------------------------------------------------------

OFRecordTransitPtr OFFaceRecord::create(const OFRecordHeader &oHeader,
                                              OFDatabase     &oDB     )
{
    return OFRecordTransitPtr(new OFFaceRecord(oHeader, oDB));
}

OFFaceRecord::OFFaceRecord(const OFRecordHeader &oHeader,
                                 OFDatabase     &oDB     ) :
     Inherited        (oHeader, 
                       oDB    ),
     iIRColorCode     (0      ),
     iRelPrio         (0      ),
     iDrawType        (0      ),
     iTextureWhite    (0      ),
     uiColorNameIdx   (0      ),
     uiAltColorNameIdx(0      ),
     iPad1            (0      ),
     iTemplate        (0      ),
     iDetailTexIdx    (0      ),
     iTexIdx          (0      ),
     iMatIdx          (0      ),
     iSurfMatCode     (0      ),
     iFeatureId       (0      ),
     iIRMatCode       (0      ),
     uiTransparency   (0      ),
     uiLODGenControl  (0      ),
     uiLineStyle      (0      ),
     iFlags           (0      ),
     uiLightMode      (0      ),
     uiPackedPrimCol  (0      ),
     uiPackedAltCol   (0      ),
     iTexMapIdx       (0      ),
     iPad3            (0      ),
     uiPrimColIdx     (0      ),
     uiAltColIdx      (0      ),
     iPad4            (0      ),
     iShaderIdx       (0      ),
    _pVList           (NULL   )
{
}

OFFaceRecord::~OFFaceRecord(void)
{
    _pVList = NULL;
}

bool OFFaceRecord::read(std::istream &is)
{
    OSG_OPENFLIGHT_LOG(("OFFaceRecord::read len [%u]\n",
                        _sLength));

    Inherited::readChar8(is, szASCIIId, 8     );
    Inherited::readVal  (is, iIRColorCode     );
    Inherited::readVal  (is, iRelPrio         );
    Inherited::readVal  (is, iDrawType        );
    Inherited::readVal  (is, iTextureWhite    );
    Inherited::readVal  (is, uiColorNameIdx   );
    Inherited::readVal  (is, uiAltColorNameIdx);
    Inherited::readVal  (is, iPad1            );
    Inherited::readVal  (is, iTemplate        );
    Inherited::readVal  (is, iDetailTexIdx    );
    Inherited::readVal  (is, iTexIdx          );
    Inherited::readVal  (is, iMatIdx          );
    Inherited::readVal  (is, iSurfMatCode     );
    Inherited::readVal  (is, iFeatureId       );
    Inherited::readVal  (is, iIRMatCode       );
    Inherited::readVal  (is, uiTransparency   );
    Inherited::readVal  (is, uiLODGenControl  );
    Inherited::readVal  (is, uiLineStyle      );
    Inherited::readVal  (is, iFlags           );
    Inherited::readVal  (is, uiLightMode      );
    Inherited::readChar8(is, szPad2, 7        );
    Inherited::readVal  (is, uiPackedPrimCol  );
    Inherited::readVal  (is, uiPackedAltCol   );
    Inherited::readVal  (is, iTexMapIdx       );
    Inherited::readVal  (is, iPad3            );
    Inherited::readVal  (is, uiPrimColIdx     );
    Inherited::readVal  (is, uiAltColIdx      );
    Inherited::readVal  (is, iPad4            );
    Inherited::readVal  (is, iShaderIdx       );

    return is.good();
}

bool OFFaceRecord::addChild(OFRecord *pChild)
{
    if(pChild == NULL)
        return false;

    switch(pChild->getOpCode())
    {
        case OFVertexListRecord::OpCode:
        {
            if(_pVList != NULL)
            {
                FWARNING(("OFFaceRecord::addChild: Vertex List already set.\n"));
            }
            else
            {
                _pVList = dynamic_cast<OFVertexListRecord *>(pChild);
            }
        }
        break;

        default:
        {
            Inherited::addChild(pChild);
        }
        break;
    }

    return true;
}

UInt16 OFFaceRecord::getOpCode(void) const
{
    return OpCode;
}

OFVertexListRecord *OFFaceRecord::getVertexList(void)
{
    return _pVList;
}

void OFFaceRecord::dump(UInt32 uiIndent) const
{
    indentLog(uiIndent, PLOG);
    PLOG << "FaceRecord : " << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "{" << std::endl;

    uiIndent += 2;

    indentLog(uiIndent, PLOG);
    PLOG << "TextureWhite : " << UInt32(iTextureWhite) << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "TexIdx       : " << iTexIdx << std::endl;
    indentLog(uiIndent, PLOG);
    PLOG << "TexMapIdx    : " << iTexMapIdx << std::endl;
    indentLog(uiIndent, PLOG);
    PLOG << "MatIdx       : " << iMatIdx << std::endl;
    indentLog(uiIndent, PLOG);
    PLOG << "Transparency : " << uiTransparency << std::endl;

    PLOG.setf (std::ios::hex, std::ios::basefield);

    indentLog(uiIndent, PLOG);
    PLOG << "FullFlags : " << iFlags << std::endl;

    PLOG.setf (std::ios::dec, std::ios::basefield);

    indentLog(uiIndent, PLOG);
    PLOG << "Flags : "
         << "(T : "   << ((iFlags & 0x80000000) >> 31) << ") "
         << "(NC : "  << ((iFlags & 0x40000000) >> 30) << ") "
         << "(NAC : " << ((iFlags & 0x20000000) >> 29) << ") "
         << "(PC  : " << ((iFlags & 0x10000000) >> 28) << ") "
         << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "LightMode    : " << UInt32(uiLightMode) << std::endl;

    if(uiLightMode == 0 || uiLightMode == 2)
    {
        PLOG.setf (std::ios::hex, std::ios::basefield);

        indentLog(uiIndent, PLOG);
        PLOG << "ColorPacked : " << uiPackedPrimCol << std::endl;

        indentLog(uiIndent, PLOG);
        PLOG << "Color    : B : "
             << (uiPackedPrimCol & 0x000000FF)
             << " G : "
             << ((uiPackedPrimCol & 0x0000FF00) >> 8)
             << " R : "
             << ((uiPackedPrimCol & 0x00FF0000) >> 16)
             << std::endl;

        PLOG.setf (std::ios::dec, std::ios::basefield);

        indentLog(uiIndent, PLOG);
        PLOG << "ColorIdx    : " << uiPrimColIdx << std::endl;
    }

    uiIndent -= 2;

    indentLog(uiIndent, PLOG);
    PLOG << "}" << std::endl;
}

bool OFFaceRecord::operator ==(const OFFaceRecord &rhs) const
{
    bool returnValue = (iDrawType     == rhs.iDrawType     &&
                        iTextureWhite == rhs.iTextureWhite &&
                        iTexIdx       == rhs.iTexIdx       &&
                        iMatIdx       == rhs.iMatIdx       &&
                        uiLightMode   == rhs.uiLightMode     );

    if(uiLightMode == 0 || uiLightMode == 2)
    {
        if((iFlags & FlagPackedColor) != 0)
        {
            returnValue &= (uiPackedPrimCol == rhs.uiPackedPrimCol);
        }
        else
        {
            returnValue &= (uiPrimColIdx == rhs.uiPrimColIdx);
        }
    }

    return returnValue;
}

Int8 OFFaceRecord::getDrawType(void) const
{
    return iDrawType;
}

Int8 OFFaceRecord::getTextureWhite(void) const
{
    return iTextureWhite;
}

Int16 OFFaceRecord::getTexIdx(void) const
{
    return iTexIdx;
}

Int16 OFFaceRecord::getMatIdx(void) const
{
    return iMatIdx;
}

UInt16 OFFaceRecord::getTransparency(void) const
{
    return uiTransparency;
}

Int32 OFFaceRecord::getFlags(void) const
{
    return iFlags;
}

UInt8 OFFaceRecord::getLightMode(void) const
{
    return uiLightMode;
}

Color4f OFFaceRecord::getPrimColor(void) const
{
    Color4f returnValue;

    if((iFlags & FlagPackedColor) != 0)
    {
        returnValue[0] = ((uiPackedPrimCol & 0x00FF0000) >> 16) / 255.f;
        returnValue[1] = ((uiPackedPrimCol & 0x0000FF00) >>  8) / 255.f;
        returnValue[2] = ((uiPackedPrimCol & 0x000000FF)      ) / 255.f;
        returnValue[3] = 1.f;
    }
    else if((iFlags & FlagNoColor) == 0)
    {
        const OFColorPaletteRecord *colPal = _oDB.getColorPalette();

        returnValue = colPal->getColor(uiPrimColIdx);
    }

    return returnValue;
}

Color4f OFFaceRecord::getAltColor(void) const
{
    Color4f returnValue;

    if((iFlags & FlagPackedColor) != 0)
    {
        returnValue[0] = ((uiPackedAltCol & 0x00FF0000) >> 16) / 255.f;
        returnValue[1] = ((uiPackedAltCol & 0x0000FF00) >>  8) / 255.f;
        returnValue[2] = ((uiPackedAltCol & 0x000000FF)      ) / 255.f;
        returnValue[3] = 1.f;
    }
    else if((iFlags & FlagNoColor) == 0)
    {
        const OFColorPaletteRecord *colPal = _oDB.getColorPalette();

        returnValue = colPal->getColor(uiAltColIdx);
    }

    return returnValue;
}

OFRecordFactoryBase::RegisterRecord OFFaceRecord::_regHelper(
    &OFFaceRecord::create,
    OFFaceRecord::OpCode);

//---------------------------------------------------------------------
// OFVertexListRecord
//---------------------------------------------------------------------


OFRecordTransitPtr OFVertexListRecord::create(const OFRecordHeader &oHeader,
                                                    OFDatabase     &oDB    )
{
    return OFRecordTransitPtr(new OFVertexListRecord(oHeader, oDB));
}

OFVertexListRecord::OFVertexListRecord(const OFRecordHeader &oHeader,
                                             OFDatabase     &oDB     ) :
     Inherited(oHeader, oDB),
    _vIndices (            )
{
}

OFVertexListRecord::~OFVertexListRecord(void)
{
}

bool OFVertexListRecord::read(std::istream &is)
{
    UInt32 uiListSize = (_sLength - 4) / 4;

    OSG_OPENFLIGHT_LOG(("OFVertexListRecord::read len [%u], indices [%u]\n",
                        _sLength, uiListSize));

    _vIndices.resize(uiListSize);

    for(UInt32 i = 0; i < uiListSize; ++i)
    {
        Inherited::readVal(is, _vIndices[i]);
    }

    return is.good();
}

UInt16 OFVertexListRecord::getOpCode(void) const
{
    return OpCode;
}

const std::vector<Int32> &OFVertexListRecord::getIndices(void)
{
    return _vIndices;
}

OFRecordFactoryBase::RegisterRecord OFVertexListRecord::_regHelper(
    &OFVertexListRecord::create,
    OFVertexListRecord::OpCode);

//---------------------------------------------------------------------
// OFLODRecord
//---------------------------------------------------------------------

OFRecordTransitPtr OFLODRecord::create(const OFRecordHeader &oHeader,
                                             OFDatabase     &oDB     )
{
    return OFRecordTransitPtr(new OFLODRecord(oHeader, oDB));
}

OFLODRecord::OFLODRecord(const OFRecordHeader &oHeader,
                               OFDatabase     &oDB     ) :
    Inherited   (oHeader, 
                 oDB    ),
    iPad1       (0      ),
    rSwitchIn   (0      ),
    rSwitchOut  (0      ),
    iSpecialEff1(0      ),
    iSpecialEff2(0      ),
    iFlags      (0      ),
    rCenterX    (0      ),
    rCenterY    (0      ),
    rCenterZ    (0      ),
    rTransRange (0      ),
    rSigSize    (0      )
{
}

OFLODRecord::~OFLODRecord(void)
{
}

bool OFLODRecord::read(std::istream &is)
{
    OSG_OPENFLIGHT_LOG(("OFLODRecord::read len [%u]\n",
                        _sLength));

    Inherited::readChar8(is, szASCIIId, 8);
    Inherited::readVal  (is, iPad1       );
    Inherited::readVal  (is, rSwitchIn   );
    Inherited::readVal  (is, rSwitchOut  );
    Inherited::readVal  (is, iSpecialEff1);
    Inherited::readVal  (is, iSpecialEff2);
    Inherited::readVal  (is, iFlags      );
    Inherited::readVal  (is, rCenterX    );
    Inherited::readVal  (is, rCenterY    );
    Inherited::readVal  (is, rCenterZ    );
    Inherited::readVal  (is, rTransRange );

    if(_sLength >= 80)
        Inherited::readVal(is, rSigSize);

    rSwitchIn  *= _oDB.getUnitScale();
    rSwitchOut *= _oDB.getUnitScale();

    rCenterX   *= _oDB.getUnitScale();
    rCenterY   *= _oDB.getUnitScale();
    rCenterZ   *= _oDB.getUnitScale();

    return is.good();
}

UInt16 OFLODRecord::getOpCode(void) const
{
    return OpCode;
}

void OFLODRecord::dump(UInt32 uiIndent) const
{
    indentLog(uiIndent, PLOG);
    PLOG << "LODRecord" << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "{" << std::endl;

    uiIndent += 2;

    indentLog(uiIndent, PLOG);
    PLOG << "rSwitchIn  : " << rSwitchIn  << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "rSwitchOut : " << rSwitchOut << std::endl;

    uiIndent -= 2;

    indentLog(uiIndent, PLOG);
    PLOG << "}" << std::endl;

    Inherited::dump(uiIndent);
}

NodeTransitPtr OFLODRecord::convertToNode(void)
{
    NodeUnrecPtr returnValue(NULL);

    if(_primaryChildren.empty() == false)
    {
        RangeLODUnrecPtr pCore = RangeLOD::create();
        NodeUnrecPtr     pNode = makeNodeFor(pCore);

        pCore->setSwitchIn (this->getSwitchIn ());
        pCore->setSwitchOut(this->getSwitchOut());

        pCore->setCenter   (this->getCenter   ());

        if(returnValue != NULL)
        {
            returnValue->addChild(pNode);
        }
        else
        {
            returnValue = pNode;
        }

        for(UInt32 i = 0; i < _primaryChildren.size(); ++i)
        {
            NodeTransitPtr pChild = _primaryChildren[i]->convertToNode();

            if(pChild != NULL)
            {
                returnValue->addChild(pChild);
            }
        }
    }

    returnValue = convertAncillaryChildren(returnValue);

    return NodeTransitPtr(returnValue);
}

Real64 OFLODRecord::getSwitchIn (void)
{
    return rSwitchIn;
}

Real64 OFLODRecord::getSwitchOut(void)
{
    return rSwitchOut;
}

Pnt3f  OFLODRecord::getCenter(void)
{
    return Pnt3f(rCenterX, rCenterY, rCenterZ);
}

NodeTransitPtr OFLODRecord::convertAncillaryChildren(Node *pNode)
{
    NodeUnrecPtr returnValue(pNode);

    for(UInt32 i = 0; i < _ancillaryChildren.size(); ++i)
    {
        returnValue = _ancillaryChildren[i]->convert(returnValue);
    }

    return NodeTransitPtr(returnValue);
}

OFRecordFactoryBase::RegisterRecord OFLODRecord::_regHelper(
    &OFLODRecord::create,
    OFLODRecord::OpCode);

//---------------------------------------------------------------------
// OFSwitchRecord
//---------------------------------------------------------------------

OFRecordTransitPtr OFSwitchRecord::create(const OFRecordHeader &oHeader,
                                                OFDatabase     &oDB     )
{
    return OFRecordTransitPtr(new OFSwitchRecord(oHeader, oDB));
}

OFSwitchRecord::OFSwitchRecord(const OFRecordHeader &oHeader,
                                     OFDatabase     &oDB     ) :
    Inherited (oHeader, 
               oDB    ),
    szPad1    (0      ),
    iCurrMask (0      ),
    iNumMask  (0      ),
    iMaskWords(0      ),
    vMask     (0      )
{
}

OFSwitchRecord::~OFSwitchRecord(void)
{
}

bool OFSwitchRecord::read(std::istream &is)
{
    OSG_OPENFLIGHT_LOG(("OFSwitchRecord::read len [%u]\n",
                        _sLength));

    Inherited::readChar8(is, szASCIIID, 8);
    Inherited::readVal  (is, szPad1      );
    Inherited::readVal  (is, iCurrMask   );
    Inherited::readVal  (is, iNumMask    );
    Inherited::readVal  (is, iMaskWords  );

    vMask.resize(iNumMask);

    for(Int32 i = 0; i < iNumMask; ++i)
    {
        vMask[i].resize(iMaskWords);
    }

    for(Int32 i = 0; i < iNumMask; ++i)
    {
        for(Int32 j = 0; j < iMaskWords; ++j)
        {
            Inherited::readVal(is, vMask[i][j]);
        }
    }

    return is.good();
}

UInt16 OFSwitchRecord::getOpCode(void) const
{
    return OpCode;
}


void OFSwitchRecord::dump(UInt32 uiIndent) const
{
    indentLog(uiIndent, PLOG);
    PLOG << "SwitchRecord" << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "{" << std::endl;

    uiIndent += 2;

    indentLog(uiIndent, PLOG);
    PLOG << "iCurrMask  : " << iCurrMask  << std::endl;
    indentLog(uiIndent, PLOG);
    PLOG << "iNumMask   : " << iNumMask   << std::endl;
    indentLog(uiIndent, PLOG);
    PLOG << "iMaskWords : " << iMaskWords << std::endl;

    PLOG.setf (std::ios::hex, std::ios::basefield);

    for(Int32 i = 0; i < iNumMask; ++i)
    {
        indentLog(uiIndent, PLOG);
        PLOG << "Mask[" << i << "] : ";

        for(Int32 j = 0; j < iMaskWords; ++j)
        {
            PLOG << vMask[i][j] << " ";
        }
        PLOG << std::endl;
    }

    PLOG.setf(std::ios::dec, std::ios::basefield);

    uiIndent -= 2;

    indentLog(uiIndent, PLOG);
    PLOG << "}" << std::endl;

    Inherited::dump(uiIndent);
}

NodeTransitPtr OFSwitchRecord::convertToNode(void)
{
    NodeUnrecPtr returnValue(NULL);

    if(_primaryChildren.empty() == false)
    {
        GroupUnrecPtr pCore = Group::create();
        NodeUnrecPtr  pNode = makeNodeFor(pCore);

        if(returnValue != NULL)
        {
            returnValue->addChild(pNode);
        }
        else
        {
            returnValue = pNode;
        }

        for(UInt32 i = 0; i < _primaryChildren.size(); ++i)
        {
            NodeTransitPtr pChild = _primaryChildren[i]->convertToNode();

            if(pChild != NULL)
            {
                returnValue->addChild(pChild);
            }
        }
    }

    returnValue = convertAncillaryChildren(returnValue);

    return NodeTransitPtr(returnValue);
}

NodeTransitPtr OFSwitchRecord::convertAncillaryChildren(Node *pNode)
{
    NodeUnrecPtr returnValue(pNode);

    for(UInt32 i = 0; i < _ancillaryChildren.size(); ++i)
    {
        returnValue = _ancillaryChildren[i]->convert(returnValue);
    }

    return NodeTransitPtr(returnValue);
}

OFRecordFactoryBase::RegisterRecord OFSwitchRecord::_regHelper(
    &OFSwitchRecord::create,
    OFSwitchRecord::OpCode);

//---------------------------------------------------------------------
// OFExternalReferenceRecord
//---------------------------------------------------------------------

OFRecordTransitPtr OFExternalReferenceRecord::create(
    const OFRecordHeader &oHeader, OFDatabase &oDB)
{
    return OFRecordTransitPtr(new OFExternalReferenceRecord(oHeader, oDB));
}

OFExternalReferenceRecord::OFExternalReferenceRecord(
    const OFRecordHeader &oHeader, OFDatabase &oDB) :

    Inherited  (oHeader,
                oDB    ),
    iPad1      (0      ),
    iFlags     (0      ),
    iViewAsBBox(0      ),
    iPad2      (0      )
{
}

OFExternalReferenceRecord::~OFExternalReferenceRecord(void)
{
}

bool OFExternalReferenceRecord::read(std::istream &is)
{
    Inherited::readChar8(is, szFilename, 200);
    Inherited::readVal  (is, iPad1          );
    Inherited::readVal  (is, iFlags         );
    Inherited::readVal  (is, iViewAsBBox    );
    Inherited::readVal  (is, iPad2          );

    OSG_OPENFLIGHT_LOG(("OFExternalReferenceRecord::read len [%u] - file [%s]\n",
                        _sLength, szFilename));

    return is.good();
}

UInt16 OFExternalReferenceRecord::getOpCode(void) const
{
    return OpCode;
}

void OFExternalReferenceRecord::dump(UInt32 uiIndent) const
{
    indentLog(uiIndent, PLOG);
    PLOG << "ExternalReference : " << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "{" << std::endl;

    uiIndent += 2;

    indentLog(uiIndent, PLOG);
    PLOG << "Filename : " << szFilename << std::endl;

    PLOG.setf (std::ios::hex, std::ios::basefield);

    indentLog(uiIndent, PLOG);
    PLOG << "FullFlags : " << iFlags << std::endl;

    PLOG.setf (std::ios::dec, std::ios::basefield);

    indentLog(uiIndent, PLOG);
    PLOG << "Flags : "
         << "(CP : "  << ((iFlags & 0x80000000) >> 31) << ") "
         << "(MP : "  << ((iFlags & 0x40000000) >> 30) << ") "
         << "(TP : "  << ((iFlags & 0x20000000) >> 29) << ") "
         << "(LP : "  << ((iFlags & 0x10000000) >> 28) << ") "
         << "(SP : "  << ((iFlags & 0x08000000) >> 27) << ") "
         << "(LSP : " << ((iFlags & 0x04000000) >> 26) << ") "
         << "(LPP : " << ((iFlags & 0x02000000) >> 25) << ") "
         << "(SHP : " << ((iFlags & 0x01000000) >> 24) << ") "
         << std::endl;

    uiIndent -= 2;

    indentLog(uiIndent, PLOG);
    PLOG << "}" << std::endl;

    Inherited::dump(uiIndent);
}

NodeTransitPtr OFExternalReferenceRecord::convertToNode(void)
{
    NodeUnrecPtr returnValue;

    PathHandler *pHandler = SceneFileHandler::the()->getPathHandler();

    if(pHandler != NULL)
    {
        std::string szFilenameResolved = pHandler->findFile(szFilename);

        if(szFilenameResolved.empty() == true)
        {
            FWARNING(("OFExternalReferenceRecord::convertToNode: Could not "
                      "find file [%s].\n", szFilename));

            return NodeTransitPtr(returnValue);
        }

        OSG_OPENFLIGHT_LOG(("OFExternalReferenceRecord::convertToNode: "
                            "reading file [%s]\n",
                            szFilenameResolved.c_str()));

        pHandler->pushState();

        pHandler->setBaseFile(szFilenameResolved.c_str());

        std::ifstream is;

        is.open(szFilenameResolved.c_str(), std::ios::binary);

        NodeUnrecPtr pExtNode =
            OpenFlightSceneFileType::the().read(is,
                                                szFilenameResolved.c_str());

        if(pExtNode != NULL && returnValue != NULL)
        {
            returnValue->addChild(pExtNode);
        }
        else if(pExtNode != NULL)
        {
            returnValue = pExtNode;
        }

        pHandler->popState();
    }
    else
    {
        FFATAL(("OFExternalReferenceRecord::convertToNode: No PathHandler.\n"));
    }

    returnValue = convertAncillaryChildren(returnValue);

    return NodeTransitPtr(returnValue);
}

NodeTransitPtr OFExternalReferenceRecord::convertAncillaryChildren(Node *pNode)
{
    NodeUnrecPtr returnValue(pNode);

    for(UInt32 i = 0; i < _ancillaryChildren.size(); ++i)
    {
        returnValue = _ancillaryChildren[i]->convert(returnValue);
    }

    return NodeTransitPtr(returnValue);
}

OFRecordFactoryBase::RegisterRecord OFExternalReferenceRecord::_regHelper(
    &OFExternalReferenceRecord::create,
    OFExternalReferenceRecord::OpCode);

OSG_END_NAMESPACE
