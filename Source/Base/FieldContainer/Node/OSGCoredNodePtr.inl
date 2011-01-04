/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                     Copyright 2000-2002 by OpenSG Forum                   *
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
/* CoredNodeRefPtr<CoreT>                                                  */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/* Constructors                                                            */

template<class CoreT> inline
CoredNodeRefPtr<CoreT>::CoredNodeRefPtr(void) : 
    _pNode(),
    _pCore()
{
}

template<class CoreT> inline
CoredNodeRefPtr<CoreT>::CoredNodeRefPtr(Node *pNode) : 
    _pNode(),
    _pCore()
{
    setNode(pNode);
    
    if(pNode != NULL)
        setCore(dynamic_cast<CorePtr>(_pNode->getCore()));
}

template<class CoreT> inline
CoredNodeRefPtr<CoreT>::CoredNodeRefPtr(NodeCore *pCore) : 
    _pNode(),
    _pCore()
{
    setCore(dynamic_cast<CorePtr>(pCore));

    updateNode();
}

template<class CoreT> inline
CoredNodeRefPtr<CoreT>::CoredNodeRefPtr(CorePtr pCore) : 
    _pNode(),
    _pCore()
{
    setCore(pCore);

    updateNode();
}

template<class CoreT> inline
CoredNodeRefPtr<CoreT>::CoredNodeRefPtr(Self const &pCore) : 
    _pNode(),
    _pCore()
{
    setCore(pCore._pCore);
    setNode(pCore._pNode);
}

