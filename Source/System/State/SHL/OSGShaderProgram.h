/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
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

#ifndef _OSGSHADERPROGRAM_H_
#define _OSGSHADERPROGRAM_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGSHLChunk.h"

OSG_BEGIN_NAMESPACE

/*! \brief ShaderProgram class. See \ref
           PageSystemShaderProgram for a description.
*/

class ShaderProgram
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef ShaderProgram     Self;

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    static UInt32 getFuncIdUniform1i         (void);

    static UInt32 getFuncIdUniform1f         (void);

    static UInt32 getFuncIdUniform1iv        (void);
    static UInt32 getFuncIdUniform2iv        (void);
    static UInt32 getFuncIdUniform3iv        (void);
    static UInt32 getFuncIdUniform4iv        (void);

    static UInt32 getFuncIdUniform1fv        (void);
    static UInt32 getFuncIdUniform2fv        (void);
    static UInt32 getFuncIdUniform3fv        (void);
    static UInt32 getFuncIdUniform4fv        (void);

    static UInt32 getFuncIdUniformMatrix4fv  (void);

    static UInt32 getFuncIdGetUniformiv      (void);
    static UInt32 getFuncIdGetUniformfv      (void);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*==========================  PRIVATE  ================================*/

  private:
};


OSG_END_NAMESPACE

#include "OSGShaderProgram.inl"

#endif /* _OSGSHADERPROGRAM_H_ */
