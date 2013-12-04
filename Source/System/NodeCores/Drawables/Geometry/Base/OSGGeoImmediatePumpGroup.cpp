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
#include "OSGConceptPropertyChecks.h"

//#define DEBUG_WHICH_PUMP 1

OSG_BEGIN_NAMESPACE

// Intentionally INSIDE the namespace
#include "OSGGeoPumpCommon.inl"

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

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)

namespace
{
    struct PumpClassicInfo : public PumpData
    {
        explicit PumpClassicInfo(void);

        pumpFunc      attribPump [Geometry::MaxAttribs];
        multiPumpFunc attribMPump[Geometry::MaxAttribs];
    };

    PumpClassicInfo::PumpClassicInfo(void) : 
        PumpData()
    {
        for(Int16 i = 0; i < Geometry::MaxAttribs; ++i)
        {
            attribPump  [i] = NULL;
            attribMPump [i] = NULL;
        }
    }



    // collect info for property in 'slot'
    bool pumpGLSetup(PumpClassicInfo &info, UInt16 slot, UInt32 pumpSlot)
    {
        bool retVal = true;

        if(slot < info.prop->size())
            info.attribPtr  [slot] = (*info.prop   )[slot];

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

            UInt16 formatIdx = info.attribPtr[slot]->getFormat() - formatBase;
            UInt16 dimIdx    = info.attribPtr[slot]->getDimension() - 1;

            info.attribPump[slot] = pumpFuncs[pumpSlot][formatIdx][dimIdx];

            if(info.attribPump[slot] == NULL)
            {
                SWARNING << "GeoImmediatePumpGroup - pumpGLSetup: "
                         << "Invalid pump function for property " << slot
                         << " type " << info.attribPtr[slot]->getDimension()
                         << "D " << formatNames[formatIdx]
                         << endLog;

                info.attribData  [slot] = NULL;
                info.attribStride[slot] = 0;
                info.attribPtr   [slot] = NULL;
                info.attribIndex [slot] = NULL;

                retVal = false;
            }
        }
        else
        {
            info.attribData  [slot] = NULL;
            info.attribStride[slot] = 0;
            info.attribPtr   [slot] = NULL;
            info.attribIndex [slot] = NULL;
        }

