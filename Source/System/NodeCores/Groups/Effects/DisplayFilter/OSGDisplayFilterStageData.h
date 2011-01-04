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

#ifndef _OSGDISPLAYFILTERSTAGEDATA_H_
#define _OSGDISPLAYFILTERSTAGEDATA_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGDisplayFilterStageDataBase.h"
#include "OSGFrameBufferObject.h"
#include "OSGChunkMaterial.h"
#include "OSGSimpleSHLChunk.h"
#include "OSGTextureObjChunk.h"

OSG_BEGIN_NAMESPACE

class DistortionDisplayFilter;
class ColorDisplayFilter;

/*! \brief DisplayFilterStageData class. See \ref
           PageGroupDisplayFilterStageData for a description.

    \ingroup GrpEffectsGroupsDisplayFilterObj
    \ingroup GrpLibOSGEffectsGroups
    \includebasedoc
*/

class OSG_EFFECTGROUPS_DLLMAPPING DisplayFilterStageData : 
    public DisplayFilterStageDataBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef DisplayFilterStageDataBase   Inherited;
    typedef DisplayFilterStageData       Self;

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

    void                     setColFilter (ColorDisplayFilter      *pFilter);
    ColorDisplayFilter      *getColFilter (void                            );

    void                     setDistFilter(DistortionDisplayFilter *pFilter);
    DistortionDisplayFilter *getDistFilter(void                            );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    void                setInitColTableFrom(ColorDisplayFilter *pFilter);
    ColorDisplayFilter *getInitColTableFrom(void                       );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in DisplayFilterStageDataBase.
    
    ColorDisplayFilter      *_pColFilter;
    DistortionDisplayFilter *_pDistFilter;
    
    ColorDisplayFilter      *_pInitColTableFrom;
    
    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    DisplayFilterStageData(void);
    DisplayFilterStageData(const DisplayFilterStageData &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~DisplayFilterStageData(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class DisplayFilterStageDataBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const DisplayFilterStageData &source);
};

typedef DisplayFilterStageData *DisplayFilterStageDataP;

OSG_END_NAMESPACE

#include "OSGDisplayFilterStageDataBase.inl"
#include "OSGDisplayFilterStageData.inl"

#endif /* _OSGDISPLAYFILTERSTAGEDATA_H_ */
