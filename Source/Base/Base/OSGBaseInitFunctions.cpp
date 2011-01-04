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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include "OSGConfig.h"

#include <cstdlib>
#include <cstdio>
#include <cmath>

#include <cstring>


#include <vector>

#include "OSGBaseInitFunctions.h"

#include "OSGThreadManager.h"

#include "OSGFactoryController.h"
#include "OSGSharedObjectHandler.h"
#include "OSGFileSystem.h"

#include <locale.h>

OSG_BEGIN_NAMESPACE

static std::vector<InitFuncF>    *osgPreMPInitFunctions       = NULL;
static std::vector<InitFuncF>    *osgPreFactoryInitFunctions  = NULL;
static std::vector<InitFuncF>    *osgPostFactoryInitFunctions = NULL;

static std::vector<ExitFuncF>    *osgPreFactoryExitFunctions  = NULL;
static std::vector<ExitFuncF>    *osgPostFactoryExitFunctions = NULL;
static std::vector<ExitFuncF>    *osgPreMPExitFunctions       = NULL;
static std::vector<ExitFuncF>    *osgPostMPExitFunctions      = NULL;

static std::vector<tstring  >    *osgPreloadSharedObject      = NULL;



/*! \ingroup GrpBaseBaseInitExit
    \nohierarchy
 */

struct OSG_BASE_DLLMAPPING CompileConfig
{
    /*---------------------------------------------------------------------*/
    /*! \name                      Constructors                            */
    /*! \{                                                                 */

    CompileConfig(UInt16 major, 
                  UInt16 minor, 
                  UInt16 release,
                  bool debug, 
                  bool dll, 
                  bool mt);

    bool compare(const CompileConfig& c);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Members                               */
    /*! \{                                                                 */

    UInt16  _major;
    UInt16  _minor;
    UInt16  _release;

    // Windows-specific ones
 
    bool    _debug;
    bool    _dll;
    bool    _mt;
    
    /*! \}                                                                 */
};

CompileConfig::CompileConfig(UInt16 major, 
                             UInt16 minor, 
                             UInt16 release,
                             bool debug, 
                             bool dll, 
                             bool mt) :
    _major  (major  ),
    _minor  (minor  ),
    _release(release),
    _debug  (debug  ),
    _dll    (dll    ),
    _mt     (mt     )
{
}

bool CompileConfig::compare(const CompileConfig &c)
{
    FDEBUG(("CompileConfig::compare: lib: version %d.%d.%d, %sdebug, %sdll, "
            "%smt \n",
            _major, 
            _minor, 
            _release, 
            _debug ? "" : "non-", 
            _dll   ? "" : "non-", 
            _mt    ? "" : "non-"));

    FDEBUG(("CompileConfig::compare: prog: version %d.%d.%d, %sdebug, %sdll, "
            "%smt \n",
            c._major, 
            c._minor, 
            c._release, 
            c._debug ? "" : "non-", 
            c._dll   ? "" : "non-", 
            c._mt    ? "" : "non-"));
             
    if(_major != c._major)
    {
        FFATAL(("The program is compiled against version %d headers, "
                "but the library is version %d! It's a miracle it linked, "
                "but it will not work.\n", 
                  _major, 
                c._major));
        return true;
    }

    if(_minor != c._minor)
    {
        FWARNING(("The program is compiled against version %d.%d headers, "
                  "but the library is version %d.%d! This is not recommended "
                  "use at your own risk.\n", 
                    _major, 
                    _minor, 
                  c._major, 
                  c._minor));
    }

    if(_release != c._release)
    {
        FNOTICE(("The program is compiled against version %d.%d.%d headers, "
                 "but the library is version %d.%d.%d! This should "
                 "work fine, but if you have problems please mention it "
                 "in your report.\n", 
                   _major, 
                   _minor, 
                   _release,
                 c._major, 
                 c._minor, 
                 c._release));
    }

    if(_mt != c._mt)
    {
        FFATAL(("The program is linked against the %s-threaded runtime lib, "
                "but the library is linked against the %s-threaded one! "
                "This will lead to memory corruption, please link the "
                "%s-threaded lib (use /M%s%s instead of /M%s%s)!\n", 
                c._mt    ? "multi" : "single", 
                  _mt    ? "multi" : "single", 
                  _mt    ? "multi" : "single",
                  _mt    ? "D"     : "L", 
                  _debug ? "d"     : "",
                  _mt    ? "L"     : "D", 
                  _debug ? "d"     : ""));
        return true;
    }
    
#ifdef WIN32
    if(_debug != c._debug)
    {
        FFATAL(("The program is linked against the %sdebug runtime lib, "
                "but the library is linked against the %sdebug one! "
                "This will lead to memory corruption, please link the "
                "%sdebug lib (use /M%s%s instead of /M%s%s)!\n", 
                c._debug ? ""  : "non-", 
                  _debug ? ""  : "non-", 
                  _debug ? ""  : "non-",
                  _mt    ? "D" : "L", 
                  _debug ? "d" : "", 
                  _mt    ? "D" : "L", 
                  _debug ? "d" : ""));

        return true;
    }
#endif

    return false;
}


