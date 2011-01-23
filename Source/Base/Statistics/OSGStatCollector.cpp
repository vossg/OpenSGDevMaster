/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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

#include "OSGStatElemDesc.h"
#include "OSGStatElem.h"

#include "OSGStatCollector.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::StatCollector

    The StatCollector is responsible for managing a set of OSG::StatElem
    elements, see \ref PageSystemStatistics for details.
*/

/***************************************************************************\
 *                         Instance methods                                *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                -
\*-------------------------------------------------------------------------*/

StatCollector::StatCollector(void) :
    Inherited()
{
    refitElemNum();
}

/*! copy constructor 
 */

StatCollector::StatCollector(const StatCollector &source) :
     Inherited(source),
    _elemVec  (      )
{
    _elemVec.resize(source._elemVec.size());

    for(UInt32 i = 0; i < source._elemVec.size(); ++i)
    {
        if(source._elemVec[i])
        {
            _elemVec[i] = source._elemVec[i]->clone();
        }
        else
        {
            _elemVec[i] = NULL;
        }
    }
}

StatCollector *StatCollector::create(void)
{
    return new StatCollector();
}

StatCollector::~StatCollector(void)
{
    for(UInt32 i = 0; i < _elemVec.size(); ++i)
        delete _elemVec[i];
}

/*-------------------------- your_category---------------------------------*/

/*! Increase the size of the StatCollector's data array. This is called during
    construction and will only be needed later, when a new StatElem has been
    added after the StatCollector was instanced. This will very rarely be the
    case.
 */
void StatCollector::refitElemNum(void)
{
    UInt32 eN = _elemVec.size();
    UInt32 dN = StatElemDescBase::getNumOfDescs();

    if(eN != dN)
    {
        _elemVec.resize(dN, 0);
    }
}

/*! Convert the current contents into a string. This
    string can be used as a compact representation of the data, and as input
    for StatCollector::getFromString.
 */
void StatCollector::putToString(std::string &str) const
{
    bool first = true;

    str = "{";

    StatElemStoreConstIt it    = _elemVec.begin();
    StatElemStoreConstIt endIt = _elemVec.end();

    for(; it != endIt; ++it)
    {
        if(*it != NULL)
        {
            std::string elem;

            if(!first)
                str.append("|");

            str.append((*it)->getDesc()->getName().c_str());
            str.append("=");
            (*it)->putToString(elem);
            str.append(elem);
            first = false;
        }
    }
    str.append("}");
}


/*! Set the contents from a string. The string has to have the format that is
    used by StatCollector::putToString.
 */
bool StatCollector::getFromCString(const Char8 *&inVal)
{
    const Char8 *c = inVal;

    if(*c++ != '{')
        return false;

    StatElemDescBase *desc;
    StatElem *elem;

    clearElems();

    while(*c && *c != '}')
    {
        const Char8 *end = c;

        while(*end != 0 && *end != '=' && *end != '}' && *end != '|')
            end++;

        if(*end == 0 || *end == '}' || *end == '|')
            return false;

        std::string name(c, end - c);
        desc = StatElemDescBase::findDescByName(name.c_str());

        if(!desc)
            return false;

        elem = getElem(*desc);

        c = end = end + 1;
        while(*end != 0 && *end != '}' && *end != '|')
            end++;

        if(*end == 0)
            return false;

        std::string val(c, end - c);
        const Char8 *valp = val.c_str();
        if(!elem->getFromCString(valp))
            return false;

        c = end + 1;
    }
    return true;
}

/*! Get the value of the named element, if it exists, return false if not.
 */

bool StatCollector::getValue(std::string &name, Real64 &val)
{
    StatElemDescBase *desc = StatElemDescBase::findDescByName(name.c_str());

    if(!desc)
        return false;

    StatElem *el = getElem(*desc, false);

    if(!el)
        return false;

    val = el->getValue();

    return true;
}

/*! Remove all elements from the collector.
 */
void StatCollector::clearElems(void)
{
    StatElemStoreIt      it    = _elemVec.begin();
    StatElemStoreConstIt endIt = _elemVec.end();

    for(; it != endIt; ++it)
    {
        if(*it != NULL)
        {
            delete *it;

            *it = NULL;
        }
    }
    _elemVec.clear();
}

/*! Reset all elements to the start value.
 */
void StatCollector::reset(StatElemDescBase::ResetMode mode)
{
    StatElemStoreIt      it    = _elemVec.begin();
    StatElemStoreConstIt endIt = _elemVec.end();

    for(; it != endIt; ++it)
    {
        if(*it != NULL && (*it)->getDesc()->getResetMode() >= mode)
        {
            (*it)->reset();
        }
    }
}

/*-------------------------- assignment -----------------------------------*/

const StatCollector &StatCollector::operator = (const StatCollector &source)
{
    if(this == &source)
        return *this;

    _elemVec = source._elemVec;

    return *this;
}

/*-------------------------- comparison -----------------------------------*/

/*! The comparison is only done on the addresses, as a real comparison is not
    well defined on a StatCollector.
 */
bool StatCollector::operator < (const StatCollector &other) const
{
    return this < &other;
}

bool StatCollector::operator == (const StatCollector &rhs  ) const
{
    return false;
}

StatCollector StatCollector::operator + (const StatCollector &other)
{
    StatCollector res(*this);

    res += other;

    return res;
}

StatCollector &StatCollector::operator += (const StatCollector &other)
{
    if(other._elemVec.size() > _elemVec.size())
    {
        _elemVec.resize(other._elemVec.size());
    }

    for(UInt32 i = 0; i < _elemVec.size(); ++i)
    {
        if(_elemVec[i])
        {
            *_elemVec[i] += *other._elemVec[i];
        }
    }

    return *this;
}

OSG_END_NAMESPACE

#include "OSGSField.h"
#include "OSGSField.ins"

#include "OSGMField.h"
#include "OSGMField.ins"

#include "OSGFieldContainer.h"

OSG_BEGIN_NAMESPACE

#ifndef OSG_DO_DOC

/*-------------------------- field instantiations -------------------------*/

DataType FieldTraits<StatCollectorP>::_type("StatCollectorP",
                                            "TypeRoot");


DataType &FieldTraits<StatCollectorP>::getType(void) 
{
    return _type;          
}
#endif

OSG_FIELD_DLLEXPORT_DEF1(SField, StatCollectorP);

OSG_END_NAMESPACE

