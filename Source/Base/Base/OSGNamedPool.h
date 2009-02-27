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

#ifndef _OSGNAMEDPOOL_H_
#define _OSGNAMEDPOOL_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGBaseTypes.h"

#include <map>
#include <string>

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpBaseBasePools
    \ingroup GrpBaseBase
    \ingroup GrpLibOSGBase
    \nohierarchy
*/

template <class ValueT>
class NamedPool 
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    NamedPool(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~NamedPool(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      create                                  */
    /*! \{                                                                 */

    ValueT get(const Char8 *szName);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       free                                   */
    /*! \{                                                                 */
    
//    void freeAll(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       stat                                   */
    /*! \{                                                                 */
    
    void printStat(void);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef          std::map<std::string, ValueT>           ValueStore;

    typedef typename std::map<std::string, ValueT>::iterator ValueStoreIt;

    
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    void   initCurrentValue(void);
    ValueT getNextValue    (void);
    ValueT getInvalidValue (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    ValueStore   _elementStore;
    ValueT       _currentValue;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    /*!\brief prohibit default function (move to 'public' if needed) */
    NamedPool(const NamedPool &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const NamedPool &source);
};

template <> inline
void NamedPool<Int32>::initCurrentValue(void)
{
    _currentValue = -1;
}

template <> inline
Int32 NamedPool<Int32>::getNextValue(void)
{
    ++_currentValue;

    return _currentValue;
}

template <> inline
Int32 NamedPool<Int32>::getInvalidValue(void)
{
    return -1;
}

template <> inline
void NamedPool<BitVector>::initCurrentValue(void)
{
    _currentValue = 1;
}

template <> inline
BitVector NamedPool<BitVector>::getNextValue(void)
{
    BitVector returnValue = _currentValue;

    _currentValue <<= 1;

    return returnValue;
}

template <> inline
BitVector NamedPool<BitVector>::getInvalidValue(void)
{
    return 0;
}

OSG_END_NAMESPACE

#include "OSGNamedPool.inl"

#endif /* _OSGNAMEDPOOL_H_ */
