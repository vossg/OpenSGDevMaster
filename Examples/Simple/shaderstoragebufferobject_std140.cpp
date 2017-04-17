// OpenSG Tutorial Example: ShaderStorageBufferObject
//
// This example shows how to create a shader buffer block and binding it 
// to a shader storage buffer object.
//
// The example does use the ShaderStorageBufferObjStdLayoutChunk which 
// allows the host application to directly provide a buffer to the chunk 
// according to the std140 or std430 specification. Which specification
// is used is determined by the buffer block layout declaration in the 
// shader code.
//
// This example uses solely the std140 layout.
//
// We create a simple scene geometry consisting of a cylinder and a 
// torus. The materials for these objects are indexed from a material
// database. The indices are part of the material state of the objects.
// In particular, the geometry objects do have chunk materials with
// exactly one ShaderStorageBufferObjStdLayoutChunk each, which only 
// contain the index into the material database. 
// The material database itself is also a ShaderStorageBufferObjStd-
// LayoutChunk as well as the active lights of the scene. These are
// added globally with the help of a MaterialChunkOverrideGroup for
// all geometry of the scene.
//
// Additionally, a ShaderStorageBufferObjStdLayoutChunk is also 
// added to the MaterialChunkOverrideGroup that does access a shader
// storage test block with the same layout as in the OpenGL std140 
// specification. The  shader does check the content of this block.
// If the content is invalid the complete fragement color is switched 
// to plain red, indicating an error.
//
// Remark:
//   In real life one would probably not use a shader storage buffer 
//   for the geometry material index state. But this example should 
//   only use a couple of shader storage buffers for illustration 
//   purpose.
//
// Shader Storage buffer objects in this example:
//      test block            -> added to the MaterialChunkOverrideGroup
//      material database     -> added to the MaterialChunkOverrideGroup
//      lights                -> added to the MaterialChunkOverrideGroup
//      geom (indices) states -> added to geometry material
//
// The example is roughly grouped into five parts:
//
//      Part   I: Declaration of structurs corresponding to buffer blocks in the shader.
//      Part  II: Some helper functions.
//      Part III: Memory buffer handling and creation routines.
//      Part  IV: The main example application.
//      Part   V: The shader programs.
//

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>

#ifdef OSG_BUILD_ACTIVE
// Headers
#include <OSGGLUT.h>
#include <OSGConfig.h>
#include <OSGSimpleGeometry.h>
#include <OSGGLUTWindow.h>
#include <OSGSimpleSceneManager.h>
#include <OSGBaseFunctions.h>
#include <OSGTransform.h>
#include <OSGGroup.h>

// new headers: 
#include <OSGGLEXT.h>
#include <OSGShaderProgramChunk.h>
#include <OSGShaderProgram.h>
#include <OSGShaderVariableOSG.h>
#include <OSGChunkMaterial.h>
#include <OSGMaterialGroup.h>
#include <OSGMaterialChunkOverrideGroup.h>
#include <OSGShaderStorageBufferObjStdLayoutChunk.h>
#include <OSGPolygonChunk.h>
#include <OSGDepthChunk.h>
#include <OSGShaderProgramVariableChunk.h>

#else
// Headers
#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGBaseFunctions.h>
#include <OpenSG/OSGTransform.h>
#include <OpenSG/OSGGroup.h>

// new headers: 
#include <OpenSG/OSGGLEXT.h>
#include <OpenSG/OSGShaderProgramChunk.h>
#include <OpenSG/OSGShaderProgram.h>
#include <OpenSG/OSGShaderVariableOSG.h>
#include <OpenSG/OSGChunkMaterial.h>
#include <OpenSG/OSGMaterialGroup.h>
#include <OpenSG/OSGMaterialChunkOverrideGroup.h>
#include <OpenSG/OSGShaderStorageBufferObjStdLayoutChunk.h>
#include <OpenSG/OSGPolygonChunk.h>
#include <OpenSG/OSGDepthChunk.h>
#include <OpenSG/OSGShaderProgramVariableChunk.h>
#endif

//
// The SimpleSceneManager to manage simple applications
//
OSG::SimpleSceneManagerRefPtr mgr;

//
// Part I: Declaration of
//              struct TestBlock,
//              struct Light and type VecLightsT,
//              struct Material and type VecMaterialsT,
//              struct GeomState
//         and corresponding initialization routines.
//

//
// The OpenGL std140 specification test block
// Remark: Since OpenSG does not have a Matrix3f or a Matrix2x3f which
//         are used in the specification, we provide dummy structs for
//         them.
//
namespace OSG
{
    struct Matrix3f
    {
        Vec3f row1;
        Vec3f row2;
        Vec3f row3;

        Matrix3f(void) :
            row1(0.f, 0.f, 0.f),
            row2(0.f, 0.f, 0.f),
            row3(0.f, 0.f, 0.f)
        {
        }
    };

    struct Matrix2x3f
    {
        Vec3f row1;
        Vec3f row2;

        Matrix2x3f(void) :
            row1(0.f, 0.f, 0.f),
            row2(0.f, 0.f, 0.f)
        {
        }
    };
}

struct S0
{
    OSG::Int32 d;
    OSG::Vec2b e;
    
    S0(void) :
        d(0   ),
        e(0, 0)
    {
    }
};

struct S1
{
    OSG::Vec3u j;
    OSG::Vec2f k;
    OSG::Real32 l[2];
    OSG::Vec2f m;
    OSG::Matrix3f n[2];

    S1(void) :
        j(0, 0, 0),
        k(0.f, 0.f, 0.f),
        m(0.f, 0.f)
    {
    }
};

struct TestBlock
{
    OSG::Real32 a;
    OSG::Vec2f  b;
    OSG::Vec3f  c;
    S0 f;
    OSG::Real32 g;
    OSG::Real32 h[2];
    OSG::Matrix2x3f i;
    S1 o[2];

    TestBlock(void) :
        a(0.f),
        b(0.f, 0.f),
        c(0.f, 0.f, 0.f),
        f(),
        g(0.f),
        i() 
    {
    }
};

TestBlock initialize_test_block()
{
    TestBlock test_block;

    test_block.a = 27.4f;
    test_block.b = OSG::Vec2f(15.3f, 12.8f);
    test_block.c = OSG::Vec3f(11.4f, 21.9f, 10.5f);

    test_block.f.d = 61;
    test_block.f.e = OSG::Vec2b(true, false);

    test_block.g = 57.3f;

    test_block.h[0] =  9.1f;
    test_block.h[1] = 17.56f;

    test_block.i.row1 = OSG::Vec3f(19.43f, 1243.2f,   0.56f);
    test_block.i.row2 = OSG::Vec3f(13.54f,  264.22f, 65.52f);

    test_block.o[0].j         = OSG::Vec3u(10, 11, 12);
    test_block.o[0].k         = OSG::Vec2f(64.62f, 275.21f);
    test_block.o[0].l[0]      = 41.346f;
    test_block.o[0].l[1]      = 67.9456f;
    test_block.o[0].m         = OSG::Vec2f(-56.62f, 768.276f);
    test_block.o[0].n[0].row1 = OSG::Vec3f(-0.4f,-0.5f,-0.6f);
    test_block.o[0].n[0].row2 = OSG::Vec3f(-0.7f,-0.8f,-0.9f);
    test_block.o[0].n[0].row3 = OSG::Vec3f(-0.1f,-0.2f,-0.3f);
    test_block.o[0].n[1].row1 = OSG::Vec3f( 1.1f, 2.2f, 3.3f);
    test_block.o[0].n[1].row2 = OSG::Vec3f( 1.2f, 2.3f, 3.4f);
    test_block.o[0].n[1].row3 = OSG::Vec3f( 1.3f, 2.4f, 3.5f);

    test_block.o[1].j         = OSG::Vec3u(20, 31, 42);
    test_block.o[1].k         = OSG::Vec2f(-96.62f,-658.456f);
    test_block.o[1].l[0]      = 88.34f;
    test_block.o[1].l[1]      = -488.21f;
    test_block.o[1].m         = OSG::Vec2f(777.7f, 888.8f);
    test_block.o[1].n[0].row1 = OSG::Vec3f( 1.1f, 1.2f, 1.3f);
    test_block.o[1].n[0].row2 = OSG::Vec3f( 2.1f, 2.2f, 2.3f);
    test_block.o[1].n[0].row3 = OSG::Vec3f( 3.1f, 3.2f, 3.3f);
    test_block.o[1].n[1].row1 = OSG::Vec3f(-1.1f,-1.2f,-1.3f);
    test_block.o[1].n[1].row2 = OSG::Vec3f(-2.1f,-2.2f,-2.3f);
    test_block.o[1].n[1].row3 = OSG::Vec3f(-3.1f,-3.2f,-3.3f);

    return test_block;
}

TestBlock global_test_block = initialize_test_block();

//
// simple light data structure
//
struct Light
{
    enum Type
    {
        directional_light = 0,
        point_light,
        spot_light,
        no_light
    };

    Light() 
    : position(0.f, 0.f, 0.f)
    , spot_direction(0.f, 1.f, 0.f)
    , Ia(1.f, 1.f, 1.f)
    , Id(1.f, 1.f, 1.f)
    , Is(1.f, 1.f, 1.f)
    , attenuation(1.f, 0.f, 0.f)
    , spot_cos_cutoff(cosf(45.f))
    , spot_exponent(1.f)
    , type(no_light)
    {}

