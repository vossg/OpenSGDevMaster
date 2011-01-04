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

#ifndef _OSGTGAIMAGEFILETYPE_H_
#define _OSGTGAIMAGEFILETYPE_H_

#ifdef  __sgi
#pragma  once
#endif

#include "OSGImageFileIODef.h"
#include "OSGImageFileType.h"

OSG_BEGIN_NAMESPACE

/*! \brief TGA File Handler. Used to read/write TGA files.
    See \ref PageSystemImage for a detailed description.

    \ingroup GrpImageFileIOTGA
    \ingroup GrpLibOSGImageFileIO
 */

class OSG_IMGFILEIO_DLLMAPPING TGAImageFileType : public ImageFileType
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~TGAImageFileType(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Read/Write                                 */
    /*! \{                                                                 */

    virtual bool read (      Image            *pImage, 
                             std::istream     &is, 
                       const std::string      &mimetype);

    virtual bool write(const Image            *pImage, 
                             std::ostream     &os, 
                       const std::string      &mimetype);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name               Default Constructor                            */
    /*! \{                                                                 */

    TGAImageFileType(const Char8  *mimeType,
                     const Char8  *suffixArray[], 
                           UInt16  suffixByteCount);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Copy Op                                  */
    /*! \{                                                                 */

          TGAImageFileType            (const TGAImageFileType &obj);
    const TGAImageFileType &operator =(const TGAImageFileType &obj);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    // header struct

    /*! \nohierarchy
     */

    struct TGAHeader
    {
        UInt8   idLength;
        UInt8   colorMapType;
        UInt8   imageType;
        UInt16  cmapFirst;
        UInt16  cmapLength;
        UInt8   cmapEntrySize;
        UInt16  xOrigin;
        UInt16  yOrigin;
        UInt16  width;
        UInt16  height;
        UInt8   depth;
        UInt8   descriptor;
    };

    bool readHeader             (std::istream &is, TGAHeader   &header);
    bool readCompressedImageData(std::istream &is, Image       *pImage);

    typedef ImageFileType Inherited;

    static TGAImageFileType _the;
};

typedef TGAImageFileType *TGAImageFileTypeP;

OSG_END_NAMESPACE

#endif // _OSGTGAIMAGEFILETYPE_H_
