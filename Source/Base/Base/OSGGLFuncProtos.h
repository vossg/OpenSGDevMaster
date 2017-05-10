/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2003 by the OpenSG Forum                   *
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

#ifndef _OSGGLFUNCPROTOS_H_
#define _OSGGLFUNCPROTOS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGConceptPropertyChecks.h"

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#include "OSGGL.h"
#endif

#include "OSGGLEXT.h"

OSG_BEGIN_NAMESPACE

#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*---------------------------------------------------------------------------*/
/*! \name Shader                                                             */
/*! \ingroup GrpBaseBaseGLFunc                                               */
/*! \{                                                                       */

typedef GLuint (OSG_APIENTRY * osgGlCreateShaderProc )(      GLenum    );
typedef void   (OSG_APIENTRY * osgGlDeleteShaderProc )(      GLuint    );
#  if defined(OSG_USE_OGL3_PROTOS) || defined(OSG_USE_OGL4_PROTOS)
typedef void   (OSG_APIENTRY * osgGlShaderSourceProc )(      GLuint, 
                                                             GLsizei, 
                                                       const GLchar  * const *, 
                                                       const GLint   * );
#else
typedef void   (OSG_APIENTRY * osgGlShaderSourceProc )(      GLuint, 
                                                             GLsizei, 
                                                       const GLchar  **, 
                                                       const GLint   * );
#endif

typedef void     (OSG_APIENTRY * osgGlCompileShaderProc)(    GLuint    );

typedef void     (OSG_APIENTRY * osgGlAttachShaderProc )(    GLuint, 
                                                             GLuint    );

typedef void     (OSG_APIENTRY * osgGlGetShaderivProc  )(    GLuint, 
                                                             GLenum, 
                                                             GLint   * );
typedef void     (OSG_APIENTRY * 
                             osgGlGetShaderInfoLogProc )(    GLuint, 
                                                             GLsizei, 
                                                             GLsizei *, 
                                                             GLchar  * );

typedef GLuint (OSG_APIENTRY * osgGlCreateProgramProc  )(    void      );
typedef void   (OSG_APIENTRY * osgGlDeleteProgramProc  )(    GLuint    );
typedef void   (OSG_APIENTRY * osgGlLinkProgramProc    )(    GLuint    );
typedef void   (OSG_APIENTRY * osgGlGetProgramivProc   )(    GLuint, 
                                                             GLenum, 
                                                             GLint   * );
typedef void   (OSG_APIENTRY * 
                           osgGlGetProgramInfoLogProc  )(    GLuint, 
                                                             GLsizei, 
                                                             GLsizei *, 
                                                             GLchar  *);
typedef void   (OSG_APIENTRY * osgGlUseProgramProc     )(    GLuint   );

typedef void   (OSG_APIENTRY * osgGlGetActiveAttribProc)(    GLuint, 
                                                             GLuint, 
                                                             GLsizei, 
                                                             GLsizei *, 
                                                             GLint   *, 
                                                             GLenum  *, 
                                                             GLchar  *);

/*! \}                                                                       */
/*---------------------------------------------------------------------------*/
/*! \name Shader Uniforms                                                    */
/*! \ingroup GrpBaseBaseGLFunc                                               */
/*! \{                                                                       */

typedef GLint (OSG_APIENTRY * osgGlGetUniformLocationProc)(      GLuint, 
                                                           const char  *);

typedef void  (OSG_APIENTRY * osgGlUniform1iProc         )(      GLint,        
                                                                 GLint  );
typedef void  (OSG_APIENTRY * osgGlUniform2iProc         )(      GLint,        
                                                                 GLint,
                                                                 GLint  );
typedef void  (OSG_APIENTRY * osgGlUniform3iProc         )(      GLint,        
                                                                 GLint,
                                                                 GLint,
                                                                 GLint  );
typedef void  (OSG_APIENTRY * osgGlUniform4iProc         )(      GLint,        
                                                                 GLint,
                                                                 GLint,
                                                                 GLint,
                                                                 GLint  );

typedef void  (OSG_APIENTRY * osgGlUniform1uiProc        )(      GLint,
                                                                 GLuint );
typedef void  (OSG_APIENTRY * osgGlUniform2uiProc        )(      GLint,
                                                                 GLuint,
                                                                 GLuint );
typedef void  (OSG_APIENTRY * osgGlUniform3uiProc        )(      GLint,
                                                                 GLuint,
                                                                 GLuint,
                                                                 GLuint );
typedef void  (OSG_APIENTRY * osgGlUniform4uiProc        )(      GLint,
                                                                 GLuint,
                                                                 GLuint,
                                                                 GLuint,
                                                                 GLuint  );

typedef void  (OSG_APIENTRY * osgGlUniform1fProc         )(      GLint,        
                                                                 GLfloat );
typedef void  (OSG_APIENTRY * osgGlUniform2fProc         )(      GLint,        
                                                                 GLfloat,
                                                                 GLfloat );
typedef void  (OSG_APIENTRY * osgGlUniform3fProc         )(      GLint,        
                                                                 GLfloat,
                                                                 GLfloat,
                                                                 GLfloat);
typedef void  (OSG_APIENTRY * osgGlUniform4fProc         )(      GLint,        
                                                                 GLfloat,
                                                                 GLfloat,
                                                                 GLfloat,
                                                                 GLfloat);

typedef void  (OSG_APIENTRY * osgGlUniform1ivProc        )(      GLint,
                                                                 GLsizei,
                                                           const GLint *);
typedef void  (OSG_APIENTRY * osgGlUniform2ivProc        )(      GLint,        
                                                                 GLsizei,
                                                           const GLint *);
typedef void  (OSG_APIENTRY * osgGlUniform3ivProc        )(      GLint,        
                                                                 GLsizei,
                                                           const GLint *);
typedef void  (OSG_APIENTRY * osgGlUniform4ivProc        )(      GLint,        
                                                                 GLsizei,
                                                           const GLint *);

typedef void  (OSG_APIENTRY * osgGlUniform1uivProc       )(      GLint,
                                                                 GLsizei,
                                                           const GLuint *);
typedef void  (OSG_APIENTRY * osgGlUniform2uivProc       )(      GLint,
                                                                 GLsizei,
                                                           const GLuint *);
typedef void  (OSG_APIENTRY * osgGlUniform3uivProc       )(      GLint,
                                                                 GLsizei,
                                                           const GLuint *);
typedef void  (OSG_APIENTRY * osgGlUniform4uivProc       )(      GLint,
                                                                 GLsizei,
                                                           const GLuint *);

typedef void  (OSG_APIENTRY * osgGlUniform1fvProc        )(      GLint,        
                                                                 GLsizei,
                                                           const GLfloat *);
typedef void  (OSG_APIENTRY * osgGlUniform2fvProc        )(      GLint,        
                                                                 GLsizei,
                                                           const GLfloat *);
typedef void  (OSG_APIENTRY * osgGlUniform3fvProc        )(      GLint,        
                                                                 GLsizei,
                                                           const GLfloat *);
typedef void  (OSG_APIENTRY * osgGlUniform4fvProc        )(      GLint,        
                                                                 GLsizei,
                                                           const GLfloat *);


typedef void  (OSG_APIENTRY * osgGlUniformMatrix2fvProc  )(      GLint,
                                                                 GLsizei, 
                                                                 GLboolean, 
                                                           const GLfloat   *);
