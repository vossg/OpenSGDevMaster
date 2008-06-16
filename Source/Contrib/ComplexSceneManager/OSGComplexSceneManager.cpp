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

#include <OSGConfig.h>

#include "OSGComplexSceneManager.h"
#include "OSGOSGSceneFileType.h"
#include "OSGContainerCollection.h"
#include "OSGSceneFileHandler.h"
#include "OSGNameAttachment.h"
#include "OSGAction.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGComplexSceneManagerBase.cpp file.
// To modify it, please change the .fcd file (OSGComplexSceneManager.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

ComplexSceneManagerUnrecPtr ComplexSceneManager::_the = NULL;

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

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ComplexSceneManager::ComplexSceneManager(void) :
     Inherited(),
    _fMainloop()
{
}

ComplexSceneManager::ComplexSceneManager(const ComplexSceneManager &source) :
     Inherited(source),
    _fMainloop(      )
    
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

    FieldContainerUnrecPtr pRes =
        OSGSceneFileType::the().readContainer(
            filename.c_str(),
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

    NodeUnrecPtr pFile = 
        OSG::SceneFileHandler::the()->read(
            filename.c_str(), 
            NULL,
            boost::bind(&ComplexSceneManager::resolve, this, _1));

    if(pFile != NULL)
    {
        pModelRoot->addChild(pFile);
    }
}

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
            NodeFinder oFinder;

            oFinder._szRefName = szName;

            traverse(pNode, boost::bind(&NodeFinder::enter, &oFinder, _1));

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
}

bool ComplexSceneManager::init(int argc, char **argv)
{
    bool returnValue = true;

    bool bDoData = false;

    for(UInt32 i = 2; i < argc; ++i)
    {
        if(argv[i][0] == '-' && argv[i][1] == '-')
        {
            fprintf(stderr, "Switch option %s\n", argv[i]);

            if(argv[i][2] == 'd' && argv[i][3] == 'a' && argv[i][4] == 't' &&
               argv[i][5] == 'a')
            {
                bDoData = true;
            }
            else if(argv[i][2] == 'g' && argv[i][3] == 'l' && 
                    argv[i][4] == 'o' && argv[i][5] == 'b' &&
                    argv[i][6] == 'a' && argv[i][7] == 'l')
            {
                bDoData = false;
            }
            else
            {
                fprintf(stderr, "Unknow option %s\n", argv[i]);
                return false;
            }
               
        }
        else
        {
            if(bDoData == true)
            {
                fprintf(stderr, "Adding Data %s\n", argv[i]);
                addData(argv[i]);
            }
            else
            {
                fprintf(stderr, "Adding Globals %s\n", argv[i]);
                addGlobals(argv[i]);
            }
        }
    }

    if(_sfDrawManager.getValue() == NULL)
    {
        return false;
    }

    returnValue = _sfDrawManager.getValue()->init();

    return returnValue;
}

void ComplexSceneManager::terminate(void)
{
    _the = NULL;
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

    osgExit(); 
}

void ComplexSceneManager::frame(void)
{
    if(_sfDrawManager.getValue() != NULL)
    {
        _sfDrawManager.getValue()->frame(0., 0);
    }
}

void ComplexSceneManager::key(Int32 x,
                              Int32 y,
                              Int32 iState,
                              Char8 cKey  )
{
}

OSG_END_NAMESPACE
