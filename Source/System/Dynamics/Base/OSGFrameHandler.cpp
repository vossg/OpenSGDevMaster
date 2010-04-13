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
     Inherited                (),
    _mfFrameTasks             (),
    _mfUninitializedFrameTasks()
{
}

FrameHandler::FrameHandler(const FrameHandler &source) :
     Inherited                (source),
    _mfFrameTasks             (      ),
    _mfUninitializedFrameTasks(      )
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

void FrameHandler::addTask(FrameTaskInterface *pTask)
{
    if(pTask == NULL)
        return;

    this->pushToFrameTasks             (pTask);
    this->pushToUninitializedFrameTasks(pTask);
}

void FrameHandler::removeTask(FrameTaskInterface *pTask)
{
    if(pTask != NULL)
    {
        pTask->shutdown();
        
        this->removeObjFromFrameTasks             (pTask);
        this->removeObjFromUninitializedFrameTasks(pTask);
    }
}

bool FrameHandler::init(void)
{
    bool returnValue = true;

    InterfaceStoreConstIt tIt  = this->getMFUninitializedFrameTasks()->begin();
    InterfaceStoreConstIt tEnd = this->getMFUninitializedFrameTasks()->end  ();

    while(tIt != tEnd)
    {
        returnValue &= (*tIt)->init();
        
        ++tIt;
    }

    this->clearUninitializedFrameTasks();

    return returnValue;
}

void FrameHandler::frame(Time frameTime)
{
    if(_mfUninitializedFrameTasks.size() != 0)
    {
        this->init();
    }

    setCurrTime(frameTime);
    
    if(_sfStartTime.getValue() < 0.0)
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

    callTasks();
}

void FrameHandler::frame(void)
{
    frame(getSystemTime());
}

void FrameHandler::shutdown(void)
{
    InterfaceStoreConstIt tIt  = getMFFrameTasks()->begin();
    InterfaceStoreConstIt tEnd = getMFFrameTasks()->end  ();

    while(tIt != tEnd)
    {
        (*tIt)->shutdown();
        
        ++tIt;
    }
}

void
FrameHandler::callTasks(void)
{
    Int32                 currPrio = TypeTraits<Int32>::getMin();
    InterfaceStoreConstIt tIt      = getMFFrameTasks()->begin();
    InterfaceStoreConstIt tEnd     = getMFFrameTasks()->end  ();

    while(tIt != tEnd)
    {
        if((*tIt)->getPriority() > currPrio)
        {
            currPrio = (*tIt)->getPriority();
            commitChanges();
        }

        (*tIt)->frame(_sfTimeStamp.getValue(), _sfFrameCount.getValue());
        
        ++tIt;
    }
}

//! Get the FrameHandler::_mfFrameTasks field.
const FrameHandler::InterfaceStore *FrameHandler::getMFFrameTasks(void) const
{
    return &_mfFrameTasks;
}

//! Get the FrameHandler::_mfUninitializedFrameTasks field.
const FrameHandler::InterfaceStore *
    FrameHandler::getMFUninitializedFrameTasks(void) const
{
    return &_mfUninitializedFrameTasks;
}

void FrameHandler::pushToFrameTasks(FrameTaskInterface * const value)
{
    InterfaceStoreIt tIt = std::lower_bound(_mfFrameTasks.begin(),
                                            _mfFrameTasks.end  (), value,
                                            FrameTaskLess()              );

    _mfFrameTasks.insert(tIt, value);
}

void FrameHandler::pushToUninitializedFrameTasks(
    FrameTaskInterface * const value)
{
    _mfUninitializedFrameTasks.push_back(value);
}


void FrameHandler::removeObjFromFrameTasks(FrameTaskInterface * const value)
{
    InterfaceStoreIt it = std::find(_mfFrameTasks.begin(), 
                                    _mfFrameTasks.end  (), value);

    if(it != _mfFrameTasks.end())
    {
        _mfFrameTasks.erase(it);
    }
}

void FrameHandler::removeObjFromUninitializedFrameTasks(
    FrameTaskInterface * const value)
{
    InterfaceStoreIt it = std::find(_mfUninitializedFrameTasks.begin(), 
                                    _mfUninitializedFrameTasks.end  (), value);

    if(it != _mfUninitializedFrameTasks.end())
    {
        _mfUninitializedFrameTasks.erase(it);
    }
}

void FrameHandler::clearFrameTasks(void)
{
    _mfFrameTasks.clear();
}

void FrameHandler::clearUninitializedFrameTasks(void)
{
    _mfUninitializedFrameTasks.clear();
}

void FrameHandler::resolveLinks(void)
{
    Inherited::resolveLinks();

    static_cast<FrameHandler *>(this)->clearFrameTasks();
    static_cast<FrameHandler *>(this)->clearUninitializedFrameTasks();
}

OSG_END_NAMESPACE
