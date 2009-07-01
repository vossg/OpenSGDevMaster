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

#ifndef _OSGLOG_H_
#define _OSGLOG_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGBaseTypes.h"
#include "OSGBaseInitFunctions.h"
#include "OSGTime.h"
#include "OSGLock.h"

#include <cstdio>
#include <fstream>
#include <list>


OSG_BEGIN_NAMESPACE

/*! \name Configuration Enums
    \{
 */

/*! \ingroup GrpBaseBaseLog
 */

enum LogType
{
    LOG_NONE   = 0,
    LOG_STDOUT = 1,
    LOG_STDERR = 2,
    LOG_FILE   = 3,
    LOG_BUFFER = 4
};

/*! \ingroup GrpBaseBaseLog
 */

enum LogLevel
{
    LOG_LOG      = 0,
    LOG_FATAL    = 1,
    LOG_WARNING  = 2,
    LOG_NOTICE   = 3,
    LOG_DEBUG_GV = 4,
    LOG_INFO     = 5,
    LOG_DEBUG    = 6
};

/*! \ingroup GrpBaseBaseLog
 */

enum LogHeaderElem
{
    LOG_NONE_HEADER          = 0,
    LOG_BEGIN_NEWLINE_HEADER = 1,
    LOG_TYPE_HEADER          = 2,
    LOG_TIMESTAMP_HEADER     = 4,
    LOG_MODULE_HEADER        = 8,
    LOG_FILE_HEADER          = 16,
    LOG_LINE_HEADER          = 32,
    LOG_END_NEWLINE_HEADER   = 64,

    LOG_COLOR_HEADER         = 8192,
    LOG_TAB_HEADER           = 16384,

    LOG_ALL_HEADER           = 32767
};

/*! \ingroup GrpBaseBaseLog
    \brief Log Module Handling
 */

enum LogModuleHandling
{
    LOG_MODULE_NONE           = 0,
    LOG_MODULE_KNOWN          = 1,
    LOG_MODULE_UNKNOWN        = 2,
    LOG_MODULE_UNDEFINED      = 4,
    LOG_MODULE_ALL            = 7
};

/*! \} */

/*! \name Defaults
    \{
 */

#ifndef OSG_DEFAULT_LOG_LEVEL
#    define OSG_DEFAULT_LOG_LEVEL LOG_WARNING
#endif

#ifndef OSG_DEFAULT_LOG_TYPE
#    define OSG_DEFAULT_LOG_TYPE LOG_STDERR
#endif

/*! \} */


/*! \ingroup GrpBaseBaseLog
    \ingroup GrpLibOSGBase
    Logger ostream, required to fix some problems between the different
    plattforms
    \nohierarchy
 */

struct OSG_BASE_DLLMAPPING LogOStream : public std::ostream
{
  public:

    LogOStream(std::streambuf *buf);

    virtual ~LogOStream(void);

    void setrdbuf(std::streambuf *buf);
};

/*! \ingroup GrpBaseBaseLog
    \ingroup GrpLibOSGBase
    \nohierarchy
    stream buf helper class; creates a chunk buffer of all messages
    which can ge fetched by a application (e.g. gui)
 */

class OSG_BASE_DLLMAPPING LogBuf : public std::streambuf
{
    /*==========================  PUBLIC  =================================*/

  public:

  // only temporary until the functors work with all compiler

    typedef void (*Callback)(const Char8 *data,
                                   Int32  size,
                                   void  *clientData);

    /*! \nohierarchy */
    struct Chunk
    {
        Char8 *data;
        Int32  size;

        Chunk(void);
        ~Chunk(void);
    };

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    LogBuf(      UInt32  bufferSize = 1024);
    LogBuf(const LogBuf &                 );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~LogBuf();

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Class Specific                             */
    /*! \{                                                                 */

    bool getEnabled   (void             );
    void setEnabled   (bool value = true);

    void clearChunkBag(void             );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Callback handling                          */
    /*! \{                                                                 */

    void setCallback   (Callback  cb,
                        void     *clientData = 0,
                        bool      flushData  = false);
    void removeCallback(void                        );


    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    bool               _enabled;

