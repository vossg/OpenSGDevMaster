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

#include <boost/bind.hpp>

#include "OSGConfig.h"

#include "OSGComplexSceneManager.h"
#include "OSGOSGSceneFileType.h"
#include "OSGContainerCollection.h"
#include "OSGSceneFileHandler.h"
#include "OSGImageFileHandler.h"
#include "OSGNameAttachment.h"
#include "OSGAction.h"
#include "OSGCSMResetInterface.h"
#include "OSGFrameHandler.h"
#include "OSGGeoProperty.h"

#include "OSGGeoFunctions.h"

//#include "OSGFieldContainerFactory.h"
//#include "OSGTypeFactory.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGComplexSceneManagerBase.cpp file.
// To modify it, please change the .fcd file (OSGComplexSceneManager.fcd) and
// regenerate the base file.

struct NodeFinder
{
    std::string  _szRefName;
    Node        *_pResult;

    NodeFinder(void) :
        _szRefName(    ),
        _pResult  (NULL)
    {
    }

    Action::ResultE enter(Node * const pNode)
    {
        Action::ResultE returnValue = Action::Continue;

        const Char8 *szName = OSG::getName(pNode);

        if(szName != NULL)
        {
            if(osgStringCmp(_szRefName.c_str(), szName) == 0)
            {
                _pResult = pNode;

                returnValue = Action::Quit;
            }
        }
        
        return returnValue;
    }
};

struct ElementFinder
{
    std::string     _szRefName;
    FieldContainer *_pResult;

    ElementFinder(void) :
        _szRefName(    ),
        _pResult  (NULL)
    {
    }

    Action::ResultE enter(Node * const pNode)
    {
        Action::ResultE returnValue = Action::Continue;

        const Char8 *szName = OSG::getName(pNode);

        if(szName != NULL)
        {
            if(osgStringCmp(_szRefName.c_str(), szName) == 0)
            {
                _pResult = pNode;

                returnValue = Action::Quit;
            }
        }
        else if(pNode->getCore() != NULL)
        {
            szName = OSG::getName(pNode->getCore());

            if(szName != NULL)
            {
                if(osgStringCmp(_szRefName.c_str(), szName) == 0)
                {
                    _pResult = pNode;
                    
                    returnValue = Action::Quit;
                }
            }
        }
        
        return returnValue;
    }
};

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

Time                                ComplexSceneManager::SystemTime = 0.0;

ComplexSceneManagerUnrecPtr         ComplexSceneManager::_the = NULL;
PathHandler                         ComplexSceneManager::_oPathHandler;
std::vector<FieldContainerUnrecPtr> ComplexSceneManager::_vStaticGlobals;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ComplexSceneManager::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


ComplexSceneManager *ComplexSceneManager::the(void)
{
    return _the;
}

FieldContainer *ComplexSceneManager::resolveStatic(const Char8 *szName)
{
    std::vector<FieldContainerUnrecPtr>::const_iterator gIt  = 
        _vStaticGlobals.begin();

    std::vector<FieldContainerUnrecPtr>::const_iterator gEnd = 
        _vStaticGlobals.end  ();

          AttachmentContainer *pAttCnt     = NULL;
          Node                *pNode       = NULL;
    const Char8               *szTmpName   = NULL;

    while(gIt != gEnd)
    {
        pNode = dynamic_cast<Node *>((*gIt).get());

        if(pNode != NULL)
        {
            ElementFinder oFinder;

            oFinder._szRefName = szName;

            traverse(pNode, boost::bind(&ElementFinder::enter, &oFinder, _1));

            if(oFinder._pResult != NULL)
            {
                return oFinder._pResult;
            }
         }
        
        pAttCnt = dynamic_cast<AttachmentContainer *>((*gIt).get());

        if(pAttCnt != NULL)
        {
            szTmpName = OSG::getName(pAttCnt);
           
            if(szTmpName != NULL && osgStringCmp(szTmpName, szName) == 0)
            {
                return pAttCnt;
            }
            else
            {
#if 0                                                                    
                FieldContainer *tmpVal = pAttCnt->findNamedComponent(szName);
                
                if(tmpVal != NULL)
                    return tmpVal;
#endif
            }
        }

        ++gIt;
    }

    return NULL;
}