/*! Version string that is composed of each library's version 
    contributions
*/
static std::vector<std::string>   *osgLibraryVersions = NULL;

/*! \ingroup GrpBaseBaseInitExit
 */

OSG_BASE_DLLMAPPING 
SystemState GlobalSystemState = Startup;

/*---------------------------------------------------------------------*/
/*! \name add init functions                                           */
/*! \{                                                                 */

/*! \typedef boost::function<bool (void)> InitFuncF

    Prototype for the initialization callbacks. The system initialization and
    the points that allow customization through callbacks are as follows:

    <ol>
    <li>PreMP, this is before multithreading is initialized, callbacks can
    be added through addPreMPInitFunction.</li>
    <li>MP, this is the initialization of the multithreading subsystem, it is
    an internal call with no callbacks.</li>
    <li>PreFactories, this is before the FactoryController is initialized,
    callbacks can be added through addPreFactoryInitFunction.</li>
    <li>Factories, this initializes the FactoryController, it is an internal
    call with no callbacks.</li>
    <li>PostFactories, this is after the FactoryController is initialized,
    callbacks can be added through addPostFactoryInitFunction.</li>
    </ol>

    \ingroup GrpBaseBaseInitExit
 */


/*! Adds a callback function that is called by \c osgInit before multithreading
    is initialized.

    \param[in] initFunc Callback function to add.

    \sa InitFuncF

    \ingroup GrpBaseBaseInitExit
 */
void addPreMPInitFunction(OSG::InitFuncF initFunc)
{
    if(osgPreMPInitFunctions == NULL)
    {
        osgPreMPInitFunctions = new std::vector<InitFuncF>(0);
    }

    osgPreMPInitFunctions->push_back(initFunc);
}

/*! Adds a callback function that is called by \c osgInit after multithreading,
    but before the factories are initialized.

    \param[in] initFunc Callback function to add.

    \sa InitFuncF

    \ingroup GrpBaseBaseInitExit
 */
void addPreFactoryInitFunction(OSG::InitFuncF initFunc)
{
    if(osgPreFactoryInitFunctions == NULL)
    {
        osgPreFactoryInitFunctions = new std::vector<InitFuncF>(0);
    }

    osgPreFactoryInitFunctions->push_back(initFunc);
}

/*! Adds a callback function that is called by \c osgInit after multithreading
    and the factories are initialized.

    \param[in] initFunc Callback function to add.

    \sa InitFuncF

    \ingroup GrpBaseBaseInitExit
 */
void addPostFactoryInitFunction(OSG::InitFuncF initFunc)
{
    if(osgPostFactoryInitFunctions == NULL)
    {
        osgPostFactoryInitFunctions = new std::vector<InitFuncF>(0);
    }

    osgPostFactoryInitFunctions->push_back(initFunc);
}
 
/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name add exit function                                            */
/*! \{                                                                 */

/*! \typedef boost::function<bool (void)> ExitFuncF

    Prototype for the shutdown callbacks. The system shutdown steps and the
    points that allow customization through callbacks are as follows:

    <ol>
    <li>PreFactories, this is before the FactorController is shut down,
    callbacks can be added through addPreFactoryExitFunction.</li>
    <li>Factories, this shuts the FactoryController down, it is an internal
    call with no callbacks.</li>
    <li>PostFactories, this is after the FactoryController was shut down,
    callbacks can be added through addPostFactoryExitFunction.</li>
    <li>MP, this shuts down the multithreading subsystem, it is an internal
    call with no callbacks.</li>
    <li>PostMP, this is after multithreading was shut down, callbacks can be
    added through addPostMPExitFunction.</li>
    </ol>

    \ingroup GrpBaseBaseInitExit
 */

