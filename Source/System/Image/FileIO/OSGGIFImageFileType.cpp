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
//      Includes                                
//-------------------------------

#include <cstdlib>
#include <cstdio>
#include <setjmp.h>
#include <cstring>
#include <cctype>

#include "OSGConfig.h"

#ifdef   OSG_SGI_LIB
#include <limits>
#endif
#include "OSGGIFImageFileType.h"
#include "OSGLog.h"

#ifndef OSG_DO_DOC
#    ifdef OSG_WITH_GIF
#        define OSG_GIF_ARG(ARG) ARG
#    else
#        define OSG_GIF_ARG(ARG)
#    endif
#else
#    define OSG_GIF_ARG(ARG) ARG
#endif

#ifdef OSG_WITH_GIF


/*! \class OSG::GIFImageFileType 

  Image File Type to read/write and store/restore Image objects as
  GIF data.
  
  All the type specific code is included in the class. Does
  not depend on external libs.
  
  You have to --enable-gif in the configure line to enable
  the singleton object.
 
*/


//--- GIF-INCLUDE START ----------------------------------------------------

#define GIF_MAXCOLORS   256

typedef enum
{
    gif_image,
    gif_comment,
    gif_text
} GIFStreamType;

typedef enum
{
    gif_no_disposal     = 0,
    gif_keep_disposal   = 1,
    gif_color_restore   = 2,
    gif_image_restore   = 3
}
GIFDisposalType;

typedef struct
{
    int             transparent;    /* transparency index */
    int             delayTime;      /* Time in 1/100 of a second */
    int             inputFlag;      /* wait for input after display */
    GIFDisposalType disposal;
} GIF89info;

typedef struct  GIFData
{
    GIF89info       info;
    int             x, y;
    int             width, height;
    GIFStreamType   type;
    union
    {
        struct
        {
            int             cmapSize;
            unsigned char   cmapData[GIF_MAXCOLORS][3];
            unsigned char   *data;
            int             interlaced;
        } image;
        struct
        {
            int     fg, bg;
            int     cellWidth, cellHeight;
            int     len;
            char    *text;
        } text;
        struct
        {
            int     len;
            char    *text;
        } comment;
    } data;

    struct GIFData  *next;
} GIFData;

typedef struct
{
    int             width, height;

    int             colorResolution;
    int             colorMapSize;
    int             cmapSize;
    unsigned char   cmapData[GIF_MAXCOLORS][3];

    int             background;
    int             aspectRatio;

    GIFData         *data;
} GIFStream;


static GIFStream *GIFRead   (std::istream &is);
       int        GIFTest   (char *);
       int        GIFWrite  (char *, GIFStream *, int);
static int        GIFWriteFP(FILE *, GIFStream *, int);
static int        GIFFree   (GIFStream *);

#endif

//--- GIF INCLUDE END ----------------------------------------------------

static const OSG::Char8 *suffixArray[] = 
{
    "gif"
};

OSG_USING_NAMESPACE

GIFImageFileType GIFImageFileType::_the("image/gif",
                                        suffixArray, 
                                        sizeof(suffixArray));



//-------------------------------------------------------------------------
/*! Tries to fill the image object with the data read from
    the given fileName. Returns true on success.
*/

