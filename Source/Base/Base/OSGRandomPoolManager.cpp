/*---------------------------------------------------------------------------*\
 *                            OpenSG Toolbox                                 *
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

#include "OSGRandomPoolManager.h"

#include "boost/random/uniform_int.hpp"
#include "boost/random/uniform_real.hpp"

#include "OSGSingletonHolder.ins"

OSG_BEGIN_NAMESPACE

OSG_SINGLETON_INST(RandomPoolManagerBase, addPostFactoryExitFunction)

template class SingletonHolder<RandomPoolManagerBase>;


Int32 RandomPoolManagerBase::getRandomInt32(UInt32 uiRandomPool, 
                                            Int32  iMin, 
                                            Int32  iMax)
{
    boost::uniform_int<Int32> oDistribution(iMin, iMax);

    if(uiRandomPool < _vRandomPoolGenerators.size())
        return oDistribution(_vRandomPoolGenerators[uiRandomPool]);
    else
        return 0;
}

Int64 RandomPoolManagerBase::getRandomInt64(UInt32 uiRandomPool, 
                                            Int64  iMin, 
                                            Int64  iMax)
{
    boost::uniform_int<Int64> oDistribution(iMin, iMax);

    if(uiRandomPool < _vRandomPoolGenerators.size())
        return oDistribution(_vRandomPoolGenerators[uiRandomPool]);
    else 
        return 0;
}

Real32 RandomPoolManagerBase::getRandomReal32(UInt32 uiRandomPool, 
                                              Real32 fMin, 
                                              Real32 fMax)
{
    boost::uniform_real<Real32> oDistribution(fMin, fMax);

    if(uiRandomPool < _vRandomPoolGenerators.size())
        return oDistribution(_vRandomPoolGenerators[uiRandomPool]);
    else
        return 0.f;
}

Real64 RandomPoolManagerBase::getRandomReal64(UInt32 uiRandomPool, 
                                              Real64 fMin, 
                                              Real64 fMax)
{
    boost::uniform_real<Real64> oDistribution(fMin, fMax);

    if(uiRandomPool < _vRandomPoolGenerators.size())
        return oDistribution(_vRandomPoolGenerators[uiRandomPool]);
    else
        return 0.0;
}
#if 0

RandomPoolManagerBase::RandomGeneratorType& RandomPoolManager::getRandomGeneratorType(UInt32 RandomPool)
{
    if(uiRandomPool < _vRandomPoolGenerators.size())
        return _RandomPoolGenerators[RandomPool];
    else
        return  GeneratorType();   

}
#endif

OSG_END_NAMESPACE
