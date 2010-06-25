/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2008 by the OpenSG Forum                          *
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

/*! \class PointerSFieldBase
 */
 
/*-------------------------------------------------------------------------*/
/* Constructors                                                            */

inline
PointerSFieldBase::PointerSFieldBase(void) : 
     Inherited (    ),
    _fieldValue(NULL)
{
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

inline
PointerSFieldBase::~PointerSFieldBase(void)
{
}

/*-------------------------------------------------------------------------*/
/* Raw Store Access                                                        */


inline 
PointerSFieldBase::value_type PointerSFieldBase::getValue(void) const
{
    return WeakRefCountPolicy::validate(_fieldValue);
}

inline
UInt32 PointerSFieldBase::getBinSize(void) const
{
    return SFieldTraits::getBinSize(_fieldValue);
}


inline
void PointerSFieldBase::copyToBin(BinaryDataHandler &pMem) const
{
    SFieldTraits::copyToBin( pMem, 
                            _fieldValue);
}

inline
bool PointerSFieldBase::operator ==(const Self &source) const
{
    return _fieldValue == source._fieldValue;
}


inline
PointerSFieldBase::StoredType &PointerSFieldBase::editRawStore(void)
{
    return _fieldValue;
}

inline
PointerSFieldBase::StoredType const &PointerSFieldBase::getRawStore (void) const
{
    return _fieldValue;
}

OSG_END_NAMESPACE
