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

#ifndef _OSGCONTAINERCREATEMIXIN_H_
#define _OSGCONTAINERCREATEMIXIN_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGCompileTimeFunctions.h"
#ifndef OSG_WINCE
#include "OSGThreadManager.h"
#endif
#include "OSGChangeList.h"
#include "OSGThread.h"

#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_pointer.hpp>

OSG_BEGIN_NAMESPACE

template <class ContainerFactoryT>    
struct CPtrConstructionFunctions
{
    template <class ObjectT>
    static void newPtr(      typename ObjectT::ObjPtr &result, 
                       const          ObjectT         *prototypeP);

    template <class ObjectT>
    static void newPtr(      typename ObjectT::ObjPtr &result);

    template <class ObjectT>
    static typename ObjectT::     ObjPtr constructPtr(      ObjectT *pObj);

    template <class ObjectT>
    static typename ObjectT::ObjConstPtr constructPtr(const ObjectT *pObj);
};

template <class ContainerFactoryT>    
struct PtrConstructionFunctions
{
    template <class ObjectT>
    static void newPtr       (      typename ObjectT::ObjPtr &result, 
                              const          ObjectT         *prototypeP);

    template <class ObjectT>
    static void newPtr       (      typename ObjectT::ObjPtr &result);

#ifdef OSG_MT_CPTR_ASPECT
    template <class ObjectT>
    static void newAspectCopy(      typename ObjectT::ObjPtr &result, 
                              const          ObjectT         *prototypeP);
#endif

    template <class ObjectT>
    static       ObjectT *constructPtr(      ObjectT *pObj);

    template <class ObjectT>
    static const ObjectT *constructPtr(const ObjectT *pObj);
};

template <class ParentT>
class PtrCreateMixin : public ParentT
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                      dcast                                   */
    /*! \{                                                                 */

    typedef          ParentT                  Inherited;

    typedef          PtrCreateMixin<ParentT>  Self;

    typedef typename Inherited::Desc          Desc;

    typedef typename Desc::ContainerFactoryT  ContainerFactory;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name        General Fieldcontainer Declaration                    */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Set                                     */
    /*! \{                                                                 */

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

/*
    struct CPtrConstructionFunctions
    {
        template <class ObjectT>
        static void newPtr(      typename ObjectT::Ptr &result, 
                           const          ObjectT      *prototypeP);

        template <class ObjectT>
        static void newPtr(typename ObjectT::Ptr &result);

        template <class ObjectT>
        static typename ObjectT::Ptr constructPtr(ObjectT *pObj);
    };
    
    struct PtrConstructionFunctions
    {
        template <class ObjectT>
        static void newPtr(      typename ObjectT::Ptr &result, 
                           const          ObjectT      *prototypeP);

        template <class ObjectT>
        static void newPtr(typename ObjectT::Ptr &result);

        template <class ObjectT>
        static typename ObjectT *constructPtr(ObjectT *pObj);
    };
 */

    typedef CPtrConstructionFunctions<ContainerFactory> CPtrConstructionFuncs;
    typedef PtrConstructionFunctions <ContainerFactory>  PtrConstructionFuncs;

    /*---------------------------------------------------------------------*/
    /*! \name                  Type information                            */
    /*! \{                                                                 */

    template <class ObjectT>
    static void newPtr       (      typename ObjectT::ObjPtr &result, 
                              const          ObjectT         *prototypeP);

    template <class ObjectT>
    static void newPtr       (      typename ObjectT::ObjPtr &result);

#ifdef OSG_MT_CPTR_ASPECT
    template <class ObjectT>
    static void newAspectCopy(      typename ObjectT::ObjPtr &result,
                              const          ObjectT         *prototypeP);
#endif

    template <class ObjectT>
    static typename ObjectT::     ObjPtr constructPtr(      ObjectT *pObj);

    template <class ObjectT>
    static typename ObjectT::ObjConstPtr constructPtr(const ObjectT *pObj);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Fields                                  */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    PtrCreateMixin(void);
    PtrCreateMixin(const PtrCreateMixin &source);

    virtual ~PtrCreateMixin(void);

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

    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const PtrCreateMixin &source);
};

OSG_END_NAMESPACE

#define OSGCONTAINERCREATEMIXIN_HEADER_CVSID "@(#)$Id$"

#include "OSGContainerCreateMixin.inl"

#endif /* _OSGCONTAINERCREATEMIXIN_H_ */
