/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  Johannes Brunen                                               *
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

#ifndef _OSGMATERIALCHUNKOVERRIDEGROUP_H_
#define _OSGMATERIALCHUNKOVERRIDEGROUP_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGMaterialChunkOverrideGroupBase.h"
#include "OSGAction.h"
#include "OSGMaterial.h"

OSG_BEGIN_NAMESPACE

/*! \brief MaterialChunkOverrideGroup class. See \ref
           PageContribDataSolidMaterialChunkOverrideGroup for a description.
    \ingroup GrpGroupMiscObj
    \ingroup GrpLibOSGGroup
    \includebasedoc
 */

class OSG_GROUP_DLLMAPPING MaterialChunkOverrideGroup : 
    public MaterialChunkOverrideGroupBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef MaterialChunkOverrideGroupBase Inherited;
    typedef MaterialChunkOverrideGroup     Self;

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

    // Variables should all be in MaterialChunkOverrideGroupBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    MaterialChunkOverrideGroup(void);
    MaterialChunkOverrideGroup(const MaterialChunkOverrideGroup &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~MaterialChunkOverrideGroup(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Render                                     */
    /*! \{                                                                 */

    ActionBase::ResultE renderEnter(Action *action);
    ActionBase::ResultE renderLeave(Action *action);

    /*! \}                                                                 */

    /*---------------------------------------------------------------------*/
    /*! \name                      Set                                     */
    /*! \{                                                                 */

    using Inherited::addChunkBlock;
    using Inherited::subChunkBlock;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Set                                     */
    /*! \{                                                                 */

    using Inherited::findChunkBlock;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   your_category                              */
    /*! \{                                                                 */

    using Inherited::getSFChunkBlockStore;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Rendering                                  */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    using Inherited::addChunk;
    using Inherited::subChunk;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    using Inherited::find;

    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class MaterialChunkOverrideGroupBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const MaterialChunkOverrideGroup &source);
};

typedef MaterialChunkOverrideGroup *MaterialChunkOverrideGroupP;

OSG_END_NAMESPACE

#include "OSGMaterialChunkOverrideGroupBase.inl"
#include "OSGMaterialChunkOverrideGroup.inl"

#endif /* _OSGMATERIALCHUNKOVERRIDEGROUP_H_ */
