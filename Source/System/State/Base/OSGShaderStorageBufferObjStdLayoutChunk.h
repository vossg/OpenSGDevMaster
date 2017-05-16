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

#ifndef _OSGSHADERSTORAGEBUFFEROBJSTDLAYOUTCHUNK_H_
#define _OSGSHADERSTORAGEBUFFEROBJSTDLAYOUTCHUNK_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGShaderStorageBufferObjStdLayoutChunkBase.h"
#include "OSGWindow.h"

OSG_BEGIN_NAMESPACE

/*! \brief ShaderStorageBufferObjStdLayoutChunk class. See \ref
           PageSystemShaderStorageBufferObjStdLayoutChunk for a description.
*/

class OSG_SYSTEM_DLLMAPPING ShaderStorageBufferObjStdLayoutChunk : public ShaderStorageBufferObjStdLayoutChunkBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef ShaderStorageBufferObjStdLayoutChunkBase Inherited;
    typedef ShaderStorageBufferObjStdLayoutChunk     Self;

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
    // Variables should all be in ShaderStorageBufferObjStdLayoutChunkBase.

    void onCreate      (const ShaderStorageBufferObjStdLayoutChunk *source      = NULL);
    void onCreateAspect(const ShaderStorageBufferObjStdLayoutChunk *createAspect,
                        const ShaderStorageBufferObjStdLayoutChunk *source      = NULL);
    void onDestroy     (      UInt32                                uiContainerId     );

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ShaderStorageBufferObjStdLayoutChunk(void);
    ShaderStorageBufferObjStdLayoutChunk(const ShaderStorageBufferObjStdLayoutChunk &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ShaderStorageBufferObjStdLayoutChunk(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */

    // extension indices for used extensions;
    static UInt32 _extVertexBufferObject;
    static UInt32 _funcBindBuffer;
    static UInt32 _funcMapBuffer;
    static UInt32 _funcUnmapBuffer;
    static UInt32 _funcBufferData;
    static UInt32 _funcBufferSubData;
    static UInt32 _funcGenBuffers;
    static UInt32 _funcDeleteBuffers;
    static UInt32 _funcGetBufferParameteriv;


    static UInt32 _extUniformBufferObject;    
    static UInt32 _funcBindBufferBase;

    static UInt32 _extProgramInterfaceQuery;
    static UInt32 _extShaderStorageBufferObject;

    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class ShaderStorageBufferObjStdLayoutChunkBase;

    /*---------------------------------------------------------------------*/
    /*! \name                         GL                                   */
    /*! \{                                                                 */

           UInt32 handleGL       (DrawEnv                 *pEnv, 
                                  UInt32                   id, 
                                  Window::GLObjectStatusE  mode,
                                  UInt64                   uiOptions);

    static void   handleDestroyGL(DrawEnv                 *pEnv, 
                                  UInt32                   id, 
                                  Window::GLObjectStatusE  mode     );

    /*! \}                                                                 */

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ShaderStorageBufferObjStdLayoutChunk &source);
};

typedef ShaderStorageBufferObjStdLayoutChunk *ShaderStorageBufferObjStdLayoutChunkP;

OSG_END_NAMESPACE

#include "OSGShaderStorageBufferObjStdLayoutChunkBase.inl"
#include "OSGShaderStorageBufferObjStdLayoutChunk.inl"

#endif /* _OSGSHADERSTORAGEBUFFEROBJSTDLAYOUTCHUNK_H_ */
