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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#include "OSGFieldContainerType.h"
#include "OSGContainerPtrFuncs.h"
#include "OSGFieldContainerFactory.h"
#include "OSGFieldDescriptionBase.h"

#include "OSGNodeCore.h"
#include "OSGNode.h"
#include "OSGAttachment.h"

OSG_USING_NAMESPACE

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

/*! Constructor for a new field container type.
*
*/
FieldContainerType::FieldContainerType(
    const Char8                *szName,
    const Char8                *szParentName,
    const Char8                *szGroupName,
    const UInt32                uiNameSpace,
          PrototypeCreateF      fPrototypeCreate,
          InitContainerF        fInitMethod,
          ExitContainerF        fExitMethod,
          InitalInsertDescFunc  descInsertFunc,
          bool                  bDescsAddable,
          BitVector             bvUnmarkedOnCreate,
          std::string           fcdXML,
          std::string           typeDoc) :

     Inherited       (szName,
                      szParentName,
                      szGroupName,
                      uiNameSpace,
                      descInsertFunc,
                      bDescsAddable,
                      bvUnmarkedOnCreate),


    _baseType        (IsFieldContainer  ),
    _pPrototype      (NULL              ),
    _fPrototypeCreate(fPrototypeCreate  ),
    _fInitMethod     (fInitMethod       ),
    _fExitMethod     (fExitMethod       ),
    _fcdXML          (fcdXML            ),
    _typeDoc         (typeDoc           )
{
    registerType();

    if(fInitMethod != NULL)
        fInitMethod(Static);
}

