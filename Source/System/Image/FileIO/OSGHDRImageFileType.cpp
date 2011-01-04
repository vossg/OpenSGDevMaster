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
#include <cmath>
#include <memory.h>

#include "OSGConfig.h"

#include <iostream>
#include <fstream>

#include "OSGLog.h"
#include "OSGImageFileHandler.h"
#include "OSGPathHandler.h"
#include "OSGFileSystem.h"

#include "OSGHDRImageFileType.h"

// Static Class Varible implementations: 
static const OSG::Char8 *suffixArray[] = 
{
    "hdr"
};

OSG_BEGIN_NAMESPACE

#define MINELEN 8           // minimum scanline length for encoding
#define MAXELEN 0x7fff      // maximum scanline length for encoding
#define MINRUN  4           // minimum run length
#define RED 0
#define GRN 1
#define BLU 2
#define EXP 3
#define COLXS 128

// copy source -> dest
#define copy_rgbe(c1, c2) (c2[RED]=c1[RED],c2[GRN]=c1[GRN],c2[BLU]=c1[BLU],c2[EXP]=c1[EXP])

/*! \class HDRImageFileType 

  Image File Type to read/write and store/restore Image objects as
  HDR data.

  All the type specific code is included in the class. Does
  not depend on external libs.
    
 */

/*****************************
 *   Types
 *****************************/

HDRImageFileType HDRImageFileType::_the("image/x-hdr",
                                        suffixArray, sizeof(suffixArray),
                                        OSG_READ_SUPPORTED | 
                                        OSG_WRITE_SUPPORTED );


/*****************************
 *    Classvariables
 *****************************/


/********************************
 *    Class methodes
 *******************************/


/*******************************
*public
*******************************/

//-------------------------------------------------------------------------
/*!
  Tries to fill the image object with the data read from
  the given input stream. Returns true on success.
*/

bool HDRImageFileType::read(      Image        *image, 
                                  std::istream &is, 
                            const std::string  &mimetype)
{
    int width, height;
    
    if (!checkHDR(is, width, height))
    {
        FWARNING(("No valid RADIANCE picture format\n"));
        return false;
    }

    bool use16BitFloat = false;

    if(this->hasOption("use16BitFloat") == true)
    {
        this->getOptionAs("use16BitFloat", use16BitFloat);
    }

    image->set(Image::OSG_RGB_PF, 
               width, 
               height, 
               1, 1, 1, 0.0, 0, 
               (use16BitFloat == true) ? 
                   Image::OSG_FLOAT16_IMAGEDATA : Image::OSG_FLOAT32_IMAGEDATA);

    if(!image->isValid())
        return false;

    image->clear();

    if(use16BitFloat)
    {
        Real16 *data = reinterpret_cast<Real16 *>(image->editData());

        return radiance2fp(is, data, width, height);
    }
    else
    {
        Real32 *data = reinterpret_cast<Real32 *>(image->editData());
        
        return radiance2fp(is, data, width, height);
    }
}

//-------------------------------------------------------------------------
/*!
  Tries to write the image object to the given output stream.
  Returns true on success.
*/

