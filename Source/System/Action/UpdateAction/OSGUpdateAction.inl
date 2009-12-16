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

inline UpdatePartition *
UpdateAction::getActivePartition(void) const
{
    return _activePartition;
}

template <class MatrixT>
inline void
UpdateAction::pushMatrix(const MatrixT &matrix)
{
    _activePartition->pushMatrix(matrix);
}

inline void
UpdateAction::popMatrix(void)
{
    _activePartition->popMatrix();
}

inline const Matrix &
UpdateAction::getModelMatrix(void) const
{
    return _activePartition->getModelMatrix();
}

inline const Matrix &
UpdateAction::getModelViewMatrix(void) const
{
    return _activePartition->getModelViewMatrix();
}

inline const DrawEnv &
UpdateAction::getDrawEnv(void) const
{
    return _activePartition->getDrawEnv();
}

inline DrawEnv &
UpdateAction::editDrawEnv(void)
{
    return _activePartition->editDrawEnv();
}

inline Camera *
UpdateAction::getCamera(void) const
{
    return _camera;
}

inline void
UpdateAction::setCamera(Camera *camera)
{
    _camera = camera;
}

inline Viewport *
UpdateAction::getViewport(void) const
{
    return _viewport;
}

inline void
UpdateAction::setViewport(Viewport *port)
{
    _viewport = port;
}

inline Window *
UpdateAction::getWindow(void) const
{
    return _window;
}

inline void
UpdateAction::setWindow(Window *window)
{
    _window = window;
}

OSG_END_NAMESPACE
