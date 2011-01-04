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
 *                                                                           *
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

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#include "OSGGL.h"
#include "OSGGLEXT.h"

#include "OSGLog.h"

#include "OSGGeometry.h"
#include "OSGDrawEnv.h"

#include "OSGMaterial.h"

#include "OSGGeoImmediatePumpGroup.h"

OSG_USING_NAMESPACE


/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/*! An InitFuncWrapper to initialize the GeoImmediatePumpGroup.
 */

InitFuncWrapper GeoImmediatePumpGroup::_glextInitFuncWrapper(
    GeoImmediatePumpGroup::glextInitFunction);

/*! OpenGL extension indices.
*/
UInt32 GeoImmediatePumpGroup::_extSecondaryColor;
UInt32 GeoImmediatePumpGroup::_extMultitexture;
UInt32 GeoImmediatePumpGroup::_arbVertexProgram;

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*------------- constructors & destructors --------------------------------*/

GeoImmediatePumpGroup::GeoImmediatePumpGroup(void)
{
}

GeoImmediatePumpGroup::~GeoImmediatePumpGroup(void)
{
}

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

// Pumping function definitions

typedef void (OSG_APIENTRY *pumpFunc)(const UInt8 * data);
typedef void (OSG_APIENTRY *multiPumpFunc)(GLenum which,  const UInt8 * data);
typedef void (OSG_APIENTRY *attribPumpFunc)(GLuint index, const UInt8 * data);


// Some helper arrays for function selection
// indexed by data type and dimension

static const int formatBase = GL_BYTE;
static const int numFormats = GL_DOUBLE - GL_BYTE + 1;

static const char *formatNames[] =
{   "GL_BYTE", "GL_UNSIGNED_BYTE", "GL_SHORT", "GL_UNSIGNED_SHORT",
    "GL_INT", "GL_UNSIGNED_INT", "GL_FLOAT", "GL_2_BYTES",
    "GL_3_BYTES", "GL_4_BYTES", "GL_DOUBLE"
};

// little helper class for function init

/*! \nohierarchy
 */
class glextFuncInit
{
    public:

        glextFuncInit(const char *name, UInt32 format, UInt32 dim, 
                bool normalizing = false) :
            _name(name), _format(format), _dim(dim),
            _normalizing(normalizing) {};

        void init(UInt32 (&extids)[numFormats][4], UInt32 extension)
        {
            extids[_format - formatBase][_dim - 1] =
                              Window::registerFunction(_name, extension);
        }

    private:

        const char   *_name;
              UInt32  _format;
              UInt32  _dim;
              bool    _normalizing;
};

static glextFuncInit secondaryColorInitFuncs[8] = {
    glextFuncInit(OSG_DLSYM_UNDERSCORE"glSecondaryColor3bvEXT",
                  GL_BYTE,
                  3),
    glextFuncInit(OSG_DLSYM_UNDERSCORE"glSecondaryColor3ubvEXT",
                  GL_UNSIGNED_BYTE,
                  3),
    glextFuncInit(OSG_DLSYM_UNDERSCORE"glSecondaryColor3svEXT",
                  GL_SHORT,
                  3),
    glextFuncInit(OSG_DLSYM_UNDERSCORE"glSecondaryColor3usvEXT",
                  GL_UNSIGNED_SHORT,
                  3),
    glextFuncInit(OSG_DLSYM_UNDERSCORE"glSecondaryColor3ivEXT",
                  GL_INT,
                  3),
    glextFuncInit(OSG_DLSYM_UNDERSCORE"glSecondaryColor3uivEXT",
                  GL_UNSIGNED_INT,
                  3),
    glextFuncInit(OSG_DLSYM_UNDERSCORE"glSecondaryColor3fvEXT",
                  GL_FLOAT,
                  3),
    glextFuncInit(OSG_DLSYM_UNDERSCORE"glSecondaryColor3dvEXT",
                  GL_DOUBLE,
                  3)
};

static glextFuncInit multiTexCoordsInitFuncs[16] = {
    glextFuncInit(OSG_DLSYM_UNDERSCORE"glMultiTexCoord1svARB",
                  GL_SHORT,
                  1),
    glextFuncInit(OSG_DLSYM_UNDERSCORE"glMultiTexCoord2svARB",
                  GL_SHORT,
                  2),
    glextFuncInit(OSG_DLSYM_UNDERSCORE"glMultiTexCoord3svARB",
                  GL_SHORT,
                  3),
    glextFuncInit(OSG_DLSYM_UNDERSCORE"glMultiTexCoord4svARB",
                  GL_SHORT,
                  4),
    glextFuncInit(OSG_DLSYM_UNDERSCORE"glMultiTexCoord1ivARB",
                  GL_INT,
                  1),
    glextFuncInit(OSG_DLSYM_UNDERSCORE"glMultiTexCoord2ivARB",
                  GL_INT,
                  2),
    glextFuncInit(OSG_DLSYM_UNDERSCORE"glMultiTexCoord3ivARB",
                  GL_INT,
                  3),
    glextFuncInit(OSG_DLSYM_UNDERSCORE"glMultiTexCoord4ivARB",
                  GL_INT,
                  4),
    glextFuncInit(OSG_DLSYM_UNDERSCORE"glMultiTexCoord1fvARB",
                  GL_FLOAT,
                  1),
    glextFuncInit(OSG_DLSYM_UNDERSCORE"glMultiTexCoord2fvARB",
                  GL_FLOAT,
                  2),
    glextFuncInit(OSG_DLSYM_UNDERSCORE"glMultiTexCoord3fvARB",
                  GL_FLOAT,
                  3),
    glextFuncInit(OSG_DLSYM_UNDERSCORE"glMultiTexCoord4fvARB",
                  GL_FLOAT,
                  4),
    glextFuncInit(OSG_DLSYM_UNDERSCORE"glMultiTexCoord1dvARB",
                  GL_DOUBLE,
                  1),
    glextFuncInit(OSG_DLSYM_UNDERSCORE"glMultiTexCoord2dvARB",
                  GL_DOUBLE,
                  2),
    glextFuncInit(OSG_DLSYM_UNDERSCORE"glMultiTexCoord3dvARB",
                  GL_DOUBLE,
                  3),
    glextFuncInit(OSG_DLSYM_UNDERSCORE"glMultiTexCoord4dvARB",
                  GL_DOUBLE,
                  4)
};

