/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                   Copyright (C) 2008 by the OpenSG Forum                  *
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

#ifndef _OSGFIELDCONTAINERUTILS_H_
#define _OSGFIELDCONTAINERUTILS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGSystemDef.h"
#include "OSGFieldContainer.h"
#include "OSGAction.h"

#include <iosfwd>

OSG_BEGIN_NAMESPACE

OSG_SYSTEM_DLLMAPPING
bool compareContainerEqual(const FieldContainer *lhs,
                           const FieldContainer *rhs,
                                 bool            ignoreAttachments = true,
                                 bool            compareIdentity   = false);

//---------------------------------------------------------------------------
//  MemoryConsumption
//---------------------------------------------------------------------------

class OSG_SYSTEM_DLLMAPPING MemoryConsumption
{
  public:
    typedef std::pair<UInt32, UInt32      >       MemCountPair;
    typedef std::map <UInt32, MemCountPair>       TypeMemMap;
    typedef TypeMemMap::iterator                  TypeMemMapIt;
    typedef TypeMemMap::const_iterator            TypeMemMapConstIt;
    
    void scan (void                                     );
    void print(std::ostream &os, bool ignoreProto = true) const;
    
    TypeMemMapConstIt beginMap     (void) const;
    TypeMemMapConstIt endMap       (void) const;

    TypeMemMapConstIt beginAccumMap(void) const;
    TypeMemMapConstIt endAccumMap  (void) const;
    
  private:
    TypeMemMap _memMap;
};

//---------------------------------------------------------------------------
//  SceneGraphPrinter
//---------------------------------------------------------------------------

class OSG_SYSTEM_DLLMAPPING SceneGraphPrinter
{
  public:
    typedef SceneGraphPrinter Self;

    SceneGraphPrinter(Node *root);

    void printDownTree(std::ostream &os);
    void printUpTree  (std::ostream &os);

  private:
    Node         *_pRoot;
    std::ostream *_pStream;
    UInt32        _indent;

    Action::ResultE traverseEnter(Node *node                     );
    Action::ResultE traverseLeave(Node *node, Action::ResultE res);

    void          incIndent   (void            );
    void          decIndent   (void            );
    std::ostream &indentStream(std::ostream &os);
};


OSG_END_NAMESPACE

#endif // _OSGFIELDCONTAINERUTILS_H_
