#ifndef _OSGOFRECORDS_H_
#define _OSGOFRECORDS_H_

#include "boost/function.hpp"

#include "OSGFileIODef.h"
#include "OSGBaseTypes.h"
#include "OSGBaseFunctions.h"
#include "OSGSingletonHolder.h"
#include "OSGNode.h"
#include "OSGTextureObjChunk.h"
#include "OSGMemoryObject.h"

#include <map>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

class OFRecord;
class OFDatabase;

/*! \brief General VRML Node Desc
*/

struct OFRecordHeader
{
    UInt16 sOpCode;
    UInt16 sLength;

    bool read(std::istream &is)
    {
        is.read(reinterpret_cast<char *>(&sOpCode), 2);
        is.read(reinterpret_cast<char *>(&sLength), 2);

        sOpCode = osgBigEndianToHost(sOpCode);
        sLength = osgBigEndianToHost(sLength);

//        fprintf(stderr, "opcode %hu, length %hu\n", sOpCode, sLength);

        return is.good();
    }
};

typedef TransitPtr<OFRecord> OFRecordTransitPtr;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

class OSG_FILEIO_DLLMAPPING OFRecordFactoryBase 
{
    /*==========================  PUBLIC  =================================*/

  public :

    typedef boost::function<
        OFRecordTransitPtr (const OFRecordHeader &)> CreateRecord;

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

typedef SingletonHolder<OFRecordFactoryBase> OFRecordFactory;

// OpCode without object

static const UInt16 OFPushLevelOC = 10;
static const UInt16 OFPopLevelOC  = 11;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

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

    virtual bool read(std::istream &is, OFDatabase &oDB);
    
    /*---------------------------------------------------------------------*/

    virtual bool   addChild (OFRecord *pChild);
    virtual UInt16 getOpCode(void            ) = 0;

    /*---------------------------------------------------------------------*/

    virtual NodeTransitPtr convertToNode(OFDatabase &oDB);

    /*---------------------------------------------------------------------*/

    virtual void dump(UInt32 uiIndent);
};

typedef RefCountPtr<OFRecord, MemObjRefCountPolicy> OFRecordRCPtr;

class OFVertexPaletteRecord;
class OFTexturePaletteRecord;

typedef RefCountPtr<OFTexturePaletteRecord, 
                    MemObjRefCountPolicy  > OFTexturePaletteRecordRCPtr;

typedef RefCountPtr<OFVertexPaletteRecord, 
                    MemObjRefCountPolicy > OFVertexPaletteRecordRCPtr;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

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
};

typedef RefCountPtr<OFVertexPalette, 
                    MemObjRefCountPolicy> OFVertexPaletteRCPtr;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

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
};

typedef RefCountPtr<OFTexturePalette, 
                    MemObjRefCountPolicy> OFTexturePaletteRCPtr;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

class OSG_FILEIO_DLLMAPPING OFHeaderRecord : public OFRecord
{
    typedef OFRecord Inherited;

    friend class OFDatabase;

    /*---------------------------------------------------------------------*/

    std::vector<OFRecordRCPtr> _vChildren;

    OFVertexPaletteRCPtr       _pVertexPal;
    OFTexturePaletteRCPtr      _pTexturePal;

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

    const OFVertexPaletteRecord  *getVertexPalette(void        );
    const OFTexturePaletteRecord *getTexRecord    (UInt32 uiIdx);
};

typedef RefCountPtr<OFHeaderRecord, 
                    MemObjRefCountPolicy> OFHeaderRecordRCPtr;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

class OSG_FILEIO_DLLMAPPING OFUnknownRecord : public OFRecord
{
  protected:
  
    typedef OFRecord Inherited;

    /*---------------------------------------------------------------------*/

    UInt16 _sOpCode;

    /*---------------------------------------------------------------------*/

    OFUnknownRecord(const OFRecordHeader &oHeader);

    virtual ~OFUnknownRecord(void);

    /*---------------------------------------------------------------------*/

    friend class OFRecordFactoryBase;

  public:

    virtual bool read(std::istream &is, OFDatabase &oDB);

    /*---------------------------------------------------------------------*/

    virtual UInt16 getOpCode(void);
};

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

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

    Int32            getPatternIdx(void);

    TextureObjChunk *getTexObj    (void) const;
};

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

class OSG_FILEIO_DLLMAPPING OFVertexPaletteRecord : public OFRecord
{
  public:

    /*---------------------------------------------------------------------*/

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

        bool operator <(const UInt32 &uiOff) const;
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

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

class OFVertexListRecord;

typedef RefCountPtr<OFVertexListRecord, 
                    MemObjRefCountPolicy> OFVertexListRecordRCPtr;

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
    Int16  iSurMatCode;     // 32 2 Surface material code (for DFAD)
    Int16  iFeatureId;      // 34 2 Feature ID (for DFAD)
    Int32  iIRMatCode;      // 36 4 IR material code
    UInt16 uiTransparenct;  // 40 2 Transparency
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
    UInt32 uiPrimColIdx;    // 68 4 Primary color index, -1 if none
    UInt32 uiAltColIdx;     // 72 4 Alternate color index, -1 if none
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

    OFVertexListRecord *getVertexList(void);
    UInt8 getLightMode(void) const;
    Int16 getTexIdx   (void) const;
};

typedef RefCountPtr<OFFaceRecord, MemObjRefCountPolicy> OFFaceRecordRCPtr;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

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

class OSG_FILEIO_DLLMAPPING OFFaceContainer : public OFRecord
{
  protected:

    /*---------------------------------------------------------------------*/

    typedef OFRecord Inherited;

    /*---------------------------------------------------------------------*/

    std::vector<OFFaceRecordRCPtr> _vFaces;

    /*---------------------------------------------------------------------*/

    OFFaceContainer(const OFRecordHeader &oHeader);

    virtual ~OFFaceContainer(void);

    /*---------------------------------------------------------------------*/

    virtual bool addChild (OFRecord *pChild);

    /*---------------------------------------------------------------------*/

    virtual void dump(UInt32 uiIndent);

    /*---------------------------------------------------------------------*/

    void groupFaces(std::vector< std::vector<OFFaceRecord *> > &vFaceGroups);

    /*---------------------------------------------------------------------*/

    NodeTransitPtr convertFaceGroup(std::vector<OFFaceRecord *> &vFaceGroup,
                                    OFDatabase                  &oDB       );

    NodeTransitPtr convertFaces    (OFDatabase                  &oDB       );
};

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

class OSG_FILEIO_DLLMAPPING OFGroupingRecord : public OFFaceContainer
{
  protected:

    /*---------------------------------------------------------------------*/

    typedef OFFaceContainer Inherited;

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

class OSG_FILEIO_DLLMAPPING OFObjectRecord : public OFFaceContainer
{
  protected:
  
    /*---------------------------------------------------------------------*/

    typedef OFFaceContainer Inherited;

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
