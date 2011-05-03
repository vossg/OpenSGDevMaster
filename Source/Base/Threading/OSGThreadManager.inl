/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2003 by the OpenSG Forum                   *
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


/*-------------------------- constructor ----------------------------------*/

template <class MPFieldT> inline
MPFieldStore<MPFieldT>::MPFieldStore(void)
{
}

/*--------------------------- destructor ----------------------------------*/

template <class MPFieldT> inline
MPFieldStore<MPFieldT>::~MPFieldStore(void)
{
}

/*------------------------------ access -----------------------------------*/

template <class MPFieldT> inline
MPFieldT *MPFieldStore<MPFieldT>::getMPField(const Char8 *szName,
                                             const Char8 *szTypeName,
                                                   bool   bGlobal   )
{
    MPFieldT    *returnValue = NULL;
    MPFieldType *pElemType;

    returnValue = findMPField(szName);

    if(returnValue == NULL)
    {
        pElemType = findMPFieldType(szTypeName);

        if(pElemType != NULL)
        {
            returnValue = pElemType->create(szName, bGlobal);

            if(returnValue != NULL)
            {
                if(returnValue->isGlobal() == true)
                {
                    OSG::addRef(returnValue);
                }

                _mFieldMap[std::string(returnValue->getCName())]= returnValue;
            }
        }
        else
        {
            PWARNING  << "could not find type named : " << szName << std::endl;

            returnValue = NULL;
        }
    }

    return returnValue;
}


/*------------------------------- get -----------------------------------*/

template <class MPFieldT> inline
MPFieldT *MPFieldStore<MPFieldT>::findMPField(const Char8 *szName)
{
    MPFieldMapIt gIt;

    if(szName == NULL)
        return NULL;

    gIt = _mFieldMap.find(std::string(szName));

    if(gIt != _mFieldMap.end())
    {
        return (*gIt).second;
    }
    else
    {
        return NULL;
    }
}

template <class MPFieldT> inline
void MPFieldStore<MPFieldT>::removeMPField(MPFieldT *pField)
{
    if(pField == NULL)
        return;

    MPFieldMapIt gIt = _mFieldMap.find(std::string(pField->getCName()));

    if(gIt != _mFieldMap.end())
    {
        if((*gIt).second->isGlobal() == true)
        {
            subRef((*gIt).second);
        }

        _mFieldMap.erase(gIt);
    }
}

/*-------------------------------------------------------------------------*/
/*                               Helper                                    */

template <class MPFieldT> inline
void MPFieldStore<MPFieldT>::clear(void)
{
    MPFieldMapIt gIt = _mFieldMap.begin();

    // don't delete objects that are refcounted - rather leak them
    // than destroying an object with active references to it.

     while(gIt != _mFieldMap.end())
     {
         if((*gIt).second                != NULL && 
            (*gIt).second->isGlobal()    == true && 
            (*gIt).second->getRefCount() == 1     )
         {
             delete (*gIt).second;
         }

         ++gIt;
     }

    _mFieldMap.clear();
}


template <class MPFieldT> inline
typename MPFieldStore<MPFieldT>::MPFieldType *
    MPFieldStore<MPFieldT>::findMPFieldType(const Char8 *szName) const
{
    MPFieldTypeMapCIt gIt;

    if(szName == NULL)
    {
        SWARNING << "typename == NULL" << std::endl;
        return NULL;
    }

    gIt = _mFieldTypeMap.find(std::string(szName));

    if(gIt != _mFieldTypeMap.end())
    {
        return (*gIt).second;
    }
    else
    {
        return NULL;
    }
}

/*-------------------------------------------------------------------------*/
/*                             Register                                    */

template <class MPFieldT> inline
UInt32 MPFieldStore<MPFieldT>::registerMPType(MPFieldType *pType)
{
    UInt32 returnValue = 0;

    if(pType == NULL)
        return 0;

    MPFieldType *pTmp = findMPFieldType(pType->getCName());

    if(pTmp != NULL)
    {
        SLOG << "Error could not add second mp type with name "
                << pType->getCName()
                << std::endl;

        return returnValue;
    }

/*
    returnValue = TypeFactory::the()->registerType(pType);

    if(returnValue == 0)
    {
        SLOG << "Error in base type registration" << std::endl;
        return returnValue;
    }
*/

    _mFieldTypeMap[std::string(pType->getCName())] = pType;

    return returnValue;
}

OSG_END_NAMESPACE
