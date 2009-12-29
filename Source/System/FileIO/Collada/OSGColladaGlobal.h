/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                Copyright (C) 2009 by the OpenSG Forum                     *
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

#ifndef _OSGCOLLADAGLOBAL_H_
#define _OSGCOLLADAGLOBAL_H_
#ifdef __sgi
#pragma once
#endif

/*! \file OSGColladaGlobal.h
    \ingroup GrpLoader
 */
#include "OSGConfig.h"

#ifdef OSG_WITH_COLLADA

#include "OSGFileIODef.h"
#include "OSGMemoryObject.h"
#include "OSGPathHandler.h"
#include "OSGNode.h"
#include "OSGColladaElement.h"
#include "OSGColladaOptions.h"

// collada dom includes
#include <dae.h>
#include <dom/domCOLLADA.h>

#include <string>
#include <vector>

OSG_BEGIN_NAMESPACE

class OSG_FILEIO_DLLMAPPING ColladaGlobal : public MemoryObject
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
    /*! \{                                                                 */

    typedef MemoryObject   Inherited;
    typedef ColladaGlobal  Self;

    OSG_GEN_INTERNAL_MEMOBJPTR(ColladaGlobal);

    typedef std::vector<ColladaElementRefPtr> ElementStore;
    typedef ElementStore::iterator            ElementStoreIt;
    typedef ElementStore::const_iterator      ElementStoreConstIt;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Create                                                       */
    /*! \{                                                                 */

    static ObjTransitPtr create(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Read                                                         */
    /*! \{                                                                 */

    NodeTransitPtr read(      std::istream &is,
                        const std::string  &fileName);

    NodeTransitPtr read(      DAE          *dae,
                        const std::string  &fileName);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Access                                                       */
    /*! \{                                                                 */

    inline const DAE          *getDAE       (void                      ) const;
    inline DAE                *editDAE      (void                      );

    inline const std::string  &getDocPath   (void                      ) const;
    inline void                setDocPath   (const std::string &docPath);

    inline ColladaOptions     *getOptions   (void                      ) const;
    inline void                setOptions   (ColladaOptions    *options);

    inline Node               *getRoot      (void                      ) const;
    inline void                setRoot      (Node              *rootN  );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name ElementStore                                                 */
    /*! \{                                                                 */

    inline const ElementStore &getElemStore  (void                      ) const;
    inline ElementStore       &editElemStore (void                      );

           void                addElement    (ColladaElement    *elem   );

           ColladaElement     *getElement    (const daeURI      &elemURI) const;
           ColladaElement     *getElement    (const std::string &elemId ) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:
    /*---------------------------------------------------------------------*/
    /*! \name Constructors/Destructor                                      */
    /*! \{                                                                 */

             ColladaGlobal(void);
    virtual ~ColladaGlobal(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Read                                                         */
    /*! \{                                                                 */

    NodeTransitPtr doRead(DAE *dae);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

    ElementStore          _elemStore;

    ColladaOptionsRefPtr  _options;

    PathHandler           _pathHandler;
    std::string           _docPath;

    DAE                  *_dae;
    domCOLLADARef         _docRoot;

    NodeUnrecPtr          _rootN;
};


OSG_GEN_MEMOBJPTR(ColladaGlobal);

OSG_END_NAMESPACE

#include "OSGColladaGlobal.inl"

#endif // OSG_WITH_COLLADA

#endif // _OSGCOLLADAGLOBAL_H_