static glextFuncInit attribInitFuncs[23] = {
    glextFuncInit(OSG_DLSYM_UNDERSCORE"glVertexAttrib1svARB",
                  GL_SHORT,
                  1),
    glextFuncInit(OSG_DLSYM_UNDERSCORE"glVertexAttrib1fvARB",
                  GL_FLOAT,
                  1),
    glextFuncInit(OSG_DLSYM_UNDERSCORE"glVertexAttrib1dvARB",
                  GL_DOUBLE,
                  1),
    glextFuncInit(OSG_DLSYM_UNDERSCORE"glVertexAttrib2svARB",
                  GL_SHORT,
                  2),
    glextFuncInit(OSG_DLSYM_UNDERSCORE"glVertexAttrib2fvARB",
                  GL_FLOAT,
                  2),
    glextFuncInit(OSG_DLSYM_UNDERSCORE"glVertexAttrib2dvARB",
                  GL_DOUBLE,
                  2),
    glextFuncInit(OSG_DLSYM_UNDERSCORE"glVertexAttrib3svARB",
                  GL_SHORT,
                  3),
    glextFuncInit(OSG_DLSYM_UNDERSCORE"glVertexAttrib3fvARB",
                  GL_FLOAT,
                  3),
    glextFuncInit(OSG_DLSYM_UNDERSCORE"glVertexAttrib3dvARB",
                  GL_DOUBLE,
                  3),
    glextFuncInit(OSG_DLSYM_UNDERSCORE"glVertexAttrib4bvARB",
                  GL_BYTE,
                  4),
    glextFuncInit(OSG_DLSYM_UNDERSCORE"glVertexAttrib4svARB",
                  GL_SHORT,
                  4),
    glextFuncInit(OSG_DLSYM_UNDERSCORE"glVertexAttrib4ivARB",
                  GL_INT,
                  4),
    glextFuncInit(OSG_DLSYM_UNDERSCORE"glVertexAttrib4ubvARB",
                  GL_UNSIGNED_BYTE,
                  4),
    glextFuncInit(OSG_DLSYM_UNDERSCORE"glVertexAttrib4usvARB",
                  GL_UNSIGNED_SHORT,
                  4),
    glextFuncInit(OSG_DLSYM_UNDERSCORE"glVertexAttrib4uivARB",
                  GL_UNSIGNED_INT,
                  4),
    glextFuncInit(OSG_DLSYM_UNDERSCORE"glVertexAttrib4bvARB",
                  GL_BYTE,
                  4),
    glextFuncInit(OSG_DLSYM_UNDERSCORE"glVertexAttrib4svARB",
                  GL_SHORT,
                  4),
    glextFuncInit(OSG_DLSYM_UNDERSCORE"glVertexAttrib4ivARB",
                  GL_INT,
                  4),
    glextFuncInit(OSG_DLSYM_UNDERSCORE"glVertexAttrib4ubvARB",
                  GL_UNSIGNED_BYTE,
                  4),
    glextFuncInit(OSG_DLSYM_UNDERSCORE"glVertexAttrib4usvARB",
                  GL_UNSIGNED_SHORT,
                  4),
    glextFuncInit(OSG_DLSYM_UNDERSCORE"glVertexAttrib4uivARB",
                  GL_UNSIGNED_INT,
                  4),
    glextFuncInit(OSG_DLSYM_UNDERSCORE"glVertexAttrib4fvARB",
                  GL_FLOAT,
                  4),
    glextFuncInit(OSG_DLSYM_UNDERSCORE"glVertexAttrib4dvARB",
                  GL_DOUBLE,
                  4),
};


static glextFuncInit normAttribInitFuncs[6] = {
    glextFuncInit(OSG_DLSYM_UNDERSCORE"glVertexAttrib4NbvARB",
                  GL_BYTE,
                  4, true),
    glextFuncInit(OSG_DLSYM_UNDERSCORE"glVertexAttrib4NsvARB",
                  GL_SHORT,
                  4, true),
    glextFuncInit(OSG_DLSYM_UNDERSCORE"glVertexAttrib4NivARB",
                  GL_INT,
                  4, true),
    glextFuncInit(OSG_DLSYM_UNDERSCORE"glVertexAttrib4NubvARB",
                  GL_UNSIGNED_BYTE,
                  4, true),
    glextFuncInit(OSG_DLSYM_UNDERSCORE"glVertexAttrib4NusvARB",
                  GL_UNSIGNED_SHORT,
                  4, true),
    glextFuncInit(OSG_DLSYM_UNDERSCORE"glVertexAttrib4NuivARB",
                  GL_UNSIGNED_INT,
                  4, true),
};

// The real pumping functions

