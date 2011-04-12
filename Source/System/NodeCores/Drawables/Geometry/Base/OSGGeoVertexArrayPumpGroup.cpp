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

#include "OSGGeoVertexArrayPumpGroup.h"

OSG_USING_NAMESPACE


/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/*! An InitFuncWrapper to initialize the GeoVertexArrayPumpGroup.
*/
InitFuncWrapper
GeoVertexArrayPumpGroup::_glextInitFuncWrapper(GeoVertexArrayPumpGroup::glextInitFunction);

/*! OpenGL extension indices.
*/
UInt32 GeoVertexArrayPumpGroup::_extSecondaryColor;
UInt32 GeoVertexArrayPumpGroup::_extMultitexture;
UInt32 GeoVertexArrayPumpGroup::_arbVertexProgram;
UInt32 GeoVertexArrayPumpGroup::_extCompiledVertexArray;
UInt32 GeoVertexArrayPumpGroup::_extDrawRangeElements;

/*! OpenGL extension function indices.
*/
UInt32 GeoVertexArrayPumpGroup::_funcglSecondaryColorPointer;
UInt32 GeoVertexArrayPumpGroup::_funcglClientActiveTextureARB;
UInt32 GeoVertexArrayPumpGroup::_funcglLockArraysEXT;
UInt32 GeoVertexArrayPumpGroup::_funcglUnlockArraysEXT;
UInt32 GeoVertexArrayPumpGroup::_funcglDrawRangeElementsEXT;
UInt32 GeoVertexArrayPumpGroup::_funcglVertexAttribPointerARB;
UInt32 GeoVertexArrayPumpGroup::_funcglEnableVertexAttribArrayARB;
UInt32 GeoVertexArrayPumpGroup::_funcglDisableVertexAttribArrayARB;

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*------------- constructors & destructors --------------------------------*/

GeoVertexArrayPumpGroup::GeoVertexArrayPumpGroup(void)
{
}

GeoVertexArrayPumpGroup::~GeoVertexArrayPumpGroup(void)
{
}

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)

namespace
{
    // Pumping function definitions

    typedef void (OSG_APIENTRY *pumpFunc      )(              const UInt8 *data);
    typedef void (OSG_APIENTRY *multiPumpFunc )(GLenum which, const UInt8 *data);
    typedef void (OSG_APIENTRY *attribPumpFunc)(GLuint index, const UInt8 *data);

    // Some helper arrays for function selection
    // indexed by data type and dimension

