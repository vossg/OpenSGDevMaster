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

#ifndef _OSGINTERSECTACTION_H_
#define _OSGINTERSECTACTION_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <vector>

#include "OSGSystemDef.h"
#include "OSGBaseTypes.h"
#include "OSGAction.h"
#include "OSGLine.h"

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class Node;

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \brief IntersectAction class
    \ingroup GrpSystemIntersectAction
    \ingroup GrpLibOSGSystem
 */

class OSG_SYSTEM_DLLMAPPING IntersectAction : public Action
{
  public:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    // create a new IntersectAction by cloning the prototype
    static IntersectAction *create(      void                 );
    static IntersectAction *create(const Line   &line, 
                                   const Real32  maxdist = Inf);
    
    // prototype access
    // after setting the prototype all new IntersectActions are clones of it

    static void             setPrototype(IntersectAction *proto);
    static IntersectAction *getPrototype(void                  );

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------
 
    IntersectAction& operator =(const IntersectAction &source);

    virtual ~IntersectAction(void); 

    /*------------------------- your_category -------------------------------*/


    // set input data
          void     setLine(       const Line   &line, 
                                  const Real32  maxdist = Inf);
          void     setTestLines     ( bool value );
          void     setTestLineWidth (Real32 width);


    // get input data
    const Line    &getLine       (      void                 ) const;
          Real32   getMaxDist    (      void                 ) const;
          bool     getTestLines  (      void                 ) const;
          Real32   getTestLineWidth (   void                 ) const;
          
    
    // get result data
          bool     didHit        (      void                 ) const;
    
          Real32   getHitT       (      void                 ) const;
    
          Pnt3f    getHitPoint   (      void                 ) const;
    
          Vec3f    getHitNormal  (      void                 ) const;
    
          Node    *getHitObject  (      void                 ) const;
    
          Int32    getHitTriangle(      void                 ) const;

          Int32    getHitLine    (      void                 ) const;

    /*------------------------- access ------------------------------*/

    // to be used by the traversed nodes
    // set (temporary) results
    Action::ResultE setEnterLeave(Real32   enter, 
                                  Real32   leave   );
    void            setHit       (Real32   t, 
                                  Node    *obj, 
                                  Int32    triIndex, 
                                  Vec3f   &normal,
                                  Int32    lineIndex );

    // when entering/leaving a different coordinate system, the values might
    // have to be scaled
    void scale(Real32 s);
    
    /*------------------------- your_operators ------------------------------*/

    /*------------------------- assignment ----------------------------------*/

    /*------------------------- comparison ----------------------------------*/

    bool operator < (const IntersectAction &other) const;
    
    bool operator == (const IntersectAction &other) const;
    bool operator != (const IntersectAction &other) const;
    
    
    // default registration. static, so it can be called during static init
    static void registerEnterDefault(const FieldContainerType &type, 
                                     const Action::Functor    &func);
    
    static void registerLeaveDefault(const FieldContainerType &type, 
                                     const Action::Functor    &func);

  protected:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static bool terminateEnter(void);
    static bool terminateLeave(void);

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    IntersectAction(void);
    IntersectAction(const IntersectAction &source);

    virtual Action::ResultE start(void);  

    // access default functors

    virtual FunctorStore *getDefaultEnterFunctors(void);
    virtual FunctorStore *getDefaultLeaveFunctors(void);

  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef Action Inherited;

    //-----------------------------------------------------------------------
    //   friend classes                                                      
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   friend functions                                                    
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

    // the prototype which is copied to create new actions
    static IntersectAction * _prototype;

    // default functors for instantiation
    static FunctorStore *_defaultEnterFunctors;
    static FunctorStore *_defaultLeaveFunctors;
    
    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------
    
    // the line to be tested
    Line   _line;
    bool   _testLines;     /**< If true, attempt to intersect lines as well as geom. */
    float  _lineTestWidth; /**< The width to assume for all lines we intersect against. */
    
    // the maximum distance along the line
    Real32 _maxdist;
    
    // Results (also intermediate)
    // hit at all (either bv or face)
    bool    _hit;
    // enter leave distance for bounding volume
    Real32  _enterT;
    Real32  _leaveT;
    
    // Hit distance
    Real32  _hitT;

    // Hit object   
    Node   *_hitObject;

    // Index of the hit triangle ( from TriangleIterator::getIndex() )
    Int32   _hitTriangle;

    // Normal of the hit triangle
    Vec3f   _hitNormal;

    // Index of the hit line ( from LineInterator::getIndex() )
    Int32   _hitLine;
    
    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

// class pointer

typedef IntersectAction *IntersectActionP;

OSG_END_NAMESPACE

#include "OSGIntersectAction.inl"

#endif /* _OSGRENDERACTION_H_ */
