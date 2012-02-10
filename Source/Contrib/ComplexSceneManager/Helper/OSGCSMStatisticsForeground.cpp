/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#include "OSGCSMStatisticsForeground.h"
#include "OSGSimpleStatisticsForeground.h"

#include "OSGRenderAction.h"
#include "OSGPointLight.h"
#include "OSGSpotLight.h"
#include "OSGDirectionalLight.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGCSMStatisticsForegroundBase.cpp file.
// To modify it, please change the .fcd file (OSGCSMStatisticsForeground.fcd)
// and regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void CSMStatisticsForeground::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

CSMStatisticsForeground::CSMStatisticsForeground(void) :
     Inherited(    ),
    _pStatFG  (NULL)
{
}

CSMStatisticsForeground::CSMStatisticsForeground(
    const CSMStatisticsForeground &source) :

     Inherited(source),
    _pStatFG  (NULL  )
{
}

CSMStatisticsForeground::~CSMStatisticsForeground(void)
{
}

void CSMStatisticsForeground::draw(DrawEnv *)
{
}

void CSMStatisticsForeground::addElement(     
          SimpleStatisticsForeground *pStatFG,
    const std::string                &szStatObj,
    const std::string                &szStatElem,
    const std::string                &szFormat  )
{
#if !defined(OSG_OGL_COREONLY) || defined(OSG_CHECK_COREONLY)
    if(szStatObj.compare("Text") == 0)
    {
        if(szStatElem.compare("freetext") == 0)
        {
            pStatFG->addText(szFormat.c_str());
        }
        else
        {
            fprintf(stderr, "Unknown stat elem %s for %s\n",
                    szStatElem.c_str(),
                    szStatObj.c_str());
        }
    }
    else if(szStatObj.compare("RenderAction") == 0)
    {
        if(szStatElem.compare("statDrawTime") == 0)
        {
            pStatFG->addElement(RenderAction::statDrawTime, 
                                szFormat.c_str());
        }
        else if(szStatElem.compare("statTravTime") == 0)
        {
            pStatFG->addElement(RenderAction::statTravTime, 
                                szFormat.c_str());
        }
        else if(szStatElem.compare("statNStates") == 0)
        {
            pStatFG->addElement(RenderAction::statNStates, 
                                szFormat.c_str());
        }
        else if(szStatElem.compare("statNShaders") == 0)
        {
            pStatFG->addElement(RenderAction::statNShaders, 
                                szFormat.c_str());
        }
        else if(szStatElem.compare("statNShaderParams") == 0)
        {
            pStatFG->addElement(RenderAction::statNShaderParams, 
                                szFormat.c_str());
        }
        else if(szStatElem.compare("statNGeometries") == 0)
        {
            pStatFG->addElement(RenderAction::statNGeometries, 
                                szFormat.c_str());
        }
        else if(szStatElem.compare("statNMatrices") == 0)
        {
            pStatFG->addElement(RenderAction::statNMatrices, 
                                szFormat.c_str());
        }
        else if(szStatElem.compare("statNTriangles") == 0)
        {
            pStatFG->addElement(RenderAction::statNTriangles, 
                                szFormat.c_str());
        }
        else
        {
            fprintf(stderr, "Unknown stat elem %s for %s\n",
                    szStatElem.c_str(),
                    szStatObj.c_str());
        }
    }
    else if(szStatObj.compare("PointLight") == 0)
    {
        if(szStatElem.compare("statNPointLights") == 0)
        {
            pStatFG->addElement(PointLight::statNPointLights, 
                                szFormat.c_str());
        }
        else
        {
            fprintf(stderr, "Unknown stat elem %s for %s\n",
                    szStatElem.c_str(),
                    szStatObj.c_str());
        }
    }
    else if(szStatObj.compare("DirectionalLight") == 0)
    {
        if(szStatElem.compare("statNDirectionalLights") == 0)
        {
            pStatFG->addElement(DirectionalLight::statNDirectionalLights, 
                                szFormat.c_str());
        }
        else
        {
            fprintf(stderr, "Unknown stat elem %s for %s\n",
                    szStatElem.c_str(),
                    szStatObj.c_str());
        }
    }
    else if(szStatObj.compare("SpotLight") == 0)
    {
        if(szStatElem.compare("statNSpotLights") == 0)
        {
            pStatFG->addElement(SpotLight::statNSpotLights, 
                                szFormat.c_str());
        }
        else
        {
            fprintf(stderr, "Unknown stat elem %s for %s\n",
                    szStatElem.c_str(),
                    szStatObj.c_str());
        }
    }
    else if(szStatObj.compare("Drawable") == 0)
    {
        if(szStatElem.compare("statNTriangles") == 0)
        {
            pStatFG->addElement(Drawable::statNTriangles, 
                                szFormat.c_str());
        }
        else if(szStatElem.compare("statNLines") == 0)
        {
            pStatFG->addElement(Drawable::statNLines, 
                                szFormat.c_str());
        }
        else if(szStatElem.compare("statNPoints") == 0)
        {
            pStatFG->addElement(Drawable::statNPoints, 
                                szFormat.c_str());
        }
        else if(szStatElem.compare("statNVertices") == 0)
        {
            pStatFG->addElement(Drawable::statNVertices, 
                                szFormat.c_str());
        }
        else if(szStatElem.compare("statNPrimitives") == 0)
        {
            pStatFG->addElement(Drawable::statNPrimitives, 
                                szFormat.c_str());
        }
        else
        {
            fprintf(stderr, "Unknown stat elem %s for %s\n",
                    szStatElem.c_str(),
                    szStatObj.c_str());
        }
    }
    else if(szStatObj.compare("TextureObjChunk") == 0)
    {
        if(szStatElem.compare("statNTextures") == 0)
        {
            pStatFG->addElement(TextureObjChunk::statNTextures, 
                                szFormat.c_str());
        }
        else if(szStatElem.compare("statNTexBytes") == 0)
        {
            pStatFG->addElement(TextureObjChunk::statNTexBytes, 
                                szFormat.c_str());
        }
        else
        {
            fprintf(stderr, "Unknown stat elem %s for %s\n",
                    szStatElem.c_str(),
                    szStatObj.c_str());
        }
    }
    else if(szStatObj.compare("ChangeList") == 0)
    {
        if(szStatElem.compare("statNChangedStoreSize") == 0)
        {
            pStatFG->addElement(ChangeList::statNChangedStoreSize, 
                                szFormat.c_str());
        }
        else if(szStatElem.compare("statNCreatedStoreSize") == 0)
        {
            pStatFG->addElement(ChangeList::statNCreatedStoreSize, 
                                szFormat.c_str());
        }
        else if(szStatElem.compare("statNUnCommittedStoreSize") == 0)
        {
            pStatFG->addElement(ChangeList::statNUnCommittedStoreSize, 
                                szFormat.c_str());
        }
        else if(szStatElem.compare("statNPoolSize") == 0)
        {
            pStatFG->addElement(ChangeList::statNPoolSize, 
                                szFormat.c_str());
        }
        else
        {
            fprintf(stderr, "Unknown stat elem %s for %s\n",
                    szStatElem.c_str(),
                    szStatObj.c_str());
        }
    }
    else
    {
        fprintf(stderr, "Unknown stat object %s\n",
                szStatObj.c_str());
    }
#endif
}

