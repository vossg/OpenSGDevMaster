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

#if __GNUC__ >= 4 || __GNUC_MINOR__ >=3
#pragma GCC diagnostic ignored "-Wold-style-cast"
#endif

#include "OSGColladaSource.h"

#if defined(OSG_WITH_COLLADA) || defined(OSG_DO_DOC)

#include "OSGColladaLog.h"
#include "OSGTypedGeoVectorProperty.h"
#include "OSGAnimMatrixDataSource.h"
#include "OSGAnimQuaternionDataSource.h"
#include "OSGAnimVec3fDataSource.h"

#include <dom/domSource.h>
#include <dom/domAccessor.h>
#include <dom/domParam.h>
#include <dom/domIDREF_array.h>

OSG_BEGIN_NAMESPACE

ColladaElementRegistrationHelper ColladaSource::_regHelper(
    &ColladaSource::create, "source");


ColladaElementTransitPtr
ColladaSource::create(daeElement *elem, ColladaGlobal *global)
{
    return ColladaElementTransitPtr(new ColladaSource(elem, global));
}

void
ColladaSource::read(ColladaElement *colElemParent)
{
    OSG_COLLADA_LOG(("ColladaSource::read\n"));

    domSourceRef source = getDOMElementAs<domSource>();

    OSG_COLLADA_LOG(("ColladaSource::read: id [%s]\n",
                     source->getID()));

    domSource::domTechnique_commonRef techCom = source ->getTechnique_common();
    domAccessorRef                    acc     = techCom->getAccessor        ();

    _offset   = acc->getOffset();
    _count    = acc->getCount ();
    _stride   = acc->getStride();
    _elemSize = 0;

    _strideMap.resize(_stride, -1);

    const domParam_Array &params = acc->getParam_array();

    UInt32 idx = 0;

    for(UInt32 i = 0; i < params.getCount(); ++i)
    {
        if(params[i]->getName() == NULL)
        {
            _strideMap[idx] = -1;
            ++idx;
        }
        else
        {
            std::string paramType = params[i]->getType();

            if(paramType == "float")
            {
                _strideMap[idx] = _elemSize;
                ++idx;
                ++_elemSize;
            }
            else if(paramType == "float4x4")
            {
                for(UInt32 j = 0; j < 16; ++j)
                {
                    _strideMap[idx] = _elemSize;
                    ++idx;
                    ++_elemSize;
                }
            }
            else if(paramType == "Name")
            {
                _strideMap[idx] = _elemSize;
                ++idx;
                ++_elemSize;
            }
            else
            {
                SWARNING << "ColladaSource::read: Unknown <param> type ["
                         << paramType << "], defaulting to elemSize 1"
                         << std::endl;

                _strideMap[idx] = _elemSize;
                ++idx;
                ++_elemSize;
            }
        }
    }

    OSG_COLLADA_LOG(("ColladaSource::read: offset [%d] count [%d] "
                     "stride [%d] elemSize [%d]\n",
                     _offset, _count, _stride, _elemSize));
}

GeoVectorProperty *
ColladaSource::getProperty(const std::string &semantic)
{
    GeoVectorProperty *retVal = NULL;
    domSourceRef       source = getDOMElementAs<domSource>();
    PropertyMapIt      pmIt   = _propMap.find(semantic);

    if(pmIt != _propMap.end())
    {
        retVal = pmIt->second;
    }
    else
    {
        retVal = fillProperty(semantic);
    }

    if(retVal == NULL)
    {
        SFATAL << "ColladaSource::getProperty: Could not read data for "
               << "semantic [" << semantic << "] from source ["
               << source->getId() << "]."
               << std::endl;
    }

    return retVal;
}

AnimKeyFrameDataSource *
ColladaSource::getDataSource(const std::string &semantic)
{
    AnimKeyFrameDataSource *retVal = NULL;
    domSourceRef            source = getDOMElementAs<domSource>();
    DataSourceMapIt         dmIt   = _dataMap.find(semantic);

    if(dmIt != _dataMap.end())
    {
        retVal = dmIt->second;
    }
    else
    {
        retVal = fillDataSource(semantic);
    }

    if(retVal == NULL)
    {
        SFATAL << "ColladaSource::getDataSource: Could not read data for "
               << "semantic [" << semantic << "] from source ["
               << source->getId() << "]." << std::endl;
    }

    return retVal;
}

