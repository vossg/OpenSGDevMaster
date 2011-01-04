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
//-------------------------------
// Includes
//-------------------------------

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#include "OSGBMPImageFileType.h"
#include "OSGLog.h"

#include <iostream>

OSG_BEGIN_NAMESPACE

/*! \class BMPImageFileType

Image File Type to read/write and store/restore Image objects as
BMP data.

All the type specific code is included in the class. Does
not depend on external libs.

@author Patrick D&auml;hne
*/


namespace
{
    UInt32 parseUInt32(char *&ptr)
    {
        UInt32 result =
            (static_cast<UInt32>(static_cast<UInt8>(ptr[0])) <<  0) |
            (static_cast<UInt32>(static_cast<UInt8>(ptr[1])) <<  8) |
            (static_cast<UInt32>(static_cast<UInt8>(ptr[2])) << 16) |
            (static_cast<UInt32>(static_cast<UInt8>(ptr[3])) << 24);
        ptr += 4;
        return result;
    }

    UInt16 parseUInt16(char *&ptr)
    {
        UInt16 result =
            (static_cast<UInt32>(static_cast<UInt8>(ptr[0])) << 0) |
            (static_cast<UInt32>(static_cast<UInt8>(ptr[1])) << 8);
        ptr +=2;
        return result;
    }

    struct OSGBITMAPFILEHEADER
    {
        Int8   bfType[2];
        UInt32 bfSize;
        UInt16 bfReserved1;
        UInt16 bfReserved2;
        UInt32 bfOffBits;
    };

    struct OSGBITMAPINFOHEADER
    {
        UInt32 biSize;
        UInt32 biWidth;
        Int32  biHeight; // Not a typo - height can be negative
        UInt16 biPlanes;
        UInt16 biBitCount;
        UInt32 biCompression;
        UInt32 biSizeImage;
        UInt32 biXPelsPerMeter;
        UInt32 biYPelsPerMeter;
        UInt32 biClrUsed;
        UInt32 biClrImportant;
        UInt32 redMask;
        UInt32 greenMask;
        UInt32 blueMask;
        UInt32 alphaMask;
    };

    struct RGB
    {
        UInt8 r, g, b;
    };

    bool readBitmapFileHeader(std::istream &is, OSGBITMAPFILEHEADER &header)
    {
        // Read the header
        char buffer[14];
        is.read(buffer, 14);
        if (is.gcount() != 14)
            return false;

        // Parse the header
        char *ptr = buffer;
        memcpy(header.bfType, ptr, 2);
        ptr += 2;
        header.bfSize = parseUInt32(ptr);
        header.bfReserved1 = parseUInt16(ptr);
        header.bfReserved2 = parseUInt16(ptr);
        header.bfOffBits = parseUInt32(ptr);

        // Check the header
        if (memcmp(header.bfType, "BM", 2) != 0)
            return false;

        return true;
    }

