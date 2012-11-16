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

#if defined(OSG_WITH_COLLADA) || defined(OSG_DO_DOC)

#include "OSGColladaLog.h"
#include "OSGColladaCOLLADA.h"
#include "OSGColladaInstInfo.h"
#include "OSGColladaElementFactory.h"
#include "OSGColladaOptions.h"

#include "OSGNode.h"

/*! \class OSG::ColladaGlobal
    This is the entry point for the Collada loader from which the loading
    process is started.
    You can think of it as representing the &lt;COLLADA&gt; tag in a document.
 */

OSG_BEGIN_NAMESPACE

StatElemDesc<StatIntElem> ColladaGlobal::statNGeometryCreated(
    "Collada::NGeometryCreated",
    "Number of OpenSG geometries created by the collada loader",
    StatElemDescBase::RESET_ALWAYS);
StatElemDesc<StatIntElem> ColladaGlobal::statNGeometryUsed(
    "Collada::NGeometryUsed",
    "Number of OpenSG geometries in the scene created by the collada loader",
    StatElemDescBase::RESET_ALWAYS);
StatElemDesc<StatIntElem> ColladaGlobal::statNMaterialCreated(
    "Collada::NMaterialCreated",
    "Number of OpenSG materials created by the collada loader",
    StatElemDescBase::RESET_ALWAYS);
StatElemDesc<StatIntElem> ColladaGlobal::statNMaterialUsed(
    "Collada::NMaterialUsed",
    "Number of OpenSG materials in the scene created by the collada loader",
    StatElemDescBase::RESET_ALWAYS);
StatElemDesc<StatIntElem> ColladaGlobal::statNLightCreated(
    "Collada::NLightCreated",
    "Number of OpenSG lights created by the collada loader",
    StatElemDescBase::RESET_ALWAYS);
StatElemDesc<StatIntElem> ColladaGlobal::statNLightUsed(
    "Collada::NLightUsed",
    "Number of OpenSG lights in the scene created by the collada loader",
    StatElemDescBase::RESET_ALWAYS);
StatElemDesc<StatIntElem> ColladaGlobal::statNTextureCreated(
    "Collada::NTextureCreated",
    "Number of OpenSG textures created by the collada loader",
    StatElemDescBase::RESET_ALWAYS);
