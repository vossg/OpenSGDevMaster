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

#ifndef _OSGSKYBACKGROUND_H_
#define _OSGSKYBACKGROUND_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGSkyBackgroundBase.h"
#include "OSGTextureBaseChunk.h"

OSG_BEGIN_NAMESPACE

class Viewport;

/*! \brief Background clearing class using a sky sphere and box. See \ref 
           PageSystemWindowBackgroundSky for a description.
    \ingroup GrpWindowBackgroundObj
    \ingroup GrpLibOSGWindow
    \includebasedoc
 */

class OSG_WINDOW_DLLMAPPING SkyBackground : public SkyBackgroundBase
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef SkyBackgroundBase                           Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField, 
                         UInt32            origin,
                         BitVector         detail);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Background                               */
    /*! \{                                                                 */

    virtual void clear(DrawEnv *pEnv);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in SkyBackgroundBase.

    std::vector<Real32> _cosval;
    std::vector<Real32> _sinval;

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    SkyBackground(void);
    SkyBackground(const SkyBackground &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SkyBackground(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Draw Helper                                */
    /*! \{                                                                 */

    void drawFace(      DrawEnv             * action, 
                        TextureBaseChunk    * tex, 
                        StateChunk          *&oldtex, 
                  const Pnt3f                &p1, 
                  const Pnt3f                &p2, 
                  const Pnt3f                &p3, 
                  const Pnt3f                &p4,  
                  const Vec3f               * texCoord);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class SkyBackgroundBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const SkyBackground &source);
    
    const Vec3f *selectTexCoords(const Vec3f            *userTexCoords,
                                       TextureBaseChunk *texImage,
                                       UInt32            side          );
    
    static const Vec3f _defaultTexCoords    [7][4];
    static const Vec3f _defaultVRMLTexCoords[7][4];
};

typedef SkyBackground              *SkyBackgroundP;

OSG_END_NAMESPACE

#include "OSGSkyBackgroundBase.inl"
#include "OSGSkyBackground.inl"

#endif /* _OSGSKYBACKGROUND_H_ */