const ColladaSource::NameStore &
ColladaSource::getNameStore(void)
{
    if(_nameStore.empty() == true && _count > 0)
    {
        fillNameStore();
    }

    return _nameStore;
}

const ColladaSource::MatrixStore &
ColladaSource::getMatrixStore(void)
{
    if(_matrixStore.empty() == true && _count > 0)
    {
        fillMatrixStore();
    }

    return _matrixStore;
}

const ColladaSource::FloatStore &
ColladaSource::getFloatStore(void)
{
    if(_floatStore.empty() == true && _count > 0)
    {
        fillFloatStore();
    }

    return _floatStore;
}

std::string
ColladaSource::getNameValue(UInt32 idx)
{
    std::string retVal;
    getNameValue(idx, retVal);

    return retVal;
}

bool
ColladaSource::getNameValue(UInt32 idx, std::string &nameVal)
{
    bool                              retVal  = false;
    domSourceRef                      source  = getDOMElementAs<domSource>  ();
    domSource::domTechnique_commonRef techCom = source ->getTechnique_common();
    domAccessorRef                    acc     = techCom->getAccessor        ();

    daeURI           dataURI   = acc->getSource();
    domName_arrayRef dataArray = 
        daeSafeCast<domName_array>(dataURI.getElement());

    if(dataArray == NULL)
    {
        SWARNING << "ColladaSource::getNameValue: Could not find <name_array> "
                 << "for [" << dataURI.str() << "]." << std::endl;
        return retVal;
    }

    if(_elemSize != 1)
    {
        SWARNING << "ColladaSource::getNameValue: Unexpected elemSize ["
                 << _elemSize << "] != 1." << std::endl;
    }

    nameVal = dataArray->getValue()[_offset + idx * _stride];
    retVal  = true;

    return retVal;
}

Real32
ColladaSource::getFloatValue(UInt32 idx)
{
    Real32 retVal;
    getFloatValue(idx, retVal);

    return retVal;
}

bool
ColladaSource::getFloatValue(UInt32 idx, Real32 &floatVal)
{
    bool                              retVal  = false;
    domSourceRef                      source  = getDOMElementAs<domSource> ();
    domSource::domTechnique_commonRef techCom = source->getTechnique_common();
    domAccessorRef                    acc     = techCom->getAccessor       ();

    daeURI            dataURI   = acc->getSource();
    domFloat_arrayRef dataArray =
        daeSafeCast<domFloat_array>(dataURI.getElement());

    if(dataArray == NULL)
    {
        SWARNING << "ColladaSource::getFloatValue: Could not find "
                 << "<float_array> for [" << dataURI.str() << "]."
                 << std::endl;
        return retVal;
    }

    if(_elemSize != 1)
    {
        SWARNING << "ColladaSource::getFloatValue: Unexpected elemSize ["
                 << _elemSize << "] != 1." << std::endl;
    }

    floatVal = dataArray->getValue()[_offset + idx * _stride];
    retVal   = true;

    return retVal;
}

Matrix
ColladaSource::getMatrixValue(UInt32 idx)
{
    Matrix retVal;
    getMatrixValue(idx, retVal);

    return retVal;
}

