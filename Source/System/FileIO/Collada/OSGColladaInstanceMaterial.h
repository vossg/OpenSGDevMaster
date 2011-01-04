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

#ifndef _OSGCOLLADAINSTANCEMATERIAL_H_
#define _OSGCOLLADAINSTANCEMATERIAL_H_

#include "OSGConfig.h"

#if defined(OSG_WITH_COLLADA) || defined(OSG_DO_DOC)

#include "OSGColladaInstanceElement.h"
#include "OSGColladaMaterial.h"
#include "OSGColladaElementFactoryHelper.h"

#include <dom/domMaterial.h>

OSG_BEGIN_NAMESPACE

// forward decl
class ColladaInstanceEffect;

/*! \ingroup GrpFileIOCollada
    \nohierarchy
 */

class OSG_FILEIO_DLLMAPPING ColladaInstanceMaterial
  : public ColladaInstanceElement
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
    /*! \{                                                                 */

    typedef ColladaInstanceElement  Inherited;
    typedef ColladaInstanceMaterial Self;

    OSG_GEN_INTERNAL_MEMOBJPTR(ColladaInstanceMaterial);

    /*! \nohierarchy
     */
    struct BindInfo
    {
        std::string semantic;
        std::string target;
    };

    typedef std::vector<BindInfo>            BindStore;
    typedef BindStore::iterator              BindStoreIt;
    typedef BindStore::const_iterator        BindStoreConstIt;

    /*! \nohierarchy
     */
    struct BindVertexInfo
    {
        std::string semantic;
        std::string inSemantic;
        UInt32      inSet;
    };

    typedef std::vector<BindVertexInfo>      BindVertexStore;
    typedef BindVertexStore::iterator        BindVertexStoreIt;
    typedef BindVertexStore::const_iterator  BindVertexStoreConstIt;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Create                                                       */
    /*! \{                                                                 */

    static ColladaElementTransitPtr
        create(daeElement *elem, ColladaGlobal *global); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Reading                                                      */
    /*! \{                                                                 */

    virtual void      read   (void                  );
    virtual Material *process(ColladaElement *parent);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Access                                                       */
    /*! \{                                                                 */

    virtual ColladaMaterial *getTargetElem     (void) const;
    virtual domMaterial     *getTargetDOMElem  (void) const;

    const std::string       &getSymbol         (void) const;
    const std::string       &getTarget         (void) const;

    const BindStore         &getBindStore      (void                ) const;
    const BindInfo          *findBindInfo      (
                                      const std::string &semantic   ) const;

    const BindVertexStore   &getBindVertexStore(void                ) const;
    const BindVertexInfo    *findBindVertexInfo(
                                      const std::string &inSemantic,
                                      UInt32             inSet      ) const;

    ColladaInstanceEffect   *getInstanceEffect(void                 ) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:
    /*---------------------------------------------------------------------*/
    /*! \name Constructors/Destructor                                      */
    /*! \{                                                                 */
    
             ColladaInstanceMaterial(daeElement *elem, ColladaGlobal *global);
    virtual ~ColladaInstanceMaterial(void                                   );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

    static ColladaElementRegistrationHelper _regHelper;

    std::string            _symbol;
    std::string            _target;
    BindStore              _bindStore;
    BindVertexStore        _bindVertexStore;
};

OSG_GEN_MEMOBJPTR(ColladaInstanceMaterial);

OSG_END_NAMESPACE

// #include "OSGColladaInstanceMaterial.inl"

#endif // OSG_WITH_COLLADA

#endif // _OSGCOLLADAINSTANCEMATERIAL_H_
