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


#ifndef _OSGVERIFYGEOGRAPHOP_H_
#define _OSGVERIFYGEOGRAPHOP_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGSingleTypeGraphOp.h"
#include "OSGGeometry.h"

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpUtilGraphOp
    \ingroup GrpLibOSGUtil
 */

class OSG_UTIL_DLLMAPPING VerifyGeoGraphOp : public SingleTypeGraphOp<Geometry>
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
    /*! \{                                                                 */

    typedef SingleTypeGraphOp<Geometry>             Inherited;
    typedef VerifyGeoGraphOp                        Self;

    OSG_GEN_INTERNAL_MEMOBJPTR(VerifyGeoGraphOp);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Classname                                                    */
    /*! \{                                                                 */

    static const char *getClassname(void) { return "VerifyGeoGraphOp"; };

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */
    
    static  ObjTransitPtr     create(bool repair = true);

    virtual GraphOpTransitPtr clone (void              );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Main methods                               */
    /*! \{                                                                 */

    virtual bool traverse(Node *root);
    
    void setParams(const std::string params);
    void setRepair(bool repair);

    std::string usage(void);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    bool travNodeEnter(Node *node);
    bool travNodeLeave(Node *node);

    /*---------------------------------------------------------------------*/
    /*! \name Constructors/Destructor                                      */
    /*! \{                                                                 */

             VerifyGeoGraphOp(      bool  repair = true,
                              const char *name   = "VerifyGeo");
    virtual ~VerifyGeoGraphOp(void                            );

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

 private:

    bool checkIndexedGeo   (Geometry *geo, UInt32 sumLengths);
    bool checkNonindexedGeo(Geometry *geo, UInt32 sumLengths);
    
    UInt32 _errorCount;
    bool   _repair;
};

OSG_GEN_MEMOBJPTR(VerifyGeoGraphOp);

OSG_END_NAMESPACE

#endif /* _OSGVERIFYGEOGRAPHOP_H_ */
