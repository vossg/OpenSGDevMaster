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
//  Includes
//-------------------------------

#define OSG_COMPILE_SCENEFILEHANDLER

#include <cstdlib>
#include <cstdio>

#include <fstream>

#include "OSGConfig.h"

#include "OSGLog.h"
#include "OSGBaseTypes.h"
#include "OSGPathHandler.h"

#include "OSGGraphOpSeq.h"

#include "OSGImageFileHandler.h"

#include "OSGSceneFileHandler.h"
#include "OSGZStream.h"

#include "OSGNode.h"
#include "OSGThread.h"
#include "OSGThreadManager.h"
#include "OSGBaseFunctions.h"

#include "OSGSingletonHolder.ins"

OSG_BEGIN_NAMESPACE

OSG_SINGLETON_INST(SceneFileHandlerBase, addPostFactoryExitFunction)

template class SingletonHolder<SceneFileHandlerBase>;

GraphOpSeq       *SceneFileHandlerBase::_defaultgraphOpSeq = NULL;

SceneFileType *SceneFileHandlerBase::getFileType(
    const Char8 *fileNameOrExtension)
{
    const Char8 separator = '.';

    if(fileNameOrExtension == NULL)
        return NULL;

    std::string fe = fileNameOrExtension;

    Int32 p = fe.rfind(separator);

    std::string ext;

    if(p != -1)
    {
        ext = fe.substr(p+1, fe.length() - p - 1);
    }
    else
    {
        ext = fe; // extension without '.'
    }

    // skip .gz extension
    if(ext == "gz")
    {
        fe = fe.substr(0, p);
        p  = fe.rfind(separator);

        if(p != -1)
        {
            ext = fe.substr(p+1, fe.length() - p - 1);
        }
        else
        {
            ext = fe;
        }
    }

    std::string suffix;

    suffix.assign (ext.c_str());
//    suffix.toLower(           );
    std::transform(suffix.begin(), suffix.end(), suffix.begin(), ::tolower);

    FileTypeMap::iterator sI = _suffixTypeMap.find(suffix);

    SceneFileType *type =
        (sI == _suffixTypeMap.end()) ? 0 : sI->second->front();

    return type;
}

//CHECK
#ifdef OSG_WIN32_ICL
#pragma warning (disable : 383)
#endif

Int32 SceneFileHandlerBase::getSuffixList(std::list<const Char8 *> &suffixList,
                                          UInt32                    flags)
{
    Int32                 count = 0;
    FileTypeMap::iterator sI;

    suffixList.clear();

    for(sI = _suffixTypeMap.begin(); sI != _suffixTypeMap.end(); ++sI)
    {
        SceneFileType *type = sI->second->front();

        if((type->getFlags() & flags) == flags)
        {
            suffixList.push_back(sI->first.c_str());
            count++;
        }
    }

    return count;
}

#ifdef OSG_WIN32_ICL
#pragma warning (default : 383)
#endif


NodeTransitPtr SceneFileHandlerBase::read(
          std::istream &is,
    const Char8        *fileNameOrExtension,
          GraphOpSeq   *graphOpSeq         ,       
          Resolver      resolver           )
{
    SceneFileType *type  = getFileType(fileNameOrExtension);
    NodeUnrecPtr   scene = NULL;

    if(!fileNameOrExtension)
    {
        SWARNING << "cannot read NULL extension" << std::endl;
        return NodeTransitPtr(scene);
    }

    if(type != NULL)
    {
        SINFO << "try to read stream as " << type->getName() << std::endl;

        // check for fileio read callback
        if(_readFP != NULL)
        {
            initReadProgress(is);
            scene = _readFP(type, is, fileNameOrExtension);
            terminateReadProgress();
        }
        else
        {
            if(isGZip(is))
            {
                SINFO << "Detected gzip compressed stream." << std::endl;

#ifdef OSG_WITH_ZLIB

                initReadProgress(is);

                zip_istream unzipper(is);

                scene = type->read(unzipper, 
                                   fileNameOrExtension, 
                                   resolver ? resolver : _oGlobalResolver);

                if(scene != NULL)
                {
                    if(unzipper.check_crc() == true)
                    {
                        SINFO << "Compressed stream has correct checksum."
                              << std::endl;
                    }
                    else
                    {
                        SWARNING << "Compressed stream has wrong checksum."
                                 << std::endl;
                    }
                }
                terminateReadProgress();
#else
                SFATAL << "Compressed streams are not supported! Configure "
                       << "with --enable-png --with-png=DIR options."
                       << std::endl;
#endif
            }
            else
            {
                initReadProgress(is);

                scene = type->read(is, 
                                   fileNameOrExtension, 
                                   resolver  ? resolver : _oGlobalResolver);

                terminateReadProgress();
            }
        }

        if(scene != NULL)
        {
            if(graphOpSeq != NULL)
                graphOpSeq->traverse(scene);

            SINFO    << "read ok:"        << std::endl;
        }
        else
        {
            SWARNING << "could not read " << std::endl;
        }
    }
    else
    {
        SWARNING << "could not read unknown file format" << std::endl;
    }

    commitChanges();

    return NodeTransitPtr(scene);
}


