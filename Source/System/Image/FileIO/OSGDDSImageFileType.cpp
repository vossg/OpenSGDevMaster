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
//  Includes
//-------------------------------

#include <cstdlib>
#include <cstdio>
#include <cassert>

#include "OSGConfig.h"

#include <string>
#include <vector>

#include <iostream>
#include <fstream>

#include "OSGLog.h"

#include "OSGImage.h"

#include "OSGDDSImageFileType.h"

#ifdef OSG_SGI_STL

//#include <limits>
#ifndef INT_MAX
#define INT_MAX numeric_limits<Int32>::max()
#endif
#else
#include <climits>
#endif

// Static Class Varible implementations:
static const OSG::Char8 *suffixArray[] =
{
    "dds"
};

OSG_BEGIN_NAMESPACE

/*! \class DDSImageFileType 

  Image File Type to read/write and store/restore Image objects as
  DDS data. Should work with binary and ascii dds/pbm/pgm/ppm data.
  
  All the type specific code is included in the class. Does
  not depend on external libs.
  
*/

DDSImageFileType DDSImageFileType::_the("image/x-dds",
                                        suffixArray, 
                                        sizeof(suffixArray),
                                        (OSG_READ_SUPPORTED | 
                                         OSG_WRITE_SUPPORTED));

#ifdef WIN32
#  include <windows.h>
#endif

const UInt32 DDS_ALPHAPIXELS = 0x00000001;
const UInt32 DDS_ALPHA       = 0x00000002;
const UInt32 DDS_FOURCC      = 0x00000004;
const UInt32 DDS_RGB         = 0x00000040;
const UInt32 DDS_RGBA        = 0x00000041;
const UInt32 DDS_DEPTH       = 0x00800000;
const UInt32 DDS_COMPRESSED  = 0x00000080;
const UInt32 DDS_LUMINANCE   = 0x00020000;

const UInt32 DDS_COMPLEX = 0x00000008;
const UInt32 DDS_CUBEMAP = 0x00000200;
const UInt32 DDS_VOLUME  = 0x00200000;

const UInt32 FOURCC_DXT1 = 0x31545844;
const UInt32 FOURCC_DXT3 = 0x33545844;
const UInt32 FOURCC_DXT5 = 0x35545844;

/*! \nohierarchy
 */

struct DDS_PIXELFORMAT 
{
    UInt32 dwSize;
    UInt32 dwFlags;
    UInt32 dwFourCC;
    UInt32 dwRGBBitCount;
    UInt32 dwRBitMask;
    UInt32 dwGBitMask;
    UInt32 dwBBitMask;
    UInt32 dwABitMask;
};

/*! \nohierarchy
 */

struct DXTColBlock 
{
    UInt16 col0;
    UInt16 col1;
    
    UInt8  row[4];
};

/*! \nohierarchy
 */

struct DXT3AlphaBlock 
{
    UInt16 row[4];
};

/*! \nohierarchy
 */

struct DXT5AlphaBlock
{
    UInt8 alpha0;
    UInt8 alpha1;
    
    UInt8 row[6];
};

/*! \nohierarchy
 */

struct DDS_HEADER 
{
    UInt32          dwSize;
    UInt32          dwFlags;
    UInt32          dwHeight;
    UInt32          dwWidth;
    UInt32          dwPitchOrLinearSize;
    UInt32          dwDepth;
    UInt32          dwMipMapCount;
    UInt32          dwReserved1[11];
    DDS_PIXELFORMAT ddspf;
    UInt32          dwCaps1;
    UInt32          dwCaps2;
    UInt32          dwReserved2[3];
};

/*! \nohierarchy
 */

class CSurface
{
    friend class CTexture;
    friend class CDDSImage;    
    
  public:

    CSurface();
    CSurface(Int32 w, Int32 h, Int32 d, Int32 imgsize);
    CSurface(const CSurface &copy);
    CSurface &operator= (const CSurface &rhs);
    virtual ~CSurface();
  
    operator char *();
  
    void create(Int32 w, Int32 h, Int32 d, Int32 imgsize);
    void clear();
    
    Int32   get_width () { return width; }
    Int32   get_height() { return height; }
    Int32   get_depth () { return depth; }
    Int32   get_size  () { return size; }
    char*   get_pixels() { return pixels; }
    
  protected:

    Int32 width;
    Int32 height;
    Int32 depth;
    Int32 size;
    
    char *pixels;       
};

