#!/usr/bin/perl

use strict;

my %gl_define_list_one;
my %gl_define_list_two;

my @exclude_list = 
(
 "GL_VERSION_.*",
 "GL_NO_ERROR",
 "GL_INVALID_ENUM",
 "GL_INVALID_VALUE",
 "GL_INVALID_OPERATION",
 "GL_STACK_OVERFLOW",
 "GL_STACK_UNDERFLOW",
 "GL_OUT_OF_MEMORY",
 "GL_TABLE_TOO_LARGE",
 "GL_GLEXT_VERSION",
 "GL_TIMEOUT_IGNORED"
);

my @match_one_way_list = 
(
 "RELATIVE_VERTICAL_LINE_TO_NV\$",
 "RELATIVE_CUBIC_CURVE_TO_NV\$",
 "RELATIVE_QUADRATIC_CURVE_TO_NV\$",

 "VERTICAL_LINE_TO_NV\$",
 "CUBIC_CURVE_TO_NV\$",
 "QUADRATIC_CURVE_TO_NV\$",

 "SMOOTH_QUADRATIC_CURVE_TO_NV\$",

 "CURRENT_OCCLUSION_QUERY_ID_NV\$",

 "UNSIGNED_INT64_NV\$",

 "CURRENT_TIME_NV\$",
 "PROGRAM_ERROR_STRING_NV\$",

 "PIXEL_COUNT_AVAILABLE_NV\$",
 "PIXEL_COUNT_NV\$",

 "PROGRAM_ERROR_POSITION_NV\$",

 "CURRENT_MATRIX_STACK_DEPTH_NV\$",
 "CURRENT_MATRIX_NV\$",
 "MAX_TRACK_MATRICES_NV\$",
 "MAX_TRACK_MATRIX_STACK_DEPTH_NV\$",

 "PIXEL_COUNTER_BITS_NV\$",

 "OFFSET_TEXTURE_2D_MATRIX_NV\$",
 "OFFSET_TEXTURE_2D_BIAS_NV\$",

 "VERTEX_PROGRAM_NV\$",
 "PROGRAM_STRING_NV\$",
 "PROGRAM_LENGTH_NV\$",

 "VERTEX_PROGRAM_POINT_SIZE_NV\$",

 "OFFSET_TEXTURE_2D_SCALE_NV\$",

 "RENDERBUFFER_COVERAGE_SAMPLES_NV\$",

 "MAX_GEOMETRY_PROGRAM_INVOCATIONS_NV\$",

 "MAP2_VERTEX_ATTRIB7_4_NV\$",

 "CURRENT_ATTRIB_NV\$",

 "ATTRIB_ARRAY_POINTER_NV\$",
 "ATTRIB_ARRAY_STRIDE_NV\$",
 "ATTRIB_ARRAY_TYPE_NV\$",
 "ATTRIB_ARRAY_SIZE_NV\$",

 "TRANSFORM_FEEDBACK_BUFFER_ACTIVE_NV\$",
 "TRANSFORM_FEEDBACK_BUFFER_PAUSED_NV\$",

 "FRAGMENT_PROGRAM_INTERPOLATION_OFFSET_BITS_NV\$",



 "ALPHA_FLOAT16_ATI\$",
 "ALPHA_FLOAT32_ATI\$",

 "INTENSITY_FLOAT16_ATI\$",
 "INTENSITY_FLOAT32_ATI\$",

 "LUMINANCE_FLOAT16_ATI\$",
 "LUMINANCE_FLOAT32_ATI\$",

 "LUMINANCE_ALPHA_FLOAT16_ATI\$",
 "LUMINANCE_ALPHA_FLOAT32_ATI\$",

 "RGB_FLOAT16_ATI\$",
 "RGB_FLOAT32_ATI\$",

 "RGBA_FLOAT16_ATI\$",
 "RGBA_FLOAT32_ATI\$",

 "RGBA_FLOAT_MODE_ATI\$",
 "MIRROR_CLAMP_ATI\$",
 "SATURATE_BIT_ATI\$",

 "OBJECT_BUFFER_SIZE_ATI\$",
 "OBJECT_BUFFER_USAGE_ATI\$",




 "VIRTUAL_PAGE_SIZE_X_AMD\$",
 "VIRTUAL_PAGE_SIZE_Y_AMD\$",
 "VIRTUAL_PAGE_SIZE_Z_AMD\$",

 "MIN_SPARSE_LEVEL_AMD\$",
 "MAX_SPARSE_TEXTURE_SIZE_AMD\$",
 "MAX_SPARSE_3D_TEXTURE_SIZE_AMD\$",

 "DEBUG_SEVERITY_HIGH_AMD\$",
 "DEBUG_SEVERITY_LOW_AMD\$",
 "DEBUG_SEVERITY_MEDIUM_AMD\$",
 "DEBUG_LOGGED_MESSAGES_AMD\$",
 "MAX_DEBUG_LOGGED_MESSAGES_AMD\$",
 "MAX_DEBUG_MESSAGE_LENGTH_AMD\$",

 "QUERY_OBJECT_AMD\$",
 "QUERY_BUFFER_AMD\$",
 "QUERY_BUFFER_BINDING_AMD\$",
 "QUERY_RESULT_NO_WAIT_AMD\$",

 "VERTEX_ARRAY_OBJECT_AMD\$",
 "DATA_BUFFER_AMD\$",

 "MAX_COMPUTE_FIXED_GROUP_SIZE_ARB\$",
 "MAX_COMPUTE_FIXED_GROUP_INVOCATIONS_ARB\$",

 "MAX_VARYING_FLOATS_ARB\$",

 "MODELVIEW0_ARB\$",

 "OBJECT_DELETE_STATUS_ARB\$",
 "OBJECT_ATTACHED_OBJECTS_ARB\$",
 "OBJECT_ACTIVE_ATTRIBUTES_ARB\$",
 "OBJECT_LINK_STATUS_ARB\$",
 "OBJECT_ACTIVE_UNIFORM_MAX_LENGTH_ARB\$",
 "OBJECT_INFO_LOG_LENGTH_ARB\$",
 "OBJECT_SUBTYPE_ARB\$",
 "OBJECT_SHADER_SOURCE_LENGTH_ARB\$",
 "OBJECT_VALIDATE_STATUS_ARB\$",
 "OBJECT_COMPILE_STATUS_ARB\$",
 "OBJECT_ACTIVE_ATTRIBUTE_MAX_LENGTH_ARB\$",
 "OBJECT_ACTIVE_UNIFORMS_ARB\$",

 "FOG_COORDINATE_ARRAY_BUFFER_BINDING_ARB\$",

 "SOURCE0_RGB_ARB\$",
 "SOURCE0_ALPHA_ARB\$",
 "SOURCE1_RGB_ARB\$",
 "SOURCE1_ALPHA_ARB\$",
 "SOURCE2_RGB_ARB\$",
 "SOURCE2_ALPHA_ARB\$",

 "VERTEX_PROGRAM_POINT_SIZE_ARB\$",



 "TEXTURE_1D_BINDING_EXT\$",
 "TEXTURE_2D_BINDING_EXT\$",
 "TEXTURE_3D_BINDING_EXT\$",

 "FRAMEBUFFER_BINDING_EXT\$",

 "TEXTURE_BUFFER_FORMAT_EXT\$",

 "MAX_VERTEX_VARYING_COMPONENTS_EXT\$",
 "MAX_GEOMETRY_VARYING_COMPONENTS_EXT\$",
 "MAX_COMBINED_IMAGE_UNITS_AND_FRAGMENT_OUTPUTS_EXT\$",

 "FRAMEBUFFER_ATTACHMENT_TEXTURE_3D_ZOFFSET_EXT\$",

 "MODELVIEW0_MATRIX_EXT\$",
 "MODELVIEW0_EXT\$",
 "MODELVIEW1_EXT\$",
 "MODELVIEW0_STACK_DEPTH_EXT\$",

 "PROGRAM_OBJECT_EXT\$",
 "SHADER_OBJECT_EXT\$",

 "COMPARE_REF_DEPTH_TO_TEXTURE_EXT\$",

 "COMPRESSED_RED_GREEN_RGTC2_EXT\$",
 "COMPRESSED_SIGNED_RED_GREEN_RGTC2_EXT\$",

 "FRAMEBUFFER_INCOMPLETE_LAYER_COUNT_EXT\$",

 "POLYGON_OFFSET_EXT\$",
 "DISTANCE_ATTENUATION_EXT\$",
 "BLEND_EQUATION_EXT\$",

 "SAMPLE_MASK_INVERT_EXT\$",
 "SAMPLE_ALPHA_TO_MASK_EXT\$",
 "SAMPLE_ALPHA_TO_ONE_EXT\$",

 "FOG_COORDINATE_ARRAY_EXT\$",
 "FOG_COORDINATE_ARRAY_POINTER_EXT\$",
 "FOG_COORDINATE_ARRAY_STRIDE_EXT\$",
 "FOG_COORDINATE_ARRAY_TYPE_EXT\$",
 "FOG_COORDINATE_SOURCE_EXT\$",
 "FOG_COORDINATE_EXT\$",
 "CURRENT_FOG_COORDINATE_EXT\$",

 "SOURCE0_ALPHA_EXT\$",
 "SOURCE0_RGB_EXT\$",
 "SOURCE1_ALPHA_EXT\$",
 "SOURCE1_RGB_EXT\$",
 "SOURCE2_ALPHA_EXT\$",
 "SOURCE2_RGB_EXT\$",

 "LAYOUT_DEFAULT_INTEL\$",


 "UNSIGNED_SHORT_8_8_APPLE\$",
 "UNSIGNED_SHORT_8_8_REV_APPLE\$",
 "HALF_APPLE\$",

 "ALPHA_FLOAT16_APPLE\$",
 "ALPHA_FLOAT32_APPLE\$",

 "INTENSITY_FLOAT16_APPLE\$",
 "INTENSITY_FLOAT32_APPLE\$",

 "LUMINANCE_FLOAT16_APPLE\$",
 "LUMINANCE_FLOAT32_APPLE\$",

 "LUMINANCE_ALPHA_FLOAT16_APPLE\$",
 "LUMINANCE_ALPHA_FLOAT32_APPLE\$",

 "RGB_FLOAT16_APPLE\$",
 "RGB_FLOAT32_APPLE\$",

 "RGBA_FLOAT16_APPLE\$",
 "RGBA_FLOAT32_APPLE\$",

 "VERTEX_ARRAY_BINDING_APPLE\$",
 "VERTEX_ARRAY_RANGE_APPLE\$",
 "VERTEX_ARRAY_RANGE_LENGTH_APPLE\$",
 "VERTEX_ARRAY_RANGE_POINTER_APPLE\$",
 "VERTEX_ARRAY_STORAGE_HINT_APPLE\$",




 "1PASS_SGIS\$",
 "2PASS_0_SGIS\$",
 "2PASS_1_SGIS\$",
 "4PASS_0_SGIS\$",
 "4PASS_1_SGIS\$",
 "4PASS_2_SGIS\$",
 "4PASS_3_SGIS\$",

 "SAMPLE_PATTERN_SGIS\$",
 "SAMPLE_MASK_INVERT_SGIS\$",
 "SAMPLE_ALPHA_TO_MASK_SGIS\$",
 "SAMPLE_ALPHA_TO_ONE_SGIS\$",

 "SHADOW_AMBIENT_SGIX\$",
 "DISTANCE_ATTENUATION_SGIS\$",



 "REPLACE_OLDEST_SUN\$",


 "FIXED_OES\$",

 "IMPLEMENTATION_COLOR_READ_TYPE_OES\$",
 "IMPLEMENTATION_COLOR_READ_FORMAT_OES\$",



 "TEXTURE_COMPONENTS\$",
 "LOGIC_OP\$",
 "BLEND_EQUATION\$",
 "COMPARE_REF_TO_TEXTURE\$",


 "CLIP_DISTANCE0\$",
 "CLIP_DISTANCE1\$",
 "CLIP_DISTANCE2\$",
 "CLIP_DISTANCE3\$",
 "CLIP_DISTANCE4\$",
 "CLIP_DISTANCE5\$",
 "MAX_CLIP_DISTANCES\$",

 "TRANSFORM_FEEDBACK_BUFFER_ACTIVE\$",
 "TRANSFORM_FEEDBACK_BUFFER_PAUSED\$",

 "MAX_COMBINED_IMAGE_UNITS_AND_FRAGMENT_OUTPUTS\$",
 "MAX_VARYING_FLOATS\$",

 "VERTEX_PROGRAM_POINT_SIZE\$",
 "POINT_SIZE_GRANULARITY\$",
 "POINT_SIZE_RANGE\$",

 "LINE_WIDTH_RANGE\$",
 "LINE_WIDTH_GRANULARITY\$",

 "SOURCE0_ALPHA\$",
 "SOURCE0_RGB\$",
 "SOURCE1_ALPHA\$",
 "SOURCE1_RGB\$",
 "SOURCE2_ALPHA\$",
 "SOURCE2_RGB\$",

 "FOG_COORDINATE\$",
 "FOG_COORDINATE_ARRAY\$",
 "FOG_COORDINATE_ARRAY_STRIDE\$",
 "FOG_COORDINATE_ARRAY_BUFFER_BINDING\$",
 "FOG_COORDINATE_ARRAY_POINTER\$",
 "FOG_COORDINATE_ARRAY_TYPE\$",
 "FOG_COORDINATE_SOURCE\$",

 "CURRENT_FOG_COORDINATE\$",

 "COPY_READ_BUFFER\$",
 "COPY_WRITE_BUFFER\$",
 "FRAMEBUFFER_BINDING\$",
 "TEXTURE_BUFFER_BINDING\$",


# 0 POINTS

 "NONE\$",
 "CLOSE_PATH_NV\$",
 "ZERO\$",
 "FALSE\$",

# 1 LINES

 "TRUE\$",
 "ONE\$",

 "CLIENT_PIXEL_STORE_BIT\$",
 "VERTEX_ATTRIB_ARRAY_BARRIER_BIT\$",
 "SYNC_FLUSH_COMMANDS_BIT\$",
 "VERTEX_SHADER_BIT\$",
 "MAP_READ_BIT\$",

 "CONTEXT_FLAG_FORWARD_COMPATIBLE_BIT\$",
 "CONTEXT_CORE_PROFILE_BIT\$",

 "CURRENT_BIT\$",

 "VERTEX_ATTRIB_ARRAY_BARRIER_BIT_EXT\$",

 "2X_BIT_ATI\$",
 "RED_BIT_ATI\$",

 "TEXTURE_STORAGE_SPARSE_BIT_AMD\$",

 "BOLD_BIT_NV\$",
 "GLYPH_WIDTH_BIT_NV\$",

 "TEXTURE_DEFORMATION_BIT_SGIX\$",

 "RESTART_SUN\$",

 "LAYOUT_LINEAR_INTEL\$",


# 2 LINE_LOOP

 "FRAGMENT_SHADER_BIT\$",
 "MAP_WRITE_BIT\$",
 "POINT_BIT\$",
 "CONTEXT_COMPATIBILITY_PROFILE_BIT\$",
 "CONTEXT_FLAG_DEBUG_BIT\$",
 "ELEMENT_ARRAY_BARRIER_BIT\$",
 "CLIENT_VERTEX_ARRAY_BIT\$",

 "ELEMENT_ARRAY_BARRIER_BIT_EXT\$",

 "COMP_BIT_ATI\$",
 "GREEN_BIT_ATI\$",
 "4X_BIT_ATI\$",

 "MOVE_TO_NV\$",
 "ITALIC_BIT_NV\$",
 "GLYPH_HEIGHT_BIT_NV\$",

 "GEOMETRY_DEFORMATION_BIT_SGIX\$",

 "REPLACE_MIDDLE_SUN\$",

 "LAYOUT_LINEAR_CPU_CACHED_INTEL\$",


# 3 LINE_STRIP

 "RELATIVE_MOVE_TO_NV\$",

# 4 TRIANGLES

 "LINE_BIT\$",
 "MAP_INVALIDATE_RANGE_BIT\$",
 "GEOMETRY_SHADER_BIT\$",
 "UNIFORM_BARRIER_BIT\$",

 "CONTEXT_FLAG_ROBUST_ACCESS_BIT_ARB\$",

 "UNIFORM_BARRIER_BIT_EXT\$",

 "NEGATE_BIT_ATI\$",
 "BLUE_BIT_ATI\$",
 "8X_BIT_ATI\$",

 "GLYPH_HORIZONTAL_BEARING_X_BIT_NV\$",
 "LINE_TO_NV\$",

 "VERTEX23_BIT_PGI\$",


# 5 TRIANGLE_STRIP

 "RELATIVE_LINE_TO_NV\$",

# 6 TRIANGLE_FAN

 "HORIZONTAL_LINE_TO_NV\$",

# 7 QUADS

 "RELATIVE_HORIZONTAL_LINE_TO_NV\$",

# 8 QUAD_STRIP

 "MAP_INVALIDATE_BUFFER_BIT\$",
 "TEXTURE_FETCH_BARRIER_BIT\$",
 "TESS_CONTROL_SHADER_BIT\$",
 "POLYGON_BIT\$",

 "TEXTURE_FETCH_BARRIER_BIT_EXT\$",

 "BIAS_BIT_ATI\$",
 "HALF_BIT_ATI\$",

 "GLYPH_HORIZONTAL_BEARING_Y_BIT_NV\$",

 "VERTEX4_BIT_PGI\$",

# 10 TESS_EVALUATION_SHADER_BIT\$",

 "POLYGON_STIPPLE_BIT\$",
 "MAP_FLUSH_EXPLICIT_BIT\$",

 "GLYPH_HORIZONTAL_BEARING_ADVANCE_BIT_NV\$",
 "SHADER_GLOBAL_ACCESS_BARRIER_BIT_NV\$",

 "QUARTER_BIT_ATI\$",


# 20 COMPUTE_SHADER_BIT

 "PIXEL_MODE_BIT\$",
 "SHADER_IMAGE_ACCESS_BARRIER_BIT\$",
 "MAP_UNSYNCHRONIZED_BIT\$",

 "SHADER_IMAGE_ACCESS_BARRIER_BIT_EXT\$",

 "EIGHTH_BIT_ATI\$",

 "GLYPH_VERTICAL_BEARING_X_BIT_NV\$",


# 40 LIGHTING_BIT

 "COMMAND_BARRIER_BIT\$",
 "MAP_PERSISTENT_BIT\$",

 "COMMAND_BARRIER_BIT_EXT\$",

 "GLYPH_VERTICAL_BEARING_Y_BIT_NV\$",

# 80 PIXEL_BUFFER_BARRIER_BIT

 "FOG_BIT\$",
 "MAP_COHERENT_BIT\$",

 "GLYPH_VERTICAL_BEARING_ADVANCE_BIT_NV\$",


# 100 ACCUM

 "DEPTH_BUFFER_BIT\$",
 "TEXTURE_UPDATE_BARRIER_BIT\$",
 "DYNAMIC_STORAGE_BIT\$",

 "TEXTURE_UPDATE_BARRIER_BIT_EXT\$",

 "GLYPH_HAS_KERNING_BIT_NV\$",


# 200 NEVER

 "CLIENT_STORAGE_BIT\$",
 "BUFFER_UPDATE_BARRIER_BIT\$",
 "ACCUM_BUFFER_BIT\$",

 "BUFFER_UPDATE_BARRIER_BIT_EXT\$",



# 400 FRONT_LEFT

 "STENCIL_BUFFER_BIT\$",
 "FRAMEBUFFER_BARRIER_BIT\$",

 "FRAMEBUFFER_BARRIER_BIT_EXT\$",


# 800 EXP

 "VIEWPORT_BIT\$",
 "TRANSFORM_FEEDBACK_BARRIER_BIT\$",

 "TRANSFORM_FEEDBACK_BARRIER_BIT_EXT\$",



# 1000 TEXTURE_WIDTH

 "ATOMIC_COUNTER_BARRIER_BIT\$",
 "TRANSFORM_BIT\$",

 "ATOMIC_COUNTER_BARRIER_BIT_EXT\$",



# 2000 S

 "SHADER_STORAGE_BARRIER_BIT\$",
 "ENABLE_BIT\$",

# 4000 LIGHT0

 "CLIENT_MAPPED_BUFFER_BARRIER_BIT\$",
 "COLOR_BUFFER_BIT\$",

# 8000 ABGR_EXT

 "HINT_BIT\$",
 "QUERY_BUFFER_BARRIER_BIT\$",

# 10000 EVAL_BIT

 "FONT_X_MIN_BOUNDS_BIT_NV\$",
 "COLOR3_BIT_PGI\$",

# 20000 LIST_BIT

 "FONT_Y_MIN_BOUNDS_BIT_NV\$",
 "COLOR4_BIT_PGI\$",

# 40000 TEXTURE_BIT

 "FONT_X_MAX_BOUNDS_BIT_NV\$",
 "EDGEFLAG_BIT_PGI\$",

# 80000 SCISSOR_BIT

 "FONT_Y_MAX_BOUNDS_BIT_NV\$",
 "INDEX_BIT_PGI\$",

# 100000 FONT_UNITS_PER_EM_BIT_NV

 "MAT_AMBIENT_BIT_PGI\$",

# 200000 FONT_ASCENDER_BIT_NV

 "MAT_AMBIENT_AND_DIFFUSE_BIT_PGI\$",

# 400000 FONT_DESCENDER_BIT_NV

 "MAT_DIFFUSE_BIT_PGI\$",

# 800000 FONT_HEIGHT_BIT_NV

 "MAT_EMISSION_BIT_PGI\$",

# 1000000 FONT_MAX_ADVANCE_WIDTH_BIT_NV

 "MAT_COLOR_INDEXES_BIT_PGI\$",

# 2000000 FONT_MAX_ADVANCE_HEIGHT_BIT_NV

 "MAT_SHININESS_BIT_PGI\$",

# 4000000 FONT_UNDERLINE_POSITION_BIT_NV

 "MAT_SPECULAR_BIT_PGI\$",

# 8000000 FONT_UNDERLINE_THICKNESS_BIT_NV

 "NORMAL_BIT_PGI\$",

# 10000000 FONT_HAS_KERNING_BIT_NV

 "TEXCOORD1_BIT_PGI\$",

# 20000000 MULTISAMPLE_BIT

 "MULTISAMPLE_BIT_3DFX\$",
 "TEXCOORD2_BIT_PGI\$",

# ffffffff ALL_ATTRIB_BITS

 "INVALID_INDEX\$",
 "ALL_SHADER_BITS\$",
 "ALL_BARRIER_BITS\$",
 "CLIENT_ALL_ATTRIB_BITS\$",

 "ALL_BARRIER_BITS_EXT\$"
);

