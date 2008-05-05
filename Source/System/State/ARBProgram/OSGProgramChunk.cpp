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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <cstdlib>
#include <cstdio>
#include <boost/bind.hpp>

#include <OSGConfig.h>

#include <OSGGL.h>
#include <OSGGLU.h>
#include <OSGGLEXT.h>

#include <OSGBaseFunctions.h>

#include "OSGDrawEnv.h"
#include "OSGWindow.h"

#include "OSGProgramChunk.h"

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGProgramChunkBase.cpp file.
// To modify it, please change the .fcd file (OSGProgramChunk.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

StateChunkClass ProgramChunk::_class("Program");

UInt32 ProgramChunk::_funcGenPrograms              = Window::invalidFunctionID;
UInt32 ProgramChunk::_funcProgramString            = Window::invalidFunctionID;
UInt32 ProgramChunk::_funcBindProgram              = Window::invalidFunctionID;
UInt32 ProgramChunk::_funcDeletePrograms           = Window::invalidFunctionID;
UInt32 ProgramChunk::_funcProgramLocalParameter4fv = Window::invalidFunctionID;
UInt32 ProgramChunk::_funcGetProgramiv             = Window::invalidFunctionID;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ProgramChunk::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        UInt32 extension = Window::registerExtension("GL_ARB_vertex_program");
    
        _funcGenPrograms                    =
            Window::registerFunction (OSG_DLSYM_UNDERSCORE"glGenProgramsARB", 
                                      extension);

        _funcProgramString                  =
            Window::registerFunction(OSG_DLSYM_UNDERSCORE"glProgramStringARB", 
                                     extension);
        _funcBindProgram                    =
            Window::registerFunction(OSG_DLSYM_UNDERSCORE"glBindProgramARB", 
                                     extension);
        _funcDeletePrograms                 =
            Window::registerFunction(OSG_DLSYM_UNDERSCORE"glDeleteProgramsARB",
                                     extension);
        _funcProgramLocalParameter4fv       =
            Window::registerFunction(OSG_DLSYM_UNDERSCORE
                                     "glProgramLocalParameter4fvARB", 
                                     extension);
        _funcGetProgramiv       =
            Window::registerFunction(OSG_DLSYM_UNDERSCORE"glGetProgramivARB", 
                                     extension);
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ProgramChunk::ProgramChunk(void) :
    Inherited()
{
}

ProgramChunk::ProgramChunk(const ProgramChunk &source) :
    Inherited(source)
{
}

ProgramChunk::~ProgramChunk(void)
{
    if(getGLId() > 0)
        Window::destroyGLObject(getGLId());
}

/*----------------------------- onCreate --------------------------------*/

void ProgramChunk::onCreate(const ProgramChunk *)
{
    if(GlobalSystemState == Startup)
        return;
}


/*------------------------- Chunk Class Access ---------------------------*/

const StateChunkClass *ProgramChunk::getClass(void) const
{
    return &_class;
}

/*----------------------------- class specific ----------------------------*/

void ProgramChunk::changed(ConstFieldMaskArg whichField, 
                           UInt32            origin,
                           BitVector         details)
{
    Inherited::changed(whichField, origin, details);
    
    if(whichField & ProgramFieldMask)
    {
        Window::reinitializeGLObject(getGLId());
    }  
     
    if(whichField & ParamValuesFieldMask)
    {
        Window::refreshGLObject(getGLId());
    }
}

/*------------------------------ Output ----------------------------------*/

void ProgramChunk::dump(      UInt32    , 
                        const BitVector ) const
{
    SLOG << "Dump ProgramChunk NI" << std::endl;
}

/*---------------------------- Access ------------------------------------*/

/*! Read the program string from the given file
 */
bool ProgramChunk::read(const char *file)
{
    std::ifstream s(file);
    
    if(s.good())
    {
        return read(s);
    }
    else
    {
        FWARNING(("ProgramChunk::read: couldn't open '%s' for reading!\n",
                    file));
        return false;
    }
}

/*! Read the program string from the given stream
 */

bool ProgramChunk::read(std::istream &stream)
{
#define BUFSIZE 200
    
    editProgram().erase();    
    char buf[BUFSIZE];

    if(!stream.good())
    {
        FWARNING(("ProgramChunk::read: stream is not good!\n"));
        return false;
   
    }
    
    do
    {
        stream.read(buf, BUFSIZE);
        editProgram().append(buf, stream.gcount());
    }
    while(!stream.eof());
    
    return true;
}
    