template<class CoreT> inline
CoredNodeRefPtr<CoreT>::CoredNodeRefPtr(CoreTransitPtr pCore) : 
    _pNode(),
    _pCore()
{
    _pCore = pCore;

    updateNode();
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

template<class CoreT> inline
CoredNodeRefPtr<CoreT>::~CoredNodeRefPtr(void)
{
    setCore(CorePtr(NULL));
    setNode(NULL         );
}

/*-------------------------------------------------------------------------*/
/* Create                                                                  */

template<class CoreT> inline
CoredNodeRefPtr<CoreT> CoredNodeRefPtr<CoreT>::create(void)
{
    return CoredNodeRefPtr<CoreT>(CoreRefPtr(Core::create()));
}

/*-------------------------------------------------------------------------*/
/* Access                                                                  */

template<class CoreT> inline
void CoredNodeRefPtr<CoreT>::coreChanged(void)
{
    setCore(_pNode->getCore());
}

template <class CoreT> inline 
Node *CoredNodeRefPtr<CoreT>::node(void) const
{
    return _pNode;
}

template<class CoreT> inline 
typename CoredNodeRefPtr<CoreT>::CorePtr
    CoredNodeRefPtr<CoreT>::core(void) const
{
#ifdef OSG_DEBUG
    FFASSERT((_pNode->getCore() == _pCore), false, 
             ("CoredNodeRefPtr::core: core changed!"););
#endif

    return _pCore;
}

template<class CoreT> inline 
typename CoredNodeRefPtr<CoreT>::CorePtr
    CoredNodeRefPtr<CoreT>::operator->(void) const
{
#ifdef OSG_DEBUG
    FFASSERT((_pNode->getCore() == _pCore), false, 
             ("CoredNodeRefPtr::operator ->: core changed!"););
#endif

    return _pCore;
}

template<class CoreT> inline
CoredNodeRefPtr<CoreT>::operator Node *(void)
{
#ifdef OSG_DEBUG
    FFASSERT((_pNode->getCore() == _pCore), false, 
             ("CoredNodeRefPtr::operator NodePtr: core changed!"););
#endif

    return _pNode;
}

#ifndef OSG_DOXYGEN_IGNORE_RECOG_PROBS
template<class CoreT> inline
CoredNodeRefPtr<CoreT>::operator typename CoredNodeRefPtr<CoreT>::CorePtr(void)
{
#ifdef OSG_DEBUG
    FFASSERT((_pNode->getCore() == _pCore), false, 
             ("CoredNodeRefPtr::operator Core::ObjPtr: core changed!"););
#endif

    return _pCore;
}
#endif

/*-------------------------------------------------------------------------*/
/* Assignment                                                              */

template<class CoreT> 
inline typename CoredNodeRefPtr<CoreT>::Self &
    CoredNodeRefPtr<CoreT>::operator =(Node *pNode)
{
    setNode(pNode);

    if(_pNode != NULL)
    {
        setCore(dynamic_cast<CorePtr>(pNode->getCore()));
    }
    else
    {
        setCore(CorePtr(NULL));
    }

    return *this;
}

template<class CoreT> 
inline typename CoredNodeRefPtr<CoreT>::Self &
    CoredNodeRefPtr<CoreT>::operator =(NodeTransitPtr pNode)
{
    setNode(pNode);

    if(_pNode != NULL)
    {
        setCore(dynamic_cast<CorePtr>(_pNode->getCore()));
    }
    else
    {
        setCore(CorePtr(NULL));
    }

    return *this;
}

template<class CoreT>
inline typename CoredNodeRefPtr<CoreT>::Self &
    CoredNodeRefPtr<CoreT>::operator =(CorePtr pCore)
{
    setCore(pCore);

    updateNode();

    return *this;
}

template<class CoreT>
inline typename CoredNodeRefPtr<CoreT>::Self &
    CoredNodeRefPtr<CoreT>::operator =(Self const &pCNRP)
{
    setNode(pCNRP._pNode);
    setCore(pCNRP._pCore);

    return *this;
}

template<class CoreT>
inline typename CoredNodeRefPtr<CoreT>::Self &
    CoredNodeRefPtr<CoreT>::operator =(CoreTransitPtr pCore)
{
    if(pCore != _pCore)
        _pCore = pCore;

    updateNode();

    return *this;
}

/*-------------------------------------------------------------------------*/
/* Access                                                                  */

template <class CoreT> inline 
void CoredNodeRefPtr<CoreT>::setNode(Node * const pNode)
{
    if(_pNode == pNode)
        return;
        
    _pNode = pNode;
}

template <class CoreT> inline 
void CoredNodeRefPtr<CoreT>::setNode(NodeTransitPtr pNode)
{
    if(pNode == _pNode)
        return;
        
    _pNode = pNode;
}

template<class CoreT> inline 
void CoredNodeRefPtr<CoreT>::setCore(NodeCore * const pCore)
{
    setCore(dynamic_cast<CorePtr>(pCore));
}

template<class CoreT> inline 
void CoredNodeRefPtr<CoreT>::setCore(CorePtr pCore)
{
    if(_pCore == pCore)
        return;

    _pCore = pCore;
}

template<class CoreT> inline 
void CoredNodeRefPtr<CoreT>::updateNode(void)
{
    if(node() == NULL)
    {
        setNode(NodeRefPtr(Node::create()));
    }

    node()->setCore(_pCore);
}

/*-------------------------------------------------------------------------*/
/* CoredNodeMTRefPtr<CoreT>                                                  */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/* Constructors                                                            */

template<class CoreT> inline
CoredNodeMTRefPtr<CoreT>::CoredNodeMTRefPtr(void) : 
    _pNode(),
    _pCore()
{
}

template<class CoreT> inline
CoredNodeMTRefPtr<CoreT>::CoredNodeMTRefPtr(Node *pNode) : 
    _pNode(),
    _pCore()
{
    setNode(pNode                                   );
    setCore(dynamic_cast<CorePtr>(_pNode->getCore()));
}

template<class CoreT> inline
CoredNodeMTRefPtr<CoreT>::CoredNodeMTRefPtr(NodeCore *pCore) : 
    _pNode(),
    _pCore()
{
    setCore(dynamic_cast<CorePtr>(pCore));

    updateNode();
}

template<class CoreT> inline
CoredNodeMTRefPtr<CoreT>::CoredNodeMTRefPtr(CorePtr pCore) : 
    _pNode(),
    _pCore()
{
    setCore(pCore);

    updateNode();
}

template<class CoreT> inline
CoredNodeMTRefPtr<CoreT>::CoredNodeMTRefPtr(Self const &pCore) : 
    _pNode(),
    _pCore()
{
    setCore(pCore._pCore);
    setNode(pCore._pNode);
}

template<class CoreT> inline
CoredNodeMTRefPtr<CoreT>::CoredNodeMTRefPtr(CoreTransitPtr pCore) : 
    _pNode(),
    _pCore()
{
    _pCore = pCore;

    updateNode();
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

template<class CoreT> inline
CoredNodeMTRefPtr<CoreT>::~CoredNodeMTRefPtr(void)
{
    setCore(CorePtr(NULL));
    setNode(NULL         );
}

/*-------------------------------------------------------------------------*/
/* Create                                                                  */

template<class CoreT> inline
CoredNodeMTRefPtr<CoreT> CoredNodeMTRefPtr<CoreT>::create(void)
{
    return CoredNodeMTRefPtr<CoreT>(CoreMTRefPtr(Core::create()));
}

/*-------------------------------------------------------------------------*/
/* Access                                                                  */

template<class CoreT> inline
void CoredNodeMTRefPtr<CoreT>::coreChanged(void)
{
    setCore(_pNode->getCore());
}

template <class CoreT> inline 
Node *CoredNodeMTRefPtr<CoreT>::node(void) const
{
    return _pNode;
}

template<class CoreT>
inline typename CoredNodeMTRefPtr<CoreT>::CorePtr
    CoredNodeMTRefPtr<CoreT>::core(void) const
{
#ifdef OSG_DEBUG
    FFASSERT((_pNode->getCore() == _pCore), false, 
             ("CoredNodeMTRefPtr::core: core changed!"););
#endif

    return _pCore;
}

template<class CoreT>
inline typename CoredNodeMTRefPtr<CoreT>::CorePtr
    CoredNodeMTRefPtr<CoreT>::operator->(void) const
{
#ifdef OSG_DEBUG
    FFASSERT((_pNode->getCore() == _pCore), false, 
             ("CoredNodeMTRefPtr::operator ->: core changed!"););
#endif

    return _pCore;
}

template<class CoreT> inline
CoredNodeMTRefPtr<CoreT>::operator Node *(void)
{
#ifdef OSG_DEBUG
    FFASSERT((_pNode->getCore() == _pCore), false, 
             ("CoredNodeMTRefPtr::operator NodePtr: core changed!"););
#endif

    return _pNode;
}

#ifndef OSG_DOXYGEN_IGNORE_RECOG_PROBS
template<class CoreT> inline
CoredNodeMTRefPtr<CoreT>::operator 
    typename CoredNodeMTRefPtr<CoreT>::CorePtr(void)
{
#ifdef OSG_DEBUG
    FFASSERT((_pNode->getCore() == _pCore), false, 
             ("CoredNodeMTRefPtr::operator Core::ObjPtr: core changed!"););
#endif

    return _pCore;
}
#endif

/*-------------------------------------------------------------------------*/
/* Assignment                                                              */

template<class CoreT> 
inline typename CoredNodeMTRefPtr<CoreT>::Self &
    CoredNodeMTRefPtr<CoreT>::operator =(Node *pNode)
{
    setNode(pNode);

    if(_pNode != NULL)
    {
        setCore(dynamic_cast<CorePtr>(pNode->getCore()));
    }
    else
    {
        setCore(CorePtr(NULL));
    }

    return *this;
}

template<class CoreT>
inline typename CoredNodeMTRefPtr<CoreT>::Self &
    CoredNodeMTRefPtr<CoreT>::operator =(CorePtr pCore)
{
    setCore(pCore);

    updateNode();

    return *this;
}

template<class CoreT> inline 
typename CoredNodeMTRefPtr<CoreT>::Self &
    CoredNodeMTRefPtr<CoreT>::operator =(Self const &pCNRP)
{
    setNode(pCNRP._pNode);
    setCore(pCNRP._pCore);

    return *this;
}

template<class CoreT>
inline typename CoredNodeMTRefPtr<CoreT>::Self &
    CoredNodeMTRefPtr<CoreT>::operator =(CoreTransitPtr pCore)
{
    if(_pCore != pCore)
        _pCore = pCore;

    updateNode();

    return *this;
}

/*-------------------------------------------------------------------------*/
/* Access                                                                  */

template <class CoreT> inline 
void CoredNodeMTRefPtr<CoreT>::setNode(Node * const pNode)
{
    if(_pNode == pNode)
        return;
        
    _pNode = pNode;
}

template<class CoreT> inline 
void CoredNodeMTRefPtr<CoreT>::setCore(NodeCore * const pCore)
{
    setCore(dynamic_cast<CorePtr>(pCore));
}

template<class CoreT> inline 
void CoredNodeMTRefPtr<CoreT>::setCore(CorePtr pCore)
{
    if(_pCore == pCore)
        return;

    _pCore = pCore;
}

template<class CoreT> inline 
void CoredNodeMTRefPtr<CoreT>::updateNode(void)
{
    if(node() == NULL)
    {
        setNode(NodeRefPtr(Node::create()));
    }

    node()->setCore(_pCore);
}


OSG_END_NAMESPACE


