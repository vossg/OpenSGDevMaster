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

#include "OSGGeoSplitVertexArrayPumpGroup.h"

#include "OSGGLFuncProtos.h"

OSG_BEGIN_NAMESPACE

#define OSG_COMPILE_SPLIT_PUMP 1

// Intentionally INSIDE the namespace
#include "OSGGeoPumpCommon.inl"

//#define DEBUG_WHICH_PUMP 1

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/*! An InitFuncWrapper to initialize the GeoVertexArrayPumpGroup.
*/

InitFuncWrapper GeoSplitVertexArrayPumpGroup::_glextInitFuncWrapper(
    GeoSplitVertexArrayPumpGroup::glextInitFunction);

/*! OpenGL extension indices.
*/

UInt32 GeoSplitVertexArrayPumpGroup::_arbVertexProgram;
#if !defined(OSG_OGL_COREONLY) || defined(OSG_CHECK_COREONLY)
UInt32 GeoSplitVertexArrayPumpGroup::_extSecondaryColor;
UInt32 GeoSplitVertexArrayPumpGroup::_extMultitexture;
#endif

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*------------- constructors & destructors --------------------------------*/

GeoSplitVertexArrayPumpGroup::GeoSplitVertexArrayPumpGroup(void)
{
}

GeoSplitVertexArrayPumpGroup::~GeoSplitVertexArrayPumpGroup(void)
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
        if(info.attribData[slot]         != NULL &&
           info.attribPtr [slot]->size() == 1      )
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
            info.attribPtr [slot] = NULL;
        }
    }
#endif

#if !defined(OSG_OGL_COREONLY) || defined(OSG_CHECK_COREONLY)
    // handle vertex attrib with global value - using GL extension
    void globalExtAttrib(PumpData &info,     UInt16  slot,
                         UInt16    pumpSlot, Window *win)
    {
        if(info.attribData[slot]         != NULL &&
           info.attribPtr [slot]->size() == 1      )
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
            info.attribPtr [slot] = NULL;
        }
    }
#endif

#if !defined(OSG_OGL_COREONLY) || defined(OSG_CHECK_COREONLY)
    // handle vertex attrib with global value - using GL extension, multi
    void globalExtMultiAttrib(PumpData &info,     UInt16  slot,
                              UInt16    pumpSlot, GLenum  attrib,
                              Window   *win                      )
    {
        if(info.attribData[slot]         != NULL &&
           info.attribPtr [slot]->size() == 1      )
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
            info.attribPtr [slot] = NULL;
        }
    }
#endif

} // namespace

#endif      // remove from all but dev docs



GeoPumpGroup::SplitGeoPump GeoSplitVertexArrayPumpGroup::getSplitGeoPump(
    DrawEnv                 *pEnv,
    PropertyCharacteristics  acset)
{
    SplitGeoPump pump = { NULL, NULL, NULL };

    // Remove the stuff we can handle
    PropertyCharacteristics prop;
    prop = acset & GeoPumpGroup::IndexMask;

    if(prop == SingleIndexed || prop == NonIndexed)
    {
        Window *win = pEnv->getWindow();

        if(win->hasExtOrVersion(_arbVertexProgram, 
                                 0x0200, 
                                 0x0200           ) && (acset & UsesShader))
        {
            pump.setupPump    = masterAttribGeoSetupPumpFull;
            pump.drawPump     = masterAttribGeoJustDrawPump;
            pump.shutdownPump = masterAttribGeoShutdownPump;
        }
#if !defined(OSG_OGL_COREONLY) || defined(OSG_CHECK_COREONLY)
        else
        {
            pump.setupPump    = masterClassicGeoSetupPumpFull;
            pump.drawPump     = masterClassicGeoJustDrawPump;
            pump.shutdownPump = masterClassicGeoShutdownPump;
        }
#endif
    }

    return pump;
}

GeoPumpGroup::GeoPump GeoSplitVertexArrayPumpGroup::getGeoPump(
    DrawEnv                 *pEnv,
    PropertyCharacteristics  acset)
{
    return NULL;
};

