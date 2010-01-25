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

#ifndef _OSGSHLCHUNK_H_
#define _OSGSHLCHUNK_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGSHLChunkBase.h"
#include "OSGWindow.h"

#include <string>
#include <vector>
#include <map>

OSG_BEGIN_NAMESPACE

class Window;
class SHLParameterChunk;
class ShaderProgram;

/*! \brief SHLChunk class.
*/
class OSG_STATE_DLLMAPPING SHLChunk : public SHLChunkBase
{
  private:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef SHLChunkBase Inherited;

    typedef GLint (OSG_APIENTRY *GetUniformLocProc)(      GLuint  programObj,
                                                    const Char8  *name);

    typedef void (*parametercbfp  ) (GetUniformLocProc  getUniformLocation,
                                     DrawEnv           *pEnv,
                                     GLuint             program);

    typedef void (*osgparametercbfp)(ShaderParameter * const parameter,
                                           DrawEnv   *       pEnv,
                                           GLuint            program);

    /*---------------------------------------------------------------------*/
    /*! \name                 Chunk Class Access                           */
    /*! \{                                                                 */

    virtual const StateChunkClass *getClass(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name              Static Chunk Class Access                       */
    /*! \{                                                                 */

    static       UInt32           getStaticClassId(void);
    static const StateChunkClass *getStaticClass  (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Chunk Id                                  */
    /*! \{                                                                 */

    virtual UInt16 getChunkId(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin,
                         BitVector         details);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Paramerters                            */
    /*! \{                                                                 */

#ifndef OSG_1_COMPAT
  protected:
#endif

    void updateParameters(      
              Window                         *win,
        const MFUnrecChildShaderParameterPtr &parameters,
              bool                            useProgram       = true,
              bool                            force            = false,
              bool                            keepProgramActive=false);
    

    void updateProgramParameters(Window *win);

    static void updateParameterLocation(Window          *       win, 
                                        GLuint                  program,
                                        ShaderParameter * const parameter);

    void updateParameterLocations(
              Window                         *win,
        const MFUnrecChildShaderParameterPtr &parameters);

#ifndef OSG_1_COMPAT
  public:
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       State                                  */
    /*! \{                                                                 */

#ifdef OSG_1_COMPAT
    virtual void update    (DrawEnv    *pEnv     );
#endif

    virtual void activate  (DrawEnv    *pEnv,
                            UInt32      index = 0);

    virtual void changeFrom(DrawEnv    *pEnv,
                            StateChunk *old,
                            UInt32      index = 0);

    virtual void deactivate(DrawEnv    *action,
                            UInt32      index = 0);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Comparison                                */
    /*! \{                                                                 */

    virtual Real32 switchCost(StateChunk *chunk);

    virtual bool   operator <  (const StateChunk &other) const;

    virtual bool   operator == (const StateChunk &other) const;
    virtual bool   operator != (const StateChunk &other) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Cluster                                   */
    /*! \{                                                                 */

#ifdef OSG_1_COMPAT
    static void setClusterId(Int32 id);
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Parameter Callbacks                       */
    /*! \{                                                                 */

    void addParameterCallback(const char *name, parametercbfp    fp);
    void addParameterCallback(const char *name, osgparametercbfp fp);

#ifdef OSG_1_COMPAT
    static void setParameterCallback(parametercbfp fp);
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Program Parameter                         */
    /*! \{                                                                 */

#ifdef OSG_1_COMPAT
  protected:
#endif

    void addProgramParameter(GLenum name, UInt32 value);
    void subProgramParameter(GLenum name);

#ifdef OSG_1_COMPAT
  public:
#endif

    void setProgramParameter(GLenum name, UInt32 value);
    UInt32 getProgramParameter(GLenum name);
#ifdef OSG_1_COMPAT
    std::vector<std::pair<GLenum, UInt32> > getProgramParameters(void);
#endif

    void clearProgramParameters(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Parameter funcs                           */
    /*! \{                                                                 */

#ifndef OSG_1_COMPAT
  protected:
#endif

    static UInt32 getFuncUniform1i       (void);
    static UInt32 getFuncUniform1iv      (void);
    static UInt32 getFuncUniform2iv      (void);
    static UInt32 getFuncUniform3iv      (void);
    static UInt32 getFuncUniform4iv      (void);

    static UInt32 getFuncUniform1f       (void);
    static UInt32 getFuncUniform1fv      (void);
    static UInt32 getFuncUniform2fv      (void);
    static UInt32 getFuncUniform3fv      (void);
    static UInt32 getFuncUniform4fv      (void);

    static UInt32 getFuncUniformMatrix4fv(void);

    static UInt32 getFuncGetUniformiv    (void);
    static UInt32 getFuncGetUniformfv    (void);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    UInt16 _uiChunkId;

    void onCreate      (const SHLChunk *source      = NULL);
    void onCreateAspect(const SHLChunk *createAspect,
                        const SHLChunk *source      = NULL);
    void onDestroy(           UInt32    uiId              );

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    SHLChunk(void);
    SHLChunk(const SHLChunk &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SHLChunk(void);

    /*! \}                                                                 */

    static void   initMethod     (InitPhase                ePhase);

    static volatile UInt16 _uiChunkCounter;

    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class SHLChunkBase;
    friend class SHLParameterChunk;
    friend class ShaderProgram;

    // class. Used for indexing in State
    static StateChunkClass _class;

    /*---------------------------------------------------------------------*/
    /*! \name            OpenGL Extension Handling                         */
    /*! \{                                                                 */

    static UInt32 _shl_extension;
    static UInt32 _cg_extension;
    static UInt32 _geometry_extension;

    static UInt32 _funcCreateProgramObject;
    static UInt32 _funcProgramParameteri;
    static UInt32 _funcCreateShaderObject;
    static UInt32 _funcDeleteObject;
    static UInt32 _funcDetachObject;
    static UInt32 _funcAttachObject;

    static UInt32 _funcShaderSource;
    static UInt32 _funcCompileShader;
    static UInt32 _funcLinkProgram;
    static UInt32 _funcGetInfoLog;
    static UInt32 _funcUseProgramObject;

    static UInt32 _funcGetObjectParameteriv;
    static UInt32 _funcGetObjectParameterfv;
    static UInt32 _funcGetUniformLocation;

    static UInt32 _funcBindAttribLocation;
    static UInt32 _funcGetAttribLocation;

    static UInt32 _funcUniform1i;
    static UInt32 _funcUniform1iv;
    static UInt32 _funcUniform2iv;
    static UInt32 _funcUniform3iv;
    static UInt32 _funcUniform4iv;

    static UInt32 _funcUniform1f;
    static UInt32 _funcUniform1fv;
    static UInt32 _funcUniform2fv;
    static UInt32 _funcUniform3fv;
    static UInt32 _funcUniform4fv;

    static UInt32 _funcUniformMatrix4fv;

    static UInt32 _funcGetUniformiv;
    static UInt32 _funcGetUniformfv;

    static Int32 _clusterId;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

           UInt32 handleGL       (DrawEnv                 *pEnv, 
                                  UInt32                   id, 
                                  Window::GLObjectStatusE  mode,
                                  UInt32                   uiOptions);

    static void   handleDestroyGL(DrawEnv                 *pEnv, 
                                  UInt32                   id, 
                                  Window::GLObjectStatusE  mode     );

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const SHLChunk &source);

    void updateProgram      (Window         *win    );
    void checkOSGParameters (bool force = false     );
    void updateOSGParameters(DrawEnv        *pEnv,
                             GLuint          program,
                             bool update = false);


    static void updateWorldMatrix        (ShaderParameter * const parameter,
                                          DrawEnv         *       pEnv, 
                                          GLuint                  program  );

    static void updateInvWorldMatrix     (ShaderParameter * const parameter,
                                          DrawEnv         *       pEnv, 
                                          GLuint                  program  );

    static void updateTransInvWorldMatrix(ShaderParameter * const parameter,
                                          DrawEnv         *       pEnv, 
                                          GLuint                  program  );

    static void updateCameraOrientation  (ShaderParameter * const parameter,
                                          DrawEnv         *       pEnv,
                                          GLuint                  program  );

    static void updateCameraPosition     (ShaderParameter * const parameter,
                                          DrawEnv         *       pEnv,
                                          GLuint                  program  );

    static void updateViewMatrix         (ShaderParameter * const parameter,
                                          DrawEnv         *       pEnv,
                                          GLuint                  program  );

    static void updateInvViewMatrix      (ShaderParameter * const parameter,
                                          DrawEnv         *       pEnv,
                                          GLuint                  program  );

    static void updateStereoLeftEye      (ShaderParameter * const parameter,
                                          DrawEnv         *       pEnv,
                                          GLuint                  program  );

    static void updateClusterId          (ShaderParameter * const parameter,
                                          DrawEnv         *       pEnv,
                                          GLuint                  program  );

    static void updateActiveLightsMask   (ShaderParameter * const parameter,
                                          DrawEnv         *       pEnv,
                                          GLuint                  program  );

    static void updateLight0Active       (ShaderParameter * const parameter,
                                          DrawEnv         *       pEnv,
                                          GLuint                  program  );

    static void updateLight1Active       (ShaderParameter * const parameter,
                                          DrawEnv         *       pEnv,
                                          GLuint                  program  );

    static void updateLight2Active       (ShaderParameter * const parameter,
                                          DrawEnv         *       pEnv,
                                          GLuint                  program  );

    static void updateLight3Active       (ShaderParameter * const parameter,
                                          DrawEnv         *       pEnv,
                                          GLuint                  program  );

    static void updateLight4Active       (ShaderParameter * const parameter,
                                          DrawEnv         *       pEnv,
                                          GLuint                  program  );

    static void updateLight5Active       (ShaderParameter * const parameter,
                                          DrawEnv         *       pEnv,
                                          GLuint                  program  );

    static void updateLight6Active       (ShaderParameter * const parameter,
                                          DrawEnv         *       pEnv,
                                          GLuint                  program  );

    static void updateLight7Active       (ShaderParameter * const parameter,
                                          DrawEnv         *       pEnv,
                                          GLuint                  program  );


    typedef std::vector<
        std::pair<   std::pair<parametercbfp, 
                               osgparametercbfp>,
                     ShaderParameter *         > > OSGParametersCallbacks;

    typedef std::map<std::string, 
                     std::pair<parametercbfp, 
                               osgparametercbfp> > UserParameterCallbacksMap;


           OSGParametersCallbacks    _osgParametersCallbacks;
           UInt32                    _oldParameterSize;

           UserParameterCallbacksMap _userParameterCallbacks;
    static parametercbfp             _userParametersCallback;
};

typedef SHLChunk *SHLChunkP;

OSG_END_NAMESPACE

#include "OSGSHLChunkBase.inl"
#include "OSGSHLChunk.inl"

#endif /* _OSGCGCHUNK_H_ */
