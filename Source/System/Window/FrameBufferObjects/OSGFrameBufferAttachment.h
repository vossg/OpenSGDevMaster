/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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

#ifndef _OSGFRAMEBUFFERATTACHMENT_H_
#define _OSGFRAMEBUFFERATTACHMENT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGFrameBufferAttachmentBase.h"

OSG_BEGIN_NAMESPACE

class RenderActionBase;
class DrawEnv;
class FrameBufferObject;

/*! \brief Viewport class for color channel selection. See \ref 
    PageSystemFBOBuffer for a description.
    \ingroup GrpSystemWindowFBOObj
    \ingroup GrpLibOSGSystem
    \includebasedoc
 */

class OSG_SYSTEM_DLLMAPPING FrameBufferAttachment : 
    public FrameBufferAttachmentBase
{
  private:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef FrameBufferAttachmentBase                           Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField, 
                         UInt32            origin,
                         BitVector         detail);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    your_category                             */
    /*! \{                                                                 */

    virtual void bind    (DrawEnv *pEnv, UInt32 index = 0) = 0;
    virtual void validate(DrawEnv *pEnv                  ) = 0;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    your_category                             */
    /*! \{                                                                 */

    virtual void processPreDeactivate (DrawEnv *pEnv, UInt32 index) = 0;
    virtual void processPostDeactivate(DrawEnv *pEnv              ) = 0;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in FrameBufferAttachmentBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    FrameBufferAttachment(void);
    FrameBufferAttachment(const FrameBufferAttachment &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~FrameBufferAttachment(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        size                                  */
    /*! \{                                                                 */

    void resize(UInt32 uiWidth, UInt32 uiHeight);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class FrameBufferAttachmentBase;
    friend class FrameBufferObject;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const FrameBufferAttachment &source);
};

typedef FrameBufferAttachment *FrameBufferAttachmentP;

OSG_END_NAMESPACE

#include "OSGFrameBufferAttachmentBase.inl"
#include "OSGFrameBufferAttachment.inl"

#endif /* _OSGFRAMEBUFFERATTACHMENT_H_ */