void ComplexSceneManager::addStaticGlobals(const Char8 *szFilename)
{
    std::string szFilenameResolved = _oPathHandler.findFile(szFilename);

    if(szFilenameResolved.empty() == true)
    {
        fprintf(stderr, "Could not find static global file %s\n",
                szFilename);

        return;
    }

    FieldContainerUnrecPtr pRes = 
        readOSGFile(szFilenameResolved,
                    boost::bind(&ComplexSceneManager::resolveStatic, _1));
    
    if(pRes == NULL)
        return;

    ContainerCollectionUnrecPtr pColl = 
        dynamic_pointer_cast<ContainerCollection>(pRes);

    if(pColl == NULL)
        return;

    MFUnrecFieldContainerPtr::const_iterator fIt  = 
        pColl->getMFContainers()->begin();

    MFUnrecFieldContainerPtr::const_iterator fEnd = 
        pColl->getMFContainers()->end();

    while(fIt != fEnd)
    {
        _vStaticGlobals.push_back(*fIt);

        ++fIt;
    }
}

void ComplexSceneManager::scanParamFile(
    const Char8                    *szFilename,
          std::vector<std::string> &vParams   )
{
    FILE *pIn = fopen(szFilename, "r");

    Char8 szRow[1024];

          std::string  szBuffer;
    const Char8       *szDelim = " \t\n ";

    vParams.clear();

    while(!feof(pIn))
    {
        fgets(szRow, 1024, pIn);
        
        szBuffer = szRow;

        if(feof(pIn)                ||
           szBuffer.empty() == true || 
           szBuffer[0]      == '\n' || 
           szBuffer[0]      == '#'   )
        {
            continue;
        }

        string_token_iterator cIt (szBuffer, szDelim);
        string_token_iterator cEnd;

        while(cIt != cEnd)
        {
            vParams.push_back(*cIt);
            ++cIt;
        }
    }

    fclose(pIn);
}

void ComplexSceneManager::scanPreSystem(std::vector<std::string> &vParams)
{
    static const UInt32 ScanSystem  = 0;
    static const UInt32 ScanData    = 1;
    static const UInt32 ScanGlobals = 2;

    UInt32 uiState = ScanSystem;

    std::vector<std::string>::iterator       pIt  = vParams.begin();
    std::vector<std::string>::const_iterator pEnd = vParams.end  ();

    while(pIt != pEnd)
    {
        if((*pIt)[0] == '-' && (*pIt)[1] == '-')
        {
            if((*pIt)[2] == 'd' && (*pIt)[3] == 'a' && 
               (*pIt)[4] == 't' && (*pIt)[5] == 'a')
            {
                uiState = ScanData;
            }
            else if((*pIt)[2] == 'g' && (*pIt)[3] == 'l' && 
                    (*pIt)[4] == 'o' && (*pIt)[5] == 'b' &&
                    (*pIt)[6] == 'a' && (*pIt)[7] == 'l')
            {
                uiState = ScanGlobals;
            }
            else if((*pIt)[2] == 's' && (*pIt)[3] == 'y' && 
                    (*pIt)[4] == 's' && (*pIt)[5] == 't' &&
                    (*pIt)[6] == 'e' && (*pIt)[7] == 'm')
            {
                uiState = ScanSystem;
            }
            else
            {
                fprintf(stderr, "Unknow option %s\n", (*pIt).c_str());
                break;
            }
        }
        else
        {
            if(uiState == ScanSystem)
            {
                break;
            }
            else if(uiState == ScanGlobals)
            {
                addStaticGlobals((*pIt).c_str());
            }
            else if(uiState == ScanData)
            {
                FWARNING(("Error data not allowed at this point, "
                          "ignoring %s\n", (*pIt).c_str()));
            }
        }

        ++pIt;
    }

    if(pIt != vParams.begin())
    {
        vParams.erase(vParams.begin(), pIt);
    }
}

