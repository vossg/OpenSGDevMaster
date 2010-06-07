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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#include <iostream>
#include <sstream>

#ifdef OSG_FLEX_USE_IOSTREAM_INPUT
#include <fstream>
#endif

#include "OSGScanParseLexer.h"
#include "OSGScanParseSkel.h"
#include "OSGBaseFunctions.h"
#include "OSGLog.h"


OSG_USING_NAMESPACE

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

ScanParseSkel::ScanParseSkel(void) :
    _bMapTypeIds      (false ),
    _szReferenceHeader(NULL  ),
    _pLexer           (new OSGScanParseLexer),
    _image            (NULL  ),
    _imageDataPtr     (0     ),
    _options          (0     )
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

ScanParseSkel::~ScanParseSkel(void)
{
    _image = NULL;

    delete _pLexer;

    delete [] _szReferenceHeader;
}

/*-------------------------------------------------------------------------*/
/*                                Scan                                     */

extern int OSGScanParseSkel_parse(void *);

#ifdef OSG_FLEX_USE_IOSTREAM_INPUT
void ScanParseSkel::scanStream(std::istream &is)
{
    if(is.good())
    {
        _pLexer->switch_streams(&is, 0);
        OSGScanParseSkel_parse(this);
    }
}
#endif

void ScanParseSkel::scanFile(const Char8 *szFilename)
{
    if(szFilename == NULL)
        return;

#ifdef OSG_FLEX_USE_IOSTREAM_INPUT
    std::ifstream is(szFilename);

    if(is.good())
    {
        PNOTICE << "Loading Stream: " << szFilename << std::endl;

        scanStream(is);

        is.close();
    }
#else
    FILE *pInFile = fopen(szFilename, "r");

    if(pInFile != NULL)
    {
        PNOTICE << "Loading File : " << szFilename << std::endl;

        OSGScanParseSkel_in = pInFile;

        OSGScanParseSkel_parse(this);

        fclose(pInFile);
    }
#endif
}

Int32 ScanParseSkel::lex(YYSTYPE *lvalp)
{
    return _pLexer->yylex(lvalp);
}

const Char8 *ScanParseSkel::getText(void)
{
    return _pLexer->YYText();
}

void ScanParseSkel::handleError(const Char8 *szErrorText)
{
    FWARNING(("-----> %s in Line %d, read '%s'\n",
              szErrorText,
              _pLexer->lineno(),
              _pLexer->YYText()));
}

/*-------------------------------------------------------------------------*/
/*                             Prototypes                                  */

bool ScanParseSkel::verifyHeader(const Char8 *szHeader)
{
    bool returnValue = true;

    if(szHeader == NULL)
    {
        SLOG << "Error Null Header String Read" << std::endl;
        return false;
    }

    if(_szReferenceHeader != NULL)
    {
        if(strncmp(szHeader,
                   _szReferenceHeader,
                   osgStringLen(_szReferenceHeader)) != 0)
        {
            SLOG << "Error : Header [" << szHeader << "] does not "
                    << "match reference [" << _szReferenceHeader << "]"
                    << std::endl;

            returnValue = false;
        }
    }
    else
    {
        SLOG << "Error Null Reference Header, Check disabled " << std::endl;
        return true;
    }

    return returnValue;
}

bool ScanParseSkel::checkHeader(void)
{
    return false;
}

void ScanParseSkel::beginProto(const Char8 *)
{
}

void ScanParseSkel::endProto(void)
{
}

void ScanParseSkel::endProtoInterface(void)
{
}

void ScanParseSkel::beginExternProto(const Char8 *)
{
}

void ScanParseSkel::endExternProtoInterface(void)
{
}

void ScanParseSkel::endExternProto(void)
{
}

void ScanParseSkel::beginScript(const Char8 *)
{
}

void ScanParseSkel::endScript(void)
{
}

void ScanParseSkel::beginEventInDecl (const Char8  *,
                                      const UInt32  ,
                                      const Char8  *)
{
}

void ScanParseSkel::beginEventOutDecl(const Char8  *,
                                      const UInt32  ,
                                      const Char8  *)
{
}

void ScanParseSkel::endEventDecl(void)
{
}

void ScanParseSkel::beginFieldDecl(const Char8  *,
                                   const UInt32  ,
                                   const Char8  *)
{
}

void ScanParseSkel::endFieldDecl(void)
{
}

void ScanParseSkel::beginExposedFieldDecl(const Char8  *,
                                          const UInt32  ,
                                          const Char8  *)
{
}

void ScanParseSkel::endExposedFieldDecl(void)
{
}


void ScanParseSkel::addExternEventInDecl (const Char8  *,
                                          const UInt32  ,
                                          const Char8  *)
{
}

void ScanParseSkel::addExternEventOutDecl(const Char8  *,
                                          const UInt32  ,
                                          const Char8  *)
{
}

void ScanParseSkel::addExternFieldDecl(const Char8  *,
                                       const UInt32  ,
                                       const Char8  *)
{
}

