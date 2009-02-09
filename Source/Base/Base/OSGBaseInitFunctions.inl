/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                Copyright (C) 2008 by the OpenSG Forum                     *
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

OSG_BEGIN_NAMESPACE

// Windows maintains an atexit stack for each DLL, which is run when that DLL
// is unloaded. We need to do the cleanup before any DLL is unloaded, i.e.
// we need to register osgExitWrapper on the application atexit stack.
// Inlining this part of osgInit ensures that.


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

    \ingroup GrpBaseBaseInitExit
 */

inline
bool osgInit  (OSG::Int32    argc,  OSG::Char8  **argv,
               OSG::UInt16   major, OSG::UInt16   minor, OSG::UInt16 release,
               bool          debug, bool          dll,   bool        mt      )
{
    bool returnValue = osgDoInit(argc,  argv,
                                 major, minor, release,
                                 debug, dll,   mt      );

    atexit(osgExitWrapper);

    return returnValue;
}


OSG_END_NAMESPACE
