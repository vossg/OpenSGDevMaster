
#include "OSGOFRecords.h"

#include "OSGSingletonHolder.ins"

#include "OSGGroup.h"
#include "OSGRangeLOD.h"
#include "OSGTransform.h"
#include "OSGGeometry.h"
#include "OSGTypedGeoIntegralProperty.h"
#include "OSGOFDatabase.h"

#include "OSGImageFileHandler.h"
#include "OSGSceneFileHandler.h"

#include "OSGChunkMaterial.h"
#include "OSGMaterialChunk.h"

#include "OSGGeoFunctions.h"

#include "OSGOpenFlightSceneFileType.h"

OSG_BEGIN_NAMESPACE

OSG_SINGLETON_INST(OFRecordFactoryBase)

template class SingletonHolder<OFRecordFactoryBase>;

//---------------------------------------------------------------------
// OFRecordFactoryBase
//---------------------------------------------------------------------

OFRecordFactoryBase::RegisterRecord::RegisterRecord(CreateRecord fCreate, 
                                                    UInt16       sRecordOpCode)
{
    OFRecordFactory::the()->registerRecord(fCreate, sRecordOpCode);
}


OFRecordFactoryBase::OFRecordFactoryBase(void) :
    _mRegisteredRecords()
{
}

OFRecordFactoryBase::~OFRecordFactoryBase(void)
{
}

void OFRecordFactoryBase::registerRecord(CreateRecord fHelper,
                                         UInt16       sRecordOpCode)
{
    if(fHelper == NULL) 
        return;

    NameRecordCreateMap::iterator mRecordIt = 
        _mRegisteredRecords.find(sRecordOpCode);
  

    if(mRecordIt == _mRegisteredRecords.end())
    {
        _mRegisteredRecords[sRecordOpCode] = fHelper;

        PINFO << "Record registered for "
              << sRecordOpCode
              << std::endl;
    }
    else
    {
        PWARNING << "Record already registered for %s "
                 << sRecordOpCode
                 << std::endl;
    }
}

OFRecordTransitPtr OFRecordFactoryBase::createRecord(
    const OFRecordHeader &oHeader)
{
    NameRecordCreateMap::iterator mRecordIt =
        _mRegisteredRecords.find(oHeader.sOpCode);
  
    OFRecordTransitPtr returnValue(NULL);

    if(mRecordIt != _mRegisteredRecords.end())
    {
        returnValue = (*mRecordIt).second(oHeader);
    }
    else
    {
        returnValue = new OFUnknownRecord(oHeader);
    }

    return returnValue;
}

//---------------------------------------------------------------------
// OFRecord
//---------------------------------------------------------------------

struct OFOpCodeDesc
{
          UInt16  sOpCode;
    const Char8  *szDesc;
};


OFOpCodeDesc aOpCodeDescs[] =
{
    {1,   "Header"                             },
    {2,   "Group"                              },
    {4,   "Object                             "},
    {5,   "Face"                               },                
    {10,  "Push Level                         "},
    {11,  "Pop Level                          "},
    {14,  "Degree of Freedom                  "},
    {19,  "Push Subface                       "},
    {20,  "Pop Subface                        "},
    {21,  "Push Extension                     "},
    {22,  "Pop Extension                      "},
    {23,  "Continuation                       "},
    {31,  "Comment                            "},
    {32,  "Color Palette                      "},
    {33,  "Long ID                            "},
    {49,  "Matrix                             "},
    {50,  "Vector                             "},
    {52,  "Multitexture                       "},
    {53,  "UV List                            "},
    {55,  "Binary Separating Plane            "},
    {60,  "Replicate                          "},
    {61,  "Instance Reference                 "},
    {62,  "Instance Definition                "},
    {63,  "External Reference                 "},
    {64,  "Texture Palette"                    },
    {67,  "Vertex Palette"                     },
    {68,  "Vertex with Color                  "},
    {69,  "Vertex with Color and Normal"       },
    {70,  "Vertex with Color, Normal and UV"   },
    {71,  "Vertex with Color and UV           "},
    {72,  "Vertex List"                        },
    {73,  "Level of Detail"                    },
    {74,  "Bounding Box                       "},
    {76,  "Rotate About Edge                  "},
    {78,  "Translate                          "},
    {79,  "Scale                              "},
    {80,  "Rotate About Point                 "},
    {81,  "Rotate and/or Scale to Point       "},
    {82,  "Put                                "},
    {83,  "Eyepoint and Trackplane Palette    "},
    {84,  "Mesh                               "},
    {85,  "Local Vertex Pool                  "},
    {86,  "Mesh Primitive                     "},
    {87,  "Road Segment                       "},
    {88,  "Road Zone                          "},
    {89,  "Morph Vertex List                  "},
    {90,  "Linkage Palette                    "},
    {91,  "Sound                              "},
    {92,  "Road Path                          "},
    {93,  "Sound Palette                      "},
    {94,  "General Matrix                     "},
    {95,  "Text                               "},
    {96,  "Switch                             "},
    {97,  "Line Style Palette                 "},
    {98,  "Clip Region                        "},
    {100, "Extension                          "},
    {101, "Light Source                       "},
    {102, "Light Source Palette               "},
    {103, "Reserved                           "},
    {104, "Reserved                           "},
    {105, "Bounding Sphere                    "},
    {106, "Bounding Cylinder                  "},
    {107, "Bounding Convex Hull               "},
    {108, "Bounding Volume Center             "},
    {109, "Bounding Volume Orientation        "},
    {110, "Reserved                           "},
    {111, "Light Point                        "},
    {112, "Texture Mapping Palette            "},
    {113, "Material Palette                   "},
    {114, "Name Table                         "},
    {115, "Continuously Adaptive Terrain (CAT)"},
    {116, "CAT Data                           "},
    {117, "Reserved                           "},
    {118, "Reserved                           "},
    {119, "Bounding Histogram                 "},
    {120, "Reserved                           "},
    {121, "Reserved                           "},
    {122, "Push Attribute                     "},
    {123, "Pop Attribute                      "},
    {124, "Reserved                           "},
    {125, "Reserved                           "},
    {126, "Curve                              "},
    {127, "Road Construction                  "},
    {128, "Light Point Appearance Palette     "},
    {129, "Light Point Animation Palette      "},
    {130, "Indexed Light Point                "},
    {131, "Light Point System                 "},
    {132, "Indexed String                     "},
    {133, "Shader Palette                     "},
    {134, "Reserved                           "},
    {135, "Extended Material Header           "},
    {136, "Extended Material Ambient          "},
    {137, "Extended Material Diffuse          "},
    {138, "Extended Material Specular         "},
    {139, "Extended Material Emissive         "},
    {140, "Extended Material Alpha            "},
    {141, "Extended Material Light Map        "},
    {142, "Extended Material Normal Map       "},
    {143, "Extended Material Bump Map         "},
    {144, "Reserved                           "},
    {145, "Extended Material Shadow Map       "},
    {146, "Reserved                           "},
    {147, "Extended Material Reflection Map   "},

    {0, "Reached last -> Unknown              "}
};

