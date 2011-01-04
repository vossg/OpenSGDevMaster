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

#ifndef _OSGPNGIMAGEFILETYPE_H_
#define _OSGPNGIMAGEFILETYPE_H_

#ifdef  __sgi
#pragma  once
#endif

#include "OSGImageFileIODef.h"
#include "OSGImageFileType.h"

OSG_BEGIN_NAMESPACE

/*! \brief PNG File Handler. 
    See \ref PageSystemImage for a detailed description.

    \ingroup GrpImageFileIOPNG
    \ingroup GrpLibOSGImageFileIO
 */

class OSG_IMGFILEIO_DLLMAPPING PNGImageFileType : public ImageFileType
{

    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~PNGImageFileType (void);

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
    /*---------------------------------------------------------------------*/
    /*! \name                   Read/Write                                 */
    /*! \{                                                                 */

    virtual std::string determineMimetypeFromStream(std::istream &is);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Read/Write                                 */
    /*! \{                                                                 */

    virtual bool validateHeader(const Char8    *fileName, 
                                      bool     &implemented);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Buffer                                   */
    /*! \{                                                                 */

    virtual UInt64 restoreData(      Image            *pImage, 
                               const UChar8           *buffer,
                                     Int32             memSize = -1);

    virtual UInt64 storeData  (const Image            *pImage, 
                                     UChar8           *buffer,
                                     Int32             memSize = -1);
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name               Default Constructor                            */
    /*! \{                                                                 */

    PNGImageFileType(const Char8  *mimeType,
                     const Char8  *suffixArray[], 
                           UInt16  suffixByteCount,
                           UInt32  flags          );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                         Copy Op                              */
    /*! \{                                                                 */

          PNGImageFileType            (const PNGImageFileType &obj);
    const PNGImageFileType &operator =(const PNGImageFileType &obj);

    /*! \}                                                                 */
    /*===========================  PRIVATE  ===============================*/

  private:

    typedef ImageFileType Inherited;

    static PNGImageFileType _the;

};

typedef PNGImageFileType *PNGImageFileTypeP;

OSG_END_NAMESPACE

#endif // _OSGPNGIMAGEFILETYPE_H_
