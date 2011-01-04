/*---------------------------------------------------------------------------*\
 *                           OpenSG NURBS Library                            *
 *                                                                           *
 *                                                                           *
 * Copyright (C) 2001-2006 by the University of Bonn, Computer Graphics Group*
 *                                                                           *
 *                         http://cg.cs.uni-bonn.de/                         *
 *                                                                           *
 * contact: edhellon@cs.uni-bonn.de, guthe@cs.uni-bonn.de, rk@cs.uni-bonn.de *
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

#ifndef _OSGFATBORDERCHUNK_H_
#define _OSGFATBORDERCHUNK_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGDrawableDef.h"
#include "OSGFatBorderChunkBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief FatBorderChunk class. See \ref 
           PageMyExtensionFatBorderChunk for a description.
    \ingroup GrpDrawablesNurbsObj
    \ingroup GrpLibOSGDrawables
    \includebasedoc
 */

class OSG_DRAWABLE_DLLMAPPING FatBorderChunk : public FatBorderChunkBase
{
  private:

    typedef FatBorderChunkBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin,
                         BitVector         detail);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                Helper Functions                              */
    /*! \{                                                                 */

	void activateWithStandardLighting( );
	void activateWithFragmentBasedLighting( );

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in FatBorderChunkBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    FatBorderChunk(void);
    FatBorderChunk(const FatBorderChunk &source);

    void onCreate(const FatBorderChunk *source = NULL);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~FatBorderChunk(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class FatBorderChunkBase;

    static void initMethod(InitPhase ePhase);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const FatBorderChunk &source);
};

typedef FatBorderChunk *FatBorderChunkP;

OSG_END_NAMESPACE

#include "OSGFatBorderChunkBase.inl"
#include "OSGFatBorderChunk.inl"

#define OSGFATBORDERCHUNK_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGFATBORDERCHUNK_H_ */
