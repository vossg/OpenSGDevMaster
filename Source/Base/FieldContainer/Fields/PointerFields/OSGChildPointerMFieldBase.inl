/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                 Copyright (C) 2008 by the OpenSG Forum                    *
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
/* Constructors                                                            */

template <typename AccessHandlerT, Int32 NamespaceI> inline
ChildPointerMFieldBase<AccessHandlerT, 
                       NamespaceI    >::ChildPointerMFieldBase(
                           FieldContainer * const pParent,
                           UInt16                 usChildFieldId,
                           UInt16                 usParentFieldId) : 
     Inherited    (               ),
    _pEnclosingObj(pParent        ),
    _childFieldId (usChildFieldId ),
    _parentFieldId(usParentFieldId)
{
}


/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

template <typename AccessHandlerT, Int32 NamespaceI> inline
ChildPointerMFieldBase<AccessHandlerT, 
                       NamespaceI    >::~ChildPointerMFieldBase(void)
{
}

/*-------------------------------------------------------------------------*/
/* Child Linking Information                                               */

template <typename AccessHandlerT, Int32 NamespaceI> inline 
FieldContainer * 
    ChildPointerMFieldBase<AccessHandlerT, 
                           NamespaceI    >::getEnclosingObject(void) const
{
    return _pEnclosingObj;
}

template <typename AccessHandlerT, Int32 NamespaceI> inline 
void ChildPointerMFieldBase<AccessHandlerT, 
                            NamespaceI    >::setEnclosingObject(
                                FieldContainer * const pObj)
{
    _pEnclosingObj = pObj;
}

template <typename AccessHandlerT, Int32 NamespaceI> inline 
UInt16 ChildPointerMFieldBase<AccessHandlerT, 
                              NamespaceI    >::getChildFieldId(void) const
{
    return _childFieldId;
}

template <typename AccessHandlerT, Int32 NamespaceI> inline 
void ChildPointerMFieldBase<AccessHandlerT, 
                            NamespaceI    >::setChildFieldId(
                                const UInt16 childFieldId)
{
    _childFieldId = childFieldId;
}

template <typename AccessHandlerT, Int32 NamespaceI> inline 
UInt16 ChildPointerMFieldBase<AccessHandlerT, 
                              NamespaceI    >::getParentFieldId(void) const
{
    return _parentFieldId;
}

template <typename AccessHandlerT, Int32 NamespaceI> inline 
void ChildPointerMFieldBase<AccessHandlerT, 
                            NamespaceI    >::setParentFieldId(
                                const UInt16 parentFieldId)
{
    _parentFieldId = parentFieldId;
}

OSG_END_NAMESPACE
