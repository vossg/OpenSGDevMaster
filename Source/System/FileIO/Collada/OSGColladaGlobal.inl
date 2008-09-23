/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                Copyright (C) 2008 by the OpenSG Forum                     *
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

inline ColladaGlobalTransitPtr ColladaGlobal::create(void)
{
    return ColladaGlobalTransitPtr(new ColladaGlobal());
}

inline DAE &ColladaGlobal::getDAE(void)
{
    return _dae;
}

inline void ColladaGlobal::setDocPath(const std::string &docPath)
{
    _docPath = docPath;
}

inline const std::string &ColladaGlobal::getDocPath(void) const
{
    return _docPath;
}

inline Node *ColladaGlobal::getRootNode(void) const
{
    return _rootNode;
}

inline void ColladaGlobal::addElement(ColladaElement *elem)
{
    _elements.push_back(elem);
}

inline void ColladaGlobal::subElement(ColladaElement *elem)
{
    ColladaElementStoreIt elemIt = std::find(
                                             _elements.begin(), _elements.end(), elem);
    
    if(elemIt != _elements.end())
        _elements.erase(elemIt);
}

OSG_END_NAMESPACE
