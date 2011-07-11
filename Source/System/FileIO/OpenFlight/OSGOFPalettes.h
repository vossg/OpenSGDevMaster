/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                Copyright (C) 2011 by the OpenSG Forum                     *
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

#ifndef _OSGOFPALETTES_H_
#define _OSGOFPALETTES_H_

#include "OSGFileIODef.h"
#include "OSGMemoryObject.h"
#include "OSGRefCountPtr.h"

#include <map>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward declarations
//---------------------------------------------------------------------------

/*! \ingroup GrpFileIOOpenFlight
 */
class OFVertexPaletteRecord;
/*! \ingroup GrpFileIOOpenFlight
 */
typedef RefCountPtr<OFVertexPaletteRecord,
                    MemObjRefCountPolicy   >  OFVertexPaletteRecordRCPtr;

/*! \ingroup GrpFileIOOpenFlight
 */
class OFTexturePaletteRecord;
/*! \ingroup GrpFileIOOpenFlight
 */
typedef RefCountPtr<OFTexturePaletteRecord,
                    MemObjRefCountPolicy   >  OFTexturePaletteRecordRCPtr;

/*! \ingroup GrpFileIOOpenFlight
 */
class OFMaterialPaletteRecord;
/*! \ingroup GrpFileIOOpenFlight
 */
typedef RefCountPtr<OFMaterialPaletteRecord,
                    MemObjRefCountPolicy   >  OFMaterialPaletteRecordRCPtr;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpFileIOOpenFlight
    \nohierarchy
 */

class OSG_FILEIO_DLLMAPPING OFVertexPalette : public MemoryObject
{
  protected:

    typedef MemoryObject Inherited;

    /*---------------------------------------------------------------------*/

    OFVertexPaletteRecordRCPtr _pVertexPalette;

    /*---------------------------------------------------------------------*/

    virtual ~OFVertexPalette(void);

  public:

    OFVertexPalette(void);

    /*---------------------------------------------------------------------*/

          void                   addRecord(OFVertexPaletteRecord *pVertexPal);
    const OFVertexPaletteRecord *getRecord(void                             );

    /*---------------------------------------------------------------------*/

    void dump(UInt32 uiIndent);
};

/*! \ingroup GrpFileIOOpenFlight
 */
typedef RefCountPtr<OFVertexPalette,
                    MemObjRefCountPolicy> OFVertexPaletteRCPtr;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpFileIOOpenFlight
    \nohierarchy
 */

class OSG_FILEIO_DLLMAPPING OFTexturePalette : public MemoryObject
{
  protected:

    typedef MemoryObject Inherited;

    /*---------------------------------------------------------------------*/

    typedef std::map<Int32,
                     OFTexturePaletteRecordRCPtr>           TextureStore;
    typedef std::map<Int32,
                     OFTexturePaletteRecordRCPtr>::iterator TextureStoreIt;

    /*---------------------------------------------------------------------*/

    TextureStore _mTextures;

    /*---------------------------------------------------------------------*/

    virtual ~OFTexturePalette(void);

  public:

    OFTexturePalette(void);

    /*---------------------------------------------------------------------*/

          void                    addRecord(OFTexturePaletteRecord *pTex);
    const OFTexturePaletteRecord *getRecord(Int32                   uiId);

    /*---------------------------------------------------------------------*/

    void dump(UInt32 uiIndent);
};

/*! \ingroup GrpFileIOOpenFlight
 */
typedef RefCountPtr<OFTexturePalette,
                    MemObjRefCountPolicy> OFTexturePaletteRCPtr;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpFileIOOpenFlight
    \nohierarchy
 */

class OSG_FILEIO_DLLMAPPING OFMaterialPalette : public MemoryObject
{
  protected:
    typedef MemoryObject Inherited;

    /*---------------------------------------------------------------------*/

    typedef std::map<Int32,
                     OFMaterialPaletteRecordRCPtr>           MaterialStore;
    typedef std::map<Int32,
                     OFMaterialPaletteRecordRCPtr>::iterator MaterialStoreIt;

    /*---------------------------------------------------------------------*/

    MaterialStore _mMaterials;

    /*---------------------------------------------------------------------*/

    virtual ~OFMaterialPalette(void);

  public:

    typedef RefCountPtr<OFMaterialPalette,
                        MemObjRefCountPolicy> ObjRCPtr;
    typedef TransitPtr <OFMaterialPalette   > ObjTransitPtr;

    OFMaterialPalette(void);

    /*---------------------------------------------------------------------*/

          void                     addRecord(OFMaterialPaletteRecord *pMat);
    const OFMaterialPaletteRecord *getRecord(Int32                    uiId);

    /*---------------------------------------------------------------------*/

    void dump(UInt32 uiIndent);
};

/*! \ingroup GrpFileIOOpenFlight
 */
typedef OFMaterialPalette::ObjRCPtr      OFMaterialPaletteRCPtr;
/*! \ingroup GrpFileIOOpenFlight
 */
typedef OFMaterialPalette::ObjTransitPtr OFMaterialPaletteTransitPtr;

OSG_END_NAMESPACE

#endif /* _OSGOFPALETTES_H_ */
