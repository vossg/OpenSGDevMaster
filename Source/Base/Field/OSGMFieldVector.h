/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2003 by the OpenSG Forum                   *
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

#ifndef _OSGMFIELDVECTOR_H_
#define _OSGMFIELDVECTOR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"

#include <vector>

OSG_BEGIN_NAMESPACE

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGMFieldVector.h
    \ingroup GrpBaseField
    \ingroup GrpBaseFieldMulti
 */
#endif

#if defined(__sgi) || defined(__linux) || defined(darwin) || \
    defined(__sun) || defined(__hpux)

#if defined(__sgi)
#pragma set woff 1375
#endif

#if defined(__linux) || defined(__hpux) || defined(darwin) || defined(__sun)
#    if defined(__GNUC__)
#        if __GNUC__ >= 3
#            define OSG_STL_DEFAULT_ALLOCATOR(TP) = std::allocator<TP>
#        endif
#    elif defined (__ICL)
#        define OSG_STL_DEFAULT_ALLOCATOR(TP) = std::allocator<TP>
#    elif defined (OSG_HPUX_ACC)
#        define OSG_STL_DEFAULT_ALLOCATOR(TP) _RWSTD_COMPLEX_DEFAULT(std::allocator<TP>)
#    elif defined(OSG_SUN_CC)
#        define OSG_STL_DEFAULT_ALLOCATOR(TP) _RWSTD_COMPLEX_DEFAULT(std::allocator<TP>)
#    else
#        define OSG_STL_DEFAULT_ALLOCATOR(TP) = std::__STL_DEFAULT_ALLOCATOR(TP)
#    endif
#else
#    define OSG_STL_DEFAULT_ALLOCATOR(TP) = std::__STL_DEFAULT_ALLOCATOR(TP)
#endif

/*! \ingroup GrpBaseField
    \ingroup GrpBaseFieldMulti
    \hideinhierarchy
 */

template <class Tp, class Alloc OSG_STL_DEFAULT_ALLOCATOR(Tp) >
class MFieldVector : public std::vector<Tp, Alloc> 
{
  public:

    typedef std::vector<Tp, Alloc> Inherited;

  private:

    typedef MFieldVector<Tp, Alloc> Self;
    
  public:

    typedef typename Inherited::allocator_type allocator_type;
    typedef typename Inherited::size_type      size_type;

    explicit MFieldVector(const allocator_type& __a = allocator_type());

             MFieldVector(      size_type       __n, 
                          const Tp             &__value,
                          const allocator_type &__a    = allocator_type());

    explicit MFieldVector(size_type __n);
    
             MFieldVector(const std::vector <Tp, Alloc>& __x);
             MFieldVector(const MFieldVector<Tp, Alloc>& __x);

#ifdef __STL_MEMBER_TEMPLATES
  // Check whether it's an integral type.  If so, it's not an iterator.
             template <class InputIterator>
             MFieldVector(      InputIterator   __first, 
                                InputIterator   __last,
                          const allocator_type &__a = allocator_type());
#else
             MFieldVector(const Tp             *__first, 
                          const Tp             *__last,
                          const allocator_type &__a = allocator_type());
#endif /* __STL_MEMBER_TEMPLATES */

    ~MFieldVector();

    void shareValues (Self &other, bool bDeleteOld);
    void resolveShare(void                        );

    void dump(      UInt32    uiIndent = 0, 
              const BitVector bvFlags  = 0) const;
};

#if defined(__sgi)
#pragma reset woff 1375
#endif

#elif defined(WIN32)

/*! \ingroup GrpBaseField
    \ingroup GrpBaseFieldMulti
    \hideinhierarchy
 */

template<class Ty, class A = std::allocator<Ty> >
class MFieldVector : public std::vector<Ty, A>
{
  public:

    typedef          std::vector<Ty, A>        Inherited;

  private :

	typedef typename Inherited::const_iterator It;

    typedef           MFieldVector<Ty, A>      Self;

  public :	

    explicit MFieldVector(const A& _Al = A());

	explicit MFieldVector(      size_type  _N, 
                          const Ty        &_V  = Ty(),
                          const A         &_Al = A ());

	MFieldVector(const MFieldVector<Ty, A> &_X);


	MFieldVector(      It  _F, 
                       It  _L, 
                 const A  &_Al = A());

	~MFieldVector(void);

    void shareValues (Self &other, bool bDeleteOld);
    void resolveShare(void                        );
};

#endif

OSG_END_NAMESPACE

#define OSGMFIELDVECTOR_HEADER_CVSID "@(#)$Id: $"

#include "OSGMFieldVector.inl"

#endif /* _OSGMFIELDVECTOR_H_ */