#if 0
Obsolete

3  Level of Detail (single precision floating point, replaced by Opcode 73)
6  Vertex with ID (scaled integer coordinates, replaced by Opcodes 68-71)
7  Short Vertex w/o ID (scaled integer coordinates, replaced by Opcodes 68-71)
8  Vertex with Color (scaled integer coordinates, replaced by Opcodes 68-71)
9  Vertex with Color and Normal (scaled integer coordinates, replaced by Opcodes 68-71)
12 Translate (replaced by Opcode 78)
13 Degree of Freedom (scaled integer coordinates, replaced by Opcode 14)
16 Instance Reference (replaced by Opcode 61)
17 Instance Definition (replaced by Opcode 62)
40 Translate (replaced by Opcode 78)
41 Rotate about Point (replaced by Opcode 80)
42 Rotate about Edge (replaced by Opcode 76)
43 Scale (replaced by Opcode 79)
44 Translate (replaced by Opcode 78)
45 Scale nonuniform (replaced by Opcode 79)
46 Rotate about Point (replaced by Opcode 80)
47 Rotate and/or Scale to Point (replaced by Opcode 81)
48 Put (replaced by Opcode 82)
51 Bounding Box (replaced by Opcode 74)
65 Eyepoint Palette (only eyepoints, replaced by Opcode 83)
66 Material Palette (fixed size 64 entries, replaced by Opcode 80)
77 Scale (replaced by Opcode 79)

#endif


void OFRecord::readChar8(std::istream &is, Char8  *cVal, UInt32 iSize)
{
    is.read(cVal, iSize);
}

template<class ValueT>
UInt32 OFRecord::readVal(std::istream &is, ValueT &val)
{
    is.read(reinterpret_cast<char *>(&val), sizeof(ValueT));

    val = osgBigEndianToHost(val);

    return sizeof(ValueT);
}

template<>
UInt32 OFRecord::readVal<Int8>(std::istream &is, Int8 &val)
{
    is.read(reinterpret_cast<char *>(&val), sizeof(Int8));

    return sizeof(Int8);
}

template<>
UInt32 OFRecord::readVal<UInt8>(std::istream &is, UInt8 &val)
{
    is.read(reinterpret_cast<char *>(&val), sizeof(UInt8));

    return sizeof(UInt8);
}

OFRecord::OFRecord(const OFRecordHeader &oHeader) :
     Inherited(               ),
    _sLength  (oHeader.sLength)
{
}

OFRecord::~OFRecord(void)
{
}

bool OFRecord::read(std::istream &is, OFDatabase &oDB)
{
    static std::vector<char> tmpBuf;

    if(_sLength > 4)
    {
        tmpBuf.resize(_sLength);

        is.read(&(tmpBuf.front()), _sLength - 4);
    }

    return is.good();
}

bool OFRecord::addChild (OFRecord *pChild)
{
    if(pChild == NULL)
        return false;

          UInt16  uiCurrOpCode  = this  ->getOpCode(             );
    const Char8  *szCurrDesc    = this  ->findDesc (uiCurrOpCode );
          UInt16  uiChildOpCode = pChild->getOpCode(             );
    const Char8  *szChildDesc   = this  ->findDesc (uiChildOpCode);

#if 0
    fprintf(stderr, "Add %hu (%p) (%s) to %hu (%p) (%s)\n",
            uiChildOpCode,
            pChild,
            szChildDesc,
            uiCurrOpCode,
            this,
            szCurrDesc);
#endif

    return true;
}

NodeTransitPtr OFRecord::convertToNode(OFDatabase &oDB)
{
    NodeTransitPtr returnValue(NULL);

    return returnValue;
}
   

const Char8 *OFRecord::findDesc(UInt16 sOpCode)
{
    OFOpCodeDesc *pDesc = aOpCodeDescs;

    while(pDesc->sOpCode != 0)
    {
        if(pDesc->sOpCode == sOpCode)
        {
            break;
        }

        ++pDesc;
    }

    return pDesc->szDesc;
}

