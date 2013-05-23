/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                   Copyright (C) 2013 by the OpenSG Forum                  *
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

#include "OSGOSBShaderParameterIntElement.h"

OSG_BEGIN_NAMESPACE

/*-------------------------------------------------------------------------*/
/* OSBShaderParameterElement                                               */
/*-------------------------------------------------------------------------*/

/*! Abstract base class for ShaderParamter${Type}Elements that handle 1.x
    shader uniforms.
 */

/*-------------------------------------------------------------------------*/
/* Constructor                                                             */

OSBShaderParameterElement::OSBShaderParameterElement(
    OSBRootElement *root, UInt16 version)
    : Inherited(root, version)
{
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

OSBShaderParameterElement::~OSBShaderParameterElement(void)
{
}

/*-------------------------------------------------------------------------*/
/* Access                                                                  */

const Char8*
OSBShaderParameterElement::getName(void) const
{
    return _name.getValue().c_str();
}

OSG_END_NAMESPACE
