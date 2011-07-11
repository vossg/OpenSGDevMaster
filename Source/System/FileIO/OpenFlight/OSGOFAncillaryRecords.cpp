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

#include "OSGOFAncillaryRecords.h"

#include "OSGImageFileHandler.h"
#include "OSGNameAttachment.h"
#include "OSGTransform.h"
#include "OSGOFDatabase.h"
#include "OSGOpenFlightLog.h"

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------
// OFTexturePaletteRecord
//---------------------------------------------------------------------

/* static */
OFRecordTransitPtr OFTexturePaletteRecord::create(const OFRecordHeader &oHeader,
                                                        OFDatabase     &oDB     )
{
    return OFRecordTransitPtr(new OFTexturePaletteRecord(oHeader, oDB));
}

OFTexturePaletteRecord::OFTexturePaletteRecord(const OFRecordHeader &oHeader,
                                                     OFDatabase     &oDB     ) :
    Inherited(oHeader, oDB),
    pTexObj  ()
{
}

OFTexturePaletteRecord::~OFTexturePaletteRecord(void)
{
    pTexObj = NULL;
}

/* virtual */
bool OFTexturePaletteRecord::read(std::istream &is)
{
    OSG_OPENFLIGHT_LOG(("OFTexturePaletteRecord::read len [%u]\n",
                        _sLength));

    Inherited::readChar8(is, szFilename, 200);
    Inherited::readVal  (is, iPatternIdx    );
    Inherited::readVal  (is, iPatternX      );
    Inherited::readVal  (is, iPatternY      );

    ImageUnrecPtr pImage = ImageFileHandler::the()->read(szFilename);

    if(pImage != NULL)
    {
        pTexObj = TextureObjChunk::create();

        pTexObj->setImage(pImage);
    }
    else
    {
        std::string szTmp = szFilename;

        std::string::size_type uiPos = szTmp.rfind('/');

        if(uiPos != std::string::npos)
        {
            pImage = ImageFileHandler::the()->read(
                &(szFilename[uiPos + 1]));

            if(pImage != NULL)
            {
                pTexObj = TextureObjChunk::create();

                pTexObj->setImage(pImage);
            }
            else
            {
                FWARNING(("OFTexturePaletteRecord::read: Could not read image "
                          "[%s].\n", &(szFilename[uiPos + 1])));
            }
        }
        else
        {
            FWARNING(("OFTexturePaletteRecord::read: Could not read image "
                      "[%s].\n", szFilename));
        }
    }

    return is.good();
}

/* virtual */
UInt16 OFTexturePaletteRecord::getOpCode(void) const
{
    return OpCode;
}

void OFTexturePaletteRecord::dump(UInt32 uiIndent)
{
    indentLog(uiIndent, PLOG);
    PLOG << "TexturePaletteRecord" << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "{" << std::endl;

    uiIndent += 2;

    indentLog(uiIndent, PLOG);
    PLOG << "Filename : " << szFilename << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "PatternIdx : " << iPatternIdx << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "PatternX : " << iPatternX << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "PatternY : " << iPatternY << std::endl;

    uiIndent -= 2;

    indentLog(uiIndent, PLOG);
    PLOG << "}" << std::endl;
}

Int32 OFTexturePaletteRecord::getPatternIdx(void)
{
    return iPatternIdx;
}

TextureObjChunk *OFTexturePaletteRecord::getTexObj(void) const
{
    return pTexObj;
}

OFRecordFactoryBase::RegisterRecord OFTexturePaletteRecord::_regHelper(
    &OFTexturePaletteRecord::create,
    OFTexturePaletteRecord::OpCode);

//---------------------------------------------------------------------
// OFVertexPaletteRecord
//---------------------------------------------------------------------

OFRecordTransitPtr OFVertexPaletteRecord::create(const OFRecordHeader &oHeader,
                                                       OFDatabase     &oDB     )
{
    return OFRecordTransitPtr(new OFVertexPaletteRecord(oHeader, oDB));
}

OFVertexPaletteRecord::OFVertexPaletteRecord(const OFRecordHeader &oHeader,
                                                   OFDatabase     &oDB     ) :
    Inherited(oHeader, oDB)
{
}

OFVertexPaletteRecord::~OFVertexPaletteRecord(void)
{
}

