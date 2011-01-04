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

#ifndef _OSGCOLLADAINSTANCEGEOMETRY_H_
#define _OSGCOLLADAINSTANCEGEOMETRY_H_

#include "OSGConfig.h"

#if defined(OSG_WITH_COLLADA) || defined(OSG_DO_DOC)

#include "OSGColladaInstanceElement.h"
#include "OSGColladaGeometry.h"
#include "OSGColladaInstanceMaterial.h"
#include "OSGColladaElementFactoryHelper.h"

#include <dom/domGeometry.h>

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpFileIOCollada
    \nohierarchy
 */

class OSG_FILEIO_DLLMAPPING ColladaInstanceGeometry
    : public ColladaInstanceElement
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
    /*! \{                                                                 */

    typedef ColladaInstanceElement  Inherited;
    typedef ColladaInstanceGeometry Self;

    OSG_GEN_INTERNAL_MEMOBJPTR(ColladaInstanceGeometry);

    // map material symbol to material instance
    typedef std::map<std::string,
                     ColladaInstanceMaterialRefPtr>  MaterialMap;
    typedef MaterialMap::iterator                    MaterialMapIt;
    typedef MaterialMap::const_iterator              MaterialMapConstIt;

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

    virtual void  read   (void                  );
    virtual Node *process(ColladaElement *parent);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Access                                                       */
    /*! \{                                                                 */

    virtual ColladaGeometry *getTargetElem   (void) const;
    virtual daeElement      *getTargetDOMElem(void) const;

    const MaterialMap       &getMaterialMap  (void) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:
    /*---------------------------------------------------------------------*/
    /*! \name Constructors/Destructor                                      */
    /*! \{                                                                 */
    
             ColladaInstanceGeometry(daeElement *elem, ColladaGlobal *global);
    virtual ~ColladaInstanceGeometry(void                                   );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

    static ColladaElementRegistrationHelper _regHelper;

    MaterialMap _matMap;
};

OSG_GEN_MEMOBJPTR(ColladaInstanceGeometry);

OSG_END_NAMESPACE

// #include "OSGColladaInstanceGeometry.inl"

#endif // OSG_WITH_COLLADA

#endif // _OSGCOLLADAINSTANCEGEOMETRY_H_