NodeTransitPtr SceneFileHandlerBase::read(const Char8      *fileName,
                                                GraphOpSeq *graphOpSeq,       
                                                Resolver    resolver,
                                                bool        bWarnNotFound )
{
    NodeTransitPtr returnValue(NULL);

    if(fileName == NULL)
    {
        SWARNING << "cannot read NULL file" << std::endl;
        return NodeTransitPtr(NULL);
    }

    std::string fullFilePath = initPathHandler(fileName);

    if(fullFilePath.empty() == true)
    {
        if(_readFP != NULL)
        {
            // that's a fallback could be a url so the callback
            // can handle this correctly.
            SceneFileType *type = getFileType(fileName);
            if(type != NULL)
            {
                // create a dummy stream with the bad flag set.
                std::ifstream in;
                in.setstate(std::ios::badbit);
                returnValue = _readFP(type, in, fileName);
            }
            else
            {
                if(bWarnNotFound == true)
                    SWARNING << "Couldn't open file " << fileName << std::endl;
            }
        }
        else
        {
            if(bWarnNotFound == true)
                SWARNING << "Couldn't open file " << fileName << std::endl;
        }

        commitChanges();

        return returnValue;
    }


    SceneFileType *type  = getFileType(fullFilePath.c_str());
    NodeUnrecPtr   scene = NULL;

    if(type != NULL)
    {
        triggerReadBegin(fullFilePath.c_str());
        updateReadProgress(0);

        SINFO << "try to read " << fullFilePath
              << " as "         << type->getName() << std::endl;

        std::ifstream in(fullFilePath.c_str(), std::ios::binary);

        if(in)
        {
            scene = read(in, fullFilePath.c_str(), graphOpSeq);

            in.close();

            if(scene != NULL)
            {
                triggerReadEnd(fullFilePath.c_str());
            }
        }
        else
        {
            if(bWarnNotFound == true)
            {
                SWARNING << "Couldn't open input stream for file "
                         << fullFilePath
                         << std::endl;
            }
        }

#ifndef OSG_DISABLE_DEPRECATED

        // Ok stream interface didn't work try via filename
        if(scene == NULL)
            scene = type->readFile(fullFilePath.c_str());

        if(scene != NULL)
        {
            if(graphOpSeq != NULL)
                graphOpSeq->run(scene);

            SINFO    << "read ok:"        << std::endl;
        }
        else
        {
            if(bWarnNotFound == true)
                SWARNING << "could not read " << std::endl;
        }
#endif

#if 0
        if(scene != NULL && graphOpSeq != NULL)
        {
            SINFO    << "Running GraphOps..." << std::endl;
            graphOpSeq->run(scene);
        }
#endif
    }
    else
    {
        if(bWarnNotFound == true)
        {
            SWARNING << "could not read "       << fullFilePath
                     << "; unknown file format" << std::endl;
        }
    }

    commitChanges();

    return NodeTransitPtr(scene);
}


void SceneFileHandlerBase::setReadCB(FileIOReadCBF fp)
{
    _readFP = fp;
}

SceneFileHandlerBase::FileIOReadCBF SceneFileHandlerBase::getReadCB(void)
{
    return _readFP;
}

