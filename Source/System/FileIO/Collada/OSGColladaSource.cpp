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

#include "OSGColladaSource.h"

#ifdef OSG_WITH_COLLADA

#include "OSGColladaLog.h"
#include "OSGTypedGeoVectorProperty.h"

#include "dom/domSource.h"
#include "dom/domAccessor.h"
#include "dom/domParam.h"

OSG_BEGIN_NAMESPACE

ColladaElementRegistrationHelper ColladaSource::_regHelper(
    &ColladaSource::create, "source");


ColladaElementTransitPtr
ColladaSource::create(daeElement *elem, ColladaGlobal *global)
{
    return ColladaElementTransitPtr(new ColladaSource(elem, global));
}

void
ColladaSource::read(void)
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

    for(UInt32 i = 0; i < params.getCount(); ++i)
    {
        if(params[i]->getName() == NULL)
        {
            _strideMap[i] = -1;
        }
        else
        {
            _strideMap[i] = _elemSize;
            ++_elemSize;
        }
    }

    OSG_COLLADA_LOG(("ColladaSource::read: offset [%d] count [%d] "
                     "stride [%d] elemSize [%d]\n",
                     _offset, _count, _stride, _elemSize));
}

FieldContainer *
ColladaSource::process(ColladaElement *parent)
{
    SFATAL << "ColladaSource::process: <source> has no direct "
           << "correspondence in OpenSG and must be interpreted by "
           << "its parent element."
           << std::endl;

    OSG_ASSERT(false);

    return NULL;
}

GeoVectorProperty *
ColladaSource::getProperty(const std::string &semantic, UInt32 set)
{
    SemanticSetPair semSetPair(semantic, set);
    PropertyMapIt   pmIt = _propMap.find(semSetPair);

    if(pmIt != _propMap.end())
    {
        return pmIt->second;
    }

    readProperty(semSetPair);

    pmIt = _propMap.find(semSetPair);

    if(pmIt != _propMap.end())
    {
        return pmIt->second;
    }

    SFATAL << "ColladaSource::getProperty: Could not read data for "
           << "semantic [" << semantic << "] set [" << set << "]."
           << std::endl;

    return NULL;
}



ColladaSource::ColladaSource(daeElement *elem, ColladaGlobal *global)
    : Inherited (elem, global)
    , _offset   (0)
    , _count    (0)
    , _stride   (1)
    , _elemSize (0)
    , _strideMap()
    , _propMap  ()
{
}

ColladaSource::~ColladaSource(void)
{
}

void
ColladaSource::readProperty(const SemanticSetPair &semSetPair)
{
    OSG_COLLADA_LOG(("ColladaSource::readProperty: semantic [%s] set [%d]\n",
                     semSetPair.first.c_str(), semSetPair.second));

    GeoVectorPropertyUnrecPtr         prop    = NULL;
    domSourceRef                      source  = getDOMElementAs<domSource>  ();
    domSource::domTechnique_commonRef techCom = source ->getTechnique_common();
    domAccessorRef                    acc     = techCom->getAccessor        ();

    daeURI                 dataURI   = acc->getSource();
    domFloat_arrayRef      dataArray = 
        daeSafeCast<domFloat_array>(dataURI.getElement());

    if(dataArray == NULL)
    {
        SWARNING << "ColladaSource::readProperty: Could not find <float_array> "
                 << "for [" << dataURI.str() << "]." << std::endl;
        return;
    }

    const domListOfFloats &data      = dataArray->getValue();

    OSG_ASSERT((_offset + _count * _stride) <= data.getCount());

    if(semSetPair.first == "POSITION")
    {
        if(_elemSize != 3)
        {
            SWARNING << "ColladaSource::readProperty: Unexpected _elemSize ["
                     << _elemSize << "]." << std::endl;
            return;
        }

        prop = GeoPnt3fProperty::create();
        
        Pnt3f  currPnt;
        UInt32 currIdx = 0;

        for(UInt32 i = _offset; i < _count * _stride; ++i)
        {
            if(_strideMap[currIdx] != -1)
            {
                currPnt[_strideMap[currIdx]] = data[i];
            }
            
            ++currIdx;

            if(currIdx == _stride)
            {
                prop->push_back(currPnt);
                currIdx = 0;
            }
        }
    }
    else if(semSetPair.first == "NORMAL")
    {
        if(_elemSize != 3)
        {
            SWARNING << "ColladaSource::readProperty: Unexpected _elemSize ["
                     << _elemSize << "]." << std::endl;
            return;
        }

        prop = GeoVec3fProperty::create();
        
        Vec3f  currVec;
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
    else if(semSetPair.first == "TEXCOORD")
    {
        if(_elemSize != 2)
        {
            SWARNING << "ColladaSource::readProperty: Unexpected _elemSize ["
                     << _elemSize << "]." << std::endl;
            return;
        }

        prop = GeoVec2fProperty::create();
        
        Vec2f  currVec;
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
    else
    {
        SWARNING << "ColladaSource::readProperty: Unknown semantic ["
                 << semSetPair.first << "]." << std::endl;
        return;
    }

    if(prop != NULL)
    {
        _propMap.insert(PropertyMap::value_type(semSetPair, prop));
    }
}


OSG_END_NAMESPACE

#endif // OSG_WITH_COLLADA