typedef void  (OSG_APIENTRY * osgGlUniformMatrix3fvProc  )(      GLint,
                                                                 GLsizei, 
                                                                 GLboolean, 
                                                           const GLfloat   *);
typedef void  (OSG_APIENTRY * osgGlUniformMatrix4fvProc  )(      GLint,
                                                                 GLsizei, 
                                                                 GLboolean, 
                                                           const GLfloat   *);

typedef void  (OSG_APIENTRY * 
                          osgGlProgramParameteriEXTProc  )(      GLuint, 
                                                                 GLenum, 
                                                                 GLint      );

typedef void  (OSG_APIENTRY * osgGlBindAttribLocationProc)(      GLuint, 
                                                                 GLuint, 
                                                           const GLchar *   );

/*! \}                                                                       */
#endif

/*---------------------------------------------------------------------------*/
/*! \name GL_ARB_uniform_buffer_object                                       */
/*! \ingroup GrpBaseBaseGLFunc                                               */
/*! \{                                                                       */
typedef void   (OSG_APIENTRY *osgGlGetUniformIndicesProc    )(GLuint,
                                                              GLsizei,
                                                              const GLchar* const *, 
                                                              GLuint *          );
typedef void   (OSG_APIENTRY *osgGlGetActiveUniformsivProc  )(GLuint, GLsizei, 
                                                              const GLuint *, 
                                                              GLenum, GLint *   );
typedef void   (OSG_APIENTRY *osgGlGetActiveUniformNameProc )(GLuint, 
                                                              GLuint, 
                                                              GLsizei, 
                                                              GLsizei *,
                                                              GLchar *          );
typedef GLuint (OSG_APIENTRY *osgGlGetUniformBlockIndexProc )(GLuint,
                                                              const GLchar *    );
typedef void   (OSG_APIENTRY *osgGlGetActiveUniformBlockivProc)
                                                             (GLuint, 
                                                              GLuint, 
                                                              GLenum, 
                                                              GLint *           );
typedef void   (OSG_APIENTRY *osgGlGetActiveUniformBlockNameProc)
                                                             (GLuint, 
                                                              GLuint, 
                                                              GLsizei, 
                                                              GLsizei *, 
                                                              GLchar *          );
typedef void   (OSG_APIENTRY *osgGlUniformBlockBindingProc  )(GLuint, 
                                                              GLuint, 
                                                              GLuint            );
/*! \}                                                                       */
/*---------------------------------------------------------------------------*/
/*! \name FrameBuffer Objects                                                */
/*! \ingroup GrpBaseBaseGLFunc                                               */
/*! \{                                                                       */

typedef void (OSG_APIENTRY *osgGlGenerateMipmapEXTProc)(GLenum);

/*! \}                                                                       */
/*---------------------------------------------------------------------------*/
/*! \name Clamp Color                                                        */
/*! \ingroup GrpBaseBaseGLFunc                                               */
/*! \{                                                                       */

typedef void (OSG_APIENTRY *osgGlClampColorARBProc)(GLenum, GLenum);

/*! \}                                                                       */
/*---------------------------------------------------------------------------*/
/*! \name Texture 3D                                                         */
/*! \ingroup GrpBaseBaseGLFunc                                               */
/*! \{                                                                       */

typedef void (OSG_APIENTRY *osgGlTexImage3DProc)(
          GLenum  target,
          GLint   level,
          GLint   internalformat,
          GLsizei width,
          GLsizei height,
          GLsizei depth,
          GLint   border,
          GLenum  format,
          GLenum  type,
    const GLvoid *pixels);

typedef void (OSG_APIENTRY*osgGlTexSubImage3DProc)(
          GLenum    target,
          GLint     level,
          GLint     xoffset,
          GLint     yoffset,
          GLint     zoffset,
          GLsizei   width,
          GLsizei   height,
          GLsizei   depth,
          GLenum    format,
          GLenum    type,
    const GLvoid   *pixels);

/*! \}                                                                       */
/*---------------------------------------------------------------------------*/
/*! \name Texture Compressed                                                 */
/*! \ingroup GrpBaseBaseGLFunc                                               */
/*! \{                                                                       */

typedef void (OSG_APIENTRY *osgGlCompressedTexImage1DProc)(
          GLenum    target,
          GLint     level,
          GLenum    internalformat,
          GLsizei   width,
          GLint     border,
          GLsizei   imageSize,
    const GLvoid   *pixels);

typedef void (OSG_APIENTRY *osgGlCompressedTexSubImage1DProc)(
          GLenum   target,
          GLint    level,
          GLint    xoffset,
          GLsizei  width,
          GLenum   format,
          GLsizei  imageSize,
    const GLvoid  *pixels);


typedef void (OSG_APIENTRY *osgGlCompressedTexImage2DProc)(
          GLenum   target,
          GLint    level,
          GLenum   internalformat,
          GLsizei  width,
          GLsizei  height,
          GLint    border,
          GLsizei  imageSize,
    const GLvoid  *pixels);

typedef void (OSG_APIENTRY *osgGlCompressedTexSubImage2DProc)(
          GLenum   target,
          GLint    level,
          GLint    xoffset,
          GLint    yoffset,
          GLsizei  width,
          GLsizei  height,
          GLenum   format,
          GLsizei  imageSize,
    const GLvoid  *pixels);


typedef void (OSG_APIENTRY *osgGlCompressedTexImage3DProc)(
          GLenum   target,
          GLint    level,
          GLenum   internalformat,
          GLsizei  width,
          GLsizei  height,
          GLsizei  depth,
          GLint    border,
          GLsizei  imageSize,
    const GLvoid  *pixels);

typedef void (OSG_APIENTRY *osgGlCompressedTexSubImage3DProc)(
          GLenum   target,
          GLint    level,
          GLint    xoffset,
          GLint    yoffset,
          GLint    zoffset,
          GLsizei  width,
          GLsizei  height,
          GLsizei  depth,
          GLenum   format,
          GLsizei  imageSize,
    const GLvoid  *pixels);

/*! \}                                                                       */
/*---------------------------------------------------------------------------*/
/*! \name BufferObjects                                                      */
/*! \ingroup GrpBaseBaseGLFunc                                               */
/*! \{                                                                       */

typedef void       (OSG_APIENTRY *osgGlBindBufferProc              )(      
          GLenum         target,
          GLuint         buffer);

typedef void       (OSG_APIENTRY *osgGlBufferDataProc              )(      
          GLenum         target, 
          GLsizeiptr     size, 
    const void          *data,
          GLenum         usage);

typedef void       (OSG_APIENTRY *osgGlBufferSubDataProc           )(      
          GLenum         target,
          GLintptr       offset,
          GLsizeiptr     size,
    const void          *data);

typedef void       (OSG_APIENTRY *osgGlGenBuffersProc              )(      
          GLsizei        n, 
          GLuint        *bufs);

typedef void       (OSG_APIENTRY *osgGlDeleteBuffersProc           )(      
          GLsizei        n, 
    const GLuint        *bufs);

typedef void      *(OSG_APIENTRY *osgGlMapBufferProc               )(
          GLenum         target, 
          GLenum         access);

typedef GLboolean  (OSG_APIENTRY *osgGlUnmapBufferProc             )(
          GLenum         target);

typedef void       (OSG_APIENTRY *osgGlEnableVertexAttribArrayProc )(
          GLuint         index);