        return retVal;
    }

    // collect info for property in 'slot'
    bool pumpGLSetup(PumpAttribInfo &info, UInt16 slot)
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

    // collect info for property in 'slot' - using GL extension
    bool pumpGLExtSetup(PumpClassicInfo &info,     UInt16  slot,
                        UInt32           pumpSlot, Window *win)
    {
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

            UInt16 formatIdx = info.attribPtr[slot]->getFormat() - formatBase;
            UInt16 dimIdx    = info.attribPtr[slot]->getDimension() - 1;

            UInt32 funcId    = pumpFuncIDs[pumpSlot][formatIdx][dimIdx];

            if(funcId == Window::invalidFunctionID)
            {
                SWARNING << "GeoImmediatePumpGroup - pumpGLExtSetup: "
                         << "Invalid extension function for property " << slot
                         << " type " << info.attribPtr[slot]->getDimension()
                         << "D " << formatNames[formatIdx]
                         << endLog;

                info.attribData  [slot] = NULL;
                info.attribStride[slot] = 0;
                info.attribPtr   [slot] = NULL;
                info.attribIndex [slot] = NULL;

                return false;
            }

            info.attribPump[slot] =
                reinterpret_cast<pumpFunc>(win->getFunction(funcId));

            if(info.attribPump[slot] == NULL)
            {
                SWARNING << "GeoImmediatePumpGroup - pumpGLExtSetup: "
                         << "Extension function for property " << slot
                         << " type " << info.attribPtr[slot]->getDimension()
                         << "D " << formatNames[formatIdx]
                         << " not supported by Window " << win
                         << endLog;

                info.attribData  [slot] = NULL;
                info.attribStride[slot] = 0;
                info.attribPtr   [slot] = NULL;
                info.attribIndex [slot] = NULL;

                return false;
            }
        }

        return true;
    }

    // collect info for property in 'slot' - using GL extension, multi
    bool pumpGLExtMultiSetup(PumpClassicInfo &info,     UInt16  slot,
                             UInt32           pumpSlot, Window *win)
    {
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

            UInt16 formatIdx = info.attribPtr[slot]->getFormat() - formatBase;
            UInt32 dimIdx    = info.attribPtr[slot]->getDimension() - 1;

            UInt32 funcId    = pumpFuncIDs[pumpSlot][formatIdx][dimIdx];

            if(funcId == Window::invalidFunctionID)
            {
                SWARNING << "GeoImmediatePumpGroup - pumpGLExtMultiSetup: "
                         << "Invalid extension function for property " << slot
                         << " type " << info.attribPtr[slot]->getDimension()
                         << "D " << formatNames[formatIdx]
                         << endLog;

                info.attribData  [slot] = NULL;
                info.attribStride[slot] = 0;
                info.attribPtr   [slot] = NULL;
                info.attribIndex [slot] = NULL;

                return false;
            }

            info.attribMPump[slot] =
                reinterpret_cast<multiPumpFunc>(win->getFunction(funcId));

            if(info.attribMPump[slot] == NULL)
            {
                SWARNING << "GeoImmediatePumpGroup - pumpGLExtMultiSetup: "
                         << "Extension function for property " << slot
                         << " type " << info.attribPtr[slot]->getDimension()
                         << "D " << formatNames[formatIdx]
                         << " not supported by Window " << win
                         << endLog;

                info.attribData  [slot] = NULL;
                info.attribStride[slot] = 0;
                info.attribPtr   [slot] = NULL;
                info.attribIndex [slot] = NULL;

                return false;
            }
        }

        return true;
    }


    // handle vertex attrib with global value
    void globalAttrib(PumpClassicInfo &info, UInt16 slot, UInt16 pumpSlot)
    {
        if(info.attribData[slot]         != NULL &&
           info.attribPtr [slot]->size() == 1      )
        {
            OSG_ASSERT(info.attribPump[slot] != NULL);

            info.attribPump[slot](info.attribData[slot]);
            info.attribData[slot] = NULL;
        }
    }

    // handle vertex attrib with global value - using GL extension
    void globalExtAttrib(PumpClassicInfo &info,     UInt16  slot,
                         UInt16           pumpSlot, Window *win)
    {
        if(info.attribData[slot]         != NULL &&
           info.attribPtr [slot]->size() == 1      )
        {
            OSG_ASSERT(info.attribPump[slot] != NULL);

            info.attribPump[slot](info.attribData[slot]);
            info.attribData[slot] = NULL;
        }
    }

    // handle vertex attrib with global value - using GL extension, multi
    void globalExtMultiAttrib(PumpClassicInfo &info,     UInt16  slot,
                              UInt16           pumpSlot, GLenum  attrib,
                              Window          *win                      )
    {
        if(info.attribData[slot]         != NULL &&
           info.attribPtr [slot]->size() == 1      )
        {
            OSG_ASSERT(info.attribMPump[slot] != NULL);

            info.attribMPump[slot](attrib, info.attribData[slot]);
            info.attribData [slot] = NULL;
        }
    }

    // pass a single attrib value to OpenGL
    void pumpAttrib(PumpClassicInfo &info, UInt16 slot, UInt32 vertIdx)
    {
        if(info.attribData[slot] != NULL)
        {
            OSG_ASSERT(info.attribPump[slot] != NULL);

            if(info.attribIndex[slot] != NULL)
            {
                info.attribPump[slot](
                    info.attribData  [slot] +
                    info.attribStride[slot] *
                    info.attribIndex [slot]->getValue<UInt32>(vertIdx));
            }
            else
            {
                info.attribPump[slot](
                    info.attribData  [slot] +
                    info.attribStride[slot] * vertIdx);
            }
        }
    }

    // pass a single (multi) attrib value to OpenGL
    void pumpMultiAttrib(PumpClassicInfo &info,   UInt16 slot,
                         GLenum           attrib, UInt32 vertIdx)
    {
        if(info.attribData[slot] != NULL)
        {
            OSG_ASSERT(info.attribMPump[slot] != NULL);

            if(info.attribIndex[slot] != NULL)
            {
                info.attribMPump[slot](
                    attrib,
                    info.attribData  [slot] +
                    info.attribStride[slot] *
                    info.attribIndex [slot]->getValue<UInt32>(vertIdx));
            }
            else
            {
                info.attribMPump[slot](
                    attrib,
                    info.attribData  [slot] +
                    info.attribStride[slot] * vertIdx);
            }
        }
    }

} // namespace

