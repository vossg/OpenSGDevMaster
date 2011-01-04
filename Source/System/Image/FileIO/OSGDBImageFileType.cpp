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
//-------------------------------
// Includes  
//-------------------------------

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#include "OSGDBImageFileType.h"
#include "OSGGeoReferenceAttachment.h"
#include "OSGImageFunctions.h"

#ifndef OSG_DO_DOC
#    ifdef OSG_WITH_DB
#        define OSG_DB_ARG(ARG) ARG
#    else
#        define OSG_DB_ARG(ARG)
#    endif
#else
#    define OSG_DB_ARG(ARG) ARG
#endif

// Static Class Varible implementations:
static const OSG::Char8 *suffixArray[] = 
{
    "db"
};

OSG_BEGIN_NAMESPACE

DBHeaderParameter::DBHeaderParameter(void) :
    _bLastParam(false)
{
}

DBHeaderParameter::~DBHeaderParameter(void)
{
}

void DBHeaderParameter::setLastParam(void)
{
    _bLastParam = true;
}

bool DBHeaderParameter::isLastParam(void)
{
    return _bLastParam;
}


DBHeaderIntParameter::DBHeaderIntParameter(UInt32 &uiParam) :
     Inherited(       ),
    _uiParam  (uiParam)
{
}

DBHeaderIntParameter::~DBHeaderIntParameter(void)
{
}

void DBHeaderIntParameter::convert(const Char8 *str)
{
    if(str != NULL)
    {
        sscanf(str, "%u", &_uiParam);
    }
}

DBHeaderFloatParameter::DBHeaderFloatParameter(Real32 &rParam) :
     Inherited(      ),
    _rParam   (rParam)
{
}

DBHeaderFloatParameter::~DBHeaderFloatParameter(void)
{
}

void DBHeaderFloatParameter::convert(const Char8 *str)
{
    if(str != NULL)
    {
        sscanf(str, "%f", &_rParam);
    }
}

