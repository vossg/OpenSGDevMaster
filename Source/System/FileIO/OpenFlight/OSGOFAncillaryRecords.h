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
/*---------------------------------------------------------------------------*\
 *                                Changes                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/

#ifndef _OSGOFANCILLARYRECORDS_H_
#define _OSGOFANCILLARYRECORDS_H_

#include "OSGFileIODef.h"
#include "OSGOFRecords.h"

#include "OSGTextureEnvChunk.h"
#include "OSGTextureObjChunk.h"

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpFileIOOpenFlight
    \nohierarchy
 */

class OSG_FILEIO_DLLMAPPING OFColorPaletteRecord : public OFAncillaryRecord
{
  protected:

    typedef OFAncillaryRecord  Inherited;

    typedef std::vector<Color4f    >  ColorStore;
    typedef std::vector<std::string>  ColorNameStore;

    /*---------------------------------------------------------------------*/

    static OFRecordFactoryBase::RegisterRecord _regHelper;

    /*---------------------------------------------------------------------*/

    ColorStore     colors;
    ColorNameStore colorNames;

    /*---------------------------------------------------------------------*/

             OFColorPaletteRecord(const OFRecordHeader &oHeader,
                                        OFDatabase     &oDB     );
    virtual ~OFColorPaletteRecord(void                          );

  public:

    static const UInt16 OpCode = 32;

    static OFRecordTransitPtr create(const OFRecordHeader &oHeader,
                                           OFDatabase     &oDB     );

    /*---------------------------------------------------------------------*/

    virtual bool read(std::istream &is);

    /*---------------------------------------------------------------------*/

    virtual UInt16 getOpCode(void) const;

    /*---------------------------------------------------------------------*/

    virtual void dump(UInt32 uiIndent) const;

    /*---------------------------------------------------------------------*/

    Color4f            getColor(UInt32 uiIdx) const;

    bool               hasNames(void        ) const;
    std::string const &getName (UInt32 uiIdx) const;
};

/*! \ingroup GrpFileIOOpenFlight
 */
typedef RefCountPtr<OFColorPaletteRecord,
                    MemObjRefCountPolicy >  OFColorPaletteRecordRCPtr;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpFileIOOpenFlight
    \nohierarchy
 */

class OSG_FILEIO_DLLMAPPING OFTexturePaletteRecord : public OFAncillaryRecord
{
  protected:

    typedef OFAncillaryRecord Inherited;

    struct TexAttr
    {
        Int32 numTexelU;   //  0   4  number of texels in u direction
        Int32 numTexelV;   //  4   8  number of texels in v direction
        Int32 realSizeU;   //  8   4  obsolete
        Int32 realSizeV;   // 12   4  obsolete
        Int32 upX;         // 16   4  x component of up vector
        Int32 upY;         // 20   4  y component of up vector
        Int32 fileFormat;  // 24   4  file format type
                           //          0 AT&T image 8 pattern
                           //          1 AT&T image 8 template
                           //          2 SGI itensity modulation
                           //          3 SGI inensity w/alpha
                           //          4 SGI RGB
                           //          5 SGI RGB w/alpha
        Int32 minFilter;   // 28   4 minifiaction filter
                           //         0 point
                           //         1 bilinear
                           //         2 mipmap (obsolete)
                           //         3 mipmap point
                           //         4 mipmap linear
                           //         5 mipmap bilinear
                           //         7 mipmap trilinear
                           //         8 none
                           //         9 bicubic
                           //        10 bilinear GEQ
                           //        11 bilinear LEQ
                           //        12 bicubic GEQ
                           //        13 bicubic LEQ
        Int32 magFilter;   // 32   4 magnification filter
                           //         0 point
                           //         1 bilinear
                           //         2 none
                           //         3 bicubic
                           //         4 sharpen
                           //         5 add detail
                           //         6 modulate detail
                           //         7 bilinear GEQ
                           //         8 bilinear LEQ
                           //         9 bicubic GEQ
                           //        10 bicubic LEQ
        Int32 wrapUV;      // 36   4 wrap u,v
                           //         0 repeat
                           //         1 clamp
                           //         4 mirror repeat
        Int32 wrapU;       // 40   4 wrap u
                           //         0 repeat
                           //         1 clamp
                           //         3 none - use wrapUV
                           //         4 mirror repeat
        Int32 wrapV;       // 44   4 wrap v
                           //         0 repeat
                           //         1 clamp
                           //         3 none - use wrapUV
                           //         4 mirror repeat
        Int32 modified;    // 48   4 modified flag (internal use only)
        Int32 pivotX;      // 52   4 x pivot for rotating textures
        Int32 pivotY;      // 56   4 y pivot for rotating textures
        Int32 envMode;     // 60   4 environment mode
                           //         0 modulate
                           //         1 blend
                           //         2 decal
                           //         3 replace
                           //         4 add

