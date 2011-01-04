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

#ifndef _OSGCARBONWINDOW_H_
#define _OSGCARBONWINDOW_H_
#ifdef __sgi
#pragma once
#endif

#if defined(__APPLE__) || defined(OSG_DO_DOC)

#include "OSGCarbonWindowBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief CarbonWindow class. See \ref
           PageWindowCarbon for a description.
    \ingroup GrpWindowCarbonObj
    \ingroup GrpLibOSGWindowCarbon
    \includebasedoc
 */

class OSG_WINDOWCARBON_DLLMAPPING CarbonWindow : public CarbonWindowBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef CarbonWindowBase Inherited;
    typedef CarbonWindow     Self;

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

    // Variables should all be in CarbonWindowBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    CarbonWindow(void);
    CarbonWindow(const CarbonWindow &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~CarbonWindow(void);

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
    friend class CarbonWindowBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const CarbonWindow &source);
};

typedef CarbonWindow *CarbonWindowP;

OSG_END_NAMESPACE

#include "OSGCarbonWindowBase.inl"
#include "OSGCarbonWindow.inl"

#endif /* __APPLE__ */

#endif /* _OSGCARBONWINDOW_H_ */