void ScanParseSkel::addExternExposedFieldDecl(const Char8  *,
                                              const UInt32  ,
                                              const Char8  *)
{
}

/*-------------------------------------------------------------------------*/
/*                               Fields                                    */

void ScanParseSkel::beginField(const Char8 *,
                               const UInt32)
{
}

void ScanParseSkel::endField(void)
{
}

/*-------------------------------------------------------------------------*/
/*                               Nodes                                     */

void ScanParseSkel::beginNode(const Char8 *szNodeTypename,
                              const Char8 *szNodename)
{
    fprintf(stderr, "Calling default begin node %s %s\n",
            szNodeTypename,
            szNodename);
}

void ScanParseSkel::endNode(void)
{
}

void ScanParseSkel::nullNode(void)
{
}

void ScanParseSkel::use(const Char8 *szName)
{
    PINFO << "Use : " << szName << std::endl;
}

void ScanParseSkel::is(const Char8 *)
{
}

void ScanParseSkel::profileElement(const Char8 *szProfileName)
{
    fprintf(stderr, "PROFILE %s\n", szProfileName);
}

void ScanParseSkel::componentElement    (const Char8 *szComponentName)
{
    fprintf(stderr, "COMPONENT %s\n", szComponentName);
}

void ScanParseSkel::metaElement  (const Char8 *szMetaKey,
                                  const Char8 *szMetaValue)
{
    fprintf(stderr, "META %s %s\n", szMetaKey, szMetaValue);
}

void ScanParseSkel::importElement(const Char8 *szInlineName,
                                  const Char8 *szNodeName,
                                  const Char8 *szImportAs   )
{
    fprintf(stderr, "IMPORT %s.%s AS %s\n", 
                    szInlineName, szNodeName, szImportAs);
}

void ScanParseSkel::exportElement(const Char8 *szNodeName,
                                  const Char8 *szExportAs )
{
    fprintf(stderr, "EXPORT %s AS %s\n", szNodeName, szExportAs);
}

/*-------------------------------------------------------------------------*/
/*                               Helper                                    */

void ScanParseSkel::addBufferAsStringValue(void)
{
    addStringValue(_pLexer->YYText());
}

void ScanParseSkel::addFieldValue(const Char8 *)
{
}

void ScanParseSkel::addBoolValue(bool b)
{
    addFieldValue(_pLexer->YYText());
}

void ScanParseSkel::addColorValue(const Color3f &c)
{
    addFieldValue(_tmpString1.c_str());
}

void ScanParseSkel::addColorRGBAValue(const Color4f &c)
{
    addFieldValue(_tmpString1.c_str());
}

void ScanParseSkel::addDoubleValue(Real64 d)
{
    addFieldValue(_pLexer->YYText());
}

void ScanParseSkel::addFloatValue(Real32 f)
{
    addFieldValue(_pLexer->YYText());
}

void ScanParseSkel::addImageValue(Image *img)
{
    UInt32 numComponents = img->getComponents();
    std::ostringstream os;
    os << img->getWidth() << ' ' << img->getHeight() << ' ' << numComponents;
    addFieldValue(os.str().c_str());
    UInt32 numPixels = img->getWidth() * img->getHeight();
    UInt32 pixel;
    UInt8 *data = img->editData();
    for (UInt32 i = 0; i < numPixels; ++i)
    {
        pixel = 0;
        for (UInt32 j = 0; j < numComponents; ++j)
            pixel = (pixel << 8) | *data++;
        os.str(std::string());
        os << pixel;
        addFieldValue(os.str().c_str());
    }
}

void ScanParseSkel::addInt32Value(Int32 i)
{
    addFieldValue(_pLexer->YYText());
}

void ScanParseSkel::addMatrix3dValue(Real64 m00, Real64 m10, Real64 m20,
                                     Real64 m01, Real64 m11, Real64 m21,
                                     Real64 m02, Real64 m12, Real64 m22)
{
    addFieldValue(_tmpString1.c_str());
}

void ScanParseSkel::addMatrix3fValue(Real32 m00, Real32 m10, Real32 m20,
                                     Real32 m01, Real32 m11, Real32 m21,
                                     Real32 m02, Real32 m12, Real32 m22)
{
    addFieldValue(_tmpString1.c_str());
}

void ScanParseSkel::addMatrix4dValue(const Matrix4d &m)
{
    addFieldValue(_tmpString1.c_str());
}

void ScanParseSkel::addMatrix4fValue(const Matrix4f &m)
{
    addFieldValue(_tmpString1.c_str());
}

void ScanParseSkel::addRotationValue(const Vec3f &axis, Real32 angle)
{
    addFieldValue(_tmpString1.c_str());
}

void ScanParseSkel::addStringValue(const std::string &s)
{
    addFieldValue(s.c_str());
}

void ScanParseSkel::addTimeValue(Time t)
{
    addFieldValue(_pLexer->YYText());
}

