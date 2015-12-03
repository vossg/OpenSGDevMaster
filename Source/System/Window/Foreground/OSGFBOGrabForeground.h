/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2013 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 * contact: dirk@opensg.org, gerrit.voss@vossg.org, carsten_neumann@gmx.net  *
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

#ifndef _OSGFBOGRABFOREGROUND_H_
#define _OSGFBOGRABFOREGROUND_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGFBOGrabForegroundBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief FBOGrabForeground class. See \ref
           PageWindowFBOGrabForeground for a description.
*/

class OSG_WINDOW_DLLMAPPING FBOGrabForeground : public FBOGrabForegroundBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef FBOGrabForegroundBase Inherited;
    typedef FBOGrabForeground     Self;

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
    /*! \name                   draw                                       */
    /*! \{                                                                 */

    virtual void draw(DrawEnv *pEnv);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    static UInt32 _uiFramebufferObjectExt;
    static UInt32 _uiFramebufferBlitExt;

    static UInt32 _uiFuncBindFramebuffer;
    static UInt32 _uiFuncBlitFramebuffer;

    // Variables should all be in FBOGrabForegroundBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    FBOGrabForeground(void);
    FBOGrabForeground(const FBOGrabForeground &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~FBOGrabForeground(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class FBOGrabForegroundBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const FBOGrabForeground &source);
};

typedef FBOGrabForeground *FBOGrabForegroundP;

OSG_END_NAMESPACE

#include "OSGFBOGrabForegroundBase.inl"
#include "OSGFBOGrabForeground.inl"

#endif /* _OSGFBOGRABFOREGROUND_H_ */
