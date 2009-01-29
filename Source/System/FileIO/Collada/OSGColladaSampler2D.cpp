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

#if __GNUC__ >= 4 || __GNUC_MINOR__ >=3
#pragma GCC diagnostic warning "-Wold-style-cast"
#endif

#include <OSGColladaSampler2D.h>
#include <OSGColladaLog.h>

#ifdef OSG_WITH_COLLADA

#include <OSGColladaEffect.h>
#include <OSGColladaSurface.h>

#include <dom/domFx_sampler2D_common.h>
#include <dom/domFx_surface_common.h>

OSG_BEGIN_NAMESPACE

void ColladaSampler2D::read(void)
{
    OSG_COLLADA_LOG(("ColladaSampler2D::read:\n"));
    
    domFx_sampler2D_common::domSourceRef    source;
    domFx_sampler2D_common::domWrap_sRef    wrapS;
    domFx_sampler2D_common::domWrap_tRef    wrapT;
    domFx_sampler2D_common::domMinfilterRef minFilter;
    domFx_sampler2D_common::domMagfilterRef magFilter;

    domFx_sampler2D_commonRef sampler =
        getDOMElementAs<domFx_sampler2D_common>();

    if(sampler == NULL)
        return;

    source    = sampler->getSource   ();
    wrapS     = sampler->getWrap_s   ();
    wrapT     = sampler->getWrap_t   ();
    minFilter = sampler->getMinfilter();
    magFilter = sampler->getMagfilter();

    if(source != NULL && _colEffect != NULL)
    {
        OSG_COLLADA_LOG(("ColladaSampler2D::read: source [%p] effect [%p]\n",
                         source.cast(), _colEffect));

        domFx_surface_commonRef surface =
            _colEffect->getSurface(source->getValue());

        OSG_COLLADA_LOG(("ColladaSampler2D::read: surface [%p]\n",
                         surface.cast()));

        ColladaSurfaceRefPtr colSurface =
            getUserDataAs<ColladaSurface>(surface);
        
        if(colSurface == NULL)
        {
            colSurface = ColladaSurface::create(surface, getGlobal());
            addElement(colSurface);
            
            colSurface->read();
        }
        
        _texObj = colSurface->getTexObj();
    }

    OSG_COLLADA_LOG(("ColladaSampler2D::read: surface texObj [%p]\n",
                     _texObj.get()));
}

ColladaSampler2D::ColladaSampler2D(
    domFx_sampler2D_common *sampler, ColladaGlobal *global)

    : Inherited(sampler, global)
{
}

ColladaSampler2D::~ColladaSampler2D(void)
{
}

OSG_END_NAMESPACE

#endif // OSG_WITH_COLLADA
