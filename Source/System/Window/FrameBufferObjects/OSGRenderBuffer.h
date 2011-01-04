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

#ifndef _OSGRENDERBUFFER_H_
#define _OSGRENDERBUFFER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGRenderBufferBase.h"
#include "OSGWindow.h"
#include "OSGImage.h"

OSG_BEGIN_NAMESPACE

/*! \brief Viewport class for color channel selection. See \ref 
    PageSystemFBOBuffer for a description.
    \ingroup GrpSystemWindowFBOObj
    \ingroup GrpLibOSGSystem
    \includebasedoc
*/

class OSG_SYSTEM_DLLMAPPING RenderBuffer : 
    public RenderBufferBase
{
  private:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef RenderBufferBase                           Inherited;

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

    virtual void bind    (DrawEnv *pEnv, UInt32 index = 0);
    virtual void validate(DrawEnv *pEnv                  );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    your_category                             */
    /*! \{                                                                 */

    virtual void processPreDeactivate (DrawEnv *pEnv, UInt32 index);
    virtual void processPostDeactivate(DrawEnv *pEnv              );

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in RenderBufferBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    RenderBuffer(void);
    RenderBuffer(const RenderBuffer &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~RenderBuffer(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                         GL                                   */
    /*! \{                                                                 */

    static UInt32 _uiFramebuffer_object_extension;

    static UInt32 _uiFuncFramebufferRenderbuffer;
    static UInt32 _uiFuncGenRenderbuffers;
    static UInt32 _uiFuncDeleteRenderbuffers;
    static UInt32 _uiFuncBindRenderbuffer;
    static UInt32 _uiFuncRenderbufferStorage;

           UInt32 handleGL       (DrawEnv                 *pEnv, 
                                  UInt32                   id, 
                                  Window::GLObjectStatusE  mode,
                                  UInt32                   uiOptions);

    static void   handleDestroyGL(DrawEnv                 *pEnv, 
                                  UInt32                   id, 
                                  Window::GLObjectStatusE  mode);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    void onCreate(const RenderBuffer *source = NULL);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class RenderBufferBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const RenderBuffer &source);
};

typedef RenderBuffer *RenderBufferP;

OSG_END_NAMESPACE

#include "OSGRenderBufferBase.inl"
#include "OSGRenderBuffer.inl"

#endif /* _OSGRENDERBUFFER_H_ */