/*! \nohierarchy
 */

class CTexture : public CSurface
{
    friend class CDDSImage;
    
  public:
    
    CTexture();
    CTexture(Int32 w, Int32 h, Int32 d, Int32 imgSize);
    CTexture(const CTexture &copy);
    CTexture &operator= (const CTexture &rhs);
    ~CTexture();
    
    CSurface &get_mipmap(Int32 index) 
    { 
        assert(index < Int32(mipmaps.size()));
        return mipmaps[index]; 
    }
  
    int get_num_mipmaps() { return Int32(mipmaps.size()); }

  protected:
    std::vector<CSurface> mipmaps;
};

/*! \nohierarchy
 */

class CDDSImage
{
  public:
    CDDSImage();
    ~CDDSImage();
    
    bool load(std::istream &is, 
              bool flipImage = true, 
              bool swapCubeMap = true,
              bool flipCubeMap = false);
    void clear();
    
    operator char*();
    CTexture &operator[](Int32 index);
    
    Int32 get_num_images(void) { return Int32(images.size()); }
    CTexture &get_image(Int32 index) 
    {
        assert(index < Int32(images.size()));
        return images[index];
    }
    
    Int32 get_components() { return components; }
    Int32 get_format    () { return format; }
  
    bool is_compressed() { return compressed; }
    bool is_cubemap() { return cubemap; }
    bool is_volume() { return volume; }
    bool is_valid() { return valid; }
    
  private:

    Int32 clamp_size(Int32 size);
    Int32 get_line_width(Int32 width, Int32 bpp);
    Int32 size_dxtc(Int32 width, Int32 height);
    Int32 size_rgb(Int32 width, Int32 height);
    void swap_endian(void *val);
    void align_memory(CTexture *surface);
    
    void flip (char *image, Int32 width, Int32 height, Int32 depth, Int32 size);
    bool check_dxt1_alpha_data (char *image, Int32 size);
    
    void swap(void *byte1, void *byte2, Int32 size);
    
    void flip_blocks_dxtc1(DXTColBlock *line, Int32 numBlocks);
    void flip_blocks_dxtc3(DXTColBlock *line, Int32 numBlocks);
    void flip_blocks_dxtc5(DXTColBlock *line, Int32 numBlocks);
    void flip_dxt5_alpha(DXT5AlphaBlock *block);
    
    Int32 format;
    Int32 components;
    bool compressed;
    bool cubemap;
    bool volume;
    bool valid;
    
    std::vector<CTexture> images;
};


void DDSImageFileType::setFlipImage(bool s)
{
    _flipImage = s;
}

bool DDSImageFileType::getFlipImage(void)
{
    return _flipImage;
}

void DDSImageFileType::setFlipCubeMap(bool s)
{
    _flipCubeMap = s;
}

bool DDSImageFileType::getFlipCubeMap(void)
{
    return _flipCubeMap;
}

void DDSImageFileType::setSwapCubeMap(bool s)
{
    _swapCubeMap = s;
}

bool DDSImageFileType::getSwapCubeMap(void)
{
    return _swapCubeMap;
}


//-------------------------------------------------------------------------
/*! Tries to fill the image object with the data read from
    the given stream. Returns true on success.
 */

