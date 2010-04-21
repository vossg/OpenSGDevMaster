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

#include "OSGDeprecatedCPP.h"

#include "OSGVector.h"

#include "OSGBackground.h"
#include "OSGCamera.h"
#include "OSGViewport.h"

#include "OSGWindowBase.h"
#include "OSGWindowDrawTask.h"
#include "OSGWindowDrawThread.h"
#include "OSGDrawEnv.h"

OSG_BEGIN_NAMESPACE

class RenderActionBase;
class TraversalValidator;
class ShaderCache;

/*! \brief Window base class. See \ref PageSystemWindowWindow
for a description. */
class OSG_SYSTEM_DLLMAPPING Window : public WindowBase
{
    /*==========================  PUBLIC  =================================*/

  public:

    /**
     * Enumeration values for the status of the GL objects. This is primarily
     * used to signal the object's callback functions what to do. See \ref
     * PageSystemOGLObjects for a description.
     */
    enum GLObjectStatusE
    {
        notused      = 0x0001,  /**< Object is not used at all right now. */
        initialize   = 0x0002,  /**< Object is being initialized for the first time. */
        reinitialize = 0x0003,  /**< Object is being re-initialized (ie. significant change) */
        initialized  = 0x0004,  /**< Object is initialized and valid. */
        needrefresh  = 0x0005,  /**< Object is initialized but needs a refresh. */
        destroy      = 0x0006,  /**< Object is to be destroyed (removed from context) */
        finaldestroy = 0x0007   /**< Object has been removed from contexts, now release resources. */
    };

    enum
    {
        invalidExtensionID = 0x7fffffff,
        invalidFunctionID  = 0x7fffffff
    };

    enum
    {
        SequentialPartitionDraw = 0x000001,
        ParallelPartitionDraw   = 0x000002,
        PartitionDrawMask       = 0x0000FF,       

        StdDrawer               = 0x000100,
        ParallelDrawer          = 0x000200,        
        DrawerMask              = 0x00FF00,

        CycleContext            = 0x010000,
        KeepContextActive       = 0x020000,
        ContextMask             = 0xFF0000
    };

    static const Real32 unknownConstant;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Typedefs                               */
    /*! \{                                                                 */

    typedef UIntPointer                               GLObjectId;

    typedef boost::function<UInt32 (DrawEnv *, 
                                    UInt32,
                                    GLObjectStatusE,
                                    UInt32         )> GLObjectFunctor;
    typedef boost::function<void   (DrawEnv *, 
                                    UInt32, 
                                    GLObjectStatusE)> GLObjectDestroyFunctor;

    typedef void (*GLExtensionFunction)(void);

    typedef WindowDrawTask::GLInitFunctor             GLInitFunctor;

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

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name             Extension registration                           
    * See \ref */
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
           GLExtensionFunction  getFunction       (      UInt32  funcId);
           GLExtensionFunction  getFunctionNoCheck(      UInt32  funcId);
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

    static UInt32 registerGLObject(GLObjectFunctor        functor,
                                   GLObjectDestroyFunctor destroyFunctor,
                                   UInt32                 num = 1);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name               GL object handling                             */
    /*! \{                                                                 */

    UInt32     validateGLObject    (UInt32      osgId,
                                    DrawEnv    *pEnv,
                                    UInt32      uiOptions = 0);
    void       validateAllGLObjects(void);
    
    void       setGLObjectId       (UInt32      osgId,
                                    GLObjectId  id2          );
    GLObjectId getGLObjectId       (UInt32      osgId        );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name            static GL object handling                         */
    /*! \{                                                                 */

    static UInt32 getGLObjectsSize        (void                  );

    static void   refreshGLObject         (UInt32   osgId        );
    static void   refreshAllGLObjects     (void                  );

    static void   reinitializeGLObject    (UInt32   osgId        );
    static void   reinitializeAllGLObjects(void                  );

    static void   destroyGLObject         (UInt32   osgId,
                                           UInt32   num = 1      );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Size handling                                */
    /*! \{                                                                 */

    virtual void resize         (int width,
                                 int height   );

            void setSize        (UInt16 width,
                                 UInt16 height);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Drawing                                   */
    /*! \{                                                                 */

    virtual void render        (RenderActionBase *action          );
    virtual void renderNoFinish(RenderActionBase *action          );
    virtual void frameFinish   (bool              bActivate = true);
    virtual void runFrameExit  (void                              );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name      Window system implementation functions                  */
    /*! \{                                                                 */

    virtual void init(GLInitFunctor oFunc = GLInitFunctor());

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name             Sequential drawing                               */
    /*! \{                                                                 */

    virtual void activate          (void                    ) = 0;
    virtual void deactivate        (void                    ) = 0;
    virtual bool swap              (void                    ) = 0;

    virtual void frameExit         (void                    );
    virtual void frameInit         (void                    );
    virtual void renderAllViewports(RenderActionBase *action);


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    void   setPartitionDrawMode(UInt32 uiMode      );
    void   setDrawerType       (UInt32 uiDrawerType);
    void   setKeepContextActive(bool   bVal        );

