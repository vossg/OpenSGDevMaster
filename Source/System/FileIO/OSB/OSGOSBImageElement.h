/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                   Copyright (C) 2007 by the OpenSG Forum                  *
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

#ifndef _OSGOSBIMAGEELEMENT_H_
#define _OSGOSBIMAGEELEMENT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGFileIODef.h"
#include "OSGOSBCommonElement.h"
#include "OSGOSBElementFactoryHelper.h"

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpFileIOOSB
    \nohierarchy
 */

class OSG_FILEIO_DLLMAPPING OSBImageElement : public OSBCommonElement
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
    /*! \{                                                                 */

    typedef OSBCommonElement Inherited;
    typedef OSBImageElement  Self;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constructor                                                  */
    /*! \{                                                                 */

    OSBImageElement(OSBRootElement *root);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Destructor                                                   */
    /*! \{                                                                 */

    virtual ~OSBImageElement(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Reading                                                      */
    /*! \{                                                                 */

    virtual void read    (const std::string &typeName);
    virtual void postRead(      void                 );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Writing                                                      */
    /*! \{                                                                 */

    virtual void preWrite(FieldContainer * const);
    virtual void write   (void                  );

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:
    /*!\brief prohibit default function (move to 'public' if needed)       */
    OSBImageElement(const OSBImageElement &source);
    /*!\brief prohibit default function (move to 'public' if needed)       */
    void operator =(const OSBImageElement &source);

    /*---------------------------------------------------------------------*/
    /*! \name Reading Helper Functions                                     */
    /*! \{                                                                 */

    void readCompressedPixelData(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Writing Helper Functions                                     */
    /*! \{                                                                 */

    void writeCompressedPixelData(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

    bool   _hasJPEGSupport;
    UInt16 _version;

    /*---------------------------------------------------------------------*/

    static OSBElementRegistrationHelper<OSBImageElement> _regHelper;

    static const UInt8 FlagPixelDataCompressedMask = 0x01;
    static const UInt8 FlagPixelDataCompressed     = 0x01;
    static const UInt8 FlagPixelDataOutOfLineMask  = 0x02;
    static const UInt8 FlagPixelDataOutOfLine      = 0x02;
};

OSG_END_NAMESPACE

#endif /* _OSGOSBIMAGEELEMENT_H_ */
