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

OSG_BEGIN_NAMESPACE

inline void
UpdatePartition::setUpdateAction(UpdateAction *action)
{
    _updateAction = action;
}

inline UpdateAction *
UpdatePartition::getUpdateAction(void) const
{
    return _updateAction;
}

template <class MatrixT>
inline void
UpdatePartition::pushMatrix(const MatrixT &matrix)
{
    _modelViewMatrixStack.push_back(_modelViewMatrix);

    _modelViewMatrix.first  = ++_matrixId;
    _modelViewMatrix.second.mult(matrix);

    _modelMatrixValid = false;
}

inline void
UpdatePartition::popMatrix(void)
{
    _modelViewMatrix = _modelViewMatrixStack.back();
    
    _modelViewMatrixStack.pop_back();

    _modelMatrixValid = false;
}

inline const Matrix &
UpdatePartition::getModelMatrix(void) const
{
    updateModelMatrix();

    return _modelMatrix;
}

inline const Matrix &
UpdatePartition::getModelViewMatrix(void) const
{
    return _modelViewMatrix.second;
}

inline const DrawEnv &
UpdatePartition::getDrawEnv(void) const
{
    return _drawEnv;
}

inline DrawEnv &
UpdatePartition::editDrawEnv(void)
{
    return _drawEnv;
}

OSG_END_NAMESPACE
