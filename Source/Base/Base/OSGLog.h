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
#include "OSGTime.h"

#include <fstream>
#include <list>

/*! \defgroup GrpBaseLog Log
    \ingroup GrpBase
 */

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpBaseLog
 */

enum LogType
{
    LOG_NONE   = 0,
    LOG_STDOUT = 1,
    LOG_STDERR = 2,
    LOG_FILE   = 3,
    LOG_BUFFER = 4
};

/*! \ingroup GrpBaseLog
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

/*! \ingroup GrpBaseLog
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

    LOG_ALL_HEADER           = 127
};

/*! \ingroup GrpBaseLog
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

/*! \ingroup GrpBaseLog
    Logger ostream, required to fix some problems between the different
    plattforms
    \hideinhierarchy
 */

struct OSG_BASE_DLLMAPPING LogOStream : public std::ostream
{
  public:

    LogOStream(std::streambuf *buf);

    virtual ~LogOStream(void);

    void setrdbuf(std::streambuf *buf);
};

/*! \ingroup GrpBaseLog
    \hideinhierarchy
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

    /*! \hideinhierarchy */
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

/*! \ingroup GrpBaseLog
 *  Message logger class, handles info,warning and error messages
 *
 * Logging is controlled by several environment variables.
 *  - OSG_LOG_LEVEL: "log","fatal", "warning", "notice", "debug_gv","info", "debug"
 *  - OSG_LOG_TYPE: "none","-","stdout", "stderr", "file", "buffer"
 *  - OSG_LOG_FILE: Name of file to write log to.
 *  - OSG_LOG_HEADER: ???
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

    void lock  (void) {;} // TODO: implement
    void unlock(void) {;} // TODO: implement

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

    void connect(void);

    static void terminate(void);

    /*! \}                                                                 */
    /*===========================  PRIVATE  ===============================*/

  private:

    typedef std::ostream Inherited;

    friend OSG_BASE_DLLMAPPING void doInitLog(void);

    /*---------------------------------------------------------------------*/
    /*! \name                         Helper                               */
    /*! \{                                                                 */

    /*! \hideinhierarchy */
    struct OSG_BASE_DLLMAPPING nilbuf : public std::streambuf
    {
    };

    /*! \hideinhierarchy */
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

    static       nilbuf       *_nilbufP;
    static       std::ostream *_nilstreamP;

    static const Char8        *_levelName [];
    static const Char8        *_levelColor[];

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

    friend OSG_BASE_DLLMAPPING bool osgExit(void);
};

typedef Log *LogP;

#ifndef OSG_LOG_MODULE
#define OSG_LOG_MODULE "OpenSG"
#endif

extern OSG_BASE_DLLMAPPING LogP osgLogP;


OSG_BASE_DLLMAPPING
void          doInitLog  (      void                   );

inline
void          initLog    (      void                   );

inline
Log          &osgLog     (      void                   );

inline
std::ostream &osgStartLog(      bool          logHeader,
                                LogLevel      level,
                          const Char8        *module,
                          const Char8        *file,
                                UInt32        line     );

inline
std::ostream &endLog      (     std::ostream &strm     );

inline
void          indentLog   (     UInt32        indent,
                                std::ostream &stream   );


/*! \brief SLOG
    \ingroup GrpBaseLog
*/

#define SLOG     \
  OSG::osgStartLog(true, OSG::LOG_LOG,     OSG_LOG_MODULE, __FILE__, __LINE__)

/*! \brief SFATAL
    \ingroup GrpBaseLog
*/

#define SFATAL   \
  OSG::osgStartLog(true, OSG::LOG_FATAL,   OSG_LOG_MODULE, __FILE__, __LINE__)

/*! \brief SWARNING
    \ingroup GrpBaseLog
*/

#define SWARNING \
  OSG::osgStartLog(true, OSG::LOG_WARNING, OSG_LOG_MODULE, __FILE__, __LINE__)

/*! \brief SNOTICE
    \ingroup GrpBaseLog
*/

#define SNOTICE  \
  OSG::osgStartLog(true, OSG::LOG_NOTICE,  OSG_LOG_MODULE, __FILE__, __LINE__)

/*! \brief SINFO
    \ingroup GrpBaseLog
*/

#define SINFO    \
  OSG::osgStartLog(true, OSG::LOG_INFO,    OSG_LOG_MODULE, __FILE__, __LINE__)


/*! \brief PLOG
    \ingroup GrpBaseLog
*/

#define PLOG     \
  OSG::osgStartLog(false, OSG::LOG_LOG,     OSG_LOG_MODULE, __FILE__, __LINE__)

/*! \brief PFATAL
    \ingroup GrpBaseLog
*/

#define PFATAL   \
  OSG::osgStartLog(false, OSG::LOG_FATAL,   OSG_LOG_MODULE, __FILE__, __LINE__)