#endif      // remove from all but dev docs

GeoPumpGroup::GeoPump GeoImmediatePumpGroup::getGeoPump(
    DrawEnv                 *pEnv,
    PropertyCharacteristics  acset)
{
    Window *win = pEnv->getWindow();

    if(win->hasExtOrVersion(_arbVertexProgram,
                            0x0200,
                            0x0200           ) && (acset & UsesShader))
    {
        return masterAttribGeoPump;
    }
    else
    {
        return masterClassicGeoPump;
    }
}

bool GeoImmediatePumpGroup::glextInitFunction(void)
{
    _extSecondaryColor      =
        Window::registerExtension("GL_EXT_secondary_color");
    _extMultitexture        =
        Window::registerExtension("GL_ARB_multitexture");
    _arbVertexProgram       =
        Window::registerExtension("GL_ARB_vertex_program");

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

    for(UInt16 i = 0; i < uiNumAttribFuncs; ++i)
        attribInitFuncs[i].init(attribPumpFuncIDs, _arbVertexProgram);

    for(UInt16 i = 0; i < uiNumNormAttribFuncs; ++i)
        normAttribInitFuncs[i].init(normAttribPumpFuncIDs, _arbVertexProgram);
 
#if defined(OSG_USE_OGLES_PROTOS) || defined(OSG_USE_OGL3_PROTOS) || \
    defined(OSG_USE_OGL4_PROTOS)
    osgSinkUnusedWarning(attribPumpFuncs);
    osgSinkUnusedWarning(attribNormPumpFuncs);
#endif

    return true;
}