DBHeader::DBHeader(void) :
    uiMagic     (0  ),
    uiXSize     (0  ),
    uiYSize     (0  ),
    uiZSize     (0  ),
    uiTSteps    (0  ),
    uiType      (0  ),

    rSWx        (0.f),
    rSWy        (0.f),
    rNWx        (0.f),
    rNWy        (0.f),

    rNEx        (0.f),
    rNEy        (0.f),
    rSEx        (0.f),
    rSEy        (0.f),

    rH0         (0.f),
    rDh         (0.f),
    rT0         (0.f),
    rDt         (0.f),
    
    rScaling    (1.f),
    rBias       (0.f),

    uiExtFormat (0  ),
    uiImplFormat(0  ),

    LLWGS84_rSWx(0.f),
    LLWGS84_rSWy(0.f),
    LLWGS84_rNWx(0.f),
    LLWGS84_rNWy(0.f),

    LLWGS84_rNEx(0.f),
    LLWGS84_rNEy(0.f),
    LLWGS84_rSEx(0.f),
    LLWGS84_rSEy(0.f),

    uiBytes     (0  )
{
    std::string szParamName("MAGIC");

    _mParams[szParamName] = new DBHeaderIntParameter(uiMagic);
    
    szParamName = "xsize";

    _mParams[szParamName] = new DBHeaderIntParameter(uiXSize);

    szParamName = "ysize";

    _mParams[szParamName] = new DBHeaderIntParameter(uiYSize);

    szParamName = "zsize";

    _mParams[szParamName] = new DBHeaderIntParameter(uiZSize);

    szParamName = "tsteps";

    _mParams[szParamName] = new DBHeaderIntParameter(uiTSteps);

    szParamName = "type";

    _mParams[szParamName] = new DBHeaderIntParameter(uiType);



    szParamName = "swx";

    _mParams[szParamName] = new DBHeaderFloatParameter(rSWx);

    szParamName = "swy";

    _mParams[szParamName] = new DBHeaderFloatParameter(rSWy);

    szParamName = "nwx";

    _mParams[szParamName] = new DBHeaderFloatParameter(rNWx);

    szParamName = "nwy";

    _mParams[szParamName] = new DBHeaderFloatParameter(rNWy);



    szParamName = "nex";

    _mParams[szParamName] = new DBHeaderFloatParameter(rNEx);

    szParamName = "ney";

    _mParams[szParamName] = new DBHeaderFloatParameter(rNEy);

    szParamName = "sex";

    _mParams[szParamName] = new DBHeaderFloatParameter(rSEx);

    szParamName = "sey";

    _mParams[szParamName] = new DBHeaderFloatParameter(rSEy);



    szParamName = "h0";

    _mParams[szParamName] = new DBHeaderFloatParameter(rH0);

    szParamName = "dh";

    _mParams[szParamName] = new DBHeaderFloatParameter(rDh);

    szParamName = "t0";

    _mParams[szParamName] = new DBHeaderFloatParameter(rT0);

    szParamName = "dt";

    _mParams[szParamName] = new DBHeaderFloatParameter(rDt);



    szParamName = "scaling";

    _mParams[szParamName] = new DBHeaderFloatParameter(rScaling);

    szParamName = "bias";

    _mParams[szParamName] = new DBHeaderFloatParameter(rBias);



    szParamName = "extformat";

    _mParams[szParamName] = new DBHeaderIntParameter(uiExtFormat);

    szParamName = "implformat";

    _mParams[szParamName] = new DBHeaderIntParameter(uiImplFormat);



    szParamName = "LLWGS84_swx";

    _mParams[szParamName] = new DBHeaderFloatParameter(LLWGS84_rSWx);

    szParamName = "LLWGS84_swy";

    _mParams[szParamName] = new DBHeaderFloatParameter(LLWGS84_rSWy);

    szParamName = "LLWGS84_nwx";

    _mParams[szParamName] = new DBHeaderFloatParameter(LLWGS84_rNWx);

    szParamName = "LLWGS84_nwy";

    _mParams[szParamName] = new DBHeaderFloatParameter(LLWGS84_rNWy);



    szParamName = "LLWGS84_nex";

    _mParams[szParamName] = new DBHeaderFloatParameter(LLWGS84_rNEx);

    szParamName = "LLWGS84_ney";

    _mParams[szParamName] = new DBHeaderFloatParameter(LLWGS84_rNEy);

    szParamName = "LLWGS84_sex";

    _mParams[szParamName] = new DBHeaderFloatParameter(LLWGS84_rSEx);

    szParamName = "LLWGS84_sey";

    _mParams[szParamName] = new DBHeaderFloatParameter(LLWGS84_rSEy);



    szParamName = "bytes";

    _mParams[szParamName] = new DBHeaderIntParameter(uiBytes);

    _mParams[szParamName]->setLastParam();
}
 
DBHeader::~DBHeader(void)
{
    ParameterMap::iterator mapIt  = _mParams.begin();
    ParameterMap::iterator mapEnd = _mParams.end  ();

    while(mapIt != mapEnd)
    {
        delete mapIt->second;

        ++mapIt;
    }
}

bool DBHeader::read(FILE *pIn)
{
    bool returnValue = true;

    if(pIn == NULL)
        return returnValue;

    Char8  buffer[1024];
    bool   bEnd = false;
    Char8 *strIt;

    while(!bEnd)
    {
        fgets(buffer, 1024, pIn);

        strIt = strtok(buffer, "=");

        if(strIt != NULL)
        {
            ParameterMap::iterator mapIt = _mParams.find(std::string(strIt));

            if(mapIt != _mParams.end())
            {
                bEnd = mapIt->second->isLastParam();

                strIt = strtok(NULL, "\n");

                mapIt->second->convert(strIt);
            }
            else
            {
                fprintf(stderr, "Unknown parameter %s\n", strIt);
            }
        }
        else
        {
            bEnd = true;
        }
    }

    buffer[0] = fgetc(pIn);

    if(buffer[0] != '\0')
    {
        fprintf(stderr, "missing 0\n");
        returnValue = false;
    }

    return returnValue;
}

