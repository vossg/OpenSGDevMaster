/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                 Copyright (C) 2000 by the OpenSG Forum                    *
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

#ifndef _OSGBASEPROFILE_H_
#define _OSGBASEPROFILE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGBaseTypes.h"
#include "OSGGL.h"
#include "OSGMatrix.h"
#include "OSGQuaternion.h"
#include "OSGColor.h"

#define osgFToFX(x) ((GLfixed)((x)*65536.0f))
#define osgONE_FX 0x00010000

//---------------------------------------------------------------------------
//  Defines
//---------------------------------------------------------------------------

OSG_BEGIN_NAMESPACE

#ifdef OSG_GLES

//#define OSG_FLOAT_PROFILE

#ifdef OSG_FLOAT_PROFILE

namespace GLP
{
    static inline 
    void glMaterialf (GLenum face, GLenum pname, GLfloat param)
    {
        GLfixed fixParam = osgFToFX(param);

        ::glMaterialx(face, pname, fixParam);
    }

    static inline
    void glMaterialfv(GLenum face, GLenum pname, const GLfloat *params)
    {
        GLfixed fixParams[4];

        fixParams[0] = osgFToFX(params[0]);
        fixParams[1] = osgFToFX(params[1]);
        fixParams[2] = osgFToFX(params[2]);
        fixParams[3] = osgFToFX(params[3]);

        ::glMaterialxv(face, pname, fixParams);
    }

    static inline
    void glColor4fv(const GLfloat *v)
    {
        ::glColor4x(osgFToFX(v[0]),
                    osgFToFX(v[1]),
                    osgFToFX(v[2]),
                    osgFToFX(v[3]));
    }

    static inline
    void glLightf (GLenum light, GLenum pname, GLfloat param)
    {
        GLfixed fixParam = osgFToFX(param);

        ::glLightx(light, pname, fixParam);
    }

    static inline
    void glLightfv (GLenum light, GLenum pname, const GLfloat *params)
    {
        GLfixed fixParams[4];

        fixParams[0] = osgFToFX(params[0]);
        fixParams[1] = osgFToFX(params[1]);
        fixParams[2] = osgFToFX(params[2]);

        if(pname != GL_SPOT_DIRECTION)
        {
            fixParams[3] = osgFToFX(params[3]);
        }

        ::glLightxv(light, pname, fixParams);
    }

    static inline
    void glClearColor(GLclampf r, GLclampf g, GLclampf b, GLclampf a)
    {
        ::glClearColorx(osgFToFX(r), 
                        osgFToFX(g), 
                        osgFToFX(b), 
                        osgFToFX(a));
    }

    static inline
    void glLoadMatrixf (const GLfloat *m)
    {
        GLfixed mf[16];

        for(UInt32 i = 0; i < 16; ++i)
        {
            mf[i] = osgFToFX(m[i]);
        }

        ::glLoadMatrixx(mf);
    }
};

#else

namespace GLP
{
    static inline
    void glMaterialf (GLenum face, GLenum pname, Fixed32 param)
    {

        ::glMaterialx(face, pname, param.getValue());
    }

    static inline
    void glMaterialfv(      GLenum   face, 
                            GLenum   pname, 
                      const Fixed32 *params)
    {
        ::glMaterialxv(face, pname, reinterpret_cast<const GLfixed *>(params));
    }

    static inline
    void glColor4fv(const Fixed32 *v)
    {
        ::glColor4x(v[0].getValue(),
                    v[1].getValue(),
                    v[2].getValue(),
                    v[3].getValue());
    }

    static inline
    void glLightf (GLenum light, GLenum pname, Fixed32 param)
    {
        ::glLightx(light, pname, param.getValue());
    }

    static inline
    void glLightfv (GLenum light, GLenum pname, const Fixed32 *params)
    {
        ::glLightxv(light, pname, reinterpret_cast<const GLfixed *>(params));
    }

    static inline
    void glClearColor(Fixed32 r, 
                             Fixed32 g, 
                             Fixed32 b, 
                             Fixed32 a)
    {
        ::glClearColorx(r.getValue(), 
                        g.getValue(), 
                        b.getValue(), 
                        a.getValue());
    }

    static inline
    void glLoadMatrixf (const Fixed32 *m)
    {
        ::glLoadMatrixx(reinterpret_cast<const GLfixed *>(m));
    }
};
#endif

#else

namespace GLP
{
    static inline
    void glMaterialf (GLenum face, GLenum pname, GLfloat param)
    {
        ::glMaterialf(face, pname, param);
    }

    static inline
    void glMaterialfv(GLenum face, GLenum pname, const GLfloat *params)
    {
        ::glMaterialfv(face, pname, params);
    }

    static inline
    void glColor4fv(const GLfloat *v)
    {
        ::glColor4fv(v);
    }

    static inline
    void glLightf (GLenum light, GLenum pname, GLfloat param)
    {
        ::glLightf(light, pname, param);
    }

    static inline
    void glLightfv (GLenum light, GLenum pname, const GLfloat *params)
    {
        ::glLightfv(light, pname, params);
    }

    static inline
    void glClearColor(GLclampf r, GLclampf g, GLclampf b, GLclampf a)
    {
        ::glClearColor(r, g, b, a);
    }

    static inline
    void glLoadMatrixf (const GLfloat *m)
    {
        ::glLoadMatrixf(m);
    }
};

#endif

OSG_END_NAMESPACE

#endif /* _OSGBASEPROFILE_H_ */
