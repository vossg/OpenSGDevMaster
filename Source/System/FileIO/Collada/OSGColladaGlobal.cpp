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

#include <OSGColladaGlobal.h>
#include <OSGColladaLog.h>

#ifdef OSG_WITH_COLLADA

#include <OSGColladaInstanceVisualScene.h>

#include <1.4/dom/domCOLLADA.h>
#include <1.4/dom/domInstanceWithExtra.h>

/*! \class OSG::ColladaGlobal
    A special \c ColladaElement that is the loader's entry point for loading a
    collada document into OpenSG. It is the starting point from which all
    other instances of \c ColladaElements are created.
    You can think of it as representing the &lt;COLLADA&gt; DOM element or
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
    
    domInstanceWithExtraRef          instVisScene    =
        scene->getInstance_visual_scene();
    ColladaInstanceVisualSceneRefPtr colInstVisScene =
        ColladaInstanceVisualScene::create(instVisScene, getGlobal());
    addElement(colInstVisScene);
    
    colInstVisScene->read();
    
    _rootNode = colInstVisScene->createInstance();
}

ColladaGlobal::ColladaGlobal(void)
    : Inherited(NULL, this)
{
}

ColladaGlobal::~ColladaGlobal(void)
{
}

OSG_END_NAMESPACE

#endif // OSG_WITH_COLLADA