    bool readBitmapInfoHeader(std::istream &is, OSGBITMAPINFOHEADER &infoHeader)
    {
        // Determine size of the header
        char buffer[56];
        is.read(buffer, 4);
        if (is.gcount() != 4)
            return false;
        char *ptr = buffer;
        infoHeader.biSize = parseUInt32(ptr);

        infoHeader.redMask   = 0;
        infoHeader.greenMask = 0;
        infoHeader.blueMask  = 0;
        infoHeader.alphaMask = 0;

        // Parse the header
        if (infoHeader.biSize >= 40)
        {
            // Read the remaining header
            int size = infoHeader.biSize >= 56 ? 56 - 4 : 40 - 4;
            is.read(&(buffer[4]), size);
            if (is.gcount() != size)
                return false;

            infoHeader.biWidth = parseUInt32(ptr);
            infoHeader.biHeight = parseUInt32(ptr);
            infoHeader.biPlanes = parseUInt16(ptr);
            infoHeader.biBitCount = parseUInt16(ptr);
            infoHeader.biCompression = parseUInt32(ptr);
            infoHeader.biSizeImage = parseUInt32(ptr);
            infoHeader.biXPelsPerMeter = parseUInt32(ptr);
            infoHeader.biYPelsPerMeter = parseUInt32(ptr);
            infoHeader.biClrUsed = parseUInt32(ptr);
            infoHeader.biClrImportant = parseUInt32(ptr);

            if ((infoHeader.biSize >= 56) && (infoHeader.biCompression == 3 /*BI_BITFIELDS*/))
            {
                infoHeader.redMask = parseUInt32(ptr);
                infoHeader.greenMask = parseUInt32(ptr);
                infoHeader.blueMask = parseUInt32(ptr);
                infoHeader.alphaMask = parseUInt32(ptr);
            }
            else
                infoHeader.alphaMask = 0;

            is.ignore(infoHeader.biSize - size - 4);
        }
        else if (infoHeader.biSize >= 12)
        {
            // Read the remaining header
            is.read(&(buffer[4]), 12 - 4);
            if (is.gcount() != 12 - 4)
                return false;

            infoHeader.biWidth = parseUInt16(ptr);
            infoHeader.biHeight = parseUInt16(ptr);
            infoHeader.biPlanes = parseUInt16(ptr);
            infoHeader.biBitCount = parseUInt16(ptr);
            infoHeader.biCompression = 0;
            infoHeader.biSizeImage = 0;
            infoHeader.biXPelsPerMeter = 0;
            infoHeader.biYPelsPerMeter = 0;
            infoHeader.biClrUsed = 0;
            infoHeader.biClrImportant = 0;

            is.ignore(infoHeader.biSize - 12);
        }
        else
            return false;

        // Check header
        if ((infoHeader.biBitCount !=  1) &&
            (infoHeader.biBitCount !=  4) &&
            (infoHeader.biBitCount !=  8) &&
            (infoHeader.biBitCount != 16) &&
            (infoHeader.biBitCount != 24) &&
            (infoHeader.biBitCount != 32))
            return false;
        if (infoHeader.biPlanes !=  1)
            return false;
        if ((infoHeader.biBitCount ==  1) && (infoHeader.biCompression != 0 /*BI_RGB*/))
            return false;
        if ((infoHeader.biBitCount ==  4) && (infoHeader.biCompression != 0 /*BI_RGB*/) &&
            (infoHeader.biCompression != 2 /*BI_RLE4*/))
            return false;
        if ((infoHeader.biBitCount ==  8) && (infoHeader.biCompression != 0 /*BI_RGB*/) &&
            (infoHeader.biCompression != 1 /*BI_RLE8*/))
            return false;
        if ((infoHeader.biBitCount == 16) && (infoHeader.biCompression != 0 /*BI_RGB*/) &&
            (infoHeader.biCompression != 3 /*BI_BITFIELDS*/))
            return false;
        if ((infoHeader.biBitCount == 24) && (infoHeader.biCompression != 0 /*BI_RGB*/))
            return false;
        if ((infoHeader.biBitCount == 32) && (infoHeader.biCompression != 0 /*BI_RGB*/) &&
            (infoHeader.biCompression != 3 /*BI_BITFIELDS*/))
            return false;

        if (infoHeader.biSize < 56)
        {
            if (infoHeader.biCompression == 3 /*BI_BITFIELDS*/)
            {
                is.read(buffer, 12);
                if (is.gcount() != 12)
                    return false;
                ptr = buffer;
                infoHeader.redMask = parseUInt32(ptr);
                infoHeader.greenMask = parseUInt32(ptr);
                infoHeader.blueMask = parseUInt32(ptr);
                infoHeader.alphaMask = 0;
                infoHeader.biSize += 12;
            }
            else if (infoHeader.biBitCount == 16)
            {
                infoHeader.redMask = 0x7c00;
                infoHeader.greenMask = 0x03e0;
                infoHeader.blueMask = 0x001f;
                infoHeader.alphaMask = 0;
            }
            else if (infoHeader.biBitCount == 32)
            {
                infoHeader.redMask = 0x00ff0000;
                infoHeader.greenMask = 0x0000ff00;
                infoHeader.blueMask = 0x000000ff;
                infoHeader.alphaMask = 0xff000000;
            }
        }

#if 0
        std::cout << "infoHeader.biSize = " << infoHeader.biSize << std::endl;
        std::cout << "infoHeader.biWidth = " << infoHeader.biWidth << std::endl;
        std::cout << "infoHeader.biHeight = " << infoHeader.biHeight << std::endl;
        std::cout << "infoHeader.biPlanes = " << infoHeader.biPlanes << std::endl;
        std::cout << "infoHeader.biBitCount = " << infoHeader.biBitCount << std::endl;
        std::cout << "infoHeader.biCompression = " << infoHeader.biCompression << std::endl;
#endif

        return true;
    }