void DBHeader::dump(void) const
{
    fprintf(stderr, "MAGIC       = %u\n", this->uiMagic     );
    fprintf(stderr, "xsize       = %u\n", this->uiXSize     );
    fprintf(stderr, "ysize       = %u\n", this->uiYSize     );
    fprintf(stderr, "zsize       = %u\n", this->uiZSize     );
    fprintf(stderr, "tsteps      = %u\n", this->uiTSteps    );
    fprintf(stderr, "type        = %u\n", this->uiType      );
    fprintf(stderr, "swx         = %f\n", this->rSWx        );
    fprintf(stderr, "swy         = %f\n", this->rSWy        );
    fprintf(stderr, "nwx         = %f\n", this->rNWx        );
    fprintf(stderr, "nwy         = %f\n", this->rNWy        );
    fprintf(stderr, "nex         = %f\n", this->rNEx        );
    fprintf(stderr, "ney         = %f\n", this->rNEy        );
    fprintf(stderr, "sex         = %f\n", this->rSEx        );
    fprintf(stderr, "sey         = %f\n", this->rSEy        );
    fprintf(stderr, "h0          = %f\n", this->rDh         );
    fprintf(stderr, "dh          = %f\n", this->rDh         );
    fprintf(stderr, "t0          = %f\n", this->rT0         );
    fprintf(stderr, "dt          = %f\n", this->rDt         );
    fprintf(stderr, "scaling     = %f\n", this->rScaling    );
    fprintf(stderr, "bias        = %f\n", this->rBias       );
    fprintf(stderr, "extformat   = %u\n", this->uiExtFormat );
    fprintf(stderr, "implformat  = %u\n", this->uiImplFormat);
    fprintf(stderr, "LLWGS84_swx = %f\n", this->LLWGS84_rSWx);
    fprintf(stderr, "LLWGS84_swy = %f\n", this->LLWGS84_rSWy);
    fprintf(stderr, "LLWGS84_nwx = %f\n", this->LLWGS84_rNWx);
    fprintf(stderr, "LLWGS84_nwy = %f\n", this->LLWGS84_rNWy);
    fprintf(stderr, "LLWGS84_nex = %f\n", this->LLWGS84_rNEx);
    fprintf(stderr, "LLWGS84_ney = %f\n", this->LLWGS84_rNEy);
    fprintf(stderr, "LLWGS84_sex = %f\n", this->LLWGS84_rSEx);
    fprintf(stderr, "LLWGS84_sey = %f\n", this->LLWGS84_rSEy);
    fprintf(stderr, "bytes       = %u\n", this->uiBytes     );
}

DBBlockAccessor::~DBBlockAccessor(void)
{
}

bool DBBlockAccessor::isOpen(void)
{
    return false;
}


DBBlockAccessor::DBBlockAccessor(void) :
    Inherited()
{
}

