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

#ifndef _OSGVRMLFILE_H_
#define _OSGVRMLFILE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGFileIODef.h"

#include <map>
#include <stack>
#include <vector>

#include "OSGBaseTypes.h"
#include "OSGScanParseSkel.h"
#include "OSGScanParseFieldTypeMapper.h"

#include "OSGField.h"
#include "OSGFieldContainer.h"

#include "OSGVRMLPrototypeHandler.h"

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpFileIOWRL
 */

typedef VRMLNodePrototypeHandler<
    ScanParseFieldTypeMapper<ScanParseSkel> > Parent;

/*! \brief VRML97 Loader (Geometry only)
    \ingroup GrpFileIOWRL
    \ingroup GrpLibOSGFileIO
 */

class OSG_FILEIO_DLLMAPPING VRMLFile : public Parent
{
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef Parent   Inherited;
    typedef VRMLFile Self;

    /*==========================  PUBLIC  =================================*/

  public:

    enum
    {
        CreateNormals       = Inherited::LastOption << 1,
        StripeGeometry      = CreateNormals         << 1,
        LogProtoGeneration  = StripeGeometry        << 1,
        LogObjectGeneration = LogProtoGeneration    << 1,
        PushNames           = LogObjectGeneration   << 1,

        LastOption          = PushNames
    };

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    VRMLFile(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~VRMLFile(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Skel replacements                          */
    /*! \{                                                                 */

    virtual NodeTransitPtr scanStream(std::istream &is);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Skel replacements                          */
    /*! \{                                                                 */

    virtual bool   checkHeader   (      void                      );

    virtual void   handleError   (const Char8  *szErrorText);

    virtual void   beginProto            (const Char8 *szProtoname);
    virtual void   endProtoInterface     (      void);
    virtual void   endProto              (      void);

    virtual void   beginFieldDecl(const Char8  *szFieldType,
                                  const UInt32  uiFieldTypeId,
                                  const Char8  *szFieldName);

    virtual void   endFieldDecl  (void                      );

    virtual void   beginNode     (const Char8 *szNodeTypename,
                                  const Char8 *szNodename);

    virtual void   endNode       (void);

    virtual void   beginScript   (const Char8 *szNodename);

    virtual void   endScript     (void);


    virtual void   beginField    (const Char8  *szFieldname,
                                  const UInt32  uiFieldTypeId);

    virtual void   endField      (void);


    virtual void   addFieldValue(const Char8 *szFieldVal);

    virtual void   addImageValue(      Image *pImage    );


    virtual UInt32 getFieldType (const Char8 *szFieldname);


    virtual void   use          (const Char8 *szName);

    virtual void   addRoute     (const Char8  *szOutNodename,
                                 const Char8  *szOutFieldname,
                                 const Char8  *szInNodename,
                                 const Char8  *szInFieldname    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Helper                                  */
    /*! \{                                                                 */

    void    scanStandardPrototypes  (const Char8  *szFilename);

    void    createStandardPrototypes(void);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    typedef std::map<std::string, FieldContainer *> NameContainerMap;

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

               NodeUnrecPtr                   _pSceneRootNode;

               VRMLNodeHelper *               _pCurrNodeHelper;
    std::stack<VRMLNodeHelper *>              _sNodeHelpers;

               FieldContainerUnrecPtr         _pCurrentFC;
               FieldContainer                *_pCurrentFieldFC;
               EditFieldHandlePtr             _pCurrentField;
    const      FieldDescriptionBase          *_pCurrentFieldDesc;

    std::stack<      FieldContainer       *>  _fcStack;
    std::stack<      EditFieldHandlePtr    >  _fStack;
    std::stack<const FieldDescriptionBase *>  _fdStack;

    NameContainerMap                          _nameFCMap;


    void              initIntExtFieldTypeMapper(void);
    void              initExtIntFieldTypeMapper(void);

    FieldContainer   *findFCByName             (const Char8  *szName,
                                                      Node   *pNode);

    FieldContainer   *findReference            (const Char8 *szName);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    /*!\brief prohibit default function (move to 'public' if needed) */
    VRMLFile(const VRMLFile &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const VRMLFile &source);
};

OSG_END_NAMESPACE

#endif /* _OSGVRMLFILE_H_ */
