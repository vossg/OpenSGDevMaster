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

#include "OSGColladaElement.h"
#include "OSGColladaGlobal.h"

#if defined(OSG_WITH_COLLADA) || defined(OSG_DO_DOC)

/*! \class OSG::ColladaElement
    The base class for all objects responsible for converting a part of the
    Collada DOM representation to OpenSG data structures.
    Each has a pointer to the DOM element it converts (\c _elem ) and a pointer
    to a \c ColladaGlobal object (\c _global ).
    
    Each DOM element that has a corresponding \c ColladaElement associated with
    it, stores a pointer to it in its user data pointer. This pointer allows
    the reuse of already converted data e.g. when instantiating elements in the
    DOM.
 */

/*! \fn void ColladaElement::read(void)
    Read the collada DOM elements and generate internal data structures.
    This function will only be called once for every ColladaElement,
    usually right after it is created.
 */

#if 0
/*! \fn FieldContainer *ColladaElement::process(ColladaElement *parent)
    Generates the OpenSG data structures that correspond to this
    ColladaElement.
 */
#endif

OSG_BEGIN_NAMESPACE

ColladaElement::ColladaElement(daeElement *elem, ColladaGlobal *global)
    : Inherited(      )
    , _elem    (elem  )
    , _global  (global)
{
}

ColladaElement::~ColladaElement(void)
{
}

OSG_END_NAMESPACE

#endif // OSG_WITH_COLLADA