void DBBlockAccessor::open(const Char8 *szFilename)
{
#ifdef OSG_WITH_GDALX
    _pDataset = (GDALDataset *) GDALOpen(szFilename, GA_ReadOnly);

    if(_pDataset != NULL)
    {
        _pGeoRef = GeoReferenceAttachment::create();

        double adfGeoTransform[6];

        if(_pDataset->GetGeoTransform(adfGeoTransform) == CE_None)
        {
            _pGeoRef->editOrigin().setValues(adfGeoTransform[0], 
                                             adfGeoTransform[3]);

            _pGeoRef->editPixelSize().setValues(adfGeoTransform[1], 
                                                adfGeoTransform[5]);

            if(GDALGetProjectionRef(_pDataset) != NULL)
            {
                OGRSpatialReferenceH  hSRS;

                Char8 *szProjection = (char *) GDALGetProjectionRef(_pDataset);
        
                hSRS = OSRNewSpatialReference(NULL);

                if(OSRImportFromWkt(hSRS, &szProjection) == CE_None)
                {
                    _pGeoRef->editEllipsoidAxis().setValues(
                        OSRGetSemiMajor(hSRS, NULL),
                        OSRGetSemiMinor(hSRS, NULL));

                    const Char8 *szDatum = OSRGetAttrValue(hSRS, "DATUM", 0);

                    if(szDatum != NULL && 0 == strcmp(szDatum, "WGS_1984"))
                    {
                        _pGeoRef->editDatum() = 
                            GeoReferenceAttachment::WGS84;
                    }
                    else
                    {
                        fprintf(stderr, "Unknow datum %s\n",
                                szDatum);

                        _pGeoRef->editDatum() = 
                            GeoReferenceAttachment::UnknownDatum;
                    }
                }            

                OSRDestroySpatialReference(hSRS);
            }
        }

        int             nBlockXSize, nBlockYSize;
        int             bGotMin, bGotMax;
        double          adfMinMax[2];
        
        _pBand = _pDataset->GetRasterBand(1);

        _pBand->GetBlockSize(&nBlockXSize, &nBlockYSize);

        adfMinMax[0] = _pBand->GetMinimum(&bGotMin);
        adfMinMax[1] = _pBand->GetMaximum(&bGotMax);

        if(!(bGotMin && bGotMax))
        {
            GDALComputeRasterMinMax((GDALRasterBandH) _pBand, TRUE, adfMinMax);
        }

        if(_pBand != NULL)
        {
            _eImgFormat = Image::OSG_INVALID_PF;

            switch(_pDataset->GetRasterCount())
            {
                case 1:
                    _eImgFormat = Image::OSG_L_PF;
                    break;
                case 2:
                    _eImgFormat = Image::OSG_LA_PF;
                    break;
                case 3:
                    _eImgFormat = Image::OSG_RGB_PF;
                    break;
                case 4:
                    _eImgFormat = Image::OSG_RGBA_PF;
                    break;
            }

            _eImgType = Image::OSG_INVALID_IMAGEDATATYPE;

            switch(_pBand->GetRasterDataType())
            {
                case GDT_Byte:
                    _eImgType = Image::OSG_UINT8_IMAGEDATA;
                    break;

                case GDT_UInt16:
                    _eImgType = Image::OSG_UINT16_IMAGEDATA;
                    break;

                case GDT_Int16:
                    _eImgType = Image::OSG_INT16_IMAGEDATA;
                    break;

                case GDT_UInt32:
                    _eImgType = Image::OSG_UINT32_IMAGEDATA;
                    break;

                case GDT_Int32:
                    _eImgType = Image::OSG_INT32_IMAGEDATA;
                    break;

                case GDT_Float32: 
                    _eImgType = Image::OSG_FLOAT32_IMAGEDATA;
                    break;

                case GDT_Float64:
                case GDT_CInt16: 
                case GDT_CInt32:
                case GDT_CFloat32:
                case GDT_CFloat64:
                default:
                    GDALClose(_pDataset);
                    _pDataset = NULL;
                    break;
        
            }

            _vSize[0] = _pDataset->GetRasterXSize();
            _vSize[1] = _pDataset->GetRasterYSize();

            _fNoDataValue = _pBand->GetNoDataValue();

            _pGeoRef->setNoDataValue(_fNoDataValue);
        }
    }
#endif
}

 bool DBBlockAccessor::readBlockA16(Vec2i   vSampleOrigin,
                                    Int32   iTextureSize,
                                    UInt16 *pTarget,
                                    Int32   iTargetSizeBytes)
{
#ifdef OSG_WITH_GDALX
    OSG_ASSERT(false);

    UInt32 destIdx = 0;

    UInt8 *pDst = (UInt8 *) pTarget;

    Int32 xMin = vSampleOrigin.x();
    Int32 xMax = vSampleOrigin.x() + iTextureSize;

    Int32 yMin = vSampleOrigin.y();
    Int32 yMax = vSampleOrigin.y() + iTextureSize;

    for(UInt32 y = yMin; y < yMax; y++)
    {
        for(UInt32 x = xMin; x < xMax; x++)
        {
            for(UInt32 i = 0; i < 2; i++)
            {
                pDst[destIdx] = 0;

                destIdx++;
            }
        }
        
        destIdx += (iTextureSize - (xMax - xMin)) * 2;
    }
#endif

    return false;
}

