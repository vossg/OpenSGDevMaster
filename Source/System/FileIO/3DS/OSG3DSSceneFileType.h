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

#ifndef _OSG3DSSCENEFILETYPE_H_
#define _OSG3DSSCENEFILETYPE_H_
#ifdef  __sgi
#pragma  once
#endif

#include "OSGFileIODef.h"
#include "OSGAction.h"
#include "OSGBaseTypes.h"
#include "OSGGeoPositionsFields.h"
#include "OSGGeometry.h"
#include "OSGNode.h"
#include "OSGSceneFileType.h"
#include "OSGMaterial.h"

#include "OSG3DSLoader.h"

OSG_BEGIN_NAMESPACE

/*! \brief 3DS SceneFileType
    \ingroup GrpFileIO3DS
    \ingroup GrpLibOSGFileIO
 */

class OSG_FILEIO_DLLMAPPING A3DSSceneFileType : public SceneFileType
{

  public:

    static A3DSSceneFileType &the(void);

    virtual ~A3DSSceneFileType(void);

    virtual const Char8 *getName(void) const;

    virtual NodeTransitPtr read(      std::istream &is, 
                                const Char8        *fileNameOrExtension,
                                      Resolver      resolver  = NULL   ) const;

  protected:

    static const Char8            *_suffixA[];
    static       A3DSSceneFileType  _the;

    A3DSSceneFileType(const Char8  *suffixArray[],
                            UInt16  suffixByteCount,
                            bool    override,
                            UInt32  overridePriority,
                            UInt32  flags);

    A3DSSceneFileType(const A3DSSceneFileType &obj);

  private:

    NodeTransitPtr     createMesh    (L3DS &scene, LMesh  &mesh) const;
    MaterialTransitPtr createMaterial(L3DS &scene, UInt32  id  ) const;

    mutable std::map<UInt32, MaterialUnrecPtr> _materials;
    typedef std::map<UInt32, MaterialUnrecPtr>::iterator materialIt;
};

typedef A3DSSceneFileType* A3DSSceneFileTypeP;

OSG_END_NAMESPACE

#endif // _OSG3DSSCENEFILETYPE_H_
