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

#ifndef _OSGCOLLADASOURCE_H_
#define _OSGCOLLADASOURCE_H_

#include "OSGConfig.h"

#if defined(OSG_WITH_COLLADA) || defined(OSG_DO_DOC)

#include "OSGColladaElement.h"
#include "OSGColladaElementFactoryHelper.h"
#include "OSGGeoVectorProperty.h"
#include "OSGAnimKeyFrameDataSource.h"

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpFileIOCollada
    \nohierarchy
 */

class OSG_FILEIO_DLLMAPPING ColladaSource : public ColladaElement
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
    /*! \{                                                                 */

    typedef ColladaElement Inherited;
    typedef ColladaSource  Self;

    OSG_GEN_INTERNAL_MEMOBJPTR(ColladaSource);

    typedef std::vector<std::string>    NameStore;
    typedef NameStore::iterator         NameStoreIt;
    typedef NameStore::const_iterator   NameStoreConstIt;

    typedef std::vector<Matrix>         MatrixStore;
    typedef MatrixStore::iterator       MatrixStoreIt;
    typedef MatrixStore::const_iterator MatrixStoreConstIt;

    typedef std::vector<Real32>         FloatStore;
    typedef FloatStore::iterator        FloatStoreIt;
    typedef FloatStore::const_iterator  FloatStoreConstIt;

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

    virtual void read(ColladaElement *colElemParent);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Access                                                       */
    /*! \{                                                                 */

    GeoVectorProperty      *getProperty  (const std::string &semantic);
    AnimKeyFrameDataSource *getDataSource(const std::string &semantic);

    const NameStore   &getNameStore  (void);
    const MatrixStore &getMatrixStore(void);
    const FloatStore  &getFloatStore (void);

    std::string getNameValue  (UInt32 idx                       );
    bool        getNameValue  (UInt32 idx, std::string &nameVal );
    
    Real32      getFloatValue (UInt32 idx                       );
    bool        getFloatValue (UInt32 idx, Real32      &floatVal);

    Matrix      getMatrixValue(UInt32 idx                       );
    bool        getMatrixValue(UInt32 idx, Matrix      &matVal  );

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:
    /*---------------------------------------------------------------------*/
    /*! \name Constructors/Destructor                                      */
    /*! \{                                                                 */

             ColladaSource(daeElement *elem, ColladaGlobal *global);
    virtual ~ColladaSource(void                                   );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

    // map semantic to a property holding data of this source in the
    // appropriate form for the semantic
    typedef std::map<std::string,
                     GeoVectorPropertyUnrecPtr>      PropertyMap;
    typedef PropertyMap::iterator                    PropertyMapIt;
    typedef PropertyMap::const_iterator              PropertyMapConstIt;

    typedef std::map<std::string,
                     AnimKeyFrameDataSourceUnrecPtr> DataSourceMap;
    typedef DataSourceMap::iterator                  DataSourceMapIt;
    typedef DataSourceMap::const_iterator            DataSourceMapConstIt;

    typedef std::vector<Int16>                  StrideMap;
    typedef StrideMap::iterator                 StrideMapIt;
    typedef StrideMap::const_iterator           StrideMapConstIt;


    GeoVectorProperty      *fillProperty   (const std::string &semantic);
    AnimKeyFrameDataSource *fillDataSource (const std::string &semantic);
    void                    fillNameStore  (void                       );
    void                    fillMatrixStore(void                       );
    void                    fillFloatStore (void                       );
    

    static ColladaElementRegistrationHelper _regHelper;

    UInt32      _offset;
    UInt32      _count;
    UInt32      _stride;
    UInt32      _elemSize;
    StrideMap   _strideMap;

    PropertyMap   _propMap;
    DataSourceMap _dataMap;
    NameStore     _nameStore;
    MatrixStore   _matrixStore;
    FloatStore    _floatStore;
};

OSG_GEN_MEMOBJPTR(ColladaSource);

OSG_END_NAMESPACE

// #include "OSGColladaSource.inl"

#endif // OSG_WITH_COLLADA

#endif // _OSGCOLLADASOURCE_H_
