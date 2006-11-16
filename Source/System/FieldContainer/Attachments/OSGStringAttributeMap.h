/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
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

#ifndef _OSGSTRINGATTRIBUTEMAP_H_
#define _OSGSTRINGATTRIBUTEMAP_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGStringAttributeMapBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief StringAttributeMap class. See \ref 
           PageSystemStringAttributeMap for a description.
*/

class OSG_SYSTEM_DLLMAPPING StringAttributeMap : public StringAttributeMapBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef StringAttributeMapBase Inherited;
    typedef StringAttributeMap     Self;

    typedef PointerBuilder<StringAttributeMap>::ObjPtr           ObjPtr;
    typedef PointerBuilder<StringAttributeMap>::ObjPtrConst      ObjPtrConst;

    typedef PointerBuilder<StringAttributeMap>::ObjConstPtr      ObjConstPtr;
    typedef PointerBuilder<StringAttributeMap>::ObjConstPtrConst ObjConstPtrConst;

    typedef PointerBuilder<StringAttributeMap>::ObjPtrArg        ObjPtrArg;
    typedef PointerBuilder<StringAttributeMap>::ObjPtrConstArg   ObjPtrConstArg;

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField, 
                         UInt32            origin    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector  bvFlags  = 0) const;


    /*! \}                                                                 */

    inline const MFString& getKeys() const;

    void setAttribute(const std::string& key, const std::string& value);

    inline bool hasAttribute(const std::string& key) const;

    bool getAttribute(const std::string& key, std::string& value) const;

    inline const std::string getAttribute(const std::string& key) const;

    inline std::string& operator[](const std::string& key);


    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in StringAttributeMapBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    StringAttributeMap(void);
    StringAttributeMap(const StringAttributeMap &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~StringAttributeMap(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);


    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class StringAttributeMapBase;

    template<class ContainerFactoryT>
    friend struct CPtrConstructionFunctions;

    template<class ContainerFactoryT>
    friend struct PtrConstructionFunctions;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const StringAttributeMap &source);
};

typedef StringAttributeMap *StringAttributeMapP;

typedef StringAttributeMap::ObjPtr           StringAttributeMapPtr;
typedef StringAttributeMap::ObjPtrConst      StringAttributeMapPtrConst;

typedef StringAttributeMap::ObjConstPtr      StringAttributeMapConstPtr;
typedef StringAttributeMap::ObjConstPtrConst StringAttributeMapConstPtrConst;

typedef StringAttributeMap::ObjPtrArg        StringAttributeMapPtrArg;
typedef StringAttributeMap::ObjPtrConstArg   StringAttributeMapPtrConstArg;

/*---------------------------------------------------------------------*/
/*! \name              StringAttributeMap Util                         */
/*! \{                                                                 */
StringAttributeMapPtr stringAttributeMap(AttachmentContainerPtr container);
/*! \}                                                                 */

OSG_END_NAMESPACE

#include "OSGStringAttributeMapBase.inl"
#include "OSGStringAttributeMap.inl"

#define OSGSTRINGATTRIBUTEMAP_HEADER_CVSID "@(#)$Id$"

#endif /* _OSGSTRINGATTRIBUTEMAP_H_ */
