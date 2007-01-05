/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2003 by the OpenSG Forum                   *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *         contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de    *
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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#include <iostream>

#include <cstdio>
#include <stdarg.h>

#include "OSGLog.h"
#include "OSGBaseFunctions.h"

OSG_USING_NAMESPACE

#ifndef OSG_DEFAULT_LOG_LEVEL
#    define OSG_DEFAULT_LOG_LEVEL LOG_WARNING
#endif

#ifndef OSG_DEFAULT_LOG_TYPE
#    define OSG_DEFAULT_LOG_TYPE LOG_STDERR 
#endif

//---------------------------------------------------------------------------
//  LogBuf
//---------------------------------------------------------------------------


LogBuf::LogBuf(UInt32 bufferSize) :
     std::streambuf(    ), 
    _enabled       (true), 
    _chunkBag      (    ),
    _callback      (NULL), 
    _clientData    (NULL)
{
    setg(0, 0, 0);

    if(bufferSize > 0) 
    {
        Char8 *buffer = new Char8[bufferSize];

        setp(buffer, buffer + bufferSize - 1);
    }
    else
    {
        setp(0, 0);
    }
}

LogBuf::~LogBuf(void)
{
    delete [] pbase();

    _callback = NULL;
}

/*! \brief clear the chunk bag
 */

void LogBuf::clearChunkBag(void) 
{
    std::list<LogBuf::Chunk*>::iterator cI;

    for(cI = _chunkBag.begin(); cI != _chunkBag.end(); ++cI)
        delete *cI;

    _chunkBag.clear();
}


void LogBuf::setCallback ( LogBuf::Callback cb, void *clientData, 
                           bool flushData )
{
    std::list<LogBuf::Chunk*>::iterator  cI;
    LogBuf::Chunk                       *chunk;

    if(cb) 
    {
        if(flushData) 
        {
            for(cI = _chunkBag.begin(); cI != _chunkBag.end(); cI++) 
            {
                if((chunk = *cI))
                    cb(chunk->data,chunk->size,clientData);
            }
        }

        _callback   = cb;
        _clientData = clientData;
    }
}


void LogBuf::removeCallback(void)
{
    _callback = 0;
}


void LogBuf::write(const Char8 *buffer, std::streamsize size)
{
    Chunk    *chunk = 0;
    Callback  cb    = NULL;

    if(_enabled)
    {
        chunk = new Chunk;

        chunk->size = size;
        chunk->data = new Char8[size];

        memcpy(chunk->data, buffer, size);

        _chunkBag.push_back(chunk);
    }
    
    if ((cb = _callback))
        cb(buffer,size, _clientData);
}

int LogBuf::overflow(Int32 c)
{
    if(!pptr())
        return EOF;
    
    if(c != EOF) 
    {
        // Put character into write buffer
        *pptr() = c; 

        pbump(1);

        // Flush write buffer
        std::streamsize size = pptr() - pbase();

        if(size > 0)
        {
            write(pbase(), size);
            pbump(-size);
        }
    }
  
    return 0;
}

int LogBuf::sync(void)
{
    if(!pptr())
        return EOF;

    // Flush write buffer
    std::streamsize size = pptr() -  pbase();

    if(size > 0) 
    {
        write(pbase(), size);
        pbump(-size);
    }

    return 0;
}

std::streamsize LogBuf::xsputn(const Char8 *buffer, std::streamsize size)
{
    if(size > 0)
    {
        if(!pptr())
            return 0;

        std::streamsize s = epptr() - pptr();

        if(s >= size) 
        {
            // Put it into the write buffer
            memcpy(pptr(), buffer, size);
            pbump(size);
        }
        else 
        {
            // Flush write buffer
            s = pptr() - pbase();

            if (s > 0) 
            {
                write(pbase(), s);
                pbump(-s);
            }

            // Write data
            write(buffer, size);
        }
    }

    return size;
}

//---------------------------------------------------------------------------
//  Log
//---------------------------------------------------------------------------

/*! \brief holds the nil buffer 
 */

      Log::nilbuf  *Log::_nilbufP     = NULL;
      std::ostream *Log::_nilstreamP  = NULL;

const Char8        *Log::_levelName[] = 
{
    "LOG", "FATAL", "WARNING", "NOTICE", "DEBUG_GV", "INFO", "DEBUG", 0
};

const Char8        *Log::_levelColor[] = 
{
    0,          // LOG
    "\x1b[31m", // FATAL
    "\x1b[33m", // WARNING
    0,          // NOTICE
    0,          // DEBUG_GV
    0,          // INFO
    0,          // DEBUG
    0
};


