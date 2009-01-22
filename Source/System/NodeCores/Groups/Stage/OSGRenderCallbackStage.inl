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

OSG_BEGIN_NAMESPACE

template<class FunctorT> inline
void RenderCallbackStage::subPreRenderFunctor(FunctorT func)
{
    MFRenderFunctorCallback::iterator       cfIt = 
        _mfPreRenderCallbacks.begin();

    MFRenderFunctorCallback::const_iterator cfEnd= 
        _mfPreRenderCallbacks.end();

    while(cfIt != cfEnd)
    {
        if(cfIt->_func == func)
            break;

        ++cfIt;
    }

    if(cfIt != cfEnd)
        _mfPreRenderCallbacks.erase(cfIt);
}

template<class FunctorT> inline
void RenderCallbackStage::subPostRenderFunctor(FunctorT func)
{
    MFRenderFunctorCallback::iterator       cfIt = 
        _mfPostRenderCallbacks.begin();

    MFRenderFunctorCallback::const_iterator cfEnd= 
        _mfPostRenderCallbacks.end();

    while(cfIt != cfEnd)
    {
        if(cfIt->_func == func)
            break;

        ++cfIt;
    }

    if(cfIt != cfEnd)
        _mfPostRenderCallbacks.erase(cfIt);
}

inline
void RenderCallbackStage::fillPreRenderStore (RenderFunctorStore &vStore)
{
    MFRenderFunctorCallback::const_iterator cfIt = 
        _mfPreRenderCallbacks.begin();

    MFRenderFunctorCallback::const_iterator cfEnd= 
        _mfPreRenderCallbacks.end();

    while(cfIt != cfEnd)
    {
        vStore.push_back(cfIt->_func);

        ++cfIt;
    }
}

inline
void RenderCallbackStage::fillPostRenderStore(RenderFunctorStore &vStore)
{
    MFRenderFunctorCallback::const_iterator cfIt = 
        _mfPostRenderCallbacks.begin();

    MFRenderFunctorCallback::const_iterator cfEnd= 
        _mfPostRenderCallbacks.end();

    while(cfIt != cfEnd)
    {
        vStore.push_back(cfIt->_func);

        ++cfIt;
    }
}

OSG_END_NAMESPACE


