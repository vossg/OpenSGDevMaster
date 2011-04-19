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

template<typename ValueT> 
const std::string StringValueMapper<ValueT>::szUnknown("NONEXX");

template<typename ValueT> inline
const std::string &StringValueMapper<ValueT>::toString(const ValueT eval) const
{
    typename MapFromValue::const_iterator mIt = _mFromValue.find(eval);

    if(mIt != _mFromValue.end())
    {
        return mIt->second;
    }
    else
    {
        return szUnknown;
    }
}

template<typename ValueT> inline
ValueT StringValueMapper<ValueT>::fromString(const Char8  *sval) const
{
    ValueT returnValue = 0;

    if(sval == NULL)
        return returnValue;

    if(sval[0] >= 48 && sval[0] <= 57)
    {
        returnValue = TypeTraits<ValueT>::getFromCString(sval);
    }
    else
    {
        typename MapToValue::const_iterator mIt = _mToValue.find(sval);

        if(mIt != _mToValue.end())
        {
            returnValue = mIt->second;
        }
        else
        {
            FWARNING(("Unknow string constant : %s\n", sval));
        }
    }

    return returnValue;
}

template<typename ValueT> inline
void StringValueMapper<ValueT>::addToValuePair(const std::string &sval, 
                                               const      ValueT   val)
{
#ifdef OSG_DEBUG
    typename MapToValue::const_iterator mIt = _mToValue.find(sval);

    if(mIt != _mToValue.end())
    {
        fprintf(stderr, "%s already present : %x|%x\n",
                sval.c_str(),
                val,
                mIt->second);
    }
    else
    {
#endif
        _mToValue.insert(std::make_pair(sval, val));
#ifdef OSG_DEBUG
    }
#endif
}

template<typename ValueT> inline
void StringValueMapper<ValueT>::addFromValuePair(const      ValueT  val, 
                                                 const std::string &sval)
{
#ifdef OSG_DEBUG
    typename MapFromValue::const_iterator mIt = _mFromValue.find(val);

    if(mIt != _mFromValue.end())
    {
        fprintf(stderr, "%x already present : %s|%s\n",
                val,
                sval.c_str(),
                mIt->second.c_str());
    }
    else
    {
#endif
        _mFromValue.insert(std::make_pair(val, sval));
#ifdef OSG_DEBUG
    }
#endif
}

template<typename ValueT> inline
StringValueMapper<ValueT>::StringValueMapper(void) :
    _mToValue  (),
    _mFromValue()
{
}

template<typename ValueT> inline
StringValueMapper<ValueT>::~StringValueMapper(void)
{
}


inline
void GLDefineMapperBase::addToEnumPair(const std::string &sval, 
                                       const      GLenum  eval)
{
    Inherited::addToValuePair(sval, eval);
}

inline
void GLDefineMapperBase::addFromEnumPair(const      GLenum  eval, 
                                         const std::string &sval)
{
    Inherited::addFromValuePair(eval, sval);
}

OSG_END_NAMESPACE

