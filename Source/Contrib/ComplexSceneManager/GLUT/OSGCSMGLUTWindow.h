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

#ifndef _OSGCSMGLUTWINDOW_H_
#define _OSGCSMGLUTWINDOW_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGCSMGLUTWindowBase.h"
#include "OSGCSMDrawer.h"

OSG_BEGIN_NAMESPACE

/*! \brief CSMGLUTWindow class. See \ref
           PageContribCSMCSMGLUTWindow for a description.
*/

class OSG_CONTRIBCSM_DLLMAPPING CSMGLUTWindow : public CSMGLUTWindowBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef CSMGLUTWindowBase Inherited;
    typedef CSMGLUTWindow     Self;

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

    virtual bool init(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in CSMGLUTWindowBase.

    static bool           _bGLUTInitialized;
    static CSMGLUTWindow *_pGLUTWindow;

           Int32          _iGlutWinId;

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    CSMGLUTWindow(void);
    CSMGLUTWindow(const CSMGLUTWindow &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~CSMGLUTWindow(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

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

    static void csmGlutKeyHandler        (UChar8 key, 
                                          Int32, 
                                          Int32       );

    static void csmGlutReshapeHandler    (Int32 w, 
                                          Int32 h     );

    static void csmGlutFrameHandler      (void           );

    static void csmGlutMouseHandler      (Int32 iButton, 
                                          Int32 iState,
                                          Int32 x,       
                                          Int32 y      );

    static void csmGlutMouseMotionHandler(Int32 x, 
                                          Int32 y      );

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class CSMGLUTWindowBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const CSMGLUTWindow &source);
};

typedef CSMGLUTWindow *CSMGLUTWindowP;

OSG_END_NAMESPACE

#include "OSGCSMGLUTWindowBase.inl"
#include "OSGCSMGLUTWindow.inl"

#endif /* _OSGCSMGLUTWINDOW_H_ */
