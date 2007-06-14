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


OSG_BEGIN_NAMESPACE

/*-------------------------------------------------------------------------*/
/*                               Access                                    */

inline
DrawTreeNode *DrawTreeNode::getFirstChild(void)
{
    return _pFirstChild;
}

inline
DrawTreeNode *DrawTreeNode::getLastChild(void)
{
    return _pLastChild;
}

inline
DrawTreeNode *DrawTreeNode::getBrother(void)
{
    return _pBrother;
}

inline
void DrawTreeNode::setBrother(DrawTreeNode *pBrother)
{
    _pBrother = pBrother;
}


inline
void DrawTreeNode::addChild(DrawTreeNode *pChild)
{
    if(_pLastChild == NULL)
    {
        _pFirstChild = pChild;
        _pLastChild  = pChild;
    }
    else
    {
        _pLastChild->setBrother(pChild);
        _pLastChild = pChild;
    }
}

inline
void DrawTreeNode::insertFirstChild  (DrawTreeNode *pChild)
{
    if(pChild == NULL)
        return;

    if(_pFirstChild == NULL)
    {
        addChild(pChild);
    }
    else
    {
        pChild->setBrother(_pFirstChild);
        
        _pFirstChild = pChild;
    }
    
}

inline
void DrawTreeNode::insertChildAfter(DrawTreeNode *pCurrent, 
                                    DrawTreeNode *pChild)
{
    if(pCurrent == NULL || pChild == NULL)
        return;

    pChild  ->setBrother(pCurrent->getBrother());
    pCurrent->setBrother(pChild  );

    if(pCurrent == _pLastChild)
    {
        _pLastChild = pChild;
    }    
}


inline
void DrawTreeNode::setGeometry(MaterialDrawable *pGeo)
{
    _pGeo = pGeo;
}

inline
MaterialDrawable *DrawTreeNode::getGeometry(void)
{
    return _pGeo;
}

inline
void DrawTreeNode::setFunctor(Material::DrawFunctor &func)
{
    _functor=func;
    _hasFunctor=true;
}

inline
Material::DrawFunctor &DrawTreeNode::getFunctor(void)
{
    return _functor;
}

inline
bool DrawTreeNode::hasFunctor(void)
{
    return _hasFunctor;
}

inline
void DrawTreeNode::setState(State *pState)
{
    _pState = pState;
}

inline
State *DrawTreeNode::getState(void)
{
    return _pState;
}

inline
void DrawTreeNode::setNode(NodePtr pNode)
{
    _pNode = pNode;
}

inline
NodePtr DrawTreeNode::getNode(void)
{
    return _pNode;
}

inline
void DrawTreeNode::setMatrixStore(const MatrixStore &oMatrixStore)
{
    _oMatrixStore = oMatrixStore;
}

inline
DrawTreeNode::MatrixStore &DrawTreeNode::getMatrixStore(void)
{
    return _oMatrixStore;
}

inline
void DrawTreeNode::setScalar(Real rScalar)
{
    _rScalarVal = rScalar;
}

inline
Real DrawTreeNode::getScalar(void)
{
    return _rScalarVal;
}

inline
void DrawTreeNode::setLightsState(UInt64 state)
{
    _lightsState = state;
}

inline
UInt64 DrawTreeNode::getLightsState(void)
{
    return _lightsState;
}

inline
void DrawTreeNode::setClipPlanesState(UInt32 state)
{
    _clipPlanesState = state;
}

inline
UInt32 DrawTreeNode::getClipPlanesState(void)
{
    return _clipPlanesState;
}

inline
void DrawTreeNode::setMultiPass(void)
{
    _flags |= DrawTreeNode::MultiPass;
}

inline
void DrawTreeNode::setLastMultiPass(void)
{
    _flags |= DrawTreeNode::LastMultiPass;
}

inline
bool DrawTreeNode::isMultiPass(void)
{
    return (_flags & DrawTreeNode::MultiPass) ||
           (_flags & DrawTreeNode::LastMultiPass);
}

inline
bool DrawTreeNode::isLastMultiPass(void)
{
    return (_flags & DrawTreeNode::LastMultiPass);
}

inline
void DrawTreeNode::setNoStateSorting(void)
{
    _flags |= DrawTreeNode::NoStateSorting;
}

inline
bool DrawTreeNode::isNoStateSorting(void)
{
    return (_flags & DrawTreeNode::NoStateSorting);
}

inline
void DrawTreeNode::reset(void)
{
    _pFirstChild = NULL;
    _pLastChild  = NULL;
    _pBrother    = NULL;
    _pState      = NULL;
    _pGeo        = NULL;
    _hasFunctor  = false;

    _oMatrixStore.first = 0;
    _oMatrixStore.second.setIdentity();

    _rScalarVal  = 0.f;

    _lightsState = 0;
    _flags       = 0;
}

OSG_END_NAMESPACE
