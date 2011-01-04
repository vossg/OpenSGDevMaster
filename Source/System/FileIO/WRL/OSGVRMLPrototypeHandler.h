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

#ifndef _OSGVRMLPROTOTYPEHANDLER_H_
#define _OSGVRMLPROTOTYPEHANDLER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGBaseTypes.h"
#include "OSGBaseFunctions.h"

#include <stack>

#include "OSGVRMLNodeHelper.h"

#include <string>

OSG_BEGIN_NAMESPACE

/*! \brief VRML97 Loader prototype handler
    \ingroup GrpFileIOWRLObj
    \ingroup GrpLibOSGFileIO
 */

template <class BaseT>
class VRMLNodePrototypeHandler : public BaseT
{
    /*==========================  PRIVATE  ================================*/
  private:


    typedef VRMLNodePrototypeHandler<BaseT> Self;

    /*==========================  PUBLIC  =================================*/
  public :

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    VRMLNodePrototypeHandler(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~VRMLNodePrototypeHandler(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Skel replacements                          */
    /*! \{                                                                 */

    virtual void beginProto            (const Char8 *szProtoname);
    virtual void endProtoInterface     (      void);
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

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef BaseT Inherited;

#ifndef WIN32
    /*! \nohierarchy
     */
    struct string_hash
    {
        size_t operator()(const std::string &s) const
        {
            return OSG_STDEXTENSION_NAMESPACE::__stl_hash_string(s.c_str());
        }
    };
#endif

#ifdef OSG_STL_HAS_HASH_MAP
#ifdef OSG_USE_HASH_COMPARE
    typedef
        OSG_STDEXTENSION_NAMESPACE::hash_map<
            const Char8    *,
                  VRMLNodeHelper *,
                  HashCmpString                   > NameHelperMap;
#else
    typedef
        OSG_STDEXTENSION_NAMESPACE::hash_map<
              const std::string,
                    VRMLNodeHelper *,
                    string_hash                   > NameHelperMap;
#endif
#else
    typedef
        std::map<const std::string,
                       VRMLNodeHelper *           > NameHelperMap;
#endif

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    /** The current helper that we are actively adding fields too and 
        building up. */

    VRMLNodeHelper     *_pCurrentHelper;

    /** Map from proto name to the helper to handle that proto type. */
    NameHelperMap       _mNodeHelperHash;


    VRMLNodeHelper *findNodeHelper    (const Char8          *szNodeTypename);

    virtual void    preStandardProtos (      void);
    virtual void    postStandardProtos(      void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    /*!\brief prohibit default function (move to 'public' if needed) */
    VRMLNodePrototypeHandler(const VRMLNodePrototypeHandler &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const VRMLNodePrototypeHandler &source);
};

OSG_END_NAMESPACE

#include "OSGVRMLPrototypeHandler.inl"

#endif /* _OSGVRMLPROTOTYPEHANDLER_H_ */