bool SceneFileHandlerBase::write(Node         * const  node,
                                 std::ostream         &os,
                                 Char8          const *fileNameOrExtension,
                                 bool                  compress           )
{
    bool           retCode = false;
    SceneFileType *type    = getFileType(fileNameOrExtension);

    if(type != NULL)
    {
        updateWriteProgress(0);

        SINFO << "try to write stream as " << type->getName() << std::endl;

        if(_writeFP != NULL)
        {
            retCode = _writeFP(type, node, os, fileNameOrExtension, compress);
        }
        else
        {
            if(compress == true)
            {
#ifdef OSG_WITH_ZLIB
                SINFO << "writing compressed stream." << std::endl;

                zip_ostream zipper(os, true);

                retCode = type->write(node, zipper, fileNameOrExtension);

                zipper.zflush();
#else
                SFATAL << "Compressed streams are not supported! Build "
                       << "with zlib= options."
                       << std::endl;
#endif
            }
            else
            {
                retCode = type->write(node, os, fileNameOrExtension);
            }
        }
    }
    else
    {
        SWARNING << "can't write stream unknown scene format" << std::endl;
    }

    return retCode;
}

bool SceneFileHandlerBase::write(Node  * const  node,
                                 Char8   const *fileName,
                                 bool           compress)
{
    bool           retCode = false;
    SceneFileType *type    = getFileType(fileName);

    if(type != NULL)
    {
        updateWriteProgress(0);
        triggerWriteBegin(fileName);
        
        SINFO << "try to write "
              << fileName
              << " as "
              << type->getName()
              << std::endl;

        std::ofstream out(fileName, std::ios::binary);

        if(out)
        {
            retCode = write(node, out, fileName, compress);
            out.close();
        }
        else
        {
            SWARNING << "Can not open output stream for file '"
                     << fileName
                     << "'!"
                     << std::endl;
        }

#ifndef OSG_DISABLE_DEPRECATED
        if(!retCode)
        {
            retCode = type->writeFile(node, fileName);
        }
#endif

        if(!retCode)
        {
            SWARNING << "Couldn't write " << fileName << std::endl;
        }
        else
        {
            triggerWriteEnd(fileName);
        }
    }
    else
        SWARNING << "can't write "
                 << fileName
                 << "; unknown scene format"
                 << std::endl;

    return retCode;
}

void SceneFileHandlerBase::setWriteCB(FileIOWriteCBF fp)
{
    _writeFP = fp;
}

SceneFileHandlerBase::FileIOWriteCBF SceneFileHandlerBase::getWriteCB(void)
{
    return _writeFP;
}

PathHandler *SceneFileHandlerBase::getPathHandler(void)
{
    if(_pathHandler == NULL)
    {
        return &_defaultPathHandler;
    }
    else
    {
        return _pathHandler;
    }
}

void SceneFileHandlerBase::setPathHandler(PathHandler *pathHandler)
{
    _pathHandler = pathHandler;
}

SceneFileHandlerBase::Resolver 
    SceneFileHandlerBase::getGlobalResolver(void) const
{
    return _oGlobalResolver;
}

void SceneFileHandlerBase::setGlobalResolver(Resolver oResolver)
{
    _oGlobalResolver = oResolver;
}

std::string SceneFileHandlerBase::initPathHandler(const Char8 *fileName)
{
    std::string fullFilePath;

    if(_pathHandler != NULL)
    {
        // Set also a image path handler if not set.

        if(ImageFileHandler::the()->getPathHandler() == NULL)
        {
            ImageFileHandler::the()->setPathHandler(_pathHandler);
        }

        fullFilePath = _pathHandler->findFile(fileName);
    }
    else
    {
        // Set a default image path handler if not set.
        if(ImageFileHandler::the()->getPathHandler() == NULL)
        {
            ImageFileHandler::the()->setPathHandler(&_defaultPathHandler);
        }

        _defaultPathHandler.clearPathList();
        _defaultPathHandler.clearBaseFile();

        _defaultPathHandler.push_frontCurrentDir(        );

        fullFilePath = _defaultPathHandler.findFile(fileName);

        _defaultPathHandler.setBaseFile(fullFilePath.c_str());
    }

    return fullFilePath;
}

GraphOpSeq *SceneFileHandlerBase::getDefaultGraphOp(void)
{
    return _defaultgraphOpSeq;
}

void SceneFileHandlerBase::setDefaultGraphOp(GraphOpSeq *graphOpSeq)
{
    setRefd(_defaultgraphOpSeq, graphOpSeq);
}

/*-------------------------------------------------------------------------*/
/* Options                                                                 */

/*! Sets the option \a name to \a value for the SceneFileType that handles
    files with the given \a suffix.
    Returns \c true if the option was set successfully, \c false otherwise. 
    
    \param[in] suffix File extension to choose the scene file type
                      this option applies to.
    \param[in] name Name of the option.
    \param[in] value Value of the option.
    \return Whether the value was set successfully.
 */
