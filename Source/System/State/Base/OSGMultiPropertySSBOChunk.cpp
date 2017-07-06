/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2013 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
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

#include <cstdlib>
#include <cstdio>

#include <boost/bind.hpp>

#include "OSGConfig.h"

#include "OSGGL.h"
#include "OSGGLU.h"
#include "OSGGLEXT.h"
#include "OSGWindow.h"

#include "OSGGLFuncProtos.h"
#include "OSGBaseFunctions.h"

#include "OSGDrawEnv.h"
#include "OSGNode.h"

#include "OSGMultiPropertySSBOChunk.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGMultiPropertySSBOChunkBase.cpp file.
// To modify it, please change the .fcd file (OSGMultiPropertySSBOChunk.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

const UInt8 MultiPropertySSBOChunk::_numTypes =
    MultiPropertySSBOChunk::MAT4_T + 1;

typedef OSG::Window Win;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void MultiPropertySSBOChunk::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

MultiPropertySSBOChunk::MultiPropertySSBOChunk(void) :
    Inherited(),
    _bUpdateBuffer(false)
{
}

MultiPropertySSBOChunk::MultiPropertySSBOChunk(const MultiPropertySSBOChunk &source) :
    Inherited(source),
    _bUpdateBuffer(false)
{
}

MultiPropertySSBOChunk::~MultiPropertySSBOChunk(void)
{
}

/*----------------------------- class specific ----------------------------*/

void MultiPropertySSBOChunk::changed(ConstFieldMaskArg whichField, 
                                     UInt32            origin,
                                     BitVector         details)
{
    if((whichField & (TypesFieldMask |
                      CardinalityFieldMask |
                      CardinalitiesFieldMask |
                      NumPropertiesFieldMask |
                      FloatValuesFieldMask |
                      DoubleValuesFieldMask |
                      IntValuesFieldMask |
                      UIntValuesFieldMask |
                      BoolValuesFieldMask |
                      Vec3ValuesFieldMask |
                      Vec4ValuesFieldMask |
                      MatrixValuesFieldMask)) != 0)
    {
        _bUpdateBuffer = true;
    }

    Inherited::changed(whichField, origin, details);
}

/*----------------------------- onCreate --------------------------------*/

void MultiPropertySSBOChunk::onCreate(const MultiPropertySSBOChunk *source)
{
    Inherited::onCreate(source);

    if(GlobalSystemState == Startup)
        return;
}

void MultiPropertySSBOChunk::onCreateAspect(
    const MultiPropertySSBOChunk *createAspect,
    const MultiPropertySSBOChunk *source      )
{
    Inherited::onCreateAspect(createAspect, source);
}

void MultiPropertySSBOChunk::onDestroy(UInt32 uiContainerId)
{
    Inherited::onDestroy(uiContainerId);
}

/*------------------------------ Output -------------------------------------*/
void MultiPropertySSBOChunk::dump(      UInt32    ,
                                  const BitVector ) const
{
    SLOG << "Dump MultiPropertySSBOChunk NI" << std::endl;
}

/*------------------------------ buffer -------------------------------------*/

std::size_t MultiPropertySSBOChunk::calc_property_buffer_size() const
{
    std::size_t ao = 0; // aligned offset
    std::size_t bo = 0; // base offset

    OSG_ASSERT(check_invariant());

    std::size_t sz = _mfTypes.size();

    for (std::size_t i = 0; i < sz; ++i)
    {
        UInt32 card = _mfCardinality[i];
        UInt8     e = _mfTypes[i];

        while (card-- > 0)
        {
            switch (e)
            {
                case FLOAT_T:
                    ao = alignOffset( 4, bo); bo = ao + sizeof(Real32);
                    break;
                case DOUBLE_T:
                    ao = alignOffset( 8, bo); bo = ao + sizeof(Real64);
                    break;
                case INT_T:
                    ao = alignOffset( 4, bo); bo = ao + sizeof(Int32);
                    break;
                case UINT_T:
                    ao = alignOffset( 4, bo); bo = ao + sizeof(UInt32);
                    break;
                case BOOL_T:
                    ao = alignOffset( 4, bo); bo = ao + sizeof(Int32);
                    break;
                case VEC3_T:
                    ao = alignOffset(16, bo); bo = ao + sizeof(Vec3f);
                    break;
                case VEC4_T:
                    ao = alignOffset(16, bo); bo = ao + sizeof(Vec4f);
                    break;
                case MAT4_T:
                    ao = alignOffset(16, bo); bo = ao + sizeof(Vec4f);
                    ao = alignOffset(16, bo); bo = ao + sizeof(Vec4f);
                    ao = alignOffset(16, bo); bo = ao + sizeof(Vec4f);
                    ao = alignOffset(16, bo); bo = ao + sizeof(Vec4f);
                    ao = alignOffset(16, bo); bo = ao;
                    break;
            }
        }
    }

    ao = alignOffset( 16, bo); bo = ao;                         // padding

    ao *= getNumProperties();  bo = ao;                         // array
    ao = alignOffset( 16, bo); bo = ao;                         // padding

    return ao;
}

