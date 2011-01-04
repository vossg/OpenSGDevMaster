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

#ifndef _OSGTILEABLEBACKGROUND_H_
#define _OSGTILEABLEBACKGROUND_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGTileableBackgroundBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief TileableBackground class. See \ref
           PageWindowTileableBackground for a description.
    \ingroup GrpWindowBackgroundObj
    \ingroup GrpLibOSGWindow
    \includebasedoc
*/

class OSG_WINDOW_DLLMAPPING TileableBackground : public TileableBackgroundBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef TileableBackgroundBase Inherited;
    typedef TileableBackground     Self;

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
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in TileableBackgroundBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    TileableBackground(void);
    TileableBackground(const TileableBackground &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~TileableBackground(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Helpers                                  */
    /*! \{                                                                 */

    void beginOrthoRender(DrawEnv *pEnv,      bool    normX,     bool normY,
                          UInt32  &fullWidth, UInt32 &fullHeight            );
    void endOrthoRender  (DrawEnv *pEnv                                     );

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class TileableBackgroundBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const TileableBackground &source);
};

typedef TileableBackground *TileableBackgroundP;

OSG_END_NAMESPACE

#include "OSGTileableBackgroundBase.inl"
#include "OSGTileableBackground.inl"

#endif /* _OSGTILEABLEBACKGROUND_H_ */
