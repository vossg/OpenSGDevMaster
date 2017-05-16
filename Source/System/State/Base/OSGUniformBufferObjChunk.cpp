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

#include "OSGConfig.h"

#include "OSGGL.h"
#include "OSGGLU.h"
#include "OSGGLEXT.h"
#include "OSGWindow.h"

#include "OSGGLFuncProtos.h"

#include "OSGDrawEnv.h"

#include "OSGUniformBufferObjChunk.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGUniformBufferObjChunkBase.cpp file.
// To modify it, please change the .fcd file (OSGUniformBufferObjChunk.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

typedef OSG::Window Win;

UInt32 UniformBufferObjChunk::_extUniformBufferObject      = Win::invalidExtensionID;
UInt32 UniformBufferObjChunk::_extVertexBufferObject       = Win::invalidExtensionID;

UInt32 UniformBufferObjChunk::_funcBindBuffer              = Win::invalidFunctionID;
UInt32 UniformBufferObjChunk::_funcMapBuffer               = Win::invalidFunctionID;
UInt32 UniformBufferObjChunk::_funcUnmapBuffer             = Win::invalidFunctionID;
UInt32 UniformBufferObjChunk::_funcBufferData              = Win::invalidFunctionID;
UInt32 UniformBufferObjChunk::_funcBufferSubData           = Win::invalidFunctionID;
UInt32 UniformBufferObjChunk::_funcGenBuffers              = Win::invalidFunctionID;
UInt32 UniformBufferObjChunk::_funcDeleteBuffers           = Win::invalidFunctionID;
UInt32 UniformBufferObjChunk::_funcGetBufferParameteriv    = Win::invalidFunctionID;

UInt32 UniformBufferObjChunk::_funcBindBufferBase          = Win::invalidFunctionID;
UInt32 UniformBufferObjChunk::_funcGetUniformBlockIndex    = Win::invalidFunctionID;
UInt32 UniformBufferObjChunk::_funcGetActiveUniformBlockiv = Win::invalidFunctionID;
UInt32 UniformBufferObjChunk::_funcGetActiveUniformsiv     = Win::invalidFunctionID;
UInt32 UniformBufferObjChunk::_funcGetUniformIndices       = Win::invalidFunctionID;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void UniformBufferObjChunk::initMethod(InitPhase ePhase)
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

        _funcDeleteBuffers = Window::registerFunction(
            OSG_DLSYM_UNDERSCORE"glDeleteBuffersARB",   
            _extVertexBufferObject);

        _funcGenBuffers = Window::registerFunction(
            OSG_DLSYM_UNDERSCORE"glGenBuffersARB",   
            _extVertexBufferObject);

        _funcGetBufferParameteriv = Window::registerFunction(
            OSG_DLSYM_UNDERSCORE"glGetBufferParameterivARB",   
            _extVertexBufferObject);


        _extUniformBufferObject  =
            Window::registerExtension("GL_ARB_uniform_buffer_object"  );

        _funcBindBufferBase = Window::registerFunction(
            OSG_DLSYM_UNDERSCORE"glBindBufferBase",   
            _extUniformBufferObject);

        _funcGetUniformBlockIndex = Window::registerFunction(
            OSG_DLSYM_UNDERSCORE"glGetUniformBlockIndex",   
            _extUniformBufferObject);

        _funcGetActiveUniformBlockiv = Window::registerFunction(
            OSG_DLSYM_UNDERSCORE"glGetActiveUniformBlockiv",   
            _extUniformBufferObject);

        _funcGetActiveUniformsiv = Window::registerFunction(
            OSG_DLSYM_UNDERSCORE"glGetActiveUniformsiv",   
            _extUniformBufferObject);

        _funcGetUniformIndices = Window::registerFunction(
            OSG_DLSYM_UNDERSCORE"glGetUniformIndices",   
            _extUniformBufferObject);
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

UniformBufferObjChunk::UniformBufferObjChunk(void) :
    Inherited()
{
}

UniformBufferObjChunk::UniformBufferObjChunk(const UniformBufferObjChunk &source) :
    Inherited(source)
{
}

UniformBufferObjChunk::~UniformBufferObjChunk(void)
{
}

/*----------------------------- class specific ----------------------------*/

