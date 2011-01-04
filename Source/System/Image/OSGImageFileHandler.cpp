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

#define OSG_COMPILE_IMAGEFILEHANDLER

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#include "OSGLog.h"
#include "OSGBaseTypes.h"
#include "OSGPathHandler.h"
#include "OSGBaseFunctions.h"
#include "OSGFileSystem.h"

#include "OSGImageFileHandler.h"

#include "OSGSingletonHolder.ins"

OSG_BEGIN_NAMESPACE

/*! \class ImageFileHandlerBase

  Singelton Object/Class which holds all known ImageFileTypes.
  The class is used to write/read Image objects to/from
  files and to store/restore image data to/from memory blocks.
  Utilizes the local pathHandler for file path handler and
  construction. The PathHandler can be set from the application.

  See \ref PageSystemImage for details.
    
*/

/*****************************
 *   Types
 *****************************/

OSG_SINGLETON_INST(ImageFileHandlerBase, addPostFactoryExitFunction)

template class SingletonHolder<ImageFileHandlerBase>;

/*****************************
 *   Classvariables
 *****************************/

const std::string ImageFileHandlerBase::_fileNameKey    ("fileName"    );
const std::string ImageFileHandlerBase::_fullFilePathKey("fullFilePath");

/********************************
 *   Class methodes
 *******************************/

/*******************************
*public
*******************************/

//-------------------------------------------------------------------------
/*! Method to find a ImageFileHandler for the given mimeType for 
    fileName suffix. Returns the ImageFileHandler object or Null.
*/

ImageFileType *ImageFileHandlerBase::getFileType(const Char8 *mimeType,
                                                 const Char8 *fileName,
                                                       bool   validateHeader)
{
    std::string                          suffix;
    ImageFileType                       *type = 0;
    std::map<std::string, 
             ImageFileType *>::iterator  sI;
    const char                           separator = '.';
    int                                  i, l;

    if(mimeType && *mimeType)
    {
        std::string mt = mimeType;

        normalizeMimetype(mt);

        if(mt.find('/') == std::string::npos)
            mt.insert(0, "image/");

        TypeMap::iterator tIt = _mimeTypeMap.find(mt);

        if(tIt != _mimeTypeMap.end())
            type = tIt->second;

        if(!type) 
        {
            FWARNING (("Invalid mimeType %s in getFileType()\n", mimeType));
        }
    }
    
    if(!type && fileName && *fileName)
    {
        // check file suffix

        if(!type)
        {
            l = strlen(fileName);

            for(i = l - 1; i >= 0; i--)
            {
                if(fileName[i] == separator)
                    break;
            }

            if(i >= 0)
            {
                suffix.assign(&(fileName[i + 1]));

                normalizeSuffix(suffix);

                sI = _suffixTypeMap.find(suffix);

                type = (sI == _suffixTypeMap.end()) ? 0 : sI->second;
            }
        }
    }

    if(validateHeader)
    {
        // now validate the header of the file

        bool implemented = false;

        if( fileName     && 
           *fileName     &&
            type != NULL && 
           !type->validateHeader(fileName, implemented))
        {
            FWARNING (("Found wrong image header trying to "
                       "autodetect image type!\n"));

            for(sI = _suffixTypeMap.begin(); sI != _suffixTypeMap.end(); ++sI)
            {
                type = sI->second;

                if(type != NULL && type->validateHeader(fileName, implemented))
                {
                    if(implemented)
                    {
                        FWARNING (("Autodetected '%s' image type!\n", 
                                   sI->first.c_str()));

                        return type;
                    }
                }
            }

            FWARNING (("Couldn't autodetect image type!\n"));

            return NULL;
        }
    }
    
    return type;
}

//-------------------------------------------------------------------------
/*! Returns the default OpenSG ImageFileType
*/

ImageFileType *ImageFileHandlerBase::getDefaultType(void)
{
    std::string dSuffix("opensg");
    
    std::map<std::string, 
             ImageFileType *>::iterator sI = _suffixTypeMap.find(dSuffix);


    ImageFileType *type = (sI == _suffixTypeMap.end()) ? 0 : sI->second;

    if(!type)
    {
        FFATAL(("Can not find any default (suffix:%s) image handler\n",
                dSuffix.c_str()));
    }

    return type;
}


//-------------------------------------------------------------------------
/*! Returns the list of supported image suffixes
*/