    std::list<Chunk*>  _chunkBag;

    Callback           _callback;
    void              *_clientData;

    const LogBuf &operator=(const LogBuf          &);
          void    write    (const Char8           *buffer,
                                  std::streamsize  size  );

    /*---------------------------------------------------------------------*/
    /*! \name                   Callback handling                          */
    /*! \{                                                                 */

    virtual Int32           overflow(      Int32            c    );
    virtual Int32           sync    (      void                  );
    virtual std::streamsize xsputn  (const Char8           *buffer,
                                           std::streamsize  size);

};

/*! \ingroup GrpBaseBaseLog
    \ingroup GrpLibOSGBase
    \nohierarchy
    Message logger class, handles info,warning and error messages

    Logging is controlled by several environment variables.
    - OSG_LOG_LEVEL_STARTUP:
        The level a message has to have to be emitted during system startup,
        one of: "log", "fatal", "warning", "notice", debug_gv", "info", "debug"
    - OSG_LOG_LEVEL:
        The level a message has to have to be emitted, one of "log", "fatal",
        "warning", "notice", "debug_gv","info", "debug"
    - OSG_LOG_TYPE: "none","-","stdout", "stderr", "file", "buffer"
    - OSG_LOG_FILE: Name of file to write log to.
    - OSG_LOG_HEADER: ???
 */