    static Light create_light(Type e)
    {
        Light l;
        l.type = e;

        switch (e) {
            case directional_light:                                          l.spot_direction = OSG::Vec3f(1.f, 0.f, 0.f);
                break;
            case       point_light: l.position = OSG::Pnt3f(0.f, 0.2f, 0.f);
                break;
            case        spot_light: l.position = OSG::Pnt3f(0.f, 0.2f, 0.f); l.spot_direction = OSG::Pnt3f(0.f, 0.f, 0.f) - l.position;
                break;
            default:
                break;
        }
        return l;
    }

    OSG::Pnt3f   position;           // in object space
    OSG::Vec3f   spot_direction;     // in object space, also used for dir of directional lights (see shader code)
    OSG::Color3f Ia;                 // ambient  max. Intensity
    OSG::Color3f Id;                 // diffuse  max. Intensity
    OSG::Color3f Is;                 // specular max. Intensity

    OSG::Vec3f   attenuation;        // (constant, linear, quadratic) with constant >= 1 and linear,quadratic >= 0
    OSG::Real32  spot_cos_cutoff;    // cosine cut of angle
    OSG::Real32  spot_exponent;      // [0-128]
    OSG::Int32   type;               // directional_light, point_light, spot_light, no_light
};

typedef std::vector<Light>       VecLightsT;        // multiple lights

const std::size_t num_lights = 1;                   // simple example with just one light

VecLightsT initialize_lights()         // helper to create lights
{
    VecLightsT lights;

    lights.push_back(Light::create_light(Light::directional_light));

    assert(lights.size() == num_lights);

    return lights;
}

VecLightsT lights = initialize_lights();    // the lights


//
// Simple material data structure
//
struct Material
{
    Material()
    : ambient (0.f, 0.f, 0.f)
    , diffuse (0.f, 0.f, 0.f)
    , specular(0.f, 0.f, 0.f)
    , emissive(0.f, 0.f, 0.f)
    , opacity(1.f)
    , shininess(100.f)
    {}

    OSG::Color3f ambient;
    OSG::Color3f diffuse;
    OSG::Color3f specular;
    OSG::Color3f emissive;

    OSG::Real32  opacity;
    OSG::Real32  shininess;
};

typedef std::vector<Material> VecMaterialsT;        // multiple materials

VecMaterialsT initialize_materials(std::size_t num) // helper to create materials
{
    VecMaterialsT materials;

    for (std::size_t i = 0; i < num; ++i)
    {
        Material m;

        m.ambient   = OSG::Color3f(0.1f, 0.1f, 0.1f);
        m.diffuse.setRandom();
        m.specular  = OSG::Color3f(0.9f, 0.9f, 0.9f);
        m.emissive  = OSG::Color3f(0.0f, 0.0f, 0.0f);
        m.opacity   = 1.f;
        m.shininess = 80.f;

        materials.push_back(m);
    }

    return materials;
}

const std::size_t num_materials = 500;                            // any number of materials
VecMaterialsT materials = initialize_materials(num_materials);    // the material database


//
// Simple geometry state data structure
//
struct GeomState
{
    GeomState()
    : material_index(0)
    {}

    OSG::UInt32  material_index;
};


//
// Part II: Some helper functions:
//      Pnt3f  transform_to_eye_space(const Pnt3f& p, SimpleSceneManager* pSSM)
//      Vec3f  transform_to_eye_space(const Vec3f& v, SimpleSceneManager* pSSM)
//      size_t align_offset          (size_t base_alignment, size_t base_offset)
//

//
// transform point from world space to eye space
//
OSG::Pnt3f transform_to_eye_space(const OSG::Pnt3f& p, OSG::SimpleSceneManager* pSSM)
{
    if (!pSSM || !pSSM->getWindow() || pSSM->getWindow()->getMFPort()->size() == 0)
        return p;

    OSG::Viewport* pPort = mgr->getWindow()->getPort(0);

    OSG::Pnt3f p_es;

    OSG::Matrix view;
    OSG::Int16 width  = pPort->calcPixelWidth();
    OSG::Int16 height = pPort->calcPixelHeight();

    pPort->getCamera()->getViewing(view, width, height);

    view.multFull( p, p_es);

    return p_es;
}

//
// transform vector from world space to eye space
//
OSG::Vec3f transform_to_eye_space(const OSG::Vec3f& v, OSG::SimpleSceneManager* pSSM)
{
    if (!pSSM || !pSSM->getWindow() || pSSM->getWindow()->getMFPort()->size() == 0)
        return v;

    OSG::Viewport* pPort = mgr->getWindow()->getPort(0);

    OSG::Vec3f v_es;

    OSG::Matrix view;
    OSG::Int16 width  = pPort->calcPixelWidth();
    OSG::Int16 height = pPort->calcPixelHeight();

    pPort->getCamera()->getViewing(view, width, height);

    view.multFull( v, v_es);

    return v_es;
}

//
// helper to calculate the correct buffer insert positions on std140 or std430
//
std::size_t align_offset(std::size_t base_alignment, std::size_t base_offset)
{
    return base_alignment * ((base_alignment + base_offset - 1) / base_alignment);
}


//
// Part III: Some routines for handling of the memory buffer and the the creation of
//           the ShaderStorageBufferObjStdLayoutChunk objects:
//
//           i) calc_test_block_buffer_size, 
//              create_test_block_buffer, 
//              create_test_block_state, 
//              update_test_block_state
//
//          ii) calc_light_buffer_size, 
//              create_light_buffer, 
//              create_light_state, 
//              update_light_state
//
//         iii) calc_material_database_buffer_size, 
//              create_material_database_buffer, 
//              create_material_database_state, 
//              update_material_database_state
//
//          iv) calc_geometry_material_buffer_size, 
//              create_geometry_material_buffer, 
//              create_geometry_material_state, 
//              update_geometry_material_state
//

