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

#ifndef _OSGCOREGLWINDOW_H_
#define _OSGCOREGLWINDOW_H_
#ifdef __sgi
#pragma once
#endif

#ifdef __APPLE__

#include "OSGCoreGLWindowBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief CoreGLWindow class. See \ref 
           PageWindowCoreGLCoreGLWindow for a description.
*/

class OSG_WINDOWCOREGL_DLLMAPPING CoreGLWindow : public CoreGLWindowBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef CoreGLWindowBase Inherited;
    typedef CoreGLWindow     Self;

    typedef PointerBuilder<CoreGLWindow>::ObjPtr           ObjPtr;
    typedef PointerBuilder<CoreGLWindow>::ObjPtrConst      ObjPtrConst;

    typedef PointerBuilder<CoreGLWindow>::ObjConstPtr      ObjConstPtr;
    typedef PointerBuilder<CoreGLWindow>::ObjConstPtrConst ObjConstPtrConst;

    typedef PointerBuilder<CoreGLWindow>::ObjPtrArg        ObjPtrArg;
    typedef PointerBuilder<CoreGLWindow>::ObjPtrConstArg   ObjPtrConstArg;

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
    /*! \name                Window functions                              */
    /*! \{                                                                 */
    
    virtual void init      (void);
    virtual void activate  (void);
    virtual void deactivate(void);
    virtual bool swap      (void);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in CoreGLWindowBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    CoreGLWindow(void);
    CoreGLWindow(const CoreGLWindow &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~CoreGLWindow(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class CoreGLWindowBase;

    template<class ContainerFactoryT>
    friend struct CPtrConstructionFunctions;

    template<class ContainerFactoryT>
    friend struct PtrConstructionFunctions;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const CoreGLWindow &source);
};

typedef CoreGLWindow *CoreGLWindowP;

typedef CoreGLWindow::ObjPtr           CoreGLWindowPtr;
typedef CoreGLWindow::ObjPtrConst      CoreGLWindowPtrConst;

typedef CoreGLWindow::ObjConstPtr      CoreGLWindowConstPtr;
typedef CoreGLWindow::ObjConstPtrConst CoreGLWindowConstPtrConst;

typedef CoreGLWindow::ObjPtrArg        CoreGLWindowPtrArg;
typedef CoreGLWindow::ObjPtrConstArg   CoreGLWindowPtrConstArg;

OSG_END_NAMESPACE

#include "OSGCoreGLWindowBase.inl"
#include "OSGCoreGLWindow.inl"

#define OSGCOREGLWINDOW_HEADER_CVSID "@(#)$Id: FCTemplate_h.h 106 2006-09-14 03:15:53Z dirk $"

#endif /* __APPLE__ */

#endif /* _OSGCOREGLWINDOW_H_ */
