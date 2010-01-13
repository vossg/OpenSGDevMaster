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

#if defined(OSG_WITH_COLLADA) || defined(OSG_DO_DOC)

#include "OSGFileIODef.h"
#include "OSGMemoryObject.h"
#include "OSGPathHandler.h"
#include "OSGNode.h"
#include "OSGColladaElement.h"
#include "OSGColladaLoaderState.h"
#include "OSGColladaOptions.h"
#include "OSGStatElemTypes.h"
#include "OSGStatCollector.h"
#include "OSGGlobalsAttachment.h"

// collada dom includes
#include <dae.h>
#include <dom/domCOLLADA.h>

#include <deque>
#include <map>
#include <string>
#include <vector>

OSG_BEGIN_NAMESPACE

// forward decl
class ColladaInstInfo;
OSG_GEN_MEMOBJPTR(ColladaInstInfo);



// forward decl
class ColladaInstInfo;
OSG_GEN_MEMOBJPTR(ColladaInstInfo);

/*! \ingroup GrpFileIOCollada
    \nohierarchy
 */

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

    typedef std::deque<ColladaInstInfoRefPtr>  InstanceQueue;
    typedef InstanceQueue::iterator            InstanceQueueIt;
    typedef InstanceQueue::const_iterator      InstanceQueueConstIt;

    typedef std::map<std::string,
                     ColladaLoaderStateRefPtr> LoaderStateMap;
    typedef LoaderStateMap::iterator           LoaderStateMapIt;
    typedef LoaderStateMap::const_iterator     LoaderStateMapConstIt;

    typedef std::vector<ColladaElementRefPtr>  ElementStore;
    typedef ElementStore::iterator             ElementStoreIt;
    typedef ElementStore::const_iterator       ElementStoreConstIt;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Statistics                                                   */
    /*! \{                                                                 */

    static StatElemDesc<StatIntElem> statNGeometryCreated;
    static StatElemDesc<StatIntElem> statNGeometryUsed;
    static StatElemDesc<StatIntElem> statNMaterialCreated;
    static StatElemDesc<StatIntElem> statNMaterialUsed;
    static StatElemDesc<StatIntElem> statNTextureCreated;
    static StatElemDesc<StatIntElem> statNTextureUsed;

    StatCollector *getStatCollector(void                   );
    void           setStatCollector(StatCollector *statColl);

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
    inline domCOLLADA         *getDocRoot   (void                      ) const;

    inline const std::string  &getDocPath   (void                      ) const;
    inline void                setDocPath   (const std::string &docPath);

    inline ColladaOptions     *getOptions   (void                      ) const;
    inline void                setOptions   (ColladaOptions    *options);

    inline Node               *getRoot      (void                      ) const;
    inline void                setRoot      (Node              *rootN  );

    inline GlobalsAttachment  *getGlobalsAtt(void                      ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name LoaderState                                                  */
    /*! \{                                                                 */

    inline void addLoaderState(const std::string  &name,
                               ColladaLoaderState *state);
    inline void subLoaderState(const std::string &name  );

    inline ColladaLoaderState *getLoaderState  (const std::string &name) const;
    template <class StateTypeT>
    inline StateTypeT         *getLoaderStateAs(const std::string &name) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name ElementStore                                                 */
    /*! \{                                                                 */

    inline const InstanceQueue &getInstQueue (void                      ) const;
    inline InstanceQueue       &editInstQueue(void                      );

    inline const ElementStore  &getElemStore (void                      ) const;
    inline ElementStore        &editElemStore(void                      );

           void                 addElement   (ColladaElement    *elem   );

           ColladaElement      *getElement   (const daeURI      &elemURI) const;
           ColladaElement      *getElement   (const std::string &elemId ) const;

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

    NodeTransitPtr doRead(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

    InstanceQueue              _instQueue;
    LoaderStateMap             _loaderState;
    ElementStore               _elemStore;

    ColladaOptionsRefPtr       _options;
    StatCollectorRefPtr        _statColl;

    PathHandler                _pathHandler;
    std::string                _docPath;

    domCOLLADARef              _docRoot;
    DAE                       *_dae;

    NodeUnrecPtr               _rootN;
    GlobalsAttachmentUnrecPtr  _globalsAtt;
};


OSG_GEN_MEMOBJPTR(ColladaGlobal);

OSG_END_NAMESPACE

#include "OSGColladaGlobal.inl"

#endif // OSG_WITH_COLLADA

#endif // _OSGCOLLADAGLOBAL_H_
