/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2013 by the OpenSG Forum                 *
 *                                                                           *
 * contact: dirk@opensg.org, gerrit.voss@vossg.org, carsten_neumann@gmx.net  *
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

inline
bool MultiPropertyUBOChunk::check_invariant() const
{
    UInt32 num = getNumProperties();

    if (_mfCardinalities.empty() && num == 0)
        return true;
    if (_mfCardinalities.empty() && num != 0)
        return false;

    if (_mfTypes.size() != _mfCardinality.size())
        return false;

    UInt32 card;

    card = _mfCardinalities[FLOAT_T];   if (num * card != _mfFloatValues .size()) return false;
    card = _mfCardinalities[DOUBLE_T];  if (num * card != _mfDoubleValues.size()) return false;
    card = _mfCardinalities[INT_T];     if (num * card != _mfIntValues   .size()) return false;
    card = _mfCardinalities[UINT_T];    if (num * card != _mfUIntValues  .size()) return false;
    card = _mfCardinalities[BOOL_T];    if (num * card != _mfBoolValues  .size()) return false;
    card = _mfCardinalities[VEC3_T];    if (num * card != _mfVec3Values  .size()) return false;
    card = _mfCardinalities[VEC4_T];    if (num * card != _mfVec4Values  .size()) return false;
    card = _mfCardinalities[MAT4_T];    if (num * card != _mfMatrixValues.size()) return false;

    return true;
}

inline 
UInt32 MultiPropertyUBOChunk::getNumProperties() const
{
    return Inherited::getNumProperties();
}

inline
Real32 MultiPropertyUBOChunk::getFloatProperty(UInt32 idx, UInt32 num) const
{
    OSG_ASSERT(!_mfCardinalities.empty());
    OSG_ASSERT(idx < getNumProperties());
    OSG_ASSERT(num <= _mfCardinalities[FLOAT_T]);
    UInt32 i = idx * _mfCardinalities[FLOAT_T] + num - 1; 
    OSG_ASSERT(i < _mfFloatValues.size());
    return Inherited::getFloatValues(i);
}

inline
Real64 MultiPropertyUBOChunk::getDoubleProperty(UInt32 idx, UInt32 num) const
{
    OSG_ASSERT(!_mfCardinalities.empty());
    OSG_ASSERT(idx < getNumProperties());
    OSG_ASSERT(num <= _mfCardinalities[DOUBLE_T]);
    UInt32 i = idx * _mfCardinalities[DOUBLE_T] + num - 1; 
    OSG_ASSERT(i < _mfDoubleValues.size());
    return Inherited::getDoubleValues(i);
}

inline
Int32 MultiPropertyUBOChunk::getIntProperty(UInt32 idx, UInt32 num) const
{
    OSG_ASSERT(!_mfCardinalities.empty());
    OSG_ASSERT(idx < getNumProperties());
    OSG_ASSERT(num <= _mfCardinalities[INT_T]);
    UInt32 i = idx * _mfCardinalities[INT_T] + num - 1; 
    OSG_ASSERT(i < _mfIntValues.size());
    return Inherited::getIntValues(i);
}

inline
UInt32 MultiPropertyUBOChunk::getUIntProperty(UInt32 idx, UInt32 num) const
{
    OSG_ASSERT(!_mfCardinalities.empty());
    OSG_ASSERT(idx < getNumProperties());
    OSG_ASSERT(num <= _mfCardinalities[UINT_T]);
    UInt32 i = idx * _mfCardinalities[UINT_T] + num - 1; 
    OSG_ASSERT(i < _mfUIntValues.size());
    return Inherited::getUIntValues(i);
}

inline
bool MultiPropertyUBOChunk::getBoolProperty(UInt32 idx, UInt32 num) const
{
    OSG_ASSERT(!_mfCardinalities.empty());
    OSG_ASSERT(idx < getNumProperties());
    OSG_ASSERT(num <= _mfCardinalities[BOOL_T]);
    UInt32 i = idx * _mfCardinalities[BOOL_T] + num - 1; 
    OSG_ASSERT(i < _mfBoolValues.size());
    return Inherited::getBoolValues(i);
}

inline
const Vec3f& MultiPropertyUBOChunk::getVec3Property(UInt32 idx, UInt32 num) const
{
    OSG_ASSERT(!_mfCardinalities.empty());
    OSG_ASSERT(idx < getNumProperties());
    OSG_ASSERT(num <= _mfCardinalities[VEC3_T]);
    UInt32 i = idx * _mfCardinalities[VEC3_T] + num - 1; 
    OSG_ASSERT(i < _mfVec3Values.size());
    return Inherited::getVec3Values(i);
}

inline
const Vec4f& MultiPropertyUBOChunk::getVec4Property(UInt32 idx, UInt32 num) const
{
    OSG_ASSERT(!_mfCardinalities.empty());
    OSG_ASSERT(idx < getNumProperties());
    OSG_ASSERT(num <= _mfCardinalities[VEC4_T]);
    UInt32 i = idx * _mfCardinalities[VEC4_T] + num - 1; 
    OSG_ASSERT(i < _mfVec4Values.size());
    return Inherited::getVec4Values(i);
}