bool DBBlockAccessor::readBlockA16(Vec2i   vSampleOrigin,
                                   Int32   iTextureSize,
                                   Int16  *pTarget,
                                   Int32   iTargetSizeBytes)
{
#ifdef OSG_WITH_GDALX
    Int32 xMin = vSampleOrigin.x();
    Int32 xMax = vSampleOrigin.x() + iTextureSize;
    
    Int32 yMin = vSampleOrigin.y();
    Int32 yMax = vSampleOrigin.y() + iTextureSize;
    
    if(xMax > _vSize[0] || yMax > _vSize[1])
    {
        UInt32 destIdx = 0;
        UInt32 srcIdx  = 0;
        
        _vI16Buffer.resize(iTextureSize * iTextureSize);

        Int32 iSampleX = osgMin(_vSize[0] - vSampleOrigin.x(), iTextureSize);
        Int32 iSampleY = osgMin(_vSize[1] - vSampleOrigin.y(), iTextureSize);

        _pBand->RasterIO(GF_Read,
                         vSampleOrigin.x(), 
                         vSampleOrigin.y(),
                         iSampleX, 
                         iSampleY,
                         &(_vI16Buffer[0]),
                         iSampleX, 
                         iSampleY,
                         GDT_Int16,
                         0,
                         0);
        

        for(UInt32 y = yMin; y < yMax; y++)
        {
            for(UInt32 x = xMin; x < xMax; x++)
            {
                if(x >= _vSize[0] || y >= _vSize[1])
                {
                    pTarget[destIdx] = Int16(_fNoDataValue);
                }
                else
                {
                    pTarget[destIdx] = _vI16Buffer[srcIdx];
                    
                    srcIdx++;
                }

                destIdx++;
            }
        }
    }
    else
    {
        _pBand->RasterIO(GF_Read,
                         vSampleOrigin.x(), 
                         vSampleOrigin.y(),
                         iTextureSize, 
                         iTextureSize,
                         pTarget,
                         iTextureSize, 
                         iTextureSize,
                         GDT_Int16,
                         0,
                         0);
    }
#endif

    return true;
}


/*! \class GDALImageFileType 
  
  Image File Type to read/write and store/restore Image objects as
  GDAL (tif/tiff suffix) data.
  
  To be able to load TIFF images you need the IJG TIFF library, 
  (check the Prerequisites page on www.opensg.org). 
  The lib comes with all Linux distributions.
  
  You have to --enable-tif in the configure line to enable
  the singleton object.
  
 */

DBImageFileType DBImageFileType:: _the("image/db",
                                       suffixArray, 
                                       sizeof(suffixArray),
                                       (OSG_READ_SUPPORTED));


//-------------------------------------------------------------------------
/*! Tries to fill the image object with the data read from
    the given fileName. Returns true on success.
 */