bool DDSImageFileType::read(      Image        *pImage, 
                                  std::istream &is, 
                            const std::string  &mimetype)
{
    bool validImage = false;
    
    CDDSImage ddsImage;
    
    Int32 i,j,w,h,d, mm = 0, components, format,size;
    Int32 width = 0, height = 0, depth = 0, numMipMaps = 0;
    bool isCompressed, isCubeMap, isVolume;
    UInt8 *data;
    UInt32 dataSize = 0;
    
    SINFO << "DDS File Info: " << ": ";
    
    if(ddsImage.load(is, _flipImage, _swapCubeMap, _flipCubeMap) && 
       (validImage = ddsImage.is_valid())) 
    {
        components   = ddsImage.get_components();
        format       = ddsImage.get_format();
        isCompressed = ddsImage.is_compressed();
        isCubeMap    = ddsImage.is_cubemap();
        isVolume     = ddsImage.is_volume();
        
        SINFO << "cs: "   << components 
              << ", f: "  << format
              << ", cd: " << isCompressed 
              << ", cm: " << isCubeMap
              << ", vo: " << isVolume
              << endLog;

        for (i = 0; i < ddsImage.get_num_images(); ++i) 
        {
            w    = ddsImage[i].get_width();
            h    = ddsImage[i].get_height();
            d    = ddsImage[i].get_depth();
            size = ddsImage[i].get_size();

            dataSize += size;

            mm = ddsImage[i].get_num_mipmaps();    

            if(i) 
            {
                if((w != width) || (h != height) || (d != depth) ||
                   (mm != numMipMaps) )
                {
                    validImage = false;
                }
            }
            else 
            {
                width      = w;
                height     = h;
                depth      = d;
                numMipMaps = mm;
            }
            
            SINFO << "  " << i 
                  << ", " << w << "x" << h << "x" << d 
                  << ", size: " << size 
                  << ", mm: " << mm
                  << endLog;

            for (j = 0; j < mm; ++j) 
            {
                w = ddsImage[i].get_mipmap(j).get_width();
                h = ddsImage[i].get_mipmap(j).get_height();
                d = ddsImage[i].get_mipmap(j).get_depth();
                size = ddsImage[i].get_mipmap(j).get_size();
                dataSize += size;
                
                SINFO << "    " << j 
                      << ", " << w << "x" << h << "x" << d 
                      << ", size: " << size 
                      << ", mm: " << mm
                      << endLog;
                
            }
        }
        
        if(validImage) 
        {
            pImage->set( OSG::Image::PixelFormat(format), 
                        width, height, depth,
                        numMipMaps + 1,
                        1, 0.0, 0, OSG::Image::OSG_UINT8_IMAGEDATA,
                        true, 
                        ddsImage.get_num_images() );
            
            if(dataSize == pImage->getSize()) 
            {
                data = pImage->editData();
                
                // copy data;
                for (i = 0; i < ddsImage.get_num_images(); ++i) 
                {
                    size = ddsImage[i].get_size();
                    memcpy (data, ddsImage[i].get_pixels(), size);
                    data += size;
                    for(j = 0; j < mm; ++j) 
                    {
                        size = ddsImage[i].get_mipmap(j).get_size();

                        memcpy (data, 
                                ddsImage[i].get_mipmap(j).get_pixels(), 
                                size);
                        data += size;
                    }
                }
            }
            else 
            {
                SWARNING << "ERROR: Invalid data size; cannot cp dds data"
                         << endLog;
                
            }
        }
    }
    else
    {
        SWARNING << "DDS Load Failed !" << endLog;
    }
    
    return validImage;;
}

//-------------------------------------------------------------------------
/*! Tries to write the image object to the given fileName.
  Returns true on success.
 */

bool DDSImageFileType::write(const Image        *, 
                                   std::ostream &, 
                             const std::string  &)
{
    SWARNING << getMimeType()
             << " write is not implemented "
             << endLog;
    
    return false;
}


//-------------------------------------------------------------------------
/*!
  Tries to determine the mime type of the data provided by an input stream
  by searching for magic bytes. Returns the mime type or an empty string
  when the function could not determine the mime type.
 */

std::string DDSImageFileType::determineMimetypeFromStream(std::istream &is)
{
    char filecode[4];

    is.read(filecode, 4);
    is.seekg(-4, std::ios::cur);
    
    return strncmp(filecode, "DDS ", 4) == 0 ?
        std::string(getMimeType()) : std::string();
}

/**constructors & destructors**/

//-------------------------------------------------------------------------
/*! Constructor used for the singleton object
 */

DDSImageFileType::DDSImageFileType(const Char8  *mimeType,
                                   const Char8  *suffixArray[],
                                         UInt16  suffixByteCount,
                                         UInt32  flags          ) :

     Inherited  (mimeType,suffixArray, suffixByteCount, flags),
    _flipImage  (true ),
    _flipCubeMap(false),
    _swapCubeMap(false)
{
}

//-------------------------------------------------------------------------
/*! Destructor
 */

DDSImageFileType::~DDSImageFileType(void)
{
}


///////////////////////////////////////////////////////////////////////////////
// CDDSImage public functions

///////////////////////////////////////////////////////////////////////////////
// default constructor

CDDSImage::CDDSImage() : 
    format(0),
    components(0),
    compressed(false),
    cubemap(false),
    volume(false),
    valid(false)
{
}

CDDSImage::~CDDSImage()
{
}

