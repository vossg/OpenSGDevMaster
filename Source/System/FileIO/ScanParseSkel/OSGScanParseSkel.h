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

#ifndef _OSGSCANPARSESKEL_H_
#define _OSGSCANPARSESKEL_H_
#ifdef __sgi
#pragma once
#endif


#include "OSGSystemDef.h"
#include "OSGBaseTypes.h"
#include "OSGScanParseSkelParser.hpp"
#include "OSGImage.h"

// We have to prevent double inclusion of the scanner header file
#ifndef TOK_HEADER
#include "OSGScanParseSkelParser.hpp"
#endif

#include <string>

#ifdef OSG_FLEX_USE_IOSTREAM_INPUT
#include <iosfwd>
#endif

class OSGScanParseLexer;
int OSGScanParseSkel_parse(void*);

OSG_BEGIN_NAMESPACE

/*! Parser / Scanner Skeleton for VRML97 syntax based file formats
    \ingroup GrpSystemFileIOScanParse
    \ingroup GrpLibOSGSystem
 */

class OSG_SYSTEM_DLLMAPPING ScanParseSkel
{
  friend int ::OSGScanParseSkel_parse(void*);

    /*==========================  PUBLIC  =================================*/

  public:

    enum BuildInFieldType
    {
        OSGsfBool      = TOK_SFBool,
        OSGsfColor     = TOK_SFColor,
        OSGsfColorRGBA = TOK_SFColorRGBA,
        OSGsfDouble    = TOK_SFDouble,
        OSGsfFloat     = TOK_SFFloat,
        OSGsfImage     = TOK_SFImage,
        OSGsfInt32     = TOK_SFInt32,
        OSGsfMatrix3d  = TOK_SFMatrix3d,
        OSGsfMatrix3f  = TOK_SFMatrix3f,
        OSGsfMatrix4d  = TOK_SFMatrix4d,
        OSGsfMatrix4f  = TOK_SFMatrix4f,
        OSGsfNode      = TOK_SFNode,
        OSGsfRotation  = TOK_SFRotation,
        OSGsfString    = TOK_SFString,
        OSGsfTime      = TOK_SFTime,
        OSGsfVec2d     = TOK_SFVec2d,
        OSGsfVec2f     = TOK_SFVec2f,
        OSGsfVec3d     = TOK_SFVec3d,
        OSGsfVec3f     = TOK_SFVec3f,
        OSGsfVec4d     = TOK_SFVec4d,
        OSGsfVec4f     = TOK_SFVec4f,
        OSGmfBool      = TOK_MFBool,
        OSGmfColor     = TOK_MFColor,
        OSGmfColorRGBA = TOK_MFColorRGBA,
        OSGmfDouble    = TOK_MFDouble,
        OSGmfFloat     = TOK_MFFloat,
        OSGmfImage     = TOK_MFImage,
        OSGmfInt32     = TOK_MFInt32,
        OSGmfMatrix3d  = TOK_MFMatrix3d,
        OSGmfMatrix3f  = TOK_MFMatrix3f,
        OSGmfMatrix4d  = TOK_MFMatrix4d,
        OSGmfMatrix4f  = TOK_MFMatrix4f,
        OSGmfNode      = TOK_MFNode,
        OSGmfRotation  = TOK_MFRotation,
        OSGmfString    = TOK_MFString,
        OSGmfTime      = TOK_MFTime,
        OSGmfVec2d     = TOK_MFVec2d,
        OSGmfVec2f     = TOK_MFVec2f,
        OSGmfVec3d     = TOK_MFVec3d,
        OSGmfVec3f     = TOK_MFVec3f,
        OSGmfVec4d     = TOK_MFVec4d,
        OSGmfVec4f     = TOK_MFVec4f,

