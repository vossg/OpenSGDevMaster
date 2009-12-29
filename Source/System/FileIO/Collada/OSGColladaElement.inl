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

OSG_BEGIN_NAMESPACE

ColladaGlobal *
ColladaElement::getGlobal(void) const
{
    return _global;
}

inline daeElement *
ColladaElement::getDOMElement(void) const
{
    return _elem;
}

template <class DomTypeT>
inline DomTypeT *
ColladaElement::getDOMElementAs(void) const
{
    return daeSafeCast<DomTypeT>(_elem);
}

/*! Return the user data associated with the DOM element of this object.
    In all normal cases this is simply this object.
 */
template <class UserDataTypeT> inline
UserDataTypeT *ColladaElement::getUserDataAs(void) const
{
    return getUserDataAs<UserDataTypeT>(_elem);
}

/*! Return the user data associated with the DOM element \a elem.
 */
template <class UserDataTypeT> inline
UserDataTypeT *ColladaElement::getUserDataAs(daeElement *elem)
{
    if(elem->getUserData() != NULL)
    {
        return dynamic_cast<UserDataTypeT *>(
            static_cast<ColladaElement *>(elem->getUserData()));
    }
    else
    {
        return NULL;
    }
}

OSG_END_NAMESPACE