///////////////////////////////////////////////////////////////////////////////
// Swap the bytes in a 32 bit value
inline void CDDSImage::swap_endian(void *val)
{
#if BYTE_ORDER == BIG_ENDIAN
    UInt32 *ival = (UInt32 *)val;

    *ival = ((*ival >> 24) & 0x000000ff) |
            ((*ival >>  8) & 0x0000ff00) |
            ((*ival <<  8) & 0x00ff0000) |
            ((*ival << 24) & 0xff000000);
#endif
}

///////////////////////////////////////////////////////////////////////////////
// clamps input size to [1-size]
inline int CDDSImage::clamp_size(Int32 size)
{
    if (size <= 0)
        size = 1;

    return size;
}


///////////////////////////////////////////////////////////////////////////////
// loads DDS image
//
// filename - fully qualified name of DDS image
// flipImage - specifies whether image is flipped on load, default is true

bool CDDSImage::load(std::istream &is, 
                     bool flipImage, 
                     bool swapCubeMap, 
                     bool flipCubeMap)
{
    DDS_HEADER ddsh;
    char filecode[4];
    Int32 width, height, depth;
    Int32 (CDDSImage::*sizefunc)(Int32, Int32);

    // clear any previously loaded images
    clear();
    
    // read in file marker, make sure its a DDS file
    is.read(filecode, 4);
    if (strncmp(filecode, "DDS ", 4) != 0)
        return false;

    // read in DDS header
    is.read(reinterpret_cast<char*>(&ddsh), sizeof(ddsh));

    swap_endian(&ddsh.dwSize);
    swap_endian(&ddsh.dwFlags);
    swap_endian(&ddsh.dwHeight);
    swap_endian(&ddsh.dwWidth);
    swap_endian(&ddsh.dwPitchOrLinearSize);
    swap_endian(&ddsh.dwDepth);
    swap_endian(&ddsh.dwMipMapCount);
    swap_endian(&ddsh.ddspf.dwSize);
    swap_endian(&ddsh.ddspf.dwFlags);
    swap_endian(&ddsh.ddspf.dwFourCC);
    swap_endian(&ddsh.ddspf.dwRGBBitCount);
    swap_endian(&ddsh.dwCaps1);
    swap_endian(&ddsh.dwCaps2);

    // check if image is a cubempa
    if (ddsh.dwCaps2 & DDS_CUBEMAP)
        cubemap = true;

    // check if image is a volume texture
    if ((ddsh.dwCaps2 & DDS_VOLUME) && (ddsh.dwDepth > 0))
        volume = true;

    // figure out what the image format is
    if (ddsh.ddspf.dwFlags & DDS_FOURCC) 
    {
        switch(ddsh.ddspf.dwFourCC)
        {
            case FOURCC_DXT1:
                format = GL_COMPRESSED_RGB_S3TC_DXT1_EXT;
                components = 3;
                compressed = true;
                break;
            case FOURCC_DXT3:
                format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
                components = 4;
                compressed = true;
                break;
            case FOURCC_DXT5:
                format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
                components = 4;
                compressed = true;
                break;
            default:
                SWARNING << "ERROR: unknown compressed format(" 
                         << ddsh.ddspf.dwFourCC
                         << ")!" 
                         << endLog;
                return false;
        }
    }
    else if (ddsh.ddspf.dwFlags == DDS_RGBA && ddsh.ddspf.dwRGBBitCount == 32)
    {
        format = Image::OSG_BGRA_PF; 
        compressed = false;
        components = 4;
    }
    else if (ddsh.ddspf.dwFlags == DDS_RGB  && ddsh.ddspf.dwRGBBitCount == 32)
    {
        format = Image::OSG_BGRA_PF; 
        compressed = false;
        components = 4;
    }
    else if (ddsh.ddspf.dwFlags == DDS_RGB  && ddsh.ddspf.dwRGBBitCount == 24)
    {
        format = Image::OSG_BGR_PF; 
        compressed = false;
        components = 3;
    }
    else if (/*ddsh.ddspf.dwFlags == 0x20000  &&*/ ddsh.ddspf.dwRGBBitCount == 8)
    {
        format = Image::OSG_L_PF; 
        compressed = false;
        components = 1;
    }
    else 
    {
        SWARNING << "ERROR: unknown image format!" << endLog;
        return false;
    }
    
    // store primary surface width/height/depth
    width = ddsh.dwWidth;
    height = ddsh.dwHeight;
    depth = clamp_size(ddsh.dwDepth);   // set to 1 if 0
    
    // use correct size calculation function depending on whether image is 
    // compressed
    sizefunc = (compressed ? &CDDSImage::size_dxtc : &CDDSImage::size_rgb);

    // load all surfaces for the image (6 surfaces for cubemaps)
    for(Int32 n = 0; n < (cubemap ? 6 : 1); n++)
    {
        Int32 size; 

        // calculate surface size
        size = (this->*sizefunc)(width, height)*depth;

        // load surface
        CTexture img(width, height, depth, size);
        is.read(img, img.size);

        align_memory(&img);
        
        if((format == GL_COMPRESSED_RGB_S3TC_DXT1_EXT) &&
           check_dxt1_alpha_data(img, img.size))
        {
            format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
        }

        if ((flipImage && !cubemap) || (flipCubeMap && cubemap))
            flip(img, img.width, img.height, img.depth, img.size);
        
        Int32 w = clamp_size(width >> 1);
        Int32 h = clamp_size(height >> 1);
        Int32 d = clamp_size(depth >> 1); 

        // store number of mipmaps
        Int32 numMipmaps = ddsh.dwMipMapCount;

        // number of mipmaps in file includes main surface so decrease count 
        // by one
        if (numMipmaps != 0)
            numMipmaps--;

        // load all mipmaps for current surface
        for (Int32 i = 0; i < numMipmaps && (w || h); i++)
        {
            // calculate mipmap size
            size = (this->*sizefunc)(w, h)*d;

            CSurface mipmap(w, h, d, size);
            is.read(mipmap, mipmap.size);

            if ((flipImage && !cubemap) || (flipCubeMap && cubemap))
            {
                flip(mipmap, mipmap.width, mipmap.height, mipmap.depth, 
                     mipmap.size);
            }

            img.mipmaps.push_back(mipmap);

            // shrink to next power of 2
            w = clamp_size(w >> 1);
            h = clamp_size(h >> 1);
            d = clamp_size(d >> 1); 
        }

        images.push_back(img);
    }

    // swap cubemaps on y axis (since image is flipped in OGL)
    if (cubemap && swapCubeMap)
    {
        CTexture tmp;
        tmp = images[3];
        images[3] = images[2];
        images[2] = tmp;
    }

    valid = true;

    return true;
}

