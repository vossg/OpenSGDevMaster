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

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  LogStream
//---------------------------------------------------------------------------

inline
LogOStream::LogOStream(std::streambuf *buf) : 
    std::ostream(buf) 
{
}


inline
LogOStream::~LogOStream(void)
{
}

inline
void LogOStream::setrdbuf(std::streambuf *buf) 
{
#ifdef OSG_STREAM_RDBUF_HAS_PARAM
    std::ostream::rdbuf(buf); 
#else
    bp = buf; 
#endif
}

//---------------------------------------------------------------------------
//  LogBuf
//---------------------------------------------------------------------------

inline
LogBuf::Chunk::Chunk(void) : 
    data(NULL), 
    size(   0) 
{
}


inline
LogBuf::Chunk::~Chunk(void)
{
    delete [] data; 
}


inline
bool LogBuf::getEnabled(void)
{
    return _enabled; 
}


inline
void LogBuf::setEnabled(bool value)
{
    _enabled = value; 
}

//---------------------------------------------------------------------------
//  Log
//---------------------------------------------------------------------------

inline
void Log::lock(void)
{
    if(_pLogLock != NULL)
        _pLogLock->acquire();
}

inline
void Log::unlock(void)
{
    if(_pLogLock != NULL)
        _pLogLock->release();
}

inline 
bool Log::checkLevel(LogLevel level)
{
    return (_logLevel >= level) ? true : false;
}

inline
Time Log::getRefTime(void)
{
    return _refTime;
}

inline
void Log::setRefTime(Time refTime)
{
    _refTime = refTime;
}

inline
void Log::resetRefTime(void)
{
    _refTime = getSystemTime();
}


inline
Log::Module::Module(void) : 
    name(NULL), 
    isStatic(true) 
{
}

inline
LogBuf & Log::getLogBuf(void)
{
  return _logBuf;
}

inline
std::ostream &Log::stream(LogLevel level)
{
    return *(_streamVec[level]); 
}

inline
std::ostream &Log::nilstream(void)
{
    return *_nilstreamP;
}

inline 
LogLock::LogLock(std::ostream &os) : 
    _os(os)
{
    if(osgLogP != NULL)
        osgLogP->lock();
}

inline 
LogLock::~LogLock(void)
{
    if(osgLogP != NULL)
        osgLogP->unlock();
}

inline 
LogLock::operator std::ostream &()
{
    return _os;
}

inline 
void initLog(void) 
{
    if(osgLogP == NULL)
        doInitLog();
}

inline 
Log &osgLog(void) 
{
    initLog();

    return *osgLogP;
}

inline 
std::ostream &osgStartLog(      bool      logHeader,
                                LogLevel  level, 
                          const Char8    *module,
                          const Char8    *file, 
                                UInt32    line)
{
    if(GlobalSystemState <= Shutdown)
    {
        initLog();

        if(osgLogP->checkModule(module)) 
        {
            if(logHeader)
                osgLogP->doHeader(level,module,file,line);

            return osgLogP->stream(level);
        }
        else
            return osgLogP->nilstream();
    }
    else
    {
        return std::cout;
    }
}

// This function is deprecated, use the std::endl instead!
inline  
std::ostream &endLog(std::ostream &strm)
{
    strm << std::endl;
    return strm;
}

inline 
void indentLog(UInt32 indent, std::ostream &stream)
{
    for(UInt32 i = 0; i < indent; i++)
    {
        stream << " ";
    }
}

OSG_END_NAMESPACE


