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

#ifndef _OSGGDALIMAGEFILETYPE_H_
#define _OSGGDALIMAGEFILETYPE_H_
#ifdef  __sgi
#pragma  once
#endif

#include "OSGImageFileIODef.h"
#include "OSGImageFileType.h"

#include "boost/shared_ptr.hpp"

#ifdef OSG_WITH_GDAL
#include "gdal/gdal_priv.h"
#include "gdal/ogr_srs_api.h"
#endif

OSG_BEGIN_NAMESPACE

class GDALImageFileType;

/*! \ingroup GrpImageFileIOGDAL
    \ingroup GrpLibOSGImageFileIO
 */

class OSG_IMGFILEIO_DLLMAPPING GDALBlockAccessor : public ImageBlockAccessor
{

    /*==========================  PUBLIC  =================================*/
    
  public:

    typedef ImageBlockAccessor Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~GDALBlockAccessor(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Read/Write                                 */
    /*! \{                                                                 */

    virtual bool isOpen(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Read/Write                                 */
    /*! \{                                                                 */

    virtual bool readBlockA16(Vec2i   vSampleOrigin,
                              Int32   iTextureSize,
                              UInt16 *pTarget,
                              Int32   iTargetSizeBytes);

    virtual bool readBlockA16(Vec2i   vSampleOrigin,
                              Int32   iTextureSize,
                              Int16  *pTarget,
                              Int32   iTargetSizeBytes);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

#ifdef OSG_WITH_GDAL
    GDALDataset               *_pDataset;
    GDALRasterBand            *_pBand;
#endif

    std::vector<Int16>         _vI16Buffer;

    /*---------------------------------------------------------------------*/
    /*! \name                Default Constructor                           */
    /*! \{                                                                 */

    GDALBlockAccessor(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Read/Write                                 */
    /*! \{                                                                 */

    void open(const Char8 *szFilename);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Read/Write                                 */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class GDALImageFileType;
};

/*! \ingroup GrpImageFileIOGDAL
 */

typedef boost::shared_ptr<GDALBlockAccessor> GDALBlockAccessorPtr;

/*! \brief GDAL File Handler. Used to read/write TIFF files.
    See \ref PageSystemImage for a detailed description.

    \ingroup GrpImageFileIOGDAL
    \ingroup GrpLibOSGImageFileIO
*/

class OSG_IMGFILEIO_DLLMAPPING GDALImageFileType : public ImageFileType
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~GDALImageFileType(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Read/Write                                 */
    /*! \{                                                                 */

    virtual bool read          (      Image            *pImage, 
                                const Char8            *fileName   ) ;

    virtual bool write         (const Image            *pImage, 
                                const Char8            *fileName   ) ;

    virtual bool validateHeader(const Char8            *fileName, 
                                      bool             &implemented);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Type                                  */
    /*! \{                                                                 */

#if 1
    virtual ImageBlockAccessorPtr open(const Char8 *fileName);
#endif

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name               Default Constructor                            */
    /*! \{                                                                 */

    GDALImageFileType (const Char8  *mimeType,
                       const Char8  *suffixArray[], 
                             UInt16  suffixByteCount,
                             UInt32  flags );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Copy Op                                 */
    /*! \{                                                                 */

          GDALImageFileType            (const GDALImageFileType &obj);
    const GDALImageFileType &operator =(const GDALImageFileType &obj);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    typedef ImageFileType Inherited;

    static GDALImageFileType _the;
};

typedef GDALImageFileType *GDALImageFileTypeP;

OSG_END_NAMESPACE

#endif // _OSGGDALIMAGEFILETYPE_H_
