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
void FieldContainerPtrMFieldBase::clear(void)
{
    iterator       fieldIt  = _values.begin();
    const_iterator fieldEnd = _values.end  ();

    while(fieldIt != fieldEnd)
    {
        OSG::subRefX(*fieldIt);

        ++fieldIt;
    }

    _values.clear();
}

inline
Int32 FieldContainerPtrMFieldBase::findIndex(ArgumentType value) const
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
FieldContainerPtrMFieldBase::size_type 
    FieldContainerPtrMFieldBase::size(void) const
{
    return _values.size();
}

inline
FieldContainerPtrMFieldBase::size_type
    FieldContainerPtrMFieldBase::capacity(void) const
{
    return _values.capacity();
}

inline
bool FieldContainerPtrMFieldBase::empty(void) const
{
    return _values.empty();
}

inline
bool FieldContainerPtrMFieldBase::operator ==(const Self &source) const
{
    return _values == source._values;
}

inline
FieldContainerPtrMFieldBase::const_reference 
    FieldContainerPtrMFieldBase::operator [](UInt32 index) const
{
    return _values[index];
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
bool  FieldContainerPtrMFieldBase::isShared(void)
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
FieldContainerPtrMFieldBase::FieldContainerPtrMFieldBase(const Self &obj) :
     Inherited(obj        ),
    _values   (obj._values)
{
}

inline
FieldContainerPtrMFieldBase::FieldContainerPtrMFieldBase(const UInt32 size) :
     Inherited(),
    _values   ()
{
    _values.resize(size);
}

inline
FieldContainerPtrMFieldBase::~FieldContainerPtrMFieldBase(void)
{
}

inline
void FieldContainerPtrMFieldBase::push_back(ArgumentType value)
{
    OSG::addRefX(value);

    _values.push_back(value);
}

inline
void FieldContainerPtrMFieldBase::resize(size_t       newsize, 
                                         StoredType   t)
{
    _values.resize(newsize, t);
}

#ifdef OSG_MT_CPTR_ASPECT
inline
void FieldContainerPtrMFieldBase::syncWith(Self               &source, 
                                           ConstFieldMaskArg   syncMode,
                                           UInt32              uiSyncInfo,
                                           AspectOffsetStore  &oOffsets    )
{
    if(source.size() != 0)
    {
        _values.resize(source.size());

        Self::iterator sIt  = source._values.begin();
        Self::iterator sEnd = source._values.end  ();

        Self::iterator fIt  = _values.begin();
        
        while(sIt != sEnd)
        {
            (*fIt) = convertToCurrentAspect(*sIt);

            ++sIt;
            ++fIt;
        }
    }
    else
    {
        _values.clear();
    }
}
#endif

OSG_END_NAMESPACE