bool OFVertexPaletteRecord::read(std::istream &is)
{
    OSG_OPENFLIGHT_LOG(("OFVertexPaletteRecord::read len [%u]\n",
                        _sLength));

    static std::vector<char> tmpBuf;

    Int32 iFullLength;
    Inherited::readVal(is, iFullLength);

    Int32          iRead = 0;

    OFRecordHeader oRHeader;
    bool           rc = true;
    Vec3d          tmpPos;
    Vec3f          tmpNorm;
    Vec2f          tmpTexCoord;
    VertexInfo     tmpInfo;

    while(iRead < iFullLength - 8 && is.good() == true)
    {
        rc = oRHeader.read(is);

        if(rc == false)
        {
            break;
        }

        tmpInfo.uiType   = HasPos | HasCol;
        tmpInfo.uiOffset = iRead + 8;

        tmpInfo.uiIdx[ColIdx     ] = -1;
        tmpInfo.uiIdx[NormIdx    ] = -1;
        tmpInfo.uiIdx[TexCoordIdx] = -1;

        Int32 uiSize = 0;

        uiSize += Inherited::readVal(is, tmpInfo.uiColNameIdx);
        uiSize += Inherited::readVal(is, tmpInfo.iFlags      );

        uiSize += Inherited::readVal(is, tmpPos[0]);
        uiSize += Inherited::readVal(is, tmpPos[1]);
        uiSize += Inherited::readVal(is, tmpPos[2]);

        tmpPos *= _oDB.getUnitScale();

        tmpInfo.uiIdx[PosIdx] = vPositions.size();

        vPositions.push_back(Pnt3f(tmpPos));

        if(oRHeader.sOpCode == 69 || oRHeader.sOpCode == 70)
        {
            uiSize += Inherited::readVal(is, tmpNorm[0]);
            uiSize += Inherited::readVal(is, tmpNorm[1]);
            uiSize += Inherited::readVal(is, tmpNorm[2]);

            tmpInfo.uiIdx[NormIdx]  = vNormals.size();
            tmpInfo.uiType         |= HasNorm;

            vNormals.push_back(tmpNorm);
        }

        if(oRHeader.sOpCode == 70 || oRHeader.sOpCode == 71)
        {
            uiSize += Inherited::readVal(is, tmpTexCoord[0]);
            uiSize += Inherited::readVal(is, tmpTexCoord[1]);

            tmpInfo.uiIdx[TexCoordIdx]  = vTexCoords.size();
            tmpInfo.uiType             |= HasTexCoord;

            vTexCoords.push_back(tmpTexCoord);
        }

        uiSize += Inherited::readVal(is, tmpInfo.iPackedCol);
        uiSize += Inherited::readVal(is, tmpInfo.iColIdx   );

        if(oRHeader.sOpCode == 69 || oRHeader.sOpCode == 70)
        {
            if(uiSize < oRHeader.sLength - 4)
            {
                uiSize += Inherited::readVal(is, tmpInfo.iPad1);
            }
        }

        vVertexInfo.push_back(tmpInfo);

        iRead += oRHeader.sLength;
    }

#if 0
    fprintf(stderr, "Got %d vertices\n",
            vVertexInfo.size());
#endif

    return is.good();
}

UInt16 OFVertexPaletteRecord::getOpCode(void) const
{
    return OpCode;
}

const OFVertexPaletteRecord::VertexInfo *
    OFVertexPaletteRecord::getVertexInfo(UInt32 uiOff) const
{
    std::vector<VertexInfo>::const_iterator iLBound =
        std::lower_bound(vVertexInfo.begin(),
                         vVertexInfo.end  (),
                         uiOff);

    if(iLBound != vVertexInfo.end())
    {
        return &(*iLBound);
    }

    return NULL;
}

const Pnt3f &OFVertexPaletteRecord::getPos(UInt32 uiIdx) const
{
    OSG_ASSERT(uiIdx < vPositions.size());

    return vPositions[uiIdx];
}

const Vec3f &OFVertexPaletteRecord::getNormal(UInt32 uiIdx) const
{
    OSG_ASSERT(uiIdx < vNormals.size());

    return vNormals[uiIdx];
}

const Vec2f &OFVertexPaletteRecord::getTexCoord(UInt32 uiIdx) const
{
    OSG_ASSERT(uiIdx < vTexCoords.size());

    return vTexCoords[uiIdx];
}

bool OFVertexPaletteRecord::VertexInfo::operator <(const UInt32 uiOff) const
{
    return this->uiOffset < uiOff;
}

bool OFVertexPaletteRecord::VertexInfo::operator <(
    const VertexInfo &vInfo) const
{
    return this->uiOffset < vInfo.uiOffset;
}

bool operator <(const UInt32                             uiOff,
                const OFVertexPaletteRecord::VertexInfo &vInfo)
{
    return uiOff < vInfo.uiOffset;
}

OFRecordFactoryBase::RegisterRecord OFVertexPaletteRecord::_regHelper(
    &OFVertexPaletteRecord::create,
    OFVertexPaletteRecord::OpCode);


//---------------------------------------------------------------------
// OFMaterialPaletteRecord
//---------------------------------------------------------------------