bool
    SceneFileHandlerBase::setOption(
        const std::string &suffix,
        const std::string &name,
        const std::string &value  )
{
    bool           retVal = false;
    SceneFileType *type   = getFileType(suffix.c_str());
    
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

    \param[in] suffix File extension to choose the scene file type
                      this option applies to.
    \param[in] name Name of the option.
    \return Whether the option was successfully removed.
 */
bool
    SceneFileHandlerBase::unsetOption(
        const std::string &suffix,
        const std::string &name   )
{
    bool           retVal = false;
    SceneFileType *type   = getFileType(suffix.c_str());
    
    if(type != NULL)
    {
        retVal = type->unsetOption(name);
    }
    
    return retVal;
}

/*! Retrieves the option \a name from the SceneFileType that handles files
    with the given \a suffix and stores its value in \a value.
    Returns \c true if successful, \c false otherwise in which case \a value has
    an undefined value.
    
    \param[in] suffix File extension to choose the scene file type
                      this option applies to.
    \param[in] name Name of the option.
    \param[out] value Value the option.
    \return Whether the option is present for the given SceneFileType.
 */
bool
    SceneFileHandlerBase::getOption(
        const std::string &suffix,
        const std::string &name,
              std::string &value  )
{
    bool           retVal = false;
    SceneFileType *type   = getFileType(suffix.c_str());
    
    if(type != NULL)
    {
        retVal = type->getOption(name, value);
    }
    
    return retVal;
}

#if defined(OSG_1_COMPAT)
void SceneFileHandlerBase::setOptions(const std::string &suffix,
                                      const std::string &osg1Options)
{
}
#endif

void SceneFileHandlerBase::print (void )
{
    FileTypeMap::iterator sI;

    for(sI = _suffixTypeMap.begin(); sI != _suffixTypeMap.end(); sI++)
    {
        std::string    rw;
        SceneFileType *type = sI->second->front();

        if((type->getFlags() & SceneFileType::OSG_READ_SUPPORTED) &&
           (type->getFlags() & SceneFileType::OSG_WRITE_SUPPORTED))
        {
            rw = "reader and writer";
        }
        else
        {
            if(type->getFlags() & SceneFileType::OSG_READ_SUPPORTED)
                rw = "reader";

            if(type->getFlags() & SceneFileType::OSG_WRITE_SUPPORTED)
                rw = "writer";
        }

        std::cerr << "suffix: " << sI->first.c_str()
                  << ", type: " << sI->second->front()->getName()
                  << " "        << rw
                  << std::endl;
    }
}

bool SceneFileHandlerBase::FindOverride::operator() (SceneFileType *fileTypeP)
{
    if(fileTypeP == NULL)
        return false;

    if(fileTypeP->doOverride() == false)
        return true;

    if(fileTypeP->getOverridePriority() <= uiRefPriority)
        return true;

    return false;
}

//CHECK
#ifdef OSG_WIN32_ICL
#pragma warning (disable : 383)
#endif

bool SceneFileHandlerBase::addSceneFileType(SceneFileType &fileType)
{
    bool retCode = false;

    std::list<std::string>::iterator sI;
         FileTypeMap      ::iterator smI;

    std::string suffix;

    for(  sI  = fileType.suffixList().begin();
          sI != fileType.suffixList().end();
        ++sI)
    {
        suffix.assign (sI->c_str());
//        suffix.toLower();
        std::transform(suffix.begin(), suffix.end(), suffix.begin(), ::tolower);

        smI = _suffixTypeMap.find(suffix);

        if (smI != _suffixTypeMap.end())
        {
            if(fileType.doOverride() == true)
            {
                FindOverride           overrideFinder;
                FileTypeList::iterator lIt;

                overrideFinder.uiRefPriority = fileType.getOverridePriority();

                lIt = std::find_if(_suffixTypeMap[suffix]->begin(),
                                   _suffixTypeMap[suffix]->end  (),
                                   overrideFinder);

                _suffixTypeMap[suffix]->insert(lIt, &fileType);

                SWARNING << "Added an file type with suffix "
                         << suffix
                         << " overriding "
                         << std::endl;
            }
            else
            {
                _suffixTypeMap[suffix]->push_back(&fileType);

                SWARNING << "Added an file type with suffix "
                         << suffix
                         << " non overriding at the end of the list"
                         << std::endl;
            }
        }
        else
        {
            FileTypeList *pTmpList = new FileTypeList;

            pTmpList->push_back(&fileType);

            _suffixTypeMap[suffix] = pTmpList;

            retCode = true;
        }
    }

    return retCode;
}

bool SceneFileHandlerBase::subSceneFileType(SceneFileType &fileType)
{
    bool retCode = false;

    std::list<std::string>::iterator sI;
         FileTypeMap      ::iterator smI;

    std::string suffix;

    for(  sI  = fileType.suffixList().begin();
          sI != fileType.suffixList().end();
        ++sI)
    {
        suffix.assign(sI->c_str());
        //suffix.toLower();
        std::transform(suffix.begin(), suffix.end(), suffix.begin(), ::tolower);
        smI = _suffixTypeMap.find(suffix);

        if (smI != _suffixTypeMap.end())
        {
            _suffixTypeMap.erase(smI);
            retCode = true;
        }
    }
    return retCode;
}

#ifdef OSG_WIN32_ICL
#pragma warning (default : 383)
#endif

    
static bool initializeDefaultGraphOps(void)
{
    GraphOpSeqRefPtr ops = GraphOpSeq::create();

    ops->setGraphOps(
            "Stripe() SharePtr(includes=Material,StateChunk)");

    SceneFileHandlerBase *the = SceneFileHandler::the();
    
    the->setDefaultGraphOp(ops);
    
    return true;
}

static bool terminateDefaultGraphOps(void)
{
    SceneFileHandlerBase *the = SceneFileHandler::the();
    
    the->setDefaultGraphOp(NULL);

    return true;
}

SceneFileHandlerBase::SceneFileHandlerBase(void) :
    _readProgressFP    (NULL          ),
    _readBeginFP       (NULL          ),
    _readEndFP         (NULL          ),
    _progressData      (              ),
    _readReady         (false         ),
    _useProgressThread (false         ),
    _writeProgressFP   (NULL          ),
    _writeBeginFP      (NULL          ),
    _writeEndFP        (NULL          ),
    _pathHandler       (NULL          ),
    _defaultPathHandler(              ),
    _readFP            (NULL          ),
    _writeFP           (NULL          ),
    _oGlobalResolver   (NULL          )
{
    _progressData.length = 0;
    _progressData.is = NULL;

    addPostFactoryInitFunction(initializeDefaultGraphOps);
    addPreFactoryExitFunction (terminateDefaultGraphOps );
    addPreFactoryExitFunction (terminateSceneFileTypes  );
}

// read progress stuff.

void SceneFileHandlerBase::setReadProgressCB(progresscbfp fp, bool use_thread)
{
    if(use_thread)
    {
        terminateReadProgress();
    }
    else
    {
        //check if setReadProgressCB was called before with use_thread enabled.

        if(_useProgressThread)
            terminateReadProgress();
    }

    _readProgressFP    = fp;
    _useProgressThread = use_thread;
}

SceneFileHandlerBase::progresscbfp
    SceneFileHandlerBase::getReadProgressCB(void)
{
    return _readProgressFP;
}

void SceneFileHandlerBase::setReadBeginCB(filenamecbfp fp)
{
    _readBeginFP = fp;
}

SceneFileHandlerBase::filenamecbfp SceneFileHandlerBase::getReadBeginCB(void)
{
    return _readBeginFP;
}

void SceneFileHandlerBase::setReadEndCB(filenamecbfp fp)
{
    _readEndFP = fp;
}

SceneFileHandlerBase::filenamecbfp SceneFileHandlerBase::getReadEndCB(void)
{
    return _readEndFP;
}

void SceneFileHandlerBase::triggerReadBegin(const Char8 *fname)
{
    if(_readBeginFP != NULL)
        _readBeginFP(fname);
}

void SceneFileHandlerBase::triggerReadEnd(const Char8 *fname)
{
    if(_readEndFP != NULL)
        _readEndFP(fname);
}

void SceneFileHandlerBase::initReadProgress(std::istream &is)
{
    if(_readProgressFP == NULL)
        return;

    // get length of the stream.
    _progressData.is = &is;
    is.seekg(0, std::ios::end);
    _progressData.length = is.tellg();
    is.seekg(0, std::ios::beg);

    _readReady = false;

    if(_useProgressThread)
    {
        _progressData.thread =  Thread::find("OSG::FileIOReadProgressThread");

        if(_progressData.thread == NULL)
        {
            _progressData.thread =
                OSG::Thread::get("OSG::FileIOReadProgressThread", true);
        }

        if(_progressData.thread != NULL)
        {
            _progressData.thread->runFunction(readProgress, 0, NULL);
        }
        else
        {
            SWARNING << "Couldn't create read progress thread!" << std::endl;
        }
    }
}

void SceneFileHandlerBase::terminateReadProgress(void)
{
    if(_readProgressFP == NULL)
        return;

    _readReady = true;

    if(_progressData.thread != NULL)
    {
        // terminate thread
        Thread::join(_progressData.thread);
        _progressData.thread = NULL;
    }

    _progressData.length = 0;
    _progressData.is     = NULL;
}

void SceneFileHandlerBase::readProgress(void * OSG_CHECK_ARG(data))
{
    SceneFileHandlerBase *the = SceneFileHandler::the();

    if(the->_readProgressFP == NULL || the->_progressData.is == NULL)
        return;

    UInt32 p = 0;

    while(p < 100 && !the->_readReady)
    {
        if(!the->_progressData.is->eof() &&
           !the->_progressData.is->bad())
        {
            UInt64 pos = the->_progressData.is->tellg();
            p = UInt32((pos * 100) / the->_progressData.length);
            if(p > 100)
                p = 100;
        }
        else
        {
            p = 100;
        }

        the->_readProgressFP(p);

        if(the->_useProgressThread)
        {
            osgSleep(100);
        }
        else
        {
            break;
        }
    }

    if(the->_useProgressThread && p < 100)
    {
        the->_readProgressFP(100);
    }
}

void SceneFileHandlerBase::updateReadProgress(void)
{
    if(_readProgressFP == NULL)
        return;

    if(_useProgressThread)
        return;

    readProgress(NULL);
}

void SceneFileHandlerBase::updateReadProgress(UInt32 p)
{
    if(_readProgressFP == NULL)
        return;

    _readProgressFP(p);
}

// write progress stuff.

void SceneFileHandlerBase::setWriteProgressCB(progresscbfp fp)
{
    _writeProgressFP = fp;
}

SceneFileHandlerBase::progresscbfp 
    SceneFileHandlerBase::getWriteProgressCB(void)
{
    return _writeProgressFP;
}

void SceneFileHandlerBase::setWriteBeginCB(filenamecbfp fp)
{
    _writeBeginFP = fp;
}

SceneFileHandlerBase::filenamecbfp SceneFileHandlerBase::getWriteBeginCB(void)
{
    return _writeBeginFP;
}

void SceneFileHandlerBase::setWriteEndCB(filenamecbfp fp)
{
    _writeEndFP = fp;
}

SceneFileHandlerBase::filenamecbfp SceneFileHandlerBase::getWriteEndCB(void)
{
    return _writeEndFP;
}

void SceneFileHandlerBase::triggerWriteBegin(const Char8 *fname)
{
    if(_writeBeginFP != NULL)
        _writeBeginFP(fname);
}

void SceneFileHandlerBase::triggerWriteEnd(const Char8 *fname)
{
    if(_writeEndFP != NULL)
        _writeEndFP(fname);
}

void SceneFileHandlerBase::updateWriteProgress(UInt32 p)
{
    if(_writeProgressFP == NULL)
        return;

    _writeProgressFP(p);
}

SceneFileHandlerBase::~SceneFileHandlerBase(void)
{
    FileTypeMap::iterator smIt  = _suffixTypeMap.begin();
    FileTypeMap::iterator smEnd = _suffixTypeMap.end  ();

    while(smIt != smEnd)
    {
        delete (*smIt).second;
        ++smIt;
    }

    _suffixTypeMap.clear();
}

bool SceneFileHandlerBase::doTerminateSceneFileTypes(void)
{
    FileTypeMap ::iterator sI;
    FileTypeList::iterator lI;

    for(sI = _suffixTypeMap.begin(); sI != _suffixTypeMap.end(); ++sI)
    {
        for(lI = sI->second->begin(); lI != sI->second->end(); ++lI)
        {
            (*lI)->terminate();
        }
    }

    return true;
}

bool SceneFileHandlerBase::terminateSceneFileTypes(void)
{
    return SceneFileHandler::the()->doTerminateSceneFileTypes();
}


OSG_END_NAMESPACE
