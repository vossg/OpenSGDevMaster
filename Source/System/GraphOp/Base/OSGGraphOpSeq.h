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


#ifndef _OSGGRAPHOPSEQ_H_
#define _OSGGRAPHOPSEQ_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGSystemDef.h"
#include "OSGAction.h"
#include "OSGGraphOp.h"

OSG_BEGIN_NAMESPACE

/*! \brief GraphOpSeq class
    \ingroup GrpSystemGraphOp
    \ingroup GrpSystemMemoryObjects
    \ingroup GrpLibOSGSystem
 */

class OSG_SYSTEM_DLLMAPPING GraphOpSeq : public MemoryObject
{
    /*==========================  PUBLIC  =================================*/
    
  public:

    typedef MemoryObject  Inherited;
    typedef GraphOpSeq    Self;
    
    OSG_GEN_INTERNAL_MEMOBJPTR(GraphOpSeq);

    /*---------------------------------------------------------------------*/
    /*! \name                    Class Get                                 */
    /*! \{                                                                 */

    static const char *getClassname(void) { return "GraphOpSeq"; };

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */
    
    static ObjTransitPtr create(      void               );
    static ObjTransitPtr create(const std::string &params);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Main methods                               */
    /*! \{                                                                 */

#ifndef OSG_DISABLE_DEPRECATED
    bool run     (Node *root);
#endif
    bool traverse(Node *root);

    /*! \}                                                                 */

    void setGraphOps(const std::string &params);

    void addGraphOp            (GraphOp *op                 );
    void removeGraphOp         (GraphOp *op                 );    
    void clearGraphOps         (void                        );

    UInt16      getSize        (void                        );
    GraphOp*    getGraphOp     (UInt16 index                );
    bool        setGraphOp     (UInt16 index, GraphOp *op   );
    bool        removeGraphOp  (UInt16 index                );

    /*=========================  PROTECTED  ===============================*/

  protected:    

    /*---------------------------------------------------------------------*/
    /*! \name              Constructors/Destructors                        */
    /*! \{                                                                 */

    GraphOpSeq(      void               );
    GraphOpSeq(const std::string &params);

    ~GraphOpSeq(void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:
    std::vector<GraphOpRefPtr> _graphOperators;
    std::list<std::string>     _excludeNames;

    UInt16 extractStr(const std::string  param, 
                            UInt16       spos, 
                      const Char8       *delim, 
                            std::string &result);
};

typedef GraphOpSeq *GraphOpSeqP;

OSG_GEN_MEMOBJPTR(GraphOpSeq);

OSG_END_NAMESPACE

#endif /* _OSGGRAPHOPSEQ_H_ */