/*! \brief PWARNING
    \ingroup GrpBaseLog
*/

#define PWARNING \
 OSG:: osgStartLog(false, OSG::LOG_WARNING, OSG_LOG_MODULE, __FILE__, __LINE__)

/*! \brief PNOTICE
    \ingroup GrpBaseLog
*/

#define PNOTICE  \
  OSG::osgStartLog(false, OSG::LOG_NOTICE,  OSG_LOG_MODULE, __FILE__, __LINE__)

/*! \brief PINFO
    \ingroup GrpBaseLog
*/

#define PINFO    \
  OSG::osgStartLog(false, OSG::LOG_INFO,    OSG_LOG_MODULE, __FILE__, __LINE__)


// C interface, because it can be compiled away
// don't use varargs macros, because they are not supported everywhere
// use the (( )) convention instead

/*! \brief FLOG
    \ingroup GrpBaseLog
*/

#define FLOG(par)                                               \
{                                                               \
   OSG::initLog();                                              \
   OSG::osgStartLog(true,                                       \
                    OSG::LOG_LOG,                               \
                    OSG_LOG_MODULE,                             \
                    __FILE__,                                   \
                    __LINE__);                                  \
   OSG::osgLogP->doLog par;                                     \
   OSG::osgLogP->unlock();                                      \
}

/*! \brief FFATAL
    \ingroup GrpBaseLog
*/

#define FFATAL(par)                                             \
{                                                               \
    OSG::initLog();                                             \
    if(OSG::osgLogP->checkLevel(OSG::LOG_FATAL))                \
    {                                                           \
        OSG::osgStartLog(true,                                  \
                         OSG::LOG_FATAL,                        \
                         OSG_LOG_MODULE,                        \
                         __FILE__,                              \
                         __LINE__);                             \
        OSG::osgLogP->doLog par;                                \
        OSG::osgLogP->unlock();                                 \
    }                                                           \
}

/*! \brief FWARNING
    \ingroup GrpBaseLog
*/

#define FWARNING(par)                                           \
{                                                               \
    OSG::initLog();                                             \
    if(OSG::osgLogP->checkLevel(OSG::LOG_WARNING))              \
    {                                                           \
        OSG::osgStartLog(true,                                  \
                         OSG::LOG_WARNING,                      \
                         OSG_LOG_MODULE,                        \
                         __FILE__,                              \
                         __LINE__);                             \
        OSG::osgLogP->doLog par;                                \
        OSG::osgLogP->unlock();                                 \
    }                                                           \
}

/*! \brief FNOTICE
    \ingroup GrpBaseLog
*/

#define FNOTICE(par)                                            \
{                                                               \
    OSG::initLog();                                             \
    if(OSG::osgLogP->checkLevel(OSG::LOG_NOTICE))               \
    {                                                           \
        OSG::osgStartLog(true,                                  \
                         OSG::LOG_NOTICE,                       \
                         OSG_LOG_MODULE,                        \
                         __FILE__,                              \
                         __LINE__);                             \
        OSG::osgLogP->doLog par;                                \
        OSG::osgLogP->unlock();                                 \
    }                                                           \
}

/*! \brief FINFO
    \ingroup GrpBaseLog
*/

#define FINFO(par)                                              \
{                                                               \
    OSG::initLog();                                             \
    if(OSG::osgLogP->checkLevel(OSG::LOG_INFO))                 \
    {                                                           \
        OSG::osgStartLog(true,                                  \
                         OSG::LOG_INFO,                         \
                         OSG_LOG_MODULE,                        \
                         __FILE__,                              \
                         __LINE__);                             \
        OSG::osgLogP->doLog par;                                \
        OSG::osgLogP->unlock();                                 \
    }                                                           \
}

/*! \brief FDEBUG
    \ingroup GrpBaseLog
*/

#ifdef OSG_DEBUG
#define FDEBUG(par)                                             \
{                                                               \
    OSG::initLog();                                             \
    if(OSG::osgLogP->checkLevel(OSG::LOG_DEBUG))                \
    {                                                           \
        OSG::osgStartLog(true,                                  \
                         OSG::LOG_DEBUG,OSG_LOG_MODULE,         \
                         __FILE__,                              \
                         __LINE__);                             \
        OSG::osgLogP->doLog par;                                \
        OSG::osgLogP->unlock();                                 \
    }                                                           \
}
#else
#define FDEBUG(par)
#endif

/*! \brief FDEBUG
    \ingroup GrpBaseLog
*/

#ifdef OSG_DEBUG
#define FDEBUG_GV(par)                                          \
{                                                               \
    OSG::initLog();                                             \
    if(OSG::osgLogP->checkLevel(OSG::LOG_DEBUG_GV))             \
    {                                                           \
        OSG::osgStartLog(true,                                  \
                         OSG::LOG_DEBUG_GV,OSG_LOG_MODULE,      \
                         __FILE__,                              \
                         __LINE__);                             \
        OSG::osgLogP->doLog par;                                \
        OSG::osgLogP->unlock();                                 \
    }                                                           \
}
#else
#define FDEBUG_GV(par)
#endif