//
// i) the test block shader storage buffer object 
//
std::size_t calc_test_block_buffer_size(const TestBlock& test_block)
{
    //
    // Introduction to the std140 storage layout
    // =========================================
    //
    // When using the "std140" storage layout, structures will be laid out in
    // buffer storage with its members stored in monotonically increasing order
    // based on their location in the declaration. A structure and each
    // structure member have a base offset and a base alignment, from which an
    // aligned offset is computed by rounding the base offset up to a multiple of
    // the base alignment. The base offset of the first member of a structure is
    // taken from the aligned offset of the structure itself. The base offset of
    // all other structure members is derived by taking the offset of the last
    // basic machine unit consumed by the previous member and adding one. Each
    // structure member is stored in memory at its aligned offset. The members
    // of a top-level shader storage block are laid out in buffer storage by treating
    // the shader storage block as a structure with a base offset of zero.
    //
    //  (1) If the member is a scalar consuming <N> basic machine units, the
    //      base alignment is <N>.
    //
    //  (2) If the member is a two- or four-component vector with components
    //      consuming <N> basic machine units, the base alignment is 2<N> or
    //      4<N>, respectively.
    //
    //  (3) If the member is a three-component vector with components consuming
    //      <N> basic machine units, the base alignment is 4<N>.
    //
    //  (4) If the member is an array of scalars or vectors, the base alignment
    //      and array stride are set to match the base alignment of a single
    //      array element, according to rules (1), (2), and (3), and rounded up
    //      to the base alignment of a vec4. The array may have padding at the
    //      end; the base offset of the member following the array is rounded up
    //      to the next multiple of the base alignment.
    //
    //  (5) If the member is a column-major matrix with <C> columns and <R>
    //      rows, the matrix is stored identically to an array of <C> column
    //      vectors with <R> components each, according to rule (4).
    //
    //  (6) If the member is an array of <S> column-major matrices with <C>
    //      columns and <R> rows, the matrix is stored identically to a row of
    //      <S>*<C> column vectors with <R> components each, according to rule
    //      (4).
    //
    //  (7) If the member is a row-major matrix with <C> columns and <R> rows,
    //      the matrix is stored identically to an array of <R> row vectors
    //      with <C> components each, according to rule (4).
    //
    //  (8) If the member is an array of <S> row-major matrices with <C> columns
    //      and <R> rows, the matrix is stored identically to a row of <S>*<R>
    //      row vectors with <C> components each, according to rule (4).
    //
    //  (9) If the member is a structure, the base alignment of the structure is
    //      <N>, where <N> is the largest base alignment value of any of its
    //      members, and rounded up to the base alignment of a vec4. The
    //      individual members of this sub-structure are then assigned offsets 
    //      by applying this set of rules recursively, where the base offset of
    //      the first member of the sub-structure is equal to the aligned offset
    //      of the structure. The structure may have padding at the end; the 
    //      base offset of the member following the sub-structure is rounded up
    //      to the next multiple of the base alignment of the structure.
    //
    //  (10) If the member is an array of <S> structures, the <S> elements of
    //       the array are laid out in order, according to rule (9).
    //
    // For shader storage blocks laid out according to these rules, the minimum buffer
    // object size returned by the GL_BUFFER_DATA_SIZE query is derived by
    // taking the offset of the last basic machine unit consumed by the last
    // entry of the shader storage block (including any end-of-array or
    // end-of-structure padding), adding one, and rounding up to the next
    // multiple of the base alignment required for a vec4.
    //
    // Using Standard Layout Qualifiers
    // ================================
    // When you group a number of variables in a uniform buffer or shader
    // storage buffer, and want to read or write their values outside a shader, you
    // need to know the offset of each one. You can query these offsets, but for
    // large collections of uniforms this process requires many queries and is
    // cumbersome. As an alternative, the standard layout qualifiers request that
    // the GLSL shader compiler organize the variables according to a set of rules,
    // where you can predictably compute the offset of any member in the block.
    // In order to qualify a block to use the std140 layout, you need to add a
    // layout directive to its declaration, as demonstrated below:
    //
    //     layout (std140) buffer UniformBlock {
    //         // declared variables
    //     };
    //
    // This std140 qualification also works for shader storage buffer objects. 
    //
    // To use these, the offset of a member in the block is the accumulated total
    // of the alignment and sizes of the previous members in the block (those
    // declared before the variable in question), bumped up to the alignment of
    // the member. The starting offset of the first member is always zero.
    //
    // The std140 Layout Rules
    // =======================
    // The set of rules shown in the table are used by the GLSL compiler to place
    // members in an std140-qualified uniform block. This feature is available
    // only with GLSL Version 1.40 or greater.
    //
    // Variable Type                           Variable Size and Alignment
    // --------------------------------------------------------------------------------
    // Scalar bool, int, uint, float and       Both the size and alignment are the size
    // double                                  of the scalar in basic machine types
    //                                         (e.g., sizeof(GLfloat)).
    //
    // Two-component vectors (e.g., ivec2)     Both the size and alignment are twice
    //                                         the size of the underlying scalar type.
    //
    // Three-component vectors (e.g., vec3)    Both the size and alignment are four
    // and                                     times the size of the underlying scalar
    // Four-component vectors (e.g., vec4)     type.
    //
    // An array of scalars or vectors          The size of each element in the array
    //                                         will be the size of the element type,
    //                                         rounded up to a multiple of the size of a
    //                                         vec4. This is also the array’s alignment.
    //                                         The array’s size will be this rounded-up
    //                                         element’s size times the number of
    //                                         elements in the array.
    //
    // A column-major matrix or an array       Same layout as an array of N vectors
    // of column-major matrices of size C      each with R components, where N is
    // columns and R rows                      the total number of columns present.
    //
    // A row-major matrix or an array of       Same layout as an array of N vectors
    // row-major matrices with R rows and C    each with C components, where N is
    // columns                                 the total number of rows present.
    //
    // A single-structure definition,          Structure alignment will be
    // or an array of structures               the alignment for the biggest structure
    //                                         member, according to the previous
    //                                         rules, rounded up to a multiple of the
    //                                         size of a vec4. Each structure will start
    //                                         on this alignment, and its size will be the
    //                                         space needed by its members, according
    //                                         to the previous rules, rounded up to
    //                                         a multiple of the structure alignment.
    //

    std::size_t ao = 0; // aligned offset
    std::size_t bo = 0; // base offset
                                                                // layout(std140) uniform Example
                                                                // {
                                                                //                    // Base types below consume 4 basic machine units
                                                                //                    //
                                                                //                    //       base   base  align
                                                                //                    // rule  align  off.  off.  bytes used
                                                                //                    // ----  ------ ----  ----  -----------------------
    ao = align_offset( 4, bo); bo = ao + sizeof(OSG::Real32);   //   Real32 a;        //  1       4     0    0    0..3
    ao = align_offset( 8, bo); bo = ao + sizeof(OSG::Vec2f);    //   Vec2f b;         //  2       8     4    8    8..15
    ao = align_offset(16, bo); bo = ao + sizeof(OSG::Vec3f);    //   Vec3f c;         //  3      16    16   16    16..27
    ao = align_offset(16, bo); bo = ao;                         //   struct {         //  9      16    28   32    (align begin)
    ao = align_offset( 4, bo); bo = ao + sizeof(OSG::Int32);    //     Int32 d;       //  1       4    32   32    32..35
    ao = align_offset( 8, bo); bo = ao + 2*sizeof(OSG::Int32);  //     Vec2b e;       //  2       8    36   40    40..47
    ao = align_offset(16, bo); bo = ao;                         //   } f;             //  9      16    48   48    (pad end)
    ao = align_offset( 4, bo); bo = ao + sizeof(OSG::Real32);   //   Real32 g;        //  1       4    48   48    48..51
    ao = align_offset(16, bo); bo = ao + sizeof(OSG::Real32);   //   Real32 h[2];     //  4      16    52   64    64..67 (h[0])
    ao = align_offset(16, bo); bo = ao + sizeof(OSG::Real32);   //                    //         16    68   80    80..83 (h[1])
    ao = align_offset(16, bo); bo = ao;                         //                    //  4      16    84   96    (pad end of h)
    ao = align_offset(16, bo); bo = ao + sizeof(OSG::Vec3f);    //   Matrix2x3f i;    // 5/4     16    96   96    96..107 (i, column 0)
    ao = align_offset(16, bo); bo = ao + sizeof(OSG::Vec3f);    //                    //         16   108  112    112..123 (i, column 1)
    ao = align_offset(16, bo); bo = ao;                         //                    // 5/4     16   124  128    (pad end of i)
    ao = align_offset(16, bo); bo = ao;                         //   struct {         //  10     16   128  128    (align begin)
    ao = align_offset(16, bo); bo = ao + sizeof(OSG::Vec3u);    //     Vec3u j;       //  3      16   128  128    128..139 (o[0].j)
    ao = align_offset( 8, bo); bo = ao + sizeof(OSG::Vec2f);    //     Vec2f k;       //  2       8   140  144    144..151 (o[0].k)
    ao = align_offset(16, bo); bo = ao + sizeof(OSG::Real32);   //     Real32 l[2];   //  4      16   152  160    160..163 (o[0].l[0])
    ao = align_offset(16, bo); bo = ao + sizeof(OSG::Real32);   //                    //         16   164  176    176..179 (o[0].l[1])
    ao = align_offset(16, bo); bo = ao;                         //                    //  4      16   180  192    (pad end of o[0].l)
    ao = align_offset( 8, bo); bo = ao + sizeof(OSG::Vec2f);    //     Vec2f m;       //  2       8   192  192    192..199 (o[0].m)
    ao = align_offset(16, bo); bo = ao + sizeof(OSG::Vec3f);    //     Matrix3f n[2]; // 6/4     16   200  208    208..219 (o[0].n[0], column 0)
    ao = align_offset(16, bo); bo = ao + sizeof(OSG::Vec3f);    //                    //         16   220  224    224..235 (o[0].n[0], column 1)
    ao = align_offset(16, bo); bo = ao + sizeof(OSG::Vec3f);    //                    //         16   236  240    240..251 (o[0].n[0], column 2)
    ao = align_offset(16, bo); bo = ao + sizeof(OSG::Vec3f);    //                    //         16   252  256    256..267 (o[0].n[1], column 0)
    ao = align_offset(16, bo); bo = ao + sizeof(OSG::Vec3f);    //                    //         16   268  272    272..283 (o[0].n[1], column 1)
    ao = align_offset(16, bo); bo = ao + sizeof(OSG::Vec3f);    //                    //         16   284  288    288..299 (o[0].n[1], column 2)
    ao = align_offset(16, bo); bo = ao;                         //                    // 6/4     16   300  304    (pad end of o[0].n)
    ao = align_offset(16, bo); bo = ao;                         //                    //  9      16   304  304    (pad end of o[0])
    ao = align_offset(16, bo); bo = ao + sizeof(OSG::Vec3u);    //                    //  3      16   304  304    304..315 (o[1].j)
    ao = align_offset( 8, bo); bo = ao + sizeof(OSG::Vec2f);    //                    //  2       8   316  320    320..327 (o[1].k)
    ao = align_offset(16, bo); bo = ao + sizeof(OSG::Real32);   //                    //  4      16   328  336    336..339 (o[1].l[0])
    ao = align_offset(16, bo); bo = ao + sizeof(OSG::Real32);   //                    //         16   340  352    352..355 (o[1].l[1])
    ao = align_offset(16, bo); bo = ao;                         //                    //  4      16   356  368    (pad end of o[1].l)
    ao = align_offset( 8, bo); bo = ao + sizeof(OSG::Vec2f);    //                    //  2       8   368  368    368..375 (o[1].m)
    ao = align_offset(16, bo); bo = ao + sizeof(OSG::Vec3f);    //                    // 6/4     16   376  384    384..395 (o[1].n[0], column 0)
    ao = align_offset(16, bo); bo = ao + sizeof(OSG::Vec3f);    //                    //         16   396  400    400..411 (o[1].n[0], column 1)
    ao = align_offset(16, bo); bo = ao + sizeof(OSG::Vec3f);    //                    //         16   412  416    416..427 (o[1].n[0], column 2)
    ao = align_offset(16, bo); bo = ao + sizeof(OSG::Vec3f);    //                    //         16   428  432    432..443 (o[1].n[1], column 0)
    ao = align_offset(16, bo); bo = ao + sizeof(OSG::Vec3f);    //                    //         16   444  448    448..459 (o[1].n[1], column 1)
    ao = align_offset(16, bo); bo = ao + sizeof(OSG::Vec3f);    //                    //         16   460  464    464..475 (o[1].n[1], column 2)
    ao = align_offset(16, bo); bo = ao;                         //                    // 6/4     16   476  480    (pad end of o[1].n)
    ao = align_offset(16, bo); bo = ao;                         //                    //  9      16   480  480    (pad end of o[1])
                                                                //   } o[2];
                                                                // };
    return ao;
}

