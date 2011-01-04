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

typedef GLXContext (*OSGglxCreateContextAttribsARB)(
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

typedef void (OSG_APIENTRY *OSGglTexImage3D)(
          GLenum  target,
          GLint   level,
          GLenum  internalformat,
          GLsizei width,
          GLsizei height,
          GLsizei depth,
          GLint   border,
          GLenum  format,
          GLenum  type,
    const GLvoid *pixels);

typedef void (OSG_APIENTRY*OSGglTexSubImage3D)(
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

typedef void (OSG_APIENTRY *OSGglCompressedTexImage1D)(
          GLenum    target,
          GLint     level,
          GLenum    internalformat,
          GLsizei   width,
          GLint     border,
          GLsizei   imageSize,
    const GLvoid   *pixels);

typedef void (OSG_APIENTRY *OSGglCompressedTexSubImage1D)(
          GLenum   target,
          GLint    level,
          GLint    xoffset,
          GLsizei  width,
          GLenum   format,
          GLsizei  imageSize,
    const GLvoid  *pixels);


typedef void (OSG_APIENTRY *OSGglCompressedTexImage2D)(
          GLenum   target,
          GLint    level,
          GLenum   internalformat,
          GLsizei  width,
          GLsizei  height,
          GLint    border,
          GLsizei  imageSize,
    const GLvoid  *pixels);

typedef void (OSG_APIENTRY *OSGglCompressedTexSubImage2D)(
          GLenum   target,
          GLint    level,
          GLint    xoffset,
          GLint    yoffset,
          GLsizei  width,
          GLsizei  height,
          GLenum   format,
          GLsizei  imageSize,
    const GLvoid  *pixels);


typedef void (OSG_APIENTRY *OSGglCompressedTexImage3D)(
          GLenum   target,
          GLint    level,
          GLenum   internalformat,
          GLsizei  width,
          GLsizei  height,
          GLsizei  depth,
          GLint    border,
          GLsizei  imageSize,
    const GLvoid  *pixels);

typedef void (OSG_APIENTRY *OSGglCompressedTexSubImage3D)(
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

typedef void (OSG_APIENTRY *OSGglBindBufferARB   )(      GLenum         target, 
                                                         GLuint         buffer);

typedef void (OSG_APIENTRY *OSGglBufferDataARB   )(      GLenum         target, 
                                                         long           size, 
                                                   const void          *data,
                                                         GLenum         usage);
typedef void (OSG_APIENTRY *OSGglBufferSubDataARB)(      GLenum         target, 
                                                         GLintptrARB    offset, 
                                                         GLsizeiptrARB  size,
                                                   const void          *data);

typedef void (OSG_APIENTRY *OSGglGenBuffersARB   )(      GLsizei        n, 
                                                         GLuint        *bufs);

typedef void (OSG_APIENTRY *OSGglDeleteBuffersARB)(      GLsizei        n, 
                                                   const GLuint        *bufs);

typedef void *(OSG_APIENTRY * OSGglMapBufferARB)(GLenum target, GLenum access);
typedef GLboolean (OSG_APIENTRY * OSGglUnmapBufferARB)(GLenum target);

typedef void (OSG_APIENTRY *OSGglEnableVertexAttribArrayARB )(GLuint index);
typedef void (OSG_APIENTRY *OSGglDisableVertexAttribArrayARB)(GLuint index);
typedef void (OSG_APIENTRY *OSGglClientActiveTextureARB     )(GLenum type );

typedef void (OSG_APIENTRY *OSGglVertexAttribPointerARB)(
          GLuint     index, 
          GLint      size, 
          GLenum     type, 
          GLboolean  normalized,
          GLsizei    stride, 
    const GLvoid    *pointer);

typedef void (OSG_APIENTRY *OSGglSecondaryColorPointerEXT)(
          GLint    size,
          GLenum   type,
          GLsizei  stride,
    const GLvoid  *pointer);

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
/*! \name GL Function Helper                                                 */
/*! \ingroup GrpBaseBaseGLFunc                                               */
/*! \{                                                                       */

#ifdef OSG_DEBUG

#define OSGGETGLFUNC(FUNCTYPE, FUNCVAR, FUNCID)                         \
    FUNCTYPE FUNCVAR =                                                  \
        reinterpret_cast<FUNCTYPE>(                                     \
            pEnv->getWindow()->getFunction(FUNCID));                    \
                                                                        \
    if(FUNCVAR == NULL)                                                 \
        FFATAL(("Func %s of type %s NULL\n", #FUNCVAR, #FUNCTYPE))

#define OSGGETGLFUNCBYID(FUNCTYPE, FUNCVAR, FUNCID, WINDOW)             \
    FUNCTYPE FUNCVAR =                                                  \
        reinterpret_cast< FUNCTYPE >(                                   \
            (WINDOW)->getFunction(FUNCID));                             \
                                                                        \
    if(FUNCVAR == NULL)                                                 \
        FFATAL(("Func %s of type %s NULL\n", #FUNCVAR, #FUNCTYPE))

#define OSGGETGLFUNCBYNAME(FUNCTYPE, FUNCVAR, FUNCNAME, WINDOW)         \
    FUNCTYPE FUNCVAR =                                                  \
        reinterpret_cast<FUNCTYPE>(                                     \
            (WINDOW)->getFunctionByName(FUNCNAME));                     \
                                                                        \
    if(FUNCVAR == NULL)                                                 \
        FFATAL(("Func %s of type %s NULL\n", #FUNCVAR, #FUNCTYPE))
        
#else

#define OSGGETGLFUNC(FUNCTYPE, FUNCVAR, FUNCID)                         \
    FUNCTYPE FUNCVAR =                                                  \
        reinterpret_cast<FUNCTYPE>(                                     \
            pEnv->getWindow()->getFunction(FUNCID))

#define OSGGETGLFUNCBYID(FUNCTYPE, FUNCVAR, FUNCID, WINDOW)             \
    FUNCTYPE FUNCVAR =                                                  \
        reinterpret_cast< FUNCTYPE >(                                   \
            (WINDOW)->getFunction(FUNCID));

#define OSGGETGLFUNCBYNAME(FUNCTYPE, FUNCVAR, FUNCNAME, WINDOW)         \
 FUNCTYPE FUNCVAR =                                                     \
    reinterpret_cast<FUNCTYPE>(                                         \
        (WINDOW)->getFunctionByName(FUNCNAME));

#endif

/*  \}                                                                       */
/*---------------------------------------------------------------------------*/


OSG_END_NAMESPACE

#endif /* _OSGGLFUNCPROTOS_H_ */
