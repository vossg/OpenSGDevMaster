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

#include "OSGColladaInstantiableElement.h"

#ifdef OSG_WITH_COLLADA

OSG_BEGIN_NAMESPACE

FieldContainer *
ColladaInstantiableElement::process(ColladaElement *parent)
{
    SFATAL << "ColladaInstantiableElement::process: "
           << "InstantiableElements must be created from their "
           << "respective <instance_*> elements with createInstance()"
           << std::endl;

    return NULL;
}

ColladaInstantiableElement::ColladaInstantiableElement(
    daeElement *elem, ColladaGlobal *global)

    : Inherited (elem, global)
    , _instStore(            )
{
}

ColladaInstantiableElement::~ColladaInstantiableElement(void)
{
}

OSG_END_NAMESPACE

#endif // OSG_WITH_COLLADA
