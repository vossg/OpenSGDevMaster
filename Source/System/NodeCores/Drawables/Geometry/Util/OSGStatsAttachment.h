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

#ifndef _OSGSTATSATTACHMENT_H_
#define _OSGSTATSATTACHMENT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGStatsAttachmentBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief StatsAttachment class. See \ref 
           PageSystemStatsAttachment for a description.
*/

class OSG_SYSTEM_DLLMAPPING StatsAttachment : public StatsAttachmentBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef StatsAttachmentBase Inherited;
    typedef StatsAttachment     Self;

    typedef PointerBuilder<StatsAttachment>::ObjPtr           ObjPtr;
    typedef PointerBuilder<StatsAttachment>::ObjPtrConst      ObjPtrConst;

    typedef PointerBuilder<StatsAttachment>::ObjConstPtr      ObjConstPtr;
    typedef PointerBuilder<StatsAttachment>::ObjConstPtrConst ObjConstPtrConst;

    typedef PointerBuilder<StatsAttachment>::ObjPtrArg        ObjPtrArg;
    typedef PointerBuilder<StatsAttachment>::ObjPtrConstArg   ObjPtrConstArg;

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
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in StatsAttachmentBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    StatsAttachment(void);
    StatsAttachment(const StatsAttachment &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~StatsAttachment(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Update Helper                               */
    /*! \{                                                                 */


    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class StatsAttachmentBase;

    template<class ContainerFactoryT>
    friend struct CPtrConstructionFunctions;

    template<class ContainerFactoryT>
    friend struct PtrConstructionFunctions;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const StatsAttachment &source);
};

typedef StatsAttachment *StatsAttachmentP;

typedef StatsAttachment::ObjPtr           StatsAttachmentPtr;
typedef StatsAttachment::ObjPtrConst      StatsAttachmentPtrConst;

typedef StatsAttachment::ObjConstPtr      StatsAttachmentConstPtr;
typedef StatsAttachment::ObjConstPtrConst StatsAttachmentConstPtrConst;

typedef StatsAttachment::ObjPtrArg        StatsAttachmentPtrArg;
typedef StatsAttachment::ObjPtrConstArg   StatsAttachmentPtrConstArg;

OSG_END_NAMESPACE

#include "OSGStatsAttachmentBase.inl"
#include "OSGStatsAttachment.inl"

#define OSGSTATSATTACHMENT_HEADER_CVSID "@(#)$Id$"

#endif /* _OSGSTATSATTACHMENT_H_ */
