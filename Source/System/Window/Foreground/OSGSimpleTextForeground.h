/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 * contact: David Kabala (djkabala@gmail.com)                                *
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

#ifndef _OSGSIMPLETEXTFOREGROUND_H_
#define _OSGSIMPLETEXTFOREGROUND_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGSimpleTextForegroundBase.h"
#include "OSGTextureObjChunkFields.h"
#include "OSGTextureEnvChunkFields.h"
#include "OSGTextTXFFace.h"

OSG_BEGIN_NAMESPACE

/*! \brief SimpleTextForeground class. See \ref
           PageUtilSimpleTextForeground for a description.
*/

class OSG_WINDOW_DLLMAPPING SimpleTextForeground : 
    public SimpleTextForegroundBase
{

  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef SimpleTextForegroundBase Inherited;
    typedef SimpleTextForeground     Self;

    /*---------------------------------------------------------------------*/
    /*! \name                     Modes                                    */
    /*! \{                                                                 */

    enum HorizontalAlignE
    {
        Left   = 0,
        Middle = 1,
        Right  = 2
    };

    enum VerticalAlignE
    {
        Top    = 0,
        Center = 1,
        Bottom = 2
    };
       
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin,
                         BitVector         details    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Draw                                    */
    /*! \{                                                                 */

    virtual void draw(DrawEnv *pEnv);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name               Convenience Functions                          */
    /*! \{                                                                 */

    void addLine(const std::string &szText);
    void clear  (      void             );

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in SimpleTextForegroundBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    SimpleTextForeground(void);
    SimpleTextForeground(const SimpleTextForeground &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SimpleTextForeground(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    virtual void resolveLinks(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    void beginOrthoRender(DrawEnv *pEnv,
                          UInt32  &fullWidth,
                          UInt32  &fullHeight);

    void endOrthoRender  (DrawEnv *pEnv      );

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    class TextColoredRange
    {
      public:

        TextColoredRange(UInt32 uiStart, UInt32 uiEnd, const Color4f &cColor);

              bool     isBounded(UInt32 Position) const;

        const Color4f &getColor(void) const;
              UInt32   getStart(void) const;
              UInt32   getEnd(void) const;

      private:

        UInt32  _uiStart,
                _uiEnd;
        Color4f _cColor;
    };

    bool    isColoredRange(      UInt32                   uiPosition   ) const;
    Color4f getColorRange (      UInt32                   uiPosition   ) const;

    void updateFormatting (      void                                  );

    void drawCharacters   (      TextTXFFace      * const pTextFace,
                           const TextLayoutResult &       oLayoutResult,
                                 bool                     bWithColoring);

    void initText         (const std::string      &       szFamily, 
                                 Real32                   fsize        );



    TextTXFFaceRefPtr               _pFace;

    TextureObjChunkUnrecPtr         _pTexChunk;
    TextureEnvChunkUnrecPtr         _pTexEnvChunk;

    std::vector<std::string     >   _vPlainTextLines;
    std::vector<TextColoredRange>   _vColorRanges;



    friend class FieldContainer;
    friend class SimpleTextForegroundBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const SimpleTextForeground &source);
};

typedef SimpleTextForeground *SimpleTextForegroundP;

OSG_END_NAMESPACE

#include "OSGSimpleTextForegroundBase.inl"
#include "OSGSimpleTextForeground.inl"

#endif /* _OSGSIMPLETEXTFOREGROUND_H_ */
