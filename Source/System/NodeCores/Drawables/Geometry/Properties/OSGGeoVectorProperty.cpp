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
#include "OSGGeoVectorProperty.h"
#include "OSGDrawEnv.h"

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGGeoVectorPropertyBase.cpp file.
// To modify it, please change the .fcd file (OSGGeoVectorProperty.fcd) and
// regenerate the base file.

/*! \fn bool GeoVectorProperty::getNormalize(void)
    Returns if this property stores normalized vector data.
 */

/*! \fn void GeoVectorProperty::clear(void)
    Removes all values from this property.
 */

/*! \fn void GeoVectorProperty::resize(size_t newsize)
    Changes the size of this property to \a newsize. If the new size is smaller
    than the current size, excessive elements are deleted; if the new is greater
    than the current size, new elements are default constructed.

    \param[in] newsize New size for this property.
 */

/*! \fn UInt32 GeoIntegralProperty::size(void) const
    \copydoc OSG::GeoProperty::size
 */

/*! \fn void GeoVectorProperty::getGenericValue(MaxTypeT &val, const UInt32 index)
    Retrieves this properties value at index \a index in \a val through the
    most generic type available (MaxTypeT).
    The templated access functions will use this internally and then convert to
    the user specified type, thus the concrete properties derived from this
    need to override this method.

    \param[out] val The value stored at index \a index.
    \param[in] index The index of the value to retrieve.
 */

/*! \fn void GeoVectorProperty::setGenericValue(const MaxTypeT &val, const UInt32 index)
    Stores the value \a val in this property at index \a index using the most
    generic type available (MaxTypeT).
    The templated access functions will use this internally and then convert to
    the user specified type, thus the concrete properties derived from this
    need to override this method.

    \param[in] val The value to store at index \a index.
    \param[in] index The index of the value to set.
 */

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

// extension indices for used extensions;
UInt32 GeoVectorProperty::_extSecondaryColor;
UInt32 GeoVectorProperty::_extMultitexture;

// extension indices for used fucntions;
UInt32 GeoVectorProperty::_funcglSecondaryColorPointer;
UInt32 GeoVectorProperty::_funcglClientActiveTextureARB;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void GeoVectorProperty::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);
}

/*------------------------- Chunk Class Access ---------------------------*/