FieldContainerType::FieldContainerType(const FieldContainerType &source) :

    Inherited(source),

    _baseType        (source._baseType   ),
    _pPrototype      (source._pPrototype ),
    _fPrototypeCreate(NULL               ),
    _fInitMethod     (source._fInitMethod),
    _fExitMethod     (source._fExitMethod),
    _fcdXML          (source._fcdXML     ),
    _typeDoc         (source._typeDoc    )
{
    if(_pPrototype != NULL)
        _pPrototype->addReferenceUnrecorded();
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

FieldContainerType::~FieldContainerType(void)
{
}

bool FieldContainerType::setPrototype(FieldContainer *pPrototype)
{
    bool returnValue = false;

    if(this->isAbstract() == false)
    {
        if(pPrototype != NULL)
        {
            TypePredicates::IsBaseOf baseTypePred(pPrototype->getType());

            if(baseTypePred(this) == true)
            {
                pPrototype->addReferenceUnrecorded();
            
                _pPrototype->subReferenceUnrecorded();

                _pPrototype = pPrototype;

                BitVector bCurrent = 0x0002;

                for(UInt32 i = 1; i <= this->getNumFieldDescs(); ++i)
                {
                    FieldDescriptionBase *pDesc = this->getFieldDesc(i);

                    if(pDesc == NULL)
                        continue;

                    if(0x0000 == (bCurrent & 
                                _pPrototype->_pFieldFlags->_bThreadLocalFlags))
                    {
                        pDesc->setFlags(pDesc->getFlags()  | 
                                        Field::FThreadLocal);
                    }
                    else
                    {
                        pDesc->setFlags(pDesc->getFlags()   & 
                                        ~Field::FThreadLocal);
                    }

                    if(0x0000 == (bCurrent & 
                                _pPrototype->_pFieldFlags->_bClusterLocalFlags))
                    {
                        pDesc->setFlags(pDesc->getFlags()   | 
                                        Field::FClusterLocal);
                    }
                    else
                    {
                        pDesc->setFlags(pDesc->getFlags()    & 
                                        ~Field::FClusterLocal);
                    }

                    bCurrent <<= 1;
                }

                returnValue = true;
            }
            else
            {
                FWARNING(("can not set unrelated container of type %s "
                          "as prototype for type %s\n",
                          pPrototype->getType().getCName(),
                          this->getCName()));
            }
        }
        else
        {
            FWARNING(("can not delete prototype of a concrete object\n"));
        }
    }
    else
    {
        FWARNING(("can not set prototype of an abstract object\n"));
    }

    return returnValue;
}

FieldContainerTransitPtr FieldContainerType::createContainer(void) const
{
    FieldContainerTransitPtr fc(NULL);

    if(this->isAbstract() == false)
    {
        fc = _pPrototype->shallowCopy();
    }

    return fc;
}

void FieldContainerType::markFieldsThreadLocal(const BitVector bvFieldMasks)
{
    if(_pPrototype != NULL)
    {
        BitVector bCurrent = 0x0002;

        for(UInt32 i = 1; i <= this->getNumFieldDescs(); ++i)
        {
            FieldDescriptionBase *pDesc = this->getFieldDesc(i);
        
            if(0x0000 != (bCurrent & bvFieldMasks) && pDesc != NULL)
            {
                pDesc->setFlags(pDesc->getFlags() | Field::FThreadLocal);

                _pPrototype->_pFieldFlags->_bThreadLocalFlags &=
                    ~pDesc->getFieldMask();
            }
            
            bCurrent <<= 1;
        }
    }
}

void FieldContainerType::unmarkFieldsThreadLocal(const BitVector bvFieldMasks)
{
    if(_pPrototype != NULL)
    {
        BitVector bCurrent = 0x0002;

        for(UInt32 i = 1; i <= this->getNumFieldDescs(); ++i)
        {
            FieldDescriptionBase *pDesc = this->getFieldDesc(i);

            if(0x0000 != (bCurrent & bvFieldMasks) && pDesc != NULL)
            {
                pDesc->setFlags(pDesc->getFlags() & ~Field::FThreadLocal);

                _pPrototype->_pFieldFlags->_bThreadLocalFlags |=
                    pDesc->getFieldMask();
            }

            bCurrent <<= 1;
        }
    }
}

void FieldContainerType::markFieldsClusterLocal(const BitVector bvFieldMasks)
{
    if(_pPrototype != NULL)
    {
        BitVector bCurrent = 0x0002;

        for(UInt32 i = 1; i <= this->getNumFieldDescs(); ++i)
        {
            FieldDescriptionBase *pDesc = this->getFieldDesc(i);
            
            if(0x0000 != (bCurrent & bvFieldMasks) && pDesc != NULL)
            {
                pDesc->setFlags(pDesc->getFlags() | Field::FClusterLocal);

                _pPrototype->_pFieldFlags->_bClusterLocalFlags &=
                    ~pDesc->getFieldMask();
            }

            bCurrent <<= 1;
        }
    }
}

void FieldContainerType::unmarkFieldsClusterLocal(const BitVector bvFieldMasks)
{
    if(_pPrototype != NULL)
    {
        BitVector bCurrent = 0x0002;

        for(UInt32 i = 1; i <= this->getNumFieldDescs(); ++i)
        {
            FieldDescriptionBase *pDesc = this->getFieldDesc(i);

            if(0x0000 != (bCurrent & bvFieldMasks) && pDesc != NULL)
            {
                pDesc->setFlags(pDesc->getFlags() & ~Field::FClusterLocal);

                _pPrototype->_pFieldFlags->_bClusterLocalFlags |=
                    pDesc->getFieldMask();
            }

            bCurrent <<= 1;
        }
    }
}


#ifdef OSG_MT_CPTR_ASPECT
FieldContainer *FieldContainerType::createAspectCopy(
    const FieldContainer *pRefAspect,
          UInt32          uiContainerId) const
{
    FieldContainer *fc = NULL;

    if(isAbstract() == false)
    {
        fc = _pPrototype->createAspectCopy(pRefAspect);       
    }

    if(fc != NULL)
        fc->setId(uiContainerId);

    return fc;
}
#endif

bool FieldContainerType::initialize(void)
{
    if(_bInitialized == true)
        return true;

    if(_fInitMethod != NULL)
        _fInitMethod(SystemPre);

    _bInitialized = Inherited::initialize();

    if(_bInitialized == false)
        return false;

    _bInitialized = initPrototype   ();

    if(_bInitialized == false)
        return false;

    _bInitialized = initBaseType    ();

    if(_fInitMethod != NULL)
        _fInitMethod(SystemPost);

    return _bInitialized;
}

void FieldContainerType::terminate(void)
{
    if(_fExitMethod != NULL)
        _fExitMethod(SystemPre);

    if(_pPrototype != NULL)
    {
        _pPrototype->subReferenceUnrecorded();
        _pPrototype = NULL;
    }

    if(_fExitMethod != NULL)
        _fExitMethod(SystemPost);
}

bool FieldContainerType::initialize(InitPhase ePhase)
{
    if(_fInitMethod != NULL)
        _fInitMethod(ePhase);

    return true;
}

bool FieldContainerType::initPrototype(void)
{
    if(_fPrototypeCreate != NULL && _pPrototype == NULL)
    {
        _pPrototype = _fPrototypeCreate(FCLocal::All);

        if(_pPrototype != NULL)
            _pPrototype->addReferenceUnrecorded();
    }

    return true;
}

bool FieldContainerType::initBaseType(void)
{

    if     (isDerivedFrom(NodeCore::getClassType())   == true)
    {
        _baseType = IsNodeCore;
    }
    else if(isDerivedFrom(Attachment::getClassType()) == true)
    {
        _baseType = IsAttachment;
    }
    else if(isDerivedFrom(Node::getClassType())       == true)
    {
        _baseType = IsNode;
    }

    return true;
}

void FieldContainerType::registerType(void)
{
    FieldContainerFactory::the()->registerType(this);

    _uiGroupId = FieldContainerFactory::the()->registerGroup(
        _szGroupName.empty() == false ? _szGroupName.c_str() : _szName.c_str());
}

/*! Return a string with the XML representation of the original 
    contents of the fcd file. 
 */
std::string FieldContainerType::getFcdXML() const
{
   return _fcdXML;
}

/*! Return the documentation for this type. */
std::string FieldContainerType::getDocumentation() const
{
   return _typeDoc;
}

/*-------------------------------------------------------------------------*/
/*                                Dump                                     */

void FieldContainerType::dump(      UInt32    OSG_CHECK_ARG(uiIndent),
                              const BitVector OSG_CHECK_ARG(bvFlags )) const
{
    SLOG << "FieldContainerType: "
         << getCName()
         << ", Id: "
         << getId()
         << ", parentP: "
         << (_pParentType ? _pParentType->getCName() : "NONE")
         << ", groupId: "
         << _uiGroupId
         << ", abstract: "
         << ((_pPrototype != NULL) ? "false" : "true")
         << " "
         << _vDescVec.size()
         << std::endl;

    for(UInt32 i = 0; i < _vDescVec.size(); i++)
    {
        SLOG << "Desc : " << _vDescVec[i]->getCName() << std::endl;
    }
}
