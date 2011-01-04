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

#ifndef _OSGTILEDQUADTREETERRAIN_H_
#define _OSGTILEDQUADTREETERRAIN_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"

#include "OSGTiledQuadTreeTerrainBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief TiledQuadTreeTerrain class. See \ref 
           PageContribTiledQuadTreeTerrain for a description.
    \ingroup GrpDrawablesTerrainObj
    \ingroup GrpLibOSGDrawables
    \includebasedoc
 */

class OSG_DRAWABLE_DLLMAPPING TiledQuadTreeTerrain : 
    public TiledQuadTreeTerrainBase
{
  private:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef TiledQuadTreeTerrainBase Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField, 
                         UInt32            origin,
                         BitVector         detail);

    Action::ResultE renderEnter (Action* action);

    Action::ResultE doRenderEnter  (const FrustumVolume &frustum,
                                          Matrix         camera,
                                          Matrix         toworld);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in TiledTerrainBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    TiledQuadTreeTerrain(void);
    TiledQuadTreeTerrain(const TiledQuadTreeTerrain &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~TiledQuadTreeTerrain(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class TiledQuadTreeTerrainBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const TiledQuadTreeTerrain &source);
};

typedef TiledQuadTreeTerrain *TiledQuadTreeTerrainP;

OSG_END_NAMESPACE

#include "OSGTiledQuadTreeTerrainBase.inl"
#include "OSGTiledQuadTreeTerrain.inl"

#endif /* _OSGTILEDQUADTREETERRAIN_H_ */