bool GIFImageFileType::read(      Image        *OSG_GIF_ARG(pImage), 
                                  std::istream &OSG_GIF_ARG(is),
                            const std::string  &OSG_GIF_ARG(mimetype))
{
    bool                retCode = false;

#ifdef OSG_WITH_GIF
    Image::PixelFormat  pixelFormat = Image::OSG_INVALID_PF;
    GIFStream           *gifStream = GIFRead(is);
    GIFData             *gifData = 0;
    bool                isColor;
    int                 i, j, destI, lineSize, lineEnd;
    unsigned            red, green, blue;
    int                 transparentIndex;
    int                 width = 0, height = 0, channel = 0;
    int                 xOff = 0, yOff = 0;
    unsigned char       *srcData = 0, *destData = 0;
    int                 colorIndex;
    unsigned            frameCount = 0, currentFrame = 0;
    unsigned char       *colorMap = 0;

    //    int imageSize = 0;
    int                 colorMapSize;
    Time                frameDelay;

    if(gifStream)
    {
        frameCount = 0;

        for(gifData = gifStream->data; gifData; gifData = gifData->next)
        {
            if(gifData->type == gif_image)
                frameCount++;
        }
    }

    FDEBUG(("GIF Frames: %d\n", frameCount));

    if(gifStream)
    {
        for(gifData = gifStream->data; gifData; gifData = gifData->next)
        {
            switch(gifData->type)
            {
                case gif_image:
                    if(frameCount)
                    {
                        FDEBUG(("Try to copy GIF Anim Frame %d/%d\n",
                                (currentFrame + 1), frameCount));
                    }
                    
                    // get the att.
                    transparentIndex = gifData->info.transparent;
                    frameDelay = float(gifData->info.delayTime) / 100.0f;
                    width  = gifData->width;
                    height = gifData->height;
                    xOff   = gifData->x;
                    yOff   = gifData->y;
                    
                    // check if the movie is color or greyscale
                    isColor = false;
                    if(gifData->data.image.cmapSize > 0)
                    {
                        colorMapSize = gifData->data.image.cmapSize;
                        colorMap = 
                            reinterpret_cast<unsigned char *>(
                                gifData->data.image.cmapData);
                        
                        // cout << "INFO: Use gifData colorMap" << endl;
                    }
                    else if(gifStream->cmapSize > 0)
                    {
                        colorMapSize = gifStream->cmapSize;
                        colorMap = 
                            reinterpret_cast<unsigned char *>(
                                gifStream->cmapData);
                        
                        // cout << "INFO: Use gifStream colorMap" << endl;
                    }
                    else
                    {
                        FWARNING(("Bad color map in "
                                  "GIFImageFileType::read()\n"));
                        colorMapSize = 0;
                    }
                    
                    for(i = 0; i < colorMapSize; i++)
                    {
                        if(i != transparentIndex)
                        {
                            red   = colorMap[i * 3 + 0];
                            green = colorMap[i * 3 + 1];
                            blue  = colorMap[i * 3 + 2];

                            if(red != green || red != blue)
                            {
                                isColor = true;
                                break;
                            }
                        }
                    }
                    
                    // calculate the movie channel
                    channel = 
                        (isColor ? 3 : 1) + (transparentIndex >= 0 ? 1 : 0);
                    
                    if(currentFrame)
                    {
                        // is not the first frame
                        if((channel == pImage->getBpp()) &&
                           (width == pImage->getWidth()) &&
                           (height == pImage->getHeight()))
                        {
                            destData = pImage->editData(0, currentFrame);
                        }
                        else
                        {
                            destData = pImage->editData(0, currentFrame);
                            
                            // This is probably wrong, but it's a start
                            switch(gifData->info.disposal)
                            {
                                case gif_no_disposal:
                                    break;
                                    
                                case gif_keep_disposal:
                                    memcpy(destData, 
                                           pImage->getData(0, 
                                                           currentFrame - 1), 
                                           pImage->getWidth () * 
                                           pImage->getHeight() * 
                                           channel);
                                    break;
                                    
                                case gif_color_restore:
                                {
                                    unsigned char r,g,b,a;
                                    Int32 bgindex = gifStream->background;
                                    unsigned char *d = destData;
                                    
                                    r = colorMap[bgindex * 3 + 0];
                                    g = colorMap[bgindex * 3 + 1];
                                    b = colorMap[bgindex * 3 + 2];
                                    a = (bgindex == transparentIndex) ? 
                                        0 : 255;
                                    
                                    for(UInt32 pixel = 
                                            pImage->getWidth () * 
                                            pImage->getHeight(); 
                                        pixel > 0; --pixel, d += channel)
                                    {
                                        d[0] = r;
                                        d[1] = g;
                                        d[2] = b;
                                        if(channel == 4)
                                            d[3] = a;
                                    }
                                }
                                break;
                                
                                case gif_image_restore:                       
                                    memcpy(destData, 
                                           pImage->getData(
                                               0, 
                                               (currentFrame >= 2) ?
                                                   (currentFrame - 2) : 0),
                                           pImage->getWidth () * 
                                           pImage->getHeight() * 
                                           channel);
                                    break;
                                default:
                                    FWARNING(("Unknown GIF disposal "
                                              "mode %d\n", 
                                              gifData->info.disposal));
                                    break;
                            }
                        }
                    }
                    else
                    {
                        switch(channel)
                        {
                            case 1:
                                pixelFormat = Image::OSG_L_PF;
                                break;
                            case 2:
                                pixelFormat = Image::OSG_LA_PF;
                                break;
                            case 3:
                                pixelFormat = Image::OSG_RGB_PF;
                                break;
                            case 4:
                                pixelFormat = Image::OSG_RGBA_PF;
                                break;
                        };
                        pImage->set(pixelFormat, 
                                    width, 
                                    height, 
                                    1, 1, 
                                    frameCount, frameDelay);

                        destData = pImage->editData();
                    }
                    
                    // copy the image data)
                    lineSize = pImage->getWidth() * channel;
                    lineEnd  = width * channel + xOff * channel;
                    srcData  = gifData->data.image.data;
                    destData = 
                        destData + ((pImage->getHeight() - yOff - 1)*lineSize);

                    switch(channel)
                    {
                        case 1: // Greyscale without Alpha
                            destI = 0;
                            for(i = width * height; i--;)
                            {
                                destData[destI++] = colorMap[*srcData++ *3];
                                if(destI >= lineSize)
                                {
                                    destI = 0;
                                    destData -= lineSize;
                                }
                            }
                            break;
                            
                        case 2: // Greyscale with Alpha
                            destI = 0;
                            for(i = width * height; i--;)
                            {
                                colorIndex = *srcData++;
                                if(colorIndex == transparentIndex)
                                {
                                    destData[destI++] = 0;
                                    destData[destI++] = 0;
                                }
                                else
                                {
                                    destData[destI++] = colorMap[colorIndex*3];
                                    destData[destI++] = 255;
                                }
                                
                                if(destI >= lineSize)
                                {
                                    destI = 0;
                                    destData -= lineSize;
                                }
                            }
                            break;
                            
                        case 3: // RGB without Alpha
                            destI = 0;
                            for(i = width * height; i--;)
                            {
                                colorIndex = *srcData++;
                                for(j = 0; j < 3; j++)
                                {
                                    destData[destI++] = 
                                        colorMap[colorIndex * 3 + j];
                                }
                                
                                if(destI >= lineSize)
                                {
                                    destI = 0;
                                    destData -= lineSize;
                                }
                            }
                            break;
                            
                        case 4: // RGB with Alpha
                            destI = xOff * 4;                    

                            for(i = width * height; i--;)
                            {
                                colorIndex = *srcData++;
                                if(colorIndex == transparentIndex)
                                {
#if 0
                                    for(j = 0; j < 3; j++)
                                        destData[destI++] = 0; // RGB
                                    destData[destI++] = 0;     // ALPHA
#endif

                                    destI += 4;
                                }
                                else
                                {
                                    for(j = 0; j < 3; j++)
                                    {
                                        destData[destI++] = 
                                            colorMap[colorIndex * 3 + j];// RGB
                                    }
                                    
                                    destData[destI++] = 255;          // ALPHA
                                }
                                
                                if(destI >= lineEnd)
                                {
                                    destI = xOff * 4;
                                    destData -= lineSize;
                                }
                            }
                            break;
                    }
                    
                    retCode = true;
                    
                    currentFrame++;
                    
                    break;
                case gif_comment:
                    break;
                case gif_text:
                    break;
            }
        }
        
        GIFFree(gifStream);
    }
    else
    {
        retCode = false;
    }
#endif

    return retCode;
}

//-------------------------------------------------------------------------
/*! Tries to write the image object to the given fileName.
    Returns true on success.
*/

bool GIFImageFileType::write(const Image         *  , 
                                   std::ostream  &, 
                             const std::string   &)
{
#ifdef OSG_WITH_GIF
    SWARNING << getMimeType() << " write is not implemented " << endLog;
    
#else
    SWARNING << getMimeType()
             << " write is not compiled into the current binary "
             << endLog;
#endif

    return false;
}

//-------------------------------------------------------------------------
/*!
  Tries to determine the mime type of the data provided by an input stream
  by searching for magic bytes. Returns the mime type or an empty string
  when the function could not determine the mime type.
*/

std::string GIFImageFileType::determineMimetypeFromStream(std::istream &is)
{
    char filecode[4];

    is.read(filecode, 4);
    is.seekg(-4, std::ios::cur);

    return strncmp(filecode, "GIF8", 4) == 0 ?
        std::string(getMimeType()) : std::string();
}

bool GIFImageFileType::validateHeader(const Char8 *fileName, bool &implemented)
{
    implemented = true;
    
    if(fileName == NULL)
        return false;
    
    FILE *file = fopen(fileName, "rb");

    if(file == NULL)
        return false;

    std::string magic;

    magic.resize(4);

    fread(static_cast<void *>(&magic[0]), 4, 1, file);

    fclose(file);

    if(magic == "GIF8")
    {
        return true;
    }

    return false;
}

//-------------------------------------------------------------------------
/*! Constructor used for the singleton object
 */

