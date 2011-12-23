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
#include "OSGPathHandler.h"

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------
// OFColorPaletteRecord
//---------------------------------------------------------------------

/* static */
OFRecordTransitPtr OFColorPaletteRecord::create(const OFRecordHeader &oHeader,
                                                      OFDatabase     &oDB     )
{
    return OFRecordTransitPtr(new OFColorPaletteRecord(oHeader, oDB));
}

OFColorPaletteRecord::OFColorPaletteRecord(const OFRecordHeader &oHeader,
                                                 OFDatabase     &oDB     ) :
    Inherited (oHeader, oDB),
    colors    (),
    colorNames()
{
}

/* virtual */
OFColorPaletteRecord::~OFColorPaletteRecord(void)
{
}

/* virtual */
bool OFColorPaletteRecord::read(std::istream &is)
{
    OSG_OPENFLIGHT_LOG(("OFColorPaletteRecord::read len [%u]\n", _sLength));

    Char8 reserved1[128];
    Inherited::readChar8(is, reserved1, 128);

    bool   hasNames  = _sLength > 4228;
    UInt32 numColors = 1024;

    if(hasNames == false)
    {
        // number of colors derived from record size
        UInt32 numColors2 = (_sLength - 132) / 4;

        numColors = osgMin(numColors, numColors2);
    }

    for(UInt32 i = 0; i < numColors; ++i)
    {
        UChar8 alpha;
        UChar8 blue;
        UChar8 green;
        UChar8 red;

        Inherited::readVal(is, alpha);
        Inherited::readVal(is, blue );
        Inherited::readVal(is, green);
        Inherited::readVal(is, red  );

        colors.push_back(Color4f(red  / 255.f, green / 255.f,
                                 blue / 255.f, alpha / 255.f ));
    }

    if(hasNames == true)
    {
        colorNames.resize(numColors);

        Int32 numNames;
        Inherited::readVal(is, numNames);

        for(Int32 i = 0; i < numNames; ++i)
        {
            UInt16 nameLen;
            Int16  reserved2;
            Int16  colorIdx;
            Int16  reserved3;
            Char8  name[80];

            Inherited::readVal  (is, nameLen);
            Inherited::readVal  (is, reserved2);
            Inherited::readVal  (is, colorIdx);
            Inherited::readVal  (is, reserved3);
            Inherited::readChar8(is, name, 80);

            colorNames[colorIdx] = std::string(name);
        }
    }

    return is.good();
}

/* virtual */
UInt16 OFColorPaletteRecord::getOpCode(void) const
{
    return OpCode;
}

/* virtual */
void OFColorPaletteRecord::dump(UInt32 uiIndent) const
{
    indentLog(uiIndent, PLOG);
    PLOG << "ColorPaletteRecord" << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "{" << std::endl;

    uiIndent += 2;

    for(UInt32 i = 0; i < colors.size(); ++i)
    {
        indentLog(uiIndent, PLOG);
        PLOG << "Color " << colors[i];

        if(colorNames.empty() == false)
            PLOG  << " name " << colorNames[i];

        PLOG << std::endl;
    }

    uiIndent -= 2;

    indentLog(uiIndent, PLOG);
    PLOG << "}" << std::endl;
}

Color4f OFColorPaletteRecord::getColor(UInt32 uiIdx) const
{
    Color4f returnValue;
    UInt32  uiRealIdx = uiIdx >> 7;
    Real32  intensity = (uiIdx & 0x7f) / 127.f;

    OSG_ASSERT(uiRealIdx < colors.size());

    returnValue    =  colors[uiRealIdx];
    returnValue[0] *= intensity;
    returnValue[1] *= intensity;
    returnValue[2] *= intensity;

    return returnValue;
}

bool OFColorPaletteRecord::hasNames(void) const
{
    return !colorNames.empty();
}

std::string const &OFColorPaletteRecord::getName(UInt32 uiIdx) const
{
    return colorNames[uiIdx];
}

