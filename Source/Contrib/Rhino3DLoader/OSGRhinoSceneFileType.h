/*---------------------------------------------------------------------------*\
 *                        OpenSG openNURBS SceneFileType                     *
 *                                                                           *
 *                                                                           *
 * Copyright (C) 2007-2008 by Seac02 S.r.l.     http://www.seac02.it         *
 * Copyright (C) 2008  by Patrik Mueller    muellerptr@users.sourceforge.net *
 * Copyright (C) 2008  by Akos Balazs       edhellon@cs.uni-bonn.de          *
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

#ifndef _OSGRHINOSCENEFILETYPE_H_
#define _OSGRHINOSCENEFILETYPE_H_
#ifdef  __sgi
#pragma  once
#endif

#include "OSGContribRhino3DDef.h"
#include "OSGBaseTypes.h"

#include "OSGSceneFileType.h"

OSG_BEGIN_NAMESPACE

/*!\brief OSGRhinoSceneFileType
*/

class OSG_CONTRIBRHINO3D_DLLMAPPING RhinoSceneFileType : public SceneFileType
{
    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Static Get                                 */
    /*! \{                                                                 */

    static RhinoSceneFileType &the(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~RhinoSceneFileType(void);

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
    /*! \name                  Params                                      */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    NodeTransitPtr read3DM(const Char8 *fileName) const;

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    static const Char8              *_suffixA[];
    static       RhinoSceneFileType  _the;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    RhinoSceneFileType(const Char8  *suffixArray[],
                             UInt16  suffixByteCount,
                             bool    override,
                             UInt32  overridePriority,
                             UInt32  flags);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    typedef SceneFileType Inherited;
   
    /*!\brief prohibit default function (move to 'public' if needed) */
    RhinoSceneFileType(const RhinoSceneFileType &obj);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const RhinoSceneFileType &source);
};

typedef RhinoSceneFileType* RhinoSceneFileTypeP;

OSG_END_NAMESPACE

#endif // _OSGRHINOSCENEFILETYPE_H_
