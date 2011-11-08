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

OSG_USING_NAMESPACE

inline
RandomPoolManagerBase::RandomPoolManagerBase(void) :
    _vRandomPoolGenerators (                              ),
    _uiDefaultGeneratorPool(RandomPoolManagerBase::GENERAL)
{
    for(UInt32 i = 0; i < NUM_DEFINED_POOLS; ++i)
    {
        _vRandomPoolGenerators.push_back(GeneratorType());
    }
}

#if 0
inline
void RandomPoolManager::operator=(const RandomPoolManager& val)
{
}
#endif

inline
UInt32 RandomPoolManagerBase::getNumPools(void)
{
    return _vRandomPoolGenerators.size();
}

inline
UInt32 RandomPoolManagerBase::createNewPool(void)
{
    _vRandomPoolGenerators.push_back(GeneratorType());

    return getNumPools() - 1;
}

inline
void RandomPoolManagerBase::seedPool(UInt32 uiRandomPool, SeedType seed)
{
    if(uiRandomPool < _vRandomPoolGenerators.size())
        _vRandomPoolGenerators[uiRandomPool].seed(seed);
}

inline
Int32 RandomPoolManagerBase::getRandomInt32(Int32 iMin, Int32 iMax)
{
    return getRandomInt32(_uiDefaultGeneratorPool, iMin, iMax);
}

inline
Int64 RandomPoolManagerBase::getRandomInt64(Int64 iMin, Int64 iMax)
{
    return getRandomInt64(_uiDefaultGeneratorPool, iMin, iMax);
}

inline
Real32 RandomPoolManagerBase::getRandomReal32(Real32 fMin, Real32 fMax)
{
    return getRandomReal32(_uiDefaultGeneratorPool, fMin, fMax);
}

inline
Real64 RandomPoolManagerBase::getRandomReal64(Real64 fMin, Real64 fMax)
{
    return getRandomReal64(_uiDefaultGeneratorPool, fMin, fMax);
}

inline
void RandomPoolManagerBase::setDefaultGeneratorPool(const UInt32 uiPool)
{
    _uiDefaultGeneratorPool = uiPool;
}