OFRecordFactoryBase::RegisterRecord OFColorPaletteRecord::_regHelper(
    &OFColorPaletteRecord::create,
    OFColorPaletteRecord::OpCode);

//---------------------------------------------------------------------
// OFTexturePaletteRecord
//---------------------------------------------------------------------

GLenum OFTexturePaletteRecord::TexAttr::getMinFilter(void)
{
    GLenum returnValue = GL_NEAREST;

    switch(minFilter)
    {
    case 0: returnValue = GL_NEAREST;                 break; // point
    case 1: returnValue = GL_LINEAR;                  break; // bilinear
    case 3: returnValue = GL_NEAREST_MIPMAP_NEAREST;  break; // mipmap point
    case 4: returnValue = GL_NEAREST_MIPMAP_LINEAR;   break; // mipmap linear
    case 5: returnValue = GL_LINEAR_MIPMAP_NEAREST;   break; // mipmap bilinear
    case 7: returnValue = GL_LINEAR_MIPMAP_LINEAR;    break; // mipmap trilinear

    case 9:   // bicubic
    case 10:  // bilinear GEQ
    case 11:  // bilinear LEQ
    case 12:  // bicubic GEQ
    case 13:  // bicubic LEQ
        returnValue = GL_LINEAR_MIPMAP_NEAREST;
        break;

    default: returnValue = GL_LINEAR_MIPMAP_LINEAR;   break;
    }

    return returnValue;
}

GLenum OFTexturePaletteRecord::TexAttr::getMagFilter(void)
{
    GLenum returnValue = GL_NEAREST;

    switch(magFilter)
    {
    case 0: returnValue = GL_NEAREST; break;  // point

    case  1: // bilinear
    case  3: // bicubic
    case  4: // sharpen
    case  5: // add detail
    case  6: // modulate detail
    case  7: // bilinear GEQ
    case  8: // bilinear LEQ
    case  9: // bicubic GEQ
    case 10: // bicubic LEQ
        returnValue = GL_LINEAR;
        break;
    }

    return returnValue;
}

GLenum OFTexturePaletteRecord::TexAttr::getWrapU(void)
{
    return getWrap(wrapU);
}

GLenum OFTexturePaletteRecord::TexAttr::getWrapV(void)
{
    return getWrap(wrapV);
}

GLenum OFTexturePaletteRecord::TexAttr::getEnvMode(void)
{
    GLenum returnValue = GL_MODULATE;

    switch(envMode)
    {
    case 0: returnValue = GL_MODULATE;  break; // modulate
    case 1: returnValue = GL_BLEND;     break; // blend
    case 2: returnValue = GL_DECAL;     break; // decal
    case 3: returnValue = GL_REPLACE;   break; // replace
    case 4: returnValue = GL_ADD;       break; // add
    }

    return returnValue;
}

GLenum OFTexturePaletteRecord::TexAttr::getWrap(Int32 wrap)
{
    GLenum returnValue = GL_REPEAT;

    switch(wrap)
    {
    case 0: returnValue = GL_REPEAT;        break;  // repeat
    case 1: returnValue = GL_CLAMP_TO_EDGE; break;  // clamp
    case 4: returnValue = GL_REPEAT;        break;  // mirror
    }

    return returnValue;
}

/* static */
OFRecordTransitPtr OFTexturePaletteRecord::create(const OFRecordHeader &oHeader,
                                                        OFDatabase     &oDB     )
{
    return OFRecordTransitPtr(new OFTexturePaletteRecord(oHeader, oDB));
}