void UniformBufferObjChunk::changed(ConstFieldMaskArg whichField, 
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

void UniformBufferObjChunk::onCreate(const UniformBufferObjChunk *source)
{
    Inherited::onCreate(source);

    if(GlobalSystemState == Startup)
        return;

    setGLId(Window::registerGLObject(
                boost::bind(&UniformBufferObjChunk::handleGL, 
                            UniformBufferObjChunkMTUncountedPtr(this), 
                            _1, _2, _3, _4),
                &UniformBufferObjChunk::handleDestroyGL));
}

void UniformBufferObjChunk::onCreateAspect(const UniformBufferObjChunk *createAspect,
                                           const UniformBufferObjChunk *source      )
{
    Inherited::onCreateAspect(createAspect, source);
}

void UniformBufferObjChunk::onDestroy(UInt32 uiContainerId)
{
    if(getGLId() > 0)
        Window::destroyGLObject(getGLId(), 1);

    Inherited::onDestroy(uiContainerId);
}

/*------------------------------ Output ----------------------------------*/

void UniformBufferObjChunk::dump(      UInt32    uiIndent,
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
UInt32 UniformBufferObjChunk::handleGL(DrawEnv                 *pEnv, 
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
            ("UniformBufferObjChunk::handleGL: vertex buffer objects not "
             "supported for this window!\n"));
        return 0;
    }

    bool hasUBO = pWin->hasExtOrVersion(_extUniformBufferObject, 0x0300);
    if(!hasUBO)
    {
        FWARNING(
            ("UniformBufferObjChunk::handleGL: uniform buffer objects not "
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
                    osgGlBindBuffer    (GL_UNIFORM_BUFFER, id);
                    osgGlBufferData    (GL_UNIFORM_BUFFER, sz, &buffer[0], _sfUsage.getValue());
                    osgGlBindBuffer    (GL_UNIFORM_BUFFER, 0);
                }

                glErr("UniformBufferObjChunk::handleGL initialize");
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

                osgGlBindBuffer(GL_UNIFORM_BUFFER, id);
                GLubyte* pBuffer = static_cast<GLubyte*>(
                                    osgGlMapBuffer(GL_UNIFORM_BUFFER, GL_WRITE_ONLY_ARB));

                std::vector<GLubyte> buffer = createBuffer(pEnv);
                if (!buffer.empty())
                    memcpy(pBuffer, &buffer[0], sizeof(GLubyte) * buffer.size());
    
                osgGlUnmapBuffer(GL_UNIFORM_BUFFER);
                osgGlBindBuffer (GL_UNIFORM_BUFFER, 0);

                glErr("UniformBufferObjChunk::handleGL needrefresh");
            }
            break;
        default:
            {
                SWARNING << "UniformBufferObjChunk(" << this << "::handleGL: Illegal mode: "
                         << mode << " for id " << id << std::endl;
            }
    }

    return 0;
}

/*! GL object handler
    destroy it
*/
void UniformBufferObjChunk::handleDestroyGL(DrawEnv                 *pEnv, 
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

        glErr("UniformBufferObjChunk::handleDestroyGL");
    }
    else if(mode == Window::finaldestroy)
    {
        //SWARNING << "Last buffer user destroyed" << std::endl;
    }
    else
    {
        SWARNING << "UniformBufferObjChunk::handleDestroyGL: Illegal mode: "
             << mode << " for id " << id << std::endl;
    }

}

/*------------------------------ tools --------------------------------------*/

void UniformBufferObjChunk::validate(DrawEnv *pEnv)
{
    pEnv->getWindow()->validateGLObject(this->getGLId(),
                                        pEnv           );
}

Int32 UniformBufferObjChunk::getOpenGLId(DrawEnv *pEnv)
{
    return pEnv->getWindow()->getGLObjectId(this->getGLId());
}

/*------------------------------ activate -----------------------------------*/

void UniformBufferObjChunk::activate(DrawEnv *pEnv, UInt32 idx)
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

    osgGlBindBuffer    (GL_UNIFORM_BUFFER, id);
    osgGlBindBufferBase(GL_UNIFORM_BUFFER, idx, id);

    glErr("UniformBufferObjChunk::activate");
}

/*------------------------------ deactivate ---------------------------------*/

void UniformBufferObjChunk::deactivate(DrawEnv *pEnv, UInt32 idx)
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

    osgGlBindBufferBase(GL_UNIFORM_BUFFER, idx, 0);
    osgGlBindBuffer    (GL_UNIFORM_BUFFER, 0);

    glErr("UniformBufferObjChunk::deactivate");
}

/*------------------------------ changeFrom ---------------------------------*/

