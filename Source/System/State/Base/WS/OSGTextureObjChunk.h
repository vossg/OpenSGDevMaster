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

#ifndef _OSGTEXTUREOBJCHUNK_H_
#define _OSGTEXTUREOBJCHUNK_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGImage.h"
#include "OSGTextureObjChunkBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief State chunk for textures. See \ref PageSystemTextureObjChunk 
    for a description.
 */

class OSG_SYSTEM_DLLMAPPING TextureObjChunk : public TextureObjChunkBase
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
                         UInt32            origin    );

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

    GLenum determineTextureTarget(Window *pWindow) const;

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

    void imageContentChanged  (Int32 minx = -1, Int32 maxx = -1, 
                               Int32 miny = -1, Int32 maxy = -1,
                               Int32 minz = -1, Int32 maxz = -1);

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

    void onCreate      (const TextureObjChunk *source      = NULL);
    void onCreateAspect(const TextureObjChunk *createAspect,
                        const TextureObjChunk *source      = NULL);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    TextureObjChunk(void);
    TextureObjChunk(const TextureObjChunk &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~TextureObjChunk(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                         GL                                   */
    /*! \{                                                                 */

    void handleTexture(Window                  *win, 
                       UInt32                   id, 
                       GLenum                   bindtarget,
                       GLenum                   paramtarget,
                       GLenum                   imgtarget, 
                       Window::GLObjectStatusE  mode, 
                       ImagePtr                 img,
                       Int32                    side = 0);

    /*! \}                                                                 */ 
    /*---------------------------------------------------------------------*/

    // extension indices for used extensions;
    static UInt32 _extTex3D;
    static UInt32 _sgisGenerateMipmap;
    static UInt32 _arbTextureCompression;
    static UInt32 _arbTextureRectangle;
    static UInt32 _arbTextureNonPowerOfTwo;
    static UInt32 _extTextureFilterAnisotropic;
    static UInt32 _extShadow;
    static UInt32 _extDepthTexture;

    // extension indices for used fucntions;
    static UInt32 _funcTexImage3D;
    static UInt32 _funcTexSubImage3D;
    static UInt32 _arbCubeTex;
    static UInt32 _funcCompressedTexImage1D;
    static UInt32 _funcCompressedTexSubImage1D;
    static UInt32 _funcCompressedTexImage2D;
    static UInt32 _funcCompressedTexSubImage2D;
    static UInt32 _funcCompressedTexImage3D;
    static UInt32 _funcCompressedTexSubImage3D;

    // class. Used for indexing in State
    // protected to give CubeTextureChunk access

    /*==========================  PRIVATE  ================================*/

  private:

    typedef TextureObjChunkBase Inherited;

    friend class TextureObjChunkBase;

    template<class ContainerFactoryT>
    friend struct CPtrConstructionFunctions;

    template<class ContainerFactoryT>
    friend struct PtrConstructionFunctions;

    /*---------------------------------------------------------------------*/
    /*! \name                         GL                                   */
    /*! \{                                                                 */

    void handleGL(DrawEnv *pEnv, UInt32 id);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const TextureObjChunk &source);
};

typedef TextureObjChunk *TextureObjChunkP;

OSG_END_NAMESPACE

#include "OSGTextureObjChunkBase.inl"
#include "OSGTextureObjChunk.inl"

#define OSGTEXTUREOBJCHUNK_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGTEXTUREOBJCHUNK_H_ */
