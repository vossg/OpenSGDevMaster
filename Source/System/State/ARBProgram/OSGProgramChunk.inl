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
const StateChunkClass *ProgramChunk::getStaticClass(void)
{
    return &ProgramChunk::_class;
}

inline
UInt32 ProgramChunk::getStaticClassId(void)
{
    return getStaticClass()->getId();
}


/*--------------------------- Access ------------------------------------*/

/*! Concvenience function to add a new parameter and directly set its value.
*/

inline
Int16 ProgramChunk::findParameter(const char *name)
{
    return findParameter(std::string(name));
}

inline
bool ProgramChunk::addParameter(const char   *name, 
                                      Int16  index, 
                                const Vec4f  &value)
{
    addParameter(name, index);

    return setParameter(index, value);
}

inline 
const Vec4f &ProgramChunk::getParameter(const char *name)
{
    return getParameter(findParameter(name));
}

inline 
const Vec4f &ProgramChunk::getParameter(const std::string &name)
{
    return getParameter(findParameter(name.c_str()));
}

inline       
bool ProgramChunk::setParameter(const char *name, const Vec4f& value)
{
    return setParameter(findParameter(name), value);
}

inline       
bool ProgramChunk::setParameter(const std::string &name, const Vec4f &value)
{
    return setParameter(findParameter(name.c_str()), value);
}
    
OSG_END_NAMESPACE

#define OSGPROGRAMCHUNK_INLINE_CVSID "@(#)$Id: $"