OFMaterialPaletteRecord::OFMaterialPaletteRecord(
    const OFRecordHeader &oHeader,
          OFDatabase     &oDB     ) :

    Inherited(oHeader, oDB)
{
    // nothing to do
}

OFMaterialPaletteRecord::~OFMaterialPaletteRecord(void)
{
    // nothing to do
}

OFRecordTransitPtr OFMaterialPaletteRecord::create(
    const OFRecordHeader &oHeader, OFDatabase &oDB)
{
    return OFRecordTransitPtr(new OFMaterialPaletteRecord(oHeader, oDB));
}

bool OFMaterialPaletteRecord::read(std::istream &is)
{
    OSG_OPENFLIGHT_LOG(("OFMaterialPaletteRecord::read len [%u]\n",
                        _sLength));

    Inherited::readVal  (is, iMaterialIdx      );
    Inherited::readChar8(is, szMaterialName, 12);
    Inherited::readVal  (is, iFlags            );
    Inherited::readVal  (is, colAmbient[0]     );
    Inherited::readVal  (is, colAmbient[1]     );
    Inherited::readVal  (is, colAmbient[2]     );
    Inherited::readVal  (is, colDiffuse[0]     );
    Inherited::readVal  (is, colDiffuse[1]     );
    Inherited::readVal  (is, colDiffuse[2]     );
    Inherited::readVal  (is, colSpecular[0]    );
    Inherited::readVal  (is, colSpecular[1]    );
    Inherited::readVal  (is, colSpecular[2]    );
    Inherited::readVal  (is, colEmissive[0]    );
    Inherited::readVal  (is, colEmissive[1]    );
    Inherited::readVal  (is, colEmissive[2]    );
    Inherited::readVal  (is, fShininess        );
    Inherited::readVal  (is, fAlpha            );
    Inherited::readVal  (is, iPad              );

    return is.good();
}

UInt16 OFMaterialPaletteRecord::getOpCode(void) const
{
    return OpCode;
}

void OFMaterialPaletteRecord::dump(UInt32 uiIndent)
{
    indentLog(uiIndent, PLOG);
    PLOG << "OFMaterialPaletteRecord : " << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "{" << std::endl;

    uiIndent += 2;

    indentLog(uiIndent, PLOG);
    PLOG << "MaterialIdx : " << iMaterialIdx << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "MaterialName : " << szMaterialName << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "ColAmbient : " << colAmbient << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "ColDiffuse : " << colDiffuse << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "ColSpecular : " << colSpecular << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "ColEmissive : " << colEmissive << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "Shininess : " << fShininess << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "Alpha : " << fAlpha << std::endl;

    uiIndent -= 2;

    indentLog(uiIndent, PLOG);
    PLOG << "}" << std::endl;
}

Int32 OFMaterialPaletteRecord::getMaterialIdx(void)
{
    return iMaterialIdx;
}

const Color4f &OFMaterialPaletteRecord::getAmbient(void) const
{
    return colAmbient;
}

const Color4f &OFMaterialPaletteRecord::getDiffuse(void) const
{
    return colDiffuse;
}

const Color4f &OFMaterialPaletteRecord::getSpecular(void) const
{
    return colSpecular;
}

const Color4f &OFMaterialPaletteRecord::getEmissive(void) const
{
    return colEmissive;
}

Real32 OFMaterialPaletteRecord::getShininess(void) const
{
    return fShininess;
}

Real32 OFMaterialPaletteRecord::getAlpha(void) const
{
    return fAlpha;
}

OFRecordFactoryBase::RegisterRecord OFMaterialPaletteRecord::_regHelper(
    &OFMaterialPaletteRecord::create,
    OFMaterialPaletteRecord::OpCode);

//---------------------------------------------------------------------
// OFMatrixRecord
//---------------------------------------------------------------------

/* static */
OFRecordTransitPtr OFMatrixRecord::create(const OFRecordHeader &oHeader,
                                                OFDatabase     &oDB     )
{
    return OFRecordTransitPtr(new OFMatrixRecord(oHeader, oDB));
}

OFMatrixRecord::OFMatrixRecord(const OFRecordHeader &oHeader,
                                     OFDatabase     &oDB     ) :
    Inherited(oHeader, oDB),
    matrix   ()
{
}

/* virtual */
OFMatrixRecord::~OFMatrixRecord(void)
{
}

