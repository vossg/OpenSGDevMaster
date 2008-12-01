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

inline
bool osgInit  (Int32    argc,  Char8  **argv,
               UInt16   major, UInt16   minor, UInt16 release,
               bool     debug, bool     dll,   bool   mt      )
{
    bool returnValue = osgDoInit(argc,  argv,
                                 major, minor, release,
                                 debug, dll,   mt      );

    atexit(osgExitWrapper);

    return returnValue;
}

OSG_END_NAMESPACE