static pumpFunc PositionFuncs[numFormats][4] = {
    { NULL, NULL, NULL, NULL },                           // GL_BYTE
    { NULL, NULL, NULL, NULL },                           // GL_UNSIGNED_BYTE
    { NULL, 
      reinterpret_cast<pumpFunc>(glVertex2sv),
      reinterpret_cast<pumpFunc>(glVertex3sv), 
      reinterpret_cast<pumpFunc>(glVertex4sv) },          // GL_SHORT
    { NULL, NULL, NULL, NULL },                           // GL_UNSIGNED_SHORT
    { NULL, 
      reinterpret_cast<pumpFunc>(glVertex2iv),
      reinterpret_cast<pumpFunc>(glVertex3iv), 
      reinterpret_cast<pumpFunc>(glVertex4iv) },          // GL_INT
    { NULL, NULL, NULL, NULL },                           // GL_UNSIGNED_INT
    { NULL, 
      reinterpret_cast<pumpFunc>(glVertex2fv),
      reinterpret_cast<pumpFunc>(glVertex3fv), 
      reinterpret_cast<pumpFunc>(glVertex4fv) },          // GL_FLOAT
    { NULL, NULL, NULL, NULL },                           // GL_2_BYTES
    { NULL, NULL, NULL, NULL },                           // GL_3_BYTES
    { NULL, NULL, NULL, NULL },                           // GL_4_BYTES
    { NULL, 
      reinterpret_cast<pumpFunc>(glVertex2dv),
      reinterpret_cast<pumpFunc>(glVertex3dv), 
      reinterpret_cast<pumpFunc>(glVertex4dv) },          // GL_DOUBLE
};

static pumpFunc NormalFuncs[numFormats][4] = {
    { NULL, 
      NULL, 
      reinterpret_cast<pumpFunc>(glNormal3sv),
      NULL },                                             // GL_BYTE
    { NULL, NULL, NULL, NULL },                           // GL_UNSIGNED_BYTE
    { NULL, 
      NULL, 
      reinterpret_cast<pumpFunc>(glNormal3sv),
      NULL },                                             // GL_SHORT
    { NULL, NULL, NULL, NULL },                           // GL_UNSIGNED_SHORT
    { NULL, 
      NULL,
      reinterpret_cast<pumpFunc>(glNormal3iv),
      NULL },                                             // GL_INT
    { NULL, NULL, NULL, NULL },                           // GL_UNSIGNED_INT
    { NULL, 
      NULL, 
      reinterpret_cast<pumpFunc>(glNormal3fv), 
      NULL },                                             // GL_FLOAT
    { NULL, NULL, NULL, NULL },                           // GL_2_BYTES
    { NULL, NULL, NULL, NULL },                           // GL_3_BYTES
    { NULL, NULL, NULL, NULL },                           // GL_4_BYTES
    { NULL, 
      NULL, 
      reinterpret_cast<pumpFunc>(glNormal3dv), 
      NULL },          // GL_DOUBLE
};

static pumpFunc ColorFuncs[numFormats][4] = {
    { NULL, 
      NULL,
      reinterpret_cast<pumpFunc>(glColor3bv), 
      reinterpret_cast<pumpFunc>(glColor4bv) },           // GL_BYTE
    { NULL, 
      NULL,
      reinterpret_cast<pumpFunc>(glColor3ubv),
      reinterpret_cast<pumpFunc>(glColor4ubv) },          // GL_UNSIGNED_BYTE
    { NULL, 
      NULL,
      reinterpret_cast<pumpFunc>(glColor3sv), 
      reinterpret_cast<pumpFunc>(glColor4sv) },           // GL_SHORT
    { NULL, 
      NULL,
      reinterpret_cast<pumpFunc>(glColor3usv), 
      reinterpret_cast<pumpFunc>(glColor4usv) },          // GL_UNSIGNED_SHORT
    { NULL, 
      NULL,
      reinterpret_cast<pumpFunc>(glColor3iv),
      reinterpret_cast<pumpFunc>(glColor4iv) },           // GL_INT
    { NULL, 
      NULL,
      reinterpret_cast<pumpFunc>(glColor3uiv), 
      reinterpret_cast<pumpFunc>(glColor4uiv) },          // GL_UNSIGNED_INT
    { NULL, 
      NULL,
      reinterpret_cast<pumpFunc>(glColor3fv), 
      reinterpret_cast<pumpFunc>(glColor4fv) },           // GL_FLOAT
    { NULL, NULL, NULL, NULL },                           // GL_2_BYTES
    { NULL, NULL, NULL, NULL },                           // GL_3_BYTES
    { NULL, NULL, NULL, NULL },                           // GL_4_BYTES
    { NULL, 
      NULL,
      reinterpret_cast<pumpFunc>(glColor3dv), 
      reinterpret_cast<pumpFunc>(glColor4dv) },           // GL_DOUBLE
};

static UInt32 SecColorIDs[numFormats][4];

