/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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

template<class ValueT> inline
void swapImageByteOrder(ImagePtrConstArg pImage)
{
    if(pImage == NULL)
        return;

    ValueT *pData = reinterpret_cast<ValueT *>(pImage->editData());

    UInt32 uiSize = pImage->getSize() / sizeof(ValueT);

    for(UInt32 i = 0; i < uiSize; ++i)
    {
        pData[i] = osgSwapBytes<ValueT>(pData[i]);
    }
}

template<class ValueT, ValueT (*ConvF)(ValueT)> inline
void swapAndConvertImageByteOrder(ImagePtrConstArg pImage)
{
    if(pImage == NULL)
        return;

    ValueT *pData = reinterpret_cast<ValueT *>(pImage->editData());

    UInt32 uiSize = pImage->getSize() / sizeof(ValueT);

    for(UInt32 i = 0; i < uiSize; ++i)
    {
        pData[i] = ConvF(osgSwapBytes<ValueT>(pData[i]));
    }
}

template<class ValueT, ValueT MinVal> inline
ValueT clampMin(ValueT val)
{
    if(val < MinVal)
        val = MinVal;

    return val;
}

template<class ValueT, ValueT CompVal, ValueT ReplaceVal> inline
ValueT clampMin(ValueT val)
{
    if(val < CompVal)
        val = ReplaceVal;

    return val;
}

template<class ValueT> inline
ValueT doNothing(ValueT val)
{
    return val;
}

OSG_END_NAMESPACE
