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


#ifndef _OSGPRUNEGRAPHOP_H_
#define _OSGPRUNEGRAPHOP_H_
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

class OSG_UTIL_DLLMAPPING PruneGraphOp : public GraphOp
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
    /*! \{                                                                 */

    typedef GraphOp                                 Inherited;
    typedef PruneGraphOp                            Self;

    OSG_GEN_INTERNAL_MEMOBJPTR(PruneGraphOp);
    
    enum Method
    {
        VOLUME,
        SUM_OF_DIMENSIONS,
    };

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Classname                                                    */
    /*! \{                                                                 */
    
    static const char *getClassname(void) { return "PruneGraphOp"; };

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constructors                                                 */
    /*! \{                                                                 */
    
    static ObjTransitPtr      create(float  size   = 1.0f,
                                     Method method = SUM_OF_DIMENSIONS);

    virtual GraphOpTransitPtr clone (void                             );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Parameters                                                   */
    /*! \{                                                                 */
    
    void        setParams(const std::string params);
    std::string usage    (void                    );
    
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name Constructors/Destructor                                      */
    /*! \{                                                                 */
    
             PruneGraphOp(      float  size   = 1.0f,
                                Method method = SUM_OF_DIMENSIONS,
                          const char*  name   = "Prune"           );
    virtual ~PruneGraphOp(void                                    );

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    Action::ResultE traverseEnter(Node * const node);
    Action::ResultE traverseLeave(Node * const node, Action::ResultE res);

    bool  isTooSmall(Node * const node);
    float getSize   (Node * const node);

    float  _size;
    Method _method;
};

OSG_GEN_MEMOBJPTR(PruneGraphOp);

OSG_END_NAMESPACE

#endif
