/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                Copyright (C) 2011 by the OpenSG Forum                     *
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

#ifndef _OSGGLXFUNCPROTOS_H_
#define _OSGGLXFUNCPROTOS_H_

#include "OSGConfig.h"

#ifdef OSG_USE_GLX

#if defined(OSG_USE_OGL3_PROTOS) || defined(OSG_USE_OGL4_PROTOS)
//# include <GL3/glx3.h>
# include <GLArb/glxarb.h>
#else
# include <GL/glx.h>
#endif

OSG_BEGIN_NAMESPACE

#ifndef DOXYGEN_SHOULD_SKIP_THIS

/*! \}                                                                       */
/*---------------------------------------------------------------------------*/
/*! \name FrameBuffer Config                                                 */
/*! \ingroup GrpBaseBaseGLFunc                                               */
/*! \{                                                                       */

typedef GLXFBConfig *(* osgGlxChooseFBConfigProc)(      Display *dpy, 
                                                        int      screen, 
                                                  const int     *attrib_list, 
                                                        int     *nelements);

typedef GLXContext (*osgGlxCreateContextAttribsARBProc)(
          Display     *dpy,
          GLXFBConfig  config,
          GLXContext   share_context,
          Bool         direct,
    const int         *attrib_list);

/*! \}                                                                       */
/*---------------------------------------------------------------------------*/

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

OSG_END_NAMESPACE

#endif /* OSG_USE_GLX */

#endif /* _OSGGLXFUNCPROTOS_H_ */
