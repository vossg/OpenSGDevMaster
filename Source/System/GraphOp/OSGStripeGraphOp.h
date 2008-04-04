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


#ifndef _OSGSTRIPEGRAPHOP_H_
#define _OSGSTRIPEGRAPHOP_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGSingleTypeGraphOp.h"
#include "OSGGeometry.h"

OSG_BEGIN_NAMESPACE

//! \ingroup GrpSystemRenderingBackend
//! GraphOp class

typedef SingleTypeGraphOp<Geometry> SingleTypeGraphOpGeo;

class OSG_UTIL_DLLMAPPING StripeGraphOp : public SingleTypeGraphOpGeo
{
    /*==========================  PUBLIC  =================================*/
public:

    /*---------------------------------------------------------------------*/
    /*! \name                    Class Get                                 */
    /*! \{                                                                 */

    static const char *getClassname(void) { return "StripeGraphOp"; };

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */
    
    StripeGraphOp(const char* name = "Stripe");

    GraphOp *create();

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Main methods                               */
    /*! \{                                                                 */
    
    void setParams(const std::string params);

    std::string usage(void);

    /*! \}                                                                 */

    /*=========================  PROTECTED  ===============================*/
protected:    

    bool travNodeEnter(NodePtr node);
    bool travNodeLeave(NodePtr node);       

    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~StripeGraphOp(void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
private:

    bool _force;  // Force striping striped geometries
    bool _stitch; // Stitch strips together
};

OSG_END_NAMESPACE

#endif /* _OSGSTRIPEGRAPHOP_H_ */