bool
ColladaSource::getMatrixValue(UInt32 idx, Matrix &matVal)
{
    bool                              retVal  = false;
    domSourceRef                      source  = getDOMElementAs<domSource> ();
    domSource::domTechnique_commonRef techCom = source->getTechnique_common();
    domAccessorRef                    acc     = techCom->getAccessor       ();

    daeURI            dataURI   = acc->getSource();
    domFloat_arrayRef dataArray =
        daeSafeCast<domFloat_array>(dataURI.getElement());

    if(dataArray == NULL)
    {
        SWARNING << "ColladaSource::getMatrixValue: Could not find "
                 << "<float_array> for [" << dataURI.str() << "]."
                 << std::endl;
        return retVal;
    }

    if(_elemSize != 16)
    {
        SWARNING << "ColladaSource::getMatrixValue: Not a matrix <source>, "
                 << "elemSize [" << _elemSize << "] != 16" << std::endl;
    }

    UInt32                 currIdx = 0;
    UInt32                 currRow = 0;
    UInt32                 currCol = 0;
    const domListOfFloats &data    = dataArray->getValue();

    for(UInt32 i = _offset + (idx * _stride);
        i < _offset + (idx + 1) * _stride; ++i)
    {
        if(_strideMap[currIdx] != -1)
        {
            matVal[currCol][currRow] = data[i];
        }

        ++currIdx;
        ++currRow;

        if(currRow >= 4)
        {
            currRow = 0;
            ++currCol;
        }
    }

    return true;
}


ColladaSource::ColladaSource(daeElement *elem, ColladaGlobal *global)
    : Inherited   (elem, global)
    , _offset     (0)
    , _count      (0)
    , _stride     (1)
    , _elemSize   (0)
    , _strideMap  ()
    , _propMap    ()
    , _dataMap    ()
    , _nameStore  ()
    , _matrixStore()
{
}

ColladaSource::~ColladaSource(void)
{
}

GeoVectorProperty *
ColladaSource::fillProperty(const std::string &semantic)
{
    OSG_COLLADA_LOG(("ColladaSource::fillProperty: semantic [%s]\n",
                     semantic.c_str()));

    GeoVectorPropertyUnrecPtr         prop    = NULL;
    domSourceRef                      source  = getDOMElementAs<domSource>  ();
    domSource::domTechnique_commonRef techCom = source ->getTechnique_common();
    domAccessorRef                    acc     = techCom->getAccessor        ();

    daeURI                 dataURI   = acc->getSource();
    domFloat_arrayRef      dataArray = 
        daeSafeCast<domFloat_array>(dataURI.getElement());

    if(dataArray == NULL)
    {
        SWARNING << "ColladaSource::fillProperty: Could not find <float_array> "
                 << "for [" << dataURI.str() << "]." << std::endl;
        return NULL;
    }

    const domListOfFloats &data      = dataArray->getValue();

    OSG_ASSERT((_offset + _count * _stride) <= data.getCount());

    if(semantic == "POSITION")
    {
        if(_elemSize != 3)
        {
            SWARNING << "ColladaSource::fillProperty: Unexpected _elemSize ["
                     << _elemSize << "]." << std::endl;
            return NULL;
        }

        prop = GeoPnt3fProperty::create();
        
        Pnt3f  currPnt;
        UInt32 currIdx = 0;

        for(UInt32 i = _offset; i < _count * _stride; ++i)
        {
            if(_strideMap[currIdx] != -1)
                currPnt[_strideMap[currIdx]] = data[i];
            
            ++currIdx;

            if(currIdx == _stride)
            {
                prop->push_back(currPnt);
                currIdx = 0;
            }
        }
    }
    else
    {
        OSG_COLLADA_LOG(("ColladaSource::fillProperty: Reading semantic [%s] "
                         "with elemSize [%d] stride [%d] offset [%d] count [%d]\n",
                         semantic.c_str(), _elemSize, _stride, _offset, _count));

        if(_elemSize == 2)
        {
            prop = GeoVec2fProperty::create();
        }
        else if(_elemSize == 3)
        {
            prop = GeoVec3fProperty::create();
        }
        else if(_elemSize == 4)
        {
            prop = GeoVec4fProperty::create();
        }
        else
        {
            SWARNING << "ColladaSource::fillProperty: Unhandled element size ["
                     << _elemSize << "] for semantic [" << semantic << "]"
                     << std::endl;
            return NULL;
        }

        Vec4f  currVec;
        UInt32 currIdx = 0;

        for(UInt32 i = _offset; i < _count * _stride; ++i)
        {
            if(_strideMap[currIdx] != -1)
            {
                currVec[_strideMap[currIdx]] = data[i];
            }

            ++currIdx;

            if(currIdx == _stride)
            {
                prop->push_back(currVec);
                currIdx = 0;
            }
        }
    }

    if(prop != NULL)
    {
        _propMap.insert(PropertyMap::value_type(semantic, prop));
    }

    return prop;
}

