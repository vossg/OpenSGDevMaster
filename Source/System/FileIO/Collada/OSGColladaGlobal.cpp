/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                Copyright (C) 2009 by the OpenSG Forum                     *
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
#pragma GCC diagnostic ignored "-Wold-style-cast"
#endif

#include "OSGColladaGlobal.h"

#ifdef OSG_WITH_COLLADA

#include "OSGColladaLog.h"
#include "OSGColladaCOLLADA.h"
#include "OSGColladaElementFactory.h"
#include "OSGColladaOptions.h"

#include "OSGNode.h"

/*! \class OSG::ColladaGlobal
    This is the entry point for the Collada loader from which the loading
    process is started.
    You can think of it as representing the <COLLADA> tag in a document.
 */

OSG_BEGIN_NAMESPACE

StatElemDesc<StatIntElem> ColladaGlobal::statNGeometryCreated(
    "Collada::NGeometryCreated",
    "Number of OpenSG geometries created by the collada loader",
    StatElemDescBase::RESET_ALWAYS);
StatElemDesc<StatIntElem> ColladaGlobal::statNMaterialCreated(
    "Collada::NMaterialCreated",
    "Number of OpenSG materials created by the collada loader",
    StatElemDescBase::RESET_ALWAYS);
StatElemDesc<StatIntElem> ColladaGlobal::statNTextureCreated(
    "Collada::NTextureCreated",
    "Number of OpenSG textures created by the collada loader",
    StatElemDescBase::RESET_ALWAYS);

StatCollector *
ColladaGlobal::getStatCollector(void)
{
    return _statColl;
}

void
ColladaGlobal::setStatCollector(StatCollector *statColl)
{
    _statColl = statColl;
}

ColladaGlobalTransitPtr
ColladaGlobal::create(void)
{
    return ColladaGlobalTransitPtr(new Self);
}

/*! Read the file \a fileName using a new DAE database.
 */
NodeTransitPtr
ColladaGlobal::read(std::istream &is, const std::string &fileName)
{
    NodeTransitPtr rootN;

    _pathHandler.clearPathList();
    _pathHandler.clearBaseFile();

    _pathHandler.push_frontCurrentDir(                );
    _pathHandler.setBaseFile         (fileName.c_str());

    _docPath = fileName;

    _dae = new DAE;
    _dae->open(fileName.c_str());

    rootN = doRead();

    _docPath. clear();
    _dae    ->clear();
    delete _dae;
    _dae = NULL;

    return rootN;
}

/*! Read the file \a fileName from the existing DAE database \a dae.
    The given \a fileName must already be loaded into the DAE.

    Useful if multiple documents are stored in one DAE database or
    if an application needs to access the DAE itself to extract
    data that is not processed by the loader.
 */
NodeTransitPtr
ColladaGlobal::read(DAE *dae, const std::string &fileName)
{
    NodeTransitPtr rootN(NULL);

    _pathHandler.clearPathList();
    _pathHandler.clearBaseFile();

    _pathHandler.push_frontCurrentDir(                );
    _pathHandler.setBaseFile         (fileName.c_str());

    _docPath = fileName;
    _dae     = dae;

    rootN = doRead();

    _docPath.clear();
    _dae = NULL;

    return rootN;
}

void
ColladaGlobal::addElement(ColladaElement *elem)
{
    _elemStore.push_back(elem);
}

ColladaGlobal::ColladaGlobal(void)
    : Inherited   ()
    , _elemStore  ()
    , _options    ()
    , _statColl   (NULL)
    , _pathHandler()
    , _docPath    ()
    , _dae        (NULL)
    , _rootN      (NULL)
{
}

ColladaGlobal::~ColladaGlobal(void)
{
    delete _dae;
    _dae = NULL;
}

/*! Read the file stored in _docPath from the DAE _dae.
 */
NodeTransitPtr
ColladaGlobal::doRead(void)
{
    NodeTransitPtr rootN(NULL);

    if(_statColl == NULL)
        _statColl = new StatCollector;

    _statColl->getElem(statNGeometryCreated, true);
    _statColl->getElem(statNMaterialCreated, true);
    _statColl->getElem(statNTextureCreated,  true);

    _statColl->reset  (StatElemDescBase::RESET_ALWAYS);

    domCOLLADARef docRoot = _dae->getRoot(_docPath);

    if(docRoot != NULL)
    {
        ColladaCOLLADARefPtr colCOL = dynamic_pointer_cast<ColladaCOLLADA>(
            ColladaElementFactory::the()->create(docRoot, this));

        colCOL->read();
    }
    else
    {
        SWARNING << "ColladaGlobal::read: collada-dom failed to obtain "
                 << "document root for file [" << _docPath << "]."
                 << std::endl;
    }
    
    rootN = _rootN;

    _elemStore.clear();

#ifndef OSG_COLLADA_SILENT
    std::string statString;
    _statColl->putToString(statString);

    OSG_COLLADA_LOG(("ColladaGlobal:read: Statistics\n%s\n",
                     statString.c_str()));
#endif // OSG_COLLADA_SILENT

    return rootN;
}

OSG_END_NAMESPACE

#endif // OSG_WITH_COLLADA
