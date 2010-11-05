/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2005 by the OpenSG Forum                   *
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


#ifndef _OSGIMAGEFORGROUND_H_
#define _OSGIMAGEFORGROUND_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"

#include "OSGImageForegroundBase.h"
#include "OSGImage.h"

OSG_BEGIN_NAMESPACE

class RenderTraversalActionBase;

/*! \brief Foreground class for displaying an image. See \ref 
           PageSystemWindowForegroundImage for a description.
    \ingroup GrpWindowForegroundObj
    \ingroup GrpLibOSGWindow
    \includebasedoc
 */

class OSG_WINDOW_DLLMAPPING ImageForeground : public ImageForegroundBase
{
    /*==========================  PUBLIC  =================================*/ 

 public:

    typedef ImageForegroundBase                           Inherited;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     transformation                           */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField, 
                         UInt32            origin,
                         BitVector         detail);
 
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     dump                                     */
    /*! \{                                                                 */

    virtual void dump(      UInt32    uiIndent = 0, 
                      const BitVector bvFlags  = 0) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    access fields                             */
    /*! \{                                                                 */

    inline void addImage(Image *image, Pnt2f position);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    draw                                      */
    /*! \{                                                                 */

    virtual void draw(DrawEnv *);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

 protected:
  
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    ImageForeground(void);
    ImageForeground(const ImageForeground &source);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */
 
    virtual ~ImageForeground(void); 
 
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/  

 private:

    friend class FieldContainer;
    friend class ImageForegroundBase;

    void operator =(const ImageForeground &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------


/** \brief class pointer
 */

typedef ImageForeground              *ImageForegroundP;

OSG_END_NAMESPACE

#include "OSGImageForegroundBase.inl"
#include "OSGImageForeground.inl"

#endif /* _OSGIMAGEFORGROUND_H_ */


