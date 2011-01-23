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

#ifndef _OSGFIELD_H_
#define _OSGFIELD_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGBaseTypes.h"
#include "OSGFieldForwards.h"

#include <string>

OSG_BEGIN_NAMESPACE

/*! Base class for all fields
    \ingroup GrpBaseField
    \ingroup GrpLibOSGBase 
 */

class OSG_BASE_DLLMAPPING Field
{
    /*==========================  PUBLIC  =================================*/

  public:

    static const UInt32 MFShareMask      = 0x000F;
    static const UInt32 FLocalMask       = 0x00F0;
    static const UInt32 FAccessMask      = 0x0F00;

    static const UInt32 MFSharedSync     = 0x0000;
    static const UInt32 MFCopySync       = 0x0001; 
    static const UInt32 MFNullCheckSync  = 0x0002;

    static const UInt32 FGlobal          = 0x0000;
    static const UInt32 FThreadLocal     = 0x0010;
    static const UInt32 FClusterLocal    = 0x0020;

    static const UInt32 FStdAccess       = 0x0100;
    static const UInt32 FNullCheckAccess = 0x0200;
    static const UInt32 FCustomAccess    = 0x0400;
    
    
    static const UInt32 MFDefaultFlags   = 0x0000;

    static const UInt32 SFDefaultFlags   = 0x0000;

    static const UInt32  FDefaultFlags   = 0x0000;

    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    ~Field(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   String IO                                  */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Set                                     */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    Field(void);
    Field(const Field &source);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const Field &source);
};

OSG_END_NAMESPACE

#endif /* _OSGFIELD_HPP_ */


