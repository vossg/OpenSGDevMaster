/*---------------------------------------------------------------------------*\
 *                             OpenSG Toolbox                                *
 *                                                                           *
 *                                                                           *
 *                          Authors: David Kabala                            *
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

#ifndef _OSGRANDOMPOOLMANAGER_H_
#define _OSGRANDOMPOOLMANAGER_H_

#include "OSGVector.h"
#include "OSGSingletonHolder.h"

 //Defines the rand48 Random generator
#include <boost/random/linear_congruential.hpp>

#include <vector>

OSG_BEGIN_NAMESPACE

class OSG_BASE_DLLMAPPING RandomPoolManagerBase
{
    /*==========================  PUBLIC  =================================*/

  public:

    enum RandomNumberPools 
    {
        GENERAL           = 0, 
        NUM_DEFINED_POOLS
    };

    typedef boost::rand48              GeneratorType;

    typedef GeneratorType::result_type SeedType;

    /*==========================  PRIVATE  ================================*/

  private:


    std::vector<GeneratorType> _vRandomPoolGenerators;
    UInt32                     _uiDefaultGeneratorPool;
    
    RandomPoolManagerBase(void);

    RandomPoolManagerBase(RandomPoolManagerBase &rhs);
    void operator=(const RandomPoolManagerBase &rhs);

    template <class SingletonT>
    friend class SingletonHolder;

    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    //Get Random Int uniformly distributed accross [Min, Max]

    Int32 getRandomInt32(UInt32 uiRandomPool, Int32 iMin, Int32 iMax);
    Int64 getRandomInt64(UInt32 uiRandomPool, Int64 iMin, Int64 iMax);

    Int32 getRandomInt32(                     Int32 iMin, Int32 iMax);
    Int64 getRandomInt64(                     Int64 iMin, Int64 iMax);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    //Get Random Real uniformly distributed accross [Min, Max)

    Real32 getRandomReal32(UInt32 uiRandomPool, Real32 fMin, Real32 fMax);
    Real64 getRandomReal64(UInt32 uiRandomPool, Real64 fMin, Real64 fMax);

    Real32 getRandomReal32(                     Real32 fMin, Real32 fMax);
    Real64 getRandomReal64(                     Real64 fMin, Real64 fMax);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    GeneratorType &getRandomGeneratorType(UInt32 uiRandomPool);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    void   setDefaultGeneratorPool(const UInt32   uiPool      );

    UInt32 getNumPools            (      void                 );
    UInt32 createNewPool          (      void                 );
    void   seedPool               (      UInt32   uiRandomPool, 
                                         SeedType seed        );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
};

#if defined(WIN32)
OSG_BASE_EXPIMP_TMPL
template class OSG_BASE_DLLMAPPING SingletonHolder<RandomPoolManagerBase>;
#endif

typedef SingletonHolder<RandomPoolManagerBase> RandomPoolManager;

OSG_END_NAMESPACE


#include "OSGRandomPoolManager.inl"
#endif


