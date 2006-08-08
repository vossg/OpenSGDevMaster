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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#define OSG_COMPILE_IOSTREAM

#include "OSGIOStream.h"
#include "OSGBaseTypes.h"

OSG_BEGIN_NAMESPACE

void IncIndent(_IncIndent) {}
void DecIndent(_DecIndent) {}
void BeginElem(_BeginElem) {}
void EndElem  (_EndElem  ) {}
void EndElemNL(_EndElemNL) {}

OSG_END_NAMESPACE

OSG_USING_NAMESPACE

//---------------------------------------------------------------------------
//  OutStream
//---------------------------------------------------------------------------


/*-------------------------- constructor ----------------------------------*/

OutStream::OutStream(std::ostream &baseStream) :
    _pBaseStream(&baseStream)
{
}

/*--------------------------- destructor ----------------------------------*/

OutStream::~OutStream(void)
{
}

inline
OutStream &OutStream::operator<<(const Fixed32 &val)
{
    (*_pBaseStream) << val.getValue();
    
    return *this;
}



//---------------------------------------------------------------------------
//  InStream
//---------------------------------------------------------------------------


/*-------------------------- constructor ----------------------------------*/

InStream::InStream(std::istream &baseStream) :
    _pBaseStream(&baseStream)
{
}

/*--------------------------- destructor ----------------------------------*/

InStream::~InStream(void)
{
}


