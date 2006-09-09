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
*/

class OSG_SYSTEM_DLLMAPPING PassiveWindow : public PassiveWindowBase
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg  whichField, 
                         UInt32             origin    );

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
    
    virtual void init( void );
    
    virtual void activate( void );
    
    virtual void deactivate ( void ) {}
    
    virtual bool swap( void );    
    
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
    
    /*==========================  PRIVATE  ================================*/
  private:

    typedef PassiveWindowBase Inherited;
    
    friend class FieldContainer;
    friend class PassiveWindowBase;

    static void initMethod(InitPhase ePhase);
    
    template<class ContainerFactoryT>
    friend struct CPtrConstructionFunctions;
    template<class ContainerFactoryT>
    friend struct PtrConstructionFunctions;

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const PassiveWindow &source);
};

typedef PassiveWindow *PassiveWindowP;

OSG_END_NAMESPACE

#include "OSGPassiveWindowBase.inl"
#include "OSGPassiveWindow.inl"

#define OSGPASSIVEWINDOW_HEADER_CVSID "@(#)$Id: OSGPassiveWindow.h,v 1.1.2.3 2006/08/01 07:54:18 vossg Exp $"

#endif /* _OSGPASSIVEWINDOW_H_ */
