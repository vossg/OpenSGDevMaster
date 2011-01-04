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

#ifndef _OSGSOLIDBACKGROUND_H_
#define _OSGSOLIDBACKGROUND_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGSolidBackgroundBase.h"

OSG_BEGIN_NAMESPACE

class Viewport;
class DrawEnv;

/*! \brief Single color background clearing class. See \ref 
           PageSystemWindowBackgroundSolid for a description.
    \ingroup GrpWindowBackgroundObj
    \ingroup GrpLibOSGWindow
    \includebasedoc
*/

class OSG_WINDOW_DLLMAPPING SolidBackground : public SolidBackgroundBase
{
    /*==========================  PUBLIC  =================================*/

 public:

    /*---------------------------------------------------------------------*/
    /*! \name                     your_category                            */
    /*! \{                                                                 */

    void clear(DrawEnv  *);

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

    SolidBackground(void);
    SolidBackground(const SolidBackground &source);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SolidBackground(void); 
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*=========================  PRIVATE  =================================*/

  private:

    typedef SolidBackgroundBase Inherited;

    friend class FieldContainer;
    friend class SolidBackgroundBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const SolidBackground &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

typedef SolidBackground              *SolidBackgroundP;

OSG_END_NAMESPACE

#include "OSGSolidBackgroundBase.inl"
#include "OSGSolidBackground.inl"

#endif /* _OSGSOLIDBACKGROUND_H_ */