GIFImageFileType::GIFImageFileType(const Char8  *mimeType,
                                   const Char8  *suffixArray[],
                                         UInt16  suffixByteCount) :
    Inherited(mimeType,suffixArray, suffixByteCount)
{
}

//-------------------------------------------------------------------------
/*! Destructor
 */

GIFImageFileType::~GIFImageFileType(void)
{
}

#ifdef OSG_WITH_GIF

//--- GIF-READ START ----------------------------------------------------
/*
**  Copyright 1994, Home Pages, Inc.
**
**    Please read the file COPYRIGHT for specific information.
**
**    Home Pages, Inc.
**    257 Castro St. Suite 219
**    Mountain View, CA 94041
**
**    Phone: 1 415 903 5353
**      Fax: 1 415 903 5345
**
**    EMail: support@homepages.com
** 
*/
/* +-------------------------------------------------------------------+ */
/* | Copyright 1990 - 1994, David Koblas. (koblas@netcom.com)          | */
/* |   Permission to use, copy, modify, and distribute this software   | */
/* |   and its documentation for any purpose and without fee is hereby | */
/* |   granted, provided that the above copyright notice appear in all | */
/* |   copies and that both that copyright notice and this permission  | */
/* |   notice appear in supporting documentation.  This software is    | */
/* |   provided "as is" without express or implied warranty.           | */
/* +-------------------------------------------------------------------+ */
#define GIF_TRUE                    1
#define GIF_FALSE                   0

#define MAX_LWZ_BITS                12

#define INTERLACE                   0x40
#define LOCALCOLORMAP               0x80

#define BitSet(byte, bit)           (((byte) & (bit)) == (bit))
#define ReadOK(is, buffer, len)     (is.read(reinterpret_cast<char*>(buffer), \
                                             len).gcount() == len)
#define MKINT(a, b)                 (((b) << 8) | (a))
#define NEW(x)                      (static_cast<x *>(malloc(sizeof(x))))
/***************************************************************************
*
*  ERROR()    --  should not return
*  INFO_MSG() --  info message, can be ignored
*
***************************************************************************/

#if 0
#define INFO_MSG(fmt)   pm_message fmt 
#define ERROR(str)  pm_error(str)
#else
#if 0 
#define INFO_MSG(fmt)   
#define ERROR(str) do  { RWSetMsg(str); longjmp(setjmp_buffer, 1); } while(0)
#else
#define INFO_MSG(fmt)  { FINFO(("Info loading gif: '%s'!\n", fmt)); }
#define GIF_ERROR(str) { FWARNING(("Error loading gif: '%s'!\n", str)); \
                         longjmp(setjmp_buffer, 1); }
#endif
#endif

/***************************************************************************/

static int readColorMap(std::istream &, int, unsigned char [GIF_MAXCOLORS][3]);
static int GetDataBlock(std::istream &, unsigned char *);
static void readImage  (std::istream &, int, int, int, unsigned char *);

static jmp_buf                  setjmp_buffer;

static int    verbose = GIF_FALSE;
//static int    showComment = GIF_FALSE;

/* */
static GIFStream *GIFRead(std::istream &is)
{
    unsigned char   buf[256];
    unsigned char   c;
    GIFStream       *gifStream = 0;
    GIFData         *cur, **end;
    GIF89info       info = {0, 0, 0, gif_no_disposal};
    int             resetInfo = GIF_TRUE;
    int             n;

    if(setjmp(setjmp_buffer))
        goto out;

    if(!ReadOK(is, buf, 6))
    {
        GIF_ERROR("error reading magic number");
    }

    if(strncmp(reinterpret_cast<char *>(buf), "GIF", 3) != 0)
        GIF_ERROR("not a GIF file");

    if((strncmp((reinterpret_cast<char *>(buf)) + 3, "87a", 3) != 0) &&
       (strncmp((reinterpret_cast<char *>(buf)) + 3, "89a", 3) != 0))
    {
        GIF_ERROR("bad version number, not '87a' or '89a'");
    }

    if(!ReadOK(is, buf, 7))
    {
        GIF_ERROR("failed to read screen descriptor");
    }

    gifStream = NEW(GIFStream);

    gifStream->width = MKINT(buf[0], buf[1]);
    gifStream->height = MKINT(buf[2], buf[3]);

    gifStream->cmapSize = 2 << (buf[4] & 0x07);
    gifStream->colorMapSize = gifStream->cmapSize;
    gifStream->colorResolution = (int(buf[4] & 0x70) >> 3) + 1;
    gifStream->background = buf[5];
    gifStream->aspectRatio = buf[6];

    gifStream->data = NULL;

    end = &gifStream->data;

    /*
    **  Global colormap is present.
    */
    if(BitSet(buf[4], LOCALCOLORMAP))
    {
        if(readColorMap(is, gifStream->cmapSize, gifStream->cmapData))
        {
            GIF_ERROR("unable to get global colormap");
        }
    }
    else
    {
        gifStream->cmapSize = 0;
        gifStream->background = -1;
    }

    if(gifStream->aspectRatio != 0 && gifStream->aspectRatio != 49)
    {
        INFO_MSG(("warning - non-square pixels"));
    }

    while(ReadOK(is, &c, 1) && c != ';')
    {
        if(resetInfo)
        {
            info.disposal = static_cast<GIFDisposalType>(0);
            info.inputFlag = 0;
            info.delayTime = 0;
            info.transparent = -1;
            resetInfo = GIF_FALSE;
        }

        cur = NULL;

        if(c == '!')
        {           /* Extension */
            if(!ReadOK(is, &c, 1))
            {
                GIF_ERROR("EOF / read error on extention function code");
            }

            if(c == 0xf9)
            {       /* graphic control */
                (void) GetDataBlock(is, buf);
                info.disposal = 
                    static_cast<GIFDisposalType>((buf[0] >> 2) & 0x7);
                info.inputFlag = (buf[0] >> 1) & 0x1;
                info.delayTime = MKINT(buf[1], buf[2]);
                if(BitSet(buf[0], 0x1))
                    info.transparent = buf[3];

                while(GetDataBlock(is, buf) != 0)
                    ;
            }
            else if(c == 0xfe || c == 0x01)
            {
                int     len = 0;
                int     size = 256;
                char    *text = NULL;

                /* 
                **  Comment or Plain Text
                */
                cur = NEW(GIFData);

                if(c == 0x01)
                {
                    (void) GetDataBlock(is, buf);

                    cur->type = gif_text;
                    cur->info = info;
                    cur->x = MKINT(buf[0], buf[1]);
                    cur->y = MKINT(buf[2], buf[3]);
                    cur->width = MKINT(buf[4], buf[5]);
                    cur->height = MKINT(buf[6], buf[7]);

                    cur->data.text.cellWidth = buf[8];
                    cur->data.text.cellHeight = buf[9];
                    cur->data.text.fg = buf[10];
                    cur->data.text.bg = buf[11];

                    resetInfo = GIF_TRUE;
                }
                else
                {
                    cur->type = gif_comment;
                }

                text = static_cast<char *>(malloc(size));

                while((n = GetDataBlock(is, buf)) != 0)
                {
                    if(n + len >= size)
                    {
                        text = static_cast<char *>(realloc(text, size += 256));
                    }

                    memcpy(text + len, buf, n);
                    len += n;
                }

                if(c == 0x01)
                {
                    cur->data.text.len = len;
                    cur->data.text.text = text;
                }
                else
                {
                    cur->data.comment.len = len;
                    cur->data.comment.text = text;
                }
            }
            else
            {
                /*
                **  Unrecogonized extension, consume it.
                */
                while(GetDataBlock(is, buf) > 0)
                    ;
            }
        }
        else if(c == ',')
        {
            if(!ReadOK(is, buf, 9))
            {
                GIF_ERROR("couldn't read left/top/width/height");
            }

            cur = NEW(GIFData);

            cur->type = gif_image;
            cur->info = info;
            cur->x = MKINT(buf[0], buf[1]);
            cur->y = MKINT(buf[2], buf[3]);
            cur->width = MKINT(buf[4], buf[5]);
            cur->height = MKINT(buf[6], buf[7]);
            cur->data.image.cmapSize = 1 << ((buf[8] & 0x07) + 1);
            if(BitSet(buf[8], LOCALCOLORMAP))
            {
                if(readColorMap(is, cur->data.image.cmapSize,
                                         cur->data.image.cmapData))
                {
                    GIF_ERROR("unable to get local colormap");
                }
            }
            else
            {
                cur->data.image.cmapSize = 0;
            }

            cur->data.image.data = static_cast<unsigned char *>(
                malloc(cur->width * cur->height));
            cur->data.image.interlaced = BitSet(buf[8], INTERLACE);
            readImage(is, BitSet(buf[8], INTERLACE), cur->width, cur->height,
                      cur->data.image.data);

            resetInfo = GIF_TRUE;
        }
        else
        {
            FINFO(("Info loading gif: bogus character 0x%02x, ignoring", 
                   int(c)));
        }

        if(cur != NULL)
        {
            *end = cur;
            end = &cur->next;
            cur->next = NULL;
        }
    }

    if(c != ';')
        GIF_ERROR("EOF / data stream");

out:
    return gifStream;
}

