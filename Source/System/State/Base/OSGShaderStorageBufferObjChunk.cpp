/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2013 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 * contact: dirk@opensg.org, gerrit.voss@vossg.org, carsten_neumann@gmx.net  *
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
#include <boost/algorithm/string.hpp>
#include <boost/range/iterator_range_core.hpp>
#include <boost/unordered_map.hpp>

#include "OSGConfig.h"

#include "OSGGL.h"
#include "OSGGLU.h"
#include "OSGGLEXT.h"
#include "OSGWindow.h"

#include "OSGGLFuncProtos.h"

#include "OSGDrawEnv.h"

#include "OSGShaderStorageBufferObjChunk.h"

OSG_BEGIN_NAMESPACE


struct bracket_expr_finder
{
    bracket_expr_finder(int& index) : idx(index) {}

    template<typename ForwardIteratorT>
    boost::iterator_range<ForwardIteratorT> operator()(
        ForwardIteratorT iter,
        ForwardIteratorT end )
    {
        ForwardIteratorT Begin = iter;
        ForwardIteratorT End   = iter;

        for (; iter != end; ++iter)
        {
            if (*iter == '[')
                Begin = iter;
            else if (*iter == ']')
            {
                End = ++iter;
                break;
            }
        }

        if (Begin != End)
        {
            ForwardIteratorT r1 = Begin;
            ForwardIteratorT r2 = End;
            std::string str(++r1, --r2);
            idx = atoi(str.c_str());
        }

        return boost::make_iterator_range(Begin, End);
    }

    int& idx;
};

// Documentation for this class is emitted in the
// OSGShaderStorageBufferObjChunkBase.cpp file.
// To modify it, please change the .fcd file (OSGShaderStorageBufferObjChunk.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

typedef OSG::Window Win;

UInt32 ShaderStorageBufferObjChunk::_extVertexBufferObject              = Win::invalidExtensionID;
UInt32 ShaderStorageBufferObjChunk::_extUniformBufferObject             = Win::invalidExtensionID;
UInt32 ShaderStorageBufferObjChunk::_extProgramInterfaceQuery           = Win::invalidExtensionID;
UInt32 ShaderStorageBufferObjChunk::_extShaderStorageBufferObject       = Win::invalidExtensionID;

UInt32 ShaderStorageBufferObjChunk::_funcBindBuffer                     = Win::invalidFunctionID;
UInt32 ShaderStorageBufferObjChunk::_funcMapBuffer                      = Win::invalidFunctionID;
UInt32 ShaderStorageBufferObjChunk::_funcUnmapBuffer                    = Win::invalidFunctionID;
UInt32 ShaderStorageBufferObjChunk::_funcBufferData                     = Win::invalidFunctionID;
UInt32 ShaderStorageBufferObjChunk::_funcBufferSubData                  = Win::invalidFunctionID;
UInt32 ShaderStorageBufferObjChunk::_funcGenBuffers                     = Win::invalidFunctionID;
UInt32 ShaderStorageBufferObjChunk::_funcDeleteBuffers                  = Win::invalidFunctionID;
UInt32 ShaderStorageBufferObjChunk::_funcGetBufferParameteriv           = Win::invalidFunctionID;

UInt32 ShaderStorageBufferObjChunk::_funcBindBufferBase                 = Win::invalidFunctionID;

UInt32 ShaderStorageBufferObjChunk::_funcGetProgramResourceIndex        = Win::invalidFunctionID;
UInt32 ShaderStorageBufferObjChunk::_funcGetProgramResourceiv           = Win::invalidFunctionID;
UInt32 ShaderStorageBufferObjChunk::_funcGetProgramResourceName         = Win::invalidFunctionID;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ShaderStorageBufferObjChunk::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        _extVertexBufferObject=
            Window::registerExtension("GL_ARB_vertex_buffer_object");

        _funcBindBuffer = Window::registerFunction(
            OSG_DLSYM_UNDERSCORE"glBindBufferARB",   
            _extVertexBufferObject);

        _funcMapBuffer = Window::registerFunction(
            OSG_DLSYM_UNDERSCORE"glMapBufferARB",   
            _extVertexBufferObject);

        _funcUnmapBuffer = Window::registerFunction(
            OSG_DLSYM_UNDERSCORE"glUnmapBufferARB",   
            _extVertexBufferObject);

        _funcBufferData = Window::registerFunction(
            OSG_DLSYM_UNDERSCORE"glBufferDataARB",   
            _extVertexBufferObject);

        _funcBufferSubData = Window::registerFunction(
            OSG_DLSYM_UNDERSCORE"glBufferSubDataARB",   
            _extVertexBufferObject);

        _funcGenBuffers = Window::registerFunction(
            OSG_DLSYM_UNDERSCORE"glGenBuffersARB",   
            _extVertexBufferObject);

        _funcDeleteBuffers = Window::registerFunction(
            OSG_DLSYM_UNDERSCORE"glDeleteBuffersARB",   
            _extVertexBufferObject);

        _funcGetBufferParameteriv = Window::registerFunction(
            OSG_DLSYM_UNDERSCORE"glGetBufferParameterivARB",   
            _extVertexBufferObject);


        _extShaderStorageBufferObject  =
            Window::registerExtension("GL_ARB_shader_storage_buffer_object"  );

        _funcBindBufferBase = Window::registerFunction(
            OSG_DLSYM_UNDERSCORE"glBindBufferBase",   
            _extShaderStorageBufferObject);


        _extProgramInterfaceQuery  =
            Window::registerExtension("GL_ARB_program_interface_query"  );

        _funcGetProgramResourceIndex = Window::registerFunction(
            OSG_DLSYM_UNDERSCORE"glGetProgramResourceIndex",   
            _extProgramInterfaceQuery);

        _funcGetProgramResourceiv = Window::registerFunction(
            OSG_DLSYM_UNDERSCORE"glGetProgramResourceiv",   
            _extProgramInterfaceQuery);

        _funcGetProgramResourceName = Window::registerFunction(
            OSG_DLSYM_UNDERSCORE"glGetProgramResourceName",   
            _extProgramInterfaceQuery);


        _extShaderStorageBufferObject  =
            Window::registerExtension("GL_ARB_shader_storage_buffer_object"  );
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ShaderStorageBufferObjChunk::ShaderStorageBufferObjChunk(void) :
    Inherited()
{
}

ShaderStorageBufferObjChunk::ShaderStorageBufferObjChunk(const ShaderStorageBufferObjChunk &source) :
    Inherited(source)
{
}

ShaderStorageBufferObjChunk::~ShaderStorageBufferObjChunk(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ShaderStorageBufferObjChunk::changed(ConstFieldMaskArg whichField, 
                                          UInt32            origin,
                                          BitVector         details)
{
    GLenum id = _sfGLId.getValue();

    if((whichField &  ( UsageFieldMask |
                        BlockNameFieldMask |
                        FundamentalTypesFieldMask |
                        MainTypesFieldMask |
                        CardinalityFieldMask |
                        IndexFieldMask |
                        NamesFieldMask |
                        NameToIndexFieldMask |
                        FloatValuesFieldMask |
                        DoubleValuesFieldMask |
                        IntValuesFieldMask |
                        UIntValuesFieldMask |
                        BoolValuesFieldMask     )) != 0)
    {
        Window::refreshGLObject(id);
    }

    Inherited::changed(whichField, origin, details);
}

/*----------------------------- onCreate --------------------------------*/

void ShaderStorageBufferObjChunk::onCreate(const ShaderStorageBufferObjChunk *source)
{
    Inherited::onCreate(source);

    if(GlobalSystemState == Startup)
        return;

    setGLId(Window::registerGLObject(
                boost::bind(&ShaderStorageBufferObjChunk::handleGL, 
                            ShaderStorageBufferObjChunkMTUncountedPtr(this), 
                            _1, _2, _3, _4),
                &ShaderStorageBufferObjChunk::handleDestroyGL));
}

void ShaderStorageBufferObjChunk::onCreateAspect(
    const ShaderStorageBufferObjChunk *createAspect,
    const ShaderStorageBufferObjChunk *source      )
{
    Inherited::onCreateAspect(createAspect, source);
}

void ShaderStorageBufferObjChunk::onDestroy(UInt32 uiContainerId)
{
    if(getGLId() > 0)
        Window::destroyGLObject(getGLId(), 1);

    Inherited::onDestroy(uiContainerId);
}

/*------------------------------ Output ----------------------------------*/

void ShaderStorageBufferObjChunk::dump(      UInt32    uiIndent,
                                       const BitVector bvFlags) const
{
    Inherited::dump(uiIndent, bvFlags);

    if((bvFlags & UsageFieldMask) != 0)
    {
        indentLog(uiIndent, PLOG);
        PLOG << "usage " << _sfUsage.getValue() << "\n";
    }
    if((bvFlags & BlockNameFieldMask) != 0)
    {
        indentLog(uiIndent, PLOG);
        PLOG << "block name " << _sfBlockName.getValue() << "\n";
    }
}

/*------------------------------ GL -----------------------------------------*/

/*! GL object handler                                                        */
UInt32 ShaderStorageBufferObjChunk::handleGL(DrawEnv                 *pEnv, 
                                             UInt32                   osgid, 
                                             Window::GLObjectStatusE  mode,
                                             UInt64                   uiOptions)
{
    Window *pWin = pEnv->getWindow();
    GLuint  id  = pWin->getGLObjectId(osgid);

    bool hasVBO = pWin->hasExtOrVersion(_extVertexBufferObject, 0x0105, 0x0200);
    if(!hasVBO)
    {
        FWARNING(
            ("ShaderStorageBufferObjStdLayoutChunk::handleGL: vertex buffer objects not "
             "supported for this window!\n"));
        return 0;
    }

    bool hasUBO = pWin->hasExtOrVersion(_extUniformBufferObject, 0x0301);
    if(!hasUBO)
    {
        FWARNING(
            ("ShaderStorageBufferObjStdLayoutChunk::handleGL: uniform buffer objects not "
             "supported for this window!\n"));
        return 0;
    }

    bool hasSSBO = pWin->hasExtOrVersion(_extShaderStorageBufferObject, 0x0403);
    if(!hasSSBO)
    {
        FWARNING(
            ("ShaderStorageBufferObjStdLayoutChunk::handleGL: GL_ARB_uniform_buffer_object not "
             "supported for this window!\n"));
        return 0;
    }

    bool hasPIQ = pWin->hasExtOrVersion(_extProgramInterfaceQuery, 0x0402);
    if(!hasPIQ)
    {
        FWARNING(
            ("ShaderStorageBufferObjStdLayoutChunk::handleGL: GL_ARB_program_interface_query not "
             "supported for this window!\n"));
        return 0;
    }

    switch (mode)
    {
        case Window::initialize:
            {
                OSGGETGLFUNCBYID_GL3_ES( glGenBuffers, 
                                         osgGlGenBuffers,
                                        _funcGenBuffers, 
                                         pWin);

                OSGGETGLFUNCBYID_GL3_ES( glBindBuffer,
                                         osgGlBindBuffer,
                                        _funcBindBuffer, 
                                         pWin);

                OSGGETGLFUNCBYID_GL3_ES( glBufferData, 
                                         osgGlBufferData,
                                        _funcBufferData, 
                                         pWin);

                OSGGETGLFUNCBYID_GL3_ES( glBindBufferBase, 
                                         osgGlBindBufferBase,
                                        _funcBindBufferBase, 
                                         pWin);

                osgGlGenBuffers(1, &id);
                pWin->setGLObjectId(osgid, id);

                std::vector<GLubyte> buffer = createBuffer(pEnv);

                std::size_t sz = buffer.size();
                if (sz > 0)
                {
                    osgGlBindBuffer    (GL_SHADER_STORAGE_BUFFER, id);
                    osgGlBufferData    (GL_SHADER_STORAGE_BUFFER, sz, &buffer[0], _sfUsage.getValue());
                    osgGlBindBuffer    (GL_SHADER_STORAGE_BUFFER, 0);
                }

                glErr("ShaderStorageBufferObjChunk::handleGL initialize");
            }
            break;

        case Window::needrefresh:
            {
                OSGGETGLFUNCBYID_GL3_ES( glBindBuffer,
                                         osgGlBindBuffer,
                                        _funcBindBuffer, 
                                         pWin);

                OSGGETGLFUNCBYID_GL3_ES( glMapBuffer, 
                                         osgGlMapBuffer,
                                        _funcMapBuffer, 
                                         pWin);

                OSGGETGLFUNCBYID_GL3_ES( glUnmapBuffer, 
                                         osgGlUnmapBuffer,
                                        _funcUnmapBuffer, 
                                         pWin);

                osgGlBindBuffer(GL_SHADER_STORAGE_BUFFER, id);
                GLubyte* pBuffer = static_cast<GLubyte*>(
                                    osgGlMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_WRITE_ONLY_ARB));

                std::vector<GLubyte> buffer = createBuffer(pEnv);
                if (!buffer.empty())
                    memcpy(pBuffer, &buffer[0], sizeof(GLubyte) * buffer.size());
    
                osgGlUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
                osgGlBindBuffer (GL_SHADER_STORAGE_BUFFER, 0);

                glErr("ShaderStorageBufferObjChunk::handleGL needrefresh");
            }
            break;
        default:
            {
                SWARNING << "ShaderStorageBufferObjChunk(" << this << "::handleGL: Illegal mode: "
                         << mode << " for id " << id << std::endl;
            }
    }

    return 0;
}

