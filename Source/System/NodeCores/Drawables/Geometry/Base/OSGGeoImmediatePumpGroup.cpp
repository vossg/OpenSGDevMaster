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

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include <OSGGL.h>
#include <OSGGLEXT.h>

#include "OSGLog.h"

#include "OSGFieldContainerPtr.h"
#include "OSGGeometry.h"
#include "OSGDrawEnv.h"

#include "OSGMaterial.h"

#include "OSGGeoImmediatePumpGroup.h"

OSG_USING_NAMESPACE


/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/* \class OSG::GeoImmediatePumpGroup
   \ingroup GrpSystemNodeCoresDrawablesGeometry
    
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/*! An InitFuncWrapper to initialize the GeoImmediatePumpGroup.
*/
InitFuncWrapper
GeoImmediatePumpGroup::_glextInitFuncWrapper(GeoImmediatePumpGroup::glextInitFunction);

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

static char *formatNames[] =
{   "GL_BYTE", "GL_UNSIGNED_BYTE", "GL_SHORT", "GL_UNSIGNED_SHORT",
    "GL_INT", "GL_UNSIGNED_INT", "GL_FLOAT", "GL_2_BYTES",
    "GL_3_BYTES", "GL_4_BYTES", "GL_DOUBLE"
};

// little helper class for function init

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)

class glextFuncInit
{
    public:

        glextFuncInit(char *name, UInt32 format, UInt32 dim, 
                bool normalizing = false) :
            _name(name), _format(format), _dim(dim),
            _normalizing(normalizing) {};

        void init(UInt32 (&extids)[numFormats][4], UInt32 extension)
        {
            extids[_format - formatBase][_dim - 1] =
                              Window::registerFunction(_name, extension);
        }

    private:

        char   *_name;
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
    { NULL, (pumpFunc)glVertex2sv,
      (pumpFunc)glVertex3sv, (pumpFunc)glVertex4sv },     // GL_SHORT
    { NULL, NULL, NULL, NULL },                           // GL_UNSIGNED_SHORT
    { NULL, (pumpFunc)glVertex2iv,
      (pumpFunc)glVertex3iv, (pumpFunc)glVertex4iv },     // GL_INT
    { NULL, NULL, NULL, NULL },                           // GL_UNSIGNED_INT
    { NULL, (pumpFunc)glVertex2fv,
      (pumpFunc)glVertex3fv, (pumpFunc)glVertex4fv },     // GL_FLOAT
    { NULL, NULL, NULL, NULL },                           // GL_2_BYTES
    { NULL, NULL, NULL, NULL },                           // GL_3_BYTES
    { NULL, NULL, NULL, NULL },                           // GL_4_BYTES
    { NULL, (pumpFunc)glVertex2dv,
      (pumpFunc)glVertex3dv, (pumpFunc)glVertex4dv },     // GL_DOUBLE
};

static pumpFunc NormalFuncs[numFormats][4] = {
    { NULL, NULL, (pumpFunc)glNormal3sv, NULL },          // GL_BYTE
    { NULL, NULL, NULL, NULL },                           // GL_UNSIGNED_BYTE
    { NULL, NULL, (pumpFunc)glNormal3sv, NULL },          // GL_SHORT
    { NULL, NULL, NULL, NULL },                           // GL_UNSIGNED_SHORT
    { NULL, NULL, (pumpFunc)glNormal3iv, NULL },          // GL_INT
    { NULL, NULL, NULL, NULL },                           // GL_UNSIGNED_INT
    { NULL, NULL, (pumpFunc)glNormal3fv, NULL },          // GL_FLOAT
    { NULL, NULL, NULL, NULL },                           // GL_2_BYTES
    { NULL, NULL, NULL, NULL },                           // GL_3_BYTES
    { NULL, NULL, NULL, NULL },                           // GL_4_BYTES
    { NULL, NULL, (pumpFunc)glNormal3dv, NULL },          // GL_DOUBLE
};

