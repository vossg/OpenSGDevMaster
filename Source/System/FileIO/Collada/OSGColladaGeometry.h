/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                Copyright (C) 2009 by the OpenSG Forum                     *
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

#ifndef _OSGCOLLADAGEOMETRY_H_
#define _OSGCOLLADAGEOMETRY_H_

#include "OSGConfig.h"

#if defined(OSG_WITH_COLLADA) || defined(OSG_DO_DOC)

#include "OSGColladaInstantiableElement.h"
#include "OSGColladaElementFactoryHelper.h"
#include "OSGColladaInstanceMaterial.h"
#include "OSGColladaInstInfo.h"
#include "OSGColladaSource.h"
#include "OSGNode.h"
#include "OSGGeometry.h"
#include "OSGGeoVectorProperty.h"
#include "OSGGeoIntegralProperty.h"

#include <dae/daeDomTypes.h>
#include <dom/domInputLocal.h>
#include <dom/domInputLocalOffset.h>
#include <dom/domSource.h>

// forward decls
class domMesh;
class domLines;
class domLinestrips;
class domPolygons;
class domPolylist;
class domTriangles;
class domTrifans;
class domTristrips;


OSG_BEGIN_NAMESPACE

// forward decls
class ColladaInstanceGeometry;
OSG_GEN_MEMOBJPTR(ColladaInstanceGeometry);

class ColladaNode;

/*! \ingroup GrpFileIOCollada
    \nohierarchy
 */

