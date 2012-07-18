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

#include "OSGSField.ins"

OSG_BEGIN_NAMESPACE

MouseData::MouseData(void) :
    _iButton    (-1       ),
    _iState     (-1       ),
    _iModifier  (-1       ),
    _rX         (-1.f     ),
    _rY         (-1.f     ),
    _pWindow    (NULL     ),
    _pViewport  (NULL     ),
    _uiMode     (AbsValues),
    _pActivePort(NULL     )
{
}


MouseData::MouseData(const MouseData &source) :
    _iButton    (source._iButton  ),
    _iState     (source._iState   ),
    _iModifier  (source._iModifier),
    _rX         (source._rX       ),
    _rY         (source._rY       ),
    _pWindow    (NULL             ),
    _pViewport  (NULL             ),
    _uiMode     (source._uiMode   ),
    _pActivePort(NULL             )
{
}

MouseData::~MouseData(void)
{
}

/*------------------------------ access -----------------------------------*/

void MouseData::setData(Int32      iButton, 
                        Int32      iState,
                        Int32      iModifier,
                        Real32     x,       
                        Real32     y,
                        Window    *pWindow,
                        UInt32     uiMode)
{
    _iButton   = iButton;
    _iState    = iState;
    _iModifier = iModifier;
    _rX        = x;
    _rY        = y;
    _pWindow   = pWindow;
    _pViewport = NULL;

    _uiMode    = uiMode;
}

void MouseData::updateData(Real32  x,       
                           Real32  y,
                           Window *pWindow,
                           UInt32  uiMode)
{
    _iButton   = -1;
    _iState    = -1;
    _iModifier = -1;

    _rX        = x;
    _rY        = y;

    _pWindow   = pWindow;

    _uiMode    = uiMode;
}

void MouseData::operator = (const MouseData &rhs)
{
    _iButton   = rhs._iButton;
    _iState    = rhs._iState;
    _iModifier = rhs._iModifier;
    _rX        = rhs._rX;
    _rY        = rhs._rY;
    _pWindow   = rhs._pWindow;
    _pViewport = rhs._pViewport;
    _uiMode    = rhs._uiMode;
}

bool MouseData::operator ==(const MouseData &rhs) const
{
    return (_iButton   == rhs._iButton   &&
            _iState    == rhs._iState    &&
            _iModifier == rhs._iModifier &&
            _rX        == rhs._rX        &&
            _rY        == rhs._rY        &&
            _pWindow   == rhs._pWindow   &&
            _pViewport == rhs._pViewport &&
            _uiMode    == rhs._uiMode      );
}

void MouseData::dump(void) const
{
    fprintf(stderr, "MouseData : %d %d %d | %f %f | %p | %p | %d\n",
            _iButton,
            _iState,
            _iModifier,
            _rX,
            _rY,
            _pWindow,
            _pViewport,
            _uiMode   );
}
    

DataType FieldTraits<MouseData>::_type("MouseData",        "BaseType"    );

OSG_FIELDTRAITS_GETTYPE (        MouseData    )
OSG_FIELD_DLLEXPORT_DEF1(SField, MouseData    )

OSG_END_NAMESPACE