std::vector<UInt8> MultiPropertySSBOChunk::create_property_buffer(DrawEnv* pEnv) const
{
    std::size_t size = calc_property_buffer_size();

    std::vector<UInt8> buffer(size);

    UInt32 num_properties = getNumProperties();

    std::size_t ao = 0; // aligned offset
    std::size_t bo = 0; // base offset

    for (UInt32 idx = 0; idx < num_properties; ++idx)
    {
        std::size_t sz = _mfTypes.size();

        UInt32 card_float  = 0;
        UInt32 card_double = 0;
        UInt32 card_int    = 0;
        UInt32 card_uint   = 0;
        UInt32 card_bool   = 0;
        UInt32 card_vec3   = 0;
        UInt32 card_vec4   = 0;
        UInt32 card_mat4   = 0;

        for (std::size_t i = 0; i < sz; ++i)
        {
            UInt32 card = _mfCardinality[i];
            UInt8     e = _mfTypes[i];
            UInt32    j = 0;

            while (card-- > 0)
            {
                switch (e)
                {
                    case FLOAT_T:
                        j = idx * _mfCardinalities[FLOAT_T] + card_float; 
                        ao = alignOffset( 4, bo); *(reinterpret_cast<Real32*>(&buffer[0] + ao)) = getFloatValues(j); bo = ao + sizeof(Real32);
                        card_float++;
                        break;

                    case DOUBLE_T:
                        j = idx * _mfCardinalities[DOUBLE_T] + card_double; 
                        ao = alignOffset( 8, bo); *(reinterpret_cast<Real64*>(&buffer[0] + ao)) = getDoubleValues(j); bo = ao + sizeof(Real64);
                        card_double++;
                        break;

                    case INT_T:
                        j = idx * _mfCardinalities[INT_T] + card_int; 
                        ao = alignOffset( 4, bo); *(reinterpret_cast<Int32*>(&buffer[0] + ao)) = getIntValues(j); bo = ao + sizeof(Int32);
                        card_int++;
                        break;

                    case UINT_T:
                        j = idx * _mfCardinalities[UINT_T] + card_uint; 
                        ao = alignOffset( 4, bo); *(reinterpret_cast<UInt32*>(&buffer[0] + ao)) = getUIntValues(j); bo = ao + sizeof(UInt32);
                        card_uint++;
                        break;

                    case BOOL_T:
                        j = idx * _mfCardinalities[BOOL_T] + card_bool; 
                        ao = alignOffset( 4, bo); *(reinterpret_cast<bool*>(&buffer[0] + ao)) = getBoolValues(j); bo = ao + sizeof(Int32);
                        card_bool++;
                        break;

                    case VEC3_T:
                        j = idx * _mfCardinalities[VEC3_T] + card_vec3; 
                        ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &getVec3Values(j)[0], sizeof(Vec3f)); bo = ao + sizeof(Vec3f);
                        card_vec3++;
                        break;

                    case VEC4_T:
                        j = idx * _mfCardinalities[VEC4_T] + card_vec4; 
                        ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &getVec4Values(j)[0], sizeof(Vec4f)); bo = ao + sizeof(Vec4f);
                        card_vec4++;
                        break;

                    case MAT4_T:
                        j = idx * _mfCardinalities[MAT4_T] + card_mat4; 
                        ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &getMatrixValues(j)[0][0], sizeof(Vec4f)); bo = ao + sizeof(Vec4f);
                        ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &getMatrixValues(j)[1][0], sizeof(Vec4f)); bo = ao + sizeof(Vec4f);
                        ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &getMatrixValues(j)[2][0], sizeof(Vec4f)); bo = ao + sizeof(Vec4f);
                        ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &getMatrixValues(j)[3][0], sizeof(Vec4f)); bo = ao + sizeof(Vec4f);
                        ao = alignOffset(16, bo); bo = ao;
                        card_mat4++;
                        break;
                }
            }
        }

        ao = alignOffset( 16, bo); bo = ao;    // padding

        OSG_ASSERT(card_float  == _mfCardinalities[FLOAT_T]);
        OSG_ASSERT(card_double == _mfCardinalities[DOUBLE_T]);
        OSG_ASSERT(card_int    == _mfCardinalities[INT_T]);
        OSG_ASSERT(card_uint   == _mfCardinalities[UINT_T]);
        OSG_ASSERT(card_bool   == _mfCardinalities[BOOL_T]);
        OSG_ASSERT(card_vec3   == _mfCardinalities[VEC3_T]);
        OSG_ASSERT(card_vec4   == _mfCardinalities[VEC4_T]);
        OSG_ASSERT(card_mat4   == _mfCardinalities[MAT4_T]);
    }

    return buffer;
}

