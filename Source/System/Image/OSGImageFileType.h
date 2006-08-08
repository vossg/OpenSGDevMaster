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

#ifndef _OSGIMAGEFILETYPE_H_
#define _OSGIMAGEFILETYPE_H_

#include <list>

#include "OSGImage.h"

OSG_BEGIN_NAMESPACE

/*! \brief Abstract Base ImageFileType. Defines the Interface for
all concrete ImageFileTypes. See \ref PageSystemImage for detailed description.
*/

class OSG_SYSTEM_DLLMAPPING ImageFileType 
{

    /*==========================  PUBLIC  =================================*/
    
  public:
    
    /*---------------------------------------------------------------------*/
    /*! \name                     Flags                                    */
    /*! \{                                                                 */
  
    enum
    {
        OSG_READ_SUPPORTED  = 1,
        OSG_WRITE_SUPPORTED = 2
    };
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~ImageFileType(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Get  Methods                              */
    /*! \{                                                                 */
    
    const      Char8             *getMimeType  (void) const;

    const std::list<std::string> &getSuffixList(void) const;
    
    virtual    UInt32             getFlags     (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Read/Write                                 */
    /*! \{                                                                 */

    virtual bool read          (      ImagePtrArg       pImage, 
                                const Char8            *fileName   ) ;

    virtual bool write         (      ImageConstPtrArg  pImage, 
                                const Char8            *fileName   ) ;

    virtual bool read          (      ImagePtrArg       pImage, 
                                      std::istream     &is, 
                                const std::string      &mimetype);

    virtual bool write         (const ImageConstPtrArg  pImage, 
                                      std::ostream     &os, 
                                const std::string      &mimetype);

    virtual bool validateHeader(const Char8            *fileName, 
                                      bool             &implemented);


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Type                                  */
    /*! \{                                                                 */

    virtual std::string determineMimetypeFromStream(std::istream &is);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name              static store/restore                            */
    /*! \{                                                                 */

    static UInt64 restore(      ImagePtrArg       pImage, 
                          const UChar8           *buffer,
                                Int32             memSize = -1);

    static UInt64 store  (      ImageConstPtrArg  pImage,
                          const Char8            *mimeType,
                                UChar8           *buffer, 
                                Int32             memSize = -1);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Raw Store/Restore                           */
    /*! \{                                                                 */

    virtual UInt64 restoreData(      ImagePtrArg       pImage, 
                               const UChar8           *buffer,
                                     Int32             memSize = -1);

    virtual UInt64 storeData  (      ImageConstPtrArg  pImage, 
                                     UChar8           *buffer,
                                     Int32             memSize = -1);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   store/restore                              */
    /*! \{                                                                 */

           UInt64 store         (ImageConstPtrArg  pImage, 
                                 UChar8           *buffer,
                                 Int32             memSize = -1);
    
    virtual UInt64 maxBufferSize(ImageConstPtrArg   image       );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       dump                                   */
    /*! \{                                                                 */

    void dump(void);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                   MTD Header                                 */
    /*! \{                                                                 */

    struct OSG_SYSTEM_DLLMAPPING Head
    {
        Char8          mimeType[8];
        
        unsigned short pixelFormat;
        unsigned short width;
        unsigned short height;
        unsigned short depth;
        unsigned short mipmapCount;
        unsigned short frameCount;
        unsigned short frameDelay;
        unsigned short sideCount;
        unsigned short dataType;
        unsigned short _reserved3;
        unsigned short _reserved4;
        unsigned short attachmentSize;

        bool netToHost(void);
        bool hostToNet(void);
    };

    /*! \}                                                                 */

    /*---------------------------------------------------------------------*/
    /*! \name                Default Constructor                           */
    /*! \{                                                                 */

    ImageFileType(const Char8  *mimeType,
                  const Char8  *suffixArray[], 
                        UInt16  suffixByteCount,
                        UInt32  flags = OSG_READ_SUPPORTED);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Copy Op                                  */
    /*! \{                                                                 */

          ImageFileType            (const ImageFileType &obj);
    const ImageFileType &operator =(const ImageFileType &obj);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    std::list<std::string> _suffixList;

         IDString          _mimeType;

         UInt32            _flags;
};

typedef ImageFileType *ImageFileTypeP;

OSG_END_NAMESPACE

#endif // _OSGIMAGEFILETYPE_H_