    UInt32 getPartitionDrawMode(void               ) const;
    UInt32 getDrawerType       (void               ) const;
    bool   getKeepContextActive(void               ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

           ShaderCache        *getShaderCache  (void          );
           TraversalValidator *getTravValidator(void          );
    
    static void                requestStageRun (Int32 iStageId);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Output                                  */
    /*! \{                                                                 */

    virtual void resolveLinks(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Output                                  */
    /*! \{                                                                 */

           void queueTaskFromDrawer(DrawTask *pTask);
           void queueTask          (DrawTask *pTask);
    static void queueGlobalTask    (DrawTask *pTask);

 
           void clearDrawTasks     (void           );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Output                                  */
    /*! \{                                                                 */

    virtual void submitTask       (HardwareContextTask *pTask);
    virtual void submitTaskAndWait(BlockingTask        *pTask);

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
    static bool cleanup   (void            );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name      Window system implementation functions                  */
    /*! \{                                                                 */

           void            validateAllGLObjects(DrawEnv         *pEnv    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name      Window system implementation functions                  */
    /*! \{                                                                 */

    virtual void doTerminate         (void                          );

    virtual void doActivate          (void                          ) = 0;
    virtual void doDeactivate        (void                          ) = 0;
    virtual bool doSwap              (void                          ) = 0;

    virtual void doFrameInit         (bool reinitExtFuctions = false);
    virtual void doFrameExit         (void                          );

    virtual void doRenderAllViewports(RenderActionBase *action      );


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                GL object handling                            */
    /*! \{                                                                 */

    void setupTasks(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                GL object handling                            */
    /*! \{                                                                 */

    static void doRefreshGLObject     (UInt32 osgId            );
    static void doReinitializeGLObject(UInt32 osgId            );

    static void resetGLObjectStatus   (UInt32 osgId, UInt32 num);
           void doResetGLObjectStatus (UInt32 osgId, UInt32 num);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name           GL object handling helper class                    */
    /*! \{                                                                 */

    class GLObject;

    friend class GLObject;

    /** Used to keep track of the OpenGL objects registered with the system.
     * See \ref PageSystemOGLObjects for a description.
     */
    class GLObject
    {
      public:

        GLObject(GLObjectFunctor        funct, 
                 GLObjectDestroyFunctor destroy);

        void             acquireLock(void);
        void             releaseLock(void);

        GLObjectFunctor& getFunctor(void                 );
        void             setFunctor(GLObjectFunctor funct);

        GLObjectDestroyFunctor& getDestroyFunctor(void                        );
        void                    setDestroyFunctor(GLObjectDestroyFunctor funct);

        UInt32 getRefCounter(void);
        UInt32 incRefCounter(void);
        UInt32 decRefCounter(void);
        
      protected:

                 GLObjectFunctor        _functor;
                 GLObjectDestroyFunctor _destroy;
        volatile UInt32                 _refCounter;
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

    static void staticAcquire  (void                       );
    static void staticRelease  (void                       );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name            Map for GL cvonstant handling                     */
    /*! \{                                                                 */

    typedef OSG_HASH_MAP(GLenum, Vec2f) ConstHash;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name            Map for GL cvonstant handling                     */
    /*! \{                                                                 */

    void pushToDrawTasks(DrawTask * const value);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    typedef WindowBase Inherited;

    typedef std::vector<WindowMTUncountedPtr> WindowStore;

    friend class FieldContainer;
    friend class WindowBase;
    friend class DrawTask;
    friend class WindowDrawTask;

    static WindowStore                _allWindows;
    static Int32                      _currentWindowId;

    /*---------------------------------------------------------------------*/
    /*! \name   Static GL Object / Extension variables                     */
    /*! \{                                                                 */

#ifndef OSG_EMBEDDED
    static  LockRefPtr                _GLObjectLock;
    static  LockRefPtr                _staticWindowLock;
#endif

    static std::vector<GLObject  *>   _glObjects;
    static const Char8               *_glLibraryName;

    /**
     * List of registered extension names. The index of the entry is the
     * id/handle of the extention.
     */
    static  std::vector<std::string>  _registeredExtensions;
    /** List of names of extensions to ignore. */
    static  std::vector<std::string>  _ignoredExtensions;
    static  std::vector<bool       >  _commonExtensions;       /**< ??? */
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

    std::vector<UInt32             >  _lastValidate;
    std::vector<GLObjectId         >  _ids;

    UInt32                            _glVersion;
    std::vector<std::string        >  _extensions;
    /**
     * List of whether extension can be used in current context. Indexed by
     * extension id (registeredExtensions).
     */
    std::vector<bool               >  _availExtensions;
    std::vector<GLExtensionFunction>  _extFunctions;

    ConstHash                         _availConstants;
    UInt32                            _numAvailConstants;

    Int32                             _windowId;
    TraversalValidator               *_pTravValidator;
    ShaderCache                      *_pShaderCache;

    WindowDrawTaskRefPtr              _pInitTask;
    WindowDrawTaskRefPtr              _pWaitTask;
    WindowDrawTaskRefPtr              _pSwapTask;
    WindowDrawTaskRefPtr              _pFrameInitTask;
    WindowDrawTaskRefPtr              _pFrameExitTask;
    WindowDrawTaskRefPtr              _pActivateTask;

    DrawEnv                           _oEnv;

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
