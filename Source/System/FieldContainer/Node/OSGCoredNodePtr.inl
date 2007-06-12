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
/*! \file OSGCoredNodePtr.inl
    \ingroup GrpSystemFieldContainer
 */
#endif

OSG_BEGIN_NAMESPACE

inline
CoredNodePtrBase::CoredNodePtrBase(void) : 
    _pNode(NullFC)
{
}

inline
CoredNodePtrBase::CoredNodePtrBase(NodePtr pNode) :
    _pNode(NullFC)
{
    setNode(pNode);
}

inline
CoredNodePtrBase::~CoredNodePtrBase(void)
{
    setNode(NullFC);
}

inline
NodePtr CoredNodePtrBase::node(void) const
{ 
    return _pNode; 
}

inline
void CoredNodePtrBase::setNode(NodePtrConstArg pNode)
{
    if(_pNode == pNode)
        return;

    setRefd(_pNode, pNode);
}

#ifdef OSG_MT_FIELDCONTAINERPTR
#if 0
inline
void CoredNodePtrBase::setNode(const NilFieldContainerPtr &)
{
    if(_pNode != NullFC)
        subRef(_pNode);

    _pNode = NullFC;
}
#endif
#endif

// CoredNodePtr methods

template<class Core> inline
CoredNodePtr<Core>::CoredNodePtr(void) : 
     Inherited(NullFC), 
    _pCore    (NullFC)
{
}

template<class Core> inline
CoredNodePtr<Core>::CoredNodePtr(const NodePtr &pNode) : 
     Inherited(pNode),
    _pCore    (NullFC)
{
    setCore(cast_dynamic<CorePtr>(Inherited::node()->getCore()));
}

template<class Core> inline
CoredNodePtr<Core>::CoredNodePtr(const NodeCorePtr &pCore) : 
     Inherited(      ),
    _pCore    (NullFC)
{
    setCore(cast_dynamic<CorePtr>(pCore));

    updateNode();
}

template<class Core> inline
CoredNodePtr<Core>::CoredNodePtr(const typename Core::ObjPtr &pCore) : 
     Inherited(      ),
    _pCore    (NullFC)
{
    setCore(pCore);

    updateNode();
}

template<class Core> inline
CoredNodePtr<Core>::CoredNodePtr(const CoredNodePtr<Core> &pCore) : 
     Inherited(      ),
    _pCore    (NullFC)
{
    setCore(pCore._pCore  );
    setNode(pCore. node());
}

template<class Core> inline
CoredNodePtr<Core>::~CoredNodePtr(void)
{
    setCore(NodeCorePtr(NullFC));
    setNode(NullFC             );
}

template<class Core> inline
CoredNodePtr<Core> CoredNodePtr<Core>::create(void)
{
    return CoredNodePtr<Core>(Core::create());
}

template<class Core> inline
void CoredNodePtr<Core>::coreChanged(void)
{
    setCore(node()->getCore());
}

template<class Core> inline
typename Core::ObjPtr CoredNodePtr<Core>::core(void) const
{
#ifdef OSG_DEBUG
    FFASSERT((node()->getCore() == _pCore), false, 
              ("CoredNodePtr::core: core changed!"););
#endif

    return _pCore;
}

template<class Core> inline
typename Core::ObjPtr &CoredNodePtr<Core>::operator->(void)
{
#ifdef OSG_DEBUG
    FFASSERT((node()->getCore() == _pCore), false, 
              ("CoredNodePtr::operator ->: core changed!"););
#endif

    return _pCore;
}

template<class Core> inline
CoredNodePtr<Core>::operator NodePtr(void)
{
#ifdef OSG_DEBUG
    FFASSERT((node()->getCore() == _pCore), false, 
              ("CoredNodePtr::operator NodePtr: core changed!"););
#endif

    return node();
}

template<class Core> inline
CoredNodePtr<Core>::operator typename Core::ObjPtr(void)
{
#ifdef OSG_DEBUG
    FFASSERT((node()->getCore() == _pCore), false, 
              ("CoredNodePtr::operator Core::ObjPtr: core changed!"););
#endif

    return _pCore;
}

/* Assignment. Create a new CNP if necessary */

template<class Core> inline
CoredNodePtr<Core> &CoredNodePtr<Core>::operator =(const NodePtr &pNode)
{
    setNode(pNode);

    setCore(cast_dynamic<CorePtr>(pNode->getCore()));

    return *this;
}

template<class Core> inline
CoredNodePtr<Core>& CoredNodePtr<Core>::operator =(
    const typename Core::ObjPtr &pCore)
{
    setCore(pCore);

    updateNode();

    return *this;
}

template<class Core> inline
CoredNodePtr<Core>& CoredNodePtr<Core>::operator =(
    const CoredNodePtr<Core> &pCNP)
{
    setNode(pCNP.node());
    setCore(pCNP._pCore);

    return *this;
}

#ifdef OSG_MT_FIELDCONTAINERPTR
#if 0
template<class Core> inline
CoredNodePtr<Core>& CoredNodePtr<Core>::operator =(
    const NilFieldContainerPtr &)
{
    setNode(NullFC);
    setCore(NullFC);

    return *this;
}
#endif
#endif

template<class Core> inline
NodeCorePtr CoredNodePtr<Core>::getCoreV(void) const
{
    return _pCore;
}

template<class Core> inline
void CoredNodePtr<Core>::setCore(const NodeCorePtr &pCore)
{
    setCore(cast_dynamic<CorePtr>(pCore));
}

template<class Core> inline
void CoredNodePtr<Core>::setCore(const typename Core::ObjPtr &pCore)
{
    if(_pCore == pCore)
        return;

    setRefd(_pCore, pCore);
}

#ifdef OSG_MT_FIELDCONTAINERPTR
template<class Core> inline
void CoredNodePtr<Core>::setCore(const NilFieldContainerPtr &)
{
    if(_pCore != NullFC)
        subRef(_pCore);

    _pCore = NullFC;
}
#endif

template<class Core> inline
void CoredNodePtr<Core>::updateNode(void)
{
    if(node() == NullFC)
    {
        setNode(Node::create());
    }

    node()->setCore(_pCore);
}

OSG_END_NAMESPACE


