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

#ifndef _OSGNAVIGATIONMANAGER_H_
#define _OSGNAVIGATIONMANAGER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGUtilDef.h"

#include "OSGBaseTypes.h"

#include "OSGNode.h"
#include "OSGWindow.h"
#include "OSGNavigator.h"

OSG_BEGIN_NAMESPACE

/*! \brief A helper class to simplify navigation within a subgraph.
    \ingroup GrpUtilNavigation
    \ingroup GrpLibOSGUtil
 */

class OSG_UTIL_DLLMAPPING NavigationManager
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                      Enums                                   */
    /*! \{                                                                 */

    enum
    {
        MouseLeft   =  0,
        MouseMiddle =  1,
        MouseRight  =  2,
        MouseUp     =  3,
        MouseDown   =  4,
        NoButton    = -1
    };

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    NavigationManager(void);

    NavigationManager *create(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~NavigationManager(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    virtual Window                *getWindow          ( void );
    virtual Navigator             *getNavigator       ( void );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Set                                     */
    /*! \{                                                                 */

    virtual void  setWindow        (Window         *win       );
    virtual void  setBeacon        (Node * const    newBeacon);
            void  setNavigationMode(Navigator::Mode new_mode);
    inline  bool  setClickCenter   (bool            mode    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name               Interaction handling                           */
    /*! \{                                                                 */

    virtual void resize(UInt16 width, UInt16 height);
    virtual void mouseMove(Int16 x, Int16 y);
    virtual void mouseButtonPress(UInt16 button, Int16 x, Int16 y);
    virtual void mouseButtonRelease(UInt16 button, Int16 x, Int16 y);
    virtual void key(UChar8 key, Int16 x, Int16 y);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Actions                                  */
    /*! \{                                                                 */

    virtual void update( void );
    virtual void redraw( void );
    virtual void idle  ( void );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Comparison                                */
    /*! \{                                                                 */

    bool operator < (const NavigationManager &other) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                     Updates                                  */
    /*! \{                                                                 */

            // added by martin (FIXME: remove comment)
            void  updateMouseButtonPress  (UInt16 button, Int16 x, Int16 y);
            void  updateMouseButtonRelease(UInt16 button, Int16 x, Int16 y);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    WindowRecPtr                 _win;
    Navigator                    _navigator;
    Int16                        _lastx;
    Int16                        _lasty;
    UInt16                       _mousebuttons;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    /* prohibit default function (move to 'public' if needed) */

    NavigationManager(const NavigationManager &source);
    void operator =(const NavigationManager &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

// class pointer

typedef NavigationManager *NavigationManagerP;

OSG_END_NAMESPACE

#include "OSGNavigationManager.inl"

#endif /* _OSGNAVIGATIONMANAGER_H_ */
