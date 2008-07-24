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

#include "OSGGeoPropertyFactory.h"
#include "OSGSingletonHolder.ins"
#include "OSGTypedGeoIntegralProperty.h"
#include "OSGTypedGeoVectorProperty.h"

OSG_BEGIN_NAMESPACE

OSG_SINGLETON_INST(GeoPropertyFactoryBase)

template class SingletonHolder<GeoPropertyFactoryBase>;


/*! GeoVectorProperty create function LUT.
    The dimensions are:  1      usage       - Obj, Tan/Tex, Col
                         2      dimension   - 1 to 4
                         3      format      - GL_BYTE,...
                         4      normalize
 */
GeoPropertyFactoryBase::CreatePropFuncP
    GeoPropertyFactoryBase::_createFuncMap[3][4][8][2] =
    {
        {
            {   { &createPropFunc<GeoPnt1bProperty >,   // Obj, 1, byte
                  &createPropFunc<GeoPnt1NbProperty>
                },
                { &createPropFunc<GeoPnt1ubProperty >,  // Obj, 1, ubyte
                  &createPropFunc<GeoPnt1NubProperty>
                },
                { &createPropFunc<GeoPnt1sProperty >,   // Obj, 1, short
                  &createPropFunc<GeoPnt1NsProperty>
                },
                { &createPropFunc<GeoPnt1usProperty >,  // Obj, 1, ushort
                  &createPropFunc<GeoPnt1NusProperty>
                },
                { &invalidCreatePropFunc,               // Obj, 1, int
                  &invalidCreatePropFunc
                },
                { &invalidCreatePropFunc,               // Obj, 1, uint
                  &invalidCreatePropFunc
                },
                { &createPropFunc<GeoPnt1fProperty>,    // Obj, 1, float
                  &invalidCreatePropFunc
                },
                { &createPropFunc<GeoPnt1dProperty>,    // Obj, 1, double
                  &invalidCreatePropFunc
                }
            },
            {   { &createPropFunc<GeoPnt2bProperty>,    // Obj, 2, byte
                  &createPropFunc<GeoPnt2NbProperty>
                },
                { &createPropFunc<GeoPnt2ubProperty>,   // Obj, 2, ubyte
                  &createPropFunc<GeoPnt2NubProperty>
                },
                { &createPropFunc<GeoPnt2sProperty>,    // Obj, 2, short
                  &createPropFunc<GeoPnt2NsProperty>
                },
                { &createPropFunc<GeoPnt2usProperty>,   // Obj, 2, ushort
                  &createPropFunc<GeoPnt2NusProperty>
                },
                { &invalidCreatePropFunc,               // Obj, 2, int
                  &invalidCreatePropFunc
                },
                { &invalidCreatePropFunc,               // Obj, 2, uint
                  &invalidCreatePropFunc
                },
                { &createPropFunc<GeoPnt2fProperty>,    // Obj, 2, float
                  &invalidCreatePropFunc
                },
                { &createPropFunc<GeoPnt2dProperty>,    // Obj, 2, double
                  &invalidCreatePropFunc
                }
            },
            {   { &createPropFunc<GeoPnt3bProperty>,    // Obj, 3, byte
                  &createPropFunc<GeoPnt3NbProperty>
                },
                { &createPropFunc<GeoPnt3ubProperty>,   // Obj, 3, ubyte
                  &createPropFunc<GeoPnt3NubProperty>
                },
                { &createPropFunc<GeoPnt3sProperty>,    // Obj, 3, short
                  &createPropFunc<GeoPnt3NsProperty>
                },
                { &createPropFunc<GeoPnt3usProperty>,   // Obj, 3, ushort
                  &createPropFunc<GeoPnt3NusProperty>
                },
                { &invalidCreatePropFunc,               // Obj, 3, int
                  &invalidCreatePropFunc
                },
                { &invalidCreatePropFunc,               // Obj, 3, uint
                  &invalidCreatePropFunc
                },
                { &createPropFunc<GeoPnt3fProperty>,    // Obj, 3, float
                  &invalidCreatePropFunc
                },
                { &createPropFunc<GeoPnt3dProperty>,    // Obj, 3, double
                  &invalidCreatePropFunc
                }
            },
            {   { &createPropFunc<GeoPnt4bProperty>,    // Obj, 4, byte
                  &createPropFunc<GeoPnt4NbProperty>
                },
                { &createPropFunc<GeoPnt4ubProperty>,   // Obj, 4, ubyte
                  &createPropFunc<GeoPnt4NubProperty>
                },
                { &createPropFunc<GeoPnt4sProperty>,    // Obj, 4, short
                  &createPropFunc<GeoPnt4NsProperty>
                },
                { &createPropFunc<GeoPnt4usProperty>,   // Obj, 4, ushort
                  &createPropFunc<GeoPnt4NusProperty>
                },
                { &invalidCreatePropFunc,               // Obj, 4, int
                  &invalidCreatePropFunc
                },
                { &invalidCreatePropFunc,               // Obj, 4, uint
                  &invalidCreatePropFunc
                },
                { &createPropFunc<GeoPnt4fProperty>,    // Obj, 4, float
                  &invalidCreatePropFunc
                },
                { &createPropFunc<GeoPnt4dProperty>,    // Obj, 4, double
                  &invalidCreatePropFunc
                }
            }
        },
        {   {   { &createPropFunc<GeoVec1bProperty >,   // Tan/Tex, 1, byte
                  &createPropFunc<GeoVec1NbProperty>
                },
                { &createPropFunc<GeoVec1ubProperty >,  // Tan/Tex, 1, ubyte
                  &createPropFunc<GeoVec1NubProperty>
                },
                { &createPropFunc<GeoVec1sProperty >,   // Tan/Tex, 1, short
                  &createPropFunc<GeoVec1NsProperty>
                },
                { &createPropFunc<GeoVec1usProperty >,  // Tan/Tex, 1, ushort
                  &createPropFunc<GeoVec1NusProperty>
                },
                { &invalidCreatePropFunc,               // Tan/Tex, 1, int
                  &invalidCreatePropFunc
                },
                { &invalidCreatePropFunc,               // Tan/Tex, 1, uint
                  &invalidCreatePropFunc
                },
                { &createPropFunc<GeoVec1fProperty>,    // Tan/Tex, 1, float
                  &invalidCreatePropFunc
                },
                { &createPropFunc<GeoVec1dProperty>,    // Tan/Tex, 1, double
                  &invalidCreatePropFunc
                }
            },
            {   { &createPropFunc<GeoVec2bProperty>,    // Tan/Tex, 2, byte
                  &createPropFunc<GeoVec2NbProperty>
                },
                { &createPropFunc<GeoVec2ubProperty>,   // Tan/Tex, 2, ubyte
                  &createPropFunc<GeoVec2NubProperty>
                },
                { &createPropFunc<GeoVec2sProperty>,    // Tan/Tex, 2, short
                  &createPropFunc<GeoVec2NsProperty>
                },
                { &createPropFunc<GeoVec2usProperty>,   // Tan/Tex, 2, ushort
                  &createPropFunc<GeoVec2NusProperty>
                },
                { &invalidCreatePropFunc,               // Tan/Tex, 2, int
                  &invalidCreatePropFunc
                },
                { &invalidCreatePropFunc,               // Tan/Tex, 2, uint
                  &invalidCreatePropFunc
                },
                { &createPropFunc<GeoVec2fProperty>,    // Tan/Tex, 2, float
                  &invalidCreatePropFunc
                },
                { &createPropFunc<GeoVec2dProperty>,    // Tan/Tex, 2, double
                  &invalidCreatePropFunc
                }
            },
            {   { &createPropFunc<GeoVec3bProperty>,    // Tan/Tex, 3, byte
                  &createPropFunc<GeoVec3NbProperty>
                },
                { &createPropFunc<GeoVec3ubProperty>,   // Tan/Tex, 3, ubyte
                  &createPropFunc<GeoVec3NubProperty>
                },
                { &createPropFunc<GeoVec3sProperty>,    // Tan/Tex, 3, short
                  &createPropFunc<GeoVec3NsProperty>
                },
                { &createPropFunc<GeoVec3usProperty>,   // Tan/Tex, 3, ushort
                  &createPropFunc<GeoVec3NusProperty>
                },
                { &invalidCreatePropFunc,               // Tan/Tex, 3, int
                  &invalidCreatePropFunc
                },
                { &invalidCreatePropFunc,               // Tan/Tex, 3, uint
                  &invalidCreatePropFunc
                },
                { &createPropFunc<GeoVec3fProperty>,    // Tan/Tex, 3, float
                  &invalidCreatePropFunc
                },
                { &createPropFunc<GeoVec3dProperty>,    // Tan/Tex, 3, double
                  &invalidCreatePropFunc
                }
            },
            {   { &createPropFunc<GeoVec4bProperty>,    // Tan/Tex, 4, byte
                  &createPropFunc<GeoVec4NbProperty>
                },
                { &createPropFunc<GeoVec4ubProperty>,   // Tan/Tex, 4, ubyte
                  &createPropFunc<GeoVec4NubProperty>
                },
                { &createPropFunc<GeoVec4sProperty>,    // Tan/Tex, 4, short
                  &createPropFunc<GeoVec4NsProperty>
                },
                { &createPropFunc<GeoVec4usProperty>,   // Tan/Tex, 4, ushort
                  &createPropFunc<GeoVec4NusProperty>
                },
                { &invalidCreatePropFunc,               // Tan/Tex, 4, int
                  &invalidCreatePropFunc
                },
                { &invalidCreatePropFunc,               // Tan/Tex, 4, uint
                  &invalidCreatePropFunc
                },
                { &createPropFunc<GeoVec4fProperty>,    // Tan/Tex, 4, float
                  &invalidCreatePropFunc
                },
                { &createPropFunc<GeoVec4dProperty>,    // Tan/Tex, 4, double
                  &invalidCreatePropFunc
                }
            }
        },
        {   {   { &invalidCreatePropFunc,               // Col, 1, byte
                  &invalidCreatePropFunc
                },
                { &invalidCreatePropFunc,               // Col, 1, ubyte
                  &invalidCreatePropFunc
                },
                { &invalidCreatePropFunc,               // Col, 1, short
                  &invalidCreatePropFunc
                },
                { &invalidCreatePropFunc,               // Col, 1, ushort
                  &invalidCreatePropFunc
                },
                { &invalidCreatePropFunc,               // Col, 1, int
                  &invalidCreatePropFunc
                },
                { &invalidCreatePropFunc,               // Col, 1, uint
                  &invalidCreatePropFunc
                },
                { &invalidCreatePropFunc,               // Col, 1, float
                  &invalidCreatePropFunc
                },
                { &invalidCreatePropFunc,               // Col, 1, double
                  &invalidCreatePropFunc
                }
            },
            {   { &invalidCreatePropFunc,               // Col, 2, byte
                  &invalidCreatePropFunc
                },
                { &invalidCreatePropFunc,               // Col, 2, ubyte
                  &invalidCreatePropFunc
                },
                { &invalidCreatePropFunc,               // Col, 2, short
                  &invalidCreatePropFunc
                },
                { &invalidCreatePropFunc,               // Col, 2, ushort
                  &invalidCreatePropFunc
                },
                { &invalidCreatePropFunc,               // Col, 2, int
                  &invalidCreatePropFunc
                },
                { &invalidCreatePropFunc,               // Col, 2, uint
                  &invalidCreatePropFunc
                },
                { &invalidCreatePropFunc,               // Col, 2, float
                  &invalidCreatePropFunc
                },
                { &invalidCreatePropFunc,               // Col, 2, double
                  &invalidCreatePropFunc
                }
            },
            {   { &invalidCreatePropFunc,               // Col, 3, byte
                  &invalidCreatePropFunc
                },
                { &createPropFunc<GeoColor3ubProperty>, // Col, 3, ubyte
                  &createPropFunc<GeoColor3NubProperty>
                },
                { &invalidCreatePropFunc,               // Col, 3, short
                  &invalidCreatePropFunc
                },
                { &invalidCreatePropFunc,               // Col, 3, ushort
                  &invalidCreatePropFunc
                },
                { &invalidCreatePropFunc,               // Col, 3, int
                  &invalidCreatePropFunc
                },
                { &invalidCreatePropFunc,               // Col, 3, uint
                  &invalidCreatePropFunc
                },
                { &createPropFunc<GeoColor3fProperty>,  // Col, 3, float
                  &invalidCreatePropFunc
                },
                { &invalidCreatePropFunc,               // Col, 3, double
                  &invalidCreatePropFunc
                }
            },
            {   { &invalidCreatePropFunc,               // Col, 4, byte
                  &invalidCreatePropFunc
                },
                { &createPropFunc<GeoColor4ubProperty>, // Col, 4, ubyte
                  &createPropFunc<GeoColor4NubProperty>
                },
                { &invalidCreatePropFunc,               // Col, 4, short
                  &invalidCreatePropFunc
                },
                { &invalidCreatePropFunc,               // Col, 4, ushort
                  &invalidCreatePropFunc
                },
                { &invalidCreatePropFunc,               // Col, 4, int
                  &invalidCreatePropFunc
                },
                { &invalidCreatePropFunc,               // Col, 4, uint
                  &invalidCreatePropFunc
                },
                { &createPropFunc<GeoColor4fProperty>,  // Col, 4, float
                  &invalidCreatePropFunc
                },
                { &invalidCreatePropFunc,               // Col, 4, double
                  &invalidCreatePropFunc
                }
            }
        },
    };

        