void ComplexSceneManager::startFrom(const std::string &szParamFilename)
{
    setVBOUsageOnPropertyProtos(true);

    _oPathHandler.clearPathList();
    _oPathHandler.clearBaseFile();

    _oPathHandler.push_frontCurrentDir();

    std::string szParamFileResolved = 
        _oPathHandler.findFile(szParamFilename.c_str());

    if(szParamFileResolved.empty() == true)
    {
        fprintf(stderr, "Could not find param file %s\n", 
                szParamFilename.c_str());

        return;
    }

    _oPathHandler.setBaseFile(szParamFileResolved.c_str());

    OSG::SceneFileHandler::the()->setPathHandler(&_oPathHandler);

    std::vector<std::string> vParams;

    scanParamFile(szParamFileResolved.c_str(), vParams);
    
    scanPreSystem(vParams);

    std::string szSystemFile         = vParams[0];

    std::string szSystemFileResolved = 
        _oPathHandler.findFile(szSystemFile.c_str());

    if(szSystemFileResolved.empty() == true)
    {
        fprintf(stderr, "Could not find system file %s\n",
                szSystemFile.c_str());

        return;
    }

    readOSGFile(szSystemFileResolved,
                boost::bind(&ComplexSceneManager::resolveStatic, _1));

    _vStaticGlobals.clear();

    if(OSG::ComplexSceneManager::the() == NULL)
    {
        fprintf(stderr, "Error could not find any complex scenemanager\n");
        return;
    }

    OSG::SceneFileHandler::the()->setGlobalResolver(
        boost::bind(&ComplexSceneManager::resolve, _the.get(), _1));

    OSG::ComplexSceneManager::the()->init(vParams);
    
    OSG::ComplexSceneManager::the()->run();
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ComplexSceneManager::ComplexSceneManager(void) :
     Inherited (),
    _fMainloop (),
    _oKeyHelper()
{
}

ComplexSceneManager::ComplexSceneManager(const ComplexSceneManager &source) :
     Inherited (source),
    _fMainloop (      ),
    _oKeyHelper(      )
    
{
}

ComplexSceneManager::~ComplexSceneManager(void)
{
}

FieldContainer *ComplexSceneManager::resolve(const Char8 *szName)
{
    return this->findNamedComponent(szName);
}

void ComplexSceneManager::addGlobals(const std::string &filename)
{
    if(_sfDrawManager.getValue() == NULL)
    {
        return;
    }

    std::string szFilenameResolved = _oPathHandler.findFile(filename.c_str());

    if(szFilenameResolved.empty() == true)
    {
        return;
    }

    FieldContainerUnrecPtr pRes = 
        readOSGFile(szFilenameResolved,
                    boost::bind(&ComplexSceneManager::resolve, this, _1));

    if(pRes == NULL)
        return;

    ContainerCollectionUnrecPtr pColl = 
        dynamic_pointer_cast<ContainerCollection>(pRes);

    if(pColl == NULL)
        return;

    MFUnrecFieldContainerPtr::const_iterator fIt  = 
        pColl->getMFContainers()->begin();

    MFUnrecFieldContainerPtr::const_iterator fEnd = 
        pColl->getMFContainers()->end();

    while(fIt != fEnd)
    {
        this->pushToGlobals(*fIt);
        ++fIt;
    }   
}

void ComplexSceneManager::addData(const std::string &filename)
{
    Node *pModelRoot = findNode("ModelRoot");

    if(pModelRoot == NULL)
    {
        return;
    }

    std::string szFilenameResolved = _oPathHandler.findFile(filename.c_str());

    if(szFilenameResolved.empty() == true)
    {
        fprintf(stderr, "Could not find data file %s\n",
                filename.c_str());

        return;
    }

    _oPathHandler.pushState();

    _oPathHandler.setBaseFile(szFilenameResolved.c_str());

    fprintf(stderr, "loading data %s ...\n",
            filename.c_str());

    NodeUnrecPtr pFile = 
        OSG::SceneFileHandler::the()->read(
            szFilenameResolved.c_str(), 
            NULL,
            boost::bind(&ComplexSceneManager::resolve, this, _1),
            true);

    _oPathHandler.popState();

    if(pFile != NULL)
    {
        pModelRoot->addChild(pFile);
    }
}

Node *ComplexSceneManager::findNode(const std::string &filename) const
{
    MFUnrecFieldContainerPtr::const_iterator gIt  = _mfGlobals.begin();
    MFUnrecFieldContainerPtr::const_iterator gEnd = _mfGlobals.end  ();

    Node                *pNode       = NULL;
    Node                *returnValue = NULL;

    while(gIt != gEnd)
    {
        pNode = dynamic_cast<Node *>(*gIt);

        if(pNode != NULL)
        {
            NodeFinder oFinder;

            oFinder._szRefName = filename;

            traverse(pNode, boost::bind(&NodeFinder::enter, &oFinder, _1));

            if(oFinder._pResult != NULL)
            {
                returnValue = oFinder._pResult;
                break;
            }
        }

        ++gIt;
    }

    return returnValue;
}

FieldContainerTransitPtr ComplexSceneManager::readOSGFile(
    const std::string &filename,
          Resolver     resolver)
{
    FieldContainerTransitPtr returnValue(NULL);

    _oPathHandler.pushState();

    _oPathHandler.setBaseFile(filename.c_str());

    ImageFileHandler::the()->setPathHandler(&_oPathHandler);

    fprintf(stderr, "loading osg file %s ...\n",
            filename.c_str());

    returnValue = OSG::OSGSceneFileType::the().readContainer(
        filename.c_str(),
        resolver);

    ImageFileHandler::the()->setPathHandler(NULL);

    _oPathHandler.popState();

    return returnValue;
}

FieldContainer *ComplexSceneManager::findNamedComponent(
    const Char8 *szName) const
{
    MFUnrecFieldContainerPtr::const_iterator gIt  = _mfGlobals.begin();
    MFUnrecFieldContainerPtr::const_iterator gEnd = _mfGlobals.end  ();

          AttachmentContainer *pAttCnt     = NULL;
          Node                *pNode       = NULL;
    const Char8               *szTmpName   = NULL;

    if(_sfDrawManager.getValue() != NULL)
    {
        szTmpName = OSG::getName(_sfDrawManager.getValue());

        if(szTmpName != NULL && osgStringCmp(szTmpName, szName) == 0)
        {
            return _sfDrawManager.getValue();
        }

         FieldContainer *tmpVal = 
             _sfDrawManager.getValue()->findNamedComponent(szName);

         if(tmpVal != NULL)
             return tmpVal;
    }

    while(gIt != gEnd)
    {
        pNode = dynamic_cast<Node *>(*gIt);

        if(pNode != NULL)
        {
            ElementFinder oFinder;

            oFinder._szRefName = szName;

            traverse(pNode, boost::bind(&ElementFinder::enter, &oFinder, _1));

            if(oFinder._pResult != NULL)
            {
                return oFinder._pResult;
            }
         }
        
        pAttCnt = dynamic_cast<AttachmentContainer *>(*gIt);

        if(pAttCnt != NULL)
        {
            szTmpName = OSG::getName(pAttCnt);
           
            if(szTmpName != NULL && osgStringCmp(szTmpName, szName) == 0)
            {
                return pAttCnt;
            }
            else
            {
                FieldContainer *tmpVal = pAttCnt->findNamedComponent(szName);
                
                if(tmpVal != NULL)
                    return tmpVal;
            }
        }

        ++gIt;
    }

    return NULL;
}


/*----------------------------- class specific ----------------------------*/

void ComplexSceneManager::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void ComplexSceneManager::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump ComplexSceneManager NI" << std::endl;
}