bool DBImageFileType::read(      Image       *pImage, 
                           const Char8       *fileName) 
{
    bool returnValue = false;

    FILE *pIn = fopen(fileName, "rb");

    if(pIn != NULL)
    {
        fprintf(stderr, "db::open %p\n", pIn);

        DBHeader oHeader;

        returnValue = oHeader.read(pIn);

        if(returnValue == false)
        {
            fclose(pIn);

            return returnValue;
        }

//        oHeader.dump();

        if(oHeader.uiExtFormat != 0)
        {
            fprintf(stderr, "ext == 0 only support");

            returnValue = false;

            fclose(pIn);

            return returnValue;
        }

        Image::PixelFormat imagePf   = Image::OSG_RGBA_PF;
        Image::Type        imageType = Image::OSG_UINT8_IMAGEDATA;

        switch(oHeader.uiType)
        {
            case 0:
                imagePf   = Image::OSG_L_PF;
                imageType = Image::OSG_UINT8_IMAGEDATA;
                break;
            case 1:
                imagePf   = Image::OSG_L_PF;
                imageType = Image::OSG_INT16_IMAGEDATA;
                break;
            case 2:
                imagePf   = Image::OSG_L_PF;
                imageType = Image::OSG_FLOAT32_IMAGEDATA;
                break;
            case 3:
                imagePf   = Image::OSG_RGB_PF;
                imageType = Image::OSG_UINT8_IMAGEDATA;
                break;
            case 4:
                imagePf   = Image::OSG_RGBA_PF;
                imageType = Image::OSG_UINT8_IMAGEDATA;
                break;
            case 5:
                imagePf   = Image::OSG_RGB_DXT1;
                imageType = Image::OSG_UINT8_IMAGEDATA;
                break;
            case 6:
                imagePf   = Image::OSG_RGBA_DXT1;
                imageType = Image::OSG_UINT8_IMAGEDATA;
                break;
            default:
                break;
        };

        pImage->set(imagePf,
                    oHeader.uiXSize,
                    oHeader.uiYSize,
                    oHeader.uiZSize,
                    1,
                    1,
                    0.0,
                    NULL,
                    imageType,
                    true,
                    1);

        if(pImage->getSize() == oHeader.uiBytes)
        {
            fread(pImage->editData(),
                  sizeof(UInt8),
                  oHeader.uiBytes,
                  pIn);

#if BYTE_ORDER == LITTLE_ENDIAN
            switch(oHeader.uiType)
            {
                case 1:
                    swapAndConvertImageByteOrder< 
                         Int16,
                        &clampMin<Int16, -100, 0> >(pImage);
                    break;
                case 2:
                    swapImageByteOrder<Real32>(pImage);
                    break;
                default:
                    break;
            };
#endif

            if(oHeader.uiXSize != 0 && oHeader.uiYSize != 0)
            {
                if(oHeader.LLWGS84_rSWx != 0.f &&
                   oHeader.LLWGS84_rSWy != 0.f &&
                   oHeader.LLWGS84_rNWx != 0.f &&
                   oHeader.LLWGS84_rNWy != 0.f &&
                   oHeader.LLWGS84_rNEx != 0.f &&
                   oHeader.LLWGS84_rNEy != 0.f &&
                   oHeader.LLWGS84_rSEx != 0.f &&
                   oHeader.LLWGS84_rSEy != 0.f  )
                {
                    GeoReferenceAttachmentUnrecPtr pGeoRef = 
                        GeoReferenceAttachment::create();
                    
                    pGeoRef->setupWGS84Datum();
                    
                    pGeoRef->editOrigin().setValues(oHeader.LLWGS84_rNWx,
                                                    oHeader.LLWGS84_rNWy);
                    
                    pGeoRef->editPixelSize().setValues(
                        (oHeader.LLWGS84_rSEx - 
                         oHeader.LLWGS84_rNWx) / oHeader.uiXSize,
                        (oHeader.LLWGS84_rSEy -
                         oHeader.LLWGS84_rNWy) / oHeader.uiYSize);

                    pImage->addAttachment(pGeoRef);
                }
                else if(oHeader.rSWx != 0.f &&
                        oHeader.rSWy != 0.f &&
                        oHeader.rNWx != 0.f &&
                        oHeader.rNWy != 0.f &&
                        oHeader.rNEx != 0.f &&
                        oHeader.rNEy != 0.f &&
                        oHeader.rSEx != 0.f &&
                        oHeader.rSEy != 0.f  )
                {
                    GeoReferenceAttachmentUnrecPtr pGeoRef = 
                        GeoReferenceAttachment::create();
                    
                    pGeoRef->setupWGS84Datum();
                    
                    pGeoRef->editOrigin().setValues(oHeader.rNWx,
                                                    oHeader.rNWy);
                    
                    pGeoRef->editPixelSize().setValues(
                        (oHeader.rSEx - oHeader.rNWx) / oHeader.uiXSize,
                        (oHeader.rSEy - oHeader.rNWy) / oHeader.uiYSize);

                    pImage->addAttachment(pGeoRef);
                }
            }
        }
        else
        {
            fprintf(stderr, "size mismatch %"PRISize" %d\n",
                    pImage->getSize(),
                    oHeader.uiBytes);

            returnValue = false;
        }

        fclose(pIn);
    }

    return returnValue;

#ifdef OSG_WITH_GDALX

    GDALDataset *pDataset;

    pDataset = (GDALDataset *) GDALOpen(fileName, GA_ReadOnly);

    if(pDataset != NULL)
    {
        GeoReferenceAttachmentPtr pGeoRef = GeoReferenceAttachment::create();

        pImage->addAttachment(pGeoRef);

        double        adfGeoTransform[6];
        
        if(pDataset->GetGeoTransform(adfGeoTransform) == CE_None)
        {
            pGeoRef->editOrigin().setValues(adfGeoTransform[0], 
                                            adfGeoTransform[3]);

            pGeoRef->editPixelSize().setValues(adfGeoTransform[1], 
                                               adfGeoTransform[5]);

            if(GDALGetProjectionRef(pDataset) != NULL)
            {
                OGRSpatialReferenceH  hSRS;

                Char8 *szProjection = (char *) GDALGetProjectionRef(pDataset);
        
                hSRS = OSRNewSpatialReference(NULL);

                if(OSRImportFromWkt(hSRS, &szProjection) == CE_None)
                {
                    pGeoRef->editEllipsoidAxis().setValues(
                        OSRGetSemiMajor(hSRS, NULL),
                        OSRGetSemiMinor(hSRS, NULL));

                    const Char8 *szDatum = OSRGetAttrValue(hSRS, "DATUM", 0);

                    if(szDatum != NULL && 0 == strcmp(szDatum, "WGS_1984"))
                    {
                        pGeoRef->editDatum() = 
                            GeoReferenceAttachment::WGS84;
                    }
                    else
                    {
                        fprintf(stderr, "Unknow datum %s\n",
                                szDatum);

                        pGeoRef->editDatum() = 
                            GeoReferenceAttachment::UnknownDatum;
                    }
                }            

                OSRDestroySpatialReference(hSRS);
            }
        }

        GDALRasterBand *pBand;
        int             nBlockXSize, nBlockYSize;
        int             bGotMin, bGotMax;
        double          adfMinMax[2];
        
        pBand = pDataset->GetRasterBand( 1 );
        pBand->GetBlockSize( &nBlockXSize, &nBlockYSize );

        adfMinMax[0] = pBand->GetMinimum( &bGotMin );
        adfMinMax[1] = pBand->GetMaximum( &bGotMax );

        if(!(bGotMin && bGotMax))
            GDALComputeRasterMinMax((GDALRasterBandH) pBand, TRUE, adfMinMax);

        pBand = pDataset->GetRasterBand(1);

        if(pBand != NULL)
        {
            Image::PixelFormat ePF = Image::OSG_INVALID_PF;

            switch(pDataset->GetRasterCount())
            {
                case 1:
                    ePF = Image::OSG_L_PF;
                    break;
                case 2:
                    ePF = Image::OSG_LA_PF;
                    break;
                case 3:
                    ePF = Image::OSG_RGB_PF;
                    break;
                case 4:
                    ePF = Image::OSG_RGBA_PF;
                    break;
            }

            Image::Type eDT = Image::OSG_INVALID_IMAGEDATATYPE;

            switch(pBand->GetRasterDataType())
            {
                case GDT_Byte:
                    eDT = Image::OSG_UINT8_IMAGEDATA;
                    break;

                case GDT_UInt16:
                    eDT = Image::OSG_UINT16_IMAGEDATA;
                    break;

                case GDT_Int16:
                    eDT = Image::OSG_INT16_IMAGEDATA;
                    break;

                case GDT_UInt32:
                    eDT = Image::OSG_UINT32_IMAGEDATA;
                    break;

                case GDT_Int32:
                    eDT = Image::OSG_INT32_IMAGEDATA;
                    break;

                case GDT_Float32: 
                    eDT = Image::OSG_FLOAT32_IMAGEDATA;
                    break;

                case GDT_Float64:
                case GDT_CInt16: 
                case GDT_CInt32:
                case GDT_CFloat32:
                case GDT_CFloat64:
                default:
                    GDALClose(pDataset);
                    return returnValue;
                    break;
        
            }

            pImage->set(ePF,             
                        pDataset->GetRasterXSize(), 
                        pDataset->GetRasterYSize(),
                        1,
                        1,
                        1,
                        0.0,
                        NULL,
                        eDT);
            
            UChar8 *dst = pImage->editData();

            pBand->RasterIO(GF_Read,
                            0, 
                            0,
                            pDataset->GetRasterXSize(), 
                            pDataset->GetRasterYSize(),
                            dst,
                            pDataset->GetRasterXSize(), 
                            pDataset->GetRasterYSize(),
                            pBand->GetRasterDataType(),
                            0,
                            0);

            pGeoRef->setNoDataValue(pBand->GetNoDataValue());

            returnValue = true;
        }

        GDALClose(pDataset);
    }

    return returnValue;
#endif // OSG_WITH_GDAL
}