/*! Add a named parameter 
*/
bool ProgramChunk::addParameter(const char   *name, 
                                      Int16  index)
{
    if(index < 0)
        return true;
        
    if(getMFParamNames()->size() <= UInt16(index))
    {
        editMFParamNames()->resize(index + 1);
    }

    editParamNames(index) = name;

    return false;
}
    
const Vec4f ProgramChunk::getParameter(Int16 index)
{
    static const Vec4f bad(-1e10,-1e10,-1e10);
    
    if(index < 0)
        return bad;
        
    if(getMFParamValues()->size() <= UInt16(index))
    {
        return getParamValues(index);
    }
    
    return bad;
}
 
/*! Set parameter value, create it if not set yet.
*/
bool ProgramChunk::setParameter(Int16 index, const Vec4f& value)
{
    if(index < 0)
        return true;
        
    if(getMFParamValues()->size() <= UInt16(index))
    {
        editMFParamValues()->resize(index + 1);
    }

    editParamValues(index) = value;

    return false;
}

/*! Find the index for a named parameter, return -1 if not found.
*/
Int16 ProgramChunk::findParameter(const std::string &name)
{
    MField<std::string>::const_iterator it;
    
    it = std::find(getMFParamNames()->begin(), 
                   getMFParamNames()->end(), name);

    if(it == getMFParamNames()->end())
        return -1;

    return it - getMFParamNames()->begin();
}


/*------------------------------ State ------------------------------------*/

/*! Print the error message if compilation fails
*/
void ProgramChunk::printCompileError(Window *win, UInt32 id)
{
    Window::GLObjectStatusE mode;
        
    GLint pos;   
    glGetIntegerv(GL_PROGRAM_ERROR_POSITION_ARB, &pos);
    
    FWARNING(("ProgramChunk(%p:%d,%d): error compiling program "
              "at position %d: %s\n",
              win, id, mode, pos, glGetString(GL_PROGRAM_ERROR_STRING_ARB)));
    
    UInt32 start = 0, end, line = 0;
    
    for(end = 0; end < getProgram().size(); ++end)
    {
        if(getProgram()[end] == '\n')
        {
            ++line;
            
            if(UInt32(pos) < end)
                break;
            
            start = end + 1;
        }
    }
    
    std::string mesg;
    
    for(UInt32 i = start; i < end; ++i)
    {
        if(i == pos)
        {
            mesg += '>';
            mesg += '>';
        }
        
        mesg += getProgram()[i];

        if(i == pos)
        {
            mesg += '<';
            mesg += '<';
        }
    }
    
    SWARNING << "Location (line " << line << "): " << mesg << endLog;
}