///////////////////////////////////////////////////////////////////////////////
// free image memory

void CDDSImage::clear()
{
    components = 0;
    format = 0;
    compressed = false;
    cubemap = false;
    volume = false;
    valid = false;

    images.clear();
}

///////////////////////////////////////////////////////////////////////////////
// returns individual texture when multiple textures are loaded (as is the case
// with volume textures and cubemaps)

CTexture &CDDSImage::operator[](Int32 index)
{ 
    // make sure an image has been loaded
    assert(valid);
    assert(index < Int32(images.size()));

    return images[index]; 
}

///////////////////////////////////////////////////////////////////////////////
// returns pointer to main image
CDDSImage::operator char*()
{ 
    assert(valid);

    return images[0]; 
}


///////////////////////////////////////////////////////////////////////////////
// CDDSImage private functions
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// calculates 4-byte aligned width of image
inline int CDDSImage::get_line_width(Int32 width, Int32 bpp)
{
    return ((width * bpp + 31) & -32) >> 3;
}

///////////////////////////////////////////////////////////////////////////////
// calculates size of DXTC texture in bytes
int CDDSImage::size_dxtc(Int32 width, Int32 height)
{
    Int32 comp( ( (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ||
                  (format == GL_COMPRESSED_RGB_S3TC_DXT1_EXT) ) ? 8 : 16 );
    
    return ((width+3)/4)*((height+3)/4)*comp;
}

///////////////////////////////////////////////////////////////////////////////
// calculates size of uncompressed RGB texture in bytes
int CDDSImage::size_rgb(Int32 width, Int32 height)
{
    return width*height*components;
}

///////////////////////////////////////////////////////////////////////////////
// align to 4 byte boundary (add pad bytes to end of each line in the image)
void CDDSImage::align_memory(CTexture *surface)
{
    // don't bother with compressed images, volume textures, or cubemaps
    if (compressed || volume || cubemap)
        return;

    // calculate new image size
    Int32 linesize = get_line_width(surface->width, components*8);
    Int32 imagesize = linesize*surface->height;

    // exit if already aligned
    if (surface->size == imagesize)
        return;

    // create new image of new size
    CTexture newSurface(surface->width, surface->height, surface->depth, 
                        imagesize);

    // add pad bytes to end of each line
    char *srcimage = static_cast<char*>(*surface);
    char *dstimage = static_cast<char*>(newSurface);
    for (Int32 n = 0; n < surface->depth; n++)
    {
        char *curline = srcimage;
        char *newline = dstimage;

        Int32 imsize = surface->size / surface->depth;
        Int32 lnsize = imsize / surface->height;
        
        for (Int32 i = 0; i < surface->height; i++)
        {
            memcpy(newline, curline, lnsize);
            newline += linesize;
            curline += lnsize;
        }
    }

    // save padded image
    *surface = newSurface;
}

///////////////////////////////////////////////////////////////////////////////
// flip image around X axis
bool CDDSImage::check_dxt1_alpha_data (char *image, Int32 size)
{
  bool        hasAlpha(false);
  DXTColBlock *colBlock(reinterpret_cast<DXTColBlock*>(image));

  for (unsigned i = 0, n = (size / 8); i < n; i++)
    if (colBlock[i].col0 <= colBlock[i].col1) 
    {
        for (unsigned j = 0; j < 4; j++) {
          UInt8 byte = colBlock[i].row[j];
          for (unsigned p = 0; p < 4; p++/*, byte >> 2*/) {
            if ((byte & 3) == 3) {
              hasAlpha = true;
              break;
            }
          }
        }

        if (hasAlpha) 
        {
          FNOTICE (( "Found alpha in DXT1 %d/%d, col0:%d, col1:%d\n",
                     i, n, colBlock[i].col0, colBlock[i].col1 ));

          for (unsigned j = 0; j < 4; j++) 
            FNOTICE (( "  DXT Col Index: %d %d %d %d\n",
                       ((colBlock[i].row[j] >> 0) & 3),
                       ((colBlock[i].row[j] >> 2) & 3),
                       ((colBlock[i].row[j] >> 4) & 3),
                       ((colBlock[i].row[j] >> 6) & 3) ));
        }

        if (hasAlpha)
          break;
    }

  return hasAlpha;
}

///////////////////////////////////////////////////////////////////////////////
// flip image around X axis
void CDDSImage::flip(char *image, Int32 width, Int32 height, Int32 depth, Int32 size)
{
    Int32 linesize;
    Int32 offset;

    if (!compressed)
    {
        assert(depth > 0);

        Int32 imagesize = size/depth;
        linesize = imagesize / height;

        for (Int32 n = 0; n < depth; n++)
        {
            offset = imagesize*n;
            char *top = image + offset;
            char *bottom = top + (imagesize-linesize);
    
            for (Int32 i = 0; i < (height >> 1); i++)
            {
                swap(bottom, top, linesize);

                top += linesize;
                bottom -= linesize;
            }
        }
    }
    else
    {
        void (CDDSImage::*flipblocks)(DXTColBlock*, Int32);
        Int32 xblocks = width / 4;
        Int32 yblocks = height / 4;
        Int32 blocksize;

        switch (format)
        {
            case GL_COMPRESSED_RGB_S3TC_DXT1_EXT:
                blocksize = 8;
                flipblocks = &CDDSImage::flip_blocks_dxtc1;
                break;
            case GL_COMPRESSED_RGBA_S3TC_DXT1_EXT: 
                blocksize = 8;
                flipblocks = &CDDSImage::flip_blocks_dxtc1; 
                break;
            case GL_COMPRESSED_RGBA_S3TC_DXT3_EXT: 
                blocksize = 16;
                flipblocks = &CDDSImage::flip_blocks_dxtc3; 
                break;
            case GL_COMPRESSED_RGBA_S3TC_DXT5_EXT: 
                blocksize = 16;
                flipblocks = &CDDSImage::flip_blocks_dxtc5; 
                break;
            default:
                return;
        }

        linesize = xblocks * blocksize;

        DXTColBlock *top;
        DXTColBlock *bottom;
    
        for (Int32 j = 0; j < (yblocks >> 1); j++)
        {
            top = reinterpret_cast<DXTColBlock*>(image + j * linesize);
            bottom = reinterpret_cast<DXTColBlock*>(image + (((yblocks-j)-1) * linesize));

            (this->*flipblocks)(top, xblocks);
            (this->*flipblocks)(bottom, xblocks);

            swap(bottom, top, linesize);
        }
    }
}    

///////////////////////////////////////////////////////////////////////////////
// swap to sections of memory
void CDDSImage::swap(void *byte1, void *byte2, Int32 size)
{
    UInt8 *tmp = new UInt8[size];

    memcpy(tmp, byte1, size);
    memcpy(byte1, byte2, size);
    memcpy(byte2, tmp, size);

    delete [] tmp;
}

///////////////////////////////////////////////////////////////////////////////
// flip a DXT1 color block
void CDDSImage::flip_blocks_dxtc1(DXTColBlock *line, Int32 numBlocks)
{
    DXTColBlock *curblock = line;

    for (Int32 i = 0; i < numBlocks; i++)
    {
        swap(&curblock->row[0], &curblock->row[3], sizeof(UInt8));
        swap(&curblock->row[1], &curblock->row[2], sizeof(UInt8));

        curblock++;
    }
}

///////////////////////////////////////////////////////////////////////////////
// flip a DXT3 color block
void CDDSImage::flip_blocks_dxtc3(DXTColBlock *line, Int32 numBlocks)
{
    DXTColBlock *curblock = line;
    DXT3AlphaBlock *alphablock;

    for (Int32 i = 0; i < numBlocks; i++)
    {
        alphablock = reinterpret_cast<DXT3AlphaBlock*>(curblock);

        swap(&alphablock->row[0], &alphablock->row[3], sizeof(UInt16));
        swap(&alphablock->row[1], &alphablock->row[2], sizeof(UInt16));

        curblock++;

        swap(&curblock->row[0], &curblock->row[3], sizeof(UInt8));
        swap(&curblock->row[1], &curblock->row[2], sizeof(UInt8));

        curblock++;
    }
}

///////////////////////////////////////////////////////////////////////////////
// flip a DXT5 alpha block
void CDDSImage::flip_dxt5_alpha(DXT5AlphaBlock *block)
{
    UInt8 gBits[4][4];
    
    const UInt32 mask = 0x00000007;          // bits = 00 00 01 11
    UInt32 bits = 0;
    memcpy(&bits, &block->row[0], sizeof(UInt8) * 3);

    gBits[0][0] = UInt8(bits & mask);
    bits >>= 3;
    gBits[0][1] = UInt8(bits & mask);
    bits >>= 3;
    gBits[0][2] = UInt8(bits & mask);
    bits >>= 3;
    gBits[0][3] = UInt8(bits & mask);
    bits >>= 3;
    gBits[1][0] = UInt8(bits & mask);
    bits >>= 3;
    gBits[1][1] = UInt8(bits & mask);
    bits >>= 3;
    gBits[1][2] = UInt8(bits & mask);
    bits >>= 3;
    gBits[1][3] = UInt8(bits & mask);

    bits = 0;
    memcpy(&bits, &block->row[3], sizeof(UInt8) * 3);

    gBits[2][0] = UInt8(bits & mask);
    bits >>= 3;
    gBits[2][1] = UInt8(bits & mask);
    bits >>= 3;
    gBits[2][2] = UInt8(bits & mask);
    bits >>= 3;
    gBits[2][3] = UInt8(bits & mask);
    bits >>= 3;
    gBits[3][0] = UInt8(bits & mask);
    bits >>= 3;
    gBits[3][1] = UInt8(bits & mask);
    bits >>= 3;
    gBits[3][2] = UInt8(bits & mask);
    bits >>= 3;
    gBits[3][3] = UInt8(bits & mask);

    UInt32 *pBits = (reinterpret_cast<UInt32 *>(&(block->row[0])));

    *pBits = *pBits | (gBits[3][0] << 0);
    *pBits = *pBits | (gBits[3][1] << 3);
    *pBits = *pBits | (gBits[3][2] << 6);
    *pBits = *pBits | (gBits[3][3] << 9);

    *pBits = *pBits | (gBits[2][0] << 12);
    *pBits = *pBits | (gBits[2][1] << 15);
    *pBits = *pBits | (gBits[2][2] << 18);
    *pBits = *pBits | (gBits[2][3] << 21);

    pBits = (reinterpret_cast<UInt32 *>(&(block->row[3])));

#if BYTE_ORDER == BIG_ENDIAN
    *pBits &= 0x000000ff;
#else
    *pBits &= 0xff000000;
#endif

    *pBits = *pBits | (gBits[1][0] << 0);
    *pBits = *pBits | (gBits[1][1] << 3);
    *pBits = *pBits | (gBits[1][2] << 6);
    *pBits = *pBits | (gBits[1][3] << 9);

    *pBits = *pBits | (gBits[0][0] << 12);
    *pBits = *pBits | (gBits[0][1] << 15);
    *pBits = *pBits | (gBits[0][2] << 18);
    *pBits = *pBits | (gBits[0][3] << 21);
}

///////////////////////////////////////////////////////////////////////////////
// flip a DXT5 color block
void CDDSImage::flip_blocks_dxtc5(DXTColBlock *line, Int32 numBlocks)
{
    DXTColBlock *curblock = line;
    DXT5AlphaBlock *alphablock;
    
    for (Int32 i = 0; i < numBlocks; i++)
    {
        alphablock = reinterpret_cast<DXT5AlphaBlock*>(curblock);
        
        flip_dxt5_alpha(alphablock);

        curblock++;

        swap(&curblock->row[0], &curblock->row[3], sizeof(UInt8));
        swap(&curblock->row[1], &curblock->row[2], sizeof(UInt8));

        curblock++;
    }
}

///////////////////////////////////////////////////////////////////////////////
// CTexture implementation
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// default constructor
CTexture::CTexture()
  : CSurface()  // initialize base class part
{
}

///////////////////////////////////////////////////////////////////////////////
// creates an empty texture
CTexture::CTexture(Int32 w, Int32 h, Int32 d, Int32 imgSize)
  : CSurface(w, h, d, imgSize)  // initialize base class part
{
}

///////////////////////////////////////////////////////////////////////////////
// copy constructor
CTexture::CTexture(const CTexture &copy)
  : CSurface(copy)
{
    for (UInt32 i = 0; i < copy.mipmaps.size(); i++)
        mipmaps.push_back(copy.mipmaps[i]);
}

///////////////////////////////////////////////////////////////////////////////
// assignment operator
CTexture &CTexture::operator= (const CTexture &rhs)
{
    if (this != &rhs)
    {
        CSurface::operator = (rhs);

        mipmaps.clear();
        for (UInt32 i = 0; i < rhs.mipmaps.size(); i++)
        {
            mipmaps.push_back(rhs.mipmaps[i]);
        }
    }

    return *this;
}

///////////////////////////////////////////////////////////////////////////////
// clean up texture memory
CTexture::~CTexture()
{
    mipmaps.clear();
}

///////////////////////////////////////////////////////////////////////////////
// CSurface implementation
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// default constructor
CSurface::CSurface()
  : width(0),
    height(0),
    depth(0),
    size(0),
    pixels(NULL)
{
}

///////////////////////////////////////////////////////////////////////////////
// creates an empty image
CSurface::CSurface(Int32 w, Int32 h, Int32 d, Int32 imgsize)
{
    pixels = NULL;
    create(w, h, d, imgsize);
}

///////////////////////////////////////////////////////////////////////////////
// copy constructor
CSurface::CSurface(const CSurface &copy)
  : width(0),
    height(0),
    depth(0),
    size(0),
    pixels(NULL)
{

    if (copy.pixels)
    {
        size = copy.size;
        width = copy.width;
        height = copy.height;
        depth = copy.depth;
        pixels = new char[size];
        memcpy(pixels, copy.pixels, copy.size);
    }
}

///////////////////////////////////////////////////////////////////////////////
// assignment operator
CSurface &CSurface::operator= (const CSurface &rhs)
{
    if (this != &rhs)
    {
        clear();

        if (rhs.pixels)
        {
            size = rhs.size;
            width = rhs.width;
            height = rhs.height;
            depth = rhs.depth;

            pixels = new char[size];
            memcpy(pixels, rhs.pixels, size);
        }
    }

    return *this;
}

///////////////////////////////////////////////////////////////////////////////
// clean up image memory

CSurface::~CSurface()
{
    clear();
}

///////////////////////////////////////////////////////////////////////////////
// returns a pointer to image

CSurface::operator char*()
{ 
    return pixels; 
}

///////////////////////////////////////////////////////////////////////////////
// creates an empty image

void CSurface::create(Int32 w, Int32 h, Int32 d, Int32 imgsize)
{
    clear();

    width = w;
    height = h;
    depth = d;
    size = imgsize;
    pixels = new char[imgsize];
}

///////////////////////////////////////////////////////////////////////////////
// free surface memory

void CSurface::clear()
{
    delete [] pixels;
    pixels = NULL;
}

OSG_END_NAMESPACE