/*! GL object handler
    destroy it
*/
void ShaderStorageBufferObjChunk::handleDestroyGL(DrawEnv                 *pEnv, 
                                                  UInt32                   osgid, 
                                                  Window::GLObjectStatusE  mode)
{
    Window *pWin = pEnv->getWindow();
    GLuint  id   = pWin->getGLObjectId(osgid);

    if(mode == Window::destroy)
    {
        OSGGETGLFUNCBYID_GL3_ES( glDeleteBuffers,
                                 osgGlDeleteBuffers,
                                _funcDeleteBuffers, 
                                 pWin);

        osgGlDeleteBuffers(1, &id);
        pWin->setGLObjectId(osgid, 0);

        glErr("ShaderStorageBufferObjChunk::handleDestroyGL");
    }
    else if(mode == Window::finaldestroy)
    {
        //SWARNING << "Last buffer user destroyed" << std::endl;
    }
    else
    {
        SWARNING << "ShaderStorageBufferObjChunk::handleDestroyGL: Illegal mode: "
             << mode << " for id " << id << std::endl;
    }

}

/*------------------------------ tools --------------------------------------*/

void ShaderStorageBufferObjChunk::validate(DrawEnv *pEnv)
{
    pEnv->getWindow()->validateGLObject(this->getGLId(),
                                        pEnv           );
}

Int32 ShaderStorageBufferObjChunk::getOpenGLId(DrawEnv *pEnv)
{
    return pEnv->getWindow()->getGLObjectId(this->getGLId());
}

/*------------------------------ activate -----------------------------------*/

void ShaderStorageBufferObjChunk::activate(DrawEnv *pEnv, UInt32 idx)
{
    Window *pWin = pEnv->getWindow();

    pWin->validateGLObject(getGLId(), pEnv);

    GLuint id = pWin->getGLObjectId(getGLId());

    OSGGETGLFUNCBYID_GL3_ES( glBindBuffer,
                             osgGlBindBuffer,
                            _funcBindBuffer, 
                             pWin);

    OSGGETGLFUNCBYID_GL3_ES( glBindBufferBase, 
                             osgGlBindBufferBase,
                            _funcBindBufferBase, 
                             pWin);

    osgGlBindBuffer    (GL_SHADER_STORAGE_BUFFER, id);
    osgGlBindBufferBase(GL_SHADER_STORAGE_BUFFER, idx, id);

    glErr("ShaderStorageBufferObjChunk::activate");
}

/*------------------------------ deactivate ---------------------------------*/

void ShaderStorageBufferObjChunk::deactivate(DrawEnv *pEnv, UInt32 idx)
{
    Window *pWin = pEnv->getWindow();

    OSGGETGLFUNCBYID_GL3_ES( glBindBuffer,
                             osgGlBindBuffer,
                            _funcBindBuffer, 
                             pWin);

    OSGGETGLFUNCBYID_GL3_ES( glBindBufferBase, 
                             osgGlBindBufferBase,
                            _funcBindBufferBase, 
                             pWin);

    osgGlBindBufferBase(GL_SHADER_STORAGE_BUFFER, idx, 0);
    osgGlBindBuffer    (GL_SHADER_STORAGE_BUFFER, 0);

    glErr("ShaderStorageBufferObjChunk::deactivate");
}

/*------------------------------ changeFrom ---------------------------------*/

void ShaderStorageBufferObjChunk::changeFrom(DrawEnv    *pEnv,
                                       StateChunk *old,
                                       UInt32      idx )
{
    // change from me to me?
    // this assumes I haven't changed in the meantime.
    // is that a valid assumption?
    if (old == this)
        return;

    old->deactivate(pEnv, idx);
    this->activate(pEnv, idx);
}

/*------------------------------ buffer -------------------------------------*/

std::vector<GLubyte> ShaderStorageBufferObjChunk::createBuffer(DrawEnv *pEnv)
{
    Window *pWin = pEnv->getWindow();

    OSGGETGLFUNCBYID_GL3_ES(   glGetProgramResourceIndex, 
                            osgGlGetProgramResourceIndex,
                            _funcGetProgramResourceIndex, 
                            pWin);

    OSGGETGLFUNCBYID_GL3_ES(   glGetProgramResourceiv, 
                            osgGlGetProgramResourceiv,
                            _funcGetProgramResourceiv, 
                            pWin);

    OSGGETGLFUNCBYID_GL3_ES(   glGetProgramResourceName, 
                            osgGlGetProgramResourceName,
                            _funcGetProgramResourceName, 
                            pWin);

    std::vector<GLubyte> buffer;

    GLuint index = osgGlGetProgramResourceIndex(pEnv->getActiveShader(), GL_SHADER_STORAGE_BLOCK, _sfBlockName.getValue().c_str());
    if (index == GL_INVALID_INDEX) {
        SWARNING << "ShaderStorageBufferObjChunk::createBuffer: Invalid block index" << std::endl;
        return buffer;
    }

    const GLenum       block_prop_query[2] = { GL_BUFFER_DATA_SIZE, GL_NUM_ACTIVE_VARIABLES };
    std::vector<GLint> block_prop_query_result(2);

    osgGlGetProgramResourceiv(pEnv->getActiveShader(), GL_SHADER_STORAGE_BLOCK, index, 2, block_prop_query, 2, NULL, &block_prop_query_result[0]);

    GLint size = block_prop_query_result[0];
    GLint num  = block_prop_query_result[1];

    std::vector<GLuint> indices(num);
    const GLenum indices_query[1] = { GL_ACTIVE_VARIABLES };

    osgGlGetProgramResourceiv(pEnv->getActiveShader(), GL_SHADER_STORAGE_BLOCK, index, 1, indices_query, num, NULL, reinterpret_cast<GLint*>(&indices[0]));

    for (std::size_t i = 0; i < indices.size(); ++i)
    {
        if (indices[i] == GL_INVALID_INDEX)
        {
            SWARNING << "ShaderStorageBufferObjChunk::createBuffer: Invalid index of active variables in block" << std::endl;
            return buffer;
        }
    }

    std::vector<GLint> offsets(num), 
                       array_sizes(num), 
                       array_strides(num), 
                       matrix_strides(num),
                       top_level_array_sizes(num),
                       top_level_array_strides(num),
                       name_lengths(num)
                       ;

    std::vector<std::string> names(num);
    std::vector<GLchar>      nameData(1024);

    typedef boost::unordered_map<std::string, std::size_t> MapNameToIdxT;
    MapNameToIdxT mapNameToIdx;

    for(int idx = 0; idx < num; ++idx)
    {
        const GLint num_queries = 7;
        const GLenum query[num_queries] = { 
            //GL_TYPE, 
            GL_OFFSET, 
            GL_ARRAY_SIZE, 
            GL_ARRAY_STRIDE, 
            GL_MATRIX_STRIDE,
            //GL_IS_ROW_MAJOR, 
            GL_TOP_LEVEL_ARRAY_SIZE, 
            GL_TOP_LEVEL_ARRAY_STRIDE,
            GL_NAME_LENGTH
        };
        GLint query_result[num_queries];
        osgGlGetProgramResourceiv(pEnv->getActiveShader(), GL_BUFFER_VARIABLE, indices[idx], num_queries, query, num_queries, NULL, query_result);

        offsets[idx]                 = query_result[0];
        array_sizes[idx]             = query_result[1];
        array_strides[idx]           = query_result[2];
        matrix_strides[idx]          = query_result[3];
        top_level_array_sizes[idx]   = query_result[4];
        top_level_array_strides[idx] = query_result[5];
        name_lengths[idx]            = query_result[6];

        nameData.resize(name_lengths[idx]);

        osgGlGetProgramResourceName(pEnv->getActiveShader(), GL_BUFFER_VARIABLE, indices[idx], GLsizei(nameData.size()), NULL, &nameData[0]);

        names[idx] = std::string(&nameData[0], nameData.size()-1);

        mapNameToIdx.insert(MapNameToIdxT::value_type(names[idx], idx));
    }

    buffer.resize(size);

    for (GLint i = 0; i < GLint(_mfIndex.size()); ++i)
    {
        UInt32              idx   =                               _mfIndex           [i];
        FundamentalTypes    fType = static_cast<FundamentalTypes>(_mfFundamentalTypes[i]);
        MainType            mType = static_cast<MainType>        (_mfMainTypes       [i]);
        UInt32              card  =                               _mfCardinality     [i];
        std::string         name  =                               _mfNames           [i];

        UInt8 columns = 0;
        UInt8 rows    = 0;

        switch (mType) {
            case SIMPLE_T:
                columns = 1;
                rows    = 1;
                break;
            case VEC2_T:
                columns = 1;
                rows    = 2;
                break;
            case VEC3_T:
                columns = 1;
                rows    = 3;
                break;
            case VEC4_T:
                columns = 1;
                rows    = 4;
                break;
            case MAT2_T:
                columns = 2;
                rows    = 2;
                break;
            case MAT3_T:
                columns = 3;
                rows    = 3;
                break;
            case MAT4_T:
                columns = 4;
                rows    = 4;
                break;
            case MAT2X3_T:
                columns = 2;
                rows    = 3;
                break;
            case MAT2X4_T:
                columns = 2;
                rows    = 4;
                break;
            case MAT3X4_T:
                columns = 3;
                rows    = 4;
                break;
            case MAT3X2_T:
                columns = 3;
                rows    = 2;
                break;
            case MAT4X2_T:
                columns = 4;
                rows    = 2;
                break;
            case MAT4X3_T:
                columns = 4;
                rows    = 3;
                break;
        }

        std::size_t resource_idx = 0;

        int top_level_idx = 0;

        //
        // Resource name lookup
        //
        MapNameToIdxT::const_iterator iter = mapNameToIdx.find(name);
        if (iter == mapNameToIdx.end())
        {
            if (card > 1)
            {
                iter = mapNameToIdx.find(name += "[0]");
            }
        }

        if (iter == mapNameToIdx.end())
        {
            bracket_expr_finder finder(top_level_idx);
            boost::algorithm::find_format(name, finder, boost::algorithm::const_formatter("[0]"));

            iter = mapNameToIdx.find(name);

            if (iter == mapNameToIdx.end())
            {
                if (card > 1)
                {
                    iter = mapNameToIdx.find(name += "[0]");
                }
            }
        }

        if (iter != mapNameToIdx.end())
        {
            resource_idx = iter->second;
        }
        else
        {
            SWARNING << "ShaderStorageBufferObjChunk::createBuffer: Invalid resource name found" << std::endl;
        }

        GLint top_level_array_size    = top_level_array_sizes[resource_idx];
        GLint top_level_array_stride  = top_level_array_strides[resource_idx];

        OSG_ASSERT(top_level_idx < top_level_array_size);

        GLint top_level_array_offset  = top_level_idx * top_level_array_stride;
        
        GLint offset                  = top_level_array_offset + offsets[resource_idx];
//        GLint array_size              = array_sizes[resource_idx];
        GLint array_stride            = array_strides[resource_idx];
        GLint matrix_stride           = matrix_strides[resource_idx];

        for (UInt32 j = 0; j < card; ++j)
        {
            GLint offset_ = offset;
            for (UInt8 k = 0; k < columns; ++k)
            {
                for (UInt8 l = 0; l < rows; ++l)
                {
                    UInt32 idx_ = idx + j * rows * columns + k * rows + l;
                    switch (fType) {
                        case FLOAT_T:
                            reinterpret_cast<Real32*>(&buffer[0] + offset)[l] = _mfFloatValues[idx_];
                            break;
                        case DOUBLE_T:
                            reinterpret_cast<Real64*>(&buffer[0] + offset)[l] = _mfDoubleValues[idx_];
                            break;
                        case INT_T:
                            reinterpret_cast<Int32*>(&buffer[0] + offset)[l] = _mfIntValues[idx_];
                            break;
                        case UINT_T:
                            reinterpret_cast<UInt32*>(&buffer[0] + offset)[l] = _mfUIntValues[idx_];
                            break;
                        case BOOL_T:
                            reinterpret_cast<Int32*>(&buffer[0] + offset)[l] = _mfBoolValues[idx_];
                            break;
                    }
                }
                offset += matrix_stride;
            }
            offset = offset_ + array_stride;
        }
    }

    return buffer;
}

/*------------------------------ add-interface ------------------------------*/

UInt32 ShaderStorageBufferObjChunk::addFloat(const std::string& name, UInt32 cardinality)
{
    editMField(FundamentalTypesFieldMask,   _mfFundamentalTypes);
    editMField(MainTypesFieldMask,          _mfMainTypes);
    editMField(CardinalityFieldMask,        _mfCardinality);
    editMField(IndexFieldMask,              _mfIndex);
    editMField(NamesFieldMask,              _mfNames);
    editMField(FloatValuesFieldMask,        _mfFloatValues);
    editSField(NameToIndexFieldMask);

    _mfFundamentalTypes.push_back(FLOAT_T);
    _mfMainTypes       .push_back(SIMPLE_T);
    _mfCardinality     .push_back(cardinality);
    _mfIndex           .push_back(static_cast<UInt32>(_mfFloatValues.size()));
    _mfNames           .push_back(name);

    UInt32 index = static_cast<UInt32>(_mfIndex.size()) - 1;

    _sfNameToIndex.getValue().insert(StringToUInt32Map::value_type(name, index));

    for (UInt32 i = 0; i < cardinality; ++i)
        _mfFloatValues.push_back(0.f);

    OSG_ASSERT(invariantOnStorageSize());

    return index;
}