typedef void       (OSG_APIENTRY *osgGlDisableVertexAttribArrayProc)(
          GLuint         index);

typedef void       (OSG_APIENTRY *osgGlClientActiveTextureProc     )(
          GLenum         type );

typedef void       (OSG_APIENTRY *osgGlActiveTextureProc           )(
          GLenum         texture);

typedef void       (OSG_APIENTRY *osgGlVertexAttribPointerProc     )(
          GLuint         index, 
          GLint          size, 
          GLenum         type, 
          GLboolean      normalized,
          GLsizei        stride, 
    const GLvoid        *pointer);

typedef void       (OSG_APIENTRY *osgGlSecondaryColorPointerProc   )(
          GLint          size,
          GLenum         type,
          GLsizei        stride,
    const GLvoid        *pointer);

typedef void       (OSG_APIENTRY *osgGlGetBufferSubDataProc        )(
          GLenum, 
          GLintptr, 
          GLsizeiptr, 
          GLvoid *);

typedef void       (OSG_APIENTRY *osgGlGetBufferParameterivProc    )(
          GLenum, 
          GLenum, 
          GLint *);
typedef void       (OSG_APIENTRY *osgGlGetBufferPointervProc       )(
          GLenum, 
          GLenum, 
          GLvoid* *);

typedef GLboolean  (OSG_APIENTRY *osgGlIsBufferProc                )(
          GLuint);

/*! \}                                                                       */
/*---------------------------------------------------------------------------*/
/*! \name VertexArrayObjects                                                 */
/*! \ingroup GrpBaseBaseGLFunc                                               */
/*! \{                                                                       */

typedef void (OSG_APIENTRY *osgGlBindVertexArrayProc   )(      GLuint  array  );
typedef void (OSG_APIENTRY *osgGlDeleteVertexArraysProc)(      GLsizei n, 
                                                         const GLuint *arrays );
typedef void (OSG_APIENTRY *osgGlGenVertexArraysProc   )(      GLsizei  n, 
                                                               GLuint  *arrays);

/*! \}                                                                       */
/*---------------------------------------------------------------------------*/
/*! \name Draw Elements                                                      */
/*! \ingroup GrpBaseBaseGLFunc                                               */
/*! \{                                                                       */

typedef void (OSG_APIENTRY *osgGlLockArraysProc       )(      GLint, 
                                                              GLsizei);
typedef void (OSG_APIENTRY *osgGlUnlockArraysProc     )(      void);
typedef void (OSG_APIENTRY *osgGlDrawRangeElementsProc)(      GLenum, 
                                                              GLuint, 
                                                              GLuint, 
                                                              GLsizei, 
                                                              GLenum, 
                                                        const GLvoid *);

/*! \}                                                                       */
/*---------------------------------------------------------------------------*/
/*! \name Vertex Attribs                                                     */
/*! \ingroup GrpBaseBaseGLFunc                                               */
/*! \{                                                                       */

typedef void (OSG_APIENTRY *osgGlMultiTexCoord3fvProc)(GLenum, const GLfloat *);

/*! \}                                                                       */
/*---------------------------------------------------------------------------*/
/*! \name TextureBuffers                                                     */
/*! \ingroup GrpBaseBaseGLFunc                                               */
/*! \{                                                                       */

typedef void (OSG_APIENTRY *osgGlFramebufferTexture1DProc)(GLenum target, 
                                                           GLenum attachment, 
                                                           GLenum textarget, 
                                                           GLuint texture, 
                                                           GLint  level     );

typedef void (OSG_APIENTRY *osgGlFramebufferTexture2DProc)(GLenum target, 
                                                           GLenum attachment, 
                                                           GLenum textarget, 
                                                           GLuint texture, 
                                                           GLint  level     );

typedef void (OSG_APIENTRY *osgGlFramebufferTexture3DProc)(GLenum target, 
                                                           GLenum attachment, 
                                                           GLenum textarget, 
                                                           GLuint texture, 
                                                           GLint  level, 
                                                           GLint  zoffset   );

typedef void (OSG_APIENTRY *osgGlFramebufferTextureLayerProc)(GLenum target,
                                                              GLenum attachment,
                                                              GLuint texture,
                                                              GLint  level,
                                                              GLint  layer);

typedef void   (OSG_APIENTRY *osgGlGenerateMipmapProc    )(GLenum target    );

/*! \}                                                                       */
/*---------------------------------------------------------------------------*/
/*! \name RenderBuffers                                                      */
/*! \ingroup GrpBaseBaseGLFunc                                               */
/*! \{                                                                       */

typedef void (OSG_APIENTRY *osgGlGenRenderbuffersProc       )(
    GLsizei  n, 
    GLuint  *renderbuffers);

typedef void (OSG_APIENTRY *osgGlBindRenderbufferProc       )(
    GLenum   target, 
    GLuint   renderbuffer);

typedef void (OSG_APIENTRY *osgGlRenderbufferStorageProc    )(
    GLenum   target, 
    GLenum   internalformat, 
    GLsizei  width, 
    GLsizei  height);

typedef void (OSG_APIENTRY *osgGlDeleteRenderbuffersProc    )(
          GLsizei  n, 
    const GLuint  *renderbuffers);

/*! \}                                                                       */
/*---------------------------------------------------------------------------*/
/*! \name FrameBufferObjects                                                 */
/*! \ingroup GrpBaseBaseGLFunc                                               */
/*! \{                                                                       */

typedef void   (OSG_APIENTRY *osgGlGenFramebuffersProc        )(
          GLsizei  n, 
          GLuint  *framebuffers);

typedef void   (OSG_APIENTRY *osgGlDeleteFramebuffersProc     )(
          GLsizei  n, 
    const GLuint  *framebuffers);

typedef void   (OSG_APIENTRY *osgGlBindFramebufferProc        )(
          GLenum   target, 
          GLuint   framebuffer);

typedef void   (OSG_APIENTRY *osgGlFramebufferRenderbufferProc)(
          GLenum   target, 
          GLenum   attachment, 
          GLenum   renderbuffertarget, 
          GLuint   renderbuffer);

typedef void   (OSG_APIENTRY *osgGlDrawBuffersProc           )(
          GLsizei  n, 
    const GLenum  *buffers);

typedef GLenum (OSG_APIENTRY *osgGlCheckFramebufferStatusProc)(
          GLenum   target );

/*! \}                                                                       */
/*---------------------------------------------------------------------------*/
/*! \name FrameBufferBlit                                                    */
/*! \ingroup GrpBaseBaseGLFunc                                               */
/*! \{                                                                       */

typedef void (OSG_APIENTRY *osgGlBlitFramebufferProc)(GLint      srcX0, 
                                                      GLint      srcY0, 
                                                      GLint      srcX1, 
                                                      GLint      srcY1, 
                                                      GLint      dstX0, 
                                                      GLint      dstY0, 
                                                      GLint      dstX1, 
                                                      GLint      dstY1, 
                                                      GLbitfield mask, 
                                                      GLenum     filter);

/*! \}                                                                       */
/*---------------------------------------------------------------------------*/
/*! \name FrameBufferMultiSample                                             */
/*! \ingroup GrpBaseBaseGLFunc                                               */
/*! \{                                                                       */

typedef void (OSG_APIENTRY *osgGlRenderbufferStorageMultisampleProc)(
    GLenum  target, 
    GLsizei samples, 
    GLenum  internalformat, 
    GLsizei width, 
    GLsizei height        );

