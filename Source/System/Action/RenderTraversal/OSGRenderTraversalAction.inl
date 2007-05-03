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

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/


/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/


/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/


/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/*------------------------------ access -----------------------------------*/

/*---------------------------- properties ---------------------------------*/

inline
void RenderTraversalAction::setKeyGen(UInt32 uiKeyGen)
{
    _uiKeyGen = uiKeyGen;
}

inline
void RenderTraversalAction::addPassMask(BitVector bvMask)
{
    _bvPassMask |= bvMask;
}

inline
void RenderTraversalAction::subPassMask(BitVector bvMask)
{
    _bvPassMask &= ~bvMask;
}

inline
BitVector RenderTraversalAction::getPassMask(void)
{
    return _bvPassMask;
}

inline
void RenderTraversalAction::setUseGLFinish(bool bVal)
{
    _bUseGLFinish = bVal;
}

inline
bool RenderTraversalAction::getUseGLFinish(void)
{
    return _bUseGLFinish;
}

inline
void RenderTraversalAction::beginPartitionGroup(void)
{
    _sRenderPartitionIdxStack.push(_iActivePartitionIdx);

    _iActivePartitionIdx = _vRenderPartitions[_currentBuffer].size();

    _bInPartitionGroup = true;
}

inline
void RenderTraversalAction::endPartitionGroup(void)
{
    _iActivePartitionIdx = _sRenderPartitionIdxStack.top();

    _sRenderPartitionIdxStack.pop();

    _bInPartitionGroup = false;
}

/*-------------------------- your_category---------------------------------*/

/*-------------------------- assignment -----------------------------------*/

/*-------------------------- comparison -----------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

OSG_END_NAMESPACE
