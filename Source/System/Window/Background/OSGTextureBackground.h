/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
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

#ifndef _OSGTEXTUREBACKGROUND_H_
#define _OSGTEXTUREBACKGROUND_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGTextureBackgroundBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief TextureBackground class. See \ref
           PageSystemTextureBackground for a description.
    \ingroup GrpWindowBackgroundObj
    \ingroup GrpLibOSGWindow
    \includebasedoc
*/

class OSG_WINDOW_DLLMAPPING TextureBackground : public TextureBackgroundBase
{
  public:

    typedef TextureBackgroundBase                           Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                     Clear                                    */
    /*! \{                                                                 */

    virtual void clear(DrawEnv *pEnv);

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin,
                         BitVector         detail);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in TextureBackgroundBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    TextureBackground(void);
    TextureBackground(const TextureBackground &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~TextureBackground(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    std::vector<Vec2f > _textureCoordArray;
    std::vector<Vec2f > _vertexCoordArray;
    std::vector<UInt32> _indexArray;
    
    // Values for which the grid has been calculated, 
    // to check for update necessity

    UInt16              _hor;
    UInt16              _vert;
    Real32              _radialDistortion;
    Vec2f               _centerOfDistortion;
    
    // Helper method
    void updateGrid(void);
    

    friend class FieldContainer;
    friend class TextureBackgroundBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const TextureBackground &source);
};

typedef TextureBackground *TextureBackgroundP;

OSG_END_NAMESPACE

#include "OSGTextureBackgroundBase.inl"
#include "OSGTextureBackground.inl"

#endif /* _OSGTEXTUREBACKGROUND_H_ */
