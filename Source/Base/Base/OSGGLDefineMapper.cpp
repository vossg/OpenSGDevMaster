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

//-------------------------------
//  Includes
//-------------------------------

#define OSG_COMPILE_GLDEFINEMAPPER

#include "OSGGLDefineMapper.h"

#include "OSGSingletonHolder.ins"

OSG_BEGIN_NAMESPACE

OSG_SINGLETON_INST(GLDefineMapperBase, addPostFactoryExitFunction)

template class SingletonHolder<GLDefineMapperBase>;

const std::string GLDefineMapperBase::szUnknown("NONEXX");


const std::string &GLDefineMapperBase::toString(const GLenum eval) const
{
    MapFromEnum::const_iterator mIt = _mFromEnum.find(eval);

    if(mIt != _mFromEnum.end())
    {
        return mIt->second;
    }
    else
    {
        return szUnknown;
    }
}

GLenum GLDefineMapperBase::fromString(const Char8  *sval) const
{
    GLenum returnValue = 0x0000;

    if((sval[0] != '\0' && sval[0] == 'G') &&
       (sval[1] != '\0' && sval[1] == 'L') &&
       (sval[2] != '\0' && sval[2] == '_')   )
    {
        MapToEnum::const_iterator mIt = _mToEnum.find(sval + 3);

        if(mIt != _mToEnum.end())
        {
            returnValue = mIt->second;
        }
        else
        {
            FWARNING(("Unknow gl constant : %s\n", sval));
        }
    }
    else if(sval[0] >= 48 && sval[0] <= 57)
    {
        returnValue = TypeTraits<GLenum>::getFromCString(sval);
    }
    else
    {
        MapToEnum::const_iterator mIt = _mToEnum.find(sval);

        if(mIt != _mToEnum.end())
        {
            returnValue = mIt->second;
        }
        else
        {
            FWARNING(("Unknow gl constant : %s\n", sval));
        }
    }

    return returnValue;
}


GLDefineMapperBase::GLDefineMapperBase(void) :
    _mToEnum  (),
    _mFromEnum()
{
    initMaps();
}

GLDefineMapperBase::~GLDefineMapperBase(void)
{
}

void GLDefineMapperBase::addToEnumPair(const std::string &sval, 
                                       const      GLenum  eval)
{
#ifdef OSG_DEBUG
    MapToEnum::const_iterator mIt = _mToEnum.find(sval);

    if(mIt != _mToEnum.end())
    {
        fprintf(stderr, "%s already present : %x|%x\n",
                sval.c_str(),
                eval,
                mIt->second);
    }
    else
    {
#endif
        _mToEnum.insert(std::make_pair(sval, eval));
#ifdef OSG_DEBUG
    }
#endif
}

void GLDefineMapperBase::addFromEnumPair(const      GLenum  eval, 
                                         const std::string &sval)
{
#ifdef OSG_DEBUG
    MapFromEnum::const_iterator mIt = _mFromEnum.find(eval);

    if(mIt != _mFromEnum.end())
    {
        fprintf(stderr, "%x already present : %s|%s\n",
                eval,
                sval.c_str(),
                mIt->second.c_str());
    }
    else
    {
#endif
        _mFromEnum.insert(std::make_pair(eval, sval));
#ifdef OSG_DEBUG
    }
#endif
}

OSG_END_NAMESPACE
