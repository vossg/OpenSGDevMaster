/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
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

/*****************************************************************************\
 *****************************************************************************
 **                                                                         **
 **                  This file is automatically generated.                  **
 **                                                                         **
 **          Any changes made to this file WILL be lost when it is          **
 **           regenerated, which can become necessary at any time.          **
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#ifndef _OSGTEXTUREOBJREFCHUNKFIELDS_H_
#define _OSGTEXTUREOBJREFCHUNKFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGStateDef.h"

#include "OSGTextureBaseChunkFields.h"

#include "OSGSFieldAdaptor.h"
#include "OSGMFieldAdaptor.h"


OSG_BEGIN_NAMESPACE

class TextureObjRefChunk;

#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles
//! TextureObjRefChunkPtr

typedef PointerFwdBuilder<TextureBaseChunkPtr, 
                          TextureBaseChunkConstPtr,
                          TextureObjRefChunk>::ObjPtr         TextureObjRefChunkPtr;
typedef PointerFwdBuilder<TextureBaseChunkPtr, 
                          TextureBaseChunkConstPtr,
                          TextureObjRefChunk>::ObjPtrConst    TextureObjRefChunkPtrConst;
typedef PointerFwdBuilder<TextureBaseChunkPtr, 
                          TextureBaseChunkConstPtr,
                          TextureObjRefChunk>::ObjConstPtr    TextureObjRefChunkConstPtr;
typedef PointerFwdBuilder<TextureBaseChunkPtr, 
                          TextureBaseChunkConstPtr,
                          TextureObjRefChunk>::ObjPtrArg      TextureObjRefChunkPtrArg;
typedef PointerFwdBuilder<TextureBaseChunkPtr, 
                          TextureBaseChunkConstPtr,
                          TextureObjRefChunk>::ObjConstPtrArg TextureObjRefChunkConstPtrArg;
typedef PointerFwdBuilder<TextureBaseChunkPtr, 
                          TextureBaseChunkConstPtr,
                          TextureObjRefChunk>::ObjPtrConstArg TextureObjRefChunkPtrConstArg;

#endif

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)
/*! \ingroup GrpStateFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<TextureObjRefChunkPtr> : 
    public FieldTraitsTemplateBase<TextureObjRefChunkPtr>
{
  private:

    static DataType             _type;                       

  public:

    typedef FieldTraits<TextureObjRefChunkPtr>  Self;

    enum                        { StringConvertable = 0x00 };

    static OSG_STATE_DLLMAPPING 
                     DataType &getType (void);

    static const char *getSName(void) { return "SFTextureObjRefChunkPtr"; }
    static const char *getMName(void) { return "MFTextureObjRefChunkPtr"; }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsTemplateBase<TextureObjRefChunkPtr, 0>
    \hideinhierarchy
 */
#endif

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS)
/*! \ingroup GrpStateFieldSingle */

typedef SFieldAdaptor<TextureObjRefChunkPtr, SFFieldContainerPtr> SFTextureObjRefChunkPtr;
#endif

#ifndef OSG_COMPILETEXTUREOBJREFCHUNKINST
OSG_FIELD_DLLEXPORT_DECL1(SField, TextureObjRefChunkPtr, OSG_STATE_DLLTMPLMAPPING)
#endif

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS)
/*! \ingroup GrpStateFieldMulti */

typedef MFieldAdaptor<TextureObjRefChunkPtr, MFFieldContainerPtr> MFTextureObjRefChunkPtr;
#endif

#ifndef OSG_COMPILETEXTUREOBJREFCHUNKINST
OSG_FIELD_DLLEXPORT_DECL1(MField, TextureObjRefChunkPtr, OSG_STATE_DLLTMPLMAPPING)
#endif

OSG_END_NAMESPACE

#define OSGTEXTUREOBJREFCHUNKFIELDS_HEADER_CVSID "@(#)$Id$"

#endif /* _OSGTEXTUREOBJREFCHUNKFIELDS_H_ */
