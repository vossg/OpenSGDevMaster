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

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#include "OSGGL.h"
#endif

#ifdef OSG_USE_GLX
#include "GL/glx.h"
#endif

#include "OSGGLEXT.h"

OSG_BEGIN_NAMESPACE

#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*---------------------------------------------------------------------------*/
/*! \name Shader                                                             */
/*! \ingroup GrpBaseBaseGLFunc                                               */
/*! \{                                                                       */

typedef GLuint (OSG_APIENTRY * OSGglCreateShaderProc )(      GLenum    );
typedef void   (OSG_APIENTRY * OSGglDeleteShaderProc )(      GLuint    );
typedef void   (OSG_APIENTRY * OSGglShaderSourceProc )(      GLuint, 
                                                             GLsizei, 
                                                       const GLchar  **, 
                                                       const GLint   * );

typedef void     (OSG_APIENTRY * OSGglCompileShaderProc)(    GLuint    );

typedef void     (OSG_APIENTRY * OSGglAttachShaderProc )(    GLuint, 
                                                             GLuint    );

typedef void     (OSG_APIENTRY * OSGglGetShaderivProc  )(    GLuint, 
                                                             GLenum, 
                                                             GLint   * );
typedef void     (OSG_APIENTRY * 
                             OSGglGetShaderInfoLogProc )(    GLuint, 
                                                             GLsizei, 
                                                             GLsizei *, 
                                                             GLchar  * );

typedef GLuint (OSG_APIENTRY * OSGglCreateProgramProc)(      void      );
typedef void   (OSG_APIENTRY * OSGglDeleteProgramProc)(      GLuint    );
typedef void   (OSG_APIENTRY * OSGglLinkProgramProc  )(      GLuint    );
typedef void   (OSG_APIENTRY * OSGglGetProgramivProc )(      GLuint, 
                                                             GLenum, 
                                                             GLint   * );
typedef void   (OSG_APIENTRY * 
                           OSGglGetProgramInfoLogProc)(      GLuint, 
                                                             GLsizei, 
                                                             GLsizei *, 
                                                             GLchar  *);
typedef void   (OSG_APIENTRY * OSGglUseProgramProc   )(      GLuint   );

/*! \}                                                                       */
/*---------------------------------------------------------------------------*/
/*! \name Shader Uniforms                                                    */
/*! \ingroup GrpBaseBaseGLFunc                                               */
/*! \{                                                                       */

typedef GLint (OSG_APIENTRY * OSGglGetUniformLocationProc)(      GLuint, 
                                                           const char  *);

typedef void  (OSG_APIENTRY * OSGglUniform1iProc         )(      GLint,        
                                                                 GLint  );
typedef void  (OSG_APIENTRY * OSGglUniform2iProc         )(      GLint,        
                                                                 GLint,
                                                                 GLint  );
typedef void  (OSG_APIENTRY * OSGglUniform3iProc         )(      GLint,        
                                                                 GLint,
                                                                 GLint,
                                                                 GLint  );
typedef void  (OSG_APIENTRY * OSGglUniform4iProc         )(      GLint,        
                                                                 GLint,
                                                                 GLint,
                                                                 GLint,
                                                                 GLint  );

typedef void  (OSG_APIENTRY * OSGglUniform1fProc         )(      GLint,        
                                                                 GLfloat );
typedef void  (OSG_APIENTRY * OSGglUniform2fProc         )(      GLint,        
                                                                 GLfloat,
                                                                 GLfloat );
typedef void  (OSG_APIENTRY * OSGglUniform3fProc         )(      GLint,        
                                                                 GLfloat,
                                                                 GLfloat,
                                                                 GLfloat);
typedef void  (OSG_APIENTRY * OSGglUniform4fProc         )(      GLint,        
                                                                 GLfloat,
                                                                 GLfloat,
                                                                 GLfloat,
                                                                 GLfloat);

typedef void  (OSG_APIENTRY * OSGglUniform1ivProc        )(      GLint,
                                                                 GLsizei,
                                                           const GLint *);
typedef void  (OSG_APIENTRY * OSGglUniform2ivProc        )(      GLint,        
                                                                 GLsizei,
                                                           const GLint *);
typedef void  (OSG_APIENTRY * OSGglUniform3ivProc        )(      GLint,        
                                                                 GLsizei,
                                                           const GLint *);
typedef void  (OSG_APIENTRY * OSGglUniform4ivProc        )(      GLint,        
                                                                 GLsizei,
                                                           const GLint *);

