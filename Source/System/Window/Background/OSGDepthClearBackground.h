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

#ifndef _OSGDEPTHCLEARBACKGROUND_H_
#define _OSGDEPTHCLEARBACKGROUND_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGDepthClearBackgroundBase.h"

OSG_BEGIN_NAMESPACE

class Viewport;
class DrawEnv;

/*! \brief Depth Clear Background  class. See \ref 
           PageSystemWindowBackgroundDepthClear for a description.
    \ingroup GrpWindowBackgroundObj
    \ingroup GrpLibOSGWindow
    \includebasedoc
 */

class OSG_WINDOW_DLLMAPPING DepthClearBackground : 
    public DepthClearBackgroundBase
{
    /*==========================  PUBLIC  =================================*/

 public:

    /*---------------------------------------------------------------------*/
    /*! \name                     your_category                            */
    /*! \{                                                                 */

#ifdef OSG_OLD_RENDER_ACTION
    void clear(DrawActionBase *, Viewport *);
#endif

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

    DepthClearBackground(void);
    
    DepthClearBackground(const DepthClearBackground &source);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~DepthClearBackground(void); 
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*=========================  PRIVATE  =================================*/

  private:

    typedef DepthClearBackgroundBase Inherited;

    friend class FieldContainer;
    friend class DepthClearBackgroundBase;

    void operator =(const DepthClearBackground &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------


/*! \brief class pointer
 */

typedef DepthClearBackground *DepthClearBackgroundP;

OSG_END_NAMESPACE

#include "OSGDepthClearBackgroundBase.inl"
#include "OSGDepthClearBackground.inl"

#endif /* _OSGDEPTHCLEARBACKGROUND_H_ */