/* */
static int GIFFreeData(GIFData *gifData)
{
    int retCode = 0;

    if(gifData)
    {
        switch(gifData->type)
        {
        case gif_image:
            if(gifData->data.image.data)
            {
                free(gifData->data.image.data);
            }
            break;
        case gif_comment:
            if(gifData->data.comment.text)
            {
                free(gifData->data.comment.text);
            }
            break;
        case gif_text:
            if(gifData->data.text.text)
            {
                free(gifData->data.text.text);
            }
            break;
        }

        retCode = 1;
    }
    else
        retCode = 0;

    return retCode;
}

/* */
static int GIFFree(GIFStream *gifStream)
{
    int     retCode = 1;
    GIFData *gifData, *gifNext;

    if(gifStream)
    {
        gifData = gifStream->data;
        while(gifData)
        {
            gifNext = gifData->next;
            GIFFreeData(gifData);
            free(gifData);
            gifData = gifNext;
        }
    }

    return retCode;
}

/* */
static int readColorMap(std::istream &is, int size, unsigned char data[GIF_MAXCOLORS][3])
{
    int             i;
    unsigned char   rgb[3 * GIF_MAXCOLORS];
    unsigned char   *cp = rgb;

    if(!ReadOK(is, rgb, size * 3))
        return GIF_TRUE;

    for(i = 0; i < size; i++)
    {
        data[i][0] = *cp++;
        data[i][1] = *cp++;
        data[i][2] = *cp++;
    }

    return GIF_FALSE;
}

/*
**
*/
static int  ZeroDataBlock = GIF_FALSE;

/* */

static int GetDataBlock(std::istream &is, unsigned char *buf)
{
    unsigned char   count;

    if(!ReadOK(is, &count, 1))
    {
        INFO_MSG(("error in getting DataBlock size"));
        return -1;
    }

    ZeroDataBlock = count == 0;

    if((count != 0) && (!ReadOK(is, buf, count)))
    {
        INFO_MSG(("error in reading DataBlock"));
        return -1;
    }

    return count;
}

/*
**
**
*/
/*
**  Pulled out of nextCode
*/
static int  curbit, lastbit, get_done, last_byte;
static int  return_clear;

/*
**  Out of nextLWZ
*/
static int  stack[(1 << (MAX_LWZ_BITS)) * 2], *sp;
static int  code_size, set_code_size;
static int  max_code, max_code_size;
static int  clear_code, end_code;

/* */

static void initLWZ(int input_code_size)
{
//  static int  inited = GIF_FALSE;

    set_code_size = input_code_size;
    code_size     = set_code_size + 1;
    clear_code    = 1 << set_code_size ;
    end_code      = clear_code + 1;
    max_code_size = 2 * clear_code;
    max_code      = clear_code + 2;

    curbit = lastbit = 0;
    last_byte = 2;
    get_done = GIF_FALSE;

    return_clear = GIF_TRUE;

    sp = stack;
}

/* */
static int nextCode(std::istream &is, int code_size)
{
    static unsigned char    buf[280];
    static int              maskTbl[16] =
    {
        0x0000,
        0x0001,
        0x0003,
        0x0007,
        0x000f,
        0x001f,
        0x003f,
        0x007f,
        0x00ff,
        0x01ff,
        0x03ff,
        0x07ff,
        0x0fff,
        0x1fff,
        0x3fff,
        0x7fff,
    };
    int                     i, j, ret, end;

    if(return_clear)
    {
        return_clear = GIF_FALSE;
        return clear_code;
    }

    end = curbit + code_size;

    if(end >= lastbit)
    {
        int count;

        if(get_done)
        {
            if(curbit >= lastbit)
            {
                GIF_ERROR("ran off the end of my bits");
            }

            return -1;
        }

        buf[0] = buf[last_byte - 2];
        buf[1] = buf[last_byte - 1];

        if((count = GetDataBlock(is, &buf[2])) == 0)
            get_done = GIF_TRUE;

        last_byte = 2 + count;
        curbit = (curbit - lastbit) + 16;
        lastbit = (2 + count) * 8;

        end = curbit + code_size;
    }

    j = end / 8;
    i = curbit / 8;

    if(i == j)
        ret = buf[i];
    else if(i + 1 == j)
        ret = buf[i] | (buf[i + 1] << 8);
    else
    {
        ret = buf[i] | (buf[i + 1] << 8) | (buf[i + 2] << 16);
    }

    ret = (ret >> (curbit % 8)) & maskTbl[code_size];

    curbit += code_size;

    return ret;
}

