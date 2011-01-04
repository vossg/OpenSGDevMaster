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

#ifndef _OSGDBIMAGEFILETYPE_H_
#define _OSGDBIMAGEFILETYPE_H_
#ifdef  __sgi
#pragma  once
#endif

#include "OSGImageFileIODef.h"
#include "OSGImageFileType.h"

#include "boost/shared_ptr.hpp"
#include "map"

OSG_BEGIN_NAMESPACE

class DBImageFileType;

/*! \ingroup GrpImageFileIODB
    \nohierarchy
 */

class DBHeaderParameter
{
  protected:

    bool _bLastParam;

  public:

    DBHeaderParameter(void);
    ~DBHeaderParameter(void);

    void setLastParam(void);
    bool isLastParam (void);

    virtual void convert(const Char8 *str) = 0;
};

/*! \ingroup GrpImageFileIODB
    \nohierarchy
 */

class DBHeaderIntParameter : public DBHeaderParameter
{
    typedef DBHeaderParameter Inherited;

  protected:
    
    UInt32 &_uiParam;

  public:
    
    DBHeaderIntParameter(UInt32 &uiParam);
    ~DBHeaderIntParameter(void);

    virtual void convert(const Char8 *str);
};

/*! \ingroup GrpImageFileIODB
    \nohierarchy
 */

class DBHeaderFloatParameter : public DBHeaderParameter
{
    typedef DBHeaderParameter Inherited;

  protected:
    
    Real32 &_rParam;

  public:
    
    DBHeaderFloatParameter(Real32 &rParam);
    ~DBHeaderFloatParameter(void);

    virtual void convert(const Char8 *str);
};

/*! \ingroup GrpImageFileIODB
    \nohierarchy
 */

struct DBHeader 
{
    UInt32 uiMagic;  //=13048  ::: magic number
    UInt32 uiXSize;  //=%u     ::: mandatory width
    UInt32 uiYSize;  //=%u     ::: mandatory height for 2+D, 1 for 1D data
    UInt32 uiZSize;  //=%u     ::: mandatory depth for 3+D, 1 for 1D and 2D data
    UInt32 uiTSteps; //=%u    ::: mandatory number of time steps for 4D, 
                     // 1 for 1D, 2D and 3D data

    UInt32 uiType;   //=%u      ::: mandatory cell type: 0 = unsigned byte, 1 =
                     //signed short, 2 = float, 3 = RGB, 4 = RGBA, 5 =
                     //compressed RGB (S3TC DXT1), 6 = compressed RGBA (S3TC
                     //DXT1 with 1-bit alpha) 

    Real32 rSWx;     //%g       ::: x-component of south west corner (should
                     //%be supplied for tile sets) 
    Real32 rSWy;     //=%g       ::: y-component of south west corner (should
                     //be supplied for tile sets) 
    Real32 rNWx;     //=%g       ::: x-component of north west corner (should
                     //be supplied for tile sets) 
    Real32 rNWy;     //=%g       ::: y-component of north west corner (should
                     //be supplied for tile sets) 

    Real32 rNEx;     //=%g       ::: x-component of north east corner (should
                     //be supplied for tile sets) 
    Real32 rNEy;     //=%g       ::: y-component of north east corner (should
                     //be supplied for tile sets) 
    Real32 rSEx;     //=%g       ::: x-component of south east corner (should
                     //be supplied for tile sets) 
    Real32 rSEy;     //=%g       ::: y-component of south east corner (should
                     //be supplied for tile sets) 
    Real32 rH0;      //=%g        ::: base elevation of 3D or 4D data cube
    Real32 rDh;      //=%g        ::: height of the 3D or 4D cube
    Real32 rT0;      //=%g        ::: starting time of 4D series
    Real32 rDt;      //=%g        ::: time step of 4D series
    
    Real32 rScaling; //=%g   ::: elevation scaling parameter for height fields
                     //(default is 1) 
    Real32 rBias;    //=%g      ::: elevation bias parameter for height fields
                     //(default is 0) 

    UInt32 uiExtFormat; //=%u ::: external format indicator: a value!=0
                        //triggers conversion hook (default 0, 1 reserved for
                        //JPEG, 2 for PNG) 
    UInt32 uiImplFormat;//implicit format indicator


    Real32 LLWGS84_rSWx;//%g       ::: x-component of south west corner (should
                        //%be supplied for tile sets) 
    Real32 LLWGS84_rSWy;//=%g       ::: y-component of south west corner (should
                        //be supplied for tile sets) 
    Real32 LLWGS84_rNWx;//=%g       ::: x-component of north west corner (should
                        //be supplied for tile sets) 
    Real32 LLWGS84_rNWy;//=%g       ::: y-component of north west corner (should
                        //be supplied for tile sets) 

    Real32 LLWGS84_rNEx;//=%g       ::: x-component of north east corner (should
                        //be supplied for tile sets) 
    Real32 LLWGS84_rNEy;//=%g       ::: y-component of north east corner (should
                        //be supplied for tile sets) 
    Real32 LLWGS84_rSEx;//=%g       ::: x-component of south east corner (should
                        //be supplied for tile sets) 
    Real32 LLWGS84_rSEy;//=%g       ::: y-component of south east corner (should
                        //be supplied for tile sets) 

    UInt32 uiBytes;     //=%u     ::: mandatory byte length of the following
                        //data chunk}; 

    typedef std::map<std::string, DBHeaderParameter *> ParameterMap;

    ParameterMap _mParams;

    DBHeader(void);
    ~DBHeader(void);

    bool read(FILE *pIn);
    void dump(void     ) const;
};

/*! \ingroup GrpImageFileIODB
    \ingroup GrpLibOSGImageFileIO
 */

class OSG_IMGFILEIO_DLLMAPPING DBBlockAccessor : public ImageBlockAccessor
{

    /*==========================  PUBLIC  =================================*/
    
  public:

    typedef ImageBlockAccessor Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~DBBlockAccessor(void);

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

    /*---------------------------------------------------------------------*/
    /*! \name                Default Constructor                           */
    /*! \{                                                                 */

    DBBlockAccessor(void);

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

    friend class DBImageFileType;
};

/*! \ingroup GrpImageFileIODB
 */

typedef boost::shared_ptr<DBBlockAccessor> DBBlockAccessorPtr;

/*! \brief GDAL File Handler. Used to read/write TIFF files.
    See \ref PageSystemImage for a detailed description.

    \ingroup GrpImageFileIODB
    \ingroup GrpLibOSGImageFileIO
 */

class OSG_IMGFILEIO_DLLMAPPING DBImageFileType : public ImageFileType
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~DBImageFileType(void);

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

    DBImageFileType (const Char8  *mimeType,
                     const Char8  *suffixArray[], 
                           UInt16  suffixByteCount,
                           UInt32  flags );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Copy Op                                 */
    /*! \{                                                                 */

          DBImageFileType            (const DBImageFileType &obj);
    const DBImageFileType &operator =(const DBImageFileType &obj);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    typedef ImageFileType Inherited;

    static DBImageFileType _the;
};

typedef DBImageFileType *DBImageFileTypeP;

OSG_END_NAMESPACE

#endif // _OSGDBIMAGEFILETYPE_H_