/*! \}                                                                       */
/*---------------------------------------------------------------------------*/
/*! \name FrameBufferMultiSampleCoverage                                     */
/*! \ingroup GrpBaseBaseGLFunc                                               */
/*! \{                                                                       */

typedef void (OSG_APIENTRY *osgGlRenderbufferStorageMultisampleCoverageProc)(
    GLenum  target, 
    GLsizei coverageSamples, 
    GLsizei colorSamples, 
    GLenum  internalformat, 
    GLsizei width, 
    GLsizei height         );

/*! \}                                                                       */
/*---------------------------------------------------------------------------*/
/*! \name Point Sprites                                                      */
/*! \ingroup GrpBaseBaseGLFunc                                               */
/*! \{                                                                       */

typedef void   (OSG_APIENTRY *osgGlPointParameterfProc       )(
          GLenum  pname,
          GLfloat param );

typedef void   (OSG_APIENTRY *osgGlPointParameterfvProc       )(
          GLenum   pname,
    const GLfloat *params);

/*! \}                                                                       */
/*---------------------------------------------------------------------------*/
/*! \name Queries                                                            */
/*! \ingroup GrpBaseBaseGLFunc                                               */
/*! \{                                                                       */

typedef void      (OSG_APIENTRY *osgGlGenQueriesProc       )(      GLsizei, 
                                                                   GLuint *);
typedef void      (OSG_APIENTRY *osgGlDeleteQueriesProc    )(      GLsizei, 
                                                             const GLuint *);
typedef GLboolean (OSG_APIENTRY *osgGlIsQueryProc          )(      GLuint);
typedef void      (OSG_APIENTRY *osgGlBeginQueryProc       )(      GLenum, 
                                                                   GLuint);
typedef void      (OSG_APIENTRY *osgGlEndQueryProc         )(      GLenum);
typedef void      (OSG_APIENTRY *osgGlGetQueryivProc       )(      GLenum, 
                                                                   GLenum, 
                                                                   GLint *);
typedef void      (OSG_APIENTRY *osgGlGetQueryObjectivProc )(      GLuint, 
                                                                   GLenum, 
                                                                   GLint *);
typedef void      (OSG_APIENTRY *osgGlGetQueryObjectuivProc)(      GLuint, 
                                                                   GLenum, 
                                                                   GLuint *);
typedef void      (OSG_APIENTRY *osgGlBeginQueryIndexedProc)(      GLenum, 
                                                                   GLuint, 
                                                                   GLuint  );
typedef void      (OSG_APIENTRY *osgGlEndQueryIndexedProc  )(      GLenum, 
                                                                   GLuint  );


typedef const GLubyte * (OSG_APIENTRY *osgGlGetStringiProc)(GLenum name, 
                                                            GLuint index);


/*! \}                                                                       */
/*---------------------------------------------------------------------------*/
/*! \name Blending                                                           */
/*! \ingroup GrpBaseBaseGLFunc                                               */
/*! \{                                                                       */

typedef void (OSG_APIENTRY *osgGlBlendColorProc       )(GLclampf, 
                                                        GLclampf, 
                                                        GLclampf, 
                                                        GLclampf);
typedef void (OSG_APIENTRY *osgGlBlendEquationProc    )(GLenum);
typedef void (OSG_APIENTRY *osgGlBlendFuncSeparateProc)(GLenum, 
                                                        GLenum, 
                                                        GLenum, 
                                                        GLenum);

/*! \}                                                                       */
/*---------------------------------------------------------------------------*/
/*! \name ARB Program                                                        */
/*! \ingroup GrpBaseBaseGLFunc                                               */
/*! \{                                                                       */

typedef void (OSG_APIENTRY *osgGlProgramStringARBProc           )(
          GLenum, 
          GLenum, 
          GLsizei, 
    const GLvoid *);

typedef void (OSG_APIENTRY *osgGlBindProgramARBProc             )(
          GLenum, 
          GLuint);

typedef void (OSG_APIENTRY *osgGlDeleteProgramsARBProc          )(
          GLsizei, 
    const GLuint *);

typedef void (OSG_APIENTRY *osgGlGenProgramsARBProc             )(
          GLsizei, 
          GLuint *);

#ifndef OSG_OGL_NO_DOUBLE
typedef void (OSG_APIENTRY *osgGlProgramEnvParameter4dARBProc   )(
          GLenum, 
          GLuint, 
          GLdouble, 
          GLdouble, 
          GLdouble, 
          GLdouble);

typedef void (OSG_APIENTRY *osgGlProgramEnvParameter4dvARBProc  )(
          GLenum, 
          GLuint, 
    const GLdouble *);
#endif

typedef void (OSG_APIENTRY *osgGlProgramEnvParameter4fARBProc   )(
          GLenum, 
          GLuint, 
          GLfloat, 
          GLfloat, 
          GLfloat, 
          GLfloat);

typedef void (OSG_APIENTRY *osgGlProgramEnvParameter4fvARBProc  )(
          GLenum, 
          GLuint, 
    const GLfloat *);

#ifndef OSG_OGL_NO_DOUBLE
typedef void (OSG_APIENTRY *osgGlProgramLocalParameter4dARBProc )(
          GLenum, 
          GLuint, 
          GLdouble, 
          GLdouble, 
          GLdouble, 
          GLdouble);

typedef void (OSG_APIENTRY *osgGlProgramLocalParameter4dvARBProc)(
          GLenum, 
          GLuint, 
    const GLdouble *);
#endif

typedef void (OSG_APIENTRY *osgGlProgramLocalParameter4fARBProc )(
          GLenum, 
          GLuint, 
          GLfloat, 
          GLfloat, 
          GLfloat, 
          GLfloat);

typedef void (OSG_APIENTRY *osgGlProgramLocalParameter4fvARBProc)(
          GLenum, 
          GLuint, 
    const GLfloat *);

typedef void (OSG_APIENTRY *osgGlGetProgramivARBProc            )(
          GLenum, 
          GLenum, 
          GLint *);

/*! \}                                                                       */
/*---------------------------------------------------------------------------*/
/*! \name Register Combiner                                                  */
/*! \ingroup GrpBaseBaseGLFunc                                               */
/*! \{                                                                       */

typedef void (OSG_APIENTRY *osgGlCombinerParameterfvNVProc             )(
          GLenum, 
    const GLfloat *);

typedef void (OSG_APIENTRY *osgGlCombinerParameterfNVProc              )(
    GLenum, 
    GLfloat);

typedef void (OSG_APIENTRY *osgGlCombinerParameterivNVProc             )(
          GLenum, 
    const GLint *);

typedef void (OSG_APIENTRY *osgGlCombinerParameteriNVProc              )(
    GLenum, 
    GLint);

typedef void (OSG_APIENTRY *osgGlCombinerInputNVProc                   )(
    GLenum, 
    GLenum, 
    GLenum, 
    GLenum, 
    GLenum, 
    GLenum);

typedef void (OSG_APIENTRY *osgGlCombinerOutputNVProc                  )(
    GLenum, 
    GLenum, 
    GLenum, 
    GLenum, 
    GLenum, 
    GLenum, 
    GLenum, 
    GLboolean, 
    GLboolean, 
    GLboolean);

typedef void (OSG_APIENTRY *osgGlFinalCombinerInputNVProc              )(
    GLenum, 
    GLenum, 
    GLenum, 
    GLenum);