std::vector<OSG::UInt8> create_test_block_buffer(const TestBlock& test_block)
{
    std::size_t size = calc_test_block_buffer_size(test_block);

    std::vector<OSG::UInt8> buffer(size);

    std::size_t ao = 0; // aligned offset
    std::size_t bo = 0; // base offset

    ao = align_offset( 4, bo);
    *(reinterpret_cast<OSG::Real32*>(&buffer[0] + ao)) = test_block.a;
    bo = ao + sizeof(OSG::Real32);
    
    ao = align_offset( 8, bo);
    memcpy(&buffer[0] + ao, &test_block.b[0], sizeof(OSG::Vec2f));
    bo = ao + sizeof(OSG::Vec2f);
    
    ao = align_offset(16, bo);
    memcpy(&buffer[0] + ao, &test_block.c[0], sizeof(OSG::Vec3f));
    bo = ao + sizeof(OSG::Vec3f);
    
    ao = align_offset(16, bo);
    bo = ao;
    
    ao = align_offset( 4, bo);
    *(reinterpret_cast<OSG::Int32*>(&buffer[0] + ao)) = test_block.f.d;
    bo = ao + sizeof(OSG::Int32);
    
    ao = align_offset( 8, bo);
    *(reinterpret_cast<OSG::Int32*>(&buffer[0] + ao)) = test_block.f.e[0];
    bo = ao + sizeof(OSG::Int32);
    ao = bo;
    *(reinterpret_cast<OSG::Int32*>(&buffer[0] + ao)) = test_block.f.e[1];
    bo = ao + sizeof(OSG::Int32);
    
    ao = align_offset(16, bo);
    bo = ao;
    
    ao = align_offset( 4, bo);
    *(reinterpret_cast<OSG::Real32*>(&buffer[0] + ao)) = test_block.g;
    bo = ao + sizeof(OSG::Real32);
    
    ao = align_offset(16, bo);
    *(reinterpret_cast<OSG::Real32*>(&buffer[0] + ao)) = test_block.h[0];
    bo = ao + sizeof(OSG::Real32);
    
    ao = align_offset(16, bo);
    *(reinterpret_cast<OSG::Real32*>(&buffer[0] + ao)) = test_block.h[1];
    bo = ao + sizeof(OSG::Real32);
    
    ao = align_offset(16, bo);
    bo = ao;
    
    ao = align_offset(16, bo);
    memcpy(&buffer[0] + ao, &test_block.i.row1[0], sizeof(OSG::Vec3f));
    bo = ao + sizeof(OSG::Vec3f);
    
    ao = align_offset(16, bo);
    memcpy(&buffer[0] + ao, &test_block.i.row2[0], sizeof(OSG::Vec3f));
    bo = ao + sizeof(OSG::Vec3f);
    
    ao = align_offset(16, bo);
    bo = ao;
    
    ao = align_offset(16, bo);
    bo = ao;
    
    ao = align_offset(16, bo);
    memcpy(&buffer[0] + ao, &test_block.o[0].j[0], sizeof(OSG::Vec3u));
    bo = ao + sizeof(OSG::Vec3u);
    
    ao = align_offset( 8, bo);
    memcpy(&buffer[0] + ao, &test_block.o[0].k[0], sizeof(OSG::Vec2f));
    bo = ao + sizeof(OSG::Vec2f);
    
    ao = align_offset(16, bo);
    *(reinterpret_cast<OSG::Real32*>(&buffer[0] + ao)) = test_block.o[0].l[0];
    bo = ao + sizeof(OSG::Real32);
    
    ao = align_offset(16, bo);
    *(reinterpret_cast<OSG::Real32*>(&buffer[0] + ao)) = test_block.o[0].l[1];
    bo = ao + sizeof(OSG::Real32);
    
    ao = align_offset(16, bo);
    bo = ao;
    
    ao = align_offset( 8, bo);
    memcpy(&buffer[0] + ao, &test_block.o[0].m[0], sizeof(OSG::Vec2f));
    bo = ao + sizeof(OSG::Vec2f);
    
    ao = align_offset(16, bo);
    memcpy(&buffer[0] + ao, &test_block.o[0].n[0].row1[0], sizeof(OSG::Vec3f));
    bo = ao + sizeof(OSG::Vec3f);
    
    ao = align_offset(16, bo);
    memcpy(&buffer[0] + ao, &test_block.o[0].n[0].row2[0], sizeof(OSG::Vec3f));
    bo = ao + sizeof(OSG::Vec3f);
    
    ao = align_offset(16, bo);
    memcpy(&buffer[0] + ao, &test_block.o[0].n[0].row3[0], sizeof(OSG::Vec3f));
    bo = ao + sizeof(OSG::Vec3f);
    
    ao = align_offset(16, bo);
    memcpy(&buffer[0] + ao, &test_block.o[0].n[1].row1[0], sizeof(OSG::Vec3f));
    bo = ao + sizeof(OSG::Vec3f);
    
    ao = align_offset(16, bo);
    memcpy(&buffer[0] + ao, &test_block.o[0].n[1].row2[0], sizeof(OSG::Vec3f));
    bo = ao + sizeof(OSG::Vec3f);
    
    ao = align_offset(16, bo);
    memcpy(&buffer[0] + ao, &test_block.o[0].n[1].row3[0], sizeof(OSG::Vec3f));
    bo = ao + sizeof(OSG::Vec3f);
    
    ao = align_offset(16, bo);
    bo = ao;
    
    ao = align_offset(16, bo);
    bo = ao;
    
    ao = align_offset(16, bo);
    memcpy(&buffer[0] + ao, &test_block.o[1].j[0], sizeof(OSG::Vec3u));
    bo = ao + sizeof(OSG::Vec3u);
    
    ao = align_offset( 8, bo);
    memcpy(&buffer[0] + ao, &test_block.o[1].k[0], sizeof(OSG::Vec2f));
    bo = ao + sizeof(OSG::Vec2f);
    
    ao = align_offset(16, bo);
    *(reinterpret_cast<OSG::Real32*>(&buffer[0] + ao)) = test_block.o[1].l[0];
    bo = ao + sizeof(OSG::Real32);
    
    ao = align_offset(16, bo);
    *(reinterpret_cast<OSG::Real32*>(&buffer[0] + ao)) = test_block.o[1].l[1];
    bo = ao + sizeof(OSG::Real32);
    
    ao = align_offset(16, bo);
    bo = ao;
    
    ao = align_offset( 8, bo);
    memcpy(&buffer[0] + ao, &test_block.o[1].m[0], sizeof(OSG::Vec2f));
    bo = ao + sizeof(OSG::Vec2f);
    
    ao = align_offset(16, bo);
    memcpy(&buffer[0] + ao, &test_block.o[1].n[0].row1[0], sizeof(OSG::Vec3f));
    bo = ao + sizeof(OSG::Vec3f);
    
    ao = align_offset(16, bo);
    memcpy(&buffer[0] + ao, &test_block.o[1].n[0].row2[0], sizeof(OSG::Vec3f));
    bo = ao + sizeof(OSG::Vec3f);
    
    ao = align_offset(16, bo);
    memcpy(&buffer[0] + ao, &test_block.o[1].n[0].row3[0], sizeof(OSG::Vec3f));
    bo = ao + sizeof(OSG::Vec3f);
    
    ao = align_offset(16, bo);
    memcpy(&buffer[0] + ao, &test_block.o[1].n[1].row1[0], sizeof(OSG::Vec3f));
    bo = ao + sizeof(OSG::Vec3f);
    
    ao = align_offset(16, bo);
    memcpy(&buffer[0] + ao, &test_block.o[1].n[1].row2[0], sizeof(OSG::Vec3f));
    bo = ao + sizeof(OSG::Vec3f);
    
    ao = align_offset(16, bo);
    memcpy(&buffer[0] + ao, &test_block.o[1].n[1].row3[0], sizeof(OSG::Vec3f));
    bo = ao + sizeof(OSG::Vec3f);
    
    ao = align_offset(16, bo);
    bo = ao;
    
    ao = align_offset(16, bo);
    bo = ao;

    return buffer;
}

OSG::ShaderStorageBufferObjStdLayoutChunkTransitPtr create_test_block_state(const TestBlock& test_block)
{
    OSG::ShaderStorageBufferObjStdLayoutChunkRefPtr ssbo = OSG::ShaderStorageBufferObjStdLayoutChunk::create();

    std::vector<OSG::UInt8> buffer = create_test_block_buffer(test_block);

    ssbo->editMFBuffer()->setValues(buffer);
    ssbo->setUsage(GL_DYNAMIC_DRAW);

    return OSG::ShaderStorageBufferObjStdLayoutChunkTransitPtr(ssbo);
}

void update_test_block_state(OSG::ShaderStorageBufferObjStdLayoutChunk* ssbo, const TestBlock& test_block)
{
    if (ssbo) {
        std::vector<OSG::UInt8> buffer = create_test_block_buffer(test_block);
        ssbo->editMFBuffer()->setValues(buffer);
    }
}

