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

#ifndef _OSGALGORITHMCOMPUTEELEMENTDATA_H_
#define _OSGALGORITHMCOMPUTEELEMENTDATA_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGAlgorithmComputeElementDataBase.h"
#include "OSGComputeAlgorithm.h"

OSG_BEGIN_NAMESPACE

class AlgorithmComputeElement;

/*! \brief AlgorithmComputeElementData class. See \ref
           PageGroupAlgorithmComputeElementData for a description.

    \ingroup GrpEffectsGroupsHDRObj
    \ingroup GrpLibOSGEffectsGroups
    \includebasedoc
 */

class OSG_CONTRIBCOMPUTEBASE_DLLMAPPING AlgorithmComputeElementData : 
    public AlgorithmComputeElementDataBase
{
  protected:

    /*==========================  PUBLIC  =================================*/
    
  public:

    typedef AlgorithmComputeElementDataBase Inherited;
    typedef AlgorithmComputeElementData     Self;

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

    void setTask(ComputeAlgorithmDrawTask *pTask);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    ComputeAlgorithmDrawTask *getTask(void);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:
    
    // Variables should all be in AlgorithmComputeElementDataBase.

    ComputeAlgorithmDrawTaskRefPtr _pTask;

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    AlgorithmComputeElementData(void);
    AlgorithmComputeElementData(const AlgorithmComputeElementData &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~AlgorithmComputeElementData(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

#if 0
    virtual void updateData(FieldContainer *pCore,
                            BitVector       whichField,
                            UInt32          origin    );
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

    virtual void resolveLinks(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class AlgorithmComputeElementDataBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const AlgorithmComputeElementData &source);
};

OSG_END_NAMESPACE

#include "OSGAlgorithmComputeElementDataBase.inl"
#include "OSGAlgorithmComputeElementData.inl"

#endif /* _OSGALGORITHMCOMPUTEELEEDATA_H_ */