void ScanParseSkel::addVec2dValue(const Vec2d &v)
{
    addFieldValue(_tmpString1.c_str());
}

void ScanParseSkel::addVec2fValue(const Vec2f &v)
{
    addFieldValue(_tmpString1.c_str());
}

void ScanParseSkel::addVec3dValue(const Vec3d &v)
{
    addFieldValue(_tmpString1.c_str());
}

void ScanParseSkel::addVec3fValue(const Vec3f &v)
{
    addFieldValue(_tmpString1.c_str());
}

void ScanParseSkel::addVec4dValue(const Vec4d &v)
{
    addFieldValue(_tmpString1.c_str());
}

void ScanParseSkel::addVec4fValue(const Vec4f &v)
{
    addFieldValue(_tmpString1.c_str());
}

void ScanParseSkel::addColor4iValue(const Color4ub &c)
{
    addFieldValue(_tmpString1.c_str());
}

void ScanParseSkel::addPnt2fValue(const Pnt2f &p)
{
    addFieldValue(_tmpString1.c_str());
}

void ScanParseSkel::addPnt3fValue(const Pnt3f &p)
{
    addFieldValue(_tmpString1.c_str());
}

void ScanParseSkel::addPnt4fValue(const Pnt4f &p)
{
    addFieldValue(_tmpString1.c_str());
}

void ScanParseSkel::addVec2iValue(const Vec2i &)
{
    addFieldValue(_tmpString1.c_str());
}

void ScanParseSkel::addPlaneValue(const Plane &p)
{
    addFieldValue(_tmpString1.c_str());
}

void ScanParseSkel::addVolumeValue(const BoxVolume &v)
{
    addFieldValue(_tmpString1.c_str());
}

void ScanParseSkel::addRoute(const Char8 *,
                             const Char8 *,
                             const Char8 *,
                             const Char8 *)
{
}

/*-------------------------------------------------------------------------*/
/*                           Type Information                              */

bool ScanParseSkel::getMapFieldTypes(void)
{
    return _bMapTypeIds;
}

Int32 ScanParseSkel::mapExtIntFieldType(const Char8*, const Int32 iFieldType)
{
    return iFieldType;
}

UInt32 ScanParseSkel::getFieldType(const Char8 *)
{
    return 0;
}

OSGScanParseLexer *ScanParseSkel::getLexer(void)
{
    return _pLexer;
}


/*-------------------------------------------------------------------------*/
/*                              Options                                    */

void ScanParseSkel::addOptions(UInt32 options)
{
    _options |= options;
}

void ScanParseSkel::subOptions(UInt32 options)
{
    _options &= ~options;
}

UInt32 ScanParseSkel::getOptions(void) const
{
    return _options;
}

/*-------------------------------------------------------------------------*/
/*                               Set                                       */

void ScanParseSkel::reset(void)
{
}

void ScanParseSkel::setMapTypeIds(bool bVal)
{
    _bMapTypeIds = bVal;
}

void ScanParseSkel::setReferenceHeader(const Char8 *szReferenceHeader)
{
    osgStringDup(szReferenceHeader, _szReferenceHeader);
}

/*-------------------------------------------------------------------------*/

void ScanParseSkel::beginValue()
{
    _tmpString1.assign(_pLexer->YYText(), _pLexer->YYLeng());
}

void ScanParseSkel::appendValue()
{
    _tmpString1.push_back(' ');
    _tmpString1.append(_pLexer->YYText(), _pLexer->YYLeng());
}

void ScanParseSkel::beginImage(Int32 width, Int32 height, Int32 components)
{
    if (_image == NULL)
    {
        _image = Image::create();
    }
    UInt32 pixelFormat;
    switch (components)
    {
    case 1:  pixelFormat = Image::OSG_L_PF;       break;
    case 2:  pixelFormat = Image::OSG_LA_PF;      break;
    case 3:  pixelFormat = Image::OSG_RGB_PF;     break;
    case 4:  pixelFormat = Image::OSG_RGBA_PF;    break;
    default: pixelFormat = Image::OSG_INVALID_PF; break;
    }
    _image->set(pixelFormat, width, height);
    _imageDataPtr = _image->editData();
    _pLexer->expectImageInts(width * height);
}

void ScanParseSkel::addImagePixel(Int32 pixel)
{
    switch (_image->getPixelFormat())
    {
    case Image::OSG_RGBA_PF:
        *_imageDataPtr++ = pixel >> 24;
        // Fall through
    case Image::OSG_RGB_PF:
        *_imageDataPtr++ = pixel >> 16;
        // Fall through
    case Image::OSG_LA_PF:
        *_imageDataPtr++ = pixel >> 8;
        // Fall through
    case Image::OSG_L_PF:
        *_imageDataPtr++ = pixel;
        // Fall through
    default:
        break;
    }
}

void ScanParseSkel::endImage()
{
    _imageDataPtr = 0;

    addImageValue(_image);

    _image = NULL;
}
