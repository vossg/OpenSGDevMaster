/*---------------------------------------------------------------------------*\
 *                        OpenSG openNURBS SceneFileType                     *
 *                                                                           *
 *                                                                           *
 * Copyright (C) 2007-2008 by Seac02 S.r.l.     http://www.seac02.it         *
 * Copyright (C) 2008  by Patrik Mueller    muellerptr@users.sourceforge.net *
 * Copyright (C) 2008  by Akos Balazs       edhellon@cs.uni-bonn.de          *
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

#if __GNUC__ >= 4 || __GNUC_MINOR__ >=3
#pragma GCC diagnostic warning "-Wold-style-cast"
#pragma GCC diagnostic warning "-Wignored-qualifiers"
#endif

#include <stdlib.h>
#include <stdio.h>

#include <OSGConfig.h>

#include <iostream>
#include <fstream>

#include <OSGLog.h>

#include "OSGSceneFileHandler.h"
#include "OSGRhinoSceneFileType.h"

#include "OSGrhino2osb.h"

OSG_BEGIN_NAMESPACE

#if defined(OSG_WIN32_ICL) && !defined(OSG_CHECK_FIELDSETARG)
#pragma warning (disable : 383)
#endif


/*! \class OSG::RhinoSceneFileType
    \ingroup GrpSystemFileIO

 */

/*****************************
 *   Types
 *****************************/
// Static Class Varible implementations:

const Char8 *RhinoSceneFileType::_suffixA[] = { "3dm" };

RhinoSceneFileType RhinoSceneFileType::_the(_suffixA, 
                                             sizeof(_suffixA),
                                             false,    
                                             10,
                                             SceneFileType::OSG_READ_SUPPORTED);

NodeTransitPtr RhinoSceneFileType::read3DM(const Char8 *fileName) const
{
    bool  bImportRenderMeshes      = false;
    int   iCurveInterpolationSteps = 100;
    float fTessellationError       = 0.1f;
    bool  bDoTessellation          = true;

    IOFileTypeBase::getOptionAs<Int32 >(this->getOptions(), 
                                        "curveInterpolationSteps", 
                                        iCurveInterpolationSteps);

    IOFileTypeBase::getOptionAs<Real32>(this->getOptions(), 
                                        "tesselationError", 
                                        fTessellationError      );

    IOFileTypeBase::getOptionAs<bool>  (this->getOptions(), 
                                        "doTessellation", 
                                        bDoTessellation         );

    IOFileTypeBase::getOptionAs<bool>  (this->getOptions(), 
                                        "importRenderMeshes", 
                                        bImportRenderMeshes     );

    if(iCurveInterpolationSteps <= 0)
    {
        iCurveInterpolationSteps = 100;
    }    

    if(fTessellationError <= 0.f)
    {
        fTessellationError = 0.1f;
    }

    rhino2osb ro(iCurveInterpolationSteps, 
                 fTessellationError, 
                 bDoTessellation,
                 bImportRenderMeshes     ); 

    NodeTransitPtr root = ro.load(fileName);

    return root;
}

             
NodeTransitPtr RhinoSceneFileType::read(
          std::istream &, 
    const Char8        *fileNameOrExtension,
          Resolver      resolver           ) const
{
    return read3DM(fileNameOrExtension);
}

RhinoSceneFileType::RhinoSceneFileType(const Char8  *suffixArray[],
                                             UInt16  suffixByteCount,
                                             bool    override,
                                             UInt32  overridePriority,
                                             UInt32  flags) :
    SceneFileType(suffixArray,
                  suffixByteCount,
                  override,
                  overridePriority,
                  flags           )
{
}

RhinoSceneFileType &RhinoSceneFileType::the(void)
{
    return _the;
}

const Char8 *RhinoSceneFileType::getName(void) const
{
    return "Rhinoceros3D";
}

RhinoSceneFileType::~RhinoSceneFileType (void )
{
}

OSG_END_NAMESPACE
