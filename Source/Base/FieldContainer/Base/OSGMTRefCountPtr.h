/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                       Copyright 2009 by OpenSG Forum                      *
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

#ifndef _OSGMTREFCOUNTPOINTER_H_
#define _OSGMTREFCOUNTPOINTER_H_

#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGBaseFunctions.h"
#include "OSGContainerForwards.h"
#include "OSGRefCountPtr.h"

#include <boost/mpl/if.hpp>

OSG_BEGIN_NAMESPACE

template <class ObjectT>
class TransitPtr;

template <class ObjectT, class RefCountPolicyT>
class RefCountPtr;

template <class ObjectT, class RefCountPolicyT>
class MTRefCountPtr;

/*! \ingroup GrpBaseBase
    \ingroup GrpBaseBaseMemory
    \ingroup GrpBaseBaseRefCounting
    \ingroup GrpBaseFieldContainerBase
    \ingroup GrpLibOSGBase
    \nohierarchy
 */

template <class ObjectT, 
          class RefCountPolicyT>
class MTRefCountPtr
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name Public Types                                                 */
    /*! \{                                                                 */
  
    typedef ObjectT                                          Object;
    typedef RefCountPolicyT                                  RefCountPolicy;
    typedef MTRefCountPtr<Object, 
                          RefCountPolicy>                    Self;
    typedef TransitPtr<ObjectT>                              ObjectTransitPtr;
                                           
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constructors                                                 */
    /*! \{                                                                 */
  
    MTRefCountPtr(void                          );
    MTRefCountPtr(Self              const &other);
   
    MTRefCountPtr(Object          * const  pObj );

    MTRefCountPtr(ObjectTransitPtr  const &other);

    template <class OtherObjectT>
    MTRefCountPtr(TransitPtr<OtherObjectT> const &other);
    
    template <class OtherObjectT, class OtherRefCountPolicyT>
    MTRefCountPtr(MTRefCountPtr<OtherObjectT,
                                OtherRefCountPolicyT> const &other);

    template <class OtherObjectT, class OtherRefCountPolicyT>
    MTRefCountPtr(RefCountPtr<OtherObjectT,
                              OtherRefCountPolicyT> const &other);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Desctructor                                                  */
    /*! \{                                                                 */

    ~MTRefCountPtr(void);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Assignment                                                   */
    /*! \{                                                                 */
    
    Self &operator =(const Self             &       other    );
    Self &operator =(      Object           * const pOtherObj);
    Self &operator =(const ObjectTransitPtr &       other    );

    template <class OtherObjectT, class OtherRefCountPolicyT>
    Self &operator =(const MTRefCountPtr<OtherObjectT,
                                         OtherRefCountPolicyT> &refPtr);

    template <class OtherObjectT, class OtherRefCountPolicyT>
    Self &operator =(const RefCountPtr<OtherObjectT,
                                       OtherRefCountPolicyT>   &refPtr);
   
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Conversion                                                   */
    /*! \{                                                                 */
    
    operator Object *(void) const;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Access                                                       */
    /*! \{                                                                 */
    
    Object *operator->(void) const;
    Object &operator *(void) const;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Access                                                       */
    /*! \{                                                                 */

    Object *get (void                    ) const;
#if 0
    void    set (Object * const objectPtr);
#endif
    
    void    swap(Self   &       other    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Access                                                       */
    /*! \{                                                                 */

    void shutdownSetNull(void);

#if defined(OSG_1_COMPAT)
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Access                                                       */
    /*! \{                                                                 */

           MTRefCountPtr(const NullFCType);

           bool    operator ==(const NullFCType                ) const;
           bool    operator !=(const NullFCType                ) const;

           Object *getCPtr    (      void                      ) const;

    static Self    dcast      (      FieldContainer * const src);

           Int32   getRefCount(void                            ) const;
#endif

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*==========================  PRIVATE  ================================*/

    /*---------------------------------------------------------------------*/
    /*! \name Member                                                       */
    /*! \{                                                                 */
    
    AspectStore *_pAspectStore;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

  private:

    /*---------------------------------------------------------------------*/
    /*! \name Friends                                                      */
    /*! \{                                                                 */

    template <class OtherObjectT, class OtherRefCountPolicyT>
    friend class MTRefCountPtr;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
  
};

/*! \ingroup GrpBaseBaseRefCounting
    \relatesalso MTRefCountPtr
 */
       
template <class TargetT, class SourceT, class RCPolicyT> inline
OSG::MTRefCountPtr<TargetT, RCPolicyT> dynamic_pointer_cast(
    OSG::MTRefCountPtr<SourceT, RCPolicyT> const &source);

/*! \ingroup GrpBaseBaseRefCounting
    \relatesalso MTRefCountPtr
 */

template <class TargetT, class SourceT, class RCPolicyT> inline
OSG::MTRefCountPtr<TargetT, RCPolicyT> static_pointer_cast(
    OSG::MTRefCountPtr<SourceT, RCPolicyT> const &source);

/*! The same as refPtr.get(), for interoperability with boost::bind.

    \ingroup GrpBaseBaseRefCounting
    \relatesalso MTRefCountPtr
 */

template <class ObjectT, class RCPolicyT> inline
ObjectT *get_pointer(const OSG::MTRefCountPtr<ObjectT, RCPolicyT> &refPtr);

#if defined(OSG_1_COMPATX)
template <class TargetT, class SourceT> inline
MTRefCountPtr<typename TargetT::Object, 
              typename TargetT::RefCountPolicy> 
    dynamic_pointer_cast(SourceT * const pIn);
#endif

OSG_END_NAMESPACE

#include "OSGMTRefCountPtr.inl"

#endif // _OSGMTREFCOUNTPOINTER_H_
