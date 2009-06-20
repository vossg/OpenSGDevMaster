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

#ifndef _OSGCUBES_H_
#define _OSGCUBES_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGCubesBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief Cubes class. See \ref
           PageCubesLibCubes for a description.
*/

class OSG_CUBESLIB_DLLMAPPING Cubes : public CubesBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef CubesBase Inherited;
    typedef Cubes     Self;

    /*---------------------------------------------------------------------*/
    /*! \name                    Rendering                                 */
    /*! \{                                                                 */

    virtual Action::ResultE drawPrimitives(DrawEnv                 *drawEnv);
    virtual void            fill          (DrawableStatsAttachment *stats  );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Frustum Culling                             */
    /*! \{                                                                 */

    virtual void adjustVolume(Volume &volume);

    /*! \}                                                                 */
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

    // Variables should all be in CubesBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    Cubes(void);
    Cubes(const Cubes &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~Cubes(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class CubesBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const Cubes &source);
};

typedef Cubes *CubesP;

OSG_END_NAMESPACE

#include "OSGCubesBase.inl"
#include "OSGCubes.inl"

#endif /* _OSGCUBES_H_ */