UInt32 ShaderStorageBufferObjChunk::addDouble(const std::string& name, UInt32 cardinality)
{
    editMField(FundamentalTypesFieldMask,   _mfFundamentalTypes);
    editMField(MainTypesFieldMask,          _mfMainTypes);
    editMField(CardinalityFieldMask,        _mfCardinality);
    editMField(IndexFieldMask,              _mfIndex);
    editMField(NamesFieldMask,              _mfNames);
    editMField(DoubleValuesFieldMask,       _mfDoubleValues);
    editSField(NameToIndexFieldMask);

    _mfFundamentalTypes.push_back(DOUBLE_T);
    _mfMainTypes       .push_back(SIMPLE_T);
    _mfCardinality     .push_back(cardinality);
    _mfIndex           .push_back(static_cast<UInt32>(_mfDoubleValues.size()));
    _mfNames           .push_back(name);

    UInt32 index = static_cast<UInt32>(_mfIndex.size()) - 1;

    _sfNameToIndex.getValue().insert(StringToUInt32Map::value_type(name, index));

    for (UInt32 i = 0; i < cardinality; ++i)
        _mfDoubleValues.push_back(0.);

    OSG_ASSERT(invariantOnStorageSize());

    return index;
}

UInt32 ShaderStorageBufferObjChunk::addInt(const std::string& name, UInt32 cardinality)
{
    editMField(FundamentalTypesFieldMask,   _mfFundamentalTypes);
    editMField(MainTypesFieldMask,          _mfMainTypes);
    editMField(CardinalityFieldMask,        _mfCardinality);
    editMField(IndexFieldMask,              _mfIndex);
    editMField(NamesFieldMask,              _mfNames);
    editMField(IntValuesFieldMask,          _mfIntValues);
    editSField(NameToIndexFieldMask);

    _mfFundamentalTypes.push_back(INT_T);
    _mfMainTypes       .push_back(SIMPLE_T);
    _mfCardinality     .push_back(cardinality);
    _mfIndex           .push_back(static_cast<UInt32>(_mfIntValues.size()));
    _mfNames           .push_back(name);

    UInt32 index = static_cast<UInt32>(_mfIndex.size()) - 1;

    _sfNameToIndex.getValue().insert(StringToUInt32Map::value_type(name, index));

    for (UInt32 i = 0; i < cardinality; ++i)
        _mfIntValues.push_back(0);

    OSG_ASSERT(invariantOnStorageSize());

    return index;
}

UInt32 ShaderStorageBufferObjChunk::addUInt(const std::string& name, UInt32 cardinality)
{
    editMField(FundamentalTypesFieldMask,   _mfFundamentalTypes);
    editMField(MainTypesFieldMask,          _mfMainTypes);
    editMField(CardinalityFieldMask,        _mfCardinality);
    editMField(IndexFieldMask,              _mfIndex);
    editMField(NamesFieldMask,              _mfNames);
    editMField(UIntValuesFieldMask,         _mfUIntValues);
    editSField(NameToIndexFieldMask);

    _mfFundamentalTypes.push_back(UINT_T);
    _mfMainTypes       .push_back(SIMPLE_T);
    _mfCardinality     .push_back(cardinality);
    _mfIndex           .push_back(static_cast<UInt32>(_mfUIntValues.size()));
    _mfNames           .push_back(name);

    UInt32 index = static_cast<UInt32>(_mfIndex.size()) - 1;

    _sfNameToIndex.getValue().insert(StringToUInt32Map::value_type(name, index));

    for (UInt32 i = 0; i < cardinality; ++i)
        _mfUIntValues.push_back(0);

    OSG_ASSERT(invariantOnStorageSize());

    return index;
}

UInt32 ShaderStorageBufferObjChunk::addBool(const std::string& name, UInt32 cardinality)
{
    editMField(FundamentalTypesFieldMask,   _mfFundamentalTypes);
    editMField(MainTypesFieldMask,          _mfMainTypes);
    editMField(CardinalityFieldMask,        _mfCardinality);
    editMField(IndexFieldMask,              _mfIndex);
    editMField(NamesFieldMask,              _mfNames);
    editMField(BoolValuesFieldMask,         _mfBoolValues);
    editSField(NameToIndexFieldMask);

    _mfFundamentalTypes.push_back(BOOL_T);
    _mfMainTypes       .push_back(SIMPLE_T);
    _mfCardinality     .push_back(cardinality);
    _mfIndex           .push_back(static_cast<UInt32>(_mfBoolValues.size()));
    _mfNames           .push_back(name);

    UInt32 index = static_cast<UInt32>(_mfIndex.size()) - 1;

    _sfNameToIndex.getValue().insert(StringToUInt32Map::value_type(name, index));

    for (UInt32 i = 0; i < cardinality; ++i)
        _mfBoolValues.push_back(static_cast<UInt8>(false));

    OSG_ASSERT(invariantOnStorageSize());

    return index;
}

UInt32 ShaderStorageBufferObjChunk::addVec2(const std::string& name, UInt32 cardinality)
{
    editMField(FundamentalTypesFieldMask,   _mfFundamentalTypes);
    editMField(MainTypesFieldMask,          _mfMainTypes);
    editMField(CardinalityFieldMask,        _mfCardinality);
    editMField(IndexFieldMask,              _mfIndex);
    editMField(NamesFieldMask,              _mfNames);
    editMField(FloatValuesFieldMask,        _mfFloatValues);
    editSField(NameToIndexFieldMask);

    _mfFundamentalTypes.push_back(FLOAT_T);
    _mfMainTypes       .push_back(VEC2_T);
    _mfCardinality     .push_back(cardinality);
    _mfIndex           .push_back(static_cast<UInt32>(_mfFloatValues.size()));
    _mfNames           .push_back(name);

    UInt32 index = static_cast<UInt32>(_mfIndex.size()) - 1;

    _sfNameToIndex.getValue().insert(StringToUInt32Map::value_type(name, index));

    UInt8 rows = 2;

    for (UInt32 i = 0; i < cardinality; ++i)
        for (UInt8 j = 0; j < rows; ++j)
            _mfFloatValues.push_back(0.f);

    OSG_ASSERT(invariantOnStorageSize());

    return index;
}

UInt32 ShaderStorageBufferObjChunk::addVec3(const std::string& name, UInt32 cardinality)
{
    editMField(FundamentalTypesFieldMask,   _mfFundamentalTypes);
    editMField(MainTypesFieldMask,          _mfMainTypes);
    editMField(CardinalityFieldMask,        _mfCardinality);
    editMField(IndexFieldMask,              _mfIndex);
    editMField(NamesFieldMask,              _mfNames);
    editMField(FloatValuesFieldMask,        _mfFloatValues);
    editSField(NameToIndexFieldMask);

    _mfFundamentalTypes.push_back(FLOAT_T);
    _mfMainTypes       .push_back(VEC3_T);
    _mfCardinality     .push_back(cardinality);
    _mfIndex           .push_back(static_cast<UInt32>(_mfFloatValues.size()));
    _mfNames           .push_back(name);

    UInt32 index = static_cast<UInt32>(_mfIndex.size()) - 1;

    _sfNameToIndex.getValue().insert(StringToUInt32Map::value_type(name, index));

    UInt8 rows = 3;

    for (UInt32 i = 0; i < cardinality; ++i)
        for (UInt8 j = 0; j < rows; ++j)
            _mfFloatValues.push_back(0.f);

    OSG_ASSERT(invariantOnStorageSize());

    return index;
}

UInt32 ShaderStorageBufferObjChunk::addVec4(const std::string& name, UInt32 cardinality)
{
    editMField(FundamentalTypesFieldMask,   _mfFundamentalTypes);
    editMField(MainTypesFieldMask,          _mfMainTypes);
    editMField(CardinalityFieldMask,        _mfCardinality);
    editMField(IndexFieldMask,              _mfIndex);
    editMField(NamesFieldMask,              _mfNames);
    editMField(FloatValuesFieldMask,        _mfFloatValues);
    editSField(NameToIndexFieldMask);

    _mfFundamentalTypes.push_back(FLOAT_T);
    _mfMainTypes       .push_back(VEC4_T);
    _mfCardinality     .push_back(cardinality);
    _mfIndex           .push_back(static_cast<UInt32>(_mfFloatValues.size()));
    _mfNames           .push_back(name);

    UInt32 index = static_cast<UInt32>(_mfIndex.size()) - 1;

    _sfNameToIndex.getValue().insert(StringToUInt32Map::value_type(name, index));

    UInt8 rows = 4;

    for (UInt32 i = 0; i < cardinality; ++i)
        for (UInt8 j = 0; j < rows; ++j)
            _mfFloatValues.push_back(0.f);

    OSG_ASSERT(invariantOnStorageSize());

    return index;
}

UInt32 ShaderStorageBufferObjChunk::addDVec2(const std::string& name, UInt32 cardinality)
{
    editMField(FundamentalTypesFieldMask,   _mfFundamentalTypes);
    editMField(MainTypesFieldMask,          _mfMainTypes);
    editMField(CardinalityFieldMask,        _mfCardinality);
    editMField(IndexFieldMask,              _mfIndex);
    editMField(NamesFieldMask,              _mfNames);
    editMField(DoubleValuesFieldMask,       _mfDoubleValues);
    editSField(NameToIndexFieldMask);

    _mfFundamentalTypes.push_back(DOUBLE_T);
    _mfMainTypes       .push_back(VEC2_T);
    _mfCardinality     .push_back(cardinality);
    _mfIndex           .push_back(static_cast<UInt32>(_mfDoubleValues.size()));
    _mfNames           .push_back(name);

    UInt32 index = static_cast<UInt32>(_mfIndex.size()) - 1;

    _sfNameToIndex.getValue().insert(StringToUInt32Map::value_type(name, index));

    UInt8 rows = 2;

    for (UInt32 i = 0; i < cardinality; ++i)
        for (UInt8 j = 0; j < rows; ++j)
            _mfDoubleValues.push_back(0.);

    OSG_ASSERT(invariantOnStorageSize());

    return index;
}

UInt32 ShaderStorageBufferObjChunk::addDVec3(const std::string& name, UInt32 cardinality)
{
    editMField(FundamentalTypesFieldMask,   _mfFundamentalTypes);
    editMField(MainTypesFieldMask,          _mfMainTypes);
    editMField(CardinalityFieldMask,        _mfCardinality);
    editMField(IndexFieldMask,              _mfIndex);
    editMField(NamesFieldMask,              _mfNames);
    editMField(DoubleValuesFieldMask,       _mfDoubleValues);
    editSField(NameToIndexFieldMask);

    _mfFundamentalTypes.push_back(DOUBLE_T);
    _mfMainTypes       .push_back(VEC3_T);
    _mfCardinality     .push_back(cardinality);
    _mfIndex           .push_back(static_cast<UInt32>(_mfDoubleValues.size()));
    _mfNames           .push_back(name);

    UInt32 index = static_cast<UInt32>(_mfIndex.size()) - 1;

    _sfNameToIndex.getValue().insert(StringToUInt32Map::value_type(name, index));

    UInt8 rows = 3;

    for (UInt32 i = 0; i < cardinality; ++i)
        for (UInt8 j = 0; j < rows; ++j)
            _mfDoubleValues.push_back(0.);

    OSG_ASSERT(invariantOnStorageSize());

    return index;
}

UInt32 ShaderStorageBufferObjChunk::addDVec4(const std::string& name, UInt32 cardinality)
{
    editMField(FundamentalTypesFieldMask,   _mfFundamentalTypes);
    editMField(MainTypesFieldMask,          _mfMainTypes);
    editMField(CardinalityFieldMask,        _mfCardinality);
    editMField(IndexFieldMask,              _mfIndex);
    editMField(NamesFieldMask,              _mfNames);
    editMField(DoubleValuesFieldMask,       _mfDoubleValues);
    editSField(NameToIndexFieldMask);

    _mfFundamentalTypes.push_back(DOUBLE_T);
    _mfMainTypes       .push_back(VEC4_T);
    _mfCardinality     .push_back(cardinality);
    _mfIndex           .push_back(static_cast<UInt32>(_mfDoubleValues.size()));
    _mfNames           .push_back(name);

    UInt32 index = static_cast<UInt32>(_mfIndex.size()) - 1;

    _sfNameToIndex.getValue().insert(StringToUInt32Map::value_type(name, index));

    UInt8 rows = 4;

    for (UInt32 i = 0; i < cardinality; ++i)
        for (UInt8 j = 0; j < rows; ++j)
            _mfDoubleValues.push_back(0.);

    OSG_ASSERT(invariantOnStorageSize());

    return index;
}

