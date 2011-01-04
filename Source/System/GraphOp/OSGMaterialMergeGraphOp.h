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


#ifndef _OSGMATERIALMERGEGRAPHOP_H_
#define _OSGMATERIALMERGEGRAPHOP_H_
#ifdef __sgi
#pragma once
#endif

#include <list>
#include <map>

#include "OSGGraphOp.h"
#include "OSGUtilDef.h"
#include "OSGAction.h"
#include "OSGMaterialDrawable.h"
#include "OSGMaterialGroup.h"

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpUtilGraphOp
    \ingroup GrpLibOSGUtil
 */

class OSG_UTIL_DLLMAPPING MaterialMergeGraphOp : public GraphOp
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
    /*! \{                                                                 */
    
    typedef GraphOp                                 Inherited;
    typedef MaterialMergeGraphOp                    Self;

    OSG_GEN_INTERNAL_MEMOBJPTR(MaterialMergeGraphOp);

    /*! \nohierarchy
     */
    class MaterialObject
    {
      public:
        MaterialObject(MaterialDrawable *md)
            : _md(md  ),
              _mg(NULL)
        {
        }

        MaterialObject(MaterialGroup *mg)
            : _md(NULL),
              _mg(mg  )
        {
        }

        Material *getMaterial(void)
        {
            return (_md != NULL ? _md->getMaterial() : _mg->getMaterial());
        }

        void setMaterial(Material *mat)
        {
            if(_md != NULL)
            {
                _md->setMaterial(mat);
            }
            else
            {
                _mg->setMaterial(mat);
            }
        }

      private:
        MaterialDrawable *_md;
        MaterialGroup    *_mg;
    };

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Classname                                                    */
    /*! \{                                                                 */
    
    static const char *getClassname(void)
    {
        return "MaterialMergeGraphOp";
    };

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constructors                                                 */
    /*! \{                                                                 */
    
    static  ObjTransitPtr     create(void);

    virtual GraphOpTransitPtr clone (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Main methods                                                 */
    /*! \{                                                                 */
    
    virtual bool traverse(Node *node);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Parameters                                                   */
    /*! \{                                                                 */
    
    void        setParams(const std::string params);
    std::string usage    (      void              );

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name Constructors/Destructor                                      */
    /*! \{                                                                 */
    
             MaterialMergeGraphOp(const char* name = "MaterialMerge");
    virtual ~MaterialMergeGraphOp(void                              );

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    Action::ResultE traverseEnter(Node * const node);
    Action::ResultE traverseLeave(Node * const node, Action::ResultE res);

    void addObject(MaterialObject m);

    typedef std::list<MaterialObject                      > MaterialObjectList;
    typedef std::map <MaterialUnrecPtr, MaterialObjectList> MaterialObjectMap;

    MaterialObjectMap _materialMap;
};

OSG_GEN_MEMOBJPTR(MaterialMergeGraphOp);

OSG_END_NAMESPACE

#endif /* _OSGMERGEGRAPHOP_H_ */
