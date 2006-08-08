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

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <string.h>


#include <vector>

#include "OSGBaseInitFunctions.h"

#ifndef OSG_WINCE
#include "OSGThreadManager.h"
#else
#include "OSGLog.h"
#endif

#include "OSGFactoryController.h"
#include "OSGSharedObjectHandler.h"
#include "OSGFileSystem.h"

#include <locale.h>

OSG_BEGIN_NAMESPACE

static void osgExitWrapper(void);

static std::vector<InitFuncF>    *osgPreMPInitFunctions       = NULL;
static std::vector<InitFuncF>    *osgPreFactoryInitFunctions  = NULL;
static std::vector<InitFuncF>    *osgPostFactoryInitFunctions = NULL;

static std::vector<ExitFuncF>    *osgPreFactoryExitFunctions  = NULL;
static std::vector<ExitFuncF>    *osgPostFactoryExitFunctions = NULL;
static std::vector<ExitFuncF>    *osgPostMPExitFunctions      = NULL;

static std::vector<tstring  >    *osgPreloadSharedObject      = NULL;

/*! \ingroup GrpBaseBaseInitExit
 */

OSG_BASE_DLLMAPPING 
SystemState GlobalSystemState = Startup;

/*---------------------------------------------------------------------*/
/*! \name add init functions                                           */
/*! \{                                                                 */

/*! addPreMPInitFunction, function called by osgInit before the
    multithreading is initialized 
    \ingroup GrpBaseBaseInitExit
 */

void addPreMPInitFunction(InitFuncF initFunc)
{
    if(osgPreMPInitFunctions == NULL)
    {
        osgPreMPInitFunctions = new std::vector<InitFuncF>(0);
    }

    osgPreMPInitFunctions->push_back(initFunc);
}

/*! addPreFactoryInitFunction, function called by osgInit after the
    multithreading is and before the factories are initialized.
    \ingroup GrpBaseBaseInitExit
 */

void addPreFactoryInitFunction(InitFuncF initFunc)
{
    if(osgPreFactoryInitFunctions == NULL)
    {
        osgPreFactoryInitFunctions = new std::vector<InitFuncF>(0);
    }

    osgPreFactoryInitFunctions->push_back(initFunc);
}

/*! addPostFactoryInitFunction, function called by osgInit after the
    the factories are initialized.
    \ingroup GrpBaseBaseInitExit
 */

void addPostFactoryInitFunction(InitFuncF initFunc)
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

/*! addPreFactoryExitFunction, function called by osgExit before
    the factories are termininated
   \ingroup GrpBaseBaseInitExit
 */

void addPreFactoryExitFunction(ExitFuncF exitFunc)
{
    if(osgPreFactoryExitFunctions == NULL)
    {
        osgPreFactoryExitFunctions = new std::vector<ExitFuncF>(0);
    }
    
    osgPreFactoryExitFunctions->push_back(exitFunc);
}

/*! addPostFactoryExitFunction, function called by osgExit after
    the factories are and before the multithreading is termininated
   \ingroup GrpBaseBaseInitExit
 */

void addPostFactoryExitFunction(ExitFuncF exitFunc)
{
    if(osgPostFactoryExitFunctions == NULL)
    {
        osgPostFactoryExitFunctions = new std::vector<ExitFuncF>(0);
    }
    
    osgPostFactoryExitFunctions->push_back(exitFunc);
}


/*! addPostExitFunction, function called by osgExit after the
    multithreading is termininated
   \ingroup GrpBaseBaseInitExit
 */

void addPostMPExitFunction(ExitFuncF exitFunc)
{
    if(osgPostMPExitFunctions == NULL)
    {
        osgPostMPExitFunctions = new std::vector<ExitFuncF>(0);
    }
    
    osgPostMPExitFunctions->push_back(exitFunc);
}

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name init / exit                                                  */
/*! \{                                                                 */

/*! \ingroup GrpBaseBaseInitExit
 */

void preloadSharedObject(const TChar *szName)
{
    if(osgPreloadSharedObject == NULL)
    {
        osgPreloadSharedObject = new std::vector<tstring>;
    }

    tstring tmpString(szName);

    osgPreloadSharedObject->push_back(tmpString);
}

/*! \ingroup GrpBaseBaseInitExit
 */

bool osgInit(Int32, Char8 **)
{
    bool returnValue = true;

    returnValue = SharedObjectHandler::the()->initialize();

    if(osgPreloadSharedObject != NULL)
    {
        for(UInt32 i = 0; i < osgPreloadSharedObject->size(); ++i)
        {
            SharedObjectHandler::the()->getOSGSharedObject(
                (*osgPreloadSharedObject)[i].c_str());
        }
    }

#ifndef OSG_WINCE
    char *szEnvLibs = getenv("OSG_LOAD_LIBS");

    if(szEnvLibs != NULL)
    {
        std::string tmpString(szEnvLibs);
        string_token_iterator libIt(tmpString, ":");

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

    SharedObjectHandler::the()->dump();

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
#endif

    SharedObjectHandler::the()->dump();

    if(returnValue == false)
        return returnValue;

    // without it floats could be written as "1,456" ...
#ifndef OSG_WINCE
    setlocale(LC_NUMERIC, "English");
#endif
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

#ifndef OSG_WINCE
    returnValue &= ThreadManager::initialize();

    if(returnValue == false)
        return returnValue;
#endif

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

    atexit(osgExitWrapper);

    return returnValue;
}

static void osgExitWrapper(void)
{
    osgExit();
}

/*! \ingroup GrpBaseBaseInitExit
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

#ifndef OSG_WINCE
    returnValue &= ThreadManager::terminate();

    if(returnValue == false)
        return returnValue;
#endif

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

    return returnValue;
}

/*! \}                                                                 */

OSG_END_NAMESPACE


OSG_USING_NAMESPACE


InitFuncWrapper::InitFuncWrapper(const InitFuncF func)
{
    addPostFactoryInitFunction(func);
}


 
StaticInitFuncWrapper::StaticInitFuncWrapper(const InitFuncF func)
{
    func();
}


/*-------------------------------------------------------------------------*/
/*                              cvs id's                                   */

#ifdef __sgi
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp[] = "@(#)$Id: $";
    static Char8 cvsid_hpp[] = OSGBASEINITFUNCTIONS_HEADER_CVSID;
}