        OSGmfColor4f   = TOK_MFColorRGBA,
        OSGmfColor4i   = TOK_MFColor4i,
        OSGmfColor3f   = TOK_MFColor,
        OSGmfMatrix    = TOK_MFMatrix4f,
        OSGmfPnt2f     = TOK_MFPnt2f,
        OSGmfPnt3f     = TOK_MFPnt3f,
        OSGmfPnt4f     = TOK_MFPnt4f,
        OSGmfPlane     = TOK_MFPlane,
        OSGsfColor4f   = TOK_SFColorRGBA,
        OSGsfColor4i   = TOK_SFColor4i,
        OSGsfColor3f   = TOK_SFColor,
        OSGsfMatrix    = TOK_SFMatrix4f,
        OSGsfPnt2f     = TOK_SFPnt2f,
        OSGsfPnt3f     = TOK_SFPnt3f,
        OSGsfPnt4f     = TOK_SFPnt4f,
        OSGsfVec2i     = TOK_SFVec2i,
        OSGmfVec2i     = TOK_MFVec2i,
        OSGsfPlane     = TOK_SFPlane,
        OSGsfVolume    = TOK_SFVolume
    };

    enum
    {
        LastOption = 0x0001
    };

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    ScanParseSkel(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~ScanParseSkel(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Scan                                    */
    /*! \{                                                                 */

#ifdef OSG_FLEX_USE_IOSTREAM_INPUT
                  void   scanStream (      std::istream &is        );
#endif

                  void   scanFile   (const Char8        *szFilename);

    virtual       Int32  lex        (      YYSTYPE *lvalp          );
    virtual const Char8 *getText    (      void                    );

    virtual       void   handleError(const Char8       *szErrorText);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Prototypes                               */
    /*! \{                                                                 */

    virtual bool verifyHeader             (const Char8 *szHeader   );
    virtual bool checkHeader              (      void              );

    virtual void beginProto               (const Char8 *szProtoname);
    virtual void endProtoInterface        (void);
    virtual void endProto                 (void);

    virtual void beginExternProto         (const Char8 *szProtoname);
    virtual void endExternProtoInterface  (void                    );
    virtual void endExternProto           (void                    );

    virtual void beginScript              (const Char8 *szProtoname);
    virtual void endScript                (void);

    virtual void beginEventInDecl         (const Char8  *szEventType,
                                           const UInt32  uiFieldTypeId,
                                           const Char8  *szEventName);

    virtual void beginEventOutDecl        (const Char8  *szEventType,
                                           const UInt32  uiFieldTypeId,
                                           const Char8  *szEventName);

    virtual void endEventDecl             (void);

    virtual void beginFieldDecl           (const Char8  *szFieldType,
                                           const UInt32  uiFieldTypeId,
                                           const Char8  *szFieldName);

    virtual void endFieldDecl             (void);

    virtual void beginExposedFieldDecl    (const Char8  *szFieldType,
                                           const UInt32  uiFieldTypeId,
                                           const Char8  *szFieldName);

    virtual void endExposedFieldDecl      (void);


    virtual void addExternEventInDecl     (const Char8  *szEventType,
                                           const UInt32  uiFieldTypeId,
                                           const Char8  *szEventName);

    virtual void addExternEventOutDecl    (const Char8  *szEventType,
                                           const UInt32  uiFieldTypeId,
                                           const Char8  *szEventName);

    virtual void addExternFieldDecl       (const Char8  *szFieldType,
                                           const UInt32  uiFieldTypeId,
                                           const Char8  *szFieldName);

    virtual void addExternExposedFieldDecl(const Char8  *szFieldType,
                                           const UInt32  uiFieldTypeId,
                                           const Char8  *szFieldName);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Fields                                   */
    /*! \{                                                                 */

    virtual void beginField(const Char8  *szFieldname,
                            const UInt32  uiFieldTypeId);

    virtual void endField  (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Nodes                                    */
    /*! \{                                                                 */

    virtual void beginNode(const Char8 *szNodeTypename,
                           const Char8 *szNodename);

    virtual void endNode  (void);

    virtual void nullNode (void);

    virtual void use      (const Char8 *szName);
    virtual void is       (const Char8 *szName);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Misc                                     */
    /*! \{                                                                 */

    virtual void addBufferAsStringValue(void);

    virtual void addFieldValue(const Char8 *szFieldVal);

    virtual void addBoolValue(bool b);

    virtual void addColorValue(const Color3f &c);

    virtual void addColorRGBAValue(const Color4f &c);

    virtual void addDoubleValue(Real64 d);

    virtual void addFloatValue(Real32 f);

    virtual void addImageValue(Image *img);

    virtual void addInt32Value(Int32 i);

    virtual void addMatrix3dValue(Real64 m00, Real64 m10, Real64 m20,
                                  Real64 m01, Real64 m11, Real64 m21,
                                  Real64 m02, Real64 m12, Real64 m22);

    virtual void addMatrix3fValue(Real32 m00, Real32 m10, Real32 m20,
                                  Real32 m01, Real32 m11, Real32 m21,
                                  Real32 m02, Real32 m12, Real32 m22);

    virtual void addMatrix4dValue(const Matrix4d &m);

    virtual void addMatrix4fValue(const Matrix4f &m);

    virtual void addRotationValue(const Vec3f &axis, Real32 angle);

    virtual void addStringValue(const std::string &s);

    virtual void addTimeValue(Time t);

    virtual void addVec2dValue(const Vec2d &v);

    virtual void addVec2fValue(const Vec2f &v);

    virtual void addVec3dValue(const Vec3d &v);

    virtual void addVec3fValue(const Vec3f &v);

    virtual void addVec4dValue(const Vec4d &v);

    virtual void addVec4fValue(const Vec4f &v);

    virtual void addColor4iValue(const Color4ub &c);

    virtual void addPnt2fValue(const Pnt2f &p);

    virtual void addPnt3fValue(const Pnt3f &p);

    virtual void addPnt4fValue(const Pnt4f &p);

    virtual void addVec2iValue(const Vec2i &v);

    virtual void addPlaneValue(const Plane &p);

    virtual void addVolumeValue(const BoxVolume &v);

    virtual void addRoute     (const Char8 *szOutNodename,
                               const Char8 *szOutFieldname,
                               const Char8 *szInNodename,
                               const Char8 *szInFieldname);

    virtual void profileElement   (const Char8 *szProfileName);

    virtual void componentElement (const Char8 *szComponentName);

    virtual void metaElement      (const Char8 *szMetaKey,
                                   const Char8 *szMetaValue);

    virtual void importElement    (const Char8 *szInlineName,
                                   const Char8 *szNodeName,
                                   const Char8 *szImportAs   );

    virtual void exportElement    (const Char8 *szNodeName,
                                   const Char8 *szExportAs   );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Type Information                             */
    /*! \{                                                                 */

    bool           getMapFieldTypes  (void);

    virtual Int32  mapExtIntFieldType(const Char8 *szFieldname,
                                      const Int32  iFieldTypeId);

    virtual UInt32 getFieldType      (const Char8 *szFieldname);

    OSGScanParseLexer *getLexer(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Options                                  */
    /*! \{                                                                 */
    
    void   addOptions(UInt32 options);
    void   subOptions(UInt32 options);
    UInt32 getOptions(void          ) const;
    
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    bool               _bMapTypeIds;
    Char8             *_szReferenceHeader;
    OSGScanParseLexer *_pLexer;

    void reset             (      void);

    void setMapTypeIds     (      bool   bVal);

    void setReferenceHeader(const Char8 *szReferenceHeader);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    /*!\brief prohibit default function (move to 'public' if needed) */
    ScanParseSkel(const ScanParseSkel &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const ScanParseSkel &source);

    std::string _tmpString1, _tmpString2, _tmpString3;
    Real32 _tmpFloat1, _tmpFloat2, _tmpFloat3, _tmpFloat4;

    void beginValue();

    void appendValue();

    void beginImage(Int32 width, Int32 height, Int32 components);

    void addImagePixel(Int32 pixel);

    void endImage();


    ImageUnrecPtr  _image;
    UInt8         *_imageDataPtr;

    UInt32         _options;
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

OSG_END_NAMESPACE

#endif /* _OSGSCANPARSESKEL_H_ */
