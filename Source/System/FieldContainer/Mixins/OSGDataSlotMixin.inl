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

template <class ParentT>
template <class ValuePtr>  inline
ValuePtr DataSlotMixin<ParentT>::getData(Int32 iSlotId)
{
    ValuePtr returnValue = NULL;

    if(iSlotId >= 0 && static_cast<UInt32>(iSlotId) < _mfData.size())
    {
        FieldBundleP pTmp = _mfData[iSlotId];

        returnValue = dynamic_cast<ValuePtr>(pTmp);
    }

    return returnValue;
}

template <class ParentT> inline
void DataSlotMixin<ParentT>::setDataX(FieldBundleP pBundle, Int32 iSlotId)
{
    if(iSlotId < 0)
        return;

    if(static_cast<UInt32>(iSlotId) <= _mfData.size())
    {
        _mfData.resize(iSlotId + 1, NULL);
    }

    OSG::setRefd(_mfData[iSlotId], pBundle);
}

template <class ParentT> inline
DataSlotMixin<ParentT>::DataSlotMixin(void) :
     Inherited(),
    _mfData   ()
{
}

template <class ParentT> inline
DataSlotMixin<ParentT>::DataSlotMixin(const DataSlotMixin &source) :
     Inherited(source),
    _mfData   (      )
{
}

template <class ParentT> inline
DataSlotMixin<ParentT>::~DataSlotMixin(void)
{
    for(UInt32 i = 0; i < _mfData.size(); ++i)
    {
        OSG::subRef(_mfData[i]);
    }
}

OSG_END_NAMESPACE


