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

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/


/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/


/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/


/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

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



/** \brief Destructor
 */


/*------------------------------ access -----------------------------------*/

inline 
const Line &IntersectAction::getLine(void) const
{
    return _line;
}

inline 
Real32 IntersectAction::getMaxDist(void) const
{
    return _maxdist;
}

inline 
bool IntersectAction::getTestLines(void) const
{
   return _testLines;
}

inline
Real32 IntersectAction::getTestLineWidth(void) const
{
   return _lineTestWidth;
}
          

inline 
bool IntersectAction::didHit(void) const
{
    return _hit;
}

inline 
Real32 IntersectAction::getHitT(void) const
{
    if(! didHit())
        return -1;

    return _hitT;
}

inline 
Pnt3f IntersectAction::getHitPoint(void) const
{
    if(! didHit())
        return Pnt3f::Null;
    
    Pnt3f res;

    res = _line.getPosition() + getHitT() * _line.getDirection();

    return res;
}

inline 
const Vec3f &IntersectAction::getHitNormal(void) const
{
    if(! didHit())
        return Vec3f::Null;
    
    return _hitNormal;
}

inline 
Node *IntersectAction::getHitObject(void) const
{
    if(! didHit())
        return NULL;

    return _hitObject;
}

inline 
Int32 IntersectAction::getHitTriangle(void) const
{
    if(! didHit())
        return -1;

    return _hitTriangle;
}

/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/

/*-------------------------- assignment -----------------------------------*/

/** \brief assignment
 */


/*-------------------------- comparison -----------------------------------*/

/** \brief assignment
 */


/** \brief equal
 */


/** \brief unequal
 */



/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

OSG_END_NAMESPACE
