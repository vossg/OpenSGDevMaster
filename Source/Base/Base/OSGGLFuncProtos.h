/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             CopyrightProc )(C) 2000-2003 by the OpenSG Forum                   *
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

#ifdef GL_VERSION_1_2
typedef void (OSG_APIENTRY * osgGlDrawRangeElementsProc )(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void *indices);
typedef void (OSG_APIENTRY * osgGlTexImage3DProc )(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void *pixels);
typedef void (OSG_APIENTRY * osgGlTexSubImage3DProc )(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *pixels);
typedef void (OSG_APIENTRY * osgGlCopyTexSubImage3DProc )(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);
#endif /* GL_VERSION_1_2 */

#ifdef GL_VERSION_1_3
typedef void (OSG_APIENTRY * osgGlActiveTextureProc )(GLenum texture);
typedef void (OSG_APIENTRY * osgGlSampleCoverageProc )(GLfloat value, GLboolean invert);
typedef void (OSG_APIENTRY * osgGlCompressedTexImage3DProc )(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void *data);
typedef void (OSG_APIENTRY * osgGlCompressedTexImage2DProc )(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void *data);
typedef void (OSG_APIENTRY * osgGlCompressedTexImage1DProc )(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const void *data);
typedef void (OSG_APIENTRY * osgGlCompressedTexSubImage3DProc )(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void *data);
typedef void (OSG_APIENTRY * osgGlCompressedTexSubImage2DProc )(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void *data);
typedef void (OSG_APIENTRY * osgGlCompressedTexSubImage1DProc )(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void *data);
typedef void (OSG_APIENTRY * osgGlGetCompressedTexImageProc )(GLenum target, GLint level, void *img);
typedef void (OSG_APIENTRY * osgGlClientActiveTextureProc )(GLenum texture);
typedef void (OSG_APIENTRY * osgGlMultiTexCoord1dProc )(GLenum target, GLdouble s);
typedef void (OSG_APIENTRY * osgGlMultiTexCoord1dvProc )(GLenum target, const GLdouble *v);
typedef void (OSG_APIENTRY * osgGlMultiTexCoord1fProc )(GLenum target, GLfloat s);
typedef void (OSG_APIENTRY * osgGlMultiTexCoord1fvProc )(GLenum target, const GLfloat *v);
typedef void (OSG_APIENTRY * osgGlMultiTexCoord1iProc )(GLenum target, GLint s);
typedef void (OSG_APIENTRY * osgGlMultiTexCoord1ivProc )(GLenum target, const GLint *v);
typedef void (OSG_APIENTRY * osgGlMultiTexCoord1sProc )(GLenum target, GLshort s);
typedef void (OSG_APIENTRY * osgGlMultiTexCoord1svProc )(GLenum target, const GLshort *v);
typedef void (OSG_APIENTRY * osgGlMultiTexCoord2dProc )(GLenum target, GLdouble s, GLdouble t);
typedef void (OSG_APIENTRY * osgGlMultiTexCoord2dvProc )(GLenum target, const GLdouble *v);
typedef void (OSG_APIENTRY * osgGlMultiTexCoord2fProc )(GLenum target, GLfloat s, GLfloat t);
typedef void (OSG_APIENTRY * osgGlMultiTexCoord2fvProc )(GLenum target, const GLfloat *v);
typedef void (OSG_APIENTRY * osgGlMultiTexCoord2iProc )(GLenum target, GLint s, GLint t);
typedef void (OSG_APIENTRY * osgGlMultiTexCoord2ivProc )(GLenum target, const GLint *v);
typedef void (OSG_APIENTRY * osgGlMultiTexCoord2sProc )(GLenum target, GLshort s, GLshort t);
typedef void (OSG_APIENTRY * osgGlMultiTexCoord2svProc )(GLenum target, const GLshort *v);
typedef void (OSG_APIENTRY * osgGlMultiTexCoord3dProc )(GLenum target, GLdouble s, GLdouble t, GLdouble r);
typedef void (OSG_APIENTRY * osgGlMultiTexCoord3dvProc )(GLenum target, const GLdouble *v);
typedef void (OSG_APIENTRY * osgGlMultiTexCoord3fProc )(GLenum target, GLfloat s, GLfloat t, GLfloat r);
typedef void (OSG_APIENTRY * osgGlMultiTexCoord3fvProc )(GLenum target, const GLfloat *v);
typedef void (OSG_APIENTRY * osgGlMultiTexCoord3iProc )(GLenum target, GLint s, GLint t, GLint r);
typedef void (OSG_APIENTRY * osgGlMultiTexCoord3ivProc )(GLenum target, const GLint *v);
typedef void (OSG_APIENTRY * osgGlMultiTexCoord3sProc )(GLenum target, GLshort s, GLshort t, GLshort r);
typedef void (OSG_APIENTRY * osgGlMultiTexCoord3svProc )(GLenum target, const GLshort *v);
typedef void (OSG_APIENTRY * osgGlMultiTexCoord4dProc )(GLenum target, GLdouble s, GLdouble t, GLdouble r, GLdouble q);
typedef void (OSG_APIENTRY * osgGlMultiTexCoord4dvProc )(GLenum target, const GLdouble *v);
typedef void (OSG_APIENTRY * osgGlMultiTexCoord4fProc )(GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q);
typedef void (OSG_APIENTRY * osgGlMultiTexCoord4fvProc )(GLenum target, const GLfloat *v);
typedef void (OSG_APIENTRY * osgGlMultiTexCoord4iProc )(GLenum target, GLint s, GLint t, GLint r, GLint q);
typedef void (OSG_APIENTRY * osgGlMultiTexCoord4ivProc )(GLenum target, const GLint *v);
typedef void (OSG_APIENTRY * osgGlMultiTexCoord4sProc )(GLenum target, GLshort s, GLshort t, GLshort r, GLshort q);
typedef void (OSG_APIENTRY * osgGlMultiTexCoord4svProc )(GLenum target, const GLshort *v);
typedef void (OSG_APIENTRY * osgGlLoadTransposeMatrixfProc )(const GLfloat *m);
typedef void (OSG_APIENTRY * osgGlLoadTransposeMatrixdProc )(const GLdouble *m);
typedef void (OSG_APIENTRY * osgGlMultTransposeMatrixfProc )(const GLfloat *m);
typedef void (OSG_APIENTRY * osgGlMultTransposeMatrixdProc )(const GLdouble *m);
#endif /* GL_VERSION_1_3 */

#ifdef GL_VERSION_1_4
typedef void (OSG_APIENTRY * osgGlBlendFuncSeparateProc )(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);
typedef void (OSG_APIENTRY * osgGlMultiDrawArraysProc )(GLenum mode, const GLint *first, const GLsizei *count, GLsizei drawcount);
typedef void (OSG_APIENTRY * osgGlMultiDrawElementsProc )(GLenum mode, const GLsizei *count, GLenum type, const void *const*indices, GLsizei drawcount);
typedef void (OSG_APIENTRY * osgGlPointParameterfProc )(GLenum pname, GLfloat param);
typedef void (OSG_APIENTRY * osgGlPointParameterfvProc )(GLenum pname, const GLfloat *params);
typedef void (OSG_APIENTRY * osgGlPointParameteriProc )(GLenum pname, GLint param);
typedef void (OSG_APIENTRY * osgGlPointParameterivProc )(GLenum pname, const GLint *params);
typedef void (OSG_APIENTRY * osgGlFogCoordfProc )(GLfloat coord);
typedef void (OSG_APIENTRY * osgGlFogCoordfvProc )(const GLfloat *coord);
typedef void (OSG_APIENTRY * osgGlFogCoorddProc )(GLdouble coord);
typedef void (OSG_APIENTRY * osgGlFogCoorddvProc )(const GLdouble *coord);
typedef void (OSG_APIENTRY * osgGlFogCoordPointerProc )(GLenum type, GLsizei stride, const void *pointer);
typedef void (OSG_APIENTRY * osgGlSecondaryColor3bProc )(GLbyte red, GLbyte green, GLbyte blue);
typedef void (OSG_APIENTRY * osgGlSecondaryColor3bvProc )(const GLbyte *v);
typedef void (OSG_APIENTRY * osgGlSecondaryColor3dProc )(GLdouble red, GLdouble green, GLdouble blue);
typedef void (OSG_APIENTRY * osgGlSecondaryColor3dvProc )(const GLdouble *v);
typedef void (OSG_APIENTRY * osgGlSecondaryColor3fProc )(GLfloat red, GLfloat green, GLfloat blue);
typedef void (OSG_APIENTRY * osgGlSecondaryColor3fvProc )(const GLfloat *v);
typedef void (OSG_APIENTRY * osgGlSecondaryColor3iProc )(GLint red, GLint green, GLint blue);
typedef void (OSG_APIENTRY * osgGlSecondaryColor3ivProc )(const GLint *v);
typedef void (OSG_APIENTRY * osgGlSecondaryColor3sProc )(GLshort red, GLshort green, GLshort blue);
typedef void (OSG_APIENTRY * osgGlSecondaryColor3svProc )(const GLshort *v);
typedef void (OSG_APIENTRY * osgGlSecondaryColor3ubProc )(GLubyte red, GLubyte green, GLubyte blue);
typedef void (OSG_APIENTRY * osgGlSecondaryColor3ubvProc )(const GLubyte *v);
typedef void (OSG_APIENTRY * osgGlSecondaryColor3uiProc )(GLuint red, GLuint green, GLuint blue);
typedef void (OSG_APIENTRY * osgGlSecondaryColor3uivProc )(const GLuint *v);
typedef void (OSG_APIENTRY * osgGlSecondaryColor3usProc )(GLushort red, GLushort green, GLushort blue);
typedef void (OSG_APIENTRY * osgGlSecondaryColor3usvProc )(const GLushort *v);
typedef void (OSG_APIENTRY * osgGlSecondaryColorPointerProc )(GLint size, GLenum type, GLsizei stride, const void *pointer);
typedef void (OSG_APIENTRY * osgGlWindowPos2dProc )(GLdouble x, GLdouble y);
typedef void (OSG_APIENTRY * osgGlWindowPos2dvProc )(const GLdouble *v);
typedef void (OSG_APIENTRY * osgGlWindowPos2fProc )(GLfloat x, GLfloat y);
typedef void (OSG_APIENTRY * osgGlWindowPos2fvProc )(const GLfloat *v);
typedef void (OSG_APIENTRY * osgGlWindowPos2iProc )(GLint x, GLint y);
typedef void (OSG_APIENTRY * osgGlWindowPos2ivProc )(const GLint *v);
typedef void (OSG_APIENTRY * osgGlWindowPos2sProc )(GLshort x, GLshort y);
typedef void (OSG_APIENTRY * osgGlWindowPos2svProc )(const GLshort *v);
typedef void (OSG_APIENTRY * osgGlWindowPos3dProc )(GLdouble x, GLdouble y, GLdouble z);
typedef void (OSG_APIENTRY * osgGlWindowPos3dvProc )(const GLdouble *v);
typedef void (OSG_APIENTRY * osgGlWindowPos3fProc )(GLfloat x, GLfloat y, GLfloat z);
typedef void (OSG_APIENTRY * osgGlWindowPos3fvProc )(const GLfloat *v);
typedef void (OSG_APIENTRY * osgGlWindowPos3iProc )(GLint x, GLint y, GLint z);
typedef void (OSG_APIENTRY * osgGlWindowPos3ivProc )(const GLint *v);
typedef void (OSG_APIENTRY * osgGlWindowPos3sProc )(GLshort x, GLshort y, GLshort z);
typedef void (OSG_APIENTRY * osgGlWindowPos3svProc )(const GLshort *v);
typedef void (OSG_APIENTRY * osgGlBlendColorProc )(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
typedef void (OSG_APIENTRY * osgGlBlendEquationProc )(GLenum mode);
#endif /* GL_VERSION_1_4 */

#ifdef GL_VERSION_1_5
typedef void (OSG_APIENTRY * osgGlGenQueriesProc )(GLsizei n, GLuint *ids);
typedef void (OSG_APIENTRY * osgGlDeleteQueriesProc )(GLsizei n, const GLuint *ids);
typedef GLboolean (OSG_APIENTRY * osgGlIsQueryProc )(GLuint id);
typedef void (OSG_APIENTRY * osgGlBeginQueryProc )(GLenum target, GLuint id);
typedef void (OSG_APIENTRY * osgGlEndQueryProc )(GLenum target);
typedef void (OSG_APIENTRY * osgGlGetQueryivProc )(GLenum target, GLenum pname, GLint *params);
typedef void (OSG_APIENTRY * osgGlGetQueryObjectivProc )(GLuint id, GLenum pname, GLint *params);
typedef void (OSG_APIENTRY * osgGlGetQueryObjectuivProc )(GLuint id, GLenum pname, GLuint *params);
typedef void (OSG_APIENTRY * osgGlBindBufferProc )(GLenum target, GLuint buffer);
typedef void (OSG_APIENTRY * osgGlDeleteBuffersProc )(GLsizei n, const GLuint *buffers);
typedef void (OSG_APIENTRY * osgGlGenBuffersProc )(GLsizei n, GLuint *buffers);
typedef GLboolean (OSG_APIENTRY * osgGlIsBufferProc )(GLuint buffer);
typedef void (OSG_APIENTRY * osgGlBufferDataProc )(GLenum target, GLsizeiptr size, const void *data, GLenum usage);
typedef void (OSG_APIENTRY * osgGlBufferSubDataProc )(GLenum target, GLintptr offset, GLsizeiptr size, const void *data);
typedef void (OSG_APIENTRY * osgGlGetBufferSubDataProc )(GLenum target, GLintptr offset, GLsizeiptr size, void *data);
typedef void *(OSG_APIENTRY * osgGlMapBufferProc )(GLenum target, GLenum access);
typedef GLboolean (OSG_APIENTRY * osgGlUnmapBufferProc )(GLenum target);
typedef void (OSG_APIENTRY * osgGlGetBufferParameterivProc )(GLenum target, GLenum pname, GLint *params);
typedef void (OSG_APIENTRY * osgGlGetBufferPointervProc )(GLenum target, GLenum pname, void **params);
#endif /* GL_VERSION_1_5 */

#ifdef GL_VERSION_2_0
typedef void (OSG_APIENTRY * osgGlBlendEquationSeparateProc )(GLenum modeRGB, GLenum modeAlpha);
typedef void (OSG_APIENTRY * osgGlDrawBuffersProc )(GLsizei n, const GLenum *bufs);
typedef void (OSG_APIENTRY * osgGlStencilOpSeparateProc )(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass);
typedef void (OSG_APIENTRY * osgGlStencilFuncSeparateProc )(GLenum face, GLenum func, GLint ref, GLuint mask);
typedef void (OSG_APIENTRY * osgGlStencilMaskSeparateProc )(GLenum face, GLuint mask);
typedef void (OSG_APIENTRY * osgGlAttachShaderProc )(GLuint program, GLuint shader);
typedef void (OSG_APIENTRY * osgGlBindAttribLocationProc )(GLuint program, GLuint index, const GLchar *name);
typedef void (OSG_APIENTRY * osgGlCompileShaderProc )(GLuint shader);
typedef GLuint (OSG_APIENTRY * osgGlCreateProgramProc )(void);
typedef GLuint (OSG_APIENTRY * osgGlCreateShaderProc )(GLenum type);
typedef void (OSG_APIENTRY * osgGlDeleteProgramProc )(GLuint program);
typedef void (OSG_APIENTRY * osgGlDeleteShaderProc )(GLuint shader);
typedef void (OSG_APIENTRY * osgGlDetachShaderProc )(GLuint program, GLuint shader);
typedef void (OSG_APIENTRY * osgGlDisableVertexAttribArrayProc )(GLuint index);
typedef void (OSG_APIENTRY * osgGlEnableVertexAttribArrayProc )(GLuint index);
typedef void (OSG_APIENTRY * osgGlGetActiveAttribProc )(GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name);
typedef void (OSG_APIENTRY * osgGlGetActiveUniformProc )(GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name);
typedef void (OSG_APIENTRY * osgGlGetAttachedShadersProc )(GLuint program, GLsizei maxCount, GLsizei *count, GLuint *shaders);
typedef GLint (OSG_APIENTRY * osgGlGetAttribLocationProc )(GLuint program, const GLchar *name);
typedef void (OSG_APIENTRY * osgGlGetProgramivProc )(GLuint program, GLenum pname, GLint *params);
typedef void (OSG_APIENTRY * osgGlGetProgramInfoLogProc )(GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
typedef void (OSG_APIENTRY * osgGlGetShaderivProc )(GLuint shader, GLenum pname, GLint *params);
typedef void (OSG_APIENTRY * osgGlGetShaderInfoLogProc )(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
typedef void (OSG_APIENTRY * osgGlGetShaderSourceProc )(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *source);
typedef GLint (OSG_APIENTRY * osgGlGetUniformLocationProc )(GLuint program, const GLchar *name);
typedef void (OSG_APIENTRY * osgGlGetUniformfvProc )(GLuint program, GLint location, GLfloat *params);
typedef void (OSG_APIENTRY * osgGlGetUniformivProc )(GLuint program, GLint location, GLint *params);
typedef void (OSG_APIENTRY * osgGlGetVertexAttribdvProc )(GLuint index, GLenum pname, GLdouble *params);
typedef void (OSG_APIENTRY * osgGlGetVertexAttribfvProc )(GLuint index, GLenum pname, GLfloat *params);
typedef void (OSG_APIENTRY * osgGlGetVertexAttribivProc )(GLuint index, GLenum pname, GLint *params);
typedef void (OSG_APIENTRY * osgGlGetVertexAttribPointervProc )(GLuint index, GLenum pname, void **pointer);
typedef GLboolean (OSG_APIENTRY * osgGlIsProgramProc )(GLuint program);
typedef GLboolean (OSG_APIENTRY * osgGlIsShaderProc )(GLuint shader);
typedef void (OSG_APIENTRY * osgGlLinkProgramProc )(GLuint program);
typedef void (OSG_APIENTRY * osgGlShaderSourceProc )(GLuint shader, GLsizei count, const GLchar *const*string, const GLint *length);
typedef void (OSG_APIENTRY * osgGlUseProgramProc )(GLuint program);
typedef void (OSG_APIENTRY * osgGlUniform1fProc )(GLint location, GLfloat v0);
typedef void (OSG_APIENTRY * osgGlUniform2fProc )(GLint location, GLfloat v0, GLfloat v1);
typedef void (OSG_APIENTRY * osgGlUniform3fProc )(GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
typedef void (OSG_APIENTRY * osgGlUniform4fProc )(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
typedef void (OSG_APIENTRY * osgGlUniform1iProc )(GLint location, GLint v0);
typedef void (OSG_APIENTRY * osgGlUniform2iProc )(GLint location, GLint v0, GLint v1);
typedef void (OSG_APIENTRY * osgGlUniform3iProc )(GLint location, GLint v0, GLint v1, GLint v2);
typedef void (OSG_APIENTRY * osgGlUniform4iProc )(GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
typedef void (OSG_APIENTRY * osgGlUniform1fvProc )(GLint location, GLsizei count, const GLfloat *value);
typedef void (OSG_APIENTRY * osgGlUniform2fvProc )(GLint location, GLsizei count, const GLfloat *value);
typedef void (OSG_APIENTRY * osgGlUniform3fvProc )(GLint location, GLsizei count, const GLfloat *value);
typedef void (OSG_APIENTRY * osgGlUniform4fvProc )(GLint location, GLsizei count, const GLfloat *value);
typedef void (OSG_APIENTRY * osgGlUniform1ivProc )(GLint location, GLsizei count, const GLint *value);
typedef void (OSG_APIENTRY * osgGlUniform2ivProc )(GLint location, GLsizei count, const GLint *value);
typedef void (OSG_APIENTRY * osgGlUniform3ivProc )(GLint location, GLsizei count, const GLint *value);
typedef void (OSG_APIENTRY * osgGlUniform4ivProc )(GLint location, GLsizei count, const GLint *value);
typedef void (OSG_APIENTRY * osgGlUniformMatrix2fvProc )(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (OSG_APIENTRY * osgGlUniformMatrix3fvProc )(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (OSG_APIENTRY * osgGlUniformMatrix4fvProc )(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (OSG_APIENTRY * osgGlValidateProgramProc )(GLuint program);
typedef void (OSG_APIENTRY * osgGlVertexAttrib1dProc )(GLuint index, GLdouble x);
typedef void (OSG_APIENTRY * osgGlVertexAttrib1dvProc )(GLuint index, const GLdouble *v);
typedef void (OSG_APIENTRY * osgGlVertexAttrib1fProc )(GLuint index, GLfloat x);
typedef void (OSG_APIENTRY * osgGlVertexAttrib1fvProc )(GLuint index, const GLfloat *v);
typedef void (OSG_APIENTRY * osgGlVertexAttrib1sProc )(GLuint index, GLshort x);
typedef void (OSG_APIENTRY * osgGlVertexAttrib1svProc )(GLuint index, const GLshort *v);
typedef void (OSG_APIENTRY * osgGlVertexAttrib2dProc )(GLuint index, GLdouble x, GLdouble y);
typedef void (OSG_APIENTRY * osgGlVertexAttrib2dvProc )(GLuint index, const GLdouble *v);
typedef void (OSG_APIENTRY * osgGlVertexAttrib2fProc )(GLuint index, GLfloat x, GLfloat y);
typedef void (OSG_APIENTRY * osgGlVertexAttrib2fvProc )(GLuint index, const GLfloat *v);
typedef void (OSG_APIENTRY * osgGlVertexAttrib2sProc )(GLuint index, GLshort x, GLshort y);
typedef void (OSG_APIENTRY * osgGlVertexAttrib2svProc )(GLuint index, const GLshort *v);
typedef void (OSG_APIENTRY * osgGlVertexAttrib3dProc )(GLuint index, GLdouble x, GLdouble y, GLdouble z);
typedef void (OSG_APIENTRY * osgGlVertexAttrib3dvProc )(GLuint index, const GLdouble *v);
typedef void (OSG_APIENTRY * osgGlVertexAttrib3fProc )(GLuint index, GLfloat x, GLfloat y, GLfloat z);
typedef void (OSG_APIENTRY * osgGlVertexAttrib3fvProc )(GLuint index, const GLfloat *v);
typedef void (OSG_APIENTRY * osgGlVertexAttrib3sProc )(GLuint index, GLshort x, GLshort y, GLshort z);
typedef void (OSG_APIENTRY * osgGlVertexAttrib3svProc )(GLuint index, const GLshort *v);
typedef void (OSG_APIENTRY * osgGlVertexAttrib4NbvProc )(GLuint index, const GLbyte *v);
typedef void (OSG_APIENTRY * osgGlVertexAttrib4NivProc )(GLuint index, const GLint *v);
typedef void (OSG_APIENTRY * osgGlVertexAttrib4NsvProc )(GLuint index, const GLshort *v);
typedef void (OSG_APIENTRY * osgGlVertexAttrib4NubProc )(GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w);
typedef void (OSG_APIENTRY * osgGlVertexAttrib4NubvProc )(GLuint index, const GLubyte *v);
typedef void (OSG_APIENTRY * osgGlVertexAttrib4NuivProc )(GLuint index, const GLuint *v);
typedef void (OSG_APIENTRY * osgGlVertexAttrib4NusvProc )(GLuint index, const GLushort *v);
typedef void (OSG_APIENTRY * osgGlVertexAttrib4bvProc )(GLuint index, const GLbyte *v);
typedef void (OSG_APIENTRY * osgGlVertexAttrib4dProc )(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
typedef void (OSG_APIENTRY * osgGlVertexAttrib4dvProc )(GLuint index, const GLdouble *v);
typedef void (OSG_APIENTRY * osgGlVertexAttrib4fProc )(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
typedef void (OSG_APIENTRY * osgGlVertexAttrib4fvProc )(GLuint index, const GLfloat *v);
typedef void (OSG_APIENTRY * osgGlVertexAttrib4ivProc )(GLuint index, const GLint *v);
typedef void (OSG_APIENTRY * osgGlVertexAttrib4sProc )(GLuint index, GLshort x, GLshort y, GLshort z, GLshort w);
typedef void (OSG_APIENTRY * osgGlVertexAttrib4svProc )(GLuint index, const GLshort *v);
typedef void (OSG_APIENTRY * osgGlVertexAttrib4ubvProc )(GLuint index, const GLubyte *v);
typedef void (OSG_APIENTRY * osgGlVertexAttrib4uivProc )(GLuint index, const GLuint *v);
typedef void (OSG_APIENTRY * osgGlVertexAttrib4usvProc )(GLuint index, const GLushort *v);
typedef void (OSG_APIENTRY * osgGlVertexAttribPointerProc )(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer);
#endif /* GL_VERSION_2_0 */

#ifdef GL_VERSION_2_1
typedef void (OSG_APIENTRY * osgGlUniformMatrix2x3fvProc )(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (OSG_APIENTRY * osgGlUniformMatrix3x2fvProc )(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (OSG_APIENTRY * osgGlUniformMatrix2x4fvProc )(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (OSG_APIENTRY * osgGlUniformMatrix4x2fvProc )(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (OSG_APIENTRY * osgGlUniformMatrix3x4fvProc )(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (OSG_APIENTRY * osgGlUniformMatrix4x3fvProc )(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
#endif /* GL_VERSION_2_1 */

#ifdef GL_VERSION_3_0
typedef void (OSG_APIENTRY * osgGlColorMaskiProc )(GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a);
typedef void (OSG_APIENTRY * osgGlGetBooleani_vProc )(GLenum target, GLuint index, GLboolean *data);
typedef void (OSG_APIENTRY * osgGlGetIntegeri_vProc )(GLenum target, GLuint index, GLint *data);
typedef void (OSG_APIENTRY * osgGlEnableiProc )(GLenum target, GLuint index);
typedef void (OSG_APIENTRY * osgGlDisableiProc )(GLenum target, GLuint index);
typedef GLboolean (OSG_APIENTRY * osgGlIsEnablediProc )(GLenum target, GLuint index);
typedef void (OSG_APIENTRY * osgGlBeginTransformFeedbackProc )(GLenum primitiveMode);
typedef void (OSG_APIENTRY * osgGlEndTransformFeedbackProc )(void);
typedef void (OSG_APIENTRY * osgGlBindBufferRangeProc )(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size);
typedef void (OSG_APIENTRY * osgGlBindBufferBaseProc )(GLenum target, GLuint index, GLuint buffer);
typedef void (OSG_APIENTRY * osgGlTransformFeedbackVaryingsProc )(GLuint program, GLsizei count, const GLchar *const*varyings, GLenum bufferMode);
typedef void (OSG_APIENTRY * osgGlGetTransformFeedbackVaryingProc )(GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLsizei *size, GLenum *type, GLchar *name);
typedef void (OSG_APIENTRY * osgGlClampColorProc )(GLenum target, GLenum clamp);
typedef void (OSG_APIENTRY * osgGlBeginConditionalRenderProc )(GLuint id, GLenum mode);
typedef void (OSG_APIENTRY * osgGlEndConditionalRenderProc )(void);
typedef void (OSG_APIENTRY * osgGlVertexAttribIPointerProc )(GLuint index, GLint size, GLenum type, GLsizei stride, const void *pointer);
typedef void (OSG_APIENTRY * osgGlGetVertexAttribIivProc )(GLuint index, GLenum pname, GLint *params);
typedef void (OSG_APIENTRY * osgGlGetVertexAttribIuivProc )(GLuint index, GLenum pname, GLuint *params);
typedef void (OSG_APIENTRY * osgGlVertexAttribI1iProc )(GLuint index, GLint x);
typedef void (OSG_APIENTRY * osgGlVertexAttribI2iProc )(GLuint index, GLint x, GLint y);
typedef void (OSG_APIENTRY * osgGlVertexAttribI3iProc )(GLuint index, GLint x, GLint y, GLint z);
typedef void (OSG_APIENTRY * osgGlVertexAttribI4iProc )(GLuint index, GLint x, GLint y, GLint z, GLint w);
typedef void (OSG_APIENTRY * osgGlVertexAttribI1uiProc )(GLuint index, GLuint x);
typedef void (OSG_APIENTRY * osgGlVertexAttribI2uiProc )(GLuint index, GLuint x, GLuint y);
typedef void (OSG_APIENTRY * osgGlVertexAttribI3uiProc )(GLuint index, GLuint x, GLuint y, GLuint z);
typedef void (OSG_APIENTRY * osgGlVertexAttribI4uiProc )(GLuint index, GLuint x, GLuint y, GLuint z, GLuint w);
typedef void (OSG_APIENTRY * osgGlVertexAttribI1ivProc )(GLuint index, const GLint *v);
typedef void (OSG_APIENTRY * osgGlVertexAttribI2ivProc )(GLuint index, const GLint *v);
typedef void (OSG_APIENTRY * osgGlVertexAttribI3ivProc )(GLuint index, const GLint *v);
typedef void (OSG_APIENTRY * osgGlVertexAttribI4ivProc )(GLuint index, const GLint *v);
typedef void (OSG_APIENTRY * osgGlVertexAttribI1uivProc )(GLuint index, const GLuint *v);
typedef void (OSG_APIENTRY * osgGlVertexAttribI2uivProc )(GLuint index, const GLuint *v);
typedef void (OSG_APIENTRY * osgGlVertexAttribI3uivProc )(GLuint index, const GLuint *v);
typedef void (OSG_APIENTRY * osgGlVertexAttribI4uivProc )(GLuint index, const GLuint *v);
typedef void (OSG_APIENTRY * osgGlVertexAttribI4bvProc )(GLuint index, const GLbyte *v);
typedef void (OSG_APIENTRY * osgGlVertexAttribI4svProc )(GLuint index, const GLshort *v);
typedef void (OSG_APIENTRY * osgGlVertexAttribI4ubvProc )(GLuint index, const GLubyte *v);
typedef void (OSG_APIENTRY * osgGlVertexAttribI4usvProc )(GLuint index, const GLushort *v);
typedef void (OSG_APIENTRY * osgGlGetUniformuivProc )(GLuint program, GLint location, GLuint *params);
typedef void (OSG_APIENTRY * osgGlBindFragDataLocationProc )(GLuint program, GLuint color, const GLchar *name);
typedef GLint (OSG_APIENTRY * osgGlGetFragDataLocationProc )(GLuint program, const GLchar *name);
typedef void (OSG_APIENTRY * osgGlUniform1uiProc )(GLint location, GLuint v0);
typedef void (OSG_APIENTRY * osgGlUniform2uiProc )(GLint location, GLuint v0, GLuint v1);
typedef void (OSG_APIENTRY * osgGlUniform3uiProc )(GLint location, GLuint v0, GLuint v1, GLuint v2);
typedef void (OSG_APIENTRY * osgGlUniform4uiProc )(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
typedef void (OSG_APIENTRY * osgGlUniform1uivProc )(GLint location, GLsizei count, const GLuint *value);
typedef void (OSG_APIENTRY * osgGlUniform2uivProc )(GLint location, GLsizei count, const GLuint *value);
typedef void (OSG_APIENTRY * osgGlUniform3uivProc )(GLint location, GLsizei count, const GLuint *value);
typedef void (OSG_APIENTRY * osgGlUniform4uivProc )(GLint location, GLsizei count, const GLuint *value);
typedef void (OSG_APIENTRY * osgGlTexParameterIivProc )(GLenum target, GLenum pname, const GLint *params);
typedef void (OSG_APIENTRY * osgGlTexParameterIuivProc )(GLenum target, GLenum pname, const GLuint *params);
typedef void (OSG_APIENTRY * osgGlGetTexParameterIivProc )(GLenum target, GLenum pname, GLint *params);
typedef void (OSG_APIENTRY * osgGlGetTexParameterIuivProc )(GLenum target, GLenum pname, GLuint *params);
typedef void (OSG_APIENTRY * osgGlClearBufferivProc )(GLenum buffer, GLint drawbuffer, const GLint *value);
typedef void (OSG_APIENTRY * osgGlClearBufferuivProc )(GLenum buffer, GLint drawbuffer, const GLuint *value);
typedef void (OSG_APIENTRY * osgGlClearBufferfvProc )(GLenum buffer, GLint drawbuffer, const GLfloat *value);
typedef void (OSG_APIENTRY * osgGlClearBufferfiProc )(GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil);
typedef const GLubyte *(OSG_APIENTRY * osgGlGetStringiProc )(GLenum name, GLuint index);
typedef GLboolean (OSG_APIENTRY * osgGlIsRenderbufferProc )(GLuint renderbuffer);
typedef void (OSG_APIENTRY * osgGlBindRenderbufferProc )(GLenum target, GLuint renderbuffer);
typedef void (OSG_APIENTRY * osgGlDeleteRenderbuffersProc )(GLsizei n, const GLuint *renderbuffers);
typedef void (OSG_APIENTRY * osgGlGenRenderbuffersProc )(GLsizei n, GLuint *renderbuffers);
typedef void (OSG_APIENTRY * osgGlRenderbufferStorageProc )(GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (OSG_APIENTRY * osgGlGetRenderbufferParameterivProc )(GLenum target, GLenum pname, GLint *params);
typedef GLboolean (OSG_APIENTRY * osgGlIsFramebufferProc )(GLuint framebuffer);
typedef void (OSG_APIENTRY * osgGlBindFramebufferProc )(GLenum target, GLuint framebuffer);
typedef void (OSG_APIENTRY * osgGlDeleteFramebuffersProc )(GLsizei n, const GLuint *framebuffers);
typedef void (OSG_APIENTRY * osgGlGenFramebuffersProc )(GLsizei n, GLuint *framebuffers);
typedef GLenum (OSG_APIENTRY * osgGlCheckFramebufferStatusProc )(GLenum target);
typedef void (OSG_APIENTRY * osgGlFramebufferTexture1DProc )(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
typedef void (OSG_APIENTRY * osgGlFramebufferTexture2DProc )(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
typedef void (OSG_APIENTRY * osgGlFramebufferTexture3DProc )(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset);
typedef void (OSG_APIENTRY * osgGlFramebufferRenderbufferProc )(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
typedef void (OSG_APIENTRY * osgGlGetFramebufferAttachmentParameterivProc )(GLenum target, GLenum attachment, GLenum pname, GLint *params);
typedef void (OSG_APIENTRY * osgGlGenerateMipmapProc )(GLenum target);
typedef void (OSG_APIENTRY * osgGlBlitFramebufferProc )(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);
typedef void (OSG_APIENTRY * osgGlRenderbufferStorageMultisampleProc )(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (OSG_APIENTRY * osgGlFramebufferTextureLayerProc )(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer);
typedef void *(OSG_APIENTRY * osgGlMapBufferRangeProc )(GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access);
typedef void (OSG_APIENTRY * osgGlFlushMappedBufferRangeProc )(GLenum target, GLintptr offset, GLsizeiptr length);
typedef void (OSG_APIENTRY * osgGlBindVertexArrayProc )(GLuint array);
typedef void (OSG_APIENTRY * osgGlDeleteVertexArraysProc )(GLsizei n, const GLuint *arrays);
typedef void (OSG_APIENTRY * osgGlGenVertexArraysProc )(GLsizei n, GLuint *arrays);
typedef GLboolean (OSG_APIENTRY * osgGlIsVertexArrayProc )(GLuint array);
#endif /* GL_VERSION_3_0 */

#ifdef GL_VERSION_3_1
typedef void (OSG_APIENTRY * osgGlDrawArraysInstancedProc )(GLenum mode, GLint first, GLsizei count, GLsizei instancecount);
typedef void (OSG_APIENTRY * osgGlDrawElementsInstancedProc )(GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount);
typedef void (OSG_APIENTRY * osgGlTexBufferProc )(GLenum target, GLenum internalformat, GLuint buffer);
typedef void (OSG_APIENTRY * osgGlPrimitiveRestartIndexProc )(GLuint index);
typedef void (OSG_APIENTRY * osgGlCopyBufferSubDataProc )(GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size);
typedef void (OSG_APIENTRY * osgGlGetUniformIndicesProc )(GLuint program, GLsizei uniformCount, const GLchar *const*uniformNames, GLuint *uniformIndices);
typedef void (OSG_APIENTRY * osgGlGetActiveUniformsivProc )(GLuint program, GLsizei uniformCount, const GLuint *uniformIndices, GLenum pname, GLint *params);
typedef void (OSG_APIENTRY * osgGlGetActiveUniformNameProc )(GLuint program, GLuint uniformIndex, GLsizei bufSize, GLsizei *length, GLchar *uniformName);
typedef GLuint (OSG_APIENTRY * osgGlGetUniformBlockIndexProc )(GLuint program, const GLchar *uniformBlockName);
typedef void (OSG_APIENTRY * osgGlGetActiveUniformBlockivProc )(GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint *params);
typedef void (OSG_APIENTRY * osgGlGetActiveUniformBlockNameProc )(GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei *length, GLchar *uniformBlockName);
typedef void (OSG_APIENTRY * osgGlUniformBlockBindingProc )(GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding);
#endif /* GL_VERSION_3_1 */

#ifdef GL_VERSION_3_2
typedef void (OSG_APIENTRY * osgGlDrawElementsBaseVertexProc )(GLenum mode, GLsizei count, GLenum type, const void *indices, GLint basevertex);
typedef void (OSG_APIENTRY * osgGlDrawRangeElementsBaseVertexProc )(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void *indices, GLint basevertex);
typedef void (OSG_APIENTRY * osgGlDrawElementsInstancedBaseVertexProc )(GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount, GLint basevertex);
typedef void (OSG_APIENTRY * osgGlMultiDrawElementsBaseVertexProc )(GLenum mode, const GLsizei *count, GLenum type, const void *const*indices, GLsizei drawcount, const GLint *basevertex);
typedef void (OSG_APIENTRY * osgGlProvokingVertexProc )(GLenum mode);
typedef GLsync (OSG_APIENTRY * osgGlFenceSyncProc )(GLenum condition, GLbitfield flags);
typedef GLboolean (OSG_APIENTRY * osgGlIsSyncProc )(GLsync sync);
typedef void (OSG_APIENTRY * osgGlDeleteSyncProc )(GLsync sync);
typedef GLenum (OSG_APIENTRY * osgGlClientWaitSyncProc )(GLsync sync, GLbitfield flags, GLuint64 timeout);
typedef void (OSG_APIENTRY * osgGlWaitSyncProc )(GLsync sync, GLbitfield flags, GLuint64 timeout);
typedef void (OSG_APIENTRY * osgGlGetInteger64vProc )(GLenum pname, GLint64 *data);
typedef void (OSG_APIENTRY * osgGlGetSyncivProc )(GLsync sync, GLenum pname, GLsizei bufSize, GLsizei *length, GLint *values);
typedef void (OSG_APIENTRY * osgGlGetInteger64i_vProc )(GLenum target, GLuint index, GLint64 *data);
typedef void (OSG_APIENTRY * osgGlGetBufferParameteri64vProc )(GLenum target, GLenum pname, GLint64 *params);
typedef void (OSG_APIENTRY * osgGlFramebufferTextureProc )(GLenum target, GLenum attachment, GLuint texture, GLint level);
typedef void (OSG_APIENTRY * osgGlTexImage2DMultisampleProc )(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
typedef void (OSG_APIENTRY * osgGlTexImage3DMultisampleProc )(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations);
typedef void (OSG_APIENTRY * osgGlGetMultisamplefvProc )(GLenum pname, GLuint index, GLfloat *val);
typedef void (OSG_APIENTRY * osgGlSampleMaskiProc )(GLuint maskNumber, GLbitfield mask);
#endif /* GL_VERSION_3_2 */

#ifdef GL_VERSION_3_3
typedef void (OSG_APIENTRY * osgGlBindFragDataLocationIndexedProc )(GLuint program, GLuint colorNumber, GLuint index, const GLchar *name);
typedef GLint (OSG_APIENTRY * osgGlGetFragDataIndexProc )(GLuint program, const GLchar *name);
typedef void (OSG_APIENTRY * osgGlGenSamplersProc )(GLsizei count, GLuint *samplers);
typedef void (OSG_APIENTRY * osgGlDeleteSamplersProc )(GLsizei count, const GLuint *samplers);
typedef GLboolean (OSG_APIENTRY * osgGlIsSamplerProc )(GLuint sampler);
typedef void (OSG_APIENTRY * osgGlBindSamplerProc )(GLuint unit, GLuint sampler);
typedef void (OSG_APIENTRY * osgGlSamplerParameteriProc )(GLuint sampler, GLenum pname, GLint param);
typedef void (OSG_APIENTRY * osgGlSamplerParameterivProc )(GLuint sampler, GLenum pname, const GLint *param);
typedef void (OSG_APIENTRY * osgGlSamplerParameterfProc )(GLuint sampler, GLenum pname, GLfloat param);
typedef void (OSG_APIENTRY * osgGlSamplerParameterfvProc )(GLuint sampler, GLenum pname, const GLfloat *param);
typedef void (OSG_APIENTRY * osgGlSamplerParameterIivProc )(GLuint sampler, GLenum pname, const GLint *param);
typedef void (OSG_APIENTRY * osgGlSamplerParameterIuivProc )(GLuint sampler, GLenum pname, const GLuint *param);
typedef void (OSG_APIENTRY * osgGlGetSamplerParameterivProc )(GLuint sampler, GLenum pname, GLint *params);
typedef void (OSG_APIENTRY * osgGlGetSamplerParameterIivProc )(GLuint sampler, GLenum pname, GLint *params);
typedef void (OSG_APIENTRY * osgGlGetSamplerParameterfvProc )(GLuint sampler, GLenum pname, GLfloat *params);
typedef void (OSG_APIENTRY * osgGlGetSamplerParameterIuivProc )(GLuint sampler, GLenum pname, GLuint *params);
typedef void (OSG_APIENTRY * osgGlQueryCounterProc )(GLuint id, GLenum target);
typedef void (OSG_APIENTRY * osgGlGetQueryObjecti64vProc )(GLuint id, GLenum pname, GLint64 *params);
typedef void (OSG_APIENTRY * osgGlGetQueryObjectui64vProc )(GLuint id, GLenum pname, GLuint64 *params);
typedef void (OSG_APIENTRY * osgGlVertexAttribDivisorProc )(GLuint index, GLuint divisor);
typedef void (OSG_APIENTRY * osgGlVertexAttribP1uiProc )(GLuint index, GLenum type, GLboolean normalized, GLuint value);
typedef void (OSG_APIENTRY * osgGlVertexAttribP1uivProc )(GLuint index, GLenum type, GLboolean normalized, const GLuint *value);
typedef void (OSG_APIENTRY * osgGlVertexAttribP2uiProc )(GLuint index, GLenum type, GLboolean normalized, GLuint value);
typedef void (OSG_APIENTRY * osgGlVertexAttribP2uivProc )(GLuint index, GLenum type, GLboolean normalized, const GLuint *value);
typedef void (OSG_APIENTRY * osgGlVertexAttribP3uiProc )(GLuint index, GLenum type, GLboolean normalized, GLuint value);
typedef void (OSG_APIENTRY * osgGlVertexAttribP3uivProc )(GLuint index, GLenum type, GLboolean normalized, const GLuint *value);
typedef void (OSG_APIENTRY * osgGlVertexAttribP4uiProc )(GLuint index, GLenum type, GLboolean normalized, GLuint value);
typedef void (OSG_APIENTRY * osgGlVertexAttribP4uivProc )(GLuint index, GLenum type, GLboolean normalized, const GLuint *value);
typedef void (OSG_APIENTRY * osgGlVertexP2uiProc )(GLenum type, GLuint value);
typedef void (OSG_APIENTRY * osgGlVertexP2uivProc )(GLenum type, const GLuint *value);
typedef void (OSG_APIENTRY * osgGlVertexP3uiProc )(GLenum type, GLuint value);
typedef void (OSG_APIENTRY * osgGlVertexP3uivProc )(GLenum type, const GLuint *value);
typedef void (OSG_APIENTRY * osgGlVertexP4uiProc )(GLenum type, GLuint value);
typedef void (OSG_APIENTRY * osgGlVertexP4uivProc )(GLenum type, const GLuint *value);
typedef void (OSG_APIENTRY * osgGlTexCoordP1uiProc )(GLenum type, GLuint coords);
typedef void (OSG_APIENTRY * osgGlTexCoordP1uivProc )(GLenum type, const GLuint *coords);
typedef void (OSG_APIENTRY * osgGlTexCoordP2uiProc )(GLenum type, GLuint coords);
typedef void (OSG_APIENTRY * osgGlTexCoordP2uivProc )(GLenum type, const GLuint *coords);
typedef void (OSG_APIENTRY * osgGlTexCoordP3uiProc )(GLenum type, GLuint coords);
typedef void (OSG_APIENTRY * osgGlTexCoordP3uivProc )(GLenum type, const GLuint *coords);
typedef void (OSG_APIENTRY * osgGlTexCoordP4uiProc )(GLenum type, GLuint coords);
typedef void (OSG_APIENTRY * osgGlTexCoordP4uivProc )(GLenum type, const GLuint *coords);
typedef void (OSG_APIENTRY * osgGlMultiTexCoordP1uiProc )(GLenum texture, GLenum type, GLuint coords);
typedef void (OSG_APIENTRY * osgGlMultiTexCoordP1uivProc )(GLenum texture, GLenum type, const GLuint *coords);
typedef void (OSG_APIENTRY * osgGlMultiTexCoordP2uiProc )(GLenum texture, GLenum type, GLuint coords);
typedef void (OSG_APIENTRY * osgGlMultiTexCoordP2uivProc )(GLenum texture, GLenum type, const GLuint *coords);
typedef void (OSG_APIENTRY * osgGlMultiTexCoordP3uiProc )(GLenum texture, GLenum type, GLuint coords);
typedef void (OSG_APIENTRY * osgGlMultiTexCoordP3uivProc )(GLenum texture, GLenum type, const GLuint *coords);
typedef void (OSG_APIENTRY * osgGlMultiTexCoordP4uiProc )(GLenum texture, GLenum type, GLuint coords);
typedef void (OSG_APIENTRY * osgGlMultiTexCoordP4uivProc )(GLenum texture, GLenum type, const GLuint *coords);
typedef void (OSG_APIENTRY * osgGlNormalP3uiProc )(GLenum type, GLuint coords);
typedef void (OSG_APIENTRY * osgGlNormalP3uivProc )(GLenum type, const GLuint *coords);
typedef void (OSG_APIENTRY * osgGlColorP3uiProc )(GLenum type, GLuint color);
typedef void (OSG_APIENTRY * osgGlColorP3uivProc )(GLenum type, const GLuint *color);
typedef void (OSG_APIENTRY * osgGlColorP4uiProc )(GLenum type, GLuint color);
typedef void (OSG_APIENTRY * osgGlColorP4uivProc )(GLenum type, const GLuint *color);
typedef void (OSG_APIENTRY * osgGlSecondaryColorP3uiProc )(GLenum type, GLuint color);
typedef void (OSG_APIENTRY * osgGlSecondaryColorP3uivProc )(GLenum type, const GLuint *color);
#endif /* GL_VERSION_3_3 */

#ifdef GL_VERSION_4_0
typedef void (OSG_APIENTRY * osgGlMinSampleShadingProc )(GLfloat value);
typedef void (OSG_APIENTRY * osgGlBlendEquationiProc )(GLuint buf, GLenum mode);
typedef void (OSG_APIENTRY * osgGlBlendEquationSeparateiProc )(GLuint buf, GLenum modeRGB, GLenum modeAlpha);
typedef void (OSG_APIENTRY * osgGlBlendFunciProc )(GLuint buf, GLenum src, GLenum dst);
typedef void (OSG_APIENTRY * osgGlBlendFuncSeparateiProc )(GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
typedef void (OSG_APIENTRY * osgGlDrawArraysIndirectProc )(GLenum mode, const void *indirect);
typedef void (OSG_APIENTRY * osgGlDrawElementsIndirectProc )(GLenum mode, GLenum type, const void *indirect);
typedef void (OSG_APIENTRY * osgGlUniform1dProc )(GLint location, GLdouble x);
typedef void (OSG_APIENTRY * osgGlUniform2dProc )(GLint location, GLdouble x, GLdouble y);
typedef void (OSG_APIENTRY * osgGlUniform3dProc )(GLint location, GLdouble x, GLdouble y, GLdouble z);
typedef void (OSG_APIENTRY * osgGlUniform4dProc )(GLint location, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
typedef void (OSG_APIENTRY * osgGlUniform1dvProc )(GLint location, GLsizei count, const GLdouble *value);
typedef void (OSG_APIENTRY * osgGlUniform2dvProc )(GLint location, GLsizei count, const GLdouble *value);
typedef void (OSG_APIENTRY * osgGlUniform3dvProc )(GLint location, GLsizei count, const GLdouble *value);
typedef void (OSG_APIENTRY * osgGlUniform4dvProc )(GLint location, GLsizei count, const GLdouble *value);
typedef void (OSG_APIENTRY * osgGlUniformMatrix2dvProc )(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (OSG_APIENTRY * osgGlUniformMatrix3dvProc )(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (OSG_APIENTRY * osgGlUniformMatrix4dvProc )(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (OSG_APIENTRY * osgGlUniformMatrix2x3dvProc )(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (OSG_APIENTRY * osgGlUniformMatrix2x4dvProc )(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (OSG_APIENTRY * osgGlUniformMatrix3x2dvProc )(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (OSG_APIENTRY * osgGlUniformMatrix3x4dvProc )(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (OSG_APIENTRY * osgGlUniformMatrix4x2dvProc )(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (OSG_APIENTRY * osgGlUniformMatrix4x3dvProc )(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (OSG_APIENTRY * osgGlGetUniformdvProc )(GLuint program, GLint location, GLdouble *params);
typedef GLint (OSG_APIENTRY * osgGlGetSubroutineUniformLocationProc )(GLuint program, GLenum shadertype, const GLchar *name);
typedef GLuint (OSG_APIENTRY * osgGlGetSubroutineIndexProc )(GLuint program, GLenum shadertype, const GLchar *name);
typedef void (OSG_APIENTRY * osgGlGetActiveSubroutineUniformivProc )(GLuint program, GLenum shadertype, GLuint index, GLenum pname, GLint *values);
typedef void (OSG_APIENTRY * osgGlGetActiveSubroutineUniformNameProc )(GLuint program, GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei *length, GLchar *name);
typedef void (OSG_APIENTRY * osgGlGetActiveSubroutineNameProc )(GLuint program, GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei *length, GLchar *name);
typedef void (OSG_APIENTRY * osgGlUniformSubroutinesuivProc )(GLenum shadertype, GLsizei count, const GLuint *indices);
typedef void (OSG_APIENTRY * osgGlGetUniformSubroutineuivProc )(GLenum shadertype, GLint location, GLuint *params);
typedef void (OSG_APIENTRY * osgGlGetProgramStageivProc )(GLuint program, GLenum shadertype, GLenum pname, GLint *values);
typedef void (OSG_APIENTRY * osgGlPatchParameteriProc )(GLenum pname, GLint value);
typedef void (OSG_APIENTRY * osgGlPatchParameterfvProc )(GLenum pname, const GLfloat *values);
typedef void (OSG_APIENTRY * osgGlBindTransformFeedbackProc )(GLenum target, GLuint id);
typedef void (OSG_APIENTRY * osgGlDeleteTransformFeedbacksProc )(GLsizei n, const GLuint *ids);
typedef void (OSG_APIENTRY * osgGlGenTransformFeedbacksProc )(GLsizei n, GLuint *ids);
typedef GLboolean (OSG_APIENTRY * osgGlIsTransformFeedbackProc )(GLuint id);
typedef void (OSG_APIENTRY * osgGlPauseTransformFeedbackProc )(void);
typedef void (OSG_APIENTRY * osgGlResumeTransformFeedbackProc )(void);
typedef void (OSG_APIENTRY * osgGlDrawTransformFeedbackProc )(GLenum mode, GLuint id);
typedef void (OSG_APIENTRY * osgGlDrawTransformFeedbackStreamProc )(GLenum mode, GLuint id, GLuint stream);
typedef void (OSG_APIENTRY * osgGlBeginQueryIndexedProc )(GLenum target, GLuint index, GLuint id);
typedef void (OSG_APIENTRY * osgGlEndQueryIndexedProc )(GLenum target, GLuint index);
typedef void (OSG_APIENTRY * osgGlGetQueryIndexedivProc )(GLenum target, GLuint index, GLenum pname, GLint *params);
#endif /* GL_VERSION_4_0 */

#ifdef GL_VERSION_4_1
typedef void (OSG_APIENTRY * osgGlReleaseShaderCompilerProc )(void);
typedef void (OSG_APIENTRY * osgGlShaderBinaryProc )(GLsizei count, const GLuint *shaders, GLenum binaryformat, const void *binary, GLsizei length);
typedef void (OSG_APIENTRY * osgGlGetShaderPrecisionFormatProc )(GLenum shadertype, GLenum precisiontype, GLint *range, GLint *precision);
typedef void (OSG_APIENTRY * osgGlDepthRangefProc )(GLfloat n, GLfloat f);
typedef void (OSG_APIENTRY * osgGlClearDepthfProc )(GLfloat d);
typedef void (OSG_APIENTRY * osgGlGetProgramBinaryProc )(GLuint program, GLsizei bufSize, GLsizei *length, GLenum *binaryFormat, void *binary);
typedef void (OSG_APIENTRY * osgGlProgramBinaryProc )(GLuint program, GLenum binaryFormat, const void *binary, GLsizei length);
typedef void (OSG_APIENTRY * osgGlProgramParameteriProc )(GLuint program, GLenum pname, GLint value);
typedef void (OSG_APIENTRY * osgGlUseProgramStagesProc )(GLuint pipeline, GLbitfield stages, GLuint program);
typedef void (OSG_APIENTRY * osgGlActiveShaderProgramProc )(GLuint pipeline, GLuint program);
typedef GLuint (OSG_APIENTRY * osgGlCreateShaderProgramvProc )(GLenum type, GLsizei count, const GLchar *const*strings);
typedef void (OSG_APIENTRY * osgGlBindProgramPipelineProc )(GLuint pipeline);
typedef void (OSG_APIENTRY * osgGlDeleteProgramPipelinesProc )(GLsizei n, const GLuint *pipelines);
typedef void (OSG_APIENTRY * osgGlGenProgramPipelinesProc )(GLsizei n, GLuint *pipelines);
typedef GLboolean (OSG_APIENTRY * osgGlIsProgramPipelineProc )(GLuint pipeline);
typedef void (OSG_APIENTRY * osgGlGetProgramPipelineivProc )(GLuint pipeline, GLenum pname, GLint *params);
typedef void (OSG_APIENTRY * osgGlProgramUniform1iProc )(GLuint program, GLint location, GLint v0);
typedef void (OSG_APIENTRY * osgGlProgramUniform1ivProc )(GLuint program, GLint location, GLsizei count, const GLint *value);
typedef void (OSG_APIENTRY * osgGlProgramUniform1fProc )(GLuint program, GLint location, GLfloat v0);
typedef void (OSG_APIENTRY * osgGlProgramUniform1fvProc )(GLuint program, GLint location, GLsizei count, const GLfloat *value);
typedef void (OSG_APIENTRY * osgGlProgramUniform1dProc )(GLuint program, GLint location, GLdouble v0);
typedef void (OSG_APIENTRY * osgGlProgramUniform1dvProc )(GLuint program, GLint location, GLsizei count, const GLdouble *value);
typedef void (OSG_APIENTRY * osgGlProgramUniform1uiProc )(GLuint program, GLint location, GLuint v0);
typedef void (OSG_APIENTRY * osgGlProgramUniform1uivProc )(GLuint program, GLint location, GLsizei count, const GLuint *value);
typedef void (OSG_APIENTRY * osgGlProgramUniform2iProc )(GLuint program, GLint location, GLint v0, GLint v1);
typedef void (OSG_APIENTRY * osgGlProgramUniform2ivProc )(GLuint program, GLint location, GLsizei count, const GLint *value);
typedef void (OSG_APIENTRY * osgGlProgramUniform2fProc )(GLuint program, GLint location, GLfloat v0, GLfloat v1);
typedef void (OSG_APIENTRY * osgGlProgramUniform2fvProc )(GLuint program, GLint location, GLsizei count, const GLfloat *value);
typedef void (OSG_APIENTRY * osgGlProgramUniform2dProc )(GLuint program, GLint location, GLdouble v0, GLdouble v1);
typedef void (OSG_APIENTRY * osgGlProgramUniform2dvProc )(GLuint program, GLint location, GLsizei count, const GLdouble *value);
typedef void (OSG_APIENTRY * osgGlProgramUniform2uiProc )(GLuint program, GLint location, GLuint v0, GLuint v1);
typedef void (OSG_APIENTRY * osgGlProgramUniform2uivProc )(GLuint program, GLint location, GLsizei count, const GLuint *value);
typedef void (OSG_APIENTRY * osgGlProgramUniform3iProc )(GLuint program, GLint location, GLint v0, GLint v1, GLint v2);
typedef void (OSG_APIENTRY * osgGlProgramUniform3ivProc )(GLuint program, GLint location, GLsizei count, const GLint *value);
typedef void (OSG_APIENTRY * osgGlProgramUniform3fProc )(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
typedef void (OSG_APIENTRY * osgGlProgramUniform3fvProc )(GLuint program, GLint location, GLsizei count, const GLfloat *value);
typedef void (OSG_APIENTRY * osgGlProgramUniform3dProc )(GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2);
typedef void (OSG_APIENTRY * osgGlProgramUniform3dvProc )(GLuint program, GLint location, GLsizei count, const GLdouble *value);
typedef void (OSG_APIENTRY * osgGlProgramUniform3uiProc )(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2);
typedef void (OSG_APIENTRY * osgGlProgramUniform3uivProc )(GLuint program, GLint location, GLsizei count, const GLuint *value);
typedef void (OSG_APIENTRY * osgGlProgramUniform4iProc )(GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
typedef void (OSG_APIENTRY * osgGlProgramUniform4ivProc )(GLuint program, GLint location, GLsizei count, const GLint *value);
typedef void (OSG_APIENTRY * osgGlProgramUniform4fProc )(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
typedef void (OSG_APIENTRY * osgGlProgramUniform4fvProc )(GLuint program, GLint location, GLsizei count, const GLfloat *value);
typedef void (OSG_APIENTRY * osgGlProgramUniform4dProc )(GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2, GLdouble v3);
typedef void (OSG_APIENTRY * osgGlProgramUniform4dvProc )(GLuint program, GLint location, GLsizei count, const GLdouble *value);
typedef void (OSG_APIENTRY * osgGlProgramUniform4uiProc )(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
typedef void (OSG_APIENTRY * osgGlProgramUniform4uivProc )(GLuint program, GLint location, GLsizei count, const GLuint *value);
typedef void (OSG_APIENTRY * osgGlProgramUniformMatrix2fvProc )(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (OSG_APIENTRY * osgGlProgramUniformMatrix3fvProc )(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (OSG_APIENTRY * osgGlProgramUniformMatrix4fvProc )(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (OSG_APIENTRY * osgGlProgramUniformMatrix2dvProc )(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (OSG_APIENTRY * osgGlProgramUniformMatrix3dvProc )(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (OSG_APIENTRY * osgGlProgramUniformMatrix4dvProc )(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (OSG_APIENTRY * osgGlProgramUniformMatrix2x3fvProc )(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (OSG_APIENTRY * osgGlProgramUniformMatrix3x2fvProc )(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (OSG_APIENTRY * osgGlProgramUniformMatrix2x4fvProc )(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (OSG_APIENTRY * osgGlProgramUniformMatrix4x2fvProc )(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (OSG_APIENTRY * osgGlProgramUniformMatrix3x4fvProc )(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (OSG_APIENTRY * osgGlProgramUniformMatrix4x3fvProc )(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (OSG_APIENTRY * osgGlProgramUniformMatrix2x3dvProc )(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (OSG_APIENTRY * osgGlProgramUniformMatrix3x2dvProc )(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (OSG_APIENTRY * osgGlProgramUniformMatrix2x4dvProc )(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (OSG_APIENTRY * osgGlProgramUniformMatrix4x2dvProc )(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (OSG_APIENTRY * osgGlProgramUniformMatrix3x4dvProc )(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (OSG_APIENTRY * osgGlProgramUniformMatrix4x3dvProc )(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (OSG_APIENTRY * osgGlValidateProgramPipelineProc )(GLuint pipeline);
typedef void (OSG_APIENTRY * osgGlGetProgramPipelineInfoLogProc )(GLuint pipeline, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
typedef void (OSG_APIENTRY * osgGlVertexAttribL1dProc )(GLuint index, GLdouble x);
typedef void (OSG_APIENTRY * osgGlVertexAttribL2dProc )(GLuint index, GLdouble x, GLdouble y);
typedef void (OSG_APIENTRY * osgGlVertexAttribL3dProc )(GLuint index, GLdouble x, GLdouble y, GLdouble z);
typedef void (OSG_APIENTRY * osgGlVertexAttribL4dProc )(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
typedef void (OSG_APIENTRY * osgGlVertexAttribL1dvProc )(GLuint index, const GLdouble *v);
typedef void (OSG_APIENTRY * osgGlVertexAttribL2dvProc )(GLuint index, const GLdouble *v);
typedef void (OSG_APIENTRY * osgGlVertexAttribL3dvProc )(GLuint index, const GLdouble *v);
typedef void (OSG_APIENTRY * osgGlVertexAttribL4dvProc )(GLuint index, const GLdouble *v);
typedef void (OSG_APIENTRY * osgGlVertexAttribLPointerProc )(GLuint index, GLint size, GLenum type, GLsizei stride, const void *pointer);
typedef void (OSG_APIENTRY * osgGlGetVertexAttribLdvProc )(GLuint index, GLenum pname, GLdouble *params);
typedef void (OSG_APIENTRY * osgGlViewportArrayvProc )(GLuint first, GLsizei count, const GLfloat *v);
typedef void (OSG_APIENTRY * osgGlViewportIndexedfProc )(GLuint index, GLfloat x, GLfloat y, GLfloat w, GLfloat h);
typedef void (OSG_APIENTRY * osgGlViewportIndexedfvProc )(GLuint index, const GLfloat *v);
typedef void (OSG_APIENTRY * osgGlScissorArrayvProc )(GLuint first, GLsizei count, const GLint *v);
typedef void (OSG_APIENTRY * osgGlScissorIndexedProc )(GLuint index, GLint left, GLint bottom, GLsizei width, GLsizei height);
typedef void (OSG_APIENTRY * osgGlScissorIndexedvProc )(GLuint index, const GLint *v);
typedef void (OSG_APIENTRY * osgGlDepthRangeArrayvProc )(GLuint first, GLsizei count, const GLdouble *v);
typedef void (OSG_APIENTRY * osgGlDepthRangeIndexedProc )(GLuint index, GLdouble n, GLdouble f);
typedef void (OSG_APIENTRY * osgGlGetFloati_vProc )(GLenum target, GLuint index, GLfloat *data);
typedef void (OSG_APIENTRY * osgGlGetDoublei_vProc )(GLenum target, GLuint index, GLdouble *data);
#endif /* GL_VERSION_4_1 */

#ifdef GL_VERSION_4_2
typedef void (OSG_APIENTRY * osgGlDrawArraysInstancedBaseInstanceProc )(GLenum mode, GLint first, GLsizei count, GLsizei instancecount, GLuint baseinstance);
typedef void (OSG_APIENTRY * osgGlDrawElementsInstancedBaseInstanceProc )(GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount, GLuint baseinstance);
typedef void (OSG_APIENTRY * osgGlDrawElementsInstancedBaseVertexBaseInstanceProc )(GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount, GLint basevertex, GLuint baseinstance);
typedef void (OSG_APIENTRY * osgGlGetInternalformativProc )(GLenum target, GLenum internalformat, GLenum pname, GLsizei bufSize, GLint *params);
typedef void (OSG_APIENTRY * osgGlGetActiveAtomicCounterBufferivProc )(GLuint program, GLuint bufferIndex, GLenum pname, GLint *params);
typedef void (OSG_APIENTRY * osgGlBindImageTextureProc )(GLuint unit, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLenum format);
typedef void (OSG_APIENTRY * osgGlMemoryBarrierProc )(GLbitfield barriers);
typedef void (OSG_APIENTRY * osgGlTexStorage1DProc )(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width);
typedef void (OSG_APIENTRY * osgGlTexStorage2DProc )(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (OSG_APIENTRY * osgGlTexStorage3DProc )(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth);
typedef void (OSG_APIENTRY * osgGlDrawTransformFeedbackInstancedProc )(GLenum mode, GLuint id, GLsizei instancecount);
typedef void (OSG_APIENTRY * osgGlDrawTransformFeedbackStreamInstancedProc )(GLenum mode, GLuint id, GLuint stream, GLsizei instancecount);
#endif /* GL_VERSION_4_2 */

#ifdef GL_VERSION_4_3
typedef void (OSG_APIENTRY * osgGlClearBufferDataProc )(GLenum target, GLenum internalformat, GLenum format, GLenum type, const void *data);
typedef void (OSG_APIENTRY * osgGlClearBufferSubDataProc )(GLenum target, GLenum internalformat, GLintptr offset, GLsizeiptr size, GLenum format, GLenum type, const void *data);
typedef void (OSG_APIENTRY * osgGlDispatchComputeProc )(GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z);
typedef void (OSG_APIENTRY * osgGlDispatchComputeIndirectProc )(GLintptr indirect);
typedef void (OSG_APIENTRY * osgGlCopyImageSubDataProc )(GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei srcWidth, GLsizei srcHeight, GLsizei srcDepth);
typedef void (OSG_APIENTRY * osgGlFramebufferParameteriProc )(GLenum target, GLenum pname, GLint param);
typedef void (OSG_APIENTRY * osgGlGetFramebufferParameterivProc )(GLenum target, GLenum pname, GLint *params);
typedef void (OSG_APIENTRY * osgGlGetInternalformati64vProc )(GLenum target, GLenum internalformat, GLenum pname, GLsizei bufSize, GLint64 *params);
typedef void (OSG_APIENTRY * osgGlInvalidateTexSubImageProc )(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth);
typedef void (OSG_APIENTRY * osgGlInvalidateTexImageProc )(GLuint texture, GLint level);
typedef void (OSG_APIENTRY * osgGlInvalidateBufferSubDataProc )(GLuint buffer, GLintptr offset, GLsizeiptr length);
typedef void (OSG_APIENTRY * osgGlInvalidateBufferDataProc )(GLuint buffer);
typedef void (OSG_APIENTRY * osgGlInvalidateFramebufferProc )(GLenum target, GLsizei numAttachments, const GLenum *attachments);
typedef void (OSG_APIENTRY * osgGlInvalidateSubFramebufferProc )(GLenum target, GLsizei numAttachments, const GLenum *attachments, GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (OSG_APIENTRY * osgGlMultiDrawArraysIndirectProc )(GLenum mode, const void *indirect, GLsizei drawcount, GLsizei stride);
typedef void (OSG_APIENTRY * osgGlMultiDrawElementsIndirectProc )(GLenum mode, GLenum type, const void *indirect, GLsizei drawcount, GLsizei stride);
typedef void (OSG_APIENTRY * osgGlGetProgramInterfaceivProc )(GLuint program, GLenum programInterface, GLenum pname, GLint *params);
typedef GLuint (OSG_APIENTRY * osgGlGetProgramResourceIndexProc )(GLuint program, GLenum programInterface, const GLchar *name);
typedef void (OSG_APIENTRY * osgGlGetProgramResourceNameProc )(GLuint program, GLenum programInterface, GLuint index, GLsizei bufSize, GLsizei *length, GLchar *name);
typedef void (OSG_APIENTRY * osgGlGetProgramResourceivProc )(GLuint program, GLenum programInterface, GLuint index, GLsizei propCount, const GLenum *props, GLsizei bufSize, GLsizei *length, GLint *params);
typedef GLint (OSG_APIENTRY * osgGlGetProgramResourceLocationProc )(GLuint program, GLenum programInterface, const GLchar *name);
typedef GLint (OSG_APIENTRY * osgGlGetProgramResourceLocationIndexProc )(GLuint program, GLenum programInterface, const GLchar *name);
typedef void (OSG_APIENTRY * osgGlShaderStorageBlockBindingProc )(GLuint program, GLuint storageBlockIndex, GLuint storageBlockBinding);
typedef void (OSG_APIENTRY * osgGlTexBufferRangeProc )(GLenum target, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size);
typedef void (OSG_APIENTRY * osgGlTexStorage2DMultisampleProc )(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
typedef void (OSG_APIENTRY * osgGlTexStorage3DMultisampleProc )(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations);
typedef void (OSG_APIENTRY * osgGlTextureViewProc )(GLuint texture, GLenum target, GLuint origtexture, GLenum internalformat, GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers);
typedef void (OSG_APIENTRY * osgGlBindVertexBufferProc )(GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride);
typedef void (OSG_APIENTRY * osgGlVertexAttribFormatProc )(GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset);
typedef void (OSG_APIENTRY * osgGlVertexAttribIFormatProc )(GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset);
typedef void (OSG_APIENTRY * osgGlVertexAttribLFormatProc )(GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset);
typedef void (OSG_APIENTRY * osgGlVertexAttribBindingProc )(GLuint attribindex, GLuint bindingindex);
typedef void (OSG_APIENTRY * osgGlVertexBindingDivisorProc )(GLuint bindingindex, GLuint divisor);
typedef void (OSG_APIENTRY * osgGlDebugMessageControlProc )(GLenum source, GLenum type, GLenum severity, GLsizei count, const GLuint *ids, GLboolean enabled);
typedef void (OSG_APIENTRY * osgGlDebugMessageInsertProc )(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *buf);
typedef void (OSG_APIENTRY * osgGlDebugMessageCallbackProc )(GLDEBUGPROC callback, const void *userParam);
typedef GLuint (OSG_APIENTRY * osgGlGetDebugMessageLogProc )(GLuint count, GLsizei bufSize, GLenum *sources, GLenum *types, GLuint *ids, GLenum *severities, GLsizei *lengths, GLchar *messageLog);
typedef void (OSG_APIENTRY * osgGlPushDebugGroupProc )(GLenum source, GLuint id, GLsizei length, const GLchar *message);
typedef void (OSG_APIENTRY * osgGlPopDebugGroupProc )(void);
typedef void (OSG_APIENTRY * osgGlObjectLabelProc )(GLenum identifier, GLuint name, GLsizei length, const GLchar *label);
typedef void (OSG_APIENTRY * osgGlGetObjectLabelProc )(GLenum identifier, GLuint name, GLsizei bufSize, GLsizei *length, GLchar *label);
typedef void (OSG_APIENTRY * osgGlObjectPtrLabelProc )(const void *ptr, GLsizei length, const GLchar *label);
typedef void (OSG_APIENTRY * osgGlGetObjectPtrLabelProc )(const void *ptr, GLsizei bufSize, GLsizei *length, GLchar *label);
#endif /* GL_VERSION_4_3 */

#ifdef GL_VERSION_4_4
typedef void (OSG_APIENTRY * osgGlBufferStorageProc )(GLenum target, GLsizeiptr size, const void *data, GLbitfield flags);
typedef void (OSG_APIENTRY * osgGlClearTexImageProc )(GLuint texture, GLint level, GLenum format, GLenum type, const void *data);
typedef void (OSG_APIENTRY * osgGlClearTexSubImageProc )(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *data);
typedef void (OSG_APIENTRY * osgGlBindBuffersBaseProc )(GLenum target, GLuint first, GLsizei count, const GLuint *buffers);
typedef void (OSG_APIENTRY * osgGlBindBuffersRangeProc )(GLenum target, GLuint first, GLsizei count, const GLuint *buffers, const GLintptr *offsets, const GLsizeiptr *sizes);
typedef void (OSG_APIENTRY * osgGlBindTexturesProc )(GLuint first, GLsizei count, const GLuint *textures);
typedef void (OSG_APIENTRY * osgGlBindSamplersProc )(GLuint first, GLsizei count, const GLuint *samplers);
typedef void (OSG_APIENTRY * osgGlBindImageTexturesProc )(GLuint first, GLsizei count, const GLuint *textures);
typedef void (OSG_APIENTRY * osgGlBindVertexBuffersProc )(GLuint first, GLsizei count, const GLuint *buffers, const GLintptr *offsets, const GLsizei *strides);
#endif /* GL_VERSION_4_4 */

#ifdef GL_VERSION_4_5
typedef void (OSG_APIENTRY * osgGlClipControlProc )(GLenum origin, GLenum depth);
typedef void (OSG_APIENTRY * osgGlCreateTransformFeedbacksProc )(GLsizei n, GLuint *ids);
typedef void (OSG_APIENTRY * osgGlTransformFeedbackBufferBaseProc )(GLuint xfb, GLuint index, GLuint buffer);
typedef void (OSG_APIENTRY * osgGlTransformFeedbackBufferRangeProc )(GLuint xfb, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size);
typedef void (OSG_APIENTRY * osgGlGetTransformFeedbackivProc )(GLuint xfb, GLenum pname, GLint *param);
typedef void (OSG_APIENTRY * osgGlGetTransformFeedbacki_vProc )(GLuint xfb, GLenum pname, GLuint index, GLint *param);
typedef void (OSG_APIENTRY * osgGlGetTransformFeedbacki64_vProc )(GLuint xfb, GLenum pname, GLuint index, GLint64 *param);
typedef void (OSG_APIENTRY * osgGlCreateBuffersProc )(GLsizei n, GLuint *buffers);
typedef void (OSG_APIENTRY * osgGlNamedBufferStorageProc )(GLuint buffer, GLsizeiptr size, const void *data, GLbitfield flags);
typedef void (OSG_APIENTRY * osgGlNamedBufferDataProc )(GLuint buffer, GLsizeiptr size, const void *data, GLenum usage);
typedef void (OSG_APIENTRY * osgGlNamedBufferSubDataProc )(GLuint buffer, GLintptr offset, GLsizeiptr size, const void *data);
typedef void (OSG_APIENTRY * osgGlCopyNamedBufferSubDataProc )(GLuint readBuffer, GLuint writeBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size);
typedef void (OSG_APIENTRY * osgGlClearNamedBufferDataProc )(GLuint buffer, GLenum internalformat, GLenum format, GLenum type, const void *data);
typedef void (OSG_APIENTRY * osgGlClearNamedBufferSubDataProc )(GLuint buffer, GLenum internalformat, GLintptr offset, GLsizeiptr size, GLenum format, GLenum type, const void *data);
typedef void *(OSG_APIENTRY * osgGlMapNamedBufferProc )(GLuint buffer, GLenum access);
typedef void *(OSG_APIENTRY * osgGlMapNamedBufferRangeProc )(GLuint buffer, GLintptr offset, GLsizeiptr length, GLbitfield access);
typedef GLboolean (OSG_APIENTRY * osgGlUnmapNamedBufferProc )(GLuint buffer);
typedef void (OSG_APIENTRY * osgGlFlushMappedNamedBufferRangeProc )(GLuint buffer, GLintptr offset, GLsizeiptr length);
typedef void (OSG_APIENTRY * osgGlGetNamedBufferParameterivProc )(GLuint buffer, GLenum pname, GLint *params);
typedef void (OSG_APIENTRY * osgGlGetNamedBufferParameteri64vProc )(GLuint buffer, GLenum pname, GLint64 *params);
typedef void (OSG_APIENTRY * osgGlGetNamedBufferPointervProc )(GLuint buffer, GLenum pname, void **params);
typedef void (OSG_APIENTRY * osgGlGetNamedBufferSubDataProc )(GLuint buffer, GLintptr offset, GLsizeiptr size, void *data);
typedef void (OSG_APIENTRY * osgGlCreateFramebuffersProc )(GLsizei n, GLuint *framebuffers);
typedef void (OSG_APIENTRY * osgGlNamedFramebufferRenderbufferProc )(GLuint framebuffer, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
typedef void (OSG_APIENTRY * osgGlNamedFramebufferParameteriProc )(GLuint framebuffer, GLenum pname, GLint param);
typedef void (OSG_APIENTRY * osgGlNamedFramebufferTextureProc )(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level);
typedef void (OSG_APIENTRY * osgGlNamedFramebufferTextureLayerProc )(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, GLint layer);
typedef void (OSG_APIENTRY * osgGlNamedFramebufferDrawBufferProc )(GLuint framebuffer, GLenum buf);
typedef void (OSG_APIENTRY * osgGlNamedFramebufferDrawBuffersProc )(GLuint framebuffer, GLsizei n, const GLenum *bufs);
typedef void (OSG_APIENTRY * osgGlNamedFramebufferReadBufferProc )(GLuint framebuffer, GLenum src);
typedef void (OSG_APIENTRY * osgGlInvalidateNamedFramebufferDataProc )(GLuint framebuffer, GLsizei numAttachments, const GLenum *attachments);
typedef void (OSG_APIENTRY * osgGlInvalidateNamedFramebufferSubDataProc )(GLuint framebuffer, GLsizei numAttachments, const GLenum *attachments, GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (OSG_APIENTRY * osgGlClearNamedFramebufferivProc )(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLint *value);
typedef void (OSG_APIENTRY * osgGlClearNamedFramebufferuivProc )(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLuint *value);
typedef void (OSG_APIENTRY * osgGlClearNamedFramebufferfvProc )(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLfloat *value);
typedef void (OSG_APIENTRY * osgGlClearNamedFramebufferfiProc )(GLuint framebuffer, GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil);
typedef void (OSG_APIENTRY * osgGlBlitNamedFramebufferProc )(GLuint readFramebuffer, GLuint drawFramebuffer, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);
typedef GLenum (OSG_APIENTRY * osgGlCheckNamedFramebufferStatusProc )(GLuint framebuffer, GLenum target);
typedef void (OSG_APIENTRY * osgGlGetNamedFramebufferParameterivProc )(GLuint framebuffer, GLenum pname, GLint *param);
typedef void (OSG_APIENTRY * osgGlGetNamedFramebufferAttachmentParameterivProc )(GLuint framebuffer, GLenum attachment, GLenum pname, GLint *params);
typedef void (OSG_APIENTRY * osgGlCreateRenderbuffersProc )(GLsizei n, GLuint *renderbuffers);
typedef void (OSG_APIENTRY * osgGlNamedRenderbufferStorageProc )(GLuint renderbuffer, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (OSG_APIENTRY * osgGlNamedRenderbufferStorageMultisampleProc )(GLuint renderbuffer, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (OSG_APIENTRY * osgGlGetNamedRenderbufferParameterivProc )(GLuint renderbuffer, GLenum pname, GLint *params);
typedef void (OSG_APIENTRY * osgGlCreateTexturesProc )(GLenum target, GLsizei n, GLuint *textures);
typedef void (OSG_APIENTRY * osgGlTextureBufferProc )(GLuint texture, GLenum internalformat, GLuint buffer);
typedef void (OSG_APIENTRY * osgGlTextureBufferRangeProc )(GLuint texture, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size);
typedef void (OSG_APIENTRY * osgGlTextureStorage1DProc )(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width);
typedef void (OSG_APIENTRY * osgGlTextureStorage2DProc )(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (OSG_APIENTRY * osgGlTextureStorage3DProc )(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth);
typedef void (OSG_APIENTRY * osgGlTextureStorage2DMultisampleProc )(GLuint texture, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
typedef void (OSG_APIENTRY * osgGlTextureStorage3DMultisampleProc )(GLuint texture, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations);
typedef void (OSG_APIENTRY * osgGlTextureSubImage1DProc )(GLuint texture, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void *pixels);
typedef void (OSG_APIENTRY * osgGlTextureSubImage2DProc )(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void *pixels);
typedef void (OSG_APIENTRY * osgGlTextureSubImage3DProc )(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *pixels);
typedef void (OSG_APIENTRY * osgGlCompressedTextureSubImage1DProc )(GLuint texture, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void *data);
typedef void (OSG_APIENTRY * osgGlCompressedTextureSubImage2DProc )(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void *data);
typedef void (OSG_APIENTRY * osgGlCompressedTextureSubImage3DProc )(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void *data);
typedef void (OSG_APIENTRY * osgGlCopyTextureSubImage1DProc )(GLuint texture, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width);
typedef void (OSG_APIENTRY * osgGlCopyTextureSubImage2DProc )(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (OSG_APIENTRY * osgGlCopyTextureSubImage3DProc )(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (OSG_APIENTRY * osgGlTextureParameterfProc )(GLuint texture, GLenum pname, GLfloat param);
typedef void (OSG_APIENTRY * osgGlTextureParameterfvProc )(GLuint texture, GLenum pname, const GLfloat *param);
typedef void (OSG_APIENTRY * osgGlTextureParameteriProc )(GLuint texture, GLenum pname, GLint param);
typedef void (OSG_APIENTRY * osgGlTextureParameterIivProc )(GLuint texture, GLenum pname, const GLint *params);
typedef void (OSG_APIENTRY * osgGlTextureParameterIuivProc )(GLuint texture, GLenum pname, const GLuint *params);
typedef void (OSG_APIENTRY * osgGlTextureParameterivProc )(GLuint texture, GLenum pname, const GLint *param);
typedef void (OSG_APIENTRY * osgGlGenerateTextureMipmapProc )(GLuint texture);
typedef void (OSG_APIENTRY * osgGlBindTextureUnitProc )(GLuint unit, GLuint texture);
typedef void (OSG_APIENTRY * osgGlGetTextureImageProc )(GLuint texture, GLint level, GLenum format, GLenum type, GLsizei bufSize, void *pixels);
typedef void (OSG_APIENTRY * osgGlGetCompressedTextureImageProc )(GLuint texture, GLint level, GLsizei bufSize, void *pixels);
typedef void (OSG_APIENTRY * osgGlGetTextureLevelParameterfvProc )(GLuint texture, GLint level, GLenum pname, GLfloat *params);
typedef void (OSG_APIENTRY * osgGlGetTextureLevelParameterivProc )(GLuint texture, GLint level, GLenum pname, GLint *params);
typedef void (OSG_APIENTRY * osgGlGetTextureParameterfvProc )(GLuint texture, GLenum pname, GLfloat *params);
typedef void (OSG_APIENTRY * osgGlGetTextureParameterIivProc )(GLuint texture, GLenum pname, GLint *params);
typedef void (OSG_APIENTRY * osgGlGetTextureParameterIuivProc )(GLuint texture, GLenum pname, GLuint *params);
typedef void (OSG_APIENTRY * osgGlGetTextureParameterivProc )(GLuint texture, GLenum pname, GLint *params);
typedef void (OSG_APIENTRY * osgGlCreateVertexArraysProc )(GLsizei n, GLuint *arrays);
typedef void (OSG_APIENTRY * osgGlDisableVertexArrayAttribProc )(GLuint vaobj, GLuint index);
typedef void (OSG_APIENTRY * osgGlEnableVertexArrayAttribProc )(GLuint vaobj, GLuint index);
typedef void (OSG_APIENTRY * osgGlVertexArrayElementBufferProc )(GLuint vaobj, GLuint buffer);
typedef void (OSG_APIENTRY * osgGlVertexArrayVertexBufferProc )(GLuint vaobj, GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride);
typedef void (OSG_APIENTRY * osgGlVertexArrayVertexBuffersProc )(GLuint vaobj, GLuint first, GLsizei count, const GLuint *buffers, const GLintptr *offsets, const GLsizei *strides);
typedef void (OSG_APIENTRY * osgGlVertexArrayAttribBindingProc )(GLuint vaobj, GLuint attribindex, GLuint bindingindex);
typedef void (OSG_APIENTRY * osgGlVertexArrayAttribFormatProc )(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset);
typedef void (OSG_APIENTRY * osgGlVertexArrayAttribIFormatProc )(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset);
typedef void (OSG_APIENTRY * osgGlVertexArrayAttribLFormatProc )(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset);
typedef void (OSG_APIENTRY * osgGlVertexArrayBindingDivisorProc )(GLuint vaobj, GLuint bindingindex, GLuint divisor);
typedef void (OSG_APIENTRY * osgGlGetVertexArrayivProc )(GLuint vaobj, GLenum pname, GLint *param);
typedef void (OSG_APIENTRY * osgGlGetVertexArrayIndexedivProc )(GLuint vaobj, GLuint index, GLenum pname, GLint *param);
typedef void (OSG_APIENTRY * osgGlGetVertexArrayIndexed64ivProc )(GLuint vaobj, GLuint index, GLenum pname, GLint64 *param);
typedef void (OSG_APIENTRY * osgGlCreateSamplersProc )(GLsizei n, GLuint *samplers);
typedef void (OSG_APIENTRY * osgGlCreateProgramPipelinesProc )(GLsizei n, GLuint *pipelines);
typedef void (OSG_APIENTRY * osgGlCreateQueriesProc )(GLenum target, GLsizei n, GLuint *ids);
typedef void (OSG_APIENTRY * osgGlGetQueryBufferObjecti64vProc )(GLuint id, GLuint buffer, GLenum pname, GLintptr offset);
typedef void (OSG_APIENTRY * osgGlGetQueryBufferObjectivProc )(GLuint id, GLuint buffer, GLenum pname, GLintptr offset);
typedef void (OSG_APIENTRY * osgGlGetQueryBufferObjectui64vProc )(GLuint id, GLuint buffer, GLenum pname, GLintptr offset);
typedef void (OSG_APIENTRY * osgGlGetQueryBufferObjectuivProc )(GLuint id, GLuint buffer, GLenum pname, GLintptr offset);
typedef void (OSG_APIENTRY * osgGlMemoryBarrierByRegionProc )(GLbitfield barriers);
typedef void (OSG_APIENTRY * osgGlGetTextureSubImageProc )(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, GLsizei bufSize, void *pixels);
typedef void (OSG_APIENTRY * osgGlGetCompressedTextureSubImageProc )(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLsizei bufSize, void *pixels);
typedef GLenum (OSG_APIENTRY * osgGlGetGraphicsResetStatusProc )(void);
typedef void (OSG_APIENTRY * osgGlGetnCompressedTexImageProc )(GLenum target, GLint lod, GLsizei bufSize, void *pixels);
typedef void (OSG_APIENTRY * osgGlGetnTexImageProc )(GLenum target, GLint level, GLenum format, GLenum type, GLsizei bufSize, void *pixels);
typedef void (OSG_APIENTRY * osgGlGetnUniformdvProc )(GLuint program, GLint location, GLsizei bufSize, GLdouble *params);
typedef void (OSG_APIENTRY * osgGlGetnUniformfvProc )(GLuint program, GLint location, GLsizei bufSize, GLfloat *params);
typedef void (OSG_APIENTRY * osgGlGetnUniformivProc )(GLuint program, GLint location, GLsizei bufSize, GLint *params);
typedef void (OSG_APIENTRY * osgGlGetnUniformuivProc )(GLuint program, GLint location, GLsizei bufSize, GLuint *params);
typedef void (OSG_APIENTRY * osgGlReadnPixelsProc )(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLsizei bufSize, void *data);
typedef void (OSG_APIENTRY * osgGlGetnMapdvProc )(GLenum target, GLenum query, GLsizei bufSize, GLdouble *v);
typedef void (OSG_APIENTRY * osgGlGetnMapfvProc )(GLenum target, GLenum query, GLsizei bufSize, GLfloat *v);
typedef void (OSG_APIENTRY * osgGlGetnMapivProc )(GLenum target, GLenum query, GLsizei bufSize, GLint *v);
typedef void (OSG_APIENTRY * osgGlGetnPixelMapfvProc )(GLenum map, GLsizei bufSize, GLfloat *values);
typedef void (OSG_APIENTRY * osgGlGetnPixelMapuivProc )(GLenum map, GLsizei bufSize, GLuint *values);
typedef void (OSG_APIENTRY * osgGlGetnPixelMapusvProc )(GLenum map, GLsizei bufSize, GLushort *values);
typedef void (OSG_APIENTRY * osgGlGetnPolygonStippleProc )(GLsizei bufSize, GLubyte *pattern);
typedef void (OSG_APIENTRY * osgGlGetnColorTableProc )(GLenum target, GLenum format, GLenum type, GLsizei bufSize, void *table);
typedef void (OSG_APIENTRY * osgGlGetnConvolutionFilterProc )(GLenum target, GLenum format, GLenum type, GLsizei bufSize, void *image);
typedef void (OSG_APIENTRY * osgGlGetnSeparableFilterProc )(GLenum target, GLenum format, GLenum type, GLsizei rowBufSize, void *row, GLsizei columnBufSize, void *column, void *span);
typedef void (OSG_APIENTRY * osgGlGetnHistogramProc )(GLenum target, GLboolean reset, GLenum format, GLenum type, GLsizei bufSize, void *values);
typedef void (OSG_APIENTRY * osgGlGetnMinmaxProc )(GLenum target, GLboolean reset, GLenum format, GLenum type, GLsizei bufSize, void *values);
typedef void (OSG_APIENTRY * osgGlTextureBarrierProc )(void);
#endif /* GL_VERSION_4_5 */

#ifdef GL_ARB_ES2_compatibility
#endif /* GL_ARB_ES2_compatibility */

#ifdef GL_ARB_ES3_1_compatibility
#endif /* GL_ARB_ES3_1_compatibility */

#ifdef GL_ARB_ES3_2_compatibility
typedef void (OSG_APIENTRY * osgGlPrimitiveBoundingBoxARBProc )(GLfloat minX, GLfloat minY, GLfloat minZ, GLfloat minW, GLfloat maxX, GLfloat maxY, GLfloat maxZ, GLfloat maxW);
#endif /* GL_ARB_ES3_2_compatibility */

#ifdef GL_ARB_ES3_compatibility
#endif /* GL_ARB_ES3_compatibility */

#ifdef GL_ARB_arrays_of_arrays
#endif /* GL_ARB_arrays_of_arrays */

#ifdef GL_ARB_base_instance
#endif /* GL_ARB_base_instance */

#ifdef GL_ARB_bindless_texture
typedef GLuint64 (OSG_APIENTRY * osgGlGetTextureHandleARBProc )(GLuint texture);
typedef GLuint64 (OSG_APIENTRY * osgGlGetTextureSamplerHandleARBProc )(GLuint texture, GLuint sampler);
typedef void (OSG_APIENTRY * osgGlMakeTextureHandleResidentARBProc )(GLuint64 handle);
typedef void (OSG_APIENTRY * osgGlMakeTextureHandleNonResidentARBProc )(GLuint64 handle);
typedef GLuint64 (OSG_APIENTRY * osgGlGetImageHandleARBProc )(GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum format);
typedef void (OSG_APIENTRY * osgGlMakeImageHandleResidentARBProc )(GLuint64 handle, GLenum access);
typedef void (OSG_APIENTRY * osgGlMakeImageHandleNonResidentARBProc )(GLuint64 handle);
typedef void (OSG_APIENTRY * osgGlUniformHandleui64ARBProc )(GLint location, GLuint64 value);
typedef void (OSG_APIENTRY * osgGlUniformHandleui64vARBProc )(GLint location, GLsizei count, const GLuint64 *value);
typedef void (OSG_APIENTRY * osgGlProgramUniformHandleui64ARBProc )(GLuint program, GLint location, GLuint64 value);
typedef void (OSG_APIENTRY * osgGlProgramUniformHandleui64vARBProc )(GLuint program, GLint location, GLsizei count, const GLuint64 *values);
typedef GLboolean (OSG_APIENTRY * osgGlIsTextureHandleResidentARBProc )(GLuint64 handle);
typedef GLboolean (OSG_APIENTRY * osgGlIsImageHandleResidentARBProc )(GLuint64 handle);
typedef void (OSG_APIENTRY * osgGlVertexAttribL1ui64ARBProc )(GLuint index, GLuint64EXT x);
typedef void (OSG_APIENTRY * osgGlVertexAttribL1ui64vARBProc )(GLuint index, const GLuint64EXT *v);
typedef void (OSG_APIENTRY * osgGlGetVertexAttribLui64vARBProc )(GLuint index, GLenum pname, GLuint64EXT *params);
#endif /* GL_ARB_bindless_texture */

#ifdef GL_ARB_blend_func_extended
#endif /* GL_ARB_blend_func_extended */

#ifdef GL_ARB_buffer_storage
#endif /* GL_ARB_buffer_storage */

#ifdef GL_ARB_cl_event
typedef GLsync (OSG_APIENTRY * osgGlCreateSyncFromCLeventARBProc )(struct _cl_context *context, struct _cl_event *event, GLbitfield flags);
#endif /* GL_ARB_cl_event */

#ifdef GL_ARB_clear_buffer_object
#endif /* GL_ARB_clear_buffer_object */

#ifdef GL_ARB_clear_texture
#endif /* GL_ARB_clear_texture */

#ifdef GL_ARB_clip_control
#endif /* GL_ARB_clip_control */

#ifdef GL_ARB_color_buffer_float
typedef void (OSG_APIENTRY * osgGlClampColorARBProc )(GLenum target, GLenum clamp);
#endif /* GL_ARB_color_buffer_float */

#ifdef GL_ARB_compatibility
#endif /* GL_ARB_compatibility */

#ifdef GL_ARB_compressed_texture_pixel_storage
#endif /* GL_ARB_compressed_texture_pixel_storage */

#ifdef GL_ARB_compute_shader
#endif /* GL_ARB_compute_shader */

#ifdef GL_ARB_compute_variable_group_size
typedef void (OSG_APIENTRY * osgGlDispatchComputeGroupSizeARBProc )(GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z, GLuint group_size_x, GLuint group_size_y, GLuint group_size_z);
#endif /* GL_ARB_compute_variable_group_size */

#ifdef GL_ARB_conditional_render_inverted
#endif /* GL_ARB_conditional_render_inverted */

#ifdef GL_ARB_conservative_depth
#endif /* GL_ARB_conservative_depth */

#ifdef GL_ARB_copy_buffer
#endif /* GL_ARB_copy_buffer */

#ifdef GL_ARB_copy_image
#endif /* GL_ARB_copy_image */

#ifdef GL_ARB_cull_distance
#endif /* GL_ARB_cull_distance */

#ifdef GL_ARB_debug_output
typedef void (OSG_APIENTRY * osgGlDebugMessageControlARBProc )(GLenum source, GLenum type, GLenum severity, GLsizei count, const GLuint *ids, GLboolean enabled);
typedef void (OSG_APIENTRY * osgGlDebugMessageInsertARBProc )(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *buf);
typedef void (OSG_APIENTRY * osgGlDebugMessageCallbackARBProc )(GLDEBUGPROCARB callback, const void *userParam);
typedef GLuint (OSG_APIENTRY * osgGlGetDebugMessageLogARBProc )(GLuint count, GLsizei bufSize, GLenum *sources, GLenum *types, GLuint *ids, GLenum *severities, GLsizei *lengths, GLchar *messageLog);
#endif /* GL_ARB_debug_output */

#ifdef GL_ARB_depth_buffer_float
#endif /* GL_ARB_depth_buffer_float */

#ifdef GL_ARB_depth_clamp
#endif /* GL_ARB_depth_clamp */

#ifdef GL_ARB_depth_texture
#endif /* GL_ARB_depth_texture */

#ifdef GL_ARB_derivative_control
#endif /* GL_ARB_derivative_control */

#ifdef GL_ARB_direct_state_access
#endif /* GL_ARB_direct_state_access */

#ifdef GL_ARB_draw_buffers
typedef void (OSG_APIENTRY * osgGlDrawBuffersARBProc )(GLsizei n, const GLenum *bufs);
#endif /* GL_ARB_draw_buffers */

#ifdef GL_ARB_draw_buffers_blend
typedef void (OSG_APIENTRY * osgGlBlendEquationiARBProc )(GLuint buf, GLenum mode);
typedef void (OSG_APIENTRY * osgGlBlendEquationSeparateiARBProc )(GLuint buf, GLenum modeRGB, GLenum modeAlpha);
typedef void (OSG_APIENTRY * osgGlBlendFunciARBProc )(GLuint buf, GLenum src, GLenum dst);
typedef void (OSG_APIENTRY * osgGlBlendFuncSeparateiARBProc )(GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
#endif /* GL_ARB_draw_buffers_blend */

#ifdef GL_ARB_draw_elements_base_vertex
#endif /* GL_ARB_draw_elements_base_vertex */

#ifdef GL_ARB_draw_indirect
#endif /* GL_ARB_draw_indirect */

#ifdef GL_ARB_draw_instanced
typedef void (OSG_APIENTRY * osgGlDrawArraysInstancedARBProc )(GLenum mode, GLint first, GLsizei count, GLsizei primcount);
typedef void (OSG_APIENTRY * osgGlDrawElementsInstancedARBProc )(GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei primcount);
#endif /* GL_ARB_draw_instanced */

#ifdef GL_ARB_enhanced_layouts
#endif /* GL_ARB_enhanced_layouts */

#ifdef GL_ARB_explicit_attrib_location
#endif /* GL_ARB_explicit_attrib_location */

#ifdef GL_ARB_explicit_uniform_location
#endif /* GL_ARB_explicit_uniform_location */

#ifdef GL_ARB_fragment_coord_conventions
#endif /* GL_ARB_fragment_coord_conventions */

#ifdef GL_ARB_fragment_layer_viewport
#endif /* GL_ARB_fragment_layer_viewport */

#ifdef GL_ARB_fragment_program
typedef void (OSG_APIENTRY * osgGlProgramStringARBProc )(GLenum target, GLenum format, GLsizei len, const void *string);
typedef void (OSG_APIENTRY * osgGlBindProgramARBProc )(GLenum target, GLuint program);
typedef void (OSG_APIENTRY * osgGlDeleteProgramsARBProc )(GLsizei n, const GLuint *programs);
typedef void (OSG_APIENTRY * osgGlGenProgramsARBProc )(GLsizei n, GLuint *programs);
typedef void (OSG_APIENTRY * osgGlProgramEnvParameter4dARBProc )(GLenum target, GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
typedef void (OSG_APIENTRY * osgGlProgramEnvParameter4dvARBProc )(GLenum target, GLuint index, const GLdouble *params);
typedef void (OSG_APIENTRY * osgGlProgramEnvParameter4fARBProc )(GLenum target, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
typedef void (OSG_APIENTRY * osgGlProgramEnvParameter4fvARBProc )(GLenum target, GLuint index, const GLfloat *params);
typedef void (OSG_APIENTRY * osgGlProgramLocalParameter4dARBProc )(GLenum target, GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
typedef void (OSG_APIENTRY * osgGlProgramLocalParameter4dvARBProc )(GLenum target, GLuint index, const GLdouble *params);
typedef void (OSG_APIENTRY * osgGlProgramLocalParameter4fARBProc )(GLenum target, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
typedef void (OSG_APIENTRY * osgGlProgramLocalParameter4fvARBProc )(GLenum target, GLuint index, const GLfloat *params);
typedef void (OSG_APIENTRY * osgGlGetProgramEnvParameterdvARBProc )(GLenum target, GLuint index, GLdouble *params);
typedef void (OSG_APIENTRY * osgGlGetProgramEnvParameterfvARBProc )(GLenum target, GLuint index, GLfloat *params);
typedef void (OSG_APIENTRY * osgGlGetProgramLocalParameterdvARBProc )(GLenum target, GLuint index, GLdouble *params);
typedef void (OSG_APIENTRY * osgGlGetProgramLocalParameterfvARBProc )(GLenum target, GLuint index, GLfloat *params);
typedef void (OSG_APIENTRY * osgGlGetProgramivARBProc )(GLenum target, GLenum pname, GLint *params);
typedef void (OSG_APIENTRY * osgGlGetProgramStringARBProc )(GLenum target, GLenum pname, void *string);
typedef GLboolean (OSG_APIENTRY * osgGlIsProgramARBProc )(GLuint program);
#endif /* GL_ARB_fragment_program */

#ifdef GL_ARB_fragment_program_shadow
#endif /* GL_ARB_fragment_program_shadow */

#ifdef GL_ARB_fragment_shader
#endif /* GL_ARB_fragment_shader */

#ifdef GL_ARB_fragment_shader_interlock
#endif /* GL_ARB_fragment_shader_interlock */

#ifdef GL_ARB_framebuffer_no_attachments
#endif /* GL_ARB_framebuffer_no_attachments */

#ifdef GL_ARB_framebuffer_object
#endif /* GL_ARB_framebuffer_object */

#ifdef GL_ARB_framebuffer_sRGB
#endif /* GL_ARB_framebuffer_sRGB */

#ifdef GL_ARB_geometry_shader4
typedef void (OSG_APIENTRY * osgGlProgramParameteriARBProc )(GLuint program, GLenum pname, GLint value);
typedef void (OSG_APIENTRY * osgGlFramebufferTextureARBProc )(GLenum target, GLenum attachment, GLuint texture, GLint level);
typedef void (OSG_APIENTRY * osgGlFramebufferTextureLayerARBProc )(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer);
typedef void (OSG_APIENTRY * osgGlFramebufferTextureFaceARBProc )(GLenum target, GLenum attachment, GLuint texture, GLint level, GLenum face);
#endif /* GL_ARB_geometry_shader4 */

#ifdef GL_ARB_get_program_binary
#endif /* GL_ARB_get_program_binary */

#ifdef GL_ARB_get_texture_sub_image
#endif /* GL_ARB_get_texture_sub_image */

#ifdef GL_ARB_gpu_shader5
#endif /* GL_ARB_gpu_shader5 */

#ifdef GL_ARB_gpu_shader_fp64
#endif /* GL_ARB_gpu_shader_fp64 */

#ifdef GL_ARB_gpu_shader_int64
typedef void (OSG_APIENTRY * osgGlUniform1i64ARBProc )(GLint location, GLint64 x);
typedef void (OSG_APIENTRY * osgGlUniform2i64ARBProc )(GLint location, GLint64 x, GLint64 y);
typedef void (OSG_APIENTRY * osgGlUniform3i64ARBProc )(GLint location, GLint64 x, GLint64 y, GLint64 z);
typedef void (OSG_APIENTRY * osgGlUniform4i64ARBProc )(GLint location, GLint64 x, GLint64 y, GLint64 z, GLint64 w);
typedef void (OSG_APIENTRY * osgGlUniform1i64vARBProc )(GLint location, GLsizei count, const GLint64 *value);
typedef void (OSG_APIENTRY * osgGlUniform2i64vARBProc )(GLint location, GLsizei count, const GLint64 *value);
typedef void (OSG_APIENTRY * osgGlUniform3i64vARBProc )(GLint location, GLsizei count, const GLint64 *value);
typedef void (OSG_APIENTRY * osgGlUniform4i64vARBProc )(GLint location, GLsizei count, const GLint64 *value);
typedef void (OSG_APIENTRY * osgGlUniform1ui64ARBProc )(GLint location, GLuint64 x);
typedef void (OSG_APIENTRY * osgGlUniform2ui64ARBProc )(GLint location, GLuint64 x, GLuint64 y);
typedef void (OSG_APIENTRY * osgGlUniform3ui64ARBProc )(GLint location, GLuint64 x, GLuint64 y, GLuint64 z);
typedef void (OSG_APIENTRY * osgGlUniform4ui64ARBProc )(GLint location, GLuint64 x, GLuint64 y, GLuint64 z, GLuint64 w);
typedef void (OSG_APIENTRY * osgGlUniform1ui64vARBProc )(GLint location, GLsizei count, const GLuint64 *value);
typedef void (OSG_APIENTRY * osgGlUniform2ui64vARBProc )(GLint location, GLsizei count, const GLuint64 *value);
typedef void (OSG_APIENTRY * osgGlUniform3ui64vARBProc )(GLint location, GLsizei count, const GLuint64 *value);
typedef void (OSG_APIENTRY * osgGlUniform4ui64vARBProc )(GLint location, GLsizei count, const GLuint64 *value);
typedef void (OSG_APIENTRY * osgGlGetUniformi64vARBProc )(GLuint program, GLint location, GLint64 *params);
typedef void (OSG_APIENTRY * osgGlGetUniformui64vARBProc )(GLuint program, GLint location, GLuint64 *params);
typedef void (OSG_APIENTRY * osgGlGetnUniformi64vARBProc )(GLuint program, GLint location, GLsizei bufSize, GLint64 *params);
typedef void (OSG_APIENTRY * osgGlGetnUniformui64vARBProc )(GLuint program, GLint location, GLsizei bufSize, GLuint64 *params);
typedef void (OSG_APIENTRY * osgGlProgramUniform1i64ARBProc )(GLuint program, GLint location, GLint64 x);
typedef void (OSG_APIENTRY * osgGlProgramUniform2i64ARBProc )(GLuint program, GLint location, GLint64 x, GLint64 y);
typedef void (OSG_APIENTRY * osgGlProgramUniform3i64ARBProc )(GLuint program, GLint location, GLint64 x, GLint64 y, GLint64 z);
typedef void (OSG_APIENTRY * osgGlProgramUniform4i64ARBProc )(GLuint program, GLint location, GLint64 x, GLint64 y, GLint64 z, GLint64 w);
typedef void (OSG_APIENTRY * osgGlProgramUniform1i64vARBProc )(GLuint program, GLint location, GLsizei count, const GLint64 *value);
typedef void (OSG_APIENTRY * osgGlProgramUniform2i64vARBProc )(GLuint program, GLint location, GLsizei count, const GLint64 *value);
typedef void (OSG_APIENTRY * osgGlProgramUniform3i64vARBProc )(GLuint program, GLint location, GLsizei count, const GLint64 *value);
typedef void (OSG_APIENTRY * osgGlProgramUniform4i64vARBProc )(GLuint program, GLint location, GLsizei count, const GLint64 *value);
typedef void (OSG_APIENTRY * osgGlProgramUniform1ui64ARBProc )(GLuint program, GLint location, GLuint64 x);
typedef void (OSG_APIENTRY * osgGlProgramUniform2ui64ARBProc )(GLuint program, GLint location, GLuint64 x, GLuint64 y);
typedef void (OSG_APIENTRY * osgGlProgramUniform3ui64ARBProc )(GLuint program, GLint location, GLuint64 x, GLuint64 y, GLuint64 z);
typedef void (OSG_APIENTRY * osgGlProgramUniform4ui64ARBProc )(GLuint program, GLint location, GLuint64 x, GLuint64 y, GLuint64 z, GLuint64 w);
typedef void (OSG_APIENTRY * osgGlProgramUniform1ui64vARBProc )(GLuint program, GLint location, GLsizei count, const GLuint64 *value);
typedef void (OSG_APIENTRY * osgGlProgramUniform2ui64vARBProc )(GLuint program, GLint location, GLsizei count, const GLuint64 *value);
typedef void (OSG_APIENTRY * osgGlProgramUniform3ui64vARBProc )(GLuint program, GLint location, GLsizei count, const GLuint64 *value);
typedef void (OSG_APIENTRY * osgGlProgramUniform4ui64vARBProc )(GLuint program, GLint location, GLsizei count, const GLuint64 *value);
#endif /* GL_ARB_gpu_shader_int64 */

#ifdef GL_ARB_half_float_pixel
#endif /* GL_ARB_half_float_pixel */

#ifdef GL_ARB_half_float_vertex
#endif /* GL_ARB_half_float_vertex */

#ifdef GL_ARB_imaging
typedef void (OSG_APIENTRY * osgGlColorTableProc )(GLenum target, GLenum internalformat, GLsizei width, GLenum format, GLenum type, const void *table);
typedef void (OSG_APIENTRY * osgGlColorTableParameterfvProc )(GLenum target, GLenum pname, const GLfloat *params);
typedef void (OSG_APIENTRY * osgGlColorTableParameterivProc )(GLenum target, GLenum pname, const GLint *params);
typedef void (OSG_APIENTRY * osgGlCopyColorTableProc )(GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width);
typedef void (OSG_APIENTRY * osgGlGetColorTableProc )(GLenum target, GLenum format, GLenum type, void *table);
typedef void (OSG_APIENTRY * osgGlGetColorTableParameterfvProc )(GLenum target, GLenum pname, GLfloat *params);
typedef void (OSG_APIENTRY * osgGlGetColorTableParameterivProc )(GLenum target, GLenum pname, GLint *params);
typedef void (OSG_APIENTRY * osgGlColorSubTableProc )(GLenum target, GLsizei start, GLsizei count, GLenum format, GLenum type, const void *data);
typedef void (OSG_APIENTRY * osgGlCopyColorSubTableProc )(GLenum target, GLsizei start, GLint x, GLint y, GLsizei width);
typedef void (OSG_APIENTRY * osgGlConvolutionFilter1DProc )(GLenum target, GLenum internalformat, GLsizei width, GLenum format, GLenum type, const void *image);
typedef void (OSG_APIENTRY * osgGlConvolutionFilter2DProc )(GLenum target, GLenum internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const void *image);
typedef void (OSG_APIENTRY * osgGlConvolutionParameterfProc )(GLenum target, GLenum pname, GLfloat params);
typedef void (OSG_APIENTRY * osgGlConvolutionParameterfvProc )(GLenum target, GLenum pname, const GLfloat *params);
typedef void (OSG_APIENTRY * osgGlConvolutionParameteriProc )(GLenum target, GLenum pname, GLint params);
typedef void (OSG_APIENTRY * osgGlConvolutionParameterivProc )(GLenum target, GLenum pname, const GLint *params);
typedef void (OSG_APIENTRY * osgGlCopyConvolutionFilter1DProc )(GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width);
typedef void (OSG_APIENTRY * osgGlCopyConvolutionFilter2DProc )(GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (OSG_APIENTRY * osgGlGetConvolutionFilterProc )(GLenum target, GLenum format, GLenum type, void *image);
typedef void (OSG_APIENTRY * osgGlGetConvolutionParameterfvProc )(GLenum target, GLenum pname, GLfloat *params);
typedef void (OSG_APIENTRY * osgGlGetConvolutionParameterivProc )(GLenum target, GLenum pname, GLint *params);
typedef void (OSG_APIENTRY * osgGlGetSeparableFilterProc )(GLenum target, GLenum format, GLenum type, void *row, void *column, void *span);
typedef void (OSG_APIENTRY * osgGlSeparableFilter2DProc )(GLenum target, GLenum internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const void *row, const void *column);
typedef void (OSG_APIENTRY * osgGlGetHistogramProc )(GLenum target, GLboolean reset, GLenum format, GLenum type, void *values);
typedef void (OSG_APIENTRY * osgGlGetHistogramParameterfvProc )(GLenum target, GLenum pname, GLfloat *params);
typedef void (OSG_APIENTRY * osgGlGetHistogramParameterivProc )(GLenum target, GLenum pname, GLint *params);
typedef void (OSG_APIENTRY * osgGlGetMinmaxProc )(GLenum target, GLboolean reset, GLenum format, GLenum type, void *values);
typedef void (OSG_APIENTRY * osgGlGetMinmaxParameterfvProc )(GLenum target, GLenum pname, GLfloat *params);
typedef void (OSG_APIENTRY * osgGlGetMinmaxParameterivProc )(GLenum target, GLenum pname, GLint *params);
typedef void (OSG_APIENTRY * osgGlHistogramProc )(GLenum target, GLsizei width, GLenum internalformat, GLboolean sink);
typedef void (OSG_APIENTRY * osgGlMinmaxProc )(GLenum target, GLenum internalformat, GLboolean sink);
typedef void (OSG_APIENTRY * osgGlResetHistogramProc )(GLenum target);
typedef void (OSG_APIENTRY * osgGlResetMinmaxProc )(GLenum target);
#endif /* GL_ARB_imaging */

#ifdef GL_ARB_indirect_parameters
typedef void (OSG_APIENTRY * osgGlMultiDrawArraysIndirectCountARBProc )(GLenum mode, GLintptr indirect, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride);
typedef void (OSG_APIENTRY * osgGlMultiDrawElementsIndirectCountARBProc )(GLenum mode, GLenum type, GLintptr indirect, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride);
#endif /* GL_ARB_indirect_parameters */

#ifdef GL_ARB_instanced_arrays
typedef void (OSG_APIENTRY * osgGlVertexAttribDivisorARBProc )(GLuint index, GLuint divisor);
#endif /* GL_ARB_instanced_arrays */

#ifdef GL_ARB_internalformat_query
#endif /* GL_ARB_internalformat_query */

#ifdef GL_ARB_internalformat_query2
#endif /* GL_ARB_internalformat_query2 */

#ifdef GL_ARB_invalidate_subdata
#endif /* GL_ARB_invalidate_subdata */

#ifdef GL_ARB_map_buffer_alignment
#endif /* GL_ARB_map_buffer_alignment */

#ifdef GL_ARB_map_buffer_range
#endif /* GL_ARB_map_buffer_range */

#ifdef GL_ARB_matrix_palette
typedef void (OSG_APIENTRY * osgGlCurrentPaletteMatrixARBProc )(GLint index);
typedef void (OSG_APIENTRY * osgGlMatrixIndexubvARBProc )(GLint size, const GLubyte *indices);
typedef void (OSG_APIENTRY * osgGlMatrixIndexusvARBProc )(GLint size, const GLushort *indices);
typedef void (OSG_APIENTRY * osgGlMatrixIndexuivARBProc )(GLint size, const GLuint *indices);
typedef void (OSG_APIENTRY * osgGlMatrixIndexPointerARBProc )(GLint size, GLenum type, GLsizei stride, const void *pointer);
#endif /* GL_ARB_matrix_palette */

#ifdef GL_ARB_multi_bind
#endif /* GL_ARB_multi_bind */

#ifdef GL_ARB_multi_draw_indirect
#endif /* GL_ARB_multi_draw_indirect */

#ifdef GL_ARB_multisample
typedef void (OSG_APIENTRY * osgGlSampleCoverageARBProc )(GLfloat value, GLboolean invert);
#endif /* GL_ARB_multisample */

#ifdef GL_ARB_multitexture
typedef void (OSG_APIENTRY * osgGlActiveTextureARBProc )(GLenum texture);
typedef void (OSG_APIENTRY * osgGlClientActiveTextureARBProc )(GLenum texture);
typedef void (OSG_APIENTRY * osgGlMultiTexCoord1dARBProc )(GLenum target, GLdouble s);
typedef void (OSG_APIENTRY * osgGlMultiTexCoord1dvARBProc )(GLenum target, const GLdouble *v);
typedef void (OSG_APIENTRY * osgGlMultiTexCoord1fARBProc )(GLenum target, GLfloat s);
typedef void (OSG_APIENTRY * osgGlMultiTexCoord1fvARBProc )(GLenum target, const GLfloat *v);
typedef void (OSG_APIENTRY * osgGlMultiTexCoord1iARBProc )(GLenum target, GLint s);
typedef void (OSG_APIENTRY * osgGlMultiTexCoord1ivARBProc )(GLenum target, const GLint *v);
typedef void (OSG_APIENTRY * osgGlMultiTexCoord1sARBProc )(GLenum target, GLshort s);
typedef void (OSG_APIENTRY * osgGlMultiTexCoord1svARBProc )(GLenum target, const GLshort *v);
typedef void (OSG_APIENTRY * osgGlMultiTexCoord2dARBProc )(GLenum target, GLdouble s, GLdouble t);
typedef void (OSG_APIENTRY * osgGlMultiTexCoord2dvARBProc )(GLenum target, const GLdouble *v);
typedef void (OSG_APIENTRY * osgGlMultiTexCoord2fARBProc )(GLenum target, GLfloat s, GLfloat t);
typedef void (OSG_APIENTRY * osgGlMultiTexCoord2fvARBProc )(GLenum target, const GLfloat *v);
typedef void (OSG_APIENTRY * osgGlMultiTexCoord2iARBProc )(GLenum target, GLint s, GLint t);
typedef void (OSG_APIENTRY * osgGlMultiTexCoord2ivARBProc )(GLenum target, const GLint *v);
typedef void (OSG_APIENTRY * osgGlMultiTexCoord2sARBProc )(GLenum target, GLshort s, GLshort t);
typedef void (OSG_APIENTRY * osgGlMultiTexCoord2svARBProc )(GLenum target, const GLshort *v);
typedef void (OSG_APIENTRY * osgGlMultiTexCoord3dARBProc )(GLenum target, GLdouble s, GLdouble t, GLdouble r);
typedef void (OSG_APIENTRY * osgGlMultiTexCoord3dvARBProc )(GLenum target, const GLdouble *v);
typedef void (OSG_APIENTRY * osgGlMultiTexCoord3fARBProc )(GLenum target, GLfloat s, GLfloat t, GLfloat r);
typedef void (OSG_APIENTRY * osgGlMultiTexCoord3fvARBProc )(GLenum target, const GLfloat *v);
typedef void (OSG_APIENTRY * osgGlMultiTexCoord3iARBProc )(GLenum target, GLint s, GLint t, GLint r);
typedef void (OSG_APIENTRY * osgGlMultiTexCoord3ivARBProc )(GLenum target, const GLint *v);
typedef void (OSG_APIENTRY * osgGlMultiTexCoord3sARBProc )(GLenum target, GLshort s, GLshort t, GLshort r);
typedef void (OSG_APIENTRY * osgGlMultiTexCoord3svARBProc )(GLenum target, const GLshort *v);
typedef void (OSG_APIENTRY * osgGlMultiTexCoord4dARBProc )(GLenum target, GLdouble s, GLdouble t, GLdouble r, GLdouble q);
typedef void (OSG_APIENTRY * osgGlMultiTexCoord4dvARBProc )(GLenum target, const GLdouble *v);
typedef void (OSG_APIENTRY * osgGlMultiTexCoord4fARBProc )(GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q);
typedef void (OSG_APIENTRY * osgGlMultiTexCoord4fvARBProc )(GLenum target, const GLfloat *v);
typedef void (OSG_APIENTRY * osgGlMultiTexCoord4iARBProc )(GLenum target, GLint s, GLint t, GLint r, GLint q);
typedef void (OSG_APIENTRY * osgGlMultiTexCoord4ivARBProc )(GLenum target, const GLint *v);
typedef void (OSG_APIENTRY * osgGlMultiTexCoord4sARBProc )(GLenum target, GLshort s, GLshort t, GLshort r, GLshort q);
typedef void (OSG_APIENTRY * osgGlMultiTexCoord4svARBProc )(GLenum target, const GLshort *v);
#endif /* GL_ARB_multitexture */

#ifdef GL_ARB_occlusion_query
typedef void (OSG_APIENTRY * osgGlGenQueriesARBProc )(GLsizei n, GLuint *ids);
typedef void (OSG_APIENTRY * osgGlDeleteQueriesARBProc )(GLsizei n, const GLuint *ids);
typedef GLboolean (OSG_APIENTRY * osgGlIsQueryARBProc )(GLuint id);
typedef void (OSG_APIENTRY * osgGlBeginQueryARBProc )(GLenum target, GLuint id);
typedef void (OSG_APIENTRY * osgGlEndQueryARBProc )(GLenum target);
typedef void (OSG_APIENTRY * osgGlGetQueryivARBProc )(GLenum target, GLenum pname, GLint *params);
typedef void (OSG_APIENTRY * osgGlGetQueryObjectivARBProc )(GLuint id, GLenum pname, GLint *params);
typedef void (OSG_APIENTRY * osgGlGetQueryObjectuivARBProc )(GLuint id, GLenum pname, GLuint *params);
#endif /* GL_ARB_occlusion_query */

#ifdef GL_ARB_occlusion_query2
#endif /* GL_ARB_occlusion_query2 */

#ifdef GL_ARB_parallel_shader_compile
typedef void (OSG_APIENTRY * osgGlMaxShaderCompilerThreadsARBProc )(GLuint count);
#endif /* GL_ARB_parallel_shader_compile */

#ifdef GL_ARB_pipeline_statistics_query
#endif /* GL_ARB_pipeline_statistics_query */

#ifdef GL_ARB_pixel_buffer_object
#endif /* GL_ARB_pixel_buffer_object */

#ifdef GL_ARB_point_parameters
typedef void (OSG_APIENTRY * osgGlPointParameterfARBProc )(GLenum pname, GLfloat param);
typedef void (OSG_APIENTRY * osgGlPointParameterfvARBProc )(GLenum pname, const GLfloat *params);
#endif /* GL_ARB_point_parameters */

#ifdef GL_ARB_point_sprite
#endif /* GL_ARB_point_sprite */

#ifdef GL_ARB_post_depth_coverage
#endif /* GL_ARB_post_depth_coverage */

#ifdef GL_ARB_program_interface_query
#endif /* GL_ARB_program_interface_query */

#ifdef GL_ARB_provoking_vertex
#endif /* GL_ARB_provoking_vertex */

#ifdef GL_ARB_query_buffer_object
#endif /* GL_ARB_query_buffer_object */

#ifdef GL_ARB_robust_buffer_access_behavior
#endif /* GL_ARB_robust_buffer_access_behavior */

#ifdef GL_ARB_robustness
typedef GLenum (OSG_APIENTRY * osgGlGetGraphicsResetStatusARBProc )(void);
typedef void (OSG_APIENTRY * osgGlGetnTexImageARBProc )(GLenum target, GLint level, GLenum format, GLenum type, GLsizei bufSize, void *img);
typedef void (OSG_APIENTRY * osgGlReadnPixelsARBProc )(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLsizei bufSize, void *data);
typedef void (OSG_APIENTRY * osgGlGetnCompressedTexImageARBProc )(GLenum target, GLint lod, GLsizei bufSize, void *img);
typedef void (OSG_APIENTRY * osgGlGetnUniformfvARBProc )(GLuint program, GLint location, GLsizei bufSize, GLfloat *params);
typedef void (OSG_APIENTRY * osgGlGetnUniformivARBProc )(GLuint program, GLint location, GLsizei bufSize, GLint *params);
typedef void (OSG_APIENTRY * osgGlGetnUniformuivARBProc )(GLuint program, GLint location, GLsizei bufSize, GLuint *params);
typedef void (OSG_APIENTRY * osgGlGetnUniformdvARBProc )(GLuint program, GLint location, GLsizei bufSize, GLdouble *params);
typedef void (OSG_APIENTRY * osgGlGetnMapdvARBProc )(GLenum target, GLenum query, GLsizei bufSize, GLdouble *v);
typedef void (OSG_APIENTRY * osgGlGetnMapfvARBProc )(GLenum target, GLenum query, GLsizei bufSize, GLfloat *v);
typedef void (OSG_APIENTRY * osgGlGetnMapivARBProc )(GLenum target, GLenum query, GLsizei bufSize, GLint *v);
typedef void (OSG_APIENTRY * osgGlGetnPixelMapfvARBProc )(GLenum map, GLsizei bufSize, GLfloat *values);
typedef void (OSG_APIENTRY * osgGlGetnPixelMapuivARBProc )(GLenum map, GLsizei bufSize, GLuint *values);
typedef void (OSG_APIENTRY * osgGlGetnPixelMapusvARBProc )(GLenum map, GLsizei bufSize, GLushort *values);
typedef void (OSG_APIENTRY * osgGlGetnPolygonStippleARBProc )(GLsizei bufSize, GLubyte *pattern);
typedef void (OSG_APIENTRY * osgGlGetnColorTableARBProc )(GLenum target, GLenum format, GLenum type, GLsizei bufSize, void *table);
typedef void (OSG_APIENTRY * osgGlGetnConvolutionFilterARBProc )(GLenum target, GLenum format, GLenum type, GLsizei bufSize, void *image);
typedef void (OSG_APIENTRY * osgGlGetnSeparableFilterARBProc )(GLenum target, GLenum format, GLenum type, GLsizei rowBufSize, void *row, GLsizei columnBufSize, void *column, void *span);
typedef void (OSG_APIENTRY * osgGlGetnHistogramARBProc )(GLenum target, GLboolean reset, GLenum format, GLenum type, GLsizei bufSize, void *values);
typedef void (OSG_APIENTRY * osgGlGetnMinmaxARBProc )(GLenum target, GLboolean reset, GLenum format, GLenum type, GLsizei bufSize, void *values);
#endif /* GL_ARB_robustness */

#ifdef GL_ARB_robustness_isolation
#endif /* GL_ARB_robustness_isolation */

#ifdef GL_ARB_sample_locations
typedef void (OSG_APIENTRY * osgGlFramebufferSampleLocationsfvARBProc )(GLenum target, GLuint start, GLsizei count, const GLfloat *v);
typedef void (OSG_APIENTRY * osgGlNamedFramebufferSampleLocationsfvARBProc )(GLuint framebuffer, GLuint start, GLsizei count, const GLfloat *v);
typedef void (OSG_APIENTRY * osgGlEvaluateDepthValuesARBProc )(void);
#endif /* GL_ARB_sample_locations */

#ifdef GL_ARB_sample_shading
typedef void (OSG_APIENTRY * osgGlMinSampleShadingARBProc )(GLfloat value);
#endif /* GL_ARB_sample_shading */

#ifdef GL_ARB_sampler_objects
#endif /* GL_ARB_sampler_objects */

#ifdef GL_ARB_seamless_cube_map
#endif /* GL_ARB_seamless_cube_map */

#ifdef GL_ARB_seamless_cubemap_per_texture
#endif /* GL_ARB_seamless_cubemap_per_texture */

#ifdef GL_ARB_separate_shader_objects
#endif /* GL_ARB_separate_shader_objects */

#ifdef GL_ARB_shader_atomic_counter_ops
#endif /* GL_ARB_shader_atomic_counter_ops */

#ifdef GL_ARB_shader_atomic_counters
#endif /* GL_ARB_shader_atomic_counters */

#ifdef GL_ARB_shader_ballot
#endif /* GL_ARB_shader_ballot */

#ifdef GL_ARB_shader_bit_encoding
#endif /* GL_ARB_shader_bit_encoding */

#ifdef GL_ARB_shader_clock
#endif /* GL_ARB_shader_clock */

#ifdef GL_ARB_shader_draw_parameters
#endif /* GL_ARB_shader_draw_parameters */

#ifdef GL_ARB_shader_group_vote
#endif /* GL_ARB_shader_group_vote */

#ifdef GL_ARB_shader_image_load_store
#endif /* GL_ARB_shader_image_load_store */

#ifdef GL_ARB_shader_image_size
#endif /* GL_ARB_shader_image_size */

#ifdef GL_ARB_shader_objects
typedef void (OSG_APIENTRY * osgGlDeleteObjectARBProc )(GLhandleARB obj);
typedef GLhandleARB (OSG_APIENTRY * osgGlGetHandleARBProc )(GLenum pname);
typedef void (OSG_APIENTRY * osgGlDetachObjectARBProc )(GLhandleARB containerObj, GLhandleARB attachedObj);
typedef GLhandleARB (OSG_APIENTRY * osgGlCreateShaderObjectARBProc )(GLenum shaderType);
typedef void (OSG_APIENTRY * osgGlShaderSourceARBProc )(GLhandleARB shaderObj, GLsizei count, const GLcharARB **string, const GLint *length);
typedef void (OSG_APIENTRY * osgGlCompileShaderARBProc )(GLhandleARB shaderObj);
typedef GLhandleARB (OSG_APIENTRY * osgGlCreateProgramObjectARBProc )(void);
typedef void (OSG_APIENTRY * osgGlAttachObjectARBProc )(GLhandleARB containerObj, GLhandleARB obj);
typedef void (OSG_APIENTRY * osgGlLinkProgramARBProc )(GLhandleARB programObj);
typedef void (OSG_APIENTRY * osgGlUseProgramObjectARBProc )(GLhandleARB programObj);
typedef void (OSG_APIENTRY * osgGlValidateProgramARBProc )(GLhandleARB programObj);
typedef void (OSG_APIENTRY * osgGlUniform1fARBProc )(GLint location, GLfloat v0);
typedef void (OSG_APIENTRY * osgGlUniform2fARBProc )(GLint location, GLfloat v0, GLfloat v1);
typedef void (OSG_APIENTRY * osgGlUniform3fARBProc )(GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
typedef void (OSG_APIENTRY * osgGlUniform4fARBProc )(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
typedef void (OSG_APIENTRY * osgGlUniform1iARBProc )(GLint location, GLint v0);
typedef void (OSG_APIENTRY * osgGlUniform2iARBProc )(GLint location, GLint v0, GLint v1);
typedef void (OSG_APIENTRY * osgGlUniform3iARBProc )(GLint location, GLint v0, GLint v1, GLint v2);
typedef void (OSG_APIENTRY * osgGlUniform4iARBProc )(GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
typedef void (OSG_APIENTRY * osgGlUniform1fvARBProc )(GLint location, GLsizei count, const GLfloat *value);
typedef void (OSG_APIENTRY * osgGlUniform2fvARBProc )(GLint location, GLsizei count, const GLfloat *value);
typedef void (OSG_APIENTRY * osgGlUniform3fvARBProc )(GLint location, GLsizei count, const GLfloat *value);
typedef void (OSG_APIENTRY * osgGlUniform4fvARBProc )(GLint location, GLsizei count, const GLfloat *value);
typedef void (OSG_APIENTRY * osgGlUniform1ivARBProc )(GLint location, GLsizei count, const GLint *value);
typedef void (OSG_APIENTRY * osgGlUniform2ivARBProc )(GLint location, GLsizei count, const GLint *value);
typedef void (OSG_APIENTRY * osgGlUniform3ivARBProc )(GLint location, GLsizei count, const GLint *value);
typedef void (OSG_APIENTRY * osgGlUniform4ivARBProc )(GLint location, GLsizei count, const GLint *value);
typedef void (OSG_APIENTRY * osgGlUniformMatrix2fvARBProc )(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (OSG_APIENTRY * osgGlUniformMatrix3fvARBProc )(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (OSG_APIENTRY * osgGlUniformMatrix4fvARBProc )(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (OSG_APIENTRY * osgGlGetObjectParameterfvARBProc )(GLhandleARB obj, GLenum pname, GLfloat *params);
typedef void (OSG_APIENTRY * osgGlGetObjectParameterivARBProc )(GLhandleARB obj, GLenum pname, GLint *params);
typedef void (OSG_APIENTRY * osgGlGetInfoLogARBProc )(GLhandleARB obj, GLsizei maxLength, GLsizei *length, GLcharARB *infoLog);
typedef void (OSG_APIENTRY * osgGlGetAttachedObjectsARBProc )(GLhandleARB containerObj, GLsizei maxCount, GLsizei *count, GLhandleARB *obj);
typedef GLint (OSG_APIENTRY * osgGlGetUniformLocationARBProc )(GLhandleARB programObj, const GLcharARB *name);
typedef void (OSG_APIENTRY * osgGlGetActiveUniformARBProc )(GLhandleARB programObj, GLuint index, GLsizei maxLength, GLsizei *length, GLint *size, GLenum *type, GLcharARB *name);
typedef void (OSG_APIENTRY * osgGlGetUniformfvARBProc )(GLhandleARB programObj, GLint location, GLfloat *params);
typedef void (OSG_APIENTRY * osgGlGetUniformivARBProc )(GLhandleARB programObj, GLint location, GLint *params);
typedef void (OSG_APIENTRY * osgGlGetShaderSourceARBProc )(GLhandleARB obj, GLsizei maxLength, GLsizei *length, GLcharARB *source);
#endif /* GL_ARB_shader_objects */

#ifdef GL_ARB_shader_precision
#endif /* GL_ARB_shader_precision */

#ifdef GL_ARB_shader_stencil_export
#endif /* GL_ARB_shader_stencil_export */

#ifdef GL_ARB_shader_storage_buffer_object
#endif /* GL_ARB_shader_storage_buffer_object */

#ifdef GL_ARB_shader_subroutine
#endif /* GL_ARB_shader_subroutine */

#ifdef GL_ARB_shader_texture_image_samples
#endif /* GL_ARB_shader_texture_image_samples */

#ifdef GL_ARB_shader_texture_lod
#endif /* GL_ARB_shader_texture_lod */

#ifdef GL_ARB_shader_viewport_layer_array
#endif /* GL_ARB_shader_viewport_layer_array */

#ifdef GL_ARB_shading_language_100
#endif /* GL_ARB_shading_language_100 */

#ifdef GL_ARB_shading_language_420pack
#endif /* GL_ARB_shading_language_420pack */

#ifdef GL_ARB_shading_language_include
typedef void (OSG_APIENTRY * osgGlNamedStringARBProc )(GLenum type, GLint namelen, const GLchar *name, GLint stringlen, const GLchar *string);
typedef void (OSG_APIENTRY * osgGlDeleteNamedStringARBProc )(GLint namelen, const GLchar *name);
typedef void (OSG_APIENTRY * osgGlCompileShaderIncludeARBProc )(GLuint shader, GLsizei count, const GLchar *const*path, const GLint *length);
typedef GLboolean (OSG_APIENTRY * osgGlIsNamedStringARBProc )(GLint namelen, const GLchar *name);
typedef void (OSG_APIENTRY * osgGlGetNamedStringARBProc )(GLint namelen, const GLchar *name, GLsizei bufSize, GLint *stringlen, GLchar *string);
typedef void (OSG_APIENTRY * osgGlGetNamedStringivARBProc )(GLint namelen, const GLchar *name, GLenum pname, GLint *params);
#endif /* GL_ARB_shading_language_include */

#ifdef GL_ARB_shading_language_packing
#endif /* GL_ARB_shading_language_packing */

#ifdef GL_ARB_shadow
#endif /* GL_ARB_shadow */

#ifdef GL_ARB_shadow_ambient
#endif /* GL_ARB_shadow_ambient */

#ifdef GL_ARB_sparse_buffer
typedef void (OSG_APIENTRY * osgGlBufferPageCommitmentARBProc )(GLenum target, GLintptr offset, GLsizeiptr size, GLboolean commit);
typedef void (OSG_APIENTRY * osgGlNamedBufferPageCommitmentEXTProc )(GLuint buffer, GLintptr offset, GLsizeiptr size, GLboolean commit);
typedef void (OSG_APIENTRY * osgGlNamedBufferPageCommitmentARBProc )(GLuint buffer, GLintptr offset, GLsizeiptr size, GLboolean commit);
#endif /* GL_ARB_sparse_buffer */

#ifdef GL_ARB_sparse_texture
typedef void (OSG_APIENTRY * osgGlTexPageCommitmentARBProc )(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLboolean commit);
#endif /* GL_ARB_sparse_texture */

#ifdef GL_ARB_sparse_texture2
#endif /* GL_ARB_sparse_texture2 */

#ifdef GL_ARB_sparse_texture_clamp
#endif /* GL_ARB_sparse_texture_clamp */

#ifdef GL_ARB_stencil_texturing
#endif /* GL_ARB_stencil_texturing */

#ifdef GL_ARB_sync
#endif /* GL_ARB_sync */

#ifdef GL_ARB_tessellation_shader
#endif /* GL_ARB_tessellation_shader */

#ifdef GL_ARB_texture_barrier
#endif /* GL_ARB_texture_barrier */

#ifdef GL_ARB_texture_border_clamp
#endif /* GL_ARB_texture_border_clamp */

#ifdef GL_ARB_texture_buffer_object
typedef void (OSG_APIENTRY * osgGlTexBufferARBProc )(GLenum target, GLenum internalformat, GLuint buffer);
#endif /* GL_ARB_texture_buffer_object */

#ifdef GL_ARB_texture_buffer_object_rgb32
#endif /* GL_ARB_texture_buffer_object_rgb32 */

#ifdef GL_ARB_texture_buffer_range
#endif /* GL_ARB_texture_buffer_range */

#ifdef GL_ARB_texture_compression
typedef void (OSG_APIENTRY * osgGlCompressedTexImage3DARBProc )(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void *data);
typedef void (OSG_APIENTRY * osgGlCompressedTexImage2DARBProc )(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void *data);
typedef void (OSG_APIENTRY * osgGlCompressedTexImage1DARBProc )(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const void *data);
typedef void (OSG_APIENTRY * osgGlCompressedTexSubImage3DARBProc )(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void *data);
typedef void (OSG_APIENTRY * osgGlCompressedTexSubImage2DARBProc )(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void *data);
typedef void (OSG_APIENTRY * osgGlCompressedTexSubImage1DARBProc )(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void *data);
typedef void (OSG_APIENTRY * osgGlGetCompressedTexImageARBProc )(GLenum target, GLint level, void *img);
#endif /* GL_ARB_texture_compression */

#ifdef GL_ARB_texture_compression_bptc
#endif /* GL_ARB_texture_compression_bptc */

#ifdef GL_ARB_texture_compression_rgtc
#endif /* GL_ARB_texture_compression_rgtc */

#ifdef GL_ARB_texture_cube_map
#endif /* GL_ARB_texture_cube_map */

#ifdef GL_ARB_texture_cube_map_array
#endif /* GL_ARB_texture_cube_map_array */

#ifdef GL_ARB_texture_env_add
#endif /* GL_ARB_texture_env_add */

#ifdef GL_ARB_texture_env_combine
#endif /* GL_ARB_texture_env_combine */

#ifdef GL_ARB_texture_env_crossbar
#endif /* GL_ARB_texture_env_crossbar */

#ifdef GL_ARB_texture_env_dot3
#endif /* GL_ARB_texture_env_dot3 */

#ifdef GL_ARB_texture_filter_minmax
#endif /* GL_ARB_texture_filter_minmax */

#ifdef GL_ARB_texture_float
#endif /* GL_ARB_texture_float */

#ifdef GL_ARB_texture_gather
#endif /* GL_ARB_texture_gather */

#ifdef GL_ARB_texture_mirror_clamp_to_edge
#endif /* GL_ARB_texture_mirror_clamp_to_edge */

#ifdef GL_ARB_texture_mirrored_repeat
#endif /* GL_ARB_texture_mirrored_repeat */

#ifdef GL_ARB_texture_multisample
#endif /* GL_ARB_texture_multisample */

#ifdef GL_ARB_texture_non_power_of_two
#endif /* GL_ARB_texture_non_power_of_two */

#ifdef GL_ARB_texture_query_levels
#endif /* GL_ARB_texture_query_levels */

#ifdef GL_ARB_texture_query_lod
#endif /* GL_ARB_texture_query_lod */

#ifdef GL_ARB_texture_rectangle
#endif /* GL_ARB_texture_rectangle */

#ifdef GL_ARB_texture_rg
#endif /* GL_ARB_texture_rg */

#ifdef GL_ARB_texture_rgb10_a2ui
#endif /* GL_ARB_texture_rgb10_a2ui */

#ifdef GL_ARB_texture_stencil8
#endif /* GL_ARB_texture_stencil8 */

#ifdef GL_ARB_texture_storage
#endif /* GL_ARB_texture_storage */

#ifdef GL_ARB_texture_storage_multisample
#endif /* GL_ARB_texture_storage_multisample */

#ifdef GL_ARB_texture_swizzle
#endif /* GL_ARB_texture_swizzle */

#ifdef GL_ARB_texture_view
#endif /* GL_ARB_texture_view */

#ifdef GL_ARB_timer_query
#endif /* GL_ARB_timer_query */

#ifdef GL_ARB_transform_feedback2
#endif /* GL_ARB_transform_feedback2 */

#ifdef GL_ARB_transform_feedback3
#endif /* GL_ARB_transform_feedback3 */

#ifdef GL_ARB_transform_feedback_instanced
#endif /* GL_ARB_transform_feedback_instanced */

#ifdef GL_ARB_transform_feedback_overflow_query
#endif /* GL_ARB_transform_feedback_overflow_query */

#ifdef GL_ARB_transpose_matrix
typedef void (OSG_APIENTRY * osgGlLoadTransposeMatrixfARBProc )(const GLfloat *m);
typedef void (OSG_APIENTRY * osgGlLoadTransposeMatrixdARBProc )(const GLdouble *m);
typedef void (OSG_APIENTRY * osgGlMultTransposeMatrixfARBProc )(const GLfloat *m);
typedef void (OSG_APIENTRY * osgGlMultTransposeMatrixdARBProc )(const GLdouble *m);
#endif /* GL_ARB_transpose_matrix */

#ifdef GL_ARB_uniform_buffer_object
#endif /* GL_ARB_uniform_buffer_object */

#ifdef GL_ARB_vertex_array_bgra
#endif /* GL_ARB_vertex_array_bgra */

#ifdef GL_ARB_vertex_array_object
#endif /* GL_ARB_vertex_array_object */

#ifdef GL_ARB_vertex_attrib_64bit
#endif /* GL_ARB_vertex_attrib_64bit */

#ifdef GL_ARB_vertex_attrib_binding
#endif /* GL_ARB_vertex_attrib_binding */

#ifdef GL_ARB_vertex_blend
typedef void (OSG_APIENTRY * osgGlWeightbvARBProc )(GLint size, const GLbyte *weights);
typedef void (OSG_APIENTRY * osgGlWeightsvARBProc )(GLint size, const GLshort *weights);
typedef void (OSG_APIENTRY * osgGlWeightivARBProc )(GLint size, const GLint *weights);
typedef void (OSG_APIENTRY * osgGlWeightfvARBProc )(GLint size, const GLfloat *weights);
typedef void (OSG_APIENTRY * osgGlWeightdvARBProc )(GLint size, const GLdouble *weights);
typedef void (OSG_APIENTRY * osgGlWeightubvARBProc )(GLint size, const GLubyte *weights);
typedef void (OSG_APIENTRY * osgGlWeightusvARBProc )(GLint size, const GLushort *weights);
typedef void (OSG_APIENTRY * osgGlWeightuivARBProc )(GLint size, const GLuint *weights);
typedef void (OSG_APIENTRY * osgGlWeightPointerARBProc )(GLint size, GLenum type, GLsizei stride, const void *pointer);
typedef void (OSG_APIENTRY * osgGlVertexBlendARBProc )(GLint count);
#endif /* GL_ARB_vertex_blend */

#ifdef GL_ARB_vertex_buffer_object
typedef void (OSG_APIENTRY * osgGlBindBufferARBProc )(GLenum target, GLuint buffer);
typedef void (OSG_APIENTRY * osgGlDeleteBuffersARBProc )(GLsizei n, const GLuint *buffers);
typedef void (OSG_APIENTRY * osgGlGenBuffersARBProc )(GLsizei n, GLuint *buffers);
typedef GLboolean (OSG_APIENTRY * osgGlIsBufferARBProc )(GLuint buffer);
typedef void (OSG_APIENTRY * osgGlBufferDataARBProc )(GLenum target, GLsizeiptrARB size, const void *data, GLenum usage);
typedef void (OSG_APIENTRY * osgGlBufferSubDataARBProc )(GLenum target, GLintptrARB offset, GLsizeiptrARB size, const void *data);
typedef void (OSG_APIENTRY * osgGlGetBufferSubDataARBProc )(GLenum target, GLintptrARB offset, GLsizeiptrARB size, void *data);
typedef void *(OSG_APIENTRY * osgGlMapBufferARBProc )(GLenum target, GLenum access);
typedef GLboolean (OSG_APIENTRY * osgGlUnmapBufferARBProc )(GLenum target);
typedef void (OSG_APIENTRY * osgGlGetBufferParameterivARBProc )(GLenum target, GLenum pname, GLint *params);
typedef void (OSG_APIENTRY * osgGlGetBufferPointervARBProc )(GLenum target, GLenum pname, void **params);
#endif /* GL_ARB_vertex_buffer_object */

#ifdef GL_ARB_vertex_program
typedef void (OSG_APIENTRY * osgGlVertexAttrib1dARBProc )(GLuint index, GLdouble x);
typedef void (OSG_APIENTRY * osgGlVertexAttrib1dvARBProc )(GLuint index, const GLdouble *v);
typedef void (OSG_APIENTRY * osgGlVertexAttrib1fARBProc )(GLuint index, GLfloat x);
typedef void (OSG_APIENTRY * osgGlVertexAttrib1fvARBProc )(GLuint index, const GLfloat *v);
typedef void (OSG_APIENTRY * osgGlVertexAttrib1sARBProc )(GLuint index, GLshort x);
typedef void (OSG_APIENTRY * osgGlVertexAttrib1svARBProc )(GLuint index, const GLshort *v);
typedef void (OSG_APIENTRY * osgGlVertexAttrib2dARBProc )(GLuint index, GLdouble x, GLdouble y);
typedef void (OSG_APIENTRY * osgGlVertexAttrib2dvARBProc )(GLuint index, const GLdouble *v);
typedef void (OSG_APIENTRY * osgGlVertexAttrib2fARBProc )(GLuint index, GLfloat x, GLfloat y);
typedef void (OSG_APIENTRY * osgGlVertexAttrib2fvARBProc )(GLuint index, const GLfloat *v);
typedef void (OSG_APIENTRY * osgGlVertexAttrib2sARBProc )(GLuint index, GLshort x, GLshort y);
typedef void (OSG_APIENTRY * osgGlVertexAttrib2svARBProc )(GLuint index, const GLshort *v);
typedef void (OSG_APIENTRY * osgGlVertexAttrib3dARBProc )(GLuint index, GLdouble x, GLdouble y, GLdouble z);
typedef void (OSG_APIENTRY * osgGlVertexAttrib3dvARBProc )(GLuint index, const GLdouble *v);
typedef void (OSG_APIENTRY * osgGlVertexAttrib3fARBProc )(GLuint index, GLfloat x, GLfloat y, GLfloat z);
typedef void (OSG_APIENTRY * osgGlVertexAttrib3fvARBProc )(GLuint index, const GLfloat *v);
typedef void (OSG_APIENTRY * osgGlVertexAttrib3sARBProc )(GLuint index, GLshort x, GLshort y, GLshort z);
typedef void (OSG_APIENTRY * osgGlVertexAttrib3svARBProc )(GLuint index, const GLshort *v);
typedef void (OSG_APIENTRY * osgGlVertexAttrib4NbvARBProc )(GLuint index, const GLbyte *v);
typedef void (OSG_APIENTRY * osgGlVertexAttrib4NivARBProc )(GLuint index, const GLint *v);
typedef void (OSG_APIENTRY * osgGlVertexAttrib4NsvARBProc )(GLuint index, const GLshort *v);
typedef void (OSG_APIENTRY * osgGlVertexAttrib4NubARBProc )(GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w);
typedef void (OSG_APIENTRY * osgGlVertexAttrib4NubvARBProc )(GLuint index, const GLubyte *v);
typedef void (OSG_APIENTRY * osgGlVertexAttrib4NuivARBProc )(GLuint index, const GLuint *v);
typedef void (OSG_APIENTRY * osgGlVertexAttrib4NusvARBProc )(GLuint index, const GLushort *v);
typedef void (OSG_APIENTRY * osgGlVertexAttrib4bvARBProc )(GLuint index, const GLbyte *v);
typedef void (OSG_APIENTRY * osgGlVertexAttrib4dARBProc )(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
typedef void (OSG_APIENTRY * osgGlVertexAttrib4dvARBProc )(GLuint index, const GLdouble *v);
typedef void (OSG_APIENTRY * osgGlVertexAttrib4fARBProc )(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
typedef void (OSG_APIENTRY * osgGlVertexAttrib4fvARBProc )(GLuint index, const GLfloat *v);
typedef void (OSG_APIENTRY * osgGlVertexAttrib4ivARBProc )(GLuint index, const GLint *v);
typedef void (OSG_APIENTRY * osgGlVertexAttrib4sARBProc )(GLuint index, GLshort x, GLshort y, GLshort z, GLshort w);
typedef void (OSG_APIENTRY * osgGlVertexAttrib4svARBProc )(GLuint index, const GLshort *v);
typedef void (OSG_APIENTRY * osgGlVertexAttrib4ubvARBProc )(GLuint index, const GLubyte *v);
typedef void (OSG_APIENTRY * osgGlVertexAttrib4uivARBProc )(GLuint index, const GLuint *v);
typedef void (OSG_APIENTRY * osgGlVertexAttrib4usvARBProc )(GLuint index, const GLushort *v);
typedef void (OSG_APIENTRY * osgGlVertexAttribPointerARBProc )(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer);
typedef void (OSG_APIENTRY * osgGlEnableVertexAttribArrayARBProc )(GLuint index);
typedef void (OSG_APIENTRY * osgGlDisableVertexAttribArrayARBProc )(GLuint index);
typedef void (OSG_APIENTRY * osgGlGetVertexAttribdvARBProc )(GLuint index, GLenum pname, GLdouble *params);
typedef void (OSG_APIENTRY * osgGlGetVertexAttribfvARBProc )(GLuint index, GLenum pname, GLfloat *params);
typedef void (OSG_APIENTRY * osgGlGetVertexAttribivARBProc )(GLuint index, GLenum pname, GLint *params);
typedef void (OSG_APIENTRY * osgGlGetVertexAttribPointervARBProc )(GLuint index, GLenum pname, void **pointer);
#endif /* GL_ARB_vertex_program */

#ifdef GL_ARB_vertex_shader
typedef void (OSG_APIENTRY * osgGlBindAttribLocationARBProc )(GLhandleARB programObj, GLuint index, const GLcharARB *name);
typedef void (OSG_APIENTRY * osgGlGetActiveAttribARBProc )(GLhandleARB programObj, GLuint index, GLsizei maxLength, GLsizei *length, GLint *size, GLenum *type, GLcharARB *name);
typedef GLint (OSG_APIENTRY * osgGlGetAttribLocationARBProc )(GLhandleARB programObj, const GLcharARB *name);
#endif /* GL_ARB_vertex_shader */

#ifdef GL_ARB_vertex_type_10f_11f_11f_rev
#endif /* GL_ARB_vertex_type_10f_11f_11f_rev */

#ifdef GL_ARB_vertex_type_2_10_10_10_rev
#endif /* GL_ARB_vertex_type_2_10_10_10_rev */

#ifdef GL_ARB_viewport_array
#endif /* GL_ARB_viewport_array */

#ifdef GL_ARB_window_pos
typedef void (OSG_APIENTRY * osgGlWindowPos2dARBProc )(GLdouble x, GLdouble y);
typedef void (OSG_APIENTRY * osgGlWindowPos2dvARBProc )(const GLdouble *v);
typedef void (OSG_APIENTRY * osgGlWindowPos2fARBProc )(GLfloat x, GLfloat y);
typedef void (OSG_APIENTRY * osgGlWindowPos2fvARBProc )(const GLfloat *v);
typedef void (OSG_APIENTRY * osgGlWindowPos2iARBProc )(GLint x, GLint y);
typedef void (OSG_APIENTRY * osgGlWindowPos2ivARBProc )(const GLint *v);
typedef void (OSG_APIENTRY * osgGlWindowPos2sARBProc )(GLshort x, GLshort y);
typedef void (OSG_APIENTRY * osgGlWindowPos2svARBProc )(const GLshort *v);
typedef void (OSG_APIENTRY * osgGlWindowPos3dARBProc )(GLdouble x, GLdouble y, GLdouble z);
typedef void (OSG_APIENTRY * osgGlWindowPos3dvARBProc )(const GLdouble *v);
typedef void (OSG_APIENTRY * osgGlWindowPos3fARBProc )(GLfloat x, GLfloat y, GLfloat z);
typedef void (OSG_APIENTRY * osgGlWindowPos3fvARBProc )(const GLfloat *v);
typedef void (OSG_APIENTRY * osgGlWindowPos3iARBProc )(GLint x, GLint y, GLint z);
typedef void (OSG_APIENTRY * osgGlWindowPos3ivARBProc )(const GLint *v);
typedef void (OSG_APIENTRY * osgGlWindowPos3sARBProc )(GLshort x, GLshort y, GLshort z);
typedef void (OSG_APIENTRY * osgGlWindowPos3svARBProc )(const GLshort *v);
#endif /* GL_ARB_window_pos */

#ifdef GL_KHR_blend_equation_advanced
typedef void (OSG_APIENTRY * osgGlBlendBarrierKHRProc )(void);
#endif /* GL_KHR_blend_equation_advanced */

#ifdef GL_KHR_blend_equation_advanced_coherent
#endif /* GL_KHR_blend_equation_advanced_coherent */

#ifdef GL_KHR_context_flush_control
#endif /* GL_KHR_context_flush_control */

#ifdef GL_KHR_debug
#endif /* GL_KHR_debug */

#ifdef GL_KHR_no_error
#endif /* GL_KHR_no_error */

#ifdef GL_KHR_robust_buffer_access_behavior
#endif /* GL_KHR_robust_buffer_access_behavior */

#ifdef GL_KHR_robustness
#endif /* GL_KHR_robustness */

#ifdef GL_KHR_texture_compression_astc_hdr
#endif /* GL_KHR_texture_compression_astc_hdr */

#ifdef GL_KHR_texture_compression_astc_ldr
#endif /* GL_KHR_texture_compression_astc_ldr */

#ifdef GL_KHR_texture_compression_astc_sliced_3d
#endif /* GL_KHR_texture_compression_astc_sliced_3d */

#ifdef GL_OES_byte_coordinates
typedef void (OSG_APIENTRY * osgGlMultiTexCoord1bOESProc )(GLenum texture, GLbyte s);
typedef void (OSG_APIENTRY * osgGlMultiTexCoord1bvOESProc )(GLenum texture, const GLbyte *coords);
typedef void (OSG_APIENTRY * osgGlMultiTexCoord2bOESProc )(GLenum texture, GLbyte s, GLbyte t);
typedef void (OSG_APIENTRY * osgGlMultiTexCoord2bvOESProc )(GLenum texture, const GLbyte *coords);
typedef void (OSG_APIENTRY * osgGlMultiTexCoord3bOESProc )(GLenum texture, GLbyte s, GLbyte t, GLbyte r);
typedef void (OSG_APIENTRY * osgGlMultiTexCoord3bvOESProc )(GLenum texture, const GLbyte *coords);
typedef void (OSG_APIENTRY * osgGlMultiTexCoord4bOESProc )(GLenum texture, GLbyte s, GLbyte t, GLbyte r, GLbyte q);
typedef void (OSG_APIENTRY * osgGlMultiTexCoord4bvOESProc )(GLenum texture, const GLbyte *coords);
typedef void (OSG_APIENTRY * osgGlTexCoord1bOESProc )(GLbyte s);
typedef void (OSG_APIENTRY * osgGlTexCoord1bvOESProc )(const GLbyte *coords);
typedef void (OSG_APIENTRY * osgGlTexCoord2bOESProc )(GLbyte s, GLbyte t);
typedef void (OSG_APIENTRY * osgGlTexCoord2bvOESProc )(const GLbyte *coords);
typedef void (OSG_APIENTRY * osgGlTexCoord3bOESProc )(GLbyte s, GLbyte t, GLbyte r);
typedef void (OSG_APIENTRY * osgGlTexCoord3bvOESProc )(const GLbyte *coords);
typedef void (OSG_APIENTRY * osgGlTexCoord4bOESProc )(GLbyte s, GLbyte t, GLbyte r, GLbyte q);
typedef void (OSG_APIENTRY * osgGlTexCoord4bvOESProc )(const GLbyte *coords);
typedef void (OSG_APIENTRY * osgGlVertex2bOESProc )(GLbyte x, GLbyte y);
typedef void (OSG_APIENTRY * osgGlVertex2bvOESProc )(const GLbyte *coords);
typedef void (OSG_APIENTRY * osgGlVertex3bOESProc )(GLbyte x, GLbyte y, GLbyte z);
typedef void (OSG_APIENTRY * osgGlVertex3bvOESProc )(const GLbyte *coords);
typedef void (OSG_APIENTRY * osgGlVertex4bOESProc )(GLbyte x, GLbyte y, GLbyte z, GLbyte w);
typedef void (OSG_APIENTRY * osgGlVertex4bvOESProc )(const GLbyte *coords);
#endif /* GL_OES_byte_coordinates */

#ifdef GL_OES_compressed_paletted_texture
#endif /* GL_OES_compressed_paletted_texture */

#ifdef GL_OES_fixed_point
typedef void (OSG_APIENTRY * osgGlAlphaFuncxOESProc )(GLenum func, GLfixed ref);
typedef void (OSG_APIENTRY * osgGlClearColorxOESProc )(GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha);
typedef void (OSG_APIENTRY * osgGlClearDepthxOESProc )(GLfixed depth);
typedef void (OSG_APIENTRY * osgGlClipPlanexOESProc )(GLenum plane, const GLfixed *equation);
typedef void (OSG_APIENTRY * osgGlColor4xOESProc )(GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha);
typedef void (OSG_APIENTRY * osgGlDepthRangexOESProc )(GLfixed n, GLfixed f);
typedef void (OSG_APIENTRY * osgGlFogxOESProc )(GLenum pname, GLfixed param);
typedef void (OSG_APIENTRY * osgGlFogxvOESProc )(GLenum pname, const GLfixed *param);
typedef void (OSG_APIENTRY * osgGlFrustumxOESProc )(GLfixed l, GLfixed r, GLfixed b, GLfixed t, GLfixed n, GLfixed f);
typedef void (OSG_APIENTRY * osgGlGetClipPlanexOESProc )(GLenum plane, GLfixed *equation);
typedef void (OSG_APIENTRY * osgGlGetFixedvOESProc )(GLenum pname, GLfixed *params);
typedef void (OSG_APIENTRY * osgGlGetTexEnvxvOESProc )(GLenum target, GLenum pname, GLfixed *params);
typedef void (OSG_APIENTRY * osgGlGetTexParameterxvOESProc )(GLenum target, GLenum pname, GLfixed *params);
typedef void (OSG_APIENTRY * osgGlLightModelxOESProc )(GLenum pname, GLfixed param);
typedef void (OSG_APIENTRY * osgGlLightModelxvOESProc )(GLenum pname, const GLfixed *param);
typedef void (OSG_APIENTRY * osgGlLightxOESProc )(GLenum light, GLenum pname, GLfixed param);
typedef void (OSG_APIENTRY * osgGlLightxvOESProc )(GLenum light, GLenum pname, const GLfixed *params);
typedef void (OSG_APIENTRY * osgGlLineWidthxOESProc )(GLfixed width);
typedef void (OSG_APIENTRY * osgGlLoadMatrixxOESProc )(const GLfixed *m);
typedef void (OSG_APIENTRY * osgGlMaterialxOESProc )(GLenum face, GLenum pname, GLfixed param);
typedef void (OSG_APIENTRY * osgGlMaterialxvOESProc )(GLenum face, GLenum pname, const GLfixed *param);
typedef void (OSG_APIENTRY * osgGlMultMatrixxOESProc )(const GLfixed *m);
typedef void (OSG_APIENTRY * osgGlMultiTexCoord4xOESProc )(GLenum texture, GLfixed s, GLfixed t, GLfixed r, GLfixed q);
typedef void (OSG_APIENTRY * osgGlNormal3xOESProc )(GLfixed nx, GLfixed ny, GLfixed nz);
typedef void (OSG_APIENTRY * osgGlOrthoxOESProc )(GLfixed l, GLfixed r, GLfixed b, GLfixed t, GLfixed n, GLfixed f);
typedef void (OSG_APIENTRY * osgGlPointParameterxvOESProc )(GLenum pname, const GLfixed *params);
typedef void (OSG_APIENTRY * osgGlPointSizexOESProc )(GLfixed size);
typedef void (OSG_APIENTRY * osgGlPolygonOffsetxOESProc )(GLfixed factor, GLfixed units);
typedef void (OSG_APIENTRY * osgGlRotatexOESProc )(GLfixed angle, GLfixed x, GLfixed y, GLfixed z);
typedef void (OSG_APIENTRY * osgGlScalexOESProc )(GLfixed x, GLfixed y, GLfixed z);
typedef void (OSG_APIENTRY * osgGlTexEnvxOESProc )(GLenum target, GLenum pname, GLfixed param);
typedef void (OSG_APIENTRY * osgGlTexEnvxvOESProc )(GLenum target, GLenum pname, const GLfixed *params);
typedef void (OSG_APIENTRY * osgGlTexParameterxOESProc )(GLenum target, GLenum pname, GLfixed param);
typedef void (OSG_APIENTRY * osgGlTexParameterxvOESProc )(GLenum target, GLenum pname, const GLfixed *params);
typedef void (OSG_APIENTRY * osgGlTranslatexOESProc )(GLfixed x, GLfixed y, GLfixed z);
typedef void (OSG_APIENTRY * osgGlAccumxOESProc )(GLenum op, GLfixed value);
typedef void (OSG_APIENTRY * osgGlBitmapxOESProc )(GLsizei width, GLsizei height, GLfixed xorig, GLfixed yorig, GLfixed xmove, GLfixed ymove, const GLubyte *bitmap);
typedef void (OSG_APIENTRY * osgGlBlendColorxOESProc )(GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha);
typedef void (OSG_APIENTRY * osgGlClearAccumxOESProc )(GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha);
typedef void (OSG_APIENTRY * osgGlColor3xOESProc )(GLfixed red, GLfixed green, GLfixed blue);
typedef void (OSG_APIENTRY * osgGlColor3xvOESProc )(const GLfixed *components);
typedef void (OSG_APIENTRY * osgGlColor4xvOESProc )(const GLfixed *components);
typedef void (OSG_APIENTRY * osgGlConvolutionParameterxOESProc )(GLenum target, GLenum pname, GLfixed param);
typedef void (OSG_APIENTRY * osgGlConvolutionParameterxvOESProc )(GLenum target, GLenum pname, const GLfixed *params);
typedef void (OSG_APIENTRY * osgGlEvalCoord1xOESProc )(GLfixed u);
typedef void (OSG_APIENTRY * osgGlEvalCoord1xvOESProc )(const GLfixed *coords);
typedef void (OSG_APIENTRY * osgGlEvalCoord2xOESProc )(GLfixed u, GLfixed v);
typedef void (OSG_APIENTRY * osgGlEvalCoord2xvOESProc )(const GLfixed *coords);
typedef void (OSG_APIENTRY * osgGlFeedbackBufferxOESProc )(GLsizei n, GLenum type, const GLfixed *buffer);
typedef void (OSG_APIENTRY * osgGlGetConvolutionParameterxvOESProc )(GLenum target, GLenum pname, GLfixed *params);
typedef void (OSG_APIENTRY * osgGlGetHistogramParameterxvOESProc )(GLenum target, GLenum pname, GLfixed *params);
typedef void (OSG_APIENTRY * osgGlGetLightxOESProc )(GLenum light, GLenum pname, GLfixed *params);
typedef void (OSG_APIENTRY * osgGlGetMapxvOESProc )(GLenum target, GLenum query, GLfixed *v);
typedef void (OSG_APIENTRY * osgGlGetMaterialxOESProc )(GLenum face, GLenum pname, GLfixed param);
typedef void (OSG_APIENTRY * osgGlGetPixelMapxvProc )(GLenum map, GLint size, GLfixed *values);
typedef void (OSG_APIENTRY * osgGlGetTexGenxvOESProc )(GLenum coord, GLenum pname, GLfixed *params);
typedef void (OSG_APIENTRY * osgGlGetTexLevelParameterxvOESProc )(GLenum target, GLint level, GLenum pname, GLfixed *params);
typedef void (OSG_APIENTRY * osgGlIndexxOESProc )(GLfixed component);
typedef void (OSG_APIENTRY * osgGlIndexxvOESProc )(const GLfixed *component);
typedef void (OSG_APIENTRY * osgGlLoadTransposeMatrixxOESProc )(const GLfixed *m);
typedef void (OSG_APIENTRY * osgGlMap1xOESProc )(GLenum target, GLfixed u1, GLfixed u2, GLint stride, GLint order, GLfixed points);
typedef void (OSG_APIENTRY * osgGlMap2xOESProc )(GLenum target, GLfixed u1, GLfixed u2, GLint ustride, GLint uorder, GLfixed v1, GLfixed v2, GLint vstride, GLint vorder, GLfixed points);
typedef void (OSG_APIENTRY * osgGlMapGrid1xOESProc )(GLint n, GLfixed u1, GLfixed u2);
typedef void (OSG_APIENTRY * osgGlMapGrid2xOESProc )(GLint n, GLfixed u1, GLfixed u2, GLfixed v1, GLfixed v2);
typedef void (OSG_APIENTRY * osgGlMultTransposeMatrixxOESProc )(const GLfixed *m);
typedef void (OSG_APIENTRY * osgGlMultiTexCoord1xOESProc )(GLenum texture, GLfixed s);
typedef void (OSG_APIENTRY * osgGlMultiTexCoord1xvOESProc )(GLenum texture, const GLfixed *coords);
typedef void (OSG_APIENTRY * osgGlMultiTexCoord2xOESProc )(GLenum texture, GLfixed s, GLfixed t);
typedef void (OSG_APIENTRY * osgGlMultiTexCoord2xvOESProc )(GLenum texture, const GLfixed *coords);
typedef void (OSG_APIENTRY * osgGlMultiTexCoord3xOESProc )(GLenum texture, GLfixed s, GLfixed t, GLfixed r);
typedef void (OSG_APIENTRY * osgGlMultiTexCoord3xvOESProc )(GLenum texture, const GLfixed *coords);
typedef void (OSG_APIENTRY * osgGlMultiTexCoord4xvOESProc )(GLenum texture, const GLfixed *coords);
typedef void (OSG_APIENTRY * osgGlNormal3xvOESProc )(const GLfixed *coords);
typedef void (OSG_APIENTRY * osgGlPassThroughxOESProc )(GLfixed token);
typedef void (OSG_APIENTRY * osgGlPixelMapxProc )(GLenum map, GLint size, const GLfixed *values);
typedef void (OSG_APIENTRY * osgGlPixelStorexProc )(GLenum pname, GLfixed param);
typedef void (OSG_APIENTRY * osgGlPixelTransferxOESProc )(GLenum pname, GLfixed param);
typedef void (OSG_APIENTRY * osgGlPixelZoomxOESProc )(GLfixed xfactor, GLfixed yfactor);
typedef void (OSG_APIENTRY * osgGlPrioritizeTexturesxOESProc )(GLsizei n, const GLuint *textures, const GLfixed *priorities);
typedef void (OSG_APIENTRY * osgGlRasterPos2xOESProc )(GLfixed x, GLfixed y);
typedef void (OSG_APIENTRY * osgGlRasterPos2xvOESProc )(const GLfixed *coords);
typedef void (OSG_APIENTRY * osgGlRasterPos3xOESProc )(GLfixed x, GLfixed y, GLfixed z);
typedef void (OSG_APIENTRY * osgGlRasterPos3xvOESProc )(const GLfixed *coords);
typedef void (OSG_APIENTRY * osgGlRasterPos4xOESProc )(GLfixed x, GLfixed y, GLfixed z, GLfixed w);
typedef void (OSG_APIENTRY * osgGlRasterPos4xvOESProc )(const GLfixed *coords);
typedef void (OSG_APIENTRY * osgGlRectxOESProc )(GLfixed x1, GLfixed y1, GLfixed x2, GLfixed y2);
typedef void (OSG_APIENTRY * osgGlRectxvOESProc )(const GLfixed *v1, const GLfixed *v2);
typedef void (OSG_APIENTRY * osgGlTexCoord1xOESProc )(GLfixed s);
typedef void (OSG_APIENTRY * osgGlTexCoord1xvOESProc )(const GLfixed *coords);
typedef void (OSG_APIENTRY * osgGlTexCoord2xOESProc )(GLfixed s, GLfixed t);
typedef void (OSG_APIENTRY * osgGlTexCoord2xvOESProc )(const GLfixed *coords);
typedef void (OSG_APIENTRY * osgGlTexCoord3xOESProc )(GLfixed s, GLfixed t, GLfixed r);
typedef void (OSG_APIENTRY * osgGlTexCoord3xvOESProc )(const GLfixed *coords);
typedef void (OSG_APIENTRY * osgGlTexCoord4xOESProc )(GLfixed s, GLfixed t, GLfixed r, GLfixed q);
typedef void (OSG_APIENTRY * osgGlTexCoord4xvOESProc )(const GLfixed *coords);
typedef void (OSG_APIENTRY * osgGlTexGenxOESProc )(GLenum coord, GLenum pname, GLfixed param);
typedef void (OSG_APIENTRY * osgGlTexGenxvOESProc )(GLenum coord, GLenum pname, const GLfixed *params);
typedef void (OSG_APIENTRY * osgGlVertex2xOESProc )(GLfixed x);
typedef void (OSG_APIENTRY * osgGlVertex2xvOESProc )(const GLfixed *coords);
typedef void (OSG_APIENTRY * osgGlVertex3xOESProc )(GLfixed x, GLfixed y);
typedef void (OSG_APIENTRY * osgGlVertex3xvOESProc )(const GLfixed *coords);
typedef void (OSG_APIENTRY * osgGlVertex4xOESProc )(GLfixed x, GLfixed y, GLfixed z);
typedef void (OSG_APIENTRY * osgGlVertex4xvOESProc )(const GLfixed *coords);
#endif /* GL_OES_fixed_point */

#ifdef GL_OES_query_matrix
typedef GLbitfield (OSG_APIENTRY * osgGlQueryMatrixxOESProc )(GLfixed *mantissa, GLint *exponent);
#endif /* GL_OES_query_matrix */

#ifdef GL_OES_read_format
#endif /* GL_OES_read_format */

#ifdef GL_OES_single_precision
typedef void (OSG_APIENTRY * osgGlClearDepthfOESProc )(GLclampf depth);
typedef void (OSG_APIENTRY * osgGlClipPlanefOESProc )(GLenum plane, const GLfloat *equation);
typedef void (OSG_APIENTRY * osgGlDepthRangefOESProc )(GLclampf n, GLclampf f);
typedef void (OSG_APIENTRY * osgGlFrustumfOESProc )(GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f);
typedef void (OSG_APIENTRY * osgGlGetClipPlanefOESProc )(GLenum plane, GLfloat *equation);
typedef void (OSG_APIENTRY * osgGlOrthofOESProc )(GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f);
#endif /* GL_OES_single_precision */

#ifdef GL_3DFX_multisample
#endif /* GL_3DFX_multisample */

#ifdef GL_3DFX_tbuffer
typedef void (OSG_APIENTRY * osgGlTbufferMask3DFXProc )(GLuint mask);
#endif /* GL_3DFX_tbuffer */

#ifdef GL_3DFX_texture_compression_FXT1
#endif /* GL_3DFX_texture_compression_FXT1 */

#ifdef GL_AMD_blend_minmax_factor
#endif /* GL_AMD_blend_minmax_factor */

#ifdef GL_AMD_conservative_depth
#endif /* GL_AMD_conservative_depth */

#ifdef GL_AMD_debug_output
typedef void (OSG_APIENTRY * osgGlDebugMessageEnableAMDProc )(GLenum category, GLenum severity, GLsizei count, const GLuint *ids, GLboolean enabled);
typedef void (OSG_APIENTRY * osgGlDebugMessageInsertAMDProc )(GLenum category, GLenum severity, GLuint id, GLsizei length, const GLchar *buf);
typedef void (OSG_APIENTRY * osgGlDebugMessageCallbackAMDProc )(GLDEBUGPROCAMD callback, void *userParam);
typedef GLuint (OSG_APIENTRY * osgGlGetDebugMessageLogAMDProc )(GLuint count, GLsizei bufsize, GLenum *categories, GLuint *severities, GLuint *ids, GLsizei *lengths, GLchar *message);
#endif /* GL_AMD_debug_output */

#ifdef GL_AMD_depth_clamp_separate
#endif /* GL_AMD_depth_clamp_separate */

#ifdef GL_AMD_draw_buffers_blend
typedef void (OSG_APIENTRY * osgGlBlendFuncIndexedAMDProc )(GLuint buf, GLenum src, GLenum dst);
typedef void (OSG_APIENTRY * osgGlBlendFuncSeparateIndexedAMDProc )(GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
typedef void (OSG_APIENTRY * osgGlBlendEquationIndexedAMDProc )(GLuint buf, GLenum mode);
typedef void (OSG_APIENTRY * osgGlBlendEquationSeparateIndexedAMDProc )(GLuint buf, GLenum modeRGB, GLenum modeAlpha);
#endif /* GL_AMD_draw_buffers_blend */

#ifdef GL_AMD_gcn_shader
#endif /* GL_AMD_gcn_shader */

#ifdef GL_AMD_gpu_shader_int64
typedef void (OSG_APIENTRY * osgGlUniform1i64NVProc )(GLint location, GLint64EXT x);
typedef void (OSG_APIENTRY * osgGlUniform2i64NVProc )(GLint location, GLint64EXT x, GLint64EXT y);
typedef void (OSG_APIENTRY * osgGlUniform3i64NVProc )(GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z);
typedef void (OSG_APIENTRY * osgGlUniform4i64NVProc )(GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z, GLint64EXT w);
typedef void (OSG_APIENTRY * osgGlUniform1i64vNVProc )(GLint location, GLsizei count, const GLint64EXT *value);
typedef void (OSG_APIENTRY * osgGlUniform2i64vNVProc )(GLint location, GLsizei count, const GLint64EXT *value);
typedef void (OSG_APIENTRY * osgGlUniform3i64vNVProc )(GLint location, GLsizei count, const GLint64EXT *value);
typedef void (OSG_APIENTRY * osgGlUniform4i64vNVProc )(GLint location, GLsizei count, const GLint64EXT *value);
typedef void (OSG_APIENTRY * osgGlUniform1ui64NVProc )(GLint location, GLuint64EXT x);
typedef void (OSG_APIENTRY * osgGlUniform2ui64NVProc )(GLint location, GLuint64EXT x, GLuint64EXT y);
typedef void (OSG_APIENTRY * osgGlUniform3ui64NVProc )(GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z);
typedef void (OSG_APIENTRY * osgGlUniform4ui64NVProc )(GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z, GLuint64EXT w);
typedef void (OSG_APIENTRY * osgGlUniform1ui64vNVProc )(GLint location, GLsizei count, const GLuint64EXT *value);
typedef void (OSG_APIENTRY * osgGlUniform2ui64vNVProc )(GLint location, GLsizei count, const GLuint64EXT *value);
typedef void (OSG_APIENTRY * osgGlUniform3ui64vNVProc )(GLint location, GLsizei count, const GLuint64EXT *value);
typedef void (OSG_APIENTRY * osgGlUniform4ui64vNVProc )(GLint location, GLsizei count, const GLuint64EXT *value);
typedef void (OSG_APIENTRY * osgGlGetUniformi64vNVProc )(GLuint program, GLint location, GLint64EXT *params);
typedef void (OSG_APIENTRY * osgGlGetUniformui64vNVProc )(GLuint program, GLint location, GLuint64EXT *params);
typedef void (OSG_APIENTRY * osgGlProgramUniform1i64NVProc )(GLuint program, GLint location, GLint64EXT x);
typedef void (OSG_APIENTRY * osgGlProgramUniform2i64NVProc )(GLuint program, GLint location, GLint64EXT x, GLint64EXT y);
typedef void (OSG_APIENTRY * osgGlProgramUniform3i64NVProc )(GLuint program, GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z);
typedef void (OSG_APIENTRY * osgGlProgramUniform4i64NVProc )(GLuint program, GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z, GLint64EXT w);
typedef void (OSG_APIENTRY * osgGlProgramUniform1i64vNVProc )(GLuint program, GLint location, GLsizei count, const GLint64EXT *value);
typedef void (OSG_APIENTRY * osgGlProgramUniform2i64vNVProc )(GLuint program, GLint location, GLsizei count, const GLint64EXT *value);
typedef void (OSG_APIENTRY * osgGlProgramUniform3i64vNVProc )(GLuint program, GLint location, GLsizei count, const GLint64EXT *value);
typedef void (OSG_APIENTRY * osgGlProgramUniform4i64vNVProc )(GLuint program, GLint location, GLsizei count, const GLint64EXT *value);
typedef void (OSG_APIENTRY * osgGlProgramUniform1ui64NVProc )(GLuint program, GLint location, GLuint64EXT x);
typedef void (OSG_APIENTRY * osgGlProgramUniform2ui64NVProc )(GLuint program, GLint location, GLuint64EXT x, GLuint64EXT y);
typedef void (OSG_APIENTRY * osgGlProgramUniform3ui64NVProc )(GLuint program, GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z);
typedef void (OSG_APIENTRY * osgGlProgramUniform4ui64NVProc )(GLuint program, GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z, GLuint64EXT w);
typedef void (OSG_APIENTRY * osgGlProgramUniform1ui64vNVProc )(GLuint program, GLint location, GLsizei count, const GLuint64EXT *value);
typedef void (OSG_APIENTRY * osgGlProgramUniform2ui64vNVProc )(GLuint program, GLint location, GLsizei count, const GLuint64EXT *value);
typedef void (OSG_APIENTRY * osgGlProgramUniform3ui64vNVProc )(GLuint program, GLint location, GLsizei count, const GLuint64EXT *value);
typedef void (OSG_APIENTRY * osgGlProgramUniform4ui64vNVProc )(GLuint program, GLint location, GLsizei count, const GLuint64EXT *value);
#endif /* GL_AMD_gpu_shader_int64 */

#ifdef GL_AMD_interleaved_elements
typedef void (OSG_APIENTRY * osgGlVertexAttribParameteriAMDProc )(GLuint index, GLenum pname, GLint param);
#endif /* GL_AMD_interleaved_elements */

#ifdef GL_AMD_multi_draw_indirect
typedef void (OSG_APIENTRY * osgGlMultiDrawArraysIndirectAMDProc )(GLenum mode, const void *indirect, GLsizei primcount, GLsizei stride);
typedef void (OSG_APIENTRY * osgGlMultiDrawElementsIndirectAMDProc )(GLenum mode, GLenum type, const void *indirect, GLsizei primcount, GLsizei stride);
#endif /* GL_AMD_multi_draw_indirect */

#ifdef GL_AMD_name_gen_delete
typedef void (OSG_APIENTRY * osgGlGenNamesAMDProc )(GLenum identifier, GLuint num, GLuint *names);
typedef void (OSG_APIENTRY * osgGlDeleteNamesAMDProc )(GLenum identifier, GLuint num, const GLuint *names);
typedef GLboolean (OSG_APIENTRY * osgGlIsNameAMDProc )(GLenum identifier, GLuint name);
#endif /* GL_AMD_name_gen_delete */

#ifdef GL_AMD_occlusion_query_event
typedef void (OSG_APIENTRY * osgGlQueryObjectParameteruiAMDProc )(GLenum target, GLuint id, GLenum pname, GLuint param);
#endif /* GL_AMD_occlusion_query_event */

#ifdef GL_AMD_performance_monitor
typedef void (OSG_APIENTRY * osgGlGetPerfMonitorGroupsAMDProc )(GLint *numGroups, GLsizei groupsSize, GLuint *groups);
typedef void (OSG_APIENTRY * osgGlGetPerfMonitorCountersAMDProc )(GLuint group, GLint *numCounters, GLint *maxActiveCounters, GLsizei counterSize, GLuint *counters);
typedef void (OSG_APIENTRY * osgGlGetPerfMonitorGroupStringAMDProc )(GLuint group, GLsizei bufSize, GLsizei *length, GLchar *groupString);
typedef void (OSG_APIENTRY * osgGlGetPerfMonitorCounterStringAMDProc )(GLuint group, GLuint counter, GLsizei bufSize, GLsizei *length, GLchar *counterString);
typedef void (OSG_APIENTRY * osgGlGetPerfMonitorCounterInfoAMDProc )(GLuint group, GLuint counter, GLenum pname, void *data);
typedef void (OSG_APIENTRY * osgGlGenPerfMonitorsAMDProc )(GLsizei n, GLuint *monitors);
typedef void (OSG_APIENTRY * osgGlDeletePerfMonitorsAMDProc )(GLsizei n, GLuint *monitors);
typedef void (OSG_APIENTRY * osgGlSelectPerfMonitorCountersAMDProc )(GLuint monitor, GLboolean enable, GLuint group, GLint numCounters, GLuint *counterList);
typedef void (OSG_APIENTRY * osgGlBeginPerfMonitorAMDProc )(GLuint monitor);
typedef void (OSG_APIENTRY * osgGlEndPerfMonitorAMDProc )(GLuint monitor);
typedef void (OSG_APIENTRY * osgGlGetPerfMonitorCounterDataAMDProc )(GLuint monitor, GLenum pname, GLsizei dataSize, GLuint *data, GLint *bytesWritten);
#endif /* GL_AMD_performance_monitor */

#ifdef GL_AMD_pinned_memory
#endif /* GL_AMD_pinned_memory */

#ifdef GL_AMD_query_buffer_object
#endif /* GL_AMD_query_buffer_object */

#ifdef GL_AMD_sample_positions
typedef void (OSG_APIENTRY * osgGlSetMultisamplefvAMDProc )(GLenum pname, GLuint index, const GLfloat *val);
#endif /* GL_AMD_sample_positions */

#ifdef GL_AMD_seamless_cubemap_per_texture
#endif /* GL_AMD_seamless_cubemap_per_texture */

#ifdef GL_AMD_shader_atomic_counter_ops
#endif /* GL_AMD_shader_atomic_counter_ops */

#ifdef GL_AMD_shader_stencil_export
#endif /* GL_AMD_shader_stencil_export */

#ifdef GL_AMD_shader_trinary_minmax
#endif /* GL_AMD_shader_trinary_minmax */

#ifdef GL_AMD_sparse_texture
typedef void (OSG_APIENTRY * osgGlTexStorageSparseAMDProc )(GLenum target, GLenum internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLsizei layers, GLbitfield flags);
typedef void (OSG_APIENTRY * osgGlTextureStorageSparseAMDProc )(GLuint texture, GLenum target, GLenum internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLsizei layers, GLbitfield flags);
#endif /* GL_AMD_sparse_texture */

#ifdef GL_AMD_stencil_operation_extended
typedef void (OSG_APIENTRY * osgGlStencilOpValueAMDProc )(GLenum face, GLuint value);
#endif /* GL_AMD_stencil_operation_extended */

#ifdef GL_AMD_texture_texture4
#endif /* GL_AMD_texture_texture4 */

#ifdef GL_AMD_transform_feedback3_lines_triangles
#endif /* GL_AMD_transform_feedback3_lines_triangles */

#ifdef GL_AMD_transform_feedback4
#endif /* GL_AMD_transform_feedback4 */

#ifdef GL_AMD_vertex_shader_layer
#endif /* GL_AMD_vertex_shader_layer */

#ifdef GL_AMD_vertex_shader_tessellator
typedef void (OSG_APIENTRY * osgGlTessellationFactorAMDProc )(GLfloat factor);
typedef void (OSG_APIENTRY * osgGlTessellationModeAMDProc )(GLenum mode);
#endif /* GL_AMD_vertex_shader_tessellator */

#ifdef GL_AMD_vertex_shader_viewport_index
#endif /* GL_AMD_vertex_shader_viewport_index */

#ifdef GL_APPLE_aux_depth_stencil
#endif /* GL_APPLE_aux_depth_stencil */

#ifdef GL_APPLE_client_storage
#endif /* GL_APPLE_client_storage */

#ifdef GL_APPLE_element_array
typedef void (OSG_APIENTRY * osgGlElementPointerAPPLEProc )(GLenum type, const void *pointer);
typedef void (OSG_APIENTRY * osgGlDrawElementArrayAPPLEProc )(GLenum mode, GLint first, GLsizei count);
typedef void (OSG_APIENTRY * osgGlDrawRangeElementArrayAPPLEProc )(GLenum mode, GLuint start, GLuint end, GLint first, GLsizei count);
typedef void (OSG_APIENTRY * osgGlMultiDrawElementArrayAPPLEProc )(GLenum mode, const GLint *first, const GLsizei *count, GLsizei primcount);
typedef void (OSG_APIENTRY * osgGlMultiDrawRangeElementArrayAPPLEProc )(GLenum mode, GLuint start, GLuint end, const GLint *first, const GLsizei *count, GLsizei primcount);
#endif /* GL_APPLE_element_array */

#ifdef GL_APPLE_fence
typedef void (OSG_APIENTRY * osgGlGenFencesAPPLEProc )(GLsizei n, GLuint *fences);
typedef void (OSG_APIENTRY * osgGlDeleteFencesAPPLEProc )(GLsizei n, const GLuint *fences);
typedef void (OSG_APIENTRY * osgGlSetFenceAPPLEProc )(GLuint fence);
typedef GLboolean (OSG_APIENTRY * osgGlIsFenceAPPLEProc )(GLuint fence);
typedef GLboolean (OSG_APIENTRY * osgGlTestFenceAPPLEProc )(GLuint fence);
typedef void (OSG_APIENTRY * osgGlFinishFenceAPPLEProc )(GLuint fence);
typedef GLboolean (OSG_APIENTRY * osgGlTestObjectAPPLEProc )(GLenum object, GLuint name);
typedef void (OSG_APIENTRY * osgGlFinishObjectAPPLEProc )(GLenum object, GLint name);
#endif /* GL_APPLE_fence */

#ifdef GL_APPLE_float_pixels
#endif /* GL_APPLE_float_pixels */

#ifdef GL_APPLE_flush_buffer_range
typedef void (OSG_APIENTRY * osgGlBufferParameteriAPPLEProc )(GLenum target, GLenum pname, GLint param);
typedef void (OSG_APIENTRY * osgGlFlushMappedBufferRangeAPPLEProc )(GLenum target, GLintptr offset, GLsizeiptr size);
#endif /* GL_APPLE_flush_buffer_range */

#ifdef GL_APPLE_object_purgeable
typedef GLenum (OSG_APIENTRY * osgGlObjectPurgeableAPPLEProc )(GLenum objectType, GLuint name, GLenum option);
typedef GLenum (OSG_APIENTRY * osgGlObjectUnpurgeableAPPLEProc )(GLenum objectType, GLuint name, GLenum option);
typedef void (OSG_APIENTRY * osgGlGetObjectParameterivAPPLEProc )(GLenum objectType, GLuint name, GLenum pname, GLint *params);
#endif /* GL_APPLE_object_purgeable */

#ifdef GL_APPLE_rgb_422
#endif /* GL_APPLE_rgb_422 */

#ifdef GL_APPLE_row_bytes
#endif /* GL_APPLE_row_bytes */

#ifdef GL_APPLE_specular_vector
#endif /* GL_APPLE_specular_vector */

#ifdef GL_APPLE_texture_range
typedef void (OSG_APIENTRY * osgGlTextureRangeAPPLEProc )(GLenum target, GLsizei length, const void *pointer);
typedef void (OSG_APIENTRY * osgGlGetTexParameterPointervAPPLEProc )(GLenum target, GLenum pname, void **params);
#endif /* GL_APPLE_texture_range */

#ifdef GL_APPLE_transform_hint
#endif /* GL_APPLE_transform_hint */

#ifdef GL_APPLE_vertex_array_object
typedef void (OSG_APIENTRY * osgGlBindVertexArrayAPPLEProc )(GLuint array);
typedef void (OSG_APIENTRY * osgGlDeleteVertexArraysAPPLEProc )(GLsizei n, const GLuint *arrays);
typedef void (OSG_APIENTRY * osgGlGenVertexArraysAPPLEProc )(GLsizei n, GLuint *arrays);
typedef GLboolean (OSG_APIENTRY * osgGlIsVertexArrayAPPLEProc )(GLuint array);
#endif /* GL_APPLE_vertex_array_object */

#ifdef GL_APPLE_vertex_array_range
typedef void (OSG_APIENTRY * osgGlVertexArrayRangeAPPLEProc )(GLsizei length, void *pointer);
typedef void (OSG_APIENTRY * osgGlFlushVertexArrayRangeAPPLEProc )(GLsizei length, void *pointer);
typedef void (OSG_APIENTRY * osgGlVertexArrayParameteriAPPLEProc )(GLenum pname, GLint param);
#endif /* GL_APPLE_vertex_array_range */

#ifdef GL_APPLE_vertex_program_evaluators
typedef void (OSG_APIENTRY * osgGlEnableVertexAttribAPPLEProc )(GLuint index, GLenum pname);
typedef void (OSG_APIENTRY * osgGlDisableVertexAttribAPPLEProc )(GLuint index, GLenum pname);
typedef GLboolean (OSG_APIENTRY * osgGlIsVertexAttribEnabledAPPLEProc )(GLuint index, GLenum pname);
typedef void (OSG_APIENTRY * osgGlMapVertexAttrib1dAPPLEProc )(GLuint index, GLuint size, GLdouble u1, GLdouble u2, GLint stride, GLint order, const GLdouble *points);
typedef void (OSG_APIENTRY * osgGlMapVertexAttrib1fAPPLEProc )(GLuint index, GLuint size, GLfloat u1, GLfloat u2, GLint stride, GLint order, const GLfloat *points);
typedef void (OSG_APIENTRY * osgGlMapVertexAttrib2dAPPLEProc )(GLuint index, GLuint size, GLdouble u1, GLdouble u2, GLint ustride, GLint uorder, GLdouble v1, GLdouble v2, GLint vstride, GLint vorder, const GLdouble *points);
typedef void (OSG_APIENTRY * osgGlMapVertexAttrib2fAPPLEProc )(GLuint index, GLuint size, GLfloat u1, GLfloat u2, GLint ustride, GLint uorder, GLfloat v1, GLfloat v2, GLint vstride, GLint vorder, const GLfloat *points);
#endif /* GL_APPLE_vertex_program_evaluators */

#ifdef GL_APPLE_ycbcr_422
#endif /* GL_APPLE_ycbcr_422 */

#ifdef GL_ATI_draw_buffers
typedef void (OSG_APIENTRY * osgGlDrawBuffersATIProc )(GLsizei n, const GLenum *bufs);
#endif /* GL_ATI_draw_buffers */

#ifdef GL_ATI_element_array
typedef void (OSG_APIENTRY * osgGlElementPointerATIProc )(GLenum type, const void *pointer);
typedef void (OSG_APIENTRY * osgGlDrawElementArrayATIProc )(GLenum mode, GLsizei count);
typedef void (OSG_APIENTRY * osgGlDrawRangeElementArrayATIProc )(GLenum mode, GLuint start, GLuint end, GLsizei count);
#endif /* GL_ATI_element_array */

#ifdef GL_ATI_envmap_bumpmap
typedef void (OSG_APIENTRY * osgGlTexBumpParameterivATIProc )(GLenum pname, const GLint *param);
typedef void (OSG_APIENTRY * osgGlTexBumpParameterfvATIProc )(GLenum pname, const GLfloat *param);
typedef void (OSG_APIENTRY * osgGlGetTexBumpParameterivATIProc )(GLenum pname, GLint *param);
typedef void (OSG_APIENTRY * osgGlGetTexBumpParameterfvATIProc )(GLenum pname, GLfloat *param);
#endif /* GL_ATI_envmap_bumpmap */

#ifdef GL_ATI_fragment_shader
typedef GLuint (OSG_APIENTRY * osgGlGenFragmentShadersATIProc )(GLuint range);
typedef void (OSG_APIENTRY * osgGlBindFragmentShaderATIProc )(GLuint id);
typedef void (OSG_APIENTRY * osgGlDeleteFragmentShaderATIProc )(GLuint id);
typedef void (OSG_APIENTRY * osgGlBeginFragmentShaderATIProc )(void);
typedef void (OSG_APIENTRY * osgGlEndFragmentShaderATIProc )(void);
typedef void (OSG_APIENTRY * osgGlPassTexCoordATIProc )(GLuint dst, GLuint coord, GLenum swizzle);
typedef void (OSG_APIENTRY * osgGlSampleMapATIProc )(GLuint dst, GLuint interp, GLenum swizzle);
typedef void (OSG_APIENTRY * osgGlColorFragmentOp1ATIProc )(GLenum op, GLuint dst, GLuint dstMask, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod);
typedef void (OSG_APIENTRY * osgGlColorFragmentOp2ATIProc )(GLenum op, GLuint dst, GLuint dstMask, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod, GLuint arg2, GLuint arg2Rep, GLuint arg2Mod);
typedef void (OSG_APIENTRY * osgGlColorFragmentOp3ATIProc )(GLenum op, GLuint dst, GLuint dstMask, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod, GLuint arg2, GLuint arg2Rep, GLuint arg2Mod, GLuint arg3, GLuint arg3Rep, GLuint arg3Mod);
typedef void (OSG_APIENTRY * osgGlAlphaFragmentOp1ATIProc )(GLenum op, GLuint dst, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod);
typedef void (OSG_APIENTRY * osgGlAlphaFragmentOp2ATIProc )(GLenum op, GLuint dst, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod, GLuint arg2, GLuint arg2Rep, GLuint arg2Mod);
typedef void (OSG_APIENTRY * osgGlAlphaFragmentOp3ATIProc )(GLenum op, GLuint dst, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod, GLuint arg2, GLuint arg2Rep, GLuint arg2Mod, GLuint arg3, GLuint arg3Rep, GLuint arg3Mod);
typedef void (OSG_APIENTRY * osgGlSetFragmentShaderConstantATIProc )(GLuint dst, const GLfloat *value);
#endif /* GL_ATI_fragment_shader */

#ifdef GL_ATI_map_object_buffer
typedef void *(OSG_APIENTRY * osgGlMapObjectBufferATIProc )(GLuint buffer);
typedef void (OSG_APIENTRY * osgGlUnmapObjectBufferATIProc )(GLuint buffer);
#endif /* GL_ATI_map_object_buffer */

#ifdef GL_ATI_meminfo
#endif /* GL_ATI_meminfo */

#ifdef GL_ATI_pixel_format_float
#endif /* GL_ATI_pixel_format_float */

#ifdef GL_ATI_pn_triangles
typedef void (OSG_APIENTRY * osgGlPNTrianglesiATIProc )(GLenum pname, GLint param);
typedef void (OSG_APIENTRY * osgGlPNTrianglesfATIProc )(GLenum pname, GLfloat param);
#endif /* GL_ATI_pn_triangles */

#ifdef GL_ATI_separate_stencil
typedef void (OSG_APIENTRY * osgGlStencilOpSeparateATIProc )(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass);
typedef void (OSG_APIENTRY * osgGlStencilFuncSeparateATIProc )(GLenum frontfunc, GLenum backfunc, GLint ref, GLuint mask);
#endif /* GL_ATI_separate_stencil */

#ifdef GL_ATI_text_fragment_shader
#endif /* GL_ATI_text_fragment_shader */

#ifdef GL_ATI_texture_env_combine3
#endif /* GL_ATI_texture_env_combine3 */

#ifdef GL_ATI_texture_float
#endif /* GL_ATI_texture_float */

#ifdef GL_ATI_texture_mirror_once
#endif /* GL_ATI_texture_mirror_once */

#ifdef GL_ATI_vertex_array_object
typedef GLuint (OSG_APIENTRY * osgGlNewObjectBufferATIProc )(GLsizei size, const void *pointer, GLenum usage);
typedef GLboolean (OSG_APIENTRY * osgGlIsObjectBufferATIProc )(GLuint buffer);
typedef void (OSG_APIENTRY * osgGlUpdateObjectBufferATIProc )(GLuint buffer, GLuint offset, GLsizei size, const void *pointer, GLenum preserve);
typedef void (OSG_APIENTRY * osgGlGetObjectBufferfvATIProc )(GLuint buffer, GLenum pname, GLfloat *params);
typedef void (OSG_APIENTRY * osgGlGetObjectBufferivATIProc )(GLuint buffer, GLenum pname, GLint *params);
typedef void (OSG_APIENTRY * osgGlFreeObjectBufferATIProc )(GLuint buffer);
typedef void (OSG_APIENTRY * osgGlArrayObjectATIProc )(GLenum array, GLint size, GLenum type, GLsizei stride, GLuint buffer, GLuint offset);
typedef void (OSG_APIENTRY * osgGlGetArrayObjectfvATIProc )(GLenum array, GLenum pname, GLfloat *params);
typedef void (OSG_APIENTRY * osgGlGetArrayObjectivATIProc )(GLenum array, GLenum pname, GLint *params);
typedef void (OSG_APIENTRY * osgGlVariantArrayObjectATIProc )(GLuint id, GLenum type, GLsizei stride, GLuint buffer, GLuint offset);
typedef void (OSG_APIENTRY * osgGlGetVariantArrayObjectfvATIProc )(GLuint id, GLenum pname, GLfloat *params);
typedef void (OSG_APIENTRY * osgGlGetVariantArrayObjectivATIProc )(GLuint id, GLenum pname, GLint *params);
#endif /* GL_ATI_vertex_array_object */

#ifdef GL_ATI_vertex_attrib_array_object
typedef void (OSG_APIENTRY * osgGlVertexAttribArrayObjectATIProc )(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, GLuint buffer, GLuint offset);
typedef void (OSG_APIENTRY * osgGlGetVertexAttribArrayObjectfvATIProc )(GLuint index, GLenum pname, GLfloat *params);
typedef void (OSG_APIENTRY * osgGlGetVertexAttribArrayObjectivATIProc )(GLuint index, GLenum pname, GLint *params);
#endif /* GL_ATI_vertex_attrib_array_object */

#ifdef GL_ATI_vertex_streams
typedef void (OSG_APIENTRY * osgGlVertexStream1sATIProc )(GLenum stream, GLshort x);
typedef void (OSG_APIENTRY * osgGlVertexStream1svATIProc )(GLenum stream, const GLshort *coords);
typedef void (OSG_APIENTRY * osgGlVertexStream1iATIProc )(GLenum stream, GLint x);
typedef void (OSG_APIENTRY * osgGlVertexStream1ivATIProc )(GLenum stream, const GLint *coords);
typedef void (OSG_APIENTRY * osgGlVertexStream1fATIProc )(GLenum stream, GLfloat x);
typedef void (OSG_APIENTRY * osgGlVertexStream1fvATIProc )(GLenum stream, const GLfloat *coords);
typedef void (OSG_APIENTRY * osgGlVertexStream1dATIProc )(GLenum stream, GLdouble x);
typedef void (OSG_APIENTRY * osgGlVertexStream1dvATIProc )(GLenum stream, const GLdouble *coords);
typedef void (OSG_APIENTRY * osgGlVertexStream2sATIProc )(GLenum stream, GLshort x, GLshort y);
typedef void (OSG_APIENTRY * osgGlVertexStream2svATIProc )(GLenum stream, const GLshort *coords);
typedef void (OSG_APIENTRY * osgGlVertexStream2iATIProc )(GLenum stream, GLint x, GLint y);
typedef void (OSG_APIENTRY * osgGlVertexStream2ivATIProc )(GLenum stream, const GLint *coords);
typedef void (OSG_APIENTRY * osgGlVertexStream2fATIProc )(GLenum stream, GLfloat x, GLfloat y);
typedef void (OSG_APIENTRY * osgGlVertexStream2fvATIProc )(GLenum stream, const GLfloat *coords);
typedef void (OSG_APIENTRY * osgGlVertexStream2dATIProc )(GLenum stream, GLdouble x, GLdouble y);
typedef void (OSG_APIENTRY * osgGlVertexStream2dvATIProc )(GLenum stream, const GLdouble *coords);
typedef void (OSG_APIENTRY * osgGlVertexStream3sATIProc )(GLenum stream, GLshort x, GLshort y, GLshort z);
typedef void (OSG_APIENTRY * osgGlVertexStream3svATIProc )(GLenum stream, const GLshort *coords);
typedef void (OSG_APIENTRY * osgGlVertexStream3iATIProc )(GLenum stream, GLint x, GLint y, GLint z);
typedef void (OSG_APIENTRY * osgGlVertexStream3ivATIProc )(GLenum stream, const GLint *coords);
typedef void (OSG_APIENTRY * osgGlVertexStream3fATIProc )(GLenum stream, GLfloat x, GLfloat y, GLfloat z);
typedef void (OSG_APIENTRY * osgGlVertexStream3fvATIProc )(GLenum stream, const GLfloat *coords);
typedef void (OSG_APIENTRY * osgGlVertexStream3dATIProc )(GLenum stream, GLdouble x, GLdouble y, GLdouble z);
typedef void (OSG_APIENTRY * osgGlVertexStream3dvATIProc )(GLenum stream, const GLdouble *coords);
typedef void (OSG_APIENTRY * osgGlVertexStream4sATIProc )(GLenum stream, GLshort x, GLshort y, GLshort z, GLshort w);
typedef void (OSG_APIENTRY * osgGlVertexStream4svATIProc )(GLenum stream, const GLshort *coords);
typedef void (OSG_APIENTRY * osgGlVertexStream4iATIProc )(GLenum stream, GLint x, GLint y, GLint z, GLint w);
typedef void (OSG_APIENTRY * osgGlVertexStream4ivATIProc )(GLenum stream, const GLint *coords);
typedef void (OSG_APIENTRY * osgGlVertexStream4fATIProc )(GLenum stream, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
typedef void (OSG_APIENTRY * osgGlVertexStream4fvATIProc )(GLenum stream, const GLfloat *coords);
typedef void (OSG_APIENTRY * osgGlVertexStream4dATIProc )(GLenum stream, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
typedef void (OSG_APIENTRY * osgGlVertexStream4dvATIProc )(GLenum stream, const GLdouble *coords);
typedef void (OSG_APIENTRY * osgGlNormalStream3bATIProc )(GLenum stream, GLbyte nx, GLbyte ny, GLbyte nz);
typedef void (OSG_APIENTRY * osgGlNormalStream3bvATIProc )(GLenum stream, const GLbyte *coords);
typedef void (OSG_APIENTRY * osgGlNormalStream3sATIProc )(GLenum stream, GLshort nx, GLshort ny, GLshort nz);
typedef void (OSG_APIENTRY * osgGlNormalStream3svATIProc )(GLenum stream, const GLshort *coords);
typedef void (OSG_APIENTRY * osgGlNormalStream3iATIProc )(GLenum stream, GLint nx, GLint ny, GLint nz);
typedef void (OSG_APIENTRY * osgGlNormalStream3ivATIProc )(GLenum stream, const GLint *coords);
typedef void (OSG_APIENTRY * osgGlNormalStream3fATIProc )(GLenum stream, GLfloat nx, GLfloat ny, GLfloat nz);
typedef void (OSG_APIENTRY * osgGlNormalStream3fvATIProc )(GLenum stream, const GLfloat *coords);
typedef void (OSG_APIENTRY * osgGlNormalStream3dATIProc )(GLenum stream, GLdouble nx, GLdouble ny, GLdouble nz);
typedef void (OSG_APIENTRY * osgGlNormalStream3dvATIProc )(GLenum stream, const GLdouble *coords);
typedef void (OSG_APIENTRY * osgGlClientActiveVertexStreamATIProc )(GLenum stream);
typedef void (OSG_APIENTRY * osgGlVertexBlendEnviATIProc )(GLenum pname, GLint param);
typedef void (OSG_APIENTRY * osgGlVertexBlendEnvfATIProc )(GLenum pname, GLfloat param);
#endif /* GL_ATI_vertex_streams */

#ifdef GL_EXT_422_pixels
#endif /* GL_EXT_422_pixels */

#ifdef GL_EXT_abgr
#endif /* GL_EXT_abgr */

#ifdef GL_EXT_bgra
#endif /* GL_EXT_bgra */

#ifdef GL_EXT_bindable_uniform
typedef void (OSG_APIENTRY * osgGlUniformBufferEXTProc )(GLuint program, GLint location, GLuint buffer);
typedef GLint (OSG_APIENTRY * osgGlGetUniformBufferSizeEXTProc )(GLuint program, GLint location);
typedef GLintptr (OSG_APIENTRY * osgGlGetUniformOffsetEXTProc )(GLuint program, GLint location);
#endif /* GL_EXT_bindable_uniform */

#ifdef GL_EXT_blend_color
typedef void (OSG_APIENTRY * osgGlBlendColorEXTProc )(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
#endif /* GL_EXT_blend_color */

#ifdef GL_EXT_blend_equation_separate
typedef void (OSG_APIENTRY * osgGlBlendEquationSeparateEXTProc )(GLenum modeRGB, GLenum modeAlpha);
#endif /* GL_EXT_blend_equation_separate */

#ifdef GL_EXT_blend_func_separate
typedef void (OSG_APIENTRY * osgGlBlendFuncSeparateEXTProc )(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);
#endif /* GL_EXT_blend_func_separate */

#ifdef GL_EXT_blend_logic_op
#endif /* GL_EXT_blend_logic_op */

#ifdef GL_EXT_blend_minmax
typedef void (OSG_APIENTRY * osgGlBlendEquationEXTProc )(GLenum mode);
#endif /* GL_EXT_blend_minmax */

#ifdef GL_EXT_blend_subtract
#endif /* GL_EXT_blend_subtract */

#ifdef GL_EXT_clip_volume_hint
#endif /* GL_EXT_clip_volume_hint */

#ifdef GL_EXT_cmyka
#endif /* GL_EXT_cmyka */

#ifdef GL_EXT_color_subtable
typedef void (OSG_APIENTRY * osgGlColorSubTableEXTProc )(GLenum target, GLsizei start, GLsizei count, GLenum format, GLenum type, const void *data);
typedef void (OSG_APIENTRY * osgGlCopyColorSubTableEXTProc )(GLenum target, GLsizei start, GLint x, GLint y, GLsizei width);
#endif /* GL_EXT_color_subtable */

#ifdef GL_EXT_compiled_vertex_array
typedef void (OSG_APIENTRY * osgGlLockArraysEXTProc )(GLint first, GLsizei count);
typedef void (OSG_APIENTRY * osgGlUnlockArraysEXTProc )(void);
#endif /* GL_EXT_compiled_vertex_array */

#ifdef GL_EXT_convolution
typedef void (OSG_APIENTRY * osgGlConvolutionFilter1DEXTProc )(GLenum target, GLenum internalformat, GLsizei width, GLenum format, GLenum type, const void *image);
typedef void (OSG_APIENTRY * osgGlConvolutionFilter2DEXTProc )(GLenum target, GLenum internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const void *image);
typedef void (OSG_APIENTRY * osgGlConvolutionParameterfEXTProc )(GLenum target, GLenum pname, GLfloat params);
typedef void (OSG_APIENTRY * osgGlConvolutionParameterfvEXTProc )(GLenum target, GLenum pname, const GLfloat *params);
typedef void (OSG_APIENTRY * osgGlConvolutionParameteriEXTProc )(GLenum target, GLenum pname, GLint params);
typedef void (OSG_APIENTRY * osgGlConvolutionParameterivEXTProc )(GLenum target, GLenum pname, const GLint *params);
typedef void (OSG_APIENTRY * osgGlCopyConvolutionFilter1DEXTProc )(GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width);
typedef void (OSG_APIENTRY * osgGlCopyConvolutionFilter2DEXTProc )(GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (OSG_APIENTRY * osgGlGetConvolutionFilterEXTProc )(GLenum target, GLenum format, GLenum type, void *image);
typedef void (OSG_APIENTRY * osgGlGetConvolutionParameterfvEXTProc )(GLenum target, GLenum pname, GLfloat *params);
typedef void (OSG_APIENTRY * osgGlGetConvolutionParameterivEXTProc )(GLenum target, GLenum pname, GLint *params);
typedef void (OSG_APIENTRY * osgGlGetSeparableFilterEXTProc )(GLenum target, GLenum format, GLenum type, void *row, void *column, void *span);
typedef void (OSG_APIENTRY * osgGlSeparableFilter2DEXTProc )(GLenum target, GLenum internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const void *row, const void *column);
#endif /* GL_EXT_convolution */

#ifdef GL_EXT_coordinate_frame
typedef void (OSG_APIENTRY * osgGlTangent3bEXTProc )(GLbyte tx, GLbyte ty, GLbyte tz);
typedef void (OSG_APIENTRY * osgGlTangent3bvEXTProc )(const GLbyte *v);
typedef void (OSG_APIENTRY * osgGlTangent3dEXTProc )(GLdouble tx, GLdouble ty, GLdouble tz);
typedef void (OSG_APIENTRY * osgGlTangent3dvEXTProc )(const GLdouble *v);
typedef void (OSG_APIENTRY * osgGlTangent3fEXTProc )(GLfloat tx, GLfloat ty, GLfloat tz);
typedef void (OSG_APIENTRY * osgGlTangent3fvEXTProc )(const GLfloat *v);
typedef void (OSG_APIENTRY * osgGlTangent3iEXTProc )(GLint tx, GLint ty, GLint tz);
typedef void (OSG_APIENTRY * osgGlTangent3ivEXTProc )(const GLint *v);
typedef void (OSG_APIENTRY * osgGlTangent3sEXTProc )(GLshort tx, GLshort ty, GLshort tz);
typedef void (OSG_APIENTRY * osgGlTangent3svEXTProc )(const GLshort *v);
typedef void (OSG_APIENTRY * osgGlBinormal3bEXTProc )(GLbyte bx, GLbyte by, GLbyte bz);
typedef void (OSG_APIENTRY * osgGlBinormal3bvEXTProc )(const GLbyte *v);
typedef void (OSG_APIENTRY * osgGlBinormal3dEXTProc )(GLdouble bx, GLdouble by, GLdouble bz);
typedef void (OSG_APIENTRY * osgGlBinormal3dvEXTProc )(const GLdouble *v);
typedef void (OSG_APIENTRY * osgGlBinormal3fEXTProc )(GLfloat bx, GLfloat by, GLfloat bz);
typedef void (OSG_APIENTRY * osgGlBinormal3fvEXTProc )(const GLfloat *v);
typedef void (OSG_APIENTRY * osgGlBinormal3iEXTProc )(GLint bx, GLint by, GLint bz);
typedef void (OSG_APIENTRY * osgGlBinormal3ivEXTProc )(const GLint *v);
typedef void (OSG_APIENTRY * osgGlBinormal3sEXTProc )(GLshort bx, GLshort by, GLshort bz);
typedef void (OSG_APIENTRY * osgGlBinormal3svEXTProc )(const GLshort *v);
typedef void (OSG_APIENTRY * osgGlTangentPointerEXTProc )(GLenum type, GLsizei stride, const void *pointer);
typedef void (OSG_APIENTRY * osgGlBinormalPointerEXTProc )(GLenum type, GLsizei stride, const void *pointer);
#endif /* GL_EXT_coordinate_frame */

#ifdef GL_EXT_copy_texture
typedef void (OSG_APIENTRY * osgGlCopyTexImage1DEXTProc )(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border);
typedef void (OSG_APIENTRY * osgGlCopyTexImage2DEXTProc )(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
typedef void (OSG_APIENTRY * osgGlCopyTexSubImage1DEXTProc )(GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width);
typedef void (OSG_APIENTRY * osgGlCopyTexSubImage2DEXTProc )(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (OSG_APIENTRY * osgGlCopyTexSubImage3DEXTProc )(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);
#endif /* GL_EXT_copy_texture */

#ifdef GL_EXT_cull_vertex
typedef void (OSG_APIENTRY * osgGlCullParameterdvEXTProc )(GLenum pname, GLdouble *params);
typedef void (OSG_APIENTRY * osgGlCullParameterfvEXTProc )(GLenum pname, GLfloat *params);
#endif /* GL_EXT_cull_vertex */

#ifdef GL_EXT_debug_label
typedef void (OSG_APIENTRY * osgGlLabelObjectEXTProc )(GLenum type, GLuint object, GLsizei length, const GLchar *label);
typedef void (OSG_APIENTRY * osgGlGetObjectLabelEXTProc )(GLenum type, GLuint object, GLsizei bufSize, GLsizei *length, GLchar *label);
#endif /* GL_EXT_debug_label */

#ifdef GL_EXT_debug_marker
typedef void (OSG_APIENTRY * osgGlInsertEventMarkerEXTProc )(GLsizei length, const GLchar *marker);
typedef void (OSG_APIENTRY * osgGlPushGroupMarkerEXTProc )(GLsizei length, const GLchar *marker);
typedef void (OSG_APIENTRY * osgGlPopGroupMarkerEXTProc )(void);
#endif /* GL_EXT_debug_marker */

#ifdef GL_EXT_depth_bounds_test
typedef void (OSG_APIENTRY * osgGlDepthBoundsEXTProc )(GLclampd zmin, GLclampd zmax);
#endif /* GL_EXT_depth_bounds_test */

#ifdef GL_EXT_direct_state_access
typedef void (OSG_APIENTRY * osgGlMatrixLoadfEXTProc )(GLenum mode, const GLfloat *m);
typedef void (OSG_APIENTRY * osgGlMatrixLoaddEXTProc )(GLenum mode, const GLdouble *m);
typedef void (OSG_APIENTRY * osgGlMatrixMultfEXTProc )(GLenum mode, const GLfloat *m);
typedef void (OSG_APIENTRY * osgGlMatrixMultdEXTProc )(GLenum mode, const GLdouble *m);
typedef void (OSG_APIENTRY * osgGlMatrixLoadIdentityEXTProc )(GLenum mode);
typedef void (OSG_APIENTRY * osgGlMatrixRotatefEXTProc )(GLenum mode, GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
typedef void (OSG_APIENTRY * osgGlMatrixRotatedEXTProc )(GLenum mode, GLdouble angle, GLdouble x, GLdouble y, GLdouble z);
typedef void (OSG_APIENTRY * osgGlMatrixScalefEXTProc )(GLenum mode, GLfloat x, GLfloat y, GLfloat z);
typedef void (OSG_APIENTRY * osgGlMatrixScaledEXTProc )(GLenum mode, GLdouble x, GLdouble y, GLdouble z);
typedef void (OSG_APIENTRY * osgGlMatrixTranslatefEXTProc )(GLenum mode, GLfloat x, GLfloat y, GLfloat z);
typedef void (OSG_APIENTRY * osgGlMatrixTranslatedEXTProc )(GLenum mode, GLdouble x, GLdouble y, GLdouble z);
typedef void (OSG_APIENTRY * osgGlMatrixFrustumEXTProc )(GLenum mode, GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar);
typedef void (OSG_APIENTRY * osgGlMatrixOrthoEXTProc )(GLenum mode, GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar);
typedef void (OSG_APIENTRY * osgGlMatrixPopEXTProc )(GLenum mode);
typedef void (OSG_APIENTRY * osgGlMatrixPushEXTProc )(GLenum mode);
typedef void (OSG_APIENTRY * osgGlClientAttribDefaultEXTProc )(GLbitfield mask);
typedef void (OSG_APIENTRY * osgGlPushClientAttribDefaultEXTProc )(GLbitfield mask);
typedef void (OSG_APIENTRY * osgGlTextureParameterfEXTProc )(GLuint texture, GLenum target, GLenum pname, GLfloat param);
typedef void (OSG_APIENTRY * osgGlTextureParameterfvEXTProc )(GLuint texture, GLenum target, GLenum pname, const GLfloat *params);
typedef void (OSG_APIENTRY * osgGlTextureParameteriEXTProc )(GLuint texture, GLenum target, GLenum pname, GLint param);
typedef void (OSG_APIENTRY * osgGlTextureParameterivEXTProc )(GLuint texture, GLenum target, GLenum pname, const GLint *params);
typedef void (OSG_APIENTRY * osgGlTextureImage1DEXTProc )(GLuint texture, GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const void *pixels);
typedef void (OSG_APIENTRY * osgGlTextureImage2DEXTProc )(GLuint texture, GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void *pixels);
typedef void (OSG_APIENTRY * osgGlTextureSubImage1DEXTProc )(GLuint texture, GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void *pixels);
typedef void (OSG_APIENTRY * osgGlTextureSubImage2DEXTProc )(GLuint texture, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void *pixels);
typedef void (OSG_APIENTRY * osgGlCopyTextureImage1DEXTProc )(GLuint texture, GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border);
typedef void (OSG_APIENTRY * osgGlCopyTextureImage2DEXTProc )(GLuint texture, GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
typedef void (OSG_APIENTRY * osgGlCopyTextureSubImage1DEXTProc )(GLuint texture, GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width);
typedef void (OSG_APIENTRY * osgGlCopyTextureSubImage2DEXTProc )(GLuint texture, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (OSG_APIENTRY * osgGlGetTextureImageEXTProc )(GLuint texture, GLenum target, GLint level, GLenum format, GLenum type, void *pixels);
typedef void (OSG_APIENTRY * osgGlGetTextureParameterfvEXTProc )(GLuint texture, GLenum target, GLenum pname, GLfloat *params);
typedef void (OSG_APIENTRY * osgGlGetTextureParameterivEXTProc )(GLuint texture, GLenum target, GLenum pname, GLint *params);
typedef void (OSG_APIENTRY * osgGlGetTextureLevelParameterfvEXTProc )(GLuint texture, GLenum target, GLint level, GLenum pname, GLfloat *params);
typedef void (OSG_APIENTRY * osgGlGetTextureLevelParameterivEXTProc )(GLuint texture, GLenum target, GLint level, GLenum pname, GLint *params);
typedef void (OSG_APIENTRY * osgGlTextureImage3DEXTProc )(GLuint texture, GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void *pixels);
typedef void (OSG_APIENTRY * osgGlTextureSubImage3DEXTProc )(GLuint texture, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *pixels);
typedef void (OSG_APIENTRY * osgGlCopyTextureSubImage3DEXTProc )(GLuint texture, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (OSG_APIENTRY * osgGlBindMultiTextureEXTProc )(GLenum texunit, GLenum target, GLuint texture);
typedef void (OSG_APIENTRY * osgGlMultiTexCoordPointerEXTProc )(GLenum texunit, GLint size, GLenum type, GLsizei stride, const void *pointer);
typedef void (OSG_APIENTRY * osgGlMultiTexEnvfEXTProc )(GLenum texunit, GLenum target, GLenum pname, GLfloat param);
typedef void (OSG_APIENTRY * osgGlMultiTexEnvfvEXTProc )(GLenum texunit, GLenum target, GLenum pname, const GLfloat *params);
typedef void (OSG_APIENTRY * osgGlMultiTexEnviEXTProc )(GLenum texunit, GLenum target, GLenum pname, GLint param);
typedef void (OSG_APIENTRY * osgGlMultiTexEnvivEXTProc )(GLenum texunit, GLenum target, GLenum pname, const GLint *params);
typedef void (OSG_APIENTRY * osgGlMultiTexGendEXTProc )(GLenum texunit, GLenum coord, GLenum pname, GLdouble param);
typedef void (OSG_APIENTRY * osgGlMultiTexGendvEXTProc )(GLenum texunit, GLenum coord, GLenum pname, const GLdouble *params);
typedef void (OSG_APIENTRY * osgGlMultiTexGenfEXTProc )(GLenum texunit, GLenum coord, GLenum pname, GLfloat param);
typedef void (OSG_APIENTRY * osgGlMultiTexGenfvEXTProc )(GLenum texunit, GLenum coord, GLenum pname, const GLfloat *params);
typedef void (OSG_APIENTRY * osgGlMultiTexGeniEXTProc )(GLenum texunit, GLenum coord, GLenum pname, GLint param);
typedef void (OSG_APIENTRY * osgGlMultiTexGenivEXTProc )(GLenum texunit, GLenum coord, GLenum pname, const GLint *params);
typedef void (OSG_APIENTRY * osgGlGetMultiTexEnvfvEXTProc )(GLenum texunit, GLenum target, GLenum pname, GLfloat *params);
typedef void (OSG_APIENTRY * osgGlGetMultiTexEnvivEXTProc )(GLenum texunit, GLenum target, GLenum pname, GLint *params);
typedef void (OSG_APIENTRY * osgGlGetMultiTexGendvEXTProc )(GLenum texunit, GLenum coord, GLenum pname, GLdouble *params);
typedef void (OSG_APIENTRY * osgGlGetMultiTexGenfvEXTProc )(GLenum texunit, GLenum coord, GLenum pname, GLfloat *params);
typedef void (OSG_APIENTRY * osgGlGetMultiTexGenivEXTProc )(GLenum texunit, GLenum coord, GLenum pname, GLint *params);
typedef void (OSG_APIENTRY * osgGlMultiTexParameteriEXTProc )(GLenum texunit, GLenum target, GLenum pname, GLint param);
typedef void (OSG_APIENTRY * osgGlMultiTexParameterivEXTProc )(GLenum texunit, GLenum target, GLenum pname, const GLint *params);
typedef void (OSG_APIENTRY * osgGlMultiTexParameterfEXTProc )(GLenum texunit, GLenum target, GLenum pname, GLfloat param);
typedef void (OSG_APIENTRY * osgGlMultiTexParameterfvEXTProc )(GLenum texunit, GLenum target, GLenum pname, const GLfloat *params);
typedef void (OSG_APIENTRY * osgGlMultiTexImage1DEXTProc )(GLenum texunit, GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const void *pixels);
typedef void (OSG_APIENTRY * osgGlMultiTexImage2DEXTProc )(GLenum texunit, GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void *pixels);
typedef void (OSG_APIENTRY * osgGlMultiTexSubImage1DEXTProc )(GLenum texunit, GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void *pixels);
typedef void (OSG_APIENTRY * osgGlMultiTexSubImage2DEXTProc )(GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void *pixels);
typedef void (OSG_APIENTRY * osgGlCopyMultiTexImage1DEXTProc )(GLenum texunit, GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border);
typedef void (OSG_APIENTRY * osgGlCopyMultiTexImage2DEXTProc )(GLenum texunit, GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
typedef void (OSG_APIENTRY * osgGlCopyMultiTexSubImage1DEXTProc )(GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width);
typedef void (OSG_APIENTRY * osgGlCopyMultiTexSubImage2DEXTProc )(GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (OSG_APIENTRY * osgGlGetMultiTexImageEXTProc )(GLenum texunit, GLenum target, GLint level, GLenum format, GLenum type, void *pixels);
typedef void (OSG_APIENTRY * osgGlGetMultiTexParameterfvEXTProc )(GLenum texunit, GLenum target, GLenum pname, GLfloat *params);
typedef void (OSG_APIENTRY * osgGlGetMultiTexParameterivEXTProc )(GLenum texunit, GLenum target, GLenum pname, GLint *params);
typedef void (OSG_APIENTRY * osgGlGetMultiTexLevelParameterfvEXTProc )(GLenum texunit, GLenum target, GLint level, GLenum pname, GLfloat *params);
typedef void (OSG_APIENTRY * osgGlGetMultiTexLevelParameterivEXTProc )(GLenum texunit, GLenum target, GLint level, GLenum pname, GLint *params);
typedef void (OSG_APIENTRY * osgGlMultiTexImage3DEXTProc )(GLenum texunit, GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void *pixels);
typedef void (OSG_APIENTRY * osgGlMultiTexSubImage3DEXTProc )(GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *pixels);
typedef void (OSG_APIENTRY * osgGlCopyMultiTexSubImage3DEXTProc )(GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (OSG_APIENTRY * osgGlEnableClientStateIndexedEXTProc )(GLenum array, GLuint index);
typedef void (OSG_APIENTRY * osgGlDisableClientStateIndexedEXTProc )(GLenum array, GLuint index);
typedef void (OSG_APIENTRY * osgGlGetFloatIndexedvEXTProc )(GLenum target, GLuint index, GLfloat *data);
typedef void (OSG_APIENTRY * osgGlGetDoubleIndexedvEXTProc )(GLenum target, GLuint index, GLdouble *data);
typedef void (OSG_APIENTRY * osgGlGetPointerIndexedvEXTProc )(GLenum target, GLuint index, void **data);
typedef void (OSG_APIENTRY * osgGlEnableIndexedEXTProc )(GLenum target, GLuint index);
typedef void (OSG_APIENTRY * osgGlDisableIndexedEXTProc )(GLenum target, GLuint index);
typedef GLboolean (OSG_APIENTRY * osgGlIsEnabledIndexedEXTProc )(GLenum target, GLuint index);
typedef void (OSG_APIENTRY * osgGlGetIntegerIndexedvEXTProc )(GLenum target, GLuint index, GLint *data);
typedef void (OSG_APIENTRY * osgGlGetBooleanIndexedvEXTProc )(GLenum target, GLuint index, GLboolean *data);
typedef void (OSG_APIENTRY * osgGlCompressedTextureImage3DEXTProc )(GLuint texture, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void *bits);
typedef void (OSG_APIENTRY * osgGlCompressedTextureImage2DEXTProc )(GLuint texture, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void *bits);
typedef void (OSG_APIENTRY * osgGlCompressedTextureImage1DEXTProc )(GLuint texture, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const void *bits);
typedef void (OSG_APIENTRY * osgGlCompressedTextureSubImage3DEXTProc )(GLuint texture, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void *bits);
typedef void (OSG_APIENTRY * osgGlCompressedTextureSubImage2DEXTProc )(GLuint texture, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void *bits);
typedef void (OSG_APIENTRY * osgGlCompressedTextureSubImage1DEXTProc )(GLuint texture, GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void *bits);
typedef void (OSG_APIENTRY * osgGlGetCompressedTextureImageEXTProc )(GLuint texture, GLenum target, GLint lod, void *img);
typedef void (OSG_APIENTRY * osgGlCompressedMultiTexImage3DEXTProc )(GLenum texunit, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void *bits);
typedef void (OSG_APIENTRY * osgGlCompressedMultiTexImage2DEXTProc )(GLenum texunit, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void *bits);
typedef void (OSG_APIENTRY * osgGlCompressedMultiTexImage1DEXTProc )(GLenum texunit, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const void *bits);
typedef void (OSG_APIENTRY * osgGlCompressedMultiTexSubImage3DEXTProc )(GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void *bits);
typedef void (OSG_APIENTRY * osgGlCompressedMultiTexSubImage2DEXTProc )(GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void *bits);
typedef void (OSG_APIENTRY * osgGlCompressedMultiTexSubImage1DEXTProc )(GLenum texunit, GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void *bits);
typedef void (OSG_APIENTRY * osgGlGetCompressedMultiTexImageEXTProc )(GLenum texunit, GLenum target, GLint lod, void *img);
typedef void (OSG_APIENTRY * osgGlMatrixLoadTransposefEXTProc )(GLenum mode, const GLfloat *m);
typedef void (OSG_APIENTRY * osgGlMatrixLoadTransposedEXTProc )(GLenum mode, const GLdouble *m);
typedef void (OSG_APIENTRY * osgGlMatrixMultTransposefEXTProc )(GLenum mode, const GLfloat *m);
typedef void (OSG_APIENTRY * osgGlMatrixMultTransposedEXTProc )(GLenum mode, const GLdouble *m);
typedef void (OSG_APIENTRY * osgGlNamedBufferDataEXTProc )(GLuint buffer, GLsizeiptr size, const void *data, GLenum usage);
typedef void (OSG_APIENTRY * osgGlNamedBufferSubDataEXTProc )(GLuint buffer, GLintptr offset, GLsizeiptr size, const void *data);
typedef void *(OSG_APIENTRY * osgGlMapNamedBufferEXTProc )(GLuint buffer, GLenum access);
typedef GLboolean (OSG_APIENTRY * osgGlUnmapNamedBufferEXTProc )(GLuint buffer);
typedef void (OSG_APIENTRY * osgGlGetNamedBufferParameterivEXTProc )(GLuint buffer, GLenum pname, GLint *params);
typedef void (OSG_APIENTRY * osgGlGetNamedBufferPointervEXTProc )(GLuint buffer, GLenum pname, void **params);
typedef void (OSG_APIENTRY * osgGlGetNamedBufferSubDataEXTProc )(GLuint buffer, GLintptr offset, GLsizeiptr size, void *data);
typedef void (OSG_APIENTRY * osgGlProgramUniform1fEXTProc )(GLuint program, GLint location, GLfloat v0);
typedef void (OSG_APIENTRY * osgGlProgramUniform2fEXTProc )(GLuint program, GLint location, GLfloat v0, GLfloat v1);
typedef void (OSG_APIENTRY * osgGlProgramUniform3fEXTProc )(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
typedef void (OSG_APIENTRY * osgGlProgramUniform4fEXTProc )(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
typedef void (OSG_APIENTRY * osgGlProgramUniform1iEXTProc )(GLuint program, GLint location, GLint v0);
typedef void (OSG_APIENTRY * osgGlProgramUniform2iEXTProc )(GLuint program, GLint location, GLint v0, GLint v1);
typedef void (OSG_APIENTRY * osgGlProgramUniform3iEXTProc )(GLuint program, GLint location, GLint v0, GLint v1, GLint v2);
typedef void (OSG_APIENTRY * osgGlProgramUniform4iEXTProc )(GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
typedef void (OSG_APIENTRY * osgGlProgramUniform1fvEXTProc )(GLuint program, GLint location, GLsizei count, const GLfloat *value);
typedef void (OSG_APIENTRY * osgGlProgramUniform2fvEXTProc )(GLuint program, GLint location, GLsizei count, const GLfloat *value);
typedef void (OSG_APIENTRY * osgGlProgramUniform3fvEXTProc )(GLuint program, GLint location, GLsizei count, const GLfloat *value);
typedef void (OSG_APIENTRY * osgGlProgramUniform4fvEXTProc )(GLuint program, GLint location, GLsizei count, const GLfloat *value);
typedef void (OSG_APIENTRY * osgGlProgramUniform1ivEXTProc )(GLuint program, GLint location, GLsizei count, const GLint *value);
typedef void (OSG_APIENTRY * osgGlProgramUniform2ivEXTProc )(GLuint program, GLint location, GLsizei count, const GLint *value);
typedef void (OSG_APIENTRY * osgGlProgramUniform3ivEXTProc )(GLuint program, GLint location, GLsizei count, const GLint *value);
typedef void (OSG_APIENTRY * osgGlProgramUniform4ivEXTProc )(GLuint program, GLint location, GLsizei count, const GLint *value);
typedef void (OSG_APIENTRY * osgGlProgramUniformMatrix2fvEXTProc )(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (OSG_APIENTRY * osgGlProgramUniformMatrix3fvEXTProc )(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (OSG_APIENTRY * osgGlProgramUniformMatrix4fvEXTProc )(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (OSG_APIENTRY * osgGlProgramUniformMatrix2x3fvEXTProc )(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (OSG_APIENTRY * osgGlProgramUniformMatrix3x2fvEXTProc )(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (OSG_APIENTRY * osgGlProgramUniformMatrix2x4fvEXTProc )(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (OSG_APIENTRY * osgGlProgramUniformMatrix4x2fvEXTProc )(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (OSG_APIENTRY * osgGlProgramUniformMatrix3x4fvEXTProc )(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (OSG_APIENTRY * osgGlProgramUniformMatrix4x3fvEXTProc )(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (OSG_APIENTRY * osgGlTextureBufferEXTProc )(GLuint texture, GLenum target, GLenum internalformat, GLuint buffer);
typedef void (OSG_APIENTRY * osgGlMultiTexBufferEXTProc )(GLenum texunit, GLenum target, GLenum internalformat, GLuint buffer);
typedef void (OSG_APIENTRY * osgGlTextureParameterIivEXTProc )(GLuint texture, GLenum target, GLenum pname, const GLint *params);
typedef void (OSG_APIENTRY * osgGlTextureParameterIuivEXTProc )(GLuint texture, GLenum target, GLenum pname, const GLuint *params);
typedef void (OSG_APIENTRY * osgGlGetTextureParameterIivEXTProc )(GLuint texture, GLenum target, GLenum pname, GLint *params);
typedef void (OSG_APIENTRY * osgGlGetTextureParameterIuivEXTProc )(GLuint texture, GLenum target, GLenum pname, GLuint *params);
typedef void (OSG_APIENTRY * osgGlMultiTexParameterIivEXTProc )(GLenum texunit, GLenum target, GLenum pname, const GLint *params);
typedef void (OSG_APIENTRY * osgGlMultiTexParameterIuivEXTProc )(GLenum texunit, GLenum target, GLenum pname, const GLuint *params);
typedef void (OSG_APIENTRY * osgGlGetMultiTexParameterIivEXTProc )(GLenum texunit, GLenum target, GLenum pname, GLint *params);
typedef void (OSG_APIENTRY * osgGlGetMultiTexParameterIuivEXTProc )(GLenum texunit, GLenum target, GLenum pname, GLuint *params);
typedef void (OSG_APIENTRY * osgGlProgramUniform1uiEXTProc )(GLuint program, GLint location, GLuint v0);
typedef void (OSG_APIENTRY * osgGlProgramUniform2uiEXTProc )(GLuint program, GLint location, GLuint v0, GLuint v1);
typedef void (OSG_APIENTRY * osgGlProgramUniform3uiEXTProc )(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2);
typedef void (OSG_APIENTRY * osgGlProgramUniform4uiEXTProc )(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
typedef void (OSG_APIENTRY * osgGlProgramUniform1uivEXTProc )(GLuint program, GLint location, GLsizei count, const GLuint *value);
typedef void (OSG_APIENTRY * osgGlProgramUniform2uivEXTProc )(GLuint program, GLint location, GLsizei count, const GLuint *value);
typedef void (OSG_APIENTRY * osgGlProgramUniform3uivEXTProc )(GLuint program, GLint location, GLsizei count, const GLuint *value);
typedef void (OSG_APIENTRY * osgGlProgramUniform4uivEXTProc )(GLuint program, GLint location, GLsizei count, const GLuint *value);
typedef void (OSG_APIENTRY * osgGlNamedProgramLocalParameters4fvEXTProc )(GLuint program, GLenum target, GLuint index, GLsizei count, const GLfloat *params);
typedef void (OSG_APIENTRY * osgGlNamedProgramLocalParameterI4iEXTProc )(GLuint program, GLenum target, GLuint index, GLint x, GLint y, GLint z, GLint w);
typedef void (OSG_APIENTRY * osgGlNamedProgramLocalParameterI4ivEXTProc )(GLuint program, GLenum target, GLuint index, const GLint *params);
typedef void (OSG_APIENTRY * osgGlNamedProgramLocalParametersI4ivEXTProc )(GLuint program, GLenum target, GLuint index, GLsizei count, const GLint *params);
typedef void (OSG_APIENTRY * osgGlNamedProgramLocalParameterI4uiEXTProc )(GLuint program, GLenum target, GLuint index, GLuint x, GLuint y, GLuint z, GLuint w);
typedef void (OSG_APIENTRY * osgGlNamedProgramLocalParameterI4uivEXTProc )(GLuint program, GLenum target, GLuint index, const GLuint *params);
typedef void (OSG_APIENTRY * osgGlNamedProgramLocalParametersI4uivEXTProc )(GLuint program, GLenum target, GLuint index, GLsizei count, const GLuint *params);
typedef void (OSG_APIENTRY * osgGlGetNamedProgramLocalParameterIivEXTProc )(GLuint program, GLenum target, GLuint index, GLint *params);
typedef void (OSG_APIENTRY * osgGlGetNamedProgramLocalParameterIuivEXTProc )(GLuint program, GLenum target, GLuint index, GLuint *params);
typedef void (OSG_APIENTRY * osgGlEnableClientStateiEXTProc )(GLenum array, GLuint index);
typedef void (OSG_APIENTRY * osgGlDisableClientStateiEXTProc )(GLenum array, GLuint index);
typedef void (OSG_APIENTRY * osgGlGetFloati_vEXTProc )(GLenum pname, GLuint index, GLfloat *params);
typedef void (OSG_APIENTRY * osgGlGetDoublei_vEXTProc )(GLenum pname, GLuint index, GLdouble *params);
typedef void (OSG_APIENTRY * osgGlGetPointeri_vEXTProc )(GLenum pname, GLuint index, void **params);
typedef void (OSG_APIENTRY * osgGlNamedProgramStringEXTProc )(GLuint program, GLenum target, GLenum format, GLsizei len, const void *string);
typedef void (OSG_APIENTRY * osgGlNamedProgramLocalParameter4dEXTProc )(GLuint program, GLenum target, GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
typedef void (OSG_APIENTRY * osgGlNamedProgramLocalParameter4dvEXTProc )(GLuint program, GLenum target, GLuint index, const GLdouble *params);
typedef void (OSG_APIENTRY * osgGlNamedProgramLocalParameter4fEXTProc )(GLuint program, GLenum target, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
typedef void (OSG_APIENTRY * osgGlNamedProgramLocalParameter4fvEXTProc )(GLuint program, GLenum target, GLuint index, const GLfloat *params);
typedef void (OSG_APIENTRY * osgGlGetNamedProgramLocalParameterdvEXTProc )(GLuint program, GLenum target, GLuint index, GLdouble *params);
typedef void (OSG_APIENTRY * osgGlGetNamedProgramLocalParameterfvEXTProc )(GLuint program, GLenum target, GLuint index, GLfloat *params);
typedef void (OSG_APIENTRY * osgGlGetNamedProgramivEXTProc )(GLuint program, GLenum target, GLenum pname, GLint *params);
typedef void (OSG_APIENTRY * osgGlGetNamedProgramStringEXTProc )(GLuint program, GLenum target, GLenum pname, void *string);
typedef void (OSG_APIENTRY * osgGlNamedRenderbufferStorageEXTProc )(GLuint renderbuffer, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (OSG_APIENTRY * osgGlGetNamedRenderbufferParameterivEXTProc )(GLuint renderbuffer, GLenum pname, GLint *params);
typedef void (OSG_APIENTRY * osgGlNamedRenderbufferStorageMultisampleEXTProc )(GLuint renderbuffer, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (OSG_APIENTRY * osgGlNamedRenderbufferStorageMultisampleCoverageEXTProc )(GLuint renderbuffer, GLsizei coverageSamples, GLsizei colorSamples, GLenum internalformat, GLsizei width, GLsizei height);
typedef GLenum (OSG_APIENTRY * osgGlCheckNamedFramebufferStatusEXTProc )(GLuint framebuffer, GLenum target);
typedef void (OSG_APIENTRY * osgGlNamedFramebufferTexture1DEXTProc )(GLuint framebuffer, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
typedef void (OSG_APIENTRY * osgGlNamedFramebufferTexture2DEXTProc )(GLuint framebuffer, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
typedef void (OSG_APIENTRY * osgGlNamedFramebufferTexture3DEXTProc )(GLuint framebuffer, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset);
typedef void (OSG_APIENTRY * osgGlNamedFramebufferRenderbufferEXTProc )(GLuint framebuffer, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
typedef void (OSG_APIENTRY * osgGlGetNamedFramebufferAttachmentParameterivEXTProc )(GLuint framebuffer, GLenum attachment, GLenum pname, GLint *params);
typedef void (OSG_APIENTRY * osgGlGenerateTextureMipmapEXTProc )(GLuint texture, GLenum target);
typedef void (OSG_APIENTRY * osgGlGenerateMultiTexMipmapEXTProc )(GLenum texunit, GLenum target);
typedef void (OSG_APIENTRY * osgGlFramebufferDrawBufferEXTProc )(GLuint framebuffer, GLenum mode);
typedef void (OSG_APIENTRY * osgGlFramebufferDrawBuffersEXTProc )(GLuint framebuffer, GLsizei n, const GLenum *bufs);
typedef void (OSG_APIENTRY * osgGlFramebufferReadBufferEXTProc )(GLuint framebuffer, GLenum mode);
typedef void (OSG_APIENTRY * osgGlGetFramebufferParameterivEXTProc )(GLuint framebuffer, GLenum pname, GLint *params);
typedef void (OSG_APIENTRY * osgGlNamedCopyBufferSubDataEXTProc )(GLuint readBuffer, GLuint writeBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size);
typedef void (OSG_APIENTRY * osgGlNamedFramebufferTextureEXTProc )(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level);
typedef void (OSG_APIENTRY * osgGlNamedFramebufferTextureLayerEXTProc )(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, GLint layer);
typedef void (OSG_APIENTRY * osgGlNamedFramebufferTextureFaceEXTProc )(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, GLenum face);
typedef void (OSG_APIENTRY * osgGlTextureRenderbufferEXTProc )(GLuint texture, GLenum target, GLuint renderbuffer);
typedef void (OSG_APIENTRY * osgGlMultiTexRenderbufferEXTProc )(GLenum texunit, GLenum target, GLuint renderbuffer);
typedef void (OSG_APIENTRY * osgGlVertexArrayVertexOffsetEXTProc )(GLuint vaobj, GLuint buffer, GLint size, GLenum type, GLsizei stride, GLintptr offset);
typedef void (OSG_APIENTRY * osgGlVertexArrayColorOffsetEXTProc )(GLuint vaobj, GLuint buffer, GLint size, GLenum type, GLsizei stride, GLintptr offset);
typedef void (OSG_APIENTRY * osgGlVertexArrayEdgeFlagOffsetEXTProc )(GLuint vaobj, GLuint buffer, GLsizei stride, GLintptr offset);
typedef void (OSG_APIENTRY * osgGlVertexArrayIndexOffsetEXTProc )(GLuint vaobj, GLuint buffer, GLenum type, GLsizei stride, GLintptr offset);
typedef void (OSG_APIENTRY * osgGlVertexArrayNormalOffsetEXTProc )(GLuint vaobj, GLuint buffer, GLenum type, GLsizei stride, GLintptr offset);
typedef void (OSG_APIENTRY * osgGlVertexArrayTexCoordOffsetEXTProc )(GLuint vaobj, GLuint buffer, GLint size, GLenum type, GLsizei stride, GLintptr offset);
typedef void (OSG_APIENTRY * osgGlVertexArrayMultiTexCoordOffsetEXTProc )(GLuint vaobj, GLuint buffer, GLenum texunit, GLint size, GLenum type, GLsizei stride, GLintptr offset);
typedef void (OSG_APIENTRY * osgGlVertexArrayFogCoordOffsetEXTProc )(GLuint vaobj, GLuint buffer, GLenum type, GLsizei stride, GLintptr offset);
typedef void (OSG_APIENTRY * osgGlVertexArraySecondaryColorOffsetEXTProc )(GLuint vaobj, GLuint buffer, GLint size, GLenum type, GLsizei stride, GLintptr offset);
typedef void (OSG_APIENTRY * osgGlVertexArrayVertexAttribOffsetEXTProc )(GLuint vaobj, GLuint buffer, GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, GLintptr offset);
typedef void (OSG_APIENTRY * osgGlVertexArrayVertexAttribIOffsetEXTProc )(GLuint vaobj, GLuint buffer, GLuint index, GLint size, GLenum type, GLsizei stride, GLintptr offset);
typedef void (OSG_APIENTRY * osgGlEnableVertexArrayEXTProc )(GLuint vaobj, GLenum array);
typedef void (OSG_APIENTRY * osgGlDisableVertexArrayEXTProc )(GLuint vaobj, GLenum array);
typedef void (OSG_APIENTRY * osgGlEnableVertexArrayAttribEXTProc )(GLuint vaobj, GLuint index);
typedef void (OSG_APIENTRY * osgGlDisableVertexArrayAttribEXTProc )(GLuint vaobj, GLuint index);
typedef void (OSG_APIENTRY * osgGlGetVertexArrayIntegervEXTProc )(GLuint vaobj, GLenum pname, GLint *param);
typedef void (OSG_APIENTRY * osgGlGetVertexArrayPointervEXTProc )(GLuint vaobj, GLenum pname, void **param);
typedef void (OSG_APIENTRY * osgGlGetVertexArrayIntegeri_vEXTProc )(GLuint vaobj, GLuint index, GLenum pname, GLint *param);
typedef void (OSG_APIENTRY * osgGlGetVertexArrayPointeri_vEXTProc )(GLuint vaobj, GLuint index, GLenum pname, void **param);
typedef void *(OSG_APIENTRY * osgGlMapNamedBufferRangeEXTProc )(GLuint buffer, GLintptr offset, GLsizeiptr length, GLbitfield access);
typedef void (OSG_APIENTRY * osgGlFlushMappedNamedBufferRangeEXTProc )(GLuint buffer, GLintptr offset, GLsizeiptr length);
typedef void (OSG_APIENTRY * osgGlNamedBufferStorageEXTProc )(GLuint buffer, GLsizeiptr size, const void *data, GLbitfield flags);
typedef void (OSG_APIENTRY * osgGlClearNamedBufferDataEXTProc )(GLuint buffer, GLenum internalformat, GLenum format, GLenum type, const void *data);
typedef void (OSG_APIENTRY * osgGlClearNamedBufferSubDataEXTProc )(GLuint buffer, GLenum internalformat, GLsizeiptr offset, GLsizeiptr size, GLenum format, GLenum type, const void *data);
typedef void (OSG_APIENTRY * osgGlNamedFramebufferParameteriEXTProc )(GLuint framebuffer, GLenum pname, GLint param);
typedef void (OSG_APIENTRY * osgGlGetNamedFramebufferParameterivEXTProc )(GLuint framebuffer, GLenum pname, GLint *params);
typedef void (OSG_APIENTRY * osgGlProgramUniform1dEXTProc )(GLuint program, GLint location, GLdouble x);
typedef void (OSG_APIENTRY * osgGlProgramUniform2dEXTProc )(GLuint program, GLint location, GLdouble x, GLdouble y);
typedef void (OSG_APIENTRY * osgGlProgramUniform3dEXTProc )(GLuint program, GLint location, GLdouble x, GLdouble y, GLdouble z);
typedef void (OSG_APIENTRY * osgGlProgramUniform4dEXTProc )(GLuint program, GLint location, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
typedef void (OSG_APIENTRY * osgGlProgramUniform1dvEXTProc )(GLuint program, GLint location, GLsizei count, const GLdouble *value);
typedef void (OSG_APIENTRY * osgGlProgramUniform2dvEXTProc )(GLuint program, GLint location, GLsizei count, const GLdouble *value);
typedef void (OSG_APIENTRY * osgGlProgramUniform3dvEXTProc )(GLuint program, GLint location, GLsizei count, const GLdouble *value);
typedef void (OSG_APIENTRY * osgGlProgramUniform4dvEXTProc )(GLuint program, GLint location, GLsizei count, const GLdouble *value);
typedef void (OSG_APIENTRY * osgGlProgramUniformMatrix2dvEXTProc )(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (OSG_APIENTRY * osgGlProgramUniformMatrix3dvEXTProc )(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (OSG_APIENTRY * osgGlProgramUniformMatrix4dvEXTProc )(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (OSG_APIENTRY * osgGlProgramUniformMatrix2x3dvEXTProc )(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (OSG_APIENTRY * osgGlProgramUniformMatrix2x4dvEXTProc )(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (OSG_APIENTRY * osgGlProgramUniformMatrix3x2dvEXTProc )(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (OSG_APIENTRY * osgGlProgramUniformMatrix3x4dvEXTProc )(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (OSG_APIENTRY * osgGlProgramUniformMatrix4x2dvEXTProc )(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (OSG_APIENTRY * osgGlProgramUniformMatrix4x3dvEXTProc )(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (OSG_APIENTRY * osgGlTextureBufferRangeEXTProc )(GLuint texture, GLenum target, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size);
typedef void (OSG_APIENTRY * osgGlTextureStorage1DEXTProc )(GLuint texture, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width);
typedef void (OSG_APIENTRY * osgGlTextureStorage2DEXTProc )(GLuint texture, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (OSG_APIENTRY * osgGlTextureStorage3DEXTProc )(GLuint texture, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth);
typedef void (OSG_APIENTRY * osgGlTextureStorage2DMultisampleEXTProc )(GLuint texture, GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
typedef void (OSG_APIENTRY * osgGlTextureStorage3DMultisampleEXTProc )(GLuint texture, GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations);
typedef void (OSG_APIENTRY * osgGlVertexArrayBindVertexBufferEXTProc )(GLuint vaobj, GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride);
typedef void (OSG_APIENTRY * osgGlVertexArrayVertexAttribFormatEXTProc )(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset);
typedef void (OSG_APIENTRY * osgGlVertexArrayVertexAttribIFormatEXTProc )(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset);
typedef void (OSG_APIENTRY * osgGlVertexArrayVertexAttribLFormatEXTProc )(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset);
typedef void (OSG_APIENTRY * osgGlVertexArrayVertexAttribBindingEXTProc )(GLuint vaobj, GLuint attribindex, GLuint bindingindex);
typedef void (OSG_APIENTRY * osgGlVertexArrayVertexBindingDivisorEXTProc )(GLuint vaobj, GLuint bindingindex, GLuint divisor);
typedef void (OSG_APIENTRY * osgGlVertexArrayVertexAttribLOffsetEXTProc )(GLuint vaobj, GLuint buffer, GLuint index, GLint size, GLenum type, GLsizei stride, GLintptr offset);
typedef void (OSG_APIENTRY * osgGlTexturePageCommitmentEXTProc )(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLboolean commit);
typedef void (OSG_APIENTRY * osgGlVertexArrayVertexAttribDivisorEXTProc )(GLuint vaobj, GLuint index, GLuint divisor);
#endif /* GL_EXT_direct_state_access */

#ifdef GL_EXT_draw_buffers2
typedef void (OSG_APIENTRY * osgGlColorMaskIndexedEXTProc )(GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a);
#endif /* GL_EXT_draw_buffers2 */

#ifdef GL_EXT_draw_instanced
typedef void (OSG_APIENTRY * osgGlDrawArraysInstancedEXTProc )(GLenum mode, GLint start, GLsizei count, GLsizei primcount);
typedef void (OSG_APIENTRY * osgGlDrawElementsInstancedEXTProc )(GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei primcount);
#endif /* GL_EXT_draw_instanced */

#ifdef GL_EXT_draw_range_elements
typedef void (OSG_APIENTRY * osgGlDrawRangeElementsEXTProc )(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void *indices);
#endif /* GL_EXT_draw_range_elements */

#ifdef GL_EXT_fog_coord
typedef void (OSG_APIENTRY * osgGlFogCoordfEXTProc )(GLfloat coord);
typedef void (OSG_APIENTRY * osgGlFogCoordfvEXTProc )(const GLfloat *coord);
typedef void (OSG_APIENTRY * osgGlFogCoorddEXTProc )(GLdouble coord);
typedef void (OSG_APIENTRY * osgGlFogCoorddvEXTProc )(const GLdouble *coord);
typedef void (OSG_APIENTRY * osgGlFogCoordPointerEXTProc )(GLenum type, GLsizei stride, const void *pointer);
#endif /* GL_EXT_fog_coord */

#ifdef GL_EXT_framebuffer_blit
typedef void (OSG_APIENTRY * osgGlBlitFramebufferEXTProc )(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);
#endif /* GL_EXT_framebuffer_blit */

#ifdef GL_EXT_framebuffer_multisample
typedef void (OSG_APIENTRY * osgGlRenderbufferStorageMultisampleEXTProc )(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
#endif /* GL_EXT_framebuffer_multisample */

#ifdef GL_EXT_framebuffer_multisample_blit_scaled
#endif /* GL_EXT_framebuffer_multisample_blit_scaled */

#ifdef GL_EXT_framebuffer_object
typedef GLboolean (OSG_APIENTRY * osgGlIsRenderbufferEXTProc )(GLuint renderbuffer);
typedef void (OSG_APIENTRY * osgGlBindRenderbufferEXTProc )(GLenum target, GLuint renderbuffer);
typedef void (OSG_APIENTRY * osgGlDeleteRenderbuffersEXTProc )(GLsizei n, const GLuint *renderbuffers);
typedef void (OSG_APIENTRY * osgGlGenRenderbuffersEXTProc )(GLsizei n, GLuint *renderbuffers);
typedef void (OSG_APIENTRY * osgGlRenderbufferStorageEXTProc )(GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (OSG_APIENTRY * osgGlGetRenderbufferParameterivEXTProc )(GLenum target, GLenum pname, GLint *params);
typedef GLboolean (OSG_APIENTRY * osgGlIsFramebufferEXTProc )(GLuint framebuffer);
typedef void (OSG_APIENTRY * osgGlBindFramebufferEXTProc )(GLenum target, GLuint framebuffer);
typedef void (OSG_APIENTRY * osgGlDeleteFramebuffersEXTProc )(GLsizei n, const GLuint *framebuffers);
typedef void (OSG_APIENTRY * osgGlGenFramebuffersEXTProc )(GLsizei n, GLuint *framebuffers);
typedef GLenum (OSG_APIENTRY * osgGlCheckFramebufferStatusEXTProc )(GLenum target);
typedef void (OSG_APIENTRY * osgGlFramebufferTexture1DEXTProc )(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
typedef void (OSG_APIENTRY * osgGlFramebufferTexture2DEXTProc )(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
typedef void (OSG_APIENTRY * osgGlFramebufferTexture3DEXTProc )(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset);
typedef void (OSG_APIENTRY * osgGlFramebufferRenderbufferEXTProc )(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
typedef void (OSG_APIENTRY * osgGlGetFramebufferAttachmentParameterivEXTProc )(GLenum target, GLenum attachment, GLenum pname, GLint *params);
typedef void (OSG_APIENTRY * osgGlGenerateMipmapEXTProc )(GLenum target);
#endif /* GL_EXT_framebuffer_object */

#ifdef GL_EXT_framebuffer_sRGB
#endif /* GL_EXT_framebuffer_sRGB */

#ifdef GL_EXT_geometry_shader4
typedef void (OSG_APIENTRY * osgGlProgramParameteriEXTProc )(GLuint program, GLenum pname, GLint value);
#endif /* GL_EXT_geometry_shader4 */

#ifdef GL_EXT_gpu_program_parameters
typedef void (OSG_APIENTRY * osgGlProgramEnvParameters4fvEXTProc )(GLenum target, GLuint index, GLsizei count, const GLfloat *params);
typedef void (OSG_APIENTRY * osgGlProgramLocalParameters4fvEXTProc )(GLenum target, GLuint index, GLsizei count, const GLfloat *params);
#endif /* GL_EXT_gpu_program_parameters */

#ifdef GL_EXT_gpu_shader4
typedef void (OSG_APIENTRY * osgGlGetUniformuivEXTProc )(GLuint program, GLint location, GLuint *params);
typedef void (OSG_APIENTRY * osgGlBindFragDataLocationEXTProc )(GLuint program, GLuint color, const GLchar *name);
typedef GLint (OSG_APIENTRY * osgGlGetFragDataLocationEXTProc )(GLuint program, const GLchar *name);
typedef void (OSG_APIENTRY * osgGlUniform1uiEXTProc )(GLint location, GLuint v0);
typedef void (OSG_APIENTRY * osgGlUniform2uiEXTProc )(GLint location, GLuint v0, GLuint v1);
typedef void (OSG_APIENTRY * osgGlUniform3uiEXTProc )(GLint location, GLuint v0, GLuint v1, GLuint v2);
typedef void (OSG_APIENTRY * osgGlUniform4uiEXTProc )(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
typedef void (OSG_APIENTRY * osgGlUniform1uivEXTProc )(GLint location, GLsizei count, const GLuint *value);
typedef void (OSG_APIENTRY * osgGlUniform2uivEXTProc )(GLint location, GLsizei count, const GLuint *value);
typedef void (OSG_APIENTRY * osgGlUniform3uivEXTProc )(GLint location, GLsizei count, const GLuint *value);
typedef void (OSG_APIENTRY * osgGlUniform4uivEXTProc )(GLint location, GLsizei count, const GLuint *value);
#endif /* GL_EXT_gpu_shader4 */

#ifdef GL_EXT_histogram
typedef void (OSG_APIENTRY * osgGlGetHistogramEXTProc )(GLenum target, GLboolean reset, GLenum format, GLenum type, void *values);
typedef void (OSG_APIENTRY * osgGlGetHistogramParameterfvEXTProc )(GLenum target, GLenum pname, GLfloat *params);
typedef void (OSG_APIENTRY * osgGlGetHistogramParameterivEXTProc )(GLenum target, GLenum pname, GLint *params);
typedef void (OSG_APIENTRY * osgGlGetMinmaxEXTProc )(GLenum target, GLboolean reset, GLenum format, GLenum type, void *values);
typedef void (OSG_APIENTRY * osgGlGetMinmaxParameterfvEXTProc )(GLenum target, GLenum pname, GLfloat *params);
typedef void (OSG_APIENTRY * osgGlGetMinmaxParameterivEXTProc )(GLenum target, GLenum pname, GLint *params);
typedef void (OSG_APIENTRY * osgGlHistogramEXTProc )(GLenum target, GLsizei width, GLenum internalformat, GLboolean sink);
typedef void (OSG_APIENTRY * osgGlMinmaxEXTProc )(GLenum target, GLenum internalformat, GLboolean sink);
typedef void (OSG_APIENTRY * osgGlResetHistogramEXTProc )(GLenum target);
typedef void (OSG_APIENTRY * osgGlResetMinmaxEXTProc )(GLenum target);
#endif /* GL_EXT_histogram */

#ifdef GL_EXT_index_array_formats
#endif /* GL_EXT_index_array_formats */

#ifdef GL_EXT_index_func
typedef void (OSG_APIENTRY * osgGlIndexFuncEXTProc )(GLenum func, GLclampf ref);
#endif /* GL_EXT_index_func */

#ifdef GL_EXT_index_material
typedef void (OSG_APIENTRY * osgGlIndexMaterialEXTProc )(GLenum face, GLenum mode);
#endif /* GL_EXT_index_material */

#ifdef GL_EXT_index_texture
#endif /* GL_EXT_index_texture */

#ifdef GL_EXT_light_texture
typedef void (OSG_APIENTRY * osgGlApplyTextureEXTProc )(GLenum mode);
typedef void (OSG_APIENTRY * osgGlTextureLightEXTProc )(GLenum pname);
typedef void (OSG_APIENTRY * osgGlTextureMaterialEXTProc )(GLenum face, GLenum mode);
#endif /* GL_EXT_light_texture */

#ifdef GL_EXT_misc_attribute
#endif /* GL_EXT_misc_attribute */

#ifdef GL_EXT_multi_draw_arrays
typedef void (OSG_APIENTRY * osgGlMultiDrawArraysEXTProc )(GLenum mode, const GLint *first, const GLsizei *count, GLsizei primcount);
typedef void (OSG_APIENTRY * osgGlMultiDrawElementsEXTProc )(GLenum mode, const GLsizei *count, GLenum type, const void *const*indices, GLsizei primcount);
#endif /* GL_EXT_multi_draw_arrays */

#ifdef GL_EXT_multisample
typedef void (OSG_APIENTRY * osgGlSampleMaskEXTProc )(GLclampf value, GLboolean invert);
typedef void (OSG_APIENTRY * osgGlSamplePatternEXTProc )(GLenum pattern);
#endif /* GL_EXT_multisample */

#ifdef GL_EXT_packed_depth_stencil
#endif /* GL_EXT_packed_depth_stencil */

#ifdef GL_EXT_packed_float
#endif /* GL_EXT_packed_float */

#ifdef GL_EXT_packed_pixels
#endif /* GL_EXT_packed_pixels */

#ifdef GL_EXT_paletted_texture
typedef void (OSG_APIENTRY * osgGlColorTableEXTProc )(GLenum target, GLenum internalFormat, GLsizei width, GLenum format, GLenum type, const void *table);
typedef void (OSG_APIENTRY * osgGlGetColorTableEXTProc )(GLenum target, GLenum format, GLenum type, void *data);
typedef void (OSG_APIENTRY * osgGlGetColorTableParameterivEXTProc )(GLenum target, GLenum pname, GLint *params);
typedef void (OSG_APIENTRY * osgGlGetColorTableParameterfvEXTProc )(GLenum target, GLenum pname, GLfloat *params);
#endif /* GL_EXT_paletted_texture */

#ifdef GL_EXT_pixel_buffer_object
#endif /* GL_EXT_pixel_buffer_object */

#ifdef GL_EXT_pixel_transform
typedef void (OSG_APIENTRY * osgGlPixelTransformParameteriEXTProc )(GLenum target, GLenum pname, GLint param);
typedef void (OSG_APIENTRY * osgGlPixelTransformParameterfEXTProc )(GLenum target, GLenum pname, GLfloat param);
typedef void (OSG_APIENTRY * osgGlPixelTransformParameterivEXTProc )(GLenum target, GLenum pname, const GLint *params);
typedef void (OSG_APIENTRY * osgGlPixelTransformParameterfvEXTProc )(GLenum target, GLenum pname, const GLfloat *params);
typedef void (OSG_APIENTRY * osgGlGetPixelTransformParameterivEXTProc )(GLenum target, GLenum pname, GLint *params);
typedef void (OSG_APIENTRY * osgGlGetPixelTransformParameterfvEXTProc )(GLenum target, GLenum pname, GLfloat *params);
#endif /* GL_EXT_pixel_transform */

#ifdef GL_EXT_pixel_transform_color_table
#endif /* GL_EXT_pixel_transform_color_table */

#ifdef GL_EXT_point_parameters
typedef void (OSG_APIENTRY * osgGlPointParameterfEXTProc )(GLenum pname, GLfloat param);
typedef void (OSG_APIENTRY * osgGlPointParameterfvEXTProc )(GLenum pname, const GLfloat *params);
#endif /* GL_EXT_point_parameters */

#ifdef GL_EXT_polygon_offset
typedef void (OSG_APIENTRY * osgGlPolygonOffsetEXTProc )(GLfloat factor, GLfloat bias);
#endif /* GL_EXT_polygon_offset */

#ifdef GL_EXT_polygon_offset_clamp
typedef void (OSG_APIENTRY * osgGlPolygonOffsetClampEXTProc )(GLfloat factor, GLfloat units, GLfloat clamp);
#endif /* GL_EXT_polygon_offset_clamp */

#ifdef GL_EXT_post_depth_coverage
#endif /* GL_EXT_post_depth_coverage */

#ifdef GL_EXT_provoking_vertex
typedef void (OSG_APIENTRY * osgGlProvokingVertexEXTProc )(GLenum mode);
#endif /* GL_EXT_provoking_vertex */

#ifdef GL_EXT_raster_multisample
typedef void (OSG_APIENTRY * osgGlRasterSamplesEXTProc )(GLuint samples, GLboolean fixedsamplelocations);
#endif /* GL_EXT_raster_multisample */

#ifdef GL_EXT_rescale_normal
#endif /* GL_EXT_rescale_normal */

#ifdef GL_EXT_secondary_color
typedef void (OSG_APIENTRY * osgGlSecondaryColor3bEXTProc )(GLbyte red, GLbyte green, GLbyte blue);
typedef void (OSG_APIENTRY * osgGlSecondaryColor3bvEXTProc )(const GLbyte *v);
typedef void (OSG_APIENTRY * osgGlSecondaryColor3dEXTProc )(GLdouble red, GLdouble green, GLdouble blue);
typedef void (OSG_APIENTRY * osgGlSecondaryColor3dvEXTProc )(const GLdouble *v);
typedef void (OSG_APIENTRY * osgGlSecondaryColor3fEXTProc )(GLfloat red, GLfloat green, GLfloat blue);
typedef void (OSG_APIENTRY * osgGlSecondaryColor3fvEXTProc )(const GLfloat *v);
typedef void (OSG_APIENTRY * osgGlSecondaryColor3iEXTProc )(GLint red, GLint green, GLint blue);
typedef void (OSG_APIENTRY * osgGlSecondaryColor3ivEXTProc )(const GLint *v);
typedef void (OSG_APIENTRY * osgGlSecondaryColor3sEXTProc )(GLshort red, GLshort green, GLshort blue);
typedef void (OSG_APIENTRY * osgGlSecondaryColor3svEXTProc )(const GLshort *v);
typedef void (OSG_APIENTRY * osgGlSecondaryColor3ubEXTProc )(GLubyte red, GLubyte green, GLubyte blue);
typedef void (OSG_APIENTRY * osgGlSecondaryColor3ubvEXTProc )(const GLubyte *v);
typedef void (OSG_APIENTRY * osgGlSecondaryColor3uiEXTProc )(GLuint red, GLuint green, GLuint blue);
typedef void (OSG_APIENTRY * osgGlSecondaryColor3uivEXTProc )(const GLuint *v);
typedef void (OSG_APIENTRY * osgGlSecondaryColor3usEXTProc )(GLushort red, GLushort green, GLushort blue);
typedef void (OSG_APIENTRY * osgGlSecondaryColor3usvEXTProc )(const GLushort *v);
typedef void (OSG_APIENTRY * osgGlSecondaryColorPointerEXTProc )(GLint size, GLenum type, GLsizei stride, const void *pointer);
#endif /* GL_EXT_secondary_color */

#ifdef GL_EXT_separate_shader_objects
typedef void (OSG_APIENTRY * osgGlUseShaderProgramEXTProc )(GLenum type, GLuint program);
typedef void (OSG_APIENTRY * osgGlActiveProgramEXTProc )(GLuint program);
typedef GLuint (OSG_APIENTRY * osgGlCreateShaderProgramEXTProc )(GLenum type, const GLchar *string);
#endif /* GL_EXT_separate_shader_objects */

#ifdef GL_EXT_separate_specular_color
#endif /* GL_EXT_separate_specular_color */

#ifdef GL_EXT_shader_image_load_formatted
#endif /* GL_EXT_shader_image_load_formatted */

#ifdef GL_EXT_shader_image_load_store
typedef void (OSG_APIENTRY * osgGlBindImageTextureEXTProc )(GLuint index, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLint format);
typedef void (OSG_APIENTRY * osgGlMemoryBarrierEXTProc )(GLbitfield barriers);
#endif /* GL_EXT_shader_image_load_store */

#ifdef GL_EXT_shader_integer_mix
#endif /* GL_EXT_shader_integer_mix */

#ifdef GL_EXT_shadow_funcs
#endif /* GL_EXT_shadow_funcs */

#ifdef GL_EXT_shared_texture_palette
#endif /* GL_EXT_shared_texture_palette */

#ifdef GL_EXT_sparse_texture2
#endif /* GL_EXT_sparse_texture2 */

#ifdef GL_EXT_stencil_clear_tag
typedef void (OSG_APIENTRY * osgGlStencilClearTagEXTProc )(GLsizei stencilTagBits, GLuint stencilClearTag);
#endif /* GL_EXT_stencil_clear_tag */

#ifdef GL_EXT_stencil_two_side
typedef void (OSG_APIENTRY * osgGlActiveStencilFaceEXTProc )(GLenum face);
#endif /* GL_EXT_stencil_two_side */

#ifdef GL_EXT_stencil_wrap
#endif /* GL_EXT_stencil_wrap */

#ifdef GL_EXT_subtexture
typedef void (OSG_APIENTRY * osgGlTexSubImage1DEXTProc )(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void *pixels);
typedef void (OSG_APIENTRY * osgGlTexSubImage2DEXTProc )(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void *pixels);
#endif /* GL_EXT_subtexture */

#ifdef GL_EXT_texture
#endif /* GL_EXT_texture */

#ifdef GL_EXT_texture3D
typedef void (OSG_APIENTRY * osgGlTexImage3DEXTProc )(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void *pixels);
typedef void (OSG_APIENTRY * osgGlTexSubImage3DEXTProc )(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *pixels);
#endif /* GL_EXT_texture3D */

#ifdef GL_EXT_texture_array
typedef void (OSG_APIENTRY * osgGlFramebufferTextureLayerEXTProc )(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer);
#endif /* GL_EXT_texture_array */

#ifdef GL_EXT_texture_buffer_object
typedef void (OSG_APIENTRY * PFNGLTEXBUFFEREXTPROC) (GLenum target, GLenum internalformat, GLuint buffer);
#endif /* GL_EXT_texture_buffer_object */

#ifdef GL_EXT_texture_compression_latc
#endif /* GL_EXT_texture_compression_latc */

#ifdef GL_EXT_texture_compression_rgtc
#endif /* GL_EXT_texture_compression_rgtc */

#ifdef GL_EXT_texture_compression_s3tc
#endif /* GL_EXT_texture_compression_s3tc */

#ifdef GL_EXT_texture_cube_map
#endif /* GL_EXT_texture_cube_map */

#ifdef GL_EXT_texture_env_add
#endif /* GL_EXT_texture_env_add */

#ifdef GL_EXT_texture_env_combine
#endif /* GL_EXT_texture_env_combine */

#ifdef GL_EXT_texture_env_dot3
#endif /* GL_EXT_texture_env_dot3 */

#ifdef GL_EXT_texture_filter_anisotropic
#endif /* GL_EXT_texture_filter_anisotropic */

#ifdef GL_EXT_texture_filter_minmax
#endif /* GL_EXT_texture_filter_minmax */

#ifdef GL_EXT_texture_integer
typedef void (OSG_APIENTRY * osgGlTexParameterIivEXTProc )(GLenum target, GLenum pname, const GLint *params);
typedef void (OSG_APIENTRY * osgGlTexParameterIuivEXTProc )(GLenum target, GLenum pname, const GLuint *params);
typedef void (OSG_APIENTRY * osgGlGetTexParameterIivEXTProc )(GLenum target, GLenum pname, GLint *params);
typedef void (OSG_APIENTRY * osgGlGetTexParameterIuivEXTProc )(GLenum target, GLenum pname, GLuint *params);
typedef void (OSG_APIENTRY * osgGlClearColorIiEXTProc )(GLint red, GLint green, GLint blue, GLint alpha);
typedef void (OSG_APIENTRY * osgGlClearColorIuiEXTProc )(GLuint red, GLuint green, GLuint blue, GLuint alpha);
#endif /* GL_EXT_texture_integer */

#ifdef GL_EXT_texture_lod_bias
#endif /* GL_EXT_texture_lod_bias */

#ifdef GL_EXT_texture_mirror_clamp
#endif /* GL_EXT_texture_mirror_clamp */

#ifdef GL_EXT_texture_object
typedef GLboolean (OSG_APIENTRY * osgGlAreTexturesResidentEXTProc )(GLsizei n, const GLuint *textures, GLboolean *residences);
typedef void (OSG_APIENTRY * osgGlBindTextureEXTProc )(GLenum target, GLuint texture);
typedef void (OSG_APIENTRY * osgGlDeleteTexturesEXTProc )(GLsizei n, const GLuint *textures);
typedef void (OSG_APIENTRY * osgGlGenTexturesEXTProc )(GLsizei n, GLuint *textures);
typedef GLboolean (OSG_APIENTRY * osgGlIsTextureEXTProc )(GLuint texture);
typedef void (OSG_APIENTRY * osgGlPrioritizeTexturesEXTProc )(GLsizei n, const GLuint *textures, const GLclampf *priorities);
#endif /* GL_EXT_texture_object */

#ifdef GL_EXT_texture_perturb_normal
typedef void (OSG_APIENTRY * osgGlTextureNormalEXTProc )(GLenum mode);
#endif /* GL_EXT_texture_perturb_normal */

#ifdef GL_EXT_texture_sRGB
#endif /* GL_EXT_texture_sRGB */

#ifdef GL_EXT_texture_sRGB_decode
#endif /* GL_EXT_texture_sRGB_decode */

#ifdef GL_EXT_texture_shared_exponent
#endif /* GL_EXT_texture_shared_exponent */

#ifdef GL_EXT_texture_snorm
#endif /* GL_EXT_texture_snorm */

#ifdef GL_EXT_texture_swizzle
#endif /* GL_EXT_texture_swizzle */

#ifdef GL_EXT_timer_query
typedef void (OSG_APIENTRY * osgGlGetQueryObjecti64vEXTProc )(GLuint id, GLenum pname, GLint64 *params);
typedef void (OSG_APIENTRY * osgGlGetQueryObjectui64vEXTProc )(GLuint id, GLenum pname, GLuint64 *params);
#endif /* GL_EXT_timer_query */

#ifdef GL_EXT_transform_feedback
typedef void (OSG_APIENTRY * osgGlBeginTransformFeedbackEXTProc )(GLenum primitiveMode);
typedef void (OSG_APIENTRY * osgGlEndTransformFeedbackEXTProc )(void);
typedef void (OSG_APIENTRY * osgGlBindBufferRangeEXTProc )(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size);
typedef void (OSG_APIENTRY * osgGlBindBufferOffsetEXTProc )(GLenum target, GLuint index, GLuint buffer, GLintptr offset);
typedef void (OSG_APIENTRY * osgGlBindBufferBaseEXTProc )(GLenum target, GLuint index, GLuint buffer);
typedef void (OSG_APIENTRY * osgGlTransformFeedbackVaryingsEXTProc )(GLuint program, GLsizei count, const GLchar *const*varyings, GLenum bufferMode);
typedef void (OSG_APIENTRY * osgGlGetTransformFeedbackVaryingEXTProc )(GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLsizei *size, GLenum *type, GLchar *name);
#endif /* GL_EXT_transform_feedback */

#ifdef GL_EXT_vertex_array
typedef void (OSG_APIENTRY * osgGlArrayElementEXTProc )(GLint i);
typedef void (OSG_APIENTRY * osgGlColorPointerEXTProc )(GLint size, GLenum type, GLsizei stride, GLsizei count, const void *pointer);
typedef void (OSG_APIENTRY * osgGlDrawArraysEXTProc )(GLenum mode, GLint first, GLsizei count);
typedef void (OSG_APIENTRY * osgGlEdgeFlagPointerEXTProc )(GLsizei stride, GLsizei count, const GLboolean *pointer);
typedef void (OSG_APIENTRY * osgGlGetPointervEXTProc )(GLenum pname, void **params);
typedef void (OSG_APIENTRY * osgGlIndexPointerEXTProc )(GLenum type, GLsizei stride, GLsizei count, const void *pointer);
typedef void (OSG_APIENTRY * osgGlNormalPointerEXTProc )(GLenum type, GLsizei stride, GLsizei count, const void *pointer);
typedef void (OSG_APIENTRY * osgGlTexCoordPointerEXTProc )(GLint size, GLenum type, GLsizei stride, GLsizei count, const void *pointer);
typedef void (OSG_APIENTRY * osgGlVertexPointerEXTProc )(GLint size, GLenum type, GLsizei stride, GLsizei count, const void *pointer);
#endif /* GL_EXT_vertex_array */

#ifdef GL_EXT_vertex_array_bgra
#endif /* GL_EXT_vertex_array_bgra */

#ifdef GL_EXT_vertex_attrib_64bit
typedef void (OSG_APIENTRY * osgGlVertexAttribL1dEXTProc )(GLuint index, GLdouble x);
typedef void (OSG_APIENTRY * osgGlVertexAttribL2dEXTProc )(GLuint index, GLdouble x, GLdouble y);
typedef void (OSG_APIENTRY * osgGlVertexAttribL3dEXTProc )(GLuint index, GLdouble x, GLdouble y, GLdouble z);
typedef void (OSG_APIENTRY * osgGlVertexAttribL4dEXTProc )(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
typedef void (OSG_APIENTRY * osgGlVertexAttribL1dvEXTProc )(GLuint index, const GLdouble *v);
typedef void (OSG_APIENTRY * osgGlVertexAttribL2dvEXTProc )(GLuint index, const GLdouble *v);
typedef void (OSG_APIENTRY * osgGlVertexAttribL3dvEXTProc )(GLuint index, const GLdouble *v);
typedef void (OSG_APIENTRY * osgGlVertexAttribL4dvEXTProc )(GLuint index, const GLdouble *v);
typedef void (OSG_APIENTRY * osgGlVertexAttribLPointerEXTProc )(GLuint index, GLint size, GLenum type, GLsizei stride, const void *pointer);
typedef void (OSG_APIENTRY * osgGlGetVertexAttribLdvEXTProc )(GLuint index, GLenum pname, GLdouble *params);
#endif /* GL_EXT_vertex_attrib_64bit */

#ifdef GL_EXT_vertex_shader
typedef void (OSG_APIENTRY * osgGlBeginVertexShaderEXTProc )(void);
typedef void (OSG_APIENTRY * osgGlEndVertexShaderEXTProc )(void);
typedef void (OSG_APIENTRY * osgGlBindVertexShaderEXTProc )(GLuint id);
typedef GLuint (OSG_APIENTRY * osgGlGenVertexShadersEXTProc )(GLuint range);
typedef void (OSG_APIENTRY * osgGlDeleteVertexShaderEXTProc )(GLuint id);
typedef void (OSG_APIENTRY * osgGlShaderOp1EXTProc )(GLenum op, GLuint res, GLuint arg1);
typedef void (OSG_APIENTRY * osgGlShaderOp2EXTProc )(GLenum op, GLuint res, GLuint arg1, GLuint arg2);
typedef void (OSG_APIENTRY * osgGlShaderOp3EXTProc )(GLenum op, GLuint res, GLuint arg1, GLuint arg2, GLuint arg3);
typedef void (OSG_APIENTRY * osgGlSwizzleEXTProc )(GLuint res, GLuint in, GLenum outX, GLenum outY, GLenum outZ, GLenum outW);
typedef void (OSG_APIENTRY * osgGlWriteMaskEXTProc )(GLuint res, GLuint in, GLenum outX, GLenum outY, GLenum outZ, GLenum outW);
typedef void (OSG_APIENTRY * osgGlInsertComponentEXTProc )(GLuint res, GLuint src, GLuint num);
typedef void (OSG_APIENTRY * osgGlExtractComponentEXTProc )(GLuint res, GLuint src, GLuint num);
typedef GLuint (OSG_APIENTRY * osgGlGenSymbolsEXTProc )(GLenum datatype, GLenum storagetype, GLenum range, GLuint components);
typedef void (OSG_APIENTRY * osgGlSetInvariantEXTProc )(GLuint id, GLenum type, const void *addr);
typedef void (OSG_APIENTRY * osgGlSetLocalConstantEXTProc )(GLuint id, GLenum type, const void *addr);
typedef void (OSG_APIENTRY * osgGlVariantbvEXTProc )(GLuint id, const GLbyte *addr);
typedef void (OSG_APIENTRY * osgGlVariantsvEXTProc )(GLuint id, const GLshort *addr);
typedef void (OSG_APIENTRY * osgGlVariantivEXTProc )(GLuint id, const GLint *addr);
typedef void (OSG_APIENTRY * osgGlVariantfvEXTProc )(GLuint id, const GLfloat *addr);
typedef void (OSG_APIENTRY * osgGlVariantdvEXTProc )(GLuint id, const GLdouble *addr);
typedef void (OSG_APIENTRY * osgGlVariantubvEXTProc )(GLuint id, const GLubyte *addr);
typedef void (OSG_APIENTRY * osgGlVariantusvEXTProc )(GLuint id, const GLushort *addr);
typedef void (OSG_APIENTRY * osgGlVariantuivEXTProc )(GLuint id, const GLuint *addr);
typedef void (OSG_APIENTRY * osgGlVariantPointerEXTProc )(GLuint id, GLenum type, GLuint stride, const void *addr);
typedef void (OSG_APIENTRY * osgGlEnableVariantClientStateEXTProc )(GLuint id);
typedef void (OSG_APIENTRY * osgGlDisableVariantClientStateEXTProc )(GLuint id);
typedef GLuint (OSG_APIENTRY * osgGlBindLightParameterEXTProc )(GLenum light, GLenum value);
typedef GLuint (OSG_APIENTRY * osgGlBindMaterialParameterEXTProc )(GLenum face, GLenum value);
typedef GLuint (OSG_APIENTRY * osgGlBindTexGenParameterEXTProc )(GLenum unit, GLenum coord, GLenum value);
typedef GLuint (OSG_APIENTRY * osgGlBindTextureUnitParameterEXTProc )(GLenum unit, GLenum value);
typedef GLuint (OSG_APIENTRY * osgGlBindParameterEXTProc )(GLenum value);
typedef GLboolean (OSG_APIENTRY * osgGlIsVariantEnabledEXTProc )(GLuint id, GLenum cap);
typedef void (OSG_APIENTRY * osgGlGetVariantBooleanvEXTProc )(GLuint id, GLenum value, GLboolean *data);
typedef void (OSG_APIENTRY * osgGlGetVariantIntegervEXTProc )(GLuint id, GLenum value, GLint *data);
typedef void (OSG_APIENTRY * osgGlGetVariantFloatvEXTProc )(GLuint id, GLenum value, GLfloat *data);
typedef void (OSG_APIENTRY * osgGlGetVariantPointervEXTProc )(GLuint id, GLenum value, void **data);
typedef void (OSG_APIENTRY * osgGlGetInvariantBooleanvEXTProc )(GLuint id, GLenum value, GLboolean *data);
typedef void (OSG_APIENTRY * osgGlGetInvariantIntegervEXTProc )(GLuint id, GLenum value, GLint *data);
typedef void (OSG_APIENTRY * osgGlGetInvariantFloatvEXTProc )(GLuint id, GLenum value, GLfloat *data);
typedef void (OSG_APIENTRY * osgGlGetLocalConstantBooleanvEXTProc )(GLuint id, GLenum value, GLboolean *data);
typedef void (OSG_APIENTRY * osgGlGetLocalConstantIntegervEXTProc )(GLuint id, GLenum value, GLint *data);
typedef void (OSG_APIENTRY * osgGlGetLocalConstantFloatvEXTProc )(GLuint id, GLenum value, GLfloat *data);
#endif /* GL_EXT_vertex_shader */

#ifdef GL_EXT_vertex_weighting
typedef void (OSG_APIENTRY * osgGlVertexWeightfEXTProc )(GLfloat weight);
typedef void (OSG_APIENTRY * osgGlVertexWeightfvEXTProc )(const GLfloat *weight);
typedef void (OSG_APIENTRY * osgGlVertexWeightPointerEXTProc )(GLint size, GLenum type, GLsizei stride, const void *pointer);
#endif /* GL_EXT_vertex_weighting */

#ifdef GL_EXT_x11_sync_object
typedef GLsync (OSG_APIENTRY * osgGlImportSyncEXTProc )(GLenum external_sync_type, GLintptr external_sync, GLbitfield flags);
#endif /* GL_EXT_x11_sync_object */

#ifdef GL_GREMEDY_frame_terminator
typedef void (OSG_APIENTRY * osgGlFrameTerminatorGREMEDYProc )(void);
#endif /* GL_GREMEDY_frame_terminator */

#ifdef GL_GREMEDY_string_marker
typedef void (OSG_APIENTRY * osgGlStringMarkerGREMEDYProc )(GLsizei len, const void *string);
#endif /* GL_GREMEDY_string_marker */

#ifdef GL_HP_convolution_border_modes
#endif /* GL_HP_convolution_border_modes */

#ifdef GL_HP_image_transform
typedef void (OSG_APIENTRY * osgGlImageTransformParameteriHPProc )(GLenum target, GLenum pname, GLint param);
typedef void (OSG_APIENTRY * osgGlImageTransformParameterfHPProc )(GLenum target, GLenum pname, GLfloat param);
typedef void (OSG_APIENTRY * osgGlImageTransformParameterivHPProc )(GLenum target, GLenum pname, const GLint *params);
typedef void (OSG_APIENTRY * osgGlImageTransformParameterfvHPProc )(GLenum target, GLenum pname, const GLfloat *params);
typedef void (OSG_APIENTRY * osgGlGetImageTransformParameterivHPProc )(GLenum target, GLenum pname, GLint *params);
typedef void (OSG_APIENTRY * osgGlGetImageTransformParameterfvHPProc )(GLenum target, GLenum pname, GLfloat *params);
#endif /* GL_HP_image_transform */

#ifdef GL_HP_occlusion_test
#endif /* GL_HP_occlusion_test */

#ifdef GL_HP_texture_lighting
#endif /* GL_HP_texture_lighting */

#ifdef GL_IBM_cull_vertex
#endif /* GL_IBM_cull_vertex */

#ifdef GL_IBM_multimode_draw_arrays
typedef void (OSG_APIENTRY * osgGlMultiModeDrawArraysIBMProc )(const GLenum *mode, const GLint *first, const GLsizei *count, GLsizei primcount, GLint modestride);
typedef void (OSG_APIENTRY * osgGlMultiModeDrawElementsIBMProc )(const GLenum *mode, const GLsizei *count, GLenum type, const void *const*indices, GLsizei primcount, GLint modestride);
#endif /* GL_IBM_multimode_draw_arrays */

#ifdef GL_IBM_rasterpos_clip
#endif /* GL_IBM_rasterpos_clip */

#ifdef GL_IBM_static_data
typedef void (OSG_APIENTRY * osgGlFlushStaticDataIBMProc )(GLenum target);
#endif /* GL_IBM_static_data */

#ifdef GL_IBM_texture_mirrored_repeat
#endif /* GL_IBM_texture_mirrored_repeat */

#ifdef GL_IBM_vertex_array_lists
typedef void (OSG_APIENTRY * osgGlColorPointerListIBMProc )(GLint size, GLenum type, GLint stride, const void **pointer, GLint ptrstride);
typedef void (OSG_APIENTRY * osgGlSecondaryColorPointerListIBMProc )(GLint size, GLenum type, GLint stride, const void **pointer, GLint ptrstride);
typedef void (OSG_APIENTRY * osgGlEdgeFlagPointerListIBMProc )(GLint stride, const GLboolean **pointer, GLint ptrstride);
typedef void (OSG_APIENTRY * osgGlFogCoordPointerListIBMProc )(GLenum type, GLint stride, const void **pointer, GLint ptrstride);
typedef void (OSG_APIENTRY * osgGlIndexPointerListIBMProc )(GLenum type, GLint stride, const void **pointer, GLint ptrstride);
typedef void (OSG_APIENTRY * osgGlNormalPointerListIBMProc )(GLenum type, GLint stride, const void **pointer, GLint ptrstride);
typedef void (OSG_APIENTRY * osgGlTexCoordPointerListIBMProc )(GLint size, GLenum type, GLint stride, const void **pointer, GLint ptrstride);
typedef void (OSG_APIENTRY * osgGlVertexPointerListIBMProc )(GLint size, GLenum type, GLint stride, const void **pointer, GLint ptrstride);
#endif /* GL_IBM_vertex_array_lists */

#ifdef GL_INGR_blend_func_separate
typedef void (OSG_APIENTRY * osgGlBlendFuncSeparateINGRProc )(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);
#endif /* GL_INGR_blend_func_separate */

#ifdef GL_INGR_color_clamp
#endif /* GL_INGR_color_clamp */

#ifdef GL_INGR_interlace_read
#endif /* GL_INGR_interlace_read */

#ifdef GL_INTEL_fragment_shader_ordering
#endif /* GL_INTEL_fragment_shader_ordering */

#ifdef GL_INTEL_framebuffer_CMAA
typedef void (OSG_APIENTRY * osgGlApplyFramebufferAttachmentCMAAINTELProc )(void);
#endif /* GL_INTEL_framebuffer_CMAA */

#ifdef GL_INTEL_map_texture
typedef void (OSG_APIENTRY * osgGlSyncTextureINTELProc )(GLuint texture);
typedef void (OSG_APIENTRY * osgGlUnmapTexture2DINTELProc )(GLuint texture, GLint level);
typedef void *(OSG_APIENTRY * osgGlMapTexture2DINTELProc )(GLuint texture, GLint level, GLbitfield access, GLint *stride, GLenum *layout);
#endif /* GL_INTEL_map_texture */

#ifdef GL_INTEL_parallel_arrays
typedef void (OSG_APIENTRY * osgGlVertexPointervINTELProc )(GLint size, GLenum type, const void **pointer);
typedef void (OSG_APIENTRY * osgGlNormalPointervINTELProc )(GLenum type, const void **pointer);
typedef void (OSG_APIENTRY * osgGlColorPointervINTELProc )(GLint size, GLenum type, const void **pointer);
typedef void (OSG_APIENTRY * osgGlTexCoordPointervINTELProc )(GLint size, GLenum type, const void **pointer);
#endif /* GL_INTEL_parallel_arrays */

#ifdef GL_INTEL_performance_query
typedef void (OSG_APIENTRY * osgGlBeginPerfQueryINTELProc )(GLuint queryHandle);
typedef void (OSG_APIENTRY * osgGlCreatePerfQueryINTELProc )(GLuint queryId, GLuint *queryHandle);
typedef void (OSG_APIENTRY * osgGlDeletePerfQueryINTELProc )(GLuint queryHandle);
typedef void (OSG_APIENTRY * osgGlEndPerfQueryINTELProc )(GLuint queryHandle);
typedef void (OSG_APIENTRY * osgGlGetFirstPerfQueryIdINTELProc )(GLuint *queryId);
typedef void (OSG_APIENTRY * osgGlGetNextPerfQueryIdINTELProc )(GLuint queryId, GLuint *nextQueryId);
typedef void (OSG_APIENTRY * osgGlGetPerfCounterInfoINTELProc )(GLuint queryId, GLuint counterId, GLuint counterNameLength, GLchar *counterName, GLuint counterDescLength, GLchar *counterDesc, GLuint *counterOffset, GLuint *counterDataSize, GLuint *counterTypeEnum, GLuint *counterDataTypeEnum, GLuint64 *rawCounterMaxValue);
typedef void (OSG_APIENTRY * osgGlGetPerfQueryDataINTELProc )(GLuint queryHandle, GLuint flags, GLsizei dataSize, GLvoid *data, GLuint *bytesWritten);
typedef void (OSG_APIENTRY * osgGlGetPerfQueryIdByNameINTELProc )(GLchar *queryName, GLuint *queryId);
typedef void (OSG_APIENTRY * osgGlGetPerfQueryInfoINTELProc )(GLuint queryId, GLuint queryNameLength, GLchar *queryName, GLuint *dataSize, GLuint *noCounters, GLuint *noInstances, GLuint *capsMask);
#endif /* GL_INTEL_performance_query */

#ifdef GL_MESAX_texture_stack
#endif /* GL_MESAX_texture_stack */

#ifdef GL_MESA_pack_invert
#endif /* GL_MESA_pack_invert */

#ifdef GL_MESA_resize_buffers
typedef void (OSG_APIENTRY * osgGlResizeBuffersMESAProc )(void);
#endif /* GL_MESA_resize_buffers */

#ifdef GL_MESA_window_pos
typedef void (OSG_APIENTRY * osgGlWindowPos2dMESAProc )(GLdouble x, GLdouble y);
typedef void (OSG_APIENTRY * osgGlWindowPos2dvMESAProc )(const GLdouble *v);
typedef void (OSG_APIENTRY * osgGlWindowPos2fMESAProc )(GLfloat x, GLfloat y);
typedef void (OSG_APIENTRY * osgGlWindowPos2fvMESAProc )(const GLfloat *v);
typedef void (OSG_APIENTRY * osgGlWindowPos2iMESAProc )(GLint x, GLint y);
typedef void (OSG_APIENTRY * osgGlWindowPos2ivMESAProc )(const GLint *v);
typedef void (OSG_APIENTRY * osgGlWindowPos2sMESAProc )(GLshort x, GLshort y);
typedef void (OSG_APIENTRY * osgGlWindowPos2svMESAProc )(const GLshort *v);
typedef void (OSG_APIENTRY * osgGlWindowPos3dMESAProc )(GLdouble x, GLdouble y, GLdouble z);
typedef void (OSG_APIENTRY * osgGlWindowPos3dvMESAProc )(const GLdouble *v);
typedef void (OSG_APIENTRY * osgGlWindowPos3fMESAProc )(GLfloat x, GLfloat y, GLfloat z);
typedef void (OSG_APIENTRY * osgGlWindowPos3fvMESAProc )(const GLfloat *v);
typedef void (OSG_APIENTRY * osgGlWindowPos3iMESAProc )(GLint x, GLint y, GLint z);
typedef void (OSG_APIENTRY * osgGlWindowPos3ivMESAProc )(const GLint *v);
typedef void (OSG_APIENTRY * osgGlWindowPos3sMESAProc )(GLshort x, GLshort y, GLshort z);
typedef void (OSG_APIENTRY * osgGlWindowPos3svMESAProc )(const GLshort *v);
typedef void (OSG_APIENTRY * osgGlWindowPos4dMESAProc )(GLdouble x, GLdouble y, GLdouble z, GLdouble w);
typedef void (OSG_APIENTRY * osgGlWindowPos4dvMESAProc )(const GLdouble *v);
typedef void (OSG_APIENTRY * osgGlWindowPos4fMESAProc )(GLfloat x, GLfloat y, GLfloat z, GLfloat w);
typedef void (OSG_APIENTRY * osgGlWindowPos4fvMESAProc )(const GLfloat *v);
typedef void (OSG_APIENTRY * osgGlWindowPos4iMESAProc )(GLint x, GLint y, GLint z, GLint w);
typedef void (OSG_APIENTRY * osgGlWindowPos4ivMESAProc )(const GLint *v);
typedef void (OSG_APIENTRY * osgGlWindowPos4sMESAProc )(GLshort x, GLshort y, GLshort z, GLshort w);
typedef void (OSG_APIENTRY * osgGlWindowPos4svMESAProc )(const GLshort *v);
#endif /* GL_MESA_window_pos */

#ifdef GL_MESA_ycbcr_texture
#endif /* GL_MESA_ycbcr_texture */

#ifdef GL_NVX_conditional_render
typedef void (OSG_APIENTRY * osgGlBeginConditionalRenderNVXProc )(GLuint id);
typedef void (OSG_APIENTRY * osgGlEndConditionalRenderNVXProc )(void);
#endif /* GL_NVX_conditional_render */

#ifdef GL_NVX_gpu_memory_info
#endif /* GL_NVX_gpu_memory_info */

#ifdef GL_NV_bindless_multi_draw_indirect
typedef void (OSG_APIENTRY * osgGlMultiDrawArraysIndirectBindlessNVProc )(GLenum mode, const void *indirect, GLsizei drawCount, GLsizei stride, GLint vertexBufferCount);
typedef void (OSG_APIENTRY * osgGlMultiDrawElementsIndirectBindlessNVProc )(GLenum mode, GLenum type, const void *indirect, GLsizei drawCount, GLsizei stride, GLint vertexBufferCount);
#endif /* GL_NV_bindless_multi_draw_indirect */

#ifdef GL_NV_bindless_multi_draw_indirect_count
typedef void (OSG_APIENTRY * osgGlMultiDrawArraysIndirectBindlessCountNVProc )(GLenum mode, const void *indirect, GLsizei drawCount, GLsizei maxDrawCount, GLsizei stride, GLint vertexBufferCount);
typedef void (OSG_APIENTRY * osgGlMultiDrawElementsIndirectBindlessCountNVProc )(GLenum mode, GLenum type, const void *indirect, GLsizei drawCount, GLsizei maxDrawCount, GLsizei stride, GLint vertexBufferCount);
#endif /* GL_NV_bindless_multi_draw_indirect_count */

#ifdef GL_NV_bindless_texture
typedef GLuint64 (OSG_APIENTRY * osgGlGetTextureHandleNVProc )(GLuint texture);
typedef GLuint64 (OSG_APIENTRY * osgGlGetTextureSamplerHandleNVProc )(GLuint texture, GLuint sampler);
typedef void (OSG_APIENTRY * osgGlMakeTextureHandleResidentNVProc )(GLuint64 handle);
typedef void (OSG_APIENTRY * osgGlMakeTextureHandleNonResidentNVProc )(GLuint64 handle);
typedef GLuint64 (OSG_APIENTRY * osgGlGetImageHandleNVProc )(GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum format);
typedef void (OSG_APIENTRY * osgGlMakeImageHandleResidentNVProc )(GLuint64 handle, GLenum access);
typedef void (OSG_APIENTRY * osgGlMakeImageHandleNonResidentNVProc )(GLuint64 handle);
typedef void (OSG_APIENTRY * osgGlUniformHandleui64NVProc )(GLint location, GLuint64 value);
typedef void (OSG_APIENTRY * osgGlUniformHandleui64vNVProc )(GLint location, GLsizei count, const GLuint64 *value);
typedef void (OSG_APIENTRY * osgGlProgramUniformHandleui64NVProc )(GLuint program, GLint location, GLuint64 value);
typedef void (OSG_APIENTRY * osgGlProgramUniformHandleui64vNVProc )(GLuint program, GLint location, GLsizei count, const GLuint64 *values);
typedef GLboolean (OSG_APIENTRY * osgGlIsTextureHandleResidentNVProc )(GLuint64 handle);
typedef GLboolean (OSG_APIENTRY * osgGlIsImageHandleResidentNVProc )(GLuint64 handle);
#endif /* GL_NV_bindless_texture */

#ifdef GL_NV_blend_equation_advanced
typedef void (OSG_APIENTRY * osgGlBlendParameteriNVProc )(GLenum pname, GLint value);
typedef void (OSG_APIENTRY * osgGlBlendBarrierNVProc )(void);
#endif /* GL_NV_blend_equation_advanced */

#ifdef GL_NV_blend_equation_advanced_coherent
#endif /* GL_NV_blend_equation_advanced_coherent */

#ifdef GL_NV_blend_square
#endif /* GL_NV_blend_square */

#ifdef GL_NV_command_list
typedef void (OSG_APIENTRY * osgGlCreateStatesNVProc )(GLsizei n, GLuint *states);
typedef void (OSG_APIENTRY * osgGlDeleteStatesNVProc )(GLsizei n, const GLuint *states);
typedef GLboolean (OSG_APIENTRY * osgGlIsStateNVProc )(GLuint state);
typedef void (OSG_APIENTRY * osgGlStateCaptureNVProc )(GLuint state, GLenum mode);
typedef GLuint (OSG_APIENTRY * osgGlGetCommandHeaderNVProc )(GLenum tokenID, GLuint size);
typedef GLushort (OSG_APIENTRY * osgGlGetStageIndexNVProc )(GLenum shadertype);
typedef void (OSG_APIENTRY * osgGlDrawCommandsNVProc )(GLenum primitiveMode, GLuint buffer, const GLintptr *indirects, const GLsizei *sizes, GLuint count);
typedef void (OSG_APIENTRY * osgGlDrawCommandsAddressNVProc )(GLenum primitiveMode, const GLuint64 *indirects, const GLsizei *sizes, GLuint count);
typedef void (OSG_APIENTRY * osgGlDrawCommandsStatesNVProc )(GLuint buffer, const GLintptr *indirects, const GLsizei *sizes, const GLuint *states, const GLuint *fbos, GLuint count);
typedef void (OSG_APIENTRY * osgGlDrawCommandsStatesAddressNVProc )(const GLuint64 *indirects, const GLsizei *sizes, const GLuint *states, const GLuint *fbos, GLuint count);
typedef void (OSG_APIENTRY * osgGlCreateCommandListsNVProc )(GLsizei n, GLuint *lists);
typedef void (OSG_APIENTRY * osgGlDeleteCommandListsNVProc )(GLsizei n, const GLuint *lists);
typedef GLboolean (OSG_APIENTRY * osgGlIsCommandListNVProc )(GLuint list);
typedef void (OSG_APIENTRY * osgGlListDrawCommandsStatesClientNVProc )(GLuint list, GLuint segment, const void **indirects, const GLsizei *sizes, const GLuint *states, const GLuint *fbos, GLuint count);
typedef void (OSG_APIENTRY * osgGlCommandListSegmentsNVProc )(GLuint list, GLuint segments);
typedef void (OSG_APIENTRY * osgGlCompileCommandListNVProc )(GLuint list);
typedef void (OSG_APIENTRY * osgGlCallCommandListNVProc )(GLuint list);
#endif /* GL_NV_command_list */

#ifdef GL_NV_compute_program5
#endif /* GL_NV_compute_program5 */

#ifdef GL_NV_conditional_render
typedef void (OSG_APIENTRY * osgGlBeginConditionalRenderNVProc )(GLuint id, GLenum mode);
typedef void (OSG_APIENTRY * osgGlEndConditionalRenderNVProc )(void);
#endif /* GL_NV_conditional_render */

#ifdef GL_NV_conservative_raster
typedef void (OSG_APIENTRY * osgGlSubpixelPrecisionBiasNVProc )(GLuint xbits, GLuint ybits);
#endif /* GL_NV_conservative_raster */

#ifdef GL_NV_conservative_raster_dilate
typedef void (OSG_APIENTRY * osgGlConservativeRasterParameterfNVProc )(GLenum pname, GLfloat value);
#endif /* GL_NV_conservative_raster_dilate */

#ifdef GL_NV_copy_depth_to_color
#endif /* GL_NV_copy_depth_to_color */

#ifdef GL_NV_copy_image
typedef void (OSG_APIENTRY * osgGlCopyImageSubDataNVProc )(GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei width, GLsizei height, GLsizei depth);
#endif /* GL_NV_copy_image */

#ifdef GL_NV_deep_texture3D
#endif /* GL_NV_deep_texture3D */

#ifdef GL_NV_depth_buffer_float
typedef void (OSG_APIENTRY * osgGlDepthRangedNVProc )(GLdouble zNear, GLdouble zFar);
typedef void (OSG_APIENTRY * osgGlClearDepthdNVProc )(GLdouble depth);
typedef void (OSG_APIENTRY * osgGlDepthBoundsdNVProc )(GLdouble zmin, GLdouble zmax);
#endif /* GL_NV_depth_buffer_float */

#ifdef GL_NV_depth_clamp
#endif /* GL_NV_depth_clamp */

#ifdef GL_NV_draw_texture
typedef void (OSG_APIENTRY * osgGlDrawTextureNVProc )(GLuint texture, GLuint sampler, GLfloat x0, GLfloat y0, GLfloat x1, GLfloat y1, GLfloat z, GLfloat s0, GLfloat t0, GLfloat s1, GLfloat t1);
#endif /* GL_NV_draw_texture */

#ifdef GL_NV_evaluators
typedef void (OSG_APIENTRY * osgGlMapControlPointsNVProc )(GLenum target, GLuint index, GLenum type, GLsizei ustride, GLsizei vstride, GLint uorder, GLint vorder, GLboolean packed, const void *points);
typedef void (OSG_APIENTRY * osgGlMapParameterivNVProc )(GLenum target, GLenum pname, const GLint *params);
typedef void (OSG_APIENTRY * osgGlMapParameterfvNVProc )(GLenum target, GLenum pname, const GLfloat *params);
typedef void (OSG_APIENTRY * osgGlGetMapControlPointsNVProc )(GLenum target, GLuint index, GLenum type, GLsizei ustride, GLsizei vstride, GLboolean packed, void *points);
typedef void (OSG_APIENTRY * osgGlGetMapParameterivNVProc )(GLenum target, GLenum pname, GLint *params);
typedef void (OSG_APIENTRY * osgGlGetMapParameterfvNVProc )(GLenum target, GLenum pname, GLfloat *params);
typedef void (OSG_APIENTRY * osgGlGetMapAttribParameterivNVProc )(GLenum target, GLuint index, GLenum pname, GLint *params);
typedef void (OSG_APIENTRY * osgGlGetMapAttribParameterfvNVProc )(GLenum target, GLuint index, GLenum pname, GLfloat *params);
typedef void (OSG_APIENTRY * osgGlEvalMapsNVProc )(GLenum target, GLenum mode);
#endif /* GL_NV_evaluators */

#ifdef GL_NV_explicit_multisample
typedef void (OSG_APIENTRY * osgGlGetMultisamplefvNVProc )(GLenum pname, GLuint index, GLfloat *val);
typedef void (OSG_APIENTRY * osgGlSampleMaskIndexedNVProc )(GLuint index, GLbitfield mask);
typedef void (OSG_APIENTRY * osgGlTexRenderbufferNVProc )(GLenum target, GLuint renderbuffer);
#endif /* GL_NV_explicit_multisample */

#ifdef GL_NV_fence
typedef void (OSG_APIENTRY * osgGlDeleteFencesNVProc )(GLsizei n, const GLuint *fences);
typedef void (OSG_APIENTRY * osgGlGenFencesNVProc )(GLsizei n, GLuint *fences);
typedef GLboolean (OSG_APIENTRY * osgGlIsFenceNVProc )(GLuint fence);
typedef GLboolean (OSG_APIENTRY * osgGlTestFenceNVProc )(GLuint fence);
typedef void (OSG_APIENTRY * osgGlGetFenceivNVProc )(GLuint fence, GLenum pname, GLint *params);
typedef void (OSG_APIENTRY * osgGlFinishFenceNVProc )(GLuint fence);
typedef void (OSG_APIENTRY * osgGlSetFenceNVProc )(GLuint fence, GLenum condition);
#endif /* GL_NV_fence */

#ifdef GL_NV_fill_rectangle
#endif /* GL_NV_fill_rectangle */

#ifdef GL_NV_float_buffer
#endif /* GL_NV_float_buffer */

#ifdef GL_NV_fog_distance
#endif /* GL_NV_fog_distance */

#ifdef GL_NV_fragment_coverage_to_color
typedef void (OSG_APIENTRY * osgGlFragmentCoverageColorNVProc )(GLuint color);
#endif /* GL_NV_fragment_coverage_to_color */

#ifdef GL_NV_fragment_program
typedef void (OSG_APIENTRY * osgGlProgramNamedParameter4fNVProc )(GLuint id, GLsizei len, const GLubyte *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
typedef void (OSG_APIENTRY * osgGlProgramNamedParameter4fvNVProc )(GLuint id, GLsizei len, const GLubyte *name, const GLfloat *v);
typedef void (OSG_APIENTRY * osgGlProgramNamedParameter4dNVProc )(GLuint id, GLsizei len, const GLubyte *name, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
typedef void (OSG_APIENTRY * osgGlProgramNamedParameter4dvNVProc )(GLuint id, GLsizei len, const GLubyte *name, const GLdouble *v);
typedef void (OSG_APIENTRY * osgGlGetProgramNamedParameterfvNVProc )(GLuint id, GLsizei len, const GLubyte *name, GLfloat *params);
typedef void (OSG_APIENTRY * osgGlGetProgramNamedParameterdvNVProc )(GLuint id, GLsizei len, const GLubyte *name, GLdouble *params);
#endif /* GL_NV_fragment_program */

#ifdef GL_NV_fragment_program2
#endif /* GL_NV_fragment_program2 */

#ifdef GL_NV_fragment_program4
#endif /* GL_NV_fragment_program4 */

#ifdef GL_NV_fragment_program_option
#endif /* GL_NV_fragment_program_option */

#ifdef GL_NV_fragment_shader_interlock
#endif /* GL_NV_fragment_shader_interlock */

#ifdef GL_NV_framebuffer_mixed_samples
typedef void (OSG_APIENTRY * osgGlCoverageModulationTableNVProc )(GLsizei n, const GLfloat *v);
typedef void (OSG_APIENTRY * osgGlGetCoverageModulationTableNVProc )(GLsizei bufsize, GLfloat *v);
typedef void (OSG_APIENTRY * osgGlCoverageModulationNVProc )(GLenum components);
#endif /* GL_NV_framebuffer_mixed_samples */

#ifdef GL_NV_framebuffer_multisample_coverage
typedef void (OSG_APIENTRY * osgGlRenderbufferStorageMultisampleCoverageNVProc )(GLenum target, GLsizei coverageSamples, GLsizei colorSamples, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (OSG_APIENTRY * osgGlRenderbufferStorageMultisampleCoverageProc )(GLenum target, GLsizei coverageSamples, GLsizei colorSamples, GLenum internalformat, GLsizei width, GLsizei height);
#endif /* GL_NV_framebuffer_multisample_coverage */

#ifdef GL_NV_geometry_program4
typedef void (OSG_APIENTRY * osgGlProgramVertexLimitNVProc )(GLenum target, GLint limit);
typedef void (OSG_APIENTRY * osgGlFramebufferTextureEXTProc )(GLenum target, GLenum attachment, GLuint texture, GLint level);
typedef void (OSG_APIENTRY * osgGlFramebufferTextureFaceEXTProc )(GLenum target, GLenum attachment, GLuint texture, GLint level, GLenum face);
#endif /* GL_NV_geometry_program4 */

#ifdef GL_NV_geometry_shader4
#endif /* GL_NV_geometry_shader4 */

#ifdef GL_NV_geometry_shader_passthrough
#endif /* GL_NV_geometry_shader_passthrough */

#ifdef GL_NV_gpu_program4
typedef void (OSG_APIENTRY * osgGlProgramLocalParameterI4iNVProc )(GLenum target, GLuint index, GLint x, GLint y, GLint z, GLint w);
typedef void (OSG_APIENTRY * osgGlProgramLocalParameterI4ivNVProc )(GLenum target, GLuint index, const GLint *params);
typedef void (OSG_APIENTRY * osgGlProgramLocalParametersI4ivNVProc )(GLenum target, GLuint index, GLsizei count, const GLint *params);
typedef void (OSG_APIENTRY * osgGlProgramLocalParameterI4uiNVProc )(GLenum target, GLuint index, GLuint x, GLuint y, GLuint z, GLuint w);
typedef void (OSG_APIENTRY * osgGlProgramLocalParameterI4uivNVProc )(GLenum target, GLuint index, const GLuint *params);
typedef void (OSG_APIENTRY * osgGlProgramLocalParametersI4uivNVProc )(GLenum target, GLuint index, GLsizei count, const GLuint *params);
typedef void (OSG_APIENTRY * osgGlProgramEnvParameterI4iNVProc )(GLenum target, GLuint index, GLint x, GLint y, GLint z, GLint w);
typedef void (OSG_APIENTRY * osgGlProgramEnvParameterI4ivNVProc )(GLenum target, GLuint index, const GLint *params);
typedef void (OSG_APIENTRY * osgGlProgramEnvParametersI4ivNVProc )(GLenum target, GLuint index, GLsizei count, const GLint *params);
typedef void (OSG_APIENTRY * osgGlProgramEnvParameterI4uiNVProc )(GLenum target, GLuint index, GLuint x, GLuint y, GLuint z, GLuint w);
typedef void (OSG_APIENTRY * osgGlProgramEnvParameterI4uivNVProc )(GLenum target, GLuint index, const GLuint *params);
typedef void (OSG_APIENTRY * osgGlProgramEnvParametersI4uivNVProc )(GLenum target, GLuint index, GLsizei count, const GLuint *params);
typedef void (OSG_APIENTRY * osgGlGetProgramLocalParameterIivNVProc )(GLenum target, GLuint index, GLint *params);
typedef void (OSG_APIENTRY * osgGlGetProgramLocalParameterIuivNVProc )(GLenum target, GLuint index, GLuint *params);
typedef void (OSG_APIENTRY * osgGlGetProgramEnvParameterIivNVProc )(GLenum target, GLuint index, GLint *params);
typedef void (OSG_APIENTRY * osgGlGetProgramEnvParameterIuivNVProc )(GLenum target, GLuint index, GLuint *params);
#endif /* GL_NV_gpu_program4 */

#ifdef GL_NV_gpu_program5
typedef void (OSG_APIENTRY * osgGlProgramSubroutineParametersuivNVProc )(GLenum target, GLsizei count, const GLuint *params);
typedef void (OSG_APIENTRY * osgGlGetProgramSubroutineParameteruivNVProc )(GLenum target, GLuint index, GLuint *param);
#endif /* GL_NV_gpu_program5 */

#ifdef GL_NV_gpu_program5_mem_extended
#endif /* GL_NV_gpu_program5_mem_extended */

#ifdef GL_NV_gpu_shader5
#endif /* GL_NV_gpu_shader5 */

#ifdef GL_NV_half_float
typedef void (OSG_APIENTRY * osgGlVertex2hNVProc )(GLhalfNV x, GLhalfNV y);
typedef void (OSG_APIENTRY * osgGlVertex2hvNVProc )(const GLhalfNV *v);
typedef void (OSG_APIENTRY * osgGlVertex3hNVProc )(GLhalfNV x, GLhalfNV y, GLhalfNV z);
typedef void (OSG_APIENTRY * osgGlVertex3hvNVProc )(const GLhalfNV *v);
typedef void (OSG_APIENTRY * osgGlVertex4hNVProc )(GLhalfNV x, GLhalfNV y, GLhalfNV z, GLhalfNV w);
typedef void (OSG_APIENTRY * osgGlVertex4hvNVProc )(const GLhalfNV *v);
typedef void (OSG_APIENTRY * osgGlNormal3hNVProc )(GLhalfNV nx, GLhalfNV ny, GLhalfNV nz);
typedef void (OSG_APIENTRY * osgGlNormal3hvNVProc )(const GLhalfNV *v);
typedef void (OSG_APIENTRY * osgGlColor3hNVProc )(GLhalfNV red, GLhalfNV green, GLhalfNV blue);
typedef void (OSG_APIENTRY * osgGlColor3hvNVProc )(const GLhalfNV *v);
typedef void (OSG_APIENTRY * osgGlColor4hNVProc )(GLhalfNV red, GLhalfNV green, GLhalfNV blue, GLhalfNV alpha);
typedef void (OSG_APIENTRY * osgGlColor4hvNVProc )(const GLhalfNV *v);
typedef void (OSG_APIENTRY * osgGlTexCoord1hNVProc )(GLhalfNV s);
typedef void (OSG_APIENTRY * osgGlTexCoord1hvNVProc )(const GLhalfNV *v);
typedef void (OSG_APIENTRY * osgGlTexCoord2hNVProc )(GLhalfNV s, GLhalfNV t);
typedef void (OSG_APIENTRY * osgGlTexCoord2hvNVProc )(const GLhalfNV *v);
typedef void (OSG_APIENTRY * osgGlTexCoord3hNVProc )(GLhalfNV s, GLhalfNV t, GLhalfNV r);
typedef void (OSG_APIENTRY * osgGlTexCoord3hvNVProc )(const GLhalfNV *v);
typedef void (OSG_APIENTRY * osgGlTexCoord4hNVProc )(GLhalfNV s, GLhalfNV t, GLhalfNV r, GLhalfNV q);
typedef void (OSG_APIENTRY * osgGlTexCoord4hvNVProc )(const GLhalfNV *v);
typedef void (OSG_APIENTRY * osgGlMultiTexCoord1hNVProc )(GLenum target, GLhalfNV s);
typedef void (OSG_APIENTRY * osgGlMultiTexCoord1hvNVProc )(GLenum target, const GLhalfNV *v);
typedef void (OSG_APIENTRY * osgGlMultiTexCoord2hNVProc )(GLenum target, GLhalfNV s, GLhalfNV t);
typedef void (OSG_APIENTRY * osgGlMultiTexCoord2hvNVProc )(GLenum target, const GLhalfNV *v);
typedef void (OSG_APIENTRY * osgGlMultiTexCoord3hNVProc )(GLenum target, GLhalfNV s, GLhalfNV t, GLhalfNV r);
typedef void (OSG_APIENTRY * osgGlMultiTexCoord3hvNVProc )(GLenum target, const GLhalfNV *v);
typedef void (OSG_APIENTRY * osgGlMultiTexCoord4hNVProc )(GLenum target, GLhalfNV s, GLhalfNV t, GLhalfNV r, GLhalfNV q);
typedef void (OSG_APIENTRY * osgGlMultiTexCoord4hvNVProc )(GLenum target, const GLhalfNV *v);
typedef void (OSG_APIENTRY * osgGlFogCoordhNVProc )(GLhalfNV fog);
typedef void (OSG_APIENTRY * osgGlFogCoordhvNVProc )(const GLhalfNV *fog);
typedef void (OSG_APIENTRY * osgGlSecondaryColor3hNVProc )(GLhalfNV red, GLhalfNV green, GLhalfNV blue);
typedef void (OSG_APIENTRY * osgGlSecondaryColor3hvNVProc )(const GLhalfNV *v);
typedef void (OSG_APIENTRY * osgGlVertexWeighthNVProc )(GLhalfNV weight);
typedef void (OSG_APIENTRY * osgGlVertexWeighthvNVProc )(const GLhalfNV *weight);
typedef void (OSG_APIENTRY * osgGlVertexAttrib1hNVProc )(GLuint index, GLhalfNV x);
typedef void (OSG_APIENTRY * osgGlVertexAttrib1hvNVProc )(GLuint index, const GLhalfNV *v);
typedef void (OSG_APIENTRY * osgGlVertexAttrib2hNVProc )(GLuint index, GLhalfNV x, GLhalfNV y);
typedef void (OSG_APIENTRY * osgGlVertexAttrib2hvNVProc )(GLuint index, const GLhalfNV *v);
typedef void (OSG_APIENTRY * osgGlVertexAttrib3hNVProc )(GLuint index, GLhalfNV x, GLhalfNV y, GLhalfNV z);
typedef void (OSG_APIENTRY * osgGlVertexAttrib3hvNVProc )(GLuint index, const GLhalfNV *v);
typedef void (OSG_APIENTRY * osgGlVertexAttrib4hNVProc )(GLuint index, GLhalfNV x, GLhalfNV y, GLhalfNV z, GLhalfNV w);
typedef void (OSG_APIENTRY * osgGlVertexAttrib4hvNVProc )(GLuint index, const GLhalfNV *v);
typedef void (OSG_APIENTRY * osgGlVertexAttribs1hvNVProc )(GLuint index, GLsizei n, const GLhalfNV *v);
typedef void (OSG_APIENTRY * osgGlVertexAttribs2hvNVProc )(GLuint index, GLsizei n, const GLhalfNV *v);
typedef void (OSG_APIENTRY * osgGlVertexAttribs3hvNVProc )(GLuint index, GLsizei n, const GLhalfNV *v);
typedef void (OSG_APIENTRY * osgGlVertexAttribs4hvNVProc )(GLuint index, GLsizei n, const GLhalfNV *v);
#endif /* GL_NV_half_float */

#ifdef GL_NV_internalformat_sample_query
typedef void (OSG_APIENTRY * osgGlGetInternalformatSampleivNVProc )(GLenum target, GLenum internalformat, GLsizei samples, GLenum pname, GLsizei bufSize, GLint *params);
#endif /* GL_NV_internalformat_sample_query */

#ifdef GL_NV_light_max_exponent
#endif /* GL_NV_light_max_exponent */

#ifdef GL_NV_multisample_coverage
#endif /* GL_NV_multisample_coverage */

#ifdef GL_NV_multisample_filter_hint
#endif /* GL_NV_multisample_filter_hint */

#ifdef GL_NV_occlusion_query
typedef void (OSG_APIENTRY * osgGlGenOcclusionQueriesNVProc )(GLsizei n, GLuint *ids);
typedef void (OSG_APIENTRY * osgGlDeleteOcclusionQueriesNVProc )(GLsizei n, const GLuint *ids);
typedef GLboolean (OSG_APIENTRY * osgGlIsOcclusionQueryNVProc )(GLuint id);
typedef void (OSG_APIENTRY * osgGlBeginOcclusionQueryNVProc )(GLuint id);
typedef void (OSG_APIENTRY * osgGlEndOcclusionQueryNVProc )(void);
typedef void (OSG_APIENTRY * osgGlGetOcclusionQueryivNVProc )(GLuint id, GLenum pname, GLint *params);
typedef void (OSG_APIENTRY * osgGlGetOcclusionQueryuivNVProc )(GLuint id, GLenum pname, GLuint *params);
#endif /* GL_NV_occlusion_query */

#ifdef GL_NV_packed_depth_stencil
#endif /* GL_NV_packed_depth_stencil */

#ifdef GL_NV_parameter_buffer_object
typedef void (OSG_APIENTRY * osgGlProgramBufferParametersfvNVProc )(GLenum target, GLuint bindingIndex, GLuint wordIndex, GLsizei count, const GLfloat *params);
typedef void (OSG_APIENTRY * osgGlProgramBufferParametersIivNVProc )(GLenum target, GLuint bindingIndex, GLuint wordIndex, GLsizei count, const GLint *params);
typedef void (OSG_APIENTRY * osgGlProgramBufferParametersIuivNVProc )(GLenum target, GLuint bindingIndex, GLuint wordIndex, GLsizei count, const GLuint *params);
#endif /* GL_NV_parameter_buffer_object */

#ifdef GL_NV_parameter_buffer_object2
#endif /* GL_NV_parameter_buffer_object2 */

#ifdef GL_NV_path_rendering
typedef GLuint (OSG_APIENTRY * osgGlGenPathsNVProc )(GLsizei range);
typedef void (OSG_APIENTRY * osgGlDeletePathsNVProc )(GLuint path, GLsizei range);
typedef GLboolean (OSG_APIENTRY * osgGlIsPathNVProc )(GLuint path);
typedef void (OSG_APIENTRY * osgGlPathCommandsNVProc )(GLuint path, GLsizei numCommands, const GLubyte *commands, GLsizei numCoords, GLenum coordType, const void *coords);
typedef void (OSG_APIENTRY * osgGlPathCoordsNVProc )(GLuint path, GLsizei numCoords, GLenum coordType, const void *coords);
typedef void (OSG_APIENTRY * osgGlPathSubCommandsNVProc )(GLuint path, GLsizei commandStart, GLsizei commandsToDelete, GLsizei numCommands, const GLubyte *commands, GLsizei numCoords, GLenum coordType, const void *coords);
typedef void (OSG_APIENTRY * osgGlPathSubCoordsNVProc )(GLuint path, GLsizei coordStart, GLsizei numCoords, GLenum coordType, const void *coords);
typedef void (OSG_APIENTRY * osgGlPathStringNVProc )(GLuint path, GLenum format, GLsizei length, const void *pathString);
typedef void (OSG_APIENTRY * osgGlPathGlyphsNVProc )(GLuint firstPathName, GLenum fontTarget, const void *fontName, GLbitfield fontStyle, GLsizei numGlyphs, GLenum type, const void *charcodes, GLenum handleMissingGlyphs, GLuint pathParameterTemplate, GLfloat emScale);
typedef void (OSG_APIENTRY * osgGlPathGlyphRangeNVProc )(GLuint firstPathName, GLenum fontTarget, const void *fontName, GLbitfield fontStyle, GLuint firstGlyph, GLsizei numGlyphs, GLenum handleMissingGlyphs, GLuint pathParameterTemplate, GLfloat emScale);
typedef void (OSG_APIENTRY * osgGlWeightPathsNVProc )(GLuint resultPath, GLsizei numPaths, const GLuint *paths, const GLfloat *weights);
typedef void (OSG_APIENTRY * osgGlCopyPathNVProc )(GLuint resultPath, GLuint srcPath);
typedef void (OSG_APIENTRY * osgGlInterpolatePathsNVProc )(GLuint resultPath, GLuint pathA, GLuint pathB, GLfloat weight);
typedef void (OSG_APIENTRY * osgGlTransformPathNVProc )(GLuint resultPath, GLuint srcPath, GLenum transformType, const GLfloat *transformValues);
typedef void (OSG_APIENTRY * osgGlPathParameterivNVProc )(GLuint path, GLenum pname, const GLint *value);
typedef void (OSG_APIENTRY * osgGlPathParameteriNVProc )(GLuint path, GLenum pname, GLint value);
typedef void (OSG_APIENTRY * osgGlPathParameterfvNVProc )(GLuint path, GLenum pname, const GLfloat *value);
typedef void (OSG_APIENTRY * osgGlPathParameterfNVProc )(GLuint path, GLenum pname, GLfloat value);
typedef void (OSG_APIENTRY * osgGlPathDashArrayNVProc )(GLuint path, GLsizei dashCount, const GLfloat *dashArray);
typedef void (OSG_APIENTRY * osgGlPathStencilFuncNVProc )(GLenum func, GLint ref, GLuint mask);
typedef void (OSG_APIENTRY * osgGlPathStencilDepthOffsetNVProc )(GLfloat factor, GLfloat units);
typedef void (OSG_APIENTRY * osgGlStencilFillPathNVProc )(GLuint path, GLenum fillMode, GLuint mask);
typedef void (OSG_APIENTRY * osgGlStencilStrokePathNVProc )(GLuint path, GLint reference, GLuint mask);
typedef void (OSG_APIENTRY * osgGlStencilFillPathInstancedNVProc )(GLsizei numPaths, GLenum pathNameType, const void *paths, GLuint pathBase, GLenum fillMode, GLuint mask, GLenum transformType, const GLfloat *transformValues);
typedef void (OSG_APIENTRY * osgGlStencilStrokePathInstancedNVProc )(GLsizei numPaths, GLenum pathNameType, const void *paths, GLuint pathBase, GLint reference, GLuint mask, GLenum transformType, const GLfloat *transformValues);
typedef void (OSG_APIENTRY * osgGlPathCoverDepthFuncNVProc )(GLenum func);
typedef void (OSG_APIENTRY * osgGlCoverFillPathNVProc )(GLuint path, GLenum coverMode);
typedef void (OSG_APIENTRY * osgGlCoverStrokePathNVProc )(GLuint path, GLenum coverMode);
typedef void (OSG_APIENTRY * osgGlCoverFillPathInstancedNVProc )(GLsizei numPaths, GLenum pathNameType, const void *paths, GLuint pathBase, GLenum coverMode, GLenum transformType, const GLfloat *transformValues);
typedef void (OSG_APIENTRY * osgGlCoverStrokePathInstancedNVProc )(GLsizei numPaths, GLenum pathNameType, const void *paths, GLuint pathBase, GLenum coverMode, GLenum transformType, const GLfloat *transformValues);
typedef void (OSG_APIENTRY * osgGlGetPathParameterivNVProc )(GLuint path, GLenum pname, GLint *value);
typedef void (OSG_APIENTRY * osgGlGetPathParameterfvNVProc )(GLuint path, GLenum pname, GLfloat *value);
typedef void (OSG_APIENTRY * osgGlGetPathCommandsNVProc )(GLuint path, GLubyte *commands);
typedef void (OSG_APIENTRY * osgGlGetPathCoordsNVProc )(GLuint path, GLfloat *coords);
typedef void (OSG_APIENTRY * osgGlGetPathDashArrayNVProc )(GLuint path, GLfloat *dashArray);
typedef void (OSG_APIENTRY * osgGlGetPathMetricsNVProc )(GLbitfield metricQueryMask, GLsizei numPaths, GLenum pathNameType, const void *paths, GLuint pathBase, GLsizei stride, GLfloat *metrics);
typedef void (OSG_APIENTRY * osgGlGetPathMetricRangeNVProc )(GLbitfield metricQueryMask, GLuint firstPathName, GLsizei numPaths, GLsizei stride, GLfloat *metrics);
typedef void (OSG_APIENTRY * osgGlGetPathSpacingNVProc )(GLenum pathListMode, GLsizei numPaths, GLenum pathNameType, const void *paths, GLuint pathBase, GLfloat advanceScale, GLfloat kerningScale, GLenum transformType, GLfloat *returnedSpacing);
typedef GLboolean (OSG_APIENTRY * osgGlIsPointInFillPathNVProc )(GLuint path, GLuint mask, GLfloat x, GLfloat y);
typedef GLboolean (OSG_APIENTRY * osgGlIsPointInStrokePathNVProc )(GLuint path, GLfloat x, GLfloat y);
typedef GLfloat (OSG_APIENTRY * osgGlGetPathLengthNVProc )(GLuint path, GLsizei startSegment, GLsizei numSegments);
typedef GLboolean (OSG_APIENTRY * osgGlPointAlongPathNVProc )(GLuint path, GLsizei startSegment, GLsizei numSegments, GLfloat distance, GLfloat *x, GLfloat *y, GLfloat *tangentX, GLfloat *tangentY);
typedef void (OSG_APIENTRY * osgGlMatrixLoad3x2fNVProc )(GLenum matrixMode, const GLfloat *m);
typedef void (OSG_APIENTRY * osgGlMatrixLoad3x3fNVProc )(GLenum matrixMode, const GLfloat *m);
typedef void (OSG_APIENTRY * osgGlMatrixLoadTranspose3x3fNVProc )(GLenum matrixMode, const GLfloat *m);
typedef void (OSG_APIENTRY * osgGlMatrixMult3x2fNVProc )(GLenum matrixMode, const GLfloat *m);
typedef void (OSG_APIENTRY * osgGlMatrixMult3x3fNVProc )(GLenum matrixMode, const GLfloat *m);
typedef void (OSG_APIENTRY * osgGlMatrixMultTranspose3x3fNVProc )(GLenum matrixMode, const GLfloat *m);
typedef void (OSG_APIENTRY * osgGlStencilThenCoverFillPathNVProc )(GLuint path, GLenum fillMode, GLuint mask, GLenum coverMode);
typedef void (OSG_APIENTRY * osgGlStencilThenCoverStrokePathNVProc )(GLuint path, GLint reference, GLuint mask, GLenum coverMode);
typedef void (OSG_APIENTRY * osgGlStencilThenCoverFillPathInstancedNVProc )(GLsizei numPaths, GLenum pathNameType, const void *paths, GLuint pathBase, GLenum fillMode, GLuint mask, GLenum coverMode, GLenum transformType, const GLfloat *transformValues);
typedef void (OSG_APIENTRY * osgGlStencilThenCoverStrokePathInstancedNVProc )(GLsizei numPaths, GLenum pathNameType, const void *paths, GLuint pathBase, GLint reference, GLuint mask, GLenum coverMode, GLenum transformType, const GLfloat *transformValues);
typedef GLenum (OSG_APIENTRY * osgGlPathGlyphIndexRangeNVProc )(GLenum fontTarget, const void *fontName, GLbitfield fontStyle, GLuint pathParameterTemplate, GLfloat emScale, GLuint baseAndCount[2]);
typedef GLenum (OSG_APIENTRY * osgGlPathGlyphIndexArrayNVProc )(GLuint firstPathName, GLenum fontTarget, const void *fontName, GLbitfield fontStyle, GLuint firstGlyphIndex, GLsizei numGlyphs, GLuint pathParameterTemplate, GLfloat emScale);
typedef GLenum (OSG_APIENTRY * osgGlPathMemoryGlyphIndexArrayNVProc )(GLuint firstPathName, GLenum fontTarget, GLsizeiptr fontSize, const void *fontData, GLsizei faceIndex, GLuint firstGlyphIndex, GLsizei numGlyphs, GLuint pathParameterTemplate, GLfloat emScale);
typedef void (OSG_APIENTRY * osgGlProgramPathFragmentInputGenNVProc )(GLuint program, GLint location, GLenum genMode, GLint components, const GLfloat *coeffs);
typedef void (OSG_APIENTRY * osgGlGetProgramResourcefvNVProc )(GLuint program, GLenum programInterface, GLuint index, GLsizei propCount, const GLenum *props, GLsizei bufSize, GLsizei *length, GLfloat *params);
typedef void (OSG_APIENTRY * osgGlPathColorGenNVProc )(GLenum color, GLenum genMode, GLenum colorFormat, const GLfloat *coeffs);
typedef void (OSG_APIENTRY * osgGlPathTexGenNVProc )(GLenum texCoordSet, GLenum genMode, GLint components, const GLfloat *coeffs);
typedef void (OSG_APIENTRY * osgGlPathFogGenNVProc )(GLenum genMode);
typedef void (OSG_APIENTRY * osgGlGetPathColorGenivNVProc )(GLenum color, GLenum pname, GLint *value);
typedef void (OSG_APIENTRY * osgGlGetPathColorGenfvNVProc )(GLenum color, GLenum pname, GLfloat *value);
typedef void (OSG_APIENTRY * osgGlGetPathTexGenivNVProc )(GLenum texCoordSet, GLenum pname, GLint *value);
typedef void (OSG_APIENTRY * osgGlGetPathTexGenfvNVProc )(GLenum texCoordSet, GLenum pname, GLfloat *value);
#endif /* GL_NV_path_rendering */

#ifdef GL_NV_path_rendering_shared_edge
#endif /* GL_NV_path_rendering_shared_edge */

#ifdef GL_NV_pixel_data_range
typedef void (OSG_APIENTRY * osgGlPixelDataRangeNVProc )(GLenum target, GLsizei length, const void *pointer);
typedef void (OSG_APIENTRY * osgGlFlushPixelDataRangeNVProc )(GLenum target);
#endif /* GL_NV_pixel_data_range */

#ifdef GL_NV_point_sprite
typedef void (OSG_APIENTRY * osgGlPointParameteriNVProc )(GLenum pname, GLint param);
typedef void (OSG_APIENTRY * osgGlPointParameterivNVProc )(GLenum pname, const GLint *params);
#endif /* GL_NV_point_sprite */

#ifdef GL_NV_present_video
typedef void (OSG_APIENTRY * osgGlPresentFrameKeyedNVProc )(GLuint video_slot, GLuint64EXT minPresentTime, GLuint beginPresentTimeId, GLuint presentDurationId, GLenum type, GLenum target0, GLuint fill0, GLuint key0, GLenum target1, GLuint fill1, GLuint key1);
typedef void (OSG_APIENTRY * osgGlPresentFrameDualFillNVProc )(GLuint video_slot, GLuint64EXT minPresentTime, GLuint beginPresentTimeId, GLuint presentDurationId, GLenum type, GLenum target0, GLuint fill0, GLenum target1, GLuint fill1, GLenum target2, GLuint fill2, GLenum target3, GLuint fill3);
typedef void (OSG_APIENTRY * osgGlGetVideoivNVProc )(GLuint video_slot, GLenum pname, GLint *params);
typedef void (OSG_APIENTRY * osgGlGetVideouivNVProc )(GLuint video_slot, GLenum pname, GLuint *params);
typedef void (OSG_APIENTRY * osgGlGetVideoi64vNVProc )(GLuint video_slot, GLenum pname, GLint64EXT *params);
typedef void (OSG_APIENTRY * osgGlGetVideoui64vNVProc )(GLuint video_slot, GLenum pname, GLuint64EXT *params);
#endif /* GL_NV_present_video */

#ifdef GL_NV_primitive_restart
typedef void (OSG_APIENTRY * osgGlPrimitiveRestartNVProc )(void);
typedef void (OSG_APIENTRY * osgGlPrimitiveRestartIndexNVProc )(GLuint index);
#endif /* GL_NV_primitive_restart */

#ifdef GL_NV_register_combiners
typedef void (OSG_APIENTRY * osgGlCombinerParameterfvNVProc )(GLenum pname, const GLfloat *params);
typedef void (OSG_APIENTRY * osgGlCombinerParameterfNVProc )(GLenum pname, GLfloat param);
typedef void (OSG_APIENTRY * osgGlCombinerParameterivNVProc )(GLenum pname, const GLint *params);
typedef void (OSG_APIENTRY * osgGlCombinerParameteriNVProc )(GLenum pname, GLint param);
typedef void (OSG_APIENTRY * osgGlCombinerInputNVProc )(GLenum stage, GLenum portion, GLenum variable, GLenum input, GLenum mapping, GLenum componentUsage);
typedef void (OSG_APIENTRY * osgGlCombinerOutputNVProc )(GLenum stage, GLenum portion, GLenum abOutput, GLenum cdOutput, GLenum sumOutput, GLenum scale, GLenum bias, GLboolean abDotProduct, GLboolean cdDotProduct, GLboolean muxSum);
typedef void (OSG_APIENTRY * osgGlFinalCombinerInputNVProc )(GLenum variable, GLenum input, GLenum mapping, GLenum componentUsage);
typedef void (OSG_APIENTRY * osgGlGetCombinerInputParameterfvNVProc )(GLenum stage, GLenum portion, GLenum variable, GLenum pname, GLfloat *params);
typedef void (OSG_APIENTRY * osgGlGetCombinerInputParameterivNVProc )(GLenum stage, GLenum portion, GLenum variable, GLenum pname, GLint *params);
typedef void (OSG_APIENTRY * osgGlGetCombinerOutputParameterfvNVProc )(GLenum stage, GLenum portion, GLenum pname, GLfloat *params);
typedef void (OSG_APIENTRY * osgGlGetCombinerOutputParameterivNVProc )(GLenum stage, GLenum portion, GLenum pname, GLint *params);
typedef void (OSG_APIENTRY * osgGlGetFinalCombinerInputParameterfvNVProc )(GLenum variable, GLenum pname, GLfloat *params);
typedef void (OSG_APIENTRY * osgGlGetFinalCombinerInputParameterivNVProc )(GLenum variable, GLenum pname, GLint *params);
#endif /* GL_NV_register_combiners */

#ifdef GL_NV_register_combiners2
typedef void (OSG_APIENTRY * osgGlCombinerStageParameterfvNVProc )(GLenum stage, GLenum pname, const GLfloat *params);
typedef void (OSG_APIENTRY * osgGlGetCombinerStageParameterfvNVProc )(GLenum stage, GLenum pname, GLfloat *params);
#endif /* GL_NV_register_combiners2 */

#ifdef GL_NV_sample_locations
typedef void (OSG_APIENTRY * osgGlFramebufferSampleLocationsfvNVProc )(GLenum target, GLuint start, GLsizei count, const GLfloat *v);
typedef void (OSG_APIENTRY * osgGlNamedFramebufferSampleLocationsfvNVProc )(GLuint framebuffer, GLuint start, GLsizei count, const GLfloat *v);
typedef void (OSG_APIENTRY * osgGlResolveDepthValuesNVProc )(void);
#endif /* GL_NV_sample_locations */

#ifdef GL_NV_sample_mask_override_coverage
#endif /* GL_NV_sample_mask_override_coverage */

#ifdef GL_NV_shader_atomic_counters
#endif /* GL_NV_shader_atomic_counters */

#ifdef GL_NV_shader_atomic_float
#endif /* GL_NV_shader_atomic_float */

#ifdef GL_NV_shader_atomic_fp16_vector
#endif /* GL_NV_shader_atomic_fp16_vector */

#ifdef GL_NV_shader_atomic_int64
#endif /* GL_NV_shader_atomic_int64 */

#ifdef GL_NV_shader_buffer_load
typedef void (OSG_APIENTRY * osgGlMakeBufferResidentNVProc )(GLenum target, GLenum access);
typedef void (OSG_APIENTRY * osgGlMakeBufferNonResidentNVProc )(GLenum target);
typedef GLboolean (OSG_APIENTRY * osgGlIsBufferResidentNVProc )(GLenum target);
typedef void (OSG_APIENTRY * osgGlMakeNamedBufferResidentNVProc )(GLuint buffer, GLenum access);
typedef void (OSG_APIENTRY * osgGlMakeNamedBufferNonResidentNVProc )(GLuint buffer);
typedef GLboolean (OSG_APIENTRY * osgGlIsNamedBufferResidentNVProc )(GLuint buffer);
typedef void (OSG_APIENTRY * osgGlGetBufferParameterui64vNVProc )(GLenum target, GLenum pname, GLuint64EXT *params);
typedef void (OSG_APIENTRY * osgGlGetNamedBufferParameterui64vNVProc )(GLuint buffer, GLenum pname, GLuint64EXT *params);
typedef void (OSG_APIENTRY * osgGlGetIntegerui64vNVProc )(GLenum value, GLuint64EXT *result);
typedef void (OSG_APIENTRY * osgGlUniformui64NVProc )(GLint location, GLuint64EXT value);
typedef void (OSG_APIENTRY * osgGlUniformui64vNVProc )(GLint location, GLsizei count, const GLuint64EXT *value);
typedef void (OSG_APIENTRY * osgGlProgramUniformui64NVProc )(GLuint program, GLint location, GLuint64EXT value);
typedef void (OSG_APIENTRY * osgGlProgramUniformui64vNVProc )(GLuint program, GLint location, GLsizei count, const GLuint64EXT *value);
#endif /* GL_NV_shader_buffer_load */

#ifdef GL_NV_shader_buffer_store
#endif /* GL_NV_shader_buffer_store */

#ifdef GL_NV_shader_storage_buffer_object
#endif /* GL_NV_shader_storage_buffer_object */

#ifdef GL_NV_shader_thread_group
#endif /* GL_NV_shader_thread_group */

#ifdef GL_NV_shader_thread_shuffle
#endif /* GL_NV_shader_thread_shuffle */

#ifdef GL_NV_tessellation_program5
#endif /* GL_NV_tessellation_program5 */

#ifdef GL_NV_texgen_emboss
#endif /* GL_NV_texgen_emboss */

#ifdef GL_NV_texgen_reflection
#endif /* GL_NV_texgen_reflection */

#ifdef GL_NV_texture_barrier
typedef void (OSG_APIENTRY * osgGlTextureBarrierNVProc )(void);
#endif /* GL_NV_texture_barrier */

#ifdef GL_NV_texture_compression_vtc
#endif /* GL_NV_texture_compression_vtc */

#ifdef GL_NV_texture_env_combine4
#endif /* GL_NV_texture_env_combine4 */

#ifdef GL_NV_texture_expand_normal
#endif /* GL_NV_texture_expand_normal */

#ifdef GL_NV_texture_multisample
typedef void (OSG_APIENTRY * osgGlTexImage2DMultisampleCoverageNVProc )(GLenum target, GLsizei coverageSamples, GLsizei colorSamples, GLint internalFormat, GLsizei width, GLsizei height, GLboolean fixedSampleLocations);
typedef void (OSG_APIENTRY * osgGlTexImage3DMultisampleCoverageNVProc )(GLenum target, GLsizei coverageSamples, GLsizei colorSamples, GLint internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedSampleLocations);
typedef void (OSG_APIENTRY * osgGlTextureImage2DMultisampleNVProc )(GLuint texture, GLenum target, GLsizei samples, GLint internalFormat, GLsizei width, GLsizei height, GLboolean fixedSampleLocations);
typedef void (OSG_APIENTRY * osgGlTextureImage3DMultisampleNVProc )(GLuint texture, GLenum target, GLsizei samples, GLint internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedSampleLocations);
typedef void (OSG_APIENTRY * osgGlTextureImage2DMultisampleCoverageNVProc )(GLuint texture, GLenum target, GLsizei coverageSamples, GLsizei colorSamples, GLint internalFormat, GLsizei width, GLsizei height, GLboolean fixedSampleLocations);
typedef void (OSG_APIENTRY * osgGlTextureImage3DMultisampleCoverageNVProc )(GLuint texture, GLenum target, GLsizei coverageSamples, GLsizei colorSamples, GLint internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedSampleLocations);
#endif /* GL_NV_texture_multisample */

#ifdef GL_NV_texture_rectangle
#endif /* GL_NV_texture_rectangle */

#ifdef GL_NV_texture_shader
#endif /* GL_NV_texture_shader */

#ifdef GL_NV_texture_shader2
#endif /* GL_NV_texture_shader2 */

#ifdef GL_NV_texture_shader3
#endif /* GL_NV_texture_shader3 */

#ifdef GL_NV_transform_feedback
typedef void (OSG_APIENTRY * osgGlBeginTransformFeedbackNVProc )(GLenum primitiveMode);
typedef void (OSG_APIENTRY * osgGlEndTransformFeedbackNVProc )(void);
typedef void (OSG_APIENTRY * osgGlTransformFeedbackAttribsNVProc )(GLsizei count, const GLint *attribs, GLenum bufferMode);
typedef void (OSG_APIENTRY * osgGlBindBufferRangeNVProc )(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size);
typedef void (OSG_APIENTRY * osgGlBindBufferOffsetNVProc )(GLenum target, GLuint index, GLuint buffer, GLintptr offset);
typedef void (OSG_APIENTRY * osgGlBindBufferBaseNVProc )(GLenum target, GLuint index, GLuint buffer);
typedef void (OSG_APIENTRY * osgGlTransformFeedbackVaryingsNVProc )(GLuint program, GLsizei count, const GLint *locations, GLenum bufferMode);
typedef void (OSG_APIENTRY * osgGlActiveVaryingNVProc )(GLuint program, const GLchar *name);
typedef GLint (OSG_APIENTRY * osgGlGetVaryingLocationNVProc )(GLuint program, const GLchar *name);
typedef void (OSG_APIENTRY * osgGlGetActiveVaryingNVProc )(GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLsizei *size, GLenum *type, GLchar *name);
typedef void (OSG_APIENTRY * osgGlGetTransformFeedbackVaryingNVProc )(GLuint program, GLuint index, GLint *location);
typedef void (OSG_APIENTRY * osgGlTransformFeedbackStreamAttribsNVProc )(GLsizei count, const GLint *attribs, GLsizei nbuffers, const GLint *bufstreams, GLenum bufferMode);
#endif /* GL_NV_transform_feedback */

#ifdef GL_NV_transform_feedback2
typedef void (OSG_APIENTRY * osgGlBindTransformFeedbackNVProc )(GLenum target, GLuint id);
typedef void (OSG_APIENTRY * osgGlDeleteTransformFeedbacksNVProc )(GLsizei n, const GLuint *ids);
typedef void (OSG_APIENTRY * osgGlGenTransformFeedbacksNVProc )(GLsizei n, GLuint *ids);
typedef GLboolean (OSG_APIENTRY * osgGlIsTransformFeedbackNVProc )(GLuint id);
typedef void (OSG_APIENTRY * osgGlPauseTransformFeedbackNVProc )(void);
typedef void (OSG_APIENTRY * osgGlResumeTransformFeedbackNVProc )(void);
typedef void (OSG_APIENTRY * osgGlDrawTransformFeedbackNVProc )(GLenum mode, GLuint id);
#endif /* GL_NV_transform_feedback2 */

#ifdef GL_NV_uniform_buffer_unified_memory
#endif /* GL_NV_uniform_buffer_unified_memory */

#ifdef GL_NV_vdpau_interop
typedef void (OSG_APIENTRY * osgGlVDPAUInitNVProc )(const void *vdpDevice, const void *getProcAddress);
typedef void (OSG_APIENTRY * osgGlVDPAUFiniNVProc )(void);
typedef GLvdpauSurfaceNV (OSG_APIENTRY * osgGlVDPAURegisterVideoSurfaceNVProc )(const void *vdpSurface, GLenum target, GLsizei numTextureNames, const GLuint *textureNames);
typedef GLvdpauSurfaceNV (OSG_APIENTRY * osgGlVDPAURegisterOutputSurfaceNVProc )(const void *vdpSurface, GLenum target, GLsizei numTextureNames, const GLuint *textureNames);
typedef GLboolean (OSG_APIENTRY * osgGlVDPAUIsSurfaceNVProc )(GLvdpauSurfaceNV surface);
typedef void (OSG_APIENTRY * osgGlVDPAUUnregisterSurfaceNVProc )(GLvdpauSurfaceNV surface);
typedef void (OSG_APIENTRY * osgGlVDPAUGetSurfaceivNVProc )(GLvdpauSurfaceNV surface, GLenum pname, GLsizei bufSize, GLsizei *length, GLint *values);
typedef void (OSG_APIENTRY * osgGlVDPAUSurfaceAccessNVProc )(GLvdpauSurfaceNV surface, GLenum access);
typedef void (OSG_APIENTRY * osgGlVDPAUMapSurfacesNVProc )(GLsizei numSurfaces, const GLvdpauSurfaceNV *surfaces);
typedef void (OSG_APIENTRY * osgGlVDPAUUnmapSurfacesNVProc )(GLsizei numSurface, const GLvdpauSurfaceNV *surfaces);
#endif /* GL_NV_vdpau_interop */

#ifdef GL_NV_vertex_array_range
typedef void (OSG_APIENTRY * osgGlFlushVertexArrayRangeNVProc )(void);
typedef void (OSG_APIENTRY * osgGlVertexArrayRangeNVProc )(GLsizei length, const void *pointer);
#endif /* GL_NV_vertex_array_range */

#ifdef GL_NV_vertex_array_range2
#endif /* GL_NV_vertex_array_range2 */

#ifdef GL_NV_vertex_attrib_integer_64bit
typedef void (OSG_APIENTRY * osgGlVertexAttribL1i64NVProc )(GLuint index, GLint64EXT x);
typedef void (OSG_APIENTRY * osgGlVertexAttribL2i64NVProc )(GLuint index, GLint64EXT x, GLint64EXT y);
typedef void (OSG_APIENTRY * osgGlVertexAttribL3i64NVProc )(GLuint index, GLint64EXT x, GLint64EXT y, GLint64EXT z);
typedef void (OSG_APIENTRY * osgGlVertexAttribL4i64NVProc )(GLuint index, GLint64EXT x, GLint64EXT y, GLint64EXT z, GLint64EXT w);
typedef void (OSG_APIENTRY * osgGlVertexAttribL1i64vNVProc )(GLuint index, const GLint64EXT *v);
typedef void (OSG_APIENTRY * osgGlVertexAttribL2i64vNVProc )(GLuint index, const GLint64EXT *v);
typedef void (OSG_APIENTRY * osgGlVertexAttribL3i64vNVProc )(GLuint index, const GLint64EXT *v);
typedef void (OSG_APIENTRY * osgGlVertexAttribL4i64vNVProc )(GLuint index, const GLint64EXT *v);
typedef void (OSG_APIENTRY * osgGlVertexAttribL1ui64NVProc )(GLuint index, GLuint64EXT x);
typedef void (OSG_APIENTRY * osgGlVertexAttribL2ui64NVProc )(GLuint index, GLuint64EXT x, GLuint64EXT y);
typedef void (OSG_APIENTRY * osgGlVertexAttribL3ui64NVProc )(GLuint index, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z);
typedef void (OSG_APIENTRY * osgGlVertexAttribL4ui64NVProc )(GLuint index, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z, GLuint64EXT w);
typedef void (OSG_APIENTRY * osgGlVertexAttribL1ui64vNVProc )(GLuint index, const GLuint64EXT *v);
typedef void (OSG_APIENTRY * osgGlVertexAttribL2ui64vNVProc )(GLuint index, const GLuint64EXT *v);
typedef void (OSG_APIENTRY * osgGlVertexAttribL3ui64vNVProc )(GLuint index, const GLuint64EXT *v);
typedef void (OSG_APIENTRY * osgGlVertexAttribL4ui64vNVProc )(GLuint index, const GLuint64EXT *v);
typedef void (OSG_APIENTRY * osgGlGetVertexAttribLi64vNVProc )(GLuint index, GLenum pname, GLint64EXT *params);
typedef void (OSG_APIENTRY * osgGlGetVertexAttribLui64vNVProc )(GLuint index, GLenum pname, GLuint64EXT *params);
typedef void (OSG_APIENTRY * osgGlVertexAttribLFormatNVProc )(GLuint index, GLint size, GLenum type, GLsizei stride);
#endif /* GL_NV_vertex_attrib_integer_64bit */

#ifdef GL_NV_vertex_buffer_unified_memory
typedef void (OSG_APIENTRY * osgGlBufferAddressRangeNVProc )(GLenum pname, GLuint index, GLuint64EXT address, GLsizeiptr length);
typedef void (OSG_APIENTRY * osgGlVertexFormatNVProc )(GLint size, GLenum type, GLsizei stride);
typedef void (OSG_APIENTRY * osgGlNormalFormatNVProc )(GLenum type, GLsizei stride);
typedef void (OSG_APIENTRY * osgGlColorFormatNVProc )(GLint size, GLenum type, GLsizei stride);
typedef void (OSG_APIENTRY * osgGlIndexFormatNVProc )(GLenum type, GLsizei stride);
typedef void (OSG_APIENTRY * osgGlTexCoordFormatNVProc )(GLint size, GLenum type, GLsizei stride);
typedef void (OSG_APIENTRY * osgGlEdgeFlagFormatNVProc )(GLsizei stride);
typedef void (OSG_APIENTRY * osgGlSecondaryColorFormatNVProc )(GLint size, GLenum type, GLsizei stride);
typedef void (OSG_APIENTRY * osgGlFogCoordFormatNVProc )(GLenum type, GLsizei stride);
typedef void (OSG_APIENTRY * osgGlVertexAttribFormatNVProc )(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride);
typedef void (OSG_APIENTRY * osgGlVertexAttribIFormatNVProc )(GLuint index, GLint size, GLenum type, GLsizei stride);
typedef void (OSG_APIENTRY * osgGlGetIntegerui64i_vNVProc )(GLenum value, GLuint index, GLuint64EXT *result);
#endif /* GL_NV_vertex_buffer_unified_memory */

#ifdef GL_NV_vertex_program
typedef GLboolean (OSG_APIENTRY * osgGlAreProgramsResidentNVProc )(GLsizei n, const GLuint *programs, GLboolean *residences);
typedef void (OSG_APIENTRY * osgGlBindProgramNVProc )(GLenum target, GLuint id);
typedef void (OSG_APIENTRY * osgGlDeleteProgramsNVProc )(GLsizei n, const GLuint *programs);
typedef void (OSG_APIENTRY * osgGlExecuteProgramNVProc )(GLenum target, GLuint id, const GLfloat *params);
typedef void (OSG_APIENTRY * osgGlGenProgramsNVProc )(GLsizei n, GLuint *programs);
typedef void (OSG_APIENTRY * osgGlGetProgramParameterdvNVProc )(GLenum target, GLuint index, GLenum pname, GLdouble *params);
typedef void (OSG_APIENTRY * osgGlGetProgramParameterfvNVProc )(GLenum target, GLuint index, GLenum pname, GLfloat *params);
typedef void (OSG_APIENTRY * osgGlGetProgramivNVProc )(GLuint id, GLenum pname, GLint *params);
typedef void (OSG_APIENTRY * osgGlGetProgramStringNVProc )(GLuint id, GLenum pname, GLubyte *program);
typedef void (OSG_APIENTRY * osgGlGetTrackMatrixivNVProc )(GLenum target, GLuint address, GLenum pname, GLint *params);
typedef void (OSG_APIENTRY * osgGlGetVertexAttribdvNVProc )(GLuint index, GLenum pname, GLdouble *params);
typedef void (OSG_APIENTRY * osgGlGetVertexAttribfvNVProc )(GLuint index, GLenum pname, GLfloat *params);
typedef void (OSG_APIENTRY * osgGlGetVertexAttribivNVProc )(GLuint index, GLenum pname, GLint *params);
typedef void (OSG_APIENTRY * osgGlGetVertexAttribPointervNVProc )(GLuint index, GLenum pname, void **pointer);
typedef GLboolean (OSG_APIENTRY * osgGlIsProgramNVProc )(GLuint id);
typedef void (OSG_APIENTRY * osgGlLoadProgramNVProc )(GLenum target, GLuint id, GLsizei len, const GLubyte *program);
typedef void (OSG_APIENTRY * osgGlProgramParameter4dNVProc )(GLenum target, GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
typedef void (OSG_APIENTRY * osgGlProgramParameter4dvNVProc )(GLenum target, GLuint index, const GLdouble *v);
typedef void (OSG_APIENTRY * osgGlProgramParameter4fNVProc )(GLenum target, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
typedef void (OSG_APIENTRY * osgGlProgramParameter4fvNVProc )(GLenum target, GLuint index, const GLfloat *v);
typedef void (OSG_APIENTRY * osgGlProgramParameters4dvNVProc )(GLenum target, GLuint index, GLsizei count, const GLdouble *v);
typedef void (OSG_APIENTRY * osgGlProgramParameters4fvNVProc )(GLenum target, GLuint index, GLsizei count, const GLfloat *v);
typedef void (OSG_APIENTRY * osgGlRequestResidentProgramsNVProc )(GLsizei n, const GLuint *programs);
typedef void (OSG_APIENTRY * osgGlTrackMatrixNVProc )(GLenum target, GLuint address, GLenum matrix, GLenum transform);
typedef void (OSG_APIENTRY * osgGlVertexAttribPointerNVProc )(GLuint index, GLint fsize, GLenum type, GLsizei stride, const void *pointer);
typedef void (OSG_APIENTRY * osgGlVertexAttrib1dNVProc )(GLuint index, GLdouble x);
typedef void (OSG_APIENTRY * osgGlVertexAttrib1dvNVProc )(GLuint index, const GLdouble *v);
typedef void (OSG_APIENTRY * osgGlVertexAttrib1fNVProc )(GLuint index, GLfloat x);
typedef void (OSG_APIENTRY * osgGlVertexAttrib1fvNVProc )(GLuint index, const GLfloat *v);
typedef void (OSG_APIENTRY * osgGlVertexAttrib1sNVProc )(GLuint index, GLshort x);
typedef void (OSG_APIENTRY * osgGlVertexAttrib1svNVProc )(GLuint index, const GLshort *v);
typedef void (OSG_APIENTRY * osgGlVertexAttrib2dNVProc )(GLuint index, GLdouble x, GLdouble y);
typedef void (OSG_APIENTRY * osgGlVertexAttrib2dvNVProc )(GLuint index, const GLdouble *v);
typedef void (OSG_APIENTRY * osgGlVertexAttrib2fNVProc )(GLuint index, GLfloat x, GLfloat y);
typedef void (OSG_APIENTRY * osgGlVertexAttrib2fvNVProc )(GLuint index, const GLfloat *v);
typedef void (OSG_APIENTRY * osgGlVertexAttrib2sNVProc )(GLuint index, GLshort x, GLshort y);
typedef void (OSG_APIENTRY * osgGlVertexAttrib2svNVProc )(GLuint index, const GLshort *v);
typedef void (OSG_APIENTRY * osgGlVertexAttrib3dNVProc )(GLuint index, GLdouble x, GLdouble y, GLdouble z);
typedef void (OSG_APIENTRY * osgGlVertexAttrib3dvNVProc )(GLuint index, const GLdouble *v);
typedef void (OSG_APIENTRY * osgGlVertexAttrib3fNVProc )(GLuint index, GLfloat x, GLfloat y, GLfloat z);
typedef void (OSG_APIENTRY * osgGlVertexAttrib3fvNVProc )(GLuint index, const GLfloat *v);
typedef void (OSG_APIENTRY * osgGlVertexAttrib3sNVProc )(GLuint index, GLshort x, GLshort y, GLshort z);
typedef void (OSG_APIENTRY * osgGlVertexAttrib3svNVProc )(GLuint index, const GLshort *v);
typedef void (OSG_APIENTRY * osgGlVertexAttrib4dNVProc )(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
typedef void (OSG_APIENTRY * osgGlVertexAttrib4dvNVProc )(GLuint index, const GLdouble *v);
typedef void (OSG_APIENTRY * osgGlVertexAttrib4fNVProc )(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
typedef void (OSG_APIENTRY * osgGlVertexAttrib4fvNVProc )(GLuint index, const GLfloat *v);
typedef void (OSG_APIENTRY * osgGlVertexAttrib4sNVProc )(GLuint index, GLshort x, GLshort y, GLshort z, GLshort w);
typedef void (OSG_APIENTRY * osgGlVertexAttrib4svNVProc )(GLuint index, const GLshort *v);
typedef void (OSG_APIENTRY * osgGlVertexAttrib4ubNVProc )(GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w);
typedef void (OSG_APIENTRY * osgGlVertexAttrib4ubvNVProc )(GLuint index, const GLubyte *v);
typedef void (OSG_APIENTRY * osgGlVertexAttribs1dvNVProc )(GLuint index, GLsizei count, const GLdouble *v);
typedef void (OSG_APIENTRY * osgGlVertexAttribs1fvNVProc )(GLuint index, GLsizei count, const GLfloat *v);
typedef void (OSG_APIENTRY * osgGlVertexAttribs1svNVProc )(GLuint index, GLsizei count, const GLshort *v);
typedef void (OSG_APIENTRY * osgGlVertexAttribs2dvNVProc )(GLuint index, GLsizei count, const GLdouble *v);
typedef void (OSG_APIENTRY * osgGlVertexAttribs2fvNVProc )(GLuint index, GLsizei count, const GLfloat *v);
typedef void (OSG_APIENTRY * osgGlVertexAttribs2svNVProc )(GLuint index, GLsizei count, const GLshort *v);
typedef void (OSG_APIENTRY * osgGlVertexAttribs3dvNVProc )(GLuint index, GLsizei count, const GLdouble *v);
typedef void (OSG_APIENTRY * osgGlVertexAttribs3fvNVProc )(GLuint index, GLsizei count, const GLfloat *v);
typedef void (OSG_APIENTRY * osgGlVertexAttribs3svNVProc )(GLuint index, GLsizei count, const GLshort *v);
typedef void (OSG_APIENTRY * osgGlVertexAttribs4dvNVProc )(GLuint index, GLsizei count, const GLdouble *v);
typedef void (OSG_APIENTRY * osgGlVertexAttribs4fvNVProc )(GLuint index, GLsizei count, const GLfloat *v);
typedef void (OSG_APIENTRY * osgGlVertexAttribs4svNVProc )(GLuint index, GLsizei count, const GLshort *v);
typedef void (OSG_APIENTRY * osgGlVertexAttribs4ubvNVProc )(GLuint index, GLsizei count, const GLubyte *v);
#endif /* GL_NV_vertex_program */

#ifdef GL_NV_vertex_program1_1
#endif /* GL_NV_vertex_program1_1 */

#ifdef GL_NV_vertex_program2
#endif /* GL_NV_vertex_program2 */

#ifdef GL_NV_vertex_program2_option
#endif /* GL_NV_vertex_program2_option */

#ifdef GL_NV_vertex_program3
#endif /* GL_NV_vertex_program3 */

#ifdef GL_NV_vertex_program4
typedef void (OSG_APIENTRY * osgGlVertexAttribI1iEXTProc )(GLuint index, GLint x);
typedef void (OSG_APIENTRY * osgGlVertexAttribI2iEXTProc )(GLuint index, GLint x, GLint y);
typedef void (OSG_APIENTRY * osgGlVertexAttribI3iEXTProc )(GLuint index, GLint x, GLint y, GLint z);
typedef void (OSG_APIENTRY * osgGlVertexAttribI4iEXTProc )(GLuint index, GLint x, GLint y, GLint z, GLint w);
typedef void (OSG_APIENTRY * osgGlVertexAttribI1uiEXTProc )(GLuint index, GLuint x);
typedef void (OSG_APIENTRY * osgGlVertexAttribI2uiEXTProc )(GLuint index, GLuint x, GLuint y);
typedef void (OSG_APIENTRY * osgGlVertexAttribI3uiEXTProc )(GLuint index, GLuint x, GLuint y, GLuint z);
typedef void (OSG_APIENTRY * osgGlVertexAttribI4uiEXTProc )(GLuint index, GLuint x, GLuint y, GLuint z, GLuint w);
typedef void (OSG_APIENTRY * osgGlVertexAttribI1ivEXTProc )(GLuint index, const GLint *v);
typedef void (OSG_APIENTRY * osgGlVertexAttribI2ivEXTProc )(GLuint index, const GLint *v);
typedef void (OSG_APIENTRY * osgGlVertexAttribI3ivEXTProc )(GLuint index, const GLint *v);
typedef void (OSG_APIENTRY * osgGlVertexAttribI4ivEXTProc )(GLuint index, const GLint *v);
typedef void (OSG_APIENTRY * osgGlVertexAttribI1uivEXTProc )(GLuint index, const GLuint *v);
typedef void (OSG_APIENTRY * osgGlVertexAttribI2uivEXTProc )(GLuint index, const GLuint *v);
typedef void (OSG_APIENTRY * osgGlVertexAttribI3uivEXTProc )(GLuint index, const GLuint *v);
typedef void (OSG_APIENTRY * osgGlVertexAttribI4uivEXTProc )(GLuint index, const GLuint *v);
typedef void (OSG_APIENTRY * osgGlVertexAttribI4bvEXTProc )(GLuint index, const GLbyte *v);
typedef void (OSG_APIENTRY * osgGlVertexAttribI4svEXTProc )(GLuint index, const GLshort *v);
typedef void (OSG_APIENTRY * osgGlVertexAttribI4ubvEXTProc )(GLuint index, const GLubyte *v);
typedef void (OSG_APIENTRY * osgGlVertexAttribI4usvEXTProc )(GLuint index, const GLushort *v);
typedef void (OSG_APIENTRY * osgGlVertexAttribIPointerEXTProc )(GLuint index, GLint size, GLenum type, GLsizei stride, const void *pointer);
typedef void (OSG_APIENTRY * osgGlGetVertexAttribIivEXTProc )(GLuint index, GLenum pname, GLint *params);
typedef void (OSG_APIENTRY * osgGlGetVertexAttribIuivEXTProc )(GLuint index, GLenum pname, GLuint *params);
#endif /* GL_NV_vertex_program4 */

#ifdef GL_NV_video_capture
typedef void (OSG_APIENTRY * osgGlBeginVideoCaptureNVProc )(GLuint video_capture_slot);
typedef void (OSG_APIENTRY * osgGlBindVideoCaptureStreamBufferNVProc )(GLuint video_capture_slot, GLuint stream, GLenum frame_region, GLintptrARB offset);
typedef void (OSG_APIENTRY * osgGlBindVideoCaptureStreamTextureNVProc )(GLuint video_capture_slot, GLuint stream, GLenum frame_region, GLenum target, GLuint texture);
typedef void (OSG_APIENTRY * osgGlEndVideoCaptureNVProc )(GLuint video_capture_slot);
typedef void (OSG_APIENTRY * osgGlGetVideoCaptureivNVProc )(GLuint video_capture_slot, GLenum pname, GLint *params);
typedef void (OSG_APIENTRY * osgGlGetVideoCaptureStreamivNVProc )(GLuint video_capture_slot, GLuint stream, GLenum pname, GLint *params);
typedef void (OSG_APIENTRY * osgGlGetVideoCaptureStreamfvNVProc )(GLuint video_capture_slot, GLuint stream, GLenum pname, GLfloat *params);
typedef void (OSG_APIENTRY * osgGlGetVideoCaptureStreamdvNVProc )(GLuint video_capture_slot, GLuint stream, GLenum pname, GLdouble *params);
typedef GLenum (OSG_APIENTRY * osgGlVideoCaptureNVProc )(GLuint video_capture_slot, GLuint *sequence_num, GLuint64EXT *capture_time);
typedef void (OSG_APIENTRY * osgGlVideoCaptureStreamParameterivNVProc )(GLuint video_capture_slot, GLuint stream, GLenum pname, const GLint *params);
typedef void (OSG_APIENTRY * osgGlVideoCaptureStreamParameterfvNVProc )(GLuint video_capture_slot, GLuint stream, GLenum pname, const GLfloat *params);
typedef void (OSG_APIENTRY * osgGlVideoCaptureStreamParameterdvNVProc )(GLuint video_capture_slot, GLuint stream, GLenum pname, const GLdouble *params);
#endif /* GL_NV_video_capture */

#ifdef GL_NV_viewport_array2
#endif /* GL_NV_viewport_array2 */

#ifdef GL_OML_interlace
#endif /* GL_OML_interlace */

#ifdef GL_OML_resample
#endif /* GL_OML_resample */

#ifdef GL_OML_subsample
#endif /* GL_OML_subsample */

#ifdef GL_OVR_multiview
typedef void (OSG_APIENTRY * osgGlFramebufferTextureMultiviewOVRProc )(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint baseViewIndex, GLsizei numViews);
#endif /* GL_OVR_multiview */

#ifdef GL_OVR_multiview2
#endif /* GL_OVR_multiview2 */

#ifdef GL_PGI_misc_hints
typedef void (OSG_APIENTRY * osgGlHintPGIProc )(GLenum target, GLint mode);
#endif /* GL_PGI_misc_hints */

#ifdef GL_PGI_vertex_hints
#endif /* GL_PGI_vertex_hints */

#ifdef GL_REND_screen_coordinates
#endif /* GL_REND_screen_coordinates */

#ifdef GL_S3_s3tc
#endif /* GL_S3_s3tc */

#ifdef GL_SGIS_detail_texture
typedef void (OSG_APIENTRY * osgGlDetailTexFuncSGISProc )(GLenum target, GLsizei n, const GLfloat *points);
typedef void (OSG_APIENTRY * osgGlGetDetailTexFuncSGISProc )(GLenum target, GLfloat *points);
#endif /* GL_SGIS_detail_texture */

#ifdef GL_SGIS_fog_function
typedef void (OSG_APIENTRY * osgGlFogFuncSGISProc )(GLsizei n, const GLfloat *points);
typedef void (OSG_APIENTRY * osgGlGetFogFuncSGISProc )(GLfloat *points);
#endif /* GL_SGIS_fog_function */

#ifdef GL_SGIS_generate_mipmap
#endif /* GL_SGIS_generate_mipmap */

#ifdef GL_SGIS_multisample
typedef void (OSG_APIENTRY * osgGlSampleMaskSGISProc )(GLclampf value, GLboolean invert);
typedef void (OSG_APIENTRY * osgGlSamplePatternSGISProc )(GLenum pattern);
#endif /* GL_SGIS_multisample */

#ifdef GL_SGIS_pixel_texture
typedef void (OSG_APIENTRY * osgGlPixelTexGenParameteriSGISProc )(GLenum pname, GLint param);
typedef void (OSG_APIENTRY * osgGlPixelTexGenParameterivSGISProc )(GLenum pname, const GLint *params);
typedef void (OSG_APIENTRY * osgGlPixelTexGenParameterfSGISProc )(GLenum pname, GLfloat param);
typedef void (OSG_APIENTRY * osgGlPixelTexGenParameterfvSGISProc )(GLenum pname, const GLfloat *params);
typedef void (OSG_APIENTRY * osgGlGetPixelTexGenParameterivSGISProc )(GLenum pname, GLint *params);
typedef void (OSG_APIENTRY * osgGlGetPixelTexGenParameterfvSGISProc )(GLenum pname, GLfloat *params);
#endif /* GL_SGIS_pixel_texture */

#ifdef GL_SGIS_point_line_texgen
#endif /* GL_SGIS_point_line_texgen */

#ifdef GL_SGIS_point_parameters
typedef void (OSG_APIENTRY * osgGlPointParameterfSGISProc )(GLenum pname, GLfloat param);
typedef void (OSG_APIENTRY * osgGlPointParameterfvSGISProc )(GLenum pname, const GLfloat *params);
#endif /* GL_SGIS_point_parameters */

#ifdef GL_SGIS_sharpen_texture
typedef void (OSG_APIENTRY * osgGlSharpenTexFuncSGISProc )(GLenum target, GLsizei n, const GLfloat *points);
typedef void (OSG_APIENTRY * osgGlGetSharpenTexFuncSGISProc )(GLenum target, GLfloat *points);
#endif /* GL_SGIS_sharpen_texture */

#ifdef GL_SGIS_texture4D
typedef void (OSG_APIENTRY * osgGlTexImage4DSGISProc )(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLsizei size4d, GLint border, GLenum format, GLenum type, const void *pixels);
typedef void (OSG_APIENTRY * osgGlTexSubImage4DSGISProc )(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint woffset, GLsizei width, GLsizei height, GLsizei depth, GLsizei size4d, GLenum format, GLenum type, const void *pixels);
#endif /* GL_SGIS_texture4D */

#ifdef GL_SGIS_texture_border_clamp
#endif /* GL_SGIS_texture_border_clamp */

#ifdef GL_SGIS_texture_color_mask
typedef void (OSG_APIENTRY * osgGlTextureColorMaskSGISProc )(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
#endif /* GL_SGIS_texture_color_mask */

#ifdef GL_SGIS_texture_edge_clamp
#endif /* GL_SGIS_texture_edge_clamp */

#ifdef GL_SGIS_texture_filter4
typedef void (OSG_APIENTRY * osgGlGetTexFilterFuncSGISProc )(GLenum target, GLenum filter, GLfloat *weights);
typedef void (OSG_APIENTRY * osgGlTexFilterFuncSGISProc )(GLenum target, GLenum filter, GLsizei n, const GLfloat *weights);
#endif /* GL_SGIS_texture_filter4 */

#ifdef GL_SGIS_texture_lod
#endif /* GL_SGIS_texture_lod */

#ifdef GL_SGIS_texture_select
#endif /* GL_SGIS_texture_select */

#ifdef GL_SGIX_async
typedef void (OSG_APIENTRY * osgGlAsyncMarkerSGIXProc )(GLuint marker);
typedef GLint (OSG_APIENTRY * osgGlFinishAsyncSGIXProc )(GLuint *markerp);
typedef GLint (OSG_APIENTRY * osgGlPollAsyncSGIXProc )(GLuint *markerp);
typedef GLuint (OSG_APIENTRY * osgGlGenAsyncMarkersSGIXProc )(GLsizei range);
typedef void (OSG_APIENTRY * osgGlDeleteAsyncMarkersSGIXProc )(GLuint marker, GLsizei range);
typedef GLboolean (OSG_APIENTRY * osgGlIsAsyncMarkerSGIXProc )(GLuint marker);
#endif /* GL_SGIX_async */

#ifdef GL_SGIX_async_histogram
#endif /* GL_SGIX_async_histogram */

#ifdef GL_SGIX_async_pixel
#endif /* GL_SGIX_async_pixel */

#ifdef GL_SGIX_blend_alpha_minmax
#endif /* GL_SGIX_blend_alpha_minmax */

#ifdef GL_SGIX_calligraphic_fragment
#endif /* GL_SGIX_calligraphic_fragment */

#ifdef GL_SGIX_clipmap
#endif /* GL_SGIX_clipmap */

#ifdef GL_SGIX_convolution_accuracy
#endif /* GL_SGIX_convolution_accuracy */

#ifdef GL_SGIX_depth_pass_instrument
#endif /* GL_SGIX_depth_pass_instrument */

#ifdef GL_SGIX_depth_texture
#endif /* GL_SGIX_depth_texture */

#ifdef GL_SGIX_flush_raster
typedef void (OSG_APIENTRY * osgGlFlushRasterSGIXProc )(void);
#endif /* GL_SGIX_flush_raster */

#ifdef GL_SGIX_fog_offset
#endif /* GL_SGIX_fog_offset */

#ifdef GL_SGIX_fragment_lighting
typedef void (OSG_APIENTRY * osgGlFragmentColorMaterialSGIXProc )(GLenum face, GLenum mode);
typedef void (OSG_APIENTRY * osgGlFragmentLightfSGIXProc )(GLenum light, GLenum pname, GLfloat param);
typedef void (OSG_APIENTRY * osgGlFragmentLightfvSGIXProc )(GLenum light, GLenum pname, const GLfloat *params);
typedef void (OSG_APIENTRY * osgGlFragmentLightiSGIXProc )(GLenum light, GLenum pname, GLint param);
typedef void (OSG_APIENTRY * osgGlFragmentLightivSGIXProc )(GLenum light, GLenum pname, const GLint *params);
typedef void (OSG_APIENTRY * osgGlFragmentLightModelfSGIXProc )(GLenum pname, GLfloat param);
typedef void (OSG_APIENTRY * osgGlFragmentLightModelfvSGIXProc )(GLenum pname, const GLfloat *params);
typedef void (OSG_APIENTRY * osgGlFragmentLightModeliSGIXProc )(GLenum pname, GLint param);
typedef void (OSG_APIENTRY * osgGlFragmentLightModelivSGIXProc )(GLenum pname, const GLint *params);
typedef void (OSG_APIENTRY * osgGlFragmentMaterialfSGIXProc )(GLenum face, GLenum pname, GLfloat param);
typedef void (OSG_APIENTRY * osgGlFragmentMaterialfvSGIXProc )(GLenum face, GLenum pname, const GLfloat *params);
typedef void (OSG_APIENTRY * osgGlFragmentMaterialiSGIXProc )(GLenum face, GLenum pname, GLint param);
typedef void (OSG_APIENTRY * osgGlFragmentMaterialivSGIXProc )(GLenum face, GLenum pname, const GLint *params);
typedef void (OSG_APIENTRY * osgGlGetFragmentLightfvSGIXProc )(GLenum light, GLenum pname, GLfloat *params);
typedef void (OSG_APIENTRY * osgGlGetFragmentLightivSGIXProc )(GLenum light, GLenum pname, GLint *params);
typedef void (OSG_APIENTRY * osgGlGetFragmentMaterialfvSGIXProc )(GLenum face, GLenum pname, GLfloat *params);
typedef void (OSG_APIENTRY * osgGlGetFragmentMaterialivSGIXProc )(GLenum face, GLenum pname, GLint *params);
typedef void (OSG_APIENTRY * osgGlLightEnviSGIXProc )(GLenum pname, GLint param);
#endif /* GL_SGIX_fragment_lighting */

#ifdef GL_SGIX_framezoom
typedef void (OSG_APIENTRY * osgGlFrameZoomSGIXProc )(GLint factor);
#endif /* GL_SGIX_framezoom */

#ifdef GL_SGIX_igloo_interface
typedef void (OSG_APIENTRY * osgGlIglooInterfaceSGIXProc )(GLenum pname, const void *params);
#endif /* GL_SGIX_igloo_interface */

#ifdef GL_SGIX_instruments
typedef GLint (OSG_APIENTRY * osgGlGetInstrumentsSGIXProc )(void);
typedef void (OSG_APIENTRY * osgGlInstrumentsBufferSGIXProc )(GLsizei size, GLint *buffer);
typedef GLint (OSG_APIENTRY * osgGlPollInstrumentsSGIXProc )(GLint *marker_p);
typedef void (OSG_APIENTRY * osgGlReadInstrumentsSGIXProc )(GLint marker);
typedef void (OSG_APIENTRY * osgGlStartInstrumentsSGIXProc )(void);
typedef void (OSG_APIENTRY * osgGlStopInstrumentsSGIXProc )(GLint marker);
#endif /* GL_SGIX_instruments */

#ifdef GL_SGIX_interlace
#endif /* GL_SGIX_interlace */

#ifdef GL_SGIX_ir_instrument1
#endif /* GL_SGIX_ir_instrument1 */

#ifdef GL_SGIX_list_priority
typedef void (OSG_APIENTRY * osgGlGetListParameterfvSGIXProc )(GLuint list, GLenum pname, GLfloat *params);
typedef void (OSG_APIENTRY * osgGlGetListParameterivSGIXProc )(GLuint list, GLenum pname, GLint *params);
typedef void (OSG_APIENTRY * osgGlListParameterfSGIXProc )(GLuint list, GLenum pname, GLfloat param);
typedef void (OSG_APIENTRY * osgGlListParameterfvSGIXProc )(GLuint list, GLenum pname, const GLfloat *params);
typedef void (OSG_APIENTRY * osgGlListParameteriSGIXProc )(GLuint list, GLenum pname, GLint param);
typedef void (OSG_APIENTRY * osgGlListParameterivSGIXProc )(GLuint list, GLenum pname, const GLint *params);
#endif /* GL_SGIX_list_priority */

#ifdef GL_SGIX_pixel_texture
typedef void (OSG_APIENTRY * osgGlPixelTexGenSGIXProc )(GLenum mode);
#endif /* GL_SGIX_pixel_texture */

#ifdef GL_SGIX_pixel_tiles
#endif /* GL_SGIX_pixel_tiles */

#ifdef GL_SGIX_polynomial_ffd
typedef void (OSG_APIENTRY * osgGlDeformationMap3dSGIXProc )(GLenum target, GLdouble u1, GLdouble u2, GLint ustride, GLint uorder, GLdouble v1, GLdouble v2, GLint vstride, GLint vorder, GLdouble w1, GLdouble w2, GLint wstride, GLint worder, const GLdouble *points);
typedef void (OSG_APIENTRY * osgGlDeformationMap3fSGIXProc )(GLenum target, GLfloat u1, GLfloat u2, GLint ustride, GLint uorder, GLfloat v1, GLfloat v2, GLint vstride, GLint vorder, GLfloat w1, GLfloat w2, GLint wstride, GLint worder, const GLfloat *points);
typedef void (OSG_APIENTRY * osgGlDeformSGIXProc )(GLbitfield mask);
typedef void (OSG_APIENTRY * osgGlLoadIdentityDeformationMapSGIXProc )(GLbitfield mask);
#endif /* GL_SGIX_polynomial_ffd */

#ifdef GL_SGIX_reference_plane
typedef void (OSG_APIENTRY * osgGlReferencePlaneSGIXProc )(const GLdouble *equation);
#endif /* GL_SGIX_reference_plane */

#ifdef GL_SGIX_resample
#endif /* GL_SGIX_resample */

#ifdef GL_SGIX_scalebias_hint
#endif /* GL_SGIX_scalebias_hint */

#ifdef GL_SGIX_shadow
#endif /* GL_SGIX_shadow */

#ifdef GL_SGIX_shadow_ambient
#endif /* GL_SGIX_shadow_ambient */

#ifdef GL_SGIX_sprite
typedef void (OSG_APIENTRY * osgGlSpriteParameterfSGIXProc )(GLenum pname, GLfloat param);
typedef void (OSG_APIENTRY * osgGlSpriteParameterfvSGIXProc )(GLenum pname, const GLfloat *params);
typedef void (OSG_APIENTRY * osgGlSpriteParameteriSGIXProc )(GLenum pname, GLint param);
typedef void (OSG_APIENTRY * osgGlSpriteParameterivSGIXProc )(GLenum pname, const GLint *params);
#endif /* GL_SGIX_sprite */

#ifdef GL_SGIX_subsample
#endif /* GL_SGIX_subsample */

#ifdef GL_SGIX_tag_sample_buffer
typedef void (OSG_APIENTRY * osgGlTagSampleBufferSGIXProc )(void);
#endif /* GL_SGIX_tag_sample_buffer */

#ifdef GL_SGIX_texture_add_env
#endif /* GL_SGIX_texture_add_env */

#ifdef GL_SGIX_texture_coordinate_clamp
#endif /* GL_SGIX_texture_coordinate_clamp */

#ifdef GL_SGIX_texture_lod_bias
#endif /* GL_SGIX_texture_lod_bias */

#ifdef GL_SGIX_texture_multi_buffer
#endif /* GL_SGIX_texture_multi_buffer */

#ifdef GL_SGIX_texture_scale_bias
#endif /* GL_SGIX_texture_scale_bias */

#ifdef GL_SGIX_vertex_preclip
#endif /* GL_SGIX_vertex_preclip */

#ifdef GL_SGIX_ycrcb
#endif /* GL_SGIX_ycrcb */

#ifdef GL_SGIX_ycrcb_subsample
#endif /* GL_SGIX_ycrcb_subsample */

#ifdef GL_SGIX_ycrcba
#endif /* GL_SGIX_ycrcba */

#ifdef GL_SGI_color_matrix
#endif /* GL_SGI_color_matrix */

#ifdef GL_SGI_color_table
typedef void (OSG_APIENTRY * osgGlColorTableSGIProc )(GLenum target, GLenum internalformat, GLsizei width, GLenum format, GLenum type, const void *table);
typedef void (OSG_APIENTRY * osgGlColorTableParameterfvSGIProc )(GLenum target, GLenum pname, const GLfloat *params);
typedef void (OSG_APIENTRY * osgGlColorTableParameterivSGIProc )(GLenum target, GLenum pname, const GLint *params);
typedef void (OSG_APIENTRY * osgGlCopyColorTableSGIProc )(GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width);
typedef void (OSG_APIENTRY * osgGlGetColorTableSGIProc )(GLenum target, GLenum format, GLenum type, void *table);
typedef void (OSG_APIENTRY * osgGlGetColorTableParameterfvSGIProc )(GLenum target, GLenum pname, GLfloat *params);
typedef void (OSG_APIENTRY * osgGlGetColorTableParameterivSGIProc )(GLenum target, GLenum pname, GLint *params);
#endif /* GL_SGI_color_table */

#ifdef GL_SGI_texture_color_table
#endif /* GL_SGI_texture_color_table */

#ifdef GL_SUNX_constant_data
typedef void (OSG_APIENTRY * osgGlFinishTextureSUNXProc )(void);
#endif /* GL_SUNX_constant_data */

#ifdef GL_SUN_convolution_border_modes
#endif /* GL_SUN_convolution_border_modes */

#ifdef GL_SUN_global_alpha
typedef void (OSG_APIENTRY * osgGlGlobalAlphaFactorbSUNProc )(GLbyte factor);
typedef void (OSG_APIENTRY * osgGlGlobalAlphaFactorsSUNProc )(GLshort factor);
typedef void (OSG_APIENTRY * osgGlGlobalAlphaFactoriSUNProc )(GLint factor);
typedef void (OSG_APIENTRY * osgGlGlobalAlphaFactorfSUNProc )(GLfloat factor);
typedef void (OSG_APIENTRY * osgGlGlobalAlphaFactordSUNProc )(GLdouble factor);
typedef void (OSG_APIENTRY * osgGlGlobalAlphaFactorubSUNProc )(GLubyte factor);
typedef void (OSG_APIENTRY * osgGlGlobalAlphaFactorusSUNProc )(GLushort factor);
typedef void (OSG_APIENTRY * osgGlGlobalAlphaFactoruiSUNProc )(GLuint factor);
#endif /* GL_SUN_global_alpha */

#ifdef GL_SUN_mesh_array
typedef void (OSG_APIENTRY * osgGlDrawMeshArraysSUNProc )(GLenum mode, GLint first, GLsizei count, GLsizei width);
#endif /* GL_SUN_mesh_array */

#ifdef GL_SUN_slice_accum
#endif /* GL_SUN_slice_accum */

#ifdef GL_SUN_triangle_list
typedef void (OSG_APIENTRY * osgGlReplacementCodeuiSUNProc )(GLuint code);
typedef void (OSG_APIENTRY * osgGlReplacementCodeusSUNProc )(GLushort code);
typedef void (OSG_APIENTRY * osgGlReplacementCodeubSUNProc )(GLubyte code);
typedef void (OSG_APIENTRY * osgGlReplacementCodeuivSUNProc )(const GLuint *code);
typedef void (OSG_APIENTRY * osgGlReplacementCodeusvSUNProc )(const GLushort *code);
typedef void (OSG_APIENTRY * osgGlReplacementCodeubvSUNProc )(const GLubyte *code);
typedef void (OSG_APIENTRY * osgGlReplacementCodePointerSUNProc )(GLenum type, GLsizei stride, const void **pointer);
#endif /* GL_SUN_triangle_list */

#ifdef GL_SUN_vertex
typedef void (OSG_APIENTRY * osgGlColor4ubVertex2fSUNProc )(GLubyte r, GLubyte g, GLubyte b, GLubyte a, GLfloat x, GLfloat y);
typedef void (OSG_APIENTRY * osgGlColor4ubVertex2fvSUNProc )(const GLubyte *c, const GLfloat *v);
typedef void (OSG_APIENTRY * osgGlColor4ubVertex3fSUNProc )(GLubyte r, GLubyte g, GLubyte b, GLubyte a, GLfloat x, GLfloat y, GLfloat z);
typedef void (OSG_APIENTRY * osgGlColor4ubVertex3fvSUNProc )(const GLubyte *c, const GLfloat *v);
typedef void (OSG_APIENTRY * osgGlColor3fVertex3fSUNProc )(GLfloat r, GLfloat g, GLfloat b, GLfloat x, GLfloat y, GLfloat z);
typedef void (OSG_APIENTRY * osgGlColor3fVertex3fvSUNProc )(const GLfloat *c, const GLfloat *v);
typedef void (OSG_APIENTRY * osgGlNormal3fVertex3fSUNProc )(GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z);
typedef void (OSG_APIENTRY * osgGlNormal3fVertex3fvSUNProc )(const GLfloat *n, const GLfloat *v);
typedef void (OSG_APIENTRY * osgGlColor4fNormal3fVertex3fSUNProc )(GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z);
typedef void (OSG_APIENTRY * osgGlColor4fNormal3fVertex3fvSUNProc )(const GLfloat *c, const GLfloat *n, const GLfloat *v);
typedef void (OSG_APIENTRY * osgGlTexCoord2fVertex3fSUNProc )(GLfloat s, GLfloat t, GLfloat x, GLfloat y, GLfloat z);
typedef void (OSG_APIENTRY * osgGlTexCoord2fVertex3fvSUNProc )(const GLfloat *tc, const GLfloat *v);
typedef void (OSG_APIENTRY * osgGlTexCoord4fVertex4fSUNProc )(GLfloat s, GLfloat t, GLfloat p, GLfloat q, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
typedef void (OSG_APIENTRY * osgGlTexCoord4fVertex4fvSUNProc )(const GLfloat *tc, const GLfloat *v);
typedef void (OSG_APIENTRY * osgGlTexCoord2fColor4ubVertex3fSUNProc )(GLfloat s, GLfloat t, GLubyte r, GLubyte g, GLubyte b, GLubyte a, GLfloat x, GLfloat y, GLfloat z);
typedef void (OSG_APIENTRY * osgGlTexCoord2fColor4ubVertex3fvSUNProc )(const GLfloat *tc, const GLubyte *c, const GLfloat *v);
typedef void (OSG_APIENTRY * osgGlTexCoord2fColor3fVertex3fSUNProc )(GLfloat s, GLfloat t, GLfloat r, GLfloat g, GLfloat b, GLfloat x, GLfloat y, GLfloat z);
typedef void (OSG_APIENTRY * osgGlTexCoord2fColor3fVertex3fvSUNProc )(const GLfloat *tc, const GLfloat *c, const GLfloat *v);
typedef void (OSG_APIENTRY * osgGlTexCoord2fNormal3fVertex3fSUNProc )(GLfloat s, GLfloat t, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z);
typedef void (OSG_APIENTRY * osgGlTexCoord2fNormal3fVertex3fvSUNProc )(const GLfloat *tc, const GLfloat *n, const GLfloat *v);
typedef void (OSG_APIENTRY * osgGlTexCoord2fColor4fNormal3fVertex3fSUNProc )(GLfloat s, GLfloat t, GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z);
typedef void (OSG_APIENTRY * osgGlTexCoord2fColor4fNormal3fVertex3fvSUNProc )(const GLfloat *tc, const GLfloat *c, const GLfloat *n, const GLfloat *v);
typedef void (OSG_APIENTRY * osgGlTexCoord4fColor4fNormal3fVertex4fSUNProc )(GLfloat s, GLfloat t, GLfloat p, GLfloat q, GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
typedef void (OSG_APIENTRY * osgGlTexCoord4fColor4fNormal3fVertex4fvSUNProc )(const GLfloat *tc, const GLfloat *c, const GLfloat *n, const GLfloat *v);
typedef void (OSG_APIENTRY * osgGlReplacementCodeuiVertex3fSUNProc )(GLuint rc, GLfloat x, GLfloat y, GLfloat z);
typedef void (OSG_APIENTRY * osgGlReplacementCodeuiVertex3fvSUNProc )(const GLuint *rc, const GLfloat *v);
typedef void (OSG_APIENTRY * osgGlReplacementCodeuiColor4ubVertex3fSUNProc )(GLuint rc, GLubyte r, GLubyte g, GLubyte b, GLubyte a, GLfloat x, GLfloat y, GLfloat z);
typedef void (OSG_APIENTRY * osgGlReplacementCodeuiColor4ubVertex3fvSUNProc )(const GLuint *rc, const GLubyte *c, const GLfloat *v);
typedef void (OSG_APIENTRY * osgGlReplacementCodeuiColor3fVertex3fSUNProc )(GLuint rc, GLfloat r, GLfloat g, GLfloat b, GLfloat x, GLfloat y, GLfloat z);
typedef void (OSG_APIENTRY * osgGlReplacementCodeuiColor3fVertex3fvSUNProc )(const GLuint *rc, const GLfloat *c, const GLfloat *v);
typedef void (OSG_APIENTRY * osgGlReplacementCodeuiNormal3fVertex3fSUNProc )(GLuint rc, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z);
typedef void (OSG_APIENTRY * osgGlReplacementCodeuiNormal3fVertex3fvSUNProc )(const GLuint *rc, const GLfloat *n, const GLfloat *v);
typedef void (OSG_APIENTRY * osgGlReplacementCodeuiColor4fNormal3fVertex3fSUNProc )(GLuint rc, GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z);
typedef void (OSG_APIENTRY * osgGlReplacementCodeuiColor4fNormal3fVertex3fvSUNProc )(const GLuint *rc, const GLfloat *c, const GLfloat *n, const GLfloat *v);
typedef void (OSG_APIENTRY * osgGlReplacementCodeuiTexCoord2fVertex3fSUNProc )(GLuint rc, GLfloat s, GLfloat t, GLfloat x, GLfloat y, GLfloat z);
typedef void (OSG_APIENTRY * osgGlReplacementCodeuiTexCoord2fVertex3fvSUNProc )(const GLuint *rc, const GLfloat *tc, const GLfloat *v);
typedef void (OSG_APIENTRY * osgGlReplacementCodeuiTexCoord2fNormal3fVertex3fSUNProc )(GLuint rc, GLfloat s, GLfloat t, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z);
typedef void (OSG_APIENTRY * osgGlReplacementCodeuiTexCoord2fNormal3fVertex3fvSUNProc )(const GLuint *rc, const GLfloat *tc, const GLfloat *n, const GLfloat *v);
typedef void (OSG_APIENTRY * osgGlReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fSUNProc )(GLuint rc, GLfloat s, GLfloat t, GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z);
typedef void (OSG_APIENTRY * osgGlReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fvSUNProc )(const GLuint *rc, const GLfloat *tc, const GLfloat *c, const GLfloat *n, const GLfloat *v);
#endif /* GL_SUN_vertex */

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

#endif

#define OSGGETGLFUNC_P(OGLFUNC, FUNCVAR, FUNCID)                        \
    OSG::FUNCVAR##Proc FUNCVAR = OGLFUNC;

#define OSGGETGLFUNCBYID_P(OGLFUNC, FUNCVAR, FUNCID, WINDOW)            \
    OSG::osgSinkUnusedWarning(WINDOW);                                  \
    OSG::FUNCVAR##Proc FUNCVAR = OGLFUNC;

#define OSGGETGLFUNCBYNAME_P(OGLFUNC, FUNCVAR, FUNCNAME, WINDOW)        \
    OSG::osgSinkUnusedWarning(WINDOW);                                  \
    OSG::FUNCVAR##Proc FUNCVAR = OGLFUNC;
       


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