        // many more that are not read at this point.

        GLenum getMinFilter(void);
        GLenum getMagFilter(void);

        GLenum getWrapU    (void);
        GLenum getWrapV    (void);

        GLenum getEnvMode  (void);

      protected:
        GLenum getWrap(Int32 wrap);
    };

    bool readTexAttr(TexAttr &attr);

    /*---------------------------------------------------------------------*/

    static OFRecordFactoryBase::RegisterRecord _regHelper;

    /*---------------------------------------------------------------------*/

    Char8 szFilename[200]; // 4   200 File name of texture pattern
    Int32 iPatternIdx;     // 204 4   Texture pattern index
    Int32 iPatternX;       // 208 4*2 Location in the texture palette (x, y)
    Int32 iPatternY;

    /*---------------------------------------------------------------------*/

    TextureObjChunkUnrecPtr pTexObj;
    TextureEnvChunkUnrecPtr pTexEnv;

    /*---------------------------------------------------------------------*/

             OFTexturePaletteRecord(const OFRecordHeader &oHeader,
                                          OFDatabase     &oDB     );
    virtual ~OFTexturePaletteRecord(void                          );

  public:

    static const UInt16 OpCode = 64;

    static OFRecordTransitPtr create(const OFRecordHeader &oHeader,
                                           OFDatabase     &oDB     );

    /*---------------------------------------------------------------------*/

    virtual bool read(std::istream &is);

    /*---------------------------------------------------------------------*/

    virtual UInt16 getOpCode(void) const;

    /*---------------------------------------------------------------------*/

    virtual void dump(UInt32 uiIndent) const;

    /*---------------------------------------------------------------------*/

    Int32            getPatternIdx(void);
    TextureObjChunk *getTexObj    (void) const;
    TextureEnvChunk *getTexEnv    (void) const;
};

/*! \ingroup GrpFileIOOpenFlight
 */
typedef RefCountPtr<OFTexturePaletteRecord,
                    MemObjRefCountPolicy   >  OFTexturePaletteRecordRCPtr;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpFileIOOpenFlight
    \nohierarchy
 */

class OSG_FILEIO_DLLMAPPING OFVertexPaletteRecord : public OFAncillaryRecord
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

    typedef OFAncillaryRecord Inherited;

    /*---------------------------------------------------------------------*/

    static OFRecordFactoryBase::RegisterRecord _regHelper;

    /*---------------------------------------------------------------------*/

    std::vector<Pnt3f>      vPositions;
    std::vector<Vec3f>      vNormals;
    std::vector<Vec2f>      vTexCoords;
    std::vector<VertexInfo> vVertexInfo;

    /*---------------------------------------------------------------------*/

    OFVertexPaletteRecord(const OFRecordHeader &oHeader,
                                OFDatabase     &oDB     );

    virtual ~OFVertexPaletteRecord(void);

  public:

    static const UInt16 OpCode  = 67;

    /*---------------------------------------------------------------------*/

    static OFRecordTransitPtr create(const OFRecordHeader &oHeader,
                                           OFDatabase     &oDB     );

    virtual bool read(std::istream &is);

    /*---------------------------------------------------------------------*/

    virtual UInt16 getOpCode(void) const;

    /*---------------------------------------------------------------------*/

    const VertexInfo *getVertexInfo(UInt32 uiOffset) const;

    const Pnt3f      &getPos       (UInt32 uiIdx   ) const;
    const Vec3f      &getNormal    (UInt32 uiIdx   ) const;
    const Vec2f      &getTexCoord  (UInt32 uiIdx   ) const;
};

