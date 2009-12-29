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

#include "OSGColladaInstanceGeometry.h"

#ifdef OSG_WITH_COLLADA

#include "OSGColladaLog.h"

#include <dom/domInstance_geometry.h>

OSG_BEGIN_NAMESPACE

ColladaElementRegistrationHelper ColladaInstanceGeometry::_regHelper(
    &ColladaInstanceGeometry::create, "instance_geometry");


ColladaElementTransitPtr
ColladaInstanceGeometry::create(daeElement *elem, ColladaGlobal *global)
{
    return ColladaElementTransitPtr(new ColladaInstanceGeometry(elem, global));
}

void
ColladaInstanceGeometry::read(void)
{
    OSG_COLLADA_LOG(("ColladaInstanceGeometry::read\n"));

    ColladaGeometryRefPtr colGeo = getSourceElem();

    if(colGeo == NULL)
    {
        colGeo = dynamic_pointer_cast<ColladaGeometry>(
            ColladaElementFactory::the()->create(
                getSourceDOMElem(), getGlobal()));

        colGeo->read();
    }
}

Node *
ColladaInstanceGeometry::process(ColladaElement *parent)
{
    ColladaGeometryRefPtr colGeo = getSourceElem();

    return colGeo->createInstance(this);
}

ColladaGeometry *
ColladaInstanceGeometry::getSourceElem(void) const
{
    ColladaGeometry *retVal     = NULL;
    domGeometryRef   sourceElem = getSourceDOMElem();

    if(sourceElem != NULL)
    {
        retVal = getUserDataAs<ColladaGeometry>(sourceElem);
    }

    return retVal;
}

domGeometry *
ColladaInstanceGeometry::getSourceDOMElem(void) const
{
    domGeometryRef          retVal  = NULL;
    domInstance_geometryRef instGeo = getDOMElementAs<domInstance_geometry>();

    if(instGeo->getUrl().getElement() != NULL)
    {
        retVal = daeSafeCast<domGeometry>(instGeo->getUrl().getElement());
    }

    return retVal;
}

ColladaInstanceGeometry::ColladaInstanceGeometry(
    daeElement *elem, ColladaGlobal *global)

    : Inherited(elem, global)
{
}

ColladaInstanceGeometry::~ColladaInstanceGeometry(void)
{
}
OSG_END_NAMESPACE

#endif // OSG_WITH_COLLADA