bool HDRImageFileType::write(const Image        *image, 
                                   std::ostream &os, 
                             const std::string  &mimetype)
{
    if( (image->getDataType() != Image::OSG_FLOAT32_IMAGEDATA) &&
        (image->getDataType() != Image::OSG_FLOAT16_IMAGEDATA)  )
    {
        FWARNING(("HDRImageFileType::write: Image has non float data "
                  "type!\n"));
        return false;
    }
    
    if(!os.good())
        return false;

    int width  = image->getWidth();
    int height = image->getHeight();

    os << "#?RADIANCE" << std::endl;
    os << "# Written with OpenSG" << std::endl;
    os << "FORMAT=32-bit_rle_rgbe" << std::endl;
    os << "EXPOSURE=" << 1.0f << std::endl << std::endl;
    os << "-Y " << height << " +X " << width << std::endl;

    RGBE *rgbe_scan = new RGBE[width];

    if( image->getDataType() == Image::OSG_FLOAT32_IMAGEDATA)
    {
        const Real32 *data = reinterpret_cast<const Real32 *>(image->getData());

        //upside down !!!
        for(int y=height-1;y>=0;y--)
        {
            if (fwritecolrs(os, 
                            &data[y * width * 3], 
                            rgbe_scan, 
                            width, 
                            height) < 0)
            {
                delete [] rgbe_scan;
                return false;
            }
        }
    }
    else // OSG_FLOAT16_IMAGEDATA
    {
        const Real16 *data = reinterpret_cast<const Real16 *>(image->getData());

        //upside down !!!
        for(int y=height-1;y>=0;y--)
        {
            if(fwritecolrs(os, 
                           &data[y * width * 3], 
                           rgbe_scan, 
                           width, 
                           height) < 0)
            {
                delete [] rgbe_scan;
                return false;
            }
        }
    }

    delete [] rgbe_scan;
    return true;
}

//-------------------------------------------------------------------------
/*!
  Tries to restore the image data from the given memblock.
  Returns the amount of data read.
*/

UInt64 HDRImageFileType::restoreData(      Image  *image, 
                                     const UChar8 *buffer,
                                           Int32         )
{
    image->setData(buffer);

    return image->getSize();
}

//-------------------------------------------------------------------------
/*!
  Tries to store the image data to the given memblock.
  Returns the amount of data written.
*/

UInt64 HDRImageFileType::storeData(const Image  *image, 
                                         UChar8 *buffer,
                                         Int32   OSG_CHECK_ARG(memSize))
{
    UInt32 dataSize = image->getSize();

    const UChar8 *src = image->getData();

    if(dataSize && src && buffer)
        memcpy(buffer, src, dataSize);
  
    return dataSize;
} 


//-------------------------------------------------------------------------
/*!
  Constructor used for the singleton object
*/

HDRImageFileType::HDRImageFileType(const Char8 *mimeType,
                                   const Char8 *suffixArray[], 
                                         UInt16 suffixByteCount,
                                         UInt32 flags          ) :
    Inherited(mimeType, 
              suffixArray, 
              suffixByteCount, 
              flags )
{
}

//-------------------------------------------------------------------------
/*!
  Destructor
*/

HDRImageFileType::~HDRImageFileType(void)
{
}

// check header and get resolution (streaming type)
bool HDRImageFileType::checkHDR(std::istream &is, int &width, int &height)
{
    char cs[256], st1[80], st2[80];
    bool resok = false;
    bool HDRok = false;
    int i = 0;

    while (!is.eof() && !resok)
    {
        is.getline(cs, 255);

        if (strstr(cs, "32-bit_rle_rgbe"))
            HDRok = true;

        if (HDRok && (cs[0] == '\r' || cs[0] == '\n' || cs[0] == '\0'))
        {
            // empty line found, next is resolution info, format: -Y N +X N
            // directly followed by data
            is.getline(cs, 255);
        
            i = sscanf(cs, "%79s %d %79s %d", st1, &height, st2, &width);
            if (i == 4) 
                resok = true;
        }
    }
    
    return HDRok;
}
// convert radiance hdr to float image (streaming type)
bool HDRImageFileType::radiance2fp(std::istream &is, 
                                        Real16  *data, 
                                        int      width, 
                                        int      height)
{
    int x,y,yx;
    RGBE *sline = new RGBE[width];

    if (!sline)
        return false;

    for(y=height-1;y>=0;y--)
    {
        yx = y*width;
        if (!freadcolrs(is, sline, width))
            return false;
        Real16 *fcol = &data[yx * 3];
        for (x=0;x<width;x++)
        {
            RGBE2Half(sline[x], fcol);
            fcol += 3;
        }
    }
    delete[] sline;

    return true;
}


