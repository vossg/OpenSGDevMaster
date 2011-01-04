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

#ifndef _OSGNFIOSCENEFILETYPE_H_
#define _OSGNFIOSCENEFILETYPE_H_
#ifdef  __sgi
#pragma  once
#endif

#include "OSGFileIODef.h"
#include "OSGSceneFileType.h"

OSG_BEGIN_NAMESPACE

/*! \brief NFIOSceneFileType
    \ingroup GrpFileIOOSB
    \ingroup GrpLibOSGFileIO
 */

class OSG_FILEIO_DLLMAPPING NFIOSceneFileType : public SceneFileType
{
    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Static Get                                 */
    /*! \{                                                                 */

    static NFIOSceneFileType &the(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~NFIOSceneFileType(void);

    /*! \}                                                                 */
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
    /*! \name                   Write                                      */
    /*! \{                                                                 */

    virtual bool write(Node         * const  node,
                       std::ostream         &os,
                       Char8          const *fileNameOrExtension) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    static const Char8            *_suffixA[];
    static       NFIOSceneFileType  _the;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    NFIOSceneFileType(const Char8  *suffixArray[],
                            UInt16  suffixByteCount,
                            bool    override,
                            UInt32  overridePriority,
                            UInt32  flags);

    NFIOSceneFileType(const NFIOSceneFileType &obj);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    typedef SceneFileType Inherited;

    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const NFIOSceneFileType &source);
};

typedef NFIOSceneFileType* NFIOSceneFileTypeP;

OSG_END_NAMESPACE

#endif // _OSGNFIOSCENEFILETYPE_H_
