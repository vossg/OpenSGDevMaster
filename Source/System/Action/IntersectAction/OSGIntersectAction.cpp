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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#include "OSGLog.h"
#include "OSGFieldContainer.h"
#include "OSGNode.h"
#include "OSGNodeCore.h"
#include "OSGAction.h"
#include "OSGIntersectAction.h"

OSG_USING_NAMESPACE


/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::IntersectAction
    \ingroup GrpSystemAction

  The intersect action class.

*/

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

IntersectAction      *IntersectAction::_prototype            = NULL;

Action::FunctorStore *IntersectAction::_defaultEnterFunctors = NULL;
Action::FunctorStore *IntersectAction::_defaultLeaveFunctors = NULL;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

bool IntersectAction::terminateEnter(void)
{
    FDEBUG_GV(("Terminate IntersectAction Enter\n"));

    delete _defaultEnterFunctors;

    _defaultEnterFunctors = NULL;

    return true;
}

bool IntersectAction::terminateLeave(void)
{
    FDEBUG_GV(("Terminate IntersectAction Leave\n"));

    delete _defaultLeaveFunctors;

    _defaultLeaveFunctors = NULL;

    return true;
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

void IntersectAction::registerEnterDefault(const FieldContainerType &type, 
                                           const Action::Functor    &func)
{
    if(! _defaultEnterFunctors)
    {
        _defaultEnterFunctors = new FunctorStore;

        addPostFactoryExitFunction(&IntersectAction::terminateEnter);
    }

    while(type.getId() >= _defaultEnterFunctors->size())
    {
        _defaultEnterFunctors->push_back(
            &IntersectAction::_defaultEnterFunction);
    }
    
    (*_defaultEnterFunctors)[type.getId()] = func;
}

void IntersectAction::registerLeaveDefault(const FieldContainerType &type, 
                                           const Action::Functor    &func)
{
    if(! _defaultLeaveFunctors)
    {
        _defaultLeaveFunctors = new FunctorStore;

        addPostFactoryExitFunction(&IntersectAction::terminateLeave);
    }

    while(type.getId() >= _defaultLeaveFunctors->size())
    {
        _defaultLeaveFunctors->push_back(
            &IntersectAction::_defaultLeaveFunction);
    }
    
    (*_defaultLeaveFunctors)[type.getId()] = func;
}

void IntersectAction::setPrototype(IntersectAction *proto)
{
    _prototype = proto;
}

IntersectAction *IntersectAction::getPrototype(void)
{
    return _prototype;
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/



/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

IntersectAction::IntersectAction(void) :
     Inherited    (     ),
    _line         (     ),
    _testLines    (false),
    _lineTestWidth(  0.0),
    _maxdist      (     ), 
    _hit          (false), 
    _enterT       (   -1), 
    _leaveT       (   -1), 
    _hitT         (   -1), 
    _hitObject    (     ),
    _hitTriangle  (   -1),
    _hitNormal    (     ),
    _hitLine      (   -1)
{
    if(_defaultEnterFunctors)
        _enterFunctors = *_defaultEnterFunctors;

    if(_defaultLeaveFunctors)
        _leaveFunctors = *_defaultLeaveFunctors;
}


IntersectAction::IntersectAction(const IntersectAction& source) :
     Inherited    (source             ),
    _line         (source._line       ),
    _testLines    (source._testLines  ),
    _lineTestWidth( source._lineTestWidth),
    _maxdist      (source._maxdist    ), 
    _hit          (source._hit        ), 
    _enterT       (source._enterT     ), 
    _leaveT       (source._leaveT     ), 
    _hitT         (source._hitT       ), 
    _hitObject    (source._hitObject  ),
    _hitTriangle  (source._hitTriangle),
    _hitNormal    (source._hitNormal  ),
    _hitLine      (source._hitLine    )
{
}


/** \brief create a new action
 */

IntersectAction *IntersectAction::create(void)
{
    IntersectAction * act;
    
    if(_prototype)
        act = new IntersectAction(*_prototype);
    else
        act = new IntersectAction();
    
    return act;
}


/** \brief create a new action
 */

IntersectAction *IntersectAction::create(const Line   &line, 
                                         const Real32  maxdist)
{
    IntersectAction *act;
    
    if(_prototype)
        act = new IntersectAction(*_prototype);
    else
        act = new IntersectAction();
    
    act->setLine(line, maxdist);

    return act;
}

/** \brief Destructor
 */

IntersectAction::~IntersectAction(void)
{
}

/*---------------------------- application --------------------------------*/

/*---------------------------- properties ---------------------------------*/

void IntersectAction::setLine(const Line &line, const Real32 maxdist)
{
    _line    = line;
    _maxdist = maxdist;
}

void IntersectAction::setTestLines( bool value )
{
    _testLines = value;
}

void IntersectAction::setTestLineWidth(Real32 width)
{
    _lineTestWidth = width;
}

Int32 IntersectAction::getHitLine() const
{
   return _hitLine;
}

    
Action::ResultE IntersectAction::setEnterLeave(Real32 enter, Real32 leave)
{
    if(leave < 0 || enter > _maxdist ||
       ( _hit && enter > _hitT ))
    {
        return Action::Skip;
    }

    return Action::Continue;
}

/** Attempt to set the new hit for the intersection.
 *  The hit is only set if this hit would be closer then the existing hit position.
 *  @param t  The distance along the ray that the hit occurred.
 *  @param obj The Node object that was hit.
 *  @param triIndex The index of the triangle in the geometry hit.
 *  @param normal   The normal at the hit location.
 *  @param lineIndex The index of the line in the geometry hit.
 */
void IntersectAction::setHit(Real32  t, 
                             Node   *obj, 
                             Int32   triIndex, 
                             Vec3f  &normal,
                             Int32   lineIndex)
{
    if(t < 0 || t > _hitT || t > _maxdist)
        return;
        
    _hitT        = t;
    _hitObject   = obj;
    _hitTriangle = triIndex;
    _hitNormal   = normal;
    _hitLine     = lineIndex;
    _hit         = true;
}

void IntersectAction::scale(Real32 s)
{
    _hitT    *= s;
    _maxdist *= s;
}

/*-------------------------- your_category---------------------------------*/


Action::ResultE IntersectAction::start(void)
{
    _hitT        = Inf;
    _hitObject   = NULL;
    _hitTriangle = -1;
    _hitLine     = -1;
    _hit         = false;

    return Continue;
}


/*-------------------------- assignment -----------------------------------*/

/*-------------------------- comparison -----------------------------------*/

/** \brief assignment
 */

bool IntersectAction::operator < (const IntersectAction &other) const
{
    return this < &other;
}

/** \brief equal
 */

bool IntersectAction::operator == (
    const IntersectAction &OSG_CHECK_ARG(other)) const
{
    return false;
}

/** \brief unequal
 */

bool IntersectAction::operator != (const IntersectAction &other) const
{
    return ! (*this == other);
}


/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


Action::FunctorStore *IntersectAction::getDefaultEnterFunctors(void)
{
    return _defaultEnterFunctors;
}

Action::FunctorStore *IntersectAction::getDefaultLeaveFunctors(void)
{
    return _defaultLeaveFunctors;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/