// convert radiance hdr to float image (streaming type)
bool HDRImageFileType::radiance2fp(std::istream &is, 
                                        Real32  *data, 
                                        int      width, 
                                        int      height)
{
    int x,y,yx;
    RGBE *sline = new RGBE[width];

    if (!sline)
        return false;

    for(y=height-1;y>=0;y--)
    {
        yx = y*width;
        if (!freadcolrs(is, sline, width))
            return false;
        Real32 *fcol = &data[yx * 3];
        for (x=0;x<width;x++)
        {
            RGBE2Float(sline[x], fcol);
            fcol += 3;
        }
    }

    delete[] sline;
    
    return true;
}

// read and decode a rgbe scanline (streaming type)
bool HDRImageFileType::freadcolrs(std::istream &is, RGBE *scan, int width)
{
    int i,j,code,val,size;
    unsigned char byte;

    if ((width < MINELEN) | (width > MAXELEN))
    {
        FWARNING(("Sorry, format probably too old\n"));
        return false;
    }

    byte = static_cast<unsigned char>(is.get());
    if (is.eof())
        return false;

    byte = static_cast<unsigned char>(is.get());
    scan[0][GRN] = byte;

    byte = static_cast<unsigned char>(is.get());
    scan[0][BLU] = byte;

    size = (int(scan[0][BLU])) << 8;
    i = is.get();

    if ( (size | i) != width )
        return false;

    for(i=0;i<4;i++)
    {
        for (j=0;j<width;)
        {
            if (is.eof())
                return false;
            
            code = is.get();
                
            if (code > 128)
            {
                code &= 127;
                val = is.get();
                
                while (code--)
                    scan[j++][i] = static_cast<unsigned char>(val);
            }
            else
            {
                while (code--) 
                  scan[j++][i] = is.get();
            }
        }
    }
    
    return is.eof() ? false : true;
}


//rgbe -> float color
void HDRImageFileType::RGBE2Float(RGBE rgbe, Real32 *fcol)
{
    if (rgbe[EXP] == 0)
    {
        *(fcol + RED) = *(fcol + GRN) = *(fcol + BLU) = 0;
    }
    else
    {
        Real32 f = ldexp(1., rgbe[EXP]-(COLXS+8));
        *(fcol + RED) = (rgbe[RED]+.5)*f;
        *(fcol + GRN) = (rgbe[GRN]+.5)*f;
        *(fcol + BLU) = (rgbe[BLU]+.5)*f;
    }
}

void HDRImageFileType::RGBE2Half(RGBE rgbe, Real16 *fcol)
{
    if(rgbe[EXP] == 0)
    {
        *(fcol + RED) = *(fcol + GRN) = *(fcol + BLU) = 0;
    }
    else
    {
        Real32 f = ldexp(1., rgbe[EXP]-(COLXS+8));

        *(fcol + RED) = Real16( ( rgbe[RED]+.5) * f);
        *(fcol + GRN) = Real16( ( rgbe[GRN]+.5) * f);
        *(fcol + BLU) = Real16( ( rgbe[BLU]+.5) * f);
    }
}

int HDRImageFileType::fwritecolrs(std:: ostream &os, 
                                  const Real32  *scan, 
                                        RGBE    *rgbe_scan,
                                        int      width, 
                                        int      height   )
{
    // convert scanline
    for (int i=0;i<width;i++)
    {
        float2RGBE(scan, rgbe_scan[i]);
        scan += 3;
    }

    return fwriteRGBE(os, rgbe_scan, width, height);
}

int HDRImageFileType::fwritecolrs(std:: ostream &os, 
                                  const Real16  *scan, 
                                        RGBE    *rgbe_scan,
                                        int      width, 
                                        int      height)
{
    // convert scanline
    for(int i=0;i<width;i++)
    {
        half2RGBE(scan, rgbe_scan[i]);
        scan += 3;
    }

    return fwriteRGBE(os, rgbe_scan, width, height);
}

