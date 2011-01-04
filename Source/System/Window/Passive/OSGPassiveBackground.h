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


#ifndef _OSGPASSIVEBACKGROUND_H_
#define _OSGPASSIVEBACKGROUND_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGPassiveBackgroundBase.h"

OSG_BEGIN_NAMESPACE

class Viewport;

/*! \brief Passive Background  class. See \ref 
           PageSystemWindowBackgroundPassive for a description.
    \ingroup GrpWindowPassiveObj
    \ingroup GrpLibOSGWindow
    \includebasedoc
 */

class OSG_WINDOW_DLLMAPPING PassiveBackground : 
    public PassiveBackgroundBase
{
    /*==========================  PUBLIC  =================================*/
 public:

    typedef PassiveBackgroundBase			Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                     your_category                            */
    /*! \{                                                                 */

    void clear(DrawEnv *);


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     transformation                           */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField, 
                         UInt32            origin,
                         BitVector         detail);
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   dump                                       */
    /*! \{                                                                 */

    virtual void dump(      UInt32    uiIndent = 0, 
                      const BitVector bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:
    
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    PassiveBackground(void);
    
    PassiveBackground(const PassiveBackground &source);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~PassiveBackground(void); 


    static void initMethod( InitPhase ePhase );
    
    /*! \}                                                                 */
    /*=========================  PRIVATE  =================================*/
  private:

    friend class FieldContainer;
    friend class PassiveBackgroundBase;

    void operator =(const PassiveBackground &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------


/** \brief class pointer
 */
typedef PassiveBackground *PassiveBackgroundP;

OSG_END_NAMESPACE

#include "OSGPassiveBackgroundBase.inl"
#include "OSGPassiveBackground.inl"

#endif /* _OSGPASSIVEBACKGROUND_H_ */
