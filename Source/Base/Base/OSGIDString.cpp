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

#include "OSGConfig.h"

#include <cstring>
#include <cctype>


#include "OSGIDString.h"

OSG_USING_NAMESPACE

/*-------------------------- Constructor ----------------------------------*/

IDString::IDString(UInt32 size) : 
    _str    (NULL), 
    _memType(COPY)
{
    setLength(size);
}

IDString::IDString(const Char8 *str, MemType memType) : 
    _str    (NULL   ), 
    _memType(memType)
{
    set(str, memType);
}

IDString::IDString(const IDString &obj, MemType memType) :
    _str    (NULL   ), 
    _memType(memType)
{
    set(obj._str, memType);
}


/*-------------------------- Destructor -----------------------------------*/

IDString::~IDString()
{
    if(_memType == COPY)
        delete [] _str;

    _str = NULL;
}


/*------------------------------ access -----------------------------------*/

void IDString::set(const Char8 *str, MemType memType)
{
    if(str == _str)
    {
        // !!! can you change _memType here? I think not. IMHO
        return;
    }

    if(_memType == COPY)
        delete [] _str;

    if(memType == COPY)
    {
        if(str != NULL)
        {
            _str = new Char8[strlen(str) + 1];

            strcpy(_str, str);
        }
        else
        {
            _str = NULL;
        }
    }
    else
    {
        _str = const_cast<Char8 *>(str);
    }

    _memType = memType;
}

#ifdef OSG_WIN32_ICL
#pragma warning ( disable : 810 )
#endif

void IDString::toUpper(void)
{
    UInt32 l = getLength();

    for(UInt32 i = 0; i < l; ++i)
    {
        _str[i] = ::toupper(_str[i]);
    }

}

void IDString::toLower(void)
{
    UInt32 l = getLength();

    for(UInt32 i = 0; i < l; ++i)
    {
        _str[i] = ::tolower(_str[i]);
    }

}

#ifdef OSG_WIN32_ICL
#pragma warning ( default : 810 )
#endif

UInt32 IDString::getLength(void) const
{
    return (_str != NULL) ? ::strlen(_str) : 0;
}

void IDString::setLength(UInt32 length)
{
    if(_memType == COPY)
        delete [] _str;

    if(length != 0)
    {
         _str = new Char8[length];
        *_str = 0;
    }
    else
    {
        _str = 0;
    }

    _memType = COPY;
}

void IDString::tokenize(StringVec &v)
{
    UInt32 l        = getLength();
    UInt32 oldpos   = 0;
    UInt32 pos      = 0;
    bool   inQuotes = false;
    bool   inToken  = false;

    if(l > 0)
    {
        Char8 *buf = new Char8[l + 1];

        for(pos = 0; pos <= l; ++pos)
        {
            if(!inQuotes)
            {
                if(!inToken)
                {
                    if(_str[pos] == '"')
                    {
                        inQuotes = true;
                        oldpos   = pos + 1;
                    }
                    else if(_str[pos] != ' ')
                    {
                        inToken = true;
                        oldpos  = pos;
                    }
                }
                else if(inToken)
                {
                    if(_str[pos] == '"')
                    {
                        inToken = false;

                        strncpy(buf, _str + oldpos, pos - oldpos);

                        buf[pos - oldpos] = '\0';

                        v.push_back(IDString(buf));

                        inQuotes = true;
                        oldpos   = pos;
                    }
                    else if(_str[pos] == ' ')
                    {
                        inToken = false;

                        strncpy(buf, _str + oldpos, pos - oldpos);

                        buf[pos - oldpos] = '\0';

                        v.push_back(IDString(buf));
                    }
                    else if(pos == l)
                    {
                        strncpy(buf, _str + oldpos, pos - oldpos);

                        buf[pos - oldpos] = '\0';

                        v.push_back(IDString(buf));
                    }
                }
            }
            else if(inQuotes)
            {
                if(_str[pos] == '"')
                {
                    inQuotes = false;

                    if(pos > oldpos)
                    {
                        strncpy(buf, _str + oldpos, pos - oldpos);

                        buf[pos - oldpos] = '\0';

                        v.push_back(IDString(buf));
                    }
                }
                else if(pos == l)
                {
                    if(pos > oldpos)
                    {
                        strncpy(buf, _str + oldpos, pos - oldpos);

                        buf[pos - oldpos] = '\0';

                        v.push_back(IDString(buf));
                    }
                }
            }
        }

        delete [] buf;
    }
}

void IDString::tokenize(StringPVec &v)
{
    UInt32 l        = getLength();
    UInt32 oldpos   = 0;
    UInt32 pos      = 0;
    bool   inQuotes = false;
    bool   inToken  = false;

    IDString *pString = NULL;

    if(l > 0)
    {
        Char8 *buf = new Char8[l + 1];

        for(pos = 0; pos <= l; ++pos)
        {
            if(!inQuotes)
            {
                if(!inToken)
                {
                    if(_str[pos] == '"')
                    {
                        inQuotes = true;
                        oldpos   = pos + 1;
                    }
                    else if(_str[pos] != ' ')
                    {
                        inToken = true;
                        oldpos  = pos;
                    }
                }
                else if(inToken)
                {
                    if(_str[pos] == '"')
                    {
                        inToken = false;

                        strncpy(buf, _str + oldpos, pos - oldpos);

                        buf[pos - oldpos] = '\0';

                        pString =  new IDString(buf);

                        v.push_back(pString);

                        inQuotes = true;
                        oldpos   = pos;

                    }
                    else if(_str[pos] == ' ')
                    {
                        inToken = false;

                        strncpy(buf, _str + oldpos, pos - oldpos);

                        buf[pos - oldpos] = '\0';

                        pString =  new IDString(buf);

                        v.push_back(pString);
                    }
                    else if(pos == l)
                    {
                        strncpy(buf, _str + oldpos, pos - oldpos);

                        buf[pos - oldpos] = '\0';

                        pString =  new IDString(buf);

                        v.push_back(pString);
                    }
                }
            }
            else if(inQuotes)
            {
                if(_str[pos] == '"')
                {
                    inQuotes = false;

                    if(pos > oldpos)
                    {
                        strncpy(buf, _str + oldpos, pos - oldpos);

                        buf[pos - oldpos] = '\0';

                        pString =  new IDString(buf);

                        v.push_back(pString);
                    }
                }
                else if(pos == l)
                {
                    if(pos > oldpos)
                    {
                        strncpy(buf, _str + oldpos, pos - oldpos);

                        buf[pos - oldpos] = '\0';

                        pString =  new IDString(buf);

                        v.push_back(pString);
                    }
                }
            }
        }

        delete [] buf;
    }
}


OSG_BEGIN_NAMESPACE

OSG_BASE_DLLMAPPING 
std::ostream &operator <<(      std::ostream &os, 
                          const IDString     &obj)
{
    return os << (obj.str() ? obj.str() : "0 IDString");
}

OSG_BASE_DLLMAPPING 
OutStream &operator <<(      OutStream  &os,
                       const IDString   &obj)
{
    return os << (obj.str() ? obj.str() : "0 IDString");
}

OSG_END_NAMESPACE
