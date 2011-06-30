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

#include "OSGGLFuncProtos.h"

OSG_BEGIN_NAMESPACE

// Intentionally INSIDE the namespace
#include "OSGGeoPumpCommon.inl"


/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/*! An InitFuncWrapper to initialize the GeoVertexArrayPumpGroup.
*/

InitFuncWrapper GeoVertexArrayPumpGroup::_glextInitFuncWrapper(
    GeoVertexArrayPumpGroup::glextInitFunction);

/*! OpenGL extension indices.
*/
UInt32 GeoVertexArrayPumpGroup::_extSecondaryColor;
UInt32 GeoVertexArrayPumpGroup::_extMultitexture;
UInt32 GeoVertexArrayPumpGroup::_arbVertexProgram;
UInt32 GeoVertexArrayPumpGroup::_extCompiledVertexArray;

/*! OpenGL extension function indices.
*/
UInt32 GeoVertexArrayPumpGroup::_funcglSecondaryColorPointer;
UInt32 GeoVertexArrayPumpGroup::_funcglClientActiveTextureARB;
UInt32 GeoVertexArrayPumpGroup::_funcglLockArraysEXT;
UInt32 GeoVertexArrayPumpGroup::_funcglUnlockArraysEXT;
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
    // collect info for property in 'slot'
    bool pumpGLSetup(PumpData &info, UInt16 slot)
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

