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

#ifndef _OSGCOLLADAINSTANTIABLEELEMENT_H_
#define _OSGCOLLADAINSTANTIABLEELEMENT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"

#if defined(OSG_WITH_COLLADA) || defined(OSG_DO_DOC)

#include "OSGColladaElement.h"
#include "OSGFieldContainer.h"

#include <vector>

OSG_BEGIN_NAMESPACE

// forward decl
class ColladaInstanceElement;

/*! \ingroup GrpFileIOCollada
    \nohierarchy
 */

class OSG_FILEIO_DLLMAPPING ColladaInstantiableElement : public ColladaElement
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
    /*! \{                                                                 */

    typedef ColladaElement             Inherited;
    typedef ColladaInstantiableElement Self;

    OSG_GEN_INTERNAL_MEMOBJPTR(ColladaInstantiableElement);

    typedef std::vector<FieldContainerUnrecPtr> InstanceStore;
    typedef InstanceStore::iterator             InstanceStoreIt;
    typedef InstanceStore::const_iterator       InstanceStoreConstIt;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Reading                                                      */
    /*! \{                                                                 */

    virtual void
        read          (void                            ) = 0;
    virtual FieldContainer *
        createInstance(ColladaInstanceElement *instElem) = 0;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Access                                                       */
    /*! \{                                                                 */

    inline const InstanceStore &getInstStore (void) const;
    inline InstanceStore       &editInstStore(void);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:
    /*---------------------------------------------------------------------*/
    /*! \name Constructors/Destructor                                      */
    /*! \{                                                                 */
    
             ColladaInstantiableElement(daeElement    *elem,
                                        ColladaGlobal *global);
    virtual ~ColladaInstantiableElement(void                 );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

    InstanceStore _instStore;
};

OSG_GEN_MEMOBJPTR(ColladaInstantiableElement);

OSG_END_NAMESPACE

#include "OSGColladaInstantiableElement.inl"

#endif // OSG_WITH_COLLADA

#endif // _OSGCOLLADAINSTANTIABLEELEMENT_H_
