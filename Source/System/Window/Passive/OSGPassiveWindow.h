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

#ifndef _OSGPASSIVEWINDOW_H_
#define _OSGPASSIVEWINDOW_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"

#include "OSGPassiveWindowBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief PassiveWindow class. See \ref 
           PageSystemPassiveWindow for a description.
    \ingroup GrpWindowPassiveObj
    \ingroup GrpLibOSGWindow
    \includebasedoc
 */

class OSG_WINDOW_DLLMAPPING PassiveWindow : public PassiveWindowBase
{
    /*==========================  PUBLIC  =================================*/

  public:

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
    /*! \name                      Redefined                               */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Redefined                               */
    /*! \{                                                                 */

    virtual void init     (GLInitFunctor oFunc = GLInitFunctor());
    virtual void terminate(void                                 );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Redefined                               */
    /*! \{                                                                 */

    /*! \}                                                                 */  
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in PassiveWindowBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    PassiveWindow(void);
    PassiveWindow(const PassiveWindow &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~PassiveWindow(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name      Window system implementation functions                  */
    /*! \{                                                                 */

   /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    typedef PassiveWindowBase Inherited;
    
    friend class FieldContainer;
    friend class PassiveWindowBase;
    friend class PassiveViewport;

    static void initMethod(InitPhase ePhase);
    
    // prohibit default functions (move to 'public' if you need one)
    void operator =(const PassiveWindow &source);
};

typedef PassiveWindow *PassiveWindowP;

OSG_END_NAMESPACE

#include "OSGPassiveWindowBase.inl"
#include "OSGPassiveWindow.inl"

#endif /* _OSGPASSIVEWINDOW_H_ */
