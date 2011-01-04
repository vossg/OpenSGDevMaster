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

#ifndef _OSGOSGSCENEFILETYPE_H_
#define _OSGOSGSCENEFILETYPE_H_
#ifdef __sgi
#pragma once
#endif

#include "boost/function.hpp"

#include "OSGBaseTypes.h"
#include "OSGSceneFileType.h"

OSG_BEGIN_NAMESPACE

class OSGLoader;
class FieldContainer;

/*! \brief OSGSceneFileType
    \ingroup GrpSystemFileIOOSG
    \ingroup GrpLibOSGSystem
 */

class OSG_SYSTEM_DLLMAPPING OSGSceneFileType : public SceneFileType
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef boost::function<void(FieldContainer * const)> Functor;

    typedef void (FieldContainer::*Callback)(void);

    /*---------------------------------------------------------------------*/
    /*! \name                Class Get                                     */
    /*! \{                                                                 */

    static OSGSceneFileType &the(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~OSGSceneFileType (void);

    /*---------------------------------------------------------------------*/
    /*! \name                   Get                                        */
    /*! \{                                                                 */

    virtual const Char8 *getName(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Read                                       */
    /*! \{                                                                 */

    virtual NodeTransitPtr read(      std::istream &is,
                                const Char8        *fileNameOrExtension,
                                      Resolver      resolver  = NULL   ) const;


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Read                                       */
    /*! \{                                                                 */

    virtual 
    FieldContainerTransitPtr readContainer(
        const Char8    *fileName,
              Resolver  resolver = NULL) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Write                                      */
    /*! \{                                                                 */

    virtual bool write(Node *       const  node, 
                       std::ostream       &os,
                       Char8        const *fileNameOrExtension) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Write                                      */
    /*! \{                                                                 */

    virtual bool writeContainer(FieldContainer * const  pContainer, 
                                Char8            const *fileName  ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Write                                      */
    /*! \{                                                                 */

    void registerEndNodeCallback(const FieldContainerType &type, 
                                 const Functor            &func);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    static const Char8                *_suffixA[];
    static       OSGSceneFileType      _the;

                 std::vector<Functor>  _endNodeFunctors;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    OSGSceneFileType(const Char8  *suffixArray[],
                           UInt16  suffixByteCount,
                           bool    override,
                           UInt32  overridePriority,
                           UInt32  flags);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Termination                                */
    /*! \{                                                                 */

    virtual void terminate(void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    typedef SceneFileType Inherited;

    /*!\brief prohibit default function (move to 'public' if needed) */
    OSGSceneFileType(const OSGSceneFileType &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const OSGSceneFileType &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

OSG_END_NAMESPACE

#endif /* _OSGOSGSCENEFILETYPE_H_ */
