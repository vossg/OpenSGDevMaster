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

#include <OSGColladaSource.h>
#include <OSGColladaLog.h>

#ifdef OSG_WITH_COLLADA

#include <1.4/dom/domSource.h>

OSG_BEGIN_NAMESPACE

void ColladaSource::read(void)
{
    OSG_COLLADA_LOG(("ColladaSource::read:\n"));
}

GeoVec3fProperty *ColladaSource::getAsVec3fProp(void)
{
    if(_propVec3f != NULL)
        return _propVec3f;
    
    domSourceRef source = getDOMElementAs<domSource>();
    
    if(source == NULL)
    {
        FWARNING(("ColladaSource:getAsVec3fProp: No <source> element.\n"));
        return _propVec3f;
    }
    
    _propVec3f = GeoVec3fProperty::create();
    
    const domListOfFloats &floatList = source->getFloat_array()->getValue();
    UInt32                 currIdx   = 0;
    Vec3f                  tmpVec;
    
    for(UInt32 i = 0; i < floatList.getCount(); ++i)
    {
        tmpVec[currIdx] = floatList[i];
        
        ++currIdx;
        
        if(currIdx == Vec3f::_uiSize)
        {
            currIdx = 0;
            
            _propVec3f->push_back(tmpVec);
        }
    }
    
    return _propVec3f;
}

GeoPnt3fProperty *ColladaSource::getAsPnt3fProp(void)
{
    if(_propPnt3f != NULL)
        return _propPnt3f;
    
    domSourceRef source = getDOMElementAs<domSource>();
    
    if(source == NULL)
    {
        FWARNING(("ColladaSource:getAsPnt3fProp: No <source> element.\n"));
        return _propPnt3f;
    }
    
    _propPnt3f = GeoPnt3fProperty::create();
    
    const domListOfFloats &floatList = source->getFloat_array()->getValue();
    UInt32                 currIdx   = 0;
    Pnt3f                  tmpPnt;
    
    for(UInt32 i = 0; i < floatList.getCount(); ++i)
    {
        tmpPnt[currIdx] = floatList[i];
        
        ++currIdx;
        
        if(currIdx == Pnt3f::_uiSize)
        {
            currIdx = 0;
            
            _propPnt3f->push_back(tmpPnt);
        }
    }
    
    return _propPnt3f;
}

GeoVec2fProperty *ColladaSource::getAsVec2fProp(void)
{
    if(_propVec2f != NULL)
        return _propVec2f;
    
    domSourceRef source = getDOMElementAs<domSource>();
    
    if(source == NULL)
    {
        FWARNING(("ColladaSource:getAsVec2fProp: No <source> element.\n"));
        return _propVec2f;
    }
    
    _propVec2f = GeoVec2fProperty::create();
    
    const domListOfFloats &floatList = source->getFloat_array()->getValue();
    UInt32                 currIdx   = 0;
    Vec2f                  tmpVec;
    
    for(UInt32 i = 0; i < floatList.getCount(); ++i)
    {
        tmpVec[currIdx] = floatList[i];
        
        ++currIdx;
        
        if(currIdx == Vec2f::_uiSize)
        {
            currIdx = 0;
            
            _propVec2f->push_back(tmpVec);
        }
    }
    
    return _propVec2f;
}

ColladaSource::ColladaSource(domSource *source, ColladaGlobal *global)
    : Inherited(source, global)
{
    // nothing to do
}

ColladaSource::~ColladaSource(void)
{
    // nothing to do
}

OSG_END_NAMESPACE

#endif // OSG_WITH_COLLADA
