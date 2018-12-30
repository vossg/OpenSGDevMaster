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

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)

#if __GNUC__ >= 4 || __GNUC_MINOR__ >=3
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#endif

namespace
{
    // Pumping function definitions

    typedef void (OSG_APIENTRY *pumpFunc      )(const UInt8  *data);
    typedef void (OSG_APIENTRY *multiPumpFunc )(      GLenum  which, 
                                                const UInt8  *data);
    typedef void (OSG_APIENTRY *attribPumpFunc)(      GLuint  index, 
                                                const UInt8  *data);


    // Some helper arrays for function selection
    // indexed by data type and dimension

    const Int16 formatBase = GL_BYTE;
#ifndef OSG_OGL_NO_DOUBLE
    const Int16 numFormats = GL_DOUBLE  - GL_BYTE + 1;
#else
    const Int16 numFormats = GL_4_BYTES - GL_BYTE + 1;
#endif

    const char *formatNames[] =
    {   "GL_BYTE",
        "GL_UNSIGNED_BYTE",
        "GL_SHORT",
        "GL_UNSIGNED_SHORT",
        "GL_INT",
        "GL_UNSIGNED_INT",
        "GL_FLOAT",
        "GL_2_BYTES",
        "GL_3_BYTES",
        "GL_4_BYTES",
#ifndef OSG_OGL_NO_DOUBLE
        "GL_DOUBLE",
        "GL_DOUBLE_EXT",  // Not used
#endif
        "GL_FIXED"        // Not used
    };

    // little helper class for function init

    class glextFuncInit
    {
      public:

        glextFuncInit(const char   *name, 
                            UInt32  format, 
                            UInt32  dim,
                            bool    normalizing = false) :
            
            _name       (name       ),
            _format     (format     ),
            _dim        (dim        ),
            _normalizing(normalizing)
        {
        };

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


#if !defined(OSG_OGL_COREONLY) || defined(OSG_CHECK_COREONLY)

    const UInt32 uiNumSecColFunc = 8;