Int32 ImageFileHandlerBase::getSuffixList(std::list<const Char8 *> &suffixList,
                                               UInt32               flags     )
{
    Int32                               count = 0;
    std::map<std::string, 
             ImageFileType *>::iterator sI;

    suffixList.clear();

    for(sI = _suffixTypeMap.begin(); sI != _suffixTypeMap.end(); ++sI)
    {
        ImageFileType *type = sI->second;

        if(type->getFlags() & flags)
        {
            suffixList.push_back(sI->first.c_str());
            count++;
        }
    }
    
    return count;
}

const ImageFileHandlerBase::TypeMap& ImageFileHandlerBase::getSuffixTypeMap() const
{
    return _suffixTypeMap;
}

const ImageFileHandlerBase::TypeMap& ImageFileHandlerBase::getMimeTypeMap() const
{
    return _mimeTypeMap;
}

//-------------------------------------------------------------------------
/*!
  Tries to determine the mime type from the file name.
 */

std::string ImageFileHandlerBase::determineMimetypeFromName(
    const std::string &fileName)
{
    // Determine the suffix of the filename
    std::string::size_type pos = fileName.rfind('.');

    if(pos == std::string::npos)
        return std::string();

    std::string suffix = fileName.substr(pos + 1);

    normalizeSuffix(suffix);

    // Try to find the suffix in the map of extensions
    std::map<std::string, 
                  ImageFileType *>::iterator it = _suffixTypeMap.find(suffix);

    return it != _suffixTypeMap.end() ? 
        std::string(it->second->getMimeType()) : std::string();
}

//-------------------------------------------------------------------------
/*!
  tries to determine the mimetype of a stream.
 */

std::string ImageFileHandlerBase::determineMimetypeFromStream(std::istream &is)
{
    std::string mimetype;
    TypeMap::iterator it;

    for(it = _mimeTypeMap.begin(); it != _mimeTypeMap.end(); ++it)
    {
        mimetype = it->second->determineMimetypeFromStream(is);

        if(mimetype.empty() == false)
            break;
    }

    return mimetype;
}

//-------------------------------------------------------------------------
/*!
Tries to determine the mime type from the suffix.
*/
std::string ImageFileHandlerBase::determineMimetypeFromSuffix(
    const std::string &suffix)
{
    std::string s = suffix;

    normalizeSuffix(s);

    // Try to find the suffix in the map of extensions
    std::map<std::string, ImageFileType *>::iterator it = 
        _suffixTypeMap.find(s);

    return it != _suffixTypeMap.end() ? 
        std::string(it->second->getMimeType()) : std::string();
}

//-------------------------------------------------------------------------
/*! Creates a new image and tries to read the raster data from
    the given fileName. If the mimeType is not Null the method
    will try to find the according ImageFileType. Otherwise it
    will try to use the fileName suffix to determine the mimeType
*/


ImageTransitPtr ImageFileHandlerBase::read(const Char8 *fileName, 
                                           const Char8 *mimeType)
{
    if(_pReadCallback != NULL)
        return _pReadCallback(fileName, mimeType);

    ImageUnrecPtr image = Image::create();
    
    if(read(image, fileName, mimeType) == false)
    {
        image = NULL;
    }

    return ImageTransitPtr(image);
}

//-------------------------------------------------------------------------
/*! Tries to read the raster data from
    the given fileName into the given Image. 
    If the mimeType is not Null the method
    will try to find the according ImageFileType. Otherwise it
    will try to use the fileName suffix to determine the mimeType
*/

