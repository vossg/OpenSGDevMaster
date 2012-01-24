/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2003 by the OpenSG Forum                          *
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

OSG_BEGIN_NAMESPACE

/*-------------------------------------------------------------------------*/
/*                                Set                                      */

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

template <class ParentT> inline
FrameProducerHandlerMixin<ParentT>::FrameProducerHandlerMixin(void) :
     Inherited           (    ),
    _mfFrameProducers    (    ),
    _pProducerSyncBarrier(NULL)
{
}

template <class ParentT> inline
FrameProducerHandlerMixin<ParentT>::FrameProducerHandlerMixin(
    const FrameProducerHandlerMixin &source) :

     Inherited           (source),
    _mfFrameProducers    (      ),
    _pProducerSyncBarrier(NULL  )
{
}

template <class ParentT> inline
FrameProducerHandlerMixin<ParentT>::~FrameProducerHandlerMixin(void)
{
}

template <class ParentT> inline
void FrameProducerHandlerMixin<ParentT>::dump(
          UInt32    uiIndent,
    const BitVector bvFlags ) const
{
}

template <class ParentT> inline
void FrameProducerHandlerMixin<ParentT>::addProducer(
    FrameProducerInterface *pProducer)
{
    if(pProducer == NULL)
        return;

    if(_pProducerSyncBarrier == NULL)
        _pProducerSyncBarrier = Barrier::get(NULL, false);

    pProducer->setSyncBarrier(_pProducerSyncBarrier);

    _mfFrameProducers.push_back(pProducer);

#if 0
    fprintf( stderr, "add producer (hnd) %p %p %"PRIUSize"\n",
             this,
             pProducer,
            _mfFrameTasks.size());
#endif

    updateSyncCount();
}

template <class ParentT> inline
void FrameProducerHandlerMixin<ParentT>::removeProducer(
    FrameProducerInterface *pProducer)
{
    ProducerStoreIt tIt = std::find(_mfFrameProducers.begin(),
                                    _mfFrameProducers.end  (),
                                     pProducer               );

    if(tIt != _mfFrameProducers.end())
    {
        _mfFrameProducers.erase(tIt);
    }

    updateSyncCount();

#if 0
    fprintf( stderr, "sub producer (hnd) %p %p %"PRIUSize"\n",
             this,
             pProducer,
            _mfFrameTasks.size());
#endif
}

template <class ParentT> inline
void FrameProducerHandlerMixin<ParentT>::updateSyncCount(void)
{
    _pProducerSyncBarrier->setNumWaitFor(UInt32(_mfFrameProducers.size()) + 1);
}

template <class ParentT> inline
void FrameProducerHandlerMixin<ParentT>::syncProducers(void)
{
#if 0
    static UInt32 uiFCount = 0;

    if(uiFCount < 20)
    {
        fprintf(stderr, "syncProducers %"PRIUSize"\n", _mfFrameTasks.size());
        ++uiFCount;
    }
#endif

    ProducerStoreIt      tIt  = _mfFrameProducers.begin();
    ProducerStoreConstIt tEnd = _mfFrameProducers.end  ();

    for(; tIt != tEnd; ++tIt)
    {
        (*tIt)->syncProducer();
    }
}

template <class ParentT> inline
void FrameProducerHandlerMixin<ParentT>::resolveLinks(void)
{
    Inherited::resolveLinks();

    _mfFrameProducers.clear();

    _pProducerSyncBarrier = NULL;
}

/*-------------------------------------------------------------------------*/
/*                             Comparison                                  */

OSG_END_NAMESPACE