    bool readColorMap(std::istream &is, const OSGBITMAPFILEHEADER &fileHeader,
                      const OSGBITMAPINFOHEADER &infoHeader, RGB colorMap[256])
    {
        if (infoHeader.biBitCount <= 8)
        {
            UInt32 nCols = 1 << infoHeader.biBitCount;
            if (infoHeader.biClrUsed > 0)
            {
                if (infoHeader.biClrUsed > nCols)
                    return false;
                nCols = infoHeader.biClrUsed;
            }
            int bytesPerColor = (infoHeader.biSize < 40) || (infoHeader.biSize + 14 + 4 * nCols > fileHeader.bfOffBits)
                ? 3 : 4;
            char buffer[256 * 4];
            is.read(buffer, nCols * bytesPerColor);
            if (static_cast<UInt32>(is.gcount()) != nCols * bytesPerColor)
                return false;
            char *ptr = buffer;
            for (UInt32 i = 0; i < nCols; ++i)
            {
                colorMap[i].r = ptr[2];
                colorMap[i].g = ptr[1];
                colorMap[i].b = ptr[0];
                ptr += bytesPerColor;
            }
        }

        return true;
    }

    bool parseUncompressedPaletteImage(std::istream &is, const OSGBITMAPINFOHEADER &infoHeader,
                                       const RGB colorMap[256], Image* image)
    {
        unsigned long mask = (1 << infoHeader.biBitCount) - 1;
        int height;
        long bytesPerLine;
        UChar8 *data;
        if (infoHeader.biHeight >= 0)
        {
            height = infoHeader.biHeight;
            bytesPerLine = infoHeader.biWidth * 3;
            data = image->editData();
        }
        else
        {
            height = -infoHeader.biHeight;
            bytesPerLine = infoHeader.biWidth * -3;
            data = image->editData() + image->getSize() + bytesPerLine;
        }

        for (int y = 0; y < height; ++y)
        {
            int shift = 0;
            unsigned long bits = 0;
            UChar8 *ptr = data;
            for (unsigned int x = 0; x < infoHeader.biWidth; ++x)
            {
                if (shift == 0)
                {
                    char buffer[4];
                    is.read(buffer, 4);
                    if (is.gcount() != 4)
                        return false;
                    bits = (static_cast<UInt32>(static_cast<UInt8>(buffer[0])) << 24) |
                        (static_cast<UInt32>(static_cast<UInt8>(buffer[1])) << 16) |
                        (static_cast<UInt32>(static_cast<UInt8>(buffer[2])) <<  8) |
                        (static_cast<UInt32>(static_cast<UInt8>(buffer[3])) <<  0);
                    shift = 32 - infoHeader.biBitCount;
                }
                else
                    shift -= infoHeader.biBitCount;
                unsigned long index = (bits >> shift) & mask;
                *ptr++ = colorMap[index].r;
                *ptr++ = colorMap[index].g;
                *ptr++ = colorMap[index].b;
            }
            data += bytesPerLine;
        }

        return true;
    }