static pumpFunc ColorFuncs[numFormats][4] = {
    { NULL, NULL,
      (pumpFunc)glColor3bv, (pumpFunc)glColor4bv },       // GL_BYTE
    { NULL, NULL,
      (pumpFunc)glColor3ubv, (pumpFunc)glColor4ubv },     // GL_UNSIGNED_BYTE
    { NULL, NULL,
      (pumpFunc)glColor3sv, (pumpFunc)glColor4sv },       // GL_SHORT
    { NULL, NULL,
      (pumpFunc)glColor3usv, (pumpFunc)glColor4usv },     // GL_UNSIGNED_SHORT
    { NULL, NULL,
      (pumpFunc)glColor3iv, (pumpFunc)glColor4iv },       // GL_INT
    { NULL, NULL,
      (pumpFunc)glColor3uiv, (pumpFunc)glColor4uiv },     // GL_UNSIGNED_INT
    { NULL, NULL,
      (pumpFunc)glColor3fv, (pumpFunc)glColor4fv },       // GL_FLOAT
    { NULL, NULL, NULL, NULL },                           // GL_2_BYTES
    { NULL, NULL, NULL, NULL },                           // GL_3_BYTES
    { NULL, NULL, NULL, NULL },                           // GL_4_BYTES
    { NULL, NULL,
      (pumpFunc)glColor3dv, (pumpFunc)glColor4dv },       // GL_DOUBLE
};

static UInt32 SecColorIDs[numFormats][4];

