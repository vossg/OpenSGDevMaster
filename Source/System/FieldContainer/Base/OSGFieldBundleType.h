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

#ifndef _OSGFIELDBUNDLETYPE_H_
#define _OSGFIELDBUNDLETYPE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGContainerForwards.h"
#include "OSGReflexiveContainerType.h"

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpSystemFieldContainerFuncs
 */

typedef void (*InitBundleF) (ReflexiveContainerType::InitPhase);

/*! \ingroup GrpSystemFieldContainerFuncs
 */

typedef FieldBundleP (*ProtoBundleCreateF)(void);

/*! \ingroup GrpSystemFieldContainer
 */

class OSG_SYSTEM_DLLMAPPING FieldBundleType : public ReflexiveContainerType
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

    FieldBundleType(const Char8                *szName,
                    const Char8                *szParentName       = NULL,
                    const Char8                *szGroupName        = NULL,
                    const UInt32                uiNameSpace        =    0,
                          ProtoBundleCreateF    fPrototypeCreate   = NULL,
                          InitBundleF           fInitMethod        = NULL,
                          InitalInsertDescFunc  descInsertFunc     = NULL,
                          bool                  bDescsAddable      = false,
                          BitVector             bvUnmarkedOnCreate = 0,
                          std::string           szFcdXML           = "",
                          std::string           szTypeDoc          = "");

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~FieldBundleType(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    bool isAbstract   (void                           ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    FieldBundleP getPrototype(void                   ) const;
    //bool         setPrototype(FieldBundleP pPrototype);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Set                                     */
    /*! \{                                                                 */

    FieldBundleP createContainer(void) const;

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

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                  Type information                            */
    /*! \{                                                                 */

    FieldBundleP       _pPrototype;
    ProtoBundleCreateF _fPrototypeCreate;

    InitBundleF        _fInitMethod;
    std::string        _szFcdXML;   
    std::string        _szTypeDoc;  

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Fields                                  */
    /*! \{                                                                 */

	virtual bool initialize(void);
    virtual void terminate (void);

    virtual bool initialize(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    bool initPrototype(void);

    void registerType (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Changed                                 */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   MT Destruction                             */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    typedef ReflexiveContainerType Inherited;

    template <class ParentT>
    friend class ContainerFactoryMixin;


    /*!\brief prohibit default function (move to 'public' if needed) */
    FieldBundleType(const FieldBundleType &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const FieldBundleType &source);
};

OSG_END_NAMESPACE

#define OSGFIELDBUNDLETYPE_HEADER_CVSID "@(#)$Id$"

#include "OSGFieldBundleType.inl"

#endif /* _OSGFIELDBUNDLETYPE_H_ */