Log::Log(LogType logType, LogLevel logLevel) :
     std::ostream  (_nilbufP == NULL ? 
                        _nilbufP = new Log::nilbuf() : _nilbufP), 
    _logType       (logType       ), 
    _logLevel      (logLevel      ), 
    _fileStream    (              ),
    _logBuf        (              ),
    _headerElem    (             0),
    _moduleHandling(LOG_MODULE_ALL)
{   
    if(_nilstreamP == NULL)
        _nilstreamP = new std::ostream(_nilbufP);

    for(UInt32 i = 0; i < sizeof(_streamVec)/sizeof(LogOStream *); i++)
    {
#ifdef OSG_HAS_NILBUF
        _streamVec[i] = new LogOStream(_nilbufP);
#else
        _streamVec[i] = new LogOStream(_nilStreamP->rdbuf());
#endif
    }

    setHeaderElem(LOG_TYPE_HEADER);

    _refTime = getSystemTime();

    setLogLevel(logLevel);
}

/*! \brief Constructor which takes a log file name
 */

Log::Log(const Char8 *fileName, LogLevel logLevel) :
     std::ostream  (_nilbufP == NULL ? 
                        _nilbufP = new Log::nilbuf() : _nilbufP), 
    _logType       (LOG_FILE      ), 
    _logLevel      (logLevel      ), 
    _fileStream    (              ),
    _logBuf        (              ),
    _headerElem    (             0),
    _moduleHandling(LOG_MODULE_ALL)
{
    if(_nilstreamP == NULL)
        _nilstreamP = new std::ostream(_nilbufP);

    for(UInt32 i = 0; i < sizeof(_streamVec)/sizeof(LogOStream *); i++)
    {
#ifdef OSG_HAS_NILBUF
        _streamVec[i] = new LogOStream(_nilbufP);
#else
        _streamVec[i] = new LogOStream(_nilStreamP->rdbuf());
#endif
    }

    _refTime = getSystemTime();

    setHeaderElem(LOG_TYPE_HEADER);
    setLogFile   (fileName);
    setLogLevel  (logLevel);
}

Log::~Log(void)
{
    setLogFile(NULL, true);

    delete _nilstreamP;
    delete _nilbufP;

    _nilstreamP = NULL;
    _nilbufP    = NULL;

    for(UInt32 i = 0; i < sizeof(_streamVec)/sizeof(LogOStream *); i++)
    {
        delete _streamVec[i];

        _streamVec[i] = NULL;
    }

}

/*------------------------------ access -----------------------------------*/

/*! \brief set method for attribute _headerElem
 */

void Log::setHeaderElem(UInt32 elemMask, bool force)
{
    Char8 *env;

    if(!force && (this == osgLogP) && (env = getenv( "OSG_LOG_HEADER" )))
    {
        osgLog() << "Log::setHeaderElem: overriden by envvar OSG_LOG_HEADER '" 
                 << env << "'." << endLog;  

        elemMask = LogHeaderElem(atoi(env));
    }

    _headerElem = elemMask;
}

/*! \brief add method for attribute _headerElem
 */

void Log::addHeaderElem(LogHeaderElem elem, bool force)
{
    setHeaderElem((_headerElem | elem), force);
}

/*! \brief delete method for attribute _headerElem
 */

void Log::delHeaderElem(LogHeaderElem elem, bool force)
{
    setHeaderElem((_headerElem & ~elem),force);
}

/*! \brief check for a single headerElem
 */

bool Log::hasHeaderElem(LogHeaderElem elem) 
{
    return (_headerElem & elem) != 0;
}

void Log::addModuleHandling(LogModuleHandling handling, 
                            bool              OSG_CHECK_ARG(force))
{
    _moduleHandling |= handling;
}

void Log::delModuleHandling(LogModuleHandling handling, 
                            bool              OSG_CHECK_ARG(force))
{
    _moduleHandling &= ~handling;
}

void Log::addModuleName(const Char8 *module, bool isStatic)
{
    Module m;
    int    len;

    if(module && *module) 
    {
        _moduleList.push_back(m);

        if(isStatic) 
        {
            _moduleList.back().name     = module;
            _moduleList.back().isStatic = true;
        }
        else 
        {
            len = strlen(module);

            _moduleList.back().name = new Char8[len + 1];

            strcpy(const_cast<Char8 *>(_moduleList.back().name), module);

            _moduleList.back().isStatic = false;            
        }
    }
}

void Log::delModuleName(const Char8 *OSG_CHECK_ARG(module))
{
}

bool Log::hasModule(const Char8 *module)
{
    bool                        retCode = false;
    std::list<Module>::iterator mI;

    if(module && *module) 
    {
        for(  mI = _moduleList.begin();
              retCode || (mI != _moduleList.end()); 
            ++mI) 
        {
            retCode = (mI->isStatic) ? 
                (module == mI->name) : (!strcmp(module,mI->name));
        }
    }

    return retCode;
}

