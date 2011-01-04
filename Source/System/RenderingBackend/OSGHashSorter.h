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

#ifndef _OSGHASHSORTER_H_
#define _OSGHASHSORTER_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include "OSGSystemDef.h"
#include "OSGBaseTypes.h"
#include "OSGDeprecatedCPP.h"
#include "OSGPool.h"
#include "OSGRenderTreeNode.h"

#include "google/dense_hash_map"

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------


/*! \brief HashSorter class
    \ingroup GrpSystemRenderingBackendBase
    \ingroup GrpLibOSGSystem
 */

class OSG_SYSTEM_DLLMAPPING HashSorter
{
  public:

    //-----------------------------------------------------------------------
    //   constants                                                             
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    /*------------------------- your_category -------------------------------*/

     HashSorter(void);
    ~HashSorter(void);

    /*------------------------- your_operators ------------------------------*/

    /*------------------------- assignment ----------------------------------*/
    
    /*------------------------- comparison ----------------------------------*/

    void reset(void);

    /*------------------------- comparison ----------------------------------*/

    RenderTreeNode *find  (UInt16          uiKey1,
                           UInt16          uiKey2,
                           UInt16          uiKey3);

    void            insert(UInt16              uiKey1,
                           UInt16              uiKey2,
                           UInt16              uiKey3,
                           RenderTreeNode     *pNode,
                           RenderTreeNodePool *pPool );

    /*-------------------------- comparison ---------------------------------*/

    void setupLevel1Root(RenderTreeNode *pRoot);

    /*-------------------------- comparison ---------------------------------*/

  protected:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    /*! \nohierarchy
     */

    struct Level3Sorter
    {
        typedef google::dense_hash_map<UInt16, 
                                       RenderTreeNode *>  LevelMap;
        typedef LevelMap::iterator                        LevelMapIt;


        RenderTreeNode *_pRoot;
        LevelMap        _mLevelMap;


        void clear(void);
        void init (void);
    };

    /*! \nohierarchy
     */

    struct Level2Sorter
    {
        typedef google::dense_hash_map<UInt16, 
                                       Level3Sorter *>  LevelMap;
        typedef LevelMap::iterator                      LevelMapIt;


        RenderTreeNode *_pRoot;
        LevelMap        _mLevelMap;


        void clear(void);
        void init (void);
    };

    /*! \nohierarchy
     */

    struct Level1Sorter
    {
        typedef HashSorter::Level2Sorter                Level2Sorter;
        typedef google::dense_hash_map<UInt16, 
                                       Level2Sorter *>  LevelMap;
        typedef LevelMap::iterator                      LevelMapIt;

        RenderTreeNode *_pRoot;
        LevelMap        _mLevelMap;

        void            clear    (void                 );
        void            init     (void                 );
        void            setupRoot(RenderTreeNode *pRoot);
    };

    static void initLevel2Sorter(Level2Sorter *pElement);
    static void initLevel3Sorter(Level3Sorter *pElement);

    typedef Pool< Level3Sorter, 
                  initLevel3Sorter,
                 &Level3Sorter::clear           > Level3Pool;

    typedef Pool< Level2Sorter, 
                  initLevel2Sorter,
                 &Level2Sorter::clear           > Level2Pool;

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    Level3Pool   _oLevel3Pool;
    Level2Pool   _oLevel2Pool;

    Level1Sorter _oLevel1Sorter;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   friend classes                                                      
    //-----------------------------------------------------------------------

    template <class ValueT, 
        void (        *InitFunction )(ValueT *),
        void (ValueT::*ClearFunction)(void    )>
    friend class Pool;

    //-----------------------------------------------------------------------
    //   friend functions                                                    
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------
   
    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------
    
    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const HashSorter &source);    
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

OSG_END_NAMESPACE

#include "OSGHashSorter.inl"

#endif /* _OSGHASHSORTER_H_ */


