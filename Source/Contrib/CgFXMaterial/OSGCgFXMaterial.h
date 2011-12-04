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

#ifndef _OSGCGFXMATERIAL_H_
#define _OSGCGFXMATERIAL_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGCgFXMaterialBase.h"
#include "OSGCgFXTechnique.h"
#include "OSGShaderProgramVariables.h"
#include "OSGTextureObjChunk.h"

#include "OSGCG.h"

OSG_BEGIN_NAMESPACE

class CgFXPassChunk;
class CgFXTechnique;

class ColladaDomProfileCgFXHandler;

/*! \brief CgFXMaterial class. See \ref
           PageKernelCGFXMaterial for a description.
*/

class OSG_CONTRIBCGFX_DLLMAPPING CgFXMaterial : public CgFXMaterialBase
{
  private:

    typedef CgFXMaterialBase Inherited;

    /*==========================  PUBLIC  =================================*/

  public:

    enum
    {
        CgProjection           = 0x0000,
        CgModelViewProjection  = 0x0001,

        CgModelView            = 0x0002,
        CgModelViewI           = 0x0003,
        CgModelViewIT          = 0x0004,

        CgModel                = 0x0005,
        CgModelI               = 0x0006,
        CgModelIT              = 0x0007,

        CgView                 = 0x0008,
        CgViewI                = 0x0009,
        CgViewIT               = 0x000A,

        CgViewProjection       = 0x000B,

        CgTime                 = 0x000C
    };

    enum ParamValueSource 
    {
        DEFAULT, 
        CURRENT 
    };

    static const UInt32 CgProjectionMask          = 0x0001 << CgProjection;
    static const UInt32 CgModelViewProjectionMask = 
        0x0001 << CgModelViewProjection;

    static const UInt32 CgModelViewMask           = 0x0001 << CgModelView;
    static const UInt32 CgModelViewIMask          = 0x0001 << CgModelViewI;
    static const UInt32 CgModelViewITMask         = 0x0001 << CgModelViewIT;

    static const UInt32 CgModelMask               = 0x0001 << CgModel;
    static const UInt32 CgModelIMask              = 0x0001 << CgModelI;
    static const UInt32 CgModelITMask             = 0x0001 << CgModelIT;

    static const UInt32 CgViewMask                = 0x0001 << CgView;
    static const UInt32 CgViewIMask               = 0x0001 << CgViewI;
    static const UInt32 CgViewITMask              = 0x0001 << CgViewIT;

    static const UInt32 CgViewProjectionMask      = 0x0001 << CgViewProjection;

    static const UInt32 CgTimeMask                = 0x0001 << CgTime;


    static const UInt32 NumStateVars = CgTime + 1;

    static const std::string FALBACK_MATERIAL_TECHNIQUE_NAME;

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

    virtual PrimeMaterial *finalize     (MaterialMapKey  oKey,
                                         Window         *pWin);

    virtual bool           isTransparent(void                ) const;
  
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Timer                                      */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Parameter Access                             */
    /*! \{                                                                 */

    template<class ValueT>
    bool updateUniformVariable(const Char8 *name, const ValueT &value);

    template<class ValueT>
    bool getUniformVariable   (const Char8 *name,       ValueT &value);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Parameter Access                             */
    /*! \{                                                                 */

    bool setActiveTechnique(const std::string &techniqueName);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Parameter Access                             */
    /*! \{                                                                 */

    std::vector<std::string> getAvailableTechniques(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Parameter Access                             */
    /*! \{                                                                 */

    CgFXTechnique *getTechnique(const std::string &techniqueName) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    static bool checkForCgError(const Char8     *szSituation, 
                                      CGcontext  pCGcontext );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                Texture specific                              */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:
    
    // Variables should all be in CGFXMaterialBase.
    CGcontext   _pCGcontext;
    CGeffect    _pCGeffect;

    std::string _vStateVarNames[NumStateVars];

    // index of the technique in _mfTechniques to use for this material
    UInt32      _pTechIdx; 
    bool        _mDelayTextureExtraction;
    bool        _bForceUseFallback;

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    CgFXMaterial(void);
    CgFXMaterial(const CgFXMaterial &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~CgFXMaterial(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    void onCreate (const CgFXMaterial *source      = NULL);
    void onDestroy(      UInt32        uiContainerId     );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

           UInt32 handleGL       (DrawEnv                 *pEnv, 
                                  UInt32                   id, 
                                  Window::GLObjectStatusE  mode,
                                  UInt32                   uiOptions);

    static void   handleDestroyGL(DrawEnv                 *pEnv, 
                                  UInt32                   id, 
                                  Window::GLObjectStatusE  mode     );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    void readEffectFile        (      void                      );
    void processEffectString   (      void                      );

    void extractParameters     (      void                      );
    void updateUniformVariables(      void                      );

    template<class ValueT>
    bool addUniformVariable    (const Char8          *name, 
                                const ValueT         &value     );

    void addVariable           (      ShaderVariable *pVar      );
    const ShaderVariable *getVariable(const Char8    *name) const;

    
    void initContext           (      void                      );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

          CGeffect     getEffect       (void) const;
    const std::string *getStateVarNames(void) const;

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
    friend class CgFXMaterialBase;
    friend class CgFXPassChunk;
    friend class CgFXTechnique;

    friend class ColladaDomProfileCgFXHandler;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const CgFXMaterial &source);
};

typedef CgFXMaterial *CgFXMaterialP;

OSG_END_NAMESPACE

#include "OSGCgFXMaterialBase.inl"
#include "OSGCgFXMaterial.inl"

#endif /* _OSGCGFXMATERIAL_H_ */
