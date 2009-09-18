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

#ifndef _OSGANIMTARGETATTACHMENT_H_
#define _OSGANIMTARGETATTACHMENT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGAnimTargetAttachmentBase.h"
#include "OSGAnimBlender.h"

OSG_BEGIN_NAMESPACE

/*! \brief AnimTargetAttachment class. See \ref
           PageDynamicsAnimTargetAttachment for a description.
*/

class OSG_DYNAMICS_DLLMAPPING AnimTargetAttachment : public AnimTargetAttachmentBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef AnimTargetAttachmentBase Inherited;
    typedef AnimTargetAttachment     Self;

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
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in AnimTargetAttachmentBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    AnimTargetAttachment(void);
    AnimTargetAttachment(const AnimTargetAttachment &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~AnimTargetAttachment(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class AnimTargetAttachmentBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const AnimTargetAttachment &source);
};

typedef AnimTargetAttachment *AnimTargetAttachmentP;

/*---------------------------------------------------------------------------*\
 * Free Functions                                                            *
\*---------------------------------------------------------------------------*/

OSG_DYNAMICS_DLLMAPPING
AnimTargetAttachment *getTargetAtt(      AttachmentContainer *container );

OSG_DYNAMICS_DLLMAPPING
bool                  getTargetId (      AttachmentContainer *container,
                                         std::string         &targetId  );

OSG_DYNAMICS_DLLMAPPING
bool                  setTargetId (      AttachmentContainer *container,
                                   const std::string         &targetId  );

OSG_END_NAMESPACE

#include "OSGAnimTargetAttachmentBase.inl"
#include "OSGAnimTargetAttachment.inl"

#endif /* _OSGANIMTARGETATTACHMENT_H_ */