int HDRImageFileType::fwriteRGBE(std::ostream &os,  
                                      RGBE    *rgbe_scan, 
                                      int      width, 
                                      int      height)
{
    int i, j, beg, c2, cnt=0;

    if ((width < MINELEN) | (width > MAXELEN))
    {
        // OOBs, write out flat
        os.write(reinterpret_cast<char *>(rgbe_scan), width);
        return 0;
    }

    // put magic header
    os << static_cast<unsigned char>(2);
    os << static_cast<unsigned char>(2);
    os << static_cast<unsigned char>(width>>8);
    os << static_cast<unsigned char>(width&255);

    // put components seperately
    for (i=0;i<4;i++)
    {
        for (j=0;j<width;j+=cnt)
        {
            // find next run
            for (beg=j;beg<width;beg+=cnt)
            {
                for(cnt=1; 
                    (cnt<127)&&
                        ((beg+cnt)<width)&&
                        (rgbe_scan[beg+cnt][i]==rgbe_scan[beg][i]); 
                    cnt++) ;

                if (cnt>=MINRUN)
                    break;
                    // long enough
            }
            if (((beg-j)>1) && ((beg-j) < MINRUN))
            {
                c2 = j+1;
                while (rgbe_scan[c2++][i] == rgbe_scan[j][i])
                {
                    if (c2 == beg)
                    {
                        // short run
                        os << static_cast<unsigned char>(128+beg-j);
                        os << static_cast<unsigned char>(rgbe_scan[j][i]);
                        j = beg;
                        break;
                    }
                }
            }
            while (j < beg)
            {
                // write out non-run
                if ((c2 = beg-j) > 128)
                    c2 = 128;
                os << static_cast<unsigned char>(c2);
                
                while (c2--)
                    os << rgbe_scan[j++][i];
            }
            if (cnt >= MINRUN)
            {
                // write out run
                os << static_cast<unsigned char>(128+cnt);
                os << rgbe_scan[beg][i];
            }
            else
            {
                cnt = 0;
            }
        }
    }
    return (os.fail() ? -1 : 0);
}

//float color -> rgbe
void HDRImageFileType::float2RGBE(const Real32 *fcol, RGBE rgbe)
{
    Real32 d = (*(fcol + RED) > *(fcol + GRN)) ? *(fcol + RED) : *(fcol + GRN);
    
    if(*(fcol + BLU) > d)
    {
        d = *(fcol + BLU);
    }
    if(d <= 1e-32f)
    {
        rgbe[RED] = rgbe[GRN] = rgbe[BLU] = rgbe[EXP] = 0;
    }
    else
    {
        int e;
        d = frexp(d, &e) * 256.f / d;
        rgbe[RED] = static_cast<unsigned char>(*(fcol + RED) * d);
        rgbe[GRN] = static_cast<unsigned char>(*(fcol + GRN) * d);
        rgbe[BLU] = static_cast<unsigned char>(*(fcol + BLU) * d);
        rgbe[EXP] = static_cast<unsigned char>(e + COLXS);
    }
}

//half color -> rgbe
void HDRImageFileType::half2RGBE(const Real16 *fcol, RGBE rgbe)
{
    Real32 d = (*(fcol + RED) > *(fcol + GRN)) ? *(fcol + RED) : *(fcol + GRN);
    
    if(*(fcol + BLU) > d)
    {
        d = *(fcol + BLU);
    }
    if(d <= 1e-32f)
    {
        rgbe[RED] = rgbe[GRN] = rgbe[BLU] = rgbe[EXP] = 0;
    }
    else
    {
        int e;
        d = frexp(d, &e) * 256.f / d;
        rgbe[RED] = static_cast<unsigned char>(*(fcol + RED) * d);
        rgbe[GRN] = static_cast<unsigned char>(*(fcol + GRN) * d);
        rgbe[BLU] = static_cast<unsigned char>(*(fcol + BLU) * d);
        rgbe[EXP] = static_cast<unsigned char>(e + COLXS);
    }
}

OSG_END_NAMESPACE