/* virtual */
bool OFMatrixRecord::read(std::istream &is)
{
    OSG_OPENFLIGHT_LOG(("OFMatrixRecord::read len [%u]\n", _sLength));

    Inherited::readVal(is, matrix[0][0]);
    Inherited::readVal(is, matrix[0][1]);
    Inherited::readVal(is, matrix[0][2]);
    Inherited::readVal(is, matrix[0][3]);

    Inherited::readVal(is, matrix[1][0]);
    Inherited::readVal(is, matrix[1][1]);
    Inherited::readVal(is, matrix[1][2]);
    Inherited::readVal(is, matrix[1][3]);

    Inherited::readVal(is, matrix[2][0]);
    Inherited::readVal(is, matrix[2][1]);
    Inherited::readVal(is, matrix[2][2]);
    Inherited::readVal(is, matrix[2][3]);

    Inherited::readVal(is, matrix[3][0]);
    Inherited::readVal(is, matrix[3][1]);
    Inherited::readVal(is, matrix[3][2]);
    Inherited::readVal(is, matrix[3][3]);

    matrix[3][0] *= _oDB.getUnitScale();
    matrix[3][1] *= _oDB.getUnitScale();
    matrix[3][2] *= _oDB.getUnitScale();

    return is.good();
}

/* virtual */
UInt16 OFMatrixRecord::getOpCode(void) const
{
    return OpCode;
}

/* virtual */
void OFMatrixRecord::dump(UInt32 uiIndent)
{
    indentLog(uiIndent, PLOG);
    PLOG << "MatrixRecord" << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "{" << std::endl;

    uiIndent += 2;

    indentLog(uiIndent, PLOG);
    PLOG << matrix[0][0] << " " << matrix[1][0] << " "
         << matrix[2][0] << " " << matrix[3][0] << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << matrix[0][1] << " " << matrix[1][1] << " "
         << matrix[2][1] << " " << matrix[3][1] << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << matrix[0][2] << " " << matrix[1][2] << " "
         << matrix[2][2] << " " << matrix[3][2] << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << matrix[0][3] << " " << matrix[1][3] << " "
         << matrix[2][3] << " " << matrix[3][3] << std::endl;

    uiIndent -= 2;

    indentLog(uiIndent, PLOG);
    PLOG << "}" << std::endl;

    Inherited::dump(uiIndent);
}

/* virtual */
NodeTransitPtr OFMatrixRecord::convert(Node *pNode)
{
    NodeUnrecPtr returnValue(NULL);

    if(pNode != NULL)
    {
        TransformUnrecPtr pXform = Transform::create();
        pXform->setMatrix(matrix);

        returnValue = makeNodeFor(pXform);
        returnValue->addChild(pNode);
    }

    return NodeTransitPtr(returnValue);
}

OFRecordFactoryBase::RegisterRecord OFMatrixRecord::_regHelper(
    &OFMatrixRecord::create,
    OFMatrixRecord::OpCode);

//---------------------------------------------------------------------
// OFLongIDRecord
//---------------------------------------------------------------------

/* static */
OFRecordTransitPtr OFLongIDRecord::create(const OFRecordHeader &oHeader,
                                                OFDatabase     &oDB     )
{
    return OFRecordTransitPtr(new OFLongIDRecord(oHeader, oDB));
}

OFLongIDRecord::OFLongIDRecord(const OFRecordHeader &oHeader,
                                     OFDatabase     &oDB     ) :
    Inherited(oHeader, oDB),
    longId   ()
{
}

/* virtual */
OFLongIDRecord::~OFLongIDRecord(void)
{
}

/* virtual */
bool OFLongIDRecord::read(std::istream &is)
{
    OSG_OPENFLIGHT_LOG(("OFLongIDRecord::read len [%u]\n", _sLength));

    longId.resize(_sLength - 4);
    is.read(reinterpret_cast<Char8 *>(&(*longId.begin())), _sLength - 4);

    return is.good();
}

/* virtual */
UInt16 OFLongIDRecord::getOpCode(void) const
{
    return OpCode;
}

/* virtual */
void OFLongIDRecord::dump(UInt32 uiIndent)
{
    indentLog(uiIndent, PLOG);
    PLOG << "LongIDRecord" << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "{" << std::endl;

    uiIndent += 2;

    indentLog(uiIndent, PLOG);
    PLOG << "longId: '" << longId << "'" << std::endl;

    uiIndent -= 2;

    indentLog(uiIndent, PLOG);
    PLOG << "}" << std::endl;

    Inherited::dump(uiIndent);
}

/* virtual */
NodeTransitPtr OFLongIDRecord::convert(Node *pNode)
{
    NodeUnrecPtr returnValue(pNode);

    if(pNode != NULL)
    {
        setName(pNode, longId);
    }

    return NodeTransitPtr(returnValue);
}

OFRecordFactoryBase::RegisterRecord OFLongIDRecord::_regHelper(
    &OFLongIDRecord::create,
    OFLongIDRecord::OpCode);

OSG_END_NAMESPACE
