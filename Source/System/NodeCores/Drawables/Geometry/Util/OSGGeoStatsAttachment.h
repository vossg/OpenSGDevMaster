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

#ifndef _OSGGEOSTATSATTACHMENT_H_
#define _OSGGEOSTATSATTACHMENT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGGeometry.h"
#include "OSGGeoStatsAttachmentBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief GeoStatsAttachment class. See \ref 
           PageSystemGeoStatsAttachment for a description.
*/

class OSG_SYSTEM_DLLMAPPING GeoStatsAttachment : public GeoStatsAttachmentBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef GeoStatsAttachmentBase Inherited;
    typedef GeoStatsAttachment     Self;

    typedef PointerBuilder<GeoStatsAttachment>::ObjPtr           ObjPtr;
    typedef PointerBuilder<GeoStatsAttachment>::ObjPtrConst      ObjPtrConst;

    typedef PointerBuilder<GeoStatsAttachment>::ObjConstPtr      ObjConstPtr;
    typedef PointerBuilder<GeoStatsAttachment>::ObjConstPtrConst ObjConstPtrConst;

    typedef PointerBuilder<GeoStatsAttachment>::ObjPtrArg        ObjPtrArg;
    typedef PointerBuilder<GeoStatsAttachment>::ObjPtrConstArg   ObjPtrConstArg;

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField, 
                         UInt32            origin    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector  bvFlags  = 0) const;


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Creation                                 */
    /*! \{                                                                 */

    void                            reset(void);

    void                            calc(GeometryPtrArg geo);

    static GeoStatsAttachmentPtr    calcStatic(GeometryPtrArg geo);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Access                                   */
    /*! \{                                                                 */

    static GeoStatsAttachmentPtr    get(AttachmentContainerPtr  arg);

    static GeoStatsAttachmentPtr    get(AttachmentContainer    *arg);


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Updating                                  */
    /*! \{                                                                 */

    static GeoStatsAttachmentPtr addTo(AttachmentContainerPtr obj);

    void attachTo(AttachmentContainerPtr obj);

    void validate(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Operators                                 */
    /*! \{                                                                 */

    void operator +=(GeoStatsAttachmentPtr arg);
    void operator -=(GeoStatsAttachmentPtr arg);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in GeoStatsAttachmentBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    GeoStatsAttachment(void);
    GeoStatsAttachment(const GeoStatsAttachment &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~GeoStatsAttachment(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Update Helper                               */
    /*! \{                                                                 */
    
    static void invalidateFunctor(FieldContainerPtrArg obj,
                                  ConstFieldMaskArg mask);
    
    static void invalidate(FieldContainerPtrArg obj);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class GeoStatsAttachmentBase;

    template<class ContainerFactoryT>
    friend struct CPtrConstructionFunctions;

    template<class ContainerFactoryT>
    friend struct PtrConstructionFunctions;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const GeoStatsAttachment &source);
};

typedef GeoStatsAttachment *GeoStatsAttachmentP;

typedef GeoStatsAttachment::ObjPtr           GeoStatsAttachmentPtr;
typedef GeoStatsAttachment::ObjPtrConst      GeoStatsAttachmentPtrConst;

typedef GeoStatsAttachment::ObjConstPtr      GeoStatsAttachmentConstPtr;
typedef GeoStatsAttachment::ObjConstPtrConst GeoStatsAttachmentConstPtrConst;

typedef GeoStatsAttachment::ObjPtrArg        GeoStatsAttachmentPtrArg;
typedef GeoStatsAttachment::ObjPtrConstArg   GeoStatsAttachmentPtrConstArg;


/*! Operators
   \{
*/

void operator +=(GeoStatsAttachmentPtr op, GeoStatsAttachmentPtr arg);
void operator -=(GeoStatsAttachmentPtr op, GeoStatsAttachmentPtr arg);

/*! \} */

OSG_END_NAMESPACE

#include "OSGGeoStatsAttachmentBase.inl"
#include "OSGGeoStatsAttachment.inl"

#define OSGGEOSTATSATTACHMENT_HEADER_CVSID "@(#)$Id$"

#endif /* _OSGGEOSTATSATTACHMENT_H_ */
