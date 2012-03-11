/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
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

#ifndef _OSGGPUVOLRTV1_H_
#define _OSGGPUVOLRTV1_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGGPUVolRTV1Base.h"

OSG_BEGIN_NAMESPACE

/*! \brief GPUVolRTV1 class. See \ref
           PageIEInitAlgoGPUVolRTV1 for a description.
*/

class OSG_EXGPUVOLRT_DLLMAPPING GPUVolRTV1 : public GPUVolRTV1Base
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef GPUVolRTV1Base Inherited;
    typedef GPUVolRTV1     Self;

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

    virtual Action::ResultE renderEnter(Action  *pAction);
    virtual Action::ResultE renderLeave(Action  *pAction);
    virtual void            execute    (DrawEnv *pEnv   );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    void   setStepsize     (Real32 rVal);
    Real32 getStepsize     (void       );

    void   setToggleVisuals(bool   bVal);
    bool   getToggleVisuals(void       );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in GPUVolRTV1Base.

    bool bInitialized;

    GLuint renderbuffer; 
    GLuint framebuffer; 
    GLuint volume_texture; // the volume texture
    GLuint backface_buffer; // the FBO buffers
    GLuint final_image;
    float stepsize;
    float mModelView[16];
    float mProj[16];
    
    GLuint vertexprog;
    GLuint fragmentprog;
    GLuint shaderprog;
    GLuint stepsizeLoc;
    GLuint mvLoc;
    GLuint mpLoc;
    GLuint texLoc;
    GLuint volumeTexLoc;
    bool   toggle_visuals;

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    GPUVolRTV1(void);
    GPUVolRTV1(const GPUVolRTV1 &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~GPUVolRTV1(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                original functions                            */
    /*! \{                                                                 */

    void init   (DrawEnv *pEnv);
    void display(DrawEnv *pEnv);
    void resize (DrawEnv *pEnv, int w, int h );

    void create_volumetexture   (void                                      );
    void load_vertex_program    (GLuint &v_program, const char *shader_path);
    void load_fragment_program  (GLuint &f_program, const char *shader_path);
    void check_program_status   (GLuint  uiProgram                         );
    void enable_renderbuffers   (void                                      );
    void disable_renderbuffers  (void                                      );
    void render_backface        (void                                      );
    void raycasting_pass        (void                                      );
    void render_buffer_to_screen(DrawEnv *pEnv                             );
    bool readProgram            (std::string  &szTarget,
                                 std::istream &iStream                     );
    void check_shader_status    (GLuint        uiShader                    );

    void drawQuads              (float x, float y, float z                 );

    void set_tex_param          (GLuint texLoc, GLuint tex, GLuint prog, 
                                 GLuint unit,   GLuint target              );

    void reshape_ortho          (int w, int h                              );
    void draw_fullscreen_quad   (void                                      );
    void vertex                 (float x, float y, float z                 );

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class GPUVolRTV1Base;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const GPUVolRTV1 &source);
};

typedef GPUVolRTV1 *GPUVolRTV1P;

OSG_END_NAMESPACE

#include "OSGGPUVolRTV1Base.inl"
#include "OSGGPUVolRTV1.inl"

#endif /* _OSGGPUVOLRTV1_H_ */
