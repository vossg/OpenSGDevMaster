/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                     Copyright 2000-2002 by OpenSG Forum                   *
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

/*------------------------------- size ----------------------------------*/

/*! Calculate the width of the viewport in Pixel.
 */ 

inline 
Int32 Viewport::getPixelWidth(void) const
{
    return getPixelRight() - getPixelLeft() + 1;
}

/*! Calculate the height of the viewport in Pixel.
 */ 

inline 
Int32 Viewport::getPixelHeight(void) const
{
    return getPixelTop() - getPixelBottom() + 1;
}

/*---------------------------- properties ---------------------------------*/

/*! Set all of the size-related fields of the viewport.
 */ 

inline 
void Viewport::setSize(Real32 left, 
                       Real32 bottom, 
                       Real32 right, 
                       Real32 top  )
{
    setLeft  (left  );
    setRight (right );
    setBottom(bottom);
    setTop   (top   );
}

inline
StageValidator *Viewport::getStageValidator(void)
{
    return _pStageValidator;
}

//! Set the value of the Viewport::_sfParent field.
inline
void Viewport::setParent(      
          ParentFieldContainerPtrConstArg value,
    const UInt16                          uiStoredInFieldId)
{
    editSField(ParentFieldMask);

    _sfParent.setValue(value);
    _sfParent.getValue().setParentFieldPos(uiStoredInFieldId);

}

OSG_END_NAMESPACE

#define OSGVIEWPORT_INLINE_CVSID "@(#)$Id$"