//
// ii) the light shader storage buffer object 
//
std::size_t calc_light_buffer_size(const VecLightsT& vLights)
{
    std::size_t ao = 0; // aligned offset
    std::size_t bo = 0; // base offset

    ao = align_offset( 16, bo); bo = ao + sizeof(OSG::Pnt4f);   // OSG::Pnt3f   position;
    ao = align_offset( 16, bo); bo = ao + sizeof(OSG::Vec4f);   // OSG::Vec3f   spot_direction;
    ao = align_offset( 16, bo); bo = ao + sizeof(OSG::Color4f); // OSG::Color3f Ia;
    ao = align_offset( 16, bo); bo = ao + sizeof(OSG::Color4f); // OSG::Color3f Id;
    ao = align_offset( 16, bo); bo = ao + sizeof(OSG::Color4f); // OSG::Color3f Is;
    ao = align_offset( 16, bo); bo = ao + sizeof(OSG::Vec4f);   // OSG::Vec3f   attenuation;
    ao = align_offset(  4, bo); bo = ao + sizeof(OSG::Real32);  // OSG::Real32  spot_cos_cutoff;
    ao = align_offset(  4, bo); bo = ao + sizeof(OSG::Real32);  // OSG::Real32  spot_exponent;
    ao = align_offset(  4, bo); bo = ao + sizeof(OSG::Int32);   // OSG::Int32   type;
    ao = align_offset( 16, bo); bo = ao;                        // padding

    ao *= vLights.size();       bo = ao;                        // array
    ao = align_offset( 16, bo); bo = ao;                        // padding

    return ao;
}

std::vector<OSG::UInt8> create_light_buffer(const VecLightsT& vLights)
{
    std::size_t size = calc_light_buffer_size(vLights);

    std::vector<OSG::UInt8> buffer(size);

    std::size_t ao = 0; // aligned offset
    std::size_t bo = 0; // base offset

    for (std::size_t i = 0; i < vLights.size(); ++i)
    {
        OSG::Pnt3f position_es       = transform_to_eye_space(vLights[i].position,       mgr);
        OSG::Vec3f spot_direction_es = transform_to_eye_space(vLights[i].spot_direction, mgr);

        ao = align_offset(16, bo);
        memcpy(&buffer[0] + ao, &position_es[0], sizeof(OSG::Pnt3f));
        bo = ao + sizeof(OSG::Pnt4f);

        ao = align_offset(16, bo);
        memcpy(&buffer[0] + ao, &spot_direction_es[0], sizeof(OSG::Vec3f));
        bo = ao + sizeof(OSG::Vec4f);

        ao = align_offset(16, bo);
        memcpy(&buffer[0] + ao, &vLights[i].Ia[0], sizeof(OSG::Color3f));
        bo = ao + sizeof(OSG::Color4f);

        ao = align_offset(16, bo);
        memcpy(&buffer[0] + ao, &vLights[i].Id[0], sizeof(OSG::Color3f));
        bo = ao + sizeof(OSG::Color4f);

        ao = align_offset(16, bo);
        memcpy(&buffer[0] + ao, &vLights[i].Is[0], sizeof(OSG::Color3f));
        bo = ao + sizeof(OSG::Color4f);

        ao = align_offset(16, bo);
        memcpy(&buffer[0] + ao, &vLights[i].attenuation[0], sizeof(OSG::Vec3f));
        bo = ao + sizeof(OSG::Vec4f);

        ao = align_offset( 4, bo);
        *(reinterpret_cast<OSG::Real32*>(&buffer[0] + ao)) = vLights[i].spot_cos_cutoff;
        bo = ao + sizeof(OSG::Real32);

        ao = align_offset( 4, bo);
        *(reinterpret_cast<OSG::Real32*>(&buffer[0] + ao)) = vLights[i].spot_exponent;
        bo = ao + sizeof(OSG::Real32);

        ao = align_offset( 4, bo);
        *(reinterpret_cast<OSG::Int32*>(&buffer[0] + ao)) = vLights[i].type;
        bo = ao + sizeof(OSG::Int32);

        ao = align_offset( 16, bo); bo = ao;    // padding
    }

    return buffer;
}

OSG::ShaderStorageBufferObjStdLayoutChunkTransitPtr create_light_state(const VecLightsT& vLights)
{
    OSG::ShaderStorageBufferObjStdLayoutChunkRefPtr ssbo = OSG::ShaderStorageBufferObjStdLayoutChunk::create();

    std::vector<OSG::UInt8> buffer = create_light_buffer(vLights);

    ssbo->editMFBuffer()->setValues(buffer);
    ssbo->setUsage(GL_DYNAMIC_DRAW);

    return OSG::ShaderStorageBufferObjStdLayoutChunkTransitPtr(ssbo);
}

void update_light_state(OSG::ShaderStorageBufferObjStdLayoutChunk* ssbo, const VecLightsT& vLights)
{
    if (ssbo) {
        std::vector<OSG::UInt8> buffer = create_light_buffer(vLights);
        ssbo->editMFBuffer()->setValues(buffer);
    }
}

//
// iii) the material shader storage buffer object
//
std::size_t calc_material_database_buffer_size(const VecMaterialsT& vMaterials)
{
    std::size_t ao = 0; // aligned offset
    std::size_t bo = 0; // base offset

    ao = align_offset( 16, bo); bo = ao + sizeof(OSG::Color4f); // OSG::Color3f ambient;
    ao = align_offset( 16, bo); bo = ao + sizeof(OSG::Color4f); // OSG::Color3f diffuse;
    ao = align_offset( 16, bo); bo = ao + sizeof(OSG::Color4f); // OSG::Color3f specular;
    ao = align_offset( 16, bo); bo = ao + sizeof(OSG::Color4f); // OSG::Color3f emissive;
    ao = align_offset(  4, bo); bo = ao + sizeof(OSG::Real32);  // OSG::Real32  opacity;
    ao = align_offset(  4, bo); bo = ao + sizeof(OSG::Real32);  // OSG::Real32  shininess;
    ao = align_offset( 16, bo); bo = ao;                        // padding

    ao *= vMaterials.size();    bo = ao;                        // array
    ao = align_offset( 16, bo); bo = ao;                        // padding

    return ao;
}

std::vector<OSG::UInt8> create_material_database_buffer(const VecMaterialsT& vMaterials)
{
    std::size_t size = calc_material_database_buffer_size(vMaterials);

    std::vector<OSG::UInt8> buffer(size);

    std::size_t ao = 0; // aligned offset
    std::size_t bo = 0; // base offset

    for (std::size_t i = 0; i < vMaterials.size(); ++i)
    {
        ao = align_offset(16, bo);
        memcpy(&buffer[0] + ao, &vMaterials[i].ambient[0], sizeof(OSG::Color3f));
        bo = ao + sizeof(OSG::Color4f);

        ao = align_offset(16, bo);
        memcpy(&buffer[0] + ao, &vMaterials[i].diffuse[0], sizeof(OSG::Color3f));
        bo = ao + sizeof(OSG::Color4f);

        ao = align_offset(16, bo);
        memcpy(&buffer[0] + ao, &vMaterials[i].specular[0], sizeof(OSG::Color3f));
        bo = ao + sizeof(OSG::Color4f);

        ao = align_offset(16, bo);
        memcpy(&buffer[0] + ao, &vMaterials[i].emissive[0], sizeof(OSG::Color3f));
        bo = ao + sizeof(OSG::Color4f);

        ao = align_offset( 4, bo);
        *(reinterpret_cast<OSG::Real32*>(&buffer[0] + ao)) = vMaterials[i].opacity;
        bo = ao + sizeof(OSG::Real32);

        ao = align_offset( 4, bo);
        *(reinterpret_cast<OSG::Real32*>(&buffer[0] + ao)) = vMaterials[i].shininess;
        bo = ao + sizeof(OSG::Real32);

        ao = align_offset( 16, bo); bo = ao;    // padding
    }

    return buffer;
}

OSG::ShaderStorageBufferObjStdLayoutChunkTransitPtr create_material_database_state(const VecMaterialsT& vMaterials)
{
    OSG::ShaderStorageBufferObjStdLayoutChunkRefPtr ssbo = OSG::ShaderStorageBufferObjStdLayoutChunk::create();

    std::vector<OSG::UInt8> buffer = create_material_database_buffer(vMaterials);

    ssbo->editMFBuffer()->setValues(buffer);
    ssbo->setUsage(GL_STATIC_DRAW);

    return OSG::ShaderStorageBufferObjStdLayoutChunkTransitPtr(ssbo);
}

void update_material_database_state(OSG::ShaderStorageBufferObjStdLayoutChunk* ssbo, const VecMaterialsT& vMaterials)
{
    if (ssbo) {
        std::vector<OSG::UInt8> buffer = create_material_database_buffer(vMaterials);
        ssbo->editMFBuffer()->setValues(buffer);
    }
}

//
// iv) the geomertry shader storage buffer object
//
std::size_t calc_geometry_material_buffer_size()
{
    std::size_t ao = 0; // aligned offset
    std::size_t bo = 0; // base offset

    ao = align_offset(  4, bo); bo = ao + sizeof(OSG::UInt32);  // OSG::UInt32  material_index;
    ao = align_offset( 16, bo); bo = ao;                        // padding

    return ao;
}

