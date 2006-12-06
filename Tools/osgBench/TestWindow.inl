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

OSG::UInt16 TestWindow::getWidth(void)
{
    return _width;
}

OSG::UInt16 TestWindow::getHeight(void)
{
    return _height;
}

OSG::NodePtr TestWindow::getScene(void)
{
    return _scene;
}

OSG::PerspectiveCameraPtr TestWindow::getCamera(void)
{
    return OSG::cast_dynamic<OSG::PerspectiveCameraPtr>(
        getSSM()->getWindow()->getPort()[0]->getCamera());
}

OSG::SimpleSceneManager *TestWindow::getSSM(void)
{
    return _ssm;
}

OSG::WindowPtr TestWindow::getWindow(void)
{
    return _window;
}

void TestWindow::setScene(OSG::NodePtr scene)
{
    _scene = scene;
}

void TestWindow::setScene(NodeBase &scene)
{
    _scene = scene.getNode();
}

bool TestWindow::isOpen(void)
{
    return _open;
}