AnimKeyFrameDataSource *
ColladaSource::fillDataSource(const std::string &semantic)
{
    AnimKeyFrameDataSourceUnrecPtr    retVal  = NULL;
    domSourceRef                      source  = getDOMElementAs<domSource>  ();
    domSource::domTechnique_commonRef techCom = source ->getTechnique_common();
    domAccessorRef                    acc     = techCom->getAccessor        ();

    daeURI            dataURI   = acc->getSource();
    domFloat_arrayRef dataArray = 
        daeSafeCast<domFloat_array>(dataURI.getElement());

    if(dataArray == NULL)
    {
        SWARNING << "ColladaSource::fillDataSource: Could not find "
                 << "<float_array> for [" << dataURI.str() << "]."
                 << std::endl;
        return NULL;
    }

    const domListOfFloats &data = dataArray->getValue();

    OSG_ASSERT((_offset + _count * _stride) <= data.getCount());


    if(_elemSize == 3)
    {
        AnimVec3fDataSourceUnrecPtr dataSource =
            AnimVec3fDataSource::create();

        Vec3f  currVal;
        UInt32 currIdx = 0;

        for(UInt32 i = _offset; i < _count * _stride; ++i)
        {
            if(_strideMap[currIdx] != -1)
                currVal[_strideMap[currIdx]] = data[i];

            ++currIdx;

            if(currIdx == _stride)
            {
                dataSource->editMFValues()->push_back(currVal);
                currIdx = 0;
            }
        }

        retVal = dataSource;
    }
    else if(_elemSize == 4)
    {
        AnimQuaternionDataSourceUnrecPtr dataSource =
            AnimQuaternionDataSource::create();

        Quaternion currVal;
        UInt32     currIdx = 0;

        for(UInt32 i = _offset; i < _count * _stride; ++i)
        {
            if(_strideMap[currIdx] != -1)
                currVal[_strideMap[currIdx]] = data[i];

            ++currIdx;

            if(currIdx == _stride)
            {
                dataSource->editMFValues()->push_back(currVal);
                currIdx = 0;
            }
        }

        retVal = dataSource;
    }
    else if(_elemSize == 16)
    {
        AnimMatrixDataSourceUnrecPtr dataSource =
            AnimMatrixDataSource::create();

        Matrix currVal;
        UInt32 currIdx    = 0;
        UInt32 currRowIdx = 0;
        UInt32 currColIdx = 0;

        for(UInt32 i = _offset; i < _count * _stride; ++i)
        {
            if(_strideMap[currIdx] != -1)
                currVal[currColIdx][currRowIdx] = data[i];

            ++currIdx;
            ++currColIdx;

            if(currColIdx >= 4)
            {
                currColIdx = 0;
                ++currRowIdx;
            }

            if(currIdx == _stride)
            {
                dataSource->editMFValues()->push_back(currVal);
                currIdx    = 0;
                currRowIdx = 0;
                currColIdx = 0;
            }
        }

        retVal = dataSource;
    }
    else
    {
        SWARNING << "ColladaSource::fillDataSource: Unhandled element size ["
                 << _elemSize << "] for semantic [" << semantic << "]"
                 << std::endl;
    }

    if(retVal != NULL)
    {
        _dataMap.insert(DataSourceMap::value_type(semantic, retVal));
    }

    return retVal;
}

