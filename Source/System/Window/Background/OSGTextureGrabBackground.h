/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
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

#ifndef _OSGTEXTUREGRABBACKGROUND_H_
#define _OSGTEXTUREGRABBACKGROUND_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGTextureGrabBackgroundBase.h"

OSG_BEGIN_NAMESPACE

class Viewport;
class DrawEnv;

/*! \brief TextureGrabBackground class. See \ref 
           PageWindowGLUTTextureGrabBackground for a description.
    \ingroup GrpWindowBackgroundObj
    \ingroup GrpLibOSGWindow
    \includebasedoc
*/

class OSG_WINDOW_DLLMAPPING TextureGrabBackground : 
    public TextureGrabBackgroundBase
{
  private:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef TextureGrabBackgroundBase                          Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                     Clear                                    */
    /*! \{                                                                 */

    void clear(DrawEnv *pEnv);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField, 
                         UInt32            origin,
                         BitVector         details);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in TextureGrabBackgroundBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    TextureGrabBackground(void);
    TextureGrabBackground(const TextureGrabBackground &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~TextureGrabBackground(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class TextureGrabBackgroundBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const TextureGrabBackground &source);
};

typedef TextureGrabBackground *TextureGrabBackgroundP;

OSG_END_NAMESPACE

#include "OSGTextureGrabBackgroundBase.inl"
#include "OSGTextureGrabBackground.inl"

#endif /* _OSGTEXTUREGRABBACKGROUND_H_ */
