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

#ifndef _OSGQTWINDOW_H_
#define _OSGQTWINDOW_H_
#ifdef __sgi
#pragma once
#endif

#if defined(OSG_WITH_QT) || defined(OSG_DO_DOC)

#include "OSGQT4WindowBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief QT Window class. See \ref PageWindowQt4 for a description. 
    \ingroup GrpWindowQt4Obj
    \ingroup GrpLibOSGWindowQt4
    \includebasedoc
 */

class OSG_WINDOWQT4_DLLMAPPING QT4Window : public QT4WindowBase
{
  public:

    typedef QT4WindowBase Inherited;

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
    /*! \name                Window functions                              */
    /*! \{                                                                 */

    // init the window: create the context
    virtual void init(GLInitFunctor oFunc = GLInitFunctor());

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in QTWindowBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    QT4Window(void);
    QT4Window(const QT4Window &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~QT4Window(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  
  private:

    friend class FieldContainer;
    friend class QT4WindowBase;    

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const QT4Window &source);
};

OSG_END_NAMESPACE

#include "OSGQT4Window.inl"
#include "OSGQT4WindowBase.inl"

#endif /* OSG_WITH_QT */

#endif /* _OSGQTWINDOW_H_ */
