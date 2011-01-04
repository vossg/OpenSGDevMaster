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
 * 2002/10/16: added transparency path. Thanks to Franck Sourdin             *
 *            (sourdin@ai.cluny.ensam.fr) for it!                            *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/

#ifndef _OSGOBJSCENEFILETYPE_H_
#define _OSGOBJSCENEFILETYPE_H_
#ifdef  __sgi
#pragma  once
#endif

#include "OSGFileIODef.h"
#include "OSGBaseTypes.h"
#include "OSGSceneFileType.h"

#include <map>


OSG_BEGIN_NAMESPACE

/*! \brief OBJSceneFileType
    \ingroup GrpFileIOOBJ
    \ingroup GrpLibOSGFileIO
 */

class OSG_FILEIO_DLLMAPPING OBJSceneFileType : public SceneFileType
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Class Get                                  */
    /*! \{                                                                 */

    static OBJSceneFileType &the(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~OBJSceneFileType(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Get                                        */
    /*! \{                                                                 */

    virtual const Char8 *getName(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Read                                       */
    /*! \{                                                                 */

    virtual 
    NodeTransitPtr read(      std::istream &is,
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
    static       OBJSceneFileType  _the;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    OBJSceneFileType(const Char8  *suffixArray[],
                           UInt16  suffixByteCount,
                           bool    override,
                           UInt32  overridePriority,
                           UInt32  flags);

    OBJSceneFileType(const OBJSceneFileType &obj);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    typedef SceneFileType Inherited;

    enum DataElem
    {
      UNKNOWN_DE = 0,

      VERTEX_DE, VERTEX_TEXTURECOORD_DE, VERTEX_NORMAL_DE,
      FACE_DE,
      
      LIB_MTL_DE,
      USE_MTL_DE,

      GROUP_DE, SMOOTHING_GROUP_DE, OBJECT_DE
    };

    std::map<std::string, DataElem> _dataElemMap;

    enum MaterialElem
    {
      UNKNOWN_ME = 0,

      NEW_MTL_ME,
      MTL_DIFFUSE_ME, MTL_AMBIENT_ME, MTL_SPECULAR_ME,
      MTL_SHININESS_ME, MTL_ILLUM_ME,
      MTL_TRANSPARENCY_ME, MTL_DISSOLVE_ME,
      MTL_MAP_KD_ME, MTL_MAP_KA_ME, MTL_MAP_KS_ME,
      MTL_REFL_ME
    };

    std::map<std::string, MaterialElem> _mtlElemMap;

    void initElemMap(void);

    struct Mesh;
    friend struct Mesh;

    struct Face;
    friend struct Face;

    /*! \nohierarchy 
     */
    struct TiePoint
    {
        Int32 index[3];
        TiePoint( Int32 v = -1, Int32 vt = -1, Int32 vn = -1 )
            { index[0] = v; index[1] = vt; index[2] = vn; }
        inline void set ( Int32 v = -1, Int32 vt = -1, Int32 vn = -1 )
            { index[0] = v; index[1] = vt; index[2] = vn; }
    };

    /*! \nohierarchy 
     */
    struct Face
    {
        std::vector<TiePoint> tieVec;
    };

    /*! \nohierarchy 
     */
    struct Mesh 
    {
      std::string            name;
      std::list<Face>        faceList;
      SimpleMaterialUnrecPtr mtlPtr;
    };


    Int32 readMTL (const Char8 *fileName,
                   std::map<std::string,
                   SimpleTexturedMaterialUnrecPtr> &mtlMap  ) const;

    void write(Node * const node,
               std::ostream &os,
               UInt32 &pIndex,
               UInt32 &nIndex,
               UInt32 &tIndex) const;

    /* prohibit default function (move to 'public' if needed) */
    void operator =(const OBJSceneFileType &source);
};

typedef OBJSceneFileType* OBJSceneFileTypeP;

OSG_END_NAMESPACE

#endif // _OSGOBJSCENEFILETYPE_H_

