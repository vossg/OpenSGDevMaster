/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2000,2001,2002 by the OpenSG Forum                *
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

#ifndef _OSGDRAWTREENODEFACTORY_H_
#define _OSGDRAWTREENODEFACTORY_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGBaseTypes.h"
#include "OSGSystemDef.h"
#include "OSGDrawTreeNode.h"

#include <vector>

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpSystemRenderingBackend
*/

class OSG_SYSTEM_DLLMAPPING DrawTreeNodeFactory 
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    DrawTreeNodeFactory(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~DrawTreeNodeFactory(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      create                                  */
    /*! \{                                                                 */

    DrawTreeNode *create(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       free                                   */
    /*! \{                                                                 */
    
    void freeAll(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       stat                                   */
    /*! \{                                                                 */
    
    void printStat(void);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef std::vector<DrawTreeNode *>           DrawTreeNodeStore;

    typedef std::vector<DrawTreeNode *>::iterator DrawTreeNodeStoreIt;

    
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    DrawTreeNodeStore   _nodeStore;
    DrawTreeNodeStoreIt _currentFreeNode;

    UInt32              _uiAllocated;
    UInt32              _uiReused;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    /*!\brief prohibit default function (move to 'public' if needed) */
    DrawTreeNodeFactory(const DrawTreeNodeFactory &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const DrawTreeNodeFactory &source);
};

OSG_END_NAMESPACE

#define OSGDRAWTREENODEFACTORY_HEADER_CVSID "@(#)$Id$"

#include "OSGDrawTreeNodeFactory.inl"

#endif /* _OSGDRAWTREENODEFACTORY_H_ */