void OFRecord::dump(UInt32 uiIndent)
{
}

//---------------------------------------------------------------------
// OFVertexPalette
//---------------------------------------------------------------------

OFVertexPalette::OFVertexPalette(void) :
     Inherited     (    ),
    _pVertexPalette(NULL)
{
}

OFVertexPalette::~OFVertexPalette(void)
{
    _pVertexPalette = NULL;
}

void OFVertexPalette::addRecord(OFVertexPaletteRecord *pVertexPal)
{
    _pVertexPalette = pVertexPal;
}

const OFVertexPaletteRecord *OFVertexPalette::getRecord(void)
{
    return _pVertexPalette;
}

//---------------------------------------------------------------------
// OFTexturePalette
//---------------------------------------------------------------------

OFTexturePalette::OFTexturePalette(void) :
    _mTextures()
{
}

OFTexturePalette::~OFTexturePalette(void)
{
    TextureStoreIt tIt  = _mTextures.begin();
    TextureStoreIt tEnd = _mTextures.end  ();

    while(tIt != tEnd)
    {
        tIt->second = NULL;

        ++tIt;
    }

    _mTextures.clear();
}

void OFTexturePalette::addRecord(OFTexturePaletteRecord *pTex)
{
    if(pTex != NULL)
    {
        TextureStoreIt tIt = _mTextures.find(pTex->getPatternIdx());
        
        if(tIt == _mTextures.end())
        {
            _mTextures[pTex->getPatternIdx()] = pTex;
        }
        else
        {
            fprintf(stderr, "Tex with idx %d already there \n",
                    pTex->getPatternIdx());
        }
    }
}

const OFTexturePaletteRecord *OFTexturePalette::getRecord(Int32 uiId)
{
    const OFTexturePaletteRecord *returnValue = NULL;

    TextureStoreIt tIt = _mTextures.find(uiId);

    if(tIt != _mTextures.end())
    {
        returnValue = tIt->second;
    }

    return returnValue;
}

//---------------------------------------------------------------------
// OFHeaderRecord
//---------------------------------------------------------------------

OFHeaderRecord::OFHeaderRecord(const OFRecordHeader &oHeader) :
     Inherited(oHeader),
    _vChildren(       )
{
    _pVertexPal  = new OFVertexPalette ();
    _pTexturePal = new OFTexturePalette();
}

OFHeaderRecord::~OFHeaderRecord(void)
{
    for(UInt32 i = 0; i < _vChildren.size(); ++i)
    {
        _vChildren[i] = NULL;
    }

    _vChildren.clear();

    _pVertexPal  = NULL;
    _pTexturePal = NULL;
}

bool OFHeaderRecord::read(std::istream &is, OFDatabase &)
{
    std::vector<char> tmpBuf;

    tmpBuf.resize(_sLength);

    is.read(&(tmpBuf.front()), _sLength - 4);

    return is.good();
}

bool OFHeaderRecord::addChild(OFRecord *pChild)
{
    if(pChild == NULL)
    {
        return false;
    }

    switch(pChild->getOpCode())
    {
        case 32: // color
        case 83: // eye trackplane
        case 90: // linkage
        case 93: // sound
        case 97: // line style
        case 102: // light source
        case 112: // tex mapping
        case 113: // material
        case 128: // lpoint app
        case 129: // lpoint anim
        case 133: // shader
        {
            break;
        }

        case OFTexturePaletteRecord::OpCode:
        {
            OFTexturePaletteRecord *pTex = 
                dynamic_cast<OFTexturePaletteRecord *>(pChild);

            _pTexturePal->addRecord(pTex);

            break;
        }

        case OFVertexPaletteRecord::OpCode:
        {
            _pVertexPal->addRecord(
                dynamic_cast<OFVertexPaletteRecord *>(pChild));

            break;
        }

        default:
        {
            _vChildren.push_back(pChild);
        }
    }

    return true;
}

UInt16 OFHeaderRecord::getOpCode(void)
{
    return OpCode;
}

NodeTransitPtr OFHeaderRecord::convertToNode(OFDatabase &oDB)
{
    NodeTransitPtr returnValue(NULL);

    if(_vChildren.size() != 0)
    {
        returnValue = Node::create();

        returnValue->setCore(Group::create());

        NodeTransitPtr pChild;

        for(UInt32 i = 0; i < _vChildren.size(); ++i)
        {
            pChild = _vChildren[i]->convertToNode(oDB);

            if(pChild != NULL)
            {
                returnValue->addChild(pChild);
            }
            else
            {
/*
                fprintf(stderr, "no child for record %hu %s\n",
                        vChildren[i]->getOpCode(),
                        findDesc(vChildren[i]->getOpCode()));
 */
            }
        }
    }

    return returnValue;
}

const OFVertexPaletteRecord *OFHeaderRecord::getVertexPalette(void)
{
    return _pVertexPal->getRecord();
}

const OFTexturePaletteRecord *OFHeaderRecord::getTexRecord(UInt32 uiIdx)
{
    return _pTexturePal->getRecord(uiIdx);
}

void OFHeaderRecord::dump(UInt32 uiIndent)
{
    indentLog(uiIndent, PLOG);
    PLOG << "HeaderRecord" << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "{" << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "}" << std::endl;
    
    indentLog(uiIndent, PLOG);
    PLOG << "[" << std::endl;

    uiIndent += 2;

    for(UInt32 i = 0; i < _vChildren.size(); ++i)
    {
        _vChildren[i]->dump(uiIndent);
    }

    uiIndent -= 2;

    indentLog(uiIndent, PLOG);
    PLOG << "]" << std::endl;
}


