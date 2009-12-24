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

#include <sstream>
#include <fstream>

#include "OSGConfig.h"

#include "OSGAction.h"
#include "OSGCamera.h"
#include "OSGSceneFileHandler.h"
#include "OSGVolumeDraw.h"

#include "OSGComputeAlgorithm.h"
#include "OSGDrawEnv.h"

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGComputeAlgorithmBase.cpp file.
// To modify it, please change the .fcd file (OSGComputeAlgorithm.fcd) and
// regenerate the base file.

/*-------------------------------------------------------------------------*/
/*                               Sync                                      */

void ComputeAlgorithm::changed(ConstFieldMaskArg whichField, 
                               UInt32            origin,
                               BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

/*-------------------------------------------------------------------------*/
/*                               Dump                                      */

void ComputeAlgorithm::dump(      UInt32    OSG_CHECK_ARG(uiIndent), 
                            const BitVector OSG_CHECK_ARG(bvFlags )) const
{
    SLOG << "Dump ComputeAlgorithm NI" << std::endl;
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

ComputeAlgorithm::ComputeAlgorithm(void) :
    Inherited()
{
}

ComputeAlgorithm::ComputeAlgorithm(const ComputeAlgorithm &source) :
    Inherited(source)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

ComputeAlgorithm::~ComputeAlgorithm(void)
{
}

/*-------------------------------------------------------------------------*/
/*                                Draw                                     */


/*-------------------------------------------------------------------------*/
/*                               loading                                   */

/*-------------------------------------------------------------------------*/
/*                               Init                                      */

void ComputeAlgorithm::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}



/*-------------------------------------------------------------------------*/
/*                               Task                                      */


ComputeAlgorithmDrawTask::ComputeAlgorithmDrawTask(UInt32 uiType) :
     Inherited (uiType),
    _pAlgorithm(NULL  ),
    _pBarrier  (NULL  )
{
    if(_uiTypeTask == AlgorithmWithBarrier)
    {
        _pBarrier = Barrier::get(NULL, false);
        _pBarrier->setNumWaitFor(2);
    }
}

ComputeAlgorithmDrawTask::ComputeAlgorithmDrawTask(
    ComputeAlgorithmP pAlgorithm, 
    UInt32            uiType    ) :

     Inherited (uiType    ),
    _pAlgorithm(pAlgorithm),
    _pBarrier  (NULL      )
{
    if(_uiTypeTask == AlgorithmWithBarrier)
    {
        _pBarrier = Barrier::get(NULL, false);
        _pBarrier->setNumWaitFor(2);
    }
}

ComputeAlgorithmDrawTask::~ComputeAlgorithmDrawTask(void)
{
    _pAlgorithm = NULL;
    _pBarrier   = NULL;
}

void ComputeAlgorithmDrawTask::execute(HardwareContext *pContext, 
                                       DrawEnv         *pEnv    )
{
    Window *pWindow = pEnv->getWindow();

    OSG_ASSERT( pWindow != NULL);
    OSG_ASSERT(_pAlgorithm     );

    switch(_uiTypeTask)
    {
        case Algorithm:
        {
            _pAlgorithm->execute(pContext, pEnv);
        }
        break;

        case AlgorithmWithBarrier:
        {
            _pAlgorithm->execute(pContext, pEnv);

            OSG_ASSERT(_pBarrier != NULL);

            _pBarrier->enter();
        }
        break;

        default:
            break;
    }
}

void ComputeAlgorithmDrawTask::activateBarrier(bool bVal)
{
    if(bVal == true)
    {
        _uiTypeTask = AlgorithmWithBarrier;

        if(_pBarrier == NULL)
        {
            _pBarrier = Barrier::get(NULL, false);
            _pBarrier->setNumWaitFor(2);
        }
    }
    else
    {
        _uiTypeTask = Algorithm;
    }
}

void ComputeAlgorithmDrawTask::setAlgorithm(ComputeAlgorithmP pAlgorithm)
{
    _pAlgorithm = pAlgorithm;
}


void ComputeAlgorithmDrawTask::waitForBarrier(void)
{
    OSG_ASSERT(_uiTypeTask == AlgorithmWithBarrier);
    OSG_ASSERT(_pBarrier   != NULL                );

    _pBarrier->enter();
}

void ComputeAlgorithmDrawTask::dump(UInt32 uiIndent)
{
    for(UInt32 i = 0; i < uiIndent; ++i) { fprintf(stderr, " "); }
    fprintf(stderr, "ComputeAlgorithmDrawTask : ");

    switch(_uiTypeTask)
    {
        case Algorithm:
        {
            fprintf(stderr, "Algorithm\n");
        }
        break;

        case AlgorithmWithBarrier:
        {
            fprintf(stderr, "AlgorithmWithBarrier\n");
        }
        break;

        default:
        {
            fprintf(stderr, "Unknown\n");
        }
        break;
    }

}

