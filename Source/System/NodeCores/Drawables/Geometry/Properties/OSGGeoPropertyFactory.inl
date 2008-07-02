/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                 Copyright (C) 2008 by the OpenSG Forum                    *
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

template <class PropertyTypeT> inline
GeoVectorPropertyTransitPtr GeoPropertyFactoryBase::createPropFunc(void)
{
    return GeoVectorPropertyTransitPtr(PropertyTypeT::create());
}

inline
GeoVectorPropertyTransitPtr GeoPropertyFactoryBase::invalidCreatePropFunc(void)
{
    FWARNING(("GeoPropertyFactoryBase::invalidCreatePropFunc: "
              "Unsupported property type.\n"));

    return GeoVectorPropertyTransitPtr();
}

/*! Maps an OpenGL type constant to an index for the property creation function
    LUT.
 */
inline
UInt32 GeoPropertyFactoryBase::mapFormat(UInt32 format) const
{
    UInt32 returnValue = TypeTraits<UInt32>::getMax();

    switch(format)
    {
    case GL_BYTE:           returnValue = 0;    break;
    case GL_UNSIGNED_BYTE:  returnValue = 1;    break;
    case GL_SHORT:          returnValue = 2;    break;
    case GL_UNSIGNED_SHORT: returnValue = 3;    break;
    case GL_INT:            returnValue = 4;    break;
    case GL_UNSIGNED_INT:   returnValue = 5;    break;
    case GL_FLOAT:          returnValue = 6;    break;
    case GL_DOUBLE:         returnValue = 7;    break;
    
    default:
        FWARNING(("GeoPropertyFactoryBase::mapFormat: Unsupported format [%d].\n",
                  format));
    }
    
    return returnValue;
}

/*! Maps a dimension to an index for the property creation function LUT.
 */
inline
UInt32 GeoPropertyFactoryBase::mapDimension(UInt32 dim) const
{
    UInt32 returnValue = TypeTraits<UInt32>::getMax();
    
    switch(dim)
    {
    case 1:     returnValue = 0;    break;
    case 2:     returnValue = 1;    break;
    case 3:     returnValue = 2;    break;
    case 4:     returnValue = 3;    break;
    
    default:
        FWARNING(("GeoPropertyFactoryBase::mapDim: Unsupported dimension [%d].\n",
                  dim));
    }
    
    return returnValue;
}

inline
UInt32 GeoPropertyFactoryBase::mapUsage(UInt32 usage) const
{
    UInt32 returnValue = TypeTraits<UInt32>::getMax();
    
    switch(usage)
    {
    case GeoProperty::UsageObjectSpace:     returnValue = 0;    break;
    case GeoProperty::UsageTangentSpace:    returnValue = 1;    break;
    case GeoProperty::UsageParameterSpace:  returnValue = 1;    break;
    case GeoProperty::UsageColorSpace:      returnValue = 2;    break;
    
    case GeoProperty::UsageUnspecified:     returnValue = 0;    break;
    
    default:
        FWARNING(("GeoPropertyFactoryBase::mapUsage: Unsupported usage [%d].\n",
                  usage));
    }
    
    return returnValue;
}

inline
UInt32 GeoPropertyFactoryBase::mapNormalize(bool normalize) const
{
    UInt32 returnValue = TypeTraits<UInt32>::getMax();
    
    if(normalize)
        returnValue = 1;
    else
        returnValue = 0;
        
    return returnValue;
}

OSG_END_NAMESPACE
