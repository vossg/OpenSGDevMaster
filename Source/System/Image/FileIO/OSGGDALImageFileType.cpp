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
#if __GNUC__ >= 4 || __GNUC_MINOR__ >=3
#pragma GCC diagnostic warning "-Wold-style-cast"
#endif

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#include "OSGGDALImageFileType.h"
#include "OSGGeoReferenceAttachment.h"

#ifdef OSG_WITH_GDAL
#include "gdal_priv.h"
#include "ogr_srs_api.h"
#include "cpl_multiproc.h"
#endif


#ifndef OSG_DO_DOC
#    ifdef OSG_WITH_GDAL
#        define OSG_GDAL_ARG(ARG) ARG
#    else
#        define OSG_GDAL_ARG(ARG)
#    endif
#else
#    define OSG_GDAL_ARG(ARG) ARG
#endif

// Static Class Varible implementations:
static const OSG::Char8 *suffixArray[] = 
{
    "gtif", "gtiff", "hdf4", "adf"
};

OSG_BEGIN_NAMESPACE

GDALBlockAccessor::~GDALBlockAccessor(void)
{
#ifdef OSG_WITH_GDAL
    GDALClose(_pDataset);
#endif
}

bool GDALBlockAccessor::isOpen(void)
{
#ifdef OSG_WITH_GDAL
    return (_pDataset != NULL);
#else
    return false;
#endif
}


GDALBlockAccessor::GDALBlockAccessor(void) :
     Inherited (    ),
#ifdef OSG_WITH_GDAL
    _pDataset  (NULL),
    _pBand     (NULL),
#endif
    _vI16Buffer(    )
{
}

void GDALBlockAccessor::open(const Char8 *szFilename)
{
#ifdef OSG_WITH_GDAL
    _pDataset = static_cast<GDALDataset *>(GDALOpen(szFilename, GA_ReadOnly));

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

                Char8 *szProjection = 
                    const_cast<char *>(GDALGetProjectionRef(_pDataset));
        
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
            GDALComputeRasterMinMax(GDALRasterBandH(_pBand), TRUE, adfMinMax);
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

 bool GDALBlockAccessor::readBlockA16(Vec2i   vSampleOrigin,
                                      Int32   iTextureSize,
                                      UInt16 *pTarget,
                                      Int32   iTargetSizeBytes)
{
#ifdef OSG_WITH_GDAL
    OSG_ASSERT(false);

    UInt32 destIdx = 0;

    UInt8 *pDst = reinterpret_cast<UInt8 *>(pTarget);

    Int32 xMin = vSampleOrigin.x();
    Int32 xMax = vSampleOrigin.x() + iTextureSize;

    Int32 yMin = vSampleOrigin.y();
    Int32 yMax = vSampleOrigin.y() + iTextureSize;

    for(Int32 y = yMin; y < yMax; y++)
    {
        for(Int32 x = xMin; x < xMax; x++)
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

bool GDALBlockAccessor::readBlockA16(Vec2i   vSampleOrigin,
                                     Int32   iTextureSize,
                                     Int16  *pTarget,
                                     Int32   iTargetSizeBytes)
{
#ifdef OSG_WITH_GDAL
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

        CPLErr res = _pBand->RasterIO(GF_Read,
                                      vSampleOrigin.x(), 
                                      vSampleOrigin.y(),
                                      iSampleX, 
                                      iSampleY,
                                      &(_vI16Buffer[0]),
                                      iSampleX, 
                                      iSampleY,
                                      GDT_Int16,
                                      0,
                                      0                );
        
        if(res == CE_Failure || res == CE_Fatal)
            return false;

        for(Int32 y = yMin; y < yMax; y++)
        {
            for(Int32 x = xMin; x < xMax; x++)
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
        CPLErr res = _pBand->RasterIO(GF_Read,
                                      vSampleOrigin.x(), 
                                      vSampleOrigin.y(),
                                      iTextureSize, 
                                      iTextureSize,
                                      pTarget,
                                      iTextureSize, 
                                      iTextureSize,
                                      GDT_Int16,
                                      0,
                                      0                );

        if(res == CE_Failure || res == CE_Fatal)
            return false;
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

GDALImageFileType GDALImageFileType:: _the("image/gdal",
                                           suffixArray, 
                                           sizeof(suffixArray),
                                           (OSG_READ_SUPPORTED));


//-------------------------------------------------------------------------
/*! Tries to fill the image object with the data read from
    the given fileName. Returns true on success.
 */

bool GDALImageFileType::read(      Image       *OSG_GDAL_ARG(pImage), 
                             const Char8       *OSG_GDAL_ARG(fileName)) 
{
#ifdef OSG_WITH_GDAL
    bool returnValue = false;

    GDALDataset *pDataset;

    pDataset = static_cast<GDALDataset *>(GDALOpen(fileName, GA_ReadOnly));

    if(pDataset != NULL)
    {
        GeoReferenceAttachmentUnrecPtr pGeoRef = 
            GeoReferenceAttachment::create();

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

                Char8 *szProjection = 
                    const_cast<char *>(GDALGetProjectionRef(pDataset));
        
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
            GDALComputeRasterMinMax(GDALRasterBandH(pBand), TRUE, adfMinMax);

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

            CPLErr res = pBand->RasterIO(GF_Read,
                                         0, 
                                         0,
                                         pDataset->GetRasterXSize(), 
                                         pDataset->GetRasterYSize(),
                                         dst,
                                         pDataset->GetRasterXSize(), 
                                         pDataset->GetRasterYSize(),
                                         pBand->GetRasterDataType(),
                                         0,
                                         0                         );

            if(res == CE_Failure || res == CE_Fatal)
                return returnValue;

            pGeoRef->setNoDataValue(pBand->GetNoDataValue());

            returnValue = true;
        }

        GDALClose(pDataset);
    }

    return returnValue;

#else

    SWARNING << getMimeType()
             << " read is not compiled into the current binary "
             << std::endl;
    return false;

#endif // OSG_WITH_GDAL
}

//-------------------------------------------------------------------------
/*! Tries to write the image object to the given output stream.
    Returns true on success.
*/

bool GDALImageFileType::write(const Image            *OSG_GDAL_ARG(pImage), 
                              const Char8            *OSG_GDAL_ARG(fileName)) 
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

bool GDALImageFileType::validateHeader(const Char8 *fileName, bool &implemented)
{
    implemented = true;

    return true;
}

#if 1
ImageBlockAccessorPtr GDALImageFileType::open(const Char8 *fileName)
{
    GDALBlockAccessorPtr returnValue(new GDALBlockAccessor);

    returnValue->open(fileName);

    return returnValue;
}
#endif

//-------------------------------------------------------------------------
/*! Constructor used for the singleton object
 */

GDALImageFileType::GDALImageFileType(const Char8  *mimeType,
                                     const Char8  *suffixArray[],
                                           UInt16  suffixByteCount,
                                           UInt32  flags) :
    Inherited(mimeType,
              suffixArray, 
              suffixByteCount, 
              flags          )
{
//    static bool initTIFFLib = true;
    
#ifdef OSG_WITH_GDAL
    GDALAllRegister();
#endif
}

//-------------------------------------------------------------------------
/*! Destructor
 */

GDALImageFileType::~GDALImageFileType(void)
{
#ifdef OSG_WITH_GDAL
    GDALDestroyDriverManager();
    CPLCleanupTLS();
#endif
}

OSG_END_NAMESPACE
