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

template<class SrcImageStore> inline
bool createComposedImage (const SrcImageStore &imageVec,
                                Image         *image,
                                SliceDataType  sliceDataType,
                                bool           flipY        )
{
    UInt32 dataSize, i, n = imageVec.size();
    Int32 w = 0;
    Int32 h = 0;
    UInt8 *destData;
    const UInt8 *srcData;
    Image::PixelFormat pf = Image::OSG_INVALID_PF;
    Image::Type        dt = Image::OSG_INVALID_IMAGEDATATYPE;
    bool needColor = false, needAlpha = false, needCopy = false;
    ImageUnrecPtr copy = Image::create();
    UInt32 depth, frameCount, sideCount;

    if (n) 
    {
        for (i = 0; i < n; i++) 
        {
            if ( i == 0 ) 
            {
                pf = Image::PixelFormat(imageVec[0]->getPixelFormat());
                dt = Image::Type(imageVec[0]->getDataType());
                w = imageVec[0]->getWidth();
                h = imageVec[0]->getHeight();
                needAlpha = imageVec[0]->hasAlphaChannel();
                needColor = imageVec[0]->hasColorChannel();
            }
            else 
            {
                needAlpha |= imageVec[i]->hasAlphaChannel();
                needColor |= imageVec[i]->hasColorChannel();
                if (Image::PixelFormat(imageVec[i]->getPixelFormat()) != pf) 
                {
                    needCopy = true;          
                    FWARNING (( "Image has different PF while composing\n" ));
                    pf = Image::OSG_INVALID_PF;
                }
                if (Image::Type(imageVec[i]->getDataType()) != dt) 
                {
                    needCopy = true;          
                    FWARNING (( "Image has different DT while composing\n" ));
                    dt = Image::OSG_INVALID_IMAGEDATATYPE;
                }
                if (imageVec[i]->getWidth() != w) 
                {
                    needCopy = true;          
                    FWARNING(("Image has different width while composing\n"));
                    w = osgMax ( w, imageVec[i]->getWidth());
                }
                if (imageVec[i]->getHeight() != h) 
                {
                    needCopy = true;          
                    FWARNING(("Image has different height while composing\n"));
                    h = osgMax ( h, imageVec[i]->getHeight());
                }
            }      
        }

        if (pf == Image::OSG_INVALID_PF) 
        {
            if (needColor)
                if (needAlpha)
                    pf = OSG::Image::OSG_RGBA_PF;
                else
                    pf = OSG::Image::OSG_RGB_PF;
            else
                if (needAlpha)
                    pf = OSG::Image::OSG_LA_PF;
                else
                    pf = OSG::Image::OSG_L_PF;
        }

        if (dt == Image::OSG_INVALID_IMAGEDATATYPE)
            dt = Image::OSG_UINT8_IMAGEDATA;

        depth = frameCount = sideCount = 1;
        switch (sliceDataType) 
        {
            case FRAME_SDT:
                frameCount = n;
                break;
            case SIDE_SDT:
                sideCount = n;
                break;
            case INVALID_SDT:
            case DEPTH_SDT:
            default:
                depth = n;
                break;
        }
      
        image->set( pf, w, h, depth, 1, frameCount, 0.0, 
                    0, dt, true, sideCount );

        destData   = image->editData();
        dataSize   = image->getSize() / n;
        UInt32 bpl = dataSize / h;
 

        if (needCopy) 
        {
            FLOG (("Image data/type/size missmatch while composing\n"));
        }

        for (i = 0; i < n; i++) 
        {
            if (needCopy) 
            {
                copy->set(imageVec[i]);
                if ( Image::PixelFormat(copy->getPixelFormat()) != pf )
                    copy->reformat(pf);
                if ( Image::Type(copy->getDataType()) != dt )
                    copy->convertDataTypeTo(dt);
                if ( (w != copy->getWidth()) || (h != copy->getHeight()))
                    copy->scale(w,h,copy->getDepth());
                srcData = copy->getData();
            }
            else 
            {
                srcData = imageVec[i]->getData();
            }

            if (flipY == true)
            {
                srcData += dataSize;
                for (UInt32 y = 0; y < h; ++y)
                {
                    srcData -= bpl;
                    memcpy ( destData, srcData, bpl );
                    destData += bpl;
                }
            }
            else
            {
                memcpy ( destData, srcData, dataSize );
                destData += dataSize;
            }
        }
    }

    imageVec[0]->dump();
    image->dump();

    return true;
}

template<class ValueT> inline
void swapImageByteOrder(Image * const pImage)
{
    if(pImage == NULL)
        return;

    void   *pData  = static_cast<void *>(pImage->editData());
    UInt32  uiSize = pImage->getSize() / sizeof(ValueT);

    osgSwapMem<sizeof(ValueT)>(pData, uiSize);
}

template<class ValueT, ValueT (*ConvF)(ValueT)> inline
void swapAndConvertImageByteOrder(Image * const pImage)
{
    if(pImage == NULL)
        return;

    ValueT *pData  = reinterpret_cast<ValueT *>(pImage->editData());
    UInt32  uiSize = pImage->getSize() / sizeof(ValueT);

    for(UInt32 i = 0; i < uiSize; ++i)
    {
        osgSwapMem<sizeof(ValueT)>(&pData[i], 1);
        pData[i] = ConvF(pData[i]);
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
