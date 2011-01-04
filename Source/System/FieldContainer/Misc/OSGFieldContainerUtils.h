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
#include <map>

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpSystemFieldContainerUtils
 */

OSG_SYSTEM_DLLMAPPING
bool compareContainerEqual(const FieldContainer *lhs,
                           const FieldContainer *rhs,
                                 bool            ignoreAttachments = true,
                                 bool            compareIdentity   = false);

//---------------------------------------------------------------------------
//  MemoryConsumption
//---------------------------------------------------------------------------

/*! \ingroup GrpSystemFieldContainerUtils
    \ingroup GrpLibOSGSystem
    \nohierarchy
 */

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

/*! \ingroup GrpSystemFieldContainerUtils
    \ingroup GrpLibOSGSystem
    \nohierarchy
 */

class OSG_SYSTEM_DLLMAPPING SceneGraphPrinter
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
    /*! \{                                                                 */

    typedef SceneGraphPrinter Self;

    typedef boost::function<void (SceneGraphPrinter *,
                                  NodeCore          * )>  CorePrintFunction;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constructors/Destructor                                      */
    /*! \{                                                                 */

    SceneGraphPrinter(Node *root);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Printing                                                     */
    /*! \{                                                                 */

    void printDownTree(std::ostream &os);
    void printUpTree  (std::ostream &os);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Core Print Function                                          */
    /*! \{                                                                 */

    void addPrintFunc(const FieldContainerType &fcTpye,
                      const CorePrintFunction  &printFunc);
    void subPrintFunc(const FieldContainerType &fcTpye   );

    void          incIndent   (void);
    void          decIndent   (void);
    std::ostream &indentStream(void);
    std::ostream &getStream   (void);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef std::map<UInt32, CorePrintFunction> PrintFuncMap;
    typedef PrintFuncMap::iterator              PrintFuncMapIt;
    typedef PrintFuncMap::const_iterator        PrintFuncMapConstIt;

    Node         *_pRoot;
    std::ostream *_pStream;
    UInt32        _indent;
    PrintFuncMap  _printFuncMap;

    Action::ResultE traverseEnter(Node *node                     );
    Action::ResultE traverseLeave(Node *node, Action::ResultE res);
};

struct FieldPathEntry;

/*! \ingroup GrpSystemFieldContainerUtils
 */

typedef boost::function<
          FieldContainer * (const Char8 *szName)> ContainerResolver;

/*! \ingroup GrpSystemFieldContainerUtils
 */

OSG_SYSTEM_DLLMAPPING
void splitFieldPath(      std::vector<FieldPathEntry> &vSplitPath,
                    const Char8                       *szFieldPath);

/*! \ingroup GrpSystemFieldContainerUtils
 */

FieldContainer *resolveFieldPath(std::vector<FieldPathEntry> &vSplitPath, 
                                 FieldContainer              *pRoot     );

/*! \ingroup GrpSystemFieldContainerUtils
 */

FieldContainer *resolveFieldPath(const Char8             *szNodeName, 
                                       ContainerResolver  oResolver );

OSG_END_NAMESPACE

#endif // _OSGFIELDCONTAINERUTILS_H_