void GeoImmediatePumpGroup::masterClassicGeoPump(
          DrawEnv                     *pEnv,
    const GeoIntegralProperty         *lengths,
    const GeoIntegralProperty         *types,
    const Geometry::MFPropertiesType  *prop,
    const Geometry::MFPropIndicesType *propIdx,
          UInt32                              )
{
#ifdef DEBUG_WHICH_PUMP
    static bool bPrinted = false;

    if(bPrinted == false)
    {
        fprintf(stderr, "GeoImmediatePumpGroup::masterClassicGeoPump\n");
        bPrinted = true;
    }
#endif

    Window *win = pEnv->getWindow();

    // Setup: get all the data

    // check for empty geometry
    if(types == NULL || types->size() == 0)
        return;

    if(!pumpInternalSetup(types,   true))
        return;
    if(!pumpInternalSetup(lengths, false))
        return;

    PumpClassicInfo pumpInfo;
    pumpInfo.lengths = lengths;
    pumpInfo.types   = types;
    pumpInfo.prop    = prop;
    pumpInfo.propIdx = propIdx;

    // setup standard properties
    pumpGLSetup(pumpInfo, Geometry::PositionsIndex, PositionsPumpSlot);
    pumpGLSetup(pumpInfo, Geometry::ColorsIndex,    ColorsPumpSlot);
    pumpGLSetup(pumpInfo, Geometry::NormalsIndex,   NormalsPumpSlot);
    pumpGLSetup(pumpInfo, Geometry::TexCoordsIndex, TexCoordsPumpSlot);

    // setup extension properties
    if(win->hasExtOrVersion(_extSecondaryColor, 0x0104) == true)
    {
        pumpGLExtSetup(pumpInfo, Geometry::SecondaryColorsIndex,
                       SecColorsPumpSlot, win);
    }

    // setup extension multi properties
    if(win->hasExtOrVersion(_extMultitexture, 0x0103, 0x0200) == true)
    {
        pumpGLExtMultiSetup(pumpInfo, Geometry::TexCoords1Index,
                            TexCoords1PumpSlot, win);
        pumpGLExtMultiSetup(pumpInfo, Geometry::TexCoords2Index,
                            TexCoords2PumpSlot, win);
        pumpGLExtMultiSetup(pumpInfo, Geometry::TexCoords3Index,
                            TexCoords3PumpSlot, win);
        pumpGLExtMultiSetup(pumpInfo, Geometry::TexCoords4Index,
                            TexCoords4PumpSlot, win);
        pumpGLExtMultiSetup(pumpInfo, Geometry::TexCoords5Index,
                            TexCoords5PumpSlot, win);
        pumpGLExtMultiSetup(pumpInfo, Geometry::TexCoords6Index,
                            TexCoords6PumpSlot, win);
        pumpGLExtMultiSetup(pumpInfo, Geometry::TexCoords7Index,
                            TexCoords7PumpSlot, win);
    }

    // we need positions
    if(pumpInfo.attribPtr[Geometry::PositionsIndex] == NULL)
    {
        if(pumpInfo.attribPtr[Geometry::PositionsIndex]              == NULL ||
           pumpInfo.attribPtr[Geometry::PositionsIndex]->getUseVBO() == false)
        {
            SWARNING << "GeoImmediatePumpGroup::masterClassicGeoPump: "
                     << "No positions." << endLog;
            return;
        }
    }

    // global attribs?
    globalAttrib(pumpInfo, Geometry::NormalsIndex,   NormalsPumpSlot);
    globalAttrib(pumpInfo, Geometry::ColorsIndex,    ColorsPumpSlot);
    globalAttrib(pumpInfo, Geometry::TexCoordsIndex, TexCoordsPumpSlot);

    if(win->hasExtOrVersion(_extSecondaryColor, 0x0200) == true)
    {
        globalExtAttrib(pumpInfo,          Geometry::SecondaryColorsIndex,
                        SecColorsPumpSlot, win                            );
    }

    if(win->hasExtOrVersion(_extMultitexture, 0x0103, 0x0200) == true)
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

    // Length handling. Special case: no length given

    UInt32 curlen;
    UInt32 nprims;

    // no lengths? use all available data for the first type
    if(lengths == NULL)
    {
        if(types->size() != 1)
        {
            SWARNING << "GeoImmediatePumpGroup::masterClassicGeoPump: "
                     << "No lengths, but more than one type?!"
                     << endLog;
            return;
        }

        nprims = 1;
        if(pumpInfo.attribIndex[Geometry::PositionsIndex] != NULL)
        {
            curlen = pumpInfo.attribIndex[Geometry::PositionsIndex]->size32();
        }
        else
        {
            curlen = pumpInfo.attribPtr[Geometry::PositionsIndex]->size32();
        }
    }
    else
    {
        nprims = types->size32();
        lengths->getValue(curlen, 0);
    }

    UInt32 vertindex = 0;

    for(UInt32 primindex = 0; primindex < nprims; ++primindex)
    {
        glBegin(types->getValue<UInt16>(primindex));

        if(primindex < lengths->size())
            curlen = lengths->getValue<UInt32>(primindex);

        for(; curlen > 0; --curlen, ++vertindex)
        {
            pumpAttrib(pumpInfo, Geometry::NormalsIndex,   vertindex);
            pumpAttrib(pumpInfo, Geometry::ColorsIndex,    vertindex);
            pumpAttrib(pumpInfo, Geometry::TexCoordsIndex, vertindex);

            if(win->hasExtOrVersion(_extSecondaryColor, 0x0104) == true)
            {
                pumpAttrib(pumpInfo, Geometry::SecondaryColorsIndex, vertindex);
            }

            if(win->hasExtOrVersion(_extMultitexture, 0x0103, 0x0200))
            {
                pumpMultiAttrib(pumpInfo, Geometry::TexCoords1Index,
                                GL_TEXTURE1_ARB, vertindex);
                pumpMultiAttrib(pumpInfo, Geometry::TexCoords2Index,
                                GL_TEXTURE2_ARB, vertindex);
                pumpMultiAttrib(pumpInfo, Geometry::TexCoords3Index,
                                GL_TEXTURE3_ARB, vertindex);
                pumpMultiAttrib(pumpInfo, Geometry::TexCoords4Index,
                                GL_TEXTURE4_ARB, vertindex);
                pumpMultiAttrib(pumpInfo, Geometry::TexCoords5Index,
                                GL_TEXTURE5_ARB, vertindex);
                pumpMultiAttrib(pumpInfo, Geometry::TexCoords6Index,
                                GL_TEXTURE6_ARB, vertindex);
                pumpMultiAttrib(pumpInfo, Geometry::TexCoords7Index,
                                GL_TEXTURE7_ARB, vertindex);
            }

            pumpAttrib(pumpInfo, Geometry::PositionsIndex, vertindex);
        }

        glEnd();
    }
}

