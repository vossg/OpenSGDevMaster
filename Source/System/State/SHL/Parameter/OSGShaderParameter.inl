/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
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

OSG_BEGIN_NAMESPACE

inline
void ShaderParameter::setTypeId(ShaderParameter::SHPType type)
{
    _typeid = type;
}

inline
ShaderParameter::SHPType ShaderParameter::getTypeId(void)
{
    return _typeid;
}

inline
void ShaderParameter::setLocation(GLint location)
{
    _location = location;
}

inline
GLint ShaderParameter::getLocation(void)
{
    return _location;
}

inline
bool ShaderParameter::hasChanged(void)
{
    return _changed;
}

inline
void ShaderParameter::resetChanged(void)
{
    _changed = false;
}

inline
void ShaderParameter::setChanged(void)
{
    _changed = true;
}

inline
UInt32 ShaderParameter::getFlags(void)
{
    return _flags;
}

inline
void  ShaderParameter::setFlags(UInt32 flags)
{
    _flags = flags;
}

OSG_END_NAMESPACE

#define OSGSHADERPARAMETER_INLINE_CVSID "@(#)$Id$"