static pumpFunc TexCoordsFuncs[numFormats][4] = {
    { NULL, NULL, NULL, NULL },                           // GL_BYTE
    { NULL, NULL, NULL, NULL },                           // GL_UNSIGNED_BYTE
    { reinterpret_cast<pumpFunc>(glTexCoord1sv), 
      reinterpret_cast<pumpFunc>(glTexCoord2sv),
      reinterpret_cast<pumpFunc>(glTexCoord3sv), 
      reinterpret_cast<pumpFunc>(glTexCoord4sv) },        // GL_SHORT
    { NULL, NULL, NULL, NULL },                           // GL_UNSIGNED_SHORT
    { reinterpret_cast<pumpFunc>(glTexCoord1iv), 
      reinterpret_cast<pumpFunc>(glTexCoord2iv),
      reinterpret_cast<pumpFunc>(glTexCoord3iv), 
      reinterpret_cast<pumpFunc>(glTexCoord4iv) },        // GL_INT
    { NULL, NULL, NULL, NULL },                           // GL_UNSIGNED_INT
    { reinterpret_cast<pumpFunc>(glTexCoord1fv), 
      reinterpret_cast<pumpFunc>(glTexCoord2fv),
      reinterpret_cast<pumpFunc>(glTexCoord3fv), 
      reinterpret_cast<pumpFunc>(glTexCoord4fv) },        // GL_FLOAT
    { NULL, NULL, NULL, NULL },                           // GL_2_BYTES
    { NULL, NULL, NULL, NULL },                           // GL_3_BYTES
    { NULL, NULL, NULL, NULL },                           // GL_4_BYTES
    { reinterpret_cast<pumpFunc>(glTexCoord1dv), 
      reinterpret_cast<pumpFunc>(glTexCoord2dv),
      reinterpret_cast<pumpFunc>(glTexCoord3dv), 
      reinterpret_cast<pumpFunc>(glTexCoord4dv) },        // GL_DOUBLE
};

static UInt32 TexCoords1IDs[numFormats][4];

#define TexCoords2IDs TexCoords1IDs
#define TexCoords3IDs TexCoords1IDs
#define TexCoords4IDs TexCoords1IDs
#define TexCoords5IDs TexCoords1IDs
#define TexCoords6IDs TexCoords1IDs
#define TexCoords7IDs TexCoords1IDs

static UInt32 AttribIDs[numFormats][4];
static UInt32 NormAttribIDs[numFormats][4];