void ComplexSceneManager::onCreate(const ComplexSceneManager *source)
{
    Inherited::onCreate(source);

    // Don't add the prototype instances to the list
    if(GlobalSystemState != Running)
        return;

    if(_the != NULL)
    {
        fprintf(stderr, "WARNING ADDING SECOND COMPLEX SCENE MANAGER,"
                " WILL SELF DESTRUCT IN 45 SECONDS");
    }

    _the = this;

    std::vector<FieldContainerUnrecPtr>::const_iterator gIt  = 
        _vStaticGlobals.begin();
    
    std::vector<FieldContainerUnrecPtr>::const_iterator gEnd = 
        _vStaticGlobals.end  ();

    while(gIt != gEnd)
    {
        this->pushToGlobals(*gIt);
        ++gIt;
    }   

#if 0
    SensorTaskUnrecPtr pSensorTask = SensorTask::create();

    setSensorTask(pSensorTask);
#endif
}

bool ComplexSceneManager::init(int argc, char **argv)
{
    _oPathHandler.clearPathList();
    _oPathHandler.clearBaseFile();

    _oPathHandler.push_frontCurrentDir();

    std::vector<std::string> vParams;
    std::string              szTmp;

    for(Int32 i = 1; i < argc; ++i)
    {
        szTmp = argv[i];

        vParams.push_back(szTmp);
    }

    scanPreSystem(vParams);

    return init(vParams);
}

bool ComplexSceneManager::init(const std::vector<std::string> &vParams)
{
    bool returnValue = true;

    bool bDoData = false;

    for(UInt32 i = 1; i < vParams.size(); ++i)
    {
        if(vParams[i][0] == '-' && vParams[i][1] == '-')
        {
            if(vParams[i][2] == 'd' && vParams[i][3] == 'a' && 
               vParams[i][4] == 't' && vParams[i][5] == 'a')
            {
                bDoData = true;
            }
            else if(vParams[i][2] == 'g' && vParams[i][3] == 'l' && 
                    vParams[i][4] == 'o' && vParams[i][5] == 'b' &&
                    vParams[i][6] == 'a' && vParams[i][7] == 'l')
            {
                bDoData = false;
            }
            else
            {
                fprintf(stderr, "Unknow option %s\n", vParams[i].c_str());
                return false;
            }
               
        }
        else
        {
            if(bDoData == true)
            {
                addData(vParams[i]);
            }
            else
            {
                addGlobals(vParams[i]);
            }
        }
    }

    if(_sfDrawManager.getValue() == NULL)
    {
        return false;
    }

    commitChanges();

    returnValue = _sfDrawManager.getValue()->init();

    if(returnValue == true && FrameHandler::the() != NULL)
    {
        returnValue &= FrameHandler::the()->init();
    }

    return returnValue;
}