UInt32 ShaderStorageBufferObjChunk::addIVec2(const std::string& name, UInt32 cardinality)
{
    editMField(FundamentalTypesFieldMask,   _mfFundamentalTypes);
    editMField(MainTypesFieldMask,          _mfMainTypes);
    editMField(CardinalityFieldMask,        _mfCardinality);
    editMField(IndexFieldMask,              _mfIndex);
    editMField(NamesFieldMask,              _mfNames);
    editMField(IntValuesFieldMask,          _mfIntValues);
    editSField(NameToIndexFieldMask);

    _mfFundamentalTypes.push_back(INT_T);
    _mfMainTypes       .push_back(VEC2_T);
    _mfCardinality     .push_back(cardinality);
    _mfIndex           .push_back(static_cast<UInt32>(_mfIntValues.size()));
    _mfNames           .push_back(name);

    UInt32 index = static_cast<UInt32>(_mfIndex.size()) - 1;

    _sfNameToIndex.getValue().insert(StringToUInt32Map::value_type(name, index));

    UInt8 rows = 2;

    for (UInt32 i = 0; i < cardinality; ++i)
        for (UInt8 j = 0; j < rows; ++j)
            _mfIntValues.push_back(0);

    OSG_ASSERT(invariantOnStorageSize());

    return index;
}

UInt32 ShaderStorageBufferObjChunk::addIVec3(const std::string& name, UInt32 cardinality)
{
    editMField(FundamentalTypesFieldMask,   _mfFundamentalTypes);
    editMField(MainTypesFieldMask,          _mfMainTypes);
    editMField(CardinalityFieldMask,        _mfCardinality);
    editMField(IndexFieldMask,              _mfIndex);
    editMField(NamesFieldMask,              _mfNames);
    editMField(IntValuesFieldMask,          _mfIntValues);
    editSField(NameToIndexFieldMask);

    _mfFundamentalTypes.push_back(INT_T);
    _mfMainTypes       .push_back(VEC3_T);
    _mfCardinality     .push_back(cardinality);
    _mfIndex           .push_back(static_cast<UInt32>(_mfIntValues.size()));
    _mfNames           .push_back(name);

    UInt32 index = static_cast<UInt32>(_mfIndex.size()) - 1;

    _sfNameToIndex.getValue().insert(StringToUInt32Map::value_type(name, index));

    UInt8 rows = 3;

    for (UInt32 i = 0; i < cardinality; ++i)
        for (UInt8 j = 0; j < rows; ++j)
            _mfIntValues.push_back(0);

    OSG_ASSERT(invariantOnStorageSize());

    return index;
}

UInt32 ShaderStorageBufferObjChunk::addIVec4(const std::string& name, UInt32 cardinality)
{
    editMField(FundamentalTypesFieldMask,   _mfFundamentalTypes);
    editMField(MainTypesFieldMask,          _mfMainTypes);
    editMField(CardinalityFieldMask,        _mfCardinality);
    editMField(IndexFieldMask,              _mfIndex);
    editMField(NamesFieldMask,              _mfNames);
    editMField(IntValuesFieldMask,          _mfIntValues);
    editSField(NameToIndexFieldMask);

    _mfFundamentalTypes.push_back(INT_T);
    _mfMainTypes       .push_back(VEC4_T);
    _mfCardinality     .push_back(cardinality);
    _mfIndex           .push_back(static_cast<UInt32>(_mfIntValues.size()));
    _mfNames           .push_back(name);

    UInt32 index = static_cast<UInt32>(_mfIndex.size()) - 1;

    _sfNameToIndex.getValue().insert(StringToUInt32Map::value_type(name, index));

    UInt8 rows = 4;

    for (UInt32 i = 0; i < cardinality; ++i)
        for (UInt8 j = 0; j < rows; ++j)
            _mfIntValues.push_back(0);

    OSG_ASSERT(invariantOnStorageSize());

    return index;
}

UInt32 ShaderStorageBufferObjChunk::addUVec2(const std::string& name, UInt32 cardinality)
{
    editMField(FundamentalTypesFieldMask,   _mfFundamentalTypes);
    editMField(MainTypesFieldMask,          _mfMainTypes);
    editMField(CardinalityFieldMask,        _mfCardinality);
    editMField(IndexFieldMask,              _mfIndex);
    editMField(NamesFieldMask,              _mfNames);
    editMField(UIntValuesFieldMask,         _mfUIntValues);
    editSField(NameToIndexFieldMask);

    _mfFundamentalTypes.push_back(UINT_T);
    _mfMainTypes       .push_back(VEC2_T);
    _mfCardinality     .push_back(cardinality);
    _mfIndex           .push_back(static_cast<UInt32>(_mfUIntValues.size()));
    _mfNames           .push_back(name);

    UInt32 index = static_cast<UInt32>(_mfIndex.size()) - 1;

    _sfNameToIndex.getValue().insert(StringToUInt32Map::value_type(name, index));

    UInt8 rows = 2;

    for (UInt32 i = 0; i < cardinality; ++i)
        for (UInt8 j = 0; j < rows; ++j)
            _mfUIntValues.push_back(0);

    OSG_ASSERT(invariantOnStorageSize());

    return index;
}

UInt32 ShaderStorageBufferObjChunk::addUVec3(const std::string& name, UInt32 cardinality)
{
    editMField(FundamentalTypesFieldMask,   _mfFundamentalTypes);
    editMField(MainTypesFieldMask,          _mfMainTypes);
    editMField(CardinalityFieldMask,        _mfCardinality);
    editMField(IndexFieldMask,              _mfIndex);
    editMField(NamesFieldMask,              _mfNames);
    editMField(UIntValuesFieldMask,         _mfUIntValues);
    editSField(NameToIndexFieldMask);

    _mfFundamentalTypes.push_back(UINT_T);
    _mfMainTypes       .push_back(VEC3_T);
    _mfCardinality     .push_back(cardinality);
    _mfIndex           .push_back(static_cast<UInt32>(_mfUIntValues.size()));
    _mfNames           .push_back(name);

    UInt32 index = static_cast<UInt32>(_mfIndex.size()) - 1;

    _sfNameToIndex.getValue().insert(StringToUInt32Map::value_type(name, index));

    UInt8 rows = 3;

    for (UInt32 i = 0; i < cardinality; ++i)
        for (UInt8 j = 0; j < rows; ++j)
            _mfUIntValues.push_back(0);

    OSG_ASSERT(invariantOnStorageSize());

    return index;
}

UInt32 ShaderStorageBufferObjChunk::addUVec4(const std::string& name, UInt32 cardinality)
{
    editMField(FundamentalTypesFieldMask,   _mfFundamentalTypes);
    editMField(MainTypesFieldMask,          _mfMainTypes);
    editMField(CardinalityFieldMask,        _mfCardinality);
    editMField(IndexFieldMask,              _mfIndex);
    editMField(NamesFieldMask,              _mfNames);
    editMField(UIntValuesFieldMask,         _mfUIntValues);
    editSField(NameToIndexFieldMask);

    _mfFundamentalTypes.push_back(UINT_T);
    _mfMainTypes       .push_back(VEC4_T);
    _mfCardinality     .push_back(cardinality);
    _mfIndex           .push_back(static_cast<UInt32>(_mfUIntValues.size()));
    _mfNames           .push_back(name);

    UInt32 index = static_cast<UInt32>(_mfIndex.size()) - 1;

    _sfNameToIndex.getValue().insert(StringToUInt32Map::value_type(name, index));

    UInt8 rows = 4;

    for (UInt32 i = 0; i < cardinality; ++i)
        for (UInt8 j = 0; j < rows; ++j)
            _mfUIntValues.push_back(0);

    OSG_ASSERT(invariantOnStorageSize());

    return index;
}

UInt32 ShaderStorageBufferObjChunk::addBVec2(const std::string& name, UInt32 cardinality)
{
    editMField(FundamentalTypesFieldMask,   _mfFundamentalTypes);
    editMField(MainTypesFieldMask,          _mfMainTypes);
    editMField(CardinalityFieldMask,        _mfCardinality);
    editMField(IndexFieldMask,              _mfIndex);
    editMField(NamesFieldMask,              _mfNames);
    editMField(BoolValuesFieldMask,         _mfBoolValues);
    editSField(NameToIndexFieldMask);

    _mfFundamentalTypes.push_back(BOOL_T);
    _mfMainTypes       .push_back(VEC2_T);
    _mfCardinality     .push_back(cardinality);
    _mfIndex           .push_back(static_cast<UInt32>(_mfBoolValues.size()));
    _mfNames           .push_back(name);

    UInt32 index = static_cast<UInt32>(_mfIndex.size()) - 1;

    _sfNameToIndex.getValue().insert(StringToUInt32Map::value_type(name, index));

    UInt8 rows = 2;

    for (UInt32 i = 0; i < cardinality; ++i)
        for (UInt8 j = 0; j < rows; ++j)
            _mfBoolValues.push_back(static_cast<UInt8>(false));

    OSG_ASSERT(invariantOnStorageSize());

    return index;
}

UInt32 ShaderStorageBufferObjChunk::addBVec3(const std::string& name, UInt32 cardinality)
{
    editMField(FundamentalTypesFieldMask,   _mfFundamentalTypes);
    editMField(MainTypesFieldMask,          _mfMainTypes);
    editMField(CardinalityFieldMask,        _mfCardinality);
    editMField(IndexFieldMask,              _mfIndex);
    editMField(NamesFieldMask,              _mfNames);
    editMField(BoolValuesFieldMask,         _mfBoolValues);
    editSField(NameToIndexFieldMask);

    _mfFundamentalTypes.push_back(BOOL_T);
    _mfMainTypes       .push_back(VEC3_T);
    _mfCardinality     .push_back(cardinality);
    _mfIndex           .push_back(static_cast<UInt32>(_mfBoolValues.size()));
    _mfNames           .push_back(name);

    UInt32 index = static_cast<UInt32>(_mfIndex.size()) - 1;

    _sfNameToIndex.getValue().insert(StringToUInt32Map::value_type(name, index));

    UInt8 rows = 3;

    for (UInt32 i = 0; i < cardinality; ++i)
        for (UInt8 j = 0; j < rows; ++j)
            _mfBoolValues.push_back(static_cast<UInt8>(false));

    OSG_ASSERT(invariantOnStorageSize());

    return index;
}

UInt32 ShaderStorageBufferObjChunk::addBVec4(const std::string& name, UInt32 cardinality)
{
    editMField(FundamentalTypesFieldMask,   _mfFundamentalTypes);
    editMField(MainTypesFieldMask,          _mfMainTypes);
    editMField(CardinalityFieldMask,        _mfCardinality);
    editMField(IndexFieldMask,              _mfIndex);
    editMField(NamesFieldMask,              _mfNames);
    editMField(BoolValuesFieldMask,         _mfBoolValues);
    editSField(NameToIndexFieldMask);

    _mfFundamentalTypes.push_back(BOOL_T);
    _mfMainTypes       .push_back(VEC4_T);
    _mfCardinality     .push_back(cardinality);
    _mfIndex           .push_back(static_cast<UInt32>(_mfBoolValues.size()));
    _mfNames           .push_back(name);

    UInt32 index = static_cast<UInt32>(_mfIndex.size()) - 1;

    _sfNameToIndex.getValue().insert(StringToUInt32Map::value_type(name, index));

    UInt8 rows = 4;

    for (UInt32 i = 0; i < cardinality; ++i)
        for (UInt8 j = 0; j < rows; ++j)
            _mfBoolValues.push_back(static_cast<UInt8>(false));

    OSG_ASSERT(invariantOnStorageSize());

    return index;
}

UInt32 ShaderStorageBufferObjChunk::addMat2(const std::string& name, UInt32 cardinality)
{
    editMField(FundamentalTypesFieldMask,   _mfFundamentalTypes);
    editMField(MainTypesFieldMask,          _mfMainTypes);
    editMField(CardinalityFieldMask,        _mfCardinality);
    editMField(IndexFieldMask,              _mfIndex);
    editMField(NamesFieldMask,              _mfNames);
    editMField(FloatValuesFieldMask,        _mfFloatValues);
    editSField(NameToIndexFieldMask);

    _mfFundamentalTypes.push_back(FLOAT_T);
    _mfMainTypes       .push_back(MAT2_T);
    _mfCardinality     .push_back(cardinality);
    _mfIndex           .push_back(static_cast<UInt32>(_mfFloatValues.size()));
    _mfNames           .push_back(name);

    UInt32 index = static_cast<UInt32>(_mfIndex.size()) - 1;

    _sfNameToIndex.getValue().insert(StringToUInt32Map::value_type(name, index));

    UInt8 columns = 2;
    UInt8 rows    = 2;

    for (UInt32 i = 0; i < cardinality; ++i)
        for (UInt8 j = 0; j < columns; ++j)
            for (UInt8 k = 0; k < rows; ++k)
                _mfFloatValues.push_back(0.f);

    OSG_ASSERT(invariantOnStorageSize());

    return index;
}

