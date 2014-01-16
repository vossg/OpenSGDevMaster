/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#include "OSGGLEXT.h"
#include "OSGWindow.h"
#include "OSGGeoMultiProperty.h"
#include "OSGDrawEnv.h"
#include "OSGGeoMultiPropertyData.h"

#include "OSGGLFuncProtos.h"

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGGeoMultiPropertyBase.cpp file.
// To modify it, please change the .fcd file (OSGGeoMultiProperty.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void GeoMultiProperty::initMethod(InitPhase ePhase)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

GeoMultiProperty::GeoMultiProperty(void) :
    Inherited()
{
}

GeoMultiProperty::GeoMultiProperty(const GeoMultiProperty &source) :
    Inherited(source)
{
}

GeoMultiProperty::~GeoMultiProperty(void)
{
}


/*----------------------------- Access ----------------------------*/

UInt32 GeoMultiProperty::getFormat    (void) const
{
    return getIFormat();
}

UInt32 GeoMultiProperty::getFormatSize(void) const
{
    return MapFormatToSize(getIFormat());
}

UInt32 GeoMultiProperty::getVectorType(void) const
{
    return GeoProperty::VectorTypeScalar;
}

UInt32 GeoMultiProperty::getStride    (void) const
{
    return getIStride();
}

UInt32 GeoMultiProperty::getDimension (void) const
{
    return getIDimension();
}

SizeT GeoMultiProperty::size         (void) const
{
    return getISize();
}

UInt32 GeoMultiProperty::size32       (void) const
{
    return getISize();
}

bool GeoMultiProperty::getNormalize (void) const
{
    return getINormalize();
}

const UInt8 *GeoMultiProperty::getData(void) const
{
    return getContainer()->getData() + getOffset();
}

UInt8 *GeoMultiProperty::editData(void)
{
    return getContainer()->editData() + getOffset();
}

GeoMultiProperty::MaxTypeT
GeoMultiProperty::getValue(const SizeT index) const
{
    MaxTypeT val;
    getGenericValue(val, index);

    return val;
}

void
GeoMultiProperty::getValue(MaxTypeT &val, const SizeT index) const
{
    getGenericValue(val, index);
}

void GeoMultiProperty::clear(void)
{
    resize(0);
}

void GeoMultiProperty::resize(SizeT newsize)
{
    UInt16 dim    = getDimension();

    UInt32 stride = getStride() ? getStride() : getFormatSize() * dim;    
    
    if(stride * newsize + getOffset() >= getContainer()->size())
    {
        getContainer()->resize(stride * newsize +  getFormatSize() * dim + 
                               getOffset());
    }

    setISize(UInt32(newsize));
}

void GeoMultiProperty::setFormat(UInt32 val)
{
    setIFormat(val);
}
void GeoMultiProperty::setStride(UInt32 val)
{
    setIStride(val);
}

void GeoMultiProperty::setDimension(UInt32 val)
{
    setIDimension(val);
}

void GeoMultiProperty::setSize(UInt32 val)
{
    setISize(val);
}

void GeoMultiProperty::setNormalize(bool val)
{
    setINormalize(val);
}

void GeoMultiProperty::setValue(const MaxTypeT &val, const UInt32 index)
{
    setGenericValue(val, index);
}

GeoPropertyTransitPtr GeoMultiProperty::clone(void)
{
    ObjTransitPtr obj = GeoMultiProperty::create();
    
    obj->setContainer (this->getContainer ());
    obj->setOffset    (this->getOffset    ());
    obj->setIFormat   (this->getIFormat   ());
    obj->setIDimension(this->getIDimension());
    obj->setISize     (this->getISize     ());
    obj->setINormalize(this->getINormalize());
    obj->setIStride   (this->getIStride   ());
    
    return GeoPropertyTransitPtr(obj);
}

/*---------------------------------------------------------------------*/
/*                       Chunk Class Access                            */
/*                                                                     */

const StateChunkClass *GeoMultiProperty::getClass(void) const
{
    return &GeoProperty::_class;
}

/*---------------------------------------------------------------------*/
/*                           State Commands                            */
/*                                                                     */