    const Int16 formatBase = GL_BYTE;
    const Int16 numFormats = GL_DOUBLE - GL_BYTE + 1;

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
        "GL_DOUBLE"
    };

    // little helper class for function init

    class glextFuncInit
    {
      public:
        glextFuncInit(const char *name, UInt32 format, UInt32 dim,
                      bool normalizing = false) :
            _name       (name),
            _format     (format),
            _dim        (dim),
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

    glextFuncInit secondaryColorInitFuncs[8] = {
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

    glextFuncInit multiTexCoordsInitFuncs[16] = {
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

    glextFuncInit attribInitFuncs[23] = {
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

    glextFuncInit normAttribInitFuncs[6] = {
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

    pumpFunc pumpFuncs[4][numFormats][4] = {
        { // Positions
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
        },
        { // Normals
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
            { NULL, NULL,
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
              NULL }
        },
        { // Colors
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
        },
        { // TexCoords
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
        }
    };

    const UInt16 SecColorsPumpSlot  = 0;
    const UInt16 TexCoords1PumpSlot = 1;
    const UInt16 TexCoords2PumpSlot = 1;
    const UInt16 TexCoords3PumpSlot = 1;
    const UInt16 TexCoords4PumpSlot = 1;
    const UInt16 TexCoords5PumpSlot = 1;
    const UInt16 TexCoords6PumpSlot = 1;
    const UInt16 TexCoords7PumpSlot = 1;

    UInt32 pumpFuncIDs[2][numFormats][4];

    UInt32 attribPumpFuncIDs    [numFormats][4];
    UInt32 normAttribPumpFuncIDs[numFormats][4];


    struct PumpInfo
    {
        explicit PumpInfo();

        const GeoIntegralProperty         *lengths;
        const GeoIntegralProperty         *types;
        const Geometry::MFPropertiesType  *prop;
        const Geometry::MFPropIndicesType *propIdx;

        const UInt8                       *attribData  [Geometry::MaxAttribs];
              UInt32                       attribStride[Geometry::MaxAttribs];
              GeoVectorProperty           *attribPtr   [Geometry::MaxAttribs];
              GeoIntegralProperty         *attribIndex [Geometry::MaxAttribs];
    };

    PumpInfo::PumpInfo()
        : lengths(NULL),
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

    // collect info for property in 'slot'
    bool pumpGLSetup(PumpInfo &info, UInt16 slot)
    {
        bool retVal = false;

        if(slot < info.prop->size())
            info.attribPtr[slot] = (*info.prop)[slot];

        if(slot < info.propIdx->size())
            info.attribIndex[slot] = (*info.propIdx)[slot];

        if(info.attribPtr[slot]              != NULL  &&
           info.attribPtr[slot]->getIgnore() == false   )
        {
            info.attribData  [slot] = info.attribPtr[slot]->getData();
            info.attribStride[slot] = info.attribPtr[slot]->getStride();

            if(info.attribStride[slot] == 0)
            {
                info.attribStride[slot] =
                    info.attribPtr[slot]->getFormatSize() *
                    info.attribPtr[slot]->getDimension();
            }

            retVal = true;
        }

        return retVal;
    }

    // handle vertex attrib with global value
    void globalAttrib(PumpInfo &info, UInt16 slot, UInt16 pumpSlot)
    {
        if(info.attribData[slot]            != NULL &&
           info.attribPtr [slot]->getSize() == 1      )
        {
            UInt16 formatIdx = info.attribPtr[slot]->getFormat   () - formatBase;
            UInt32 dimIdx    = info.attribPtr[slot]->getDimension() - 1;

            pumpFunc pump = pumpFuncs[pumpSlot][formatIdx][dimIdx];

            if(pump == NULL)
            {
                SWARNING << "GeoVertexArrayPumpGroup - globalExtAttrib: "
                         << "Invalid pump function for property " << slot
                         << " type " << info.attribPtr[slot]->getDimension()
                         << "D " << formatNames[formatIdx]
                         << endLog;
                return;
            }

            pump(info.attribData[slot]);
            info.attribData[slot] = NULL;
        }
    }

    // handle vertex attrib with global value - using GL extension
    void globalExtAttrib(PumpInfo &info,     UInt16  slot,
                         UInt16    pumpSlot, Window *win)
    {
        if(info.attribData[slot]            != NULL &&
           info.attribPtr [slot]->getSize() == 1      )
        {
            UInt16 formatIdx = info.attribPtr[slot]->getFormat   () - formatBase;
            UInt32 dimIdx    = info.attribPtr[slot]->getDimension() - 1;
            UInt32 funcId    = pumpFuncIDs[pumpSlot][formatIdx][dimIdx];

            if(funcId == Window::invalidFunctionID)
            {
                SWARNING << "GeoVertexArrayPumpGroup - globalExtAttrib: "
                         << "Invalid extension function for property " << slot
                         << " type " << info.attribPtr[slot]->getDimension()
                         << "D " << formatNames[formatIdx]
                         << endLog;
                return;
            }

            pumpFunc pump =
                reinterpret_cast<pumpFunc>(win->getFunction(funcId));

            if(pump == NULL)
            {
                SWARNING << "GeoVertexArrayPumpGroup - globalExtAttrib: "
                         << "Extension function for property " << slot
                         << " type " << info.attribPtr[slot]->getDimension()
                         << "D " << formatNames[formatIdx]
                         << " not supported by Window " << win
                         << endLog;
                return;
            }

            pump(info.attribData[slot]);
            info.attribData[slot] = NULL;
        }
    }

    // handle vertex attrib with global value - using GL extension, multi
    void globalExtMultiAttrib(PumpInfo &info,     UInt16  slot,
                              UInt16    pumpSlot, GLenum  attrib,
                              Window   *win                      )
    {
        if(info.attribData[slot]            != NULL &&
           info.attribPtr [slot]->getSize() == 1      )
        {
            UInt16 formatIdx = info.attribPtr[slot]->getFormat   () - formatBase;
            UInt32 dimIdx    = info.attribPtr[slot]->getDimension() - 1;
            UInt32 funcId    = pumpFuncIDs[pumpSlot][formatIdx][dimIdx];

            if(funcId == Window::invalidFunctionID)
            {
                SWARNING << "GeoVertexArrayPumpGroup - globalExtMultiAttrib: "
                         << "Invalid extension function for property " << slot
                         << " type " << info.attribPtr[slot]->getDimension()
                         << "D " << formatNames[formatIdx]
                         << endLog;
                return;
            }

            multiPumpFunc pump =
                reinterpret_cast<multiPumpFunc>(win->getFunction(funcId));

            if(pump == NULL)
            {
                SWARNING << "GeoVertexArrayPumpGroup - globalExtMutliAttrib: "
                         << "Extension function for property " << slot
                         << " type " << info.attribPtr[slot]->getDimension()
                         << "D " << formatNames[formatIdx]
                         << " not supported by Window " << win
                         << endLog;
                return;
            }

            pump(attrib, info.attribData[slot]);
            info.attribData[slot] = NULL;
        }
    }

} // namespace

#endif      // remove from all but dev docs


GeoPumpGroup::GeoPump GeoVertexArrayPumpGroup::getGeoPump(
    DrawEnv                 *pEnv,
    PropertyCharacteristics  acset)
{
    // Remove the stuff we can handle
    PropertyCharacteristics prop;
    prop = acset & ~(NonTraditionalProperties|UsesShader);

    if(prop == SingleIndexed || prop == NonIndexed)
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

    return NULL;
}

bool GeoVertexArrayPumpGroup::glextInitFunction(void)
{
    _extSecondaryColor      =
        Window::registerExtension("GL_EXT_secondary_color");
    _extMultitexture        =
        Window::registerExtension("GL_ARB_multitexture");
    _arbVertexProgram       =
        Window::registerExtension("GL_ARB_vertex_program");
    _extCompiledVertexArray =
        Window::registerExtension("GL_EXT_compiled_vertex_array");
    _extDrawRangeElements   =
        Window::registerExtension("GL_EXT_draw_range_elements");

    for(UInt16 i = 0; i < numFormats; ++i)
    {
        for(UInt16 j = 0; j < 4; ++j)
        {
            pumpFuncIDs[0][i][j] = Window::invalidFunctionID;
            pumpFuncIDs[1][i][j] = Window::invalidFunctionID;
        }
    }

    for(UInt16 i = 0; i < 8; ++i)
        secondaryColorInitFuncs[i].init(pumpFuncIDs[SecColorsPumpSlot],
                                        _extSecondaryColor             );

    for(UInt16 i = 0; i < 16; ++i)
        multiTexCoordsInitFuncs[i].init(pumpFuncIDs[TexCoords1PumpSlot],
                                        _extMultitexture                );

    for(UInt16 i = 0; i < 23; ++i)
        attribInitFuncs[i].init(attribPumpFuncIDs, _arbVertexProgram);

    for(UInt16 i = 0; i < 6; ++i)
        normAttribInitFuncs[i].init(normAttribPumpFuncIDs, _arbVertexProgram);

    _funcglSecondaryColorPointer  = Window::registerFunction(
                            OSG_DLSYM_UNDERSCORE"glSecondaryColorPointerEXT",
                            _extSecondaryColor);
    _funcglClientActiveTextureARB = Window::registerFunction(
                            OSG_DLSYM_UNDERSCORE"glClientActiveTextureARB",
                            _extMultitexture);
    _funcglLockArraysEXT          = Window::registerFunction(
                            OSG_DLSYM_UNDERSCORE"glLockArraysEXT",
                            _extCompiledVertexArray);
    _funcglUnlockArraysEXT        = Window::registerFunction(
                            OSG_DLSYM_UNDERSCORE"glUnlockArraysEXT",
                            _extCompiledVertexArray);
    _funcglDrawRangeElementsEXT   = Window::registerFunction(
                            OSG_DLSYM_UNDERSCORE"glDrawRangeElementsEXT",
                            _extDrawRangeElements);
    _funcglVertexAttribPointerARB   = Window::registerFunction(
                            OSG_DLSYM_UNDERSCORE"glVertexAttribPointerARB",
                            _arbVertexProgram);
    _funcglEnableVertexAttribArrayARB   = Window::registerFunction(
                            OSG_DLSYM_UNDERSCORE"glEnableVertexAttribArrayARB",
                            _arbVertexProgram);
    _funcglDisableVertexAttribArrayARB   = Window::registerFunction(
                            OSG_DLSYM_UNDERSCORE"glDisableVertexAttribArrayARB",
                            _arbVertexProgram);

    return true;
}


void GeoVertexArrayPumpGroup::masterClassicGeoPump(
          DrawEnv                     *pEnv,
    const GeoIntegralProperty         *lengths,
    const GeoIntegralProperty         *types,
    const Geometry::MFPropertiesType  *prop,
    const Geometry::MFPropIndicesType *propIdx)
{
    Window *win = pEnv->getWindow();

    // Setup: get all the data

    // check for empty geometry
    if(types == NULL || types->getSize() == 0)
        return;

    if(!pumpInternalSetup(types,   true))
        return;
    if(!pumpInternalSetup(lengths, false))
        return;

    PumpInfo pumpInfo;
    pumpInfo.lengths = lengths;
    pumpInfo.types   = types;
    pumpInfo.prop    = prop;
    pumpInfo.propIdx = propIdx;

    // setup standard properties
    pumpGLSetup(pumpInfo, Geometry::PositionsIndex);
    pumpGLSetup(pumpInfo, Geometry::ColorsIndex);
    pumpGLSetup(pumpInfo, Geometry::NormalsIndex);
    pumpGLSetup(pumpInfo, Geometry::TexCoordsIndex);

    // setup extension properties
    pumpGLSetup(pumpInfo, Geometry::SecondaryColorsIndex);
    pumpGLSetup(pumpInfo, Geometry::TexCoords1Index);
    pumpGLSetup(pumpInfo, Geometry::TexCoords2Index);
    pumpGLSetup(pumpInfo, Geometry::TexCoords3Index);
    pumpGLSetup(pumpInfo, Geometry::TexCoords4Index);
    pumpGLSetup(pumpInfo, Geometry::TexCoords5Index);
    pumpGLSetup(pumpInfo, Geometry::TexCoords6Index);
    pumpGLSetup(pumpInfo, Geometry::TexCoords7Index);

    // we need positions
    if(pumpInfo.attribPtr[Geometry::PositionsIndex] == NULL)
    {
        if(pumpInfo.attribPtr[Geometry::PositionsIndex]              == NULL ||
           pumpInfo.attribPtr[Geometry::PositionsIndex]->getUseVBO() == false)
        {
            SWARNING << "GeoVertexArrayPumpGroup::masterClassicGeoPump: "
                     << "No positions." << endLog;
            return;
        }
    }

    // global attribs?
    globalAttrib(pumpInfo, Geometry::NormalsIndex,   NormalsPumpSlot);
    globalAttrib(pumpInfo, Geometry::ColorsIndex,    ColorsPumpSlot);
    globalAttrib(pumpInfo, Geometry::TexCoordsIndex, TexCoordsPumpSlot);

    if(win->hasExtension(_extSecondaryColor) == true)
    {
        globalExtAttrib(pumpInfo,          Geometry::SecondaryColorsIndex,
                        SecColorsPumpSlot, win                            );
    }

    if(win->hasExtension(_extMultitexture) == true)
    {
        globalExtMultiAttrib(pumpInfo,           Geometry::TexCoords1Index,
                             TexCoords1PumpSlot, GL_TEXTURE1_ARB, win);
        globalExtMultiAttrib(pumpInfo,           Geometry::TexCoords1Index,
                             TexCoords2PumpSlot, GL_TEXTURE2_ARB, win);
        globalExtMultiAttrib(pumpInfo,           Geometry::TexCoords1Index,
                             TexCoords3PumpSlot, GL_TEXTURE3_ARB, win);
        globalExtMultiAttrib(pumpInfo,           Geometry::TexCoords1Index,
                             TexCoords4PumpSlot, GL_TEXTURE4_ARB, win);
        globalExtMultiAttrib(pumpInfo,           Geometry::TexCoords1Index,
                             TexCoords5PumpSlot, GL_TEXTURE5_ARB, win);
        globalExtMultiAttrib(pumpInfo,           Geometry::TexCoords1Index,
                             TexCoords6PumpSlot, GL_TEXTURE6_ARB, win);
        globalExtMultiAttrib(pumpInfo,           Geometry::TexCoords1Index,
                             TexCoords7PumpSlot, GL_TEXTURE7_ARB, win);
    }

    // activate vertex arrays
    // !!! This should be using the global state to reduce state changes
    // and to allow sharing data between objects

    UInt16 nattrib = prop->size();

    for(Int16 i = nattrib - 1; i >= 0; --i)
    {
        if(pumpInfo.attribPtr[i] != NULL)
        {
            pumpInfo.attribPtr[i]->activate(pEnv, i);
        }
    }

    // Length handling. Special case: no length given

    UInt32 curlen;
    UInt32 nprims;

    // no lengths? use all available data for the first type
    if(lengths == NULL)
    {
        if(types->getSize() != 1)
        {
            SWARNING << "GeoVertexArrayPumpGroup::masterClassicGeoPump: "
                     << "No lengths, but more than one type?!"
                     << endLog;
            return;
        }

        nprims = 1;
        if(pumpInfo.attribIndex[Geometry::PositionsIndex] != NULL)
        {
            curlen = pumpInfo.attribIndex[Geometry::PositionsIndex]->getSize();
        }
        else
        {
            curlen = pumpInfo.attribPtr[Geometry::PositionsIndex]->getSize();
        }
    }
    else
    {
        nprims = types->getSize();
        lengths->getValue(curlen, 0);
    }

    UInt32 vertindex = 0;

    if(pumpInfo.attribIndex[0] != NULL)
    {
        // Indexed, i.e. Single Indexed

        GeoIntegralProperty *index       = pumpInfo.attribIndex[0];
        const UInt8         *indexData   = index->getData();
        GLenum               indexFormat = index->getFormat();
        UInt32               indexSize   = index->getSize();
        UInt32               indexStride =
            index->getStride() ? index->getStride() : index->getFormatSize() *
                                                      index->getDimension();

        index->activate(pEnv, 0);

        if(index->isInVBO(pEnv) == true)
        {
            indexData = NULL;
        }
        else if(win->hasExtension(_extCompiledVertexArray) == true)
        {
            void (OSG_APIENTRY*_glLockArraysEXT) (GLint first, GLsizei count)=
                reinterpret_cast<void (OSG_APIENTRY*) (GLint first,
                                                       GLsizei count)>(
                    win->getFunction(_funcglLockArraysEXT));

            _glLockArraysEXT(0, indexSize);
        }

        if(win->hasExtension(_extDrawRangeElements))
        {
            void (OSG_APIENTRY *osgGLDrawRangeElementsEXT)
                (GLenum mode, GLuint start,
                 GLuint end, GLsizei count,
                 GLenum type, const GLvoid*indices) =
                reinterpret_cast<void (OSG_APIENTRY *)(GLenum mode,
                                                       GLuint start,
                                                       GLuint end,
                                                       GLsizei count,
                                                       GLenum type,
                                                       const GLvoid*indices)>(
                    win->getFunction(_funcglDrawRangeElementsEXT));

            for(UInt32 primindex = 0; primindex < nprims; ++primindex)
            {
                if(primindex < lengths->getSize())
                    curlen = lengths->getValue<UInt32>(primindex);

                osgGLDrawRangeElementsEXT(types->getValue<UInt16>(primindex),
                                          0,
                                          indexSize,
                                          curlen,
                                          indexFormat,
                                          indexData + vertindex * indexStride);

                vertindex += curlen;
            }
        }
        else
        {
            for(UInt32 primindex = 0; primindex < nprims; ++primindex)
            {
                if(primindex < lengths->getSize())
                    curlen = lengths->getValue<UInt32>(primindex);

                glDrawElements(types->getValue<UInt16>(primindex),
                               curlen,
                               indexFormat,
                               indexData + vertindex * indexStride);

                vertindex += curlen;
            }
        }

        if(index->isInVBO(pEnv)                       == false &&
           win->hasExtension(_extCompiledVertexArray) == true    )
        {
            void (OSG_APIENTRY*_glUnlockArraysEXT)(void)=
                reinterpret_cast<void (OSG_APIENTRY*) (void)>(
                    win->getFunction(_funcglUnlockArraysEXT));

            _glUnlockArraysEXT();
        }

        index->deactivate(pEnv, 0);
    }
    else
    {
        // Non-indexed
        for(UInt32 primindex = 0; primindex < nprims; ++primindex)
        {
            if(primindex < lengths->getSize())
                curlen = lengths->getValue<UInt32>(primindex);

            glDrawArrays(types->getValue<UInt16>(primindex), vertindex,
                         curlen);
            vertindex += curlen;
        }
    }

    // disable arrays
    for(Int16 i = nattrib - 1; i >= 0; --i)
    {
        if(pumpInfo.attribPtr[i] != NULL)
        {
            pumpInfo.attribPtr[i]->deactivate(pEnv, i);
        }
    }
}

void GeoVertexArrayPumpGroup::masterAttribGeoPump(
          DrawEnv                     *pEnv,
    const GeoIntegralProperty         *lengths,
    const GeoIntegralProperty         *types,
    const Geometry::MFPropertiesType  *prop,
    const Geometry::MFPropIndicesType *propIdx)
{
    Window *win = pEnv->getWindow();

    // Setup: get all the data

    // check for empty geometry
    if(types == NULL || types->getSize() == 0)
        return;

    if(!pumpInternalSetup(types,   true))
        return;
    if(!pumpInternalSetup(lengths, false))
        return;

    attribPumpFunc attribFunc[Geometry::MaxAttribs];
    PumpInfo       pumpInfo;
    pumpInfo.lengths = lengths;
    pumpInfo.types   = types;
    pumpInfo.prop    = prop;
    pumpInfo.propIdx = propIdx;

    UInt16 nattrib = prop->size();

    for(UInt16 i = 0; i < nattrib; ++i)
    {
        if(pumpGLSetup(pumpInfo, i) == false)
            continue;

        UInt16 formatIdx = pumpInfo.attribPtr[i]->getFormat   () - formatBase;
        UInt16 dimIdx    = pumpInfo.attribPtr[i]->getDimension() - 1;
        UInt32 funcId    = Window::invalidFunctionID;

        if(pumpInfo.attribPtr[i]->getNormalize() == true)
        {
            funcId = normAttribPumpFuncIDs[formatIdx][dimIdx];

            if(funcId == Window::invalidFunctionID)
            {
                SWARNING << "GeoVertexArrayPumpGroup::masterAttribGeoPump: "
                         << "Invalid pump function for property " << i
                         << " type " << pumpInfo.attribPtr[i]->getDimension()
                         << "D " << formatNames[formatIdx] << " (normalizing)."
                         << endLog;

                pumpInfo.attribData[i] = NULL;
                pumpInfo.attribPtr [i] = NULL;
                continue;
            }
        }
        else
        {
            funcId = attribPumpFuncIDs[formatIdx][dimIdx];

            if(funcId == Window::invalidFunctionID)
            {
                SWARNING << "GeoVertexArrayPumpGroup::masterAttribGeoPump: "
                         << "Invalid pump function for property " << i
                         << " type " << pumpInfo.attribPtr[i]->getDimension()
                         << "D " << formatNames[formatIdx]
                         << endLog;

                pumpInfo.attribData[i] = NULL;
                pumpInfo.attribPtr [i] = NULL;
                continue;
            }
        }

        attribFunc[i] = reinterpret_cast<attribPumpFunc>(
            win->getFunction(funcId));

        if(attribFunc[i] == NULL)
        {
            SWARNING << "GeoVertexArrayPumpGroup::masterAttribGeoPump: "
                     << "Extension function for property " << i
                     << " type " << pumpInfo.attribPtr[i]->getDimension()
                     << "D " << formatNames[formatIdx]
                     << " not supported by Window " << win
                     << endLog;

            pumpInfo.attribData[i] = NULL;
            pumpInfo.attribPtr [i] = NULL;
            continue;
        }
    }

    // we need positions
    if(pumpInfo.attribPtr[0] == NULL)
    {
        if(pumpInfo.attribPtr[0]              == NULL ||
           pumpInfo.attribPtr[0]->getUseVBO() == false)
        {
            SWARNING << "GeoVertexArrayPumpGroup::masterAttribGeoPump: "
                     << "No positions." << endLog;
            return;
        }
    }

    // global attribs?
    for(Int16 i = 0; i < nattrib; ++i)
    {
        if(pumpInfo.attribData[i]            != NULL &&
           pumpInfo.attribPtr [i]->getSize() == 1      )
        {
            attribFunc[i](i, pumpInfo.attribData[i]);
            pumpInfo.attribData[i] = NULL;
        }
    }

    // activate vertex arrays
    // !!! This should be using the global state to reduce state changes
    // and to allow sharing data between objects

    for(Int16 i = nattrib - 1; i >= 0; --i)
    {
        if(pumpInfo.attribPtr[i] != NULL)
        {
            pumpInfo.attribPtr[i]->activate(pEnv, i + 16); // XXX HACK
        }
    }

    // Length handling. Special case: no length given

    UInt32 curlen;
    UInt32 nprims;

    // no lengths? use all available data for the first type
    if(lengths == NULL)
    {
        if(types->getSize() != 1)
        {
            SWARNING << "GeoVertexArrayPumpGroup::masterAttribGeoPump: "
                     << "No lengths, but more than one type?!"
                     << endLog;
            return;
        }

        nprims = 1;
        if(pumpInfo.attribIndex[0] != NULL)
        {
            curlen = pumpInfo.attribIndex[0]->getSize();
        }
        else
        {
            curlen = pumpInfo.attribPtr[0]->getSize();
        }
    }
    else
    {
        nprims = types->getSize();
        lengths->getValue(curlen, 0);
    }

    UInt32 vertindex = 0;

    if(pumpInfo.attribIndex[0] != NULL)
    {
        // Single Indexed

        GeoIntegralProperty *index       = pumpInfo.attribIndex[0];
        const UInt8         *indexData   = index->getData();
        GLenum               indexFormat = index->getFormat();
        UInt32               indexSize   = index->getSize();
        UInt32               indexStride =
            index->getStride() ? index->getStride() : index->getFormatSize() *
                                                      index->getDimension();

        index->activate(pEnv, 0);

        if(index->isInVBO(pEnv))
        {
            indexData = NULL;
        }
        else if (win->hasExtension(_extCompiledVertexArray))
        {
            void (OSG_APIENTRY*_glLockArraysEXT) (GLint first, GLsizei count)=
                reinterpret_cast<void (OSG_APIENTRY*) (GLint first,
                                                       GLsizei count)>(
                                                           win->getFunction(_funcglLockArraysEXT));

            _glLockArraysEXT(0, indexSize);
        }

        if(win->hasExtension(_extDrawRangeElements))
        {
            void (OSG_APIENTRY *osgGLDrawRangeElementsEXT)
                (GLenum mode, GLuint start,
                 GLuint end, GLsizei count,
                 GLenum type, const GLvoid*indices) =
                reinterpret_cast<void (OSG_APIENTRY *)(GLenum mode,
                                                       GLuint start,
                                                       GLuint end,
                                                       GLsizei count,
                                                       GLenum type,
                                                       const GLvoid*indices)>(
                    win->getFunction(_funcglDrawRangeElementsEXT));

            for(UInt32 primindex = 0; primindex < nprims; ++primindex)
            {
                if(primindex < lengths->getSize())
                    curlen = lengths->getValue<UInt32>(primindex);

                osgGLDrawRangeElementsEXT(types->getValue<UInt16>(primindex),
                                          0,
                                          indexSize,
                                          curlen,
                                          indexFormat,
                                          indexData + vertindex * indexStride);

                vertindex += curlen;
            }
        }
        else
        {
            for(UInt32 primindex = 0; primindex < nprims; ++primindex)
            {
                if(primindex < lengths->getSize())
                    curlen = lengths->getValue<UInt32>(primindex);

                glDrawElements(types->getValue<UInt16>(primindex),
                               curlen,
                               indexFormat,
                               indexData + vertindex * indexStride);

                vertindex += curlen;
            }
        }

        if(index->isInVBO(pEnv)                       == false &&
           win->hasExtension(_extCompiledVertexArray) == true    )
        {
            void (OSG_APIENTRY*_glUnlockArraysEXT)(void)=
                reinterpret_cast<void (OSG_APIENTRY*) (void)>(
                    win->getFunction(_funcglUnlockArraysEXT));

            _glUnlockArraysEXT();
        }

        index->deactivate(pEnv, 0);
    }
    else
    {
        // Non-indexed
        for(UInt32 primindex = 0; primindex < nprims; ++primindex)
        {
            if(primindex < lengths->getSize())
                curlen = lengths->getValue<UInt32>(primindex);

            glDrawArrays(types->getValue<UInt16>(primindex), vertindex,
                         curlen);
            vertindex += curlen;
        }
    }

    // disable arrays
    for(Int16 i = nattrib - 1; i >= 0; --i)
    {
        if(pumpInfo.attribData[i] != NULL)
        {
            pumpInfo.attribPtr[i]->deactivate(pEnv, i + 16);
        }
    }
}