bool ImageFileHandlerBase::read(      Image *pImage, 
                                const Char8 *fileName,
                                const Char8 *mimeType)
{
    bool        retCode = false;
    std::string fullFilePath;

    if(_pPathHandler != NULL)
    {
        fullFilePath = _pPathHandler->findFile(fileName);
    }
    else
    {
        fullFilePath = fileName;
    }

    if(fullFilePath.empty())
    {
        SWARNING << "couldn't find image file " << fileName << std::endl;
        return false;
    }
    
    ImageFileType *type = getFileType(mimeType, fullFilePath.c_str(), true);
    
    if(type != NULL)
    {
        FDEBUG(("try to image read %s as %s\n", 
                fullFilePath.c_str(), 
                type->getMimeType()));
        
        retCode = type->read(pImage, fullFilePath.c_str());
        
        if(retCode)
        {
            FDEBUG(("image: %dx%d\n", 
                    pImage->getWidth(), 
                    pImage->getHeight()));

            pImage->setAttachmentField(_fileNameKey, fileName);
            pImage->setAttachmentField(_fullFilePathKey, fullFilePath);


            // converting the path to a absolute path.
            std::string abspath;

            if(fullFilePath[0] != '/'  && 
               fullFilePath[0] != '\\' && 
               fullFilePath[1] != ':')
            {
                std::string base;

                if(getPathHandler() != NULL)
                    base = getPathHandler()->getBaseFile();

                if(base.size() < 2 ||
                   (base[0] != '/' && base[0] != '\\' && base[1] != ':'))
                {
                    const Char8 *cdir = Directory::getCurrent();

                    abspath = cdir;
#ifdef WIN32
                    abspath += '\\';
#else
                    abspath += '/';
#endif
                    delete [] cdir;
                }

                abspath += base;
                abspath += fullFilePath;
            }
            else
            {
                abspath = fullFilePath;
            }

            pImage->setName(abspath);
        }
        else
        {
            SWARNING << "could not read " << fullFilePath << std::endl;
        }
    }
    else
    {
        SWARNING << "could not read " << fullFilePath
                 << "; unknown image format" << std::endl;
    }

    return retCode;
}

void ImageFileHandlerBase::setReadCB(ReadCB pCB)
{
    _pReadCallback = pCB;
}

ImageFileHandlerBase::ReadCB ImageFileHandlerBase::getReadCB(void)
{
    return _pReadCallback;
}

//-------------------------------------------------------------------------
/*! Tries to write the raster data (from the given Image) to 
    the given fileName.
    If the mimeType is not Null the method
    will try to find the according ImageFileType. Otherwise it
    will try to use the fileName suffix to determine the mimeType
*/

bool ImageFileHandlerBase::write(Image const *pImage, 
                                 Char8 const *fileName,
                                 Char8 const *mimeType)
{
          bool            retCode = false;
          ImageFileType  *type;
    const std::string    *fNAttachment;

    if(!fileName && (fNAttachment = pImage->findAttachmentField(_fileNameKey)))
    {
        fileName = fNAttachment->c_str();
    }

    if((type = getFileType(mimeType, fileName)))
    {
        SINFO << "try to write "
              << fileName
              << " as "
              << type->getMimeType() 
              << std::endl;

        retCode = type->write(pImage, fileName);
    }
    else
    {
        SWARNING << "can't write "
                 << fileName 
                 << "; unknown image format" << std::endl;
    }

    return retCode;
}

//-------------------------------------------------------------------------

ImageTransitPtr ImageFileHandlerBase::read(      std::istream &is, 
                                           const std::string  &mimeType)
{
    ImageUnrecPtr image = Image::create();

    if (read(image, is, mimeType) == false)
    {
        image = NULL;
    }

    return ImageTransitPtr(image);
}

//-------------------------------------------------------------------------

bool ImageFileHandlerBase::read(      Image        *pImage, 
                                      std::istream &is,
                                const std::string  &mimeType)
{
    ImageFileType *type = getFileType(mimeType.c_str());

    return type == 0 ? false : type->read(pImage, is, mimeType);
}

//-------------------------------------------------------------------------

bool ImageFileHandlerBase::write(Image        const *pImage, 
                                 std::ostream       &os,
                                 std::string  const &mimeType)
{
    ImageFileType *type = getFileType(mimeType.c_str());

    return type == 0 ? false : type->write(pImage, os, mimeType);
}


ImageFileHandlerBase::ImageBlockAccessorPtr 
    ImageFileHandlerBase::open(const Char8       *fileName,
                               const Char8       *mimeType)
{
    ImageBlockAccessorPtr returnValue;
    std::string           fullFilePath;

    if(_pPathHandler != NULL)
    {
        fullFilePath = _pPathHandler->findFile(fileName);
    }
    else
    {
        fullFilePath = fileName;
    }

    if(fullFilePath.empty())
    {
        SWARNING << "couldn't find image file " << fileName << std::endl;
        return returnValue;
    }
    
    ImageFileType *type = getFileType(mimeType, fullFilePath.c_str(), true);
    
    if(type != NULL)
    {
        FDEBUG(("try to image read %s as %s\n", 
                fullFilePath.c_str(), 
                type->getMimeType()));
        
        returnValue = type->open(fullFilePath.c_str());
    }
    else
    {
        SWARNING << "could not read " << fullFilePath
                 << "; unknown image format" << std::endl;
    }

    return returnValue;
}


