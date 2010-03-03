/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                   Copyright (C) 2006 by the OpenSG Forum                  *
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

OSG_BEGIN_NAMESPACE

/*-------------------------------------------------------------------------*/
/* OSBElementRegistrationHelper<ElementTypeT>                              */
/*-------------------------------------------------------------------------*/

/*! \class OSG::OSBElementRegistrationHelper
    Helper class to register an element for an OpenSG type. The usual way to
    use this, is to put a static member of this type into the element.

    \param ElementTypeT Type of the element to register.
 */

/*-------------------------------------------------------------------------*/
/* Constructor                                                             */

/*! Constructor. Registers the \a ElementTypeT with the OSG::OSBElementFactory
    to be responsible for the OpenSG type \a typeName.

    \param[in] typeName OpenSG type that is handled by \a ElementTypeT.
 */
template <class ElementTypeT>
OSBElementRegistrationHelper<ElementTypeT>::OSBElementRegistrationHelper(
    const std::string &typeName)
{
    OSBElementFactory::the()->registerElement(
        typeName, new OSBElementCreator<ElementType>);
}

/*-------------------------------------------------------------------------*/
/* OSBDefaultElementRegistrationHelper<ElementTypeT>                       */
/*-------------------------------------------------------------------------*/

/*! \class OSG::OSBDefaultElementRegistrationHelper
    Helper class to register an element as the default element, if no
    specific element is registered for a type. The usual way to
    use this, is to put a static member of this type into the element.

    \note This can be used sensibly only once in the system.

    \param ElementTypeT Type of the element to register as default element.
 */

/*-------------------------------------------------------------------------*/
/* Constructor                                                             */

/*! Constructor. Registers \a ElementTypeT as the default element with the
    OSG::OSBElementFactory.
 */
template <class ElementTypeT>
OSBDefaultElementRegistrationHelper<ElementTypeT>
    ::OSBDefaultElementRegistrationHelper(void)
{
    OSBElementFactory::the()->registerDefault(
        new OSBElementCreator<ElementType>());
}

OSG_END_NAMESPACE