std::vector<OSG::UInt8> create_geometry_material_buffer(const GeomState& geom_state)
{
    std::size_t size = calc_geometry_material_buffer_size();

    std::vector<OSG::UInt8> buffer(size);

    std::size_t ao = 0; // aligned offset
    std::size_t bo = 0; // base offset

    ao = align_offset( 4, bo);
    *(reinterpret_cast<OSG::UInt32*>(&buffer[0] + ao)) = geom_state.material_index;
    bo = ao + sizeof(OSG::UInt32);

    return buffer;
}

OSG::ShaderStorageBufferObjStdLayoutChunkTransitPtr create_geometry_material_state(const GeomState& geom_state)
{
    OSG::ShaderStorageBufferObjStdLayoutChunkRefPtr ssbo = OSG::ShaderStorageBufferObjStdLayoutChunk::create();

    std::vector<OSG::UInt8> buffer = create_geometry_material_buffer(geom_state);

    ssbo->editMFBuffer()->setValues(buffer);
    ssbo->setUsage(GL_DYNAMIC_DRAW);

    return OSG::ShaderStorageBufferObjStdLayoutChunkTransitPtr(ssbo);
}

void update_geometry_material_state(OSG::ShaderStorageBufferObjStdLayoutChunk* ssbo, const GeomState& geom_state)
{
    if (ssbo) {
        std::vector<OSG::UInt8> buffer = create_geometry_material_buffer(geom_state);
        ssbo->editMFBuffer()->setValues(buffer);
    }
}

//
// Part IV: The application starts here
//

//
// vertex shader program.
//
std::string get_vp_program();

//
// fragment shader program for bump mapping in surface local coordinates
//
std::string get_fp_program();

//
// random number generator
//
boost::random::mt19937  generator;
boost::random::uniform_int_distribution<> dist(0, num_materials-1);

//
// a separate transformation for every object
//
OSG::TransformRefPtr cyltrans, tortrans;

//
// Shader Storage buffer objects corresponding to transient shader blocks
//
OSG::ShaderStorageBufferObjStdLayoutChunkRefPtr ssbo_light_state  = NULL;
OSG::ShaderStorageBufferObjStdLayoutChunkRefPtr ssbo_geom_state_1 = NULL;
OSG::ShaderStorageBufferObjStdLayoutChunkRefPtr ssbo_geom_state_2 = NULL;

//
// forward declaration so we can have the interesting stuff upfront
//
int setupGLUT(int *argc, char *argv[]);

//
// redraw the window
//
void display(void)
{
    // light spot direction and light position must be provided in eye space
    update_light_state(ssbo_light_state, lights);

    // create the matrix
    OSG::Matrix m;
    OSG::Real32 t = glutGet(GLUT_ELAPSED_TIME );
    
    // set the transforms' matrices
    m.setTransform(OSG::Vec3f(0, 0, OSG::osgSin(t / 1000.f) * 1.5),
                   OSG::Quaternion( OSG::Vec3f (1, 0, 0), t / 500.f));

    cyltrans->setMatrix(m);
    
    m.setTransform(OSG::Vec3f(OSG::osgSin(t / 1000.f), 0, 0),
                   OSG::Quaternion( OSG::Vec3f (0, 0, 1), t / 1000.f));

    tortrans->setMatrix(m);

    OSG::commitChanges();
    
    mgr->redraw();
}

//
// Initialize GLUT & OpenSG and set up the scene
//
int main(int argc, char **argv)
{
    // OSG init
    OSG::osgInit(argc,argv);

    // GLUT init
    int winid = setupGLUT(&argc, argv);

    // open a new scope, because the pointers below should go out of scope
    // before entering glutMainLoop.
    // Otherwise OpenSG will complain about objects being alive after shutdown.
    {
        // the connection between GLUT and OpenSG
        OSG::GLUTWindowRefPtr gwin = OSG::GLUTWindow::create();
        gwin->setGlutId(winid);
        gwin->init();
    
        // create the SimpleSceneManager helper
        mgr = OSG::SimpleSceneManager::create();
        mgr->setWindow(gwin);

        // create a pretty simple graph: a Group with two Transforms as children,
        // each of which carries a single Geometry.
        
        // The scene
        
        OSG::NodeRefPtr  scene = OSG::Node::create();
        
        // The cylinder and its transformation
        OSG::NodeRefPtr     cyl    = OSG::Node::create();
        OSG::GeometryRefPtr cylgeo = OSG::makeCylinderGeo( 1.4f, .3f, 24, 
                                                           true, true, true );
        
        cyl->setCore(cylgeo);
    
        cyltrans = OSG::Transform::create();
    
        OSG::NodeRefPtr cyltransnode = OSG::Node::create();
        cyltransnode->setCore (cyltrans);
        cyltransnode->addChild(cyl     );
        
        // add it to the scene
        scene->addChild(cyltransnode);
        
        // The torus and its transformation
        OSG::NodeRefPtr     torus    = OSG::Node::create();
        OSG::GeometryRefPtr torusgeo = OSG::makeTorusGeo( .2f, 1, 24, 36 );
        
        torus->setCore(torusgeo);
            
        tortrans = OSG::Transform::create();
    
        OSG::NodeRefPtr tortransnode = OSG::Node::create();
        tortransnode->setCore (tortrans);
        tortransnode->addChild(torus   );
        
        // add it to the scene
        scene->addChild(tortransnode);

        //
        // create the shader program
        //
        OSG::ShaderProgramChunkRefPtr prog_chunk = OSG::ShaderProgramChunk::create();
        OSG::ShaderProgramRefPtr      vertShader = OSG::ShaderProgram::createVertexShader();
        OSG::ShaderProgramRefPtr      fragShader = OSG::ShaderProgram::createFragmentShader();

        vertShader->setProgram(get_vp_program());
        fragShader->setProgram(get_fp_program());

        //
        // binding the shader storage block to a buffer binding point can be performed 
        // either by calling the shaders's addShaderStorageBlock method or by
        // adding a 'buffer block' variable to a ShaderProgramVariableChunk.
        // In the following we use both variants for illustration.
        //
        fragShader->addShaderStorageBlock("Materials", 1);    // block binding point
        fragShader->addShaderStorageBlock("Lights",    2);    // block binding point

        //
        // The following is replaced by adding ShaderProgramVariableChunk objects
        // to the chunk material. See below...
        //
        // fragShader->addShaderStorageBlock("GeomState", 3);    // block binding point

        fragShader->addShaderStorageBlock("TestBlock", 4);    // block binding point

        prog_chunk->addShader(vertShader);
        prog_chunk->addShader(fragShader);

        //
        // create shader storage buffer objects and corresponding materials
        //
        OSG::ShaderStorageBufferObjStdLayoutChunkRefPtr ssbo_material_database = create_material_database_state(materials);
                                                        ssbo_light_state       = create_light_state(lights);

        OSG::ShaderStorageBufferObjStdLayoutChunkRefPtr ssbo_test_block        = create_test_block_state(global_test_block);

        OSG::PolygonChunkRefPtr polygon_chunk = OSG::PolygonChunk::create();
        polygon_chunk->setFrontMode(GL_FILL);
        polygon_chunk->setBackMode(GL_FILL);
        polygon_chunk->setCullFace(GL_NONE);

        OSG::DepthChunkRefPtr depth_chunk = OSG::DepthChunk::create();
        depth_chunk->setEnable(true);

        OSG::ChunkMaterialRefPtr prog_state = OSG::ChunkMaterial::create();
        prog_state->addChunk(ssbo_material_database, 1);  // buffer binding point 1
        prog_state->addChunk(ssbo_light_state,       2);  // buffer binding point 2
        prog_state->addChunk(ssbo_test_block,        4);  // buffer binding point 4
        prog_state->addChunk(prog_chunk);
        prog_state->addChunk(polygon_chunk);
        prog_state->addChunk(depth_chunk);

        OSG::ShaderProgramVariableChunkRefPtr shader_var_chunk = OSG::ShaderProgramVariableChunk::create();
        shader_var_chunk->addShaderStorageBlock("GeomState", 3);

        GeomState geom1; geom1.material_index = dist(generator);
        OSG::ChunkMaterialRefPtr geom1_state = OSG::ChunkMaterial::create();
        ssbo_geom_state_1 = create_geometry_material_state(geom1);
        geom1_state->addChunk(ssbo_geom_state_1, 3);    // buffer binding point 3
        geom1_state->addChunk(shader_var_chunk);        // block binding point

        GeomState geom2; geom2.material_index = dist(generator);
        OSG::ChunkMaterialRefPtr geom2_state = OSG::ChunkMaterial::create();
        ssbo_geom_state_2 = create_geometry_material_state(geom2);
        geom2_state->addChunk(ssbo_geom_state_2, 3);    // buffer binding point 3
        geom2_state->addChunk(shader_var_chunk);        // block binding point
       
        cylgeo  ->setMaterial(geom1_state);
        torusgeo->setMaterial(geom2_state);

        OSG::MaterialChunkOverrideGroupRefPtr mgrp = OSG::MaterialChunkOverrideGroup::create();
        mgrp->setMaterial(prog_state);
        scene->setCore(mgrp);

        OSG::commitChanges();
    
        mgr->setRoot(scene);
    
        // show the whole scene
        mgr->showAll();
    }

    // GLUT main loop
    glutMainLoop();

    return 0;
}

//
// GLUT callback functions
//

//
// react to size changes
//
void reshape(int w, int h)
{
    mgr->resize(w, h);
    glutPostRedisplay();
}