my @overload_ext = 
(
 "_ARB\$",
 "_EXT\$",
 "_NV\$",
 "_ATI\$",
 "_IBM\$",
 "_HP\$",
 "_SGI\$",
 "_SGIS\$",
 "_SGIX\$"
);

sub define_excluded
{
    my $d = shift;
    my $found = 0;

    FOUND: foreach my $p (@exclude_list)
    {
        if($d =~ m/$p/)
        {
            $found = 1;
            last FOUND;
        }
    }

    if($found == 1)
    {
#        print "excluded : $d\n";
    }

    return $found;
}

sub define_one_way
{
    my $d = shift;
    my $found = 0;

    FOUND: foreach my $p (@match_one_way_list)
    {
        if($d =~ m/$p/)
        {
            $found = 1;
            last FOUND;
        }
    }

    return $found;
}

sub process_define
{
    my $d = shift;
    my $v = shift;

    if(define_excluded($d) == 1)
    {
    }
    elsif(define_one_way($d) == 1)
    {
        if(exists $gl_define_list_one{$d})
        {
#            print "$d already there\n";
        }
        else
        {
            $gl_define_list_one{$d} = $v;  
        }
#        push @gl_define_list_one, $d
    }
    else
    {
        if(exists $gl_define_list_two{$d})
        {
#            print "$d already there\n";
        }
        else
        {
            $gl_define_list_two{$d} = $v;  
        }
#        push @gl_define_list_two, $d
    }
}

