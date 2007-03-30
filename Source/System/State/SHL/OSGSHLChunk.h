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
class DrawActionBase;

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

    typedef void (*paramtercbfp) (GetUniformLocProc  getUniformLocation,
                                  DrawEnv           *pEnv,
                                  GLuint             program);

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

    virtual void changed(ConstFieldMaskArg  whichField,
                         UInt32             origin    );

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

    void updateParameters(      Window               *win,
                          const MFShaderParameterPtr &parameters,
                                bool                 useProgram       = true,
                                bool                 force            = false,
                                bool                 keepProgramActive=false);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       State                                  */
    /*! \{                                                                 */

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

    static void setClusterId(Int32 id);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Parameter Callbacks                       */
    /*! \{                                                                 */

    void addParameterCallback(const char *name, paramtercbfp fp);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Parameter funcs                           */
    /*! \{                                                                 */

    static UInt32 getFuncUniform1i       (void);
    static UInt32 getFuncUniform2iv      (void);
    static UInt32 getFuncUniform3iv      (void);
    static UInt32 getFuncUniform4iv      (void);

    static UInt32 getFuncUniform1f       (void);
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

    static volatile UInt16 _uiChunkCounter;

    /*==========================  PRIVATE  ================================*/

  private:

    friend class SHLChunkBase;

    template<class ContainerFactoryT>
    friend struct CPtrConstructionFunctions;

    template<class ContainerFactoryT>
    friend struct PtrConstructionFunctions;

    typedef std::map<std::string, paramtercbfp> userParameterCallbacksMap;

    // class. Used for indexing in State
    static StateChunkClass _class;

    /*---------------------------------------------------------------------*/
    /*! \name            OpenGL Extension Handling                         */
    /*! \{                                                                 */

    static UInt32 _shl_extension;
    static UInt32 _cg_extension;

    static UInt32 _funcCreateProgramObject;
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
    static UInt32 _funcUniform2iv;
    static UInt32 _funcUniform3iv;
    static UInt32 _funcUniform4iv;

    static UInt32 _funcUniform1f;
    static UInt32 _funcUniform2fv;
    static UInt32 _funcUniform3fv;
    static UInt32 _funcUniform4fv;

    static UInt32 _funcUniformMatrix4fv;

    static UInt32 _funcGetUniformiv;
    static UInt32 _funcGetUniformfv;

    static Int32 _clusterId;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

    static void initMethod(InitPhase ePhase);

    void handleGL(DrawEnv *pEnv, UInt32 id, Window::GLObjectStatusE mode);
    void handleDestroyGL(DrawEnv *pEnv, UInt32 id, Window::GLObjectStatusE mode);

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const SHLChunk &source);

    void updateProgram      (Window         *win    );
    void checkOSGParameters (void                   );
    void updateOSGParameters(DrawEnv        *pEnv,
                             GLuint          program);


    static void updateCameraOrientation(GetUniformLocProc  getUniformLocation,
                                        DrawEnv           *pEnv,
                                        GLuint             program           );

    static void updateCameraPosition   (GetUniformLocProc  getUniformLocation,
                                        DrawEnv           *pEnv,
                                        GLuint             program           );

    static void updateViewMatrix       (GetUniformLocProc  getUniformLocation,
                                        DrawEnv           *pEnv,
                                        GLuint             program           );

    static void updateInvViewMatrix    (GetUniformLocProc  getUniformLocation,
                                        DrawEnv           *pEnv,
                                        GLuint             program           );

    static void updateStereoLeftEye    (GetUniformLocProc  getUniformLocation,
                                        DrawEnv           *pEnv,
                                        GLuint             program           );

    static void updateClusterId        (GetUniformLocProc  getUniformLocation,
                                        DrawEnv           *pEnv,
                                        GLuint             program           );

    static void updateActiveLightsMask (GetUniformLocProc  getUniformLocation,
                                        DrawEnv           *pEnv,
                                        GLuint             program           );

    static void updateLight0Active     (GetUniformLocProc  getUniformLocation,
                                        DrawEnv           *pEnv,
                                        GLuint             program           );

    static void updateLight1Active     (GetUniformLocProc  getUniformLocation,
                                        DrawEnv           *pEnv,
                                        GLuint             program           );

    static void updateLight2Active     (GetUniformLocProc  getUniformLocation,
                                        DrawEnv           *pEnv,
                                        GLuint             program           );

    static void updateLight3Active     (GetUniformLocProc  getUniformLocation,
                                        DrawEnv           *pEnv,
                                        GLuint             program           );

    static void updateLight4Active     (GetUniformLocProc  getUniformLocation,
                                        DrawEnv           *pEnv,
                                        GLuint             program           );

    static void updateLight5Active     (GetUniformLocProc  getUniformLocation,
                                        DrawEnv           *pEnv,
                                        GLuint             program           );

    static void updateLight6Active     (GetUniformLocProc  getUniformLocation,
                                        DrawEnv           *pEnv,
                                        GLuint             program           );

    static void updateLight7Active     (GetUniformLocProc  getUniformLocation,
                                        DrawEnv           *pEnv,
                                        GLuint             program           );


    std::vector<paramtercbfp> _osgParametersCallbacks;

    UInt32                    _oldParameterSize;

    userParameterCallbacksMap _userParameterCallbacks;
};

typedef SHLChunk *SHLChunkP;

OSG_END_NAMESPACE

#include "OSGSHLChunkBase.inl"
#include "OSGSHLChunk.inl"

#define OSGSHLCHUNK_HEADER_CVSID "@(#)$Id$"

#endif /* _OSGCGCHUNK_H_ */
