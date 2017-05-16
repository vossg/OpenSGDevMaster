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

#ifndef _OSGUNIFORMBUFFEROBJCHUNK_H_
#define _OSGUNIFORMBUFFEROBJCHUNK_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGUniformBufferObjChunkBase.h"
#include "OSGWindow.h"

OSG_BEGIN_NAMESPACE

/*! \brief UniformBufferObjChunk class. See \ref
           PageSystemUniformBufferObjChunk for a description.
*/

class OSG_SYSTEM_DLLMAPPING UniformBufferObjChunk : public UniformBufferObjChunkBase
{
  protected:
    enum FundamentalTypes   {
        FLOAT_T, DOUBLE_T, INT_T, UINT_T, BOOL_T
    };

    enum MainType           {
        SIMPLE_T, VEC2_T, VEC3_T, VEC4_T, MAT2_T, MAT3_T, MAT4_T, 
        MAT2X3_T, MAT2X4_T, MAT3X4_T, MAT3X2_T, MAT4X2_T, MAT4X3_T
    };

    /*==========================  PUBLIC  =================================*/

  public:

    typedef UniformBufferObjChunkBase Inherited;
    typedef UniformBufferObjChunk     Self;

    /*---------------------------------------------------------------------*/
    /*! \name                      Interface                               */
    /*! \{                                                                 */
    UInt32  addFloat    (const std::string& name, UInt32 cardinality = 1);
    UInt32  addDouble   (const std::string& name, UInt32 cardinality = 1);
    UInt32  addInt      (const std::string& name, UInt32 cardinality = 1);
    UInt32  addUInt     (const std::string& name, UInt32 cardinality = 1);
    UInt32  addBool     (const std::string& name, UInt32 cardinality = 1);
    UInt32  addVec2     (const std::string& name, UInt32 cardinality = 1);
    UInt32  addVec3     (const std::string& name, UInt32 cardinality = 1);
    UInt32  addVec4     (const std::string& name, UInt32 cardinality = 1);
    UInt32  addDVec2    (const std::string& name, UInt32 cardinality = 1);
    UInt32  addDVec3    (const std::string& name, UInt32 cardinality = 1);
    UInt32  addDVec4    (const std::string& name, UInt32 cardinality = 1);
    UInt32  addIVec2    (const std::string& name, UInt32 cardinality = 1);
    UInt32  addIVec3    (const std::string& name, UInt32 cardinality = 1);
    UInt32  addIVec4    (const std::string& name, UInt32 cardinality = 1);
    UInt32  addUVec2    (const std::string& name, UInt32 cardinality = 1);
    UInt32  addUVec3    (const std::string& name, UInt32 cardinality = 1);
    UInt32  addUVec4    (const std::string& name, UInt32 cardinality = 1);
    UInt32  addBVec2    (const std::string& name, UInt32 cardinality = 1);
    UInt32  addBVec3    (const std::string& name, UInt32 cardinality = 1);
    UInt32  addBVec4    (const std::string& name, UInt32 cardinality = 1);
    UInt32  addMat2     (const std::string& name, UInt32 cardinality = 1);
    UInt32  addMat3     (const std::string& name, UInt32 cardinality = 1);
    UInt32  addMat4     (const std::string& name, UInt32 cardinality = 1);
    UInt32  addDMat2    (const std::string& name, UInt32 cardinality = 1);
    UInt32  addDMat3    (const std::string& name, UInt32 cardinality = 1);
    UInt32  addDMat4    (const std::string& name, UInt32 cardinality = 1);
    UInt32  addMat2x3   (const std::string& name, UInt32 cardinality = 1);
    UInt32  addMat3x2   (const std::string& name, UInt32 cardinality = 1);
    UInt32  addMat2x4   (const std::string& name, UInt32 cardinality = 1);
    UInt32  addMat4x2   (const std::string& name, UInt32 cardinality = 1);
    UInt32  addMat3x4   (const std::string& name, UInt32 cardinality = 1);
    UInt32  addMat4x3   (const std::string& name, UInt32 cardinality = 1);
    UInt32  addDMat2x3  (const std::string& name, UInt32 cardinality = 1);
    UInt32  addDMat3x2  (const std::string& name, UInt32 cardinality = 1);
    UInt32  addDMat2x4  (const std::string& name, UInt32 cardinality = 1);
    UInt32  addDMat4x2  (const std::string& name, UInt32 cardinality = 1);
    UInt32  addDMat3x4  (const std::string& name, UInt32 cardinality = 1);
    UInt32  addDMat4x3  (const std::string& name, UInt32 cardinality = 1);

