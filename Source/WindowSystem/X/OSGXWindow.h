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

#ifndef _OSGXWINDOW_H_
#define _OSGXWINDOW_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGXWindowBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief X Window class. See \ref PageWindowX for a description. 
    \ingroup GrpWindowXObj
    \ingroup GrpLibOSGWindowX
    \includebasedoc
 */

class OSG_WINDOWX_DLLMAPPING XWindow : public XWindowBase
{
  public:

    typedef XWindowBase                           Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField, 
                         UInt32            origin,
                         BitVector         detail);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name      Window system implementation functions                  */
    /*! \{                                                                 */

    virtual void init     (GLInitFunctor oFunc = GLInitFunctor());
    virtual void terminate(void               );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Redefined                               */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in XWindowBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    XWindow(void);
    XWindow(const XWindow &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~XWindow(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    virtual void onDestroy(UInt32 uiContainerId);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    void classicInit(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
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
    friend class XWindowBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const XWindow &source);
};

OSG_END_NAMESPACE

#include "OSGXWindow.inl"
#include "OSGXWindowBase.inl"

#endif /* _OSGXWINDOW_H_ */
