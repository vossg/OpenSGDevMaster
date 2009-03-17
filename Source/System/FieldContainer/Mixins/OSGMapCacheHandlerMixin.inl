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
void MapCacheHandlerMixin<Desc>::classDescInserter(TypeObject &oType)
{
    Inherited::classDescInserter(oType);

    FieldDescriptionBase *pDesc;

    typedef typename MapCacheField::Description SFDesc;

    pDesc = new SFDesc(
        MapCacheField::getClassType(),
        Desc::getFieldName(),
        "map cache.",
        OSG_RC_FIELD_DESC(Self::MapCache),
        false,
        Field::SFDefaultFlags,
        static_cast<FieldEditMethodSig>(&Self::editHandleMapCache),
        static_cast<FieldGetMethodSig >(&Self::getHandleMapCache ));

    oType.addInitialDesc(pDesc);
}

template <class Desc> inline
void MapCacheHandlerMixin<Desc>::changed(ConstFieldMaskArg whichField, 
                                         UInt32            origin,
                                         BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

/*-------------------------------------------------------------------------*/
/*                                Set                                      */

template <class Desc> inline
typename MapCacheHandlerMixin<Desc>::FinalizedElement *
    MapCacheHandlerMixin<Desc>::finalize(MapCacheKey oKey)
{
    MapCacheFieldConstIt fcI = _fMapCache.getValue().find(oKey);

    if(fcI == _fMapCache.getValue().end())
    {
        return Desc::getFallback(this); //_sfFallbackMaterial.getValue();
    }
    else
    {
        return (*fcI).second;
    }
}

template <class Desc> inline
void MapCacheHandlerMixin<Desc>::addElement (
    MapCacheElement  const pElement,
    MapCacheKey            key     )
{
    if(pElement == NULL)
        return;

    if(key == MapKeyPool::the()->getDefault())
    {
        Desc::setFallback(this, pElement);  //setFallbackMaterial(pMaterial);

        return;
    }

    if(this->isMTLocal())
    {
        pElement->addReferenceRecorded();
    }
    else
    {
        pElement->addReferenceUnrecorded();
    }

#if 0
    pAttachment->linkParent(this, 
                            AttachmentsFieldId, 
                            Attachment::ParentsFieldId);
#endif

    Self::editSField(MapCacheFieldMask);

    MapCacheFieldIt fcI = _fMapCache.getValue().find(key);

    if(fcI != _fMapCache.getValue().end())
    {
#if 0
        (*fcI).second->unlinkParent(this, 
                                    Attachment::ParentsFieldId);
#endif

        if(this->isMTLocal())
        {
            (*fcI).second->subReferenceRecorded();
        }
        else
        {
            (*fcI).second->subReferenceUnrecorded();
        }

        (*fcI).second = pElement;
    }
    else
    {
        _fMapCache.getValue()[key] = pElement;
    }
}

template <class Desc> inline
void MapCacheHandlerMixin<Desc>::subElement(MapCacheKey key)
{
    if(key == MapKeyPool::the()->getDefault())
    {
        Desc::setFallback(this, NULL); //setFallbackMaterial(NULL);
        return;
    }

    Self::editSField(MapCacheFieldMask);

    MapCacheFieldIt fcI;

    fcI = _fMapCache.getValue().find(key);

    if(fcI != _fMapCache.getValue().end())
    {
#if 0
        (*fcI).second->unlinkParent(this, 
                                    Attachment::ParentsFieldId);
#endif

        if(this->isMTLocal())
        {
            (*fcI).second->subReferenceRecorded();
        }
        else
        {
            (*fcI).second->subReferenceUnrecorded();
        }

        _fMapCache.getValue().erase(fcI);
    }
}

template <class Desc> inline
typename MapCacheHandlerMixin<Desc>::MapCacheElement 
    MapCacheHandlerMixin<Desc>::findElement(MapCacheKey key) const
{
    MapCacheFieldConstIt fcI = _fMapCache.getValue().find(key);

    if(fcI == _fMapCache.getValue().end())
    {
        return NULL;
    }
    else
    {
        return (*fcI).second;
    }
}

template <class Desc> inline
const typename MapCacheHandlerMixin<Desc>::MapCacheField *
    MapCacheHandlerMixin<Desc>::getMapCacheField(void) const
{
    return &_fMapCache;
}

/*-------------------------------------------------------------------------*/
/* Binary access                                                           */

template <class Desc> inline
UInt32 MapCacheHandlerMixin<Desc>::getBinSize(ConstFieldMaskArg whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (MapCacheFieldMask & whichField))
    {
        returnValue += _fMapCache.getBinSize();
    }

    return returnValue;
}

template <class Desc> inline
void MapCacheHandlerMixin<Desc>::copyToBin(BinaryDataHandler  &pMem, 
                                           ConstFieldMaskArg   whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (MapCacheFieldMask & whichField))
    {
        _fMapCache.copyToBin(pMem);
    }
}

template <class Desc> inline
void MapCacheHandlerMixin<Desc>::copyFromBin(BinaryDataHandler &pMem, 
                                             ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (MapCacheFieldMask & whichField))
    {
        _fMapCache.copyFromBin(pMem);
    }
}

/*-------------------------------------------------------------------------*/
/*                             Assignment                                  */


