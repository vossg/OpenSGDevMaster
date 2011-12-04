/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                   Copyright (C) 2009 by the OpenSG Forum                  *
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

#ifndef _OSGCOLLADAHANDLERFACTORY_H_
#define _OSGCOLLADAHANDLERFACTORY_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"

#if defined(OSG_WITH_COLLADA) || defined(OSG_DO_DOC)

#include "OSGFileIODef.h"
#include "OSGSingletonHolder.h"

#include <map>
#include <string>

#include <boost/function.hpp>

OSG_BEGIN_NAMESPACE

class ColladaExtraHandler;
OSG_GEN_MEMOBJPTR(ColladaExtraHandler);

class ColladaDomProfileHandler;
OSG_GEN_MEMOBJPTR(ColladaDomProfileHandler);

/*! \ingroup GrpFileIOCollada
    \nohierarchy
 */

class OSG_FILEIO_DLLMAPPING ColladaHandlerFactoryBase
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
    /*! \{                                                                 */

    typedef boost::function<
        ColladaExtraHandlerTransitPtr     (void)>  ExtraHandlerCreator;

    typedef boost::function<
        ColladaDomProfileHandlerTransitPtr(void)>  DomProfileHandlerCreator;


    typedef std::map<UInt32, 
                     DomProfileHandlerCreator>     DomProfileHandlerMap;
    typedef DomProfileHandlerMap::iterator         DomProfileHandlerMapIt;
    typedef DomProfileHandlerMap::const_iterator   DomProfileHandlerMapConstIt;

    typedef std::vector<ExtraHandlerCreator      > ExtraHandlerCreatorStore;

    typedef std::vector<ColladaExtraHandlerRefPtr> ExtraHandlerStore;

    typedef ColladaDomProfileHandlerTransitPtr     ColladaDomProfileHandlerTPtr;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Registration                                                 */
    /*! \{                                                                 */

    void registerExtraHandler(ExtraHandlerCreator  fCreator);
    void createExtraHandlers (ExtraHandlerStore   &vStore  );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Default Profile                                              */
    /*! \{                                                                 */

    void registerDomProfileHandler(UInt32                   uiProfileId,
                                   DomProfileHandlerCreator fCreator   );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Default Profile                                              */
    /*! \{                                                                 */

    ColladaDomProfileHandlerTPtr createDomProfileHandler(UInt32 uiProfileId);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Create                                                       */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    DomProfileHandlerMap      _mDomProfileCreators;
    ExtraHandlerCreatorStore  _vExtraHandlerCreators;

   /*---------------------------------------------------------------------*/
    /*! \name Helper                                                       */
    /*! \{                                                                 */ 

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    /*---------------------------------------------------------------------*/
    /*! \name Constructors/Destructor                                      */
    /*! \{                                                                 */
    
     ColladaHandlerFactoryBase(void);
    ~ColladaHandlerFactoryBase(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

    template <class SingletonT>
    friend class SingletonHolder;
};

#if defined(WIN32)
OSG_FILEIO_EXPIMP_TMPL
template class OSG_FILEIO_DLLMAPPING SingletonHolder<ColladaHandlerFactoryBase>;
#endif

/*! \ingroup GrpFileIOCollada
 */

typedef SingletonHolder<ColladaHandlerFactoryBase> ColladaHandlerFactory;

OSG_END_NAMESPACE

#endif // OSG_WITH_COLLADA

#endif // _OSGCOLLADAHANDLERFACTORY_H_
