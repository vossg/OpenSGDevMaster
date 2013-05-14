/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                     Copyright 2000-2002 by OpenSG Forum                   *
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

OSG_BEGIN_NAMESPACE

inline
void HDRStage::renderQuad(Real32 rTexScale)
{
    glBegin(GL_QUADS);
    {
        glTexCoord2f(0.00,      0.00     );
        glVertex2f  (0.00,      0.00     );
        
        glTexCoord2f(rTexScale, 0.00     );
        glVertex2f  (1.00,      0.00     );
        
        glTexCoord2f(rTexScale, rTexScale);
        glVertex2f  (1.00,      1.00     );
        
        glTexCoord2f(0.00,      rTexScale);
        glVertex2f  (0.00,      1.00     );
    }
    glEnd();
}

inline
void HDRStage::renderQuad(Real32 rMinTex,
                          Real32 rMaxTex)
{
    glBegin(GL_QUADS);
    {
        glTexCoord2f(rMinTex, rMinTex);
        glVertex2f  (0.00,    0.00   );
        
        glTexCoord2f(rMaxTex, rMinTex);
        glVertex2f  (1.00,    0.00   );
        
        glTexCoord2f(rMaxTex, rMaxTex);
        glVertex2f  (1.00,    1.00   );
        
        glTexCoord2f(rMinTex, rMaxTex);
        glVertex2f  (0.00,    1.00   );
    }
    glEnd();
}

OSG_END_NAMESPACE
