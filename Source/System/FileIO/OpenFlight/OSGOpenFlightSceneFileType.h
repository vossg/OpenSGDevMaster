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

#ifndef _OSGOPENFLIGHTSCENEFILETYPE_H_
#define _OSGOPENFLIGHTSCENEFILETYPE_H_
#ifdef __sgi
#pragma once
#endif

#include "boost/function.hpp"

#include "OSGFileIODef.h"
#include "OSGBaseTypes.h"
#include "OSGSceneFileType.h"

OSG_BEGIN_NAMESPACE

class OSGLoader;
class FieldContainer;

/*! \brief OSGSceneFileType
    \ingroup GrpFileIOOpenFlight
    \ingroup GrpLibOSGFileIO
 */

class OSG_FILEIO_DLLMAPPING OpenFlightSceneFileType : public SceneFileType
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef boost::function<void(FieldContainer * const)> Functor;

    typedef void (FieldContainer::*Callback)(void);

    /*---------------------------------------------------------------------*/
    /*! \name                Class Get                                     */
    /*! \{                                                                 */

    static OpenFlightSceneFileType &the(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~OpenFlightSceneFileType (void);

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

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Write                                      */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Write                                      */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    static const Char8                   *_suffixA[];
    static       OpenFlightSceneFileType  _the;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    OpenFlightSceneFileType(const Char8  *suffixArray[],
                                  UInt16  suffixByteCount,
                                  bool    override,
                                  UInt32  overridePriority,
                                  UInt32  flags);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    typedef SceneFileType Inherited;

    /*!\brief prohibit default function (move to 'public' if needed) */
    OpenFlightSceneFileType(const OpenFlightSceneFileType &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const OpenFlightSceneFileType &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

OSG_END_NAMESPACE

#endif /* _OSGOPENFLIGHTSCENEFILETYPE_H_ */