#define readLWZ(fd) ((sp > stack) ? *--sp : nextLWZ(fd))

/* */
static int nextLWZ(std::istream &is)
{
    static int      table[2][(1 << MAX_LWZ_BITS)];
    static int      firstcode, oldcode;
    int             code, incode;
    register int    i;

    while((code = nextCode(is, code_size)) >= 0)
    {
        if(code == clear_code)
        {
            for(i = 0; i < clear_code; ++i)
            {
                table[0][i] = 0;
                table[1][i] = i;
            }

            for(; i < (1 << MAX_LWZ_BITS); ++i)
                table[0][i] = table[1][i] = 0;
            code_size = set_code_size + 1;
            max_code_size = 2 * clear_code;
            max_code = clear_code + 2;
            sp = stack;
            do
            {
                firstcode = oldcode = nextCode(is, code_size);
            } while(firstcode == clear_code);

            return firstcode;
        }

        if(code == end_code)
        {
            int             count;
            unsigned char   buf[260];

            if(ZeroDataBlock)
                return -2;

            while((count = GetDataBlock(is, buf)) > 0)
                ;

            if(count != 0)
            {
                INFO_MSG(("missing EOD in data stream"));
            }

            return -2;
        }

        incode = code;

        if(code >= max_code)
        {
            *sp++ = firstcode;
            code = oldcode;
        }

        while(code >= clear_code)
        {
            *sp++ = table[1][code];
            if(code == table[0][code])
            {
                GIF_ERROR("circular table entry BIG ERROR");
            }

            code = table[0][code];
        }

        *sp++ = firstcode = table[1][code];

        if((code = max_code) < (1 << MAX_LWZ_BITS))
        {
            table[0][code] = oldcode;
            table[1][code] = firstcode;
            ++max_code;
            if((max_code >= max_code_size) &&
               (max_code_size < (1 << MAX_LWZ_BITS)))
            {
                max_code_size *= 2;
                ++code_size;
            }
        }

        oldcode = incode;

        if(sp > stack)
            return *--sp;
    }

    return code;
}

/* */
static void readImage(std::istream &is, int interlace, int width, int height,
                       unsigned char *data)
{
    unsigned char   *dp, c;

    int             v, xpos = 0, ypos = 0;

    //    int pass = 0;
    /*
    **  Initialize the Compression routines
    */
    if(!ReadOK(is, &c, 1))
    {
        GIF_ERROR("EOF / read error on image data");
    }

    initLWZ(c);

    if(verbose)
    {
        FINFO(("Info loading gif: reading %d by %d%s GIF image", 
               width, height, interlace ? " interlaced" : ""));
    }

    if(interlace)
    {
        int i;
        int pass = 0, step = 8;

        for(i = 0; i < height; i++)
        {
            dp = &data[width * ypos];
            for(xpos = 0; xpos < width; xpos++)
            {
                if((v = readLWZ(is)) < 0)
                    goto fini;

                *dp++ = v;
            }

            if((ypos += step) >= height)
            {
                do
                {
                    if(pass++ > 0)
                        step /= 2;
                    ypos = step / 2;
                } while(ypos > height);
            }
        }
    }
    else
    {
        dp = data;
        for(ypos = 0; ypos < height; ypos++)
        {
            for(xpos = 0; xpos < width; xpos++)
            {
                if((v = readLWZ(is)) < 0)
                    goto fini;

                *dp++ = v;
            }
        }
    }

fini:
    if(readLWZ(is) >= 0)
    {
        INFO_MSG(("too much input data, ignoring extra..."));
    }

    return;
}

//--- GIF-READ END ------------------------------------------------------
//--- GIF-WRITE START ---------------------------------------------------
/*
**  Copyright 1994, Home Pages, Inc.
**
**    Please read the file COPYRIGHT for specific information.
**
**    Home Pages, Inc.
**    257 Castro St. Suite 219
**    Mountain View, CA 94041
**
**    Phone: 1 415 903 5353
**      Fax: 1 415 903 5345
**
**    EMail: support@homepages.com
** 
*/
/* +-------------------------------------------------------------------+ */
/* | Copyright 1993, David Koblas (koblas@netcom.com)                  | */
/* |                                                                   | */
/* | Permission to use, copy, modify, and to distribute this software  | */
/* | and its documentation for any purpose is hereby granted without   | */
/* | fee, provided that the above copyright notice appear in all       | */
/* | copies and that both that copyright notice and this permission    | */
/* | notice appear in supporting documentation.  There is no           | */
/* | representations about the suitability of this software for        | */
/* | any purpose.  this software is provided "as is" without express   | */
/* | or implied warranty.                                              | */
/* |                                                                   | */
/* +-------------------------------------------------------------------+ */
/* ppmtogif.c - read a portable pixmap and produce a GIF file
**
** Based on GIFENCOD by David Rowley <mgardi@watdscu.waterloo.edu>.A
** Lempel-Zim compression based on "compress".
**
** Copyright (C) 1989 by Jef Poskanzer.
**
** Permission to use, copy, modify, and distribute this software and its
** documentation for any purpose and without fee is hereby granted, provided
** that the above copyright notice appear in all copies and that both that
** copyright notice and this permission notice appear in supporting
** documentation.  This software is provided "as is" without express or
** implied warranty.
**
** The Graphics Interchange Format(c) is the Copyright property of
** CompuServe Incorporated.  GIF(sm) is a Service Mark property of
** CompuServe Incorporated.
*/
#define GIF_TRUE        1
#define GIF_FALSE       0

#define PUTBYTE(v, fp)  putc(v, fp)
#define PUTWORD(v, fp) \
    do \
    { \
        putc(((v) & 0xff), fp); \
        putc((((v) >> 8) & 0xff), fp); \
    } while(0)
/*
 * a code_int must be able to hold 2**BITS values of type int, and also -1
 */
    typedef int     code_int;

typedef long int    count_int;

static void         putImage(FILE *, int, int, int, int, unsigned char *);
static void         putColorMap(FILE *, int, unsigned char[GIF_MAXCOLORS][3]);
static void         putDataBlocks(FILE *fp, int, unsigned char *);
static void         putGif89Info(FILE *, GIF89info *);

static void         output(code_int code);
static void         cl_block(void);
static void         cl_hash(count_int hsize);
static void         char_init(void);
static void         char_out(int c);
static void         flush_char(void);

/*
**
*/
struct cval
{
    int idx, cnt;
};

/* */
static int cvalCMP(struct cval *a, struct cval *b)
{
    return b->cnt - a->cnt;
}