UInt32 ShaderStorageBufferObjChunk::addMat3(const std::string& name, UInt32 cardinality)
{
    editMField(FundamentalTypesFieldMask,   _mfFundamentalTypes);
    editMField(MainTypesFieldMask,          _mfMainTypes);
    editMField(CardinalityFieldMask,        _mfCardinality);
    editMField(IndexFieldMask,              _mfIndex);
    editMField(NamesFieldMask,              _mfNames);
    editMField(FloatValuesFieldMask,        _mfFloatValues);
    editSField(NameToIndexFieldMask);

    _mfFundamentalTypes.push_back(FLOAT_T);
    _mfMainTypes       .push_back(MAT3_T);
    _mfCardinality     .push_back(cardinality);
    _mfIndex           .push_back(static_cast<UInt32>(_mfFloatValues.size()));
    _mfNames           .push_back(name);

    UInt32 index = static_cast<UInt32>(_mfIndex.size()) - 1;

    _sfNameToIndex.getValue().insert(StringToUInt32Map::value_type(name, index));

    UInt8 columns = 3;
    UInt8 rows    = 3;

    for (UInt32 i = 0; i < cardinality; ++i)
        for (UInt8 j = 0; j < columns; ++j)
            for (UInt8 k = 0; k < rows; ++k)
                _mfFloatValues.push_back(0.f);

    OSG_ASSERT(invariantOnStorageSize());

    return index;
}

UInt32 ShaderStorageBufferObjChunk::addMat4(const std::string& name, UInt32 cardinality)
{
    editMField(FundamentalTypesFieldMask,   _mfFundamentalTypes);
    editMField(MainTypesFieldMask,          _mfMainTypes);
    editMField(CardinalityFieldMask,        _mfCardinality);
    editMField(IndexFieldMask,              _mfIndex);
    editMField(NamesFieldMask,              _mfNames);
    editMField(FloatValuesFieldMask,        _mfFloatValues);
    editSField(NameToIndexFieldMask);

    _mfFundamentalTypes.push_back(FLOAT_T);
    _mfMainTypes       .push_back(MAT4_T);
    _mfCardinality     .push_back(cardinality);
    _mfIndex           .push_back(static_cast<UInt32>(_mfFloatValues.size()));
    _mfNames           .push_back(name);

    UInt32 index = static_cast<UInt32>(_mfIndex.size()) - 1;

    _sfNameToIndex.getValue().insert(StringToUInt32Map::value_type(name, index));

    UInt8 columns = 4;
    UInt8 rows    = 4;

    for (UInt32 i = 0; i < cardinality; ++i)
        for (UInt8 j = 0; j < columns; ++j)
            for (UInt8 k = 0; k < rows; ++k)
                _mfFloatValues.push_back(0.f);

    OSG_ASSERT(invariantOnStorageSize());

    return index;
}

UInt32 ShaderStorageBufferObjChunk::addDMat2(const std::string& name, UInt32 cardinality)
{
    editMField(FundamentalTypesFieldMask,   _mfFundamentalTypes);
    editMField(MainTypesFieldMask,          _mfMainTypes);
    editMField(CardinalityFieldMask,        _mfCardinality);
    editMField(IndexFieldMask,              _mfIndex);
    editMField(NamesFieldMask,              _mfNames);
    editMField(DoubleValuesFieldMask,       _mfDoubleValues);
    editSField(NameToIndexFieldMask);

    _mfFundamentalTypes.push_back(DOUBLE_T);
    _mfMainTypes       .push_back(MAT2_T);
    _mfCardinality     .push_back(cardinality);
    _mfIndex           .push_back(static_cast<UInt32>(_mfDoubleValues.size()));
    _mfNames           .push_back(name);

    UInt32 index = static_cast<UInt32>(_mfIndex.size()) - 1;

    _sfNameToIndex.getValue().insert(StringToUInt32Map::value_type(name, index));

    UInt8 columns = 2;
    UInt8 rows    = 2;

    for (UInt32 i = 0; i < cardinality; ++i)
        for (UInt8 j = 0; j < columns; ++j)
            for (UInt8 k = 0; k < rows; ++k)
                _mfDoubleValues.push_back(0.f);

    OSG_ASSERT(invariantOnStorageSize());

    return index;
}

UInt32 ShaderStorageBufferObjChunk::addDMat3(const std::string& name, UInt32 cardinality)
{
    editMField(FundamentalTypesFieldMask,   _mfFundamentalTypes);
    editMField(MainTypesFieldMask,          _mfMainTypes);
    editMField(CardinalityFieldMask,        _mfCardinality);
    editMField(IndexFieldMask,              _mfIndex);
    editMField(NamesFieldMask,              _mfNames);
    editMField(DoubleValuesFieldMask,       _mfDoubleValues);
    editSField(NameToIndexFieldMask);

    _mfFundamentalTypes.push_back(DOUBLE_T);
    _mfMainTypes       .push_back(MAT3_T);
    _mfCardinality     .push_back(cardinality);
    _mfIndex           .push_back(static_cast<UInt32>(_mfDoubleValues.size()));
    _mfNames           .push_back(name);

    UInt32 index = static_cast<UInt32>(_mfIndex.size()) - 1;

    _sfNameToIndex.getValue().insert(StringToUInt32Map::value_type(name, index));

    UInt8 columns = 3;
    UInt8 rows    = 3;

    for (UInt32 i = 0; i < cardinality; ++i)
        for (UInt8 j = 0; j < columns; ++j)
            for (UInt8 k = 0; k < rows; ++k)
                _mfDoubleValues.push_back(0.f);

    OSG_ASSERT(invariantOnStorageSize());

    return index;
}

UInt32 ShaderStorageBufferObjChunk::addDMat4(const std::string& name, UInt32 cardinality)
{
    editMField(FundamentalTypesFieldMask,   _mfFundamentalTypes);
    editMField(MainTypesFieldMask,          _mfMainTypes);
    editMField(CardinalityFieldMask,        _mfCardinality);
    editMField(IndexFieldMask,              _mfIndex);
    editMField(NamesFieldMask,              _mfNames);
    editMField(DoubleValuesFieldMask,       _mfDoubleValues);
    editSField(NameToIndexFieldMask);

    _mfFundamentalTypes.push_back(DOUBLE_T);
    _mfMainTypes       .push_back(MAT4_T);
    _mfCardinality     .push_back(cardinality);
    _mfIndex           .push_back(static_cast<UInt32>(_mfDoubleValues.size()));
    _mfNames           .push_back(name);

    UInt32 index = static_cast<UInt32>(_mfIndex.size()) - 1;

    _sfNameToIndex.getValue().insert(StringToUInt32Map::value_type(name, index));

    UInt8 columns = 4;
    UInt8 rows    = 4;

    for (UInt32 i = 0; i < cardinality; ++i)
        for (UInt8 j = 0; j < columns; ++j)
            for (UInt8 k = 0; k < rows; ++k)
                _mfDoubleValues.push_back(0.f);

    OSG_ASSERT(invariantOnStorageSize());

    return index;
}

UInt32 ShaderStorageBufferObjChunk::addMat2x3(const std::string& name, UInt32 cardinality)
{
    editMField(FundamentalTypesFieldMask,   _mfFundamentalTypes);
    editMField(MainTypesFieldMask,          _mfMainTypes);
    editMField(CardinalityFieldMask,        _mfCardinality);
    editMField(IndexFieldMask,              _mfIndex);
    editMField(NamesFieldMask,              _mfNames);
    editMField(FloatValuesFieldMask,        _mfFloatValues);
    editSField(NameToIndexFieldMask);

    _mfFundamentalTypes.push_back(FLOAT_T);
    _mfMainTypes       .push_back(MAT2X3_T);
    _mfCardinality     .push_back(cardinality);
    _mfIndex           .push_back(static_cast<UInt32>(_mfFloatValues.size()));
    _mfNames           .push_back(name);

    UInt32 index = static_cast<UInt32>(_mfIndex.size()) - 1;

    _sfNameToIndex.getValue().insert(StringToUInt32Map::value_type(name, index));

    UInt8 columns = 2;
    UInt8 rows    = 3;

    for (UInt32 i = 0; i < cardinality; ++i)
        for (UInt8 j = 0; j < columns; ++j)
            for (UInt8 k = 0; k < rows; ++k)
                _mfFloatValues.push_back(0.f);

    OSG_ASSERT(invariantOnStorageSize());

    return index;
}

UInt32 ShaderStorageBufferObjChunk::addMat3x2(const std::string& name, UInt32 cardinality)
{
    editMField(FundamentalTypesFieldMask,   _mfFundamentalTypes);
    editMField(MainTypesFieldMask,          _mfMainTypes);
    editMField(CardinalityFieldMask,        _mfCardinality);
    editMField(IndexFieldMask,              _mfIndex);
    editMField(NamesFieldMask,              _mfNames);
    editMField(FloatValuesFieldMask,        _mfFloatValues);
    editSField(NameToIndexFieldMask);

    _mfFundamentalTypes.push_back(FLOAT_T);
    _mfMainTypes       .push_back(MAT3X2_T);
    _mfCardinality     .push_back(cardinality);
    _mfIndex           .push_back(static_cast<UInt32>(_mfFloatValues.size()));
    _mfNames           .push_back(name);

    UInt32 index = static_cast<UInt32>(_mfIndex.size()) - 1;

    _sfNameToIndex.getValue().insert(StringToUInt32Map::value_type(name, index));

    UInt8 columns = 3;
    UInt8 rows    = 2;

    for (UInt32 i = 0; i < cardinality; ++i)
        for (UInt8 j = 0; j < columns; ++j)
            for (UInt8 k = 0; k < rows; ++k)
                _mfFloatValues.push_back(0.f);
    OSG_ASSERT(invariantOnStorageSize());

    return index;
}

UInt32 ShaderStorageBufferObjChunk::addMat2x4(const std::string& name, UInt32 cardinality)
{
    editMField(FundamentalTypesFieldMask,   _mfFundamentalTypes);
    editMField(MainTypesFieldMask,          _mfMainTypes);
    editMField(CardinalityFieldMask,        _mfCardinality);
    editMField(IndexFieldMask,              _mfIndex);
    editMField(NamesFieldMask,              _mfNames);
    editMField(FloatValuesFieldMask,        _mfFloatValues);
    editSField(NameToIndexFieldMask);

    _mfFundamentalTypes.push_back(FLOAT_T);
    _mfMainTypes       .push_back(MAT2X4_T);
    _mfCardinality     .push_back(cardinality);
    _mfIndex           .push_back(static_cast<UInt32>(_mfFloatValues.size()));
    _mfNames           .push_back(name);

    UInt32 index = static_cast<UInt32>(_mfIndex.size()) - 1;

    _sfNameToIndex.getValue().insert(StringToUInt32Map::value_type(name, index));

    UInt8 columns = 2;
    UInt8 rows    = 4;

    for (UInt32 i = 0; i < cardinality; ++i)
        for (UInt8 j = 0; j < columns; ++j)
            for (UInt8 k = 0; k < rows; ++k)
                _mfFloatValues.push_back(0.f);

    OSG_ASSERT(invariantOnStorageSize());

    return index;
}

UInt32 ShaderStorageBufferObjChunk::addMat4x2(const std::string& name, UInt32 cardinality)
{
    editMField(FundamentalTypesFieldMask,   _mfFundamentalTypes);
    editMField(MainTypesFieldMask,          _mfMainTypes);
    editMField(CardinalityFieldMask,        _mfCardinality);
    editMField(IndexFieldMask,              _mfIndex);
    editMField(NamesFieldMask,              _mfNames);
    editMField(FloatValuesFieldMask,        _mfFloatValues);
    editSField(NameToIndexFieldMask);

    _mfFundamentalTypes.push_back(FLOAT_T);
    _mfMainTypes       .push_back(MAT4X2_T);
    _mfCardinality     .push_back(cardinality);
    _mfIndex           .push_back(static_cast<UInt32>(_mfFloatValues.size()));
    _mfNames           .push_back(name);

    UInt32 index = static_cast<UInt32>(_mfIndex.size()) - 1;

    _sfNameToIndex.getValue().insert(StringToUInt32Map::value_type(name, index));

    UInt8 columns = 4;
    UInt8 rows    = 2;

    for (UInt32 i = 0; i < cardinality; ++i)
        for (UInt8 j = 0; j < columns; ++j)
            for (UInt8 k = 0; k < rows; ++k)
                _mfFloatValues.push_back(0.f);

    OSG_ASSERT(invariantOnStorageSize());

    return index;
}

UInt32 ShaderStorageBufferObjChunk::addMat3x4(const std::string& name, UInt32 cardinality)
{
    editMField(FundamentalTypesFieldMask,   _mfFundamentalTypes);
    editMField(MainTypesFieldMask,          _mfMainTypes);
    editMField(CardinalityFieldMask,        _mfCardinality);
    editMField(IndexFieldMask,              _mfIndex);
    editMField(NamesFieldMask,              _mfNames);
    editMField(FloatValuesFieldMask,        _mfFloatValues);
    editSField(NameToIndexFieldMask);

    _mfFundamentalTypes.push_back(FLOAT_T);
    _mfMainTypes       .push_back(MAT3X4_T);
    _mfCardinality     .push_back(cardinality);
    _mfIndex           .push_back(static_cast<UInt32>(_mfFloatValues.size()));
    _mfNames           .push_back(name);

    UInt32 index = static_cast<UInt32>(_mfIndex.size()) - 1;

    _sfNameToIndex.getValue().insert(StringToUInt32Map::value_type(name, index));

    UInt8 columns = 3;
    UInt8 rows    = 4;

    for (UInt32 i = 0; i < cardinality; ++i)
        for (UInt8 j = 0; j < columns; ++j)
            for (UInt8 k = 0; k < rows; ++k)
                _mfFloatValues.push_back(0.f);

    OSG_ASSERT(invariantOnStorageSize());

    return index;
}