void MultiPropertySSBOChunk::create_property_state(DrawEnv* pEnv)
{
    std::vector<UInt8> buffer = create_property_buffer(pEnv);
    editMFBuffer()->setValues(buffer);
}

void MultiPropertySSBOChunk::update_property_state(DrawEnv* pEnv)
{
    std::vector<UInt8> buffer = create_property_buffer(pEnv);
    editMFBuffer()->setValues(buffer);

    _bUpdateBuffer = false;
}

/*------------------------------ activate -----------------------------------*/

void MultiPropertySSBOChunk::activate(DrawEnv *pEnv, UInt32 idx)
{
    if (_bUpdateBuffer)
        update_property_state(pEnv);

    Inherited::activate(pEnv, idx);
}

/*------------------------------ deactivate ---------------------------------*/

void MultiPropertySSBOChunk::deactivate(DrawEnv *pEnv, UInt32 idx)
{
    Inherited::deactivate(pEnv, idx);
}

/*------------------------------ changeFrom ---------------------------------*/

void MultiPropertySSBOChunk::changeFrom(DrawEnv    *pEnv,
                                        StateChunk *old,
                                        UInt32      idx )
{
    Inherited::changeFrom(pEnv, old, idx);
}

/*------------------------------ interface ----------------------------------*/

UInt32 MultiPropertySSBOChunk::addProperty()
{
    if (!check_invariant())
        clearProperties();

    OSG_ASSERT(check_invariant());

    editMField(FloatValuesFieldMask,    _mfFloatValues);
    editMField(DoubleValuesFieldMask,   _mfDoubleValues);
    editMField(IntValuesFieldMask,      _mfIntValues);
    editMField(UIntValuesFieldMask,     _mfUIntValues);
    editMField(BoolValuesFieldMask,     _mfBoolValues);
    editMField(Vec3ValuesFieldMask,     _mfVec3Values);
    editMField(Vec4ValuesFieldMask,     _mfVec4Values);
    editMField(MatrixValuesFieldMask,   _mfMatrixValues);

    UInt32 card;

    card = _mfCardinalities[FLOAT_T];
    while (card-- > 0)
        _mfFloatValues.push_back(0.f);

    card = _mfCardinalities[DOUBLE_T];
    while (card-- > 0)
        _mfDoubleValues.push_back(0.0);
    
    card = _mfCardinalities[INT_T];
    while (card-- > 0)
        _mfIntValues.push_back(0);

    card = _mfCardinalities[UINT_T];
    while (card-- > 0)
        _mfUIntValues.push_back(0);

    card = _mfCardinalities[BOOL_T];
    while (card-- > 0)
        _mfBoolValues.push_back(false);

    card = _mfCardinalities[VEC3_T];
    while (card-- > 0)
        _mfVec3Values.push_back(Vec3f());

    card = _mfCardinalities[VEC4_T];
    while (card-- > 0)
        _mfVec4Values.push_back(Vec4f());

    card = _mfCardinalities[MAT4_T];
    while (card-- > 0)
        _mfMatrixValues.push_back(Matrix());

    UInt32 n = getNumProperties();
    setNumProperties(++n);

    return UInt32(getNumProperties() - 1);
}

