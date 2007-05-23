/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
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

#include <OSGConfig.h>
#include <OSGBaseTypes.h>

#include "OSGManipulatorManager.h"


// TODO: der ManipulatorManager merkt sich den Core, nicht den Node des
// Manipulators. Damit besteht ein Problem mit Multi-Parents, das nicht waere,
// wenn der ManipulatorManager sich den Node merken wuerde!?!

NodePtr ManipulatorManager::createManipulator(const ManipulatorType type)
{
    NodePtr maniN = Node::create();
    
    switch (type)
    {
        case ROTATE:
            _maniC = RotateManipulator::create();
            break;
        case SCALE:
            _maniC = ScaleManipulator::create();
            break;
        case TRANSLATE:
            _maniC = MoveManipulator::create();    
            break;
    }
    
    _currentType = type;

    maniN->setCore(_maniC);
    commitChanges();

    return maniN;
}

// TODO: 
void ManipulatorManager::changeManipulator(const ManipulatorType type)
{
    if (type != _currentType)
    {
        if ( ! _maniC->getParents().empty() )
        {
            NodePtr maniN = cast_dynamic<NodePtr>(_maniC->getParents()[0]);

            _maniC = NullFC;

            switch (type)
            {
                case TRANSLATE:
                    _maniC = MoveManipulator::create();
                    break;
                case ROTATE:
                    _maniC = RotateManipulator::create();
                    break;
                case SCALE:
                    _maniC = ScaleManipulator::create();
                    break;
            }
            
            _currentType = type;

            maniN->setCore(_maniC);

            // Calling commitChanges() here seems to be critical for making
            // this method behave at all.
            commitChanges();

            _maniC->setTarget  (_target  );
            _maniC->setViewport(_viewport);

            commitChanges();
        }
    }
}

void ManipulatorManager::setTarget(const NodePtr &value)
{
    _maniC->setTarget(value);
    _target = value;
}

void ManipulatorManager::setViewport(const ViewportPtr &value)
{
    _maniC->setViewport(value);
    _viewport = value;
}

bool ManipulatorManager::isActive()
{
    return _maniC->getActive();
}

void ManipulatorManager::mouseMove(const Int16 x,
                                   const Int16 y)
{
    _maniC->mouseMove(x, y);
}

void ManipulatorManager::mouseButtonPress(const UInt16 button,
                                          const Int16 x,
                                          const Int16 y      )
{
    _maniC->mouseButtonPress(button, x, y);
}

void ManipulatorManager::mouseButtonRelease(const UInt16 button,
                                            const Int16 x,
                                            const Int16 y      )
{
    _maniC->mouseButtonRelease(button, x, y);
}

bool ManipulatorManager::activate(NodePtr n)
{
    if ( _maniC->hasSubHandle(n) )
    {
        _maniC->setActiveSubHandle(n);
        return true;
    }
    else
    {
        return false;
    }
}
