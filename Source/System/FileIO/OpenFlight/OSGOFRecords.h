/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                Copyright (C) 2008 by the OpenSG Forum                     *
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

#ifndef _OSGOFRECORDS_H_
#define _OSGOFRECORDS_H_

#include "boost/function.hpp"

#include "OSGFileIODef.h"
#include "OSGBaseTypes.h"
#include "OSGBaseFunctions.h"
#include "OSGSingletonHolder.h"
#include "OSGNode.h"
#include "OSGTextureObjChunk.h"
#include "OSGMaterialChunk.h"
#include "OSGMemoryObject.h"

#include "OSGTypedGeoIntegralProperty.h"
#include "OSGTypedGeoVectorProperty.h"

#include <map>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

class OFRecord;
class OFDatabase;

class Geometry;

/*! \brief General VRML Node Desc
    \ingroup GrpFileIOOpenFlight
    \nohierarchy
 */ 

struct OFRecordHeader
{
    UInt16 sOpCode;
    UInt16 sLength;

    bool read(std::istream &is)
    {
        is.read(reinterpret_cast<char *>(&sOpCode), 2);
        is.read(reinterpret_cast<char *>(&sLength), 2);

        sOpCode = osgNetToHost(sOpCode);
        sLength = osgNetToHost(sLength);

//        fprintf(stderr, "opcode %hu, length %hu\n", sOpCode, sLength);

        return is.good();
    }
};

/*! \ingroup GrpFileIOOpenFlight
 */

typedef TransitPtr<OFRecord> OFRecordTransitPtr;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpFileIOOpenFlight
    \nohierarchy
 */

class OSG_FILEIO_DLLMAPPING OFRecordFactoryBase
{
    /*==========================  PUBLIC  =================================*/

  public :

    typedef boost::function<
        OFRecordTransitPtr (const OFRecordHeader &)> CreateRecord;

    /*! \nohierarchy
     */
    class OSG_FILEIO_DLLMAPPING RegisterRecord
    {
      public:

        RegisterRecord(CreateRecord fCreate,
                       UInt16       sRecordOpCode);
    };

    /*---------------------------------------------------------------------*/
    /*! \name                   Class Get                                  */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Field                                    */
    /*! \{                                                                 */

    void registerRecord(CreateRecord fRecord,
                        UInt16       sRecordOpCode);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Prototypes                                 */
    /*! \{                                                                 */

    OFRecordTransitPtr createRecord(const OFRecordHeader &oHeader);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Node                                    */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      FieldValue                              */
    /*! \{                                                                 */


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    template <class SingletonT>
    friend class SingletonHolder;