    void    setFloat    (UInt32 handle, Real32          value, UInt32 array_idx = 0);
    void    setDouble   (UInt32 handle, Real64          value, UInt32 array_idx = 0);
    void    setInt      (UInt32 handle, Int32           value, UInt32 array_idx = 0);
    void    setUInt     (UInt32 handle, UInt32          value, UInt32 array_idx = 0);
    void    setBool     (UInt32 handle, bool            value, UInt32 array_idx = 0);
    void    setVec2     (UInt32 handle, const Vec2f&    value, UInt32 array_idx = 0);
    void    setVec2     (UInt32 handle, const Pnt2f&    value, UInt32 array_idx = 0);
    void    setVec3     (UInt32 handle, const Vec3f&    value, UInt32 array_idx = 0);
    void    setVec3     (UInt32 handle, const Pnt3f&    value, UInt32 array_idx = 0);
    void    setVec3     (UInt32 handle, const Color3f&  value, UInt32 array_idx = 0);
    void    setVec4     (UInt32 handle, const Vec4f&    value, UInt32 array_idx = 0);
    void    setVec4     (UInt32 handle, const Pnt4f&    value, UInt32 array_idx = 0);
    void    setVec4     (UInt32 handle, const Color4f&  value, UInt32 array_idx = 0);
    void    setDVec2    (UInt32 handle, const Vec2d&    value, UInt32 array_idx = 0);
    void    setDVec2    (UInt32 handle, const Pnt2d&    value, UInt32 array_idx = 0);
    void    setDVec3    (UInt32 handle, const Vec3d&    value, UInt32 array_idx = 0);
    void    setDVec3    (UInt32 handle, const Pnt3d&    value, UInt32 array_idx = 0);
    void    setDVec4    (UInt32 handle, const Vec4d&    value, UInt32 array_idx = 0);
    void    setDVec4    (UInt32 handle, const Pnt4d&    value, UInt32 array_idx = 0);
    void    setIVec2    (UInt32 handle, const Vec2i&    value, UInt32 array_idx = 0);
    void    setIVec2    (UInt32 handle, const Pnt2i&    value, UInt32 array_idx = 0);
    void    setIVec3    (UInt32 handle, const Vec3i&    value, UInt32 array_idx = 0);
    //void    setIVec3    (UInt32 handle, const Pnt3i&    value, UInt32 array_idx = 0);
    void    setIVec4    (UInt32 handle, const Vec4i&    value, UInt32 array_idx = 0);
    //void    setIVec4    (UInt32 handle, const Pnt4i&    value, UInt32 array_idx = 0);
    void    setUVec2    (UInt32 handle, const Vec2u&    value, UInt32 array_idx = 0);
    //void    setUVec2    (UInt32 handle, const Pnt2u&    value, UInt32 array_idx = 0);
    void    setUVec3    (UInt32 handle, const Vec3u&    value, UInt32 array_idx = 0);
    //void    setUVec3    (UInt32 handle, const Pnt3u&    value, UInt32 array_idx = 0);
    void    setUVec4    (UInt32 handle, const Vec4u&    value, UInt32 array_idx = 0);
    //void    setUVec4    (UInt32 handle, const Pnt4u&    value, UInt32 array_idx = 0);
    void    setBVec2    (UInt32 handle, const Vec2b&    value, UInt32 array_idx = 0);
    void    setBVec2    (UInt32 handle, const Pnt2b&    value, UInt32 array_idx = 0);
    void    setBVec3    (UInt32 handle, const Vec3b&    value, UInt32 array_idx = 0);
    void    setBVec3    (UInt32 handle, const Pnt3b&    value, UInt32 array_idx = 0);
    void    setBVec4    (UInt32 handle, const Vec4b&    value, UInt32 array_idx = 0);
    void    setBVec4    (UInt32 handle, const Pnt4b&    value, UInt32 array_idx = 0);
    void    setMat2     (UInt32 handle, const Matrix4f& value, UInt32 array_idx = 0);
    void    setMat3     (UInt32 handle, const Matrix4f& value, UInt32 array_idx = 0);
    void    setMat4     (UInt32 handle, const Matrix4f& value, UInt32 array_idx = 0);
    void    setDMat2    (UInt32 handle, const Matrix4d& value, UInt32 array_idx = 0);
    void    setDMat3    (UInt32 handle, const Matrix4d& value, UInt32 array_idx = 0);
    void    setDMat4    (UInt32 handle, const Matrix4d& value, UInt32 array_idx = 0);
    void    setMat2x3   (UInt32 handle, const Matrix4f& value, UInt32 array_idx = 0);
    void    setMat3x2   (UInt32 handle, const Matrix4f& value, UInt32 array_idx = 0);
    void    setMat2x4   (UInt32 handle, const Matrix4f& value, UInt32 array_idx = 0);
    void    setMat4x2   (UInt32 handle, const Matrix4f& value, UInt32 array_idx = 0);
    void    setMat3x4   (UInt32 handle, const Matrix4f& value, UInt32 array_idx = 0);
    void    setMat4x3   (UInt32 handle, const Matrix4f& value, UInt32 array_idx = 0);
    void    setDMat2x3  (UInt32 handle, const Matrix4d& value, UInt32 array_idx = 0);
    void    setDMat3x2  (UInt32 handle, const Matrix4d& value, UInt32 array_idx = 0);
    void    setDMat2x4  (UInt32 handle, const Matrix4d& value, UInt32 array_idx = 0);
    void    setDMat4x2  (UInt32 handle, const Matrix4d& value, UInt32 array_idx = 0);
    void    setDMat3x4  (UInt32 handle, const Matrix4d& value, UInt32 array_idx = 0);
    void    setDMat4x3  (UInt32 handle, const Matrix4d& value, UInt32 array_idx = 0);