/* */
static int optimizeCMAP(GIFStream *stream)
{
    GIFData *cur = 0, *img = 0;
    int     count = 0;

    for(cur = stream->data; cur != NULL; cur = cur->next)
    {
        if(cur->type == gif_image)
        {
            img = cur;
            count++;
        }
    }

    /*
    **  No images, no optimizations...
    **   or too many images...
    */
    if(count == 0 || count > 1)
        return 0;

    /*
    **  One image, nice and simple...
    **    Insure there is a global colormap, and optimize the
    **    image too it.
    */
    {
        int             size;
        unsigned char   *dp = img->data.image.data;
        unsigned char   *ep = dp + img->width * img->height;
        struct cval     vals[256];
        int             i;

        //        int  j;
        unsigned char   tmap[256][3], rmap[256];

        if((size = img->data.image.cmapSize) == 0)
            size = stream->cmapSize;

        for(i = 0; i < size; i++)
        {
            vals[i].idx = i;
            vals[i].cnt = 0;
        }

        for(dp = img->data.image.data, i = 0; dp < ep; i++, dp++)
            vals[*dp].cnt++;

        /*
        **  Quite, I'm doing a bubble sort... ACK!
        */
        qsort(vals, size, sizeof(vals[0]),
              reinterpret_cast<int(*) (const void *, const void *)>(cvalCMP));

        for(i = 0; i < size; i++)
            if(vals[i].idx != i)
                break;

        /*
        **  Already sorted, no change!
        */
        if(i == size)
            return 1;
        for(i = 0; i < size; i++)
            rmap[vals[i].idx] = i;

        /*
        **  Now reorder the colormap, and the image
        */
        for(dp = img->data.image.data, i = 0; dp < ep; i++, dp++)
            *dp = rmap[*dp];
        if(img->info.transparent != -1)
        {
            img->info.transparent = rmap[img->info.transparent];
        }

        /*
        **  Toast the local colormap
        */
        if(img->data.image.cmapSize != 0)
        {
            for(i = 0; i < size; i++)
            {
                stream->cmapData[i][0] = img->data.image.cmapData[i][0];
                stream->cmapData[i][1] = img->data.image.cmapData[i][1];
                stream->cmapData[i][2] = img->data.image.cmapData[i][2];
            }

            img->data.image.cmapSize = 0;
            stream->cmapSize = size;
        }

        /*
        **  Now finally reorer the colormap
        */
        for(i = 0; i < size; i++)
        {
            tmap[i][0] = stream->cmapData[i][0];
            tmap[i][1] = stream->cmapData[i][1];
            tmap[i][2] = stream->cmapData[i][2];
        }

        for(i = 0; i < size; i++)
        {
            stream->cmapData[rmap[i]][0] = tmap[i][0];
            stream->cmapData[rmap[i]][1] = tmap[i][1];
            stream->cmapData[rmap[i]][2] = tmap[i][2];
        }
    }

    return 1;
}

/*
**  Return the ceiling log of n 
*/
static int binaryLog(int val)
{
    int i;

    if(val == 0)
        return 0;

    for(i = 1; i <= 8; i++)
        if(val <= (1 << i))
            return i;
    return 8;
}

#ifdef __sgi
#pragma set woff 1209
#endif

/* */
static int GIFWriteFP(FILE *fp, GIFStream *stream, int optimize)
{
    GIFData *cur;
    int     flag = GIF_FALSE;
    int     c;
    int     globalBitsPP = 0;
    int     resolution;

    if(fp == NULL)
        return GIF_TRUE;
    if(stream == NULL)
        return GIF_FALSE;

    /*
    **  First find if this is a 87A or an 89A GIF image
    **    also, figure out the color resolution of the image.
    */
    resolution = binaryLog(stream->cmapSize) - 1;
    for(cur = stream->data; !flag && cur != NULL; cur = cur->next)
    {
        if(cur->type == gif_text || cur->type == gif_comment)
        {
            flag = GIF_TRUE;
        }
        else if(cur->type == gif_image)
        {
            int v = binaryLog(cur->data.image.cmapSize);

            if(v > resolution)
                resolution = v;

            /*
            **  Uses one of the 89 extensions.
            */
            if(cur->info.transparent != -1 ||
               cur->info.delayTime != 0 ||
               cur->info.inputFlag != 0 ||
               cur->info.disposal != 0)
                flag = GIF_TRUE;
        }
    }

    /*
    **
    */
    if(optimize)
        optimize = optimizeCMAP(stream);

    fwrite(flag ? "GIF89a" : "GIF87a", 1, 6, fp);

    PUTWORD(stream->width, fp);
    PUTWORD(stream->height, fp);

    /* 
    ** assume 256 entry color resution, and non sorted colormap 
    */
    c = ((resolution & 0x07) << 5) | 0x00;
    if(stream->cmapSize != 0)
    {
        globalBitsPP = binaryLog(stream->cmapSize);
        c |= 0x80;
        c |= globalBitsPP - 1;
    }

    /*
    **  Is the global colormap optimized?
    */
    if(optimize)
        c |= 0x08;
    PUTBYTE(c, fp);

    PUTBYTE(stream->background, fp);
    PUTBYTE(stream->aspectRatio, fp);

    putColorMap(fp, stream->cmapSize, stream->cmapData);

    for(cur = stream->data; cur != NULL; cur = cur->next)
    {
        if(cur->type == gif_image)
        {
            int bpp;

            putGif89Info(fp, &cur->info);

            PUTBYTE(0x2c, fp);
            PUTWORD(cur->x, fp);
            PUTWORD(cur->y, fp);
            PUTWORD(cur->width, fp);
            PUTWORD(cur->height, fp);

            c = cur->data.image.interlaced ? 0x40 : 0x00;
            if(cur->data.image.cmapSize != 0)
            {
                bpp = binaryLog(cur->data.image.cmapSize);
                c |= 0x80;
                c |= bpp;
            }
            else
            {
                bpp = globalBitsPP;
            }

            PUTBYTE(c, fp);

            putColorMap(fp, cur->data.image.cmapSize, cur->data.image.cmapData);

            putImage(fp, cur->data.image.interlaced, bpp, cur->width,
                     cur->height, cur->data.image.data);
        }
        else if(cur->type == gif_comment)
        {
            PUTBYTE('!', fp);
            PUTBYTE(0xfe, fp);
            putDataBlocks(
                fp, 
                cur->data.comment.len,
                reinterpret_cast<unsigned char *>(cur->data.comment.text));
        }
        else if(cur->type == gif_text)
        {
            putGif89Info(fp, &cur->info);

            PUTBYTE('!', fp);
            PUTBYTE(0x01, fp);

            PUTWORD(cur->x, fp);
            PUTWORD(cur->y, fp);
            PUTWORD(cur->width, fp);
            PUTWORD(cur->height, fp);

            PUTBYTE(cur->data.text.cellWidth, fp);
            PUTBYTE(cur->data.text.cellHeight, fp);
            PUTBYTE(cur->data.text.fg, fp);
            PUTBYTE(cur->data.text.bg, fp);

            putDataBlocks(
                fp, 
                cur->data.text.len,
                reinterpret_cast<unsigned char *>(cur->data.text.text));
        }
    }

    /*
    **  Write termination
    */
    PUTBYTE(';', fp);

    return GIF_FALSE;
}

