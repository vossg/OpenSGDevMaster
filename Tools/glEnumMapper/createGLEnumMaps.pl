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
 "GL_GLEXT_VERSION"
);

my @match_one_way_list = 
(
 "GL_FALSE\$",
 "GL_TRUE\$",
 "GL_ZERO\$",
 "GL_ONE\$",
 "GL_NONE\$",
 "GL_ALL_ATTRIB_BITS",
 "GL_CLIENT_ALL_ATTRIB_BITS",
 "GL_RESTART_SUN",
 "GL_REPLACE_MIDDLE_SUN",
 "GL_REPLACE_OLDEST_SUN",

 "GL_VERTEX_ARRAY_RANGE_LENGTH_APPLE",
 "GL_RGB_FLOAT16_ATI",
 "GL_INTENSITY_FLOAT16_ATI",
 "GL_MODELVIEW1_EXT",
 
 "GL_LUMINANCE_ALPHA_FLOAT32_ATI\$",
 "GL_4PASS_3_SGIS\$",
 "GL_SRC0_ALPHA\$",
 "GL_SAMPLE_ALPHA_TO_MASK_EXT\$",
 "GL_RGBA_FLOAT32_ATI\$",
 "GL_SRC1_ALPHA\$",
 "GL_COMPARE_REF_DEPTH_TO_TEXTURE_EXT\$",
 "GL_OBJECT_DELETE_STATUS_ARB\$",
 "GL_CURRENT_OCCLUSION_QUERY_ID_NV\$",
 "GL_MODELVIEW0_EXT\$",
 "GL_POINT_SIZE_GRANULARITY\$",
 "GL_MIRROR_CLAMP_ATI\$",
 "GL_OBJECT_ATTACHED_OBJECTS_ARB\$",
 "GL_QUERY_WAIT_NV\$",
 "GL_SAMPLE_MASK_INVERT_EXT\$",
 "GL_TEXTURE_COMPONENTS\$",
 "GL_DISTANCE_ATTENUATION_SGIS\$",
 "GL_SRC1_RGB\$",
 "GL_TYPE_RGBA_FLOAT_ATI\$",
 "GL_OFFSET_TEXTURE_MATRIX_NV\$",
 "GL_LINE_WIDTH_GRANULARITY\$",
 "GL_TEXTURE_1D_BINDING_EXT\$",
 "GL_ALPHA_FLOAT16_ATI\$",
 "GL_SAMPLE_MASK_VALUE_SGIS\$",
 "GL_MAP2_VERTEX_ATTRIB7_4_NV\$",
 "GL_DRAW_FRAMEBUFFER_BINDING_EXT\$",
 "GL_PROGRAM_POINT_SIZE_EXT\$",
 "GL_SAMPLE_PATTERN_SGIS\$",
 "GL_OFFSET_TEXTURE_BIAS_NV\$",
 "GL_OBJECT_SUBTYPE_ARB\$",
 "GL_SAMPLE_MASK_INVERT_SGIS\$",
 "GL_DEPTH_STENCIL_NV\$",
 "GL_OBJECT_ACTIVE_ATTRIBUTES_ARB\$",
 "GL_INDEX_LOGIC_OP\$",
 "GL_SAMPLE_MASK_EXT\$",
 "GL_OFFSET_TEXTURE_SCALE_NV\$",
 "GL_SAMPLE_ALPHA_TO_MASK_SGIS\$",
 "GL_2PASS_1_SGIS\$",
 "GL_VERTEX_ARRAY_STORAGE_HINT_APPLE\$",
 "GL_4PASS_2_SGIS\$",
 "GL_SAMPLE_MASK_SGIS\$",
 "GL_UNSIGNED_SHORT_8_8_REV_APPLE\$",
 "GL_VERTEX_ARRAY_RANGE_POINTER_APPLE\$",
 "GL_LINE_WIDTH_RANGE\$",
 "GL_ATTRIB_ARRAY_POINTER_NV\$",
 "GL_SRC0_RGB\$",
 "GL_MAX_TRACK_MATRIX_STACK_DEPTH_NV\$",
 "GL_OBJECT_LINK_STATUS_ARB\$",
 "GL_BLEND_EQUATION_RGB\$",
 "GL_CURRENT_MATRIX_STACK_DEPTH_NV\$",
 "GL_VERTEX_PROGRAM_ARB\$",
 "GL_4PASS_0_SGIS\$",
 "GL_RGBA_FLOAT16_ATI\$",
 "GL_OBJECT_BUFFER_USAGE_ATI\$",
 "GL_RENDERBUFFER_COVERAGE_SAMPLES_NV\$",
 "GL_PROGRAM_LENGTH_NV\$",
 "GL_FOG_COORDINATE\$",
 "GL_POINT_SIZE_RANGE\$",
 "GL_ATTRIB_ARRAY_TYPE_NV\$",
 "GL_MODELVIEW0_ARB\$",
 "GL_LUMINANCE_ALPHA_FLOAT16_ATI\$",
 "GL_TEXTURE_3D_BINDING_EXT\$",
 "GL_OBJECT_ACTIVE_UNIFORM_MAX_LENGTH_ARB\$",
 "GL_PIXEL_COUNTER_BITS_NV\$",
 "GL_OBJECT_SHADER_SOURCE_LENGTH_ARB\$",
 "GL_PROGRAM_ERROR_STRING_NV\$",
 "GL_MIRROR_CLAMP_TO_EDGE_ATI\$",
 "GL_OBJECT_INFO_LOG_LENGTH_ARB\$",
 "GL_MODELVIEW0_STACK_DEPTH_EXT\$",
 "GL_INTENSITY_FLOAT32_ATI\$",
 "GL_MAX_VARYING_COMPONENTS_EXT\$",
 "GL_ELEMENT_ARRAY_TYPE_APPLE\$",
 "GL_CURRENT_FOG_COORDINATE\$",
 "GL_TEXTURE_RECTANGLE_NV\$",
 "GL_FOG_COORDINATE_ARRAY_POINTER\$",
 "GL_OBJECT_BUFFER_SIZE_ATI\$",
 "GL_ELEMENT_ARRAY_POINTER_APPLE\$",
 "GL_ELEMENT_ARRAY_APPLE\$",
 "GL_PROGRAM_ERROR_POSITION_NV\$",
 "GL_UNSIGNED_SHORT_8_8_APPLE\$",
 "GL_MAX_RENDERBUFFER_COVERAGE_SAMPLES_NV\$",
 "GL_FOG_COORDINATE_ARRAY_STRIDE\$",
 "GL_MAX_RECTANGLE_TEXTURE_SIZE_NV\$",
 "GL_LUMINANCE_FLOAT16_ATI\$",
 "GL_SAMPLE_MASK_VALUE_EXT\$",
 "GL_ATTRIB_ARRAY_SIZE_NV\$",
 "GL_HALF_FLOAT_NV\$",
 "GL_POLYGON_OFFSET_EXT\$",
 "GL_ALPHA_FLOAT32_ATI\$",
 "GL_LUMINANCE_FLOAT32_ATI\$",
 "GL_2PASS_0_SGIS\$",

 "GL_BLEND_EQUATION_RGB_EXT\$",
 "GL_FOG_COORDINATE_EXT\$",
 "GL_FOG_COORDINATE_ARRAY_STRIDE_EXT\$",
 "GL_FOG_COORDINATE_ARRAY_POINTER_EXT\$",
 "GL_PIXEL_COUNT_AVAILABLE_NV\$",
 "GL_RGB_FLOAT32_ATI\$",
 "GL_CURRENT_MATRIX_NV\$",
 "GL_CURRENT_ATTRIB_NV\$",
 "GL_SHADOW_AMBIENT_SGIX\$",
 "GL_FOG_COORDINATE_ARRAY_TYPE\$",
 "GL_SRC2_RGB\$",
 "GL_PROXY_TEXTURE_RECTANGLE_NV\$",
 "GL_UNSIGNED_INT_24_8_NV\$",
 "GL_MODELVIEW0_MATRIX_EXT\$",
 "GL_4PASS_1_SGIS\$",
 "GL_TEXTURE_BINDING_RECTANGLE_NV\$",
 "GL_FOG_COORDINATE_SOURCE\$",
 "GL_OBJECT_COMPILE_STATUS_ARB\$",
 "GL_OBJECT_ACTIVE_ATTRIBUTE_MAX_LENGTH_ARB\$",
 "GL_OBJECT_ACTIVE_UNIFORMS_ARB\$",
 "GL_TEXTURE_2D_BINDING_EXT\$",
 "GL_DISTANCE_ATTENUATION_EXT\$",
 "GL_FOG_COORDINATE_ARRAY_BUFFER_BINDING\$",
 "GL_ATTRIB_ARRAY_STRIDE_NV\$",
 "GL_SRC2_ALPHA\$",
 "GL_FOG_COORDINATE_ARRAY\$",
 "GL_MAX_TRACK_MATRICES_NV\$",
 "GL_1PASS_SGIS\$",
 "GL_PROGRAM_STRING_ARB\$",
 "GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_3D_ZOFFSET_EXT\$",
 "GL_OBJECT_VALIDATE_STATUS_ARB\$",
 "GL_CURRENT_FOG_COORDINATE_EXT\$",
 "GL_VERTEX_ARRAY_RANGE_APPLE\$",
 "GL_PIXEL_COUNT_NV\$",
 "GL_FOG_COORDINATE_ARRAY_TYPE_EXT\$",
 "GL_FOG_COORDINATE_ARRAY_EXT\$",
 "GL_FOG_COORDINATE_SOURCE_EXT\$",
 "GL_FOG_COORDINATE_ARRAY_BUFFER_BINDING_ARB\$",

 "GL_.*_BIT\$",
 "GL_.*_BIT_ARB\$",
 "GL_.*_BIT_EXT\$",
 "GL_.*_BIT_SGIX\$",
 "GL_.*_BIT_ATI\$",
 "GL_.*_BIT_3DFX\$",
 "GL_.*_BIT_PGI\$"
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

processFile("/usr/include/GL/gl.h");
processFile("/usr/include/GL/glext.h");

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

print OUT "#include <OSGGLDefineMapper.h>\n\n\n";
print OUT "OSG_BEGIN_NAMESPACE\n\n";
print OUT "void GLDefineMapperBase::initMaps(void)\n";
print OUT "{\n";

foreach my $define (keys %gl_define_list_two)
{
    my $d = $define;

    $d =~ s/^GL_//;

    print OUT "    addToEnumPair  (\"$d\", $gl_define_list_two{$define});\n";
    print OUT "    addFromEnumPair($gl_define_list_two{$define}, \"$d\");\n";
}

print OUT "\n\n";

foreach my $define (keys %gl_define_list_one)
{
    my $d = $define;

    $d =~ s/^GL_//;

    print OUT "    addToEnumPair  (\"$d\", $gl_define_list_one{$define});\n";
}

print OUT "}\n\n";
print OUT "OSG_END_NAMESPACE\n\n";

close(OUT);

exit;