    void    setFloat    (const std::string& name, Real32          value, UInt32 array_idx = 0);
    void    setDouble   (const std::string& name, Real64          value, UInt32 array_idx = 0);
    void    setInt      (const std::string& name, Int32           value, UInt32 array_idx = 0);
    void    setUInt     (const std::string& name, UInt32          value, UInt32 array_idx = 0);
    void    setBool     (const std::string& name, bool            value, UInt32 array_idx = 0);
    void    setVec2     (const std::string& name, const Vec2f&    value, UInt32 array_idx = 0);
    void    setVec2     (const std::string& name, const Pnt2f&    value, UInt32 array_idx = 0);
    void    setVec3     (const std::string& name, const Vec3f&    value, UInt32 array_idx = 0);
    void    setVec3     (const std::string& name, const Pnt3f&    value, UInt32 array_idx = 0);
    void    setVec3     (const std::string& name, const Color3f&  value, UInt32 array_idx = 0);
    void    setVec4     (const std::string& name, const Vec4f&    value, UInt32 array_idx = 0);
    void    setVec4     (const std::string& name, const Pnt4f&    value, UInt32 array_idx = 0);
    void    setVec4     (const std::string& name, const Color4f&  value, UInt32 array_idx = 0);
    void    setDVec2    (const std::string& name, const Vec2d&    value, UInt32 array_idx = 0);
    void    setDVec2    (const std::string& name, const Pnt2d&    value, UInt32 array_idx = 0);
    void    setDVec3    (const std::string& name, const Vec3d&    value, UInt32 array_idx = 0);
    void    setDVec3    (const std::string& name, const Pnt3d&    value, UInt32 array_idx = 0);
    void    setDVec4    (const std::string& name, const Vec4d&    value, UInt32 array_idx = 0);
    void    setDVec4    (const std::string& name, const Pnt4d&    value, UInt32 array_idx = 0);
    void    setIVec2    (const std::string& name, const Vec2i&    value, UInt32 array_idx = 0);
    void    setIVec2    (const std::string& name, const Pnt2i&    value, UInt32 array_idx = 0);
    void    setIVec3    (const std::string& name, const Vec3i&    value, UInt32 array_idx = 0);
    //void    setIVec3    (const std::string& name, const Pnt3i&    value, UInt32 array_idx = 0);
    void    setIVec4    (const std::string& name, const Vec4i&    value, UInt32 array_idx = 0);
    //void    setIVec4    (const std::string& name, const Pnt4i&    value, UInt32 array_idx = 0);
    void    setUVec2    (const std::string& name, const Vec2u&    value, UInt32 array_idx = 0);
    //void    setUVec2    (const std::string& name, const Pnt2u&    value, UInt32 array_idx = 0);
    void    setUVec3    (const std::string& name, const Vec3u&    value, UInt32 array_idx = 0);
    //void    setUVec3    (const std::string& name, const Pnt3u&    value, UInt32 array_idx = 0);
    void    setUVec4    (const std::string& name, const Vec4u&    value, UInt32 array_idx = 0);
    //void    setUVec4    (const std::string& name, const Pnt4u&    value, UInt32 array_idx = 0);
    void    setBVec2    (const std::string& name, const Vec2b&    value, UInt32 array_idx = 0);
    void    setBVec2    (const std::string& name, const Pnt2b&    value, UInt32 array_idx = 0);
    void    setBVec3    (const std::string& name, const Vec3b&    value, UInt32 array_idx = 0);
    void    setBVec3    (const std::string& name, const Pnt3b&    value, UInt32 array_idx = 0);
    void    setBVec4    (const std::string& name, const Vec4b&    value, UInt32 array_idx = 0);
    void    setBVec4    (const std::string& name, const Pnt4b&    value, UInt32 array_idx = 0);
    void    setMat2     (const std::string& name, const Matrix4f& value, UInt32 array_idx = 0);
    void    setMat3     (const std::string& name, const Matrix4f& value, UInt32 array_idx = 0);
    void    setMat4     (const std::string& name, const Matrix4f& value, UInt32 array_idx = 0);
    void    setDMat2    (const std::string& name, const Matrix4d& value, UInt32 array_idx = 0);
    void    setDMat3    (const std::string& name, const Matrix4d& value, UInt32 array_idx = 0);
    void    setDMat4    (const std::string& name, const Matrix4d& value, UInt32 array_idx = 0);
    void    setMat2x3   (const std::string& name, const Matrix4f& value, UInt32 array_idx = 0);
    void    setMat3x2   (const std::string& name, const Matrix4f& value, UInt32 array_idx = 0);
    void    setMat2x4   (const std::string& name, const Matrix4f& value, UInt32 array_idx = 0);
    void    setMat4x2   (const std::string& name, const Matrix4f& value, UInt32 array_idx = 0);
    void    setMat3x4   (const std::string& name, const Matrix4f& value, UInt32 array_idx = 0);
    void    setMat4x3   (const std::string& name, const Matrix4f& value, UInt32 array_idx = 0);
    void    setDMat2x3  (const std::string& name, const Matrix4d& value, UInt32 array_idx = 0);
    void    setDMat3x2  (const std::string& name, const Matrix4d& value, UInt32 array_idx = 0);
    void    setDMat2x4  (const std::string& name, const Matrix4d& value, UInt32 array_idx = 0);
    void    setDMat4x2  (const std::string& name, const Matrix4d& value, UInt32 array_idx = 0);
    void    setDMat3x4  (const std::string& name, const Matrix4d& value, UInt32 array_idx = 0);
    void    setDMat4x3  (const std::string& name, const Matrix4d& value, UInt32 array_idx = 0);

