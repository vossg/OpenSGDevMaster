/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

inline
void Geometry::invalidateDlistCache(void)
{
    Window::refreshGLObject( getClassicGLId() );
    Window::refreshGLObject( getAttGLId() );
}

/*------------------------------ access -----------------------------------*/

//--------------------------
// Property Access
//--------------------------

inline
GeoIntegralPropertyPtr Geometry::getTypes(void) const
{
   return _sfTypes.getValue();
}

inline
GeoIntegralPropertyPtr Geometry::getLengths(void) const
{
   return _sfLengths.getValue();
}

inline
GeoVectorPropertyPtr Geometry::getPositions(void) const
{
   return getProperty(PositionsIndex);
}

inline
GeoVectorPropertyPtr Geometry::getNormals(void) const
{
   return getProperty(NormalsIndex);
}

inline
GeoVectorPropertyPtr Geometry::getColors(void) const
{
   return getProperty(ColorsIndex);
}

inline
GeoVectorPropertyPtr Geometry::getSecondaryColors(void) const
{
   return getProperty(SecondaryColorsIndex);
}

inline
GeoVectorPropertyPtr Geometry::getTexCoords(void) const
{
   return getProperty(TexCoordsIndex);
}

inline
GeoVectorPropertyPtr Geometry::getTexCoords1(void) const
{
   return getProperty(TexCoords1Index);
}

inline
GeoVectorPropertyPtr Geometry::getTexCoords2(void) const
{
   return getProperty(TexCoords2Index);
}

inline
GeoVectorPropertyPtr Geometry::getTexCoords3(void) const
{
   return getProperty(TexCoords3Index);
}

inline
GeoVectorPropertyPtr Geometry::getTexCoords4(void) const
{
   return getProperty(TexCoords4Index);
}

inline
GeoVectorPropertyPtr Geometry::getTexCoords5(void) const
{
   return getProperty(TexCoords5Index);
}

inline
GeoVectorPropertyPtr Geometry::getTexCoords6(void) const
{
   return getProperty(TexCoords6Index);
}

inline
GeoVectorPropertyPtr Geometry::getTexCoords7(void) const
{
   return getProperty(TexCoords7Index);
}



inline
void Geometry::setTypes(GeoIntegralPropertyPtrConstArg value)
{
    Inherited::setTypes(value);
}

inline
void Geometry::setLengths(GeoIntegralPropertyPtrConstArg value)
{
    Inherited::setLengths(value);
}

inline
void Geometry::setPositions(GeoVectorPropertyPtrConstArg value)
{
    setProperty(value, PositionsIndex);
}

inline
void Geometry::setNormals(GeoVectorPropertyPtrConstArg value)
{
    setProperty(value, NormalsIndex);
}

inline
void Geometry::setColors(GeoVectorPropertyPtrConstArg value)
{
    setProperty(value, ColorsIndex);
}

inline
void Geometry::setSecondaryColors(GeoVectorPropertyPtrConstArg value)
{
    setProperty(value, SecondaryColorsIndex);
}

inline
void Geometry::setTexCoords(GeoVectorPropertyPtrConstArg value)
{
    setProperty(value, TexCoordsIndex);
}

inline
void Geometry::setTexCoords1(GeoVectorPropertyPtrConstArg value)
{
    setProperty(value, TexCoords1Index);
}

inline
void Geometry::setTexCoords2(GeoVectorPropertyPtrConstArg value)
{
    setProperty(value, TexCoords2Index);
}

inline
void Geometry::setTexCoords3(GeoVectorPropertyPtrConstArg value)
{
    setProperty(value, TexCoords3Index);
}

inline
void Geometry::setTexCoords4(GeoVectorPropertyPtrConstArg value)
{
    setProperty(value, TexCoords4Index);
}

inline
void Geometry::setTexCoords5(GeoVectorPropertyPtrConstArg value)
{
    setProperty(value, TexCoords5Index);
}

inline
void Geometry::setTexCoords6(GeoVectorPropertyPtrConstArg value)
{
    setProperty(value, TexCoords6Index);
}

inline
void Geometry::setTexCoords7(GeoVectorPropertyPtrConstArg value)
{
    setProperty(value, TexCoords7Index);
}


/*! Set the vertex properties at index.
* \param value  The vertex attribute buffer to assign to index.
* \param index  The index of the OpenGL vertex attribute to set.
*/
inline
void Geometry::setProperty(GeoVectorPropertyPtrConstArg value, UInt16 index)
{
    editMField(PropertiesFieldMask, _mfProperties);

    while(_mfProperties.size() <= index)
    {
        _mfProperties.push_back(NullFC);
    }

    replaceInProperties(index, value);
}

/*! Return the vertext property data stored at index. */
inline
GeoVectorPropertyPtr Geometry::getProperty(UInt16 index) const
{
    if(_mfProperties.size() <= index)
        return NullFC;

    return _mfProperties[index];
}

/*! Add index array for the vertex data attribute at index.
* \param valu    The list of indices to use.
* \param index   The index of the vertex attribute data
*/
inline
void Geometry::setIndex(GeoIntegralPropertyPtrConstArg value, UInt16 index)
{
    editMField(PropIndicesFieldMask, _mfPropIndices);

    while(_mfPropIndices.size() <= index)
    {
        _mfPropIndices.push_back(NullFC);
    }

    replaceInPropIndices(index, value);
}

/*! Return the list of indices currently being used for the vertex attributes
* at index index.
*/
inline
GeoIntegralPropertyPtr Geometry::getIndex(UInt16 index) const
{
    if(_mfPropIndices.size() <= index)
        return NullFC;

    GeoIntegralPropertyPtr p =
        dynamic_cast<GeoIntegralPropertyPtr>(_mfPropIndices[index]);

    return p;
}

inline
void Geometry::setMaterial(const MaterialPtr &value)
{
    editSField(MaterialFieldMask);

    setRefd(_sfMaterial.getValue(), value);
}


inline Geometry::PumpGroupStorage &Geometry::getPumpGroupStorage(void)
{
    return _pumps;
}

/*----------------- Property/Index MField Changes -----------------*/

inline void Geometry::resizeProperties(size_t newsize)
{
    editMField(PropertiesFieldMask, _mfProperties);

    _mfProperties.resize(newsize);
}

inline void Geometry::reserveProperties(size_t newsize)
{
    editMField(PropertiesFieldMask, _mfProperties);

    _mfProperties.reserve(newsize);
}

inline void Geometry::resizePropIndices(size_t newsize)
{
    editMField(PropIndicesFieldMask, _mfPropIndices);

    _mfPropIndices.resize(newsize, NullFC);
}

inline void Geometry::reservePropIndices(size_t newsize)
{
    editMField(PropIndicesFieldMask, _mfPropIndices);

    _mfPropIndices.resize(newsize);
}

/*---------------- Backwards Compatibility Helpers ----------------*/

/*! Set all indices to the same value for all vertex attributes.
*/
inline void Geometry::setIndices(GeoIntegralPropertyPtrConstArg value)
{
    for(UInt16 i = 0; i < MaxAttribs; ++i)
        setIndex(value, i);
}

/*! Return the indices of the first set of vertex attributes.
* Use in combination with setIndices.
*/
inline GeoIntegralPropertyPtr Geometry::getIndices(void)
{
    return getIndex(0);
}

OSG_END_NAMESPACE

#define OSGGEOMETRY_INLINE_CVSID "@(#)$Id$"

