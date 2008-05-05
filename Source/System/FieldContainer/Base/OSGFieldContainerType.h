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
//#include "OSGAspectStore.h"

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpSystemFieldContainerFuncs
 */

typedef void (*InitContainerF) (ReflexiveContainerType::InitPhase);
typedef void (*ExitContainerF) (ReflexiveContainerType::InitPhase);

/*! \ingroup GrpSystemFieldContainerFuncs
 */

typedef FieldContainer *(*PrototypeCreateF)(BitVector);

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

    FieldContainerType(const Char8                *szName,
                       const Char8                *szParentName       = NULL,
                       const Char8                *szGroupName        = NULL,
                       const UInt32                uiNameSpace        =    0,
                             PrototypeCreateF      fPrototypeCreate   = NULL,
                             InitContainerF        fInitMethod        = NULL,
                             ExitContainerF        fExitMethod        = NULL,
                             InitalInsertDescFunc  descInsertFunc     = NULL,
                             bool                  bDescsAddable      = false,
                             BitVector             bvUnmarkedOnCreate = 0,
                             std::string           fcdXML             = "",
                             std::string           typeDoc            = "");

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

    FieldContainer *getPrototype    (void) const;
    std::string     getFcdXML       (void) const;
    std::string     getDocumentation(void) const;

    //bool              setPrototype(FieldContainerPtr pPrototype);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Set                                     */
    /*! \{                                                                 */

    FieldContainerTransitPtr createContainer(void) const;

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

    FieldContainer   *_pPrototype;
    PrototypeCreateF  _fPrototypeCreate;

    InitContainerF    _fInitMethod;
    ExitContainerF    _fExitMethod;

    std::string       _fcdXML;
    std::string       _typeDoc;

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
    FieldContainer *createAspectCopy(UInt32 uiContainerId) const;
#endif

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    template <class ParentT>
    friend class ContainerFactory;

    template <class AttachmentDescT>
    friend class DynFieldAttachment;

    friend class ChangeList;

    typedef ReflexiveContainerType Inherited;

    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const FieldContainerType &source);
};

OSG_END_NAMESPACE

#include "OSGFieldContainerType.inl"

#endif /* _OSGFIELDCONTAINERTYPE_H_ */
