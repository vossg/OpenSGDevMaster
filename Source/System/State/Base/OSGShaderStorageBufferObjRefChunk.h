/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2013 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 * contact: dirk@opensg.org, gerrit.voss@vossg.org, carsten_neumann@gmx.net  *
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

#ifndef _OSGSHADERSTORAGEBUFFEROBJREFCHUNK_H_
#define _OSGSHADERSTORAGEBUFFEROBJREFCHUNK_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGShaderStorageBufferObjRefChunkBase.h"
#include "OSGWindow.h"

OSG_BEGIN_NAMESPACE

/*! \brief ShaderStorageBufferObjRefChunk class. See \ref
           PageSystemShaderStorageBufferObjRefChunk for a description.
*/

class OSG_SYSTEM_DLLMAPPING ShaderStorageBufferObjRefChunk : public ShaderStorageBufferObjRefChunkBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef ShaderStorageBufferObjRefChunkBase Inherited;
    typedef ShaderStorageBufferObjRefChunk     Self;

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin,
                         BitVector         details    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

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

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name             OpenGL handling                                  */
    /*! \{                                                                 */

    virtual void   validate               (DrawEnv *pEnv);
    virtual Int32  getOpenGLId            (DrawEnv *pEnv);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:
    // Variables should all be in ShaderStorageBufferObjRefChunkBase.

    void onCreate      (const ShaderStorageBufferObjRefChunk *source      = NULL);
    void onCreateAspect(const ShaderStorageBufferObjRefChunk *createAspect,
                        const ShaderStorageBufferObjRefChunk *source      = NULL);
    void onDestroy     (      UInt32                          uiContainerId     );

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ShaderStorageBufferObjRefChunk(void);
    ShaderStorageBufferObjRefChunk(const ShaderStorageBufferObjRefChunk &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ShaderStorageBufferObjRefChunk(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */

    // extension indices for used extensions;
    static UInt32 _extVertexBufferObject;
    static UInt32 _funcBindBuffer;

    static UInt32 _extUniformBufferObject;    
    static UInt32 _funcBindBufferBase;

    static UInt32 _extShaderStorageBufferObject;

    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class ShaderStorageBufferObjRefChunkBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ShaderStorageBufferObjRefChunk &source);
};

typedef ShaderStorageBufferObjRefChunk *ShaderStorageBufferObjRefChunkP;

OSG_END_NAMESPACE

#include "OSGShaderStorageBufferObjRefChunkBase.inl"
#include "OSGShaderStorageBufferObjRefChunk.inl"

#endif /* _OSGSHADERSTORAGEBUFFEROBJREFCHUNK_H_ */
