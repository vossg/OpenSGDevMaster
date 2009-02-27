/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                       Copyright 2008 by OpenSG Forum                      *
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

#ifndef _OSGMTPOINTER_H_
#define _OSGMTPOINTER_H_

#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGBaseFunctions.h"

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpBaseBaseMemory
    \ingroup GrpBaseBaseRefCounting
    \ingroup GrpBaseFieldContainerBase
    \ingroup GrpLibOSGBase
    \nohierarchy
 */

template <class ObjectT>
class MTPtr
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name Public Types                                                 */
    /*! \{                                                                 */
  
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constructors                                                 */
    /*! \{                                                                 */
  
    MTPtr(ObjectT * const pObj);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Desctructor                                                  */
    /*! \{                                                                 */

    ~MTPtr(void);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Assignment                                                   */
    /*! \{                                                                 */
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Conversion                                                   */
    /*! \{                                                                 */
    
    operator ObjectT *(void) const;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Access                                                       */
    /*! \{                                                                 */
    
    ObjectT *operator->(void) const;
    ObjectT &operator *(void) const;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Access                                                       */
    /*! \{                                                                 */

    ObjectT *get(void) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*==========================  PRIVATE  ================================*/

    /*---------------------------------------------------------------------*/
    /*! \name Member                                                       */
    /*! \{                                                                 */
    
    ObjectT *_pObj;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

  private:

    /*---------------------------------------------------------------------*/
    /*! \name Internal Helpers                                             */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
  
};

template<class ObjectT> inline
ObjectT *get_pointer(const MTPtr<ObjectT> &pIn);

OSG_END_NAMESPACE

#include "OSGMTPtr.inl"

#endif // _OSGMTPOINTER_H_
