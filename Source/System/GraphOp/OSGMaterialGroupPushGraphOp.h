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

#ifndef _OSGMATERIALGROUPPUSHGRAPHOP_H_
#define _OSGMATERIALGROUPPUSHGRAPHOP_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGUtilDef.h"
#include "OSGGraphOp.h"
#include "OSGMaterialGroup.h"

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpUtilGraphOp
    \ingroup GrpLibOSGUtil
 */

class OSG_UTIL_DLLMAPPING MaterialGroupPushGraphOp : public GraphOp
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
    /*! \{                                                                 */
    
    typedef GraphOp              Inherited;
    typedef MaterialGroupPushGraphOp Self;
    
    OSG_GEN_INTERNAL_MEMOBJPTR(MaterialGroupPushGraphOp);
    
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
    /*! \name Constructors/Destructor                                      */
    /*! \{                                                                 */

             MaterialGroupPushGraphOp(const char* name = "MaterialGroupPush");
    virtual ~MaterialGroupPushGraphOp(void                                  );

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    typedef std::vector<Node *> PushTargetStore;

    Action::ResultE traverseEnter(Node * const node                     );
    Action::ResultE traverseLeave(Node * const node, Action::ResultE res);
    
    Action::ResultE traverseTargetsEnter(Node * const node);
    
    void pushMaterialGroup(MaterialGroup *mg);
    
    bool            _pushPossible;
    PushTargetStore _pushTargets;
};

OSG_GEN_MEMOBJPTR(MaterialGroupPushGraphOp);

OSG_END_NAMESPACE

#endif // _OSGMATERIALGROUPPUSHGRAPHOP_H_
