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


#ifndef _OSGSPLITGRAPHOP_H_
#define _OSGSPLITGRAPHOP_H_
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

class OSG_UTIL_DLLMAPPING SplitGraphOp : public GraphOp
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
    /*! \{                                                                 */

    typedef GraphOp                                 Inherited;
    typedef SplitGraphOp                            Self;

    OSG_GEN_INTERNAL_MEMOBJPTR(SplitGraphOp);

    /*---------------------------------------------------------------------*/
    /*! \name                    Class Get                                 */
    /*! \{                                                                 */

    static const char *getClassname(void) { return "SplitGraphOp"; };

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */
    
    static  ObjTransitPtr     create(UInt16 maxPolygons = 1000);

    virtual GraphOpTransitPtr clone (void                     );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Main methods                               */
    /*! \{                                                                 */

    virtual bool traverse(Node *root);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Parameters                                */
    /*! \{                                                                 */

    void setParams(const std::string params);
    void setMaxPolygons(UInt16 max_polygons);

    std::string usage(void);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

             SplitGraphOp(      UInt16  max_polygons = 1000,
                          const char   *name         = "Split");
    virtual ~SplitGraphOp(void                                );

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    UInt16 _max_polygons;

    bool isLeaf        (Node * const node);
    bool isGroup       (Node * const node);
    bool splitNode     (Node * const node, std::vector<NodeUnrecPtr> &split);

    Action::ResultE traverseEnter(Node * const node);
    Action::ResultE traverseLeave(Node * const node, Action::ResultE res);
};

typedef SplitGraphOp *SplitGraphOpP;

OSG_GEN_MEMOBJPTR(SplitGraphOp);

/*! \ingroup GrpUtilGraphOp
    \ingroup GrpLibOSGUtil
    \nohierarchy
 */

class OSG_UTIL_DLLMAPPING Pnt3fComparator : 
    public std::binary_function<int,int,bool> 
{
    const std::vector<Pnt3f> &_vec;

  public:

    Pnt3fComparator(const std::vector<Pnt3f> &vec) : _vec(vec) {}

    bool operator()(int a, int b) const
    {
        if(_vec[a][0] < _vec[b][0])
            return true;
        
        if(_vec[a][0] == _vec[b][0])
        {
            if(_vec[a][1] < _vec[b][1])
                return true;
            else if(_vec[a][1] == _vec[b][1])
                if(_vec[a][2] < _vec[b][2])
                    return true;
        }

        return false;
    }
};

OSG_END_NAMESPACE

#endif /* _OSGSPLITGRAPHOP_H_ */
