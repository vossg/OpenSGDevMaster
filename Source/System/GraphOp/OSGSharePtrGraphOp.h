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
 
#ifndef _OSGSHAREPTRGRAPHOP_H_
#define _OSGSHAREPTRGRAPHOP_H_

#ifdef __sgi
#   pragma once
#endif

#include <map>
#include <set>
#include <vector>

#include "OSGGraphOp.h"
#include "OSGUtilDef.h"

OSG_BEGIN_NAMESPACE

//! \ingroup GrpSystemRenderingBackend
//! GraphOp class

class OSG_UTIL_DLLMAPPING SharePtrGraphOp : public GraphOp
{
    /*==========================  PUBLIC  =================================*/
public:

    /*---------------------------------------------------------------------*/
    /*! \name                    Class Get                                 */
    /*! \{                                                                 */

    static const char *getClassname(void) { return "SharePtrGraphOp"; };

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */
    
    SharePtrGraphOp(const char* name = "SharePtr");

    virtual GraphOpTransitPtr create(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Main methods                               */
    /*! \{                                                                 */
    
    bool traverse(Node *root);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Parameters                                */
    /*! \{                                                                 */

    void setParams(const std::string params);
    
    void setIncludes(const std::string &includes);
    void setExcludes(const std::string &excludes);

    std::string usage(void);

    /*! \}                                                                 */
    
    /*=========================  PROTECTED  ===============================*/
protected:    

    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SharePtrGraphOp(void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
private:

    Action::ResultE traverseEnter(Node * const node);
    Action::ResultE traverseLeave(Node * const node, Action::ResultE res);

    bool isInList(const std::vector<std::string> &tlist,
                        FieldContainer * constfc);
    FieldContainer *compareFCs(FieldContainer * const fc);
    static bool isEqual(FieldContainer * const a,
                        FieldContainer * const b);

    //static Action::ResultE clearAttachmentParent(NodePtr &node);
    //static Action::ResultE addAttachmentParent(NodePtr &node);
    //static void fillAttachmentParents(const NodePtr &node);

    typedef std::set<FieldContainer *> fcsSet;
    typedef std::map<std::string, fcsSet> fcsMap;
    fcsMap      _fctypes;

    std::vector<std::string>            _includes;
    std::vector<std::string>            _excludes;
    UInt32                              _share_counter;

    static std::set<FieldContainer *>  _added_cores;
};

OSG_END_NAMESPACE

#endif /* _OSGSHAREPTRGRAPHOP_H_ */
