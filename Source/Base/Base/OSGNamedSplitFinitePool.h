/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2000,2001,2002 by the OpenSG Forum                *
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

#ifndef _OSGNAMEDFINITEPOOL_H_
#define _OSGNAMEDFINITEPOOL_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGBaseTypes.h"

#include <boost/type_traits/is_pod.hpp>
#include <boost/mpl/if.hpp>

#include <vector>
#include <deque>

OSG_BEGIN_NAMESPACE

class PoolDefaultTag;

/*! \ingroup GrpBaseBasePools
    \ingroup GrpBaseBase
    \ingroup GrpLibOSGBase
    \nohierarchy
*/

template <class    ValueT, 
          typename SplitInfo,
          class    PoolTag    = PoolDefaultTag,
          class    LockPolicy = NoLockPolicy>
class NamedSplitFinitePool 
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef typename boost::mpl::if_< boost::is_pod<ValueT>,
                                      ValueT,
                                      ValueT *>::type StoredType;

    typedef          ValueT                           ValueType;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    NamedSplitFinitePool(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~NamedSplitFinitePool(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      create                                  */
    /*! \{                                                                 */

          StoredType  getFrom1(const Char8      *szName );
          StoredType  getFrom2(const Char8      *szName );
          StoredType  getAuto (const Char8      *szName );
    const Char8      *findName(const StoredType &val    );
#if 0
          void        release (      StoredType oElement);
#endif
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       free                                   */
    /*! \{                                                                 */
   
    StoredType getDefault(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       free                                   */
    /*! \{                                                                 */

    void keyToStringList(const StoredType               &val,
                               std::vector<std::string> &result);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       stat                                   */
    /*! \{                                                                 */
    
    void printStat(void);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef std::vector<StoredType>                ValueStore;

    typedef          std::map<std::string, ValueT> NameValueMap;
    typedef          std::map<ValueT, std::string> ValueNameMap;

    typedef typename NameValueMap::iterator        NameValueMapIt;
    typedef typename NameValueMap::const_iterator  NameValueMapConstIt;

    typedef typename ValueNameMap::iterator        ValueNameMapIt;
    typedef typename ValueNameMap::const_iterator  ValueNameMapConstIt;
    
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    LockPolicy   _oLockPolicy;
    StoredType   _oDefaultElement;
    ValueStore   _vElementStore1;
    ValueStore   _vElementStore2;
    NameValueMap _mNameValueMap;
    ValueNameMap _mValueNameMap;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       stat                                   */
    /*! \{                                                                 */

    void initialize(void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    /*!\brief prohibit default function (move to 'public' if needed) */
    NamedSplitFinitePool(const NamedSplitFinitePool &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const NamedSplitFinitePool &source);
};

OSG_END_NAMESPACE

#include "OSGNamedSplitFinitePool.inl"

#endif /* _OSGNAMEDSPLITFINITEPOOL_H_ */
