/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                 Copyright (C) 2000 by the OpenSG Forum                    *
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

#ifndef _OSGSCENEFILETYPE_H_
#define _OSGSCENEFILETYPE_H_
#ifdef  __sgi
#pragma  once
#endif

#include "OSGSystemDef.h"
#include <list>
#include <iostream>
#include <string>

#include "OSGBaseTypes.h"
#include "OSGIDString.h"
#include "OSGNode.h"

OSG_BEGIN_NAMESPACE

/*!\ingroup GrpSystemDrawablesGeometrymetryLoaderLib
 * \brief OSGSceneFileType
 */

class OSG_SYSTEM_DLLMAPPING SceneFileType
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef std::vector<FieldContainerPtr> FCPtrStore;

    /*---------------------------------------------------------------------*/
    /*! \name                   Class Get                                  */
    /*! \{                                                                 */

    virtual const Char8 *getName(void) const = 0;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Flags                                    */
    /*! \{                                                                 */
  
    enum
    {
        OSG_READ_SUPPORTED  = 1,
        OSG_WRITE_SUPPORTED = 2
    };
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SceneFileType(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Set                                        */
    /*! \{                                                                 */
    
    void setOptions(const Char8 *options);

    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Get                                        */
    /*! \{                                                                 */

    virtual std::list<IDString> &suffixList         (void);

            bool                 doOverride         (void);
            UInt32               getOverridePriority(void);
            UInt32               getFlags           (void);
    
            const Char8         *getOptions         (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Read                                       */
    /*! \{                                                                 */

    virtual NodePtr read    (      std::istream &is,
                             const Char8        *fileNameOrExtension) const;

#ifndef OSG_DISABLE_DEPRECATED
    virtual NodePtr readFile(const Char8 *fileName) const;
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Write                                      */
    /*! \{                                                                 */

    virtual bool write    (const NodePtr      &node, 
                                 std::ostream &os,
                           const Char8        *fileNameOrExtension) const;

#ifndef OSG_DISABLE_DEPRECATED
    virtual bool writeFile(const NodePtr      &node,
                           const Char8        *fileName           ) const;
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Debug                                      */
    /*! \{                                                                 */

    void print(void);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    std::list<IDString> _suffixList;

    bool                _override;
    UInt32              _overridePriority;
    UInt32              _flags;
  
    std::string         _options;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    SceneFileType(const Char8  *suffixArray[],
                        UInt16  suffixByteCount,
                        bool    override,
                        UInt32  overridePriority,
                        UInt32  flags = OSG_READ_SUPPORTED);

    SceneFileType(const SceneFileType &obj);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const SceneFileType &source);
};

typedef SceneFileType* SceneFileTypeP;

OSG_END_NAMESPACE

#define OSGSCENEFILETYPE_HEADER_CVSID "@(#)$Id: $"

#endif // _OSGSCENEFILETYPE_H_