StatElemDesc<StatIntElem> ColladaGlobal::statNTextureUsed(
    "Collada::NTextureUsed",
    "Number of OpenSG textures in the scene created by the collada loader",
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

/* 
 * Helper function for de-mangling filepaths.  Removes leading filepath
 * separators and  replaces escaped url characters (i.e. "%20" with " " (a
 * single space)) 
 */

std::string ColladaGlobal::fixFilepath(std::string filepath)
{   

    std::string escaped[] = {"%20", "%22", "%3C", "%3E", "%23", "%25", "%7B", 
                             "%7D", "%7C", "%5E", "%7E", "%5B", "%5D", "%60"};

    std::string replacements[] = {" ","\"","<",">","#","%","{",
                                  "}","|","^","~","[","]","`"};

    // removing leading file path separators
    while(filepath[0] == '/' || filepath[0] == '\\')
    {
        filepath = filepath.substr(1);
    }

    // remove escaped characters and replace
    size_t pos = 0;

    for(UInt32 i = 0; i < 14; ++i)
    {
        for(;;)
        {
            pos = filepath.find(escaped[i], pos);

            if(pos == std::string::npos) 
            {
                break;
            }
            else 
            {
                filepath = filepath.replace(pos, 3, replacements[i]);
            }
        }
    }

    return filepath;
}

// re-formats an image filepath so that it can be read properly
std::string ColladaGlobal::fixImageFilepath(std::string szImgPath)
{
    if(szImgPath.substr(0, 5) == "file:")
    {
        szImgPath = szImgPath.substr(4);
    }

    return fixFilepath(szImgPath);
}

std::string ColladaGlobal::uriToNativePath(const std::string      &uriRef, 
                                                 cdom::systemType  type  ) 
{
    std::string scheme, authority, path, query, fragment;

    cdom::parseUriRef(uriRef, scheme, authority, path, query, fragment);

	// Make sure we have a file scheme URI, or that it doesn't have a scheme
	if (!scheme.empty()  &&  scheme != "file")
		return "";

    std::string filePath;

#if 0
    fprintf(stderr, "foo %s ==> | %s | %s | %s | %s | %s | \n",
            uriRef.c_str(),
            scheme.c_str(),
            authority.c_str(),
            path.c_str(),
            query.c_str(),
            fragment.c_str());
#endif

//    if(authority.empty() == false && path.empty() == true)
//        path.swap(authority);

	if(type == cdom::Windows) 
    {
		if(!authority.empty())
			filePath += std::string("\\\\") + authority; // UNC path
	
		// Replace two leading slashes with one leading slash, so that
		// ///otherComputer/file.dae becomes //otherComputer/file.dae and
		// //folder/file.dae becomes /folder/file.dae
		if(path.length() >= 2  &&  path[0] == '/'  &&  path[1] == '/')
			path.erase(0, 1);

		// Convert "/C:/" to "C:/"
		if(path.length() >= 3  &&  path[0] == '/'  &&  path[2] == ':')
			path.erase(0, 1);

		// Convert forward slashes to back slashes
		path = cdom::replace(path, "/", "\\");
	}
    else
    {
        filePath += authority;
    }
    
	filePath += path;

	// Replace %20 with space
	filePath = cdom::replace(filePath, "%20", " ");
	
	return filePath;
}

ColladaGlobal::ColladaGlobal(void)
    : Inherited   ()
    , _instQueue  ()
    , _loaderState()
    , _elemStore  ()
    , _options    ()
    , _statColl   (NULL)
    , _pathHandler()
    , _docPath    ()
    , _docRoot    ()
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

    // force creation of the statistic elements
    _statColl->getElem(statNGeometryCreated, true);
    _statColl->getElem(statNGeometryUsed,    true);
    _statColl->getElem(statNMaterialCreated, true);
    _statColl->getElem(statNMaterialUsed,    true);
    _statColl->getElem(statNLightCreated,    true);
    _statColl->getElem(statNLightUsed,       true);
    _statColl->getElem(statNTextureCreated,  true);
    _statColl->getElem(statNTextureUsed,     true);

    _statColl->reset  (StatElemDescBase::RESET_ALWAYS);

    _globalsAtt = GlobalsAttachment::create();
    _docRoot    = dynamic_cast<domCOLLADA *>(_dae->getRoot(_docPath));

    if(_docRoot != NULL)
    {
        ColladaCOLLADARefPtr colCOL = dynamic_pointer_cast<ColladaCOLLADA>(
            ColladaElementFactory::the()->create(_docRoot, this));

        colCOL->read(NULL);

        for(UInt32 i = 0; _instQueue.empty() == false; ++i)
        {
            if(i > 10)
            {
                SWARNING << "ColladaGlobal::doRead: InstanceQueue loop "
                         << "maximum iteration count reached." << std::endl;
                break;
            }

            InstanceQueue workQueue;
            workQueue.swap(_instQueue);

            InstanceQueueIt iqIt  = workQueue.begin();
            InstanceQueueIt iqEnd = workQueue.end  ();

            for(; iqIt != iqEnd; ++iqIt)
                (*iqIt)->process();
        }
    }
    else
    {
        SWARNING << "ColladaGlobal::read: collada-dom failed to obtain "
                 << "document root for file [" << _docPath << "]."
                 << std::endl;
    }
    
    if(_globalsAtt->getMFElements()->empty() == false)
        _rootN->addAttachment(_globalsAtt);

    rootN = _rootN;

    _docRoot    = NULL;
    _globalsAtt = NULL;
    _instQueue  .clear();
    _loaderState.clear();
    _elemStore  .clear();

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
