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

#ifndef _OSGFRAMEBUFFEROBJECT_H_
#define _OSGFRAMEBUFFEROBJECT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGFrameBufferObjectBase.h"
#include "OSGFrameBufferAttachment.h"
#include "OSGWindow.h"

OSG_BEGIN_NAMESPACE

class DrawEnv;
class Window;

/*! \brief Viewport class for color channel selection. See \ref 
    PageSystemFBOBuffer for a description.
    \ingroup GrpSystemWindowFBOObj
    \ingroup GrpLibOSGSystem
    \includebasedoc
 */

class OSG_SYSTEM_DLLMAPPING FrameBufferObject : 
    public FrameBufferObjectBase
{
  private:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef FrameBufferObjectBase                           Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField, 
                         UInt32            origin,
                         BitVector         detail);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    void setSize(UInt32 uiWidth, UInt32 uiHeight);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Attachments                             */
    /*! \{                                                                 */

    void setColorAttachment(FrameBufferAttachment *pAttachment,
                            UInt32                 uiSlot     );

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

    virtual void activate   (DrawEnv *pEnv,
                             GLenum   eDrawBuffer = GL_NONE);
    virtual void deactivate (DrawEnv *pEnv);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in FrameBufferObjectBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    FrameBufferObject(void);
    FrameBufferObject(const FrameBufferObject &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~FrameBufferObject(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                         GL                                   */
    /*! \{                                                                 */

    static UInt32 _uiFramebuffer_object_extension;
    static UInt32 _uiPackedDepthStencilExtension;

    static UInt32 _uiFuncGenFramebuffers;
    static UInt32 _uiFuncCheckFramebufferStatus;
    static UInt32 _uiFuncBindFramebuffer;
    static UInt32 _uiFuncDeleteFramebuffers;
    static UInt32 _uiFuncFramebufferRenderbuffer;
    static UInt32 _uiFuncDrawBuffers;

           UInt32 handleGL       (DrawEnv                 *pEnv, 
                                  UInt32                   id, 
                                  Window::GLObjectStatusE  mode,
                                  UInt32                   uiOptions) const;
    static void   handleDestroyGL(DrawEnv                 *pEnv, 
                                  UInt32                   id, 
                                  Window::GLObjectStatusE  mode     );
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    void onCreate (const FrameBufferObject *source        = NULL);
    void onDestroy(      UInt32             uiContainerId       );

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class FrameBufferObjectBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const FrameBufferObject &source);
};

typedef FrameBufferObject *FrameBufferObjectP;

OSG_END_NAMESPACE

#include "OSGFrameBufferObjectBase.inl"
#include "OSGFrameBufferObject.inl"

#endif /* _OSGFRAMEBUFFEROBJECT_H_ */
