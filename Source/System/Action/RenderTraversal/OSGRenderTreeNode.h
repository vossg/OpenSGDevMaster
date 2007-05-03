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

#ifndef _OSGRENDERTREENODE_H_
#define _OSGRENDERTREENODE_H_

#ifdef __sgi
#pragma once
#endif

#include "OSGBaseTypes.h"
#include "OSGRenderTravDef.h"
#include "OSGRenderAction.h"
#include "OSGMaterial.h"
#include "OSGRenderTraversalFwd.h"

OSG_BEGIN_NAMESPACE

class Geometry;
class MaterialDrawable;
class State;

/*! \ingroup GrpSystemRenderingBackend
*/

class OSG_RENDERTRAV_DLLMAPPING RenderTreeNode
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef Material::DrawFunctor     DrawFunctor;
//    typedef RenderAction::MatrixStore MatrixStore;
    typedef std::pair<UInt32, Matrix> MatrixStore;

    /*---------------------------------------------------------------------*/
    /*! \name                    Access                                    */
    /*! \{                                                                 */

    RenderTreeNode *getFirstChild   (void                             );
    RenderTreeNode *getLastChild    (void                             );

    void            addChild        (RenderTreeNode    *pChild        );
    void            insertFirstChild(RenderTreeNode    *pChild        );
    void            insertChildAfter(RenderTreeNode    *pCurrent, 
                                     RenderTreeNode    *pChild        );

    RenderTreeNode *getBrother      (void);
    void            setBrother      (RenderTreeNode    *pBrother      );
    void            insertBrother   (RenderTreeNode    *pBrother      );

    void            setFunctor      (DrawFunctor       &func          );
    DrawFunctor    &getFunctor(void                                   );
    bool            hasFunctor      (void                             );
    
    void            setState        (State             *pState        );
    State          *getState        (void                             );

    void            setStateOverride(StateOverride     *pStateOverride);
    StateOverride  *getStateOverride(void                             );
    
    void            setMatrixStore  (const MatrixStore &oMatrixStore  );
    MatrixStore    &getMatrixStore  (void                             );

    void            setScalar       (Real32             rScalar       );
    Real32          getScalar       (void                             );

    void            setVol       (DynamicVolume             vol       );
    DynamicVolume   getVol       (void                             );

    void            setIsRendered   (bool       bRendered           );                 
    bool            getIsRendered   (void                          );                 

    void            setResultNum    (UInt32     uiResNum        );
    UInt32          getResultNum    (void        );

    void            setLightsState  (UInt64             state         );
    UInt64          getLightsState  (void                             );
    
    void            setNode         (Node              *pNode         );
    Node           *getNode         (void                             );

    void            reset           (void                             );

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    RenderTreeNode *_pFirstChild;
    RenderTreeNode *_pLastChild;

    RenderTreeNode *_pBrother;

    State          *_pState;
    StateOverride  *_pStateOverride;

    DrawFunctor     _functor;
    bool            _hasFunctor;
    
    MatrixStore     _oMatrixStore;        

    //! Scalar value for sorting. Expected to be in 0..1
    Real32          _rScalarVal;    

    DynamicVolume   _dVol;

    bool            _isRendered;

    UInt32          _resultNum;

    UInt64          _lightsState;
    
    Node           *_node;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    RenderTreeNode(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~RenderTreeNode(void); 

    /*! \}                                                                 */

    /*==========================  PRIVATE  ================================*/

  private:

    friend class SimplePool<RenderTreeNode, PoolDefaultTag>;

    /*! \brief prohibit default function (move to 'public' if needed) */
    RenderTreeNode(const RenderTreeNode &source);
    /*! \brief prohibit default function (move to 'public' if needed) */
    void operator =(const RenderTreeNode &source);
};

OSG_END_NAMESPACE

#include "OSGRenderTreeNode.inl"

#define OSGRENDERTREENODE_HEADER_CVSID "@(#)$Id$"

#endif /* _OSGRENDERTREENODE_H_ */