typedef void (OSG_APIENTRY *osgGlGetCombinerInputParameterfvNVProc     )(
    GLenum, 
    GLenum, 
    GLenum, 
    GLenum, 
    GLfloat *);

typedef void (OSG_APIENTRY *osgGlGetCombinerInputParameterivNVProc     )(
    GLenum, 
    GLenum, 
    GLenum, 
    GLenum, 
    GLint *);

typedef void (OSG_APIENTRY *osgGlGetCombinerOutputParameterfvNVProc    )(
    GLenum, 
    GLenum, 
    GLenum, 
    GLfloat *);

typedef void (OSG_APIENTRY *osgGlGetCombinerOutputParameterivNVProc    )(
    GLenum, 
    GLenum, 
    GLenum, 
    GLint *);

typedef void (OSG_APIENTRY *osgGlGetFinalCombinerInputParameterfvNVProc)(
    GLenum, 
    GLenum, 
    GLfloat *);

typedef void (OSG_APIENTRY *osgGlGetFinalCombinerInputParameterivNVProc)(
    GLenum, 
    GLenum, 
    GLint *);

typedef void (OSG_APIENTRY *osgGlCombinerStageParameterfvNVProc        )(
          GLenum, 
          GLenum, 
    const GLfloat *);

typedef void (OSG_APIENTRY *osgGlGetCombinerStageParameterfvNVProc     )(
    GLenum, 
    GLenum, 
    GLfloat *);

/*! \}                                                                       */
/*---------------------------------------------------------------------------*/
/*! \name Register Combiner                                                  */
/*! \ingroup GrpBaseBaseGLFunc                                               */
/*! \{                                                                       */

typedef void (OSG_APIENTRY *osgGlBindBufferBaseProc           )(      GLenum, 
                                                                      GLuint, 
                                                                      GLuint  );
#  if defined(OSG_USE_OGL3_PROTOS) || defined(OSG_USE_OGL4_PROTOS)
typedef void (OSG_APIENTRY *
                  osgGlTransformFeedbackVaryingsProc)(      GLuint,
                                                            GLsizei, 
                                                      const GLchar * const*,
                                                            GLenum  );
#else
typedef void (OSG_APIENTRY *osgGlTransformFeedbackVaryingsProc)(      GLuint,
                                                                      GLsizei, 
                                                                const GLchar **,
                                                                      GLenum  );
#endif

typedef void (OSG_APIENTRY *osgGlBeginTransformFeedbackProc   )(      GLenum  );
typedef void (OSG_APIENTRY *osgGlEndTransformFeedbackProc     )(      void    );

typedef void (OSG_APIENTRY *osgGlPauseTransformFeedbackProc   )(      void    );
typedef void (OSG_APIENTRY *osgGlResumeTransformFeedbackProc  )(      void    );


/*! \}                                                                       */
/*---------------------------------------------------------------------------*/
/*! \name tesselation shader                                                 */
/*! \ingroup GrpBaseBaseGLFunc                                               */
/*! \{                                                                       */

typedef void (OSG_APIENTRY *osgGlPatchParameteriProc )(      GLenum pname, 
                                                             GLint  value   );

typedef void (OSG_APIENTRY *osgGlPatchParameterfvProc)(      GLenum   pname, 
                                                       const GLfloat *values);

/*! \}                                                                       */
/*---------------------------------------------------------------------------*/
/*! \name compute shader                                                     */
/*! \ingroup GrpBaseBaseGLFunc                                               */
/*! \{                                                                       */

typedef void (OSG_APIENTRY *osgGlDispatchComputeProc        )(
    GLuint   num_groups_x, 
    GLuint   num_groups_y, 
    GLuint   num_groups_z);

typedef void (OSG_APIENTRY *osgGlDispatchComputeIndirectProc)(
    GLintptr indirect);

/*! \}                                                                       */
/*---------------------------------------------------------------------------*/
/*! \name compute variable group size                                        */
/*! \ingroup GrpBaseBaseGLFunc                                               */
/*! \{                                                                       */

typedef void (OSG_APIENTRY * osgGlDispatchComputeGroupSizeARBProc )(
    GLuint num_groups_x, 
    GLuint num_groups_y, 
    GLuint num_groups_z, 
    GLuint group_size_x, 
    GLuint group_size_y, 
    GLuint group_size_z);

/*! \}                                                                       */

/*---------------------------------------------------------------------------*/
/*! \name shader image load/store                                            */
/*! \ingroup GrpBaseBaseGLFunc                                               */
/*! \{                                                                       */

typedef void (OSG_APIENTRY *osgGlBindImageTextureProc)(GLuint     index, 
                                                       GLuint     texture, 
                                                       GLint      level, 
                                                       GLboolean  layered, 
                                                       GLint      layer, 
                                                       GLenum     access, 
                                                       GLint      format  );
typedef void (OSG_APIENTRY *osgGlMemoryBarrierProc   )(GLbitfield barriers);

/*! \}                                                                       */
/*---------------------------------------------------------------------------*/
/*! \name draw instanced                                                     */
/*! \ingroup GrpBaseBaseGLFunc                                               */
/*! \{                                                                       */

typedef void (OSG_APIENTRY *osgGlDrawArraysInstancedProc  )(GLenum  mode, 
                                                            GLint   first, 
                                                            GLsizei count, 
                                                            GLsizei primcount);
typedef void (OSG_APIENTRY *osgGlDrawElementsInstancedProc)(
          GLenum   mode, 
          GLsizei  count, 
          GLenum   type, 
    const void    *indices,
          GLsizei  primcount);

/*! \}                                                                       */
/*---------------------------------------------------------------------------*/
/*! \name instanced array                                                    */
/*! \ingroup GrpBaseBaseGLFunc                                               */
/*! \{                                                                       */

typedef void (OSG_APIENTRY *osgGlVertexAttribDivisorProc)(GLuint index, 
                                                          GLuint divisor);

/*! \}                                                                       */
/*---------------------------------------------------------------------------*/
/*! \name instanced GL_VERSION_4_3                                           */
/*! \ingroup GrpBaseBaseGLFunc                                               */
/*! \{                                                                       */

#ifdef GL_VERSION_4_3
typedef GLuint (OSG_APIENTRY *osgGlGetProgramResourceIndexProc)(
          GLuint  program, 
          GLenum  programInterface, 
    const GLchar *name                );

typedef void   (OSG_APIENTRY *osgGlGetProgramResourceNameProc         )(
          GLuint   program, 
          GLenum   programInterface, 
          GLuint   index, 
          GLsizei  bufSize, 
          GLsizei *length, 
          GLchar  *name               );

typedef void   (OSG_APIENTRY *osgGlGetProgramResourceivProc           )(
          GLuint   program, 
          GLenum   programInterface, 
          GLuint   index, 
          GLsizei  propCount, 
    const GLenum  *props, 
          GLsizei  bufSize, 
          GLsizei *length, 
          GLint   *params             );

typedef GLint  (OSG_APIENTRY *osgGlGetProgramResourceLocationProc     )(
          GLuint   program, 
          GLenum   programInterface, 
    const GLchar  *name               );

typedef GLint  (OSG_APIENTRY *osgGlGetProgramResourceLocationIndexProc)(
          GLuint   program, 
          GLenum   programInterface, 
    const GLchar  *name               );