class OSG_FILEIO_DLLMAPPING ColladaGeometry : public ColladaInstantiableElement
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
    /*! \{                                                                 */

    typedef ColladaInstantiableElement Inherited;
    typedef ColladaGeometry            Self;

    OSG_GEN_INTERNAL_MEMOBJPTR(ColladaGeometry);

    typedef ColladaInstanceMaterial::BindInfo        BindInfo;
    typedef ColladaInstanceMaterial::BindStore       BindStore;

    typedef ColladaInstanceMaterial::BindVertexInfo  BindVertexInfo;
    typedef ColladaInstanceMaterial::BindVertexStore BindVertexStore;

    class ColladaGeometryInstInfo : public ColladaInstInfo
    {
        /*==========================  PUBLIC  =============================*/
      public:
        /*-----------------------------------------------------------------*/
        /*! \name Types                                                    */
        /*! \{                                                             */

        typedef ColladaInstInfo          Inherited;
        typedef ColladaGeometryInstInfo  Self;

        OSG_GEN_INTERNAL_MEMOBJPTR(ColladaGeometryInstInfo);

        /*! \}                                                             */
        /*-----------------------------------------------------------------*/
        /*! \name Create                                                   */
        /*! \{                                                             */

        static  ColladaInstInfoTransitPtr
            create(ColladaNode             *colInstParent,
                   ColladaInstanceGeometry *colInst,
                   Node                    *parentN       );

        /*! \}                                                             */
        /*-----------------------------------------------------------------*/
        /*! \name Access                                                   */
        /*! \{                                                             */

        inline Node *getParentNode(void) const;

        /*! \}                                                             */
        /*-----------------------------------------------------------------*/
        /*! \name Process                                                  */
        /*! \{                                                             */

        virtual void process(void);

        /*! \}                                                             */
        /*=========================  PROTECTED  ===========================*/
      protected:
        /*-----------------------------------------------------------------*/
        /*! \name Constructors/Destructor                                  */
        /*! \{                                                             */

                 ColladaGeometryInstInfo(
                     ColladaNode             *colInstParent,
                     ColladaInstanceGeometry *colInst,
                     Node                    *parentN       );
        virtual ~ColladaGeometryInstInfo(void               );

        /*! \}                                                             */
        /*-----------------------------------------------------------------*/

        NodeUnrecPtr _parentN;
    };

    OSG_GEN_MEMOBJPTR(ColladaGeometryInstInfo);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Create                                                       */
    /*! \{                                                                 */

    static ColladaElementTransitPtr
        create(daeElement *elem, ColladaGlobal *global);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Reading                                                      */
    /*! \{                                                                 */

    virtual void  read          (ColladaElement  *colElemParent);
    virtual Node *createInstance(ColladaInstInfo *colInstInfo  );

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:
    /*---------------------------------------------------------------------*/
    /*! \name Constructors/Destructor                                      */
    /*! \{                                                                 */

             ColladaGeometry(daeElement *elem, ColladaGlobal *global);
    virtual ~ColladaGeometry(void                                   );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Internal Types                                               */
    /*! \{                                                                 */

    // <source> map
    typedef std::map<std::string, ColladaSourceRefPtr> SourceMap;
    typedef SourceMap::iterator                        SourceMapIt;
    typedef SourceMap::const_iterator                  SourceMapConstIt;

    /*! \nohierarchy
     */
    struct PropInfo
    {
        PropInfo(void                  );
        PropInfo(const PropInfo &source);

        std::string               _semantic;
        Int32                     _set;

        GeoVectorPropertyUnrecPtr _prop;
    };

    typedef std::vector<PropInfo                   > PropStore;
    typedef PropStore::iterator                      PropStoreIt;
    typedef PropStore::const_iterator                PropStoreConstIt;
 
    typedef std::vector<GeoIntegralPropertyUnrecPtr> IndexStore;
    typedef IndexStore::iterator                     IndexStoreIt;
    typedef IndexStore::const_iterator               IndexStoreConstIt;

    // map <instance_material> target attribute to an index into
    // the instance store (getInstStore())
    typedef std::map<std::string, UInt32>            InstanceMap;
    typedef InstanceMap::iterator                    InstanceMapIt;
    typedef InstanceMap::const_iterator              InstanceMapConstIt;

    /*! \nohierarchy
     */
    struct GeoInfo
    {
        std::string                 _matSymbol;

        PropStore                   _propStore;
        IndexStore                  _indexStore;

        GeoIntegralPropertyUnrecPtr _lengths;
        GeoIntegralPropertyUnrecPtr _types;

        InstanceMap                 _instMap;
    };

    typedef std::vector<GeoInfo                    > GeoStore;
    typedef GeoStore::iterator                       GeoStoreIt;
    typedef GeoStore::const_iterator                 GeoStoreConstIt;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Helper Functions                                             */
    /*! \{                                                                 */

    void readMesh   (      domMesh         *mesh   );
    void readSources(const domSource_Array &sources);

    void readLines     (domMesh *mesh, domLines      *lines     );
    void readLineStrips(domMesh *mesh, domLinestrips *lineStrips);
    void readPolygons  (domMesh *mesh, domPolygons   *polygons  );
    void readPolyList  (domMesh *mesh, domPolylist   *polyList  );
    void readTriangles (domMesh *mesh, domTriangles  *triangles );
    void readTriFans   (domMesh *mesh, domTrifans    *triFans   );
    void readTriStrips (domMesh *mesh, domTristrips  *triStrips );

    UInt32 mapSemantic  (const std::string               &semantic,
                               UInt32                     set,
                               UInt32                     geoIdx     );

    void   setupProperty(UInt32                           geoIdx,
                         UInt32                           propIdx,
                         const std::string               &semantic,
                         UInt32                           set,
                         const std::string               &sourceId,
                         GeoIntegralProperty             *idxProp    );

    UInt32 setupGeometry(const domInputLocal_Array       &vertInputs,
                         const domInputLocalOffset_Array &inputs,
                         xsNCName                         matSymbold,
                         IndexStore                      &indexStore );

    void   handleBindMaterial(const GeoInfo           &geoInfo,
                              Geometry                *geo,
                              ColladaInstanceGeometry *colInstGeo);

    const BindInfo       *findBind      (const BindStore       &store,
                                         const std::string     &semantic,
                                         UInt32                &offset     );
    const BindVertexInfo *findBindVertex(const BindVertexStore &store,
                                         const std::string     &inSemantic,
                                         UInt32                 inSet,
                                         UInt32                &offset     );

    UInt16 findFreePropertyIndex(UInt32 geoIdx);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

    static ColladaElementRegistrationHelper _regHelper;

    SourceMap _sourceMap;
    GeoStore  _geoStore;

};

OSG_GEN_MEMOBJPTR(ColladaGeometry);

OSG_END_NAMESPACE

#include "OSGColladaGeometry.inl"

#endif // OSG_WITH_COLLADA

#endif // _OSGCOLLADAGEOMETRY_H_
