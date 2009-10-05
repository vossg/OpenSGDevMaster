/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                Copyright (C) 2008 by the OpenSG Forum                     *
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

#if __GNUC__ >= 4 || __GNUC_MINOR__ >=3
//#pragma GCC diagnostic warning "-Wold-style-cast"
#pragma GCC diagnostic ignored "-Wold-style-cast"
#endif

#include <OSGColladaGlobal.h>
#include <OSGColladaLog.h>

#ifdef OSG_WITH_COLLADA

#include "OSGColladaInstanceVisualScene.h"
#include "OSGMultiCore.h"

#include <dom/domCOLLADA.h>
#include <dom/domInstanceWithExtra.h>

/*! \class OSG::ColladaGlobal
    A special \c ColladaElement that is the loader's entry point for loading a
    collada document into OpenSG. It is the starting point from which all
    other instances of \c ColladaElements are created.
    You can think of it as representing the &quot;COLLADA&quot; DOM element or
    simply the whole document.
 */

OSG_BEGIN_NAMESPACE

void ColladaGlobal::read(void)
{
    OSG_COLLADA_LOG(("ColladaGlobal::read: _docPath [%s]\n", _docPath.c_str()));
    
    _elem = _dae.open(_docPath);
    
    if(_elem == NULL)
    {
        FWARNING(("ColladaGlobal::read: collada-dom failed to read file [%s]\n",
                  _docPath.c_str()));
        
        return;
    }
    
    domCOLLADARef           docRoot = getDOMElementAs<domCOLLADA>();
    domCOLLADA::domSceneRef scene   = docRoot->getScene();
    
    if(scene == NULL)
    {
        FWARNING(("ColladaGlobal::read: No <scene> found in file [%s]\n",
                  _docPath.c_str()));
        
        return;
    }
    
    domAssetRef docAsset = docRoot->getAsset();

    if(docAsset != NULL)
    {
        domAsset::domContributor_Array &domContrA = 
            docAsset->getContributor_array();

        for(UInt32 i = 0; i < domContrA.getCount(); ++i)
        {
            domAsset::domContributor::domAuthoring_toolRef docAuthTool = 
                domContrA.get(i)->getAuthoring_tool();

            if(osgStringNCaseCmp(docAuthTool->getValue(), 
                                 "Google SketchUp",
                                 15                     ) == 0)
            {
                _invertTransparency = true;
            }

            if(_invertTransparency == true)
                break;
        }
    }

    MultiCoreUnrecPtr lights = MultiCore::create();
    _lightsN = makeNodeFor         (lights);
    _rootN   = makeCoredNode<Group>(      );
    
    domInstanceWithExtraRef          instVisScene    =
        scene->getInstance_visual_scene();
    ColladaInstanceVisualSceneRefPtr colInstVisScene =
        ColladaInstanceVisualScene::create(instVisScene, getGlobal());
    addElement(colInstVisScene);
    
    colInstVisScene->read();
    
    NodeUnrecPtr visSceneN = colInstVisScene->createInstance();

    if(lights->getNCores() == 0)
    {
        _rootN->addChild(visSceneN);
    }
    else
    {
        _lightsN->addChild(visSceneN);
        _rootN  ->addChild(_lightsN );
    }
}

ColladaGlobal::ColladaGlobal(void)
    : Inherited(NULL, this),
      _docPath (),
      _rootN   (),
      _lightsN (),
      _dae     (),
      _elements(),
      _invertTransparency(false)
{
}

ColladaGlobal::~ColladaGlobal(void)
{
}

OSG_END_NAMESPACE

#endif // OSG_WITH_COLLADA
