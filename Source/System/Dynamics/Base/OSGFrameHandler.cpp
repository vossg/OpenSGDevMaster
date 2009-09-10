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

#include "OSGFrameHandler.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGFrameHandlerBase.cpp file.
// To modify it, please change the .fcd file (OSGFrameHandler.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

bool                 FrameHandler::_bRegistersInstanceRelease = false;
FrameHandlerUnrecPtr FrameHandler::_pGlobalInstance           = NULL;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void FrameHandler::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}

FrameHandler *FrameHandler::the(void)
{
    if(GlobalSystemState != Running)
        return NULL;

    if(_pGlobalInstance == NULL)
    {
        FrameHandlerUnrecPtr pHandler = FrameHandler::create();

        setGlobalInstance(pHandler);
    }

    return _pGlobalInstance;
}

void FrameHandler::setGlobalInstance(FrameHandler *pHandler)
{
    if(_bRegistersInstanceRelease == false)
    {
        _bRegistersInstanceRelease = true;

        addPreFactoryExitFunction(&FrameHandler::releaseGlobalInstance);
    }

    _pGlobalInstance = pHandler;
}

bool FrameHandler::releaseGlobalInstance(void)
{
    _pGlobalInstance = NULL;

    return true;
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

FrameHandler::FrameHandler(void) :
    Inherited()
{
}

FrameHandler::FrameHandler(const FrameHandler &source) :
    Inherited(source)
{
}

FrameHandler::~FrameHandler(void)
{
}

/*----------------------------- class specific ----------------------------*/

void FrameHandler::changed(ConstFieldMaskArg whichField, 
                           UInt32            origin,
                           BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void FrameHandler::dump(      UInt32    ,
                        const BitVector ) const
{
    SLOG << "Dump FrameHandler NI" << std::endl;
}

void FrameHandler::addTask(FrameTask *pTask)
{
    if(pTask == NULL)
        return;

    Inherited::pushToFrameTasks             (pTask);
    Inherited::pushToUninitializedFrameTasks(pTask);
}

void FrameHandler::removeTask(FrameTask *pTask)
{
    if(pTask != NULL)
    {
        pTask->shutdown();

        Inherited::removeObjFromFrameTasks             (pTask);
        Inherited::removeObjFromUninitializedFrameTasks(pTask);
    }
}

bool FrameHandler::init(void)
{
    bool returnValue = true;

    MFUncountedFrameTaskPtr::const_iterator tIt  = 
        getMFUninitializedFrameTasks()->begin();
    MFUncountedFrameTaskPtr::const_iterator tEnd = 
        getMFUninitializedFrameTasks()->end  ();

    while(tIt != tEnd)
    {
        returnValue &= (*tIt)->init();
        
        ++tIt;
    }

    Inherited::clearUninitializedFrameTasks();

    return returnValue;
}

void FrameHandler::frame(void)
{
    if(_mfUninitializedFrameTasks.size() != 0)
    {
        this->init();
    }

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

    ++(editSFFrameCount()->getValue());

#if 0
    if(_sfSensorTask.getValue() != NULL)
    {
        _sfSensorTask.getValue()->frame(_sfTimeStamp.getValue (), 
                                        _sfFrameCount.getValue());
    }
#endif

    MFUncountedFrameTaskPtr::const_iterator tIt  = getMFFrameTasks()->begin();
    MFUncountedFrameTaskPtr::const_iterator tEnd = getMFFrameTasks()->end  ();

    while(tIt != tEnd)
    {
        (*tIt)->frame(_sfTimeStamp.getValue(), _sfFrameCount.getValue());
        
        ++tIt;
    }
    
}

void FrameHandler::shutdown(void)
{
    MFUncountedFrameTaskPtr::const_iterator tIt  = getMFFrameTasks()->begin();
    MFUncountedFrameTaskPtr::const_iterator tEnd = getMFFrameTasks()->end  ();

    while(tIt != tEnd)
    {
        (*tIt)->shutdown();
        
        ++tIt;
    }
}

OSG_END_NAMESPACE