    typedef std::map<UInt16,
                     CreateRecord> NameRecordCreateMap;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    OFRecordFactoryBase(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~OFRecordFactoryBase(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    NameRecordCreateMap _mRegisteredRecords;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    /*!\brief prohibit default function (move to 'public' if needed) */
    OFRecordFactoryBase(const OFRecordFactoryBase &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const OFRecordFactoryBase &source);
};

/*! \ingroup GrpFileIOOpenFlight
 */

typedef SingletonHolder<OFRecordFactoryBase> OFRecordFactory;

// OpCode without object

static const UInt16 OFPushLevelOC    = 10;
static const UInt16 OFPopLevelOC     = 11;
static const UInt16 OFContinuationOC = 23;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpFileIOOpenFlight
    \nohierarchy
 */

class OSG_FILEIO_DLLMAPPING OFRecord : public MemoryObject
{
  protected:

    typedef MemoryObject Inherited;

    /*---------------------------------------------------------------------*/

    UInt16 _sLength;

    /*---------------------------------------------------------------------*/

    void readChar8 (std::istream &is, Char8  *cVal, UInt32 iSize);

    /*---------------------------------------------------------------------*/

    template<class ValueT>
    UInt32 readVal(std::istream &is,  ValueT &val);

    /*---------------------------------------------------------------------*/

    const Char8 *findDesc(UInt16 sOpCode);

    /*---------------------------------------------------------------------*/

             OFRecord(const OFRecordHeader &oHeader);

    virtual ~OFRecord(void);

  public:

    /*---------------------------------------------------------------------*/

    virtual bool read        (std::istream &is,
                              OFDatabase   &oDB     );
    virtual bool readContinue(std::istream &is,
                              OFDatabase   &oDB,
                              UInt16        uiLength);

    /*---------------------------------------------------------------------*/

    virtual bool   addChild (OFRecord *pChild);
    virtual UInt16 getOpCode(void            ) = 0;

    /*---------------------------------------------------------------------*/

    virtual NodeTransitPtr convertToNode(OFDatabase &oDB);

    /*---------------------------------------------------------------------*/

    virtual void dump(UInt32 uiIndent);
};

/*! \ingroup GrpFileIOOpenFlight
 */

typedef RefCountPtr<OFRecord, MemObjRefCountPolicy> OFRecordRCPtr;

class OFVertexPaletteRecord;
class OFTexturePaletteRecord;
class OFMaterialPaletteRecord;

/*! \ingroup GrpFileIOOpenFlight
 */
typedef RefCountPtr<OFTexturePaletteRecord,
                    MemObjRefCountPolicy    > OFTexturePaletteRecordRCPtr;

/*! \ingroup GrpFileIOOpenFlight
 */
typedef RefCountPtr<OFVertexPaletteRecord,
                    MemObjRefCountPolicy    > OFVertexPaletteRecordRCPtr;

/*! \ingroup GrpFileIOOpenFlight
 */
typedef RefCountPtr<OFMaterialPaletteRecord,
                    MemObjRefCountPolicy    > OFMaterialPaletteRecordRCPtr;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpFileIOOpenFlight
    \nohierarchy
 */

class OSG_FILEIO_DLLMAPPING OFVertexPalette : public MemoryObject
{
  protected:

    typedef MemoryObject Inherited;

    /*---------------------------------------------------------------------*/

    OFVertexPaletteRecordRCPtr _pVertexPalette;

    /*---------------------------------------------------------------------*/

    virtual ~OFVertexPalette(void);

  public:

    OFVertexPalette(void);

    /*---------------------------------------------------------------------*/

          void                   addRecord(OFVertexPaletteRecord *pVertexPal);
    const OFVertexPaletteRecord *getRecord(void                             );

    /*---------------------------------------------------------------------*/

    void dump(UInt32 uiIndent);
};

/*! \ingroup GrpFileIOOpenFlight
 */
typedef RefCountPtr<OFVertexPalette,
                    MemObjRefCountPolicy> OFVertexPaletteRCPtr;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpFileIOOpenFlight
    \nohierarchy
 */

class OSG_FILEIO_DLLMAPPING OFTexturePalette : public MemoryObject
{
  protected:

    typedef MemoryObject Inherited;

    /*---------------------------------------------------------------------*/

    typedef std::map<Int32,
                     OFTexturePaletteRecordRCPtr>           TextureStore;
    typedef std::map<Int32,
                     OFTexturePaletteRecordRCPtr>::iterator TextureStoreIt;

    /*---------------------------------------------------------------------*/

    TextureStore _mTextures;

    /*---------------------------------------------------------------------*/

    virtual ~OFTexturePalette(void);

  public:

    OFTexturePalette(void);

    /*---------------------------------------------------------------------*/

          void                    addRecord(OFTexturePaletteRecord *pTex);
    const OFTexturePaletteRecord *getRecord(Int32                   uiId);

    /*---------------------------------------------------------------------*/

    void dump(UInt32 uiIndent);
};

/*! \ingroup GrpFileIOOpenFlight
 */
typedef RefCountPtr<OFTexturePalette,
                    MemObjRefCountPolicy> OFTexturePaletteRCPtr;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpFileIOOpenFlight
    \nohierarchy
 */

class OSG_FILEIO_DLLMAPPING OFMaterialPalette : public MemoryObject
{
  protected:
    typedef MemoryObject Inherited;

    /*---------------------------------------------------------------------*/

    typedef std::map<Int32,
                     OFMaterialPaletteRecordRCPtr>           MaterialStore;
    typedef std::map<Int32,
                     OFMaterialPaletteRecordRCPtr>::iterator MaterialStoreIt;

    /*---------------------------------------------------------------------*/

    MaterialStore _mMaterials;

    /*---------------------------------------------------------------------*/

    virtual ~OFMaterialPalette(void);

  public:

    typedef RefCountPtr<OFMaterialPalette,
                        MemObjRefCountPolicy> ObjRCPtr;
    typedef TransitPtr <OFMaterialPalette   > ObjTransitPtr;

    OFMaterialPalette(void);

    /*---------------------------------------------------------------------*/

          void                     addRecord(OFMaterialPaletteRecord *pMat);
    const OFMaterialPaletteRecord *getRecord(Int32                    uiId);

    /*---------------------------------------------------------------------*/

    void dump(UInt32 uiIndent);
};

/*! \ingroup GrpFileIOOpenFlight
 */
typedef OFMaterialPalette::ObjRCPtr      OFMaterialPaletteRCPtr;
/*! \ingroup GrpFileIOOpenFlight
 */
typedef OFMaterialPalette::ObjTransitPtr OFMaterialPaletteTransitPtr;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpFileIOOpenFlight
    \nohierarchy
 */

class OSG_FILEIO_DLLMAPPING OFHeaderRecord : public OFRecord
{
    typedef OFRecord Inherited;

    friend class OFDatabase;

    /*---------------------------------------------------------------------*/

    std::vector<OFRecordRCPtr> _vChildren;

    OFVertexPaletteRCPtr       _pVertexPal;
    OFTexturePaletteRCPtr      _pTexturePal;
    OFMaterialPaletteRCPtr     _pMaterialPal;

    /*---------------------------------------------------------------------*/

    OFHeaderRecord(const OFRecordHeader &oHeader);

    virtual ~OFHeaderRecord(void);

  public:

    static const UInt16 OpCode = 1;

    /*---------------------------------------------------------------------*/

    virtual bool read(std::istream &is, OFDatabase &oDB);

    /*---------------------------------------------------------------------*/

    virtual bool addChild (OFRecord *pChild);

    /*---------------------------------------------------------------------*/

    virtual UInt16 getOpCode(void);

    /*---------------------------------------------------------------------*/

    virtual NodeTransitPtr convertToNode(OFDatabase &oDB);

    /*---------------------------------------------------------------------*/

    virtual void dump(UInt32 uiIndent);

    /*---------------------------------------------------------------------*/

    const OFVertexPaletteRecord   *getVertexPalette(void        );
    const OFTexturePaletteRecord  *getTexRecord    (UInt32 uiIdx);
    const OFMaterialPaletteRecord *getMatRecord    (UInt32 uiIdx);
};

/*! \ingroup GrpFileIOOpenFlight
 */
typedef RefCountPtr<OFHeaderRecord,
                    MemObjRefCountPolicy> OFHeaderRecordRCPtr;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpFileIOOpenFlight
    \nohierarchy
 */

class OSG_FILEIO_DLLMAPPING OFUnknownRecord : public OFRecord
{
  protected:

    typedef OFRecord Inherited;

    /*---------------------------------------------------------------------*/

    UInt16                     _sOpCode;
    std::vector<OFRecordRCPtr> _vChildren;

    /*---------------------------------------------------------------------*/

    OFUnknownRecord(const OFRecordHeader &oHeader);

    virtual ~OFUnknownRecord(void);

    /*---------------------------------------------------------------------*/

    friend class OFRecordFactoryBase;

  public:

    virtual bool read(std::istream &is, OFDatabase &oDB);

    /*---------------------------------------------------------------------*/

    virtual bool addChild(OFRecord *pChild);

    /*---------------------------------------------------------------------*/

    virtual UInt16 getOpCode(void);

    virtual NodeTransitPtr convertToNode(OFDatabase &oDB);

    /*---------------------------------------------------------------------*/

    virtual void dump(UInt32 uiIndent);
};

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpFileIOOpenFlight
    \nohierarchy
 */

class OSG_FILEIO_DLLMAPPING OFTexturePaletteRecord : public OFRecord
{
  protected:

    typedef OFRecord Inherited;

    /*---------------------------------------------------------------------*/

    static OFRecordFactoryBase::RegisterRecord _regHelper;

    /*---------------------------------------------------------------------*/

    Char8 szFilename[200]; // 4   200 File name of texture pattern
    Int32 iPatternIdx;     // 204 4   Texture pattern index
    Int32 iPatternX;       // 208 4*2 Location in the texture palette (x, y)
    Int32 iPatternY;

    /*---------------------------------------------------------------------*/

    TextureObjChunkUnrecPtr pTexObj;

    /*---------------------------------------------------------------------*/

    OFTexturePaletteRecord(const OFRecordHeader &oHeader);

    virtual ~OFTexturePaletteRecord(void);

  public:

    static const UInt16 OpCode = 64;

    static OFRecordTransitPtr create(const OFRecordHeader &oHeader);

    /*---------------------------------------------------------------------*/

    virtual bool read(std::istream &is, OFDatabase &oDB);

    /*---------------------------------------------------------------------*/

    virtual UInt16 getOpCode(void);

    /*---------------------------------------------------------------------*/

    virtual void dump(UInt32 uiIndent);

    /*---------------------------------------------------------------------*/

    Int32            getPatternIdx(void);

    TextureObjChunk *getTexObj    (void) const;
};

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpFileIOOpenFlight
    \nohierarchy
 */

class OSG_FILEIO_DLLMAPPING OFVertexPaletteRecord : public OFRecord
{
  public:

    /*---------------------------------------------------------------------*/

    /*! \nohierarchy
     */
    struct VertexInfo
    {
        UInt16 uiColNameIdx; // 4  2   Color name index
        Int16  iFlags;       // 6  2   Flags (bits, from left to right)
                             // 0 = Start hard edge
                             // 1 = Normal frozen
                             // 2 = No color
                             // 3 = Packed color
                             // 4-15 = Spare

        Int32   iPackedCol;  // 32 4   Packed color (a, b, g, r) - always
                             // specified when the vertex has color
        UInt32  iColIdx;     // 36 4   Vertex color index - valid only if vertex
                             // has color and  Packed color flag is not set
        Int32   iPad1;       // 52 4 Reserved

        UInt16  uiType;
        UInt32  uiOffset;
        Int32   uiIdx[4];

        bool operator <(const UInt32      uiOff) const;
        bool operator <(const VertexInfo &vInfo) const;
    };

    /*---------------------------------------------------------------------*/

    static const UInt8 PosIdx      = 0;
    static const UInt8 ColIdx      = 1;
    static const UInt8 NormIdx     = 2;
    static const UInt8 TexCoordIdx = 3;

    static const UInt8 HasPos      = 0x01;
    static const UInt8 HasCol      = 0x02;
    static const UInt8 HasNorm     = 0x04;
    static const UInt8 HasTexCoord = 0x08;

  protected:

    typedef OFRecord Inherited;

    /*---------------------------------------------------------------------*/

    static OFRecordFactoryBase::RegisterRecord _regHelper;

    /*---------------------------------------------------------------------*/

    std::vector<Pnt3f>      vPositions;
    std::vector<Vec3f>      vNormals;
    std::vector<Vec2f>      vTexCoords;
    std::vector<VertexInfo> vVertexInfo;

    /*---------------------------------------------------------------------*/

    OFVertexPaletteRecord(const OFRecordHeader &oHeader);

    virtual ~OFVertexPaletteRecord(void);

  public:

    static const UInt16 OpCode  = 67;

    /*---------------------------------------------------------------------*/

    static OFRecordTransitPtr create(const OFRecordHeader &oHeader);

    virtual bool read(std::istream &is, OFDatabase &oDB);

    /*---------------------------------------------------------------------*/

    virtual UInt16 getOpCode(void);

    /*---------------------------------------------------------------------*/

    const VertexInfo *getVertexInfo(UInt32 uiOffset) const;

    const Pnt3f      &getPos       (UInt32 uiIdx   ) const;
    const Vec3f      &getNormal    (UInt32 uiIdx   ) const;
    const Vec2f      &getTexCoord  (UInt32 uiIdx   ) const;
};

bool operator <(const UInt32                             uiOff,
                const OFVertexPaletteRecord::VertexInfo &vInfo );

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpFileIOOpenFlight
    \nohierarchy
 */

class OSG_FILEIO_DLLMAPPING OFMaterialPaletteRecord : public OFRecord
{
 protected:

    typedef OFRecord Inherited;

    /*---------------------------------------------------------------------*/

    static OFRecordFactoryBase::RegisterRecord _regHelper;

    /*---------------------------------------------------------------------*/

    Int32   iMaterialIdx;       //   4  4  Material index
    Char8   szMaterialName[12]; //   8 12  Material name
    Int32   iFlags;             //  20  4  Flags
                                // 0 = Material is used
                                // 1-31 = Spare
    Color4f colAmbient;         //  24 4*3 Ambient component of material (r, g, b)
    Color4f colDiffuse;         //  36 4*3 Diffuse component of material (r, g, b)
    Color4f colSpecular;        //  48 4*3 Specular component of material (r, g, b)
    Color4f colEmissive;        //  60 4*3 Emissive component of material (r, g, b)
    Real32  fShininess;         //  72 4   Shininess - (0.0-128.0)
    Real32  fAlpha;             //  76 4   Alpha - (0.0-1.0) where 1.0 is opaque
    Int32   iPad;               //  80 4   Reserved

    /*---------------------------------------------------------------------*/

             OFMaterialPaletteRecord(const OFRecordHeader &oHeader);

    virtual ~OFMaterialPaletteRecord(void                         );

  public:

    static const UInt16 OpCode = 113;

    static OFRecordTransitPtr create(const OFRecordHeader &oHeader);

    static const Int32  FlagMaterialUsed = 0x80000000;

    /*---------------------------------------------------------------------*/

    virtual bool read(std::istream &is, OFDatabase &oDB);

    /*---------------------------------------------------------------------*/

    virtual UInt16 getOpCode(void);

    /*---------------------------------------------------------------------*/

    virtual void dump(UInt32 uiIndent);

    /*---------------------------------------------------------------------*/

          Int32    getMaterialIdx(void);

    const Color4f &getAmbient    (void) const;
    const Color4f &getDiffuse    (void) const;
    const Color4f &getSpecular   (void) const;
    const Color4f &getEmissive   (void) const;
          Real32   getShininess  (void) const;
          Real32   getAlpha      (void) const;
};

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

class OFLocalVertexPoolRecord;

/*! \ingroup GrpFileIOOpenFlight
    \nohierarchy
 */

class OSG_FILEIO_DLLMAPPING OFMeshPrimitiveRecord : public OFRecord
{
  public:
    typedef std::vector<UInt32> IndexStore;

  protected:
    typedef OFRecord            Inherited;

    static OFRecordFactoryBase::RegisterRecord _regHelper;

    /*---------------------------------------------------------------------*/

    Int16 uiPrimType;        //  4 2 Primitive Type - specifies how the vertices
                             //     of the primitive are interpreted
                             // 1 = Triangle Strip
                             // 2 = Triangle Fan
                             // 3 = Quadrilateral Strip
                             // 4 = Indexed Polygon
    UInt16 uiIndexSize;      //  6 2 Index Size - specifies the length (in bytes)
                             //      of each of the vertex indices that follow -
                             //      will be either 1, 2, or 4
    UInt32 uiVertexCount;    //  8 4 Vertex Count- number of vertices contained
                             //      in this primitive.

    IndexStore _vIndices;

    /*---------------------------------------------------------------------*/

    friend class OFLocalVertexPoolRecord;

    /*---------------------------------------------------------------------*/

             OFMeshPrimitiveRecord(const OFRecordHeader &oHeader);

    virtual ~OFMeshPrimitiveRecord(void                         );

  public:
    typedef TransitPtr <OFMeshPrimitiveRecord >   ObjTransitPtr;
    typedef RefCountPtr<OFMeshPrimitiveRecord,
                        MemObjRefCountPolicy  >   ObjRCPtr;

    static const UInt16 OpCode = 86;

    static OFRecordTransitPtr create(const OFRecordHeader &oHeader);

    static const UInt16 PTTriStrip  = 1;
    static const UInt16 PTTriFan    = 2;
    static const UInt16 PTQuadStrip = 3;
    static const UInt16 PTPolygon   = 4;

    /*---------------------------------------------------------------------*/

    virtual bool read        (std::istream &is,
                              OFDatabase   &oDB     );
    virtual bool readContinue(std::istream &is,
                              OFDatabase   &oDB,
                              UInt16        uiLength);

    /*---------------------------------------------------------------------*/

    virtual UInt16 getOpCode(void);

    /*---------------------------------------------------------------------*/

    virtual void dump(UInt32 uiIndent);

    /*---------------------------------------------------------------------*/

          IndexStore &editIndices(void);
    const IndexStore &getIndices (void) const;
};

/*! \ingroup GrpFileIOOpenFlight
 */
typedef OFMeshPrimitiveRecord::ObjTransitPtr OFMeshPrimitiveRecordTransitPtr;
/*! \ingroup GrpFileIOOpenFlight
 */
typedef OFMeshPrimitiveRecord::ObjRCPtr      OFMeshPrimitiveRecordRCPtr;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpFileIOOpenFlight
    \nohierarchy
 */

class OSG_FILEIO_DLLMAPPING OFLocalVertexPoolRecord : public OFRecord
{
  protected:
    typedef OFRecord Inherited;

    static OFRecordFactoryBase::RegisterRecord _regHelper;

    /*---------------------------------------------------------------------*/

    UInt32  uiNumVerts;         //  4 4 Number of vertices - number of vertices in the local vertex pool
    UInt32  uiAttribMask;       //  8 4 Attribute mask - Bit mask indicating what kind of vertex infor-
                                //      mation is specified for each vertex in the local vertex pool. Bits
                                //      are ordered from left to right as follows:
                                // Bit #    Description
                                //   0     Has Position - if set, data for each vertex in will include
                                //         x, y, and z coordinates (3 doubles)
                                //   1     Has Color Index - if set, data for each vertex will in-
                                //         clude a color value that specifies a color table index as
                                //         well as an alpha value
                                //   2     Has RGBA Color - if set, data for each vertex will in-
                                //         clude a color value that is a packed RGBA color value
                                //         Note: Bits 1and 2 are mutually exclusive - a vertex can have ei-
                                //         ther color index or RGB color value or neither, but not both.
                                //   3     Has Normal - if set, data for each vertex will include a
                                //         normal (3 floats)
                                //   4     Has Base UV - if set, data for each vertex will include
                                //         uv texture coordinates for the base texture (2 floats)
                                //   5     Has UV Layer 1 - if set, data for each vertex will include
                                //         uv texture coordinates for layer 1 (2 floats)
                                //   6     Has UV Layer 2 - if set, data for each vertex will include
                                //         uv texture coordinates for layer 2 (2 floats)
                                //   7     Has UV Layer 3 - if set, data for each vertex will include
                                //         uv texture coordinates for layer 3 (2 floats)
                                //   8     Has UV Layer 4 - if set, data for each vertex will include
                                //         uv texture coordinates for layer 4 (2 floats)
                                //   9     Has UV Layer 5 - if set, data for each vertex will include
                                //         uv texture coordinates for layer 5 (2 floats)
                                //  10     Has UV Layer 6 - if set, data for each vertex will include
                                //         uv texture coordinates for layer 6 (2 floats)
                                //  11     Has UV Layer 7 - if set, data for each vertex will include
                                //         uv texture coordinates for layer 7 (2 floats)
                                //  12-31  Spare
    //      The following fields (if they are present according to uiAttribMask)
    //      are repeated uiNumVerts times
    // Double       Varies 8*3 CoordinateN - Coordinate of vertex N (x, y, z) - present if At-
    //                         tribute mask includes Has Position.
    // Unsigned Int Varies 4   colorN - Color for vertex N - present if Attribute mask includes
    //                         Has Color Index or Has RGBA Color.
    //                         If Has Color Index, lower 3 bytes specify color table index,
    //                         upper 1 byte is Alpha.
    //                         If Has RGBA Color, 4 bytes specify (a, b, g, r) values.
    // Float        Varies 4*3 normalN - Normal for vertex N (i, j, k) - present if Attribute mask
    //                         includes Has Normal.
    // Float        Varies 4*2 uvBaseN - Texture coordinates (u, v) for base texture layer of
    //                         vertex N - present if Attribute mask includes Has Base UV.
    // Float        Varies 4*2 uv1N - Texture coordinates (u, v) for layer 1 of vertex N -
    //                         present if Attribute mask includes Has UV Layer 1.
    // Float        Varies 4*2 uv2N - Texture coordinates (u, v) for layer 2 of vertex N -
    //                         present if Attribute mask includes Has UV Layer 2.
    // Float        Varies 4*2 uv3N - Texture coordinates (u, v) for layer 3 of vertex N -
    //                         present if Attribute mask includes Has UV Layer 3.
    // Float        Varies 4*2 uv4N - Texture coordinates (u, v) for layer 4 of vertex N -
    //                         present if Attribute mask includes Has UV Layer 4.
    // Float        Varies 4*2 uv5N - Texture coordinates (u, v) for layer 5 of vertex N -
    //                         present if Attribute mask includes Has UV Layer 5.
    // Float        Varies 4*2 uv6N - Texture coordinates (u, v) for layer 6 of vertex N -
    //                         present if Attribute mask includes Has UV Layer 6.
    // Float        Varies 4*2 uv7N - Texture coordinates (u, v) for layer 7 of vertex N -
    //                         present if Attribute mask includes Has UV Layer 7.

    GeoPnt3dPropertyUnrecPtr                _pPositions;
    GeoColor4ubPropertyUnrecPtr             _pColors;
    GeoVec3fPropertyUnrecPtr                _pNormals;
    GeoVec2fPropertyUnrecPtr                _texCoords[8];

    std::vector<OFMeshPrimitiveRecordRCPtr> _vTriStrips;
    std::vector<OFMeshPrimitiveRecordRCPtr> _vTriFans;
    std::vector<OFMeshPrimitiveRecordRCPtr> _vQuadStrips;
    std::vector<OFMeshPrimitiveRecordRCPtr> _vPolygons;

    /*---------------------------------------------------------------------*/

             OFLocalVertexPoolRecord(const OFRecordHeader &oHeader);

    virtual ~OFLocalVertexPoolRecord(void                         );

  public:
    typedef TransitPtr <OFLocalVertexPoolRecord >   ObjTransitPtr;
    typedef RefCountPtr<OFLocalVertexPoolRecord,
                        MemObjRefCountPolicy    >   ObjRCPtr;

    static const UInt16 OpCode = 85;

    static OFRecordTransitPtr create(const OFRecordHeader &oHeader);

    static const UInt32 AMHasPosition;
    static const UInt32 AMHasColorIndex;
    static const UInt32 AMHasColorValue;
    static const UInt32 AMHasNormal;
    static const UInt32 AMHasTexCoords[8];

    /*---------------------------------------------------------------------*/

    virtual bool read        (std::istream &is,
                              OFDatabase   &oDB     );
    virtual bool readContinue(std::istream &is,
                              OFDatabase   &oDB,
                              UInt16        uiLength);

    virtual bool addChild    (OFRecord     *pChild  );

    /*---------------------------------------------------------------------*/

    virtual UInt16 getOpCode(void);

    /*---------------------------------------------------------------------*/

    virtual void dump(UInt32 uiIndent);

    /*---------------------------------------------------------------------*/

    virtual void convertPrimitives(OFDatabase &oDB, Geometry *pGeo);

    GeoPnt3dProperty    *getPositions(void      ) const;
    GeoColor4ubProperty *getColors   (void      ) const;
    GeoVec3fProperty    *getNormals  (void      ) const;
    GeoVec2fProperty    *getTexCoords(UInt32 idx) const;
};

/*! \ingroup GrpFileIOOpenFlight
 */
typedef OFLocalVertexPoolRecord::ObjTransitPtr OFLocalVertexPoolRecordTransitPtr;
/*! \ingroup GrpFileIOOpenFlight
 */
typedef OFLocalVertexPoolRecord::ObjRCPtr      OFLocalVertexPoolRecordRCPtr;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpFileIOOpenFlight
    \nohierarchy
 */

class OSG_FILEIO_DLLMAPPING OFMeshRecord : public OFRecord
{
  protected:
    typedef OFRecord Inherited;

    static OFRecordFactoryBase::RegisterRecord _regHelper;

    /*---------------------------------------------------------------------*/

    Char8  szASCIIId[8];        //   4 8 7 char ASCII ID; 0 terminates
    Int32  iPad1;               //  12 4 Reserved
    Int32  iIRColorCode;        //  16 4 IR color code
    Int16  iRelPrio;            //  20 2 Relative priority
    Int8   iDrawType;           //  22 1 Draw type
                                // 0 = Draw solid with backface culling
                                // (front side only)
                                // 1 = Draw solid, no backface culling
                                // (both sides visible)
                                // 2 = Draw wireframe and close
                                // 3 = Draw wireframe
                                // 4 = Surround with wireframe in alternate color
                                // 8 = Omnidirectional light
                                // 9 = Unidirectional light
                                // 10 = Bidirectional light
    Int8   iTextureWhite;       //  23 1 Texture white = if TRUE, draw textured face white
    UInt16 uiColorNameIdx;      //  24 2 Color name index
    UInt16 uiAltColorNameIdx;   //  26 2 Alternate color name index
    Int8   iPad2;               //  28 1 Reserved
    Int8   iTemplate;           //  29 1 Template (billboard)
                                // 0 = Fixed, no alpha blending
                                // 1 = Fixed, alpha blending
                                // 2 = Axial rotate with alpha blending
                                // 4 = Point rotate with alpha blending
    Int16  iDetailTexIdx;       //  30 2 Detail texture pattern index, -1 if none
    Int16  iTexIdx;             //  32 2 Texture pattern index, -1 if none
    Int16  iMatIdx;             //  34 2 Material index, -1 if none
    Int16  iSurfMatCode;        //  36 2 Surface material code (for DFAD)
    Int16  iFeatureId;          //  38 2 Feature ID (for DFAD)
    Int32  iIRMatCode;          //  40 4 IR material code
    UInt16 uiTransparency;      //  44 2 Transparency
                                //  0 = Opaque
                                //  65535 = Totally clear
    UInt8  uiLODGenControl;     //  46 1 LOD generation control
    UInt8  uiLineStyle;         //  47 1 Line style index
    Int32  iFlags;              //  48 4 Flags (bits from left to right)
                                // 0 = Terrain
                                // 1 = No color
                                // 2 = No alternate color
                                // 3 = Packed color
                                // 4 = Terrain culture cutout (footprint)
                                // 5 = Hidden, not drawn
                                // 6 = Roofline
                                // 7-31 = Spare
    UInt8  uiLightMode;         //  52 1 Light mode
                                // 0 = Use mesh color, not illuminated (Flat)
                                // 1 = Use vertex colors, not illuminated (Gouraud)
                                // 2 = Use mesh color and vertex normals (Lit)
                                // 3 = Use vertex colors and vertex normals
                                //  (Lit, Gouraud)
    Char8  szPad3[7];           //  53 7 Reserved
    UInt32 uiPackedPrimCol;     //  60 4 Packed color, primary (a, b, g, r)
                                //    only b, g, r used
    UInt32 uiPackedAltCol;      //  64 4 Packed color, alternate (a, b, g, r)
                                //    only b, g, r used
    Int16  iTexMapIdx;          //  68 2 Texture mapping index, -1 if none
    Int16  iPad4;               //  70 2 Reserved
    Int32  uiPrimColIdx;        //  72 4 Primary color index, -1 if none
    Int32  uiAltColIdx;         //  76 4 Alternate color index, -1 if none
    Int16  iPad5;               //  80 2 Reserved
    Int16  iShaderIdx;          //  82 2 Shader index, -1 if none

    OFLocalVertexPoolRecordRCPtr _pVertexPool;

    /*---------------------------------------------------------------------*/

             OFMeshRecord(const OFRecordHeader &oHeader);

    virtual ~OFMeshRecord(void                         );

  public:
    typedef TransitPtr <OFMeshRecord        >   ObjTransitPtr;
    typedef RefCountPtr<OFMeshRecord,
                        MemObjRefCountPolicy>   ObjRCPtr;

    static const UInt16 OpCode = 84;

    static OFRecordTransitPtr create(const OFRecordHeader &oHeader);

    /*---------------------------------------------------------------------*/

    virtual bool read(std::istream &is, OFDatabase &oDB);

    /*---------------------------------------------------------------------*/

    virtual bool addChild (OFRecord *pChild);

    /*---------------------------------------------------------------------*/

    virtual UInt16 getOpCode(void);

    /*---------------------------------------------------------------------*/

    virtual void dump(UInt32 uiIndent);

    /*---------------------------------------------------------------------*/

    virtual NodeTransitPtr convertToNode(OFDatabase &oDB);
};

/*! \ingroup GrpFileIOOpenFlight
 */
typedef OFMeshRecord::ObjTransitPtr OFMeshRecordTransitPtr;
/*! \ingroup GrpFileIOOpenFlight
 */
typedef OFMeshRecord::ObjRCPtr      OFMeshRecordRCPtr;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

class OFVertexListRecord;

typedef RefCountPtr<OFVertexListRecord,
                    MemObjRefCountPolicy> OFVertexListRecordRCPtr;

/*! \ingroup GrpFileIOOpenFlight
    \nohierarchy
 */

class OSG_FILEIO_DLLMAPPING OFFaceRecord : public OFRecord
{
  protected:

    /*---------------------------------------------------------------------*/

    typedef OFRecord Inherited;

    /*---------------------------------------------------------------------*/

    static OFRecordFactoryBase::RegisterRecord _regHelper;

    /*---------------------------------------------------------------------*/

    Char8  szASCIIId[8];      // 4  8 7 char ASCII ID; 0 terminates
    Int32  iIRColorCode;      // 12 4 IR color code
    Int16  iRelPrio;          // 16 2 Relative priority
    Int8   iDrawType;         // 18 1 Draw type
                              // 0 = Draw solid with backface culling
                              // (front side only)
                              // 1 = Draw solid, no backface culling
                              // (both sides visible)
                              // 2 = Draw wireframe and close
                              // 3 = Draw wireframe
                              // 4 = Surround with wireframe in alternate color
                              // 8 = Omnidirectional light
                              // 9 = Unidirectional light
                              // 10 = Bidirectional light
    Int8   iTextureWhite;     // 19 1 Texture white =
                              // if TRUE, draw textured face white
    UInt16 uiColorNameIdx;    // 20 2 Color name index
    UInt16 uiAltColorNameIdx; // 22 2 Alternate color name index
    Int8   iPad1;           //       24 1 Reserved
    Int8   iTemplate;       // 25 1 Template (billboard)
                            // 0 = Fixed, no alpha blending
                            // 1 = Fixed, alpha blending
                            // 2 = Axial rotate with alpha blending
                            // 4 = Point rotate with alpha blending
    Int16  iDetailTexIdx;   // 26 2 Detail texture pattern index, -1 if none
    Int16  iTexIdx;         // 28 2 Texture pattern index, -1 if none
    Int16  iMatIdx;         // 30 2 Material index, -1 if none
    Int16  iSurfMatCode;    // 32 2 Surface material code (for DFAD)
    Int16  iFeatureId;      // 34 2 Feature ID (for DFAD)
    Int32  iIRMatCode;      // 36 4 IR material code
    UInt16 uiTransparency;  // 40 2 Transparency
                            // 0 = Opaque
                            // 65535 = Totally clear
    UInt8  uiLODGenControl; // 42 1 LOD generation control
    UInt8  uiLineStyle;     // 43 1 Line style index
    Int32  iFlags;          //         44 4 Flags (bits from left to right)
                            // 0 = Terrain
                            // 1 = No color
                            // 2 = No alternate color
                            // 3 = Packed color
                            // 4 = Terrain culture cutout (footprint)
                            // 5 = Hidden, not drawn
                            // 6 = Roofline
                            // 7-31 = Spare
    UInt8  uiLightMode;     // 48 1 Light mode
                            // 0 = Use face color, not illuminated     (Flat)
                            // 1 = Use vertex colors, not illuminated  (Gouraud)
                            // 2 = Use face color and vertex normals   (Lit)
                            // 3 = Use vertex colors and vertex normals(Lit
                            //                                          Gouraud)
    Char8  szPad2[7];       // 49 7 Reserved
    UInt32 uiPackedPrimCol; // 56 4 Packed color, primary (a, b, g, r) -
                            // only b, g, r used
    UInt32 uiPackedAltCol;  // 60 4 Packed color, alternate (a, b, g, r) -
                            // only b, g, r used
    Int16  iTexMapIdx;      // 64 2 Texture mapping index, -1 if none
    Int16  iPad3;           // 66 2 Reserved
    Int32  uiPrimColIdx;    // 68 4 Primary color index, -1 if none
    Int32  uiAltColIdx;     // 72 4 Alternate color index, -1 if none
    Int16  iPad4;           // 76 2 Reserved
    Int16  iShaderIdx;      // 78 2 Shader index, -1 if none

    /*---------------------------------------------------------------------*/

    OFVertexListRecordRCPtr _pVList;

    /*---------------------------------------------------------------------*/

             OFFaceRecord(const OFRecordHeader &oHeader);

    virtual ~OFFaceRecord(void);

  public:

    static const UInt16 OpCode = 5;

    static OFRecordTransitPtr create(const OFRecordHeader &oHeader);

    /*---------------------------------------------------------------------*/

    virtual bool read(std::istream &is, OFDatabase &oDB);

    /*---------------------------------------------------------------------*/

    virtual bool   addChild (OFRecord *pChild);

    /*---------------------------------------------------------------------*/

    virtual UInt16 getOpCode(void);

    /*---------------------------------------------------------------------*/

    virtual void dump(UInt32 uiIndent);

    /*---------------------------------------------------------------------*/

    bool operator ==(const OFFaceRecord &rhs) const;

    /*---------------------------------------------------------------------*/

    OFVertexListRecord *getVertexList  (void);
    Int8                getDrawType    (void) const;
    Int8                getTextureWhite(void) const;
    Int16               getTexIdx      (void) const;
    Int16               getMatIdx      (void) const;
    UInt16              getTransparency(void) const;
    Int32               getFlags       (void) const;
    UInt8               getLightMode   (void) const;
    Color4f             getPrimColor   (void) const;
    Color4f             getAltColor    (void) const;
};

/*! \ingroup GrpFileIOOpenFlight
 */
typedef RefCountPtr<OFFaceRecord, MemObjRefCountPolicy> OFFaceRecordRCPtr;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpFileIOOpenFlight
    \nohierarchy
 */

class OSG_FILEIO_DLLMAPPING OFVertexListRecord : public OFRecord
{
  protected:

    /*---------------------------------------------------------------------*/

    typedef OFRecord Inherited;

    /*---------------------------------------------------------------------*/

    static OFRecordFactoryBase::RegisterRecord _regHelper;

    /*---------------------------------------------------------------------*/

    std::vector<Int32> _vIndices;

    /*---------------------------------------------------------------------*/

    OFVertexListRecord(const OFRecordHeader &oHeader);

    virtual ~OFVertexListRecord(void);

  public:

    static const UInt16 OpCode = 72;

    static OFRecordTransitPtr create(const OFRecordHeader &oHeader);

    /*---------------------------------------------------------------------*/

    virtual bool read(std::istream &is, OFDatabase &oDB);

    /*---------------------------------------------------------------------*/

    virtual UInt16 getOpCode(void);

    /*---------------------------------------------------------------------*/

    const std::vector<Int32> &getIndices(void);
};

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpFileIOOpenFlight
    \nohierarchy
 */

class OSG_FILEIO_DLLMAPPING OFGeometryContainer : public OFRecord
{
  protected:

    /*---------------------------------------------------------------------*/

    typedef OFRecord Inherited;

    /*---------------------------------------------------------------------*/

    std::vector<OFFaceRecordRCPtr> _vFaces;
    std::vector<OFMeshRecordRCPtr> _vMeshes;

    /*---------------------------------------------------------------------*/

             OFGeometryContainer(const OFRecordHeader &oHeader);

    virtual ~OFGeometryContainer(void                         );

    /*---------------------------------------------------------------------*/

    virtual bool addChild (OFRecord *pChild);

    /*---------------------------------------------------------------------*/

    virtual void dump(UInt32 uiIndent);

    /*---------------------------------------------------------------------*/

    void groupFaces(std::vector< std::vector<OFFaceRecord *> > &vFaceGroups);

    /*---------------------------------------------------------------------*/

    NodeTransitPtr convertFaceGroup(std::vector<OFFaceRecord *> &vFaceGroup,
                                    OFDatabase                  &oDB       );

    NodeTransitPtr convertGeometry (OFDatabase                  &oDB       );
};

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpFileIOOpenFlight
    \nohierarchy
 */

class OSG_FILEIO_DLLMAPPING OFGroupingRecord : public OFGeometryContainer
{
  protected:

    /*---------------------------------------------------------------------*/

    typedef OFGeometryContainer Inherited;

    /*---------------------------------------------------------------------*/

    std::vector<OFRecordRCPtr> _vChildren;

    /*---------------------------------------------------------------------*/

             OFGroupingRecord(const OFRecordHeader &oHeader);

    virtual ~OFGroupingRecord(void);

    /*---------------------------------------------------------------------*/

    virtual bool addChild (OFRecord *pChild);

    /*---------------------------------------------------------------------*/

    virtual void dump(UInt32 uiIndent);

    /*---------------------------------------------------------------------*/

    virtual NodeTransitPtr convertToNode(OFDatabase &oDB);
};

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpFileIOOpenFlight
    \nohierarchy
 */

class OSG_FILEIO_DLLMAPPING OFGroupRecord : public OFGroupingRecord
{
  protected:

    /*---------------------------------------------------------------------*/

    typedef OFGroupingRecord Inherited;

    /*---------------------------------------------------------------------*/

    static OFRecordFactoryBase::RegisterRecord _regHelper;

    /*---------------------------------------------------------------------*/

    OFGroupRecord(const OFRecordHeader &oHeader);

    virtual ~OFGroupRecord(void);

  public:

    /*---------------------------------------------------------------------*/

    static const UInt16 OpCode = 2;

    static OFRecordTransitPtr create(const OFRecordHeader &oHeader);

    /*---------------------------------------------------------------------*/

    virtual bool read(std::istream &is, OFDatabase &oDB);

    /*---------------------------------------------------------------------*/

    virtual UInt16 getOpCode(void);

    /*---------------------------------------------------------------------*/

    virtual void dump(UInt32 uiIndent);
};

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpFileIOOpenFlight
    \nohierarchy
 */

class OSG_FILEIO_DLLMAPPING OFLODRecord : public OFGroupingRecord
{
  protected:

    /*---------------------------------------------------------------------*/

    typedef OFGroupingRecord Inherited;

    /*---------------------------------------------------------------------*/

    static OFRecordFactoryBase::RegisterRecord _regHelper;

    /*---------------------------------------------------------------------*/

    Char8  szASCIIId[8]; // 4  8 7 char ASCII ID; 0 terminates
    Int32  iPad1;        // 12 4 Reserved
    Real64 rSwitchIn;    // 16 8 Switch-in distance
    Real64 rSwitchOut;   // 24 8 Switch-out distance
    Int16  iSpecialEff1; // 32 2 Special effect ID1 - application defined
    Int16  iSpecialEff2; // 34 2 Special effect ID2 - application defined
    Int32  iFlags;       // 36 4 Flags (bits, from left to right)
                         // 0 = Use previous slant range
                         // 1 = Reserved
                         // 2 = Freeze center (don't recalculate)
                         // 3-31 = Spare
    Real64 rCenterX;     // 40 8 Center coordinate x of LOD
    Real64 rCenterY;     // 48 8 Center coordinate y of LOD
    Real64 rCenterZ;     // 56 8 Center coordinate z of LOD
    Real64 rTransRange;  // 64 8 Transition range
    Real64 rSigSize;     // 72 8 Significant size

    /*---------------------------------------------------------------------*/

    OFLODRecord(const OFRecordHeader &oHeader);

    virtual ~OFLODRecord(void);

  public:

    static const UInt16 OpCode = 73;

    static OFRecordTransitPtr create(const OFRecordHeader &oHeader);

    /*---------------------------------------------------------------------*/

    virtual bool read(std::istream &is, OFDatabase &oDB);

    /*---------------------------------------------------------------------*/

    virtual UInt16 getOpCode(void);

    /*---------------------------------------------------------------------*/

    virtual void dump(UInt32 uiIndent);

    /*---------------------------------------------------------------------*/

    virtual NodeTransitPtr convertToNode(OFDatabase &oDB);

    /*---------------------------------------------------------------------*/

    Real64 getSwitchIn (void);
    Real64 getSwitchOut(void);

    Pnt3f  getCenter   (void);
};

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpFileIOOpenFlight
    \nohierarchy
 */

class OSG_FILEIO_DLLMAPPING OFSwitchRecord : public OFGroupingRecord
{
  protected:

    /*---------------------------------------------------------------------*/

    typedef OFGroupingRecord Inherited;

    static OFRecordFactoryBase::RegisterRecord _regHelper;

    /*---------------------------------------------------------------------*/

    typedef std::vector< std::vector<UInt32> > MaskStore;

    /*---------------------------------------------------------------------*/

    Char8 szASCIIID[8]; // 4  8 7 char ASCII ID; 0 terminates
    Int32 szPad1;       // 12 4 Reserved
    Int32 iCurrMask;    // 16 4 Current mask
    Int32 iNumMask;     // 20 4 Number of masks
    Int32 iMaskWords;   // 24 4 Number of words per mask -
                        // the number of 32 bit words
                        // required for each mask, calculated as follows:
                        // (number of children / 32) + X
                        // where X equals:
                        // 0 if (number of children modulo 32) is zero
                        // 1 if (number of children modulo 32) is nonzero
    MaskStore vMask;    // Unsigned Int 28 Variable Mask words.
                        // The length (in bytes) can be calculated as follows:
                        // Number of words per mask * Number of masks * 4 bytes

    /*---------------------------------------------------------------------*/

    OFSwitchRecord(const OFRecordHeader &oHeader);

    virtual ~OFSwitchRecord(void);

  public:

    static const UInt16 OpCode = 96;

    static OFRecordTransitPtr create(const OFRecordHeader &oHeader);

    /*---------------------------------------------------------------------*/

    virtual bool read(std::istream &is, OFDatabase &oDB);

    /*---------------------------------------------------------------------*/

    virtual UInt16 getOpCode(void);

    /*---------------------------------------------------------------------*/

    virtual void dump(UInt32 uiIndent);

    /*---------------------------------------------------------------------*/

    virtual NodeTransitPtr convertToNode(OFDatabase &oDB);
};

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpFileIOOpenFlight
    \nohierarchy
 */

class OSG_FILEIO_DLLMAPPING OFObjectRecord : public OFGeometryContainer
{
  protected:

    /*---------------------------------------------------------------------*/

    typedef OFGeometryContainer Inherited;

    static OFRecordFactoryBase::RegisterRecord _regHelper;

    /*---------------------------------------------------------------------*/

    std::vector<OFRecordRCPtr> _vChildren;

    /*---------------------------------------------------------------------*/

    OFObjectRecord(const OFRecordHeader &oHeader);

    virtual ~OFObjectRecord(void);

  public:

    static const UInt16 OpCode = 4;

    static OFRecordTransitPtr create(const OFRecordHeader &oHeader);

    /*---------------------------------------------------------------------*/

    virtual bool addChild (OFRecord *pChild);

    /*---------------------------------------------------------------------*/

    virtual bool read(std::istream &is, OFDatabase &oDB);

    /*---------------------------------------------------------------------*/

    virtual UInt16 getOpCode(void);

    /*---------------------------------------------------------------------*/

    virtual void dump(UInt32 uiIndent);

    /*---------------------------------------------------------------------*/

    virtual NodeTransitPtr convertToNode(OFDatabase &oDB);
//    NodeTransitPtr convertFaces(OFDatabase &oDB);
};

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpFileIOOpenFlight
    \nohierarchy
 */

class OSG_FILEIO_DLLMAPPING OFExternalReferenceRecord : public OFRecord
{
  protected:

    typedef OFRecord Inherited;

    static OFRecordFactoryBase::RegisterRecord _regHelper;

    /*---------------------------------------------------------------------*/

    Char8 szFilename[200]; // 4   200 199-char ASCII path; 0 terminates
                           // Format of this string is: filename<node name>
                           // if <node name> absent, references entire file
    Int32 iPad1;           // 204 4   Reserved
    Int32 iFlags;          // 208 4   Flags (bits, from left to right)
                           // 0 = Color palette override
                           // 1 = Material palette override
                           // 2 = Texture and texture mapping palette override
                           // 3 = Line style palette override
                           // 4 = Sound palette override
                           // 5 = Light source palette override
                           // 6 = Light point palette override
                           // 7 = Shader palette override
                           // 8-31 = Spare
    Int16 iViewAsBBox;     // 212 2   View as bounding box
                           // 0 = View external reference normally
                           // 1 = View external reference as bounding box
    Int16 iPad2;           // 214 2   Reserved

    /*---------------------------------------------------------------------*/

    OFExternalReferenceRecord(const OFRecordHeader &oHeader);

    virtual ~OFExternalReferenceRecord(void);

  public:

    static const UInt16 OpCode = 63;

    static OFRecordTransitPtr create(const OFRecordHeader &oHeader);

    /*---------------------------------------------------------------------*/

    virtual bool read(std::istream &is, OFDatabase &oDB);

    /*---------------------------------------------------------------------*/

    virtual UInt16 getOpCode(void);

    /*---------------------------------------------------------------------*/

    virtual void dump(UInt32 uiIndent);

    /*---------------------------------------------------------------------*/

    virtual NodeTransitPtr convertToNode(OFDatabase &oDB);
};

OSG_END_NAMESPACE

#endif