    /*! \}                                                                 */

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
    // Variables should all be in UniformBufferObjChunkBase.

    void onCreate      (const UniformBufferObjChunk *source      = NULL);
    void onCreateAspect(const UniformBufferObjChunk *createAspect,
                        const UniformBufferObjChunk *source      = NULL);
    void onDestroy     (      UInt32                 uiContainerId     );

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    UniformBufferObjChunk(void);
    UniformBufferObjChunk(const UniformBufferObjChunk &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~UniformBufferObjChunk(void);

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
    static UInt32 _funcGetUniformBlockIndex;
    static UInt32 _funcGetActiveUniformBlockiv;
    static UInt32 _funcGetActiveUniformsiv;
    static UInt32 _funcGetUniformIndices;

    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class UniformBufferObjChunkBase;

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
    /*---------------------------------------------------------------------*/
    /*! \name                         Buffer                               */
    /*! \{                                                                 */
    std::vector<GLubyte>    createBuffer    (DrawEnv *pEnv);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                         Invariants                           */
    /*! \{                                                                 */
    bool                    invariantOnStorageSize  ();

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const UniformBufferObjChunk &source);
};

typedef UniformBufferObjChunk *UniformBufferObjChunkP;

OSG_END_NAMESPACE

#include "OSGUniformBufferObjChunkBase.inl"
#include "OSGUniformBufferObjChunk.inl"

#endif /* _OSGUNIFORMBUFFEROBJCHUNK_H_ */