typedef void  (OSG_APIENTRY * OSGglUniform1fvProc        )(      GLint,        
                                                                 GLsizei,
                                                           const GLfloat *);
typedef void  (OSG_APIENTRY * OSGglUniform2fvProc        )(      GLint,        
                                                                 GLsizei,
                                                           const GLfloat *);
typedef void  (OSG_APIENTRY * OSGglUniform3fvProc        )(      GLint,        
                                                                 GLsizei,
                                                           const GLfloat *);
typedef void  (OSG_APIENTRY * OSGglUniform4fvProc        )(      GLint,        
                                                                 GLsizei,
                                                           const GLfloat *);


typedef void  (OSG_APIENTRY * OSGglUniformMatrix2fvProc  )(      GLint,
                                                                 GLsizei, 
                                                                 GLboolean, 
                                                           const GLfloat   *);
typedef void  (OSG_APIENTRY * OSGglUniformMatrix3fvProc  )(      GLint,
                                                                 GLsizei, 
                                                                 GLboolean, 
                                                           const GLfloat   *);
typedef void  (OSG_APIENTRY * OSGglUniformMatrix4fvProc  )(      GLint,
                                                                 GLsizei, 
                                                                 GLboolean, 
                                                           const GLfloat   *);

typedef void  (OSG_APIENTRY * 
                          OSGglProgramParameteriEXTProc  )(      GLuint, 
                                                                 GLenum, 
                                                                 GLint      );

typedef void  (OSG_APIENTRY * OSGglBindAttribLocationProc)(      GLuint, 
                                                                 GLuint, 
                                                           const GLchar *   );

/*! \}                                                                       */
#endif
/*---------------------------------------------------------------------------*/
/*! \name FrameBuffer Objects                                                */
/*! \ingroup GrpBaseBaseGLFunc                                               */
/*! \{                                                                       */

typedef void (OSG_APIENTRY *OSGglGenerateMipmapEXTProc)(GLenum);

/*! \}                                                                       */
/*---------------------------------------------------------------------------*/
/*! \name FrameBuffer Config                                                 */
/*! \ingroup GrpBaseBaseGLFunc                                               */
/*! \{                                                                       */

#ifdef OSG_USE_GLX
typedef GLXFBConfig *(* OSGglxChooseFBConfigProc)(      Display *dpy, 
                                                        int      screen, 
                                                  const int     *attrib_list, 
                                                        int     *nelements);

typedef GLXContext (*OSGglxCreateContextAttribsARBProc)(
          Display     *dpy,
          GLXFBConfig  config,
          GLXContext   share_context,
          Bool         direct,
    const int         *attrib_list);
#endif

/*! \}                                                                       */
/*---------------------------------------------------------------------------*/
/*! \name Clamp Color                                                        */
/*! \ingroup GrpBaseBaseGLFunc                                               */
/*! \{                                                                       */

typedef void (OSG_APIENTRY *OSGglClampColorARBProc)(GLenum, GLenum);

/*! \}                                                                       */
/*---------------------------------------------------------------------------*/
/*! \name Texture 3D                                                         */
/*! \ingroup GrpBaseBaseGLFunc                                               */
/*! \{                                                                       */

