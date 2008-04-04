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

#ifndef _OSGWINDOW_H_
#define _OSGWINDOW_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"

#include <list>
#include <utility>
#include <boost/function.hpp>

#ifdef OSG_STL_HAS_HASH_MAP
#ifdef OSG_HASH_MAP_AS_EXT
#include <ext/hash_map>
#else
#include <hash_map>
#endif
#else
#include <map>
#endif

#include "OSGVector.h"

#include "OSGBackground.h"
#include "OSGCamera.h"
#include "OSGViewport.h"

#include "OSGWindowBase.h"

OSG_BEGIN_NAMESPACE

class DrawEnv;

class RenderActionBase;
class StageValidator;

/*! \brief Window base class. See \ref PageSystemWindowWindow
for a description. */

class OSG_SYSTEM_DLLMAPPING Window : public WindowBase
{
    /*==========================  PUBLIC  =================================*/

  public:

    enum GLObjectStatusE
    {
        notused      = 1,
        initialize,
        reinitialize,
        initialized,
        needrefresh,
        destroy,
        finaldestroy
    };

    enum
    {
        invalidExtensionID = 0x7fffffff,
        invalidFunctionID  = 0x7fffffff
    };

    static const Real32 unknownConstant;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Typedefs                               */
    /*! \{                                                                 */

    typedef boost::function<void (DrawEnv *, UInt32, GLObjectStatusE)> 
                                                        GLObjectFunctor;

    typedef void (*GLExtensionFunction)(void);

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin,
                         BitVector         detail);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                Viewport handling                             */
    /*! \{                                                                 */

