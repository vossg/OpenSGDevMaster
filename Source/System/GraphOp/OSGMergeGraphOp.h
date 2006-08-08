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


#ifndef _OSGMERGEGRAPHOP_H_
#define _OSGMERGEGRAPHOP_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGGraphOp.h"
#include "OSGAction.h"

OSG_BEGIN_NAMESPACE

//! \ingroup GrpSystemRenderingBackend
//! MergeGraphOp class

class OSG_UTIL_DLLMAPPING MergeGraphOp : public GraphOp
{
    /*==========================  PUBLIC  =================================*/
public:

    /*---------------------------------------------------------------------*/
    /*! \name                    Class Get                                 */
    /*! \{                                                                 */

    static const char *getClassname(void) { return "MergeGraphOp"; };

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */
    
    MergeGraphOp(const char* name = "Merge");

    GraphOp* create();

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~MergeGraphOp(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Main methods                               */
    /*! \{                                                                 */

    bool traverse(NodePtr& node);

    //virtual const std::string getName(void) { return _name; };

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Parameters                                */
    /*! \{                                                                 */

    void setParams(const std::string params);
    
    std::string usage(void);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
protected:    

    /*==========================  PRIVATE  ================================*/
private:
    // Use these params to transform tangent space vectors, just like normals.
    bool _color_is_vector;
    bool _secondary_color_is_vector;
    bool _texcoord0_is_vector;
    bool _texcoord1_is_vector;
    bool _texcoord2_is_vector;
    bool _texcoord3_is_vector;

    bool mergeOnce(NodePtr& node);

    void makeExcludeList        (NodePtr& node);
    void processGroups          (NodePtrConst node);
    void processTransformations (NodePtrConst node);
    void processGeometries      (NodePtrConst node);

    bool isLeaf        (NodePtrConst node);
    bool isGroup       (NodePtrConst node);

    Action::ResultE excludeListEnter(NodePtrConstArg node);
    Action::ResultE excludeListLeave(NodePtrConstArg node, Action::ResultE res);

    Action::ResultE traverseEnter(NodePtrConstArg node);
    Action::ResultE traverseLeave(NodePtrConstArg node, Action::ResultE res);
};

typedef MergeGraphOp *MergeGraphOpP;
OSG_END_NAMESPACE

#endif /* _OSGMERGEGRAPHOP_H_ */