/*! GL object handler
    create the program
*/
void ProgramChunk::handleGL(DrawEnv *pEnv, UInt32 osgid, 
                    Window::GLObjectStatusE mode, 
                    GLenum target, 
                    UInt32 extension)
{
    GLuint id;
    Window *win = pEnv->getWindow();

    // get the program-specific specifics from the derived chunks
    //GLenum target = getTarget();
    //UInt32 extension = getExtension();

    if(!win->hasExtension(extension))
        return;

    id = win->getGLObjectId(osgid);

    if(mode == Window::initialize || mode == Window::reinitialize ||
       mode == Window::needrefresh)
    {
        if(mode == Window::initialize)
        {
            // get "glGenProgramsARB" function pointer
            void (OSG_APIENTRY* genPrograms)(GLsizei n, GLuint *prog) =
                (void (OSG_APIENTRY*)(GLsizei n, GLuint *prog))
                win->getFunction(_funcGenPrograms);

            genPrograms(1, &id);
            win->setGLObjectId(osgid, id);
        }

        // get "glBindProgramARB" function pointer
        void (OSG_APIENTRY* bindProgram)(GLenum target, GLuint prog) =
            (void (OSG_APIENTRY*)(GLenum target, GLuint prog))
            win->getFunction(_funcBindProgram);
             
        glErr("ProgramChunk::handleGL: bindProgram precheck");
        
        bindProgram(target, id);
             
        glErr("ProgramChunk::handleGL: bindProgram postcheck");
        
        if(mode != Window::needrefresh)
        {
            // get "glProgramStringARB" function pointer
            void (OSG_APIENTRY* programString)(GLenum target, GLenum format, 
                        GLsizei lesn, const void *string) =
                (void (OSG_APIENTRY*)(GLenum target, GLenum format, 
                        GLsizei len, const void *string))
                win->getFunction(_funcProgramString);
            
            glErr("ProgramChunk::handleGL: programString precheck");
            
            glEnable(target);
            
            glErr("ProgramChunk::handleGL: enable postcheck");
            
            programString(target, GL_PROGRAM_FORMAT_ASCII_ARB,
                            getProgram().size(), getProgram().c_str());
            
            GLenum err = glGetError();
            
            if(err == GL_INVALID_OPERATION)
            {
                printCompileError(win, osgid);
            }
            else if (err != GL_NO_ERROR)
            {
                SWARNING << "ProgramChunk::programString postcheck failed:"
                         << gluErrorString(err) << endLog;
            }
            
            glDisable(target);
            
            glErr("ProgramChunk::handleGL: disable postcheck");
        }
        
        void (OSG_APIENTRY* programLocalParameter4fv)(GLenum target, 
                        GLuint index, const GLfloat *params) =
            (void (OSG_APIENTRY*)(GLenum target, 
                        GLuint index, const GLfloat *params))
            win->getFunction(_funcProgramLocalParameter4fv);
             
        glErr("ProgramChunk::handleGL: programLocalParameter precheck");
       
        for(UInt16 i = 0; i < getMFParamValues()->size(); ++i)
        {
            const Vec4f &val = _mfParamValues[i];
            
            programLocalParameter4fv(target, i, val.getValues());
            
            glErr("ProgramChunk::handleGL: programLocalParameter");
        }      
             
        glErr("ProgramChunk::handleGL: programLocalParameter postcheck");
    }
    else
    {
        SWARNING << "ProgramChunk(" << this << "::handleGL: Illegal mode: "
             << mode << " for id " << id << std::endl;
    }

}

/*! GL object handler
    destroy it
*/
void ProgramChunk::handleDestroyGL(DrawEnv *pEnv, UInt32 osgid, 
                    Window::GLObjectStatusE mode, 
                    GLenum Target, 
                    UInt32 extension)
{
    GLuint id;
    Window *win = pEnv->getWindow();

    // get the program-specific specifics from the derived chunks
    //GLenum target = getTarget();
    //UInt32 extension = getExtension();

    if(!win->hasExtension(extension))
        return;

    id = win->getGLObjectId(osgid);

    if(mode == Window::destroy)
    {
        // get "glDeleteProgramsARB" function pointer
        void (OSG_APIENTRY* deletePrograms)(GLsizei num, const GLuint *progs) =
            (void (OSG_APIENTRY*)(GLsizei num, const GLuint *progs))
            win->getFunction(_funcDeletePrograms);

        deletePrograms(1, &id);

        win->setGLObjectId(osgid, 0);
    }
    else if(mode == Window::finaldestroy)
    {
        //SWARNING << "Last program user destroyed" << std::endl;
    }
    else
    {
        SWARNING << "ProgramChunk(" << this << "::handleGL: Illegal mode: "
             << mode << " for id " << id << std::endl;
    }

}

void ProgramChunk::activate(DrawEnv *pEnv, UInt32)
{
    // get the program-type specifics from the derived chunks
    GLenum target = getTarget();
    UInt32 extension = getExtension();

    if(!pEnv->getWindow()->hasExtension(extension))
    {
        return;
    }
    
    if(getProgram().empty())
        return;
        
    pEnv->getWindow()->validateGLObject(getGLId(), pEnv);
           
    // get "glBindProgramARB" function pointer
    void (OSG_APIENTRY* bindProgram)(GLenum target, GLuint prog) =
        (void (OSG_APIENTRY*)(GLenum target, GLuint prog))
        pEnv->getWindow()->getFunction(_funcBindProgram);
             
    glErr("ProgramChunk::activate: bindProgram precheck");

    glEnable(target);
             
    glErr("ProgramChunk::activate: enable postcheck");

    bindProgram(target, pEnv->getWindow()->getGLObjectId(getGLId()));
             
    glErr("ProgramChunk::activate: bindProgram postcheck");
}