bool GeoSplitVertexArrayPumpGroup::glextInitFunction(void)
{
#if !defined(OSG_OGL_COREONLY) || defined(OSG_CHECK_COREONLY)
    _extSecondaryColor      =
        Window::registerExtension("GL_EXT_secondary_color");
    _extMultitexture        =
        Window::registerExtension("GL_ARB_multitexture");
#endif

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

    _arbVertexProgram       =
        Window::registerExtension("GL_ARB_vertex_program");

    for(UInt16 i = 0; i < uiNumAttribFuncs; ++i)
        attribInitFuncs[i].init(attribPumpFuncIDs, _arbVertexProgram);

    for(UInt16 i = 0; i < uiNumNormAttribFuncs; ++i)
        normAttribInitFuncs[i].init(normAttribPumpFuncIDs, _arbVertexProgram);

    return true;
}



#if !defined(OSG_OGL_COREONLY) || defined(OSG_CHECK_COREONLY)
bool GeoSplitVertexArrayPumpGroup::masterClassicGeoSetupPump(
          DrawEnv                     *pEnv,
    const GeoIntegralProperty         *lengths,
    const GeoIntegralProperty         *types,
    const Geometry::MFPropertiesType  *prop,
    const Geometry::MFPropIndicesType *propIdx,
          bool                         withFallback)
{
#ifdef DEBUG_WHICH_PUMP
    static bool bPrinted = false;

    if(bPrinted == false)
    {
        fprintf(stderr, 
                "GeoSplitVertexArrayPumpGroup::masterClassicGeoSetupPump\n");
        bPrinted = true;
    }
#endif

    // Setup: get all the data
    PumpData       pumpData;

    pumpData.lengths = lengths;
    pumpData.types   = types;
    pumpData.prop    = prop;
    pumpData.propIdx = propIdx;

    UInt16 nattrib = prop->size32();

    for(UInt16 i = 0; i < nattrib; ++i)
    {
        if(pumpGLSetup(pumpData, i) == false)
            continue;
    }

    // we need positions
    if(pumpData.attribPtr[0]              == NULL ||
       pumpData.attribPtr[0]->getUseVBO() == false)
    {
#ifdef DEBUG_WHICH_PUMP
        static bool bPrinted1 = false;

        if(bPrinted1 == false)
        {
#endif
        if(withFallback == false)
        {
            SWARNING << "GeoSplitVertexArrayPumpGroup::masterAttribGeoPump: "
                     << "No positions, or positions not in vbo." << endLog;
        }
#ifdef DEBUG_WHICH_PUMP
            bPrinted1 = true;
        }
#endif

        return false;
    }

    for(Int16 i = nattrib - 1; i >= 0; --i)
    {
        if(pumpData.attribPtr[i] != NULL &&
           pumpData.attribPtr[i]->size() != 1    )
        {
            pumpData.attribPtr[i]->activate(pEnv, i); 
        }
    }

    return true;
}


