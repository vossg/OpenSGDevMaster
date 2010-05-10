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

#include "OSGHardwareContext.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGHardwareContextBase.cpp file.
// To modify it, please change the .fcd file (OSGHardwareContext.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void HardwareContext::initMethod(InitPhase ePhase)
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

HardwareContext::HardwareContext(void) :
     Inherited     (    ),
    _pContextThread(NULL),
    _uiInitState   (0   )
{
}

HardwareContext::HardwareContext(const HardwareContext &source) :
     Inherited     (source),
    _pContextThread(NULL  ),
    _uiInitState   (0     )
{
}

HardwareContext::~HardwareContext(void)
{
}

void HardwareContext::setOpenGLInit(void)
{
    _uiInitState |= OpenGLInitialized;
}

void HardwareContext::setCudaInit(void)
{
    _uiInitState |= CudaInitialized;
}

void HardwareContext::onCreate(const HardwareContext *source)
{
    Inherited::onCreate(source);
}

void HardwareContext::onCreateAspect(const HardwareContext *createAspect,
                                     const HardwareContext *source      )
{
    Inherited::onCreateAspect(createAspect, source);

    // Don't add the prototype instances to the list
    if(GlobalSystemState != Running)
        return;

    if(createAspect != NULL)
    {
        _pContextThread = createAspect->_pContextThread;
    }
}

void HardwareContext::onDestroy(UInt32 uiContainerId)
{
    Inherited::onDestroy(uiContainerId);

    _pContextThread = NULL;
}

void HardwareContext::onDestroyAspect(UInt32 uiContainerId,
                                      UInt32 uiAspect     )
{
    Inherited::onDestroyAspect(uiContainerId, uiAspect);
}

/*----------------------------- class specific ----------------------------*/

void HardwareContext::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void HardwareContext::dump(      UInt32    ,
                           const BitVector ) const
{
    SLOG << "Dump HardwareContext NI" << std::endl;
}

void HardwareContext::clearData(FieldContainer    *pContainer, 
                                ConstFieldMaskArg  whichField,
                                Int32              iSlotId   )
{
    if(iSlotId < 0)
        return;

    if(_mfData.size() > static_cast<UInt32>(iSlotId))
    {
        if(_mfData[iSlotId] != NULL)
            _mfData[iSlotId]->releaseResources(this);
    }

    Inherited::clearData(pContainer, whichField, iSlotId);
}

OSG_END_NAMESPACE
