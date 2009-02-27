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

#ifndef _OSGMULTIPOOL_H_
#define _OSGMULTIPOOL_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGBaseTypes.h"

#include <vector>
#include <map>
#include <typeinfo>

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpBaseBasePools
    \ingroup GrpBaseBase
    \ingroup GrpLibOSGBase
    \brief Pool that can store different classes derived from a common base
    class

    \nohierarchy
 */

template<class ValueBaseT>
class MultiPool 
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    MultiPool(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~MultiPool(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      create                                  */
    /*! \{                                                                 */

    template<class ParameterT>
    ParameterT *create(ParameterT &oParam);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       free                                   */
    /*! \{                                                                 */
    
    void freeAll(void);

    /*! \}                                                                 */  
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    /*! \nohierarchy
     */
    // Store the data for a single type
    class TypeStore
    {
      public:
      
        static const int BLOCKSIZE = 16; //!< number of elements per block
        
        TypeStore(int size);
        
        ~TypeStore();
        
        void freeAll(void);
        
        template<class ParameterT>
        ParameterT *create(ParameterT &oParam);
      
      private:
      
        UInt32 _instSize; //!< size of an instance of the stored type
        
        UInt32 _currentFreeElement; //!< first unused element index
        UInt32 _currentInitElement; //!< first uninitialized element index
        
        std::vector<UInt8*> _data;  //!< Data blocks for the instances.        
    };
    
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef          std::map<const char *, TypeStore*>   TypesStoreT;
    typedef typename std::map<const char *, TypeStore*>::iterator   
                                                          TypesStoreIt;

    TypesStoreT _typesStore;
    
    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    /*!\brief prohibit default function (move to 'public' if needed) */
    MultiPool(const MultiPool &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const MultiPool &source);
};

OSG_END_NAMESPACE

#include "OSGMultiPool.inl"

#endif /* _OSGMULTIPOOL_H_ */