sub processFile
{
    my $f = shift;

    open(IN, "grep #define $f |");

    while(<IN>)
    {
        if($_ =~ m/(#define)[ \t]+(GL_[A-Z0-9_x]+)[ \t]+([0-9A-Fx]+)/)
        {
            process_define($2, $3);
        }
        elsif($_ =~ m/(#define)[ \t]+(GL_[A-Z0-9_x]+)[ \t]+(GL_[A-Z0-9_]+)/)
        {
            process_define($2, $3);
        }
        else
        {
#            print "Unknown $f $_";
        }
    }

    close(IN);
}

processFile("/usr/include/GL.bugle/gl.h");
processFile("/usr/include/GL.bugle/glext.h");

#print "TWO WAY \n";

my @delete_from_two;

foreach my $define (keys %gl_define_list_two)
{
    if($gl_define_list_two{$define} =~ m/^GL_/)
    {
        my $v = $gl_define_list_two{$define};
        
        if(exists $gl_define_list_two{$v})
        {
            $gl_define_list_two{$define} = $gl_define_list_two{$v};
        }
    }
    FINALEXT: foreach my $ext (@overload_ext)
    {
        if($define =~ m/$ext/)
        {
            my $d = $define;
            $d =~ s/$ext//;

            if(exists $gl_define_list_two{$d})
            {
#                print "$define | $d\n";

                $gl_define_list_one{$define} = $gl_define_list_two{$define};
                
                push @delete_from_two, $define
            }

            last FINALEXT;
        }
    }
#    print "$define : $gl_define_list_two{$define}\n";
}

foreach my $key (@delete_from_two)
{
#    print "del : $key\n";

    delete($gl_define_list_two{$key});
}

my @k = (keys %gl_define_list_two);

#print "$#k\n";

#print "\nONE WAY \n";

@k = (keys %gl_define_list_one);

#print "$#k\n";

#foreach my $define (keys %gl_define_list_one)
#{
#    print "$define : $gl_define_list_one{$define}\n";
#}

open(OUT, "> Source/Base/Base/OSGGLDefineMapper_auto.cpp");

print OUT "//#################################################\n";
print OUT "// auto generated use \n";
print OUT "// Tools/glEnumMapper/createGLEnumMaps.pl to rebuild\n";
print OUT "//#################################################\n\n\n";

print OUT "#include \"OSGGLDefineMapper.h\"\n\n\n";
print OUT "OSG_BEGIN_NAMESPACE\n\n";

my $nfuncs = 1;
my $defsperfunc = 100;
my $currentdef = $defsperfunc;

print OUT "#ifdef OSG_GL_DEFMAPPER\n\n";
print OUT "// Break up long function into pieces to relieve compiler optimizer\n\n";
print OUT "static void initMapsHelper_0(GLDefineMapperBase* mapper)\n";
print OUT "{\n";


foreach my $define (keys %gl_define_list_two)
{
    if($currentdef == 0)
    {
        print OUT "}\n\n";
        print OUT "static void initMapsHelper_$nfuncs(GLDefineMapperBase* mapper)\n";
        print OUT "{\n";
        $currentdef = $defsperfunc;
        $nfuncs++;
    }
    $currentdef--;
    
    my $d = $define;

    $d =~ s/^GL_//;

    print OUT "    mapper->addToEnumPair  (\"$d\", $gl_define_list_two{$define});\n";
    print OUT "    mapper->addFromEnumPair($gl_define_list_two{$define}, \"$d\");\n";
}

print OUT "\n\n";

foreach my $define (keys %gl_define_list_one)
{
    if($currentdef == 0)
    {
        print OUT "}\n\n";
        print OUT "static void initMapsHelper_$nfuncs(GLDefineMapperBase* mapper)\n";
        print OUT "{\n";
        $currentdef = $defsperfunc;
        $nfuncs++;
    }
    $currentdef--;

    my $d = $define;

    $d =~ s/^GL_//;

    print OUT "    mapper->addToEnumPair  (\"$d\", $gl_define_list_one{$define});\n";
}

print OUT "}\n\n";
print OUT "#endif\n\n";


print OUT "void GLDefineMapperBase::initMaps(void)\n";
print OUT "{\n";
print OUT "#ifdef OSG_GL_DEFMAPPER\n";

for (my $c = 0; $c < $nfuncs; $c++)
{
    print OUT "    initMapsHelper_$c(this);\n";
}

print OUT "#endif\n";
print OUT "}\n\n";
print OUT "OSG_END_NAMESPACE\n\n";

close(OUT);

exit;
