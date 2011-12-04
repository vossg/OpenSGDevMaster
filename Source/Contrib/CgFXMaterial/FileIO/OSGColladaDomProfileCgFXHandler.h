/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                Copyright (C) 2009 by the OpenSG Forum                     *
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

#ifndef _OSGCOLLADADOMPROFILECGFXHANDLER_H_
#define _OSGCOLLADADOMPROFILECGFXHANDLER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGContribCgFXDef.h"
#include "OSGMaterial.h"

#ifdef OSG_WITH_COLLADA

#include "OSGColladaDomProfileHandler.h"
#include "OSGColladaHandlerFactoryHelper.h"

#include <dom/domProfile_CG.h>

OSG_BEGIN_NAMESPACE

class OSG_CONTRIBCGFX_DLLMAPPING ColladaDomProfileCgFXHandler : 
    public ColladaDomProfileHandler
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
    /*! \{                                                                 */

    typedef ColladaDomProfileHandler     Inherited;
    typedef ColladaDomProfileCgFXHandler Self;

    OSG_GEN_INTERNAL_MEMOBJPTR(ColladaDomProfileCgFXHandler);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Reading                                                      */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Access                                                       */
    /*! \{                                                                 */

    virtual void readProfile(domFx_profile_abstract *pProf);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Reading                                                      */
    /*! \{                                                                 */

    virtual MaterialTransitPtr 
        createInstProfile(domFx_profile_abstract *pProf,
                          domEffect              *pEffect,
                          domInstance_effect     *pInstEffect);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Access                                                       */
    /*! \{                                                                 */

    static ColladaDomProfileHandlerTransitPtr create(void);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef domProfile_CG::domTechnique::domPass::domShader domShader;
    typedef domProfile_CG::domTechnique::domPassRef         domPassRef;

    /*---------------------------------------------------------------------*/
    /*! \name Constructors/Destructor                                      */
    /*! \{                                                                 */
    
             ColladaDomProfileCgFXHandler(void);
    virtual ~ColladaDomProfileCgFXHandler(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Access                                                       */
    /*! \{                                                                 */

    std::string getFuncTypeString        (domGl_func_type            func     );
    std::string getBlendEquationString   (domGl_blend_equation_type  eq       );
    std::string getBlendFuncTypeString   (domGl_blend_type           func     );
    std::string getFaceTypeString        (domGl_face_type            face     );
    std::string getMaterialModeTypeString(domGl_material_type        mat      );
    std::string getLogicOpTypeString     (domGl_logic_op_type        logicOp  );
    std::string getStencilOpTypeString   (domGl_stencil_op_type      stopType );
    std::string getBoolStringRep         (std::string                stateName, 
                                          UInt32                     idx, 
                                          bool                       state    );
    std::string getBoolStringRep         (std::string                stateName, 
                                          bool                       state    );

    bool        isCGSampler              (domFx_basic_type_commonRef param    );
    bool        isStateMatrix            (std::string                matName  );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constructors/Destructor                                      */
    /*! \{                                                                 */

    std::string buildCgFXCode      (domProfile_CG *pProf     );

    std::string extractCgBindParams(domShader     *pShader   );
    std::string extractCgStates    (domPassRef     pPass     );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Access                                                       */
    /*! \{                                                                 */

    static ColladaDomProfileHandlerRegHelper _regHelper;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
};

OSG_GEN_MEMOBJPTR(ColladaDomProfileCgFXHandler);

OSG_END_NAMESPACE

#endif // OSG_WITH_COLLADA

#endif // _OSGCOLLADADOMPROFILECGFXHANDLER_H_
