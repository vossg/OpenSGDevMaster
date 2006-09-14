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

#ifndef _OSGDRAWTREENODE_H_
#define _OSGDRAWTREENODE_H_

#ifdef __sgi
#pragma once
#endif

#include "OSGBaseTypes.h"
#include "OSGSystemDef.h"
#include "OSGRenderAction.h"
#include "OSGMaterial.h"
#include "OSGSystemProfile.h"

OSG_BEGIN_NAMESPACE

class Geometry;
class MaterialDrawable;
class State;
class DrawTreeNodeFactory;

/*! \ingroup GrpSystemRenderingBackend
*/

class OSG_SYSTEM_DLLMAPPING DrawTreeNode
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef Material::DrawFunctor     DrawFunctor;
    typedef RenderAction::MatrixStore MatrixStore;

    /*---------------------------------------------------------------------*/
    /*! \name                    Flags                                     */
    /*! \{                                                                 */

    static const UInt8 MultiPass;
    static const UInt8 LastMultiPass;
    static const UInt8 NoStateSorting;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Access                                    */
    /*! \{                                                                 */

    DrawTreeNode     *getFirstChild   (void                           );
    DrawTreeNode     *getLastChild    (void                           );

    void              addChild        (DrawTreeNode *pChild           );
    void              insertFirstChild(DrawTreeNode *pChild           );
    void              insertChildAfter(DrawTreeNode *pCurrent, 
                                       DrawTreeNode *pChild           );

    DrawTreeNode     *getBrother      (void);
    void              setBrother      (DrawTreeNode *pBrother         );

    void              setGeometry     (MaterialDrawable *pGeo         );
    MaterialDrawable *getGeometry     (void                           );

    void              setFunctor      (DrawFunctor &func              );
    DrawFunctor      &getFunctor(void                                 );
    bool              hasFunctor      (void                           );
    
    void              setState        (State    *pState               );
    State            *getState        (void                           );
    
    void              setNode         (NodePtr   pNode                );
    NodePtr           getNode         (void                           );

    void              setMatrixStore  (const MatrixStore &oMatrixStore);
    MatrixStore      &getMatrixStore  (void                           );

    void              setScalar       (Real   rScalar                 );
    Real              getScalar       (void                           );

    void              setLightsState  (UInt64 state                   );
    UInt64            getLightsState  (void                           );

    void              setMultiPass    (void                           );
    void              setLastMultiPass(void                           );
    bool              isMultiPass     (void                           );
    bool              isLastMultiPass (void                           );

    void              setNoStateSorting(void                           );
    bool              isNoStateSorting (void                           );

    void              reset           (void                           );

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    DrawTreeNode              *_pFirstChild;
    DrawTreeNode              *_pLastChild;

    DrawTreeNode              *_pBrother;

    NodePtr                    _pNode;

    State                     *_pState;
    MaterialDrawable          *_pGeo;
    Material::DrawFunctor      _functor;
    bool                       _hasFunctor;
    
    MatrixStore                _oMatrixStore;        

    Real                       _rScalarVal;

    UInt64                     _lightsState;

    Int8                       _flags;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    DrawTreeNode(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~DrawTreeNode(void); 

    /*! \}                                                                 */

    /*==========================  PRIVATE  ================================*/

  private:

    friend class DrawTreeNodeFactory;

    /*! \brief prohibit default function (move to 'public' if needed) */
    DrawTreeNode(const DrawTreeNode &source);
    /*! \brief prohibit default function (move to 'public' if needed) */
    void operator =(const DrawTreeNode &source);
};

OSG_END_NAMESPACE

#include "OSGDrawTreeNode.inl"

#define OSGDRAWTREENODE_HEADER_CVSID "@(#)$Id$"

#endif /* _OSGDRAWTREENODE_H_ */
