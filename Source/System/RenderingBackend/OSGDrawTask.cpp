/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#include "OSGDrawTask.h"

#include "OSGMField.ins"

OSG_BEGIN_NAMESPACE

/*! \class OSG::DrawTask
    \ingroup GrpSystemRenderingBackend
 */

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

DrawTask::DrawTask(UInt32 uiTaskType) :
    Inherited(uiTaskType)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

DrawTask::~DrawTask(void)
{
}

DataType FieldTraits<DrawTaskRefPtr, 0>::_type("DrawTaskRefPtr", NULL);

OSG_FIELDTRAITS_GETTYPE_NS(DrawTaskRefPtr, 0)

OSG_FIELD_DLLEXPORT_DEF1(MField, DrawTaskRefPtr);


/*! \class OSG::DrawTask
    \ingroup GrpSystemRenderingBackend
 */

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

BlockingDrawTask::BlockingDrawTask(UInt32 uiTaskType) :
     Inherited     (uiTaskType),
    _bBarrierActive(false     ),
    _pBarrier      (NULL      )
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

BlockingDrawTask::~BlockingDrawTask(void)
{
    _pBarrier = NULL;
}

void BlockingDrawTask::activateBarrier(bool bVal)
{
    _bBarrierActive = bVal;

    if(_bBarrierActive == true && _pBarrier == NULL)
    {
        _pBarrier = Barrier::get(NULL, false);
        _pBarrier->setNumWaitFor(2);
    }
}

void BlockingDrawTask::setNumWaitFor(UInt32 uiWaitees)
{
    if(_pBarrier != NULL && uiWaitees != 0)
    {
        _pBarrier->setNumWaitFor(uiWaitees);
    }
}

void BlockingDrawTask::waitForBarrier(void)
{
    if(_bBarrierActive == false)
    {
        return;
    }

    OSG_ASSERT(_pBarrier != NULL);

    _pBarrier->enter();
}

OSG_END_NAMESPACE


