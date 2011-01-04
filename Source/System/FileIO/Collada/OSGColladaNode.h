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

#ifndef _OSGCOLLADANODE_H_
#define _OSGCOLLADANODE_H_

#include "OSGConfig.h"

#if defined(OSG_WITH_COLLADA) || defined(OSG_DO_DOC)

#include "OSGColladaInstantiableElement.h"
#include "OSGColladaElementFactoryHelper.h"
#include "OSGNode.h"

// forward decl
class domLookat;
class domMatrix;
class domRotate;
class domScale;
class domSkew;
class domTranslate;
class domNode;
class domInstance_node;
class domInstance_geometry;
class domInstance_controller;


OSG_BEGIN_NAMESPACE

// forward decl
class ColladaVisualScene;

/*! \ingroup GrpFileIOCollada
    \nohierarchy
 */

class OSG_FILEIO_DLLMAPPING ColladaNode : public ColladaInstantiableElement
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
    /*! \{                                                                 */

    typedef ColladaInstantiableElement Inherited;
    typedef ColladaNode                Self;

    OSG_GEN_INTERNAL_MEMOBJPTR(ColladaNode);

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

    virtual void  read          (void                               );
    virtual Node *createInstance(ColladaInstanceElement *colInstElem);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Access                                                       */
    /*! \{                                                                 */

    Node *getTopNode   (void) const;
    Node *getBottomNode(void) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:
    /*---------------------------------------------------------------------*/
    /*! \name Constructors/Destructor                                      */
    /*! \{                                                                 */
    
             ColladaNode(daeElement    *elem,
                         ColladaGlobal *global);
    virtual ~ColladaNode(void                 );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/


    void handleLookAt   (domLookat    *lookat   );
    void handleMatrix   (domMatrix    *matrix   );
    void handleRotate   (domRotate    *rotate   );
    void handleScale    (domScale     *scale    );
    void handleSkew     (domSkew      *skew     );
    void handleTranslate(domTranslate *translate);

    void handleNode              (domNode                *node          );
    void handleInstanceNode      (domInstance_node       *instNode      );
    void handleInstanceGeometry  (domInstance_geometry   *instGeo       );
    void handleInstanceController(domInstance_controller *instController);

    void appendXForm(Node *xformN);
    void appendChild(Node *childN);       


    static ColladaElementRegistrationHelper _regHelper;

    NodeUnrecPtr _topN;
    NodeUnrecPtr _bottomN;
};

OSG_GEN_MEMOBJPTR(ColladaNode);

OSG_END_NAMESPACE

// #include "OSGColladaNode.inl"

#endif // OSG_WITH_COLLADA

#endif // _OSGCOLLADANODE_H_
