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

#ifndef _OSGFBOVIEWPORT_H_
#define _OSGFBOVIEWPORT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGFBOViewportBase.h"
#include "OSGFrameBufferObject.h"

OSG_BEGIN_NAMESPACE

/*! \brief Viewport class for color channel selection. See \ref 
    PageSystemFBOViewport for a description.
    \ingroup GrpSystemWindowFBOObj
    \ingroup GrpLibOSGSystem
    \includebasedoc
 */

class OSG_SYSTEM_DLLMAPPING FBOViewport : public FBOViewportBase
{
  private:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef FBOViewportBase                           Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                      Sizes                                   */
    /*! \{                                                                 */

    virtual Int32 getPixelLeft  (void) const;
    virtual Int32 getPixelRight (void) const;
    virtual Int32 getPixelBottom(void) const;
    virtual Int32 getPixelTop   (void) const;
//            Int32 getPixelWidth (void) const;
//            Int32 getPixelHeight(void) const;
    
    virtual bool  isFullWindow  (void) const;

    /*! \}                                                                 */
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

#ifdef OSG_OLD_RENDER_ACTION
    virtual void render(DrawActionBase *action);
#endif

    virtual FrameBufferObject *getTarget(void);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in FBOViewportBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    FBOViewport(void);
    FBOViewport(const FBOViewport &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~FBOViewport(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class FBOViewportBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const FBOViewport &source);
};

typedef FBOViewport *FBOViewportP;

OSG_END_NAMESPACE

#include "OSGFBOViewportBase.inl"
#include "OSGFBOViewport.inl"

#endif /* _OSGFBOVIEWPORT_H_ */
