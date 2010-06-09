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

#include "OSGCSMClusterWindow.h"

#include "OSGBalancedMultiWindow.h"
#include "OSGSortFirstWindow.h"
#include "OSGSortLastWindow.h"

#include "OSGCSMMultiWinOptions.h"
#include "OSGCSMSortFirstWinOptions.h"

#include "OSGNameAttachment.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGCSMClusterWindowBase.cpp file.
// To modify it, please change the .fcd file (OSGCSMClusterWindow.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

bool CSMClusterWindow::_bRun = false;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void CSMClusterWindow::initMethod(InitPhase ePhase)
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

CSMClusterWindow::CSMClusterWindow(void) :
     Inherited     (    ),
    _pClusterWindow(NULL)
{
}

CSMClusterWindow::CSMClusterWindow(const CSMClusterWindow &source) :
     Inherited     (source),
    _pClusterWindow(NULL  )
{
}

CSMClusterWindow::~CSMClusterWindow(void)
{
}

bool CSMClusterWindow::init(void)
{
    MultiDisplayWindowUnrecPtr  pCMDWindow = NULL;
    BalancedMultiWindowUnrecPtr pCBMWindow = NULL;
    SortFirstWindowUnrecPtr     pCSFWindow = NULL;
    SortLastWindowUnrecPtr      pCSLWindow = NULL;
  
    if(_sfClusterMode.getValue() == "Multi")
    {
        pCMDWindow = MultiDisplayWindow::create();

        _pWindow        = pCMDWindow;
        _pClusterWindow = pCMDWindow;
    }
    else if(_sfClusterMode.getValue() == "Balanced")
    {
        pCBMWindow = BalancedMultiWindow::create();

        pCMDWindow = pCBMWindow;

        _pWindow        = pCBMWindow;
        _pClusterWindow = pCBMWindow;
    }
    else if(_sfClusterMode.getValue() == "SortFirst")
    {
        pCSFWindow = SortFirstWindow::create();

        _pWindow        = pCSFWindow;
        _pClusterWindow = pCSFWindow;
    }
    else if(_sfClusterMode.getValue() == "SortLast")
    {
        pCSLWindow = SortLastWindow::create();

        _pWindow        = pCSLWindow;
        _pClusterWindow = pCSLWindow;
    }
    else
    {
        fprintf(stderr, "Unknown cluster mode %s\n",
                _sfClusterMode.getValue().c_str());
    }

    MFString::const_iterator serverIt  = this->getMFServers()->begin();
    MFString::const_iterator serverEnd = this->getMFServers()->end  ();

    UInt32 uiNumServer = 0;

    while(serverIt != serverEnd)
    {
        fprintf(stderr, "Connecting to %s\n", serverIt->c_str());
        
        _pClusterWindow->editMFServers()->push_back(serverIt->c_str());
        
        ++uiNumServer;
        ++serverIt;
    }

    _pClusterWindow->editMFServerIds()->setValues(*(this->getMFServerIds()));

    _pClusterWindow->setSize(UInt16(this->getXSize()), 
                             UInt16(this->getYSize()));

    _pClusterWindow->setConnectionType(this->getConnectionType());

    if(this->getSFComposer()->getValue() != NULL)
    {
        _pClusterWindow->setComposer(this->getSFComposer()->getValue());
    }

    if(pCMDWindow != NULL)
    {
        if(uiNumServer != 0)
        {
            pCMDWindow->setHServers(uiNumServer / this->getServerRows());
            
            pCMDWindow->setVServers(this->getServerRows());
        }
        else
        {
            pCMDWindow->setHServers(1);
            pCMDWindow->setVServers(1);
        }
        
        CSMMultiWinOptions *pOpts = 
            dynamic_cast<CSMMultiWinOptions *>(this->getOptions());

        if(pOpts != NULL)
        {
            pCMDWindow->setXOverlap(pOpts->getXOverlap());
            pCMDWindow->setYOverlap(pOpts->getYOverlap());

            pCMDWindow->setManageClientViewports(
                pOpts->getManageClientViewports());
        }
    }


    if(pCBMWindow != NULL)
    {
        CSMMultiWinOptions *pOpts = 
            dynamic_cast<CSMMultiWinOptions *>(this->getOptions());

        if(pOpts != NULL)
        {
            pCBMWindow->setBalance      (pOpts->getBalance      ());
            pCBMWindow->setBestCut      (pOpts->getBestCut      ());
            pCBMWindow->setShowBalancing(pOpts->getShowBalancing());
        }
    }

    if(pCSFWindow != NULL)
    {
        CSMSortFirstWinOptions *pOpts = 
            dynamic_cast<CSMSortFirstWinOptions *>(this->getOptions());

        if(pOpts != NULL)
        {
            pCSFWindow->setCompression        (pOpts->getCompression        ());
            pCSFWindow->setCompose            (pOpts->getCompose            ());
            pCSFWindow->setSubtileSize        (pOpts->getSubtileSize        ());
            pCSFWindow->setUseFaceDistribution(pOpts->getUseFaceDistribution());
        }
    }



    if(_sfClientWindow.getValue() != NULL)
    {
        _sfClientWindow.getValue()->init();

        if(this->getRenderClient() == true)
        {
            _pClusterWindow->setClientWindow(
                _sfClientWindow.getValue()->getWindow());
        }
    }

    _pClusterWindow->init();

    Inherited::init();

    return true;
}

FieldContainer *CSMClusterWindow::findNamedComponent(const Char8 *szName) const
{
    if(_sfClientWindow.getValue() != NULL)
    {
        const Char8 *szTmpName   = NULL;

        szTmpName = OSG::getName(_sfClientWindow.getValue());

        if(szTmpName != NULL  && osgStringCmp(szTmpName, szName) == 0)
        {
            return _sfClientWindow.getValue();
        }
    }

    return NULL;
}

/*----------------------------- class specific ----------------------------*/

void CSMClusterWindow::changed(ConstFieldMaskArg whichField, 
                               UInt32            origin,
                               BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void CSMClusterWindow::dump(      UInt32    ,
                            const BitVector ) const
{
    SLOG << "Dump CSMClusterWindow NI" << std::endl;
}

void CSMClusterWindow::terminateGLContext(void)
{
}

OSG_END_NAMESPACE