//
// react to mouse button presses
//
void mouse(int button, int state, int x, int y)
{
    if (state)
        mgr->mouseButtonRelease(button, x, y);
    else
        mgr->mouseButtonPress(button, x, y);
        
    glutPostRedisplay();
}

//
// react to mouse motions with pressed buttons
//
void motion(int x, int y)
{
    mgr->mouseMove(x, y);
    glutPostRedisplay();
}

//
// react to keys
//
void keyboard(unsigned char k, int x, int y)
{
    switch(k)
    {
        case 27:    
        {
            // clean up global variables
            cyltrans = NULL;
            tortrans = NULL;
            mgr      = NULL;

            ssbo_light_state  = NULL;
            ssbo_geom_state_1 = NULL;
            ssbo_geom_state_2 = NULL;

            OSG::osgExit();
            exit(0);
        }
        break;

        case 'm':
        {
            GeomState geom1; geom1.material_index = dist(generator);
            GeomState geom2; geom2.material_index = dist(generator);

            update_geometry_material_state(ssbo_geom_state_1, geom1);
            update_geometry_material_state(ssbo_geom_state_2, geom2);

            glutPostRedisplay();
        }
        break;

        case 's':
        {
            mgr->setStatistics(!mgr->getStatistics());
        }
        break;
    }
}

//
// setup the GLUT library which handles the windows for us
//
int setupGLUT(int *argc, char *argv[])
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    
    int winid = glutCreateWindow("OpenSG");
    
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);

    // call the redraw function whenever there's nothing else to do
    glutIdleFunc(display);

    return winid;
}

//
// Part V: The shader programs
//

//
// vertex shader program.
//
std::string get_vp_program()
{
    std::string vp_program =
            "\n"
            "#version 440 compatibility\n"
            "\n"
            "#extension GL_ARB_separate_shader_objects:      enable\n"
            "#extension GL_ARB_shader_storage_buffer_object: enable\n"
            "\n"
            "smooth out vec3 vNormalES;        // eye space normal\n"
            "smooth out vec3 vPositionES;      // eye space position\n"
            "\n"
            "void main()\n"
            "{\n"
            "    //\n"
            "    // multiply the object space vertex position with the modelview matrix \n"
            "    // to get the eye space vertex position\n"
            "    //\n"
            "    vPositionES = (gl_ModelViewMatrix * gl_Vertex).xyz;\n"
            "\n"
            "    //\n"
            "    // multiply the object space normal with the normal matrix (transpose of the inverse \n"
            "    // model view matrix) to get the eye space normal\n"
            "    //\n"
            "    vNormalES = gl_NormalMatrix * gl_Normal;\n"
            "\n"
            "    //\n"
            "    // multiply the combiend modelview projection matrix with the object space vertex\n"
            "    // position to get the clip space position\n"
            "    //\n"
            "    gl_Position = ftransform();\n"
            "}\n"
            "\n"
            ;
    return vp_program;
}

