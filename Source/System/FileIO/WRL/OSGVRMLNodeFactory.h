/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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

#ifndef _OSGVRMLNODEFACTORY_H_
#define _OSGVRMLNODEFACTORY_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGBaseTypes.h"
#include "OSGBaseFunctions.h"

#ifdef OSG_STL_HAS_HASH_MAP
#ifdef OSG_HASH_MAP_AS_EXT
#else
#include <hash_map>
#endif
#else
#include <map>
#endif

#include <stack>

#include "OSGNode.h"
#include "OSGNodeCore.h"
#include "OSGFieldContainerAttachment.h"
#include "OSGGroup.h"
#include "OSGGeometry.h"

#include "OSGVRMLNodeDescs.h"

OSG_BEGIN_NAMESPACE

//! VRML97 Loader prototype handler 
//! \ingroup GrpSystemDrawablesGeometrymetryLoaderLib

template <class BaseT>
class VRMLNodeFactory : public BaseT
{
    /*==========================  PRIVATE  ================================*/
  private:

#ifdef OSG_STL_HAS_HASH_MAP
#ifdef OSG_USE_HASH_COMPARE
    typedef 
        OSG_STDEXTENSION_NAMESPACE::hash_map<
            const Char8  *,  
            VRMLNodeDesc *,
            HashCmpString> NodeNameDescHash;
#else
    typedef 
        OSG_STDEXTENSION_NAMESPACE::hash_map<
            const Char8  *,  
            VRMLNodeDesc *, 
            OSG_STDEXTENSION_NAMESPACE::hash<const Char8 *>, 
            EQString                                      > NodeNameDescHash;  
#endif
#else
    typedef 
        std::map<     const Char8 *,  VRMLNodeDesc  *, 
                                      LTString       > NodeNameDescHash;
#endif

    typedef VRMLNodeFactory<BaseT> Self;
    
    /*==========================  PUBLIC  =================================*/
  public :

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    VRMLNodeFactory(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~VRMLNodeFactory(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Skel replacements                          */
    /*! \{                                                                 */

    virtual void beginProto            (const Char8 *szProtoname);
    virtual void endProto              (      void);

    virtual void beginEventInDecl      (const Char8 *szEventType,
                                        const UInt32  uiFieldTypeId,
                                        const Char8 *szEventName); 

    virtual void beginEventOutDecl     (const Char8 *szEventType,
                                        const UInt32  uiFieldTypeId,
                                        const Char8 *szEventName); 

    virtual void beginFieldDecl        (const Char8  *szFieldType,
                                        const UInt32  uiFieldTypeId,
                                        const Char8  *szFieldName); 

    virtual void endFieldDecl          (      void);

    virtual void beginExposedFieldDecl (const Char8  *szFieldType,
                                        const UInt32  uiFieldTypeId,
                                        const Char8  *szFieldName); 

    virtual void endExposedFieldDecl   (      void);

    virtual void addFieldValue         (const Char8 *szFieldVal);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    void dumpTable(void);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    typedef BaseT Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    VRMLNodeDesc     *_pCurrentNodeDesc;
    NodeNameDescHash  _mNodeDescHash;

    bool              _bInFieldProto;
    bool              _bIgnoreProto;


    VRMLNodeDesc *findNodeDesc     (const Char8        *szNodeTypename);
    void          addNodeDesc      (const Char8        *szNodeTypename,
                                          VRMLNodeDesc *pDesc);

    virtual void preStandardProtos (      void);
    virtual void postStandardProtos(      void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    /*!\brief prohibit default function (move to 'public' if needed) */
    VRMLNodeFactory(const VRMLNodeFactory &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const VRMLNodeFactory &source);
};

OSG_END_NAMESPACE

#include "OSGVRMLNodeFactory.inl"

#define OSGVRMLNODEFACTORY_HEADER_CVSID "@(#)$Id$"

#endif /* _OSGVRMLNODEFACTORY_H_ */
