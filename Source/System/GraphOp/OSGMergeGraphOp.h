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
#include "OSGUtilDef.h"
#include "OSGAction.h"

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpUtilGraphOp
    \ingroup GrpLibOSGUtil
 */

class OSG_UTIL_DLLMAPPING MergeGraphOp : public GraphOp
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
    /*! \{                                                                 */

    typedef GraphOp                                 Inherited;
    typedef MergeGraphOp                            Self;

    OSG_GEN_INTERNAL_MEMOBJPTR(MergeGraphOp);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Classname                                                    */
    /*! \{                                                                 */

    static const char *getClassname(void) { return "MergeGraphOp"; };

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */
    
    static  ObjTransitPtr     create(void);

    virtual GraphOpTransitPtr clone (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Main methods                               */
    /*! \{                                                                 */

    virtual bool traverse(Node *node);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Parameters                                */
    /*! \{                                                                 */

    void        setParams(const std::string params);
    std::string usage    (      void              );

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name Constructors/Destructor                                      */
    /*! \{                                                                 */

             MergeGraphOp(const char* name = "Merge");
    virtual ~MergeGraphOp(void                      );

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    // Use these params to transform tangent space vectors, just like normals.
    bool _color_is_vector;
    bool _secondary_color_is_vector;
    bool _texcoord0_is_vector;
    bool _texcoord1_is_vector;
    bool _texcoord2_is_vector;
    bool _texcoord3_is_vector;

    bool mergeOnce(Node *node);

    void makeExcludeList        (Node *       node);
    void processGroups          (Node * const node);
    void processTransformations (Node * const node);
    void processGeometries      (Node * const node);

    bool isLeaf        (Node * const node);
    bool isGroup       (Node * const node);

    Action::ResultE excludeListEnter(Node * const node);
    Action::ResultE excludeListLeave(Node * const node, Action::ResultE res);

    Action::ResultE traverseEnter(Node * const node);
    Action::ResultE traverseLeave(Node * const node, Action::ResultE res);
};

typedef MergeGraphOp *MergeGraphOpP;

OSG_GEN_MEMOBJPTR(MergeGraphOp);

OSG_END_NAMESPACE

#endif /* _OSGMERGEGRAPHOP_H_ */
