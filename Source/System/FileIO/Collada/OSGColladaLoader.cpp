/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2006 by the OpenSG Forum                   *
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

/*! \file OSGColladaLoader.cpp
    \ingroup GrpFoundationLoader
 */

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#include <iostream>

#include "OSGColladaLoader.h"
#include "OSGPathHandler.h"

#ifdef OSG_WITH_COLLADA
#include "OSGColladaIntegration.h"

#include "dae.h"
#include "modules/daeSTLDatabase.h"
#include "dom/domCOLLADA.h"
#endif

OSG_USING_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

ColladaLoader::ColladaLoader(void) :
    _pPathHandler(NULL)
{
    _pPathHandler = new PathHandler;
}

ColladaLoader::~ColladaLoader(void)
{
    delete _pPathHandler;
}

NodePtr ColladaLoader::read(      std::istream  &is, 
                            const Char8         *szFileName)
{
    NodePtr returnValue = NullFC;

#ifdef OSG_WITH_COLLADA
    _pPathHandler->clearPathList();
    _pPathHandler->clearBaseFile();
    _pPathHandler->push_frontCurrentDir();

    _pPathHandler->setBaseFile(szFileName);


    fprintf(stderr, "Read %s\n", szFileName);


    DAE            *pInput    = new DAE;
    daeSTLDatabase *pDataBase = new daeSTLDatabase;

    pInput->setDatabase(pDataBase);

    initColladaIntegration();
  
    Int32 iError = pInput->load(szFileName);

    if(iError != DAE_OK)
    {
        std::cerr << "load failed " << daeErrorString(iError) << "\n";
        return returnValue;
    }
    
    UInt32 uiNumCollections = pInput->getDatabase()->getCollectionCount();

    fprintf(stderr, "%d collections\n", 
            uiNumCollections);

//    pDataBase->dump();

    UInt32 i = 0;

//    for(UInt32 i = 0; i < uiNumCollections; ++i)
    {
        domCOLLADA *pDom = NULL;

        if(pInput->getDatabase()->getCollection(i) != NULL)
        {
            pDom = dynamic_cast<domCOLLADA *>(
                pInput->getDatabase()->getCollection(i)->getDomRoot());
        }

#ifdef OSG_DEBUG_PRINT
        fprintf(stderr, "got dom %p\n", pDom);
#endif

        if(pDom != NULL)
        {
            domCOLLADA::domSceneRef pScene = pDom->getScene();

#ifdef OSG_DEBUG_PRINT
            fprintf(stderr, "got scene %p\n",
                    &*pScene);
#endif

            if(pScene != NULL)
            {
                daeURI oUri = pScene->getInstance_visual_scene()->getUrl();

#ifdef OSG_DEBUG_PRINT
                fprintf(stderr, "uri %s %d\n %s", 
                        oUri.getURI(), 
                        oUri.getState(),
                        oUri.getFile());
#endif
            
                daeElementRef pElem = oUri.getElement();
                
#ifdef OSG_DEBUG_PRINT
                fprintf(stderr, "elem %p %s %s\n", 
                        &*pElem, 
                        pElem->getTypeName(),
                        pElem->getElementName());
#endif
            
                daeIntegrationObject *pIntegrationObj = pElem->getIntObject();
            
                VisualSceneIntegration *pSceneInt = 
                    dynamic_cast<VisualSceneIntegration *>(pIntegrationObj);

#ifdef OSG_DEBUG_PRINT
                fprintf(stderr, "Got int obj %p %p\n", 
                        pIntegrationObj,
                        pSceneInt);
#endif
                
                if(pSceneInt != NULL)
                {
                    returnValue = pSceneInt->getScene();
                }
            }
        }
    }

#ifdef OSG_DEBUG_PRINT
    fprintf(stderr, "returnValue %p\n", &(*returnValue));
#endif
#endif

    return returnValue;
}

/*-------------------------- assignment -----------------------------------*/
