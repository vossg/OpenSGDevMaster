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


#ifndef _OSGGEOTYPEGRAPHOP_H_
#define _OSGGEOTYPEGRAPHOP_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGSingleTypeGraphOp.h"
#include "OSGGeometry.h"

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpUtilGraphOp
    \ingroup GrpLibOSGUtil
 */

class OSG_UTIL_DLLMAPPING GeoTypeGraphOp
    : public SingleTypeGraphOp<Geometry>
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
    /*! \{                                                                 */

    typedef SingleTypeGraphOp<Geometry>             Inherited;
    typedef GeoTypeGraphOp                          Self;

    OSG_GEN_INTERNAL_MEMOBJPTR(GeoTypeGraphOp);

    static const BitVector FilterNormals = OSGLL(1) << 1;
    static const BitVector FilterIndices = OSGLL(1) << 2;
    static const BitVector FilterLengths = OSGLL(1) << 3;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Classname                                                    */
    /*! \{                                                                 */
    
    static const char *getClassname(void) { return "GeoTypeGraphOp"; };

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
    /*---------------------------------------------------------------------*/
    /*! \name Filtering                                                    */
    /*! \{                                                                 */
    
    // Individual sets
    void setFilter(const OSG::BitVector &filter);
    
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name            Constructors/Destructor                           */
    /*! \{                                                                 */
    
             GeoTypeGraphOp(const char* name = "GeoType");
    virtual ~GeoTypeGraphOp(void                        );
    
    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    bool travNodeEnter(Node *node);
    bool travNodeLeave(Node *node);

    void processNormals(Geometry *geo);
    void processIndices(Geometry *geo);
    void processLengths(Geometry *geo);
    
    OSG::BitVector _filter;
};

OSG_GEN_MEMOBJPTR(GeoTypeGraphOp);

OSG_END_NAMESPACE

#endif