static pumpFunc TexCoordsFuncs[numFormats][4] = {
    { NULL, NULL, NULL, NULL },                           // GL_BYTE
    { NULL, NULL, NULL, NULL },                           // GL_UNSIGNED_BYTE
    { (pumpFunc)glTexCoord1sv, (pumpFunc)glTexCoord2sv,
      (pumpFunc)glTexCoord3sv, (pumpFunc)glTexCoord4sv }, // GL_SHORT
    { NULL, NULL, NULL, NULL },                           // GL_UNSIGNED_SHORT
    { (pumpFunc)glTexCoord1iv, (pumpFunc)glTexCoord2iv,
      (pumpFunc)glTexCoord3iv, (pumpFunc)glTexCoord4iv }, // GL_INT
    { NULL, NULL, NULL, NULL },                           // GL_UNSIGNED_INT
    { (pumpFunc)glTexCoord1fv, (pumpFunc)glTexCoord2fv,
      (pumpFunc)glTexCoord3fv, (pumpFunc)glTexCoord4fv }, // GL_FLOAT
    { NULL, NULL, NULL, NULL },                           // GL_2_BYTES
    { NULL, NULL, NULL, NULL },                           // GL_3_BYTES
    { NULL, NULL, NULL, NULL },                           // GL_4_BYTES
    { (pumpFunc)glTexCoord1dv, (pumpFunc)glTexCoord2dv,
      (pumpFunc)glTexCoord3dv, (pumpFunc)glTexCoord4dv }, // GL_DOUBLE
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

#endif      // remove from all but dev docs


#define pumpSetup( name, typename, getmethod )                              \
    typename name##Ptr;                                                     \
    GLubyte * name##Data = NULL;                                            \
    UInt32 name##Stride;                                                    \
                                                                            \
    name##Ptr = geo->getmethod();                                           \
    if ( name##Ptr != NullFC )                                              \
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

#define pumpInternalSetup( name, typename, getmethod, mandatory )           \
    GeoIntegralPropertyPtr name##Ptr;                                                   \
    UInt32 name##Ind = 0;                                                   \
                                                                            \
    name##Ptr = geo->getmethod();                                           \
    if(mandatory && name##Ptr == NullFC)                                    \
    {                                                                       \
        SWARNING << "masterPump: Geometry " << geo << " has no "            \
                 << #name << "s!" << std::endl;                             \
        return;                                                             \
    }

#define pumpGLSetup( name, propindex )                                       \
    const UInt8 * name##Data = NULL;                                        \
    UInt32 name##Stride;                                                    \
    UInt32 name##Ind = 0;                                                   \
    GeoPropertyPtr name##Ptr = NullFC;                                   \
    GeoIntegralPropertyPtr name##Index = NullFC;                         \
    pumpFunc name##Func = NULL;                                             \
                                                                            \
    name##Ptr = geo->getProperty(propindex);                                \
    if(name##Ptr != NullFC)                                                 \
    {                                                                       \
        name##Index = geo->getIndex(propindex);                              \
        name##Data = name##Ptr->getData();                                  \
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

#define pumpGLExtSetup( name, propindex )                                    \
    const UInt8 * name##Data;                                               \
    UInt32 name##Stride;                                                    \
    UInt32 name##Ind = 0;                                                   \
    GeoPropertyPtr name##Ptr;                                            \
    GeoIntegralPropertyPtr name##Index;                                  \
    pumpFunc name##Func;                                                    \
                                                                            \
    name##Ptr = geo->getProperty(propindex);                                \
    if(name##Ptr != NullFC)                                                 \
    {                                                                       \
        name##Index = geo->getIndex(propindex);                              \
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
        if(!(name##Func = (pumpFunc)win->getFunction(name##IDs              \
                                     [name##Ptr->getFormat() - formatBase]  \
                                     [name##Ptr->getDimension() - 1])       \
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
        name##Stride = 0;                                                   \
    }


#define pumpMultiGLExtSetup( name, propindex )                               \
    const UInt8 * name##Data;                                               \
    UInt32 name##Stride;                                                    \
    UInt32 name##Ind = 0;                                                   \
    GeoPropertyPtr name##Ptr;                                            \
    GeoIntegralPropertyPtr name##Index;                                  \
    multiPumpFunc name##Func;                                               \
                                                                            \
    name##Ptr = geo->getProperty(propindex);                                \
    if(name##Ptr != NullFC)                                                 \
    {                                                                       \
        name##Index = geo->getIndex(propindex);                              \
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
        if(!(name##Func = (multiPumpFunc)win->getFunction(name##IDs         \
                                     [name##Ptr->getFormat() - formatBase]  \
                                     [name##Ptr->getDimension() - 1])       \
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
        name##Stride = 0;                                                   \
    }

void GeoImmediatePumpGroup::masterClassicGeoPump(DrawEnv  *pEnv,
                                                 Geometry *geo)
{
    Window *win = pEnv->getWindow();
    
    // Setup: get all the data

    pumpInternalSetup( Type, GeoPTypesPtr, getTypes, true );
    pumpInternalSetup( Length, GeoPLengthsPtr, getLengths, false );

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
    if(TypePtr == NullFC || TypePtr->getSize() == 0)
        return;

    // if it's not empty we need positions
    if(! PositionData)
    {
        SWARNING << "masterPump: Geometry " << geo << " has no positions!?!"
                 << endLog;
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
    if(LengthPtr == NullFC)
    {
        if(TypePtr->getSize() != 1)
        {
            SWARNING << "masterPump: Geometry " << geo 
                     << " has no length but more than one type!?!"
                     << endLog;
            return;
        }
        
        nprims = 1;
        if (PositionIndex != NullFC)
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
                if (ColorIndex != NullFC)
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
                if (NormalIndex != NullFC)
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
                if (SecColorIndex != NullFC)
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
                if (TexCoordsIndex != NullFC)
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
                    if (TexCoords1Index != NullFC)
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
                    if (TexCoords2Index != NullFC)
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
                    if (TexCoords3Index != NullFC)
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
                    if (TexCoords4Index != NullFC)
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
                    if (TexCoords5Index != NullFC)
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
                    if (TexCoords6Index != NullFC)
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
                    if (TexCoords7Index != NullFC)
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
            
            if (PositionIndex != NullFC)
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

    pumpInternalSetup( Type, GeoPTypesPtr, getTypes, true );
    pumpInternalSetup( Length, GeoPLengthsPtr, getLengths, false );

    const UInt8 *attribData[Geometry::MaxAttribs];
    UInt32 attribStride[Geometry::MaxAttribs];
    UInt32 attribInd[Geometry::MaxAttribs];
    GeoVectorPropertyPtr attribPtr[Geometry::MaxAttribs];
    GeoIntegralPropertyPtr attribIndex[Geometry::MaxAttribs];
    attribPumpFunc attribFunc[Geometry::MaxAttribs];

    UInt16 nattrib = geo->getProperties().size();
    
    for(UInt16 i = 0; i < nattrib; ++i)
    {
        attribInd[i] = 0;
        attribPtr[i] = geo->getProperty(i);
        if(attribPtr[i] != NullFC)
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
            
            if(!(attribFunc[i] = (attribPumpFunc)win->getFunction(funcid) ) )
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
    if(TypePtr == NullFC || TypePtr->getSize() == 0)
        return;

    // if it's not empty we need positions
    if(! attribData[0])
    {
        SWARNING << "masterPump: Geometry " << geo << " has no positions!?!"
                 << endLog;
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
    if(LengthPtr == NullFC)
    {
        if(TypePtr->getSize() != 1)
        {
            SWARNING << "masterPump: Geometry " << geo 
                     << " has no length but more than one type!?!"
                     << endLog;
            return;
        }
        
        nprims = 1;
        if (attribIndex[0] != NullFC)
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
                    if(attribIndex[i] != NullFC)
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

/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id$";
    static Char8 cvsid_hpp       [] = OSGGEOIMMEDIATEPUMPGROUP_HEADER_CVSID;
//    static Char8 cvsid_inl       [] = OSGGEOIMMEDIATEPUMPGROUP_INLINE_CVSID;
}

