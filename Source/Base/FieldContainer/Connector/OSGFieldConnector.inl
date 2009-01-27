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


inline
BasicFieldConnector::BasicFieldConnector(BitVector bSrcMask,
                                         BitVector bDstMask) :
    _bSrcMask(bSrcMask),
    _bDstMask(bDstMask),
    _pDst    (NULL    )
{
}

inline
BasicFieldConnector::~BasicFieldConnector(void)
{
}

inline
void BasicFieldConnector::setTargetContainer(FieldContainer *pDst)
{
    _pDst = pDst;
}

inline
bool BasicFieldConnector::match(BitVector fieldMask)
{
    return (_bSrcMask & fieldMask) != 0;
}

inline
bool BasicFieldConnector::match(      BitVector       bSrcMask,
                                const FieldContainer *pDst,
                                      BitVector       bDstMask)
{
    bool returnValue = (_bSrcMask & bSrcMask) != 0;

    if(pDst != NULL)
    {
        returnValue &= (_pDst                  == pDst) &&
                       ((_bDstMask & bDstMask) != 0   );
    }

    return returnValue;
}

inline
FieldContainer *BasicFieldConnector::getDst(void) const
{
    return _pDst;
}

template <class FieldT> inline
SFieldConnector<FieldT>::SFieldConnector(const FieldT    *pSrcField,
                                               BitVector  bSrcMask,
                                               FieldT    *pDstField,
                                               BitVector  bDstMask) :
     Inherited(bSrcMask,
               bDstMask ),
    _pSrcField(pSrcField),
    _pDstField(pDstField)
{
}

template <class FieldT> inline
SFieldConnector<FieldT>::~SFieldConnector(void)
{
}



template <class FieldT> inline
MFieldConnector<FieldT>::MFieldConnector(const FieldT    *pSrcField,
                                               BitVector  bSrcMask,
                                               FieldT    *pDstField,
                                               BitVector  bDstMask) :
     Inherited(bSrcMask,
               bDstMask ),
    _pSrcField(pSrcField),
    _pDstField(pDstField)
{
}

template <class FieldT> inline
MFieldConnector<FieldT>::~MFieldConnector(void)
{
}

OSG_END_NAMESPACE