//
// fragment shader program for bump mapping in surface local coordinates
//
std::string get_fp_program()
{
    std::string fp_program =
            "\n"
            "#version 440 compatibility\n"
            "\n"
            "#extension GL_ARB_separate_shader_objects:      enable\n"
            "#extension GL_ARB_shader_storage_buffer_object: enable\n"
            "\n"
            "smooth in vec3 vNormalES;         // eye space normal\n"
            "smooth in vec3 vPositionES;       // eye space position\n"
            "\n"
            "const int num_lights    =    1;\n"
            "const int num_materials = 5000;\n"
            "\n"
            "const int directional_light = 0;\n"
            "const int point_light = 1;\n"
            "const int spot_light = 2;\n"
            "const int no_light = 3;\n"
            "\n"
            "struct Light\n"
            "{\n"
            "    vec4 position;          // in eye space\n"
            "    vec4 spot_direction;    // in eye space\n"
            "\n"
            "    vec4 Ia;                // ambient  max. Intensity\n"
            "    vec4 Id;                // diffuse  max. Intensity\n"
            "    vec4 Is;                // specular max. Intensity\n"
            "\n"
            "    vec4 attenuation;       // (constant, linear, quadratic) with constant >= 1 and linear,quadratic >= 0\n"
            "    \n"
            "    float spot_cos_cutoff;  // cosine cut of angle\n"
            "\n"
            "    float spot_exponent;    // [0-128]\n"
            "    int  type;              // directional_light, point_light, spot_light, no_light\n"
            "};\n"
            "\n"
            "layout (std140) buffer Lights\n"
            "{\n"
            "    Light light[num_lights];\n"
            "} lights;\n"
            "\n"
            "struct Material\n"
            "{\n"
            "    vec4 ambient;\n"
            "    vec4 diffuse;\n"
            "    vec4 specular;\n"
            "    vec4 emissive;\n"
            "\n"
            "    float opacity;\n"
            "    float shininess;\n"
            "};\n"
            "\n"
            "layout (std140) buffer Materials\n"
            "{\n"
            "    Material material[num_materials];\n"
            "} materials;\n"
            "\n"
            "\n"
            "layout (std140) buffer GeomState\n"
            "{\n"
            "    int material_index;\n"
            "} geom_state;\n"
            "\n"
            "const vec3 cCameraPositionES = vec3(0,0,0); // eye is at vec3(0,0,0) in eye space!\n"
            "\n"
            "layout(location = 0) out vec4 vFragColor;\n"
            "\n"
            "//\n"
            "// The test block from the GL_ARB_uniform_buffer_object\n"
            "// specification. \n"
            "//\n"
            "struct S0\n"
            "{\n"
            "    int d;\n"
            "    bvec2 e;\n"
            "};\n"
            "\n"
            "struct S1\n"
            "{\n"
            "    uvec3 j;\n"
            "    vec2 k;\n"
            "    float l[2];\n"
            "    vec2 m;\n"
            "    mat3 n[2];\n"
            "};\n"
            "\n"
            "layout (std140) buffer TestBlock\n"
            "{\n"
            "    float a;\n"
            "    vec2  b;\n"
            "    vec3  c;\n"
            "    S0 f;\n"
            "    float g;\n"
            "    float h[2];\n"
            "    mat2x3 i;\n"
            "    S1 o[2];\n"
            "} test_block;\n"
            "\n"
            "//\n"
            "// directional light contribution\n"
            "//\n"
            "vec3 directionalLight(\n"
            "    in int i,   // light identifier, i.e. current light\n"
            "    in int j,   // material identifier\n"
            "    in vec3 n,  // vertex normal in eye space\n"
            "    in vec3 v)  // view direction in eye space\n"
            "{\n"
            "    if (lights.light[i].type != directional_light)\n"
            "        return vec3(0.0, 0.0, 0.0);\n"
            "\n"
            "    //\n"
            "    // the light direction in eye space\n"
            "    //\n"
            "    vec3 l = -lights.light[i].spot_direction.xyz;    // we carry the directional light direction in the spot_direction slot\n"
            "\n"
            "    //\n"
            "    // the half vector\n"
            "    //\n"
            "    vec3 h = normalize(l + v);\n"
            "\n"
            "    float n_dot_l = max(0.0, dot(n, l));\n"
            "    float n_dot_h = max(0.0, dot(n, h));\n"
            "\n"
            "    float m = materials.material[j].shininess;\n"
            "\n"
            "    float pf;           // power factor\n"
            "\n"
            "    if (n_dot_l == 0.0)\n"
            "       pf = 0.0;\n"
            "    else\n"
            "       pf = pow(n_dot_h, m);\n"
            "\n"
            "    return materials.material[j].emissive.rgb \n"
            "         + lights.light[i].Ia.rgb * materials.material[j].ambient.rgb \n"
            "         + lights.light[i].Id.rgb * materials.material[j].diffuse.rgb  * n_dot_l                   // / PI\n"
            "         + lights.light[i].Is.rgb * materials.material[j].specular.rgb * (m+8)*0.0125 * pf;        // * (m+8)/(8*PI)\n"
            "}\n"
            "\n"
            "//\n"
            "// point light contribution\n"
            "//\n"
            "vec3 pointLight(\n"
            "    in int i,   // light identifier, i.e. current light\n"
            "    in int j,   // material identifier\n"
            "    in vec3 n,  // vertex normal in eye space\n"
            "    in vec3 v,  // view direction in eye space\n"
            "    in vec3 p)  // vertex position in eye space\n"
            "{\n"
            "    if (lights.light[i].type != point_light)\n"
            "        return vec3(0.0, 0.0, 0.0);\n"
            "\n"
            "    vec3  l = vec3(lights.light[i].position.xyz) - p;    // direction from surface to light position\n"
            "    float d = length(l);                             // distance from surface to light source\n"
            "    l = normalize(l);                                // normalized direction from surface to light position\n"
            "\n"
            "    //\n"
            "    // the half vector\n"
            "    //\n"
            "    vec3 h = normalize(l + v);\n"
            "\n"
            "    float n_dot_l = max(0.0, dot(n, l));\n"
            "    float n_dot_h = max(0.0, dot(n, h));\n"
            "\n"
            "    float m = materials.material[j].shininess;\n"
            "\n"
            "    float pf;           // power factor\n"
            "\n"
            "    if (n_dot_l == 0.0)\n"
            "       pf = 0.0;\n"
            "    else\n"
            "       pf = pow(n_dot_h, m);\n"
            "\n"
            "    //\n"
            "    // Compute attenuation\n"
            "    //\n"
            "    float attenuation = 1.0 / (lights.light[i].attenuation.x + \n"
            "                              (lights.light[i].attenuation.y * d) + \n"
            "                              (lights.light[i].attenuation.z * d * d));\n"
            "\n"
            "    attenuation = clamp(attenuation, 0.0, 1.0);\n"
            "\n"
            "    return materials.material[j].emissive.rgb \n"
            "         + attenuation * lights.light[i].Ia.rgb * materials.material[j].ambient.rgb \n"
            "         + attenuation * lights.light[i].Id.rgb * materials.material[j].diffuse.rgb  * n_dot_l                   // / PI\n"
            "         + attenuation * lights.light[i].Is.rgb * materials.material[j].specular.rgb * (m+8)*0.0125 * pf;        // * (m+8)/(8*PI)\n"
            "}\n"
            "\n"
            "//\n"
            "// spot light contribution\n"
            "//\n"
            "vec3 spotLight(\n"
            "    in int i,   // light identifier, i.e. current light\n"
            "    in int j,   // material identifier\n"
            "    in vec3 n,  // vertex normal in eye space\n"
            "    in vec3 v,  // view direction in eye space\n"
            "    in vec3 p)  // vertex position in eye space\n"
            "{\n"
            "    if (lights.light[i].type != spot_light)\n"
            "        return vec3(0.0, 0.0, 0.0);\n"
            "\n"
            "    vec3  l = vec3(lights.light[i].position.xyz) - p;   // direction from surface to light position\n"
            "    float d = length(l);                            // distance from surface to light source\n"
            "    l = normalize(l);                               // normalized direction from surface to light position\n"
            "    \n"
            "    vec3 s = lights.light[i].spot_direction.xyz;        // spot direction\n"
            "\n"
            "    //\n"
            "    // the half vector\n"
            "    //\n"
            "    vec3 h = normalize(l + v);\n"
            "\n"
            "    float n_dot_l = max(0.0, dot(n, l));\n"
            "    float n_dot_h = max(0.0, dot(n, h));\n"
            "    float l_dot_s = dot(-l, s);\n"
            "\n"
            "    float m = materials.material[j].shininess;\n"
            "\n"
            "    float pf;           // power factor\n"
            "\n"
            "    if (n_dot_l == 0.0)\n"
            "       pf = 0.0;\n"
            "    else\n"
            "       pf = pow(n_dot_h, m);\n"
            "\n"
            "    //\n"
            "    // Compute attenuation\n"
            "    //\n"
            "    float attenuation = 1.0 / (lights.light[i].attenuation.x + \n"
            "                              (lights.light[i].attenuation.y * d) + \n"
            "                              (lights.light[i].attenuation.z * d * d));\n"
            "\n"
            "    attenuation = clamp(attenuation, 0.0, 1.0);\n"
            "\n"
            "    if (l_dot_s < lights.light[i].spot_cos_cutoff) \n"
            "        attenuation = 0.0;\n"
            "    else\n"
            "        attenuation *= pow(l_dot_s, lights.light[i].spot_exponent);\n"
            "\n"
            "    return materials.material[j].emissive.rgb \n"
            "         + attenuation * lights.light[i].Ia.rgb * materials.material[j].ambient.rgb \n"
            "         + attenuation * lights.light[i].Id.rgb * materials.material[j].diffuse.rgb  * n_dot_l                   // / PI\n"
            "         + attenuation * lights.light[i].Is.rgb * materials.material[j].specular.rgb * (m+8)*0.0125 * pf;        // * (m+8)/(8*PI)\n"
            "}\n"
            "\n"
            "void main()\n"
            "{\n"
            "    //\n"
            "    // normalize the eye space normal\n"
            "    //\n"
            "    vec3 N = normalize(vNormalES);\n"
            "\n"
            "    //\n"
            "    // get the view vector and normalize it\n"
            "    //\n"
            "    vec3 V = normalize(cCameraPositionES - vPositionES);\n"
            "\n"
            "    //\n"
            "    // Integrate over all lights: Any unused light does not contribute and each light\n"
            "    // contribute either from the directional light, the point light or the spot light.\n"
            "    //\n"
            "    vec3 color = vec3(0.0, 0.0, 0.0);\n"
            "    for (int i = 0; i < num_lights; ++i) {\n"
            "        color += directionalLight(i, geom_state.material_index, N, V) \n"
            "              +        pointLight(i, geom_state.material_index, N, V, vPositionES) \n"
            "              +         spotLight(i, geom_state.material_index, N, V, vPositionES);\n"
            "    }\n"
            "    vFragColor = vec4(color, materials.material[geom_state.material_index  ].opacity);\n"
            "\n"
            "    //\n"
            "    // Test TestBlock\n"
            "    //\n"
            "    if (test_block.a != 27.4)                               vFragColor = vec4(1, 0, 0, 1);\n"
            "    if (test_block.b != vec2(15.3, 12.8))                   vFragColor = vec4(1, 0, 0, 1);\n"
            "    if (test_block.c != vec3(11.4, 21.9, 10.5))             vFragColor = vec4(1, 0, 0, 1);\n"
            "\n"
            "    if (test_block.f.d != 61)                               vFragColor = vec4(1, 0, 0, 1);\n"
            "    if (test_block.f.e != bvec2(true, false))               vFragColor = vec4(1, 0, 0, 1);\n"
            "\n"
            "    if (test_block.g != 57.3)                               vFragColor = vec4(1, 0, 0, 1);\n"
            "\n"
            "    if (test_block.h[0] != 9.1)                             vFragColor = vec4(1, 0, 0, 1);\n"
            "    if (test_block.h[1] != 17.56)                           vFragColor = vec4(1, 0, 0, 1);\n"
            "\n"
            "    if (test_block.i[0] != vec3(19.43,1243.2, 0.56))        vFragColor = vec4(1, 0, 0, 1);\n"
            "    if (test_block.i[1] != vec3(13.54,264.22, 65.52))       vFragColor = vec4(1, 0, 0, 1);\n"
            "\n"
            "    if (test_block.o[0].j != uvec3(10,11,12))               vFragColor = vec4(1, 0, 0, 1);\n"
            "    if (test_block.o[0].k != vec2(64.62, 275.21))           vFragColor = vec4(1, 0, 0, 1);\n"
            "    if (test_block.o[0].l[0] != 41.346)                     vFragColor = vec4(1, 0, 0, 1);\n"
            "    if (test_block.o[0].l[1] != 67.9456)                    vFragColor = vec4(1, 0, 0, 1);\n"
            "    if (test_block.o[0].m != vec2(-56.62, 768.276))         vFragColor = vec4(1, 0, 0, 1);\n"
            "    if (test_block.o[0].n[0][0] != vec3(-0.4,-0.5,-0.6))    vFragColor = vec4(1, 0, 0, 1);\n"
            "    if (test_block.o[0].n[0][1] != vec3(-0.7,-0.8,-0.9))    vFragColor = vec4(1, 0, 0, 1);\n"
            "    if (test_block.o[0].n[0][2] != vec3(-0.1,-0.2,-0.3))    vFragColor = vec4(1, 0, 0, 1);\n"
            "    if (test_block.o[0].n[1][0] != vec3(1.1,2.2,3.3))       vFragColor = vec4(1, 0, 0, 1);\n"
            "    if (test_block.o[0].n[1][1] != vec3(1.2,2.3,3.4))       vFragColor = vec4(1, 0, 0, 1);\n"
            "    if (test_block.o[0].n[1][2] != vec3(1.3,2.4,3.5))       vFragColor = vec4(1, 0, 0, 1);\n"
            "\n"
            "    if (test_block.o[1].j != uvec3(20,31,42))               vFragColor = vec4(1, 0, 0, 1);\n"
            "    if (test_block.o[1].k != vec2(-96.62, -658.456))        vFragColor = vec4(1, 0, 0, 1);\n"
            "    if (test_block.o[1].l[0] != 88.34)                      vFragColor = vec4(1, 0, 0, 1);\n"
            "    if (test_block.o[1].l[1] != -488.21)                    vFragColor = vec4(1, 0, 0, 1);\n"
            "    if (test_block.o[1].m != vec2(777.7, 888.8))            vFragColor = vec4(1, 0, 0, 1);\n"
            "    if (test_block.o[1].n[0][0] != vec3(1.1,1.2,1.3))       vFragColor = vec4(1, 0, 0, 1);\n"
            "    if (test_block.o[1].n[0][1] != vec3(2.1,2.2,2.3))       vFragColor = vec4(1, 0, 0, 1);\n"
            "    if (test_block.o[1].n[0][2] != vec3(3.1,3.2,3.3))       vFragColor = vec4(1, 0, 0, 1);\n"
            "    if (test_block.o[1].n[1][0] != vec3(-1.1,-1.2,-1.3))    vFragColor = vec4(1, 0, 0, 1);\n"
            "    if (test_block.o[1].n[1][1] != vec3(-2.1,-2.2,-2.3))    vFragColor = vec4(1, 0, 0, 1);\n"
            "    if (test_block.o[1].n[1][2] != vec3(-3.1,-3.2,-3.3))    vFragColor = vec4(1, 0, 0, 1);\n"
            "\n"
            "}\n"
            "\n"
            ;
    return fp_program;
}