void ComplexSceneManager::terminate(void)
{
    _vStaticGlobals.clear();

    _the->shutdown();

    _the = NULL;
}

void ComplexSceneManager::shutdown(void)
{
    if(FrameHandler::the() != NULL)
    {
        FrameHandler::the()->shutdown();
    }

    this->clearGlobals();

    if(_sfDrawManager.getValue() != NULL)
    {
        _sfDrawManager.getValue()->shutdown();
    }


    this->setDrawManager(NULL);
//    this->setSensorTask (NULL);
}

void ComplexSceneManager::setMainloop(MainLoopFuncF fMainloop)
{
    _fMainloop = fMainloop;
}

void ComplexSceneManager::run(void)
{
    if(_fMainloop)
    {
        _fMainloop();
    }
    else
    {
        FWARNING(("ComplexSceneManager: no mainloop exiting\n"));
    }

    osgExit(); 
}

void ComplexSceneManager::frame(void)
{
#if 0
    setCurrTime(getSystemTime());
    
    if(osgAbs(_sfStartTime.getValue()) < 0.00001)
    {
        setStartTime(_sfCurrTime.getValue());
        
        setLastTime(0.f);
    }
    
    _sfCurrTime.getValue() -= _sfStartTime.getValue();

    if(_sfPaused.getValue() == false)
    {
        SFTime *pSFTimeStamp = editSFTimeStamp();

        if(_sfConstantTime.getValue() == true)
        {
            pSFTimeStamp->getValue() += _sfConstantTimeStep.getValue();

            if(pSFTimeStamp->getValue() < 0.)
                pSFTimeStamp->setValue(0.0);
        }
        else
        {
            pSFTimeStamp->getValue() += 
                (_sfCurrTime.getValue() - _sfLastTime.getValue()) * 
                _sfTimeScale.getValue();
            
            if(pSFTimeStamp->getValue() < 0.)
                pSFTimeStamp->setValue(0.0);
        }
    }
    
    setLastTime(_sfCurrTime.getValue());

    SystemTime = _sfTimeStamp.getValue();

    ++(editSFFrameCount()->getValue());

    if(_sfSensorTask.getValue() != NULL)
    {
        _sfSensorTask.getValue()->frame(_sfTimeStamp.getValue (), 
                                        _sfFrameCount.getValue());
    }
#endif

    if(_sfDumpFrameStart.getValue() == true)
    {
        fprintf(stderr, "=================================================\n");
        fprintf(stderr, "Render Frame\n");
        fprintf(stderr, "=================================================\n");
    }

    FrameHandler::the()->frame();

    SystemTime = FrameHandler::the()->getTimeStamp();

    commitChanges();

    if(_sfDrawManager.getValue() != NULL)
    {
        _sfDrawManager.getValue()->frame(FrameHandler::the()->getTimeStamp(), 
                                         FrameHandler::the()->getFrameCount());
    }
}

void ComplexSceneManager::resetScene(void)
{
    MFUnrecFieldContainerPtr::const_iterator gIt  = _mfGlobals.begin();
    MFUnrecFieldContainerPtr::const_iterator gEnd = _mfGlobals.end  ();

    CSMResetInterface *pIf = NULL;

    for(; gIt != gEnd; ++gIt)
    {
        pIf = dynamic_cast<CSMResetInterface *>(*gIt);
        
        if(pIf != NULL)
        {
            fprintf(stderr, "found if %p\n", pIf);

            pIf->reset();
        }
    }
}

void ComplexSceneManager::key(Int32 x,
                              Int32 y,
                              Int32 iState,
                              Char8 cKey  )
{
    _oKeyHelper.update(x, y, iState, cKey);
}

void ComplexSceneManager::updateKeySensor(KeySensor *pSensor)
{
    _oKeyHelper.updateSensors(pSensor);
}

void ComplexSceneManager::removeKeySensor(KeySensor *pSensor)
{
    _oKeyHelper.removeSensor(pSensor);
}

OSG_END_NAMESPACE