class OSG_BASE_DLLMAPPING Log : public std::ostream
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    Log(      LogType   logType  = LOG_STDERR,
              LogLevel  logLevel = LOG_NOTICE);

    Log(const Char8    *fileName,
              LogLevel  logLevel = LOG_NOTICE);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~Log(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Class Specific                             */
    /*! \{                                                                 */

    static bool initLock    (void);
    
    static bool finalizeLock(void);

           void lock        (void);
           void unlock      (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Module Handling                             */
    /*! \{                                                                 */

    virtual void setHeaderElem    (      UInt32             elemMask,
                                         bool               force    = false);
    virtual void addHeaderElem    (      LogHeaderElem      elem,
                                         bool               force    = false);
    virtual void delHeaderElem    (      LogHeaderElem      elem,
                                         bool               force    = false);
    virtual bool hasHeaderElem    (      LogHeaderElem      elem);

    virtual void addModuleHandling(      LogModuleHandling  handling,
                                         bool               force    = false);
    virtual void delModuleHandling(      LogModuleHandling  handling,
                                         bool               force    = false);

    virtual void addModuleName    (const Char8             *module,
                                         bool               isStatic = false);
    virtual void delModuleName    (const Char8             *module          );

            bool hasModule        (const Char8             *module          );
            bool checkModule      (const Char8             *module          );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name              Level, Type and Time Handling                   */
    /*! \{                                                                 */

    LogType  getLogType  (      void                                  );
    void     setLogType  (      LogType   logType,  bool force = false);

    LogLevel getLogLevel (      void);
    void     setLogLevel (      LogLevel  logLevel, bool force = false);
    bool     checkLevel  (      LogLevel  logLevel                    );

    void     setLogFile  (const Char8    *fileName, bool force = false);

    Time     getRefTime  (      void                                  );
    void     setRefTime  (      Time  refTime                         );
    void     resetRefTime(      void                                  );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Stream Handling                            */
    /*! \{                                                                 */

    LogBuf       &getLogBuf(void          );

    std::ostream &stream   (LogLevel level);
    std::ostream &nilstream(void          );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Logging                                */
    /*! \{                                                                 */

    std::ostream &doHeader(      LogLevel  level,
                           const Char8    *module,
                           const Char8    *file,
                                 UInt32    line       );

    void          doLog   (const Char8    *format, ...);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                   Class Specific                             */
    /*! \{                                                                 */

    void connect    (void                           );

    bool colorHeader(LogLevel level, const char *sep);

    static void terminate(void);

    /*! \}                                                                 */
    /*===========================  PRIVATE  ===============================*/

  private:

    typedef std::ostream Inherited;

    friend OSG_BASE_DLLMAPPING void doInitLog(void);
    friend OSG_BASE_DLLMAPPING bool osgExit  (void);

    /*---------------------------------------------------------------------*/
    /*! \name                         Helper                               */
    /*! \{                                                                 */

    /*! \nohierarchy */
    struct OSG_BASE_DLLMAPPING nilbuf : public std::streambuf
    {
    };

    /*! \nohierarchy */
    struct Module
    {
        const Char8 *name;
              bool   isStatic;

        Module(void);
    };

    /*! \{                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Static Fields                             */
    /*! \{                                                                 */

    static       nilbuf          *_nilbufP;
    static       std::ostream    *_nilstreamP;

    static const Char8           *_levelName [];
    static const Char8           *_levelColor[];

    static       Char8           *_buffer;
    static       int              _bufferSize;

    static       Lock            *_pLogLock;
    static       InitFuncWrapper  _lockInit;
    
    /*! \{                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Static Fields                             */
    /*! \{                                                                 */

    LogType            _logType;
    LogLevel           _logLevel;

    std::fstream       _fileStream;

    LogBuf             _logBuf;
    LogOStream        *_streamVec[7];

    UInt32             _headerElem;
    UInt32             _moduleHandling;


    std::list<Module>  _moduleList;

    Time               _refTime;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    Log(const Log &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Operators                                  */
    /*! \{                                                                 */

    void operator =(const Log &source);

    /*! \}                                                                 */
};

typedef Log *LogP;

/*! \ingroup GrpBaseBaseLog
    \ingroup GrpLibOSGBase
    \nohierarchy
 *  Helper class that handles locking and unlocking of the Log object
 */

class OSG_BASE_DLLMAPPING LogLock
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    LogLock(std::ostream &os);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    ~LogLock(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Class Specific                             */
    /*! \{                                                                 */

    operator std::ostream &();

    /*! \}                                                                 */
    /*===========================  PRIVATE  ===============================*/

  private:

    std::ostream &_os;
};

#ifndef OSG_LOG_MODULE
#define OSG_LOG_MODULE "OpenSG"
#endif

extern OSG_BASE_DLLMAPPING LogP osgLogP;

/*! \name Helper Functions
    \{
 */

/*! \ingroup GrpBaseBaseLog
 */
OSG_BASE_DLLMAPPING
void          doInitLog  (      void                   );

/*! \ingroup GrpBaseBaseLog
 */
inline
void          initLog    (      void                   );

/*! \ingroup GrpBaseBaseLog
 */
inline
OSG::Log     &osgLog     (      void                   );

/*! \ingroup GrpBaseBaseLog
 */
inline
std::ostream &osgStartLog(      bool           logHeader,
                                OSG::LogLevel  level,
                          const OSG::Char8    *module,
                          const OSG::Char8    *file,
                                OSG::UInt32    line     );

/*! \ingroup GrpBaseBaseLog
 */
inline
std::ostream &endLog      (     std::ostream  &strm     );

/*! \ingroup GrpBaseBaseLog
 */
inline
void          indentLog   (     OSG::UInt32    indent,
                                std::ostream  &stream   );
/*! \} */

/*! \name S-Macros
    \{
 */

/*! \ingroup GrpBaseBaseLog
*/

#define SLOG                                                       \
  static_cast<std::ostream&>(OSG::LogLock(                         \
                                OSG::osgStartLog(true,             \
                                                 OSG::LOG_LOG,     \
                                                 OSG_LOG_MODULE,   \
                                                 __FILE__,         \
                                                 __LINE__)))

/*! \ingroup GrpBaseBaseLog
*/

#define SFATAL                                                     \
  static_cast<std::ostream&>(OSG::LogLock(                         \
                                OSG::osgStartLog(true,             \
                                                 OSG::LOG_FATAL,   \
                                                 OSG_LOG_MODULE,   \
                                                 __FILE__,         \
                                                 __LINE__)))

/*! \ingroup GrpBaseBaseLog
*/

#define SWARNING                                                   \
  static_cast<std::ostream&>(OSG::LogLock(                         \
                                OSG::osgStartLog(true,             \
                                                 OSG::LOG_WARNING, \
                                                 OSG_LOG_MODULE,   \
                                                 __FILE__,         \
                                                 __LINE__)))

/*! \ingroup GrpBaseBaseLog
*/

#define SNOTICE                                                    \
  static_cast<std::ostream&>(OSG::LogLock(                         \
                                OSG::osgStartLog(true,             \
                                                 OSG::LOG_NOTICE,  \
                                                 OSG_LOG_MODULE,   \
                                                 __FILE__,         \
                                                 __LINE__)))

/*! \ingroup GrpBaseBaseLog
*/

#define SINFO                                                      \
  static_cast<std::ostream&>(OSG::LogLock(                         \
                                OSG::osgStartLog(true,             \
                                                 OSG::LOG_INFO,    \
                                                 OSG_LOG_MODULE,   \
                                                 __FILE__,         \
                                                 __LINE__)))

/*! \} */

/*! \name P-Macros
    \{
 */

/*! \ingroup GrpBaseBaseLog
*/

#define PLOG                                                       \
  static_cast<std::ostream&>(OSG::LogLock(                         \
                                OSG::osgStartLog(false,            \
                                                 OSG::LOG_LOG,     \
                                                 OSG_LOG_MODULE,   \
                                                 __FILE__,         \
                                                 __LINE__)))

/*! \ingroup GrpBaseBaseLog
*/

#define PFATAL                                                     \
  static_cast<std::ostream&>(OSG::LogLock(                         \
                                OSG::osgStartLog(false,            \
                                                 OSG::LOG_FATAL,   \
                                                 OSG_LOG_MODULE,   \
                                                 __FILE__,         \
                                                 __LINE__)))

/*! \ingroup GrpBaseBaseLog
*/

#define PWARNING                                                   \
  static_cast<std::ostream&>(OSG::LogLock(                         \
                                OSG:: osgStartLog(false,           \
                                                  OSG::LOG_WARNING,\
                                                  OSG_LOG_MODULE,  \
                                                  __FILE__,        \
                                                  __LINE__)))

/*! \ingroup GrpBaseBaseLog
*/

#define PNOTICE                                                    \
  static_cast<std::ostream&>(OSG::LogLock(                         \
                                OSG::osgStartLog(false,            \
                                                 OSG::LOG_NOTICE,  \
                                                 OSG_LOG_MODULE,   \
                                                 __FILE__,         \
                                                 __LINE__)))

/*! \ingroup GrpBaseBaseLog
*/

#define PINFO                                                      \
  static_cast<std::ostream&>(OSG::LogLock(                         \
                                OSG::osgStartLog(false,            \
                                                 OSG::LOG_INFO,    \
                                                 OSG_LOG_MODULE,   \
                                                 __FILE__,         \
                                                 __LINE__)))

/*! \} */

/*! \name F-Macros
    \{
 */

// C interface, because it can be compiled away
// don't use varargs macros, because they are not supported everywhere
// use the (( )) convention instead

/*! \ingroup GrpBaseBaseLog
*/

#define FLOG(par)                                               \
{                                                               \
    if(OSG::GlobalSystemState <= OSG::Shutdown)                 \
    {                                                           \
        OSG::initLog();                                         \
        OSG::osgLogP->lock();                                   \
        OSG::osgStartLog(true,                                  \
                         OSG::LOG_LOG,                          \
                         OSG_LOG_MODULE,                        \
                         __FILE__,                              \
                         __LINE__);                             \
        OSG::osgLogP->doLog par;                                \
        OSG::osgLogP->unlock();                                 \
    }                                                           \
    else                                                        \
    {                                                           \
        std::printf par;                                        \
    }                                                           \
}

/*! \ingroup GrpBaseBaseLog
*/

#define FFATAL(par)                                             \
{                                                               \
    if(OSG::GlobalSystemState <= OSG::Shutdown)                 \
    {                                                           \
        OSG::initLog();                                         \
        if(OSG::osgLogP->checkLevel(OSG::LOG_FATAL))            \
        {                                                       \
            OSG::osgLogP->lock();                               \
            OSG::osgStartLog(true,                              \
                             OSG::LOG_FATAL,                    \
                             OSG_LOG_MODULE,                    \
                             __FILE__,                          \
                             __LINE__);                         \
            OSG::osgLogP->doLog par;                            \
            OSG::osgLogP->unlock();                             \
        }                                                       \
    }                                                           \
    else                                                        \
    {                                                           \
        std::printf par;                                        \
    }                                                           \
}

/*! \ingroup GrpBaseBaseLog
*/

#define FWARNING(par)                                           \
{                                                               \
    if(OSG::GlobalSystemState <= OSG::Shutdown)                 \
    {                                                           \
        OSG::initLog();                                         \
        if(OSG::osgLogP->checkLevel(OSG::LOG_WARNING))          \
        {                                                       \
            OSG::osgLogP->lock();                               \
            OSG::osgStartLog(true,                              \
                             OSG::LOG_WARNING,                  \
                             OSG_LOG_MODULE,                    \
                             __FILE__,                          \
                             __LINE__);                         \
            OSG::osgLogP->doLog par;                            \
            OSG::osgLogP->unlock();                             \
        }                                                       \
    }                                                           \
    else                                                        \
    {                                                           \
        std::printf par;                                        \
    }                                                           \
}

/*! \ingroup GrpBaseBaseLog
*/

#define FNOTICE(par)                                                \
{                                                                   \
    if(OSG::GlobalSystemState <= OSG::Shutdown)                     \
    {                                                               \
        OSG::initLog();                                             \
        if(OSG::osgLogP->checkLevel(OSG::LOG_NOTICE))               \
        {                                                           \
            OSG::osgLogP->lock();                                   \
            OSG::osgStartLog(true,                                  \
                             OSG::LOG_NOTICE,                       \
                             OSG_LOG_MODULE,                        \
                             __FILE__,                              \
                             __LINE__);                             \
            OSG::osgLogP->doLog par;                                \
            OSG::osgLogP->unlock();                                 \
        }                                                           \
    }                                                               \
    else                                                            \
    {                                                               \
        std::printf par;                                            \
    }                                                               \
}

/*! \ingroup GrpBaseBaseLog
*/

#define FINFO(par)                                              \
{                                                               \
    if(OSG::GlobalSystemState <= OSG::Shutdown)                 \
    {                                                           \
        OSG::initLog();                                         \
        if(OSG::osgLogP->checkLevel(OSG::LOG_INFO))             \
        {                                                       \
            OSG::osgLogP->lock();                               \
            OSG::osgStartLog(true,                              \
                             OSG::LOG_INFO,                     \
                             OSG_LOG_MODULE,                    \
                             __FILE__,                          \
                             __LINE__);                         \
            OSG::osgLogP->doLog par;                            \
            OSG::osgLogP->unlock();                             \
        }                                                       \
    }                                                           \
    else                                                        \
    {                                                           \
        std::printf par;                                        \
    }                                                           \
}

/*! \ingroup GrpBaseBaseLog
*/

#ifdef OSG_DEBUG
#define FDEBUG(par)                                             \
{                                                               \
    if(OSG::GlobalSystemState <= OSG::Shutdown)                 \
    {                                                           \
        OSG::initLog();                                         \
        if(OSG::osgLogP->checkLevel(OSG::LOG_DEBUG))            \
        {                                                       \
            OSG::osgLogP->lock();                               \
            OSG::osgStartLog(true,                              \
                             OSG::LOG_DEBUG,OSG_LOG_MODULE,     \
                             __FILE__,                          \
                             __LINE__);                         \
            OSG::osgLogP->doLog par;                            \
            OSG::osgLogP->unlock();                             \
        }                                                       \
    }                                                           \
    else                                                        \
    {                                                           \
        std::printf par;                                        \
    }                                                           \
}
#else
#define FDEBUG(par)
#endif

/*! \ingroup GrpBaseBaseLog
*/

#ifdef OSG_DEBUG
#define FDEBUG_GV(par)                                              \
{                                                                   \
    if(OSG::GlobalSystemState <= OSG::Shutdown)                     \
    {                                                               \
        OSG::initLog();                                             \
        if(OSG::osgLogP->checkLevel(OSG::LOG_DEBUG_GV))             \
        {                                                           \
            OSG::osgLogP->lock();                                   \
            OSG::osgStartLog(true,                                  \
                             OSG::LOG_DEBUG_GV,OSG_LOG_MODULE,      \
                             __FILE__,                              \
                             __LINE__);                             \
            OSG::osgLogP->doLog par;                                \
            OSG::osgLogP->unlock();                                 \
        }                                                           \
    }                                                               \
    else                                                            \
    {                                                               \
        std::printf par;                                            \
    }                                                               \
}
#else
#define FDEBUG_GV(par)
#endif

/*! \ingroup GrpBaseBaseLog
*/

#define FASSERT(condition, doExit)                              \
{                                                               \
    if (!condition)                                             \
    {                                                           \
        OSG::osgLog().lock();                                   \
        OSG::osgLog().stream(OSG::LOG_FATAL)                    \
            << OSG_LOG_MODULE                                   \
            << ':'                                              \
            << __FILE__                                         \
            << ':'                                              \
            << __LINE__                                         \
            << " FATAL ASSERT: "                                \
            << (doExit ? "exit system" : "try to keep running") \
            << std::flush << std::endl;                         \
        OSG::osgLog().unlock();                                 \
        if(doExit)                                              \
            exit(-1);                                           \
    }                                                           \
}

/*! \ingroup GrpBaseBaseLog
*/

#define FFASSERT(condition, doExit, par)                        \
{                                                               \
    if(!condition)                                              \
    {                                                           \
        OSG::osgLog().lock();                                   \
        OSG::osgLog().stream(OSG::LOG_FATAL)                    \
            << OSG_LOG_MODULE                                   \
            << ':'                                              \
            << __FILE__                                         \
            << ':'                                              \
            << __LINE__                                         \
            << " FATAL ASSERT: "                                \
            << (doExit ? "exit system" : "try to keep running") \
            << std::flush << std::endl;                         \
        OSG::osgLogP->doLog par                                 \
        OSG::osgLog().unlock();                                 \
        if(doExit)                                              \
            exit(-1);                                           \
    }                                                           \
}

/*! \} */

/*! \name FP-Macros
    \{
 */

// C interface without line start outputs

/*! \ingroup GrpBaseBaseLog
*/

#define FPLOG(par)                                              \
{                                                               \
    if(OSG::GlobalSystemState <= OSG::Shutdown)                 \
    {                                                           \
        OSG::initLog();                                         \
        OSG::osgLogP->lock();                                   \
        OSG::osgStartLog(false,                                 \
                         OSG::LOG_LOG,                          \
                         OSG_LOG_MODULE,                        \
                         __FILE__,                              \
                         __LINE__);                             \
        OSG::osgLogP->doLog par;                                \
        OSG::osgLogP->unlock();                                 \
    }                                                           \
    else                                                        \
    {                                                           \
        std::printf par;                                        \
    }                                                           \
}

/*! \ingroup GrpBaseBaseLog
*/

#define FPFATAL(par)                                            \
{                                                               \
    if(OSG::GlobalSystemState <= OSG::Shutdown)                 \
    {                                                           \
        OSG::initLog();                                         \
        if(OSG::osgLogP->checkLevel(OSG::LOG_FATAL))            \
        {                                                       \
            OSG::osgLogP->lock();                               \
            OSG::osgStartLog(false,                             \
                             OSG::LOG_FATAL,                    \
                             OSG_LOG_MODULE,                    \
                             __FILE__,                          \
                             __LINE__);                         \
            OSG::osgLogP->doLog par;                            \
            OSG::osgLogP->unlock();                             \
        }                                                       \
    }                                                           \
    else                                                        \
    {                                                           \
        std::printf par;                                        \
    }                                                           \
}

/*! \ingroup GrpBaseBaseLog
*/

#define FPWARNING(par)                                          \
{                                                               \
    if(OSG::GlobalSystemState <= OSG::Shutdown)                 \
    {                                                           \
        OSG::initLog();                                         \
        if(OSG::osgLogP->checkLevel(OSG::LOG_WARNING))          \
        {                                                       \
            OSG::osgLogP->lock();                               \
            OSG::osgStartLog(false,                             \
                             OSG::LOG_WARNING,                  \
                             OSG_LOG_MODULE,                    \
                             __FILE__,                          \
                             __LINE__);                         \
            OSG::osgLogP->doLog par;                            \
            OSG::osgLogP->unlock();                             \
        }                                                       \
    }                                                           \
    else                                                        \
    {                                                           \
        std::printf par;                                        \
    }                                                           \
}

/*! \ingroup GrpBaseBaseLog
*/

#define FPNOTICE(par)                                           \
{                                                               \
    if(OSG::GlobalSystemState <= OSG::Shutdown)                 \
    {                                                           \
        OSG::initLog();                                         \
        if(OSG::osgLogP->checkLevel(OSG::LOG_NOTICE))           \
        {                                                       \
            OSG::osgLogP->lock();                               \
            OSG::osgStartLog(false,                             \
                             OSG::LOG_NOTICE,                   \
                             OSG_LOG_MODULE,                    \
                             __FILE__,                          \
                             __LINE__);                         \
            OSG::osgLogP->doLog par;                            \
            OSG::osgLogP->unlock();                             \
        }                                                       \
    }                                                           \
    else                                                        \
    {                                                           \
        std::printf par;                                        \
    }                                                           \
}

/*! \ingroup GrpBaseBaseLog
*/

#define FPINFO(par)                                             \
{                                                               \
    if(OSG::GlobalSystemState <= OSG::Shutdown)                 \
    {                                                           \
        OSG::initLog();                                         \
        if(OSG::osgLogP->checkLevel(OSG::LOG_INFO))             \
        {                                                       \
            OSG::osgLogP->lock();                               \
            OSG::osgStartLog(false,                             \
                             OSG::LOG_INFO,                     \
                             OSG_LOG_MODULE,                    \
                             __FILE__,                          \
                             __LINE__);                         \
            OSG::osgLogP->doLog par;                            \
            OSG::osgLogP->unlock();                             \
        }                                                       \
    }                                                           \
    else                                                        \
    {                                                           \
        std::printf par;                                        \
    }                                                           \
}

/*! \ingroup GrpBaseBaseLog
*/

#ifdef OSG_DEBUG
#define FPDEBUG(par)                                            \
{                                                               \
    if(OSG::GlobalSystemState <= OSG::Shutdown)                 \
    {                                                           \
        OSG::initLog();                                         \
        if(OSG::osgLogP->checkLevel(OSG::LOG_DEBUG))            \
        {                                                       \
            OSG::osgLogP->lock();                               \
            OSG::osgStartLog(false,                             \
                             OSG::LOG_DEBUG,OSG_LOG_MODULE,     \
                             __FILE__,                          \
                             __LINE__);                         \
            OSG::osgLogP->doLog par;                            \
            OSG::osgLogP->unlock();                             \
        }                                                       \
    }                                                           \
    else                                                        \
    {                                                           \
        std::printf par;                                        \
    }                                                           \
}
#else
#define FPDEBUG(par)
#endif

#ifdef OSG_DEBUG
#define FPDEBUG_GV(par)                                         \
{                                                               \
    if(OSG::GlobalSystemState <= OSG::Shutdown)                 \
    {                                                           \
        OSG::initLog();                                         \
        if(OSG::osgLogP->checkLevel(OSG::LOG_DEBUG_GV))         \
        {                                                       \
            OSG::osgLogP->lock();                               \
            OSG::osgStartLog(false,                             \
                             OSG::LOG_DEBUG_GV,OSG_LOG_MODULE,  \
                             __FILE__,                          \
                             __LINE__);                         \
            OSG::osgLogP->doLog par;                            \
            OSG::osgLogP->unlock();                             \
        }                                                       \
    }                                                           \
    else                                                        \
    {                                                           \
        std::printf par;                                        \
    }                                                           \
}
#else
#define FPDEBUG_GV(par)
#endif

/*! \} */

OSG_END_NAMESPACE

#include "OSGLog.inl"

#endif /* _OSGLOG_H_ */
