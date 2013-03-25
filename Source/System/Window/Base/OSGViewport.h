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


#ifndef _OSGVIEWPORT_H_
#define _OSGVIEWPORT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGViewportBase.h"
#include "OSGWindowDrawTask.h"

OSG_BEGIN_NAMESPACE

/*! \brief Viewport base class. See \ref 
    PageSystemWindowViewports for a description.

  \ingroup GrpSystemWindowBase
  \ingroup GrpLibOSGSystem
  \includebasedoc
 */

class OSG_SYSTEM_DLLMAPPING Viewport : public ViewportBase
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef ViewportBase                           Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                    access                                    */
    /*! \{                                                                 */

    virtual Int32   calcPixelLeft            (      void         ) const;
    virtual Int32   calcPixelRight           (      void         ) const;
    virtual Int32   calcPixelBottom          (      void         ) const;
    virtual Int32   calcPixelTop             (      void         ) const;

            Int32   calcPixelWidth           (      void         ) const;
            Int32   calcPixelHeight          (      void         ) const;
    
    virtual bool    calcIsFullWindow         (      void         ) const;

            Window *getParent                (      void         ) const;

            void    calcNormalizedCoordinates(      Real32& normX,
                                                    Real32& normY,
                                              const Int32   vpX  ,
                                              const Int32   vpY  ) const;

#ifdef OSG_1_COMPAT
            Int32   getPixelLeft             (      void         ) const;
            Int32   getPixelRight            (      void         ) const;
            Int32   getPixelBottom           (      void         ) const;
            Int32   getPixelTop              (      void         ) const;

            Int32   getPixelWidth            (      void         ) const;
            Int32   getPixelHeight           (      void         ) const;
    
            bool    isFullWindow             (      void         ) const;


            void    getNormalizedCoordinates (      Real32& normX,
                                                    Real32& normY,
                                              const Int32   vpX  ,
                                              const Int32   vpY  ) const;
#endif
                                          
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    your_category                             */
    /*! \{                                                                 */

    virtual void activateSize(void                    );
    virtual void activate    (void                    );
    virtual void deactivate  (void                    );

    virtual void render      (RenderActionBase *action);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

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

    ViewportDrawTaskRefPtr _pForegroundTask;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    Viewport(void);
    Viewport(const Viewport &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~Viewport(void); 
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */
    
    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                MT Construction                               */
    /*! \{                                                                 */

    void renderForegrounds(Window *pWin,
                           Int32   iDrawerId,
                           Int32   iDrawableId);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                MT Construction                               */
    /*! \{                                                                 */

    void onCreate       (const Viewport *source = NULL);

    void onCreateAspect (const Viewport *createAspect,
                         const Viewport *source = NULL);
    
    void onDestroy      (      UInt32    uiContainerId);

    void onDestroyAspect(      UInt32    uiContainerId,
                               UInt32    uiAspect     );
    
    /*! \}                                                                 */
    /*=========================  PRIVATE    ===============================*/

 private:

    friend class FieldContainer;
    friend class ViewportBase;
    friend class ViewportDrawTask;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const Viewport &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

typedef Viewport *ViewportP;

OSG_END_NAMESPACE

#include "OSGViewportBase.inl"
#include "OSGViewport.inl"

#endif /* _OSGVIEWPORT_H_ */