    bool parseRLEImage(std::istream &is, const OSGBITMAPINFOHEADER &infoHeader, const RGB colorMap[256], Image* image)
    {
        unsigned int height;
        long bytesPerLine;
        UChar8 *data;
        if (infoHeader.biHeight >= 0)
        {
            height = infoHeader.biHeight;
            bytesPerLine = infoHeader.biWidth * 3;
            data = image->editData();
        }
        else
        {
            height = -infoHeader.biHeight;
            bytesPerLine = infoHeader.biWidth * -3;
            data = image->editData() + image->getSize() + bytesPerLine;
        }

        UChar8 *ptr = data;
        unsigned int x = 0;
        for (unsigned int y = 0; y < height; )
        {
            int c1 = is.get();
            int c2 = is.get();
            if ((c1 == EOF) || (c2 == EOF))
                return false;
            if (c1 == 0) // Escape
            {
                switch (c2)
                {
                case 0: // End of line
                    x = 0;
                    ++y;
                    data += bytesPerLine;
                    ptr = data;
                    break;
                case 1: // End of bitmap
                    y = height;
                    break;
                case 2: // Delta
                {
                    int xOffset = is.get();
                    int yOffset = is.get();
                    if ((xOffset == EOF) || (yOffset == EOF))
                        return false;
                    x += xOffset;
                    y += yOffset;
                    if ((x >= infoHeader.biWidth) || (y >= height))
                        return false;
                    data += bytesPerLine * yOffset;
                    ptr += bytesPerLine * yOffset + 3 * xOffset;
                }
                break;
                default: // Absolute mode
                    if (infoHeader.biWidth - x < static_cast<unsigned int>(c2))
                        c2 = infoHeader.biWidth - x;
                    x += c2;
                    if (infoHeader.biBitCount == 4)
                    {
                        int n = c2;
                        for (int i = 0; i < n; ++i)
                        {
                            int index;
                            switch (i & 3)
                            {
                            case 0:
                                c1 = is.get();
                                c2 = is.get();
                                if ((c1 == EOF) || (c2 == EOF))
                                    return false;
                                index = c1 >> 4;
                                break;
                            case 1:
                                index = c1 & 0xf;
                                break;
                            case 2:
                                index = c2 >> 4;
                                break;
                            case 3:
                                index = c2 & 0xf;
                                break;
                            default:
                                index = 0; // Just to get rid of compiler warnings...
                                break;
                            }
                            *ptr++ = colorMap[index].r;
                            *ptr++ = colorMap[index].g;
                            *ptr++ = colorMap[index].b;
                        }
                    }
                    else
                        for (int i = 0; i < c2; ++i)
                        {
                            int index;
                            if ((i & 1) == 0)
                            {
                                index = is.get();
                                c1 = is.get();
                                if ((index == EOF) || (c1 == EOF))
                                    return false;
                            }
                            else
                                index = c1;
                            *ptr++ = colorMap[index].r;
                            *ptr++ = colorMap[index].g;
                            *ptr++ = colorMap[index].b;
                        }
                    break;
                }
            }
            else // Encoded mode
            {
                if (infoHeader.biWidth - x < static_cast<unsigned int>(c1))
                    c1 = infoHeader.biWidth - x;
                x += c1;
                if (infoHeader.biBitCount == 4)
                    for (int i = 0; i < c1; ++i)
                    {
                        int index = (i & 1) == 0 ? c2 >> 4 : c2 & 0xf;
                        *ptr++ = colorMap[index].r;
                        *ptr++ = colorMap[index].g;
                        *ptr++ = colorMap[index].b;
                    }
                else
                    for (int i = 0; i < c1; ++i)
                    {
                        *ptr++ = colorMap[c2].r;
                        *ptr++ = colorMap[c2].g;
                        *ptr++ = colorMap[c2].b;
                    }
            }
        }

        return true;
    }

