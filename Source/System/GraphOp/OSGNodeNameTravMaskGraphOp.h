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
//! NodeNameTravMaskGraphOp class

class OSG_UTIL_DLLMAPPING NodeNameTravMaskGraphOp : public GraphOp
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
    /*! \{                                                                 */

    typedef GraphOp                                 Inherited;
    typedef NodeNameTravMaskGraphOp                            Self;

    OSG_GEN_INTERNAL_MEMOBJPTR(NodeNameTravMaskGraphOp);

    /*---------------------------------------------------------------------*/
    /*! \name                    Class Get                                 */
    /*! \{                                                                 */

    static const char *getClassname(void) { return "NodeNameTravMaskGraphOp"; };

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

             NodeNameTravMaskGraphOp(      std::string SearchName = "_col",
                          UInt32 NewTraversalMask = 0);
    virtual ~NodeNameTravMaskGraphOp(void                                );

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
private:
	
	std::string _searchName;
	UInt32 _travMaskValue;
	UInt32 _numChanged;
	
    Action::ResultE traverseEnter(Node * const node);
    Action::ResultE traverseLeave(Node * const node, Action::ResultE res);
};

typedef NodeNameTravMaskGraphOp *NodeNameTravMaskGraphOpP;

OSG_GEN_MEMOBJPTR(NodeNameTravMaskGraphOp);


OSG_END_NAMESPACE

#endif /* _OSGCOLLISIONMESHGRAPHOP_H_ */