void GeoMultiProperty::activate(DrawEnv *pEnv, 
                                UInt32   slot )
{
    Window *win = pEnv->getWindow();
    bool isGeneric = (slot >= 16);  // !!!HACK. needs to be replaced for 2.0
    slot &= 15;
    
    if(!win->hasExtOrVersion(_extVertexBufferObject, 0x0105, 0x0200))
    {
        FWARNING(("GeoMultiProperty::activate: Window %p doesn't "
                  "support VBOs!\n", win));
                  return;
    }
    
    win->validateGLObject(getContainer()->getGLId(), pEnv);

     // get "glBindBufferARB" function pointer

    OSGGETGLFUNCBYID_GL3_ES( glBindBuffer, 
                             osgGlBindBuffer,
                            _funcBindBuffer, 
                             win);
   
    osgGlBindBuffer(GL_ARRAY_BUFFER_ARB, 
                    win->getGLObjectId(getContainer()->getGLId()));

#define BUFFER_OFFSET(i)     (static_cast<char *>(NULL) + (i))

    if(isGeneric)
    {
        OSGGETGLFUNCBYID_GL3_ES( glVertexAttribPointer, 
                                 osgGlVertexAttribPointer,
                                _funcVertexAttribPointerARB,
                                 win);

        osgGlVertexAttribPointer(slot, 
                                 getDimension(), 
                                 getFormat(), 
                                 getNormalize(),
                                 getStride(), 
                                 BUFFER_OFFSET(getOffset()));

        OSGGETGLFUNCBYID_GL3_ES( glEnableVertexAttribArray,
                                 osgGlEnableVertexAttribArray,
                                _funcEnableVertexAttribArrayARB,
                                 win);
 
        osgGlEnableVertexAttribArray(slot);
 
        OSGGETGLFUNCBYID_GL3_ES( glVertexAttribDivisor,
                                 osgGlVertexAttribDivisor,
                                _funcVertexAttribDivisorARB,
                                 win);
 
        osgGlVertexAttribDivisor(slot, _sfDivisor.getValue());
     }
    else
    {
#if !defined(OSG_OGL_COREONLY) || defined(OSG_CHECK_COREONLY)
        switch(slot)
        {
            case 0:     
                glVertexPointer(getDimension(), getFormat(),
                                getStride(), BUFFER_OFFSET(getOffset()));
                glEnableClientState(GL_VERTEX_ARRAY);
                break;
            case 2:     
                glNormalPointer(getFormat(),
                                getStride(), BUFFER_OFFSET(getOffset()));
                glEnableClientState(GL_NORMAL_ARRAY);
                break;
            case 3:     
                glColorPointer(getDimension(), getFormat(),
                               getStride(), BUFFER_OFFSET(getOffset()));
                glEnableClientState(GL_COLOR_ARRAY);
                break;
            case 4:     
                if (win->hasExtOrVersion(_extSecondaryColor, 0x0104))
                {
                    OSGGETGLFUNCBYID_EXT( glSecondaryColorPointer,
                                          osgGlSecondaryColorPointer,
                                         _funcSecondaryColorPointer,
                                          win);

                    osgGlSecondaryColorPointer(getDimension(),
                                               getFormat(),
                                               getStride(), 
                                               BUFFER_OFFSET(getOffset()));

                    glEnableClientState(GL_SECONDARY_COLOR_ARRAY_EXT);
                }
                else
                {
                    FWARNING(("GeoVectorProperty::activate: Window "
                              "has no Secondary Color extension\n"));
                }
                break;
            case 8:  case 9: 
            case 10: case 11: 
            case 12: case 13: 
            case 14: case 15: 
            {
                OSGGETGLFUNCBYID_GL3_ES( glClientActiveTexture,
                                         osgGlClientActiveTexture,
                                        _funcClientActiveTextureARB,
                                         win);

                osgGlClientActiveTexture(GL_TEXTURE0_ARB + slot - 8);

                glTexCoordPointer(getDimension(), 
                                  getFormat(),
                                  getStride(), 
                                  BUFFER_OFFSET(getOffset()));

                glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            }
            break;
            default:    FWARNING(("GeoVectorProperty::activate: Non-Generic"
                                  " attribute nr. %d unknown!\n", slot));
                break;
        }     
#endif
    } // isGeneric

    osgGlBindBuffer(GL_ARRAY_BUFFER_ARB, 0);
}

void GeoMultiProperty::changeFrom(DrawEnv    *pEnv, 
                                  StateChunk *old,
                                  UInt32      index)
{
    activate(pEnv, index);
}

void GeoMultiProperty::deactivate(DrawEnv *pEnv, 
                                  UInt32   index)
{
// Nothing to do here
}

bool GeoMultiProperty::isTransparent (void) const
{
    return false;
}

/*---------------------------------------------------------------------*/
/*!                         Comparison                                 */
/*!                                                                    */

Real32 GeoMultiProperty::switchCost(StateChunk *)
{
    return 0;
}

bool GeoMultiProperty::operator < (const StateChunk &other) const
{
    return this < &other;
}

bool GeoMultiProperty::operator == (const StateChunk &other) const
{
    GeoMultiProperty const *tother = 
        dynamic_cast<GeoMultiProperty const*>(&other);

    if(!tother)
        return false;

    if(tother == this)
        return true;

    return false;
}

