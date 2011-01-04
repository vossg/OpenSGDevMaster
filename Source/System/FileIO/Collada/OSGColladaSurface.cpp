/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                Copyright (C) 2009 by the OpenSG Forum                     *
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

#if __GNUC__ >= 4 || __GNUC_MINOR__ >=3
#pragma GCC diagnostic ignored "-Wold-style-cast"
#endif

#include "OSGColladaSurface.h"

#if defined(OSG_WITH_COLLADA) || defined(OSG_DO_DOC)

#include "OSGColladaLog.h"
#include "OSGColladaImage.h"

#include <dom/domFx_surface_common.h>
#include <dom/domImage.h>

OSG_BEGIN_NAMESPACE

ColladaElementRegistrationHelper ColladaSurface::_regHelper(
    &ColladaSurface::create, "surface");


ColladaElementTransitPtr
ColladaSurface::create(daeElement *elem, ColladaGlobal *global)
{
    return ColladaElementTransitPtr(new ColladaSurface(elem, global));
}

void
ColladaSurface::read(void)
{
    OSG_COLLADA_LOG(("ColladaSurface::read\n"));

    domFx_surface_commonRef surface = getDOMElementAs<domFx_surface_common>();

    switch(surface->getType())
    {
    case FX_SURFACE_TYPE_ENUM_UNTYPED:
        readUntyped(surface);
        break;

    case FX_SURFACE_TYPE_ENUM_1D:
        read1D(surface);
        break;

    case FX_SURFACE_TYPE_ENUM_2D:
        read2D(surface);
        break;

    case FX_SURFACE_TYPE_ENUM_3D:
        read3D(surface);
        break;

    case FX_SURFACE_TYPE_ENUM_RECT:
        readRect(surface);
        break;

    case FX_SURFACE_TYPE_ENUM_CUBE:
        readCube(surface);
        break;

    case FX_SURFACE_TYPE_ENUM_DEPTH:
        readDepth(surface);
        break;

    case FX_SURFACE_TYPE_ENUM_COUNT:
        SWARNING << "ColladaSurface::read FX_SURFACE_TYPE_ENUM_COUNT "
                 << "not handled"
                 << std::endl;
        break;
    }
}

Image *
ColladaSurface::getImage(void) const
{
    return _image;
}

ColladaSurface::ColladaSurface(daeElement *elem, ColladaGlobal *global)
    : Inherited(elem, global)
    , _image   (NULL)
{
}

ColladaSurface::~ColladaSurface(void)
{
}

void
ColladaSurface::readUntyped(domFx_surface_common *surface)
{
    SWARNING << "ColladaSurface::readUntyped: NIY" << std::endl;
}

void
ColladaSurface::read1D(domFx_surface_common *surface)
{
    SWARNING << "ColladaSurface::read1D: NIY" << std::endl;
}

void
ColladaSurface::read2D(domFx_surface_common *surface)
{
    domFx_surface_init_commonRef init = surface->getFx_surface_init_common();

    domFx_surface_init_common::domInit_as_nullRef    initNull   =
        init->getInit_as_null();
    domFx_surface_init_common::domInit_as_targetRef  initTarget =
        init->getInit_as_target();
    domFx_surface_init_planar_commonRef              initPlanar =
        init->getInit_planar();
    const domFx_surface_init_from_common_Array      &initFroms  =
        init->getInit_from_array();

    if(initNull != NULL)
    {
        SWARNING << "ColladaSurface::read2D: <init_as_null>: NIY"
                 << std::endl;
    }
    else if(initTarget != NULL)
    {
        SWARNING << "ColladaSurface::read2D: <init_as_target>: NIY"
                 << std::endl;
    }
    else if(initPlanar != NULL)
    {
        SWARNING << "ColladaSurface::read2D: <init_planar>: NIY"
                 << std::endl;
    }
    else if(initFroms.getCount() > 0)
    {
        if(initFroms.getCount() > 1)
        {
            SWARNING << "ColladaSurface::read2D: only one "
                     << "<init_from> supported." << std::endl;
        }

        daeElementRef      imageElem = initFroms[0]->getValue().getElement();
        domImageRef        image     = daeSafeCast<domImage>(imageElem);
        ColladaImageRefPtr colImage  = getUserDataAs<ColladaImage>(image);

        if(colImage == NULL)
        {
            colImage = dynamic_pointer_cast<ColladaImage>(
                ColladaElementFactory::the()->create(image, getGlobal()));

            colImage->read();
        }
        
        _image = colImage->getImage();
    }
}

void
ColladaSurface::read3D(domFx_surface_common *surface)
{
    SWARNING << "ColladaSurface::read3D: NIY" << std::endl;
}

void
ColladaSurface::readRect(domFx_surface_common *surface)
{
    SWARNING << "ColladaSurface::readRect: NIY" << std::endl;
}

void
ColladaSurface::readCube(domFx_surface_common *surface)
{
    SWARNING << "ColladaSurface::readCube: NIY" << std::endl;
}

void
ColladaSurface::readDepth(domFx_surface_common *surface)
{
    SWARNING << "ColladaSurface::readDepth: NIY" << std::endl;
}

OSG_END_NAMESPACE

#endif // OSG_WITH_COLLADA
