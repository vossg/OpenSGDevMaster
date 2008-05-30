/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

OSG_BEGIN_NAMESPACE


/*! Check if the pixelFormat, dimension, bpp and data are valid (not null)
    with a single call.    
 */

inline 
bool Image::isValid(void) const
{ 
    return !_mfPixel.empty();
}

/*! returns the data size in bytes. 
 */
inline 
unsigned long Image::getSize(bool withMipmap,
                             bool withFrames,
                             bool withSides ) const
{ 
    return ( (calcMipmapSumSize((withMipmap ? getMipMapCount() : 1))) *
             (withSides  ? getSideCount () : 1                      ) *
             (withFrames ? getFrameCount() : 1                      ) ); 
}

/*! returns a data pointer for a single frame/mipmap chunk
 */

inline 
const UInt8 *Image::getData(UInt32 mipmapNum, 
                            UInt32 frameNum,
                            UInt32 sideNum ) const
{
    if(_mfPixel.empty())
        return NULL;

    const UInt8 *data = 
        (&(_mfPixel[0])           ) + 
        (sideNum  * getSideSize ()) +
        (frameNum * getFrameSize());
    
    if (mipmapNum)
    {
        data += calcMipmapSumSize(mipmapNum);
    }
  
    return data;
}

inline 
UInt8 *Image::editData(UInt32 mipmapNum, 
                       UInt32 frameNum,
                       UInt32 sideNum) 
{
    if(_mfPixel.empty())
        return NULL;

    editMField(PixelFieldMask, _mfPixel);

    UInt8 *data = 
        (&(_mfPixel[0])           ) + 
        (sideNum  * getSideSize ()) +
        (frameNum * getFrameSize());
    
    if (mipmapNum)
    {
        data += calcMipmapSumSize(mipmapNum);
    }
 
    return data;
}


/*! returns a data pointer for a single frame/mipmap chunk
 */

inline 
const UInt8 *Image::getDataFast(UInt32 mipmapNum, 
                                UInt32 frameNum,
                                UInt32 sideNum ) const
{
    const UInt8 *data = 
        (&(_mfPixel[0])           ) + 
        (sideNum  * getSideSize ()) +
        (frameNum * getFrameSize());
    
    data += _mipmapOffset[mipmapNum];
   
    return data;
}

inline 
UInt8 *Image::editDataFast(UInt32 mipmapNum, 
                           UInt32 frameNum,
                           UInt32 sideNum) 
{
    editMField(PixelFieldMask, _mfPixel);

    UInt8 *data = 
        (&(_mfPixel[0])           ) + 
        (sideNum  * getSideSize ()) +
        (frameNum * getFrameSize());
    
    data += _mipmapOffset[mipmapNum];
  
    return data;
}


#ifdef CHECK_GV
// Specialization for Image we need this to support VRML PixelTextures.
template <> inline
void SFImagePtr::pushValueByStr(const Char8 *str)
{
    if(getValue() != NullFC)
        getValue()->addValue(str);
}
#endif

OSG_END_NAMESPACE