void ProgramChunk::changeFrom(DrawEnv    *pEnv, 
                              StateChunk  *old_chunk, 
                              UInt32                )
{
    ProgramChunk *old = dynamic_cast<ProgramChunk *>(old_chunk);

    if(old == NULL)
    {
        FWARNING(( "ProgramChunk::changeFrom: caught non-ProgramChunk!\n"));
        return;
    }
       
    // get the program-type specifics from the derived chunks
    GLenum target = getTarget();
    UInt32 extension = getExtension();

    if(!pEnv->getWindow()->hasExtension(extension))
        return;
     
    if(getProgram().empty())
    {
        if(old->getProgram().empty())
            return;
        
        glDisable(target);
    }

    pEnv->getWindow()->validateGLObject(getGLId(), pEnv);
           
    // get "glBindProgramARB" function pointer
    void (OSG_APIENTRY* bindProgram)(GLenum target, GLuint prog) =
        (void (OSG_APIENTRY*)(GLenum target, GLuint prog))
        pEnv->getWindow()->getFunction(_funcBindProgram);
             
    glErr("ProgramChunk::changeFrom: bindProgram precheck");

    if(old->getProgram().empty())
        glEnable(target);
             
    glErr("ProgramChunk::changeFrom: enable postcheck");

    bindProgram(target, pEnv->getWindow()->getGLObjectId(getGLId()));
             
    glErr("ProgramChunk::changeFrom: bindProgram postcheck");
}

void ProgramChunk::deactivate(DrawEnv *pEnv, UInt32)
{
    // get the program-type specifics from the derived chunks
    GLenum target = getTarget();
    UInt32 extension = getExtension();

    if(!pEnv->getWindow()->hasExtension(extension))
    {
        return;
    }
    
    if(getProgram().empty())
    {
        return;
    }
           
    // get "glBindProgramARB" function pointer
    void (OSG_APIENTRY* bindProgram)(GLenum target, GLuint prog) =
        (void (OSG_APIENTRY*)(GLenum target, GLuint prog))
        pEnv->getWindow()->getFunction(_funcBindProgram);

             
    glErr("ProgramChunk::deactivate: bindProgram precheck");

    bindProgram(target, pEnv->getWindow()->getGLObjectId(getGLId()));
             
    glErr("ProgramChunk::deactivate: bindProgram postcheck");

    glDisable(target);
             
    glErr("ProgramChunk::deactivate: disable postcheck");
}


/*! Virtual helper function to let the derived chunks return the extension that
    they implement. Only if this extension is supproted on the current Window
    is the porgram called.
*/

UInt32 ProgramChunk::getExtension(void) const
{
    FWARNING(( "ProgramChunk::getExtension called!\n" ));
    return 0;
}

/*! Virtual helper function to let the derived chunks return the target
    constant that they implement.
*/

GLenum ProgramChunk::getTarget(void) const
{
    FWARNING(( "ProgramChunk::getTarget called!\n" ));
    return 0;
}


/*! Virtual helper function to let the derived chunks return the name of the
    target constant that they implement, for debugging purposes.
*/

const char *ProgramChunk::getTargetName(void) const
{
    FWARNING(( "ProgramChunk::getTargetName called!\n" ));
    return "ERROR";
}

/*-------------------------- Comparison -----------------------------------*/

bool ProgramChunk::isTransparent(void) const
{
    return false;
}

Real32 ProgramChunk::switchCost(StateChunk *)
{
    return 0;
}

bool ProgramChunk::operator < (const StateChunk &other) const
{
    return this < &other;
}

bool ProgramChunk::operator == (const StateChunk &other) const
{
    ProgramChunk const *tother = dynamic_cast<ProgramChunk const*>(&other);

    if(!tother)
        return false;

    if(tother == this)
        return true;

    if(getProgram()               != tother->getProgram      ()         ||
       getMFParamValues()->size() != tother->getMFParamValues()->size() ||
       getMFParamNames()->size()  != tother->getMFParamNames ()->size()  )
        return false;

    // !!! FIXME: implement    
    
    return false;
}

bool ProgramChunk::operator != (const StateChunk &other) const
{
    return ! (*this == other);
}

