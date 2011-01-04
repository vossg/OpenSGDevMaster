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

#include "OSGColladaInstanceElement.h"

#if defined(OSG_WITH_COLLADA) || defined(OSG_DO_DOC)

/*! \class OSG::ColladaInstanceElement
    Base class for types handling the various <instance_*> tags in
    Collada.    
 */

/*! \fn ColladaInstantiableElement *ColladaInstanceElement::getTargetElem(void) const
    Returns the element instantiated by this element, if it exists and
    NULL otherwise.
 */

#if 0
/*! \fn daeElement *ColladaInstanceElement::getTargetDOMElement(void) const
    Returns the DOM element instantiated by this element (usually obtained
    by resolving the URL attribute).
    If the DOM element is not available (e.g. the URL attribute refers to
    an external document not loaded into the DAE database) NULL is returned.
 */
#endif

OSG_BEGIN_NAMESPACE

ColladaInstanceElement::ColladaInstanceElement(
    daeElement *elem, ColladaGlobal *global)

    : Inherited(elem, global)
{
}

ColladaInstanceElement::~ColladaInstanceElement(void)
{
}

OSG_END_NAMESPACE

#endif // OSG_WITH_COLLADA