inline
const Matrix& MultiPropertyUBOChunk::getMat4Property(UInt32 idx, UInt32 num) const
{
    OSG_ASSERT(!_mfCardinalities.empty());
    OSG_ASSERT(idx < getNumProperties());
    OSG_ASSERT(num <= _mfCardinalities[MAT4_T]);
    UInt32 i = idx * _mfCardinalities[MAT4_T] + num - 1; 
    OSG_ASSERT(i < _mfMatrixValues.size());
    return Inherited::getMatrixValues(i);
}

inline
void MultiPropertyUBOChunk::setFloatProperty(UInt32 idx, UInt32 num, Real32 value)
{
    OSG_ASSERT(!_mfCardinalities.empty());
    OSG_ASSERT(idx < getNumProperties());
    OSG_ASSERT(num <= _mfCardinalities[FLOAT_T]);
    UInt32 i = idx * _mfCardinalities[FLOAT_T] + num - 1; 
    OSG_ASSERT(i < _mfFloatValues.size());
    editFloatValues(i) = value;
}

inline
void MultiPropertyUBOChunk::setDoubleProperty(UInt32 idx, UInt32 num, Real64 value)
{
    OSG_ASSERT(!_mfCardinalities.empty());
    OSG_ASSERT(idx < getNumProperties());
    OSG_ASSERT(num <= _mfCardinalities[DOUBLE_T]);
    UInt32 i = idx * _mfCardinalities[DOUBLE_T] + num - 1; 
    OSG_ASSERT(i < _mfDoubleValues.size());
    editDoubleValues(i) = value;
}

inline
void MultiPropertyUBOChunk::setIntProperty(UInt32 idx, UInt32 num, Int32  value)
{
    OSG_ASSERT(!_mfCardinalities.empty());
    OSG_ASSERT(idx < getNumProperties());
    OSG_ASSERT(num <= _mfCardinalities[INT_T]);
    UInt32 i = idx * _mfCardinalities[INT_T] + num - 1; 
    OSG_ASSERT(i < _mfIntValues.size());
    editIntValues(i) = value;
}

inline
void MultiPropertyUBOChunk::setUIntProperty(UInt32 idx, UInt32 num, UInt32 value)
{
    OSG_ASSERT(!_mfCardinalities.empty());
    OSG_ASSERT(idx < getNumProperties());
    OSG_ASSERT(num <= _mfCardinalities[UINT_T]);
    UInt32 i = idx * _mfCardinalities[UINT_T] + num - 1; 
    OSG_ASSERT(i < _mfUIntValues.size());
    editUIntValues(i) = value;
}

inline
void MultiPropertyUBOChunk::setBoolProperty(UInt32 idx, UInt32 num, bool   value)
{
    OSG_ASSERT(!_mfCardinalities.empty());
    OSG_ASSERT(idx < getNumProperties());
    OSG_ASSERT(num <= _mfCardinalities[BOOL_T]);
    UInt32 i = idx * _mfCardinalities[BOOL_T] + num - 1; 
    OSG_ASSERT(i < _mfBoolValues.size());
    editBoolValues(i) = value;
}

inline
void MultiPropertyUBOChunk::setVec3Property(UInt32 idx, UInt32 num, const Vec3f&  value)
{
    OSG_ASSERT(!_mfCardinalities.empty());
    OSG_ASSERT(idx < getNumProperties());
    OSG_ASSERT(num <= _mfCardinalities[VEC3_T]);
    UInt32 i = idx * _mfCardinalities[VEC3_T] + num - 1; 
    OSG_ASSERT(i < _mfVec3Values.size());
    editVec3Values(i) = value;
}

inline
void MultiPropertyUBOChunk::setVec4Property(UInt32 idx, UInt32 num, const Vec4f&  value)
{
    OSG_ASSERT(!_mfCardinalities.empty());
    OSG_ASSERT(idx < getNumProperties());
    OSG_ASSERT(num <= _mfCardinalities[VEC4_T]);
    UInt32 i = idx * _mfCardinalities[VEC4_T] + num - 1; 
    OSG_ASSERT(i < _mfVec4Values.size());
    editVec4Values(i) = value;
}

inline
void MultiPropertyUBOChunk::setMat4Property(UInt32 idx, UInt32 num, const Matrix& value)
{
    OSG_ASSERT(!_mfCardinalities.empty());
    OSG_ASSERT(idx < getNumProperties());
    OSG_ASSERT(num <= _mfCardinalities[MAT4_T]);
    UInt32 i = idx * _mfCardinalities[MAT4_T] + num - 1; 
    OSG_ASSERT(i < _mfMatrixValues.size());
    editMatrixValues(i) = value;
}

OSG_END_NAMESPACE
