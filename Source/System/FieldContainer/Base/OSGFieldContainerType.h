/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2003 by the OpenSG Forum                          *
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

#ifndef _OSGFIELDCONTAINERTYPE_H_
#define _OSGFIELDCONTAINERTYPE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGContainerForwards.h"
#include "OSGReflexiveContainerType.h"
#include "OSGFieldContainerPtr.h"
//#include "OSGAspectStore.h"

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpSystemFieldContainerFuncs
 */

typedef void (*InitContainerF) (ReflexiveContainerType::InitPhase);

/*! \ingroup GrpSystemFieldContainerFuncs
 */

typedef FieldContainerPtr (*PrototypeCreateF)(void);

/*! \ingroup GrpSystemFieldContainer
 */

class OSG_SYSTEM_DLLMAPPING FieldContainerType : public ReflexiveContainerType
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                      dcast                                   */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name        General Fieldcontainer Declaration                    */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    FieldContainerType(bool foo,
                       const Char8                *szName,
                       const Char8                *szParentName     = NULL,
                       const Char8                *szGroupName      = NULL,
                       const UInt32                uiNameSpace      =    0,
                             PrototypeCreateF      fPrototypeCreate = NULL,
                             InitContainerF        fInitMethod      = NULL,
                             InitalInsertDescFunc  descInsertFunc   = NULL,
                             bool                  bDescsAddable    = false);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~FieldContainerType(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    bool isAbstract  (void) const;

    bool isNode      (void) const;
    bool isNodeCore  (void) const;
    bool isAttachment(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    FieldContainerPtr getPrototype(void                        ) const;
    //bool              setPrototype(FieldContainerPtr pPrototype);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Set                                     */
    /*! \{                                                                 */

    FieldContainerPtr createContainer(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   your_category                              */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Container Access                             */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Binary Access                              */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   your_operators                             */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Assignment                                */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Comparison                                */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    virtual void dump(      UInt32    uiIndent = 0, 
                      const BitVector bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                  Type information                            */
    /*! \{                                                                 */

    enum BaseType
    {
        IsFieldContainer,
        IsNode,
        IsNodeCore,
        IsAttachment
    };


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Fields                                  */
    /*! \{                                                                 */

    FieldContainerType(const FieldContainerType &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    BaseType          _baseType;

    FieldContainerPtr _pPrototype;
    PrototypeCreateF  _fPrototypeCreate;

    InitContainerF    _fInitMethod;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Changed                                 */
    /*! \{                                                                 */

	virtual bool initialize(void);
    virtual void terminate (void);

    virtual bool initialize(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   MT Destruction                             */
    /*! \{                                                                 */

    bool initPrototype(void);
    bool initBaseType (void);

    void registerType (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

#ifdef OSG_MT_CPTR_ASPECT
    FieldContainerPtr createAspectCopy(void) const;
#endif

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    template <class ParentT>
    friend class ContainerFactoryMixin;

    template <class AttachmentDescT>
    friend class DynFieldAttachment;

    friend class ChangeList;

    typedef ReflexiveContainerType Inherited;

    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const FieldContainerType &source);
};

OSG_END_NAMESPACE

#define OSGFIELDCONTAINERTYPE_HEADER_CVSID "@(#)$Id$"

#include "OSGFieldContainerType.inl"

#endif /* _OSGFIELDCONTAINERTYPE_H_ */