//-------------------------------------------------------------------------
/*! Returns the path handler used
*/

PathHandler* ImageFileHandlerBase::getPathHandler(void)
{
    return _pPathHandler;
}

//-------------------------------------------------------------------------
/*! Method to set the path handler. 
*/

void ImageFileHandlerBase::setPathHandler(PathHandler *pPathHandler)
{
    _pPathHandler = pPathHandler;
}

/*! Sets the option \a name to \a value for the ImageFileType that handles
    files with the given \a suffix.
    Returns \c true if the option was set successfully, \c false otherwise. 
    
    \param[in] suffix File extension to choose the image type
                      this option applies to.
    \param[in] name Name of the option.
    \param[in] value Value of the option.
    \return Whether the value was set successfully.
 */
bool
    ImageFileHandlerBase::setOption(
        const std::string &suffix,
        const std::string &name,
        const std::string &value  )
{
    bool           retVal = false;
    ImageFileType *type   = getFileType(suffix.c_str());
    
    if(type != NULL)
    {
        type->setOption(name, value);
        retVal = true;
    }
    
    return retVal;    
}

/*! Removes the option \a name from the ImageFileType that handles files
    with the given \a suffix. If the option is not present \c false is
    returned, \c true otherwise.

    \param[in] suffix File extension to choose the image file type
                      this option applies to.
    \param[in] name Name of the option.
    \return Whether the option was successfully removed.
 */
bool
    ImageFileHandlerBase::unsetOption(
        const std::string &suffix,
        const std::string &name   )
{
    bool           retVal = false;
    ImageFileType *type   = getFileType(suffix.c_str());
    
    if(type != NULL)
    {
        retVal = type->unsetOption(name);
    }
    
    return retVal;
}

/*! Retrieves the option \a name from the ImageFileType that handles files
    with the given \a suffix and stores its value in \a value.
    Returns \c true if successful, \c false otherwise in which case \a value has
    an undefined value.
    
    \param[in] suffix File extension to choose the image type
                      this option applies to.
    \param[in] name Name of the option.
    \param[out] value Value the option.
    \return Whether the option is present for the given ImageFileType.
 */
bool
    ImageFileHandlerBase::getOption(
        const std::string &suffix,
        const std::string &name,
              std::string &value  )
{
    bool           retVal = false;
    ImageFileType *type   = getFileType(suffix.c_str());
    
    if(type != NULL)
    {
        retVal = type->getOption(name, value);
    }
    
    return retVal;
}
    
//-------------------------------------------------------------------------
/*! Tries to restore the raster data from
    the given memblock into the given Image. 
    If the mimeType is not Null the method
    will try to find the according ImageFileType. Otherwise it
    will try to use the fileName suffix to determine the mimeType
*/

UInt64 ImageFileHandlerBase::restore(      Image  *pImage, 
                                     const UChar8 *buffer,
                                           Int32   memSize)
{
    return ImageFileType::restore(pImage, buffer, memSize);
}

//-------------------------------------------------------------------------
/*! Tries to store the raster data (from the given Image) to 
    the given memBlock.
    If the mimeType is not Null the method
    will try to find the according ImageFileType. Otherwise it
    will try to use the fileName suffix to determine the mimeType
*/

UInt64 ImageFileHandlerBase::store(Image  const *pImage, 
                                   Char8  const *mimeType,
                                   UChar8       *buffer, 
                                   Int32         memSize )
{
    ImageFileType   *type;
    
    type = mimeType ? getFileType(mimeType) : getDefaultType();
    
    return type->store(pImage, buffer, memSize);
}

//-------------------------------------------------------------------------
/*! Tries to store the raster data (from the given Image) to 
    a new memBlock. The method will automatically allocate and return a
    sufficient amount of memory with new. The application has
    to free the memory with 'delete [] mem'
    If the mimeType is not Null the method
    will try to find the according ImageFileType. Otherwise it
    will try to use the fileName suffix to determine the mimeType
*/

UChar8 *ImageFileHandlerBase::store(Image  const *pImage, 
                                    UInt64       &memSize,
                                    Char8  const *mimeType)
{
    ImageFileType   *type = 0;
    UChar8          *mem = 0;

    type    = mimeType ? getFileType(mimeType) : getDefaultType();
    memSize = type->maxBufferSize(pImage);

    if(memSize)
    {
        mem     = new UChar8[size_t(memSize)];

        memSize = type->store(pImage, mem, Int32(memSize));
    }
    else
    {
        FFATAL(("Can not store the image as %s\n", type->getMimeType()));
    }

    return mem;
}