//---------------------------------------------------------------------
// OFUnknownRecord
//---------------------------------------------------------------------

OFUnknownRecord::OFUnknownRecord(const OFRecordHeader &oHeader) :
     Inherited(oHeader        ),
    _sOpCode  (oHeader.sOpCode)
{
    const char *szDesc = findDesc(oHeader.sOpCode);

#if 0
    fprintf(stderr, "Unknow opcode %hu : %s\n",
            oHeader.sOpCode,
            szDesc);
#endif
}

OFUnknownRecord::~OFUnknownRecord(void)
{
}

bool OFUnknownRecord::read(std::istream &is, OFDatabase &oDB)
{
    static std::vector<char> tmpBuf;

    if(_sLength > 4)
    {
        tmpBuf.resize(_sLength);

        is.read(&(tmpBuf.front()), _sLength - 4);
    }

    return is.good();
}

UInt16 OFUnknownRecord::getOpCode(void)
{
    return _sOpCode;
}

//---------------------------------------------------------------------
// OFTexturePaletteRecord
//---------------------------------------------------------------------

OFRecordTransitPtr OFTexturePaletteRecord::create(const OFRecordHeader &oHeader)
{
    return OFRecordTransitPtr(new OFTexturePaletteRecord(oHeader));
}

OFTexturePaletteRecord::OFTexturePaletteRecord(const OFRecordHeader &oHeader) :
    Inherited(oHeader),
    pTexObj()
{
}

OFTexturePaletteRecord::~OFTexturePaletteRecord(void)
{
    pTexObj = NULL;
}

bool OFTexturePaletteRecord::read(std::istream &is, OFDatabase &oDB)
{
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
                fprintf(stderr, "Could not read image %s\n",
                        &(szFilename[uiPos + 1]));
            }
        }
        else
        {
            fprintf(stderr, "Could not read image %s\n",
                    szFilename);
        }
    }

    return is.good();
}