/*! Adds a callback function that is called by \c osgExit before the factories
    and multithreading are terminated.

    \param[in] exitFunc Callback function to add.

    \sa ExitFuncF

    \ingroup GrpBaseBaseInitExit
 */
void addPreFactoryExitFunction(OSG::ExitFuncF exitFunc)
{
    if(osgPreFactoryExitFunctions == NULL)
    {
        osgPreFactoryExitFunctions = new std::vector<ExitFuncF>(0);
    }

    osgPreFactoryExitFunctions->push_back(exitFunc);
}

/*! Adds a callback function that is called by \c osgExit after the factories,
    but before multithreading is terminated.

    \param[in] exitFunc Callback function to add.

    \sa ExitFuncF

    \ingroup GrpBaseBaseInitExit
 */
void addPostFactoryExitFunction(OSG::ExitFuncF exitFunc)
{
    if(osgPostFactoryExitFunctions == NULL)
    {
        osgPostFactoryExitFunctions = new std::vector<ExitFuncF>(0);
    }

    osgPostFactoryExitFunctions->push_back(exitFunc);
}


/*! Adds a callback function that is called by \c osgExit after the factories,
    and just before multithreading are terminated.

    \param[in] exitFunc Callback function to add.

    \sa ExitFuncF

    \ingroup GrpBaseBaseInitExit
 */
void addPreMPExitFunction(OSG::ExitFuncF exitFunc)
{
    if(osgPreMPExitFunctions == NULL)
    {
        osgPreMPExitFunctions = new std::vector<ExitFuncF>(0);
    }

    osgPreMPExitFunctions->push_back(exitFunc);
}

/*! Adds a callback function that is called by \c osgExit after the factories,
    and multithreading are terminated.

    \param[in] exitFunc Callback function to add.

    \sa ExitFuncF

    \ingroup GrpBaseBaseInitExit
 */
void addPostMPExitFunction(OSG::ExitFuncF exitFunc)
{
    if(osgPostMPExitFunctions == NULL)
    {
        osgPostMPExitFunctions = new std::vector<ExitFuncF>(0);
    }

    osgPostMPExitFunctions->push_back(exitFunc);
}

/*! \}                                                                 */

/*! Adds the name of a shared object to the list of objects that are dynamically
    loaded by \c osgInit.

    \param[in] szName Name of shared object.

    \ingroup GrpBaseBaseInitExit
 */
void preloadSharedObject(const OSG::TChar *szName)
{
    if(osgPreloadSharedObject == NULL)
    {
        osgPreloadSharedObject = new std::vector<tstring>;
    }

    tstring tmpString(szName);

    osgPreloadSharedObject->push_back(tmpString);
}





/*! Add a string to the version output. 
    Mainly used by the libraries to publicise the svn revision they were
    built from.
*/
OSG_BASE_DLLMAPPING
void addLibraryVersion(const OSG::Char8 *szName)
{
    if(osgLibraryVersions == NULL)
        osgLibraryVersions = new std::vector<std::string>;

    osgLibraryVersions->push_back(szName);
}


/*! Shuts down the system and performs shutdown tasks registered with
    \c addPreFactoryExitFunction, \c addPostFactoryExitFunction and
    \c addPostMPExitFunction. The returnvalue indicates if the shutdown was
    successfull (\c true ) or failed (\c false ).

    \return \c true on successfull shutdown, \c false otherwise.

    \ingroup GrpBaseBaseInitExit
 */
bool osgExit(void)
{
    bool returnValue = true;

    if(GlobalSystemState != Running)
    {
         return true;
    }

    GlobalSystemState = Shutdown;

    delete osgPreMPInitFunctions;
    delete osgPreFactoryInitFunctions;
    delete osgPostFactoryInitFunctions;

    if(osgPreFactoryExitFunctions != NULL)
    {
        for(Int32 i = osgPreFactoryExitFunctions->size() - 1; i >= 0; i--)
        {
            returnValue &= (*osgPreFactoryExitFunctions)[i]();

            if(returnValue == false)
                break;
        }
    }

    delete osgPreFactoryExitFunctions;

    if(returnValue == false)
        return returnValue;

    returnValue &= FactoryController::the()->terminate();

    if(returnValue == false)
        return returnValue;

    if(osgPostFactoryExitFunctions != NULL)
    {
        for(Int32 i = osgPostFactoryExitFunctions->size() - 1; i >= 0; i--)
        {
            returnValue &= (*osgPostFactoryExitFunctions)[i]();

            if(returnValue == false)
                break;
        }
    }

    delete osgPostFactoryExitFunctions;

    if(returnValue == false)
        return returnValue;

    if(osgPreMPExitFunctions != NULL)
    {
        for(Int32 i = osgPreMPExitFunctions->size() - 1; i >= 0; i--)
        {
            returnValue &= (*osgPreMPExitFunctions)[i]();

            if(returnValue == false)
                break;
        }
    }

    delete osgPreMPExitFunctions;

    if(returnValue == false)
        return returnValue;

    returnValue &= ThreadManager::terminate();

    if(returnValue == false)
        return returnValue;

    if(osgPostMPExitFunctions != NULL)
    {
        for(Int32 i = osgPostMPExitFunctions->size() - 1; i >= 0; i--)
        {
            returnValue &= (*osgPostMPExitFunctions)[i]();

            if(returnValue == false)
                break;
        }
    }

    delete osgPostMPExitFunctions;
    delete osgPreloadSharedObject;

    SharedObjectHandler::the()->terminate();

    Log::terminate();

    delete osgLibraryVersions;

    GlobalSystemState = PostShutdown;

    return returnValue;
}

