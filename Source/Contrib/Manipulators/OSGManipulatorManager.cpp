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

#include "OSGConfig.h"
#include "OSGIntersectAction.h"
#include "OSGManipulatorManager.h"

OSG_BEGIN_NAMESPACE

// TODO: der ManipulatorManager merkt sich den Core, nicht den Node des
// Manipulators. Damit besteht ein Problem mit Multi-Parents, das nicht waere,
// wenn der ManipulatorManager sich den Node merken wuerde!?!

ManipulatorManager::ManipulatorManager()
    : _maniN             (),
      _currentType       (),
      _currentEnablePivot(),
      _currentPivot      (),
      _target            (),
      _viewport          ()
{
}

ManipulatorManager::~ManipulatorManager()
{
    _maniN    = NULL;
    _target   = NULL;
    _viewport = NULL;
}

Node* ManipulatorManager::createManipulator(const ManipulatorType type)
{
    ManipulatorUnrecPtr mani;
  
    switch (type)
    {
        case ROTATE:
            mani = RotateManipulator::create();
            break;
        case SCALE:
            mani = ScaleManipulator::create();
            break;
        case TRANSLATE:
            mani = MoveManipulator::create();    
            break;
        case PLANE:
            mani = PlaneMoveManipulator::create();    
            break;
    }
    
    _currentType = type;
    
    mani->setEnablePivot(_currentEnablePivot);
    mani->setPivot      (_currentPivot);

    _maniN = makeNodeFor(mani);
    commitChanges();

    return _maniN;
}

// TODO: 
void ManipulatorManager::changeManipulator(const ManipulatorType type)
{
    if(type != _currentType)
    {
        ManipulatorUnrecPtr mani;
  
        switch (type)
        {
            case ROTATE:
                mani = RotateManipulator::create();
                break;
            case SCALE:
                mani = ScaleManipulator::create();
                break;
            case TRANSLATE:
                mani = MoveManipulator::create();    
                break;
            case PLANE:
                mani = PlaneMoveManipulator::create();    
                break;
       }

        _currentType = type;

        _maniN->setCore(mani);

        mani->setTarget     (_target  );
        mani->setViewport   (_viewport);
        mani->setEnablePivot(_currentEnablePivot);
        mani->setPivot      (_currentPivot);

        commitChanges();
    }
}

void ManipulatorManager::changeEnablePivot(bool enablePivot)
{
    Manipulator* mani = _maniN->getCore<Manipulator>();
   
    mani->setEnablePivot(enablePivot);   
    _currentEnablePivot = enablePivot;
    
    if (! enablePivot)
    {
        _currentPivot.setValues(0,0,0);
        mani->setPivot(Pnt3f(0,0,0));
        mani->updateHandleTransform();
    }

    commitChanges();
}

ManipulatorManager::ManipulatorType
ManipulatorManager::getCurrentType() const
{
    return _currentType;
}

bool ManipulatorManager::getCurrentEnablePivot() const
{
    return _currentEnablePivot;
}

const Pnt3f &ManipulatorManager::getCurrentPivot() const
{
    return _currentPivot;
}

void ManipulatorManager::setTarget(Node * const value)
{
    Manipulator* mani = _maniN->getCore<Manipulator>();

    if(mani != NULL)
    {
        mani->setTarget(value);
        _target = value;
    }
    else
    {
        SWARNING << "ManipulatorManager::setTarget: No active manipulator."
                 << std::endl;
    }
}

void ManipulatorManager::setViewport(Viewport * const value)
{
    Manipulator* mani = _maniN->getCore<Manipulator>();

    if(mani != NULL)
    {
        mani->setViewport(value);
        _viewport = value;
    }
    else
    {
        SWARNING << "ManipulatorManager::setViewport: No active manipulator."
                 << std::endl;
    }
}

bool ManipulatorManager::isActive()
{
    bool         retVal = false;
    Manipulator* mani   = _maniN->getCore<Manipulator>();

    if(mani != NULL)
        retVal = mani->getActive();

    return retVal;
}

void ManipulatorManager::mouseMove(const Int16 x,
                                   const Int16 y)
{
    Manipulator* mani = _maniN->getCore<Manipulator>();

    mani->mouseMove(x, y);
}

void ManipulatorManager::mouseButtonPress(const UInt16 uiButton,
                                          const Int16 x,
                                          const Int16 y      )
{
    Manipulator* mani = _maniN->getCore<Manipulator>();

    if (! _pivotChangePending)
    {
        mani->mouseButtonPress(uiButton, x, y);
    }
    else
    {
        OSG::Line viewray;
        _viewport->getCamera()->calcViewRay(viewray, x, y, *_viewport);

        OSG::Node *scene = _target;
        while (scene->getParent() != 0)
        {
            scene = scene->getParent();
        }

        OSG::IntersectActionRefPtr act = OSG::IntersectAction::create();
        act->setLine( viewray );
        act->apply( scene );

        if ( act->didHit() )
        {
            Pnt3f hitw = act->getHitPoint();
            
            // Transform from world to target space
            
            Matrix m = _target->getToWorld();
            m.invert();
            
            Pnt3f hitl;
            
            m.mult(hitw, hitl);
            
            mani->setPivot(hitl);           
            mani->updateHandleTransform();
            
            _currentPivot = hitl;
            
            //SLOG << "ManipulatorManager::mouseButtonPress: pivot changed to " << hitl << " (world:" << hitw << endLog;
        }
        else
        {
           SWARNING << "ManipulatorManager::mouseButtonPress: expected pivot change, bu no hit!?!" << endLog;
        }
        
        _pivotChangePending= false;

        act = NULL;
    }
}

void ManipulatorManager::mouseButtonRelease(const UInt16 uiButton,
                                            const Int16 x,
                                            const Int16 y      )
{
    Manipulator* mani = _maniN->getCore<Manipulator>();

    mani->mouseButtonRelease(uiButton, x, y);
}

bool ManipulatorManager::activate(Node *n)
{
    Manipulator* mani = _maniN->getCore<Manipulator>();

    if(mani->hasSubHandle(n) )
    {
        mani->setActiveSubHandle(n);
        return true;
    }
    else if (mani->getEnablePivot())
    {
        // Clicking on something below the target?
        while (n != 0 && n != _target)
        {
            n = n->getParent();
        }
        
        if (n != 0)
        {
            _pivotChangePending = true;
            
        }
        
        return false;
    }
    else
    {
        return false;
    }
}

OSG_END_NAMESPACE
