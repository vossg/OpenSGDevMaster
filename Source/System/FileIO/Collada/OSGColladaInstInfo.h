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

#ifndef _OSGCOLLADAINSTINFO_H_
#define _OSGCOLLADAINSTINFO_H_
#ifdef __sgi
#pragma once
#endif

/*! \file OSGColladaInstInfo.h
    \ingroup GrpLoader
 */

#include "OSGConfig.h"

#ifdef OSG_WITH_COLLADA

#include "OSGFileIODef.h"
#include "OSGMemoryObject.h"
#include "OSGColladaElement.h"
#include "OSGColladaInstanceElement.h"
#include "OSGNode.h"

OSG_BEGIN_NAMESPACE

class OSG_FILEIO_DLLMAPPING ColladaInstInfo : public MemoryObject
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
    /*! \{                                                                 */

    typedef MemoryObject     Inherited;
    typedef ColladaInstInfo  Self;

    OSG_GEN_INTERNAL_MEMOBJPTR(ColladaInstInfo);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Access                                                       */
    /*! \{                                                                 */

    inline ColladaElement         *getColInstParent(void) const;
    inline ColladaInstanceElement *getColInst      (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Process                                                      */
    /*! \{                                                                 */

    virtual void process(void) = 0;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:
    /*---------------------------------------------------------------------*/
    /*! \name Constructors/Destructor                                      */
    /*! \{                                                                 */

             ColladaInstInfo(ColladaElement         *colInstParent,
                             ColladaInstanceElement *colInst       );
    virtual ~ColladaInstInfo(void                                  ) = 0;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

    ColladaElementRefPtr         _colInstParent;
    ColladaInstanceElementRefPtr _colInst;
};

OSG_GEN_MEMOBJPTR(ColladaInstInfo);

OSG_END_NAMESPACE

#include "OSGColladaInstInfo.inl"

#endif // OSG_WITH_COLLADA

#endif // _OSGCOLLADAINSTINFO_H_