/*! Creates a GeoIntegralProperty that stores values of type \a format, which
    must be an appropriate OpenGL type constant (\c GL_UNSIGNED_BYTE,
    \c GL_UNSIGNED_SHORT or \c GL_UNSIGNED_INT ).
 */
GeoIntegralPropertyTransitPtr GeoPropertyFactoryBase::create(UInt32 format)
{
    GeoIntegralPropertyTransitPtr returnValue;

    switch(format)
    {
    case GL_UNSIGNED_BYTE:  returnValue = GeoUInt8Property::create();
    break;
    
    case GL_UNSIGNED_SHORT: returnValue = GeoUInt16Property::create();
    break;
    
    case GL_UNSIGNED_INT:   returnValue = GeoUInt32Property::create();
    break;
    
    default:
        FWARNING(("GeoPropertyFactoryBase::create: Invalid paramter: format [%d].\n",
                  format));
    }
    
    return returnValue;
}

/*! Creates a GeoVectorProperty that stores values described by \a format,
    \a dim, \a usage and \a normalize.
 */
GeoVectorPropertyTransitPtr GeoPropertyFactoryBase::create(
    UInt32 format, UInt32 dim, UInt32 vecType, bool normalize)
{
    GeoVectorPropertyTransitPtr returnValue;

    UInt32 formatIdx    = mapFormat    (format   );
    UInt32 dimIdx       = mapDimension (dim      );
    UInt32 vecTypeIdx   = mapVectorType(vecType  );
    UInt32 normalizeIdx = mapNormalize (normalize);
    
    if(formatIdx    == TypeTraits<UInt32>::getMax() ||
       dimIdx       == TypeTraits<UInt32>::getMax() ||
       vecTypeIdx   == TypeTraits<UInt32>::getMax() ||
       normalizeIdx == TypeTraits<UInt32>::getMax()   )
    {
        FWARNING(("GeoPropertyFactoryBase::create: Invalid parameters: "
                  "format [%d] dim [%d] vecType [%d] normalize [%d].\n",
                  format, dim, vecType, normalize));
    }

    returnValue = _createFuncMap[vecTypeIdx][dimIdx][formatIdx][normalizeIdx]();
    
    return returnValue;
}

OSG_END_NAMESPACE