bool GeoMultiProperty::operator != (const StateChunk &other) const
{
    return ! (*this == other);
}

/*----------------------------- class specific ----------------------------*/

void GeoMultiProperty::changed(ConstFieldMaskArg whichField, 
                               UInt32            origin,
                               BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void GeoMultiProperty::dump(      UInt32    , 
                            const BitVector ) const
{
    SLOG << "Dump GeoMultiProperty NI" << std::endl;
}

/*----------------------------- Generic Access ----------------------------*/

void
GeoMultiProperty::getGenericValue(MaxTypeT &eval, const SizeT index ) const
{
          UInt16  dim    = getDimension();
          bool    norm   = getNormalize();
          UInt32  stride = getStride() ? getStride() : getFormatSize() * dim;
    const UInt8  *data   = getData() + stride * index;

#define getValNormCase(vectype)                                 \
{                                                               \
vectype ival(vectype::Null);                                    \
for (UInt16 i = 0; i < dim; ++i)                                \
    ival[i] =                                                   \
        reinterpret_cast<const vectype::ValueType*>(data)[i];   \
                                                                \
if(norm)                                                        \
{                                                               \
    GeoConvertNormalize::convertOut(eval, ival,              \
        TypeTraits<vectype::ValueType>::getMax(), 0);           \
}                                                               \
else                                                            \
{                                                               \
    GeoConvert::convertOut(eval, ival);                      \
}                                                               \
}

#define getValCase(vectype)                                     \
{                                                               \
vectype ival(vectype::Null);                                    \
for (UInt16 i = 0; i < dim; ++i)                                \
    ival[i] =                                                   \
        reinterpret_cast<const vectype::ValueType*>(data)[i];   \
                                                                \
GeoConvert::convertOut(eval, ival);                          \
}
    switch(getFormat())
    {
        case GL_BYTE:                   getValNormCase(Vec4b );
            break;
        case GL_UNSIGNED_BYTE:          getValNormCase(Vec4ub);
            break;
        case GL_SHORT:                  getValNormCase(Vec4s );
            break;
        case GL_UNSIGNED_SHORT:         getValNormCase(Vec4us);
            break;
/*    case GL_INT:                    getValNormCase(Vec4i );
                                    break;
    case GL_UNSIGNED_INT:           getValNormCase(Vec4ui);
                                    break;
 */    
        case GL_FLOAT:                  getValCase    (Vec4f );
            break;
#ifndef OSG_OGL_NO_DOUBLE
        case GL_DOUBLE:                 getValCase    (Vec4d );
            break;
#endif
    }

#undef getValNormCase
#undef getValCase
}

void
GeoMultiProperty::setGenericValue(const MaxTypeT &eval, const SizeT index )
{
    UInt16 dim = getDimension();
    bool norm = getNormalize();
    UInt32 stride = getStride() ? getStride() : getFormatSize() * dim;    
    UInt8 *data = editData() + stride * index;

#define setValNormCase(vectype)                                 \
{                                                               \
vectype ival;                                                   \
if(norm)                                                        \
{                                                               \
    GeoConvertNormalize::convertIn(ival, eval,               \
        TypeTraits<vectype::ValueType>::getMax(), 0);           \
}                                                               \
else                                                            \
{                                                               \
    GeoConvert::convertIn(ival, eval);                       \
}                                                               \
for (UInt16 i = 0; i < dim; ++i)                                \
    reinterpret_cast<vectype::ValueType*>(data)[i] =            \
        ival[i];                                                \
}

#define setValCase(vectype)                                     \
{                                                               \
vectype ival;                                                   \
GeoConvert::convertIn(ival, eval);                           \
for (UInt16 i = 0; i < dim; ++i)                                \
    reinterpret_cast<vectype::ValueType*>(data)[i] =            \
        ival[i];                                                \
}
    
    switch(getFormat())
    {
        case GL_BYTE:                   setValNormCase(Vec4b );
            break;
        case GL_UNSIGNED_BYTE:          setValNormCase(Vec4ub);
            break;
        case GL_SHORT:                  setValNormCase(Vec4s );
            break;
        case GL_UNSIGNED_SHORT:         setValNormCase(Vec4us);
            break;
/*    case GL_INT:                    setValNormCase(Vec4i );
      break;
    case GL_UNSIGNED_INT:           setValNormCase(Vec4ui);
      break;
 */    
        case GL_FLOAT:                  setValCase    (Vec4f );
            break;
#ifndef OSG_OGL_NO_DOUBLE
        case GL_DOUBLE:                 setValCase    (Vec4d );
            break;
#endif
    }

#undef setValNormCase
#undef setValCase
}
