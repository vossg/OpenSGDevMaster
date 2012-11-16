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

#ifndef _OSGCOLLADADOMPROFILEHANDLER_H_
#define _OSGCOLLADADOMPROFILEHANDLER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"

#if defined(OSG_WITH_COLLADA) || defined(OSG_DO_DOC)

#include "OSGFileIODef.h"
#include "OSGMemoryObject.h"
#include "OSGRefCountPtr.h"
#include "OSGTransitPtr.h"
#include "OSGMaterial.h"

#include <dom/domEffect.h>
#include <dom/domInstance_effect.h>
#include <dom/domFx_profile_abstract.h>

#ifdef OSG_WITH_COLLADA_NAMESPACE
using namespace ColladaDOM141;
#endif

OSG_BEGIN_NAMESPACE

// forward declarations


class OSG_FILEIO_DLLMAPPING ColladaDomProfileHandler : public MemoryObject
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
    /*! \{                                                                 */

    typedef MemoryObject             Inherited;
    typedef ColladaDomProfileHandler Self;

    OSG_GEN_INTERNAL_MEMOBJPTR(ColladaDomProfileHandler);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Reading                                                      */
    /*! \{                                                                 */

    virtual void readProfile(domFx_profile_abstract *pProf) = 0;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Access                                                       */
    /*! \{                                                                 */

    virtual MaterialTransitPtr 
        createInstProfile(domFx_profile_abstract *pProf,
                          domEffect              *pEffect,
                          domInstance_effect     *pInstEffect) = 0;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name Constructors/Destructor                                      */
    /*! \{                                                                 */
    
             ColladaDomProfileHandler(void);
    virtual ~ColladaDomProfileHandler(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
};


OSG_GEN_MEMOBJPTR(ColladaDomProfileHandler);

OSG_END_NAMESPACE

#include "OSGColladaDomProfileHandler.inl"

#endif // OSG_WITH_COLLADA

#endif // _OSGCOLLADADOMPROFILEHANDLER_H_