#define pumpSetup( name, typename, getmethod )                              \
    typename name##Ptr;                                                     \
    GLubyte * name##Data = NULL;                                            \
    UInt32 name##Stride;                                                    \
                                                                            \
    name##Ptr = geo->getmethod();                                           \
    if ( name##Ptr != NULL )                                                \
    {                                                                       \
        name##Data = name##Ptr->getData();                                  \
        if ( ! ( name##Stride = name##Ptr->getStride() ) )                  \
            name##Stride = name##Ptr->getFormatSize() *                     \
            name##Ptr->getDimension();                                      \
    }


// The master pump. Can render everything, but takes ages to do so.
// A real fallback, when everything else fails.
// Its second function is the example of how things are supposed to work.
// If an optimized pump creates a different result, it's wrong.
// The formal specification is defined in the design document though.

// some little helper macros to make the code more readable

// define and initialize the variables needed to access the data

#ifdef OSG_GV_BETA
#define OSG_GV_ASSERT(X) OSG_ASSERT(X)
#else
#define OSG_GV_ASSERT(X)
#endif

//    UInt32 name##Ind = 0;

#define pumpInternalSetup( name, typename, getmethod, mandatory )           \
    GeoIntegralProperty *name##Ptr;                                         \
                                                                            \
    name##Ptr = geo->getmethod();                                           \
    if(mandatory && name##Ptr == NULL)                                      \
    {                                                                       \
        SWARNING << "masterPump: Geometry " << geo << " has no "            \
                 << #name << "s!" << std::endl;                             \
        OSG_GV_ASSERT(false);                                               \
        return;                                                             \
    }

//    UInt32 name##Ind = 0;

#define pumpGLSetup( name, propindex )                                      \
    const UInt8 * name##Data = NULL;                                        \
    UInt32 name##Stride;                                                    \
    GeoProperty *name##Ptr = NULL;                                          \
    GeoIntegralProperty *name##Index = NULL;                                \
    pumpFunc name##Func = NULL;                                             \
                                                                            \
    name##Ptr = geo->getProperty(propindex);                                \
    if(name##Ptr != NULL)                                                   \
    {                                                                       \
        name##Index = geo->getIndex(propindex);                             \
        name##Data = name##Ptr->getData();                                  \
        OSG_GV_ASSERT(name##Data != NULL);                                  \
        if(!(name##Stride = name##Ptr->getStride()))                        \
            name##Stride = name##Ptr->getFormatSize() *                     \
            name##Ptr->getDimension();                                      \
        if(!(name##Func = name##Funcs[name##Ptr->getFormat() -              \
                                            formatBase]                     \
                                     [name##Ptr->getDimension() - 1]        \
          ) )                                                               \
        {                                                                   \
            SWARNING << "masterPump: Geometry " << geo << " has illegal "   \
                     << #name << "s: " << name##Ptr->getDimension()         \
                     << "D " << formatNames[ name##Ptr->getFormat() -       \
                                            formatBase ]                    \
                     << "!" << std::endl;                                   \
            return;                                                         \
        }                                                                   \
    }                                                                       \
    else                                                                    \
    {                                                                       \
        name##Data = NULL;                                                  \
        name##Func = NULL;                                                  \
        name##Stride = 0;                                                   \
    }

//    UInt32 name##Ind = 0;

#define pumpGLExtSetup( name, propindex )                                   \
    const UInt8 * name##Data;                                               \
    UInt32 name##Stride;                                                    \
    GeoProperty *name##Ptr;                                                 \
    GeoIntegralProperty *name##Index;                                       \
    pumpFunc name##Func;                                                    \
                                                                            \
    name##Ptr = geo->getProperty(propindex);                                \
    if(name##Ptr != NULL)                                                   \
    {                                                                       \
        name##Index = geo->getIndex(propindex);                             \
        name##Data = name##Ptr->getData();                                  \
        if(!(name##Stride = name##Ptr->getStride()))                        \
            name##Stride = name##Ptr->getFormatSize() *                     \
            name##Ptr->getDimension();                                      \
        if(name##IDs[name##Ptr->getFormat() - formatBase]                   \
                    [name##Ptr->getDimension() - 1] ==                      \
                    Window::invalidFunctionID)                              \
        {                                                                   \
            SWARNING << "masterPump: Geometry " << geo << " has illegal "   \
                     << #name << "s: " << name##Ptr->getDimension()         \
                     << "D " << formatNames[ name##Ptr->getFormat() -       \
                                            formatBase ]                    \
                     << "!" << std::endl;                                   \
            return;                                                         \
        }                                                                   \
        if(!(name##Func = reinterpret_cast<pumpFunc>(                       \
                               win->getFunction(name##IDs                   \
                                     [name##Ptr->getFormat() - formatBase]  \
                                     [name##Ptr->getDimension() - 1]))      \
          ) )                                                               \
        {                                                                   \
            SWARNING << "masterPump: Geometry " << geo << " uses "          \
                     << #name << "s: " << name##Ptr->getDimension()         \
                     << "D " << formatNames[ name##Ptr->getFormat() -       \
                                            formatBase ]                    \
                     << " which are not supported by Window " << win        \
                     <<  "!" << std::endl;                                  \
            return;                                                         \
        }                                                                   \
    }                                                                       \
    else                                                                    \
    {                                                                       \
        name##Data = NULL;                                                  \
        name##Func = NULL;                                                  \
        name##Index = NULL;                                                 \
        name##Stride = 0;                                                   \
    }

//    UInt32 name##Ind = 0;

#define pumpMultiGLExtSetup( name, propindex )                              \
    const UInt8 * name##Data;                                               \
    UInt32 name##Stride;                                                    \
    GeoProperty *name##Ptr;                                                 \
    GeoIntegralProperty *name##Index;                                       \
    multiPumpFunc name##Func;                                               \
                                                                            \
    name##Ptr = geo->getProperty(propindex);                                \
    if(name##Ptr != NULL)                                                   \
    {                                                                       \
        name##Index = geo->getIndex(propindex);                             \
        name##Data = name##Ptr->getData();                                  \
        if(!(name##Stride = name##Ptr->getStride()))                        \
            name##Stride = name##Ptr->getFormatSize() *                     \
            name##Ptr->getDimension();                                      \
        if(name##IDs[name##Ptr->getFormat() - formatBase]                   \
                    [name##Ptr->getDimension() - 1] ==                      \
                    Window::invalidFunctionID)                              \
        {                                                                   \
            SWARNING << "masterPump: Geometry " << geo << " has illegal "   \
                     << #name << "s: " << name##Ptr->getDimension()         \
                     << "D " << formatNames[ name##Ptr->getFormat() -       \
                                            formatBase ]                    \
                     << "!" << std::endl;                                   \
            return;                                                         \
        }                                                                   \
        if(!(name##Func = reinterpret_cast<multiPumpFunc>(                  \
                              win->getFunction(name##IDs                    \
                                     [name##Ptr->getFormat() - formatBase]  \
                                     [name##Ptr->getDimension() - 1]))      \
          ) )                                                               \
        {                                                                   \
            SWARNING << "masterPump: Geometry " << geo << " uses "          \
                     << #name << "s: " << name##Ptr->getDimension()         \
                     << "D " << formatNames[ name##Ptr->getFormat() -       \
                                            formatBase ]                    \
                     << " which are not supported by Window " << win        \
                     <<  "!" << std::endl;                                  \
            return;                                                         \
        }                                                                   \
    }                                                                       \
    else                                                                    \
    {                                                                       \
        name##Data = NULL;                                                  \
        name##Func = NULL;                                                  \
        name##Index = NULL;                                                 \
        name##Stride = 0;                                                   \
    }

void GeoImmediatePumpGroup::masterClassicGeoPump(DrawEnv  *pEnv,
                                                 Geometry *geo)
{
    Window *win = pEnv->getWindow();
    
    // Setup: get all the data

    pumpInternalSetup( Type, GeoPTypes *, getTypes, true );
    pumpInternalSetup( Length, GeoPLengths *, getLengths, false );

    pumpGLSetup        ( Position,   Geometry::PositionsIndex      );
    pumpGLSetup        ( Color,      Geometry::ColorsIndex         );
    pumpGLSetup        ( Normal,     Geometry::NormalsIndex        );
    pumpGLSetup        ( TexCoords,  Geometry::TexCoordsIndex      );
    pumpGLExtSetup     ( SecColor,   Geometry::SecondaryColorsIndex);
    pumpMultiGLExtSetup( TexCoords1, Geometry::TexCoords1Index     );
    pumpMultiGLExtSetup( TexCoords2, Geometry::TexCoords2Index     );
    pumpMultiGLExtSetup( TexCoords3, Geometry::TexCoords3Index     );
    pumpMultiGLExtSetup( TexCoords4, Geometry::TexCoords4Index     );
    pumpMultiGLExtSetup( TexCoords5, Geometry::TexCoords5Index     );
    pumpMultiGLExtSetup( TexCoords6, Geometry::TexCoords6Index     );
    pumpMultiGLExtSetup( TexCoords7, Geometry::TexCoords7Index     );
    
    // check if the node is empty
    if(TypePtr == NULL || TypePtr->getSize() == 0)
        return;

    // if it's not empty we need positions
    if(! PositionData)
    {
        SWARNING << "masterPump: Geometry " << geo << " has no positions!?!"
                 << endLog;
        OSG_GV_ASSERT(false);                                              
        return;
    }

    // overall attributes?
    if(ColorData && ColorPtr->getSize() == 1)   
    {
        ColorFunc(ColorData);
        ColorData = NULL;
    }
    if(NormalData && NormalPtr->getSize() == 1) 
    {
        NormalFunc(NormalData);
        NormalData = NULL;
    }
    if(win->hasExtension(_extSecondaryColor) && SecColorData && 
       SecColorPtr->getSize() == 1)   
    {
        SecColorFunc(SecColorData);
        SecColorData = NULL;
    }
    if(TexCoordsData && TexCoordsPtr->getSize() == 1) 
    {
        TexCoordsFunc(TexCoordsData);
        TexCoordsData = NULL;
    }
    if(win->hasExtension(_extMultitexture))
    {
        if(TexCoords1Data && TexCoords1Ptr->getSize() == 1) 
        {
            TexCoords1Func(GL_TEXTURE1_ARB, TexCoords1Data);
            TexCoords1Data = NULL;
        }
        if(TexCoords2Data && TexCoords2Ptr->getSize() == 1) 
        {
            TexCoords2Func(GL_TEXTURE2_ARB, TexCoords2Data);
            TexCoords2Data = NULL;
        }
        if(TexCoords3Data && TexCoords3Ptr->getSize() == 1) 
        {
            TexCoords3Func(GL_TEXTURE3_ARB, TexCoords3Data);
            TexCoords3Data = NULL;
        }
        if(TexCoords4Data && TexCoords4Ptr->getSize() == 1) 
        {
            TexCoords4Func(GL_TEXTURE4_ARB, TexCoords4Data);
            TexCoords4Data = NULL;
        }
        if(TexCoords2Data && TexCoords2Ptr->getSize() == 1) 
        {
            TexCoords2Func(GL_TEXTURE2_ARB, TexCoords2Data);
            TexCoords2Data = NULL;
        }
        if(TexCoords5Data && TexCoords2Ptr->getSize() == 1) 
        {
            TexCoords2Func(GL_TEXTURE2_ARB, TexCoords2Data);
            TexCoords2Data = NULL;
        }
        if(TexCoords6Data && TexCoords6Ptr->getSize() == 1) 
        {
            TexCoords6Func(GL_TEXTURE6_ARB, TexCoords6Data);
            TexCoords6Data = NULL;
        }
        if(TexCoords7Data && TexCoords7Ptr->getSize() == 1) 
        {
            TexCoords7Func(GL_TEXTURE7_ARB, TexCoords7Data);
            TexCoords7Data = NULL;
        }
    }
 
    // Length handling. Special case: no length given

    UInt32 curlen;
    UInt32 nprims;

    // no lengths? use all available data for the first type
    if(LengthPtr == NULL)
    {
        if(TypePtr->getSize() != 1)
        {
            SWARNING << "masterPump: Geometry " << geo 
                     << " has no length but more than one type!?!"
                     << endLog;
            return;
        }
        
        nprims = 1;
        if (PositionIndex != NULL)
        {
            curlen = PositionIndex->getSize();
        }
        else
        {
            curlen = PositionPtr->getSize();
        }
    }
    else
    {
        nprims = TypePtr->getSize();
        LengthPtr->getValue(curlen, 0);
    }
    
    UInt32 vertindex = 0;

    for(UInt32 primindex = 0; primindex < nprims; ++primindex)
    {
        glBegin(TypePtr->getValue<UInt16>(primindex));

        if(primindex < LengthPtr->getSize())
            curlen = LengthPtr->getValue<UInt32>(primindex);

        for(; curlen > 0; --curlen, ++vertindex)
        {
            if(ColorData)
            {
                if (ColorIndex != NULL)
                {
                    ColorFunc(ColorData + ColorStride * 
                              ColorIndex->getValue<UInt32>(vertindex));
                }
                else
                {
                    ColorFunc(ColorData + ColorStride * vertindex);
                }
            }
            
            if(NormalData)
            {
                if (NormalIndex != NULL)
                {
                    NormalFunc(NormalData + NormalStride * 
                               NormalIndex->getValue<UInt32>(vertindex));
                }
                else
                {
                    NormalFunc(NormalData + NormalStride * vertindex);
                }
            }
            
            if(win->hasExtension(_extSecondaryColor) && SecColorData)
            {
                if (SecColorIndex != NULL)
                {
                    SecColorFunc(SecColorData + SecColorStride * 
                               SecColorIndex->getValue<UInt32>(vertindex));
                }
                else
                {
                    SecColorFunc(SecColorData + SecColorStride * vertindex);
                }
            }
            
            if(TexCoordsData)
            {
                if (TexCoordsIndex != NULL)
                {
                    TexCoordsFunc(TexCoordsData + TexCoordsStride * 
                                 TexCoordsIndex->getValue<UInt32>(vertindex));
                }
                else
                {
                    TexCoordsFunc(TexCoordsData + TexCoordsStride * vertindex);
                }
            }
            
            if(win->hasExtension(_extMultitexture))
            {
                if(TexCoords1Data)
                {
                    if (TexCoords1Index != NULL)
                    {
                        TexCoords1Func(GL_TEXTURE1_ARB, 
                                  TexCoords1Data + TexCoords1Stride * 
                                  TexCoords1Index->getValue<UInt32>(vertindex));
                    }
                    else
                    {
                        TexCoords1Func(GL_TEXTURE1_ARB, 
                                  TexCoords1Data + TexCoords1Stride * vertindex);
                    }
                }

                if(TexCoords2Data)
                {
                    if (TexCoords2Index != NULL)
                    {
                        TexCoords2Func(GL_TEXTURE2_ARB, 
                                  TexCoords2Data + TexCoords2Stride * 
                                  TexCoords2Index->getValue<UInt32>(vertindex));
                    }
                    else
                    {
                        TexCoords2Func(GL_TEXTURE2_ARB, 
                                  TexCoords2Data + TexCoords2Stride * vertindex);
                    }
                }

                if(TexCoords3Data)
                {
                    if (TexCoords3Index != NULL)
                    {
                        TexCoords3Func(GL_TEXTURE3_ARB, 
                                  TexCoords3Data + TexCoords3Stride * 
                                  TexCoords3Index->getValue<UInt32>(vertindex));
                    }
                    else
                    {
                        TexCoords3Func(GL_TEXTURE3_ARB, 
                                  TexCoords3Data + TexCoords3Stride * vertindex);
                    }
                }

                if(TexCoords4Data)
                {
                    if (TexCoords4Index != NULL)
                    {
                        TexCoords4Func(GL_TEXTURE4_ARB, 
                                  TexCoords4Data + TexCoords4Stride * 
                                  TexCoords4Index->getValue<UInt32>(vertindex));
                    }
                    else
                    {
                        TexCoords4Func(GL_TEXTURE4_ARB, 
                                  TexCoords4Data + TexCoords4Stride * vertindex);
                    }
                }

                if(TexCoords5Data)
                {
                    if (TexCoords5Index != NULL)
                    {
                        TexCoords5Func(GL_TEXTURE5_ARB, 
                                  TexCoords5Data + TexCoords5Stride * 
                                  TexCoords5Index->getValue<UInt32>(vertindex));
                    }
                    else
                    {
                        TexCoords5Func(GL_TEXTURE5_ARB, 
                                  TexCoords5Data + TexCoords5Stride * vertindex);
                    }
                }

                if(TexCoords6Data)
                {
                    if (TexCoords6Index != NULL)
                    {
                        TexCoords6Func(GL_TEXTURE6_ARB, 
                                  TexCoords6Data + TexCoords6Stride * 
                                  TexCoords6Index->getValue<UInt32>(vertindex));
                    }
                    else
                    {
                        TexCoords6Func(GL_TEXTURE6_ARB, 
                                  TexCoords6Data + TexCoords6Stride * vertindex);
                    }
                }

                if(TexCoords7Data)
                {
                    if (TexCoords7Index != NULL)
                    {
                        TexCoords7Func(GL_TEXTURE7_ARB, 
                                  TexCoords7Data + TexCoords7Stride * 
                                  TexCoords7Index->getValue<UInt32>(vertindex));
                    }
                    else
                    {
                        TexCoords7Func(GL_TEXTURE7_ARB, 
                                  TexCoords7Data + TexCoords7Stride * vertindex);
                    }
                }
                }
            
            if (PositionIndex != NULL)
            {
                PositionFunc(PositionData + PositionStride * 
                             PositionIndex->getValue<UInt32>(vertindex));
            }
            else
            {
                PositionFunc(PositionData + PositionStride * vertindex);
            }

        }

        glEnd();
    }
}

void GeoImmediatePumpGroup::masterAttribGeoPump(DrawEnv  *pEnv,
                                                Geometry *geo)
{
    Window *win = pEnv->getWindow();
    
    // Setup: get all the data

    pumpInternalSetup( Type, GeoPTypes *, getTypes, true );
    pumpInternalSetup( Length, GeoPLengths *, getLengths, false );

    const UInt8               *attribData  [Geometry::MaxAttribs];
          UInt32               attribStride[Geometry::MaxAttribs];
          UInt32               attribInd   [Geometry::MaxAttribs];
          GeoVectorProperty   *attribPtr   [Geometry::MaxAttribs];
          GeoIntegralProperty *attribIndex [Geometry::MaxAttribs];
          attribPumpFunc       attribFunc  [Geometry::MaxAttribs];

    UInt16 nattrib = geo->getMFProperties()->size();
    
    for(UInt16 i = 0; i < nattrib; ++i)
    {
        attribInd[i] = 0;
        attribPtr[i] = geo->getProperty(i);
        if(attribPtr[i] != NULL)
        {
            attribIndex[i] = geo->getIndex(i);
            attribData[i] = attribPtr[i]->getData();
            if(!(attribStride[i] = attribPtr[i]->getStride()))
                attribStride[i] = attribPtr[i]->getFormatSize() *
                                  attribPtr[i]->getDimension();
                                  
            UInt32 funcid;
            
            if(attribPtr[i]->getNormalize())
            {
                if(NormAttribIDs[attribPtr[i]->getFormat() - formatBase]
                                [attribPtr[i]->getDimension() - 1] ==
                            Window::invalidFunctionID)
                {
                    SWARNING << "masterPump: Geometry " << geo 
                             << " has illegal attribute " << i 
                             << ": " << attribPtr[i]->getDimension()
                             << "D " << formatNames[ attribPtr[i]->getFormat() -
                                                    formatBase ]
                             << " (normalizing)!" << std::endl;
                    return;
                } 
                funcid = NormAttribIDs[attribPtr[i]->getFormat() - formatBase]
                                      [attribPtr[i]->getDimension() - 1];    
            }
            else
            {
                if(AttribIDs[attribPtr[i]->getFormat() - formatBase]
                            [attribPtr[i]->getDimension() - 1] ==
                            Window::invalidFunctionID)
                {
                    SWARNING << "masterPump: Geometry " << geo 
                             << " has illegal attribute " << i 
                             << ": " << attribPtr[i]->getDimension()
                             << "D " << formatNames[ attribPtr[i]->getFormat() -
                                                    formatBase ]
                             << "!" << std::endl;
                    return;
                } 
                funcid = AttribIDs[attribPtr[i]->getFormat() - formatBase]
                                  [attribPtr[i]->getDimension() - 1];    
            }
            
            if(!(attribFunc[i] = reinterpret_cast<attribPumpFunc>(
                                     win->getFunction(funcid)) ) )
            {
                SWARNING << "masterPump: Geometry " << geo << " uses "
                         << "attribute " << i << " "
                         << attribPtr[i]->getDimension()
                         << "D " << formatNames[ attribPtr[i]->getFormat() -
                                                formatBase ]
                         << " which are not supported by Window " << win
                         <<  "!" << std::endl;
                return;
            }
        }
        else
        {
            attribData[i] = NULL;
            attribFunc[i] = NULL;
            attribStride[i] = 0;
        }
    }
    
    // check if the node is empty
    if(TypePtr == NULL || TypePtr->getSize() == 0)
        return;

    // if it's not empty we need positions
    if(! attribData[0])
    {
        SWARNING << "masterPump: Geometry " << geo << " has no positions!?!"
                 << endLog;
        OSG_GV_ASSERT(false);                                              
        return;
    }

    // overall attributes?
    for(Int16 i = 0; i < nattrib; ++i)
    {
        if(attribData[i] && attribPtr[i]->getSize() == 1)
        {
            attribFunc[i](i, attribData[i]);
            attribData[i] = NULL;
        }
    }

    // Length handling. Special case: no length given

    UInt32 curlen;
    UInt32 nprims;

    // no lengths? use all available data for the first type
    if(LengthPtr == NULL)
    {
        if(TypePtr->getSize() != 1)
        {
            SWARNING << "masterPump: Geometry " << geo 
                     << " has no length but more than one type!?!"
                     << endLog;
            return;
        }
        
        nprims = 1;
        if (attribIndex[0] != NULL)
        {
            curlen = attribIndex[0]->getSize();
        }
        else
        {
            curlen = attribPtr[0]->getSize();
        }
    }
    else
    {
        nprims = TypePtr->getSize();
        LengthPtr->getValue(curlen, 0);
    }
    
    UInt32 vertindex = 0;

    for(UInt32 primindex = 0; primindex < nprims; ++primindex)
    {
        glBegin(TypePtr->getValue<UInt16>(primindex));

        if(primindex < LengthPtr->getSize())
            curlen = LengthPtr->getValue<UInt32>(primindex);

        for(; curlen > 0; --curlen, ++vertindex)
        {
            for(Int16 i = nattrib - 1; i >= 0; --i)
            {
                if(attribData[i])
                {
                    if(attribIndex[i] != NULL)
                    {
                        attribFunc[i](i, attribData[i] + attribStride[i] *
                                attribIndex[i]->getValue<UInt32>(vertindex));
                    }
                    else
                    {
                        attribFunc[i](i, attribData[i] + attribStride[i] *
                                      vertindex);
                    }
                }
            }
        }

        glEnd();
    }
}

void GeoImmediatePumpGroup::masterGeoPump(DrawEnv  *pEnv,
                                          Geometry *geo)
{
    Window *win = pEnv->getWindow();
    
    if(win->hasExtension(_arbVertexProgram))
    {
        masterAttribGeoPump(pEnv, geo);
    }
    else
    {
        masterClassicGeoPump(pEnv, geo);
    }
}


GeoPumpGroup::GeoPump GeoImmediatePumpGroup::getGeoPump(
                    DrawEnv                 *pEnv,
                    PropertyCharacteristics  acset)
{
    Window *win = pEnv->getWindow();

    if(win->hasExtension(_arbVertexProgram) && (acset & UsesShader))
    {
        return masterAttribGeoPump;
    }
    else
    {
        return masterClassicGeoPump;
    }
}

GeoPumpGroup::PartialGeoPump GeoImmediatePumpGroup::getPartialGeoPump(
                    DrawEnv                 *pEnv, 
                    PropertyCharacteristics  acset)
{
    return NULL;
}

GeoPumpGroup::ExtIndexGeoPump GeoImmediatePumpGroup::getExtIndexGeoPump(
                    DrawEnv                 *pEnv, 
                    PropertyCharacteristics  acset)
{
    return NULL;
}

#ifdef __sgi
#pragma reset woff 1174,1209
#endif

bool GeoImmediatePumpGroup::glextInitFunction(void)
{
    _extSecondaryColor      = 
        Window::registerExtension("GL_EXT_secondary_color");
    _extMultitexture        = 
        Window::registerExtension("GL_ARB_multitexture");
    _arbVertexProgram       = 
        Window::registerExtension("GL_ARB_vertex_program");
        
    UInt16 i,j;
    for(i = 0; i < numFormats; i++)
    {
        for(j = 0; j < 4; j++)
        {
            SecColorIDs  [i][j] = Window::invalidFunctionID;
            TexCoords1IDs[i][j] = Window::invalidFunctionID;
        }
    }

    for(i = 0; i < 8; i++)
        secondaryColorInitFuncs[i].init(SecColorIDs, _extSecondaryColor);

    for(i = 0; i < 16; i++)
        multiTexCoordsInitFuncs[i].init(TexCoords1IDs, _extMultitexture);

    for(i = 0; i < 23; i++)
        attribInitFuncs[i].init(AttribIDs, _arbVertexProgram);

    for(i = 0; i < 6; i++)
        normAttribInitFuncs[i].init(NormAttribIDs, _arbVertexProgram);

    return true;
}
