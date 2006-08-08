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

#ifndef _OSGSWITCHMATERIAL_H_
#define _OSGSWITCHMATERIAL_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGSwitchMaterialBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief SwitchMaterial class. See \ref 
           PageSystemSwitchMaterial for a description.
*/

class OSG_SYSTEM_DLLMAPPING SwitchMaterial : public SwitchMaterialBase
{
  public:

    typedef SwitchMaterialBase                           Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg  whichField, 
                         UInt32             origin    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Rendering                                  */
    /*! \{                                                                 */

#if OLD
    virtual void       draw              (DrawFunctor& func,
                                          DrawActionBase * action );

    virtual void       draw              (Geometry* geo,
                                          DrawActionBase * action);

    virtual StatePtr   makeState         (void);
#endif

    virtual void       rebuildState (void            );

    virtual StatePtr   getState     (UInt32 index = 0);
    virtual UInt32     getNPasses   (void            ) const;

    virtual bool       isTransparent(void            ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Access                                    */
    /*! \{                                                                 */

    void        addMaterial       (MaterialPtr mat  );
    void        subMaterial       (MaterialPtr mat  );

    bool        hasMaterial       (MaterialPtr mat  );

    MaterialPtr getMaterial       (UInt32      index);
    MaterialPtr getCurrentMaterial(void             );

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in SwitchMaterialBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    SwitchMaterial(void);
    SwitchMaterial(const SwitchMaterial &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SwitchMaterial(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class SwitchMaterialBase;

    template<class ContainerFactoryT>
    friend struct CPtrConstructionFunctions;

    template<class ContainerFactoryT>
    friend struct PtrConstructionFunctions;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const SwitchMaterial &source);
};

typedef SwitchMaterial              *SwitchMaterialP;

OSG_END_NAMESPACE

#include "OSGSwitchMaterialBase.inl"
#include "OSGSwitchMaterial.inl"

#define OSGSWITCHMATERIAL_HEADER_CVSID "@(#)$Id: OSGSwitchMaterial.h,v 1.1.2.2 2006/07/28 06:21:54 vossg Exp $"

#endif /* _OSGSWITCHMATERIAL_H_ */
