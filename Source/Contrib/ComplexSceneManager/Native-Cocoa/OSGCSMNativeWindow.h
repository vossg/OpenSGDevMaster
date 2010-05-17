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

#ifndef _OSGCSMNATIVEWINDOW_H_
#define _OSGCSMNATIVEWINDOW_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGCSMNativeWindowBase.h"
#include "OSGCocoaWindow.h"
#include "OSGCSMDrawer.h"

#ifndef __OBJC__
struct NSAutoreleasePool;
struct CSMOpenGLView;
#else
@class NSAutoreleasePool;
@class CSMOpenGLView;
#endif


OSG_BEGIN_NAMESPACE

//static pascal OSStatus eventHandler(EventHandlerCallRef  nextHandler, 
//                                    EventRef             event, 
//                                    void                *userData   );

/*! \brief CSMNativeWindow class. See \ref
           PageContribCSMCSMNativeWindow for a description.
*/

class OSG_CONTRIBCSM_DLLMAPPING CSMNativeWindow : public CSMNativeWindowBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef CSMNativeWindowBase Inherited;
    typedef CSMNativeWindow     Self;

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

    virtual bool init     (void);
    static  bool isRunning(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    void reshape(Int32 w, 
                 Int32 h        );

    void mouse  (Int32 iButton, 
                 Int32 iState,
                 Int32 iModifier,
                 Int32 x,       
                 Int32 y        );

    void motion (Int32 x, 
                 Int32 y        );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in CSMNativeWindowBase.

    CocoaWindow       *_pCocoaWindow;
    CSMOpenGLView     *_pGLView;

    static NSAutoreleasePool *_pPool;
    static bool               _bRun;

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    CSMNativeWindow(void);
    CSMNativeWindow(const CSMNativeWindow &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~CSMNativeWindow(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    virtual void resolveLinks      (void);
    virtual void terminateGLContext(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void cocoaMainLoop(void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class CSMNativeWindowBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const CSMNativeWindow &source);
};

typedef CSMNativeWindow *CSMNativeWindowP;

OSG_END_NAMESPACE

#include "OSGCSMNativeWindowBase.inl"
#include "OSGCSMNativeWindow.inl"

#endif /* _OSGCSMNATIVEWINDOW_H_ */