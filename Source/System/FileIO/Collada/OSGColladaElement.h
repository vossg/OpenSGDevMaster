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

#ifndef _OSGCOLLADAELEMENT_H_
#define _OSGCOLLADAELEMENT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"

#if defined(OSG_WITH_COLLADA) || defined(OSG_DO_DOC)

#include "OSGFileIODef.h"
#include "OSGMemoryObject.h"
#include "OSGContainerForwards.h"
#include "OSGRefCountPtr.h"
#include "OSGTransitPtr.h"

// collada dom includes
#include <dae.h>
#include <dae/daeElement.h>

OSG_BEGIN_NAMESPACE

// forward declarations
class ColladaGlobal;
OSG_GEN_MEMOBJPTR(ColladaGlobal);

/*! \ingroup GrpFileIOCollada
    \nohierarchy
 */

class OSG_FILEIO_DLLMAPPING ColladaElement : public MemoryObject
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
    /*! \{                                                                 */

    typedef MemoryObject   Inherited;
    typedef ColladaElement Self;

    OSG_GEN_INTERNAL_MEMOBJPTR(ColladaElement);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Reading                                                      */
    /*! \{                                                                 */

    virtual void read(void) = 0;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Access                                                       */
    /*! \{                                                                 */

    inline ColladaGlobal *getGlobal      (void) const;

    inline daeElement    *getDOMElement  (void) const;
    template <class DomTypeT>
    inline DomTypeT      *getDOMElementAs(void) const;

    template <class UserDataTypeT>
    inline        UserDataTypeT *getUserDataAs(void            ) const;

    template <class UserDataTypeT>
    static inline UserDataTypeT *getUserDataAs(daeElement *elem);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:
    /*---------------------------------------------------------------------*/
    /*! \name Constructors/Destructor                                      */
    /*! \{                                                                 */
    
             ColladaElement(daeElement *elem, ColladaGlobal *global);
    virtual ~ColladaElement(void                                   );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

    daeElementRef       _elem;
    ColladaGlobalRefPtr _global;
};


OSG_GEN_MEMOBJPTR(ColladaElement);

OSG_END_NAMESPACE

#include "OSGColladaElement.inl"
#include "OSGColladaGlobal.h"

#endif // OSG_WITH_COLLADA

#endif // _OSGCOLLADAELEMENT_H_