typedef void (OSG_APIENTRY *OSGglTexImage3DProc)(
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

typedef void (OSG_APIENTRY*OSGglTexSubImage3DProc)(
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

typedef void (OSG_APIENTRY *OSGglCompressedTexImage1DProc)(
          GLenum    target,
          GLint     level,
          GLenum    internalformat,
          GLsizei   width,
          GLint     border,
          GLsizei   imageSize,
    const GLvoid   *pixels);

typedef void (OSG_APIENTRY *OSGglCompressedTexSubImage1DProc)(
          GLenum   target,
          GLint    level,
          GLint    xoffset,
          GLsizei  width,
          GLenum   format,
          GLsizei  imageSize,
    const GLvoid  *pixels);


typedef void (OSG_APIENTRY *OSGglCompressedTexImage2DProc)(
          GLenum   target,
          GLint    level,
          GLenum   internalformat,
          GLsizei  width,
          GLsizei  height,
          GLint    border,
          GLsizei  imageSize,
    const GLvoid  *pixels);

typedef void (OSG_APIENTRY *OSGglCompressedTexSubImage2DProc)(
          GLenum   target,
          GLint    level,
          GLint    xoffset,
          GLint    yoffset,
          GLsizei  width,
          GLsizei  height,
          GLenum   format,
          GLsizei  imageSize,
    const GLvoid  *pixels);


typedef void (OSG_APIENTRY *OSGglCompressedTexImage3DProc)(
          GLenum   target,
          GLint    level,
          GLenum   internalformat,
          GLsizei  width,
          GLsizei  height,
          GLsizei  depth,
          GLint    border,
          GLsizei  imageSize,
    const GLvoid  *pixels);

typedef void (OSG_APIENTRY *OSGglCompressedTexSubImage3DProc)(
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

typedef void       (OSG_APIENTRY *OSGglBindBufferProc              )(      
          GLenum         target,
          GLuint         buffer);

typedef void       (OSG_APIENTRY *OSGglBufferDataProc              )(      
          GLenum         target, 
          GLintptrARB    size, 
    const void          *data,
          GLenum         usage);

typedef void       (OSG_APIENTRY *OSGglBufferSubDataProc           )(      
          GLenum         target,
          GLintptrARB    offset,
          GLsizeiptrARB  size,
    const void          *data);

typedef void       (OSG_APIENTRY *OSGglGenBuffersProc              )(      
          GLsizei        n, 
          GLuint        *bufs);

typedef void       (OSG_APIENTRY *OSGglDeleteBuffersProc           )(      
          GLsizei        n, 
    const GLuint        *bufs);

typedef void      *(OSG_APIENTRY *OSGglMapBufferProc               )(
          GLenum         target, 
          GLenum         access);

typedef GLboolean  (OSG_APIENTRY *OSGglUnmapBufferProc             )(
          GLenum         target);

typedef void       (OSG_APIENTRY *OSGglEnableVertexAttribArrayProc )(
          GLuint         index);

typedef void       (OSG_APIENTRY *OSGglDisableVertexAttribArrayProc)(
          GLuint         index);

typedef void       (OSG_APIENTRY *OSGglClientActiveTextureProc     )(
          GLenum         type );

typedef void       (OSG_APIENTRY *OSGglActiveTextureProc           )(
          GLenum         texture);

typedef void       (OSG_APIENTRY *OSGglVertexAttribPointerProc     )(
          GLuint         index, 
          GLint          size, 
          GLenum         type, 
          GLboolean      normalized,
          GLsizei        stride, 
    const GLvoid        *pointer);

typedef void       (OSG_APIENTRY *OSGglSecondaryColorPointerProc   )(
          GLint          size,
          GLenum         type,
          GLsizei        stride,
    const GLvoid        *pointer);

typedef void       (OSG_APIENTRY *OSGglGetBufferSubDataProc        )(
          GLenum, 
          GLintptr, 
          GLsizeiptr, 
          GLvoid *);

typedef void       (OSG_APIENTRY *OSGglGetBufferParameterivProc    )(
          GLenum, 
          GLenum, 
          GLint *);
typedef void       (OSG_APIENTRY *OSGglGetBufferPointervProc       )(
          GLenum, 
          GLenum, 
          GLvoid* *);

typedef GLboolean  (OSG_APIENTRY *OSGglIsBufferProc                )(
          GLuint);

/*! \}                                                                       */
/*---------------------------------------------------------------------------*/
/*! \name Draw Elements                                                      */
/*! \ingroup GrpBaseBaseGLFunc                                               */
/*! \{                                                                       */

typedef void (OSG_APIENTRY *OSGglLockArraysProc       )(      GLint, 
                                                              GLsizei);
typedef void (OSG_APIENTRY *OSGglUnlockArraysProc     )(      void);
typedef void (OSG_APIENTRY *OSGglDrawRangeElementsProc)(      GLenum, 
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

typedef void (OSG_APIENTRY *OSGglMultiTexCoord3fvProc)(GLenum, const GLfloat *);

/*! \}                                                                       */
/*---------------------------------------------------------------------------*/
/*! \name TextureBuffers                                                     */
/*! \ingroup GrpBaseBaseGLFunc                                               */
/*! \{                                                                       */

typedef void (OSG_APIENTRY *OSGglFramebufferTexture1DProc)(GLenum target, 
                                                           GLenum attachment, 
                                                           GLenum textarget, 
                                                           GLuint texture, 
                                                           GLint  level     );

typedef void (OSG_APIENTRY *OSGglFramebufferTexture2DProc)(GLenum target, 
                                                           GLenum attachment, 
                                                           GLenum textarget, 
                                                           GLuint texture, 
                                                           GLint  level     );

typedef void (OSG_APIENTRY *OSGglFramebufferTexture3DProc)(GLenum target, 
                                                           GLenum attachment, 
                                                           GLenum textarget, 
                                                           GLuint texture, 
                                                           GLint  level, 
                                                           GLint  zoffset   );

typedef void   (OSG_APIENTRY *OSGglGenerateMipmapProc    )(GLenum target    );

/*! \}                                                                       */
/*---------------------------------------------------------------------------*/
/*! \name RenderBuffers                                                      */
/*! \ingroup GrpBaseBaseGLFunc                                               */
/*! \{                                                                       */

typedef void (OSG_APIENTRY *OSGglGenRenderbuffersProc       )(
    GLsizei  n, 
    GLuint  *renderbuffers);

typedef void (OSG_APIENTRY *OSGglBindRenderbufferProc       )(
    GLenum   target, 
    GLuint   renderbuffer);

typedef void (OSG_APIENTRY *OSGglRenderbufferStorageProc    )(
    GLenum   target, 
    GLenum   internalformat, 
    GLsizei  width, 
    GLsizei  height);

typedef void (OSG_APIENTRY *OSGglDeleteRenderbuffersProc    )(
          GLsizei  n, 
    const GLuint  *renderbuffers);

/*! \}                                                                       */
/*---------------------------------------------------------------------------*/
/*! \name FrameBufferObjects                                                 */
/*! \ingroup GrpBaseBaseGLFunc                                               */
/*! \{                                                                       */

typedef void   (OSG_APIENTRY *OSGglGenFramebuffersProc        )(
          GLsizei  n, 
          GLuint  *framebuffers);

typedef void   (OSG_APIENTRY *OSGglDeleteFramebuffersProc     )(
          GLsizei  n, 
    const GLuint  *framebuffers);

typedef void   (OSG_APIENTRY *OSGglBindFramebufferProc        )(
          GLenum   target, 
          GLuint   framebuffer);

typedef void   (OSG_APIENTRY *OSGglFramebufferRenderbufferProc)(
          GLenum   target, 
          GLenum   attachment, 
          GLenum   renderbuffertarget, 
          GLuint   renderbuffer);

typedef void   (OSG_APIENTRY *OSGglDrawBuffersProc           )(
          GLsizei  n, 
    const GLenum  *buffers);

typedef GLenum (OSG_APIENTRY *OSGglCheckFramebufferStatusProc)(
          GLenum   target );

/*! \}                                                                       */
/*---------------------------------------------------------------------------*/
/*! \name Point Sprites                                                      */
/*! \ingroup GrpBaseBaseGLFunc                                               */
/*! \{                                                                       */

typedef void   (OSG_APIENTRY *OSGglPointParameterfProc       )(
          GLenum  pname,
          GLfloat param );

typedef void   (OSG_APIENTRY *OSGglPointParameterfvProc       )(
          GLenum   pname,
    const GLfloat *params);

/*! \}                                                                       */
/*---------------------------------------------------------------------------*/
/*! \name Queries                                                            */
/*! \ingroup GrpBaseBaseGLFunc                                               */
/*! \{                                                                       */

typedef void      (OSG_APIENTRY *OSGglGenQueriesProc       )(      GLsizei, 
                                                                   GLuint *);
typedef void      (OSG_APIENTRY *OSGglDeleteQueriesProc    )(      GLsizei, 
                                                             const GLuint *);
typedef GLboolean (OSG_APIENTRY *OSGglIsQueryProc          )(      GLuint);
typedef void      (OSG_APIENTRY *OSGglBeginQueryProc       )(      GLenum, 
                                                                   GLuint);
typedef void      (OSG_APIENTRY *OSGglEndQueryProc         )(      GLenum);
typedef void      (OSG_APIENTRY *OSGglGetQueryivProc       )(      GLenum, 
                                                                   GLenum, 
                                                                   GLint *);
typedef void      (OSG_APIENTRY *OSGglGetQueryObjectivProc )(      GLuint, 
                                                                   GLenum, 
                                                                   GLint *);
typedef void      (OSG_APIENTRY *OSGglGetQueryObjectuivProc)(      GLuint, 
                                                                   GLenum, 
                                                                   GLuint *);

typedef const GLubyte * (OSG_APIENTRY *OSGglGetStringiProc)(GLenum name, 
                                                            GLuint index);

/*! \}                                                                       */
/*---------------------------------------------------------------------------*/
/*! \name Blending                                                           */
/*! \ingroup GrpBaseBaseGLFunc                                               */
/*! \{                                                                       */

typedef void (OSG_APIENTRY *OSGglBlendColorProc       )(GLclampf, 
                                                        GLclampf, 
                                                        GLclampf, 
                                                        GLclampf);
typedef void (OSG_APIENTRY *OSGglBlendEquationProc    )(GLenum);
typedef void (OSG_APIENTRY *OSGglBlendFuncSeparateProc)(GLenum, 
                                                        GLenum, 
                                                        GLenum, 
                                                        GLenum);

/*! \}                                                                       */
/*---------------------------------------------------------------------------*/
/*! \name ARB Program                                                        */
/*! \ingroup GrpBaseBaseGLFunc                                               */
/*! \{                                                                       */

typedef void (OSG_APIENTRY *OSGglProgramStringARBProc           )(
          GLenum, 
          GLenum, 
          GLsizei, 
    const GLvoid *);

typedef void (OSG_APIENTRY *OSGglBindProgramARBProc             )(
          GLenum, 
          GLuint);

typedef void (OSG_APIENTRY *OSGglDeleteProgramsARBProc          )(
          GLsizei, 
    const GLuint *);

typedef void (OSG_APIENTRY *OSGglGenProgramsARBProc             )(
          GLsizei, 
          GLuint *);

#ifndef OSG_OGL_NO_DOUBLE
typedef void (OSG_APIENTRY *OSGglProgramEnvParameter4dARBProc   )(
          GLenum, 
          GLuint, 
          GLdouble, 
          GLdouble, 
          GLdouble, 
          GLdouble);

typedef void (OSG_APIENTRY *OSGglProgramEnvParameter4dvARBProc  )(
          GLenum, 
          GLuint, 
    const GLdouble *);
#endif

typedef void (OSG_APIENTRY *OSGglProgramEnvParameter4fARBProc   )(
          GLenum, 
          GLuint, 
          GLfloat, 
          GLfloat, 
          GLfloat, 
          GLfloat);

typedef void (OSG_APIENTRY *OSGglProgramEnvParameter4fvARBProc  )(
          GLenum, 
          GLuint, 
    const GLfloat *);

#ifndef OSG_OGL_NO_DOUBLE
typedef void (OSG_APIENTRY *OSGglProgramLocalParameter4dARBProc )(
          GLenum, 
          GLuint, 
          GLdouble, 
          GLdouble, 
          GLdouble, 
          GLdouble);

typedef void (OSG_APIENTRY *OSGglProgramLocalParameter4dvARBProc)(
          GLenum, 
          GLuint, 
    const GLdouble *);
#endif

typedef void (OSG_APIENTRY *OSGglProgramLocalParameter4fARBProc )(
          GLenum, 
          GLuint, 
          GLfloat, 
          GLfloat, 
          GLfloat, 
          GLfloat);

typedef void (OSG_APIENTRY *OSGglProgramLocalParameter4fvARBProc)(
          GLenum, 
          GLuint, 
    const GLfloat *);

typedef void (OSG_APIENTRY *OSGglGetProgramivARBProc            )(
          GLenum, 
          GLenum, 
          GLint *);

/*! \}                                                                       */
/*---------------------------------------------------------------------------*/
/*! \name Register Combiner                                                  */
/*! \ingroup GrpBaseBaseGLFunc                                               */
/*! \{                                                                       */

typedef void (OSG_APIENTRY *OSGglCombinerParameterfvNVProc             )(
          GLenum, 
    const GLfloat *);

typedef void (OSG_APIENTRY *OSGglCombinerParameterfNVProc              )(
    GLenum, 
    GLfloat);

typedef void (OSG_APIENTRY *OSGglCombinerParameterivNVProc             )(
          GLenum, 
    const GLint *);

typedef void (OSG_APIENTRY *OSGglCombinerParameteriNVProc              )(
    GLenum, 
    GLint);

typedef void (OSG_APIENTRY *OSGglCombinerInputNVProc                   )(
    GLenum, 
    GLenum, 
    GLenum, 
    GLenum, 
    GLenum, 
    GLenum);

typedef void (OSG_APIENTRY *OSGglCombinerOutputNVProc                  )(
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

typedef void (OSG_APIENTRY *OSGglFinalCombinerInputNVProc              )(
    GLenum, 
    GLenum, 
    GLenum, 
    GLenum);
typedef void (OSG_APIENTRY *OSGglGetCombinerInputParameterfvNVProc     )(
    GLenum, 
    GLenum, 
    GLenum, 
    GLenum, 
    GLfloat *);

typedef void (OSG_APIENTRY *OSGglGetCombinerInputParameterivNVProc     )(
    GLenum, 
    GLenum, 
    GLenum, 
    GLenum, 
    GLint *);

typedef void (OSG_APIENTRY *OSGglGetCombinerOutputParameterfvNVProc    )(
    GLenum, 
    GLenum, 
    GLenum, 
    GLfloat *);

typedef void (OSG_APIENTRY *OSGglGetCombinerOutputParameterivNVProc    )(
    GLenum, 
    GLenum, 
    GLenum, 
    GLint *);

typedef void (OSG_APIENTRY *OSGglGetFinalCombinerInputParameterfvNVProc)(
    GLenum, 
    GLenum, 
    GLfloat *);

typedef void (OSG_APIENTRY *OSGglGetFinalCombinerInputParameterivNVProc)(
    GLenum, 
    GLenum, 
    GLint *);

typedef void (OSG_APIENTRY *OSGglCombinerStageParameterfvNVProc        )(
          GLenum, 
          GLenum, 
    const GLfloat *);

typedef void (OSG_APIENTRY *OSGglGetCombinerStageParameterfvNVProc     )(
    GLenum, 
    GLenum, 
    GLfloat *);

/*! \}                                                                       */
/*---------------------------------------------------------------------------*/
/*! \name GL Function Helper                                                 */
/*! \ingroup GrpBaseBaseGLFunc                                               */
/*! \{                                                                       */

#ifdef OSG_DEBUG

# define OSGGETGLFUNC_W(OGLFUNC, FUNCVAR, FUNCID)                       \
    OSG::OSG##OGLFUNC##Proc FUNCVAR =                                   \
        reinterpret_cast<OSG::OSG##OGLFUNC##Proc>(                      \
            pEnv->getWindow()->getFunction(FUNCID));                    \
                                                                        \
    if(FUNCVAR == NULL)                                                 \
        FFATAL(("Func %s of type %s NULL, window %p\n",                 \
                #FUNCVAR, #OGLFUNC, pEnv->getWindow()))                 \

# define OSGGETGLFUNCBYID_W(OGLFUNC, FUNCVAR, FUNCID, WINDOW)           \
    OSG::OSG##OGLFUNC##Proc FUNCVAR =                                   \
        reinterpret_cast< OSG::OSG##OGLFUNC##Proc >(                    \
            (WINDOW)->getFunction(FUNCID));                             \
                                                                        \
    if(FUNCVAR == NULL)                                                 \
        FFATAL(("Func %s of type %s NULL, window %p\n",                 \
                #FUNCVAR, #OGLFUNC, (WINDOW)))                          \

# define OSGGETGLFUNCBYNAME_W(OGLFUNC, FUNCVAR, FUNCNAME, WINDOW)       \
    OSG::OSG##OGLFUNC##Proc FUNCVAR =                                   \
        reinterpret_cast<OSG::OSG##OGLFUNC##Proc>(                      \
            (WINDOW)->getFunctionByName(FUNCNAME));                     \
                                                                        \
    if(FUNCVAR == NULL)                                                 \
        FFATAL(("Func %s of type %s NULL, window %p\n",                 \
                #FUNCVAR, #OGLFUNC, (WINDOW)))                          \

#else

# define OSGGETGLFUNC_W(OGLFUNC, FUNCVAR, FUNCID)                       \
    OSG::OSG##OGLFUNC##Proc FUNCVAR =                                   \
        reinterpret_cast<OSG::OSG##OGLFUNC##Proc>(                      \
            pEnv->getWindow()->getFunction(FUNCID));

# define OSGGETGLFUNCBYID_W(OGLFUNC, FUNCVAR, FUNCID, WINDOW)           \
    OSG::OSG##OGLFUNC##Proc FUNCVAR =                                   \
        reinterpret_cast<OSG::OSG##OGLFUNC##Proc>(                      \
            (WINDOW)->getFunction(FUNCID));

# define OSGGETGLFUNCBYNAME_W(OGLFUNC, FUNCVAR, FUNCNAME, WINDOW)       \
    OSG::OSG##OGLFUNC##Proc FUNCVAR =                                   \
        reinterpret_cast<OSG::OSG##OGLFUNC##Proc>(                      \
            (WINDOW)->getFunctionByName(FUNCNAME));

#endif

#define OSGGETGLFUNC_P(OGLFUNC, FUNCVAR, FUNCID)                        \
    OSG::OSG##OGLFUNC##Proc FUNCVAR = OGLFUNC;

#define OSGGETGLFUNCBYID_P(OGLFUNC, FUNCVAR, FUNCID, WINDOW)            \
    OSG::OSG##OGLFUNC##Proc FUNCVAR = OGLFUNC;

#define OSGGETGLFUNCBYNAME_P(OGLFUNC, FUNCVAR, FUNCNAME, WINDOW)        \
    OSG::OSG##OGLFUNC##Proc FUNCVAR = OGLFUNC;
       


#ifdef OSG_USE_OGL3_PROTOS
# define OSGGETGLFUNC_GL3(FUNCTYPE, FUNCVAR, FUNCID)                     \
    OSGGETGLFUNC_P(FUNCTYPE, FUNCVAR, FUNCID)

# define OSGGETGLFUNCBYID_GL3(FUNCTYPE, FUNCVAR, FUNCID, WINDOW)         \
    OSGGETGLFUNCBYID_P(FUNCTYPE, FUNCVAR, FUNCID, WINDOW)

# define OSGGETGLFUNCBYNAME_GL3(FUNCTYPE, FUNCVAR, FUNCNAME, WINDOW)     \
    OSGGETGLFUNCBYNAME_P(FUNCTYPE, FUNCVAR, FUNCNAME, WINDOW)
#endif //OSG_USE_OGL3_PROTOS

#ifdef OSG_USE_OGL4_PROTOS
# define OSGGETGLFUNC_GL4(FUNCTYPE, FUNCVAR, FUNCID)                     \
    OSGGETGLFUNC_P(FUNCTYPE, FUNCVAR, FUNCID)

# define OSGGETGLFUNCBYID_GL4(FUNCTYPE, FUNCVAR, FUNCID, WINDOW)         \
    OSGGETGLFUNCBYID_P(FUNCTYPE, FUNCVAR, FUNCID, WINDOW)

# define OSGGETGLFUNCBYNAME_GL4(FUNCTYPE, FUNCVAR, FUNCNAME, WINDOW)     \
    OSGGETGLFUNCBYNAME_P(FUNCTYPE, FUNCVAR, FUNCNAME, WINDOW)
#endif // OSG_USE_OGL4_PROTOS


#if defined(OSG_USE_OGLES_PROTOS) || defined(OSG_USE_OGL3_PROTOS)
# define OSGGETGLFUNC_GL3_ES(FUNCTYPE, FUNCVAR, FUNCID)                  \
    OSGGETGLFUNC_P(FUNCTYPE, FUNCVAR, FUNCID)

# define OSGGETGLFUNCBYID_GL3_ES(FUNCTYPE, FUNCVAR, FUNCID, WINDOW)      \
    OSGGETGLFUNCBYID_P(FUNCTYPE, FUNCVAR, FUNCID, WINDOW)

# define OSGGETGLFUNCBYNAME_GL3_ES(FUNCTYPE, FUNCVAR, FUNCNAME, WINDOW)  \
    OSGGETGLFUNCBYNAME_P(FUNCTYPE, FUNCVAR, FUNCNAME, WINDOW)
#endif


#if defined(OSG_USE_OGLES_PROTOS) || defined(OSG_USE_OGL4_PROTOS)
# define OSGGETGLFUNC_GL4_ES(FUNCTYPE, FUNCVAR, FUNCID)                  \
    OSGGETGLFUNC_P(FUNCTYPE, FUNCVAR, FUNCID)

# define OSGGETGLFUNCBYID_GL4_ES(FUNCTYPE, FUNCVAR, FUNCID, WINDOW)      \
    OSGGETGLFUNCBYID_P(FUNCTYPE, FUNCVAR, FUNCID, WINDOW)

# define OSGGETGLFUNCBYNAME_GL4_ES(FUNCTYPE, FUNCVAR, FUNCNAME, WINDOW)  \
    OSGGETGLFUNCBYNAME_P(FUNCTYPE, FUNCVAR, FUNCNAME, WINDOW)
#endif

// OpenGL 3 Protos
#ifndef OSGGETGLFUNC_GL3
# define OSGGETGLFUNC_GL3(FUNCTYPE, FUNCVAR, FUNCID)                     \
    OSGGETGLFUNC_W(FUNCTYPE, FUNCVAR, FUNCID)

# define OSGGETGLFUNCBYID_GL3(FUNCTYPE, FUNCVAR, FUNCID, WINDOW)         \
    OSGGETGLFUNCBYID_W(FUNCTYPE, FUNCVAR, FUNCID, WINDOW)

# define OSGGETGLFUNCBYNAME_GL3(FUNCTYPE, FUNCVAR, FUNCNAME, WINDOW)     \
    OSGGETGLFUNCBYNAME_W(FUNCTYPE, FUNCVAR, FUNCNAME, WINDOW)
#endif //OSGGETGLFUNC_GL3


// OpenGL 3 and ES Protos
#ifndef OSGGETGLFUNC_GL3_ES
# define OSGGETGLFUNC_GL3_ES(FUNCTYPE, FUNCVAR, FUNCID)                  \
    OSGGETGLFUNC_W(FUNCTYPE, FUNCVAR, FUNCID)

# define OSGGETGLFUNCBYID_GL3_ES(FUNCTYPE, FUNCVAR, FUNCID, WINDOW)      \
    OSGGETGLFUNCBYID_W(FUNCTYPE, FUNCVAR, FUNCID, WINDOW)

# define OSGGETGLFUNCBYNAME_GL3_ES(FUNCTYPE, FUNCVAR, FUNCNAME, WINDOW)  \
    OSGGETGLFUNCBYNAME_W(FUNCTYPE, FUNCVAR, FUNCNAME, WINDOW)
#endif //OSGGETGLFUNC_GL3_ES


// OpenGL 4 Protos
#ifndef OSGGETGLFUNC_GL4
# define OSGGETGLFUNC_GL4(FUNCTYPE, FUNCVAR, FUNCID)                     \
    OSGGETGLFUNC_W(FUNCTYPE, FUNCVAR, FUNCID)

# define OSGGETGLFUNCBYID_GL4(FUNCTYPE, FUNCVAR, FUNCID, WINDOW)         \
    OSGGETGLFUNCBYID_W(FUNCTYPE, FUNCVAR, FUNCID, WINDOW)

# define OSGGETGLFUNCBYNAME_GL4(FUNCTYPE, FUNCVAR, FUNCNAME, WINDOW)     \
    OSGGETGLFUNCBYNAME_W(FUNCTYPE, FUNCVAR, FUNCNAME, WINDOW)
#endif //SGGETGLFUNC_GL4


// OpenGL 4 and ES Protos
#ifndef OSGGETGLFUNC_GL4_ES
# define OSGGETGLFUNC_GL4_ES(FUNCTYPE, FUNCVAR, FUNCID)                  \
    OSGGETGLFUNC_W(FUNCTYPE, FUNCVAR, FUNCID)

# define OSGGETGLFUNCBYID_GL4_ES(FUNCTYPE, FUNCVAR, FUNCID, WINDOW)      \
    OSGGETGLFUNCBYID_W(FUNCTYPE, FUNCVAR, FUNCID, WINDOW)

# define OSGGETGLFUNCBYNAME_GL4_ES(FUNCTYPE, FUNCVAR, FUNCNAME, WINDOW)  \
    OSGGETGLFUNCBYNAME_W(FUNCTYPE, FUNCVAR, FUNCNAME, WINDOW)
#endif //OSGGETGLFUNC_GL4_ES


// OpenGL Ext

#define OSGGETGLFUNC_EXT(FUNCTYPE, FUNCVAR, FUNCID)                      \
    OSGGETGLFUNC_W(FUNCTYPE, FUNCVAR, FUNCID)

#define OSGGETGLFUNCBYID_EXT(FUNCTYPE, FUNCVAR, FUNCID, WINDOW)          \
    OSGGETGLFUNCBYID_W(FUNCTYPE, FUNCVAR, FUNCID, WINDOW)

#define OSGGETGLFUNCBYNAME_EXT(FUNCTYPE, FUNCVAR, FUNCNAME, WINDOW)      \
    OSGGETGLFUNCBYNAME_W(FUNCTYPE, FUNCVAR, FUNCNAME, WINDOW)




/*  \}                                                                       */
/*---------------------------------------------------------------------------*/


OSG_END_NAMESPACE

#endif /* _OSGGLFUNCPROTOS_H_ */
