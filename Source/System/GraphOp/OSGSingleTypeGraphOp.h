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


#ifndef _OSGSINGLETYPEGRAPHOP_H_
#define _OSGSINGLETYPEGRAPHOP_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGGraphOp.h"
#include "OSGUtilDef.h"

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpUtilGraphOp
    \ingroup GrpLibOSGUtil
 */

template < class Type > 
class SingleTypeGraphOp : public GraphOp
{
    /*==========================  PUBLIC  =================================*/

  public:
  
    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
    /*! \{                                                                 */

    typedef GraphOp           Inherited;
    typedef SingleTypeGraphOp Self;

    OSG_GEN_INTERNAL_MEMOBJPTR(SingleTypeGraphOp);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Class Get                                 */
    /*! \{                                                                 */

    static const char *getClassname(void) { return "SingleTypeGraphOp"; };

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Main methods                               */
    /*! \{                                                                 */
    

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:    

    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

             SingleTypeGraphOp(const char* name="");
    virtual ~SingleTypeGraphOp(void               );

    virtual bool travNodeEnter(Node *node) = 0; // only called for Type type objects 
    virtual bool travNodeLeave(Node *node) = 0; // only called for Type type objects 
        
    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    Action::ResultE traverseEnter(Node * const node);
    Action::ResultE traverseLeave(Node * const node, Action::ResultE res);
};

OSG_END_NAMESPACE

#include "OSGSingleTypeGraphOp.inl"

#endif /* _OSGSINGLETYPEGRAPHOP_H_ */
