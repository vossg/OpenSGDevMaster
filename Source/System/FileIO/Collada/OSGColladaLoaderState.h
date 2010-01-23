/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                Copyright (C) 2010 by the OpenSG Forum                     *
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

#ifndef _OSGCOLLADALOADERSTATE_H_
#define _OSGCOLLADALOADERSTATE_H_

#include "OSGConfig.h"

#ifdef OSG_WITH_COLLADA

#include "OSGFileIODef.h"
#include "OSGMemoryObject.h"
#include "OSGRefCountPtr.h"
#include "OSGTransitPtr.h"

OSG_BEGIN_NAMESPACE

// forward decl
class ColladaLoaderState;
OSG_GEN_MEMOBJPTR(ColladaLoaderState);


class ColladaLoaderState : public MemoryObject
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
    /*! \{                                                                 */

    typedef MemoryObject        Inherited;
    typedef ColladaLoaderState  Self;

    OSG_GEN_INTERNAL_MEMOBJPTR(ColladaLoaderState);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:
    /*---------------------------------------------------------------------*/
    /*! \name Constructors/Destructor                                      */
    /*! \{                                                                 */
    
             ColladaLoaderState(void);
    virtual ~ColladaLoaderState(void) = 0;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
};

OSG_END_NAMESPACE

// #include  "OSGColladaLoaderState.inl"

#endif // OSG_WITH_COLLADA

#endif // _OSGCOLLADALOADERSTATE_H_
