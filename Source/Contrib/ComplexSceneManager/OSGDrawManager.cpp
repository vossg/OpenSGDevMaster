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

#include <OSGConfig.h>

#include "OSGDrawManager.h"
#include "OSGNameAttachment.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGDrawManagerBase.cpp file.
// To modify it, please change the .fcd file (OSGDrawManager.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void DrawManager::initMethod(InitPhase ePhase)
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

DrawManager::DrawManager(void) :
    Inherited()
{
}

DrawManager::DrawManager(const DrawManager &source) :
    Inherited(source)
{
}

DrawManager::~DrawManager(void)
{
}

/*----------------------------- class specific ----------------------------*/

void DrawManager::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void DrawManager::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump DrawManager NI" << std::endl;
}

bool DrawManager::init(void)
{
    bool returnValue = true;

    MFUnrecDrawerPtr::const_iterator dIt  = getMFDrawer()->begin();
    MFUnrecDrawerPtr::const_iterator dEnd = getMFDrawer()->end  ();

    while(dIt != dEnd)
    {
        returnValue = (*dIt)->init();

        if(returnValue == false)
            break;

        ++dIt;
    }

    return returnValue;
}

void DrawManager::frame(Time oTime, UInt32 uiFrame)
{
    commitChanges();

#ifdef OSG_CSM_PAR
    if(_sfParallel.getValue() == true)
    {
        _pSyncBarrier->enter(_uiSyncCount);
        _pSyncBarrier->enter(_uiSyncCount);

        _pOSGThread->getChangeList()->clear();
    }
    else
#endif
    {
        MFUnrecDrawerPtr::const_iterator drawerIt  = getMFDrawer()->begin();
        MFUnrecDrawerPtr::const_iterator drawerEnd = getMFDrawer()->end  ();

        while(drawerIt != drawerEnd)
        {
            (*drawerIt)->frame(oTime, uiFrame);
                        
            ++drawerIt;
        }
    }
}

FieldContainer *DrawManager::findNamedComponent(const Char8 *szName) const
{
    MFUnrecDrawerPtr::const_iterator drawerIt  = _mfDrawer.begin();
    MFUnrecDrawerPtr::const_iterator drawerEnd = _mfDrawer.end  ();

    const Char8               *szTmpName   = NULL;

    while(drawerIt != drawerEnd)
    {
        szTmpName = OSG::getName(*drawerIt);
            
        if(szTmpName != NULL && osgStringCmp(szTmpName, szName) == 0)
        {
            return *drawerIt;
        }
        else
        {
            FieldContainer *tmpVal = (*drawerIt)->findNamedComponent(szName);
                
            if(tmpVal != NULL)
                return tmpVal;
        }
        
        ++drawerIt;
    }
    
    return NULL;
}

OSG_END_NAMESPACE
