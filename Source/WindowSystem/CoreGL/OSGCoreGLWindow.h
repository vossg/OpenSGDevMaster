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

#if defined(__APPLE__) || defined(OSG_DO_DOC)

#include "OSGCoreGLWindowBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief CoreGLWindow class. See \ref
           PageWindowCoreGL for a description.
    \ingroup GrpWindowCoreGLObj
    \ingroup GrpLibOSGWindowCoreGL
    \includebasedoc
 */

class OSG_WINDOWCOREGL_DLLMAPPING CoreGLWindow : public CoreGLWindowBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef CoreGLWindowBase Inherited;
    typedef CoreGLWindow     Self;

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
    /*! \name                Window functions                              */
    /*! \{                                                                 */
    
    virtual void init     (GLInitFunctor oFunc = GLInitFunctor());
    virtual void terminate(void                                 );


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
    /*---------------------------------------------------------------------*/
    /*! \name      Window system implementation functions                  */
    /*! \{                                                                 */

    virtual void doActivate  (void);
    virtual void doDeactivate(void);
    virtual bool doSwap      (void);

    virtual bool hasContext  (void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class CoreGLWindowBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const CoreGLWindow &source);
};

typedef CoreGLWindow *CoreGLWindowP;

OSG_END_NAMESPACE

#include "OSGCoreGLWindowBase.inl"
#include "OSGCoreGLWindow.inl"

#endif /* __APPLE__ */

#endif /* _OSGCOREGLWINDOW_H_ */
