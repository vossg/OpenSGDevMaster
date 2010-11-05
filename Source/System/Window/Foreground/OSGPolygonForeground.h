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

#ifndef _OSGPOLYGONFOREGROUND_H_
#define _OSGPOLYGONFOREGROUND_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGPrimeMaterial.h"
#include "OSGPolygonForegroundBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief PolygonForeground class. See \ref 
           PageSystemPolygonForeground for a description.
    \ingroup GrpWindowForegroundObj
    \ingroup GrpLibOSGWindow
    \includebasedoc
*/

class OSG_WINDOW_DLLMAPPING PolygonForeground : public PolygonForegroundBase
{
  private:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef PolygonForegroundBase Inherited;

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
    /*! \name                    draw                                      */
    /*! \{                                                                 */

    virtual void draw(DrawEnv *);

    /*! \}                                                                 */
     /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in PolygonForegroundBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    PolygonForeground(void);
    PolygonForeground(const PolygonForeground &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~PolygonForeground(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Helpers                                  */
    /*! \{                                                                 */

    Real32 mapCoordinate(Real32 val, Real32 max, bool norm);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class PolygonForegroundBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const PolygonForeground &source);
};

typedef PolygonForeground *PolygonForegroundP;

OSG_END_NAMESPACE

#include "OSGPolygonForegroundBase.inl"
#include "OSGPolygonForeground.inl"

#endif /* _OSGPOLYGONFOREGROUND_H_ */