bool CSMStatisticsForeground::init(CSMWindow *pCSMWin)
{
#if !defined(OSG_OGL_COREONLY) || defined(OSG_CHECK_COREONLY)
    SimpleStatisticsForegroundUnrecPtr pStatFG =  
        OSG::SimpleStatisticsForeground::create();

    pStatFG->setActive(this->getActive());
    pStatFG->setSize  (this->getSize  ());
    pStatFG->setColor (this->getColor ());

    _pStatFG = pStatFG;

    if(_mfElements.size() != 0)
    {
        std::string szSep("::");

        for(SizeT i = 0; i < _mfElements.size(); ++i)
        {
            SizeT uiPos = _mfElements[i].rfind(szSep);

            if(uiPos != std::string::npos)
            {
                std::string szElem   = _mfElements[i].substr(0, 
                                                             uiPos            );
                std::string szFormat = _mfElements[i].substr(uiPos + 2, 
                                                             std::string::npos);
                
                if(szElem.size() == 0 || szFormat.size() == 0)
                    continue;

                uiPos = szElem.rfind(szSep);

                if(uiPos != std::string::npos)
                {
                    std::string szStatObj  = szElem.substr(0, 
                                                           uiPos            );
                    std::string szStatElem = szElem.substr(uiPos + 2, 
                                                           std::string::npos);

                    if(szStatObj.size() == 0 || szStatElem.size() == 0)
                        continue;

                    addElement(pStatFG,
                               szStatObj,
                               szStatElem,
                               szFormat  );
                }
            }
        }
    }

//    pStatFG->addElement(RenderAction::statDrawTime, "Draw FPS: %r.3f");
//    pStatFG->addElement(RenderAction::statDrawTime, "DrawTime: %.3f s");
#endif

    return true;
}

StatisticsForeground *CSMStatisticsForeground::getOSGForeground(void)
{
    return _pStatFG;
}

void CSMStatisticsForeground::resolveLinks(void)
{
    _pStatFG = NULL;

    Inherited::resolveLinks();
}

/*----------------------------- class specific ----------------------------*/

void CSMStatisticsForeground::changed(ConstFieldMaskArg whichField, 
                                      UInt32            origin,
                                      BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void CSMStatisticsForeground::dump(      UInt32    ,
                                   const BitVector ) const
{
    SLOG << "Dump CSMStatisticsForeground NI" << std::endl;
}

OSG_END_NAMESPACE
