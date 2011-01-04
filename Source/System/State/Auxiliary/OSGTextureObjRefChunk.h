/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zghdv.de          *
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

#ifndef _OSGTEXTUREOBJREFCHUNK_H_
#define _OSGTEXTUREOBJREFCHUNK_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGGLEXT.h"
#include "OSGWindow.h"
#include "OSGImage.h"
#include "OSGTextureObjRefChunkBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief State chunk for textures. See \ref PageSystemTextureObjRefChunk 
           for a description.
    \ingroup GrpStateAuxiliaryObj
    \ingroup GrpLibOSGState
    \includebasedoc
 */

class OSG_STATE_DLLMAPPING TextureObjRefChunk : public TextureObjRefChunkBase
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                 Chunk Class Access                           */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name              Static Chunk Class Access                       */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Chunk Id                                  */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin,
                         BitVector         details);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Output                                  */
    /*! \{                                                                 */

    virtual void dump(      UInt32    uiIndent = 0,
                      const BitVector bvFlags  = 0) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       State                                  */
    /*! \{                                                                 */

    virtual void activate   (DrawEnv    *pEnv, 
                             UInt32      index = 0);

    virtual void changeFrom (DrawEnv    *pEnv, 
                             StateChunk *pOld,
                             UInt32      index = 0);

    virtual void deactivate (DrawEnv    *pEnv, 
                             UInt32      index = 0);

    virtual bool isTransparent (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       query                                  */
    /*! \{                                                                 */

    //GLenum determineTextureTarget(Window *pWindow) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Comparison                                 */
    /*! \{                                                                 */

    virtual Real32 switchCost(StateChunk * chunk);

    virtual bool   operator <  (const StateChunk &other) const;

    virtual bool   operator == (const StateChunk &other) const;
    virtual bool   operator != (const StateChunk &other) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                Texture specific                              */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name             Multitexture handling                            */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    void onCreate      (const TextureObjRefChunk *source      = NULL);
    void onCreateAspect(const TextureObjRefChunk *createAspect,
                        const TextureObjRefChunk *source      = NULL);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    TextureObjRefChunk(void);
    TextureObjRefChunk(const TextureObjRefChunk &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~TextureObjRefChunk(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                         GL                                   */
    /*! \{                                                                 */

    /*! \}                                                                 */ 
    /*---------------------------------------------------------------------*/

    /*==========================  PRIVATE  ================================*/

  private:

    typedef TextureObjRefChunkBase Inherited;

    friend class FieldContainer;
    friend class TextureObjRefChunkBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const TextureObjRefChunk &source);
};

typedef TextureObjRefChunk *TextureObjRefChunkP;

OSG_END_NAMESPACE

#include "OSGTextureObjRefChunkBase.inl"
#include "OSGTextureObjRefChunk.inl"

#endif /* _OSGTEXTUREOBJREFCHUNK_H_ */