    int calcShift(UInt32 mask)
    {
        if (mask == 0)
            return 0;
        int shift = 0;
        while (mask > 255)
        {
            ++shift;
            mask >>= 1;
        }
        return shift;
    }

    bool parseTrueColorImage(std::istream &is, const OSGBITMAPINFOHEADER &infoHeader, Image* image)
    {
        int redShift = calcShift(infoHeader.redMask);
        int redScale = infoHeader.redMask == 0 ? 0 : 255 / (infoHeader.redMask >> redShift);
        int greenShift = calcShift(infoHeader.greenMask);
        int greenScale = infoHeader.greenMask == 0 ? 0 : 255 / (infoHeader.greenMask >> greenShift);
        int blueShift = calcShift(infoHeader.blueMask);
        int blueScale = infoHeader.blueMask == 0 ? 0 : 255 / (infoHeader.blueMask >> blueShift);
        int alphaShift = calcShift(infoHeader.alphaMask);
        int alphaScale = infoHeader.alphaMask == 0 ? 0 : 255 / (infoHeader.alphaMask >> alphaShift);

        int height;
        long bytesPerLine = infoHeader.biWidth * (infoHeader.alphaMask != 0 ? 4 : 3);
        UChar8 *data;
        if (infoHeader.biHeight >= 0)
        {
            height = infoHeader.biHeight;
            data = image->editData();
        }
        else
        {
            height = -infoHeader.biHeight;
            bytesPerLine = -bytesPerLine;
            data = image->editData() + image->getSize() + bytesPerLine;
        }

        for (int y = 0; y < height; ++y)
        {
            int shift = 32;
            unsigned long bits = 0;
            UChar8 *ptr = data;
            for (unsigned int x = 0; x < infoHeader.biWidth; ++x)
            {
                if (shift >= 32)
                {
                    char buffer[4];
                    is.read(buffer, 4);
                    if (is.gcount() != 4)
                        return false;
                    bits = (static_cast<UInt32>(static_cast<UInt8>(buffer[0])) <<  0) |
                        (static_cast<UInt32>(static_cast<UInt8>(buffer[1])) <<  8) |
                        (static_cast<UInt32>(static_cast<UInt8>(buffer[2])) << 16) |
                        (static_cast<UInt32>(static_cast<UInt8>(buffer[3])) << 24);
                    shift = 0;
                }
                unsigned long color = bits >> shift;
                *ptr++ = static_cast<UChar8>(((color & infoHeader.redMask) >> redShift) * redScale);
                *ptr++ = static_cast<UChar8>(((color & infoHeader.greenMask) >> greenShift) * greenScale);
                *ptr++ = static_cast<UChar8>(((color & infoHeader.blueMask) >> blueShift) * blueScale);
                if (infoHeader.alphaMask != 0)
                    *ptr++ = static_cast<UChar8>(((color & infoHeader.alphaMask) >> alphaShift) * alphaScale);
                shift += infoHeader.biBitCount;
            }
            data += bytesPerLine;
        }

        return true;
    }

    bool parse24bitImage(std::istream &is, const OSGBITMAPINFOHEADER &infoHeader, Image* image)
    {
        int height;
        long bytesPerLine;
        UChar8 *data;
        if (infoHeader.biHeight >= 0)
        {
            height = infoHeader.biHeight;
            bytesPerLine = infoHeader.biWidth * 3;
            data = image->editData();
        }
        else
        {
            height = -infoHeader.biHeight;
            bytesPerLine = infoHeader.biWidth * -3;
            data = image->editData() + image->getSize() + bytesPerLine;
        }
        int padding = (infoHeader.biWidth * 3) & 3;
        if (padding != 0)
            padding = 4 - padding;

        for (int y = 0; y < height; ++y)
        {
            UChar8 *ptr = data;
            for (unsigned int x = 0; x < infoHeader.biWidth; ++x)
            {
                char buffer[3];
                is.read(buffer, 3);
                if (is.gcount() != 3)
                    return false;
                *ptr++ = buffer[2];
                *ptr++ = buffer[1];
                *ptr++ = buffer[0];
            }
            is.ignore(padding);
            data += bytesPerLine;
        }

        return true;
    }

// -----------------------------------------
// write stuff
// -----------------------------------------

