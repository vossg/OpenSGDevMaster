
#include "OSGColladaGlobal.h"

#ifdef OSG_WITH_COLLADA

#include "OSGColladaLog.h"
#include "OSGColladaScene.h"
#include "OSGColladaElementFactory.h"
#include "OSGColladaOptions.h"

#include "OSGNode.h"

/*! \class OSG::ColladaGlobal
    This is the entry point for the Collada loader from which the loading
    process is started.
    You can think of it as representing the <COLLADA> tag in a document.
 */

OSG_BEGIN_NAMESPACE

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

    DAE *dae = new DAE;
    dae->open(fileName.c_str());

    rootN = doRead(dae);

    dae->clear();
    delete dae;

    _docPath.clear();

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

    rootN = doRead(dae);

    _docPath.clear();

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
    , _pathHandler()
    , _docPath    ()
    , _dae        (NULL)
    , _docRoot    ()
    , _rootN      (NULL)
{
}

ColladaGlobal::~ColladaGlobal(void)
{
    delete _dae;
    _dae = NULL;
}

/*! Read the file stored in _docPath from the DAE \dae.
 */
NodeTransitPtr
ColladaGlobal::doRead(DAE *dae)
{
    NodeTransitPtr rootN(NULL);

    _dae     = dae;
    _docRoot = _dae->getRoot(_docPath);

    if(_docRoot != NULL)
    {
        domCOLLADA::domSceneRef scene = _docRoot->getScene();

        if(scene != NULL)
        {
            ColladaSceneRefPtr colScene = dynamic_pointer_cast<ColladaScene>(
                ColladaElementFactory::the()->create(scene, this));

            colScene->read   ();
            colScene->process();
        }
        else
        {
            SWARNING << "ColladaGlobal::read: No <scene> tag found in file ["
                     << _docPath << "]." << std::endl;
        }
    }
    else
    {
        SWARNING << "ColladaGlobal::read: collada-dom failed to obtain "
                 << "document root for file [" << _docPath << "]."
                 << std::endl;
    }
    
    rootN = _rootN;

    _docRoot = NULL;
    _dae     = NULL;
    _elemStore.clear();

    return rootN;
}

OSG_END_NAMESPACE

#endif // OSG_WITH_COLLADA