//-------------------------------------------------------------------------
/*! Tries to write the image object to the given output stream.
    Returns true on success.
*/

bool DBImageFileType::write(const Image            *OSG_DB_ARG(pImage), 
                            const Char8            *OSG_DB_ARG(fileName)) 
{
    bool                retCode = false;

#ifdef OSG_WITH_GDALX
    if(pImage->getDimension() < 1 || pImage->getDimension() > 2)
    {
        FWARNING(("TIFImageFileType::write: invalid dimension %d!\n",
            pImage->getDimension()));

        return false;
    }

    TIFF         *out = TIFFClientOpen("dummy", "wm", (thandle_t)&os,
                                       osReadProc, 
                                       osWriteProc, 
                                       osSeekProc, 
                                       closeProc,
			                           osSizeProc, 
                                       mapFileProc, 
                                       unmapFileProc);

    int           lineSize = pImage->getWidth() * pImage->getBpp();
    int           photometric = 0;
    int           samplesPerPixel = 0;
    const UChar8 *data;
    int           row;

    // TODO: implement all cases correct
    switch(pImage->getBpp())
    {
        case 1:
            samplesPerPixel = 1;
            photometric = PHOTOMETRIC_MINISBLACK;
            break;
        case 2:
            samplesPerPixel = 2;
            photometric = PHOTOMETRIC_MINISBLACK;
            break;
        case 3:
            samplesPerPixel = 3;
            photometric = PHOTOMETRIC_RGB;
            break;
        case 4:
            samplesPerPixel = 4;
            photometric = PHOTOMETRIC_RGB;
            break;
    }
    
    if(out)
    {
        TIFFSetField(out, TIFFTAG_IMAGEWIDTH, pImage->getWidth());
        TIFFSetField(out, TIFFTAG_IMAGELENGTH, pImage->getHeight());
        TIFFSetField(out, TIFFTAG_XRESOLUTION, pImage->getResX());
        TIFFSetField(out, TIFFTAG_YRESOLUTION, pImage->getResY());
        TIFFSetField(out, TIFFTAG_RESOLUTIONUNIT, pImage->getResUnit());
        TIFFSetField(out, TIFFTAG_ORIENTATION, ORIENTATION_TOPLEFT);
        TIFFSetField(out, TIFFTAG_SAMPLESPERPIXEL, samplesPerPixel);
        TIFFSetField(out, TIFFTAG_BITSPERSAMPLE, 8);
        TIFFSetField(out, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);
        TIFFSetField(out, TIFFTAG_PHOTOMETRIC, photometric);

        if(_options.find("compressionType=LZW") != std::string::npos)
        {
            TIFFSetField(out, TIFFTAG_COMPRESSION, COMPRESSION_LZW);
        }
        else
        {
            TIFFSetField(out, TIFFTAG_COMPRESSION, COMPRESSION_NONE);
        }

        TIFFSetField(out, TIFFTAG_ROWSPERSTRIP, TIFFDefaultStripSize(out, 0));

        for(row = 0; row < pImage->getHeight(); row++)
        {
            data = 
                pImage->getData() + 
                ((pImage->getHeight() - row - 1) * lineSize);

            if(TIFFWriteScanline(out, 
                                 (tdata_t) const_cast<UChar8 *>(data), 
                                 row, 
                                 0) < 0)
            {
                break;
            }
        }
        
        TIFFClose(out);

        retCode = true;
    }

#else
    SWARNING << getMimeType()
             << " write is not compiled into the current binary " 
             << std::endl;
#endif

    return retCode;
}

bool DBImageFileType::validateHeader(const Char8 *fileName, bool &implemented)
{
    implemented = true;

    return true;
}

#if 1
ImageBlockAccessorPtr DBImageFileType::open(const Char8 *fileName)
{
    DBBlockAccessorPtr returnValue(new DBBlockAccessor);

    returnValue->open(fileName);

    return returnValue;
}
#endif

//-------------------------------------------------------------------------
/*! Constructor used for the singleton object
 */

DBImageFileType::DBImageFileType(const Char8  *mimeType,
                                 const Char8  *suffixArray[],
                                       UInt16  suffixByteCount,
                                       UInt32  flags) :
    Inherited(mimeType,
              suffixArray, 
              suffixByteCount, 
              flags          )
{
}

//-------------------------------------------------------------------------
/*! Destructor
 */

DBImageFileType::~DBImageFileType(void)
{
}

OSG_END_NAMESPACE