    void u_short_int_write(unsigned short int u_short_int_val,
                           std::ostream &os);

// fixme
    bool _bmp_byte_swap = true;

    void long_int_write ( long int long_int_val, std::ostream &os)
    {
        long int temp;
        unsigned short int u_short_int_val_hi;
        unsigned short int u_short_int_val_lo;

        temp = long_int_val / 65536;
        if(temp < 0)
            temp = temp + 65536;

        u_short_int_val_hi = static_cast<unsigned short>(temp);

        temp = long_int_val % 65536;
        if(temp < 0)
            temp = temp + 65536;

        u_short_int_val_lo = static_cast<unsigned short>(temp);

        if(_bmp_byte_swap)
        {
            u_short_int_write ( u_short_int_val_lo, os);
            u_short_int_write ( u_short_int_val_hi, os);
        }
        else
        {
            u_short_int_write ( u_short_int_val_hi, os);
            u_short_int_write ( u_short_int_val_lo, os);
        }
        return;
    }

    void u_long_int_write(unsigned long int u_long_int_val,
                          std::ostream &os)
    {
        unsigned short int u_short_int_val_hi;
        unsigned short int u_short_int_val_lo;

        u_short_int_val_hi = static_cast<unsigned short>( u_long_int_val / 65536 );
        u_short_int_val_lo = static_cast<unsigned short>( u_long_int_val % 65536 );

        if(_bmp_byte_swap)
        {
            u_short_int_write ( u_short_int_val_lo, os);
            u_short_int_write ( u_short_int_val_hi, os);
        }
        else
        {
            u_short_int_write ( u_short_int_val_hi, os);
            u_short_int_write ( u_short_int_val_lo, os);
        }

        return;
    }

    void u_short_int_write(unsigned short int u_short_int_val,
                           std::ostream &os)
    {
        unsigned char chi;
        unsigned char clo;

        chi = static_cast<unsigned char>( u_short_int_val / 256 );
        clo = static_cast<unsigned char>( u_short_int_val % 256 );

        if(_bmp_byte_swap)
            os << clo << chi;
        else
            os << chi << clo;

        return;
    }

    void bmp_header1_write(std::ostream &os, unsigned short int filetype,
                           unsigned long int filesize, unsigned short int reserved1,
                           unsigned short int reserved2, unsigned long int bitmapoffset)
    {
        u_short_int_write(filetype, os);
        u_long_int_write(filesize, os);
        u_short_int_write(reserved1, os);
        u_short_int_write(reserved2, os);
        u_long_int_write(bitmapoffset, os);
        return;
    }

    void bmp_header2_write(std::ostream &os, unsigned long int size,
                           unsigned long int width, long int height,
                           unsigned short int planes, unsigned short int bitsperpixel,
                           unsigned long int compression, unsigned long int sizeofbitmap,
                           unsigned long int horzresolution, unsigned long int vertresolution,
                           unsigned long int colorsused, unsigned long int colorsimportant)

