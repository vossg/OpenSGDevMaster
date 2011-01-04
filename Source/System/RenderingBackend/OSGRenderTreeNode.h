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
#include "OSGRenderingBackendFwd.h"
#include "OSGDrawEnv.h"

OSG_BEGIN_NAMESPACE

class Geometry;
class MaterialDrawable;
class State;

/*! \ingroup GrpSystemRenderingBackendBase
    \ingroup GrpLibOSGSystem
 */

class OSG_SYSTEM_DLLMAPPING RenderTreeNode
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name                      Types                                   */
    /*! \{                                                                 */

    typedef DrawEnv::DrawFunctor      DrawFunctor;
    typedef std::pair<UInt32, Matrix> MatrixStore;

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
    /*---------------------------------------------------------------------*/
    /*! \name                    Access                                    */
    /*! \{                                                                 */

    RenderTreeNode *getFirstChild   (void                             );
    RenderTreeNode *getLastChild    (void                             );

    void            addChild        (RenderTreeNode    *pChild        );
    void            insertFirstChild(RenderTreeNode    *pChild        );
    void            insertChildAfter(RenderTreeNode    *pCurrent, 
                                     RenderTreeNode    *pChild        );

    RenderTreeNode *getBrother      (void                             );
    void            setBrother      (RenderTreeNode    *pBrother      );
    void            insertBrother   (RenderTreeNode    *pBrother      );

    void            setFunctor      (DrawFunctor       &func          );
    DrawFunctor    &getFunctor      (void                             );
    bool            hasFunctor      (void                             );
    
    void            setState        (State             *pState        );
    State          *getState        (void                             );

    void            setStateOverride(StateOverride     *pStateOverride);
    StateOverride  *getStateOverride(void                             );
    
    void            setMatrixStore  (const MatrixStore &oMatrixStore  );
    MatrixStore    &getMatrixStore  (void                             );

    void            setScalar       (Real32             rScalar       );
    Real32          getScalar       (void                             );

    void            setLightState   (UInt32             state         );
    UInt32          getLightState   (void                             );
    
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
    
    MatrixStore     _oMatrixStore;        

    //! Scalar value for sorting. Expected to be in 0..1
    Real32          _rScalarVal;    

    UInt32          _lightState;
    
    Node           *_node;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    /*! \brief prohibit default function (move to 'public' if needed) */
    RenderTreeNode(const RenderTreeNode &source);
    /*! \brief prohibit default function (move to 'public' if needed) */
    void operator =(const RenderTreeNode &source);
};

OSG_END_NAMESPACE

#include "OSGRenderTreeNode.inl"

#endif /* _OSGRENDERTREENODE_H_ */
