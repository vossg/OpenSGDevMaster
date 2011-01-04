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

#ifndef _OSGPRIMEMATERIAL_H_
#define _OSGPRIMEMATERIAL_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGPrimeMaterialBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief PrimeMaterial class. See \ref
    PageSystemPrimeMaterial for a description.

    \ingroup GrpSystemMaterialBase
    \ingroup GrpLibOSGSystem
    \includebasedoc
 */

class OSG_SYSTEM_DLLMAPPING PrimeMaterial : public PrimeMaterialBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef PrimeMaterialBase Inherited;
    typedef PrimeMaterial     Self;

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

    virtual PrimeMaterial *finalize(MaterialMapKey  oKey,
                                    Window         *pWin);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void    rebuildState(void            ) = 0;
    virtual State  *getState    (UInt32 index = 0);
    virtual UInt32  getNPasses  (void            );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:


    StateUnrecPtr _pState;  // !!! TODO is that MT safe?

    // Yes, but not efficient. Every material has as many States as there
    // are aspects, each of which itself is threadsafe (i.e. multibuffered).
    // A single State per Material would be better. I'm just not sure how to
    // initialize it. :( DR
    // Actually, no, it isn't!!! Multiple materials updating the same aspect 
    // in different threads make this crash!!! DR

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    PrimeMaterial(void);
    PrimeMaterial(const PrimeMaterial &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~PrimeMaterial(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
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

    friend class FieldContainer;
    friend class PrimeMaterialBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const PrimeMaterial &source);
};

typedef PrimeMaterial *PrimeMaterialP;

OSG_END_NAMESPACE

#include "OSGPrimeMaterialBase.inl"
#include "OSGPrimeMaterial.inl"

#endif /* _OSGPRIMEMATERIAL_H_ */
