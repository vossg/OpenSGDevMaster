/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                  Copyright (C) 2009 by the OpenSG Forum                   *
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

#ifndef _OSGUPDATEPARTITION_H_
#define _OSGUPDATEPARTITION_H_

#include "OSGConfig.h"
#include "OSGSystemDef.h"

#include "OSGDrawEnv.h"

OSG_BEGIN_NAMESPACE

// forward decl
class UpdateAction;


class OSG_SYSTEM_DLLMAPPING UpdatePartition : public MemoryObject
{
  public:
    typedef MemoryObject     Inherited;
    typedef UpdatePartition  Self;

    OSG_GEN_INTERNAL_MEMOBJPTR(UpdatePartition);

#ifndef OSG_ENABLE_DOUBLE_MATRIX_STACK
    typedef std::pair  <UInt32, Matrix4f>  MatrixStore;
#else
    typedef std::pair  <UInt32, Matrix4d>  MatrixStore;
#endif
    typedef std::vector<MatrixStore     >  MatrixStack;

    
    void          setUpdateAction(UpdateAction *action);
    UpdateAction *getUpdateAction(void                ) const;


    template <class MatrixT>
    void pushMatrix(const MatrixT &matrix);
    void popMatrix (void                 );

    const Matrix &getModelMatrix    (void) const;
    const Matrix &getModelViewMatrix(void) const;


    const DrawEnv &getDrawEnv (void) const;
          DrawEnv &editDrawEnv(void);

    void setupProjection(const Matrix &matProj, const Matrix &matProjTrans);
    void setupViewing   (const Matrix &matView                            );


    void reset   (void                                          );
//    void init    (void                                          );
    void initFrom(UpdatePartition *sourcePart, UInt32 copyOnPush);

  protected:

    void updateModelMatrix(void) const;


    UpdateAction     *_updateAction;

    UInt32            _matrixId;
    mutable bool      _modelMatrixValid;
    mutable Matrix4f  _modelMatrix;
    MatrixStore       _modelViewMatrix;
    MatrixStack       _modelViewMatrixStack;

    DrawEnv           _drawEnv;
};

OSG_END_NAMESPACE

#include "OSGUpdatePartition.inl"

#endif // _OSGUPDATEPARTITION_H_