void GeoImmediatePumpGroup::masterAttribGeoPump(
          DrawEnv                     *pEnv,
    const GeoIntegralProperty         *lengths,
    const GeoIntegralProperty         *types,
    const Geometry::MFPropertiesType  *prop,
    const Geometry::MFPropIndicesType *propIdx,
          UInt32                              )
{
#ifdef DEBUG_WHICH_PUMP
    static bool bPrinted = false;

    if(bPrinted == false)
    {
        fprintf(stderr, "GeoImmediatePumpGroup::masterAttribGeoPump\n");
        bPrinted = true;
    }
#endif

    Window *win = pEnv->getWindow();

    // Setup: get all the data

    // check for empty geometry
    if(types == NULL || types->size() == 0)
        return;

    if(!pumpInternalSetup(types,   true))
        return;
    if(!pumpInternalSetup(lengths, false))
        return;

    PumpAttribInfo pumpInfo;
    pumpInfo.lengths = lengths;
    pumpInfo.types   = types;
    pumpInfo.prop    = prop;
    pumpInfo.propIdx = propIdx;

    UInt16 nattrib = prop->size32();

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
                SWARNING << "GeoImmediatePumpGroup::masterAttribGeoPump: "
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
                SWARNING << "GeoImmediatePumpGroup::masterAttribGeoPump: "
                         << "Invalid pump function for property " << i
                         << " type " << pumpInfo.attribPtr[i]->getDimension()
                         << "D " << formatNames[formatIdx]
                         << endLog;

                pumpInfo.attribData[i] = NULL;
                pumpInfo.attribPtr [i] = NULL;
                continue;
            }
        }

        pumpInfo.attribPump[i] = reinterpret_cast<attribPumpFunc>(
            win->getFunction(funcId));

        if(pumpInfo.attribPump[i] == NULL)
        {
            SWARNING << "GeoImmediatePumpGroup::masterAttribGeoPump: "
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
            SWARNING << "GeoImmediatePumpGroup::masterAttribGeoPump: "
                     << "No positions." << endLog;
            return;
        }
    }

    // global attribs?
    for(Int16 i = 0; i < nattrib; ++i)
    {
        if(pumpInfo.attribData[i]         != NULL &&
           pumpInfo.attribPtr [i]->size() == 1      )
        {
            pumpInfo.attribPump[i](i, pumpInfo.attribData[i]);
            pumpInfo.attribData[i] = NULL;
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
            SWARNING << "GeoImmediatePumpGroup::masterAttribGeoPump: "
                     << "No lengths, but more than one type?!"
                     << endLog;
            return;
        }

        nprims = 1;
        if(pumpInfo.attribIndex[0] != NULL)
        {
            curlen = pumpInfo.attribIndex[0]->size32();
        }
        else
        {
            curlen = pumpInfo.attribPtr[0]->size32();
        }
    }
    else
    {
        nprims = types->size32();
        lengths->getValue(curlen, 0);
    }

    UInt32 vertindex = 0;

    for(UInt32 primindex = 0; primindex < nprims; ++primindex)
    {
        glBegin(types->getValue<UInt16>(primindex));

        if(primindex < lengths->size())
            curlen = lengths->getValue<UInt32>(primindex);

        for(; curlen > 0; --curlen, ++vertindex)
        {
            for(Int16 i = nattrib - 1; i >= 0; --i)
            {
                if(pumpInfo.attribData[i])
                {
                    if(pumpInfo.attribIndex[i] != NULL)
                    {
                        pumpInfo.attribPump[i](
                            i, pumpInfo.attribData  [i] +
                               pumpInfo.attribStride[i] *
                               pumpInfo.attribIndex [i]->getValue<UInt32>(vertindex));
                    }
                    else
                    {
                        pumpInfo.attribPump[i](
                            i, pumpInfo.attribData  [i] +
                               pumpInfo.attribStride[i] * vertindex);
                    }
                }
            }
        }

        glEnd();
    }
}

OSG_END_NAMESPACE
