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

// Helper function
// This should go into Attachment...
inline 
void Geometry::fixParents(FieldContainerAttachmentPtrConstArg oldvalue,
                          FieldContainerAttachmentPtrConstArg newvalue, 
                          FieldContainerPtr                   obj,
                          UInt32                              fieldId)
{
    if(oldvalue != NullFC)
    {
        oldvalue->subParent(obj);

        subRef(oldvalue);
    }

    if(newvalue != NullFC)
    {
        newvalue->addParent(obj, fieldId);
    }
}

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
    addRef(value);

    fixParents(_sfTypes.getValue(), 
               value, 
               Inherited::constructPtr<Geometry>(this), 
               TypesFieldId);
 
    editSField(TypesFieldMask);

    _sfTypes.setValue(value);
}

inline
void Geometry::setLengths(GeoIntegralPropertyPtrConstArg value)
{
    addRef(value);

    fixParents(_sfLengths.getValue(), 
               value, 
               Inherited::constructPtr<Geometry>(this), 
               LengthsFieldId);
 
    editSField(LengthsFieldMask);

    _sfLengths.setValue(value);
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



inline
void Geometry::setProperty(GeoVectorPropertyPtrConstArg value, UInt16 index)
{
    addRef(value);

    editMField(PropertiesFieldMask, _mfProperties);

    while(_mfProperties.size() <= index)
    {
        _mfProperties.push_back(NullFC);
    }
    
    fixParents(_mfProperties[index], 
                value, 
                Inherited::constructPtr<Geometry>(this), 
                PropertiesFieldId);
   
    _mfProperties[index] = value;
}

inline
GeoVectorPropertyPtr Geometry::getProperty(UInt16 index) const
{
    if(_mfProperties.size() <= index)
        return NullFC;
   
    return _mfProperties[index];
}

inline
void Geometry::setIndex(GeoIntegralPropertyPtrConstArg value, UInt16 index)
{
    addRef(value);

    editMField(PropIndicesFieldMask, _mfPropIndices);

    while(_mfPropIndices.size() <= index)
    {
        _mfPropIndices.push_back(NullFC);
    }
    
    fixParents(_mfPropIndices[index], 
                value, 
                Inherited::constructPtr<Geometry>(this),
                PropIndicesFieldId);
   
    _mfPropIndices[index] = value;
}

inline
GeoIntegralPropertyPtr Geometry::getIndex(UInt16 index) const
{
    if(_mfPropIndices.size() <= index)
        return NullFC;
   
    GeoIntegralPropertyPtr p =
        cast_dynamic<GeoIntegralPropertyPtr>(_mfPropIndices[index]);
        
    return p;
}

inline
void Geometry::setMaterial(const MaterialPtr &value)
{
    editSField(MaterialFieldMask);

    setRefd(_sfMaterial.getValue(), value);
}

#if 0
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

/* Set all indices to the same value */
inline void Geometry::setIndices(GeoIntegralPropertyPtrConstArg value)
{
    for(UInt16 i = 0; i < 16; ++i)
        setIndex(value, i);
}

/* Return the first index */
inline GeoIntegralPropertyPtr Geometry::getIndices(void)
{
    return getIndex(0);
}
#endif

OSG_END_NAMESPACE

#define OSGGEOMETRY_INLINE_CVSID "@(#)$Id$"

