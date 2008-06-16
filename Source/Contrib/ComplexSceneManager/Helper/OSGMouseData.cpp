/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2008 by the OpenSG Forum                          *
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

#include "OSGMouseData.h"
#include "OSGMouseDataFields.h"

#include <OSGSField.ins>

OSG_BEGIN_NAMESPACE

MouseData::MouseData(void) :
    _iButton  (-1  ),
    _iState   (-1  ),
    _iModifier(-1  ),
    _iX       (-1  ),
    _iY       (-1  ),
    _pWindow  (NULL)
{
}


MouseData::MouseData(const MouseData &source) :
    _iButton  (source._iButton  ),
    _iState   (source._iState   ),
    _iModifier(source._iModifier),
    _iX       (source._iX       ),
    _iY       (source._iY       ),
    _pWindow  (NULL             )
{
}

MouseData::~MouseData(void)
{
}

/*------------------------------ access -----------------------------------*/

void MouseData::setData(Int32      iButton, 
                        Int32      iState,
                        Int32      iModifier,
                        Int32      x,       
                        Int32      y,
                        Window    *pWindow  )
{
    _iButton   = iButton;
    _iState    = iState;
    _iModifier = iModifier;
    _iX        = x;
    _iY        = y;
    _pWindow   = pWindow;
}

void MouseData::setData(Int32   x,       
                        Int32   y,
                        Window *pWindow)
{
    _iButton   = -1;
    _iState    = -1;
    _iModifier = -1;

    _iX        = x;
    _iY        = y;

    _pWindow   = pWindow;
}

void MouseData::operator = (const MouseData &rhs)
{
    _iButton   = rhs._iButton;
    _iState    = rhs._iState;
    _iModifier = rhs._iModifier;
    _iX        = rhs._iX;
    _iY        = rhs._iY;
    _pWindow   = rhs._pWindow;
}

bool MouseData::operator ==(const MouseData &rhs) const
{
    return (_iButton   == rhs._iButton   &&
            _iState    == rhs._iState    &&
            _iModifier == rhs._iModifier &&
            _iX        == rhs._iX        &&
            _iY        == rhs._iY        &&
            _pWindow   == rhs._pWindow    );
}


DataType FieldTraits<MouseData>::_type("MouseData",        "BaseType"    );

OSG_FIELDTRAITS_GETTYPE (        MouseData    )
OSG_FIELD_DLLEXPORT_DEF1(SField, MouseData    )

OSG_END_NAMESPACE
