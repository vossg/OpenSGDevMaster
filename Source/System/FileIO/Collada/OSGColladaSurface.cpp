/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                Copyright (C) 2008 by the OpenSG Forum                     *
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

#include <OSGColladaSurface.h>
#include <OSGColladaLog.h>

#ifdef OSG_WITH_COLLADA

#include <OSGColladaImage.h>
#include <OSGImage.h>

#include <1.4/dom/domImage.h>
#include <1.4/dom/domFx_surface_common.h>

OSG_BEGIN_NAMESPACE

void ColladaSurface::read(void)
{
    OSG_COLLADA_LOG(("ColladaSurface::read:\n"));
    
    domFx_surface_commonRef surface = getDOMElementAs<domFx_surface_common>();

    if(surface == NULL)
        return;

    domFx_surface_init_commonRef init =
        surface->getFx_surface_init_common();

    if(init == NULL)
        return;
    
    OSG_COLLADA_LOG(("ColladaSurface::read: Got <surface> <init_*> [%p] [%s]\n",
                    init.cast(), init->getTypeName()));
    
    const domFx_surface_init_from_common_Array &commonInits =
        init->getInit_from_array();
    
    domFx_surface_init_from_commonRef commonInit = commonInits[0];
    
    OSG_COLLADA_LOG(("ColladaSurface::read: Got commonInits [%d]\n",
                     commonInits.getCount()));
    
    commonInit->getValue().resolveElement();
    
    daeElementRef imageElem = commonInit->getValue().getElement();
    domImageRef   image     = daeSafeCast<domImage>(imageElem);

    if(image == NULL)
        return;

    ColladaImageRefPtr colImage = getUserDataAs<ColladaImage>(image);
    
    if(colImage == NULL)
    {
        colImage = ColladaImage::create(image, getGlobal());
        addElement(colImage);
        
        colImage->read();
    }
    
    ImageUnrecPtr texImage = colImage->getImage();

    if(texImage != NULL)
    {
        _texObj = TextureObjChunk::create();

        _texObj->setImage(texImage);
    }
}

ColladaSurface::ColladaSurface(
    domFx_surface_common *surface, ColladaGlobal *global)

    : Inherited(surface, global)
{
    // nothing to do
}

ColladaSurface::~ColladaSurface(void)
{
    // nothing to do
}

OSG_END_NAMESPACE

#endif // OSG_WITH_COLLADA
