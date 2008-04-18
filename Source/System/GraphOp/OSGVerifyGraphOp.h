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


#ifndef _OSGVERIFYGRAPHOP_H_
#define _OSGVERIFYGRAPHOP_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGGraphOp.h"
#include "OSGGeometry.h"

OSG_BEGIN_NAMESPACE

//! \ingroup GrpSystemRenderingBackend
//! GraphOp class

class OSG_UTIL_DLLMAPPING VerifyGraphOp : public GraphOp
{
    /*==========================  PUBLIC  =================================*/
public:

    /*---------------------------------------------------------------------*/
    /*! \name                    Class Get                                 */
    /*! \{                                                                 */

    static const char *getClassname(void) { return "VerifyGraphOp"; };

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */
    
    VerifyGraphOp(const char* name = "Verify", bool repair = true, 
                  bool verbose = false);

    GraphOp *create();

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Main methods                               */
    /*! \{                                                                 */

    bool traverse(NodePtr node);
    
    void setParams(const std::string params);
    void setVerbose(bool verbose);    
    void setRepair (bool repair);    

    std::string usage(void);

    /*! \}                                                                 */

    /*=========================  PROTECTED  ===============================*/
protected:    

    Action::ResultE traverseEnter(const NodePtr node);
    Action::ResultE traverseLeave(const NodePtr node, Action::ResultE res);

    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~VerifyGraphOp(void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
private:

    /* Some internal helper methods */
    
    Action::ResultE verifyGeometry(const NodePtr node);
    bool verifyIndexMap(GeometryPtr geo, bool &repair);
    bool repairGeometry(void);    

    /* Configuration variables */
 
    bool _repair;    
    bool _verbose;    
    
    /* Traversal variables */
    
   UInt32 _numErrors;  /**< The running total of errors found. */

   std::vector<OSG::GeometryPtr> _corruptedGeos;
   std::vector<OSG::NodePtr>     _corruptedNodes;
    
};

OSG_END_NAMESPACE

#endif /* _OSGVERIFYGRAPHOP_H_ */
