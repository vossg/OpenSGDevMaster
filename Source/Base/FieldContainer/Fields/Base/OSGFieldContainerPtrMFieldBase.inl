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
UInt32 FieldContainerPtrMFieldBase::getBinSize(void) const
{
    return 
        sizeof(UInt32) + // num elements
        (_values.size() ? 
         MFieldTraits::getBinSize(&(_values[0]), _values.size()) : 0);
}


inline
void FieldContainerPtrMFieldBase::copyToBin(BinaryDataHandler &pMem) const
{
    UInt32 n = _values.size();

    pMem.putValue(n);

    if(n != 0)
    {
        MFieldTraits::copyToBin(   pMem, 
                                &(_values[0]),
                                  _values.size());
    }
}

inline
FieldContainerPtrMFieldBase::const_iterator 
    FieldContainerPtrMFieldBase::begin(void) const
{
    return _values.begin();
}

inline
FieldContainerPtrMFieldBase::const_iterator 
    FieldContainerPtrMFieldBase::end(void) const
{
    return _values.end();
}

inline 
FieldContainerPtrMFieldBase::const_reverse_iterator
    FieldContainerPtrMFieldBase::rbegin(void) const
{
    return _values.rbegin();
}

inline 
FieldContainerPtrMFieldBase::const_reverse_iterator
    FieldContainerPtrMFieldBase::rend(void) const
{
    return _values.rend();
}

inline 
FieldContainerPtrMFieldBase::const_value
    FieldContainerPtrMFieldBase::front(void) const
{
    return _values.front();
}

inline 
FieldContainerPtrMFieldBase::const_value
    FieldContainerPtrMFieldBase::back(void) const
{
    return _values.back();
}

inline
bool FieldContainerPtrMFieldBase::empty(void) const
{
    return _values.empty();
}

inline
FieldContainerPtrMFieldBase::size_type 
    FieldContainerPtrMFieldBase::size(void) const
{
    return _values.size();
}

inline 
FieldContainerPtrMFieldBase::size_type
    FieldContainerPtrMFieldBase::max_size(void) const
{
    return _values.max_size();
}

inline
FieldContainerPtrMFieldBase::size_type
    FieldContainerPtrMFieldBase::capacity(void) const
{
    return _values.capacity();
}


inline
Int32 FieldContainerPtrMFieldBase::findIndex(const_value value) const
{
    const_iterator it = std::find(_values.begin(), _values.end(), value);

    if(it != _values.end())
    {
        return it - _values.begin();
    }
    else
    {
        return -1;
    }
}


inline
FieldContainerPtrMFieldBase::const_value 
    FieldContainerPtrMFieldBase::operator [](UInt32 index) const
{
    return _values[index];
}

inline 
FieldContainerPtrMFieldBase::const_value 
    FieldContainerPtrMFieldBase::at(UInt32 const index) const
{
    return _values.at(index);
}

inline
bool FieldContainerPtrMFieldBase::operator ==(const Self &source) const
{
    return _values == source._values;
}

#ifdef OSG_MT_CPTR_ASPECT
inline
void FieldContainerPtrMFieldBase::beginEdit(UInt32              ,
                                            AspectOffsetStore  &)
{
}

inline
FieldContainerPtrMFieldBase::Self *
    FieldContainerPtrMFieldBase::resolveShare(UInt32              , 
                                              AspectOffsetStore  &)
{
    return NULL;
}

inline
void FieldContainerPtrMFieldBase::terminateShare(UInt32              , 
                                                 AspectOffsetStore  &)
{
    
}

inline
bool FieldContainerPtrMFieldBase::isShared(void)
{
    return false;
}
#endif


inline
FieldContainerPtrMFieldBase::FieldContainerPtrMFieldBase(void) :
     Inherited(),
    _values   ()
{
}

inline
FieldContainerPtrMFieldBase::~FieldContainerPtrMFieldBase(void)
{
}

OSG_END_NAMESPACE
