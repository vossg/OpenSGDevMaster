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

inline
Int32  Geometry::getClassicGLId(void) const
{
    return Inherited::getClassicGLId();
}

inline
Int32  Geometry::getAttGLId(void) const
{
    return Inherited::getAttGLId();
}


/*------------------------------ access -----------------------------------*/

//--------------------------
// Property Access
//--------------------------

inline
GeoIntegralProperty *Geometry::getTypes(void) const
{
   return _sfTypes.getValue();
}

inline
GeoIntegralProperty *Geometry::getLengths(void) const
{
   return _sfLengths.getValue();
}

inline
GeoVectorProperty *Geometry::getPositions(void) const
{
   return getProperty(PositionsIndex);
}

inline
GeoVectorProperty *Geometry::getNormals(void) const
{
   return getProperty(NormalsIndex);
}

inline
GeoVectorProperty *Geometry::getColors(void) const
{
   return getProperty(ColorsIndex);
}

inline
GeoVectorProperty *Geometry::getSecondaryColors(void) const
{
   return getProperty(SecondaryColorsIndex);
}

inline
GeoVectorProperty *Geometry::getTexCoords(void) const
{
   return getProperty(TexCoordsIndex);
}

inline
GeoVectorProperty *Geometry::getTexCoords1(void) const
{
   return getProperty(TexCoords1Index);
}

inline
GeoVectorProperty *Geometry::getTexCoords2(void) const
{
   return getProperty(TexCoords2Index);
}

inline
GeoVectorProperty *Geometry::getTexCoords3(void) const
{
   return getProperty(TexCoords3Index);
}

inline
GeoVectorProperty *Geometry::getTexCoords4(void) const
{
   return getProperty(TexCoords4Index);
}

inline
GeoVectorProperty *Geometry::getTexCoords5(void) const
{
   return getProperty(TexCoords5Index);
}

inline
GeoVectorProperty *Geometry::getTexCoords6(void) const
{
   return getProperty(TexCoords6Index);
}

inline
GeoVectorProperty *Geometry::getTexCoords7(void) const
{
   return getProperty(TexCoords7Index);
}



inline
void Geometry::setPositions(GeoVectorProperty * const value)
{
    setProperty(value, PositionsIndex);
}

inline
void Geometry::setNormals(GeoVectorProperty * const value)
{
    setProperty(value, NormalsIndex);
}

inline
void Geometry::setColors(GeoVectorProperty * const value)
{
    setProperty(value, ColorsIndex);
}

inline
void Geometry::setSecondaryColors(GeoVectorProperty * const value)
{
    setProperty(value, SecondaryColorsIndex);
}

inline
void Geometry::setTexCoords(GeoVectorProperty * const value)
{
    setProperty(value, TexCoordsIndex);
}

inline
void Geometry::setTexCoords1(GeoVectorProperty * const value)
{
    setProperty(value, TexCoords1Index);
}

inline
void Geometry::setTexCoords2(GeoVectorProperty * const value)
{
    setProperty(value, TexCoords2Index);
}

inline
void Geometry::setTexCoords3(GeoVectorProperty * const value)
{
    setProperty(value, TexCoords3Index);
}

inline
void Geometry::setTexCoords4(GeoVectorProperty * const value)
{
    setProperty(value, TexCoords4Index);
}

inline
void Geometry::setTexCoords5(GeoVectorProperty * const value)
{
    setProperty(value, TexCoords5Index);
}

inline
void Geometry::setTexCoords6(GeoVectorProperty * const value)
{
    setProperty(value, TexCoords6Index);
}

inline
void Geometry::setTexCoords7(GeoVectorProperty * const value)
{
    setProperty(value, TexCoords7Index);
}


/*! Set the vertex properties at index.
* \param value  The vertex attribute buffer to assign to index.
* \param index  The index of the OpenGL vertex attribute to set.
*/
inline
void Geometry::setProperty(GeoVectorProperty * const value, UInt16 index)
{
    editMField(PropertiesFieldMask, _mfProperties);

    while(_mfProperties.size() <= index)
    {
        _mfProperties.push_back(NULL);
    }
    
    if(value  != NULL &&
       0x0000 != (value->getUsage() & GeoProperty::UsageSystemSet))
    {
        switch(index)
        {
        case PositionsIndex:
            value->setUsage(GeoProperty::UsageObjectSpace |
                            GeoProperty::UsageSystemSet    );
        break;
        
        case NormalsIndex:
            value->setUsage(GeoProperty::UsageTangentSpace |
                            GeoProperty::UsageSystemSet     );
        break;
        
        case ColorsIndex:
        case SecondaryColorsIndex:
            value->setUsage(GeoProperty::UsageColorSpace |
                            GeoProperty::UsageSystemSet   );
        break;
        
        case TexCoordsIndex:
        case TexCoords1Index:
        case TexCoords2Index:
        case TexCoords3Index:
        case TexCoords4Index:
        case TexCoords5Index:
        case TexCoords6Index:
        case TexCoords7Index:
            value->setUsage(GeoProperty::UsageParameterSpace |
                            GeoProperty::UsageSystemSet       );
        break;
        
        default:
            value->setUsage(GeoProperty::UsageUnspecified |
                            GeoProperty::UsageSystemSet       );
        }
    }

    _mfProperties.replace(index, value);
}

/*! Return the vertext property data stored at index. */
inline
GeoVectorProperty *Geometry::getProperty(UInt16 index) const
{
    if(_mfProperties.size() <= index)
        return NULL;

    return _mfProperties[index];
}

/*! Add index array for the vertex data attribute at index.
* \param value   The list of indices to use.
* \param index   The index of the vertex attribute data
*/
inline
void Geometry::setIndex(GeoIntegralProperty * const value, UInt16 index)
{
    editMField(PropIndicesFieldMask, _mfPropIndices);

    while(_mfPropIndices.size() <= index)
    {
        _mfPropIndices.push_back(NULL);
    }

    _mfPropIndices.replace(index, value);
}

/*! Return the list of indices currently being used for the vertex attributes
* at index index.
*/
inline
GeoIntegralProperty *Geometry::getIndex(UInt16 index) const
{
    if(_mfPropIndices.size() <= index)
        return NULL;

    GeoIntegralProperty *p =
        dynamic_cast<GeoIntegralProperty *>(_mfPropIndices[index]);

    return p;
}

inline
void Geometry::setMaterial(Material * const value)
{
    Inherited::setMaterial(value);
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

    _mfPropIndices.resize(newsize, NULL);
}

inline void Geometry::reservePropIndices(size_t newsize)
{
    editMField(PropIndicesFieldMask, _mfPropIndices);

    _mfPropIndices.resize(newsize);
}

/*---------------- Backwards Compatibility Helpers ----------------*/

/*! Set all indices to the same value for all vertex attributes.
*/
inline void Geometry::setIndices(GeoIntegralProperty * const value)
{
    for(UInt16 i = 0; i < MaxAttribs; ++i)
        setIndex(value, i);
}

/*! Return the indices of the first set of vertex attributes.
* Use in combination with setIndices.
*/
inline GeoIntegralProperty *Geometry::getIndices(void)
{
    return getIndex(0);
}

OSG_END_NAMESPACE