//-------------------------------------------------------------------------
/*! The dump method just writes some object debugging info to the LOG stream
 */

void ImageFileHandlerBase::dump(void)
{
    std::map<std::string, ImageFileType *>::iterator    sI;

    for(sI = _suffixTypeMap.begin(); sI != _suffixTypeMap.end(); sI++)
    {
        FLOG (( "Image suffix: %s, mimeType: %s\n",
                sI->first.c_str(), sI->second->getMimeType() ));
    }
}

//-------------------------------------------------------------------------
/*! Internal Method to add a new ImageFileType
*/

bool ImageFileHandlerBase::addImageFileType(ImageFileType &fileType)
{
    bool                                       retCode = false;
    std::list<std::string    >::const_iterator sI;
    std::map <std::string, 
              ImageFileType *>::iterator       smI;
    std::string                                suffix;
    
    for(  sI  = fileType.getSuffixList().begin(); 
          sI != fileType.getSuffixList().end();
        ++sI)
    {
        suffix.assign(sI->c_str());

        normalizeSuffix(suffix);

        smI = _suffixTypeMap.find(suffix);

        if(smI != _suffixTypeMap.end())
        {
            SWARNING << "Can't add an image file type with suffix "
                     << suffix << " a second time" << std::endl;
        }
        else
        {
            _suffixTypeMap[suffix] = &fileType;

            retCode = true;
        }
    }

    std::string mimetype = fileType.getMimeType();

    normalizeMimetype(mimetype);

    TypeMap::iterator tIt = _mimeTypeMap.find(mimetype);

    if(tIt != _mimeTypeMap.end())
    {
        SWARNING << "Can't add an image file type with mimetype "
                 << mimetype << " a second time" << std::endl;
    }
    else
    {
        _mimeTypeMap[mimetype] = &fileType;
    }

    return retCode;
}

//----------------------------------------------------------------------
/*!
  Normalizes a mime type, i.e. removes parameters and whitespaces
  and transforms it to lowercase
 */

void ImageFileHandlerBase::normalizeMimetype(std::string &mimetype)
{
    // Remove any parameters
    std::string::size_type endpos = mimetype.find(';');

    if (endpos == 0)
    {
        mimetype.erase();
        return;
    }

    if (endpos != std::string::npos)
        --endpos;

    // Remove trailing whitespace

    endpos = mimetype.find_last_not_of(" \t\r\n", endpos);

    if (endpos == std::string::npos)
    {
        mimetype.erase();
        return;
    }

    mimetype.erase(endpos + 1);

    // Remove leading whitespace
    std::string::size_type startpos = mimetype.find_first_not_of(" \t\r\n");

    if(startpos == std::string::npos)
    {
        mimetype.erase();
        return;
    }

    mimetype.erase(0, startpos);

    // Transform to lower case
    std::transform(mimetype.begin(), 
                   mimetype.end  (), 
                   mimetype.begin(), 
                   ::tolower);
}

//-------------------------------------------------------------------------
/*!
  Normalizes a suffix, i.e. removes whitespaces and transforms it to lowercase
*/
void ImageFileHandlerBase::normalizeSuffix(std::string &suffix)
{
    // Remove trailing whitespace
    std::string::size_type endpos = suffix.find_last_not_of(" \t\r\n");

    if (endpos == std::string::npos)
    {
        suffix.erase();
        return;
    }

    suffix.erase(endpos + 1);

    // Remove leading whitespace
    std::string::size_type startpos = suffix.find_first_not_of(" \t\r\n");

    if (startpos == std::string::npos)
    {
        suffix.erase();
        return;
    }

    suffix.erase(0, startpos);

    // Transform to lower case
    std::transform(suffix.begin(), suffix.end(), suffix.begin(), ::tolower);
}

//-------------------------------------------------------------------------
/*! Default Constructor
 */

ImageFileHandlerBase::ImageFileHandlerBase(void) :
    _pReadCallback(NULL),
    _pPathHandler (NULL),
    _suffixTypeMap(    ),
    _mimeTypeMap  (    )
{
}

//-------------------------------------------------------------------------
/*! Destructor
 */

ImageFileHandlerBase::~ImageFileHandlerBase(void)
{
}


OSG_END_NAMESPACE
