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

inline
void HashSorter::Level3Sorter::clear(void)
{
    _mLevelMap.clear();

    _pRoot = NULL;
}

inline
void HashSorter::Level3Sorter::init(void)
{
    _mLevelMap.set_empty_key  (0xFFFF);
    _mLevelMap.set_deleted_key(0xFFFE);

    _pRoot = NULL;
}

inline
void HashSorter::Level2Sorter::clear(void)
{
    _mLevelMap.clear();

    _pRoot = NULL;
}

inline
void HashSorter::Level2Sorter::init(void)
{
    _mLevelMap.set_empty_key  (0xFFFF);
    _mLevelMap.set_deleted_key(0xFFFE);

    _pRoot = NULL;
}

inline
void HashSorter::Level1Sorter::clear(void)
{
    _mLevelMap.clear();

    _pRoot = NULL;
}

inline
void HashSorter::Level1Sorter::init(void)
{
    _mLevelMap.set_empty_key  (0xFFFF);
    _mLevelMap.set_deleted_key(0xFFFE);

    _pRoot = NULL;
}

inline
RenderTreeNode *HashSorter::Level1Sorter::setupRoot(RenderTreeNodePool *pPool)
{
    if(_pRoot == NULL)
        _pRoot = pPool->create();

    return _pRoot;
}

inline
void HashSorter::initLevel2Sorter(Level2Sorter *pElement)
{
    pElement->init();
}

inline
void HashSorter::initLevel3Sorter(Level3Sorter *pElement)
{
    pElement->init();
}

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

inline
void HashSorter::reset(void)
{
    _oLevel3Pool.freeAll();
    _oLevel2Pool.freeAll();

    _oLevel1Sorter.clear();
}

inline
RenderTreeNode *HashSorter::setupLevel1Root(RenderTreeNodePool *pPool)
{
    return _oLevel1Sorter.setupRoot(pPool);
}


/*------------- constructors & destructors --------------------------------*/

/*------------------------------ access -----------------------------------*/

/*---------------------------- properties ---------------------------------*/

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

#define OSGHASHSORTER_INLINE_CVSID "@(#)$Id$"
