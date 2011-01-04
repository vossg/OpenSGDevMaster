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

#ifndef _OSGCOLLADAELEMENTFACTORY_H_
#define _OSGCOLLADAELEMENTFACTORY_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"

#if defined(OSG_WITH_COLLADA) || defined(OSG_DO_DOC)

#include "OSGFileIODef.h"
#include "OSGSingletonHolder.h"
#include "OSGColladaElement.h"

#include <map>
#include <string>

#include <boost/function.hpp>

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpFileIOCollada
    \nohierarchy
 */

class OSG_FILEIO_DLLMAPPING ColladaElementFactorySingleton
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
    /*! \{                                                                 */

    typedef boost::function<
        ColladaElementTransitPtr (daeElement *, 
                                  ColladaGlobal *)> CreateFunctor;

    typedef std::map<std::string, CreateFunctor>    HandlerMap;
    typedef HandlerMap::iterator                    HandlerMapIt;
    typedef HandlerMap::const_iterator              HandlerMapConstIt;

    typedef std::map<std::string, HandlerMap   >    ProfileHandlerMap;
    typedef ProfileHandlerMap::iterator             ProfileHandlerMapIt;
    typedef ProfileHandlerMap::const_iterator       ProfileHandlerMapConstIt;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Registration                                                 */
    /*! \{                                                                 */

    bool registerElement  (CreateFunctor      createFunc,
                           const std::string &elemName,
                           const std::string &profile = "");
    bool unregisterElement(const std::string &elemName,
                           const std::string &profile = "");

    const HandlerMap        &getDefaultHandlerMap (void) const;
    HandlerMap              &editDefaultHandlerMap(void);

    const ProfileHandlerMap &getProfileHandlerMap (void) const;
    ProfileHandlerMap       &editProfileHandlerMap(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Default Profile                                              */
    /*! \{                                                                 */

    const std::string &getDefaultProfile(void                      ) const;
    void               setDefaultProfile(const std::string &profile);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Create                                                       */
    /*! \{                                                                 */

    CreateFunctor            getCreateFunc(const std::string &elemName,
                                           const std::string &profile  = "" );

    ColladaElementTransitPtr create       (daeElement        *daeElem,
                                           ColladaGlobal     *global,
                                           const std::string &elemName = "",
                                           const std::string &profile  = "" );

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:
    /*---------------------------------------------------------------------*/
    /*! \name Helper                                                       */
    /*! \{                                                                 */ 

    bool          doRegisterElement  (CreateFunctor      createFunc,
                                      const std::string &elemName,
                                      HandlerMap        &handlerMap );
    bool          doUnregisterElement(const std::string &elemName,
                                      HandlerMap        &handlerMap );

    CreateFunctor doGetCreateFunc    (const std::string &elemName,
                                      HandlerMap        &handlerMap );

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    /*---------------------------------------------------------------------*/
    /*! \name Constructors/Destructor                                      */
    /*! \{                                                                 */
    
     ColladaElementFactorySingleton(void);
    ~ColladaElementFactorySingleton(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

    template <class SingletonT>
    friend class SingletonHolder;

    std::string       _defaultProfile;
    HandlerMap        _defaultHandlerMap;
    ProfileHandlerMap _profileHandlerMap;
};

/*! \ingroup GrpFileIOCollada
 */

typedef SingletonHolder<ColladaElementFactorySingleton> ColladaElementFactory;

OSG_END_NAMESPACE

#endif // OSG_WITH_COLLADA

#endif // _OSGCOLLADAELEMENTFACTORY_H_
