/*---------------------------------------------------------------------------*\
*                                OpenSG                                     *
*                                                                           *
*                                                                           *
*             Copyright (C) 2000-2002 by the OpenSG Forum                   *
*                                                                           *
*                            www.opensg.org                                 *
*                                                                           *
*                   contact: dan.guilliams@gmail.com                        *
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


#ifndef _OSGCOLLISIONMESHGRAPHOP_H_
#define _OSGCOLLISIONMESHGRAPHOP_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGGraphOp.h"
#include "OSGUtilDef.h"
#include "OSGAction.h"

OSG_BEGIN_NAMESPACE

//! \ingroup GrpSystemRenderingBackend
//! CollisionMeshGraphOp class

class OSG_UTIL_DLLMAPPING CollisionMeshGraphOp : public GraphOp
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
    /*! \{                                                                 */

    typedef GraphOp                                 Inherited;
    typedef CollisionMeshGraphOp                            Self;

    OSG_GEN_INTERNAL_MEMOBJPTR(CollisionMeshGraphOp);

    /*---------------------------------------------------------------------*/
    /*! \name                    Class Get                                 */
    /*! \{                                                                 */

    static const char *getClassname(void) { return "CollisionMeshGraphOp"; };

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */
    
    static  ObjTransitPtr     create(std::string SearchName = "_col",
                          UInt32 NewTraversalMask = 0);

    virtual GraphOpTransitPtr clone (void );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Main methods                               */
    /*! \{                                                                 */

    virtual bool traverse(Node *root);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Parameters                                */
    /*! \{                                                                 */

    void setSearchString(std::string SearchName);
    void setNewTravMask(UInt32 NewTraversalMask);

	/*! Returns the number of nodes whose traversal masks was changed. 
	 *
	 *	@return Only accurate after the graph op has been completed.
	 */
	UInt32 getNumChanged( void );

	virtual std::string usage(void);
	virtual void setParams(const std::string params);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
protected:

    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

             CollisionMeshGraphOp(      std::string SearchName = "_col",
                          UInt32 NewTraversalMask = 0);
    virtual ~CollisionMeshGraphOp(void                                );

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
private:
	
	std::string _searchName;
	UInt32 _travMaskValue;
	UInt32 _numChanged;
	
    Action::ResultE traverseEnter(Node * const node);
    Action::ResultE traverseLeave(Node * const node, Action::ResultE res);
};

typedef CollisionMeshGraphOp *CollisionMeshGraphOpP;

OSG_GEN_MEMOBJPTR(CollisionMeshGraphOp);


OSG_END_NAMESPACE

#endif /* _OSGCOLLISIONMESHGRAPHOP_H_ */