bool OFTexturePaletteRecord::readTexAttr(TexAttr &attr)
{
    bool        returnValue = false;
    PathHandler *ph         = ImageFileHandler::the()->getPathHandler();

    if(ph != NULL)
    {
        std::string imgFile  = szFilename;
        std::string attrFile = imgFile + ".attr";

        attrFile = ph->findFile(attrFile.c_str());

        if(attrFile.empty() == false)
        {
            OSG_OPENFLIGHT_LOG(("OFTexturePaletteRecord::readTexAttr: [%s]\n",
                                attrFile.c_str()));

            std::ifstream ifs;
            ifs.open(attrFile.c_str(), std::ios::in | std::ios::binary);

            Inherited::readVal(ifs, attr.numTexelU);
            Inherited::readVal(ifs, attr.numTexelV);
            Inherited::readVal(ifs, attr.realSizeU);
            Inherited::readVal(ifs, attr.realSizeV);
            Inherited::readVal(ifs, attr.upX);
            Inherited::readVal(ifs, attr.upY);
            Inherited::readVal(ifs, attr.fileFormat);
            Inherited::readVal(ifs, attr.minFilter);
            Inherited::readVal(ifs, attr.magFilter);
            Inherited::readVal(ifs, attr.wrapUV);
            Inherited::readVal(ifs, attr.wrapU);
            Inherited::readVal(ifs, attr.wrapV);
            Inherited::readVal(ifs, attr.modified);
            Inherited::readVal(ifs, attr.pivotX);
            Inherited::readVal(ifs, attr.pivotY);
            Inherited::readVal(ifs, attr.envMode);

            if(attr.wrapU == 3)
                attr.wrapU = attr.wrapUV;
            if(attr.wrapV == 3)
                attr.wrapV = attr.wrapUV;

            returnValue = true;
        }
    }

    return returnValue;
}

OFTexturePaletteRecord::OFTexturePaletteRecord(const OFRecordHeader &oHeader,
                                                     OFDatabase     &oDB     ) :
    Inherited(oHeader, oDB),
    pTexObj  (),
    pTexEnv  ()
{
}

OFTexturePaletteRecord::~OFTexturePaletteRecord(void)
{
    pTexObj = NULL;
}

/* virtual */
bool OFTexturePaletteRecord::read(std::istream &is)
{
    Inherited::readChar8(is, szFilename, 200);
    Inherited::readVal  (is, iPatternIdx    );
    Inherited::readVal  (is, iPatternX      );
    Inherited::readVal  (is, iPatternY      );

    OSG_OPENFLIGHT_LOG(("OFTexturePaletteRecord::read len "
                        "[%u] file [%s] idx [%d]\n",
                        _sLength, szFilename, iPatternIdx));

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

    if(pTexObj != NULL)
    {
        TexAttr attr;
        if(readTexAttr(attr) == true)
        {
            pTexObj->setMinFilter(attr.getMinFilter());
            pTexObj->setMagFilter(attr.getMagFilter());
            pTexObj->setWrapS    (attr.getWrapU    ());
            pTexObj->setWrapT    (attr.getWrapV    ());

            pTexEnv = TextureEnvChunk::create();
            pTexEnv->setEnvMode(attr.getEnvMode());
        }
    }

    return is.good();
}

/* virtual */
UInt16 OFTexturePaletteRecord::getOpCode(void) const
{
    return OpCode;
}

void OFTexturePaletteRecord::dump(UInt32 uiIndent) const
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