void GeoSplitVertexArrayPumpGroup::masterClassicGeoDrawPump(
    DrawEnv                     *pEnv,
    const GeoIntegralProperty         *lengths,
    const GeoIntegralProperty         *types,
    const Geometry::MFPropertiesType  *prop,
    const Geometry::MFPropIndicesType *propIdx)
{
#ifdef DEBUG_WHICH_PUMP
    static bool bPrinted = false;

    if(bPrinted == false)
    {
        fprintf(stderr, 
                "GeoSplitVertexArrayPumpGroup::masterClassicGeoDrawPump\n");
        bPrinted = true;
    }
#endif

    Window *win = pEnv->getWindow();

    // check for empty geometry
    if(types == NULL || types->size() == 0)
        return;

    if(!pumpInternalSetup(types,   true))
        return;
    if(!pumpInternalSetup(lengths, false))
        return;

    PumpData       pumpData;

    pumpData.lengths = lengths;
    pumpData.types   = types;
    pumpData.prop    = prop;
    pumpData.propIdx = propIdx;

    UInt16 nattrib = prop->size32();

    for(UInt16 i = 0; i < nattrib; ++i)
    {
        if(pumpGLSetup(pumpData, i) == false)
            continue;
    }

    // Length handling. Special case: no length given

    UInt32 curlen;
    UInt32 nprims;

    // no lengths? use all available data for the first type
    if(lengths == NULL)
    {
        if(types->size() != 1)
        {
            SWARNING << "GeoVertexArrayPumpGroup::masterAttribGeoPump: "
                     << "No lengths, but more than one type?!"
                     << endLog;
            return;
        }

        nprims = 1;

        if(propIdx->size() != 0 && (*propIdx)[0] != NULL)
        {
            curlen = (*propIdx)[0]->size32();
        }
        else
        {
            curlen = (*prop)[0]->size32();
        }
    }
    else
    {
        nprims = types->size32();
        lengths->getValue(curlen, 0);
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

    UInt32 vertindex = 0;

    if(propIdx->size() != 0 && (*propIdx)[0] != NULL)
    {
        // Single Indexed

        GeoIntegralProperty *index       = (*propIdx)[0];
        const UInt8         *indexData   = index->getData();
        GLenum               indexFormat = index->getFormat();
        UInt32               indexStride =
            index->getStride() ? index->getStride() : index->getFormatSize() *
            index->getDimension();

        index->activate(pEnv, 0);

        if(index->isInVBO(pEnv))
        {
            indexData = NULL;
        }

        for(UInt32 primindex = 0; primindex < nprims; ++primindex)
        {
            if(primindex < lengths->size())
                curlen = lengths->getValue<UInt32>(primindex);

            if(curlen > 0)
            {
                glDrawElements(types->getValue<UInt16>(primindex),
                               curlen,
                               indexFormat,
                               indexData + vertindex * indexStride);

                vertindex += curlen;
            }
        }

        index->deactivate(pEnv, 0);
    }
    else
    {
        // Non-indexed
        for(UInt32 primindex = 0; primindex < nprims; ++primindex)
        {
            if(primindex < lengths->size())
                curlen = lengths->getValue<UInt32>(primindex);

            if(curlen > 0)
            {
                glDrawArrays(types->getValue<UInt16>(primindex), vertindex,
                             curlen);
                vertindex += curlen;
            }
        }
    }
}


bool GeoSplitVertexArrayPumpGroup::masterClassicGeoSetupPumpFull(
          DrawEnv                     *pEnv,
    const GeoIntegralProperty         *lengths,
    const GeoIntegralProperty         *types,
    const Geometry::MFPropertiesType  *prop,
    const Geometry::MFPropIndicesType *propIdx,
          bool                         withFallback)
{
#ifdef DEBUG_WHICH_PUMP
    static bool bPrinted = false;

    if(bPrinted == false)
    {
        fprintf(stderr, 
                "GeoSplitVertexArrayPumpGroup::masterClassicGeoSetupPumpFull\n");
        bPrinted = true;
    }
#endif

    // Setup: get all the data
    PumpData       pumpData;

    pumpData.lengths = lengths;
    pumpData.types   = types;
    pumpData.prop    = prop;
    pumpData.propIdx = propIdx;

    UInt16 nattrib = prop->size32();

    for(UInt16 i = 0; i < nattrib; ++i)
    {
        if(pumpGLSetup(pumpData, i) == false)
            continue;
    }

    // we need positions
    if(pumpData.attribPtr[0]              == NULL ||
       pumpData.attribPtr[0]->getUseVBO() == false)
    {
#ifdef DEBUG_WHICH_PUMP
        static bool bPrinted1 = false;

        if(bPrinted1 == false)
        {
#endif
        if(withFallback == false)
        {
            SWARNING << "GeoSplitVertexArrayPumpGroup::masterAttribGeoPump: "
                     << "No positions." << endLog;
        }
#ifdef DEBUG_WHICH_PUMP
            bPrinted1 = true;
        }
#endif
        return false;
    }

    for(Int16 i = nattrib - 1; i >= 0; --i)
    {
        if(pumpData.attribPtr[i] != NULL &&
           pumpData.attribPtr[i]->size() != 1    )
        {
            pumpData.attribPtr[i]->activate(pEnv, i); 
        }
    }

    if(propIdx->size() != 0 && (*propIdx)[0] != NULL)
    {
        (*propIdx)[0]->activate(pEnv, 0);
    }

    return true;
}

void GeoSplitVertexArrayPumpGroup::masterClassicGeoJustDrawPump(
          DrawEnv                     *pEnv,
    const GeoIntegralProperty         *lengths,
    const GeoIntegralProperty         *types,
    const Geometry::MFPropertiesType  *prop,
    const Geometry::MFPropIndicesType *propIdx,
          UInt32                       uiNumInstances)
{
#ifdef DEBUG_WHICH_PUMP
    static bool bPrinted = false;

    if(bPrinted == false)
    {
        fprintf(stderr, 
                "GeoSplitVertexArrayPumpGroup::masterClassicGeoJustDrawPump\n");
        bPrinted = true;
    }
#endif

    Window *win = pEnv->getWindow();

    // check for empty geometry
    if(types == NULL || types->size() == 0)
        return;

    if(!pumpInternalSetup(types,   true))
        return;
    if(!pumpInternalSetup(lengths, false))
        return;

    PumpData       pumpData;

    pumpData.lengths = lengths;
    pumpData.types   = types;
    pumpData.prop    = prop;
    pumpData.propIdx = propIdx;

    UInt16 nattrib = prop->size32();

    for(UInt16 i = 0; i < nattrib; ++i)
    {
        if(pumpGLSetup(pumpData, i) == false)
            continue;
    }

    // Length handling. Special case: no length given

    UInt32 curlen;
    UInt32 nprims;

    // no lengths? use all available data for the first type
    if(lengths == NULL)
    {
        if(types->size() != 1)
        {
            SWARNING << "GeoVertexArrayPumpGroup::masterAttribGeoPump: "
                     << "No lengths, but more than one type?!"
                     << endLog;
            return;
        }

        nprims = 1;

        if(propIdx->size() != 0 && (*propIdx)[0] != NULL)
        {
            curlen = (*propIdx)[0]->size32();
        }
        else
        {
            curlen = (*prop)[0]->size32();
        }
    }
    else
    {
        nprims = types->size32();
        lengths->getValue(curlen, 0);
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

    UInt32 vertindex = 0;

    if(propIdx->size() != 0 && (*propIdx)[0] != NULL)
    {
        // Single Indexed

        GeoIntegralProperty *index       = (*propIdx)[0];
        const UInt8         *indexData   = index->getData();
        GLenum               indexFormat = index->getFormat();
        UInt32               indexStride =
            index->getStride() ? index->getStride() : index->getFormatSize() *
            index->getDimension();

#if 0
        index->activate(pEnv, 0);

        if(index->isInVBO(pEnv))
        {
#endif
            indexData = NULL;
#if 0
        }
#endif

        if(uiNumInstances > 1)
        {        
            OSGGETGLFUNCBYID_GL3_ES(glDrawElementsInstanced,
                                    osgGlDrawElementsInstanced,
                                    Geometry::getFuncIdDrawElementsInstanced(),
                                    win);

            for(UInt32 primindex = 0; primindex < nprims; ++primindex)
            {
                if(primindex < lengths->size())
                    curlen = lengths->getValue<UInt32>(primindex);

                if(curlen > 0)
                {
                    osgGlDrawElementsInstanced(
                        types->getValue<UInt16>(primindex),
                        curlen,
                        indexFormat,
                        indexData + vertindex * indexStride,
                        uiNumInstances                     );

                    vertindex += curlen;
                }
            }
        }
        else
        {
            for(UInt32 primindex = 0; primindex < nprims; ++primindex)
            {
                if(primindex < lengths->size())
                    curlen = lengths->getValue<UInt32>(primindex);

                if(curlen > 0)
                {
                    glDrawElements(types->getValue<UInt16>(primindex),
                                   curlen,
                                   indexFormat,
                                   indexData + vertindex * indexStride);

                    vertindex += curlen;
                }
            }
        }

#if 0
        index->deactivate(pEnv, 0);
#endif
    }
    else
    {
        if(uiNumInstances > 1)
        {
            OSGGETGLFUNCBYID_GL3_ES(glDrawArraysInstanced,
                                    osgGlDrawArraysInstanced,
                                    Geometry::getFuncIdDrawArraysInstanced(),
                                    win);
            // Non-indexed
            for(UInt32 primindex = 0; primindex < nprims; ++primindex)
            {
                if(primindex < lengths->size())
                    curlen = lengths->getValue<UInt32>(primindex);

                if(curlen > 0)
                {
                    osgGlDrawArraysInstanced(
                        types->getValue<UInt16>(primindex), 
                        vertindex,
                        curlen,
                        uiNumInstances);

                    vertindex += curlen;
                }
            }
        }
        else
        {
            // Non-indexed
            for(UInt32 primindex = 0; primindex < nprims; ++primindex)
            {
                if(primindex < lengths->size())
                    curlen = lengths->getValue<UInt32>(primindex);

                if(curlen > 0)
                {
                    glDrawArrays(types->getValue<UInt16>(primindex), vertindex,
                                 curlen);
                    vertindex += curlen;
                }
            }
        }
    }
}

bool GeoSplitVertexArrayPumpGroup::masterClassicGeoShutdownPump(
    DrawEnv                     *pEnv,
    const GeoIntegralProperty         *lengths,
    const GeoIntegralProperty         *types,
    const Geometry::MFPropertiesType  *prop,
    const Geometry::MFPropIndicesType *propIdx)
{
#ifdef DEBUG_WHICH_PUMP
    static bool bPrinted = false;

    if(bPrinted == false)
    {
        fprintf(stderr, 
                "GeoSplitVertexArrayPumpGroup::masterClassicGeoShutdownPump\n");
        bPrinted = true;
    }
#endif

    // Setup: get all the data
    PumpData       pumpData;

    pumpData.lengths = lengths;
    pumpData.types   = types;
    pumpData.prop    = prop;
    pumpData.propIdx = propIdx;

    UInt16 nattrib = prop->size32();

    for(UInt16 i = 0; i < nattrib; ++i)
    {
        if(pumpGLSetup(pumpData, i) == false)
            continue;
    }

    // we need positions
    if(pumpData.attribPtr[0]              == NULL ||
       pumpData.attribPtr[0]->getUseVBO() == false)
    {
#ifdef DEBUG_WHICH_PUMP
        static bool bPrinted1 = false;

        if(bPrinted1 == false)
        {
#endif
        SWARNING << "GeoSplitVertexArrayPumpGroup::masterAttribGeoPump: "
                 << "No positions." << endLog;

        return false;
#ifdef DEBUG_WHICH_PUMP
            bPrinted1 = true;
        }
#endif
    }

    for(Int16 i = nattrib - 1; i >= 0; --i)
    {
        if(pumpData.attribPtr[i] != NULL &&
           pumpData.attribPtr[i]->size() != 1    )
        {
            pumpData.attribPtr[i]->deactivate(pEnv, i); 
        }
    }

    if(propIdx->size() != 0 && (*propIdx)[0] != NULL)
    {
        (*propIdx)[0]->deactivate(pEnv, 0);
    }

    return true;
}

#endif


bool GeoSplitVertexArrayPumpGroup::masterAttribGeoSetupPump(
          DrawEnv                     *pEnv,
    const GeoIntegralProperty         *lengths,
    const GeoIntegralProperty         *types,
    const Geometry::MFPropertiesType  *prop,
    const Geometry::MFPropIndicesType *propIdx,
          bool                         withFallback)
{
#ifdef DEBUG_WHICH_PUMP
    static bool bPrinted = false;

    if(bPrinted == false)
    {
        fprintf(stderr, 
                "GeoSplitVertexArrayPumpGroup::masterAttribGeoSetupPump\n");
        bPrinted = true;
    }
#endif

    // Setup: get all the data
    PumpData       pumpData;

    pumpData.lengths = lengths;
    pumpData.types   = types;
    pumpData.prop    = prop;
    pumpData.propIdx = propIdx;

    UInt16 nattrib = prop->size32();

    for(UInt16 i = 0; i < nattrib; ++i)
    {
        if(pumpGLSetup(pumpData, i) == false)
            continue;
    }

    // we need positions
    if(pumpData.attribPtr[0]              == NULL ||
       pumpData.attribPtr[0]->getUseVBO() == false)
    {
#ifdef DEBUG_WHICH_PUMP
        static bool bPrinted1 = false;

        if(bPrinted1 == false)
        {
#endif
        if(withFallback == false)
        {
            SWARNING << "GeoSplitVertexArrayPumpGroup::masterAttribGeoPump: "
                     << "No positions." << endLog;
        }
#ifdef DEBUG_WHICH_PUMP
            bPrinted1 = true;
        }
#endif
        return false;
    }

    for(Int16 i = nattrib - 1; i >= 0; --i)
    {
        if(pumpData.attribPtr[i]         != NULL &&
           pumpData.attribPtr[i]->size() != 1     )
        {
            pumpData.attribPtr[i]->activate(pEnv, i + 16); // XXX HACK
        }
    }

    return true;
}


void GeoSplitVertexArrayPumpGroup::masterAttribGeoDrawPump(
    DrawEnv                     *pEnv,
    const GeoIntegralProperty         *lengths,
    const GeoIntegralProperty         *types,
    const Geometry::MFPropertiesType  *prop,
    const Geometry::MFPropIndicesType *propIdx)
{
#ifdef DEBUG_WHICH_PUMP
    static bool bPrinted = false;

    if(bPrinted == false)
    {
        fprintf(stderr, 
                "GeoSplitVertexArrayPumpGroup::masterAttribGeoDrawPump\n");
        bPrinted = true;
    }
#endif

    Window *win = pEnv->getWindow();

    // check for empty geometry
    if(types == NULL || types->size() == 0)
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

    UInt16 nattrib = prop->size32();

    for(UInt16 i = 0; i < nattrib; ++i)
    {
        if(pumpGLSetup(pumpData, i) == false)
            continue;

        UInt16 formatIdx = pumpData.attribPtr[i]->getFormat   () - formatBase;
        UInt16 dimIdx    = pumpData.attribPtr[i]->getDimension() - 1;

#if !defined(OSG_USE_OGLES_PROTOS) && !defined(OSG_USE_OGL3_PROTOS) &&  \
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

    // Length handling. Special case: no length given

    UInt32 curlen;
    UInt32 nprims;

    // no lengths? use all available data for the first type
    if(lengths == NULL)
    {
        if(types->size() != 1)
        {
            SWARNING << "GeoVertexArrayPumpGroup::masterAttribGeoPump: "
                     << "No lengths, but more than one type?!"
                     << endLog;
            return;
        }

        nprims = 1;

        if(propIdx->size() != 0 && (*propIdx)[0] != NULL)
        {
            curlen = (*propIdx)[0]->size32();
        }
        else
        {
            curlen = (*prop)[0]->size32();
        }
    }
    else
    {
        nprims = types->size32();
        lengths->getValue(curlen, 0);
    }

    // global attribs?
    for(Int16 i = 0; i < nattrib; ++i)
    {
        if(pumpData.attribData[i]         != NULL &&
           pumpData.attribPtr [i]->size() == 1      )
        {
            attribFunc[i](i, pumpData.attribData[i]);
            pumpData.attribData[i] = NULL;
        }
    }

    UInt32 vertindex = 0;

    if(propIdx->size() != 0 && (*propIdx)[0] != NULL)
    {
        // Single Indexed

        GeoIntegralProperty *index       = (*propIdx)[0];
        const UInt8         *indexData   = index->getData();
        GLenum               indexFormat = index->getFormat();
        UInt32               indexStride =
            index->getStride() ? index->getStride() : index->getFormatSize() *
            index->getDimension();

        index->activate(pEnv, 0);

        if(index->isInVBO(pEnv))
        {
            indexData = NULL;
        }

        for(UInt32 primindex = 0; primindex < nprims; ++primindex)
        {
            if(primindex < lengths->size())
                curlen = lengths->getValue<UInt32>(primindex);

            if(curlen > 0)
            {
                glDrawElements(types->getValue<UInt16>(primindex),
                               curlen,
                               indexFormat,
                               indexData + vertindex * indexStride);

                vertindex += curlen;
            }
        }

        index->deactivate(pEnv, 0);
    }
    else
    {
        // Non-indexed
        for(UInt32 primindex = 0; primindex < nprims; ++primindex)
        {
            if(primindex < lengths->size())
                curlen = lengths->getValue<UInt32>(primindex);

            if(curlen > 0)
            {
                glDrawArrays(types->getValue<UInt16>(primindex), vertindex,
                             curlen);
                vertindex += curlen;
            }
        }
    }
}

bool GeoSplitVertexArrayPumpGroup::masterAttribGeoSetupPumpFull(
          DrawEnv                     *pEnv,
    const GeoIntegralProperty         *lengths,
    const GeoIntegralProperty         *types,
    const Geometry::MFPropertiesType  *prop,
    const Geometry::MFPropIndicesType *propIdx,
          bool                         withFallback)
{
#ifdef DEBUG_WHICH_PUMP
    static bool bPrinted = false;

    if(bPrinted == false)
    {
        fprintf(stderr, 
                "GeoSplitVertexArrayPumpGroup::masterAttribGeoSetupPumpFull\n");
        bPrinted = true;
    }
#endif

    // Setup: get all the data
    PumpData       pumpData;

    pumpData.lengths = lengths;
    pumpData.types   = types;
    pumpData.prop    = prop;
    pumpData.propIdx = propIdx;

    UInt16 nattrib = prop->size32();

    for(UInt16 i = 0; i < nattrib; ++i)
    {
        if(pumpGLSetup(pumpData, i) == false)
            continue;
    }

    // we need positions
    if(pumpData.attribPtr[0]              == NULL ||
       pumpData.attribPtr[0]->getUseVBO() == false)
    {
#ifdef DEBUG_WHICH_PUMP
        static bool bPrinted1 = false;

        if(bPrinted1 == false)
        {
#endif
        if(withFallback == false)
        {
            SWARNING << "GeoSplitVertexArrayPumpGroup::masterAttribGeoPump: "
                     << "No positions, or positions not in vbo." << endLog;
        }
#ifdef DEBUG_WHICH_PUMP
            bPrinted1 = true;
        }
#endif
        return false;
    }

    for(Int16 i = nattrib - 1; i >= 0; --i)
    {
        if(pumpData.attribPtr[i]         != NULL &&
           pumpData.attribPtr[i]->size() != 1     )
        {
            pumpData.attribPtr[i]->activate(pEnv, i + 16); // XXX HACK
        }
    }

    if(propIdx->size() != 0 && (*propIdx)[0] != NULL)
    {
        (*propIdx)[0]->activate(pEnv, 0);
    }

    return true;
}

void GeoSplitVertexArrayPumpGroup::masterAttribGeoJustDrawPump(
    DrawEnv                     *pEnv,
    const GeoIntegralProperty         *lengths,
    const GeoIntegralProperty         *types,
    const Geometry::MFPropertiesType  *prop,
    const Geometry::MFPropIndicesType *propIdx,
          UInt32                       uiNumInstances)
{
#ifdef DEBUG_WHICH_PUMP
    static bool bPrinted = false;

    if(bPrinted == false)
    {
        fprintf(stderr, 
                "GeoSplitVertexArrayPumpGroup::masterAttribGeoJustDrawPump\n");
        bPrinted = true;
    }
#endif

    Window *win = pEnv->getWindow();

    // check for empty geometry
    if(types == NULL || types->size() == 0)
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

    UInt16 nattrib = prop->size32();

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

    // Length handling. Special case: no length given

    UInt32 curlen;
    UInt32 nprims;

    // no lengths? use all available data for the first type
    if(lengths == NULL)
    {
        if(types->size() != 1)
        {
            SWARNING << "GeoVertexArrayPumpGroup::masterAttribGeoPump: "
                     << "No lengths, but more than one type?!"
                     << endLog;
            return;
        }

        nprims = 1;

        if(propIdx->size() != 0 && (*propIdx)[0] != NULL)
        {
            curlen = (*propIdx)[0]->size32();
        }
        else
        {
            curlen = (*prop)[0]->size32();
        }
    }
    else
    {
        nprims = types->size32();
        lengths->getValue(curlen, 0);
    }

    // global attribs?
    for(Int16 i = 0; i < nattrib; ++i)
    {
        if(pumpData.attribData[i]         != NULL &&
           pumpData.attribPtr [i]->size() == 1      )
        {
            attribFunc[i](i, pumpData.attribData[i]);
            pumpData.attribData[i] = NULL;
        }
    }

    UInt32 vertindex = 0;

    if(propIdx->size() != 0 && (*propIdx)[0] != NULL)
    {
        // Single Indexed

        GeoIntegralProperty *index       = (*propIdx)[0];
        const UInt8         *indexData   = index->getData();
        GLenum               indexFormat = index->getFormat();
        UInt32               indexStride =
            index->getStride() ? index->getStride() : index->getFormatSize() *
                                                      index->getDimension();

#if 0
        index->activate(pEnv, 0);

        if(index->isInVBO(pEnv))
        {
#endif
            indexData = NULL;
#if 0
        }
#endif

        if(uiNumInstances > 1)
        {
            OSGGETGLFUNCBYID_GL3_ES(glDrawElementsInstanced,
                                    osgGlDrawElementsInstanced,
                                    Geometry::getFuncIdDrawElementsInstanced(),
                                    win);

            for(UInt32 primindex = 0; primindex < nprims; ++primindex)
            {
                if(primindex < lengths->size())
                    curlen = lengths->getValue<UInt32>(primindex);

                if(curlen > 0)
                {
                    osgGlDrawElementsInstanced(
                        types->getValue<UInt16>(primindex),
                        curlen,
                        indexFormat,
                        indexData + vertindex * indexStride,
                        uiNumInstances                     );

                    vertindex += curlen;
                }
            }
        }
        else
        {
            for(UInt32 primindex = 0; primindex < nprims; ++primindex)
            {
                if(primindex < lengths->size())
                    curlen = lengths->getValue<UInt32>(primindex);

                if(curlen > 0)
                {
                    glDrawElements(types->getValue<UInt16>(primindex),
                               curlen,
                               indexFormat,
                               indexData + vertindex * indexStride);

                    vertindex += curlen;
                }
            }
        }

#if 0
        index->deactivate(pEnv, 0);
#endif
    }
    else
    {
        if(uiNumInstances > 1)
        {
            OSGGETGLFUNCBYID_GL3_ES(glDrawArraysInstanced,
                                    osgGlDrawArraysInstanced,
                                    Geometry::getFuncIdDrawArraysInstanced(),
                                    win);

            // Non-indexed
            for(UInt32 primindex = 0; primindex < nprims; ++primindex)
            {
                if(primindex < lengths->size())
                    curlen = lengths->getValue<UInt32>(primindex);

                if(curlen > 0)
                {
                    osgGlDrawArraysInstanced(
                        types->getValue<UInt16>(primindex), 
                        vertindex,
                        curlen,
                        uiNumInstances                    );

                    vertindex += curlen;
                }
            }
        }
        else
        {
            // Non-indexed
            for(UInt32 primindex = 0; primindex < nprims; ++primindex)
            {
                if(primindex < lengths->size())
                    curlen = lengths->getValue<UInt32>(primindex);

                if(curlen > 0)
                {
                    glDrawArrays(types->getValue<UInt16>(primindex), vertindex,
                                 curlen);
                    vertindex += curlen;
                }
            }
        }
    }
}

bool GeoSplitVertexArrayPumpGroup::masterAttribGeoShutdownPump(
          DrawEnv                     *pEnv,
    const GeoIntegralProperty         *lengths,
    const GeoIntegralProperty         *types,
    const Geometry::MFPropertiesType  *prop,
    const Geometry::MFPropIndicesType *propIdx)
{
#ifdef DEBUG_WHICH_PUMP
    static bool bPrinted = false;

    if(bPrinted == false)
    {
        fprintf(stderr, 
                "GeoSplitVertexArrayPumpGroup::masterAttribGeoShutdownPump\n");
        bPrinted = true;
    }
#endif

    // Setup: get all the data
    PumpData       pumpData;

    pumpData.lengths = lengths;
    pumpData.types   = types;
    pumpData.prop    = prop;
    pumpData.propIdx = propIdx;

    UInt16 nattrib = prop->size32();

    for(UInt16 i = 0; i < nattrib; ++i)
    {
        if(pumpGLSetup(pumpData, i) == false)
            continue;
    }

    // we need positions
    if(pumpData.attribPtr[0]              == NULL ||
       pumpData.attribPtr[0]->getUseVBO() == false)
    {
#ifdef DEBUG_WHICH_PUMP
        static bool bPrinted1 = false;

        if(bPrinted1 == false)
        {
#endif
        SWARNING << "GeoSplitVertexArrayPumpGroup::masterAttribGeoPump: "
                 << "No positions." << endLog;

#ifdef DEBUG_WHICH_PUMP
            bPrinted1 = true;
        }
#endif
        return false;
    }

    for(Int16 i = nattrib - 1; i >= 0; --i)
    {
        if(pumpData.attribPtr[i]         != NULL &&
           pumpData.attribPtr[i]->size() != 1     )
        {
            pumpData.attribPtr[i]->deactivate(pEnv, i + 16); // XXX HACK
        }
    }

    if(propIdx->size() != 0 && (*propIdx)[0] != NULL)
    {
        (*propIdx)[0]->deactivate(pEnv, 0);
    }

    return true;
}

OSG_END_NAMESPACE

