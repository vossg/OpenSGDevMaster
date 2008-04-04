/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2003 by the OpenSG Forum                          *
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

inline
FieldContainerPtrSFieldBase::FieldContainerPtrSFieldBase(void) :
     Inherited (      ),
    _fieldValue(NullFC)
{
}

inline
FieldContainerPtrSFieldBase::FieldContainerPtrSFieldBase(const Self &obj) :
     Inherited (obj            ),
    _fieldValue(obj._fieldValue)
{
}

inline
FieldContainerPtrSFieldBase::FieldContainerPtrSFieldBase(ArgumentType value) :
     Inherited (     ),
    _fieldValue(value)
{
}

inline
FieldContainerPtrSFieldBase::~FieldContainerPtrSFieldBase(void)
{
}

inline
UInt32 FieldContainerPtrSFieldBase::getBinSize(void) const
{
    return SFieldTraits::getBinSize(_fieldValue);
}

inline
FieldContainerPtrSFieldBase::const_reference 
    FieldContainerPtrSFieldBase::getValue(void) const
{
    return _fieldValue;
}

inline
void FieldContainerPtrSFieldBase::copyToBin(BinaryDataHandler &pMem) const
{
    SFieldTraits::copyToBin( pMem, 
                            _fieldValue);
}

inline
bool FieldContainerPtrSFieldBase::operator ==(const Self &source) const
{
    return _fieldValue == source._fieldValue;
}


inline
FieldContainerPtrSFieldBase::reference 
    FieldContainerPtrSFieldBase::getValue(void)
{
    return _fieldValue;
}

inline
void FieldContainerPtrSFieldBase::setValue(ArgumentType value)
{
    _fieldValue = value;
}

inline
void FieldContainerPtrSFieldBase::setValue(const Self &obj)
{
    _fieldValue = obj._fieldValue;
}

#ifdef OSG_MT_CPTR_ASPECT
inline
void FieldContainerPtrSFieldBase::syncWith(Self &source)
{
    setValue(convertToCurrentAspect(source.getValue()));
}
#endif

OSG_END_NAMESPACE