void UniformBufferObjChunk::changeFrom(DrawEnv    *pEnv,
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

std::vector<GLubyte> UniformBufferObjChunk::createBuffer(DrawEnv *pEnv)
{
    Window *pWin = pEnv->getWindow();

    OSGGETGLFUNCBYID_GL3_ES(   glGetUniformBlockIndex, 
                            osgGlGetUniformBlockIndex,
                            _funcGetUniformBlockIndex, 
                            pWin);

    OSGGETGLFUNCBYID_GL3_ES(   glGetActiveUniformBlockiv, 
                            osgGlGetActiveUniformBlockiv,
                            _funcGetActiveUniformBlockiv, 
                            pWin);

    OSGGETGLFUNCBYID_GL3_ES(   glGetActiveUniformsiv, 
                            osgGlGetActiveUniformsiv,
                            _funcGetActiveUniformsiv, 
                            pWin);

    OSGGETGLFUNCBYID_GL3_ES(   glGetUniformIndices, 
                            osgGlGetUniformIndices,
                            _funcGetUniformIndices, 
                            pWin);

    std::vector<GLubyte> buffer;

    GLuint index = osgGlGetUniformBlockIndex(pEnv->getActiveShader(), _sfBlockName.getValue().c_str());
    if (index == GL_INVALID_INDEX) {
        SWARNING << "UniformBufferObjChunk::createBuffer: Invalid block index" << std::endl;
        return buffer;
    }

    GLint num;
    osgGlGetActiveUniformBlockiv(pEnv->getActiveShader(), index, GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS, &num);

    if (SizeT(num) != _mfIndex.size())
    {
        SWARNING << "UniformBufferObjChunk::createBuffer: Invalid number of active uniforms in block" << std::endl;
        return buffer;
    }

    std::vector<const GLchar*> names;
    for (std::size_t i = 0; i < _mfNames.size(); ++i)
        names.push_back(_mfNames[i].c_str());

    std::vector<GLuint> indices(num);
    osgGlGetUniformIndices(pEnv->getActiveShader(), num, &names[0], &indices[0]);
    for (std::size_t i = 0; i < indices.size(); ++i) {
        if (indices[i] == GL_INVALID_INDEX) {
            SWARNING << "UniformBufferObjChunk::createBuffer: Invalid block indices" << std::endl;
            return buffer;
        }
    }

    std::vector<GLint> offsets(num), array_strides(num), matrix_strides(num);

    osgGlGetActiveUniformsiv(pEnv->getActiveShader(), num, &indices[0], GL_UNIFORM_OFFSET,        &offsets[0]);
    osgGlGetActiveUniformsiv(pEnv->getActiveShader(), num, &indices[0], GL_UNIFORM_ARRAY_STRIDE,  &array_strides[0]);
    osgGlGetActiveUniformsiv(pEnv->getActiveShader(), num, &indices[0], GL_UNIFORM_MATRIX_STRIDE, &matrix_strides[0]);
    
    GLint size;
    osgGlGetActiveUniformBlockiv(pEnv->getActiveShader(), index, GL_UNIFORM_BLOCK_DATA_SIZE, &size);

    buffer.resize(size);

    for (GLint i = 0; i < num; ++i)
    {
        UInt32              idx   =                               _mfIndex           [i];
        FundamentalTypes    fType = static_cast<FundamentalTypes>(_mfFundamentalTypes[i]);
        MainType            mType = static_cast<MainType>        (_mfMainTypes       [i]);
        UInt32              card  =                               _mfCardinality     [i];

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

        GLint  offset        = offsets[i];
        GLint  array_stride  = array_strides[i];
        GLint  matrix_stride = matrix_strides[i];

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

UInt32 UniformBufferObjChunk::addFloat(const std::string& name, UInt32 cardinality)
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

UInt32 UniformBufferObjChunk::addDouble(const std::string& name, UInt32 cardinality)
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

UInt32 UniformBufferObjChunk::addInt(const std::string& name, UInt32 cardinality)
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

UInt32 UniformBufferObjChunk::addUInt(const std::string& name, UInt32 cardinality)
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

UInt32 UniformBufferObjChunk::addBool(const std::string& name, UInt32 cardinality)
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

UInt32 UniformBufferObjChunk::addVec2(const std::string& name, UInt32 cardinality)
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

UInt32 UniformBufferObjChunk::addVec3(const std::string& name, UInt32 cardinality)
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

UInt32 UniformBufferObjChunk::addVec4(const std::string& name, UInt32 cardinality)
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

UInt32 UniformBufferObjChunk::addDVec2(const std::string& name, UInt32 cardinality)
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

UInt32 UniformBufferObjChunk::addDVec3(const std::string& name, UInt32 cardinality)
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

UInt32 UniformBufferObjChunk::addDVec4(const std::string& name, UInt32 cardinality)
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

UInt32 UniformBufferObjChunk::addIVec2(const std::string& name, UInt32 cardinality)
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

UInt32 UniformBufferObjChunk::addIVec3(const std::string& name, UInt32 cardinality)
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

UInt32 UniformBufferObjChunk::addIVec4(const std::string& name, UInt32 cardinality)
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

UInt32 UniformBufferObjChunk::addUVec2(const std::string& name, UInt32 cardinality)
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

UInt32 UniformBufferObjChunk::addUVec3(const std::string& name, UInt32 cardinality)
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

UInt32 UniformBufferObjChunk::addUVec4(const std::string& name, UInt32 cardinality)
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

UInt32 UniformBufferObjChunk::addBVec2(const std::string& name, UInt32 cardinality)
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

UInt32 UniformBufferObjChunk::addBVec3(const std::string& name, UInt32 cardinality)
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

UInt32 UniformBufferObjChunk::addBVec4(const std::string& name, UInt32 cardinality)
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

UInt32 UniformBufferObjChunk::addMat2(const std::string& name, UInt32 cardinality)
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

UInt32 UniformBufferObjChunk::addMat3(const std::string& name, UInt32 cardinality)
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

UInt32 UniformBufferObjChunk::addMat4(const std::string& name, UInt32 cardinality)
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

UInt32 UniformBufferObjChunk::addDMat2(const std::string& name, UInt32 cardinality)
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

UInt32 UniformBufferObjChunk::addDMat3(const std::string& name, UInt32 cardinality)
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

UInt32 UniformBufferObjChunk::addDMat4(const std::string& name, UInt32 cardinality)
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

UInt32 UniformBufferObjChunk::addMat2x3(const std::string& name, UInt32 cardinality)
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

UInt32 UniformBufferObjChunk::addMat3x2(const std::string& name, UInt32 cardinality)
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

UInt32 UniformBufferObjChunk::addMat2x4(const std::string& name, UInt32 cardinality)
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

UInt32 UniformBufferObjChunk::addMat4x2(const std::string& name, UInt32 cardinality)
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

UInt32 UniformBufferObjChunk::addMat3x4(const std::string& name, UInt32 cardinality)
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

UInt32 UniformBufferObjChunk::addMat4x3(const std::string& name, UInt32 cardinality)
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

UInt32 UniformBufferObjChunk::addDMat2x3(const std::string& name, UInt32 cardinality)
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

UInt32 UniformBufferObjChunk::addDMat3x2(const std::string& name, UInt32 cardinality)
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

UInt32 UniformBufferObjChunk::addDMat2x4(const std::string& name, UInt32 cardinality)
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

UInt32 UniformBufferObjChunk::addDMat4x2(const std::string& name, UInt32 cardinality)
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

UInt32 UniformBufferObjChunk::addDMat3x4(const std::string& name, UInt32 cardinality)
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

UInt32 UniformBufferObjChunk::addDMat4x3(const std::string& name, UInt32 cardinality)
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

void UniformBufferObjChunk::setFloat(UInt32 handle, Real32 value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(FloatValuesFieldMask, _mfFloatValues);
    _mfFloatValues[_mfIndex[handle] + array_idx] = value;
}

void UniformBufferObjChunk::setDouble(UInt32 handle, Real64 value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(DoubleValuesFieldMask, _mfDoubleValues);
    _mfDoubleValues[_mfIndex[handle] + array_idx] = value;
}

void UniformBufferObjChunk::setInt(UInt32 handle, Int32 value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(IntValuesFieldMask, _mfIntValues);
    _mfIntValues[_mfIndex[handle] + array_idx] = value;
}

void UniformBufferObjChunk::setUInt(UInt32 handle, UInt32 value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(UIntValuesFieldMask, _mfUIntValues);
    _mfUIntValues[_mfIndex[handle] + array_idx] = value;
}

void UniformBufferObjChunk::setBool(UInt32 handle, bool value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(BoolValuesFieldMask, _mfBoolValues);
    _mfBoolValues[_mfIndex[handle] + array_idx] = static_cast<UInt8>(value);
}

void UniformBufferObjChunk::setVec2(UInt32 handle, const Vec2f& value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(FloatValuesFieldMask, _mfFloatValues);

    int size = 2;
    for (int i = 0; i < size; ++i)
        _mfFloatValues[_mfIndex[handle] + (array_idx * size) + i] = value[i];
}

void UniformBufferObjChunk::setVec2(UInt32 handle, const Pnt2f& value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(FloatValuesFieldMask, _mfFloatValues);

    int size = 2;
    for (int i = 0; i < size; ++i)
        _mfFloatValues[_mfIndex[handle] + (array_idx * size) + i] = value[i];
}

void UniformBufferObjChunk::setVec3(UInt32 handle, const Vec3f& value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(FloatValuesFieldMask, _mfFloatValues);
    
    int size = 3;
    for (int i = 0; i < size; ++i)
        _mfFloatValues[_mfIndex[handle] + (array_idx * size) + i] = value[i];
}

void UniformBufferObjChunk::setVec3(UInt32 handle, const Pnt3f& value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(FloatValuesFieldMask, _mfFloatValues);
    
    int size = 3;
    for (int i = 0; i < size; ++i)
        _mfFloatValues[_mfIndex[handle] + (array_idx * size) + i] = value[i];
}

void UniformBufferObjChunk::setVec3(UInt32 handle, const Color3f& value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(FloatValuesFieldMask, _mfFloatValues);
    
    int size = 3;
    for (int i = 0; i < size; ++i)
        _mfFloatValues[_mfIndex[handle] + (array_idx * size) + i] = value[i];
}

void UniformBufferObjChunk::setVec4(UInt32 handle, const Vec4f& value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(FloatValuesFieldMask, _mfFloatValues);

    int size = 4;
    for (int i = 0; i < size; ++i)
        _mfFloatValues[_mfIndex[handle] + (array_idx * size) + i] = value[i];
}

void UniformBufferObjChunk::setVec4(UInt32 handle, const Pnt4f& value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(FloatValuesFieldMask, _mfFloatValues);

    int size = 4;
    for (int i = 0; i < size; ++i)
        _mfFloatValues[_mfIndex[handle] + (array_idx * size) + i] = value[i];
}

void UniformBufferObjChunk::setVec4(UInt32 handle, const Color4f& value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(FloatValuesFieldMask, _mfFloatValues);

    int size = 4;
    for (int i = 0; i < size; ++i)
        _mfFloatValues[_mfIndex[handle] + (array_idx * size) + i] = value[i];
}

void UniformBufferObjChunk::setDVec2(UInt32 handle, const Vec2d& value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(DoubleValuesFieldMask, _mfDoubleValues);

    int size = 2;
    for (int i = 0; i < size; ++i)
        _mfDoubleValues[_mfIndex[handle] + (array_idx * size) + i] = value[i];
}

void UniformBufferObjChunk::setDVec2(UInt32 handle, const Pnt2d& value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(DoubleValuesFieldMask, _mfDoubleValues);

    int size = 2;
    for (int i = 0; i < size; ++i)
        _mfDoubleValues[_mfIndex[handle] + (array_idx * size) + i] = value[i];
}

void UniformBufferObjChunk::setDVec3(UInt32 handle, const Vec3d& value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(DoubleValuesFieldMask, _mfDoubleValues);

    int size = 3;
    for (int i = 0; i < size; ++i)
        _mfDoubleValues[_mfIndex[handle] + (array_idx * size) + i] = value[i];
}

void UniformBufferObjChunk::setDVec3(UInt32 handle, const Pnt3d& value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(DoubleValuesFieldMask, _mfDoubleValues);

    int size = 3;
    for (int i = 0; i < size; ++i)
        _mfDoubleValues[_mfIndex[handle] + (array_idx * size) + i] = value[i];
}

void UniformBufferObjChunk::setDVec4(UInt32 handle, const Vec4d& value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(DoubleValuesFieldMask, _mfDoubleValues);

    int size = 4;
    for (int i = 0; i < size; ++i)
        _mfDoubleValues[_mfIndex[handle] + (array_idx * size) + i] = value[i];
}

void UniformBufferObjChunk::setDVec4(UInt32 handle, const Pnt4d& value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(DoubleValuesFieldMask, _mfDoubleValues);

    int size = 4;
    for (int i = 0; i < size; ++i)
        _mfDoubleValues[_mfIndex[handle] + (array_idx * size) + i] = value[i];
}

void UniformBufferObjChunk::setIVec2(UInt32 handle, const Vec2i& value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(IntValuesFieldMask, _mfIntValues);

    int size = 2;
    for (int i = 0; i < size; ++i)
        _mfIntValues[_mfIndex[handle] + (array_idx * size) + i] = value[i];
}

void UniformBufferObjChunk::setIVec2(UInt32 handle, const Pnt2i& value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(IntValuesFieldMask, _mfIntValues);

    int size = 2;
    for (int i = 0; i < size; ++i)
        _mfIntValues[_mfIndex[handle] + (array_idx * size) + i] = value[i];
}

void UniformBufferObjChunk::setIVec3(UInt32 handle, const Vec3i& value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(IntValuesFieldMask, _mfIntValues);

    int size = 3;
    for (int i = 0; i < size; ++i)
        _mfIntValues[_mfIndex[handle] + (array_idx * size) + i] = value[i];
}
/*
void UniformBufferObjChunk::setIVec3(UInt32 handle, const Pnt3i& value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(IntValuesFieldMask, _mfIntValues);

    int size = 3;
    for (int i = 0; i < size; ++i)
        _mfIntValues[_mfIndex[handle] + (array_idx * size) + i] = value[i];
}
*/
void UniformBufferObjChunk::setIVec4(UInt32 handle, const Vec4i& value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(IntValuesFieldMask, _mfIntValues);

    int size = 4;
    for (int i = 0; i < size; ++i)
        _mfIntValues[_mfIndex[handle] + (array_idx * size) + i] = value[i];
}
/*
void UniformBufferObjChunk::setIVec4(UInt32 handle, const Pnt4i& value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(IntValuesFieldMask, _mfIntValues);

    int size = 4;
    for (int i = 0; i < size; ++i)
        _mfIntValues[_mfIndex[handle] + (array_idx * size) + i] = value[i];
}
*/
void UniformBufferObjChunk::setUVec2(UInt32 handle, const Vec2u& value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(UIntValuesFieldMask, _mfUIntValues);

    int size = 2;
    for (int i = 0; i < size; ++i)
        _mfUIntValues[_mfIndex[handle] + (array_idx * size) + i] = value[i];
}
/*
void UniformBufferObjChunk::setUVec2(UInt32 handle, const Pnt2u& value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(UIntValuesFieldMask, _mfUIntValues);

    int size = 2;
    for (int i = 0; i < size; ++i)
        _mfUIntValues[_mfIndex[handle] + (array_idx * size) + i] = value[i];
}
*/
void UniformBufferObjChunk::setUVec3(UInt32 handle, const Vec3u& value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(UIntValuesFieldMask, _mfUIntValues);

    int size = 3;
    for (int i = 0; i < size; ++i)
        _mfUIntValues[_mfIndex[handle] + (array_idx * size) + i] = value[i];
}
/*
void UniformBufferObjChunk::setUVec3(UInt32 handle, const Pnt3u& value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(UIntValuesFieldMask, _mfUIntValues);

    int size = 3;
    for (int i = 0; i < size; ++i)
        _mfUIntValues[_mfIndex[handle] + (array_idx * size) + i] = value[i];
}
*/
void UniformBufferObjChunk::setUVec4(UInt32 handle, const Vec4u& value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(UIntValuesFieldMask, _mfUIntValues);

    int size = 4;
    for (int i = 0; i < size; ++i)
        _mfUIntValues[_mfIndex[handle] + (array_idx * size) + i] = value[i];
}
/*
void UniformBufferObjChunk::setUVec4(UInt32 handle, const Pnt4u& value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(UIntValuesFieldMask, _mfUIntValues);

    int size = 4;
    for (int i = 0; i < size; ++i)
        _mfUIntValues[_mfIndex[handle] + (array_idx * size) + i] = value[i];
}
*/
void UniformBufferObjChunk::setBVec2(UInt32 handle, const Vec2b& value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(BoolValuesFieldMask, _mfBoolValues);

    int size = 2;
    for (int i = 0; i < size; ++i)
        _mfBoolValues[_mfIndex[handle] + (array_idx * size) + i] = static_cast<UInt8>(value[i]);
}

void UniformBufferObjChunk::setBVec2(UInt32 handle, const Pnt2b& value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(BoolValuesFieldMask, _mfBoolValues);

    int size = 2;
    for (int i = 0; i < size; ++i)
        _mfBoolValues[_mfIndex[handle] + (array_idx * size) + i] = static_cast<UInt8>(value[i]);
}

void UniformBufferObjChunk::setBVec3(UInt32 handle, const Vec3b& value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(BoolValuesFieldMask, _mfBoolValues);

    int size = 3;
    for (int i = 0; i < size; ++i)
        _mfBoolValues[_mfIndex[handle] + (array_idx * size) + i] = static_cast<UInt8>(value[i]);
}

void UniformBufferObjChunk::setBVec3(UInt32 handle, const Pnt3b& value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(BoolValuesFieldMask, _mfBoolValues);

    int size = 3;
    for (int i = 0; i < size; ++i)
        _mfBoolValues[_mfIndex[handle] + (array_idx * size) + i] = static_cast<UInt8>(value[i]);
}

void UniformBufferObjChunk::setBVec4(UInt32 handle, const Vec4b& value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(BoolValuesFieldMask, _mfBoolValues);

    int size = 4;
    for (int i = 0; i < size; ++i)
        _mfBoolValues[_mfIndex[handle] + (array_idx * size) + i] = static_cast<UInt8>(value[i]);
}

void UniformBufferObjChunk::setBVec4(UInt32 handle, const Pnt4b& value, UInt32 array_idx)
{
    OSG_ASSERT(array_idx < _mfCardinality[handle]);

    editMField(BoolValuesFieldMask, _mfBoolValues);

    int size = 4;
    for (int i = 0; i < size; ++i)
        _mfBoolValues[_mfIndex[handle] + (array_idx * size) + i] = static_cast<UInt8>(value[i]);
}

void UniformBufferObjChunk::setMat2(UInt32 handle, const Matrix4f& value, UInt32 array_idx)
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

void UniformBufferObjChunk::setMat3(UInt32 handle, const Matrix4f& value, UInt32 array_idx)
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

void UniformBufferObjChunk::setMat4(UInt32 handle, const Matrix4f& value, UInt32 array_idx)
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

void UniformBufferObjChunk::setDMat2(UInt32 handle, const Matrix4d& value, UInt32 array_idx)
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

void UniformBufferObjChunk::setDMat3(UInt32 handle, const Matrix4d& value, UInt32 array_idx)
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

void UniformBufferObjChunk::setDMat4(UInt32 handle, const Matrix4d& value, UInt32 array_idx)
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

void UniformBufferObjChunk::setMat2x3(UInt32 handle, const Matrix4f& value, UInt32 array_idx)
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

void UniformBufferObjChunk::setMat3x2(UInt32 handle, const Matrix4f& value, UInt32 array_idx)
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

void UniformBufferObjChunk::setMat2x4(UInt32 handle, const Matrix4f& value, UInt32 array_idx)
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

void UniformBufferObjChunk::setMat4x2(UInt32 handle, const Matrix4f& value, UInt32 array_idx)
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

void UniformBufferObjChunk::setMat3x4(UInt32 handle, const Matrix4f& value, UInt32 array_idx)
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

void UniformBufferObjChunk::setMat4x3(UInt32 handle, const Matrix4f& value, UInt32 array_idx)
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

void UniformBufferObjChunk::setDMat2x3(UInt32 handle, const Matrix4d& value, UInt32 array_idx)
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

void UniformBufferObjChunk::setDMat3x2(UInt32 handle, const Matrix4d& value, UInt32 array_idx)
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

void UniformBufferObjChunk::setDMat2x4(UInt32 handle, const Matrix4d& value, UInt32 array_idx)
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

void UniformBufferObjChunk::setDMat4x2(UInt32 handle, const Matrix4d& value, UInt32 array_idx)
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

void UniformBufferObjChunk::setDMat3x4(UInt32 handle, const Matrix4d& value, UInt32 array_idx)
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

void UniformBufferObjChunk::setDMat4x3(UInt32 handle, const Matrix4d& value, UInt32 array_idx)
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

void UniformBufferObjChunk::setFloat(const std::string& name, Real32 value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setFloat(iter->second, value, array_idx);
}

void UniformBufferObjChunk::setDouble(const std::string& name, Real64 value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setDouble(iter->second, value, array_idx);
}

void UniformBufferObjChunk::setInt(const std::string& name, Int32 value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setInt(iter->second, value, array_idx);
}

void UniformBufferObjChunk::setUInt(const std::string& name, UInt32 value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setUInt(iter->second, value, array_idx);
}

void UniformBufferObjChunk::setBool(const std::string& name, bool value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setBool(iter->second, value, array_idx);
}

void UniformBufferObjChunk::setVec2(const std::string& name, const Vec2f& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setVec2(iter->second, value, array_idx);
}

void UniformBufferObjChunk::setVec2(const std::string& name, const Pnt2f& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setVec2(iter->second, value, array_idx);
}

void UniformBufferObjChunk::setVec3(const std::string& name, const Vec3f& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setVec3(iter->second, value, array_idx);
}

void UniformBufferObjChunk::setVec3(const std::string& name, const Pnt3f& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setVec3(iter->second, value, array_idx);
}

void UniformBufferObjChunk::setVec3(const std::string& name, const Color3f& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setVec3(iter->second, value, array_idx);
}

void UniformBufferObjChunk::setVec4(const std::string& name, const Vec4f& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setVec4(iter->second, value, array_idx);
}

void UniformBufferObjChunk::setVec4(const std::string& name, const Pnt4f& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setVec4(iter->second, value, array_idx);
}

void UniformBufferObjChunk::setVec4(const std::string& name, const Color4f& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setVec4(iter->second, value, array_idx);
}

void UniformBufferObjChunk::setDVec2(const std::string& name, const Vec2d& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setDVec2(iter->second, value, array_idx);
}

void UniformBufferObjChunk::setDVec2(const std::string& name, const Pnt2d& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setDVec2(iter->second, value, array_idx);
}

void UniformBufferObjChunk::setDVec3(const std::string& name, const Vec3d& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setDVec3(iter->second, value, array_idx);
}

void UniformBufferObjChunk::setDVec3(const std::string& name, const Pnt3d& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setDVec3(iter->second, value, array_idx);
}

void UniformBufferObjChunk::setDVec4(const std::string& name, const Vec4d& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setDVec4(iter->second, value, array_idx);
}

void UniformBufferObjChunk::setDVec4(const std::string& name, const Pnt4d& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setDVec4(iter->second, value, array_idx);
}

void UniformBufferObjChunk::setIVec2(const std::string& name, const Vec2i& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setIVec2(iter->second, value, array_idx);
}

void UniformBufferObjChunk::setIVec2(const std::string& name, const Pnt2i& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setIVec2(iter->second, value, array_idx);
}

void UniformBufferObjChunk::setIVec3(const std::string& name, const Vec3i& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setIVec3(iter->second, value, array_idx);
}
/*
void UniformBufferObjChunk::setIVec3(const std::string& name, const Pnt3i& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setIVec3(iter->second, value, array_idx);
}
*/
void UniformBufferObjChunk::setIVec4(const std::string& name, const Vec4i& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setIVec4(iter->second, value, array_idx);
}
/*
void UniformBufferObjChunk::setIVec4(const std::string& name, const Pnt4i& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setIVec4(iter->second, value, array_idx);
}
*/
void UniformBufferObjChunk::setUVec2(const std::string& name, const Vec2u& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setUVec2(iter->second, value, array_idx);
}
/*
void UniformBufferObjChunk::setUVec2(const std::string& name, const Pnt2u& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setUVec2(iter->second, value, array_idx);
}
*/
void UniformBufferObjChunk::setUVec3(const std::string& name, const Vec3u& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setUVec3(iter->second, value, array_idx);
}
/*
void UniformBufferObjChunk::setUVec3(const std::string& name, const Pnt3u& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setUVec3(iter->second, value, array_idx);
}
*/
void UniformBufferObjChunk::setUVec4(const std::string& name, const Vec4u& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setUVec4(iter->second, value, array_idx);
}
/*
void UniformBufferObjChunk::setUVec4(const std::string& name, const Pnt4u& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setUVec4(iter->second, value, array_idx);
}
*/
void UniformBufferObjChunk::setBVec2(const std::string& name, const Vec2b& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setBVec2(iter->second, value, array_idx);
}

void UniformBufferObjChunk::setBVec2(const std::string& name, const Pnt2b& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setBVec2(iter->second, value, array_idx);
}

void UniformBufferObjChunk::setBVec3(const std::string& name, const Vec3b& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setBVec3(iter->second, value, array_idx);
}

void UniformBufferObjChunk::setBVec3(const std::string& name, const Pnt3b& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setBVec3(iter->second, value, array_idx);
}

void UniformBufferObjChunk::setBVec4(const std::string& name, const Vec4b& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setBVec4(iter->second, value, array_idx);
}

void UniformBufferObjChunk::setBVec4(const std::string& name, const Pnt4b& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setBVec4(iter->second, value, array_idx);
}

void UniformBufferObjChunk::setMat2(const std::string& name, const Matrix4f& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setMat2(iter->second, value, array_idx);
}

void UniformBufferObjChunk::setMat3(const std::string& name, const Matrix4f& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setMat3(iter->second, value, array_idx);
}

void UniformBufferObjChunk::setMat4(const std::string& name, const Matrix4f& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setMat4(iter->second, value, array_idx);
}

void UniformBufferObjChunk::setDMat2(const std::string& name, const Matrix4d& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setDMat2(iter->second, value, array_idx);
}

void UniformBufferObjChunk::setDMat3(const std::string& name, const Matrix4d& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setDMat3(iter->second, value, array_idx);
}

void UniformBufferObjChunk::setDMat4(const std::string& name, const Matrix4d& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setDMat4(iter->second, value, array_idx);
}

void UniformBufferObjChunk::setMat2x3(const std::string& name, const Matrix4f& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setMat2x3(iter->second, value, array_idx);
}

void UniformBufferObjChunk::setMat3x2(const std::string& name, const Matrix4f& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setMat3x2(iter->second, value, array_idx);
}

void UniformBufferObjChunk::setMat2x4(const std::string& name, const Matrix4f& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setMat2x4(iter->second, value, array_idx);
}

void UniformBufferObjChunk::setMat4x2(const std::string& name, const Matrix4f& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setMat4x2(iter->second, value, array_idx);
}

void UniformBufferObjChunk::setMat3x4(const std::string& name, const Matrix4f& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setMat3x4(iter->second, value, array_idx);
}

void UniformBufferObjChunk::setMat4x3(const std::string& name, const Matrix4f& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setMat4x3(iter->second, value, array_idx);
}

void UniformBufferObjChunk::setDMat2x3(const std::string& name, const Matrix4d& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setDMat2x3(iter->second, value, array_idx);
}

void UniformBufferObjChunk::setDMat3x2(const std::string& name, const Matrix4d& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setDMat3x2(iter->second, value, array_idx);
}

void UniformBufferObjChunk::setDMat2x4(const std::string& name, const Matrix4d& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setDMat2x4(iter->second, value, array_idx);
}

void UniformBufferObjChunk::setDMat4x2(const std::string& name, const Matrix4d& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setDMat4x2(iter->second, value, array_idx);
}

void UniformBufferObjChunk::setDMat3x4(const std::string& name, const Matrix4d& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setDMat3x4(iter->second, value, array_idx);
}

void UniformBufferObjChunk::setDMat4x3(const std::string& name, const Matrix4d& value, UInt32 array_idx)
{
    StringToUInt32Map::const_iterator iter = _sfNameToIndex.getValue().find(name);
    OSG_ASSERT(iter != _sfNameToIndex.getValue().end());
    setDMat4x3(iter->second, value, array_idx);
}

/*------------------------------ Invariants ---------------------------------*/

bool UniformBufferObjChunk::invariantOnStorageSize()
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
