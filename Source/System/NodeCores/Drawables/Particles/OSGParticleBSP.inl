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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

// exclude the whole class from user docs
#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)

OSG_BEGIN_NAMESPACE

inline
bool ParticleBSPNode::isLeaf(void) const
{
    return _axis == Leaf;
}

inline
Int32 ParticleBSPNode::getValue(void) const
{
    return _value;
}

inline
Real32 ParticleBSPNode::getSplitValue(void) const
{
    return _splitvalue;
}

inline
UInt8 ParticleBSPNode::getAxis(void) const
{
    return _axis;
}

inline
void ParticleBSPNode::setValue(Int32 value)
{
    _value = value;
    _axis = Leaf;
}

inline
void ParticleBSPNode::setSplit(UInt8 axis, Real32 splitvalue)
{
    _splitvalue = splitvalue;
    _axis       = axis;
}

inline 
bool ParticleBSPTree::created(void) const
{
    return _tree.size() > 1;
}

OSG_END_NAMESPACE

#endif // Doc exclude

#define OSGPARTICLEBSP_INLINE_CVSID "@(#)$Id$"

