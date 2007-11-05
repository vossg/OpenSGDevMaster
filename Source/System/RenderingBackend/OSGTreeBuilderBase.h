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

#ifndef _OSGTREEBUILDERBASE_H_
#define _OSGTREEBUILDERBASE_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <map>

#include "OSGRenderingBackendFwd.h"
#include "OSGBaseTypes.h"
#include "OSGMultiPool.h"
#include "OSGDrawEnv.h"

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class State;

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------


/*! \class TreeBuilderBase
 *  \brief Base class for all TreeBuilders.
 */

class OSG_SYSTEM_DLLMAPPING TreeBuilderBase
{
  public:

    //-----------------------------------------------------------------------
    //   constants                                                             
    //-----------------------------------------------------------------------
  
    static const TreeBuilderBase Proto;
   
    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    /*------------------------- your_category -------------------------------*/

    /*------------------------- your_operators ------------------------------*/

    /*------------------------- assignment ----------------------------------*/
    
    void setNodePool(RenderTreeNodePool *pNodePool);

    /*------------------------- comparison ----------------------------------*/

    virtual void reset(void);

    /*------------------------- comparison ----------------------------------*/

    virtual void add(DrawEnv &denv, 
                     RenderPartition *part,
                     RenderTreeNode *pNode,
                     State          *pState,
                     StateOverride  *pStateOverride,
                     UInt32          uiKeyGen      );

    /*-------------------------- comparison ---------------------------------*/

    RenderTreeNode *getRoot(void);

    virtual void draw(DrawEnv &denv, RenderPartition *part);

    /*-------------------------- comparison ---------------------------------*/

  protected:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    /*! MatrixStore is stored internally to keep track of the current matrix.
        The UInt32 is used to quickly identify the same matrix without having
        to compare actual matrix elements.
    */
    typedef std::pair<UInt32, Matrix>               MatrixStore;

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    /*! Draws the all the subtrees associated with pNode and his siblings.
     *  \param pNode the node to start drawing from.
     *  \param denv the draw environment which is being used.
     *  \param part the step in rendering we are in.
     */
    void drawNode(RenderTreeNode *pNode, DrawEnv &denv, RenderPartition *part);

    /*! Updates the nodes _accMatrix from the DrawEnv */
    void updateTopMatrix(DrawEnv &denv);

    const Matrix &topMatrix(void);

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    RenderTreeNodePool *_pNodePool;
    RenderTreeNode     *_pRoot;

    UInt32              _uiActiveMatrix;
    UInt32              _uiMatrixId;

    MatrixStore         _currMatrix;
    Matrix              _accMatrix;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    TreeBuilderBase(void);
    virtual ~TreeBuilderBase(void);

  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   friend classes                                                      
    //-----------------------------------------------------------------------

    friend class MultiPool<TreeBuilderBase>::TypeStore;

    //-----------------------------------------------------------------------
    //   friend functions                                                    
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------
   
    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------
    
    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const TreeBuilderBase &source);    
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

OSG_END_NAMESPACE

#include "OSGTreeBuilderBase.inl"

#endif /* _OSGTREEBUILDERBASE_H_ */