    glextFuncInit secondaryColorInitFuncs[uiNumSecColFunc] = {
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

    const UInt32 uiNumMTexFuncs = 16;

    glextFuncInit multiTexCoordsInitFuncs[uiNumMTexFuncs] = {
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

#endif


#ifndef OSG_OGL_NO_DOUBLE
    const UInt32 uiNumAttribFuncs = 23;
#else
    const UInt32 uiNumAttribFuncs = 19;
#endif

    glextFuncInit attribInitFuncs[uiNumAttribFuncs] = {
        glextFuncInit(OSG_DLSYM_UNDERSCORE"glVertexAttrib1svARB",
                      GL_SHORT,
                      1),
        glextFuncInit(OSG_DLSYM_UNDERSCORE"glVertexAttrib1fvARB",
                      GL_FLOAT,
                      1),
#ifndef OSG_OGL_NO_DOUBLE
        glextFuncInit(OSG_DLSYM_UNDERSCORE"glVertexAttrib1dvARB",
                      GL_DOUBLE,
                      1),
#endif
        glextFuncInit(OSG_DLSYM_UNDERSCORE"glVertexAttrib2svARB",
                      GL_SHORT,
                      2),
        glextFuncInit(OSG_DLSYM_UNDERSCORE"glVertexAttrib2fvARB",
                      GL_FLOAT,
                      2),
#ifndef OSG_OGL_NO_DOUBLE
        glextFuncInit(OSG_DLSYM_UNDERSCORE"glVertexAttrib2dvARB",
                      GL_DOUBLE,
                      2),
#endif
        glextFuncInit(OSG_DLSYM_UNDERSCORE"glVertexAttrib3svARB",
                      GL_SHORT,
                      3),
        glextFuncInit(OSG_DLSYM_UNDERSCORE"glVertexAttrib3fvARB",
                      GL_FLOAT,
                      3),
#ifndef OSG_OGL_NO_DOUBLE
        glextFuncInit(OSG_DLSYM_UNDERSCORE"glVertexAttrib3dvARB",
                      GL_DOUBLE,
                      3),
#endif
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
#ifndef OSG_OGL_NO_DOUBLE
        glextFuncInit(OSG_DLSYM_UNDERSCORE"glVertexAttrib4dvARB",
                      GL_DOUBLE,
                      4),
#endif
    };

    const UInt32 uiNumNormAttribFuncs = 6;

    glextFuncInit normAttribInitFuncs[uiNumNormAttribFuncs] = {
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



    // Classic pumping functions

    const UInt16 PositionsPumpSlot = 0;
    const UInt16 NormalsPumpSlot   = 1;
    const UInt16 ColorsPumpSlot    = 2;
    const UInt16 TexCoordsPumpSlot = 3;


#if !defined(OSG_OGL_COREONLY) || defined(OSG_CHECK_COREONLY)
    pumpFunc pumpFuncs[4][numFormats][4] = {
        { // Positions
            { NULL, NULL, NULL, NULL },                     // GL_BYTE
            { NULL, NULL, NULL, NULL },                     // GL_UNSIGNED_BYTE
            { NULL,
              reinterpret_cast<pumpFunc>(glVertex2sv),
              reinterpret_cast<pumpFunc>(glVertex3sv),
              reinterpret_cast<pumpFunc>(glVertex4sv) },    // GL_SHORT
            { NULL, NULL, NULL, NULL },                     // GL_UNSIGNED_SHORT
            { NULL,
              reinterpret_cast<pumpFunc>(glVertex2iv),
              reinterpret_cast<pumpFunc>(glVertex3iv),
              reinterpret_cast<pumpFunc>(glVertex4iv) },    // GL_INT
            { NULL, NULL, NULL, NULL },                     // GL_UNSIGNED_INT
            { NULL,
              reinterpret_cast<pumpFunc>(glVertex2fv),
              reinterpret_cast<pumpFunc>(glVertex3fv),
              reinterpret_cast<pumpFunc>(glVertex4fv) },    // GL_FLOAT
            { NULL, NULL, NULL, NULL },                     // GL_2_BYTES
            { NULL, NULL, NULL, NULL },                     // GL_3_BYTES
            { NULL, NULL, NULL, NULL },                     // GL_4_BYTES
            { NULL,
              reinterpret_cast<pumpFunc>(glVertex2dv),
              reinterpret_cast<pumpFunc>(glVertex3dv),
              reinterpret_cast<pumpFunc>(glVertex4dv) },    // GL_DOUBLE
        },
        { // Normals
            { NULL,
              NULL,
              reinterpret_cast<pumpFunc>(glNormal3sv),
              NULL },                                       // GL_BYTE
            { NULL, NULL, NULL, NULL },                     // GL_UNSIGNED_BYTE
            { NULL,
              NULL,
              reinterpret_cast<pumpFunc>(glNormal3sv),
              NULL },                                       // GL_SHORT
            { NULL, NULL, NULL, NULL },                     // GL_UNSIGNED_SHORT
            { NULL, NULL,
              reinterpret_cast<pumpFunc>(glNormal3iv),
              NULL },                                       // GL_INT
            { NULL, NULL, NULL, NULL },                     // GL_UNSIGNED_INT
            { NULL,
              NULL,
              reinterpret_cast<pumpFunc>(glNormal3fv),
              NULL },                                       // GL_FLOAT
            { NULL, NULL, NULL, NULL },                     // GL_2_BYTES
            { NULL, NULL, NULL, NULL },                     // GL_3_BYTES
            { NULL, NULL, NULL, NULL },                     // GL_4_BYTES
            { NULL,
              NULL,
              reinterpret_cast<pumpFunc>(glNormal3dv),
              NULL }
        },
        { // Colors
            { NULL,
              NULL,
              reinterpret_cast<pumpFunc>(glColor3bv),
              reinterpret_cast<pumpFunc>(glColor4bv) },     // GL_BYTE
            { NULL,
              NULL,
              reinterpret_cast<pumpFunc>(glColor3ubv),
              reinterpret_cast<pumpFunc>(glColor4ubv) },    // GL_UNSIGNED_BYTE
            { NULL,
              NULL,
              reinterpret_cast<pumpFunc>(glColor3sv),
              reinterpret_cast<pumpFunc>(glColor4sv) },     // GL_SHORT
            { NULL,
              NULL,
              reinterpret_cast<pumpFunc>(glColor3usv),
              reinterpret_cast<pumpFunc>(glColor4usv) },    // GL_UNSIGNED_SHORT
            { NULL,
              NULL,
              reinterpret_cast<pumpFunc>(glColor3iv),
              reinterpret_cast<pumpFunc>(glColor4iv) },     // GL_INT
            { NULL,
              NULL,
              reinterpret_cast<pumpFunc>(glColor3uiv),
              reinterpret_cast<pumpFunc>(glColor4uiv) },    // GL_UNSIGNED_INT
            { NULL,
              NULL,
              reinterpret_cast<pumpFunc>(glColor3fv),
              reinterpret_cast<pumpFunc>(glColor4fv) },     // GL_FLOAT
            { NULL, NULL, NULL, NULL },                     // GL_2_BYTES
            { NULL, NULL, NULL, NULL },                     // GL_3_BYTES
            { NULL, NULL, NULL, NULL },                     // GL_4_BYTES
            { NULL,
              NULL,
              reinterpret_cast<pumpFunc>(glColor3dv),
              reinterpret_cast<pumpFunc>(glColor4dv) },     // GL_DOUBLE
        },
        { // TexCoords
            { NULL, NULL, NULL, NULL },                     // GL_BYTE
            { NULL, NULL, NULL, NULL },                     // GL_UNSIGNED_BYTE
            { reinterpret_cast<pumpFunc>(glTexCoord1sv),
              reinterpret_cast<pumpFunc>(glTexCoord2sv),
              reinterpret_cast<pumpFunc>(glTexCoord3sv),
              reinterpret_cast<pumpFunc>(glTexCoord4sv) },  // GL_SHORT
            { NULL, NULL, NULL, NULL },                     // GL_UNSIGNED_SHORT
            { reinterpret_cast<pumpFunc>(glTexCoord1iv),
              reinterpret_cast<pumpFunc>(glTexCoord2iv),
              reinterpret_cast<pumpFunc>(glTexCoord3iv),
              reinterpret_cast<pumpFunc>(glTexCoord4iv) },  // GL_INT
            { NULL, NULL, NULL, NULL },                     // GL_UNSIGNED_INT
            { reinterpret_cast<pumpFunc>(glTexCoord1fv),
              reinterpret_cast<pumpFunc>(glTexCoord2fv),
              reinterpret_cast<pumpFunc>(glTexCoord3fv),
              reinterpret_cast<pumpFunc>(glTexCoord4fv) },  // GL_FLOAT
            { NULL, NULL, NULL, NULL },                     // GL_2_BYTES
            { NULL, NULL, NULL, NULL },                     // GL_3_BYTES
            { NULL, NULL, NULL, NULL },                     // GL_4_BYTES
            { reinterpret_cast<pumpFunc>(glTexCoord1dv),
              reinterpret_cast<pumpFunc>(glTexCoord2dv),
              reinterpret_cast<pumpFunc>(glTexCoord3dv),
              reinterpret_cast<pumpFunc>(glTexCoord4dv) },  // GL_DOUBLE
        }
    };
#endif


#if defined(OSG_USE_OGLES_PROTOS) || defined(OSG_USE_OGL3_PROTOS) || \
    defined(OSG_USE_OGL4_PROTOS)

    attribPumpFunc attribPumpFuncs[numFormats][4] = {
#if !defined(OSG_USE_OGLES_PROTOS)
        { NULL, NULL, NULL,                                       // GL_BYTE
          reinterpret_cast<attribPumpFunc>(glVertexAttrib4bv) },
        { NULL, NULL, NULL,                                       // GL_UBYTE
          reinterpret_cast<attribPumpFunc>(glVertexAttrib4ubv) },
        { reinterpret_cast<attribPumpFunc>(glVertexAttrib1sv),
          reinterpret_cast<attribPumpFunc>(glVertexAttrib2sv),
          reinterpret_cast<attribPumpFunc>(glVertexAttrib3sv),
          reinterpret_cast<attribPumpFunc>(glVertexAttrib4sv) },  // GL_SHORT
        { NULL, NULL, NULL,                                       // GL_USHORT
          reinterpret_cast<attribPumpFunc>(glVertexAttrib4usv) }, 
        { NULL, NULL, NULL,                                       // GL_INT
          reinterpret_cast<attribPumpFunc>(glVertexAttrib4iv) }, 
        { NULL, NULL, NULL,                                       // GL_UINT
          reinterpret_cast<attribPumpFunc>(glVertexAttrib4uiv) },
#else
        { NULL, NULL, NULL, NULL },                     // GL_BYTE   ES
        { NULL, NULL, NULL, NULL },                     // GL_UBYTE  ES
        { NULL, NULL, NULL, NULL },                     // GL_SHORT  ES
        { NULL, NULL, NULL, NULL },                     // GL_USHORT ES
        { NULL, NULL, NULL, NULL },                     // GL_INT    ES
        { NULL, NULL, NULL, NULL },                     // GL_UINT   ES
#endif
        { reinterpret_cast<attribPumpFunc>(glVertexAttrib1fv),
          reinterpret_cast<attribPumpFunc>(glVertexAttrib2fv),
          reinterpret_cast<attribPumpFunc>(glVertexAttrib3fv),
          reinterpret_cast<attribPumpFunc>(glVertexAttrib4fv)  }, // GL_FLOAT
        { NULL, NULL, NULL, NULL },                               // GL_2_BYTES
        { NULL, NULL, NULL, NULL },                               // GL_3_BYTES
        { NULL, NULL, NULL, NULL },                               // GL_4_BYTES
#if !defined(OSG_OGL_NO_DOUBLE)
        { reinterpret_cast<attribPumpFunc>(glVertexAttrib1dv),
          reinterpret_cast<attribPumpFunc>(glVertexAttrib2dv),
          reinterpret_cast<attribPumpFunc>(glVertexAttrib3dv),
          reinterpret_cast<attribPumpFunc>(glVertexAttrib4dv)  }  // GL_DOUBLE
#endif
    };


    attribPumpFunc attribNormPumpFuncs[numFormats][4] = {
#if !defined(OSG_USE_OGLES_PROTOS)
        { NULL, NULL, NULL,                                        // GL_BYTE
          reinterpret_cast<attribPumpFunc>(glVertexAttrib4Nbv)  },
        { NULL, NULL, NULL,                                        // GL_UBYTE
          reinterpret_cast<attribPumpFunc>(glVertexAttrib4Nubv) },
        { NULL, NULL, NULL,
          reinterpret_cast<attribPumpFunc>(glVertexAttrib4Nsv)  }, // GL_SHORT
        { NULL, NULL, NULL,                                        // GL_USHORT
          reinterpret_cast<attribPumpFunc>(glVertexAttrib4Nusv) }, 
        { NULL, NULL, NULL,                                        // GL_INT
          reinterpret_cast<attribPumpFunc>(glVertexAttrib4Niv)  }, 
        { NULL, NULL, NULL,                                        // GL_UINT
          reinterpret_cast<attribPumpFunc>(glVertexAttrib4Nuiv) },
        { NULL, NULL, NULL, NULL },                               // GL_FLOAT
        { NULL, NULL, NULL, NULL },                               // GL_2_BYTES
        { NULL, NULL, NULL, NULL },                               // GL_3_BYTES
        { NULL, NULL, NULL, NULL },                               // GL_4_BYTES
#if !defined(OSG_OGL_NO_DOUBLE)
        { NULL, NULL, NULL, NULL }                                // GL_DOUBLE
#endif

#else // !OSG_USE_OGLES_PROTOS
        { NULL, NULL, NULL, NULL },                     // GL_BYTE    ES
        { NULL, NULL, NULL, NULL },                     // GL_UBYTE   ES
        { NULL, NULL, NULL, NULL },                     // GL_SHORT   ES
        { NULL, NULL, NULL, NULL },                     // GL_USHORT  ES
        { NULL, NULL, NULL, NULL },                     // GL_INT     ES
        { NULL, NULL, NULL, NULL },                     // GL_UINT    ES
        { NULL, NULL, NULL, NULL },                     // GL_FLOAT   ES
        { NULL, NULL, NULL, NULL },                     // GL_2_BYTES ES
        { NULL, NULL, NULL, NULL },                     // GL_3_BYTES ES
        { NULL, NULL, NULL, NULL },                     // GL_4_BYTES ES
#if !defined(OSG_OGL_NO_DOUBLE)
        { NULL, NULL, NULL, NULL }                      // GL_DOUBLE  ES
#endif
#endif // OSG_USE_OGLES_PROTOS
    };
#endif 



    const UInt16 SecColorsPumpSlot  = 0;
    const UInt16 TexCoords1PumpSlot = 1;
    const UInt16 TexCoords2PumpSlot = 1;
    const UInt16 TexCoords3PumpSlot = 1;
    const UInt16 TexCoords4PumpSlot = 1;
    const UInt16 TexCoords5PumpSlot = 1;
    const UInt16 TexCoords6PumpSlot = 1;
    const UInt16 TexCoords7PumpSlot = 1;

#if !defined(OSG_OGL_COREONLY) || defined(OSG_CHECK_COREONLY)
    UInt32 pumpFuncIDs       [2][numFormats][4];
#endif

    UInt32 attribPumpFuncIDs    [numFormats][4];
    UInt32 normAttribPumpFuncIDs[numFormats][4];


    struct PumpData
    {
        explicit PumpData();

        const GeoIntegralProperty         *lengths;
        const GeoIntegralProperty         *types;
        const Geometry::MFPropertiesType  *prop;
        const Geometry::MFPropIndicesType *propIdx;

        const UInt8                       *attribData  [Geometry::MaxAttribs];
              UInt32                       attribStride[Geometry::MaxAttribs];
              GeoVectorProperty           *attribPtr   [Geometry::MaxAttribs];
              GeoIntegralProperty         *attribIndex [Geometry::MaxAttribs];
    };

    PumpData::PumpData() : 
        lengths(NULL),
        types  (NULL),
        prop   (NULL),
        propIdx(NULL)
    {
        for(Int16 i = 0; i < Geometry::MaxAttribs; ++i)
        {
            attribData  [i] = NULL;
            attribStride[i] = 0;
            attribPtr   [i] = NULL;
            attribIndex [i] = NULL;
        }
    }

    struct PumpAttribInfo : public PumpData
    {
        explicit PumpAttribInfo(void);

        attribPumpFunc attribPump[Geometry::MaxAttribs];

    };

    PumpAttribInfo::PumpAttribInfo(void) :
        PumpData()
    {
        for(Int16 i = 0; i < Geometry::MaxAttribs; ++i)
        {
            attribPump[i] = NULL;
        }
    }


    // check mandatory properties
    bool pumpInternalSetup(const GeoIntegralProperty* prop, bool mandatory)
    {
        bool retVal = true;

        if(mandatory == true && prop == NULL)
        {
            retVal = false;
        }

        return retVal;
    }

}

#if __GNUC__ >= 4 || __GNUC_MINOR__ >=3
#pragma GCC diagnostic pop
#endif

#endif // remove from all but dev docs