/*
    void addPort      (const ViewportPtr &portP);
    void insertPort   (      UInt32       portIndex,
                       const ViewportPtr &portP);

    void replacePort  (      UInt32       portIndex,
                       const ViewportPtr &portP);
    void replacePortBy(const ViewportPtr &portP,
                       const ViewportPtr &newPortP);

    void subPort      (const ViewportPtr &portP);
    void subPort      (      UInt32       portIndex);
 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name             Extension registration                           */
    /*! \{                                                                 */

    static UInt32 registerExtension(const Char8 *s               );
    static void   ignoreExtensions (const Char8 *s               );

    static UInt32 registerFunction (const Char8 *s,
                                          Int32  ext     = -1,
                                          UInt32 version = 0xffff);

    static void   registerConstant (      GLenum val             );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name               Extension handling                             */
    /*! \{                                                                 */

    static void                 setGLLibraryName  (const Char8  *s     );

           UInt32               getGLVersion      (      void          );

    static Int32                getExtensionId    (const Char8  *s     );
           bool                 hasExtension      (      UInt32  extId );
           bool                 hasExtension      (const Char8  *s     );
    static bool                 hasCommonExtension(      UInt32  extId );
           void                *getFunction       (      UInt32  funcId);
           void                *getFunctionNoCheck(      UInt32  funcId);
           void                 dumpExtensions    (      void          );
           GLExtensionFunction  getFunctionByName (const Char8  *s     );
           Real32               getConstantValue  (      GLenum  val   );
    const  Vec2f               &getConstantValuev (      GLenum  val   );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name            Extension string handling                         */
    /*! \{                                                                 */

    static const std::vector<std::string> &getRegisteredExtensions(void);
           const std::vector<std::string> &getRegisteredFunctions (void);
           const std::vector<std::string> &getExtensions          (void);
           const std::vector<std::string> &getIgnoredExtensions   (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name             GL object registration                           */
    /*! \{                                                                 */

    static UInt32 registerGLObject(GLObjectFunctor functor,
                                   GLObjectFunctor destroyFunctor,
                                   UInt32          num = 1);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name               GL object handling                             */
    /*! \{                                                                 */

           void            validateGLObject    (UInt32           osgId,
                                                DrawEnv         *pEnv    );
           void            validateAllGLObjects(DrawEnv         *pEnv    );

           //GLObjectStatusE getGLObjectStatus   (UInt32           osgId   );
           void            setGLObjectId       (UInt32           osgId,
                                                UInt32           id2     );
           UInt32          getGLObjectId       (UInt32           osgId   );


    static UInt32          getGLObjectsSize    (void                     );

    static void            refreshGLObject         (UInt32           osgId   );
    static void            refreshAllGLObjects     (void                     );

    static void            reinitializeGLObject    (UInt32           osgId   );
    static void            reinitializeAllGLObjects(void                     );

    static void            destroyGLObject         (UInt32           osgId,
                                                    UInt32           num = 1 );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Size handling                                */
    /*! \{                                                                 */

            bool isResizePending(void         );

    virtual void resize         (int width,
                                 int height   );
    virtual void resizeGL       (void         );

            void setSize        (UInt16 width,
                                 UInt16 height);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Drawing                                   */
    /*! \{                                                                 */

    virtual void    frameInit         (void);
    virtual void    frameExit         (void);

#ifdef OSG_OLD_RENDER_ACTION
    virtual void    render            (DrawActionBase   *action = NULL);
    virtual void    renderAllViewports(DrawActionBase   *action = NULL);
#endif

    virtual void    render            (RenderActionBase *action);
    virtual void    renderAllViewports(RenderActionBase *action);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name      Window system implementation functions                  */
    /*! \{                                                                 */

    virtual void init      (void) = 0;
    virtual void activate  (void) = 0;
    virtual void deactivate(void) = 0;
    virtual bool swap      (void) = 0;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    StageValidator *getStageValidator(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Output                                  */
    /*! \{                                                                 */

    virtual void dump(      UInt32    uiIndent = 0,
                      const BitVector bvFlags  = 0) const;

    /*! \}                                                                 */

    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    Window(void);
    Window(const Window &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~Window(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                GL setup handling                             */
    /*! \{                                                                 */

    virtual void setupGL(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);
    static bool terminate (void            );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                GL object handling                            */
    /*! \{                                                                 */

    static void   initRegisterGLObject  (UInt32          osgId,
                                         UInt32          num   );

           void   doInitRegisterGLObject(UInt32          osgId,
                                         UInt32          num   );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name           GL object handling helper class                    */
    /*! \{                                                                 */

    class GLObject;

    friend class GLObject;

    class GLObject
    {
      public:

        GLObject(GLObjectFunctor funct, GLObjectFunctor destroy);

        GLObjectFunctor& getFunctor(void                 );
        void             setFunctor(GLObjectFunctor funct);

        GLObjectFunctor& getDestroyFunctor(void                 );
        void             setDestroyFunctor(GLObjectFunctor funct);

        UInt32 getLastValidate(void      );
        void   setLastValidate(UInt32 val);

        UInt32 getRefCounter(void);
        UInt32 incRefCounter(void);
        UInt32 decRefCounter(void);

      protected:

        GLObjectFunctor _functor;
        GLObjectFunctor _destroy;
        volatile UInt32 _refCounter;
                 UInt32 _lastValidate;
    };

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                MT Construction                               */
    /*! \{                                                                 */

           void onCreate       (const Window *source = NULL);

           void onCreateAspect (const Window *createAspect,
                                const Window *source = NULL);

           void onDestroy      (      UInt32  uiContainerId);

           void onDestroyAspect(      UInt32  uiContainerId,
                                      UInt32  uiAspect     );

    static void staticAcquire (void                       );
    static void staticRelease (void                       );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name            Map for GL cvonstant handling                     */
    /*! \{                                                                 */

#ifdef OSG_STL_HAS_HASH_MAP
    typedef
        OSG_STDEXTENSION_NAMESPACE::hash_map<
            GLenum,
            Vec2f> ConstHash;
#else
    typedef
        std::map< GLenum,  Vec2f > ConstHash;
#endif

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    typedef WindowBase Inherited;

    friend class FieldContainer;
    friend class WindowBase;

    static std::vector<WindowPtr> _allWindows;
    static UInt32                 _currentWindowId;

    //! Does init() not to be called?
    bool    _initNeeded;
    
    /*---------------------------------------------------------------------*/
    /*! \name   Static GL Object / Extension variables                     */
    /*! \{                                                                 */

#ifndef OSG_WINCE
    static  Lock                     *_GLObjectLock;
    static  Lock                     *_staticWindowLock;
#endif

    static std::vector<GLObject  *>   _glObjects;
    static const Char8               *_glLibraryName;

    static  std::vector<std::string>  _registeredExtensions;
    static  std::vector<std::string>  _ignoredExtensions;
    static  std::vector<bool       >  _commonExtensions;
    static  std::vector<std::string>  _registeredFunctions;
    static  std::vector<Int32      >  _registeredFunctionExts;
    static  std::vector<UInt32     >  _registeredFunctionVersions;

    static  std::vector<GLenum     >  _registeredConstants;

    typedef std::pair<UInt32,UInt32>   DestroyEntry;

            std::list<DestroyEntry >  _glObjectDestroyList;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name        GL Object / Extension variables                       */
    /*! \{                                                                 */

    std::vector<UInt32     > _lastValidate;
    std::vector<UInt32     > _ids;

    UInt32                   _glVersion;
    std::vector<std::string> _extensions;
    std::vector<bool       > _availExtensions;
    std::vector<void      *> _extFunctions;

    ConstHash                _availConstants;
    UInt32                   _numAvailConstants;

    UInt32                   _windowId;
    StageValidator          *_pStageValidator;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

    // prohibit default functions (move to 'public' if you need one)
    Window &operator =(const Window &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

typedef Window *WindowP;

OSG_END_NAMESPACE

#include "OSGWindowBase.inl"
#include "OSGWindow.inl"

#endif /* _OSGWINDOW_H_ */
