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

#ifndef _OSGGLUTWINDOW_H_
#define _OSGGLUTWINDOW_H_
#ifdef __sgi
#pragma once
#endif

#if defined(OSG_WITH_GLUT) || defined(OSG_DO_DOC)

#include "OSGGLUTWindowBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief GLUT Window class. See \ref PageWindowGLUT for a description. 
    \ingroup GrpWindowGLUTObj
    \ingroup GrpLibOSGWindowGLUT
    \includebasedoc
 */

class OSG_WINDOWGLUT_DLLMAPPING GLUTWindow : public GLUTWindowBase
{
  public:

    typedef GLUTWindowBase Inherited;

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
    /*! \name                Window functions                              */
    /*! \{                                                                 */
    
    virtual void init(GLInitFunctor oFunc = GLInitFunctor());   

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Redefined                               */
    /*! \{                                                                 */

    virtual void activate (void);
    virtual void terminate(void);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in GLUTWindowBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    GLUTWindow(void);
    GLUTWindow(const GLUTWindow &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~GLUTWindow(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name      Window system implementation functions                  */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class GLUTWindowBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const GLUTWindow &source);
};

OSG_END_NAMESPACE

#include "OSGGLUTWindow.inl"
#include "OSGGLUTWindowBase.inl"

#endif /* OSG_WITH_GLUT */

#endif /* _OSGGLUTWINDOW_H_ */