bool Log::checkModule(const Char8 *module)
{
    bool                        retCode = false;
    std::list<Module>::iterator mI;

    if(_moduleHandling != LOG_MODULE_NONE) 
    {
        if(_moduleHandling == LOG_MODULE_ALL) 
        {
            retCode = true;
        }
        else
        {
            if(module && &module) 
            {
                if(hasModule(module))
                {
                    if(_moduleHandling & LOG_MODULE_KNOWN)
                        retCode = true;
                }
                else 
                {
                    if(_moduleHandling & LOG_MODULE_UNKNOWN)
                        retCode = true;
                }
            }
            else
            {
                if(_moduleHandling & LOG_MODULE_UNDEFINED)
                    retCode = true;
            }
        }
    }

    return retCode;
}


LogType Log::getLogType(void)
{ 
    return _logType; 
}

/*! \brief set method for attribute logType, checks OSG_LOG_TYPE env var
           if not forced.
 */

void Log::setLogType(LogType logType, bool force) 
{
    static Char8   *typenames[] = 
    {
        "none", 
        "-",
        "stdout", 
        "stderr", 
        "file",
        "buffer",
        NULL
    };

    static LogType  types    [] = 
    {
        LOG_NONE, 
        LOG_STDOUT, 
        LOG_STDOUT, 
        LOG_STDERR, 
        LOG_FILE,
        LOG_BUFFER
    };

    static Int32 typeCount = sizeof(types) / sizeof(LogType);

    Char8 *et;
    Int32  lt;
    Int32  i;                               

    if(!force && (this == osgLogP) && (et = getenv("OSG_LOG_TYPE")))
    {
        osgLog() << "Log::setLogType: overriden by envvar OSG_LOG_TYPE '" 
                 << et << "'." << std::endl; 

        if(sscanf(et, "%d", &lt) != 1)
        {               
            for(i = 0; typenames[i]; i++)
            {
                if(!osgStringCaseCmp(et, typenames[i]))
                {
                    _logType = types[i];
                    break;
                }
            }

            if(! typenames[i])
            {
                _logType = LOG_STDERR;

                osgLog() << "Log::setLogType: couldn't interpret envvar, "
                         << "set to LOG_STDERR!" 
                         << std::endl; 
            }
        }
        else 
        {
            if(lt < 0)
            {
                lt = 0;
            }
            else 
            {
                if(lt >= typeCount)
                    lt = typeCount - 1;
            }

            _logType = types[lt];
        }
    }
    else
    {
        _logType = logType; 
    }

    connect(); 
}


LogLevel Log::getLogLevel(void) 
{
    return _logLevel; 
}


/*! \brief set method for attribute logLevel, checks OSG_LOG_LEVEL env var
           if not forced.
 */

void Log::setLogLevel(LogLevel logLevel, bool force)
{ 
    static Char8    *levelnames[] = 
    {
        "log", 
        "fatal", 
        "warning", 
        "notice", 
        "debug_gv",
        "info", 
        "debug", 
        NULL 
    };

    static LogLevel  levels    [] = 
    {
        LOG_LOG, 
        LOG_FATAL,
        LOG_WARNING, 
        LOG_NOTICE,
        LOG_DEBUG_GV,
        LOG_INFO,
        LOG_DEBUG
    };

    static Int32 levelCount = sizeof(levels) / sizeof(LogLevel);

    Char8 *el;
    Int32  ll;
    Int32  i;                               

    if(!force && (this == osgLogP) && (el = getenv("OSG_LOG_LEVEL")))
    {
        osgLog() << "OSGLog::setLogLevel: overriden by envvar OSG_LOG_LEVEL '" 
                 << el << "'." << std::endl; 

        if(sscanf(el, "%d", &ll) != 1)
        {
            for(i = 0; levelnames[i]; i++)
            {
                if(!osgStringCaseCmp(el, levelnames[i]))
                {
                    _logLevel = levels[i];
                    break;
                }
            }

            if(! levelnames[i])
            {
                _logLevel = LOG_DEBUG;

                osgLog() << "Log::setLogLevel: couldn't interpret envvar, "
                         << "set to LOG_DEBUG!"
                         << std::endl; 
            }
        }
        else 
        {
            if (ll < 0)
            {
                ll = 0;
            }
            else 
            {
                if (ll >= levelCount)
                    ll = levelCount - 1;
            }

            _logLevel = levels[ll];
        }
    }
    else
    {
        _logLevel = logLevel; 
    }    

    connect() ; 
}


/*! \brief method to set and activate the log file, checks OSG_LOG_FILE env
           var if not forced 
 */