#if !defined(OSG_OGL_COREONLY) || defined(OSG_CHECK_COREONLY)
    // handle vertex attrib with global value
    void globalAttrib(PumpData &info, UInt16 slot, UInt16 pumpSlot)
    {
        if(info.attribData[slot]            != NULL &&
           info.attribPtr [slot]->getSize() == 1      )
        {
            UInt16 formatIdx = info.attribPtr[slot]->getFormat() - formatBase;
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
#endif

#if !defined(OSG_OGL_COREONLY) || defined(OSG_CHECK_COREONLY)
    // handle vertex attrib with global value - using GL extension
    void globalExtAttrib(PumpData &info,     UInt16  slot,
                         UInt16    pumpSlot, Window *win)
    {
        if(info.attribData[slot]            != NULL &&
           info.attribPtr [slot]->getSize() == 1      )
        {
            UInt16 formatIdx = info.attribPtr[slot]->getFormat() - formatBase;
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
#endif

#if !defined(OSG_OGL_COREONLY) || defined(OSG_CHECK_COREONLY)
    // handle vertex attrib with global value - using GL extension, multi
    void globalExtMultiAttrib(PumpData &info,     UInt16  slot,
                              UInt16    pumpSlot, GLenum  attrib,
                              Window   *win                      )
    {
        if(info.attribData[slot]            != NULL &&
           info.attribPtr [slot]->getSize() == 1      )
        {
            UInt16 formatIdx = info.attribPtr[slot]->getFormat() - formatBase;
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
#endif

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

        if(win->hasExtOrVersion(_arbVertexProgram, 
                                 0x0200, 
                                 0x0200           ) && (acset & UsesShader))
        {
            return masterAttribGeoPump;
        }
#if !defined(OSG_OGL_COREONLY) || defined(OSG_CHECK_COREONLY)
        else
        {
            return masterClassicGeoPump;
        }
#endif
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

#if !defined(OSG_OGL_COREONLY) || defined(OSG_CHECK_COREONLY)
    for(UInt16 i = 0; i < numFormats; ++i)
    {
        for(UInt16 j = 0; j < 4; ++j)
        {
            pumpFuncIDs[0][i][j] = Window::invalidFunctionID;
            pumpFuncIDs[1][i][j] = Window::invalidFunctionID;
        }
    }

    for(UInt16 i = 0; i < uiNumSecColFunc; ++i)
        secondaryColorInitFuncs[i].init(pumpFuncIDs[SecColorsPumpSlot],
                                        _extSecondaryColor             );

    for(UInt16 i = 0; i < uiNumMTexFuncs; ++i)
        multiTexCoordsInitFuncs[i].init(pumpFuncIDs[TexCoords1PumpSlot],
                                        _extMultitexture                );
#endif

    for(UInt16 i = 0; i < uiNumAttribFuncs; ++i)
        attribInitFuncs[i].init(attribPumpFuncIDs, _arbVertexProgram);

    for(UInt16 i = 0; i < uiNumNormAttribFuncs; ++i)
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


#if !defined(OSG_OGL_COREONLY) || defined(OSG_CHECK_COREONLY)
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

    PumpData pumpData;
    pumpData.lengths = lengths;
    pumpData.types   = types;
    pumpData.prop    = prop;
    pumpData.propIdx = propIdx;

    // setup standard properties
    pumpGLSetup(pumpData, Geometry::PositionsIndex);
    pumpGLSetup(pumpData, Geometry::ColorsIndex);
    pumpGLSetup(pumpData, Geometry::NormalsIndex);
    pumpGLSetup(pumpData, Geometry::TexCoordsIndex);

    // setup extension properties
    pumpGLSetup(pumpData, Geometry::SecondaryColorsIndex);
    pumpGLSetup(pumpData, Geometry::TexCoords1Index);
    pumpGLSetup(pumpData, Geometry::TexCoords2Index);
    pumpGLSetup(pumpData, Geometry::TexCoords3Index);
    pumpGLSetup(pumpData, Geometry::TexCoords4Index);
    pumpGLSetup(pumpData, Geometry::TexCoords5Index);
    pumpGLSetup(pumpData, Geometry::TexCoords6Index);
    pumpGLSetup(pumpData, Geometry::TexCoords7Index);

    // we need positions
    if(pumpData.attribPtr[Geometry::PositionsIndex] == NULL)
    {
        if(pumpData.attribPtr[Geometry::PositionsIndex]              == NULL ||
           pumpData.attribPtr[Geometry::PositionsIndex]->getUseVBO() == false)
        {
            SWARNING << "GeoVertexArrayPumpGroup::masterClassicGeoPump: "
                     << "No positions." << endLog;
            return;
        }
    }

    // global attribs?
    globalAttrib(pumpData, Geometry::NormalsIndex,   NormalsPumpSlot);
    globalAttrib(pumpData, Geometry::ColorsIndex,    ColorsPumpSlot);
    globalAttrib(pumpData, Geometry::TexCoordsIndex, TexCoordsPumpSlot);

    if(win->hasExtOrVersion(_extSecondaryColor, 0x0104) == true)
    {
        globalExtAttrib(pumpData,          Geometry::SecondaryColorsIndex,
                        SecColorsPumpSlot, win                            );
    }

    if(win->hasExtOrVersion(_extMultitexture, 0x0103, 0x0200) == true)
    {
        globalExtMultiAttrib(pumpData,           Geometry::TexCoords1Index,
                             TexCoords1PumpSlot, GL_TEXTURE1_ARB, win);
        globalExtMultiAttrib(pumpData,           Geometry::TexCoords1Index,
                             TexCoords2PumpSlot, GL_TEXTURE2_ARB, win);
        globalExtMultiAttrib(pumpData,           Geometry::TexCoords1Index,
                             TexCoords3PumpSlot, GL_TEXTURE3_ARB, win);
        globalExtMultiAttrib(pumpData,           Geometry::TexCoords1Index,
                             TexCoords4PumpSlot, GL_TEXTURE4_ARB, win);
        globalExtMultiAttrib(pumpData,           Geometry::TexCoords1Index,
                             TexCoords5PumpSlot, GL_TEXTURE5_ARB, win);
        globalExtMultiAttrib(pumpData,           Geometry::TexCoords1Index,
                             TexCoords6PumpSlot, GL_TEXTURE6_ARB, win);
        globalExtMultiAttrib(pumpData,           Geometry::TexCoords1Index,
                             TexCoords7PumpSlot, GL_TEXTURE7_ARB, win);
    }

    // activate vertex arrays
    // !!! This should be using the global state to reduce state changes
    // and to allow sharing data between objects

    UInt16 nattrib = prop->size();

    for(Int16 i = nattrib - 1; i >= 0; --i)
    {
        if(pumpData.attribPtr[i] != NULL)
        {
            pumpData.attribPtr[i]->activate(pEnv, i);
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
        if(pumpData.attribIndex[Geometry::PositionsIndex] != NULL)
        {
            curlen = pumpData.attribIndex[Geometry::PositionsIndex]->getSize();
        }
        else
        {
            curlen = pumpData.attribPtr[Geometry::PositionsIndex]->getSize();
        }
    }
    else
    {
        nprims = types->getSize();
        lengths->getValue(curlen, 0);
    }

    UInt32 vertindex = 0;

    if(pumpData.attribIndex[0] != NULL)
    {
        // Indexed, i.e. Single Indexed

        GeoIntegralProperty *index       = pumpData.attribIndex[0];
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
            OSGGETGLFUNCBYID_EXT( glLockArrays,
                                   osgGlLockArraysEXT,
                                  _funcglLockArraysEXT,
                                   win);

            osgGlLockArraysEXT(0, indexSize);
        }

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

        if(index->isInVBO(pEnv)                       == false &&
           win->hasExtension(_extCompiledVertexArray) == true    )
        {
            OSGGETGLFUNCBYID_EXT( glUnlockArrays,
                                  osgGlUnlockArraysEXT,
                                 _funcglUnlockArraysEXT,
                                  win);

            osgGlUnlockArraysEXT();
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
        if(pumpData.attribPtr[i] != NULL)
        {
            pumpData.attribPtr[i]->deactivate(pEnv, i);
        }
    }
}
#endif

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
    PumpData       pumpData;

    pumpData.lengths = lengths;
    pumpData.types   = types;
    pumpData.prop    = prop;
    pumpData.propIdx = propIdx;

    UInt16 nattrib = prop->size();

    for(UInt16 i = 0; i < nattrib; ++i)
    {
        if(pumpGLSetup(pumpData, i) == false)
            continue;

        UInt16 formatIdx = pumpData.attribPtr[i]->getFormat   () - formatBase;
        UInt16 dimIdx    = pumpData.attribPtr[i]->getDimension() - 1;

#if !defined(OSG_USE_OGLES_PROTOS) && !defined(OSG_USE_OGL3_PROTOS) && \
    !defined(OSG_USE_OGL4_PROTOS)
        UInt32 funcId    = Window::invalidFunctionID;

        if(pumpData.attribPtr[i]->getNormalize() == true)
        {
            funcId = normAttribPumpFuncIDs[formatIdx][dimIdx];

            if(funcId == Window::invalidFunctionID)
            {
                SWARNING << "GeoVertexArrayPumpGroup::masterAttribGeoPump: "
                         << "Invalid pump function for property " << i
                         << " type " << pumpData.attribPtr[i]->getDimension()
                         << "D " << formatNames[formatIdx] << " (normalizing)."
                         << endLog;

                pumpData.attribData[i] = NULL;
                pumpData.attribPtr [i] = NULL;
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
                         << " type " << pumpData.attribPtr[i]->getDimension()
                         << "D " << formatNames[formatIdx]
                         << endLog;

                pumpData.attribData[i] = NULL;
                pumpData.attribPtr [i] = NULL;
                continue;
            }
        }

        attribFunc[i] = reinterpret_cast<attribPumpFunc>(
            win->getFunction(funcId));

#else
        if(pumpData.attribPtr[i]->getNormalize() == true)
        {
            attribFunc[i] = attribNormPumpFuncs[formatIdx][dimIdx];
        }
        else
        {
            attribFunc[i] = attribPumpFuncs[formatIdx][dimIdx];
        }
#endif

        if(attribFunc[i] == NULL)
        {
            SWARNING << "GeoVertexArrayPumpGroup::masterAttribGeoPump: "
                     << "Extension function for property " << i
                     << " type " << pumpData.attribPtr[i]->getDimension()
                     << "D " << formatNames[formatIdx]
                     << " not supported by Window " << win
                     << endLog;

            pumpData.attribData[i] = NULL;
            pumpData.attribPtr [i] = NULL;
            continue;
        }
    }

    // we need positions
    if(pumpData.attribPtr[0] == NULL)
    {
        if(pumpData.attribPtr[0]              == NULL ||
           pumpData.attribPtr[0]->getUseVBO() == false)
        {
            SWARNING << "GeoVertexArrayPumpGroup::masterAttribGeoPump: "
                     << "No positions." << endLog;
            return;
        }
    }

    // global attribs?
    for(Int16 i = 0; i < nattrib; ++i)
    {
        if(pumpData.attribData[i]            != NULL &&
           pumpData.attribPtr [i]->getSize() == 1      )
        {
            attribFunc[i](i, pumpData.attribData[i]);
            pumpData.attribData[i] = NULL;
        }
    }

    // activate vertex arrays
    // !!! This should be using the global state to reduce state changes
    // and to allow sharing data between objects

    for(Int16 i = nattrib - 1; i >= 0; --i)
    {
        if(pumpData.attribPtr[i] != NULL)
        {
            pumpData.attribPtr[i]->activate(pEnv, i + 16); // XXX HACK
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
        if(pumpData.attribIndex[0] != NULL)
        {
            curlen = pumpData.attribIndex[0]->getSize();
        }
        else
        {
            curlen = pumpData.attribPtr[0]->getSize();
        }
    }
    else
    {
        nprims = types->getSize();
        lengths->getValue(curlen, 0);
    }

    UInt32 vertindex = 0;

    if(pumpData.attribIndex[0] != NULL)
    {
        // Single Indexed

        GeoIntegralProperty *index       = pumpData.attribIndex[0];
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
            OSGGETGLFUNCBYID_EXT( glLockArrays,
                                  osgGlLockArraysEXT,
                                 _funcglLockArraysEXT,
                                  win);

            osgGlLockArraysEXT(0, indexSize);
        }

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

        if(index->isInVBO(pEnv)                       == false &&
           win->hasExtension(_extCompiledVertexArray) == true    )
        {
            OSGGETGLFUNCBYID_EXT( glUnlockArrays,
                                  osgGlUnlockArraysEXT,
                                 _funcglUnlockArraysEXT,
                                  win);

            osgGlUnlockArraysEXT();
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
        if(pumpData.attribData[i] != NULL)
        {
            pumpData.attribPtr[i]->deactivate(pEnv, i + 16);
        }
    }
}

OSG_END_NAMESPACE

