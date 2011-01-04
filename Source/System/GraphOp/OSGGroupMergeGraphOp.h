/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                   Copyright (C) 2008 by the OpenSG Forum                  *
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

#ifndef _OSGGROUPMERGEGRAPHOP_H_
#define _OSGGROUPMERGEGRAPHOP_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGUtilDef.h"
#include "OSGGraphOp.h"

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpUtilGraphOp
    \ingroup GrpLibOSGUtil
 */

class OSG_UTIL_DLLMAPPING GroupMergeGraphOp : public GraphOp
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
    /*! \{                                                                 */
    
    typedef GraphOp           Inherited;
    typedef GroupMergeGraphOp Self;
    
    OSG_GEN_INTERNAL_MEMOBJPTR(GroupMergeGraphOp);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Classname                                                    */
    /*! \{                                                                 */
    
    static const char *getClassname(void);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constructors                                                 */
    /*! \{                                                                 */
    
    static  ObjTransitPtr     create(void);

    virtual GraphOpTransitPtr clone (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Parameters                                */
    /*! \{                                                                 */

    void        setParams(const std::string params);

    std::string usage    (void                    );

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name Constructors/Destructors                                     */
    /*! \{                                                                 */

             GroupMergeGraphOp(const char* name = "GroupMerge");
    virtual ~GroupMergeGraphOp(void                           );

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    Action::ResultE traverseEnter(Node * const node                     );
    Action::ResultE traverseLeave(Node * const node, Action::ResultE res);
    
    void handleNoChildren      (Node * const node, NodeCore * const core);
    void handleSingleChild     (Node * const node, NodeCore * const core);
    void handleMultipleChildren(Node * const node, NodeCore * const core);
};

OSG_GEN_MEMOBJPTR(GroupMergeGraphOp);

OSG_END_NAMESPACE

#endif // _OSGGROUPMERGEGRAPHOP_H_