UInt32 ShaderStorageBufferObjChunk::addMat4x3(const std::string& name, UInt32 cardinality)
{
    editMField(FundamentalTypesFieldMask,   _mfFundamentalTypes);
    editMField(MainTypesFieldMask,          _mfMainTypes);
    editMField(CardinalityFieldMask,        _mfCardinality);
    editMField(IndexFieldMask,              _mfIndex);
    editMField(NamesFieldMask,              _mfNames);
    editMField(FloatValuesFieldMask,        _mfFloatValues);
    editSField(NameToIndexFieldMask);

    _mfFundamentalTypes.push_back(FLOAT_T);
    _mfMainTypes       .push_back(MAT4X3_T);
    _mfCardinality     .push_back(cardinality);
    _mfIndex           .push_back(static_cast<UInt32>(_mfFloatValues.size()));
    _mfNames           .push_back(name);

    UInt32 index = static_cast<UInt32>(_mfIndex.size()) - 1;

    _sfNameToIndex.getValue().insert(StringToUInt32Map::value_type(name, index));

    UInt8 columns = 4;
    UInt8 rows    = 3;

    for (UInt32 i = 0; i < cardinality; ++i)
        for (UInt8 j = 0; j < columns; ++j)
            for (UInt8 k = 0; k < rows; ++k)
                _mfFloatValues.push_back(0.f);

    OSG_ASSERT(invariantOnStorageSize());

    return index;
}

UInt32 ShaderStorageBufferObjChunk::addDMat2x3(const std::string& name, UInt32 cardinality)
{
    editMField(FundamentalTypesFieldMask,   _mfFundamentalTypes);
    editMField(MainTypesFieldMask,          _mfMainTypes);
    editMField(CardinalityFieldMask,        _mfCardinality);
    editMField(IndexFieldMask,              _mfIndex);
    editMField(NamesFieldMask,              _mfNames);
    editMField(DoubleValuesFieldMask,       _mfDoubleValues);
    editSField(NameToIndexFieldMask);

    _mfFundamentalTypes.push_back(DOUBLE_T);
    _mfMainTypes       .push_back(MAT2X3_T);
    _mfCardinality     .push_back(cardinality);
    _mfIndex           .push_back(static_cast<UInt32>(_mfDoubleValues.size()));
    _mfNames           .push_back(name);

    UInt32 index = static_cast<UInt32>(_mfIndex.size()) - 1;

    _sfNameToIndex.getValue().insert(StringToUInt32Map::value_type(name, index));

    UInt8 columns = 2;
    UInt8 rows    = 3;

    for (UInt32 i = 0; i < cardinality; ++i)
        for (UInt8 j = 0; j < columns; ++j)
            for (UInt8 k = 0; k < rows; ++k)
                _mfDoubleValues.push_back(0.f);

    OSG_ASSERT(invariantOnStorageSize());

    return index;
}

UInt32 ShaderStorageBufferObjChunk::addDMat3x2(const std::string& name, UInt32 cardinality)
{
    editMField(FundamentalTypesFieldMask,   _mfFundamentalTypes);
    editMField(MainTypesFieldMask,          _mfMainTypes);
    editMField(CardinalityFieldMask,        _mfCardinality);
    editMField(IndexFieldMask,              _mfIndex);
    editMField(NamesFieldMask,              _mfNames);
    editMField(DoubleValuesFieldMask,       _mfDoubleValues);
    editSField(NameToIndexFieldMask);

    _mfFundamentalTypes.push_back(DOUBLE_T);
    _mfMainTypes       .push_back(MAT3X2_T);
    _mfCardinality     .push_back(cardinality);
    _mfIndex           .push_back(static_cast<UInt32>(_mfDoubleValues.size()));
    _mfNames           .push_back(name);

    UInt32 index = static_cast<UInt32>(_mfIndex.size()) - 1;

    _sfNameToIndex.getValue().insert(StringToUInt32Map::value_type(name, index));

    UInt8 columns = 3;
    UInt8 rows    = 2;

    for (UInt32 i = 0; i < cardinality; ++i)
        for (UInt8 j = 0; j < columns; ++j)
            for (UInt8 k = 0; k < rows; ++k)
                _mfDoubleValues.push_back(0.f);

    OSG_ASSERT(invariantOnStorageSize());

    return index;
}

UInt32 ShaderStorageBufferObjChunk::addDMat2x4(const std::string& name, UInt32 cardinality)
{
    editMField(FundamentalTypesFieldMask,   _mfFundamentalTypes);
    editMField(MainTypesFieldMask,          _mfMainTypes);
    editMField(CardinalityFieldMask,        _mfCardinality);
    editMField(IndexFieldMask,              _mfIndex);
    editMField(NamesFieldMask,              _mfNames);
    editMField(DoubleValuesFieldMask,       _mfDoubleValues);
    editSField(NameToIndexFieldMask);

    _mfFundamentalTypes.push_back(DOUBLE_T);
    _mfMainTypes       .push_back(MAT2X4_T);
    _mfCardinality     .push_back(cardinality);
    _mfIndex           .push_back(static_cast<UInt32>(_mfDoubleValues.size()));
    _mfNames           .push_back(name);

    UInt32 index = static_cast<UInt32>(_mfIndex.size()) - 1;

    _sfNameToIndex.getValue().insert(StringToUInt32Map::value_type(name, index));

    UInt8 columns = 2;
    UInt8 rows    = 4;

    for (UInt32 i = 0; i < cardinality; ++i)
        for (UInt8 j = 0; j < columns; ++j)
            for (UInt8 k = 0; k < rows; ++k)
                _mfDoubleValues.push_back(0.f);

    OSG_ASSERT(invariantOnStorageSize());

    return index;
}

UInt32 ShaderStorageBufferObjChunk::addDMat4x2(const std::string& name, UInt32 cardinality)
{
    editMField(FundamentalTypesFieldMask,   _mfFundamentalTypes);
    editMField(MainTypesFieldMask,          _mfMainTypes);
    editMField(CardinalityFieldMask,        _mfCardinality);
    editMField(IndexFieldMask,              _mfIndex);
    editMField(NamesFieldMask,              _mfNames);
    editMField(DoubleValuesFieldMask,       _mfDoubleValues);
    editSField(NameToIndexFieldMask);

    _mfFundamentalTypes.push_back(DOUBLE_T);
    _mfMainTypes       .push_back(MAT4X2_T);
    _mfCardinality     .push_back(cardinality);
    _mfIndex           .push_back(static_cast<UInt32>(_mfDoubleValues.size()));
    _mfNames           .push_back(name);

    UInt32 index = static_cast<UInt32>(_mfIndex.size()) - 1;

    _sfNameToIndex.getValue().insert(StringToUInt32Map::value_type(name, index));

    UInt8 columns = 4;
    UInt8 rows    = 2;

    for (UInt32 i = 0; i < cardinality; ++i)
        for (UInt8 j = 0; j < columns; ++j)
            for (UInt8 k = 0; k < rows; ++k)
                _mfDoubleValues.push_back(0.f);

    OSG_ASSERT(invariantOnStorageSize());

    return index;
}

UInt32 ShaderStorageBufferObjChunk::addDMat3x4(const std::string& name, UInt32 cardinality)
{
    editMField(FundamentalTypesFieldMask,   _mfFundamentalTypes);
    editMField(MainTypesFieldMask,          _mfMainTypes);
    editMField(CardinalityFieldMask,        _mfCardinality);
    editMField(IndexFieldMask,              _mfIndex);
    editMField(NamesFieldMask,              _mfNames);
    editMField(DoubleValuesFieldMask,       _mfDoubleValues);
    editSField(NameToIndexFieldMask);

    _mfFundamentalTypes.push_back(DOUBLE_T);
    _mfMainTypes       .push_back(MAT3X4_T);
    _mfCardinality     .push_back(cardinality);
    _mfIndex           .push_back(static_cast<UInt32>(_mfDoubleValues.size()));
    _mfNames           .push_back(name);

    UInt32 index = static_cast<UInt32>(_mfIndex.size()) - 1;

    _sfNameToIndex.getValue().insert(StringToUInt32Map::value_type(name, index));

    UInt8 columns = 3;
    UInt8 rows    = 4;

    for (UInt32 i = 0; i < cardinality; ++i)
        for (UInt8 j = 0; j < columns; ++j)
            for (UInt8 k = 0; k < rows; ++k)
                _mfDoubleValues.push_back(0.f);

    OSG_ASSERT(invariantOnStorageSize());

    return index;
}

UInt32 ShaderStorageBufferObjChunk::addDMat4x3(const std::string& name, UInt32 cardinality)
{
    editMField(FundamentalTypesFieldMask,   _mfFundamentalTypes);
    editMField(MainTypesFieldMask,          _mfMainTypes);
    editMField(CardinalityFieldMask,        _mfCardinality);
    editMField(IndexFieldMask,              _mfIndex);
    editMField(NamesFieldMask,              _mfNames);
    editMField(DoubleValuesFieldMask,       _mfDoubleValues);
    editSField(NameToIndexFieldMask);

    _mfFundamentalTypes.push_back(DOUBLE_T);
    _mfMainTypes       .push_back(MAT4X3_T);
    _mfCardinality     .push_back(cardinality);
    _mfIndex           .push_back(static_cast<UInt32>(_mfDoubleValues.size()));
    _mfNames           .push_back(name);

    UInt32 index = static_cast<UInt32>(_mfIndex.size()) - 1;

    _sfNameToIndex.getValue().insert(StringToUInt32Map::value_type(name, index));

    UInt8 columns = 4;
    UInt8 rows    = 3;

    for (UInt32 i = 0; i < cardinality; ++i)
        for (UInt8 j = 0; j < columns; ++j)
            for (UInt8 k = 0; k < rows; ++k)
                _mfDoubleValues.push_back(0.f);

    OSG_ASSERT(invariantOnStorageSize());

    return index;
}

/*------------------------------ set-interface I ----------------------------*/

void ShaderStorageBufferObjChunk::setFloat(UInt32 handle, Real32 value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(FloatValuesFieldMask, _mfFloatValues);
    _mfFloatValues[_mfIndex[handle] + array_idx] = value;
}

void ShaderStorageBufferObjChunk::setDouble(UInt32 handle, Real64 value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(DoubleValuesFieldMask, _mfDoubleValues);
    _mfDoubleValues[_mfIndex[handle] + array_idx] = value;
}

void ShaderStorageBufferObjChunk::setInt(UInt32 handle, Int32 value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(IntValuesFieldMask, _mfIntValues);
    _mfIntValues[_mfIndex[handle] + array_idx] = value;
}

void ShaderStorageBufferObjChunk::setUInt(UInt32 handle, UInt32 value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(UIntValuesFieldMask, _mfUIntValues);
    _mfUIntValues[_mfIndex[handle] + array_idx] = value;
}

void ShaderStorageBufferObjChunk::setBool(UInt32 handle, bool value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(BoolValuesFieldMask, _mfBoolValues);
    _mfBoolValues[_mfIndex[handle] + array_idx] = static_cast<UInt8>(value);
}

void ShaderStorageBufferObjChunk::setVec2(UInt32 handle, const Vec2f& value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(FloatValuesFieldMask, _mfFloatValues);

    int size = 2;
    for (int i = 0; i < size; ++i)
        _mfFloatValues[_mfIndex[handle] + (array_idx * size) + i] = value[i];
}

void ShaderStorageBufferObjChunk::setVec2(UInt32 handle, const Pnt2f& value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(FloatValuesFieldMask, _mfFloatValues);

    int size = 2;
    for (int i = 0; i < size; ++i)
        _mfFloatValues[_mfIndex[handle] + (array_idx * size) + i] = value[i];
}

void ShaderStorageBufferObjChunk::setVec3(UInt32 handle, const Vec3f& value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(FloatValuesFieldMask, _mfFloatValues);
    
    int size = 3;
    for (int i = 0; i < size; ++i)
        _mfFloatValues[_mfIndex[handle] + (array_idx * size) + i] = value[i];
}

void ShaderStorageBufferObjChunk::setVec3(UInt32 handle, const Pnt3f& value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(FloatValuesFieldMask, _mfFloatValues);
    
    int size = 3;
    for (int i = 0; i < size; ++i)
        _mfFloatValues[_mfIndex[handle] + (array_idx * size) + i] = value[i];
}

void ShaderStorageBufferObjChunk::setVec3(UInt32 handle, const Color3f& value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(FloatValuesFieldMask, _mfFloatValues);
    
    int size = 3;
    for (int i = 0; i < size; ++i)
        _mfFloatValues[_mfIndex[handle] + (array_idx * size) + i] = value[i];
}

void ShaderStorageBufferObjChunk::setVec4(UInt32 handle, const Vec4f& value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(FloatValuesFieldMask, _mfFloatValues);

    int size = 4;
    for (int i = 0; i < size; ++i)
        _mfFloatValues[_mfIndex[handle] + (array_idx * size) + i] = value[i];
}

