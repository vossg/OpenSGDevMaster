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

#ifndef _OSGCOLLADAINSTANCEELEMENT_H_
#define _OSGCOLLADAINSTANCEELEMENT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"

#if defined(OSG_WITH_COLLADA) || defined(OSG_DO_DOC)

#include "OSGColladaElement.h"

OSG_BEGIN_NAMESPACE

// forward decl
class ColladaInstantiableElement;

/*! \ingroup GrpFileIOCollada
    \nohierarchy
 */

class OSG_FILEIO_DLLMAPPING ColladaInstanceElement : public ColladaElement
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
    /*! \{                                                                 */

    typedef ColladaElement         Inherited;
    typedef ColladaInstanceElement Self;

    OSG_GEN_INTERNAL_MEMOBJPTR(ColladaInstanceElement);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Reading                                                      */
    /*! \{                                                                 */

    virtual void            read   (void                  ) = 0;
    virtual FieldContainer *process(ColladaElement *parent) = 0;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Access                                                       */
    /*! \{                                                                 */

    virtual ColladaInstantiableElement *getTargetElem   (void) const = 0;
    virtual daeElement                 *getTargetDOMElem(void) const = 0;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:
    /*---------------------------------------------------------------------*/
    /*! \name Constructors/Destructor                                      */
    /*! \{                                                                 */
    
             ColladaInstanceElement(daeElement *elem, ColladaGlobal *global);
    virtual ~ColladaInstanceElement(void                                   );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
};

OSG_GEN_MEMOBJPTR(ColladaInstanceElement);

OSG_END_NAMESPACE

// #include "OSGColladaInstanceElement.inl"

#endif // OSG_WITH_COLLADA

#endif // _OSGCOLLADAINSTANCEELEMENT_H_
