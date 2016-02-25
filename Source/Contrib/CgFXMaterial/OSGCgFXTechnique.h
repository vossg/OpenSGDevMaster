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

#ifndef _OSGCGFXTECHNIQUE_H_
#define _OSGCGFXTECHNIQUE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGCgFXTechniqueBase.h"

#include "OSGCG.h"

OSG_BEGIN_NAMESPACE

class DrawEnv;
class CgFXMaterial;

/*! \brief CgFXTechnique class. See \ref
           PageKernelCGFXTechnique for a description.
*/

class OSG_CONTRIBCGFX_DLLMAPPING CgFXTechnique : public CgFXTechniqueBase
{
  private:

    typedef CgFXTechniqueBase Inherited;

    /*==========================  PUBLIC  =================================*/

    static const UInt8 TechniqueValid  = 0x01;
    static const UInt8 ValidationTried = 0x02;

  public:    

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin,
                         BitVector         detail    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void    rebuildState (void            );
    virtual bool    isTransparent(void            ) const;
    virtual UInt32  getNPasses   (void            );
    virtual State  *getState     (UInt32 index = 0);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Timer                                      */
    /*! \{                                                                 */

    bool validate(CgFXMaterial *pMat,
                  DrawEnv      *pEnv);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Parameter Access                             */
    /*! \{                                                                 */
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                Texture specific                              */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:
    
    // Variables should all be in CGFXTechniqueBase.

    CGtechnique _pCGTechnique;
    UInt8       _uiValidationState;

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    CgFXTechnique(void);
    CgFXTechnique(const CgFXTechnique &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~CgFXTechnique(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    void        setTechnique(CGtechnique pTechnique);
    CGtechnique getTechnique(void                  );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    virtual void resolveLinks(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class CgFXTechniqueBase;
    friend class CgFXMaterial;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const CgFXTechnique &source);
};

typedef CgFXTechnique *CgFXTechniqueP;

OSG_END_NAMESPACE

#include "OSGCgFXTechniqueBase.inl"
#include "OSGCgFXTechnique.inl"


#endif /* _OSGCGFXTECHNIQUE_H_ */
