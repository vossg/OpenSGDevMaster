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
RenderTreeNode *RenderTreeNode::getFirstChild(void)
{
    return _pFirstChild;
}

inline
RenderTreeNode *RenderTreeNode::getLastChild(void)
{
    return _pLastChild;
}


inline
RenderTreeNode *RenderTreeNode::getBrother(void)
{
    return _pBrother;
}

inline
void RenderTreeNode::setBrother(RenderTreeNode *pBrother)
{
    _pBrother = pBrother;
}

inline
void RenderTreeNode::insertBrother(RenderTreeNode *pBrother)
{
    if(_pBrother != NULL)
        pBrother->setBrother(_pBrother);

    _pBrother = pBrother;
}

inline
void RenderTreeNode::addChild(RenderTreeNode *pChild)
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
void RenderTreeNode::insertFirstChild(RenderTreeNode *pChild)
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
void RenderTreeNode::insertChildAfter(RenderTreeNode *pCurrent, 
                                      RenderTreeNode *pChild)
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
void RenderTreeNode::setFunctor(DrawFunctor &func)
{
    _functor=func;
    _hasFunctor=true;
}

inline
Material::DrawFunctor &RenderTreeNode::getFunctor(void)
{
    return _functor;
}

inline
bool RenderTreeNode::hasFunctor(void)
{
    return _hasFunctor;
}

inline
void RenderTreeNode::setState(State *pState)
{
    _pState = pState;
}

inline
State *RenderTreeNode::getState(void)
{
    return _pState;
}

inline
void RenderTreeNode::setStateOverride(StateOverride *pStateOverride)
{
    _pStateOverride = pStateOverride;
}

inline
StateOverride *RenderTreeNode::getStateOverride(void)
{
    return _pStateOverride;
}

inline
void RenderTreeNode::setMatrixStore(const MatrixStore &oMatrixStore)
{
    _oMatrixStore = oMatrixStore;
}

inline
RenderTreeNode::MatrixStore &RenderTreeNode::getMatrixStore(void)
{
    return _oMatrixStore;
}

inline
void RenderTreeNode::setScalar(Real32 rScalar)
{
    _rScalarVal = rScalar;
}

inline
Real32 RenderTreeNode::getScalar(void)
{
    return _rScalarVal;
}

inline
void RenderTreeNode::setVol(const BoxVolume &vol)
{
    _bVol = vol;
}

inline
BoxVolume RenderTreeNode::getVol(void)
{
    return _bVol;
}

inline
void  RenderTreeNode::setResultNum(UInt32 uiResNum)
{
    _resultNum = uiResNum;
}

inline
UInt32 RenderTreeNode::getResultNum(void)
{
    return _resultNum;
}

inline
void  RenderTreeNode::setIsRendered(bool bRendered)
{
    _isRendered = bRendered;
}

inline
bool RenderTreeNode::getIsRendered(void)
{
    return _isRendered;
}


inline
void RenderTreeNode::setLightsState(UInt64 state)
{
    _lightsState = state;
}

inline
UInt64 RenderTreeNode::getLightsState(void)
{
    return _lightsState;
}

inline
void RenderTreeNode::setNode(Node *pNode)
{
    _node = pNode;
}

inline
Node *RenderTreeNode::getNode(void)
{
    return _node;
}

inline
void RenderTreeNode::reset(void)
{
    _pFirstChild    = NULL;
    _pLastChild     = NULL;
    _pBrother       = NULL;
    _pState         = NULL;
    _pStateOverride = NULL;
    _hasFunctor     = false;

    _oMatrixStore.first = 0;
    _oMatrixStore.second.setIdentity();

    _rScalarVal  = 0.f;

    _lightsState = 0;
}

OSG_END_NAMESPACE