bool operator <(const UInt32                             uiOff,
                const OFVertexPaletteRecord::VertexInfo &vInfo );

/*! \ingroup GrpFileIOOpenFlight
 */
typedef RefCountPtr<OFVertexPaletteRecord,
                    MemObjRefCountPolicy   >  OFVertexPaletteRecordRCPtr;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpFileIOOpenFlight
    \nohierarchy
 */

class OSG_FILEIO_DLLMAPPING OFMaterialPaletteRecord : public OFAncillaryRecord
{
 protected:

    typedef OFAncillaryRecord Inherited;

    /*---------------------------------------------------------------------*/

    static OFRecordFactoryBase::RegisterRecord _regHelper;

    /*---------------------------------------------------------------------*/

    Int32   iMaterialIdx;       //   4  4  Material index
    Char8   szMaterialName[12]; //   8 12  Material name
    Int32   iFlags;             //  20  4  Flags
                                //          0    = Material is used
                                //          1-31 = Spare
    Color4f colAmbient;         //  24 4*3 Ambient component of material (r, g, b)
    Color4f colDiffuse;         //  36 4*3 Diffuse component of material (r, g, b)
    Color4f colSpecular;        //  48 4*3 Specular component of material (r, g, b)
    Color4f colEmissive;        //  60 4*3 Emissive component of material (r, g, b)
    Real32  fShininess;         //  72 4   Shininess - (0.0-128.0)
    Real32  fAlpha;             //  76 4   Alpha - (0.0-1.0) where 1.0 is opaque
    Int32   iPad;               //  80 4   Reserved

    /*---------------------------------------------------------------------*/

             OFMaterialPaletteRecord(const OFRecordHeader &oHeader,
                                           OFDatabase     &oDB     );
    virtual ~OFMaterialPaletteRecord(void                          );

  public:

    static const UInt16 OpCode = 113;

    static OFRecordTransitPtr create(const OFRecordHeader &oHeader,
                                           OFDatabase     &oDB     );

    static const Int32  FlagMaterialUsed = 0x80000000;

    /*---------------------------------------------------------------------*/

    virtual bool read(std::istream &is);

    /*---------------------------------------------------------------------*/

    virtual UInt16 getOpCode(void) const;

    /*---------------------------------------------------------------------*/

    virtual void dump(UInt32 uiIndent) const;

    /*---------------------------------------------------------------------*/

          Int32    getMaterialIdx(void);

    const Color4f &getAmbient    (void) const;
    const Color4f &getDiffuse    (void) const;
    const Color4f &getSpecular   (void) const;
    const Color4f &getEmissive   (void) const;
          Real32   getShininess  (void) const;
          Real32   getAlpha      (void) const;
};

/*! \ingroup GrpFileIOOpenFlight
 */
typedef RefCountPtr<OFMaterialPaletteRecord,
                    MemObjRefCountPolicy   >  OFMaterialPaletteRecordRCPtr;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpFileIOOpenFlight
    \nohierarchy
 */

class OSG_FILEIO_DLLMAPPING OFMatrixRecord : public OFAncillaryRecord
{
  protected:
    /*---------------------------------------------------------------------*/

    typedef OFAncillaryRecord Inherited;

    /*---------------------------------------------------------------------*/

    static OFRecordFactoryBase::RegisterRecord _regHelper;

    /*---------------------------------------------------------------------*/

    Matrix matrix;   // 4  64  4x4 matrix, row major

    /*---------------------------------------------------------------------*/

             OFMatrixRecord(const OFRecordHeader &oHeader,
                                  OFDatabase     &oDB    );
    virtual ~OFMatrixRecord(void                         );

  public:

    static const UInt16 OpCode = 49;

    static OFRecordTransitPtr create(const OFRecordHeader &oHeader,
                                           OFDatabase     &oDB    );