#ifdef __sgi
#pragma reset woff 1209
#endif

/* */
int GIFWrite(char *file, GIFStream *stream, int optimize)
{
    if(stream != NULL)
    {
        FILE    *fp = fopen(file, "wb");

        if(fp != NULL)
        {
            int s = GIFWriteFP(fp, stream, optimize);
            fclose(fp);
            return s;
        }
    }

    return GIF_TRUE;
}

/* */
static void putColorMap(FILE *fp, int size, unsigned char data[GIF_MAXCOLORS][3])
{
    int i;

    for(i = 0; i < size; i++)
    {
        PUTBYTE(data[i][0], fp);
        PUTBYTE(data[i][1], fp);
        PUTBYTE(data[i][2], fp);
    }
}

/* */
static void putDataBlocks(FILE *fp, int size, unsigned char *data)
{
    int n;

    while(size > 0)
    {
        n = size > 255 ? 255 : size;

        PUTBYTE(n, fp);
        fwrite(data, 1, n, fp);
        data += n;
        size -= n;
    }

    PUTBYTE(0, fp); /* End Block */
}

#ifdef __sgi
#pragma set woff 1209
#endif

/* */
static void putGif89Info(FILE *fp, GIF89info *info)
{
    unsigned char   c;

    if(info->transparent == -1 &&
       info->delayTime == 0 &&
       info->inputFlag == 0 &&
       info->disposal == 0)
        return;

    PUTBYTE('!', fp);
    PUTBYTE(0xf9, fp);
    PUTBYTE(4, fp);
    c = (info->inputFlag ? 0x02 : 0x00) | ((info->disposal & 0x07) << 2) | ((info->transparent != -1) ? 0x01 : 0x00);
    PUTBYTE(c, fp);
    PUTWORD(info->delayTime, fp);
    PUTBYTE(info->transparent, fp);

    /*
    **  End
    */
    PUTBYTE(0, fp);
}

#ifdef __sgi
#pragma reset woff 1209
#endif

/***************************************************************************
 *
 *  GIFCOMPR.C       - GIF Image compression routines
 *
 *  Lempel-Ziv compression based on 'compress'.  GIF modifications by
 *  David Rowley (mgardi@watdcsu.waterloo.edu)
 *
 ***************************************************************************/
/*
 * General DEFINEs
 */

#define BITS    12

#define HSIZE  5003            /* 80% occupancy */

#ifdef NO_UCHAR
typedef char   char_type;
#else /*NO_UCHAR*/
typedef        unsigned char   char_type;
#endif /*NO_UCHAR*/

/*
 *
 * GIF Image compression - modified 'compress'
 *
 * Based on: compress.c - File compression ala IEEE Computer, June 1984.
 *
 * By Authors:  Spencer W. Thomas       (decvax!harpo!utah-cs!utah-gr!thomas)
 *              Jim McKie               (decvax!mcvax!jim)
 *              Steve Davies            (decvax!vax135!petsd!peora!srd)
 *              Ken Turkowski           (decvax!decwrl!turtlevax!ken)
 *              James A. Woods          (decvax!ihnp4!ames!jaw)
 *              Joe Orost               (decvax!vax135!petsd!joe)
 *
 */
#define ARGVAL()    (*++(*argv) || (--argc && *++argv))
static int              n_bits;     /* number of bits/code */
static int              maxbits;    /* user settable max # bits/code */
static code_int         maxcode;    /* maximum code, given n_bits */
static code_int         maxmaxcode; /* should NEVER generate this code */
#define MAXCODE(n_bits) ((static_cast<code_int>(1) << (n_bits)) - 1)
static count_int        htab[HSIZE];
static unsigned short   codetab[HSIZE];
#define HashTabOf(i)    htab[i]
#define CodeTabOf(i)    codetab[i]

static code_int         hsize;      /* for dynamic table sizing */

static unsigned long    cur_accum;
static int              cur_bits;

/*
 * To save much memory, we overlay the table used by compress() with those
 * used by decompress().  The tab_prefix table is the same size and type
 * as the codetab.  The tab_suffix table needs 2**BITS characters.  We
 * get this from the beginning of htab.  The output stack uses the rest
 * of htab, and contains characters.  There is plenty of room for any
 * possible stack (stack used to be 8000 characters).
 */
#define tab_prefixof(i) CodeTabOf(i)
#define tab_suffixof(i) ((char_type *) (htab))[i]
#define de_stack        ((char_type *) &tab_suffixof((code_int) 1 << BITS))
static code_int free_ent;           /* first unused entry */

/*
 * block compression parameters -- after all codes are used up,
 * and compression rate changes, start over.
 */
static int      clear_flg;

// static int offset = 0;
/*
 * compress stdin to stdout
 *
 * Algorithm:  use open addressing double hashing (no chaining) on the
 * prefix code / next character combination.  We do a variant of Knuth's
 * algorithm D (vol. 3, sec. 6.4) along with G. Knott's relatively-prime
 * secondary probe.  Here, the modular division first probe is gives way
 * to a faster exclusive-or manipulation.  Also do block compression with
 * an adaptive reset, whereby the code table is cleared when the compression
 * ratio decreases, but after the table fills.  The variable-length output
 * codes are re-sized at this point, and a special CLEAR code is generated
 * for the decompressor.  Late addition:  construct the table according to
 * file size for noticeable speed improvement on small files.  Please direct
 * questions about this implementation to ames!jaw.
 */
static int      g_init_bits;
static FILE     *g_outfile;

static int      ClearCode;
static int      EOFCode;

/* */

#ifdef __sgi
#pragma set woff 1209
#endif

