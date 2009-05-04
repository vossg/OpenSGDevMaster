/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                Copyright (C) 2008 by the OpenSG Forum                     *
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

#ifndef _OSGCOLLADAINSTANCEELEMENT_H_
#define _OSGCOLLADAINSTANCEELEMENT_H_
#ifdef __sgi
#pragma once
#endif

/*! \file OSGColladaInstanceElement.h
    \ingroup GrpLoader
 */

#include <OSGConfig.h>

#ifdef OSG_WITH_COLLADA

#include <OSGFileIODef.h>
#include <OSGColladaElement.h>

OSG_BEGIN_NAMESPACE

/*! \brief Base class for <instance_*> elements.
 */

class OSG_FILEIO_DLLMAPPING ColladaInstanceElement : public ColladaElement
{
    /*==========================  PUBLIC  =================================*/
 public:
    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
    /*! \{                                                                 */
    typedef ColladaElement                          Inherited;
    typedef ColladaInstanceElement                  Self;
    
    typedef RefCountPtr<Self, MemObjRefCountPolicy> ObjRefPtr;
    typedef TransitPtr <Self                      > ObjTransitPtr;
    
    /*---------------------------------------------------------------------*/
    /*! \name Read                                                         */
    /*! \{                                                                 */

    virtual void read(void) = 0;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name  Instantiated element access                                 */
    /*! \{                                                                 */
    
    inline void        setInstDOMElement  (daeElement *instElem);
    inline daeElement *getInstDOMElement  (void                ) const;
    template <class DomTypeT>
    inline DomTypeT   *getInstDOMElementAs(void                ) const;
    
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:
             ColladaInstanceElement(daeElement *elem, ColladaGlobal *global);
    virtual ~ColladaInstanceElement(void                                   );

    daeElementRef _instElem;
};

typedef ColladaInstanceElement::ObjRefPtr     ColladaInstanceElementRefPtr;
typedef ColladaInstanceElement::ObjTransitPtr ColladaInstanceElementTransitPtr;

OSG_END_NAMESPACE

#include <OSGColladaInstanceElement.inl>

#endif // OSG_WITH_COLLADA

#endif // _OSGCOLLADAINSTANCEELEMENT_H_