    /*---------------------------------------------------------------------*/

    virtual bool           read   (std::istream &is   );
    virtual NodeTransitPtr convert(Node         *pNode);

    /*---------------------------------------------------------------------*/

    virtual UInt16 getOpCode(void) const;

    /*---------------------------------------------------------------------*/

    virtual void dump(UInt32 uiIndent) const;

    /*---------------------------------------------------------------------*/
};

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpFileIOOpenFlight
    \nohierarchy
 */

class OSG_FILEIO_DLLMAPPING OFIgnoredTransformRecord : public OFAncillaryRecord
{
  protected:

    typedef OFAncillaryRecord Inherited;

    /*---------------------------------------------------------------------*/

    static OFRecordFactoryBase::RegisterRecord _regHelperRotateAboutEdge;
    static OFRecordFactoryBase::RegisterRecord _regHelperTranslate;
    static OFRecordFactoryBase::RegisterRecord _regHelperScale;
    static OFRecordFactoryBase::RegisterRecord _regHelperRotateAboutPoint;
    static OFRecordFactoryBase::RegisterRecord _regHelperRotateScaleToPoint;
    static OFRecordFactoryBase::RegisterRecord _regHelperPut;
    static OFRecordFactoryBase::RegisterRecord _regHelperGeneralMatrix;

    /*---------------------------------------------------------------------*/

    UInt16 _sOpCode;

    /*---------------------------------------------------------------------*/

             OFIgnoredTransformRecord(const OFRecordHeader &oHeader,
                                            OFDatabase     &oDB    );
    virtual ~OFIgnoredTransformRecord(void                         );

  public:

    static const UInt16 OpCodeRotateAboutEdge    = 76;
    static const UInt16 OpCodeTranslate          = 78;
    static const UInt16 OpCodeScale              = 79;
    static const UInt16 OpCodeRotateAboutPoint   = 80;
    static const UInt16 OpCodeRotateScaleToPoint = 81;
    static const UInt16 OpCodePut                = 82;
    static const UInt16 OpCodeGeneralMatrix      = 94;

    /*---------------------------------------------------------------------*/

    static OFRecordTransitPtr create(const OFRecordHeader &oHeader,
                                           OFDatabase     &oDB    );

    /*---------------------------------------------------------------------*/

    virtual bool           read   (std::istream &is   );
    virtual NodeTransitPtr convert(Node         *pNode);

    /*---------------------------------------------------------------------*/

    virtual UInt16 getOpCode(void) const;

    /*---------------------------------------------------------------------*/

    virtual void dump(UInt32 uiIndent) const;

    /*---------------------------------------------------------------------*/
};

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpFileIOOpenFlight
    \nohierarchy
 */

class OSG_FILEIO_DLLMAPPING OFLongIDRecord : public OFAncillaryRecord
{
  protected:
    /*---------------------------------------------------------------------*/

    typedef OFAncillaryRecord Inherited;

    /*---------------------------------------------------------------------*/

    static OFRecordFactoryBase::RegisterRecord _regHelper;

    /*---------------------------------------------------------------------*/

    std::string longId;     // 4  len-4  ASCIIId of node, 0 terminates

    /*---------------------------------------------------------------------*/

             OFLongIDRecord(const OFRecordHeader &oHeader,
                                  OFDatabase     &oDB    );
    virtual ~OFLongIDRecord(void                         );

  public:

    static const UInt16 OpCode = 33;

    static OFRecordTransitPtr create(const OFRecordHeader &oHeader,
                                           OFDatabase     &oDB    );

    /*---------------------------------------------------------------------*/

    virtual bool           read   (std::istream &is   );
    virtual NodeTransitPtr convert(Node         *pNode);

    /*---------------------------------------------------------------------*/

    virtual UInt16 getOpCode(void) const;

    /*---------------------------------------------------------------------*/

    virtual void dump(UInt32 uiIndent) const;

    /*---------------------------------------------------------------------*/
};

OSG_END_NAMESPACE

#endif /* _OSGOFANCILLARYRECORDS_H_ */
