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
#include "OSGOFAncillaryRecords.h"

#include <map>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpFileIOOpenFlight
    \nohierarchy
 */

class OSG_FILEIO_DLLMAPPING OFColorPalette : public MemoryObject
{
  protected:

    typedef MemoryObject Inherited;

    /*---------------------------------------------------------------------*/

    OFColorPaletteRecordRCPtr _pColorPalette;

    /*---------------------------------------------------------------------*/

    virtual ~OFColorPalette(void);

  public:

    OFColorPalette(void);

    /*---------------------------------------------------------------------*/

          void                  addRecord(OFColorPaletteRecord *pColorPal);
    const OFColorPaletteRecord *getRecord(void                           );

    /*---------------------------------------------------------------------*/

    void dump(UInt32 uiIndent) const;
};

/*! \ingroup GrpFileIOOpenFlight
 */
typedef RefCountPtr<OFColorPalette,
                    MemObjRefCountPolicy> OFColorPaletteRCPtr;

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

    void dump(UInt32 uiIndent) const;
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
                     OFTexturePaletteRecordRCPtr> TextureStore;
    typedef TextureStore::iterator                TextureStoreIt;
    typedef TextureStore::const_iterator          TextureStoreConstIt;


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

    void dump(UInt32 uiIndent) const;
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
                     OFMaterialPaletteRecordRCPtr>  MaterialStore;
    typedef MaterialStore::iterator                 MaterialStoreIt;
    typedef MaterialStore::const_iterator           MaterialStoreConstIt;

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

    void dump(UInt32 uiIndent) const;
};

/*! \ingroup GrpFileIOOpenFlight
 */
typedef OFMaterialPalette::ObjRCPtr      OFMaterialPaletteRCPtr;
/*! \ingroup GrpFileIOOpenFlight
 */
typedef OFMaterialPalette::ObjTransitPtr OFMaterialPaletteTransitPtr;

OSG_END_NAMESPACE

#endif /* _OSGOFPALETTES_H_ */
