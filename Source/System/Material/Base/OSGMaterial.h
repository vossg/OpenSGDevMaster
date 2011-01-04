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


#ifndef _OSGMATERIAL_H_
#define _OSGMATERIAL_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGAction.h"
#include "OSGMaterialBase.h"
#include "OSGState.h"
#include "OSGMaterialMapFields.h"

OSG_BEGIN_NAMESPACE


class MaterialDrawable;
class DrawEnv;
class Window;
class PrimeMaterial;

template <class Desc>
class MapCacheHandlerMixin;

/*! \brief Abstract Material base class. See \ref PageSystemMaterial for a
    description.

    \ingroup GrpSystemMaterialBase
    \ingroup GrpLibOSGSystem
    \includebasedoc
 */

class OSG_SYSTEM_DLLMAPPING Material : public MaterialBase
{
    /*==========================  PUBLIC  =================================*/

  public:
    /*---------------------------------------------------------------------*/
    /*! \name                    Constants                                 */
    /*! \{                                                                 */

    static const Int32 NoStateSorting;
    static const Int32 TransparencyAutoDetection;
    static const Int32 TransparencyForceTransparent;
    static const Int32 TransparencyForceOpaque;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin,
                         BitVector         detail);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Output                                  */
    /*! \{                                                                 */

    virtual void dump(      UInt32    uiIndent = 0,
                      const BitVector bvFlags  = 0) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Rendering                                  */
    /*! \{                                                                 */

    virtual PrimeMaterial *finalize     (MaterialMapKey  oKey,
                                         Window         *pWin)       = 0;
    virtual bool           isTransparent(void                ) const = 0;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Comparison                                */
    /*! \{                                                                 */

    virtual ActionBase::ResultE renderEnter(NodeCore * const  pCore,
                                            Action           *pAction);

    virtual ActionBase::ResultE renderLeave(NodeCore * const  pCore,
                                            Action           *pAction);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Comparison                                */
    /*! \{                                                                 */

#if 0
    virtual bool operator <  (const Material &other) const;

    virtual bool operator == (const Material &other) const;
    virtual bool operator != (const Material &other) const;
#endif

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:
    
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    Material(void);
    Material(const Material &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~Material(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Helper                                   */
    /*! \{                                                                 */

    virtual void resolveLinks(void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    typedef MaterialBase Inherited;

    friend class FieldContainer;
    friend class MaterialBase;

    template <class Desc>
    friend class MapCacheHandlerMixin;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const Material &source);
};

typedef Material *MaterialP;

/*---------------------------------------------------------------------*/
/*! \name                     Material Access                          */
/*! \{                                                                 */

/*! \ingroup GrpSystemFunctions
 */

OSG_SYSTEM_DLLMAPPING PrimeMaterial *getDefaultMaterial     (void);

/*! \ingroup GrpSystemFunctions
 */

OSG_SYSTEM_DLLMAPPING PrimeMaterial *getDefaultUnlitMaterial(void);

/*! \}                                                                 */
/*---------------------------------------------------------------------*/

OSG_END_NAMESPACE

#include "OSGMaterialBase.inl"
#include "OSGMaterial.inl"

#endif /* _OSGMATERIAL_H_ */
