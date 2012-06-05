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

template <class Desc> inline
ChunkListHandlerMixin<Desc>::ListEditHandle::ListEditHandle(
    const ListEditHandle &source) :

    Inherited(source)
{
}

template <class Desc> inline
ChunkListHandlerMixin<Desc>::ListEditHandle::ListEditHandle(      
          FieldT                *pField, 
    const FieldDescriptionBase  *pDescription,
          FieldContainer        *pContainer  ) :

    Inherited(pField,
              pDescription,
              pContainer  )
{
}


template <class Desc> inline
bool ChunkListHandlerMixin<Desc>::ListEditHandle::add(
    FieldContainer *newFC) const
{
    ChunkHelper *pHelper = dynamic_cast<ChunkHelper *>(newFC);

    if(pHelper != NULL)
    {
        FinalContainer *pCnt = dynamic_cast<FinalContainer *>(
            this->_pContainer);

        if(pCnt != NULL)
        {
            pCnt->addChunk( pHelper->getChunk(), pHelper->getSlot());
        }

        return true;
    }

    Inherited::add(newFC);

    return true;
}


/*-------------------------------------------------------------------------*/
/*                                Set                                      */

/*-------------------------------------------------------------------------*/
/* Binary access                                                           */

/*-------------------------------------------------------------------------*/
/*                             Assignment                                  */


/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

template <class Desc> inline
ChunkListHandlerMixin<Desc>::ChunkListHandlerMixin(void) :
    Inherited()
{
}

template <class Desc> inline
ChunkListHandlerMixin<Desc>::ChunkListHandlerMixin(
    const ChunkListHandlerMixin &source) :

    Inherited(source)
{
}

template <class Desc> inline
ChunkListHandlerMixin<Desc>::~ChunkListHandlerMixin(void)
{
}

template <class Desc> inline
void ChunkListHandlerMixin<Desc>::dump(      UInt32    uiIndent,
                                       const BitVector bvFlags ) const
{
    Inherited::dump(uiIndent, bvFlags);
}

template <class Desc> inline
EditFieldHandlePtr ChunkListHandlerMixin<Desc>::editHandleChunks(void)
{
    typedef ListEditHandle    ChunksEditHandle;
    typedef ListEditHandlePtr ChunksEditHandlePtr;

    ChunksEditHandlePtr returnValue(
        new ChunksEditHandle(
             &this->_mfChunks,
             this->getType().getFieldDesc(Self::ChunksFieldId),
             this));

    returnValue->setAddMethod(
        boost::bind(&FinalContainer::pushToChunks,
                    static_cast<FinalContainer *>(this), _1));

    this->editMField(Self::ChunksFieldMask, this->_mfChunks);

    return returnValue;
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

/*-------------------------------------------------------------------------*/
/*                             Assignment                                  */

/*-------------------------------------------------------------------------*/
/*                             Comparison                                  */

OSG_END_NAMESPACE