void Log::setLogFile(const Char8 *fileName, bool force)
{
    const Char8 *name;

#ifdef OSG_STREAM_HAS_ISOPEN
    if(_fileStream.is_open())
#else
    if(_fileStream.rdbuf()->is_open())
#endif
    {
        _fileStream.close();
    }

    if(!force && (this == osgLogP) && (name = getenv("OSG_LOG_FILE"))) 
    {
        osgLog() << "Log::setLogFile: overriden by envvar OSG_LOG_FILE '" 
                 << name << "'." << std::endl;                            
    }
    else
    {
        name = fileName;
    }

    if(name && *name) 
    {
        _fileStream.open(name, std::ios::out);

#ifdef OSG_STREAM_HAS_ISOPEN
        if(_fileStream.is_open()) 
#else
        if(_fileStream.rdbuf()->is_open())
#endif
        {
            _logType = LOG_FILE;
            connect();
        }
    }
}


/*! \brief print for C-interface helper method 
 */

void Log::doLog(const Char8 * format, ...)
{
    Char8   buffer[4096];
    va_list args;
    
    va_start( args, format );

#ifdef OSG_HAS_VSNPRINTF
    vsnprintf(buffer, sizeof(buffer) - 1, format, args);
#else
    vsprintf(buffer, format, args);
#endif

//    *this << buffer;
//    *this << std::flush;
//  Work around VC71. Patch by Chad Austin.
    std::ostream& os = *this;
    os << buffer;
    os << std::flush;
 

    va_end(args);
}


/*! \brief reconnects the streams for the current settings 
 */

void Log::connect(void)  
{
    Int32 i;

#ifndef OSG_STREAM_RDBUF_HAS_PARAM
    switch(_logType) 
    {
        case LOG_STDOUT:
            this->bp = std::cout.rdbuf();
            break;
        case LOG_STDERR:
            this->bp = std::cerr.rdbuf();
            break;
        case LOG_FILE:
            this->bp = _fileStream.rdbuf();
            break;
        case LOG_BUFFER:
            this->bp = _logBuf;
            break;
        case LOG_NONE:
        default:
            this->bp = _nilStreamP->rdbuf();
            break;
    }
#else
    switch(_logType) 
    {
        case LOG_STDOUT:
            this->rdbuf(std::cout.rdbuf());
            break;
        case LOG_STDERR:
            this->rdbuf(std::cerr.rdbuf());
            break;
        case LOG_FILE:
            this->rdbuf(_fileStream.rdbuf());
            break;
        case LOG_BUFFER:
            this->rdbuf(&_logBuf);
            break;
        case LOG_NONE:
        default:
            this->rdbuf(_nilbufP);
            break;
    }
#endif

    for(i = 0; i < int(sizeof(_streamVec)/sizeof(std::ostream*)); ++i) 
    {
        if (i <= _logLevel)
        {
            _streamVec[i]->setrdbuf(this->rdbuf());
        }
        else
        {
#ifdef OSG_HAS_NILBUF
            _streamVec[i]->setrdbuf(_nilbufP);
#else
            _streamVec[i]->setrdbuf(_nilStreamP->rdbuf());
#endif
        }
    }
}

void Log::terminate(void)
{
#ifdef OSG_HAS_NILBUF
    delete Log::_nilbufP;
    
    Log::_nilbufP = NULL;
#else
    if(Log::_nilstreamP != NULL)
    {
        Log::_nilstreamP->close();

        delete Log::_nilstreamP;

        Log::_nilstreamP = NULL;
    }
#endif
    
    delete osgLogP;
}

/** \var LogType Log::_logType;
 *  \brief  holds the log type
 */

/** \var LogLevel Log::_logLevel;
 *  \brief holds the log level
 */

/** \var fstream Log::_fileStream;
 *  \brief file stream 
 */

/** \var LogOStream *Log::_streamVec[6];
 *  \brief stream vector
 */


OSG_BEGIN_NAMESPACE

OSG_BASE_DLLMAPPING LogP osgLogP = NULL;

OSG_END_NAMESPACE


void OSG::doInitLog(void)
{
#ifdef OSG_HAS_NILBUF
    if(Log::_nilbufP == NULL)
        Log::_nilbufP = new Log::nilbuf();
#else
    if(Log::_nilstreamP == NULL)
        Log::_nilstreamP = new std::fstream("/dev/null", std::ios::out);
#endif

    if(osgLogP == NULL)
    {
        osgLogP = new Log();

        osgLogP->setLogLevel(OSG_DEFAULT_LOG_LEVEL);
        osgLogP->setLogFile (NULL                 );
        osgLogP->setLogType (OSG_DEFAULT_LOG_TYPE );
    }
}
