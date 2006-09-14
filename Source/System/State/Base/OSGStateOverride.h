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

#ifndef _OSGSTATEOVERRIDE_H_
#define _OSGSTATEOVERRIDE_H_

#ifdef __sgi
#pragma once
#endif

#include "OSGBaseTypes.h"
#include "OSGSystemDef.h"
#include "OSGSimplePool.h"

#include <vector>
#include <utility>
#include <algorithm>

OSG_BEGIN_NAMESPACE

class StateChunk;

/*! \ingroup GrpSystemRenderingBackend
*/

class OSG_SYSTEM_DLLMAPPING StateOverride 
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef std::pair  <UInt32, StateChunk *>           ChunkElement;

    typedef std::vector<ChunkElement        >           ChunkStore;
    typedef std::vector<ChunkElement        >::iterator ChunkStoreIt;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    StateOverride(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~StateOverride(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Statistic                                  */
    /*! \{                                                                 */

    void fillFrom(StateOverride *pState);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Statistic                                  */
    /*! \{                                                                 */

    ChunkStoreIt begin(void);
    ChunkStoreIt end  (void);
    UInt32       size (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Access                                    */
    /*! \{                                                                 */

    void reset      (void             );
    void addOverride(UInt32      uiSlot, 
                     StateChunk *pChunk);
    bool empty      (void              );

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    ChunkStore _vChunks;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    template <class T> friend class SimplePool;

    /*! \brief prohibit default function (move to 'public' if needed) */
    StateOverride(const StateOverride &source);
    /*! \brief prohibit default function (move to 'public' if needed) */
    void operator =(const StateOverride &source);
};

bool operator <(const StateOverride::ChunkElement &lhs, 
                const StateOverride::ChunkElement &rhs);

OSG_END_NAMESPACE

#include "OSGStateOverride.inl"

#define OSGSTATEOVERRIDE_HEADER_CVSID "@(#)$Id$"

#endif /* _OSGSTATEOVERRIDE_H_ */
