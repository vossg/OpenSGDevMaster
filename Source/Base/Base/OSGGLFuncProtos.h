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

#ifndef OSG_EMBEDDED

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#include "OSGGL.h"
#endif

OSG_BEGIN_NAMESPACE

/*---------------------------------------------------------------------------*/
/*! shader                                                                   */


typedef GLuint (OSG_APIENTRY * OSGglCreateShaderProc )(      GLenum    );
typedef void   (OSG_APIENTRY * OSGglDeleteShaderProc )(      GLuint    );
typedef void   (OSG_APIENTRY * OSGglShaderSourceProc )(      GLuint, 
                                                             GLsizei, 
                                                       const GLchar  **, 
                                                       const GLint   * );

typedef void   (OSG_APIENTRY * OSGglCompileShaderProc)(      GLuint    );

typedef void   (OSG_APIENTRY * OSGglAttachShaderProc )(      GLuint, 
                                                             GLuint    );

typedef void   (OSG_APIENTRY * OSGglGetShaderivProc  )(      GLuint, 
                                                             GLenum, 
                                                             GLint   * );
typedef void   (OSG_APIENTRY * 
                           OSGglGetShaderInfoLogProc )(      GLuint, 
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

/*---------------------------------------------------------------------------*/
/*! shader uniform vars                                                      */

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

/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*! framebuffer objects                                                      */

typedef void (OSG_APIENTRY *OSGglGenerateMipmapEXTProc)(GLenum);

/*---------------------------------------------------------------------------*/

#ifdef OSG_DEBUG

#define OSGGETGLFUNC(FUNCTYPE, FUNCVAR, FUNCID)                         \
 FUNCTYPE FUNCVAR =                                                     \
    reinterpret_cast<FUNCTYPE>(                                         \
        pEnv->getWindow()->getFunction(FUNCID));                        \
                                                                        \
 if(FUNCVAR == NULL)                                                    \
    fprintf(stderr, "Func %s of type %s NULL\n", #FUNCVAR, #FUNCTYPE)
        
        
#else

#define OSGGETGLFUNC(FUNCTYPE, FUNCVAR, FUNCID)                         \
    FUNCTYPE FUNCVAR =                                                  \
        reinterpret_cast<FUNCTYPE>(                                     \
            pEnv->getWindow()->getFunction(FUNCID))

#endif


OSG_END_NAMESPACE

#endif /* OSG_EMBEDDED) */

#endif /* _OSGGLFUNCPROTOS_H_ */
