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

namespace
{
    template<class CoreT>
    struct CoreCollector
    {
        std::vector<CoreT *> &_vResultStore;

        CoreCollector(std::vector<CoreT *> &vResultStore);
        ~CoreCollector(void);

        Action::ResultE travEnter(Node * const pRoot);

      private:
        
        CoreCollector(const CoreCollector &source);
        void operator =(const CoreCollector &source);
    };

    template <class CoreT> inline
    CoreCollector<CoreT>::CoreCollector(std::vector<CoreT *> &vResultStore) :
        _vResultStore(vResultStore)
    {
    }
    
    template <class CoreT> inline
    CoreCollector<CoreT>::~CoreCollector(void)
    {
    }

    template <class CoreT> inline
    Action::ResultE CoreCollector<CoreT>::travEnter(Node * const pRoot)
    {
        if(pRoot != NULL)
        {
            CoreT *pTypedCore = dynamic_cast<CoreT *>(pRoot->getCore());

            if(pTypedCore != NULL)
            {
                _vResultStore.push_back(pTypedCore);
            }
        }

        return Action::Continue;
    }
}

template<class CoreT> inline
void collectCoresByType(Node                 *pRoot, 
                        std::vector<CoreT *> &result)
{
    CoreCollector<CoreT> oCoreColl(result);

    traverse(pRoot, boost::bind(&CoreCollector<CoreT>::travEnter,
                                &oCoreColl,
                                _1                              ));
}

OSG_END_NAMESPACE