typedef void   (OSG_APIENTRY *osgGlShaderStorageBlockBindingProc      )(
          GLuint   program, 
          GLuint   storageBlockIndex, 
          GLuint   storageBlockBinding);
#endif

/*! \}                                                                       */
/*---------------------------------------------------------------------------*/
/*! \name GL Function Helper                                                 */
/*! \ingroup GrpBaseBaseGLFunc                                               */
/*! \{                                                                       */

#ifdef OSG_DEBUG

# define OSGGETGLFUNC_W(OGLFUNC, FUNCVAR, FUNCID)                            \
    OSG::FUNCVAR##Proc FUNCVAR =                                             \
        reinterpret_cast<OSG::FUNCVAR##Proc>(                                \
            pEnv->getWindow()->getFunction(FUNCID));                         \
                                                                             \
    if(FUNCVAR == NULL)                                                      \
        FFATAL(("Func %s of type %s NULL, window %p\n",                      \
                #FUNCVAR, #OGLFUNC, static_cast<void *>(pEnv->getWindow()))) \

# define OSGGETGLFUNCBYID_W(OGLFUNC, FUNCVAR, FUNCID, WINDOW)           \
    OSG::FUNCVAR##Proc FUNCVAR =                                        \
        reinterpret_cast< OSG:: FUNCVAR##Proc >(                        \
            (WINDOW)->getFunction(FUNCID));                             \
                                                                        \
    if(FUNCVAR == NULL)                                                 \
        FFATAL(("Func %s of type %s NULL, window %p\n",                 \
                #FUNCVAR, #OGLFUNC, static_cast<void *>((WINDOW))))     \

# define OSGGETGLFUNCBYNAME_W(OGLFUNC, FUNCVAR, FUNCNAME, WINDOW)       \
    OSG::FUNCVAR##Proc FUNCVAR =                                        \
        reinterpret_cast<OSG::FUNCVAR##Proc>(                           \
            (WINDOW)->getFunctionByName(FUNCNAME));                     \
                                                                        \
    if(FUNCVAR == NULL)                                                 \
        FFATAL(("Func %s of type %s NULL, window %p\n",                 \
                #FUNCVAR, #OGLFUNC, static_cast<void *>((WINDOW))))     \

# define OSGGETGLFUNC_NV_W(OGLFUNC, FUNCVAR, FUNCID)                         \
    FUNCVAR =                                                                \
        reinterpret_cast<OSG::FUNCVAR##Proc>(                                \
            pEnv->getWindow()->getFunction(FUNCID));                         \
                                                                             \
    if(FUNCVAR == NULL)                                                      \
        FFATAL(("Func %s of type %s NULL, window %p\n",                      \
                #FUNCVAR, #OGLFUNC, static_cast<void *>(pEnv->getWindow()))) \

# define OSGGETGLFUNCBYID_NV_W(OGLFUNC, FUNCVAR, FUNCID, WINDOW)        \
    FUNCVAR =                                                           \
        reinterpret_cast< OSG:: FUNCVAR##Proc >(                        \
            (WINDOW)->getFunction(FUNCID));                             \
                                                                        \
    if(FUNCVAR == NULL)                                                 \
        FFATAL(("Func %s of type %s NULL, window %p\n",                 \
                #FUNCVAR, #OGLFUNC, static_cast<void *>((WINDOW))))     \

# define OSGGETGLFUNCBYNAME_NV_W(OGLFUNC, FUNCVAR, FUNCNAME, WINDOW)    \
    FUNCVAR =                                                           \
        reinterpret_cast<OSG::FUNCVAR##Proc>(                           \
            (WINDOW)->getFunctionByName(FUNCNAME));                     \
                                                                        \
    if(FUNCVAR == NULL)                                                 \
        FFATAL(("Func %s of type %s NULL, window %p\n",                 \
                #FUNCVAR, #OGLFUNC, static_cast<void *>((WINDOW))))     \

#else

# define OSGGETGLFUNC_W(OGLFUNC, FUNCVAR, FUNCID)                       \
    OSG::FUNCVAR##Proc FUNCVAR =                                        \
        reinterpret_cast<OSG::FUNCVAR##Proc>(                           \
            pEnv->getWindow()->getFunction(FUNCID));

# define OSGGETGLFUNCBYID_W(OGLFUNC, FUNCVAR, FUNCID, WINDOW)           \
    OSG::FUNCVAR##Proc FUNCVAR =                                        \
        reinterpret_cast<OSG::FUNCVAR##Proc>(                           \
            (WINDOW)->getFunction(FUNCID));

# define OSGGETGLFUNCBYNAME_W(OGLFUNC, FUNCVAR, FUNCNAME, WINDOW)       \
    OSG::FUNCVAR##Proc FUNCVAR =                                        \
        reinterpret_cast<OSG::FUNCVAR##Proc>(                           \
            (WINDOW)->getFunctionByName(FUNCNAME));

# define OSGGETGLFUNC_NV_W(OGLFUNC, FUNCVAR, FUNCID)                    \
    FUNCVAR =                                                           \
        reinterpret_cast<OSG::FUNCVAR##Proc>(                           \
            pEnv->getWindow()->getFunction(FUNCID));

# define OSGGETGLFUNCBYID_NV_W(OGLFUNC, FUNCVAR, FUNCID, WINDOW)        \
    FUNCVAR =                                                           \
        reinterpret_cast<OSG::FUNCVAR##Proc>(                           \
            (WINDOW)->getFunction(FUNCID));

# define OSGGETGLFUNCBYNAME_NV_W(OGLFUNC, FUNCVAR, FUNCNAME, WINDOW)    \
    FUNCVAR =                                                           \
        reinterpret_cast<OSG::FUNCVAR##Proc>(                           \
            (WINDOW)->getFunctionByName(FUNCNAME));

#endif

#define OSGGETGLFUNC_P(OGLFUNC, FUNCVAR, FUNCID)                        \
    OSG::FUNCVAR##Proc FUNCVAR = OGLFUNC;

#define OSGGETGLFUNCBYID_P(OGLFUNC, FUNCVAR, FUNCID, WINDOW)            \
    OSG::osgSinkUnusedWarning(WINDOW);                                  \
    OSG::FUNCVAR##Proc FUNCVAR = OGLFUNC;

#define OSGGETGLFUNCBYNAME_P(OGLFUNC, FUNCVAR, FUNCNAME, WINDOW)        \
    OSG::osgSinkUnusedWarning(WINDOW);                                  \
    OSG::FUNCVAR##Proc FUNCVAR = OGLFUNC;

#define OSGGETGLFUNC_NV_P(OGLFUNC, FUNCVAR, FUNCID)                     \
    FUNCVAR = OGLFUNC;

#define OSGGETGLFUNCBYID_NV_P(OGLFUNC, FUNCVAR, FUNCID, WINDOW)         \
    OSG::osgSinkUnusedWarning(WINDOW);                                  \
    FUNCVAR = OGLFUNC;

#define OSGGETGLFUNCBYNAME_NV_P(OGLFUNC, FUNCVAR, FUNCNAME, WINDOW)     \
    OSG::osgSinkUnusedWarning(WINDOW);                                  \
    FUNCVAR = OGLFUNC;
       


#ifdef OSG_USE_OGL3_PROTOS
# define OSGGETGLFUNC_GL3(FUNCTYPE, FUNCVAR, FUNCID)                     \
    OSGGETGLFUNC_P(FUNCTYPE, FUNCVAR, FUNCID)

# define OSGGETGLFUNCBYID_GL3(FUNCTYPE, FUNCVAR, FUNCID, WINDOW)         \
    OSGGETGLFUNCBYID_P(FUNCTYPE, FUNCVAR, FUNCID, WINDOW)

# define OSGGETGLFUNCBYNAME_GL3(FUNCTYPE, FUNCVAR, FUNCNAME, WINDOW)     \
    OSGGETGLFUNCBYNAME_P(FUNCTYPE, FUNCVAR, FUNCNAME, WINDOW)

# define OSGGETGLFUNC_NV_GL3(FUNCTYPE, FUNCVAR, FUNCID)                  \
    OSGGETGLFUNC_NV_P(FUNCTYPE, FUNCVAR, FUNCID)

# define OSGGETGLFUNCBYID_NV_GL3(FUNCTYPE, FUNCVAR, FUNCID, WINDOW)      \
    OSGGETGLFUNCBYID_NV_P(FUNCTYPE, FUNCVAR, FUNCID, WINDOW)

# define OSGGETGLFUNCBYNAME_NV_GL3(FUNCTYPE, FUNCVAR, FUNCNAME, WINDOW)  \
    OSGGETGLFUNCBYNAME_NV_P(FUNCTYPE, FUNCVAR, FUNCNAME, WINDOW)
#endif //OSG_USE_OGL3_PROTOS

#ifdef OSG_USE_OGL4_PROTOS
# define OSGGETGLFUNC_GL4(FUNCTYPE, FUNCVAR, FUNCID)                     \
    OSGGETGLFUNC_P(FUNCTYPE, FUNCVAR, FUNCID)

# define OSGGETGLFUNCBYID_GL4(FUNCTYPE, FUNCVAR, FUNCID, WINDOW)         \
    OSGGETGLFUNCBYID_P(FUNCTYPE, FUNCVAR, FUNCID, WINDOW)

# define OSGGETGLFUNCBYNAME_GL4(FUNCTYPE, FUNCVAR, FUNCNAME, WINDOW)     \
    OSGGETGLFUNCBYNAME_P(FUNCTYPE, FUNCVAR, FUNCNAME, WINDOW)

# define OSGGETGLFUNC_NV_GL4(FUNCTYPE, FUNCVAR, FUNCID)                  \
    OSGGETGLFUNC_NV_P(FUNCTYPE, FUNCVAR, FUNCID)

# define OSGGETGLFUNCBYID_NV_GL4(FUNCTYPE, FUNCVAR, FUNCID, WINDOW)      \
    OSGGETGLFUNCBYID_NV_P(FUNCTYPE, FUNCVAR, FUNCID, WINDOW)

# define OSGGETGLFUNCBYNAME_NV_GL4(FUNCTYPE, FUNCVAR, FUNCNAME, WINDOW)  \
    OSGGETGLFUNCBYNAME_NV_P(FUNCTYPE, FUNCVAR, FUNCNAME, WINDOW)
#endif // OSG_USE_OGL4_PROTOS


#if defined(OSG_USE_OGLES_PROTOS) || defined(OSG_USE_OGL3_PROTOS)
# define OSGGETGLFUNC_GL3_ES(FUNCTYPE, FUNCVAR, FUNCID)                     \
    OSGGETGLFUNC_P(FUNCTYPE, FUNCVAR, FUNCID)

# define OSGGETGLFUNCBYID_GL3_ES(FUNCTYPE, FUNCVAR, FUNCID, WINDOW)         \
    OSGGETGLFUNCBYID_P(FUNCTYPE, FUNCVAR, FUNCID, WINDOW)

# define OSGGETGLFUNCBYNAME_GL3_ES(FUNCTYPE, FUNCVAR, FUNCNAME, WINDOW)     \
    OSGGETGLFUNCBYNAME_P(FUNCTYPE, FUNCVAR, FUNCNAME, WINDOW)

# define OSGGETGLFUNC_NV_GL3_ES(FUNCTYPE, FUNCVAR, FUNCID)                  \
    OSGGETGLFUNC_NV_P(FUNCTYPE, FUNCVAR, FUNCID)

# define OSGGETGLFUNCBYID_NV_GL3_ES(FUNCTYPE, FUNCVAR, FUNCID, WINDOW)      \
    OSGGETGLFUNCBYID_NV_P(FUNCTYPE, FUNCVAR, FUNCID, WINDOW)

# define OSGGETGLFUNCBYNAME_NV_GL3_ES(FUNCTYPE, FUNCVAR, FUNCNAME, WINDOW)  \
    OSGGETGLFUNCBYNAME_NV_P(FUNCTYPE, FUNCVAR, FUNCNAME, WINDOW)
#endif


#if defined(OSG_USE_OGLES_PROTOS) || defined(OSG_USE_OGL4_PROTOS)
# define OSGGETGLFUNC_GL4_ES(FUNCTYPE, FUNCVAR, FUNCID)                     \
    OSGGETGLFUNC_P(FUNCTYPE, FUNCVAR, FUNCID)

# define OSGGETGLFUNCBYID_GL4_ES(FUNCTYPE, FUNCVAR, FUNCID, WINDOW)         \
    OSGGETGLFUNCBYID_P(FUNCTYPE, FUNCVAR, FUNCID, WINDOW)

# define OSGGETGLFUNCBYNAME_GL4_ES(FUNCTYPE, FUNCVAR, FUNCNAME, WINDOW)     \
    OSGGETGLFUNCBYNAME_P(FUNCTYPE, FUNCVAR, FUNCNAME, WINDOW)

# define OSGGETGLFUNC_NV_GL4_ES(FUNCTYPE, FUNCVAR, FUNCID)                  \
    OSGGETGLFUNC_NV_P(FUNCTYPE, FUNCVAR, FUNCID)

# define OSGGETGLFUNCBYID_NV_GL4_ES(FUNCTYPE, FUNCVAR, FUNCID, WINDOW)      \
    OSGGETGLFUNCBYID_NV_P(FUNCTYPE, FUNCVAR, FUNCID, WINDOW)

# define OSGGETGLFUNCBYNAME_NV_GL4_ES(FUNCTYPE, FUNCVAR, FUNCNAME, WINDOW)  \
    OSGGETGLFUNCBYNAME_NV_P(FUNCTYPE, FUNCVAR, FUNCNAME, WINDOW)
#endif

// OpenGL 3 Protos
#ifndef OSGGETGLFUNC_GL3
# define OSGGETGLFUNC_GL3(FUNCTYPE, FUNCVAR, FUNCID)                        \
    OSGGETGLFUNC_W(FUNCTYPE, FUNCVAR, FUNCID)

# define OSGGETGLFUNCBYID_GL3(FUNCTYPE, FUNCVAR, FUNCID, WINDOW)            \
    OSGGETGLFUNCBYID_W(FUNCTYPE, FUNCVAR, FUNCID, WINDOW)

# define OSGGETGLFUNCBYNAME_GL3(FUNCTYPE, FUNCVAR, FUNCNAME, WINDOW)        \
    OSGGETGLFUNCBYNAME_W(FUNCTYPE, FUNCVAR, FUNCNAME, WINDOW)

# define OSGGETGLFUNC_NV_GL3(FUNCTYPE, FUNCVAR, FUNCID)                     \
    OSGGETGLFUNC_NV_W(FUNCTYPE, FUNCVAR, FUNCID)

# define OSGGETGLFUNCBYID_NV_GL3(FUNCTYPE, FUNCVAR, FUNCID, WINDOW)         \
    OSGGETGLFUNCBYID_NV_W(FUNCTYPE, FUNCVAR, FUNCID, WINDOW)

# define OSGGETGLFUNCBYNAME_NV_GL3(FUNCTYPE, FUNCVAR, FUNCNAME, WINDOW)     \
    OSGGETGLFUNCBYNAME_NV_W(FUNCTYPE, FUNCVAR, FUNCNAME, WINDOW)
#endif //OSGGETGLFUNC_GL3


// OpenGL 3 and ES Protos
#ifndef OSGGETGLFUNC_GL3_ES
# define OSGGETGLFUNC_GL3_ES(FUNCTYPE, FUNCVAR, FUNCID)                     \
    OSGGETGLFUNC_W(FUNCTYPE, FUNCVAR, FUNCID)

# define OSGGETGLFUNCBYID_GL3_ES(FUNCTYPE, FUNCVAR, FUNCID, WINDOW)         \
    OSGGETGLFUNCBYID_W(FUNCTYPE, FUNCVAR, FUNCID, WINDOW)

# define OSGGETGLFUNCBYNAME_GL3_ES(FUNCTYPE, FUNCVAR, FUNCNAME, WINDOW)     \
    OSGGETGLFUNCBYNAME_W(FUNCTYPE, FUNCVAR, FUNCNAME, WINDOW)

# define OSGGETGLFUNC_NV_GL3_ES(FUNCTYPE, FUNCVAR, FUNCID)                  \
    OSGGETGLFUNC_NV_W(FUNCTYPE, FUNCVAR, FUNCID)

# define OSGGETGLFUNCBYID_NV_GL3_ES(FUNCTYPE, FUNCVAR, FUNCID, WINDOW)      \
    OSGGETGLFUNCBYID_NV_W(FUNCTYPE, FUNCVAR, FUNCID, WINDOW)

# define OSGGETGLFUNCBYNAME_NV_GL3_ES(FUNCTYPE, FUNCVAR, FUNCNAME, WINDOW)  \
    OSGGETGLFUNCBYNAME_NV_W(FUNCTYPE, FUNCVAR, FUNCNAME, WINDOW)
#endif //OSGGETGLFUNC_GL3_ES


// OpenGL 4 Protos
#ifndef OSGGETGLFUNC_GL4
# define OSGGETGLFUNC_GL4(FUNCTYPE, FUNCVAR, FUNCID)                        \
    OSGGETGLFUNC_W(FUNCTYPE, FUNCVAR, FUNCID)

# define OSGGETGLFUNCBYID_GL4(FUNCTYPE, FUNCVAR, FUNCID, WINDOW)            \
    OSGGETGLFUNCBYID_W(FUNCTYPE, FUNCVAR, FUNCID, WINDOW)

# define OSGGETGLFUNCBYNAME_GL4(FUNCTYPE, FUNCVAR, FUNCNAME, WINDOW)        \
    OSGGETGLFUNCBYNAME_W(FUNCTYPE, FUNCVAR, FUNCNAME, WINDOW)

# define OSGGETGLFUNC_NV_GL4(FUNCTYPE, FUNCVAR, FUNCID)                     \
    OSGGETGLFUNC_NV_W(FUNCTYPE, FUNCVAR, FUNCID)

# define OSGGETGLFUNCBYID_NV_GL4(FUNCTYPE, FUNCVAR, FUNCID, WINDOW)         \
    OSGGETGLFUNCBYID_NV_W(FUNCTYPE, FUNCVAR, FUNCID, WINDOW)

# define OSGGETGLFUNCBYNAME_NV_GL4(FUNCTYPE, FUNCVAR, FUNCNAME, WINDOW)     \
    OSGGETGLFUNCBYNAME_NV_W(FUNCTYPE, FUNCVAR, FUNCNAME, WINDOW)
#endif //SGGETGLFUNC_GL4


// OpenGL 4 and ES Protos
#ifndef OSGGETGLFUNC_GL4_ES
# define OSGGETGLFUNC_GL4_ES(FUNCTYPE, FUNCVAR, FUNCID)                     \
    OSGGETGLFUNC_W(FUNCTYPE, FUNCVAR, FUNCID)

# define OSGGETGLFUNCBYID_GL4_ES(FUNCTYPE, FUNCVAR, FUNCID, WINDOW)         \
    OSGGETGLFUNCBYID_W(FUNCTYPE, FUNCVAR, FUNCID, WINDOW)

# define OSGGETGLFUNCBYNAME_GL4_ES(FUNCTYPE, FUNCVAR, FUNCNAME, WINDOW)     \
    OSGGETGLFUNCBYNAME_W(FUNCTYPE, FUNCVAR, FUNCNAME, WINDOW)

# define OSGGETGLFUNC_NV_GL4_ES(FUNCTYPE, FUNCVAR, FUNCID)                  \
    OSGGETGLFUNC_NV_W(FUNCTYPE, FUNCVAR, FUNCID)

# define OSGGETGLFUNCBYID_NV_GL4_ES(FUNCTYPE, FUNCVAR, FUNCID, WINDOW)      \
    OSGGETGLFUNCBYID_NV_W(FUNCTYPE, FUNCVAR, FUNCID, WINDOW)

# define OSGGETGLFUNCBYNAME_NV_GL4_ES(FUNCTYPE, FUNCVAR, FUNCNAME, WINDOW)  \
    OSGGETGLFUNCBYNAME_NV_W(FUNCTYPE, FUNCVAR, FUNCNAME, WINDOW)
#endif //OSGGETGLFUNC_GL4_ES


// OpenGL Ext

#define OSGGETGLFUNC_EXT(FUNCTYPE, FUNCVAR, FUNCID)                         \
    OSGGETGLFUNC_W(FUNCTYPE, FUNCVAR, FUNCID)

#define OSGGETGLFUNCBYID_EXT(FUNCTYPE, FUNCVAR, FUNCID, WINDOW)             \
    OSGGETGLFUNCBYID_W(FUNCTYPE, FUNCVAR, FUNCID, WINDOW)

#define OSGGETGLFUNCBYNAME_EXT(FUNCTYPE, FUNCVAR, FUNCNAME, WINDOW)         \
    OSGGETGLFUNCBYNAME_W(FUNCTYPE, FUNCVAR, FUNCNAME, WINDOW)

#define OSGGETGLFUNC_NV_EXT(FUNCTYPE, FUNCVAR, FUNCID)                      \
    OSGGETGLFUNC_NV_W(FUNCTYPE, FUNCVAR, FUNCID)

#define OSGGETGLFUNCBYID_NV_EXT(FUNCTYPE, FUNCVAR, FUNCID, WINDOW)          \
    OSGGETGLFUNCBYID_NV_W(FUNCTYPE, FUNCVAR, FUNCID, WINDOW)

#define OSGGETGLFUNCBYNAME_NV_EXT(FUNCTYPE, FUNCVAR, FUNCNAME, WINDOW)      \
    OSGGETGLFUNCBYNAME_NV_W(FUNCTYPE, FUNCVAR, FUNCNAME, WINDOW)




/*  \}                                                                       */
/*---------------------------------------------------------------------------*/


OSG_END_NAMESPACE

#endif /* _OSGGLFUNCPROTOS_H_ */
