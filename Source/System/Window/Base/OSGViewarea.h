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

#ifndef _OSGVIEWAREA_H_
#define _OSGVIEWAREA_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGRenderOptions.h"
#include "OSGViewareaBase.h"
#include "OSGWindowDrawTask.h"

OSG_BEGIN_NAMESPACE

class RenderActionBase;
class TraversalValidator;
class FrameBufferObject;

/*! \brief Viewarea base class. See \ref 
    PageSystemWindowViewareas for a description.

  \ingroup GrpSystemWindowBase
  \ingroup GrpLibOSGSystem
  \includebasedoc
 */

class OSG_SYSTEM_DLLMAPPING Viewarea : public ViewareaBase
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef ViewareaBase                           Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                    access                                    */
    /*! \{                                                                 */

    void setSize          (Real32   left,  
                           Real32   bottom, 
                           Real32   right, 
                           Real32   top           );
    
    void computePixelSizes(Window  *pWin,

                           UInt32   &uiPixelWidth,
                           UInt32   &uiPixelHeight);
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    your_category                             */
    /*! \{                                                                 */

    virtual void render      (RenderActionBase *action);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual bool               isPassive(void);
    virtual FrameBufferObject *getTarget(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    TraversalValidator *getTravValidator(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   change                                     */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField, 
                         UInt32            origin,
                         BitVector         detail);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   dump                                       */
    /*! \{                                                                 */

    virtual void dump(      UInt32    uiIndent = 0, 
                      const BitVector bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

 protected:

    TraversalValidator *_pTravValidator;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    Viewarea(void);
    Viewarea(const Viewarea &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~Viewarea(void); 
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */
    
    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                MT Construction                               */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                MT Construction                               */
    /*! \{                                                                 */

    void onCreate       (const Viewarea *source = NULL);

    void onCreateAspect (const Viewarea *createAspect,
                         const Viewarea *source = NULL);
    
    void onDestroy      (      UInt32    uiContainerId);

    void onDestroyAspect(      UInt32    uiContainerId,
                               UInt32    uiAspect     );
    
    /*! \}                                                                 */
    /*=========================  PRIVATE    ===============================*/

 private:

    friend class FieldContainer;
    friend class ViewareaBase;
    friend class ViewareaDrawTask;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const Viewarea &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

typedef Viewarea *ViewareaP;

OSG_END_NAMESPACE

#include "OSGViewareaBase.inl"
#include "OSGViewarea.inl"

#endif /* _OSGVIEWAREA_H_ */
