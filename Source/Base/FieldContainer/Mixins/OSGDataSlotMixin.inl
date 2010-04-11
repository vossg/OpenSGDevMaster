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
ValuePtr DataSlotMixin<ParentT>::getData(Int32 iSlotId) const
{
    ValuePtr returnValue = NULL;

    if(iSlotId >= 0 && static_cast<UInt32>(iSlotId) < _mfData.size())
    {
        FieldContainer *pTmp = _mfData[iSlotId];

        returnValue = dynamic_cast<ValuePtr>(pTmp);
    }

    return returnValue;
}

template <class ParentT> inline
void DataSlotMixin<ParentT>::setData(FieldContainer *pData, Int32 iSlotId)
{
    if(iSlotId < 0)
        return;

    if(_mfData.size() <= static_cast<UInt32>(iSlotId))
    {
        _mfData.resize(iSlotId + 1, NULL);
    }

    _mfData.replace(iSlotId, pData);
}

template <class ParentT> inline
void DataSlotMixin<ParentT>::dumpStore(void)
{
    for(UInt32 i = 0; i < _mfData.size(); ++i)
    {
        fprintf(stderr, "(%d) : ", i);
        Desc::dumpElement(_mfData[i]);
        fprintf(stderr, "\n");
    }
}

template <class ParentT> inline
void DataSlotMixin<ParentT>::clearData(FieldContainer    *pContainer, 
                                       ConstFieldMaskArg  whichField,
                                       Int32              iSlotId)
{
    fprintf(stderr, "Clear Data %p %d\n",
            pContainer,
            iSlotId);

    if(iSlotId < 0)
        return;

    if(_mfData.size() > static_cast<UInt32>(iSlotId))
    {
        _mfData.replace(iSlotId, NULL);
    }

    typename DestroyFunctorStore::iterator       cfIt = 
        _mfDestroyedFunctors.begin();

    typename DestroyFunctorStore::const_iterator cfEnd= 
        _mfDestroyedFunctors.end();

    while(cfIt != cfEnd)
    {
        if((*cfIt).second == pContainer)
        {
            cfIt  = _mfDestroyedFunctors.erase(cfIt);
            cfEnd = _mfDestroyedFunctors.end();
        }
        else
        {
            ++cfIt;
        }
    }
}

template <class ParentT> inline
DataSlotMixin<ParentT>::DataSlotMixin(void) :
     Inherited          (),
    _mfData             (),
    _mfDestroyedFunctors()
{
}

template <class ParentT> inline
DataSlotMixin<ParentT>::DataSlotMixin(const DataSlotMixin &source) :
     Inherited          (source),
    _mfData             (      ),
    _mfDestroyedFunctors(      )
{
}

template <class ParentT> inline
void DataSlotMixin<ParentT>::addDestroyedFunctorFor(      DestroyFunctor  func,
                                                    const FieldContainer *pCnt)
{
    DestroyedFunctorElem tmpElem;

    tmpElem.first  = func;
    tmpElem.second = pCnt;

    _mfDestroyedFunctors.push_back(tmpElem);
}

template <class ParentT> inline
DataSlotMixin<ParentT>::~DataSlotMixin(void)
{
    for(UInt32 i = 0; i < _mfData.size(); ++i)
    {
        _mfData.replace(i, NULL);
    }

    for(UInt32 i = 0; i < _mfDestroyedFunctors.size(); ++i)
    {
        fprintf(stderr, "DF (%d) (%p)\n",
                i, this);

        (_mfDestroyedFunctors[i].first)(this);
    }
}

OSG_END_NAMESPACE