TextureEnvChunk *OFTexturePaletteRecord::getTexEnv(void) const
{
    return pTexEnv;
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

        tmpInfo.uiIdx[PosIdx] = UInt32(vPositions.size());

        vPositions.push_back(Pnt3f(tmpPos));

        if(oRHeader.sOpCode == 69 || oRHeader.sOpCode == 70)
        {
            uiSize += Inherited::readVal(is, tmpNorm[0]);
            uiSize += Inherited::readVal(is, tmpNorm[1]);
            uiSize += Inherited::readVal(is, tmpNorm[2]);

            tmpInfo.uiIdx[NormIdx]  = UInt32(vNormals.size());
            tmpInfo.uiType         |= HasNorm;

            vNormals.push_back(tmpNorm);
        }

        if(oRHeader.sOpCode == 70 || oRHeader.sOpCode == 71)
        {
            uiSize += Inherited::readVal(is, tmpTexCoord[0]);
            uiSize += Inherited::readVal(is, tmpTexCoord[1]);

            tmpInfo.uiIdx[TexCoordIdx]  = UInt32(vTexCoords.size());
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

void OFMaterialPaletteRecord::dump(UInt32 uiIndent) const
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
void OFMatrixRecord::dump(UInt32 uiIndent) const
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
// OFIgnoredTransformRecord
//---------------------------------------------------------------------

/* static */
OFRecordTransitPtr OFIgnoredTransformRecord::create(
    const OFRecordHeader &oHeader,
          OFDatabase     &oDB     )
{
    return OFRecordTransitPtr(new OFIgnoredTransformRecord(oHeader, oDB));
}

OFIgnoredTransformRecord::OFIgnoredTransformRecord(
    const OFRecordHeader &oHeader,
          OFDatabase     &oDB     ) :

    Inherited(oHeader, oDB),
    _sOpCode (oHeader.sOpCode)
{
}

/* virtual */
OFIgnoredTransformRecord::~OFIgnoredTransformRecord(void)
{
}

/* virtual */
bool OFIgnoredTransformRecord::read(std::istream &is)
{
    OSG_OPENFLIGHT_LOG(("OFIgnoredTransformRecord::read op [%u][%s] len [%u]\n",
                        _sOpCode, getOpCodeString(_sOpCode), _sLength));

    static std::vector<char> tmpBuf;

    if(_sLength > 4)
    {
        tmpBuf.resize(_sLength);

        is.read(&(tmpBuf.front()), _sLength - 4);
    }

    return is.good();
}

/* virtual */
NodeTransitPtr OFIgnoredTransformRecord::convert(Node *pNode)
{
    return NodeTransitPtr(pNode);
}

/* virtual */
UInt16 OFIgnoredTransformRecord::getOpCode(void) const
{
    return _sOpCode;
}

/* virtual */
void OFIgnoredTransformRecord::dump(UInt32 uiIndent) const
{
    indentLog(uiIndent, PLOG);
    PLOG << "OFIgnoredTransformRecord - " << _sOpCode
         << " - "                         << getOpCodeString(_sOpCode)
         << std::endl;
}

OFRecordFactoryBase::RegisterRecord
OFIgnoredTransformRecord::_regHelperRotateAboutEdge(
    &OFIgnoredTransformRecord::create,
    OFIgnoredTransformRecord::OpCodeRotateAboutEdge);

OFRecordFactoryBase::RegisterRecord
OFIgnoredTransformRecord::_regHelperTranslate(
    &OFIgnoredTransformRecord::create,
    OFIgnoredTransformRecord::OpCodeTranslate);

OFRecordFactoryBase::RegisterRecord
OFIgnoredTransformRecord::_regHelperScale(
    &OFIgnoredTransformRecord::create,
    OFIgnoredTransformRecord::OpCodeScale);

OFRecordFactoryBase::RegisterRecord
OFIgnoredTransformRecord::_regHelperRotateAboutPoint(
    &OFIgnoredTransformRecord::create,
    OFIgnoredTransformRecord::OpCodeRotateAboutPoint);

OFRecordFactoryBase::RegisterRecord
OFIgnoredTransformRecord::_regHelperRotateScaleToPoint(
    &OFIgnoredTransformRecord::create,
    OFIgnoredTransformRecord::OpCodeRotateScaleToPoint);

OFRecordFactoryBase::RegisterRecord
OFIgnoredTransformRecord::_regHelperPut(
    &OFIgnoredTransformRecord::create,
    OFIgnoredTransformRecord::OpCodePut);

OFRecordFactoryBase::RegisterRecord
OFIgnoredTransformRecord::_regHelperGeneralMatrix(
    &OFIgnoredTransformRecord::create,
    OFIgnoredTransformRecord::OpCodeGeneralMatrix);

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
void OFLongIDRecord::dump(UInt32 uiIndent) const
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