UInt16 OFTexturePaletteRecord::getOpCode(void)
{
    return OpCode;
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

OFRecordTransitPtr OFVertexPaletteRecord::create(const OFRecordHeader &oHeader)
{
    return OFRecordTransitPtr(new OFVertexPaletteRecord(oHeader));
}

OFVertexPaletteRecord::OFVertexPaletteRecord(const OFRecordHeader &oHeader) :
    Inherited(oHeader)
{
}

OFVertexPaletteRecord::~OFVertexPaletteRecord(void)
{
}

bool OFVertexPaletteRecord::read(std::istream &is, OFDatabase &oDB)
{
    static std::vector<char> tmpBuf;

    Int32 iFullLength;

    is.read(reinterpret_cast<char *>(&iFullLength), 4);

    iFullLength = osgBigEndianToHost(iFullLength);

    Int32          iRead = 0;

    Real64         tmpDouble[3];
    OFRecordHeader oRHeader;
    bool           rc = true;
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

        tmpInfo.uiType   = HasPos;
        tmpInfo.uiOffset = iRead + 8;

        tmpInfo.uiIdx[ColIdx     ] = -1;
        tmpInfo.uiIdx[NormIdx    ] = -1;
        tmpInfo.uiIdx[TexCoordIdx] = -1;

        UInt32 uiSize = 0;

        uiSize += Inherited::readVal(is, tmpInfo.uiColNameIdx);
        uiSize += Inherited::readVal(is, tmpInfo.iFlags      );

        uiSize += Inherited::readVal(is, tmpDouble[0]);
        uiSize += Inherited::readVal(is, tmpDouble[1]);
        uiSize += Inherited::readVal(is, tmpDouble[2]);

        tmpInfo.uiIdx[PosIdx] = vPositions.size();
        
        vPositions.push_back(Pnt3f(tmpDouble[0], tmpDouble[1], tmpDouble[2]));

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

UInt16 OFVertexPaletteRecord::getOpCode(void)
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

bool OFVertexPaletteRecord::VertexInfo::operator <(const UInt32 &uiOff) const
{
    return this->uiOffset < uiOff;
}

OFRecordFactoryBase::RegisterRecord OFVertexPaletteRecord::_regHelper(
    &OFVertexPaletteRecord::create,
    OFVertexPaletteRecord::OpCode);


//---------------------------------------------------------------------
// OFFaceRecord
//---------------------------------------------------------------------

OFRecordTransitPtr OFFaceRecord::create(const OFRecordHeader &oHeader)
{
    return OFRecordTransitPtr(new OFFaceRecord(oHeader));
}

OFFaceRecord::OFFaceRecord(const OFRecordHeader &oHeader) :
     Inherited(oHeader),
    _pVList   (NULL   )
{
}

OFFaceRecord::~OFFaceRecord(void)
{
    _pVList = NULL;
}

bool OFFaceRecord::read(std::istream &is, OFDatabase &oDB)
{
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
    Inherited::readVal  (is, iSurMatCode      );
    Inherited::readVal  (is, iFeatureId       );
    Inherited::readVal  (is, iIRMatCode       );
    Inherited::readVal  (is, uiTransparenct   );
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

bool OFFaceRecord::addChild (OFRecord *pChild)
{
    if(pChild == NULL)
    {
        return false;
    }

    switch(pChild->getOpCode())
    {
        case OFVertexListRecord::OpCode:
        {
            if(_pVList != NULL)
            {
                fprintf(stderr, "strange vlist already set\n");
            }
            else
            {
                _pVList = dynamic_cast<OFVertexListRecord *>(pChild);
            }
            
            break;
        }
       

        default:
        {
            fprintf(stderr, "OFFaceRecord : unknow child %hu\n",
                    pChild->getOpCode());
        }
    }

    return true;
}

UInt16 OFFaceRecord::getOpCode(void)
{
    return OpCode;
}

OFVertexListRecord *OFFaceRecord::getVertexList(void)
{
    return _pVList;
}

void OFFaceRecord::dump(UInt32 uiIndent)
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
    bool returnValue = (iTextureWhite == rhs.iTextureWhite &&
                        iTexIdx       == rhs.iTexIdx       &&
                        iMatIdx       == rhs.iMatIdx       &&
                        uiLightMode   == rhs.uiLightMode     );

    if(uiLightMode == 0 || uiLightMode == 2)
    {
        returnValue &= (uiPackedPrimCol == rhs.uiPackedPrimCol);
    }

    return returnValue;
}

UInt8 OFFaceRecord::getLightMode(void) const
{
    return uiLightMode;
}

Int16 OFFaceRecord::getTexIdx(void) const
{
    return iTexIdx;
}

OFRecordFactoryBase::RegisterRecord OFFaceRecord::_regHelper(
    &OFFaceRecord::create,
    OFFaceRecord::OpCode);


//---------------------------------------------------------------------
// OFVertexListRecord
//---------------------------------------------------------------------
 

OFRecordTransitPtr OFVertexListRecord::create(const OFRecordHeader &oHeader)
{
    return OFRecordTransitPtr(new OFVertexListRecord(oHeader));
}

OFVertexListRecord::OFVertexListRecord(const OFRecordHeader &oHeader) :
    Inherited(oHeader)
{
}

OFVertexListRecord::~OFVertexListRecord(void)
{
}

bool OFVertexListRecord::read(std::istream &is, OFDatabase &oDB)
{
    UInt32 uiListSize = (_sLength - 4) / 4;

    _vIndices.resize(uiListSize);

    for(UInt32 i = 0; i < uiListSize; ++i)
    {
        Inherited::readVal(is, _vIndices[i]);
    }

    return is.good();
}

UInt16 OFVertexListRecord::getOpCode(void)
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
// OFFaceContainerRecord
//---------------------------------------------------------------------

OFFaceContainer::OFFaceContainer(const OFRecordHeader &oHeader) :
     Inherited   (oHeader),
    _vFaces      (       )
{
}

OFFaceContainer::~OFFaceContainer(void)
{
    for(UInt32 i = 0; i < _vFaces.size(); ++i)
    {
        _vFaces[i] = NULL;
    }
    
    _vFaces.clear();
}

bool OFFaceContainer::addChild (OFRecord *pChild)
{    
    if(pChild == NULL)
    {
        return false;
    }

    bool returnValue = false;

    switch(pChild->getOpCode())
    {
        case OFFaceRecord::OpCode:
        {
            _vFaces.push_back(dynamic_cast<OFFaceRecord *>(pChild));

            returnValue = true;

            break;
        }

        default:
        {
            break;
        }
    }

    return returnValue;
}

void OFFaceContainer::groupFaces(
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

NodeTransitPtr OFFaceContainer::convertFaceGroup(
    std::vector<OFFaceRecord *> &vFaceGroup,
    OFDatabase                  &oDB)
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
   
    const OFVertexPaletteRecord *pVertexPal = oDB.getVertexPalette();

    UInt32 uiNumValid;

    GeoPnt3fPropertyUnrecPtr  pnts  = GeoPnt3fProperty ::create();
    GeoVec3fPropertyUnrecPtr  norms = NULL; 
    GeoVec2fPropertyUnrecPtr  tex   = NULL; 

    GeoPnt3fProperty::StoredFieldType *pPos  = pnts ->editFieldPtr();
    GeoVec3fProperty::StoredFieldType *pNorm = NULL; 
    GeoVec2fProperty::StoredFieldType *pTX   = NULL; 

    UInt16 uiVertexType;
    bool   bSingleIdx  = true;

    for(UInt32 i = 0; i < vFaceGroup.size(); ++i)
    {
        OFVertexListRecord *pVList = vFaceGroup[i]->getVertexList();
        
        if(pVList != NULL)
        {
            const std::vector<Int32> &vIndices = pVList->getIndices();

            uiNumValid = 0;

            for(UInt32 j = 0; j < vIndices.size(); ++j)
            {
                const VertexInfo *vInfo = 
                    pVertexPal->getVertexInfo(vIndices[j]);

                if(vInfo != NULL)
                {
                    // First Vertex
                    if(i == 0 && j == 0)
                    {
                        uiVertexType = vInfo->uiType;

                        if(uiVertexType & OFVertexPaletteRecord::HasNorm)
                        {
                            norms  = GeoVec3fProperty ::create();
                            pNorm  = norms->editFieldPtr();

                            nindex = GeoUInt32Property::create();
                            pNI    = nindex->editFieldPtr();
                        }

                        if(uiVertexType & OFVertexPaletteRecord::HasTexCoord)
                        {
                            tex    = GeoVec2fProperty ::create();
                            pTX    = tex ->editFieldPtr();

                            tindex = GeoUInt32Property::create();
                            pTI    = tindex->editFieldPtr();
                       }
                    }

                    if(uiVertexType != vInfo->uiType)
                    {
                        fprintf(stderr, "Found different vtypes\n");
                        break;
                    }

                    UInt32 uiPosIdx = 
                        vInfo->uiIdx[OFVertexPaletteRecord::PosIdx];

                    pPI->push_back(pPos->size());

                    pPos->push_back(pVertexPal->getPos(uiPosIdx));
                    
                    if(uiVertexType & OFVertexPaletteRecord::HasNorm)
                    {
                        UInt32 uiNormIdx = 
                            vInfo->uiIdx[OFVertexPaletteRecord::NormIdx];

                        pNI->push_back(pNorm->size());
                        
                        pNorm->push_back(pVertexPal->getNormal(uiNormIdx));

                        if(uiNormIdx != uiPosIdx)
                        {
                            bSingleIdx = false;
                        }
                    }

                    if(uiVertexType & OFVertexPaletteRecord::HasTexCoord)
                    {
                        UInt32 uiTXIdx = 
                            vInfo->uiIdx[OFVertexPaletteRecord::TexCoordIdx];

                        pTI->push_back(pTX->size());
                        
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

    pGeo->setTypes   (types                           );
    pGeo->setLengths (lens                            );

    const OFTexturePaletteRecord *pTexRec   = NULL;
          ChunkMaterialUnrecPtr   pChunkMat = ChunkMaterial::create();
    
    if(vFaceGroup[0]->getLightMode() == 0 || vFaceGroup[0]->getLightMode() == 2)
    {
        MaterialChunkUnrecPtr pMatChunk = MaterialChunk::create();

        Color4f oCol(1.f, 1.f, 1.f, 1.f);

        pMatChunk->setDiffuse(oCol);

        pChunkMat->addChunk(pMatChunk);
    }
    else
    {
        fprintf(stderr, "Unsupported lightmode\n");
    }

    if(vFaceGroup[0]->getLightMode() == 2 || vFaceGroup[0]->getLightMode() == 3)
    {
//        fprintf(stderr, "%p %p\n", pNI, pNorm);

        if(pNI == NULL && pNorm == NULL)
        {
            calcVertexNormals(pGeo);
        }
    }

    if(vFaceGroup[0]->getTexIdx() != -1)
    {
        pTexRec = oDB.getTexRecord(vFaceGroup[0]->getTexIdx());
        
        if(pTexRec != NULL)
        {
            TextureObjChunk *pTexObj = pTexRec->getTexObj();

            if(pTexObj != NULL)
                pChunkMat->addChunk(pTexObj);
        }
        else
        {
            fprintf(stderr, "error no texrec for index %d\n",
                    vFaceGroup[0]->getTexIdx());
        }
    }

    pGeo->setMaterial(pChunkMat);

    return returnValue;
}

NodeTransitPtr OFFaceContainer::convertFaces(OFDatabase &oDB)
{
    NodeTransitPtr returnValue(NULL);

    std::vector< std::vector<OFFaceRecord *> > vFaceGroups;

    groupFaces(vFaceGroups);

//    fprintf(stderr, "Got %d facegroups\n", vFaceGroups.size());

    if(vFaceGroups.size() == 1)
    {
        returnValue = convertFaceGroup(vFaceGroups[0], oDB);
    }
    else if(vFaceGroups.size() > 1)
    {
        returnValue = Node::create();
        returnValue->setCore(Group::create());

        for(UInt32 i = 0; i < vFaceGroups.size(); ++i)
        {
            returnValue->addChild(convertFaceGroup(vFaceGroups[i], oDB));
        }
    }

    return returnValue;
}

void OFFaceContainer::dump(UInt32 uiIndent)
{
    indentLog(uiIndent, PLOG);
    PLOG << "#NumFaces : " << _vFaces.size() << std::endl;
    
    indentLog(uiIndent, PLOG);
    PLOG << "[" << std::endl;

#if 1
    uiIndent += 2;

    for(UInt32 i = 0; i < _vFaces.size(); ++i)
    {
        _vFaces[i]->dump(uiIndent);
    }

    uiIndent -= 2;
#endif

    indentLog(uiIndent, PLOG);
    PLOG << "]" << std::endl;
}

//---------------------------------------------------------------------
// OFGroupingRecord
//---------------------------------------------------------------------


OFGroupingRecord::OFGroupingRecord(const OFRecordHeader &oHeader) :
     Inherited(oHeader),
    _vChildren(       )
{
}

OFGroupingRecord::~OFGroupingRecord(void)
{
    for(UInt32 i = 0; i < _vChildren.size(); ++i)
    {
        _vChildren[i] = NULL;
    }
    
    _vChildren.clear();
}

bool OFGroupingRecord::addChild (OFRecord *pChild)
{    
    if(pChild == NULL)
    {
        return false;
    }

    bool rc = Inherited::addChild(pChild);

    if(rc == false)
    {
        _vChildren.push_back(pChild);
    }

    return true;
}

void OFGroupingRecord::dump(UInt32 uiIndent)
{
    indentLog(uiIndent, PLOG);
    PLOG << "#NumChildren : " << _vChildren.size() << std::endl;
    
    indentLog(uiIndent, PLOG);
    PLOG << "[" << std::endl;

    uiIndent += 2;

    for(UInt32 i = 0; i < _vChildren.size(); ++i)
    {
        _vChildren[i]->dump(uiIndent);
    }

    uiIndent -= 2;

    indentLog(uiIndent, PLOG);
    PLOG << "]" << std::endl;

    Inherited::dump(uiIndent);
}

NodeTransitPtr OFGroupingRecord::convertToNode(OFDatabase &oDB)
{
    NodeTransitPtr returnValue(NULL);

    if(_vChildren.size() != 0 || _vFaces.size() != 0)
    {
        returnValue = Node::create();

        returnValue->setCore(Group::create());
    }
    else
    {
        return returnValue;
    }
    
    if(_vChildren.size() != 0)
    {
        NodeTransitPtr pChild;

        for(UInt32 i = 0; i < _vChildren.size(); ++i)
        {
            pChild = _vChildren[i]->convertToNode(oDB);

            if(pChild != NULL)
            {
                returnValue->addChild(pChild);
            }
        }
    }

    if(_vFaces.size() != 0)
    {
        returnValue->addChild(convertFaces(oDB));
    }

    return returnValue;
}


//---------------------------------------------------------------------
// OFGroupRecord
//---------------------------------------------------------------------

OFRecordTransitPtr OFGroupRecord::create(const OFRecordHeader &oHeader)
{
    return OFRecordTransitPtr(new OFGroupRecord(oHeader));
}

OFGroupRecord::OFGroupRecord(const OFRecordHeader &oHeader) :
    Inherited(oHeader)
{
}

OFGroupRecord::~OFGroupRecord(void)
{
}

bool OFGroupRecord::read(std::istream &is, OFDatabase &oDB)
{
    return Inherited::read(is, oDB);
}

UInt16 OFGroupRecord::getOpCode(void)
{
    return OpCode;
}

void OFGroupRecord::dump(UInt32 uiIndent)
{
    indentLog(uiIndent, PLOG);
    PLOG << "GroupRecord" << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "{" << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "}" << std::endl;

    Inherited::dump(uiIndent);
}

OFRecordFactoryBase::RegisterRecord OFGroupRecord::_regHelper(
    &OFGroupRecord::create,
    OFGroupRecord::OpCode);


//---------------------------------------------------------------------
// OFLODRecord
//---------------------------------------------------------------------

OFRecordTransitPtr OFLODRecord::create(const OFRecordHeader &oHeader)
{
    return OFRecordTransitPtr(new OFLODRecord(oHeader));
}

OFLODRecord::OFLODRecord(const OFRecordHeader &oHeader) :
    Inherited(oHeader)
{
}

OFLODRecord::~OFLODRecord(void)
{
}

bool OFLODRecord::read(std::istream &is, OFDatabase &oDB)
{
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
        Inherited::readVal  (is, rSigSize    );

    return is.good();
}

UInt16 OFLODRecord::getOpCode(void)
{
    return OpCode;
}

void OFLODRecord::dump(UInt32 uiIndent)
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

NodeTransitPtr OFLODRecord::convertToNode(OFDatabase &oDB)
{
    NodeTransitPtr returnValue(NULL);

    if(_vChildren.size() != 0 || _vFaces.size() != 0)
    {
        returnValue            = Node::create();
        RangeLODUnrecPtr pCore = RangeLOD::create();

        returnValue->setCore(pCore);

        pCore->setSwitchIn (this->getSwitchIn ());
        pCore->setSwitchOut(this->getSwitchOut());

        pCore->setCenter   (this->getCenter   ());
    }
    else
    {
        return returnValue;
    }

    if(_vChildren.size() != 0)
    {
        NodeTransitPtr pChild;

        for(UInt32 i = 0; i < _vChildren.size(); ++i)
        {
            pChild = _vChildren[i]->convertToNode(oDB);

            if(pChild != NULL)
            {
                returnValue->addChild(pChild);
            }
        }
    }

    if(_vFaces.size() != 0)
    {
        returnValue->addChild(convertFaces(oDB));
    }

    return returnValue;
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

OFRecordFactoryBase::RegisterRecord OFLODRecord::_regHelper(
    &OFLODRecord::create,
    OFLODRecord::OpCode);


//---------------------------------------------------------------------
// OFSwitchRecord
//---------------------------------------------------------------------

OFRecordTransitPtr OFSwitchRecord::create(const OFRecordHeader &oHeader)
{
    return OFRecordTransitPtr(new OFSwitchRecord(oHeader));
}

OFSwitchRecord::OFSwitchRecord(const OFRecordHeader &oHeader) :
    Inherited(oHeader)
{
}

OFSwitchRecord::~OFSwitchRecord(void)
{
}

bool OFSwitchRecord::read(std::istream &is, OFDatabase &oDB)
{
    Inherited::readChar8(is, szASCIIID, 8);
    Inherited::readVal  (is, szPad1      );
    Inherited::readVal  (is, iCurrMask   );
    Inherited::readVal  (is, iNumMask    );
    Inherited::readVal  (is, iMaskWords  );

    vMask.resize(iNumMask);

    for(UInt32 i = 0; i < iNumMask; ++i)
    {
        vMask[i].resize(iMaskWords);
    }

    for(UInt32 i = 0; i < iNumMask; ++i)
    {
        for(UInt32 j = 0; j < iMaskWords; ++j)
        {
            Inherited::readVal(is, vMask[i][j]);
        }
    }

    return is.good();
}

UInt16 OFSwitchRecord::getOpCode(void)
{
    return OpCode;
}


void OFSwitchRecord::dump(UInt32 uiIndent)
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

    for(UInt32 i = 0; i < iNumMask; ++i)
    {
        indentLog(uiIndent, PLOG);
        PLOG << "Mask[" << i << "] : ";
        
        for(UInt32 j = 0; j < iMaskWords; ++j)
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

NodeTransitPtr OFSwitchRecord::convertToNode(OFDatabase &oDB)
{
    NodeTransitPtr returnValue(NULL);

    if(_vChildren.size() != 0 || _vFaces.size() != 0)
    {
        returnValue         = Node ::create();
        GroupUnrecPtr pCore = Group::create();

        returnValue->setCore(pCore);

//        pCore->setSwitchIn (this->getSwitchIn ());
//        pCore->setSwitchOut(this->getSwitchOut());

//        pCore->setCenter   (this->getCenter   ());
    }
    else
    {
        return returnValue;
    }

    if(_vChildren.size() != 0)
    {
        NodeTransitPtr pChild;

        for(UInt32 i = 0; i < _vChildren.size(); ++i)
        {
            pChild = _vChildren[i]->convertToNode(oDB);

            if(pChild != NULL)
            {
//                returnValue->addChild(pChild);
            }
        }
    }

    if(_vFaces.size() != 0)
    {
        returnValue->addChild(convertFaces(oDB));
    }

    return returnValue;
}

OFRecordFactoryBase::RegisterRecord OFSwitchRecord::_regHelper(
    &OFSwitchRecord::create,
    OFSwitchRecord::OpCode);



//---------------------------------------------------------------------
// OFObjectRecord
//---------------------------------------------------------------------

OFRecordTransitPtr OFObjectRecord::create(const OFRecordHeader &oHeader)
{
    return OFRecordTransitPtr(new OFObjectRecord(oHeader));
}

OFObjectRecord::OFObjectRecord(const OFRecordHeader &oHeader) :
     Inherited(oHeader),
    _vChildren(       )
{
}

OFObjectRecord::~OFObjectRecord(void)
{
    for(UInt32 i = 0; i < _vChildren.size(); ++i)
    {
        _vChildren[i] = NULL;
    }

    _vChildren.clear();
}

bool OFObjectRecord::addChild (OFRecord *pChild)
{    
    if(pChild == NULL)
    {
        return false;
    }

    bool rc = Inherited::addChild(pChild);

    if(rc == false)
    {
        _vChildren.push_back(pChild);
    }

    return true;
}

void OFObjectRecord::dump(UInt32 uiIndent)
{
    indentLog(uiIndent, PLOG);
    PLOG << "ObjectRecord" << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "{" << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "}" << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "#NumChildren : " << _vChildren.size() << std::endl;
    
    indentLog(uiIndent, PLOG);
    PLOG << "[" << std::endl;

    uiIndent += 2;

    for(UInt32 i = 0; i < _vChildren.size(); ++i)
    {
        _vChildren[i]->dump(uiIndent);
    }

    uiIndent -= 2;

    indentLog(uiIndent, PLOG);
    PLOG << "]" << std::endl;


    Inherited::dump(uiIndent);
}

bool OFObjectRecord::read(std::istream &is, OFDatabase &oDB)
{
    return Inherited::read(is, oDB);
}


UInt16 OFObjectRecord::getOpCode(void)
{
    return OpCode;
}

NodeTransitPtr OFObjectRecord::convertToNode(OFDatabase &oDB)
{
    return Inherited::convertFaces(oDB);
}

OFRecordFactoryBase::RegisterRecord OFObjectRecord::_regHelper(
    &OFObjectRecord::create,
    OFObjectRecord::OpCode);


//---------------------------------------------------------------------
// OFExternalReferenceRecord
//---------------------------------------------------------------------

OFRecordTransitPtr OFExternalReferenceRecord::create(
    const OFRecordHeader &oHeader)
{
    return OFRecordTransitPtr(new OFExternalReferenceRecord(oHeader));
}

OFExternalReferenceRecord::OFExternalReferenceRecord(
    const OFRecordHeader &oHeader) :

    Inherited(oHeader)
{
}

OFExternalReferenceRecord::~OFExternalReferenceRecord(void)
{
}

bool OFExternalReferenceRecord::read(std::istream &is, OFDatabase &oDB)
{
    Inherited::readChar8(is, szFilename, 200);
    Inherited::readVal  (is, iPad1          );
    Inherited::readVal  (is, iFlags         );
    Inherited::readVal  (is, iViewAsBBox    );
    Inherited::readVal  (is, iPad2          );

    return is.good();
}

UInt16 OFExternalReferenceRecord::getOpCode(void)
{
    return OpCode;
}

void OFExternalReferenceRecord::dump(UInt32 uiIndent)
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
}

NodeTransitPtr OFExternalReferenceRecord::convertToNode(OFDatabase &oDB)
{
    NodeTransitPtr returnValue(NULL);

    PathHandler *pHandler = SceneFileHandler::the()->getPathHandler();

    if(pHandler != NULL)
    {
        std::string szFilenameResolved = pHandler->findFile(szFilename);

        if(szFilenameResolved.empty() == true)
        {
            fprintf(stderr, "Could not find data file %s\n",
                    szFilename);

            return returnValue;
        }

        pHandler->pushState();

        pHandler->setBaseFile(szFilenameResolved.c_str());

        std::ifstream is;

        is.open(szFilenameResolved.c_str(), std::ios::binary);

        returnValue = 
            OpenFlightSceneFileType::the().read(is,
                                                szFilenameResolved.c_str());
        
        pHandler->popState();

    }
    else
    {
        fprintf(stderr, "No handler\n");
    }

    return returnValue;
}

OFRecordFactoryBase::RegisterRecord OFExternalReferenceRecord::_regHelper(
    &OFExternalReferenceRecord::create,
    OFExternalReferenceRecord::OpCode);



OSG_END_NAMESPACE