void ShaderStorageBufferObjChunk::setVec4(UInt32 handle, const Pnt4f& value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(FloatValuesFieldMask, _mfFloatValues);

    int size = 4;
    for (int i = 0; i < size; ++i)
        _mfFloatValues[_mfIndex[handle] + (array_idx * size) + i] = value[i];
}

void ShaderStorageBufferObjChunk::setVec4(UInt32 handle, const Color4f& value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(FloatValuesFieldMask, _mfFloatValues);

    int size = 4;
    for (int i = 0; i < size; ++i)
        _mfFloatValues[_mfIndex[handle] + (array_idx * size) + i] = value[i];
}

void ShaderStorageBufferObjChunk::setDVec2(UInt32 handle, const Vec2d& value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(DoubleValuesFieldMask, _mfDoubleValues);

    int size = 2;
    for (int i = 0; i < size; ++i)
        _mfDoubleValues[_mfIndex[handle] + (array_idx * size) + i] = value[i];
}

void ShaderStorageBufferObjChunk::setDVec2(UInt32 handle, const Pnt2d& value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(DoubleValuesFieldMask, _mfDoubleValues);

    int size = 2;
    for (int i = 0; i < size; ++i)
        _mfDoubleValues[_mfIndex[handle] + (array_idx * size) + i] = value[i];
}

void ShaderStorageBufferObjChunk::setDVec3(UInt32 handle, const Vec3d& value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(DoubleValuesFieldMask, _mfDoubleValues);

    int size = 3;
    for (int i = 0; i < size; ++i)
        _mfDoubleValues[_mfIndex[handle] + (array_idx * size) + i] = value[i];
}

void ShaderStorageBufferObjChunk::setDVec3(UInt32 handle, const Pnt3d& value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(DoubleValuesFieldMask, _mfDoubleValues);

    int size = 3;
    for (int i = 0; i < size; ++i)
        _mfDoubleValues[_mfIndex[handle] + (array_idx * size) + i] = value[i];
}

void ShaderStorageBufferObjChunk::setDVec4(UInt32 handle, const Vec4d& value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(DoubleValuesFieldMask, _mfDoubleValues);

    int size = 4;
    for (int i = 0; i < size; ++i)
        _mfDoubleValues[_mfIndex[handle] + (array_idx * size) + i] = value[i];
}

void ShaderStorageBufferObjChunk::setDVec4(UInt32 handle, const Pnt4d& value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(DoubleValuesFieldMask, _mfDoubleValues);

    int size = 4;
    for (int i = 0; i < size; ++i)
        _mfDoubleValues[_mfIndex[handle] + (array_idx * size) + i] = value[i];
}

void ShaderStorageBufferObjChunk::setIVec2(UInt32 handle, const Vec2i& value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(IntValuesFieldMask, _mfIntValues);

    int size = 2;
    for (int i = 0; i < size; ++i)
        _mfIntValues[_mfIndex[handle] + (array_idx * size) + i] = value[i];
}

void ShaderStorageBufferObjChunk::setIVec2(UInt32 handle, const Pnt2i& value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(IntValuesFieldMask, _mfIntValues);

    int size = 2;
    for (int i = 0; i < size; ++i)
        _mfIntValues[_mfIndex[handle] + (array_idx * size) + i] = value[i];
}

void ShaderStorageBufferObjChunk::setIVec3(UInt32 handle, const Vec3i& value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(IntValuesFieldMask, _mfIntValues);

    int size = 3;
    for (int i = 0; i < size; ++i)
        _mfIntValues[_mfIndex[handle] + (array_idx * size) + i] = value[i];
}
/*
void ShaderStorageBufferObjChunk::setIVec3(UInt32 handle, const Pnt3i& value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(IntValuesFieldMask, _mfIntValues);

    int size = 3;
    for (int i = 0; i < size; ++i)
        _mfIntValues[_mfIndex[handle] + (array_idx * size) + i] = value[i];
}
*/
void ShaderStorageBufferObjChunk::setIVec4(UInt32 handle, const Vec4i& value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(IntValuesFieldMask, _mfIntValues);

    int size = 4;
    for (int i = 0; i < size; ++i)
        _mfIntValues[_mfIndex[handle] + (array_idx * size) + i] = value[i];
}
/*
void ShaderStorageBufferObjChunk::setIVec4(UInt32 handle, const Pnt4i& value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(IntValuesFieldMask, _mfIntValues);

    int size = 4;
    for (int i = 0; i < size; ++i)
        _mfIntValues[_mfIndex[handle] + (array_idx * size) + i] = value[i];
}
*/
void ShaderStorageBufferObjChunk::setUVec2(UInt32 handle, const Vec2u& value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(UIntValuesFieldMask, _mfUIntValues);

    int size = 2;
    for (int i = 0; i < size; ++i)
        _mfUIntValues[_mfIndex[handle] + (array_idx * size) + i] = value[i];
}
/*
void ShaderStorageBufferObjChunk::setUVec2(UInt32 handle, const Pnt2u& value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(UIntValuesFieldMask, _mfUIntValues);

    int size = 2;
    for (int i = 0; i < size; ++i)
        _mfUIntValues[_mfIndex[handle] + (array_idx * size) + i] = value[i];
}
*/
void ShaderStorageBufferObjChunk::setUVec3(UInt32 handle, const Vec3u& value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(UIntValuesFieldMask, _mfUIntValues);

    int size = 3;
    for (int i = 0; i < size; ++i)
        _mfUIntValues[_mfIndex[handle] + (array_idx * size) + i] = value[i];
}
/*
void ShaderStorageBufferObjChunk::setUVec3(UInt32 handle, const Pnt3u& value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(UIntValuesFieldMask, _mfUIntValues);

    int size = 3;
    for (int i = 0; i < size; ++i)
        _mfUIntValues[_mfIndex[handle] + (array_idx * size) + i] = value[i];
}
*/
void ShaderStorageBufferObjChunk::setUVec4(UInt32 handle, const Vec4u& value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(UIntValuesFieldMask, _mfUIntValues);

    int size = 4;
    for (int i = 0; i < size; ++i)
        _mfUIntValues[_mfIndex[handle] + (array_idx * size) + i] = value[i];
}
/*
void ShaderStorageBufferObjChunk::setUVec4(UInt32 handle, const Pnt4u& value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(UIntValuesFieldMask, _mfUIntValues);

    int size = 4;
    for (int i = 0; i < size; ++i)
        _mfUIntValues[_mfIndex[handle] + (array_idx * size) + i] = value[i];
}
*/
void ShaderStorageBufferObjChunk::setBVec2(UInt32 handle, const Vec2b& value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(BoolValuesFieldMask, _mfBoolValues);

    int size = 2;
    for (int i = 0; i < size; ++i)
        _mfBoolValues[_mfIndex[handle] + (array_idx * size) + i] = static_cast<UInt8>(value[i]);
}

void ShaderStorageBufferObjChunk::setBVec2(UInt32 handle, const Pnt2b& value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(BoolValuesFieldMask, _mfBoolValues);

    int size = 2;
    for (int i = 0; i < size; ++i)
        _mfBoolValues[_mfIndex[handle] + (array_idx * size) + i] = static_cast<UInt8>(value[i]);
}

void ShaderStorageBufferObjChunk::setBVec3(UInt32 handle, const Vec3b& value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(BoolValuesFieldMask, _mfBoolValues);

    int size = 3;
    for (int i = 0; i < size; ++i)
        _mfBoolValues[_mfIndex[handle] + (array_idx * size) + i] = static_cast<UInt8>(value[i]);
}

void ShaderStorageBufferObjChunk::setBVec3(UInt32 handle, const Pnt3b& value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(BoolValuesFieldMask, _mfBoolValues);

    int size = 3;
    for (int i = 0; i < size; ++i)
        _mfBoolValues[_mfIndex[handle] + (array_idx * size) + i] = static_cast<UInt8>(value[i]);
}

void ShaderStorageBufferObjChunk::setBVec4(UInt32 handle, const Vec4b& value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(BoolValuesFieldMask, _mfBoolValues);

    int size = 4;
    for (int i = 0; i < size; ++i)
        _mfBoolValues[_mfIndex[handle] + (array_idx * size) + i] = static_cast<UInt8>(value[i]);
}

void ShaderStorageBufferObjChunk::setBVec4(UInt32 handle, const Pnt4b& value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(BoolValuesFieldMask, _mfBoolValues);

    int size = 4;
    for (int i = 0; i < size; ++i)
        _mfBoolValues[_mfIndex[handle] + (array_idx * size) + i] = static_cast<UInt8>(value[i]);
}

void ShaderStorageBufferObjChunk::setMat2(UInt32 handle, const Matrix4f& value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(FloatValuesFieldMask, _mfFloatValues);

    UInt8 columns = 2;
    UInt8 rows    = 2;

    for (int i = 0; i < columns; ++i) {
        const Vec4f& v = value[i];
        for (int j = 0; j < rows; ++j) {
            _mfFloatValues[_mfIndex[handle] + (array_idx * rows * columns) + (j + rows * i)] = v[j];
        }
    }
}

void ShaderStorageBufferObjChunk::setMat3(UInt32 handle, const Matrix4f& value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(FloatValuesFieldMask, _mfFloatValues);

    UInt8 columns = 3;
    UInt8 rows    = 3;

    for (int i = 0; i < columns; ++i) {
        const Vec4f& v = value[i];
        for (int j = 0; j < rows; ++j) {
            _mfFloatValues[_mfIndex[handle] + (array_idx * rows * columns) + (j + rows * i)] = v[j];
        }
    }
}

void ShaderStorageBufferObjChunk::setMat4(UInt32 handle, const Matrix4f& value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(FloatValuesFieldMask, _mfFloatValues);

    UInt8 columns = 4;
    UInt8 rows    = 4;

    for (int i = 0; i < columns; ++i) {
        const Vec4f& v = value[i];
        for (int j = 0; j < rows; ++j) {
            _mfFloatValues[_mfIndex[handle] + (array_idx * rows * columns) + (j + rows * i)] = v[j];
        }
    }
}

void ShaderStorageBufferObjChunk::setDMat2(UInt32 handle, const Matrix4d& value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(DoubleValuesFieldMask, _mfDoubleValues);

    UInt8 columns = 2;
    UInt8 rows    = 2;

    for (int i = 0; i < columns; ++i) {
        const Vec4d& v = value[i];
        for (int j = 0; j < rows; ++j) {
            _mfDoubleValues[_mfIndex[handle] + (array_idx * rows * columns) + (j + rows * i)] = v[j];
        }
    }
}

void ShaderStorageBufferObjChunk::setDMat3(UInt32 handle, const Matrix4d& value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(DoubleValuesFieldMask, _mfDoubleValues);

    UInt8 columns = 3;
    UInt8 rows    = 3;

    for (int i = 0; i < columns; ++i) {
        const Vec4d& v = value[i];
        for (int j = 0; j < rows; ++j) {
            _mfDoubleValues[_mfIndex[handle] + (array_idx * rows * columns) + (j + rows * i)] = v[j];
        }
    }
}

void ShaderStorageBufferObjChunk::setDMat4(UInt32 handle, const Matrix4d& value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(DoubleValuesFieldMask, _mfDoubleValues);

    UInt8 columns = 4;
    UInt8 rows    = 4;

    for (int i = 0; i < columns; ++i) {
        const Vec4d& v = value[i];
        for (int j = 0; j < rows; ++j) {
            _mfDoubleValues[_mfIndex[handle] + (array_idx * rows * columns) + (j + rows * i)] = v[j];
        }
    }
}

void ShaderStorageBufferObjChunk::setMat2x3(UInt32 handle, const Matrix4f& value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(FloatValuesFieldMask, _mfFloatValues);

    UInt8 columns = 2;
    UInt8 rows    = 3;

    for (int i = 0; i < columns; ++i) {
        const Vec4f& v = value[i];
        for (int j = 0; j < rows; ++j) {
            _mfFloatValues[_mfIndex[handle] + (array_idx * rows * columns) + (j + rows * i)] = v[j];
        }
    }
}

void ShaderStorageBufferObjChunk::setMat3x2(UInt32 handle, const Matrix4f& value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(FloatValuesFieldMask, _mfFloatValues);

    UInt8 columns = 3;
    UInt8 rows    = 2;

    for (int i = 0; i < columns; ++i) {
        const Vec4f& v = value[i];
        for (int j = 0; j < rows; ++j) {
            _mfFloatValues[_mfIndex[handle] + (array_idx * rows * columns) + (j + rows * i)] = v[j];
        }
    }
}

void ShaderStorageBufferObjChunk::setMat2x4(UInt32 handle, const Matrix4f& value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(FloatValuesFieldMask, _mfFloatValues);

    UInt8 columns = 2;
    UInt8 rows    = 4;

    for (int i = 0; i < columns; ++i) {
        const Vec4f& v = value[i];
        for (int j = 0; j < rows; ++j) {
            _mfFloatValues[_mfIndex[handle] + (array_idx * rows * columns) + (j + rows * i)] = v[j];
        }
    }
}