/*---------------------------------------------------------------------*/
/*! \name internal                                                     */
/*! \{                                                                 */

/*! Initializes the system and performs startup tasks registered with
    \c addPreMPInitFunction, \c addPreFactoryInitFunction and 
    \c addPostFactoryInitFunction functions. The arguments can be used to
    pass command line arguments to the library, but this is currently unused.

    Part of the behavior of \c osgInit can be controlled through environment
    variables, these are:

    <dl>
    <dt>OSG_LOAD_LIBS</dt>
    <dd>A list of shared object names (separated by the platform path
        delimiter) that will be loaded during \c osgInit. </dd>
    <dt>OSG_PLUGIN_PATH</dt>
    <dd>A directory name. From this directory plugins that match the 
        OSG_PLUGIN_PATTERN will be loaded. This avoids writing out the names of
        all plugins and putting them in OSG_LOAD_LIBS, which would result in
        the same behavior. </dd>
    <dt>OSG_PLUGIN_PATTERN</dt>
    <dd>A regular expression against which all files in the directory
        specified with OSG_PLUGIN_PATH are tested, those that match are
        loaded dynamically as shared objects.</dd> 
    </dl>
    \internal
    \ingroup GrpBaseBaseInitExit
 */

bool osgDoInit(OSG::Int32, 
               OSG::Char8 **,
               OSG::UInt16   major,
               OSG::UInt16   minor,
               OSG::UInt16   release,
               bool          debug,
               bool          dll,
               bool          mt)
{
    CompileConfig prog(major, 
                       minor, 
                       release, 
                       debug, 
                       dll, 
                       mt);

    CompileConfig lib (OSG_MAJOR_VERSION, 
                       OSG_MINOR_VERSION, 
                       OSG_RELEASE_VERSION,
                       OSG_INIT_DEBUG,
                       OSG_INIT_DLL,
                       OSG_INIT_MT);
    
    if(lib.compare(prog))
    {
        exit(1);
    }

#ifdef WIN32 
    // Very crude way to safeguard on low level cast, have to find a better
    // way later.
    OSG_ASSERT(sizeof(UInt32) == sizeof(long));
#endif

    bool returnValue = true;
    
    if(GlobalSystemState != Startup)
    {
        FFATAL(("osgInit: System was already initialized; repeated calls are "
                "NOT allowed.\n"));
                
        returnValue = false;
    }

    if(returnValue == false)
        return returnValue;

    returnValue = SharedObjectHandler::the()->initialize();

    if(osgPreloadSharedObject != NULL)
    {
        for(UInt32 i = 0; i < osgPreloadSharedObject->size(); ++i)
        {
            SharedObjectHandler::the()->getOSGSharedObject(
                (*osgPreloadSharedObject)[i].c_str());
        }
    }

#ifdef WIN32
    std::string pathSep(";");
#else
    std::string pathSep(":");
#endif

    char *szEnvLibs = getenv("OSG_LOAD_LIBS");

    if(szEnvLibs != NULL)
    {
        std::string tmpString(szEnvLibs);
        string_token_iterator libIt(tmpString, pathSep.c_str());

        string_token_iterator libEnd;

        while(libIt != libEnd)
        {
            SharedObjectHandler::the()->getOSGSharedObject(
                (*libIt).c_str());

            ++libIt;
        }
    }

    const char *szEnvPlugins       = getenv("OSG_PLUGIN_PATH");
    const char *szEnvPluginPattern = getenv("OSG_PLUGIN_PATTERN");

    //SharedObjectHandler::the()->dump();

    if(szEnvPlugins != NULL)
    {
        if(szEnvPluginPattern == NULL)
        {
            szEnvPluginPattern = PluginPattern;
        }

        fprintf(stderr, "Get Plugins %s from %s\n", 
                szEnvPluginPattern,
                szEnvPlugins);

        std::vector<Char8 *> *pPlugins = 
            Directory::getEntries(szEnvPlugins, szEnvPluginPattern);

        if(pPlugins != NULL)
        {
            std::string szPluginName;

            for(UInt32 i = 0; i < pPlugins->size(); ++i)
            {
                if((*pPlugins)[i][0] == '.')
                {
                    if((*pPlugins)[i][1] == '\0')
                    {
                        continue;
                    }
                    else if((*pPlugins)[i][1] == '.' &&
                            (*pPlugins)[i][2] == '\0')
                    {
                        continue;
                    }
                }

                szPluginName.assign(szEnvPlugins);
                szPluginName += '/';
                szPluginName += (*pPlugins)[i];

                fprintf(stderr, "plugin : %s\n", szPluginName.c_str());

                SharedObjectHandler::the()->getSharedObject(
                    szPluginName.c_str());
            }
        }

        delete pPlugins;
    }

    FNOTICE(("osgInit: Main Version:        %s\n", OSG_VERSION_STRING));
    for(UInt16 i = 0; i < osgLibraryVersions->size(); ++i)
    {
        FNOTICE(("osgInit: %s\n", (*osgLibraryVersions)[i].c_str()));
    }
    
    //SharedObjectHandler::the()->dump();

    if(returnValue == false)
        return returnValue;

    // without it floats could be written as "1,456" ...
    setlocale(LC_NUMERIC, "English");

    if(osgPreMPInitFunctions != NULL)
    {
        for(UInt32 i = 0; i < osgPreMPInitFunctions->size(); i++)
        {
            returnValue &= (*osgPreMPInitFunctions)[i]();

            if(returnValue == false)
                break;
        }

        osgPreMPInitFunctions->clear();
    }

    if(returnValue == false)
        return returnValue;

    returnValue &= ThreadManager::initialize();

    if(returnValue == false)
        return returnValue;

    if(osgPreFactoryInitFunctions != NULL)
    {
        for(UInt32 i = 0; i < osgPreFactoryInitFunctions->size(); i++)
        {
            returnValue &= (*osgPreFactoryInitFunctions)[i]();

            if(returnValue == false)
                break;
        }

        osgPreFactoryInitFunctions->clear();
    }

    if(returnValue == false)
        return returnValue;

    returnValue &= FactoryController::the()->initialize();

    if(returnValue == false)
        return returnValue;

    if(osgPostFactoryInitFunctions != NULL)
    {
        for(UInt32 i = 0; i < osgPostFactoryInitFunctions->size(); i++)
        {
            returnValue &= (*osgPostFactoryInitFunctions)[i]();

            if(returnValue == false)
                break;
        }

        osgPostFactoryInitFunctions->clear();
    }

    GlobalSystemState = Running;

    osgLog().setLogLevel(OSG_DEFAULT_LOG_LEVEL);

    return returnValue;
}

/*! wraps osgExit for atexit registration

    \ingroup GrpBaseBaseInitExit
    \internal
 */
void osgExitWrapper(void)
{
    osgExit();
}

/*! \}                                                                 */


/*! \class InitFuncWrapper

    \brief Registers an init function during instance creation

    InitFuncWrapper is a little wrapper class that allows calling an init 
    function without an associated class.
*/

/*! The constructor has the important side effect of adding \a func to the list
    of init functions by calling addPostFactoryInitFunction.

    \param[in] func Init function to be added.
 */
InitFuncWrapper::InitFuncWrapper(const InitFuncF func)
{
    addPostFactoryInitFunction(func);
}

/*! \class StaticInitFuncWrapper

    \brief Calls an init function during instance creation.

    StaticInitFuncWrapper is a little wrapper class that allows calling a 
    static init function without an associated class.
 */

/*! The constructor has the important side effect of calling \a func, thus
    executing it during C++ static init by creating a static member of type
    StaticInitFuncWrapper.

    \param[in] func Init function to be called during static init.
 */

StaticInitFuncWrapper::StaticInitFuncWrapper(const InitFuncF func)
{
    func();
}

OSG_END_NAMESPACE