static void putImage(FILE *fp, int interlaced, int bpp, int width, int height,
                     unsigned char *data)
{
    //  unsigned char   *end = data + width * height;
    int             left = interlaced ? width : width * height;
    int             cury = 0, pass = 0;
    unsigned char   *dp = data;
    long            fcode;
    code_int        v, i, ent, disp, hsize_reg;
    int             c, hshift;

    //  int         skip = 8;
    if(bpp <= 1)
    {
        g_init_bits = 3;
        PUTBYTE(2, fp);
    }
    else
    {
        g_init_bits = bpp + 1;
        PUTBYTE(bpp, fp);
    }

    /*
    ** Set up the globals:  g_init_bits - initial number of bits
    **                      g_outfile   - pointer to output file
    */
    g_outfile = fp;

    /*
    ** Set up the necessary values
    */
    // offset = 0;
    clear_flg = GIF_FALSE;
    maxbits = BITS;
    maxmaxcode = 1 << BITS;
    maxcode = MAXCODE(n_bits = g_init_bits);
    hsize = HSIZE;
    cur_accum = 0;
    cur_bits = 0;

    ClearCode = (1 << (g_init_bits - 1));
    EOFCode = ClearCode + 1;
    free_ent = ClearCode + 2;

    char_init();                                /* clear the output accumulator */

    hshift = 0;
    for(fcode = long(hsize); fcode < 65536; fcode *= 2)
        ++hshift;
    hshift = 8 - hshift;                        /* set hash code range bound */

    hsize_reg = hsize;
    cl_hash(count_int(hsize));                 /* clear hash table */

    output(code_int(ClearCode));

    ent = *dp++;
    do
    {
again:
        /*
        **  Fetch the next pixel
        */
        c = *dp++;
        if(--left == 0)
        {
            if(interlaced)
            {
                do
                {
                    switch(pass)
                    {
                    case 0:
                        cury += 8;
                        if(cury >= height)
                        {
                            pass++;
                            cury = 4;
                        }
                        break;
                    case 1:
                        cury += 8;
                        if(cury >= height)
                        {
                            pass++;
                            cury = 2;
                        }
                        break;
                    case 2:
                        cury += 4;
                        if(cury >= height)
                        {
                            pass++;
                            cury = 1;
                        }
                        break;
                    case 3:
                        cury += 2;
                        break;
                    }
                } while(pass < 3 && cury >= height);
                if(cury >= height)
                    goto done;
                dp = data + cury * width;
                left = width;
                c = *dp++;
            }
            else
            {
                goto done;
            }
        }

        /*
        **  Now output it...
        */
        fcode = long((long(c) << maxbits) + ent);

        i = ((code_int(c) << hshift) ^ ent);   /* xor hashing */
        v = HashTabOf(i);

        if(v == fcode)
        {
            ent = CodeTabOf(i);
            goto again;
        }
        else if(v >= 0)
        {
            /* 
            ** secondary hash (after G. Knott) 
            */
            disp = hsize_reg - i;
            if(i == 0)
                disp = 1;
            do
            {
                if((i -= disp) < 0)
                    i += hsize_reg;

                v = HashTabOf(i);
                if(v == fcode)
                {
                    ent = CodeTabOf(i);
                    goto again;
                }
            } while(v > 0);
        }

        output(code_int(ent));
        ent = c;
        if(free_ent < maxmaxcode)
        {
            CodeTabOf(i) = free_ent++;          /* code -> hashtable */
            HashTabOf(i) = fcode;
        }
        else
        {
            cl_block();
        }
    } while(1);
done:
    /*
    ** Put out the final code.
    **/
    output(code_int(ent));
    output(code_int(EOFCode));

    /*
    **  End block byte
    */
    PUTBYTE(0x00, fp);
}

#ifdef __sgi
#pragma reset woff 1209
#endif

/*****************************************************************
 * TAG( output )
 *
 * Output the given code.
 * Inputs:
 *      code:   A n_bits-bit integer.  If == -1, then EOF.  This assumes
 *              that n_bits =< (long)wordsize - 1.
 * Outputs:
 *      Outputs code to the file.
 * Assumptions:
 *      Chars are 8 bits long.
 * Algorithm:
 *      Maintain a BITS character long buffer (so that 8 codes will
 * fit in it exactly).  Use the VAX insv instruction to insert each
 * code in turn.  When the buffer fills up empty it and start over.
 */

static unsigned long masks[] = {  0x0000, 
                                  0x0001, 0x0003, 0x0007, 0x000F,
                                  0x001F, 0x003F, 0x007F, 0x00FF,
                                  0x01FF, 0x03FF, 0x07FF, 0x0FFF,
                                  0x1FFF, 0x3FFF, 0x7FFF, 0xFFFF };

static void output(code_int code)
{
    cur_accum &= masks[cur_bits];

    if(cur_bits > 0)
    {
        cur_accum |= (long(code) << cur_bits);
    }
    else
        cur_accum = code;

    cur_bits += n_bits;

    while(cur_bits >= 8)
    {
        char_out(static_cast<unsigned int>(cur_accum & 0xff));
        cur_accum >>= 8;
        cur_bits -= 8;
    }

    /*
    ** If the next entry is going to be too big for the code size,
    ** then increase it, if possible.
    */
    if(free_ent > maxcode || clear_flg)
    {
        if(clear_flg)
        {
            maxcode = MAXCODE(n_bits = g_init_bits);
            clear_flg = GIF_FALSE;
        }
        else
        {
            ++n_bits;
            if(n_bits == maxbits)
                maxcode = maxmaxcode;
            else
                maxcode = MAXCODE(n_bits);
        }
    }

    if(code == EOFCode)
    {
        /*
        ** At EOF, write the rest of the buffer.
        */
        while(cur_bits > 0)
        {
            char_out(static_cast<unsigned int>(cur_accum & 0xff));
            cur_accum >>= 8;
            cur_bits -= 8;
        }

        flush_char();

        fflush(g_outfile);
    }
}

/*
 * Clear out the hash table
 */
static void cl_block(void)
{
    cl_hash(count_int(hsize));
    free_ent = ClearCode + 2;
    clear_flg = GIF_TRUE;

    output(code_int(ClearCode));
}

/* */
static void cl_hash(count_int hsize)    /* reset code table */
{
    int i;

    for(i = 0; i < hsize; i++)
        htab[i] = -1;
}

/******************************************************************************
 *
 * GIF Specific routines
 *
 ******************************************************************************/
/*
** Number of characters so far in this 'packet'
*/
static int  a_count;

/*
** Define the storage for the packet accumulator
*/
static char accum[256];

/*
** Set up the 'byte output' routine
*/
static void char_init(void)
{
    a_count = 0;
}

/*
** Add a character to the end of the current packet, and if it is 254
** characters, flush the packet to disk.
*/
static void char_out(int c)
{
    accum[a_count++] = c;
    if(a_count == 255)
        flush_char();
}

/*
** Flush the packet to disk, and reset the accumulator
*/
static void flush_char(void)
{
    if(a_count != 0)
    {
        PUTBYTE(a_count, g_outfile);
        fwrite(accum, 1, a_count, g_outfile);
        a_count = 0;
    }
}

//--- GIF-WRITE END -----------------------------------------------------
#endif