void
ColladaSource::fillNameStore(void)
{
    domSourceRef                      source  = getDOMElementAs<domSource>  ();
    domSource::domTechnique_commonRef techCom = source ->getTechnique_common();
    domAccessorRef                    acc     = techCom->getAccessor        ();

    daeURI            dataURI    = acc->getSource();
    domName_arrayRef  nameArray  = 
        daeSafeCast<domName_array> (dataURI.getElement());
    domIDREF_arrayRef idrefArray =
        daeSafeCast<domIDREF_array>(dataURI.getElement());

    if(nameArray == NULL && idrefArray == NULL)
    {
        SWARNING << "ColladaSource::fillNameStore: Could not find <name_array>"
                 << " or <IDREF_array> for [" << dataURI.str() << "]."
                 << std::endl;
        return;
    }

    if(nameArray != NULL)
    {
        std::string           currVal;
        UInt32                currIdx = 0;
        const domListOfNames &data    = nameArray->getValue();
    
        for(UInt32 i = _offset; i < _count * _stride; ++i)
        {
            if(_strideMap[currIdx] != -1)
            {
                currVal = data[i];
            }

            ++currIdx;
        
            if(currIdx == _stride)
            {
                _nameStore.push_back(currVal);
                currIdx = 0;
            }
        }
    }
    else if(idrefArray != NULL)
    {
        std::string     currVal;
        UInt32          currIdx = 0;
        const xsIDREFS &data    = idrefArray->getValue();
    
        for(UInt32 i = _offset; i < _count * _stride; ++i)
        {
            if(_strideMap[currIdx] != -1)
            {
                currVal = data[i].getID();
            }

            ++currIdx;
        
            if(currIdx == _stride)
            {
                _nameStore.push_back(currVal);
                currIdx = 0;
            }
        }
    }
}

void
ColladaSource::fillMatrixStore(void)
{
    domSourceRef                      source  = getDOMElementAs<domSource>  ();
    domSource::domTechnique_commonRef techCom = source ->getTechnique_common();
    domAccessorRef                    acc     = techCom->getAccessor        ();

    daeURI                 dataURI   = acc->getSource();
    domFloat_arrayRef      dataArray = 
        daeSafeCast<domFloat_array>(dataURI.getElement());

    if(dataArray == NULL)
    {
        SWARNING << "ColladaSource::fillMatrixStore: Could not find "
                 << "<float_array> for [" << dataURI.str() << "]."
                 << std::endl;
        return;
    }

    Matrix                 currVal;
    UInt32                 currIdx    = 0;
    UInt32                 currRowIdx = 0;
    UInt32                 currColIdx = 0;
    const domListOfFloats &data       = dataArray->getValue();

    for(UInt32 i = _offset; i < _count * _stride; ++i)
    {
        if(_strideMap[currIdx] != -1)
        {
            currVal[currColIdx][currRowIdx] = data[i];
        }

        ++currIdx;
        ++currColIdx;

        if(currColIdx >= 4)
        {
            currColIdx = 0;
            ++currRowIdx;
        }

        if(currIdx == _stride)
        {
            _matrixStore.push_back(currVal);
            currIdx    = 0;
            currRowIdx = 0;
            currColIdx = 0;
        }
    }
}

void
ColladaSource::fillFloatStore(void)
{
    domSourceRef                      source  = getDOMElementAs<domSource>  ();
    domSource::domTechnique_commonRef techCom = source ->getTechnique_common();
    domAccessorRef                    acc     = techCom->getAccessor        ();

    daeURI            dataURI   = acc->getSource();
    domFloat_arrayRef dataArray =
        daeSafeCast<domFloat_array>(dataURI.getElement());

    if(dataArray == NULL)
    {
        SWARNING << "ColladaSource::fillFloatStore: Could not find "
                 << "<float_array> for [" << dataURI.str() << "]."
                 << std::endl;
        return;
    }

    Real32                 currVal;
    UInt32                 currIdx = 0;
    const domListOfFloats &data    = dataArray->getValue();

    for(UInt32 i = _offset; i < _count * _stride; ++i)
    {
        if(_strideMap[currIdx] != -1)
        {
            currVal = data[i];
        }

        ++currIdx;

        if(currIdx == _stride)
        {
            _floatStore.push_back(currVal);
            currIdx = 0;
        }
    }
}

OSG_END_NAMESPACE

#endif // OSG_WITH_COLLADA