const StateChunkClass *GeoVectorProperty::getClass(void) const
{
    return GeoProperty::getClass();
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

GeoVectorProperty::GeoVectorProperty(void) :
    Inherited()
{
    _extSecondaryColor      =
        Window::registerExtension("GL_EXT_secondary_color");

    _funcglSecondaryColorPointer  = Window::registerFunction(
                            OSG_DLSYM_UNDERSCORE"glSecondaryColorPointerEXT",
                            _extSecondaryColor);

    _extMultitexture        =
        Window::registerExtension("GL_ARB_multitexture");
    _funcglClientActiveTextureARB = Window::registerFunction(
                            OSG_DLSYM_UNDERSCORE"glClientActiveTextureARB",
                            _extMultitexture);
 }

GeoVectorProperty::GeoVectorProperty(const GeoVectorProperty &source) :
    Inherited(source)
{
}

GeoVectorProperty::~GeoVectorProperty(void)
{
}

#if 0
/*-------------------- Arbitrary Type Interface Methods ------------------*/

/*! Returns the value at index \a index in \a val after converting it to
    Vec3f.
    There is no range check for \a index, it must be in [0, size()[.

    \note This is a convenience function and therefore not the most efficient
    way to access property values. It is more efficient to obtain a pointer
    or reference to the stored field an modify it directly.

    \param[out] val Value at the given index.
    \param[in] index Index of the element to access.
 */
void GeoVectorProperty::getValue(      Vec3f  &val,
                                 const UInt32  index) const
{
    MaxTypeT ival;
    getValue(ival, index);
    GeoConvert::convertOut(val, ival, 1, 0);
}

/*! Sets the value at index \a index to \a val.
    There is no range check for \a index, it must be in [0, size()[.

    \note This is a convenience function and therefore not the most efficient
    way to access property values. It is more efficient to obtain a pointer
    or reference to the stored field an modify it directly.

    \param[in] val Value to set the element at the given index to.
    \param[in] index Index of the element to set.
*/
void GeoVectorProperty::setValue(const Vec3f  &val,
                                 const UInt32  index )
{
    MaxTypeT ival;
    GeoConvert::convertIn(ival, val, 1, 0);
    setValue(ival, index);
}
#endif

/*! State Chunk handling */

GLenum GeoVectorProperty::getBufferType(void)
{
#ifndef OSG_WINCE
    return GL_ARRAY_BUFFER_ARB;
#else
    return GL_NONE;
#endif
}

void GeoVectorProperty::activate(DrawEnv *pEnv, UInt32 slot)
{
#ifndef OSG_WINCE
    Window *win = pEnv->getWindow();
    bool isGeneric = (slot >= 16);  // !!!HACK. needs to be replaced for 2.0
    slot &= 15;

    if(win->hasExtension(_extVertexBufferObject) &&
       isGeneric)
    {
        void (OSG_APIENTRY*_glVertexAttribPointerARB)(GLuint index, 
                                                      GLint size, 
                                                      GLenum type, 
                                                      GLboolean normalized,
                                                      GLsizei stride, 
                                                      const GLvoid *pointer)=
            reinterpret_cast<void (OSG_APIENTRY*) (GLuint index, 
                                                   GLint size, 
                                                   GLenum type,
                                                   GLboolean normalized, 
                                                   GLsizei stride, 
                                                   const GLvoid *pointer)>(
                win->getFunction(_funcglVertexAttribPointerARB));

        if(getGLId() != 0 && getUseVBO()) // Do we have a VBO?
        {
            win->validateGLObject(getGLId(), pEnv);

             // get "glBindBufferARB" function pointer
            void (OSG_APIENTRY*_glBindBufferARB)(GLenum target, GLuint buffer) =
                reinterpret_cast<void (OSG_APIENTRY*)(GLenum target, 
                                                      GLuint buffer)>(
                    pEnv->getWindow()->getFunction(_funcBindBuffer));

            _glBindBufferARB(GL_ARRAY_BUFFER_ARB,
                             win->getGLObjectId(getGLId()));

            _glVertexAttribPointerARB(slot, getDimension(),
                getFormat(),
                getNormalize(),
                getStride(), 0);

            _glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
        }
        else
        {
            _glVertexAttribPointerARB(slot, getDimension(),
                getFormat(), getNormalize(),
                getStride(), getData());
        }

        void (OSG_APIENTRY*_glEnableVertexAttribArrayARB)(GLuint index)=
            reinterpret_cast<void (OSG_APIENTRY*) (GLuint index)>(
                win->getFunction(_funcglEnableVertexAttribArrayARB));

        _glEnableVertexAttribArrayARB(slot);
    }
    else
    {
        switch(slot)
        {
        case 0:     glVertexPointer(getDimension(), getFormat(),
                        getStride(), getData());
                    glEnableClientState(GL_VERTEX_ARRAY);
                    break;
        case 2:     glNormalPointer(getFormat(),
                        getStride(), getData());
                    glEnableClientState(GL_NORMAL_ARRAY);
                    break;
        case 3:     glColorPointer(getDimension(), getFormat(),
                        getStride(), getData());
                    glEnableClientState(GL_COLOR_ARRAY);
                    break;
        case 4:     if (win->hasExtension(_extSecondaryColor))
                    {
                         void (OSG_APIENTRY*_glSecondaryColorPointerEXT)
                              (GLint size,GLenum type,GLsizei stride,
                               const GLvoid *pointer)=
                             reinterpret_cast<void (OSG_APIENTRY*)(
                                 GLint size,
                                 GLenum type,
                                 GLsizei stride,
                                 const GLvoid *pointer)>(
                                     win->getFunction(
                                         _funcglSecondaryColorPointer));

                        _glSecondaryColorPointerEXT(getDimension(),
                                                    getFormat(),
                                                    getStride(), getData());
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
                    void (OSG_APIENTRY*_glClientActiveTextureARB)(GLenum type)= 
                        reinterpret_cast<void (OSG_APIENTRY*) (GLenum type)>(
                            win->getFunction(_funcglClientActiveTextureARB));

                    _glClientActiveTextureARB(GL_TEXTURE0_ARB + slot - 8);
                    glTexCoordPointer(getDimension(), getFormat(),
                                      getStride(), getData());
                    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
                    }
                    break;
        default:    FWARNING(("GeoVectorProperty::activate: Non-Generic"
                        " attribute nr. %d unknown!\n", slot));
                    break;
        }

    }
#endif
}

void GeoVectorProperty::changeFrom(DrawEnv    *pEnv,
                                   StateChunk *old,
                                   UInt32      slot)
{
    // change from me to me?
    // this assumes I haven't changed in the meantime.
    if(old == this)
        return;

    // The activation will overwrite the previous activation fully,
    // so no need to deactivate

    activate(pEnv, slot);
}

void GeoVectorProperty::deactivate(DrawEnv *pEnv, UInt32 slot)
{
#ifndef OSG_WINCE
    Window *win = pEnv->getWindow();
    bool isGeneric = (slot >= 16);  // !!!HACK. needs to be replaced for 2.0
    slot &= 15;

    if(win->hasExtension(_extVertexBufferObject) &&
       isGeneric)
    {
        void (OSG_APIENTRY*_glDisableVertexAttribArrayARB)(GLuint index)=
            reinterpret_cast<void (OSG_APIENTRY*) (GLuint index)>(
                win->getFunction(_funcglDisableVertexAttribArrayARB));

        _glDisableVertexAttribArrayARB(slot);
    }
    else
    {
        switch(slot)
        {
        case 0:     glDisableClientState(GL_VERTEX_ARRAY);
                    break;
        case 2:     glDisableClientState(GL_NORMAL_ARRAY);
                    break;
        case 3:     glDisableClientState(GL_COLOR_ARRAY);
                    break;
        case 4:     glDisableClientState(GL_SECONDARY_COLOR_ARRAY_EXT);
                    break;
        case 8:  case 9:
        case 10: case 11:
        case 12: case 13:
        case 14: case 15:
                    {
                    void (OSG_APIENTRY*_glClientActiveTextureARB)(GLenum type)= 
                        reinterpret_cast<void (OSG_APIENTRY*) (GLenum type)>(
                            win->getFunction(_funcglClientActiveTextureARB));

                    _glClientActiveTextureARB(GL_TEXTURE0_ARB + slot - 8);
                    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
                    }
                    break;
        default:    FWARNING(("GeoVectorProperty::deactivate: Non-Generic"
                        " attribute nr. %d unknown!\n", slot));
                    break;
        }
    }
#endif
}

/*----------------------------- class specific ----------------------------*/

void GeoVectorProperty::changed(ConstFieldMaskArg whichField, 
                                UInt32            origin,
                                BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void GeoVectorProperty::dump(      UInt32    ,
                             const BitVector ) const
{
    SLOG << "Dump GeoVectorProperty NI" << std::endl;
}
