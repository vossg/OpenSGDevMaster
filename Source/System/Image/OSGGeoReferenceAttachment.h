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

#ifndef _OSGGEOREFERENCEATTACHMENT_H_
#define _OSGGEOREFERENCEATTACHMENT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGGeoReferenceAttachmentBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief GeoReferenceAttachment class. See \ref
    PageSystemGeoReferenceAttachment for a description.
    \ingroup GrpSystemImageHelper
    \ingroup GrpLibOSGSystem
    \includebasedoc
*/

class OSG_SYSTEM_DLLMAPPING GeoReferenceAttachment : 
    public GeoReferenceAttachmentBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef GeoReferenceAttachmentBase Inherited;
    typedef GeoReferenceAttachment     Self;

    enum Datum
    {
        UnknownDatum = 0x0000,
        WGS84        = 0x0001
    };

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin,
                         BitVector         details    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    void setupWGS84Datum(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in GeoReferenceAttachmentBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    GeoReferenceAttachment(void);
    GeoReferenceAttachment(const GeoReferenceAttachment &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~GeoReferenceAttachment(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class GeoReferenceAttachmentBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const GeoReferenceAttachment &source);
};

typedef GeoReferenceAttachment *GeoReferenceAttachmentP;

OSG_END_NAMESPACE

#include "OSGGeoReferenceAttachmentBase.inl"
#include "OSGGeoReferenceAttachment.inl"

#endif /* _OSGGEOREFERENCEATTACHMENT_H_ */