/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

template <class Desc> inline
MapCacheHandlerMixin<Desc>::MapCacheHandlerMixin(void) :
     Inherited(),
    _fMapCache()
{
}

template <class Desc> inline
MapCacheHandlerMixin<Desc>::MapCacheHandlerMixin(
    const MapCacheHandlerMixin &source) :

     Inherited(source),
    _fMapCache(      )
{
}

template <class Desc> inline
MapCacheHandlerMixin<Desc>::~MapCacheHandlerMixin(void)
{
}

template <class Desc> inline
void MapCacheHandlerMixin<Desc>::dump(      UInt32    uiIndent,
                                      const BitVector bvFlags ) const
{
}

template <class Desc> inline
EditFieldHandlePtr MapCacheHandlerMixin<Desc>::editHandleMapCache(void)
{
    typename MapCacheField::EditHandlePtr returnValue(
        new  typename MapCacheField::EditHandle(
             &_fMapCache,
             this->getType().getFieldDesc(MapCacheFieldId),
             this));

    returnValue->setAddMethod(
        boost::bind(&Self::addElement,
                    static_cast<Self *>(this), _1, _2));

    this->editSField(MapCacheFieldMask);

    return returnValue;
}

template <class Desc> inline
GetFieldHandlePtr  MapCacheHandlerMixin<Desc>::getHandleMapCache(void) const
{
    typename MapCacheField::GetHandlePtr returnValue(
        new  typename MapCacheField::GetHandle(
             &_fMapCache,
             this->getType().getFieldDesc(MapCacheFieldId),
             const_cast<Self *>(this)));

    return returnValue;
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */


#ifdef OSG_MT_CPTR_ASPECT
template <class Desc> inline
void MapCacheHandlerMixin<Desc>::execSync(
          Self              *pFrom,
          ConstFieldMaskArg  whichField,
                             AspectOffsetStore &oOffsets,
          ConstFieldMaskArg  syncMode  ,
    const UInt32             uiSyncInfo)
{
    Inherited::execSync(pFrom, whichField, oOffsets, syncMode, uiSyncInfo);

    if(FieldBits::NoField != (MapCacheFieldMask & whichField))
    {
//        _sfAttachments.syncWith(pFrom->_sfAttachments);

        // needs optimizing

        MapCache tmpMap;

        MapCacheFieldIt fcI = pFrom->_fMapCache.getValue().begin();
        MapCacheFieldIt fcE = pFrom->_fMapCache.getValue().end  ();
        
        while(fcI != fcE)
        {
            MapCacheElement pMat = convertToCurrentAspect((*fcI).second);

            if(pMat != NULL)
            {
                tmpMap[(*fcI).first] = pMat;

                pMat->addReferenceUnrecorded();
            }

            ++fcI;
        }

        fcI = _fMapCache.getValue().begin();
        fcE = _fMapCache.getValue().end  ();

        while(fcI != fcE)
        {
            if(this->isMTLocal())
            {
                (*fcI).second->subReferenceRecorded();
            }
            else
            {
                (*fcI).second->subReferenceUnrecorded();
            }
            
            ++fcI;
        }

        _fMapCache.setValue(tmpMap);
    }
}
#endif

template <class Desc> inline
void MapCacheHandlerMixin<Desc>::onCreateAspect(
    const FinalContainer *createAspect,
    const FinalContainer *source      )
{
    Inherited::onCreateAspect(createAspect, source);

    // avoid prototype
    if(GlobalSystemState == OSG::Running)
    {
    }
}

template <class Desc> inline
void MapCacheHandlerMixin<Desc>::onCreate(const FinalContainer *source)
{
    Inherited::onCreate(source);

    // avoid prototype
    if(GlobalSystemState == OSG::Running)
    {
    }
}

template <class Desc> inline
void MapCacheHandlerMixin<Desc>::onDestroy(UInt32 uiContainerId)
{
    Inherited::onDestroy(uiContainerId);

    // avoid prototype
    if(GlobalSystemState == OSG::Running)
    {
    }
}

template <class Desc> inline
void MapCacheHandlerMixin<Desc>::onDestroyAspect(UInt32  uiContainerId,
                                                 UInt32  uiAspect     )
{
    Inherited::onDestroy(uiContainerId);

    // avoid prototype
    if(GlobalSystemState == OSG::Running)
    {
    }
}

template <class Desc> inline
void MapCacheHandlerMixin<Desc>::resolveLinks(void)
{
    Inherited::resolveLinks();

    MapCacheFieldIt fcI = _fMapCache.getValue().begin();
    MapCacheFieldIt fcE = _fMapCache.getValue().end  ();

    while(fcI != fcE)
    {
#if 0
        (*fcI).second->unlinkParent(this, 
                                    Material::ParentsFieldId);
#endif

        if(this->isMTLocal())
        {
            (*fcI).second->subReferenceRecorded();
        }
        else
        {
            (*fcI).second->subReferenceUnrecorded();
        }

        ++fcI;
    }

    _fMapCache.getValue().clear();
}

/*-------------------------------------------------------------------------*/
/*                             Assignment                                  */

/*-------------------------------------------------------------------------*/
/*                             Comparison                                  */

OSG_END_NAMESPACE

