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

#ifndef _OSGIMAGEFILEHANDLER_H_
#define _OSGIMAGEFILEHANDLER_H_

#ifdef  __sgi
#pragma  once
#endif

#include <list>
#include <map>

#include "OSGSystemDef.h"
#include "OSGIDStringLink.h"
#include "OSGImageFileType.h"
#include "OSGSingletonHolder.h"


OSG_BEGIN_NAMESPACE

class PathHandler;

/*! \brief Image file Handler. Used to read/write and store/restore image data.
    See \ref PageSystemImage for a detailed description.
*/

class OSG_SYSTEM_DLLMAPPING ImageFileHandlerBase 
{

    friend class ImageFileType;

    /*==========================  PUBLIC  =================================*/

  public:

    typedef ImageTransitPtr (*ReadCB) (const Char8 *fileName, 
                                       const Char8 *mimeType);

    /*---------------------------------------------------------------------*/
    /*! \name                   Read/Write                                 */
    /*! \{                                                                 */

    virtual ImageTransitPtr read (const Char8            *fileName, 
                                  const Char8            *mimeType = 0);

    virtual bool            read (      ImagePtrArg       pImage,
                                  const Char8            *fileName, 
                                  const Char8            *mimeType = 0);

    virtual bool            write(      ImageConstPtrArg  pImage,
                                  const Char8            *fileName, 
                                  const Char8            *mimeType = 0);


    virtual ImageTransitPtr read (      std::istream     &is,
                                  const std::string      &mimeType    );

    virtual bool            read (      ImagePtrArg       pImage,
                                        std::istream     &is,
                                  const std::string      &mimeType    );

    virtual bool            write(      ImageConstPtrArg  pImage,
                                        std::ostream     &os,
                                  const std::string      &mimeType    );

    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Read Callback                              */
    /*! \{                                                                 */

    void   setReadCB(ReadCB pCB);
    ReadCB getReadCB(void      );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   PathHandler                                */
    /*! \{                                                                 */

    virtual PathHandler *getPathHandler(void                     );
    virtual void         setPathHandler(PathHandler *pPathHandler);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Options                                    */
    /*! \{                                                                 */

    virtual       bool          setOptions(const Char8 *suffix, 
                                           const Char8 *options);
    virtual const Char8        *getOptions(const Char8 *suffix);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Storage                                  */
    /*! \{                                                                 */

    virtual UInt64  restore(      ImagePtrArg       pImage,
                            const UChar8           *buffer, 
                                  Int32             memSize = -1);

    virtual UInt64  store  (      ImageConstPtrArg  pImage, 
                            const Char8            *mimeType,
                                  UChar8           *buffer, 
                                  Int32             memSize = -1);

    virtual UChar8 *store  (      ImageConstPtrArg  pImage, 
                                  UInt64           &memSize,
                            const Char8            *mimeType = 0);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Get Types                                  */
    /*! \{                                                                 */

    ImageFileType *getFileType   (const Char8 *mimeType,
                                  const Char8 *fileName       = 0,
                                        bool   validateHeader = false);

    ImageFileType *getDefaultType(void);


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Get MimeTypes                              */
    /*! \{                                                                 */

    std::string    determineMimetypeFromName  (const std::string  &fileName);

    std::string    determineMimetypeFromStream(      std::istream &is      );

    std::string    determineMimetypeFromSuffix(const std::string  &suffix  );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Get Types                                  */
    /*! \{                                                                 */

    virtual int getSuffixList(
        std::list<const Char8*> &suffixList,
             UInt32              flags = (ImageFileType::OSG_READ_SUPPORTED |
                                          ImageFileType::OSG_WRITE_SUPPORTED));

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Print                                     */
    /*! \{                                                                 */

    void dump(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Get Method                                  */
    /*! \{                                                                 */

    /*! \}                                                                 */

    /*=========================  PROTECTED  ===============================*/

  protected:
    
    typedef std::map<std::string, ImageFileType *> TypeMap;

    ReadCB       _pReadCallback;

    PathHandler *_pPathHandler;

    TypeMap      _suffixTypeMap;
    TypeMap      _mimeTypeMap;

    static const std::string _fileNameKey;
    static const std::string _fullFilePathKey;

           bool addImageFileType (ImageFileType &fileType);

    static void normalizeMimetype(std::string   &mimetype);

    static void normalizeSuffix  (std::string   &suffix  );

    /*==========================  PRIVATE  ================================*/

  private:

    template <class SingletonT>
    friend class SingletonHolder;

    /*---------------------------------------------------------------------*/
    /*! \name               Constructor                                    */
    /*! \{                                                                 */

    ImageFileHandlerBase(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Copy Op                                    */
    /*! \{                                                                 */

          ImageFileHandlerBase            (const ImageFileHandlerBase &obj);
    const ImageFileHandlerBase &operator =(const ImageFileHandlerBase &obj);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~ImageFileHandlerBase(void);

    /*! \}                                                                 */
};

#if defined(WIN32)
#    if !defined(OSG_COMPILE_IMAGEFILEHANDLER)
OSG_SYSTEM_EXPIMP_TMPL 
template class OSG_SYSTEM_DLLMAPPING SingletonHolder<ImageFileHandlerBase>;
#    endif
#endif

typedef SingletonHolder<ImageFileHandlerBase> ImageFileHandler;

typedef ImageFileHandler *ImageFileHandlerP;

OSG_END_NAMESPACE

#endif // _OSGIMAGEFILEHANDLER_H_
