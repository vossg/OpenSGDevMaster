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

OSG_BEGIN_NAMESPACE


class MaterialDrawable;

#ifdef OSG_OLD_RENDER_ACTION
class DrawActionBase;
#endif

class DrawEnv;

/*! \brief Abstract Material base class. See \ref PageSystemMaterial for a
    description.
*/

class OSG_SYSTEM_DLLMAPPING Material : public MaterialBase
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef boost::function<Action::ResultE (DrawEnv *)> DrawFunctor;

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

    // TODO: switch geo to functor too, remove makeState, replace by rebuild
    

#ifdef OLD
    virtual void     draw          (DrawFunctor      &func,
                                    DrawActionBase   *action   )       = 0;

    virtual void     draw          (MaterialDrawable *geo,
                                    DrawActionBase   *action   )       = 0;

    virtual StatePtr makeState     (void                       )       = 0;
#endif

    virtual void     rebuildState  (void                       )       = 0;

    virtual StatePtr getState      (UInt32            index = 0);
    virtual UInt32   getNPasses    (void                       );
  
    virtual bool     isTransparent (void                       ) const = 0;

    virtual Int32    getRealSortKey(void                       ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Comparison                                */
    /*! \{                                                                 */

    virtual ActionBase::ResultE renderEnter(const NodeCorePtr &pCore,
                                                  Action      *pAction);

    virtual ActionBase::ResultE renderLeave(const NodeCorePtr &pCore,
                                                  Action      *pAction);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Comparison                                */
    /*! \{                                                                 */

    virtual bool operator <  (const Material &other) const;

    virtual bool operator == (const Material &other) const;
    virtual bool operator != (const Material &other) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    StatePtr _pState;  // !!! TODO is that MT safe?

    // Yes, but not efficient. Every material has as many States as there
    // are aspects, each of which itself is threadsafe (i.e. multibuffered).
    // A single State per Material would be better. I'm just not sure how to
    // initialize it. :( DR
    // Actually, no, it isn't!!! Multiple materials updating the same aspect 
    // in different threads make this crash!!! DR
    
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

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const Material &source);
};

typedef Material *MaterialP;

extern OSG_SYSTEM_DLLMAPPING MaterialPtr NullMaterial;

/*---------------------------------------------------------------------*/
/*! \name                     Material Access                          */
/*! \{                                                                 */

OSG_SYSTEM_DLLMAPPING MaterialPtr getDefaultMaterial     (void);
OSG_SYSTEM_DLLMAPPING MaterialPtr getDefaultUnlitMaterial(void);

/*! \}                                                                 */
/*---------------------------------------------------------------------*/

OSG_END_NAMESPACE

#include "OSGMaterialBase.inl"
#include "OSGMaterial.inl"

#endif /* _OSGMATERIAL_H_ */