void MultiPropertySSBOChunk::removeProperty(const UInt32 idx)
{
    OSG_ASSERT(check_invariant());

    if (idx >= getNumProperties())
        return;

    editMField(FloatValuesFieldMask,    _mfFloatValues);
    editMField(DoubleValuesFieldMask,   _mfDoubleValues);
    editMField(IntValuesFieldMask,      _mfIntValues);
    editMField(UIntValuesFieldMask,     _mfUIntValues);
    editMField(BoolValuesFieldMask,     _mfBoolValues);
    editMField(Vec3ValuesFieldMask,     _mfVec3Values);
    editMField(Vec4ValuesFieldMask,     _mfVec4Values);
    editMField(MatrixValuesFieldMask,   _mfMatrixValues);

    UInt32 card, i;

    card = _mfCardinalities[FLOAT_T];   
    i    = getNumProperties() * card;
    while (card-- > 0)
        _mfFloatValues.erase(i);

    card = _mfCardinalities[DOUBLE_T];
    i    = getNumProperties() * card;
    while (card-- > 0)
        _mfDoubleValues.erase(i);
    
    card = _mfCardinalities[INT_T];
    i    = getNumProperties() * card;
    while (card-- > 0)
        _mfIntValues.erase(i);

    card = _mfCardinalities[UINT_T];
    i    = getNumProperties() * card;
    while (card-- > 0)
        _mfUIntValues.erase(i);

    card = _mfCardinalities[BOOL_T];
    i    = getNumProperties() * card;
    while (card-- > 0)
        _mfBoolValues.erase(i);

    card = _mfCardinalities[VEC3_T];
    i    = getNumProperties() * card;
    while (card-- > 0)
        _mfVec3Values.erase(i);

    card = _mfCardinalities[VEC4_T];
    i    = getNumProperties() * card;
    while (card-- > 0)
        _mfVec4Values.erase(i);

    card = _mfCardinalities[MAT4_T];
    i    = getNumProperties() * card;
    while (card-- > 0)
        _mfMatrixValues.erase(i);

    UInt32 n = getNumProperties();
    setNumProperties(--n);
    
    OSG_ASSERT(check_invariant());
}

void MultiPropertySSBOChunk::clearProperties()
{
    setNumProperties(0);
   
    editMField(FloatValuesFieldMask,    _mfFloatValues);
    editMField(DoubleValuesFieldMask,   _mfDoubleValues);
    editMField(IntValuesFieldMask,      _mfIntValues);
    editMField(UIntValuesFieldMask,     _mfUIntValues);
    editMField(BoolValuesFieldMask,     _mfBoolValues);
    editMField(Vec3ValuesFieldMask,     _mfVec3Values);
    editMField(Vec4ValuesFieldMask,     _mfVec4Values);
    editMField(MatrixValuesFieldMask,   _mfMatrixValues);

    _mfFloatValues.clear();
    _mfDoubleValues.clear();
    _mfIntValues.clear();
    _mfUIntValues.clear();
    _mfBoolValues.clear();
    _mfVec3Values.clear();
    _mfVec4Values.clear();
    _mfMatrixValues.clear();
}

void MultiPropertySSBOChunk::clearMembers()
{
    clearProperties();

    editMField(CardinalitiesFieldMask, _mfCardinalities);
    editMField(TypesFieldMask,         _mfTypes);
    editMField(CardinalityFieldMask,   _mfCardinality);

    _mfCardinalities.clear();
    _mfTypes.clear();
    _mfCardinality.clear();
}

UInt32 MultiPropertySSBOChunk::addMember(Types type, UInt32 cardinality)
{
    OSG_ASSERT(cardinality > 0);

    if (getNumProperties() > 0)
        clearProperties();

    editMField(CardinalitiesFieldMask, _mfCardinalities);

    if (_mfCardinalities.empty())
    {
        _mfCardinalities.resize(_numTypes);
    }

    UInt32 tag = _mfCardinalities[type] + 1;

    _mfCardinalities[type] += cardinality;

    editMField(TypesFieldMask,       _mfTypes);
    editMField(CardinalityFieldMask, _mfCardinality);

    _mfTypes.push_back(type);
    _mfCardinality.push_back(cardinality);

    return tag;
}

OSG_END_NAMESPACE
