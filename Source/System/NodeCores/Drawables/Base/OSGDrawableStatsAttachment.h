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

#ifndef _OSGDRAWABLESTATSATTACHMENT_H_
#define _OSGDRAWABLESTATSATTACHMENT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGDrawableStatsAttachmentBase.h"
#include "OSGDrawableFields.h"

OSG_BEGIN_NAMESPACE

/*! \brief DrawableStatsAttachment class. See \ref
    PageSystemDrawableStatsAttachment for a description.
    \ingroup GrpSystemNodeCoreDrawablesHelper
    \ingroup GrpLibOSGSystem
    \includebasedoc
 */

class OSG_SYSTEM_DLLMAPPING DrawableStatsAttachment : 
    public DrawableStatsAttachmentBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef DrawableStatsAttachmentBase Inherited;
    typedef DrawableStatsAttachment     Self;

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

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Creation                                 */
    /*! \{                                                                 */

    void                              reset(void);

    static DrawableStatsAttachmentTransitPtr calcStatic(Drawable *pDrawable);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Access                                   */
    /*! \{                                                                 */

    template<class CntPtr>
    static DrawableStatsAttachment *get(CntPtr arg);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Updating                                  */
    /*! \{                                                                 */

    static DrawableStatsAttachmentTransitPtr addTo(AttachmentContainer *obj);

    void attachTo(AttachmentContainer *obj);

    void validate(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Operators                                 */
    /*! \{                                                                 */

    void operator +=(DrawableStatsAttachment *arg);
    void operator -=(DrawableStatsAttachment *arg);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in DrawableStatsAttachmentBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    DrawableStatsAttachment(void);
    DrawableStatsAttachment(const DrawableStatsAttachment &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~DrawableStatsAttachment(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Update Helper                               */
    /*! \{                                                                 */
    
    static void invalidateFunctor(FieldContainer *obj,
                                  BitVector       mask);
    
    static void invalidate       (FieldContainer *obj );

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class DrawableStatsAttachmentBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const DrawableStatsAttachment &source);
};

typedef DrawableStatsAttachment *DrawableStatsAttachmentP;

OSG_END_NAMESPACE

#include "OSGDrawableStatsAttachmentBase.inl"
#include "OSGDrawableStatsAttachment.inl"

#endif /* _OSGDRAWABLESTATSATTACHMENT_H_ */