void ShaderStorageBufferObjChunk::setMat4x2(UInt32 handle, const Matrix4f& value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(FloatValuesFieldMask, _mfFloatValues);

    UInt8 columns = 4;
    UInt8 rows    = 2;
    
    for (int i = 0; i < columns; ++i) {
        const Vec4f& v = value[i];
        for (int j = 0; j < rows; ++j) {
            _mfFloatValues[_mfIndex[handle] + (array_idx * rows * columns) + (j + rows * i)] = v[j];
        }
    }
}

void ShaderStorageBufferObjChunk::setMat3x4(UInt32 handle, const Matrix4f& value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(FloatValuesFieldMask, _mfFloatValues);

    UInt8 columns = 3;
    UInt8 rows    = 4;

    for (int i = 0; i < columns; ++i) {
        const Vec4f& v = value[i];
        for (int j = 0; j < rows; ++j) {
            _mfFloatValues[_mfIndex[handle] + (array_idx * rows * columns) + (j + rows * i)] = v[j];
        }
    }
}

void ShaderStorageBufferObjChunk::setMat4x3(UInt32 handle, const Matrix4f& value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(FloatValuesFieldMask, _mfFloatValues);

    UInt8 columns = 4;
    UInt8 rows    = 3;

    for (int i = 0; i < columns; ++i) {
        const Vec4f& v = value[i];
        for (int j = 0; j < rows; ++j) {
            _mfFloatValues[_mfIndex[handle] + (array_idx * rows * columns) + (j + rows * i)] = v[j];
        }
    }
}

void ShaderStorageBufferObjChunk::setDMat2x3(UInt32 handle, const Matrix4d& value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(DoubleValuesFieldMask, _mfDoubleValues);

    UInt8 columns = 2;
    UInt8 rows    = 3;

    for (int i = 0; i < columns; ++i) {
        const Vec4d& v = value[i];
        for (int j = 0; j < rows; ++j) {
            _mfDoubleValues[_mfIndex[handle] + (array_idx * rows * columns) + (j + rows * i)] = v[j];
        }
    }
}

void ShaderStorageBufferObjChunk::setDMat3x2(UInt32 handle, const Matrix4d& value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(DoubleValuesFieldMask, _mfDoubleValues);

    UInt8 columns = 3;
    UInt8 rows    = 2;

    for (int i = 0; i < columns; ++i) {
        const Vec4d& v = value[i];
        for (int j = 0; j < rows; ++j) {
            _mfDoubleValues[_mfIndex[handle] + (array_idx * rows * columns) + (j + rows * i)] = v[j];
        }
    }
}

void ShaderStorageBufferObjChunk::setDMat2x4(UInt32 handle, const Matrix4d& value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(DoubleValuesFieldMask, _mfDoubleValues);

    UInt8 columns = 2;
    UInt8 rows    = 4;

    for (int i = 0; i < columns; ++i) {
        const Vec4d& v = value[i];
        for (int j = 0; j < rows; ++j) {
            _mfDoubleValues[_mfIndex[handle] + (array_idx * rows * columns) + (j + rows * i)] = v[j];
        }
    }
}

void ShaderStorageBufferObjChunk::setDMat4x2(UInt32 handle, const Matrix4d& value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(DoubleValuesFieldMask, _mfDoubleValues);

    UInt8 columns = 4;
    UInt8 rows    = 2;

    for (int i = 0; i < columns; ++i) {
        const Vec4d& v = value[i];
        for (int j = 0; j < rows; ++j) {
            _mfDoubleValues[_mfIndex[handle] + (array_idx * rows * columns) + (j + rows * i)] = v[j];
        }
    }
}

void ShaderStorageBufferObjChunk::setDMat3x4(UInt32 handle, const Matrix4d& value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(DoubleValuesFieldMask, _mfDoubleValues);

    UInt8 columns = 3;
    UInt8 rows    = 4;

    for (int i = 0; i < columns; ++i) {
        const Vec4d& v = value[i];
        for (int j = 0; j < rows; ++j) {
            _mfDoubleValues[_mfIndex[handle] + (array_idx * rows * columns) + (j + rows * i)] = v[j];
        }
    }
}

void ShaderStorageBufferObjChunk::setDMat4x3(UInt32 handle, const Matrix4d& value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(DoubleValuesFieldMask, _mfDoubleValues);

    UInt8 columns = 4;
    UInt8 rows    = 3;

    for (int i = 0; i < columns; ++i) {
        const Vec4d& v = value[i];
        for (int j = 0; j < rows; ++j) {
            _mfDoubleValues[_mfIndex[handle] + (array_idx * rows * columns) + (j + rows * i)] = v[j];
        }
    }
}

/*------------------------------ set-interface II ---------------------------*/

void ShaderStorageBufferObjChunk::setFloat(const std::string& name, Real32 value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setFloat(iter->second, value, array_idx);
}

void ShaderStorageBufferObjChunk::setDouble(const std::string& name, Real64 value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setDouble(iter->second, value, array_idx);
}

void ShaderStorageBufferObjChunk::setInt(const std::string& name, Int32 value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setInt(iter->second, value, array_idx);
}

void ShaderStorageBufferObjChunk::setUInt(const std::string& name, UInt32 value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setUInt(iter->second, value, array_idx);
}

void ShaderStorageBufferObjChunk::setBool(const std::string& name, bool value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setBool(iter->second, value, array_idx);
}

void ShaderStorageBufferObjChunk::setVec2(const std::string& name, const Vec2f& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setVec2(iter->second, value, array_idx);
}

void ShaderStorageBufferObjChunk::setVec2(const std::string& name, const Pnt2f& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setVec2(iter->second, value, array_idx);
}

void ShaderStorageBufferObjChunk::setVec3(const std::string& name, const Vec3f& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setVec3(iter->second, value, array_idx);
}

void ShaderStorageBufferObjChunk::setVec3(const std::string& name, const Pnt3f& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setVec3(iter->second, value, array_idx);
}

void ShaderStorageBufferObjChunk::setVec3(const std::string& name, const Color3f& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setVec3(iter->second, value, array_idx);
}

void ShaderStorageBufferObjChunk::setVec4(const std::string& name, const Vec4f& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setVec4(iter->second, value, array_idx);
}

void ShaderStorageBufferObjChunk::setVec4(const std::string& name, const Pnt4f& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setVec4(iter->second, value, array_idx);
}

void ShaderStorageBufferObjChunk::setVec4(const std::string& name, const Color4f& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setVec4(iter->second, value, array_idx);
}

void ShaderStorageBufferObjChunk::setDVec2(const std::string& name, const Vec2d& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setDVec2(iter->second, value, array_idx);
}

void ShaderStorageBufferObjChunk::setDVec2(const std::string& name, const Pnt2d& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setDVec2(iter->second, value, array_idx);
}

void ShaderStorageBufferObjChunk::setDVec3(const std::string& name, const Vec3d& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setDVec3(iter->second, value, array_idx);
}

void ShaderStorageBufferObjChunk::setDVec3(const std::string& name, const Pnt3d& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setDVec3(iter->second, value, array_idx);
}

void ShaderStorageBufferObjChunk::setDVec4(const std::string& name, const Vec4d& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setDVec4(iter->second, value, array_idx);
}

void ShaderStorageBufferObjChunk::setDVec4(const std::string& name, const Pnt4d& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setDVec4(iter->second, value, array_idx);
}

void ShaderStorageBufferObjChunk::setIVec2(const std::string& name, const Vec2i& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setIVec2(iter->second, value, array_idx);
}

void ShaderStorageBufferObjChunk::setIVec2(const std::string& name, const Pnt2i& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setIVec2(iter->second, value, array_idx);
}

void ShaderStorageBufferObjChunk::setIVec3(const std::string& name, const Vec3i& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setIVec3(iter->second, value, array_idx);
}
/*
void ShaderStorageBufferObjChunk::setIVec3(const std::string& name, const Pnt3i& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setIVec3(iter->second, value, array_idx);
}
*/
void ShaderStorageBufferObjChunk::setIVec4(const std::string& name, const Vec4i& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setIVec4(iter->second, value, array_idx);
}
/*
void ShaderStorageBufferObjChunk::setIVec4(const std::string& name, const Pnt4i& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setIVec4(iter->second, value, array_idx);
}
*/
void ShaderStorageBufferObjChunk::setUVec2(const std::string& name, const Vec2u& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setUVec2(iter->second, value, array_idx);
}
/*
void ShaderStorageBufferObjChunk::setUVec2(const std::string& name, const Pnt2u& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setUVec2(iter->second, value, array_idx);
}
*/
void ShaderStorageBufferObjChunk::setUVec3(const std::string& name, const Vec3u& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setUVec3(iter->second, value, array_idx);
}
/*
void ShaderStorageBufferObjChunk::setUVec3(const std::string& name, const Pnt3u& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setUVec3(iter->second, value, array_idx);
}
*/
void ShaderStorageBufferObjChunk::setUVec4(const std::string& name, const Vec4u& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setUVec4(iter->second, value, array_idx);
}
/*
void ShaderStorageBufferObjChunk::setUVec4(const std::string& name, const Pnt4u& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setUVec4(iter->second, value, array_idx);
}
*/
void ShaderStorageBufferObjChunk::setBVec2(const std::string& name, const Vec2b& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setBVec2(iter->second, value, array_idx);
}

void ShaderStorageBufferObjChunk::setBVec2(const std::string& name, const Pnt2b& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setBVec2(iter->second, value, array_idx);
}

void ShaderStorageBufferObjChunk::setBVec3(const std::string& name, const Vec3b& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setBVec3(iter->second, value, array_idx);
}

void ShaderStorageBufferObjChunk::setBVec3(const std::string& name, const Pnt3b& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setBVec3(iter->second, value, array_idx);
}

void ShaderStorageBufferObjChunk::setBVec4(const std::string& name, const Vec4b& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setBVec4(iter->second, value, array_idx);
}

void ShaderStorageBufferObjChunk::setBVec4(const std::string& name, const Pnt4b& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setBVec4(iter->second, value, array_idx);
}

void ShaderStorageBufferObjChunk::setMat2(const std::string& name, const Matrix4f& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setMat2(iter->second, value, array_idx);
}

void ShaderStorageBufferObjChunk::setMat3(const std::string& name, const Matrix4f& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setMat3(iter->second, value, array_idx);
}

void ShaderStorageBufferObjChunk::setMat4(const std::string& name, const Matrix4f& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setMat4(iter->second, value, array_idx);
}

void ShaderStorageBufferObjChunk::setDMat2(const std::string& name, const Matrix4d& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setDMat2(iter->second, value, array_idx);
}

void ShaderStorageBufferObjChunk::setDMat3(const std::string& name, const Matrix4d& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setDMat3(iter->second, value, array_idx);
}

void ShaderStorageBufferObjChunk::setDMat4(const std::string& name, const Matrix4d& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setDMat4(iter->second, value, array_idx);
}

void ShaderStorageBufferObjChunk::setMat2x3(const std::string& name, const Matrix4f& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setMat2x3(iter->second, value, array_idx);
}

void ShaderStorageBufferObjChunk::setMat3x2(const std::string& name, const Matrix4f& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setMat3x2(iter->second, value, array_idx);
}

void ShaderStorageBufferObjChunk::setMat2x4(const std::string& name, const Matrix4f& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setMat2x4(iter->second, value, array_idx);
}

void ShaderStorageBufferObjChunk::setMat4x2(const std::string& name, const Matrix4f& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setMat4x2(iter->second, value, array_idx);
}

void ShaderStorageBufferObjChunk::setMat3x4(const std::string& name, const Matrix4f& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setMat3x4(iter->second, value, array_idx);
}

void ShaderStorageBufferObjChunk::setMat4x3(const std::string& name, const Matrix4f& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setMat4x3(iter->second, value, array_idx);
}

void ShaderStorageBufferObjChunk::setDMat2x3(const std::string& name, const Matrix4d& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setDMat2x3(iter->second, value, array_idx);
}

void ShaderStorageBufferObjChunk::setDMat3x2(const std::string& name, const Matrix4d& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setDMat3x2(iter->second, value, array_idx);
}

void ShaderStorageBufferObjChunk::setDMat2x4(const std::string& name, const Matrix4d& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setDMat2x4(iter->second, value, array_idx);
}

void ShaderStorageBufferObjChunk::setDMat4x2(const std::string& name, const Matrix4d& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setDMat4x2(iter->second, value, array_idx);
}

void ShaderStorageBufferObjChunk::setDMat3x4(const std::string& name, const Matrix4d& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setDMat3x4(iter->second, value, array_idx);
}

void ShaderStorageBufferObjChunk::setDMat4x3(const std::string& name, const Matrix4d& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setDMat4x3(iter->second, value, array_idx);
}

/*------------------------------ Invariants ---------------------------------*/

bool ShaderStorageBufferObjChunk::invariantOnStorageSize()
{
    std::size_t sz = _mfFundamentalTypes.size();
    if (sz != _mfMainTypes  .size() || 
        sz != _mfCardinality.size() ||
        sz != _mfIndex      .size() ||
        sz != _mfNames      .size() ||
        sz != _sfNameToIndex.getValue().size()
        ) return false;
    return true;
}

OSG_END_NAMESPACE
