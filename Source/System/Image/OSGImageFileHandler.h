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
#include "OSGImageFileType.h"
#include "OSGSingletonHolder.h"

#include "boost/shared_ptr.hpp"

OSG_BEGIN_NAMESPACE

class PathHandler;
class ImageBlockAccessor;

/*! \brief Image file Handler. Used to read/write and store/restore image data.
    See \ref PageSystemImage for a detailed description.

    \ingroup GrpSystemImageFileIOBase
    \ingroup GrpLibOSGSystem
 */

class OSG_SYSTEM_DLLMAPPING ImageFileHandlerBase 
{

    friend class ImageFileType;

    /*==========================  PUBLIC  =================================*/

  public:

    typedef ImageTransitPtr (*ReadCB) (const Char8 *fileName, 
                                       const Char8 *mimeType);

    typedef boost::shared_ptr<ImageBlockAccessor> ImageBlockAccessorPtr;

    /*---------------------------------------------------------------------*/
    /*! \name                   Read/Write                                 */
    /*! \{                                                                 */

    virtual ImageTransitPtr read (const Char8            *fileName, 
                                  const Char8            *mimeType = 0);

    virtual bool            read (      Image            *pImage,
                                  const Char8            *fileName, 
                                  const Char8            *mimeType = 0);

    virtual bool            write(      Image const      *pImage,
                                  const Char8            *fileName, 
                                  const Char8            *mimeType = 0);


    virtual ImageTransitPtr read (      std::istream     &is,
                                  const std::string      &mimeType    );

    virtual bool            read (      Image            *pImage,
                                        std::istream     &is,
                                  const std::string      &mimeType    );

    virtual bool            write(      Image const      *pImage,
                                        std::ostream     &os,
                                  const std::string      &mimeType    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Read Callback                              */
    /*! \{                                                                 */

    virtual ImageBlockAccessorPtr open(const Char8 *fileName, 
                                       const Char8 *mimeType = 0);
    
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

    template <class ValueTypeT>
    bool              setOptionAs(const std::string &suffix,
                                  const std::string &name,
                                  const ValueTypeT  &value  );
    bool              setOption  (const std::string &suffix,
                                  const std::string &name,
                                  const std::string &value  );
    
    bool              unsetOption(const std::string &suffix,
                                  const std::string &name   );
      
    template <class ValueTypeT>
    bool              getOptionAs(const std::string &suffix,
                                  const std::string &name,
                                        ValueTypeT  &value  );
    bool              getOption  (const std::string &suffix,
                                  const std::string &name,
                                        std::string &value  );
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Storage                                  */
    /*! \{                                                                 */

    virtual UInt64  restore(      Image            *pImage,
                            const UChar8           *buffer, 
                                  Int32             memSize = -1);

    virtual UInt64  store  (      Image const      *pImage, 
                            const Char8            *mimeType,
                                  UChar8           *buffer, 
                                  Int32             memSize = -1);

    virtual UChar8 *store  (      Image const      *pImage, 
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

    typedef std::map<std::string, ImageFileType *> TypeMap;

    const TypeMap& getSuffixTypeMap() const;

    const TypeMap& getMimeTypeMap()   const;

    /*! \}                                                                 */

    /*=========================  PROTECTED  ===============================*/

  protected:
    
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

/*! \typedef OSG::SingletonHolder<OSG::ImageFileHandlerBase> ImageFileHandler;
    \ingroup GrpSystemImageFileIOBase
    \relatesalso OSG::ImageFileHandlerBase
 */

typedef SingletonHolder<ImageFileHandlerBase> ImageFileHandler;

typedef ImageFileHandler *ImageFileHandlerP;

OSG_END_NAMESPACE

#include "OSGImageFileHandler.inl"

#endif // _OSGIMAGEFILEHANDLER_H_
