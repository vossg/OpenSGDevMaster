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

#include "OSGDrawer.h"
#include "OSGRenderAction.h"
#include "OSGNameAttachment.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGDrawerBase.cpp file.
// To modify it, please change the .fcd file (OSGDrawer.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void Drawer::initMethod(InitPhase ePhase)
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

Drawer::Drawer(void) :
     Inherited(    ),
    _pAction  (NULL)
{
}

Drawer::Drawer(const Drawer &source) :
     Inherited(source),
    _pAction  (NULL  )
{
}

Drawer::~Drawer(void)
{
    delete _pAction;
}

/*----------------------------- class specific ----------------------------*/

void Drawer::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void Drawer::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump Drawer NI" << std::endl;
}

bool Drawer::init(void)
{
    bool returnValue = true;

    MFUnrecCSMWindowPtr::const_iterator wIt  = _mfWindows.begin();
    MFUnrecCSMWindowPtr::const_iterator wEnd = _mfWindows.end  ();

    while(wIt != wEnd)
    {
        returnValue = (*wIt)->init();

        if(returnValue == false)
            break;

        ++wIt;
    };

    _pAction = RenderAction::create();

    return returnValue;
}

void Drawer::frame(Time oTime, UInt32 uiFrame)
{
    MFUnrecCSMWindowPtr::const_iterator winIt  = _mfWindows.begin();
    MFUnrecCSMWindowPtr::const_iterator winEnd = _mfWindows.end  ();

    while(winIt != winEnd)
    {
        (*winIt)->render(_pAction);
        
        ++winIt;
    }
}

FieldContainer *Drawer::findNamedComponent(const Char8 *szName) const
{
    MFUnrecCSMWindowPtr::const_iterator winIt  = _mfWindows.begin();
    MFUnrecCSMWindowPtr::const_iterator winEnd = _mfWindows.end  ();

    const Char8               *szTmpName   = NULL;

    while(winIt != winEnd)
    {
        szTmpName = OSG::getName(*winIt);
            
        if(szTmpName != NULL && osgStringCmp(szTmpName, szName) == 0)
        {
            return *winIt;
        }
        else
        {
/*
            FieldContainer *tmpVal = (*drawerIt)->findNamedComponent(szName);
                
            if(tmpVal != NULL)
                return tmpVal;
 */
        }
        
        ++winIt;
    }
    
    return NULL;
}

OSG_END_NAMESPACE
