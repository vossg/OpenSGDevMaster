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

#ifndef _OSGCOLLADAMATERIAL_H_
#define _OSGCOLLADAMATERIAL_H_

#include "OSGConfig.h"

#if defined(OSG_WITH_COLLADA) || defined(OSG_DO_DOC)

#include "OSGColladaInstantiableElement.h"
#include "OSGColladaElementFactoryHelper.h"
#include "OSGColladaInstInfo.h"
#include "OSGMaterial.h"

OSG_BEGIN_NAMESPACE

// forward decl
class ColladaInstanceMaterial;

// forward decl
class ColladaInstanceMaterial;

/*! \ingroup GrpFileIOCollada
    \nohierarchy
 */

class OSG_FILEIO_DLLMAPPING ColladaMaterial : public ColladaInstantiableElement
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
    /*! \{                                                                 */

    typedef ColladaInstantiableElement Inherited;
    typedef ColladaMaterial            Self;

    OSG_GEN_INTERNAL_MEMOBJPTR(ColladaMaterial);

    class ColladaMaterialInstInfo : public ColladaInstInfo
    {
        /*==========================  PUBLIC  =============================*/
      public:
        /*-----------------------------------------------------------------*/
        /*! \name Types                                                    */
        /*! \{                                                             */

        typedef ColladaInstInfo          Inherited;
        typedef ColladaMaterialInstInfo  Self;

        OSG_GEN_INTERNAL_MEMOBJPTR(ColladaMaterialInstInfo);

        /*! \}                                                             */
        /*-----------------------------------------------------------------*/
        /*! \name Create                                                   */
        /*! \{                                                             */

        static  ColladaInstInfoTransitPtr
            create(ColladaElement          *colInstParent,
                   ColladaInstanceMaterial *colInst       );

        /*! \}                                                             */
        /*-----------------------------------------------------------------*/
        /*! \name Process                                                  */
        /*! \{                                                             */

        virtual void process(void);

        /*! \}                                                             */
        /*=========================  PROTECTED  ===========================*/
      protected:
        /*-----------------------------------------------------------------*/
        /*! \name Constructors/Destructor                                  */
        /*! \{                                                             */

                 ColladaMaterialInstInfo(
                     ColladaElement          *colInstParent,
                     ColladaInstanceMaterial *colInst       );
        virtual ~ColladaMaterialInstInfo(void               );

        /*! \}                                                             */
        /*-----------------------------------------------------------------*/
    };

    OSG_GEN_MEMOBJPTR(ColladaMaterialInstInfo);

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

    virtual void      read          (ColladaElement  *colElemParent);
    virtual Material *createInstance(ColladaInstInfo *colInstInfo  );

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:
    /*---------------------------------------------------------------------*/
    /*! \name Constructors/Destructor                                      */
    /*! \{                                                                 */

             ColladaMaterial(daeElement *elem, ColladaGlobal *global);
    virtual ~ColladaMaterial(void                                   );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

    static ColladaElementRegistrationHelper _regHelper;
};

OSG_GEN_MEMOBJPTR(ColladaMaterial);

OSG_END_NAMESPACE

#endif // OSG_WITH_COLLADA

#endif // _OSGCOLLADAMATERIAL_H_
