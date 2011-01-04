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

#ifndef _OSGLOADER_H_
#define _OSGLOADER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGSystemDef.h"
#include "OSGBaseTypes.h"
#include "OSGScanParseSkel.h"
#include "OSGScanParseFieldTypeMapper.h"

#include "OSGNode.h"
#include "OSGField.h"
#include "OSGFieldContainer.h"

#include <stack>
#include <map>
#include <string>

OSG_BEGIN_NAMESPACE

/*! \brief native osg loader (vrml syntax)
    \ingroup GrpSystemFileIOOSG
    \ingroup GrpLibOSGSystem
 */

class OSG_SYSTEM_DLLMAPPING OSGLoader :
    public ScanParseFieldTypeMapper<ScanParseSkel>
{
    /*==========================  PRIVATE  ================================*/

  private:

    typedef ScanParseFieldTypeMapper<ScanParseSkel   >       Inherited;
    typedef std::map                <std::string,
                                     FieldContainer *>       NamedFCMap;
    typedef OSGLoader                                        Self;

    typedef boost::function<FieldContainer *(const Char8 *)> Resolver; 

  public :

    typedef boost::function<void(FieldContainer * const)> Functor;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    OSGLoader(const std::vector<Functor> &endNodeFunctors);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~OSGLoader(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                Skel replacements                             */
    /*! \{                                                                 */

    NodeTransitPtr           scanStream         (std::istream &is,
                                                 Resolver      fResolver);
    FieldContainerTransitPtr scanStreamContainer(std::istream &is,
                                                 Resolver      fResolver);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                Skel replacements                             */
    /*! \{                                                                 */

    virtual bool    checkHeader       (      void                     );

    virtual void    beginNode         (const Char8  *szNodeTypename,
                                       const Char8  *szNodename       );

    virtual void    endNode           (void);

    virtual void    nullNode          (void);

    virtual void    use               (const Char8  *szName           );

    virtual void    beginField        (const Char8  *szFieldname,
                                       const UInt32  uiFieldTypeId    );

    virtual void    endField          (void                           );

    virtual void    addFieldValue     (const Char8  *szFieldVal       );

    virtual Int32   mapExtIntFieldType(const Char8  *szFieldname,
                                       const Int32   iFieldTypeId     );

    virtual UInt32  getFieldType      (const Char8  *szFieldname      );

    virtual void    addRoute          (const Char8  *szOutNodename,
                                       const Char8  *szOutFieldname,
                                       const Char8  *szInNodename,
                                       const Char8  *szInFieldname    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    virtual FieldContainer *getReference (const Char8 *szName);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

          FieldContainerUnrecPtr                _pCurrentFC;
          NodeUnrecPtr                          _pRootNode;
          FieldContainerUnrecPtr                _pRootContainer;
          EditFieldHandlePtr                    _pCurrentField;
    const FieldDescriptionBase                 *_pCurrentFieldDesc;
          NamedFCMap                            _defMap;
          bool                                  _bReadContainer;
          Resolver                              _fResolver;
    const std::vector<Functor>                 &_endNodeFunctors;

          std::stack<      FieldContainerUnrecPtr>  _fcStack;
          std::stack<      EditFieldHandlePtr    >  _fStack;
          std::stack<const FieldDescriptionBase *>  _fdStack;
    
          BitVector                                _bvChanged;
          std::stack<      BitVector             > _sChangedStack;

    void              initFieldTypeMapper   (      void                      );

    void              setFieldContainerValue(      FieldContainer   *pNewNode);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    /*!\brief prohibit default function (move to 'public' if needed) */
    OSGLoader(const OSGLoader &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const OSGLoader &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

// class pointer

typedef OSGLoader *OSGLoaderP;

OSG_END_NAMESPACE

#endif /* _OSGLOADER_H_ */
