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

#ifndef _OSGTRANSFORMPUSHGRAPHOP_H_
#define _OSGTRANSFORMPUSHGRAPHOP_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGUtilDef.h"
#include "OSGGraphOp.h"
#include "OSGGeometry.h"
#include "OSGTransform.h"

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpUtilGraphOp
    \ingroup GrpLibOSGUtil
 */

class OSG_UTIL_DLLMAPPING TransformPushGraphOp : public GraphOp
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
    /*! \{                                                                 */
    
    typedef GraphOp              Inherited;
    typedef TransformPushGraphOp Self;
    
    OSG_GEN_INTERNAL_MEMOBJPTR(TransformPushGraphOp);
    
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

             TransformPushGraphOp(const char* name = "TransformPush");
    virtual ~TransformPushGraphOp(void                              );

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    typedef std::vector<Node *> PushTargetStore;

    Action::ResultE traverseEnter(Node * const node                     );
    Action::ResultE traverseLeave(Node * const node, Action::ResultE res);
    
    Action::ResultE traverseTargetsEnter(Node * const node);
    
    bool validTargetGeo (const Geometry  *geo                          );
    
    void pushTransform  (const Transform *srcTrans                     );
    void pushToTransform(const Transform *srcTrans, Transform *dstTrans);
    void pushToGeometry (const Transform *srcTrans, Geometry  *dstGeo  );
    
    bool            _pushPossible;
    PushTargetStore _pushTargets;
};

OSG_GEN_MEMOBJPTR(TransformPushGraphOp);

OSG_END_NAMESPACE

#endif // _OSGTRANSFORMPUSHGRAPHOP_H_