/*! \brief FASSERT
    \ingroup GrpBaseLog
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

/*! \brief FFASSERT
    \ingroup GrpBaseLog
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

// C interface without line start outputs

/*! \brief FPLOG
    \ingroup GrpBaseLog
*/

#define FPLOG(par)                                              \
{                                                               \
   OSG::initLog();                                              \
   OSG::osgStartLog(false,                                      \
                    OSG::LOG_LOG,                               \
                    OSG_LOG_MODULE,                             \
                    __FILE__,                                   \
                    __LINE__);                                  \
   OSG::osgLogP->doLog par;                                     \
   OSG::osgLogP->unlock();                                      \
}

/*! \brief FPFPATAL
    \ingroup GrpBaseLog
*/

#define FPFPATAL(par)                                           \
{                                                               \
    OSG::initLog();                                             \
    if(OSG::osgLogP->checkLevel(OSG::LOG_FPATAL))               \
    {                                                           \
        OSG::osgStartLog(false,                                 \
                         OSG::LOG_FPATAL,                       \
                         OSG_LOG_MODULE,                        \
                         __FILE__,                              \
                         __LINE__);                             \
        OSG::osgLogP->doLog par;                                \
        OSG::osgLogP->unlock();                                 \
    }                                                           \
}

/*! \brief FPWARNING
    \ingroup GrpBaseLog
*/

#define FPWARNING(par)                                          \
{                                                               \
    OSG::initLog();                                             \
    if(OSG::osgLogP->checkLevel(OSG::LOG_WARNING))              \
    {                                                           \
        OSG::osgStartLog(false,                                 \
                         OSG::LOG_WARNING,                      \
                         OSG_LOG_MODULE,                        \
                         __FILE__,                              \
                         __LINE__);                             \
        OSG::osgLogP->doLog par;                                \
        OSG::osgLogP->unlock();                                 \
    }                                                           \
}

/*! \brief FPNOTICE
    \ingroup GrpBaseLog
*/

#define FPNOTICE(par)                                           \
{                                                               \
    OSG::initLog();                                             \
    if(OSG::osgLogP->checkLevel(OSG::LOG_NOTICE))               \
    {                                                           \
        OSG::osgStartLog(false,                                 \
                         OSG::LOG_NOTICE,                       \
                         OSG_LOG_MODULE,                        \
                         __FILE__,                              \
                         __LINE__);                             \
        OSG::osgLogP->doLog par;                                \
        OSG::osgLogP->unlock();                                 \
    }                                                           \
}

/*! \brief FPINFPO
    \ingroup GrpBaseLog
*/

#define FPINFPO(par)                                            \
{                                                               \
    OSG::initLog();                                             \
    if(OSG::osgLogP->checkLevel(OSG::LOG_INFPO))                \
    {                                                           \
        OSG::osgStartLog(false,                                 \
                         OSG::LOG_INFPO,                        \
                         OSG_LOG_MODULE,                        \
                         __FILE__,                              \
                         __LINE__);                             \
        OSG::osgLogP->doLog par;                                \
        OSG::osgLogP->unlock();                                 \
    }                                                           \
}

/*! \brief FPDEBUG
    \ingroup GrpBaseLog
*/

#ifdef OSG_DEBUG
#define FPDEBUG(par)                                            \
{                                                               \
    OSG::initLog();                                             \
    if(OSG::osgLogP->checkLevel(OSG::LOG_DEBUG))                \
    {                                                           \
        OSG::osgStartLog(false,                                 \
                         OSG::LOG_DEBUG,OSG_LOG_MODULE,         \
                         __FILE__,                              \
                         __LINE__);                             \
        OSG::osgLogP->doLog par;                                \
        OSG::osgLogP->unlock();                                 \
    }                                                           \
}
#else
#define FPDEBUG(par)
#endif

#ifdef OSG_DEBUG
#define FPDEBUG_GV(par)                                         \
{                                                               \
    OSG::initLog();                                             \
    if(OSG::osgLogP->checkLevel(OSG::LOG_DEBUG_GV))             \
    {                                                           \
        OSG::osgStartLog(false,                                 \
                         OSG::LOG_DEBUG_GV,OSG_LOG_MODULE,      \
                         __FILE__,                              \
                         __LINE__);                             \
        OSG::osgLogP->doLog par;                                \
        OSG::osgLogP->unlock();                                 \
    }                                                           \
}
#else
#define FPDEBUG_GV(par)
#endif

OSG_END_NAMESPACE

#include "OSGLog.inl"

#endif /* _OSGLOG_H_ */
