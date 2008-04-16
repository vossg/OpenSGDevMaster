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

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGCoredNodeRefPtr.inl
    \ingroup GrpSystemFieldContainer
 */
#endif

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
CoredNodeRefPtr<CoreT>::CoredNodeRefPtr(NodePtr pNode) : 
    _pNode(),
    _pCore()
{
    setNode(pNode                                   );
    setCore(dynamic_cast<CorePtr>(_pNode->getCore()));
}

template<class CoreT> inline
CoredNodeRefPtr<CoreT>::CoredNodeRefPtr(NodeCorePtr pCore) : 
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

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

template<class CoreT> inline
CoredNodeRefPtr<CoreT>::~CoredNodeRefPtr(void)
{
    setCore(NodeCorePtr(NullFC));
    setNode(NullFC             );
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

template <class CoreT>
inline NodePtr
    CoredNodeRefPtr<CoreT>::node(void) const
{
    return _pNode;
}

template<class CoreT>
inline typename CoredNodeRefPtr<CoreT>::CorePtr
    CoredNodeRefPtr<CoreT>::core(void) const
{
#ifdef OSG_DEBUG
    FFASSERT((_pNode->getCore() == _pCore), false, 
             ("CoredNodeRefPtr::core: core changed!"););
#endif

    return _pCore;
}

template<class CoreT>
inline typename CoredNodeRefPtr<CoreT>::CorePtr
    CoredNodeRefPtr<CoreT>::operator->(void) const
{
#ifdef OSG_DEBUG
    FFASSERT((_pNode->getCore() == _pCore), false, 
             ("CoredNodeRefPtr::operator ->: core changed!"););
#endif

    return _pCore;
}

template<class CoreT> inline
CoredNodeRefPtr<CoreT>::operator NodePtr(void)
{
#ifdef OSG_DEBUG
    FFASSERT((_pNode->getCore() == _pCore), false, 
             ("CoredNodeRefPtr::operator NodePtr: core changed!"););
#endif

    return _pNode;
}

template<class CoreT> inline
CoredNodeRefPtr<CoreT>::operator CorePtr(void)
{
#ifdef OSG_DEBUG
    FFASSERT((_pNode->getCore() == _pCore), false, 
             ("CoredNodeRefPtr::operator Core::ObjPtr: core changed!"););
#endif

    return _pCore;
}

/*-------------------------------------------------------------------------*/
/* Assignment                                                              */

template<class CoreT> 
inline typename CoredNodeRefPtr<CoreT>::Self &
    CoredNodeRefPtr<CoreT>::operator =(NodePtr pNode)
{
    setNode(pNode);

    if(_pNode != NullFC)
    {
        setCore(dynamic_cast<CorePtr>(pNode->getCore()));
    }
    else
    {
        setCore(NodeCorePtr(NullFC));
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

/*-------------------------------------------------------------------------*/
/* Access                                                                  */

template <class CoreT>
inline void
    CoredNodeRefPtr<CoreT>::setNode(NodePtrConstArg pNode)
{
    if(_pNode == pNode)
        return;
        
    _pNode = pNode;
}

template<class CoreT>
inline void
    CoredNodeRefPtr<CoreT>::setCore(NodeCorePtrConstArg pCore)
{
    setCore(dynamic_cast<CorePtr>(pCore));
}

template<class CoreT>
inline void
    CoredNodeRefPtr<CoreT>::setCore(CorePtr pCore)
{
    if(_pCore == pCore)
        return;

    _pCore = pCore;
}

template<class CoreT>
inline void
    CoredNodeRefPtr<CoreT>::updateNode(void)
{
    if(node() == NullFC)
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
CoredNodeMTRefPtr<CoreT>::CoredNodeMTRefPtr(NodePtr pNode) : 
    _pNode(),
    _pCore()
{
    setNode(pNode                                   );
    setCore(dynamic_cast<CorePtr>(_pNode->getCore()));
}

template<class CoreT> inline
CoredNodeMTRefPtr<CoreT>::CoredNodeMTRefPtr(NodeCorePtr pCore) : 
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

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

template<class CoreT> inline
CoredNodeMTRefPtr<CoreT>::~CoredNodeMTRefPtr(void)
{
    setCore(NodeCorePtr(NullFC));
    setNode(NullFC             );
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

template <class CoreT>
inline NodePtr
    CoredNodeMTRefPtr<CoreT>::node(void) const
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
CoredNodeMTRefPtr<CoreT>::operator NodePtr(void)
{
#ifdef OSG_DEBUG
    FFASSERT((_pNode->getCore() == _pCore), false, 
             ("CoredNodeMTRefPtr::operator NodePtr: core changed!"););
#endif

    return _pNode;
}

template<class CoreT> inline
CoredNodeMTRefPtr<CoreT>::operator CorePtr(void)
{
#ifdef OSG_DEBUG
    FFASSERT((_pNode->getCore() == _pCore), false, 
             ("CoredNodeMTRefPtr::operator Core::ObjPtr: core changed!"););
#endif

    return _pCore;
}

/*-------------------------------------------------------------------------*/
/* Assignment                                                              */

template<class CoreT> 
inline typename CoredNodeMTRefPtr<CoreT>::Self &
    CoredNodeMTRefPtr<CoreT>::operator =(NodePtr pNode)
{
    setNode(pNode);

    if(_pNode != NullFC)
    {
        setCore(dynamic_cast<CorePtr>(pNode->getCore()));
    }
    else
    {
        setCore(NodeCorePtr(NullFC));
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

template<class CoreT>
inline typename CoredNodeMTRefPtr<CoreT>::Self &
    CoredNodeMTRefPtr<CoreT>::operator =(Self const &pCNRP)
{
    setNode(pCNRP._pNode);
    setCore(pCNRP._pCore);

    return *this;
}

/*-------------------------------------------------------------------------*/
/* Access                                                                  */

template <class CoreT>
inline void
    CoredNodeMTRefPtr<CoreT>::setNode(NodePtrConstArg pNode)
{
    if(_pNode == pNode)
        return;
        
    _pNode = pNode;
}

template<class CoreT>
inline void
    CoredNodeMTRefPtr<CoreT>::setCore(NodeCorePtrConstArg pCore)
{
    setCore(dynamic_cast<CorePtr>(pCore));
}

template<class CoreT>
inline void
    CoredNodeMTRefPtr<CoreT>::setCore(CorePtr pCore)
{
    if(_pCore == pCore)
        return;

    _pCore = pCore;
}

template<class CoreT>
inline void
    CoredNodeMTRefPtr<CoreT>::updateNode(void)
{
    if(node() == NullFC)
    {
        setNode(NodeRefPtr(Node::create()));
    }

    node()->setCore(_pCore);
}


OSG_END_NAMESPACE