    //****************************************************************************
    //
    //    4 bytes SIZE;                Size of this header, in bytes.
    //    4 bytes WIDTH;               Image width, in pixels.
    //    4 bytes HEIGHT;              Image height, in pixels.
    //                                 (Pos/Neg, origin at bottom, top)
    //    2 bytes PLANES;              Number of color planes (always 1).
    //    2 bytes BITSPERPIXEL;        1 to 24.  1, 4, 8, 16, 24 or 32.
    //    4 bytes COMPRESSION;         0, uncompressed; 1, 8 bit RLE;
    //                                 2, 4 bit RLE; 3, bitfields.
    //    4 bytes SIZEOFBITMAP;        Size of bitmap in bytes. (0 if uncompressed).
    //    4 bytes HORZRESOLUTION;      Pixels per meter. (Can be zero)
    //    4 bytes VERTRESOLUTION;      Pixels per meter. (Can be zero)
    //    4 bytes COLORSUSED;          Number of colors in palette.  (Can be zero).
    //    4 bytes COLORSIMPORTANT.     Minimum number of important colors. (Can be zero).
    //
    //  Parameters:
    //
    //    Input, ofstream &FILE_OUT, a reference to the output file.
    //
    //    Input, unsigned long int SIZE, the size of this header in bytes.
    //
    //    Input, unsigned long int WIDTH, the X dimensions of the image.
    //
    //    Input, long int HEIGHT, the Y dimensions of the image.
    //
    //    Input, unsigned short int PLANES, the number of color planes.
    //
    //    Input, unsigned short int BITSPERPIXEL, color bits per pixel.
    //
    //    Input, unsigned long int COMPRESSION, the compression option.
    //
    //    Input, unsigned long int SIZEOFBITMAP, the size of the bitmap.
    //
    //    Input, unsigned long int HORZRESOLUTION, the horizontal resolution.
    //
    //    Input, unsigned long int VERTRESOLUTION, the vertical resolution.
    //
    //    Input, unsigned long int COLORSUSED, the number of colors in the palette.
    //
    //    Input, unsigned long int COLORSIMPORTANT, the minimum number of colors.
    //
    {
        u_long_int_write(size, os);
        u_long_int_write(width, os);
        long_int_write(height, os);
        u_short_int_write(planes, os);
        u_short_int_write(bitsperpixel, os);
        u_long_int_write(compression, os);
        u_long_int_write(sizeofbitmap, os);
        u_long_int_write(horzresolution, os);
        u_long_int_write(vertresolution, os);
        u_long_int_write(colorsused, os);
        u_long_int_write(colorsimportant, os);
        return;
    }

    void bmp_24_data_write(std::ostream &os, unsigned long int width,
                           long int height, const unsigned char *data)
    {
        int padding;

        //  Set the padding.
        padding = ( 4 - ( ( 3 * width ) % 4 ) ) % 4;

        for(long j = 0; j < abs ( height ); ++j)
        {
            for(unsigned long i = 0; i < width; ++i)
            {
                os << *(data + 2);
                os << *(data + 1);
                os << *(data + 0);
                data += 3;
            }

            for(int i = 0; i < padding; ++i)
            {
                os << 0;
            }
        }
        return;
    }

// -----------

    // Static Class Variable implementations:
    const Char8 *suffixArray[] =
    {
        "bmp", "dib", "rle"
    };

} // namespace

BMPImageFileType BMPImageFileType:: _the("image/bmp",
                                         suffixArray,
                                         sizeof(suffixArray),
                                         (OSG_READ_SUPPORTED |
                                          OSG_WRITE_SUPPORTED));


//-------------------------------------------------------------------------
/*! Tries to fill the image object with the data read from
    the given fileName. Returns true on success.
 */

bool BMPImageFileType::read(      Image        *pImage,
                                  std::istream &is,
                            const std::string  &mimetype)
{
    // Parse bitmap file header
    OSGBITMAPFILEHEADER fileHeader;
    if (readBitmapFileHeader(is, fileHeader) == false)
        return false;

    // Parse bitmap info header
    OSGBITMAPINFOHEADER infoHeader;
    if (readBitmapInfoHeader(is, infoHeader) == false)
        return false;

    // Parse color map
    RGB colorMap[256];
    if (readColorMap(is, fileHeader, infoHeader, colorMap) == false)
        return false;

    // Parse the image data
    UInt32 pixelFormat = infoHeader.alphaMask != 0 ? Image::OSG_RGBA_PF: Image::OSG_RGB_PF;
    Int32 height = infoHeader.biHeight >= 0 ? infoHeader.biHeight : -infoHeader.biHeight;
    pImage->set(pixelFormat, infoHeader.biWidth, height);
    switch (infoHeader.biBitCount)
    {
    case 1:
    case 4:
    case 8:
        if (infoHeader.biCompression == 0 /*BI_RGB*/)
        {
            if (parseUncompressedPaletteImage(is, infoHeader, colorMap, pImage) == false)
                return false;
        }
        else
        {
            if (parseRLEImage(is, infoHeader, colorMap, pImage) == false)
                return false;
        }
        break;
    case 16:
    case 32:
        if (parseTrueColorImage(is, infoHeader, pImage) == false)
            return false;
        break;
    case 24:
        if (parse24bitImage(is, infoHeader, pImage) == false)
            return false;
        break;
    default:
        return false;
    }


    return true;
}

//-------------------------------------------------------------------------
/*! Tries to write the image object to the given output stream.
    Returns true on success.
*/

bool BMPImageFileType::write(const Image            *pImage,
                                   std::ostream     &os,
                             const std::string      &mimetype)
{
    if(!pImage)
        return false;

    int bpp = pImage->getBpp();
    if(bpp != 3)
    {
        FWARNING(("Writing of bmp files is only supported for 24 bit RGB images!\n"));
        return false;
    }

    if (!os.good())
        return false;

    int width = pImage->getWidth();
    int height = pImage->getHeight();
    const unsigned char *data =
        static_cast<const unsigned char *>(pImage->getData());

    unsigned long int bitmapoffset;
    unsigned short int bitsperpixel;
    unsigned long int colorsimportant;
    unsigned long int colorsused;
    unsigned long int compression;
    unsigned long int filesize;
    unsigned short int filetype;
    unsigned long int horzresolution;
    int padding;
    unsigned short int planes;
    unsigned short int reserved1 = 0;
    unsigned short int reserved2 = 0;
    unsigned long int size = 40;
    unsigned long int sizeofbitmap;
    unsigned long int vertresolution;

    //  Write header 1.
    if(_bmp_byte_swap)
        filetype = 'M' * 256 + 'B';
    else
        filetype = 'B' * 256 + 'M';

    //  Determine the padding needed when WIDTH is not a multiple of 4.
    padding = ( 4 - ( ( 3 * width ) % 4 ) ) % 4;

    filesize = 54 + ( ( 3 * width ) + padding ) * abs ( height );
    bitmapoffset = 54;

    bmp_header1_write(os, filetype, filesize, reserved1,
                      reserved2, bitmapoffset );

    //  Write header 2.

    planes = 1;
    bitsperpixel = 24;
    compression = 0;
    sizeofbitmap = 0;
    horzresolution = 0;
    vertresolution = 0;
    colorsused = 0;
    colorsimportant = 0;

    bmp_header2_write(os, size, width, height, planes, bitsperpixel,
                      compression, sizeofbitmap, horzresolution, vertresolution,
                      colorsused, colorsimportant);

    //  Write the data.
    bmp_24_data_write(os, width, height, data);

    return true;
}

//-------------------------------------------------------------------------
/*!
  Tries to determine the mime type of the data provided by an input stream
  by searching for magic bytes. Returns the mime type or an empty string
  when the function could not determine the mime type.
 */

std::string BMPImageFileType::determineMimetypeFromStream(std::istream &is)
{
    char filecode[2];

    is.read(filecode, 2);
    is.seekg(-2, std::ios::cur);

    return strncmp(filecode, "BM", 2) == 0 ?
        std::string(getMimeType()) : std::string();
}

//-------------------------------------------------------------------------
/*! Constructor used for the singleton object
 */

BMPImageFileType::BMPImageFileType(const Char8  *mimeType,
                                   const Char8  *suffixArray[],
                                         UInt16  suffixByteCount,
                                         UInt32  flags) :
    Inherited(mimeType,
              suffixArray,
              suffixByteCount,
              flags          )
{
}

//-------------------------------------------------------------------------
/*! Destructor
 */

BMPImageFileType::~BMPImageFileType(void)
{
}

OSG_END_NAMESPACE
