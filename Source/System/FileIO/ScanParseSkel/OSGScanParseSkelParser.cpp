/* A Bison parser, made by GNU Bison 2.0.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* Written by Richard Stallman by simplifying the original so called
   ``semantic'' parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Using locations.  */
#define YYLSP_NEEDED 0

/* Substitute the variable and function names.  */
#define yyparse OSGScanParseSkel_parse
#define yylex   OSGScanParseSkel_lex
#define yyerror OSGScanParseSkel_error
#define yylval  OSGScanParseSkel_lval
#define yychar  OSGScanParseSkel_char
#define yydebug OSGScanParseSkel_debug
#define yynerrs OSGScanParseSkel_nerrs


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     TOK_HEADER = 258,
     TOK_PROFILE = 259,
     TOK_COMPONENT = 260,
     TOK_META = 261,
     TOK_PROTO = 262,
     TOK_EXTERNPROTO = 263,
     TOK_IS = 264,
     TOK_DEF = 265,
     TOK_USE = 266,
     TOK_ROUTE = 267,
     TOK_TO = 268,
     TOK_IMPORT = 269,
     TOK_EXPORT = 270,
     TOK_AS = 271,
     TOK_eventIn = 272,
     TOK_eventOut = 273,
     TOK_exposedField = 274,
     TOK_field = 275,
     TOK_MFBool = 276,
     TOK_MFColor = 277,
     TOK_MFColorRGBA = 278,
     TOK_MFDouble = 279,
     TOK_MFFloat = 280,
     TOK_MFImage = 281,
     TOK_MFInt32 = 282,
     TOK_MFMatrix3d = 283,
     TOK_MFMatrix3f = 284,
     TOK_MFMatrix4d = 285,
     TOK_MFMatrix4f = 286,
     TOK_MFNode = 287,
     TOK_MFRotation = 288,
     TOK_MFString = 289,
     TOK_MFTime = 290,
     TOK_MFVec2d = 291,
     TOK_MFVec2f = 292,
     TOK_MFVec3d = 293,
     TOK_MFVec3f = 294,
     TOK_MFVec4d = 295,
     TOK_MFVec4f = 296,
     TOK_SFBool = 297,
     TOK_SFColor = 298,
     TOK_SFColorRGBA = 299,
     TOK_SFDouble = 300,
     TOK_SFFloat = 301,
     TOK_SFImage = 302,
     TOK_SFInt32 = 303,
     TOK_SFMatrix3d = 304,
     TOK_SFMatrix3f = 305,
     TOK_SFMatrix4d = 306,
     TOK_SFMatrix4f = 307,
     TOK_SFNode = 308,
     TOK_SFRotation = 309,
     TOK_SFString = 310,
     TOK_SFTime = 311,
     TOK_SFVec2d = 312,
     TOK_SFVec2f = 313,
     TOK_SFVec3d = 314,
     TOK_SFVec3f = 315,
     TOK_SFVec4d = 316,
     TOK_SFVec4f = 317,
     TOK_MFColor4i = 318,
     TOK_MFPnt2f = 319,
     TOK_MFPnt3f = 320,
     TOK_MFPnt4f = 321,
     TOK_MFPlane = 322,
     TOK_SFColor4i = 323,
     TOK_SFPnt2f = 324,
     TOK_SFPnt3f = 325,
     TOK_SFPnt4f = 326,
     TOK_SFPlane = 327,
     TOK_SFVolume = 328,
     TOK_hex = 329,
     TOK_int32 = 330,
     TOK_double = 331,
     TOK_string = 332,
     TOK_bool = 333,
     TOK_NULL = 334,
     TOK_Id = 335,
     TOK_ImageFinished = 336,
     TOK_Error = 337
   };
#endif
#define TOK_HEADER 258
#define TOK_PROFILE 259
#define TOK_COMPONENT 260
#define TOK_META 261
#define TOK_PROTO 262
#define TOK_EXTERNPROTO 263
#define TOK_IS 264
#define TOK_DEF 265
#define TOK_USE 266
#define TOK_ROUTE 267
#define TOK_TO 268
#define TOK_IMPORT 269
#define TOK_EXPORT 270
#define TOK_AS 271
#define TOK_eventIn 272
#define TOK_eventOut 273
#define TOK_exposedField 274
#define TOK_field 275
#define TOK_MFBool 276
#define TOK_MFColor 277
#define TOK_MFColorRGBA 278
#define TOK_MFDouble 279
#define TOK_MFFloat 280
#define TOK_MFImage 281
#define TOK_MFInt32 282
#define TOK_MFMatrix3d 283
#define TOK_MFMatrix3f 284
#define TOK_MFMatrix4d 285
#define TOK_MFMatrix4f 286
#define TOK_MFNode 287
#define TOK_MFRotation 288
#define TOK_MFString 289
#define TOK_MFTime 290
#define TOK_MFVec2d 291
#define TOK_MFVec2f 292
#define TOK_MFVec3d 293
#define TOK_MFVec3f 294
#define TOK_MFVec4d 295
#define TOK_MFVec4f 296
#define TOK_SFBool 297
#define TOK_SFColor 298
#define TOK_SFColorRGBA 299
#define TOK_SFDouble 300
#define TOK_SFFloat 301
#define TOK_SFImage 302
#define TOK_SFInt32 303
#define TOK_SFMatrix3d 304
#define TOK_SFMatrix3f 305
#define TOK_SFMatrix4d 306
#define TOK_SFMatrix4f 307
#define TOK_SFNode 308
#define TOK_SFRotation 309
#define TOK_SFString 310
#define TOK_SFTime 311
#define TOK_SFVec2d 312
#define TOK_SFVec2f 313
#define TOK_SFVec3d 314
#define TOK_SFVec3f 315
#define TOK_SFVec4d 316
#define TOK_SFVec4f 317
#define TOK_MFColor4i 318
#define TOK_MFPnt2f 319
#define TOK_MFPnt3f 320
#define TOK_MFPnt4f 321
#define TOK_MFPlane 322
#define TOK_SFColor4i 323
#define TOK_SFPnt2f 324
#define TOK_SFPnt3f 325
#define TOK_SFPnt4f 326
#define TOK_SFPlane 327
#define TOK_SFVolume 328
#define TOK_hex 329
#define TOK_int32 330
#define TOK_double 331
#define TOK_string 332
#define TOK_bool 333
#define TOK_NULL 334
#define TOK_Id 335
#define TOK_ImageFinished 336
#define TOK_Error 337




/* Copy the first part of user declarations.  */


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 41 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
typedef union YYSTYPE {
    long intVal;
    double doubleVal;
    float floatVal;
    const char *stringVal;
    bool boolVal;
} YYSTYPE;
/* Line 190 of yacc.c.  */
#line 257 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.cpp"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */
#line 49 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"


#define YYPARSE_PARAM pSkel
#define YYLEX_PARAM   pSkel

#define OSGScanParseSkel_error SKEL->handleError

#include "OSGConfig.h"
#include "OSGBaseFunctions.h"
#include "OSGScanParseLexer.h"
#include "OSGScanParseSkel.h"

#include <iostream>

#if defined(OSG_LINUX_ICC) || defined(OSG_WIN32_ICL)
#pragma warning( disable : 193 810 177 )
#endif

OSG_USING_NAMESPACE

int OSGScanParseSkel_lex(YYSTYPE *lvalp, void *);

#define SKEL ((ScanParseSkel *) pSkel)

#if(!defined(__GNUC__) && defined(__ICL) && __INTEL_COMPILER_VERSION >= 900)
# define alloca(size)   __builtin_alloca (size)
#endif



/* Line 213 of yacc.c.  */
#line 298 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.cpp"

#if ! defined (yyoverflow) || YYERROR_VERBOSE

# ifndef YYFREE
#  define YYFREE free
# endif
# ifndef YYMALLOC
#  define YYMALLOC malloc
# endif

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   else
#    define YYSTACK_ALLOC alloca
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
# else
#  if defined (__STDC__) || defined (__cplusplus)
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T size_t
#  endif
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
# endif
#endif /* ! defined (yyoverflow) || YYERROR_VERBOSE */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (defined (YYSTYPE_IS_TRIVIAL) && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short int yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short int) + sizeof (YYSTYPE))			\
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined (__GNUC__) && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  register YYSIZE_T yyi;		\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (0)
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (0)

#endif

#if defined (__STDC__) || defined (__cplusplus)
   typedef signed char yysigned_char;
#else
   typedef short int yysigned_char;
#endif

/* YYFINAL -- State number of the termination state. */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   967

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  88
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  257
/* YYNRULES -- Number of rules. */
#define YYNRULES  458
/* YYNRULES -- Number of states. */
#define YYNSTATES  749

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   337

#define YYTRANSLATE(YYX) 						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,    87,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    83,     2,    84,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    85,     2,    86,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned short int yyprhs[] =
{
       0,     0,     3,     9,    11,    12,    15,    16,    18,    21,
      22,    25,    27,    29,    32,    33,    34,    39,    41,    43,
      46,    47,    49,    51,    53,    55,    57,    58,    62,    63,
      64,    71,    74,    75,    79,    80,    81,    88,    90,    92,
      95,    96,    97,   107,   111,   114,   115,   116,   121,   122,
     127,   128,   129,   136,   137,   138,   145,   146,   147,   156,
     159,   160,   161,   166,   167,   172,   173,   178,   179,   184,
     185,   186,   187,   199,   200,   201,   209,   210,   215,   218,
     219,   221,   225,   228,   229,   231,   233,   235,   237,   239,
     241,   242,   243,   250,   251,   252,   259,   260,   263,   264,
     265,   272,   273,   274,   281,   283,   287,   288,   292,   294,
     296,   298,   300,   302,   306,   308,   310,   312,   314,   316,
     318,   320,   322,   324,   326,   328,   330,   332,   334,   336,
     338,   340,   342,   344,   346,   348,   350,   352,   354,   356,
     358,   360,   362,   364,   366,   368,   370,   372,   374,   376,
     378,   380,   382,   384,   386,   388,   390,   392,   394,   396,
     398,   400,   402,   404,   406,   408,   410,   412,   414,   416,
     418,   420,   422,   425,   428,   431,   434,   437,   440,   443,
     446,   449,   452,   455,   458,   461,   464,   467,   470,   473,
     476,   479,   482,   485,   488,   491,   494,   497,   500,   503,
     506,   509,   512,   515,   518,   521,   524,   527,   530,   533,
     536,   539,   542,   545,   548,   551,   554,   557,   560,   563,
     566,   569,   572,   575,   578,   581,   583,   585,   587,   589,
     591,   593,   595,   597,   598,   599,   605,   606,   607,   608,
     616,   618,   620,   621,   622,   623,   632,   635,   636,   638,
     639,   640,   641,   642,   643,   644,   645,   646,   664,   665,
     666,   667,   668,   669,   670,   671,   672,   690,   691,   692,
     693,   694,   695,   696,   697,   698,   699,   700,   701,   702,
     703,   704,   705,   737,   738,   739,   740,   741,   742,   743,
     744,   745,   746,   747,   748,   749,   750,   751,   752,   784,
     786,   788,   789,   790,   791,   799,   801,   803,   805,   806,
     810,   811,   815,   816,   817,   818,   825,   826,   827,   828,
     835,   836,   837,   838,   839,   848,   849,   850,   851,   852,
     861,   863,   867,   870,   871,   873,   877,   880,   881,   883,
     887,   890,   891,   893,   897,   900,   901,   903,   907,   910,
     911,   913,   917,   920,   921,   923,   927,   930,   931,   933,
     937,   940,   941,   943,   947,   950,   951,   953,   957,   960,
     961,   963,   967,   970,   971,   973,   977,   980,   981,   983,
     987,   990,   991,   993,   997,  1000,  1001,  1003,  1007,  1010,
    1011,  1013,  1017,  1020,  1021,  1023,  1027,  1030,  1031,  1033,
    1037,  1040,  1041,  1043,  1047,  1050,  1051,  1053,  1057,  1060,
    1061,  1063,  1067,  1070,  1071,  1072,  1073,  1074,  1082,  1083,
    1087,  1088,  1089,  1095,  1096,  1097,  1098,  1106,  1107,  1108,
    1109,  1117,  1118,  1119,  1120,  1121,  1131,  1132,  1136,  1137,
    1139,  1143,  1146,  1147,  1149,  1153,  1156,  1157,  1159,  1163,
    1166,  1167,  1169,  1173,  1176,  1177,  1179,  1183,  1186
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const short int yyrhs[] =
{
      89,     0,    -1,    90,    91,    93,    96,   101,    -1,     3,
      -1,    -1,     4,    92,    -1,    -1,    80,    -1,    93,    94,
      -1,    -1,     5,    95,    -1,    80,    -1,    77,    -1,    96,
      97,    -1,    -1,    -1,     6,    99,    98,   100,    -1,    77,
      -1,    77,    -1,   101,   102,    -1,    -1,   103,    -1,   111,
      -1,   133,    -1,   137,    -1,   140,    -1,    -1,   165,   104,
     144,    -1,    -1,    -1,    10,   164,   105,   165,   106,   144,
      -1,    11,   164,    -1,    -1,   165,   108,   144,    -1,    -1,
      -1,    10,   164,   109,   165,   110,   144,    -1,   113,    -1,
     124,    -1,   112,   111,    -1,    -1,    -1,     7,   165,   114,
      83,   116,    84,    85,   115,    86,    -1,   112,   107,   101,
      -1,   116,   117,    -1,    -1,    -1,    17,   169,   118,   167,
      -1,    -1,    18,   169,   119,   168,    -1,    -1,    -1,    20,
     169,   120,   166,   121,   170,    -1,    -1,    -1,    19,   169,
     122,   166,   123,   170,    -1,    -1,    -1,     8,   165,   125,
      83,   127,    84,   126,   143,    -1,   127,   128,    -1,    -1,
      -1,    17,   169,   129,   167,    -1,    -1,    18,   169,   130,
     168,    -1,    -1,    20,   169,   131,   166,    -1,    -1,    19,
     169,   132,   166,    -1,    -1,    -1,    -1,    12,   164,   134,
      87,   168,   135,    13,   164,   136,    87,   167,    -1,    -1,
      -1,    14,   164,   138,    87,   164,   139,   142,    -1,    -1,
      15,   164,   141,   142,    -1,    16,   164,    -1,    -1,   295,
      -1,    85,   145,    86,    -1,   145,   146,    -1,    -1,   161,
      -1,   147,    -1,   150,    -1,   154,    -1,   157,    -1,     1,
      -1,    -1,    -1,    17,   169,   148,   167,   149,   153,    -1,
      -1,    -1,    18,   169,   151,   168,   152,   153,    -1,    -1,
       9,   166,    -1,    -1,    -1,    20,   169,   155,   166,   156,
     160,    -1,    -1,    -1,    19,   169,   158,   166,   159,   160,
      -1,   170,    -1,   169,     9,   166,    -1,    -1,   166,   162,
     163,    -1,   133,    -1,   111,    -1,   137,    -1,   140,    -1,
     170,    -1,   169,     9,   166,    -1,    80,    -1,    80,    -1,
      80,    -1,    80,    -1,    80,    -1,    21,    -1,    22,    -1,
      23,    -1,    24,    -1,    25,    -1,    26,    -1,    27,    -1,
      28,    -1,    29,    -1,    30,    -1,    31,    -1,    32,    -1,
      33,    -1,    34,    -1,    35,    -1,    36,    -1,    37,    -1,
      38,    -1,    39,    -1,    40,    -1,    41,    -1,    42,    -1,
      43,    -1,    44,    -1,    45,    -1,    46,    -1,    47,    -1,
      48,    -1,    49,    -1,    50,    -1,    51,    -1,    52,    -1,
      53,    -1,    54,    -1,    55,    -1,    56,    -1,    57,    -1,
      58,    -1,    59,    -1,    60,    -1,    61,    -1,    62,    -1,
      63,    -1,    64,    -1,    65,    -1,    66,    -1,    67,    -1,
      68,    -1,    69,    -1,    70,    -1,    71,    -1,    72,    -1,
      73,    -1,    21,   269,    -1,    22,   271,    -1,    23,   273,
      -1,    24,   275,    -1,    25,   277,    -1,    26,   279,    -1,
      27,   281,    -1,    28,   283,    -1,    29,   285,    -1,    30,
     287,    -1,    31,   289,    -1,    32,   291,    -1,    33,   293,
      -1,    34,   295,    -1,    35,   297,    -1,    36,   299,    -1,
      37,   301,    -1,    38,   303,    -1,    39,   305,    -1,    40,
     307,    -1,    41,   309,    -1,    42,   174,    -1,    43,   175,
      -1,    44,   178,    -1,    45,   182,    -1,    46,   183,    -1,
      47,   184,    -1,    48,   189,    -1,    49,   190,    -1,    50,
     199,    -1,    51,   208,    -1,    52,   224,    -1,    53,   240,
      -1,    54,   241,    -1,    55,   245,    -1,    56,   246,    -1,
      57,   247,    -1,    58,   249,    -1,    59,   251,    -1,    60,
     255,    -1,    61,   259,    -1,    62,   264,    -1,    63,   335,
      -1,    64,   337,    -1,    65,   339,    -1,    66,   341,    -1,
      67,   343,    -1,    68,   311,    -1,    69,   315,    -1,    70,
     317,    -1,    71,   320,    -1,    72,   324,    -1,    73,   328,
      -1,    74,    -1,    75,    -1,    75,    -1,    76,    -1,    75,
      -1,    76,    -1,    78,    -1,    80,    -1,    -1,    -1,   173,
     176,   173,   177,   173,    -1,    -1,    -1,    -1,   173,   179,
     173,   180,   173,   181,   173,    -1,   172,    -1,   173,    -1,
      -1,    -1,    -1,   171,   185,   171,   186,   171,   187,   188,
      81,    -1,   188,   171,    -1,    -1,   171,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   172,   191,   172,   192,
     172,   193,   172,   194,   172,   195,   172,   196,   172,   197,
     172,   198,   172,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   173,   200,   173,   201,   173,   202,   173,   203,
     173,   204,   173,   205,   173,   206,   173,   207,   173,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   172,   209,   172,   210,   172,
     211,   172,   212,   172,   213,   172,   214,   172,   215,   172,
     216,   172,   217,   172,   218,   172,   219,   172,   220,   172,
     221,   172,   222,   172,   223,   172,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   173,   225,   173,   226,   173,   227,   173,   228,
     173,   229,   173,   230,   173,   231,   173,   232,   173,   233,
     173,   234,   173,   235,   173,   236,   173,   237,   173,   238,
     173,   239,   173,    -1,   103,    -1,    79,    -1,    -1,    -1,
      -1,   173,   242,   173,   243,   173,   244,   173,    -1,    77,
      -1,    80,    -1,   172,    -1,    -1,   172,   248,   172,    -1,
      -1,   173,   250,   173,    -1,    -1,    -1,    -1,   172,   252,
     172,   253,   172,   254,    -1,    -1,    -1,    -1,   173,   256,
     173,   257,   173,   258,    -1,    -1,    -1,    -1,    -1,   172,
     260,   172,   261,   172,   262,   172,   263,    -1,    -1,    -1,
      -1,    -1,   173,   265,   173,   266,   173,   267,   173,   268,
      -1,   174,    -1,    83,   270,    84,    -1,   270,   174,    -1,
      -1,   175,    -1,    83,   272,    84,    -1,   272,   175,    -1,
      -1,   178,    -1,    83,   274,    84,    -1,   274,   178,    -1,
      -1,   182,    -1,    83,   276,    84,    -1,   276,   182,    -1,
      -1,   183,    -1,    83,   278,    84,    -1,   278,   183,    -1,
      -1,   184,    -1,    83,   280,    84,    -1,   280,   184,    -1,
      -1,   189,    -1,    83,   282,    84,    -1,   282,   189,    -1,
      -1,   190,    -1,    83,   284,    84,    -1,   284,   190,    -1,
      -1,   199,    -1,    83,   286,    84,    -1,   286,   199,    -1,
      -1,   208,    -1,    83,   288,    84,    -1,   288,   208,    -1,
      -1,   224,    -1,    83,   290,    84,    -1,   290,   224,    -1,
      -1,   240,    -1,    83,   292,    84,    -1,   292,   240,    -1,
      -1,   241,    -1,    83,   294,    84,    -1,   294,   241,    -1,
      -1,   245,    -1,    83,   296,    84,    -1,   296,   245,    -1,
      -1,   246,    -1,    83,   298,    84,    -1,   298,   246,    -1,
      -1,   247,    -1,    83,   300,    84,    -1,   300,   247,    -1,
      -1,   249,    -1,    83,   302,    84,    -1,   302,   249,    -1,
      -1,   251,    -1,    83,   304,    84,    -1,   304,   251,    -1,
      -1,   255,    -1,    83,   306,    84,    -1,   306,   255,    -1,
      -1,   259,    -1,    83,   308,    84,    -1,   308,   259,    -1,
      -1,   264,    -1,    83,   310,    84,    -1,   310,   264,    -1,
      -1,    -1,    -1,    -1,   171,   312,   171,   313,   171,   314,
     171,    -1,    -1,   173,   316,   173,    -1,    -1,    -1,   173,
     318,   173,   319,   173,    -1,    -1,    -1,    -1,   173,   321,
     173,   322,   173,   323,   173,    -1,    -1,    -1,    -1,   173,
     325,   173,   326,   173,   327,   173,    -1,    -1,    -1,    -1,
      -1,   173,   329,   173,   330,   173,   331,   173,   332,   333,
      -1,    -1,   173,   334,   173,    -1,    -1,   311,    -1,    83,
     336,    84,    -1,   336,   311,    -1,    -1,   315,    -1,    83,
     338,    84,    -1,   338,   315,    -1,    -1,   317,    -1,    83,
     340,    84,    -1,   340,   317,    -1,    -1,   320,    -1,    83,
     342,    84,    -1,   342,   320,    -1,    -1,   324,    -1,    83,
     344,    84,    -1,   344,   324,    -1,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short int yyrline[] =
{
       0,   196,   196,   203,   204,   207,   208,   211,   214,   215,
     219,   224,   225,   232,   233,   238,   236,   243,   246,   249,
     250,   253,   254,   255,   256,   257,   260,   260,   263,   264,
     262,   266,   270,   270,   273,   274,   272,   278,   279,   282,
     283,   286,   286,   291,   294,   295,   299,   298,   302,   301,
     305,   306,   304,   309,   310,   308,   314,   315,   314,   319,
     320,   324,   323,   327,   326,   330,   329,   333,   332,   338,
     340,   342,   337,   349,   351,   348,   362,   361,   372,   374,
     377,   380,   383,   384,   387,   388,   389,   390,   391,   392,
     396,   397,   395,   402,   403,   401,   406,   408,   412,   413,
     411,   418,   419,   417,   423,   424,   428,   427,   436,   437,
     438,   439,   442,   443,   446,   449,   452,   455,   458,   461,
     462,   463,   464,   465,   466,   467,   468,   469,   470,   471,
     472,   473,   474,   475,   476,   477,   478,   479,   480,   481,
     482,   483,   484,   485,   486,   487,   488,   489,   490,   491,
     492,   493,   494,   495,   496,   497,   498,   499,   500,   501,
     502,   504,   505,   506,   507,   508,   509,   510,   511,   512,
     513,   514,   517,   518,   519,   520,   521,   522,   523,   524,
     525,   526,   527,   528,   529,   530,   531,   532,   533,   534,
     535,   536,   537,   538,   539,   540,   541,   542,   543,   544,
     545,   546,   547,   548,   549,   550,   551,   552,   553,   554,
     555,   556,   557,   558,   560,   561,   562,   563,   564,   565,
     566,   567,   568,   569,   570,   573,   574,   577,   578,   581,
     582,   585,   589,   592,   593,   592,   601,   602,   603,   601,
     611,   617,   623,   624,   626,   623,   636,   640,   643,   649,
     650,   651,   652,   653,   654,   655,   656,   649,   667,   668,
     669,   670,   671,   672,   673,   674,   667,   685,   686,   687,
     688,   689,   690,   691,   692,   693,   694,   695,   696,   697,
     698,   699,   685,   711,   712,   713,   714,   715,   716,   717,
     718,   719,   720,   721,   722,   723,   724,   725,   711,   737,
     738,   741,   742,   743,   741,   751,   755,   761,   767,   767,
     775,   775,   783,   784,   785,   783,   792,   793,   794,   792,
     801,   802,   803,   804,   801,   811,   812,   813,   814,   811,
     821,   822,   825,   826,   829,   830,   833,   834,   837,   838,
     841,   842,   845,   846,   849,   850,   853,   854,   857,   858,
     861,   862,   865,   866,   869,   870,   873,   874,   877,   878,
     881,   882,   885,   886,   889,   890,   893,   894,   897,   898,
     901,   902,   905,   906,   909,   910,   913,   914,   917,   918,
     921,   922,   925,   926,   929,   930,   933,   934,   937,   938,
     941,   942,   945,   946,   949,   950,   953,   954,   957,   958,
     961,   962,   965,   966,   969,   970,   973,   974,   977,   978,
     981,   982,   985,   986,   991,   992,   993,   991,  1002,  1002,
    1010,  1011,  1010,  1019,  1020,  1021,  1019,  1029,  1030,  1031,
    1029,  1039,  1040,  1041,  1043,  1039,  1051,  1051,  1061,  1069,
    1070,  1073,  1074,  1077,  1078,  1081,  1082,  1085,  1086,  1089,
    1090,  1093,  1094,  1097,  1098,  1101,  1102,  1105,  1106
};
#endif

#if YYDEBUG || YYERROR_VERBOSE
/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TOK_HEADER", "TOK_PROFILE",
  "TOK_COMPONENT", "TOK_META", "TOK_PROTO", "TOK_EXTERNPROTO", "TOK_IS",
  "TOK_DEF", "TOK_USE", "TOK_ROUTE", "TOK_TO", "TOK_IMPORT", "TOK_EXPORT",
  "TOK_AS", "TOK_eventIn", "TOK_eventOut", "TOK_exposedField", "TOK_field",
  "TOK_MFBool", "TOK_MFColor", "TOK_MFColorRGBA", "TOK_MFDouble",
  "TOK_MFFloat", "TOK_MFImage", "TOK_MFInt32", "TOK_MFMatrix3d",
  "TOK_MFMatrix3f", "TOK_MFMatrix4d", "TOK_MFMatrix4f", "TOK_MFNode",
  "TOK_MFRotation", "TOK_MFString", "TOK_MFTime", "TOK_MFVec2d",
  "TOK_MFVec2f", "TOK_MFVec3d", "TOK_MFVec3f", "TOK_MFVec4d",
  "TOK_MFVec4f", "TOK_SFBool", "TOK_SFColor", "TOK_SFColorRGBA",
  "TOK_SFDouble", "TOK_SFFloat", "TOK_SFImage", "TOK_SFInt32",
  "TOK_SFMatrix3d", "TOK_SFMatrix3f", "TOK_SFMatrix4d", "TOK_SFMatrix4f",
  "TOK_SFNode", "TOK_SFRotation", "TOK_SFString", "TOK_SFTime",
  "TOK_SFVec2d", "TOK_SFVec2f", "TOK_SFVec3d", "TOK_SFVec3f",
  "TOK_SFVec4d", "TOK_SFVec4f", "TOK_MFColor4i", "TOK_MFPnt2f",
  "TOK_MFPnt3f", "TOK_MFPnt4f", "TOK_MFPlane", "TOK_SFColor4i",
  "TOK_SFPnt2f", "TOK_SFPnt3f", "TOK_SFPnt4f", "TOK_SFPlane",
  "TOK_SFVolume", "TOK_hex", "TOK_int32", "TOK_double", "TOK_string",
  "TOK_bool", "TOK_NULL", "TOK_Id", "TOK_ImageFinished", "TOK_Error",
  "'['", "']'", "'{'", "'}'", "'.'", "$accept", "x3dScene",
  "headerStatement", "profileStatement", "profileNameId",
  "componentStatements", "componentStatement", "componentNameId",
  "metaStatements", "metaStatement", "@1", "metakey", "metavalue",
  "statements", "statement", "nodeStatement", "@2", "@3", "@4",
  "rootNodeStatement", "@5", "@6", "@7", "protoStatement",
  "protoStatements", "proto", "@8", "protoBody", "interfaceDeclarations",
  "interfaceDeclaration", "@9", "@10", "@11", "@12", "@13", "@14",
  "externproto", "@15", "@16", "externInterfaceDeclarations",
  "externInterfaceDeclaration", "@17", "@18", "@19", "@20",
  "routeStatement", "@21", "@22", "@23", "importStatement", "@24", "@25",
  "exportStatement", "@26", "asStatement", "URLList", "node", "scriptBody",
  "scriptBodyElement", "eventInDeclaration", "@27", "@28",
  "eventOutDeclaration", "@29", "@30", "eventDeclarationEnd",
  "fieldDeclaration", "@31", "@32", "exposedFieldDeclaration", "@33",
  "@34", "fieldDeclarationEnd", "nodeBodyElement", "@35", "fieldEnd",
  "nodeNameId", "nodeTypeId", "fieldId", "eventInId", "eventOutId",
  "fieldType", "fieldValue", "int32", "double", "float", "sfboolValue",
  "sfcolorValue", "@36", "@37", "sfcolorRGBAValue", "@38", "@39", "@40",
  "sfdoubleValue", "sffloatValue", "sfimageValue", "@41", "@42", "@43",
  "pixels", "sfint32Value", "sfmatrix3dValue", "@44", "@45", "@46", "@47",
  "@48", "@49", "@50", "@51", "sfmatrix3fValue", "@52", "@53", "@54",
  "@55", "@56", "@57", "@58", "@59", "sfmatrix4dValue", "@60", "@61",
  "@62", "@63", "@64", "@65", "@66", "@67", "@68", "@69", "@70", "@71",
  "@72", "@73", "@74", "sfmatrix4fValue", "@75", "@76", "@77", "@78",
  "@79", "@80", "@81", "@82", "@83", "@84", "@85", "@86", "@87", "@88",
  "@89", "sfnodeValue", "sfrotationValue", "@90", "@91", "@92",
  "sfstringValue", "sftimeValue", "sfvec2dValue", "@93", "sfvec2fValue",
  "@94", "sfvec3dValue", "@95", "@96", "@97", "sfvec3fValue", "@98", "@99",
  "@100", "sfvec4dValue", "@101", "@102", "@103", "@104", "sfvec4fValue",
  "@105", "@106", "@107", "@108", "mfboolValue", "sfboolValues",
  "mfcolorValue", "sfcolorValues", "mfcolorRGBAValue", "sfcolorRGBAValues",
  "mfdoubleValue", "sfdoubleValues", "mffloatValue", "sffloatValues",
  "mfimageValue", "sfimageValues", "mfint32Value", "sfint32Values",
  "mfmatrix3dValue", "sfmatrix3dValues", "mfmatrix3fValue",
  "sfmatrix3fValues", "mfmatrix4dValue", "sfmatrix4dValues",
  "mfmatrix4fValue", "sfmatrix4fValues", "mfnodeValue", "sfnodeValues",
  "mfrotationValue", "sfrotationValues", "mfstringValue", "sfstringValues",
  "mftimeValue", "sftimeValues", "mfvec2dValue", "sfvec2dValues",
  "mfvec2fValue", "sfvec2fValues", "mfvec3dValue", "sfvec3dValues",
  "mfvec3fValue", "sfvec3fValues", "mfvec4dValue", "sfvec4dValues",
  "mfvec4fValue", "sfvec4fValues", "sfcolor4iValue", "@109", "@110",
  "@111", "sfpnt2fValue", "@112", "sfpnt3fValue", "@113", "@114",
  "sfpnt4fValue", "@115", "@116", "@117", "sfplaneValue", "@118", "@119",
  "@120", "sfVolumeValue", "@121", "@122", "@123", "@124",
  "sfVolumeValueEnd", "@125", "mfcolor4iValue", "sfcolor4iValues",
  "mfpnt2fValue", "sfpnt2fValues", "mfpnt3fValue", "sfpnt3fValues",
  "mfpnt4fValue", "sfpnt4fValues", "mfplaneValue", "sfplaneValues", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const unsigned short int yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,    91,    93,   123,   125,    46
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned short int yyr1[] =
{
       0,    88,    89,    90,    90,    91,    91,    92,    93,    93,
      94,    95,    95,    96,    96,    98,    97,    99,   100,   101,
     101,   102,   102,   102,   102,   102,   104,   103,   105,   106,
     103,   103,   108,   107,   109,   110,   107,   111,   111,   112,
     112,   114,   113,   115,   116,   116,   118,   117,   119,   117,
     120,   121,   117,   122,   123,   117,   125,   126,   124,   127,
     127,   129,   128,   130,   128,   131,   128,   132,   128,   134,
     135,   136,   133,   138,   139,   137,   141,   140,   142,   142,
     143,   144,   145,   145,   146,   146,   146,   146,   146,   146,
     148,   149,   147,   151,   152,   150,   153,   153,   155,   156,
     154,   158,   159,   157,   160,   160,   162,   161,   161,   161,
     161,   161,   163,   163,   164,   165,   166,   167,   168,   169,
     169,   169,   169,   169,   169,   169,   169,   169,   169,   169,
     169,   169,   169,   169,   169,   169,   169,   169,   169,   169,
     169,   169,   169,   169,   169,   169,   169,   169,   169,   169,
     169,   169,   169,   169,   169,   169,   169,   169,   169,   169,
     169,   169,   169,   169,   169,   169,   169,   169,   169,   169,
     169,   169,   170,   170,   170,   170,   170,   170,   170,   170,
     170,   170,   170,   170,   170,   170,   170,   170,   170,   170,
     170,   170,   170,   170,   170,   170,   170,   170,   170,   170,
     170,   170,   170,   170,   170,   170,   170,   170,   170,   170,
     170,   170,   170,   170,   170,   170,   170,   170,   170,   170,
     170,   170,   170,   170,   170,   171,   171,   172,   172,   173,
     173,   174,   174,   176,   177,   175,   179,   180,   181,   178,
     182,   183,   185,   186,   187,   184,   188,   188,   189,   191,
     192,   193,   194,   195,   196,   197,   198,   190,   200,   201,
     202,   203,   204,   205,   206,   207,   199,   209,   210,   211,
     212,   213,   214,   215,   216,   217,   218,   219,   220,   221,
     222,   223,   208,   225,   226,   227,   228,   229,   230,   231,
     232,   233,   234,   235,   236,   237,   238,   239,   224,   240,
     240,   242,   243,   244,   241,   245,   245,   246,   248,   247,
     250,   249,   252,   253,   254,   251,   256,   257,   258,   255,
     260,   261,   262,   263,   259,   265,   266,   267,   268,   264,
     269,   269,   270,   270,   271,   271,   272,   272,   273,   273,
     274,   274,   275,   275,   276,   276,   277,   277,   278,   278,
     279,   279,   280,   280,   281,   281,   282,   282,   283,   283,
     284,   284,   285,   285,   286,   286,   287,   287,   288,   288,
     289,   289,   290,   290,   291,   291,   292,   292,   293,   293,
     294,   294,   295,   295,   296,   296,   297,   297,   298,   298,
     299,   299,   300,   300,   301,   301,   302,   302,   303,   303,
     304,   304,   305,   305,   306,   306,   307,   307,   308,   308,
     309,   309,   310,   310,   312,   313,   314,   311,   316,   315,
     318,   319,   317,   321,   322,   323,   320,   325,   326,   327,
     324,   329,   330,   331,   332,   328,   334,   333,   333,   335,
     335,   336,   336,   337,   337,   338,   338,   339,   339,   340,
     340,   341,   341,   342,   342,   343,   343,   344,   344
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     5,     1,     0,     2,     0,     1,     2,     0,
       2,     1,     1,     2,     0,     0,     4,     1,     1,     2,
       0,     1,     1,     1,     1,     1,     0,     3,     0,     0,
       6,     2,     0,     3,     0,     0,     6,     1,     1,     2,
       0,     0,     9,     3,     2,     0,     0,     4,     0,     4,
       0,     0,     6,     0,     0,     6,     0,     0,     8,     2,
       0,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       0,     0,    11,     0,     0,     7,     0,     4,     2,     0,
       1,     3,     2,     0,     1,     1,     1,     1,     1,     1,
       0,     0,     6,     0,     0,     6,     0,     2,     0,     0,
       6,     0,     0,     6,     1,     3,     0,     3,     1,     1,
       1,     1,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     0,     5,     0,     0,     0,     7,
       1,     1,     0,     0,     0,     8,     2,     0,     1,     0,
       0,     0,     0,     0,     0,     0,     0,    17,     0,     0,
       0,     0,     0,     0,     0,     0,    17,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    31,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    31,     1,
       1,     0,     0,     0,     7,     1,     1,     1,     0,     3,
       0,     3,     0,     0,     0,     6,     0,     0,     0,     6,
       0,     0,     0,     0,     8,     0,     0,     0,     0,     8,
       1,     3,     2,     0,     1,     3,     2,     0,     1,     3,
       2,     0,     1,     3,     2,     0,     1,     3,     2,     0,
       1,     3,     2,     0,     1,     3,     2,     0,     1,     3,
       2,     0,     1,     3,     2,     0,     1,     3,     2,     0,
       1,     3,     2,     0,     1,     3,     2,     0,     1,     3,
       2,     0,     1,     3,     2,     0,     1,     3,     2,     0,
       1,     3,     2,     0,     1,     3,     2,     0,     1,     3,
       2,     0,     1,     3,     2,     0,     1,     3,     2,     0,
       1,     3,     2,     0,     0,     0,     0,     7,     0,     3,
       0,     0,     5,     0,     0,     0,     7,     0,     0,     0,
       7,     0,     0,     0,     0,     9,     0,     3,     0,     1,
       3,     2,     0,     1,     3,     2,     0,     1,     3,     2,
       0,     1,     3,     2,     0,     1,     3,     2,     0
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned short int yydefact[] =
{
       4,     3,     0,     6,     1,     0,     9,     7,     5,    14,
       0,     8,    20,    12,    11,    10,     0,    13,     2,    17,
      15,     0,     0,     0,     0,     0,     0,     0,   115,    19,
      21,    22,    37,    38,    23,    24,    25,    26,     0,    41,
      56,   114,    28,    31,    69,    73,    76,     0,    18,    16,
       0,     0,     0,     0,     0,    79,    83,    27,    45,    60,
      29,     0,     0,     0,    77,     0,     0,     0,     0,   118,
      70,    74,    78,    89,     0,     0,     0,     0,   116,    81,
     109,   108,   110,   111,    82,    85,    86,    87,    88,    84,
     106,     0,     0,     0,     0,     0,    44,     0,     0,     0,
       0,    57,    59,    30,     0,    79,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   171,    90,
      93,   101,    98,     0,    46,    48,    53,    50,    40,    61,
      63,    67,    65,     0,     0,    75,     0,     0,     0,     0,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,   141,   142,   143,   144,   145,   146,   147,   148,
     149,   150,   151,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   107,     0,   112,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   305,   306,   385,    58,
     382,    80,    71,   117,    91,    94,   102,    99,   231,   232,
     333,   330,   172,   229,   230,   337,   233,   334,   173,   341,
     236,   338,   174,   227,   228,   345,   240,   342,   175,   349,
     241,   346,   176,   225,   226,   353,   242,   350,   177,   357,
     248,   354,   178,   361,   249,   358,   179,   365,   258,   362,
     180,   369,   267,   366,   181,   373,   283,   370,   182,   300,
     377,   299,   374,   183,   381,   301,   378,   184,   185,   389,
     307,   386,   186,   393,   308,   390,   187,   397,   310,   394,
     188,   401,   312,   398,   189,   405,   316,   402,   190,   409,
     320,   406,   191,   413,   325,   410,   192,   193,   194,   195,
     196,   197,   198,   199,   200,   201,   202,   203,   204,   205,
     206,   207,   208,   209,   210,   211,   212,   213,   442,   414,
     439,   214,   446,   418,   443,   215,   450,   420,   447,   216,
     454,   423,   451,   217,   458,   427,   455,   218,   219,   220,
     221,   222,   223,   431,   224,     0,    47,    49,    54,    51,
       0,    20,    39,    32,    42,    62,    64,    68,    66,     0,
       0,    96,    96,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     113,     0,     0,    34,    43,     0,   383,   384,     0,     0,
      92,    95,   103,     0,   104,   100,   331,   332,   335,   336,
     234,   339,   340,   237,   343,   344,   347,   348,   351,   352,
     243,   355,   356,   359,   360,   250,   363,   364,   259,   367,
     368,   268,   371,   372,   284,   375,   376,   379,   380,   302,
     387,   388,   391,   392,   309,   395,   396,   311,   399,   400,
     313,   403,   404,   317,   407,   408,   321,   411,   412,   326,
     440,   441,   415,   444,   445,   419,   448,   449,   421,   452,
     453,   424,   456,   457,   428,   432,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    55,
      52,     0,    33,    72,    97,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    35,   105,   235,   238,   244,   251,   260,
     269,   285,   303,   314,   318,   322,   327,   416,   422,   425,
     429,   433,     0,     0,   247,     0,     0,     0,     0,     0,
     315,   319,     0,     0,     0,     0,     0,     0,    36,   239,
       0,   252,   261,   270,   286,   304,   323,   328,   417,   426,
     430,   434,   245,   246,     0,     0,     0,     0,   324,   329,
     438,   253,   262,   271,   287,   436,   435,     0,     0,     0,
       0,     0,   254,   263,   272,   288,   437,     0,     0,     0,
       0,   255,   264,   273,   289,     0,     0,     0,     0,   256,
     265,   274,   290,     0,     0,     0,     0,   257,   266,   275,
     291,     0,     0,   276,   292,     0,     0,   277,   293,     0,
       0,   278,   294,     0,     0,   279,   295,     0,     0,   280,
     296,     0,     0,   281,   297,     0,     0,   282,   298
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short int yydefgoto[] =
{
      -1,     2,     3,     6,     8,     9,    11,    15,    12,    17,
      38,    20,    49,    18,    29,   311,    47,    52,    68,   401,
     465,   601,   642,    31,   240,    32,    50,   241,    66,    96,
     236,   237,   239,   462,   238,   461,    33,    51,   173,    67,
     102,   242,   243,   245,   244,    34,    53,   104,   410,    35,
      54,   105,    36,    55,    64,   249,    57,    65,    84,    85,
     176,   411,    86,   177,   412,   470,    87,   179,   414,    88,
     178,   413,   472,    89,   163,   233,    42,    37,    90,   254,
      70,   473,   474,   286,   276,   266,   261,   267,   417,   606,
     271,   419,   607,   643,   277,   281,   287,   423,   608,   644,
     660,   291,   295,   426,   609,   645,   674,   687,   697,   705,
     713,   299,   428,   610,   646,   675,   688,   698,   706,   714,
     303,   430,   611,   647,   676,   689,   699,   707,   715,   721,
     725,   729,   733,   737,   741,   745,   307,   432,   612,   648,
     677,   690,   700,   708,   716,   722,   726,   730,   734,   738,
     742,   746,   312,   316,   435,   613,   649,   250,   321,   325,
     438,   329,   440,   333,   442,   614,   650,   337,   444,   615,
     651,   341,   446,   616,   652,   678,   345,   448,   617,   653,
     679,   262,   415,   268,   416,   272,   418,   278,   420,   282,
     421,   288,   422,   292,   424,   296,   425,   300,   427,   304,
     429,   308,   431,   313,   433,   317,   434,   318,   409,   322,
     436,   326,   437,   330,   439,   334,   441,   338,   443,   342,
     445,   346,   447,   370,   450,   618,   654,   374,   452,   378,
     454,   619,   382,   456,   620,   655,   386,   458,   621,   656,
     394,   459,   622,   657,   680,   686,   691,   371,   449,   375,
     451,   379,   453,   383,   455,   387,   457
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -204
static const short int yypact[] =
{
      32,  -204,    87,   122,  -204,   -41,  -204,  -204,  -204,    60,
     120,  -204,   135,  -204,  -204,  -204,    78,  -204,    81,  -204,
    -204,    80,    80,    95,    95,    95,    95,    95,  -204,  -204,
    -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,   111,  -204,
    -204,  -204,  -204,  -204,  -204,  -204,  -204,   101,  -204,  -204,
     133,   145,    80,   112,   127,   176,  -204,  -204,  -204,  -204,
    -204,   153,    95,    95,  -204,   110,   114,   134,   101,  -204,
    -204,  -204,  -204,  -204,   560,   560,   560,   560,  -204,  -204,
    -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,
    -204,   560,   560,   560,   560,   146,  -204,   560,   560,   560,
     560,  -204,  -204,  -204,   224,   176,  -204,  -204,  -204,  -204,
    -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,
    -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,
    -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,
    -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,
    -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,
    -204,  -204,  -204,   841,  -204,  -204,  -204,  -204,  -204,  -204,
    -204,  -204,  -204,   237,    95,  -204,   163,   153,   166,   166,
     255,   151,   282,   284,   371,     7,    84,   373,   376,   396,
     408,    64,   410,   237,   412,   424,   427,   430,   439,   441,
     455,    68,    37,    37,    89,    37,   137,   137,    89,    37,
      89,    37,    94,    37,   144,    89,    89,    37,    89,    37,
      89,    37,    88,   473,   489,   494,   559,   137,    37,    37,
      37,    37,    37,  -204,   242,  -204,   163,   153,   166,   166,
      70,   173,   163,   153,   166,   166,  -204,  -204,  -204,  -204,
    -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,
    -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,
    -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,
    -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,
    -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,
    -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,
    -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,
    -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,
    -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,
    -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,
    -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,
    -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,
    -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,
    -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,
    -204,  -204,  -204,  -204,  -204,   166,  -204,  -204,  -204,  -204,
      95,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,    39,
     175,   258,   258,   841,   841,    -8,    93,    37,   103,    37,
     105,   107,    61,   137,    65,   109,    89,   119,    37,   126,
      89,   129,    37,    58,   131,    37,   208,   222,    89,   225,
      37,   232,    89,   243,    37,   253,    89,   264,    37,    82,
     137,   266,    37,   268,    37,   278,    37,   280,    37,    37,
    -204,   894,   894,  -204,    81,   101,  -204,  -204,   163,   166,
    -204,  -204,  -204,   261,  -204,  -204,  -204,  -204,  -204,  -204,
    -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,
    -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,
    -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,
    -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,
    -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,
    -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,
    -204,  -204,  -204,  -204,  -204,  -204,   255,   151,   282,   284,
     371,     7,    84,   373,   376,   396,   408,    64,   410,   237,
     412,   424,   427,   430,   439,   441,   455,    68,    37,    37,
      89,    37,   137,   137,    89,    37,    89,    37,    94,    37,
     144,    89,    89,    37,    89,    37,    89,    37,    88,   473,
     489,   494,   559,   137,    37,    37,    37,    37,    37,  -204,
    -204,    80,  -204,  -204,  -204,   166,    37,    37,   137,    89,
      37,    89,    37,    37,    89,    37,    89,    37,   137,    37,
      37,    37,    37,  -204,  -204,  -204,  -204,  -204,  -204,  -204,
    -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,
    -204,  -204,   101,    37,  -204,    89,    37,    89,    37,    37,
    -204,  -204,    89,    37,   137,    37,    37,    37,  -204,  -204,
     212,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,
    -204,  -204,  -204,  -204,    89,    37,    89,    37,  -204,  -204,
      37,  -204,  -204,  -204,  -204,  -204,  -204,    89,    37,    89,
      37,    37,  -204,  -204,  -204,  -204,  -204,    89,    37,    89,
      37,  -204,  -204,  -204,  -204,    89,    37,    89,    37,  -204,
    -204,  -204,  -204,    89,    37,    89,    37,  -204,  -204,  -204,
    -204,    89,    37,  -204,  -204,    89,    37,  -204,  -204,    89,
      37,  -204,  -204,    89,    37,  -204,  -204,    89,    37,  -204,
    -204,    89,    37,  -204,  -204,    89,    37,  -204,  -204
};

/* YYPGOTO[NTERM-NUM].  */
static const short int yypgoto[] =
{
    -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,
    -204,  -204,  -204,  -113,  -204,   -14,  -204,  -204,  -204,  -204,
    -204,  -204,  -204,   -32,  -204,  -204,  -204,  -204,  -204,  -204,
    -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,
    -204,  -204,  -204,  -204,  -204,   226,  -204,  -204,  -204,   239,
    -204,  -204,   247,  -204,   197,  -204,   -66,  -204,  -204,  -204,
    -204,  -204,  -204,  -204,  -204,   -89,  -204,  -204,  -204,  -204,
    -204,  -204,   -84,  -204,  -204,  -204,    35,   -21,  -124,  -169,
     -67,     9,  -115,  -128,   116,  -179,  -195,  -194,  -204,  -204,
    -193,  -204,  -204,  -204,  -197,  -191,  -190,  -204,  -204,  -204,
    -204,  -189,  -196,  -204,  -204,  -204,  -204,  -204,  -204,  -204,
    -204,  -186,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,
    -185,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,
    -204,  -204,  -204,  -204,  -204,  -204,  -184,  -204,  -204,  -204,
    -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,
    -204,  -204,  -183,  -198,  -204,  -204,  -204,  -192,  -178,  -180,
    -204,  -176,  -204,  -175,  -204,  -204,  -204,  -162,  -204,  -204,
    -204,  -200,  -204,  -204,  -204,  -204,  -165,  -204,  -204,  -204,
    -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,
    -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,
    -204,  -204,  -204,  -204,  -204,  -204,  -204,   152,  -204,  -204,
    -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,
    -204,  -204,  -204,  -164,  -204,  -204,  -204,  -157,  -204,  -163,
    -204,  -204,  -166,  -204,  -204,  -204,  -203,  -204,  -204,  -204,
    -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,
    -204,  -204,  -204,  -204,  -204,  -204,  -204
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const unsigned short int yytable[] =
{
      39,    40,   103,   270,    30,   280,   347,   350,   348,   298,
     349,   306,   354,   315,   351,   359,   352,   328,   353,   336,
     366,   344,   360,   355,   270,   356,   280,   357,   392,   358,
     298,    60,   306,    80,   315,     1,   362,   361,   328,     7,
     336,   363,   344,   364,   373,   377,   381,   385,   235,   373,
     377,   381,   385,   393,   256,   257,   367,   365,   290,    43,
      44,    45,    46,   388,   391,    10,   390,   396,    23,    24,
     258,   389,   259,   405,    23,    24,   476,    21,    22,   290,
     400,   283,   284,   159,   160,   161,   162,     4,    21,    22,
     285,    23,    24,    25,   369,    26,    27,    71,    72,   369,
     164,   165,   166,   167,    23,    24,   169,   170,   171,   172,
     255,    73,   263,   264,   398,   399,   246,    21,    22,   247,
     407,   408,    25,   466,    26,    27,     5,    74,    75,    76,
      77,    91,    92,    93,    94,   283,   284,   309,    28,   283,
     284,    16,   505,   309,    28,   488,   258,   310,   259,   491,
      28,    97,    98,    99,   100,    19,   283,   284,   283,   284,
      28,    28,   283,   284,   273,   274,   530,   289,   263,   264,
     397,   368,   234,   309,    28,    41,   406,   478,   263,   264,
     273,   274,   263,   264,   273,   274,    56,   481,    48,   484,
      78,   486,    63,   493,   263,   264,    79,    13,    95,    61,
      14,   273,   274,   496,   263,   264,   263,   264,   402,   252,
     499,   283,   284,   502,    62,   507,    58,   467,   101,   403,
     477,   246,   479,   485,   247,   482,   263,   264,    59,   494,
     487,   168,   489,    69,   265,   492,   508,   174,   480,   270,
     483,   497,   280,   253,   500,   525,    78,   503,   298,   498,
     506,   395,   306,   504,   543,   315,   509,   513,   511,   404,
     328,   517,   468,   516,   336,   523,   519,   469,   344,   529,
     605,   460,   373,   535,   377,   538,   381,   541,   385,   544,
     545,   522,   528,   273,   274,   531,   283,   284,   464,   540,
     537,    81,   510,   672,   534,   490,   290,   273,   274,   603,
     263,   264,   175,   294,    82,   302,   512,   273,   274,   515,
     320,   324,    83,   332,   246,   340,   518,   247,   263,   264,
     248,   369,   532,   471,   294,   251,   302,   521,   273,   274,
     475,   320,   324,   258,   332,   259,   340,   524,   260,   263,
     264,   263,   264,   263,   264,   604,   599,   600,   527,     0,
     533,     0,   536,   263,   264,   263,   264,   263,   264,   273,
     274,     0,   539,     0,   542,   269,     0,   275,     0,   270,
       0,   280,   347,   350,   348,   298,   349,   306,   354,   315,
     351,   359,   352,   328,   353,   336,   366,   344,   360,   355,
     270,   356,   280,   357,   392,   358,   298,     0,   306,   602,
     315,     0,   362,   361,   328,     0,   336,   363,   344,   364,
     373,   377,   381,   385,     0,   373,   377,   381,   385,   393,
       0,     0,   367,   365,   290,     0,     0,   625,   626,   388,
     391,   629,   390,   631,   632,   463,   634,   389,   636,     0,
     638,   639,   640,   641,     0,   290,   263,   264,   273,   274,
      30,   263,   264,     0,   279,     0,   293,     0,     0,   297,
     369,     0,     0,     0,   659,   369,     0,   662,     0,   664,
     665,   273,   274,     0,   667,     0,   669,   670,   671,   301,
     627,   624,     0,   263,   264,   263,   264,   273,   274,     0,
     637,   305,     0,   314,     0,   319,   682,     0,   684,   273,
     274,   685,   263,   264,     0,   273,   274,   323,     0,   693,
     327,   695,   696,   331,   263,   264,   273,   274,     0,   702,
       0,   704,   335,     0,   339,     0,   668,   710,     0,   712,
     263,   264,   673,     0,     0,   718,     0,   720,   343,     0,
       0,   294,   495,   724,     0,   302,   501,   728,   263,   264,
       0,   732,   320,   324,   514,   736,   372,   332,   520,   740,
       0,   340,   526,   744,   263,   264,     0,   748,     0,   263,
     264,     0,   376,     0,     0,     0,   658,   380,     0,     0,
     623,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   263,   264,     0,     0,     0,     0,
       0,     0,   384,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   294,
       0,   302,     0,     0,     0,     0,   320,   324,     0,   332,
       0,   340,     0,     0,     0,     0,     0,     0,     0,     0,
     294,     0,   302,     0,     0,     0,     0,   320,   324,     0,
     332,     0,   340,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   628,     0,   630,     0,     0,
     633,     0,   635,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   661,     0,   663,     0,     0,     0,     0,   666,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     681,     0,   683,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   692,     0,   694,     0,     0,     0,     0,
       0,     0,     0,   701,     0,   703,     0,     0,     0,     0,
       0,   709,     0,   711,     0,     0,     0,     0,     0,   717,
       0,   719,     0,     0,     0,     0,     0,   723,     0,     0,
       0,   727,     0,     0,     0,   731,     0,     0,     0,   735,
       0,     0,     0,   739,     0,     0,     0,   743,     0,     0,
       0,   747,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   200,   201,   202,   203,   204,   205,   206,   207,
     208,   209,   210,   211,   212,   213,   214,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,   225,   226,   227,
     228,   229,   230,   231,   232,   546,   547,   548,   549,   550,
     551,   552,   553,   554,   555,   556,   557,   558,   559,   560,
     561,   562,   563,   564,   565,   566,   567,   568,   569,   570,
     571,   572,   573,   574,   575,   576,   577,   578,   579,   580,
     581,   582,   583,   584,   585,   586,   587,   588,   589,   590,
     591,   592,   593,   594,   595,   596,   597,   598
};

static const short int yycheck[] =
{
      21,    22,    68,   182,    18,   184,   201,   204,   202,   188,
     203,   190,   208,   192,   205,   213,   206,   196,   207,   198,
     220,   200,   214,   209,   203,   210,   205,   211,   231,   212,
     209,    52,   211,    65,   213,     3,   216,   215,   217,    80,
     219,   217,   221,   218,   223,   224,   225,   226,   163,   228,
     229,   230,   231,   232,   178,   179,   221,   219,   186,    24,
      25,    26,    27,   227,   230,     5,   229,   236,    10,    11,
      78,   228,    80,   242,    10,    11,    84,     7,     8,   207,
      10,    74,    75,    74,    75,    76,    77,     0,     7,     8,
      83,    10,    11,    12,   222,    14,    15,    62,    63,   227,
      91,    92,    93,    94,    10,    11,    97,    98,    99,   100,
     177,     1,    75,    76,   238,   239,    77,     7,     8,    80,
     244,   245,    12,    84,    14,    15,     4,    17,    18,    19,
      20,    17,    18,    19,    20,    74,    75,    79,    80,    74,
      75,     6,    84,    79,    80,    84,    78,    83,    80,    84,
      80,    17,    18,    19,    20,    77,    74,    75,    74,    75,
      80,    80,    74,    75,    75,    76,    84,    83,    75,    76,
     237,    83,   163,    79,    80,    80,   243,    84,    75,    76,
      75,    76,    75,    76,    75,    76,    85,    84,    77,    84,
      80,    84,    16,    84,    75,    76,    86,    77,    84,    87,
      80,    75,    76,    84,    75,    76,    75,    76,   240,   174,
      84,    74,    75,    84,    87,    84,    83,   409,    84,   240,
     415,    77,   416,   420,    80,   418,    75,    76,    83,   425,
     421,    85,   422,    80,    83,   424,   434,    13,   417,   418,
     419,   427,   421,    80,   429,   445,    80,   431,   427,   428,
     433,     9,   431,   432,   457,   434,   435,   437,   436,    86,
     439,   440,    87,   439,   443,   444,   441,     9,   447,   448,
       9,   395,   451,   452,   453,   454,   455,   456,   457,   458,
     459,   443,   447,    75,    76,   449,    74,    75,   401,   455,
     453,    65,    84,    81,   451,   423,   424,    75,    76,   468,
      75,    76,   105,   187,    65,   189,    84,    75,    76,    84,
     194,   195,    65,   197,    77,   199,    84,    80,    75,    76,
      83,   449,   450,   412,   208,   173,   210,    84,    75,    76,
     414,   215,   216,    78,   218,    80,   220,    84,    83,    75,
      76,    75,    76,    75,    76,   469,   461,   462,    84,    -1,
      84,    -1,    84,    75,    76,    75,    76,    75,    76,    75,
      76,    -1,    84,    -1,    84,    83,    -1,    83,    -1,   548,
      -1,   550,   567,   570,   568,   554,   569,   556,   574,   558,
     571,   579,   572,   562,   573,   564,   586,   566,   580,   575,
     569,   576,   571,   577,   597,   578,   575,    -1,   577,   465,
     579,    -1,   582,   581,   583,    -1,   585,   583,   587,   584,
     589,   590,   591,   592,    -1,   594,   595,   596,   597,   598,
      -1,    -1,   587,   585,   552,    -1,    -1,   606,   607,   593,
     596,   610,   595,   612,   613,   400,   615,   594,   617,    -1,
     619,   620,   621,   622,    -1,   573,    75,    76,    75,    76,
     464,    75,    76,    -1,    83,    -1,    83,    -1,    -1,    83,
     588,    -1,    -1,    -1,   643,   593,    -1,   646,    -1,   648,
     649,    75,    76,    -1,   653,    -1,   655,   656,   657,    83,
     608,   605,    -1,    75,    76,    75,    76,    75,    76,    -1,
     618,    83,    -1,    83,    -1,    83,   675,    -1,   677,    75,
      76,   680,    75,    76,    -1,    75,    76,    83,    -1,   688,
      83,   690,   691,    83,    75,    76,    75,    76,    -1,   698,
      -1,   700,    83,    -1,    83,    -1,   654,   706,    -1,   708,
      75,    76,   660,    -1,    -1,   714,    -1,   716,    83,    -1,
      -1,   425,   426,   722,    -1,   429,   430,   726,    75,    76,
      -1,   730,   436,   437,   438,   734,    83,   441,   442,   738,
      -1,   445,   446,   742,    75,    76,    -1,   746,    -1,    75,
      76,    -1,    83,    -1,    -1,    -1,   642,    83,    -1,    -1,
     601,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    75,    76,    -1,    -1,    -1,    -1,
      -1,    -1,    83,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   553,
      -1,   555,    -1,    -1,    -1,    -1,   560,   561,    -1,   563,
      -1,   565,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     574,    -1,   576,    -1,    -1,    -1,    -1,   581,   582,    -1,
     584,    -1,   586,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   609,    -1,   611,    -1,    -1,
     614,    -1,   616,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   645,    -1,   647,    -1,    -1,    -1,    -1,   652,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     674,    -1,   676,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   687,    -1,   689,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   697,    -1,   699,    -1,    -1,    -1,    -1,
      -1,   705,    -1,   707,    -1,    -1,    -1,    -1,    -1,   713,
      -1,   715,    -1,    -1,    -1,    -1,    -1,   721,    -1,    -1,
      -1,   725,    -1,    -1,    -1,   729,    -1,    -1,    -1,   733,
      -1,    -1,    -1,   737,    -1,    -1,    -1,   741,    -1,    -1,
      -1,   745,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned short int yystos[] =
{
       0,     3,    89,    90,     0,     4,    91,    80,    92,    93,
       5,    94,    96,    77,    80,    95,     6,    97,   101,    77,
      99,     7,     8,    10,    11,    12,    14,    15,    80,   102,
     103,   111,   113,   124,   133,   137,   140,   165,    98,   165,
     165,    80,   164,   164,   164,   164,   164,   104,    77,   100,
     114,   125,   105,   134,   138,   141,    85,   144,    83,    83,
     165,    87,    87,    16,   142,   145,   116,   127,   106,    80,
     168,   164,   164,     1,    17,    18,    19,    20,    80,    86,
     111,   133,   137,   140,   146,   147,   150,   154,   157,   161,
     166,    17,    18,    19,    20,    84,   117,    17,    18,    19,
      20,    84,   128,   144,   135,   139,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,   169,
     169,   169,   169,   162,   169,   169,   169,   169,    85,   169,
     169,   169,   169,   126,    13,   142,   148,   151,   158,   155,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,   163,   169,   170,   118,   119,   122,   120,
     112,   115,   129,   130,   132,   131,    77,    80,    83,   143,
     245,   295,   164,    80,   167,   168,   166,   166,    78,    80,
      83,   174,   269,    75,    76,    83,   173,   175,   271,    83,
     173,   178,   273,    75,    76,    83,   172,   182,   275,    83,
     173,   183,   277,    74,    75,    83,   171,   184,   279,    83,
     171,   189,   281,    83,   172,   190,   283,    83,   173,   199,
     285,    83,   172,   208,   287,    83,   173,   224,   289,    79,
      83,   103,   240,   291,    83,   173,   241,   293,   295,    83,
     172,   246,   297,    83,   172,   247,   299,    83,   173,   249,
     301,    83,   172,   251,   303,    83,   173,   255,   305,    83,
     172,   259,   307,    83,   173,   264,   309,   174,   175,   178,
     182,   183,   184,   189,   190,   199,   208,   224,   240,   241,
     245,   246,   247,   249,   251,   255,   259,   264,    83,   171,
     311,   335,    83,   173,   315,   337,    83,   173,   317,   339,
      83,   173,   320,   341,    83,   173,   324,   343,   311,   315,
     317,   320,   324,   173,   328,     9,   167,   168,   166,   166,
      10,   107,   111,   165,    86,   167,   168,   166,   166,   296,
     136,   149,   152,   159,   156,   270,   272,   176,   274,   179,
     276,   278,   280,   185,   282,   284,   191,   286,   200,   288,
     209,   290,   225,   292,   294,   242,   298,   300,   248,   302,
     250,   304,   252,   306,   256,   308,   260,   310,   265,   336,
     312,   338,   316,   340,   318,   342,   321,   344,   325,   329,
     166,   123,   121,   164,   101,   108,    84,   245,    87,     9,
     153,   153,   160,   169,   170,   160,    84,   174,    84,   175,
     173,    84,   178,   173,    84,   182,    84,   183,    84,   184,
     171,    84,   189,    84,   190,   172,    84,   199,   173,    84,
     208,   172,    84,   224,   173,    84,   240,    84,   241,   173,
      84,   246,    84,   247,   172,    84,   249,   173,    84,   251,
     172,    84,   255,   173,    84,   259,   172,    84,   264,   173,
      84,   311,   171,    84,   315,   173,    84,   317,   173,    84,
     320,   173,    84,   324,   173,   173,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,   170,
     170,   109,   144,   167,   166,     9,   177,   180,   186,   192,
     201,   210,   226,   243,   253,   257,   261,   266,   313,   319,
     322,   326,   330,   165,   166,   173,   173,   171,   172,   173,
     172,   173,   173,   172,   173,   172,   173,   171,   173,   173,
     173,   173,   110,   181,   187,   193,   202,   211,   227,   244,
     254,   258,   262,   267,   314,   323,   327,   331,   144,   173,
     188,   172,   173,   172,   173,   173,   172,   173,   171,   173,
     173,   173,    81,   171,   194,   203,   212,   228,   263,   268,
     332,   172,   173,   172,   173,   173,   333,   195,   204,   213,
     229,   334,   172,   173,   172,   173,   173,   196,   205,   214,
     230,   172,   173,   172,   173,   197,   206,   215,   231,   172,
     173,   172,   173,   198,   207,   216,   232,   172,   173,   172,
     173,   217,   233,   172,   173,   218,   234,   172,   173,   219,
     235,   172,   173,   220,   236,   172,   173,   221,   237,   172,
     173,   222,   238,   172,   173,   223,   239,   172,   173
};

#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# if defined (__STDC__) || defined (__cplusplus)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# endif
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { 								\
      yyerror ("syntax error: cannot back up");\
      YYERROR;							\
    }								\
while (0)


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (N)								\
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (0)
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
              (Loc).first_line, (Loc).first_column,	\
              (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (&yylval, YYLEX_PARAM)
#else
# define YYLEX yylex (&yylval)
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (0)

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)		\
do {								\
  if (yydebug)							\
    {								\
      YYFPRINTF (stderr, "%s ", Title);				\
      yysymprint (stderr, 					\
                  Type, Value);	\
      YYFPRINTF (stderr, "\n");					\
    }								\
} while (0)

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_stack_print (short int *bottom, short int *top)
#else
static void
yy_stack_print (bottom, top)
    short int *bottom;
    short int *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (/* Nothing. */; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_reduce_print (int yyrule)
#else
static void
yy_reduce_print (yyrule)
    int yyrule;
#endif
{
  int yyi;
  unsigned int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %u), ",
             yyrule - 1, yylno);
  /* Print the symbols being reduced, and their result.  */
  for (yyi = yyprhs[yyrule]; 0 <= yyrhs[yyi]; yyi++)
    YYFPRINTF (stderr, "%s ", yytname [yyrhs[yyi]]);
  YYFPRINTF (stderr, "-> %s\n", yytname [yyr1[yyrule]]);
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (Rule);		\
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   SIZE_MAX < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined (__GLIBC__) && defined (_STRING_H)
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
#   if defined (__STDC__) || defined (__cplusplus)
yystrlen (const char *yystr)
#   else
yystrlen (yystr)
     const char *yystr;
#   endif
{
  register const char *yys = yystr;

  while (*yys++ != '\0')
    continue;

  return yys - yystr - 1;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined (__GLIBC__) && defined (_STRING_H) && defined (_GNU_SOURCE)
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
#   if defined (__STDC__) || defined (__cplusplus)
yystpcpy (char *yydest, const char *yysrc)
#   else
yystpcpy (yydest, yysrc)
     char *yydest;
     const char *yysrc;
#   endif
{
  register char *yyd = yydest;
  register const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

#endif /* !YYERROR_VERBOSE */



#if YYDEBUG
/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yysymprint (FILE *yyoutput, int yytype, YYSTYPE *yyvaluep)
#else
static void
yysymprint (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);


# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  switch (yytype)
    {
      default:
        break;
    }
  YYFPRINTF (yyoutput, ")");
}

#endif /* ! YYDEBUG */
/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
        break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM);
# else
int yyparse ();
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */






/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM)
# else
int yyparse (YYPARSE_PARAM)
  void *YYPARSE_PARAM;
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  /* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;

  register int yystate;
  register int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  short int yyssa[YYINITDEPTH];
  short int *yyss = yyssa;
  register short int *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;



#define YYPOPSTACK   (yyvsp--, yyssp--)

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* When reducing, the number of symbols on the RHS of the reduced
     rule.  */
  int yylen;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;


  yyvsp[0] = yylval;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed. so pushing a state here evens the stacks.
     */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack. Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	short int *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyoverflowlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyoverflowlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	short int *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyoverflowlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

/* Do appropriate processing given the current state.  */
/* Read a look-ahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to look-ahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;


  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  yystate = yyn;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 3:
#line 203 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->verifyHeader((yyvsp[0].stringVal)); ;}
    break;

  case 5:
#line 207 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->profileElement((yyvsp[0].stringVal)); ;}
    break;

  case 10:
#line 221 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->componentElement((yyvsp[0].stringVal)); ;}
    break;

  case 15:
#line 238 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = (yyvsp[0].stringVal); ;}
    break;

  case 16:
#line 240 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->metaElement(SKEL->_tmpString1.c_str(), (yyvsp[0].stringVal)); ;}
    break;

  case 26:
#line 260 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginNode((yyvsp[0].stringVal), 0); ;}
    break;

  case 28:
#line 263 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = (yyvsp[0].stringVal); ;}
    break;

  case 29:
#line 264 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginNode((yyvsp[0].stringVal), SKEL->_tmpString1.c_str()); ;}
    break;

  case 31:
#line 267 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->use((yyvsp[0].stringVal)); ;}
    break;

  case 32:
#line 270 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginNode((yyvsp[0].stringVal), 0); ;}
    break;

  case 34:
#line 273 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = (yyvsp[0].stringVal); ;}
    break;

  case 35:
#line 274 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginNode((yyvsp[0].stringVal), SKEL->_tmpString1.c_str()); ;}
    break;

  case 41:
#line 286 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginProto((yyvsp[0].stringVal)); ;}
    break;

  case 42:
#line 288 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endProto(); ;}
    break;

  case 46:
#line 299 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 47:
#line 300 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginEventInDecl(SKEL->_tmpString1.c_str(), (yyvsp[-2].intVal), (yyvsp[0].stringVal)); SKEL->endEventDecl(); ;}
    break;

  case 48:
#line 302 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 49:
#line 303 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginEventOutDecl(SKEL->_tmpString1.c_str(), (yyvsp[-2].intVal), (yyvsp[0].stringVal)); SKEL->endEventDecl(); ;}
    break;

  case 50:
#line 305 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 51:
#line 306 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginFieldDecl(SKEL->_tmpString1.c_str(), (yyvsp[-2].intVal), (yyvsp[0].stringVal)); SKEL->getLexer()->expectType((yyvsp[-2].intVal)); ;}
    break;

  case 52:
#line 307 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endFieldDecl(); ;}
    break;

  case 53:
#line 309 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 54:
#line 310 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginExposedFieldDecl(SKEL->_tmpString1.c_str(), (yyvsp[-2].intVal), (yyvsp[0].stringVal)); SKEL->getLexer()->expectType((yyvsp[-2].intVal)); ;}
    break;

  case 55:
#line 311 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endExposedFieldDecl(); ;}
    break;

  case 56:
#line 314 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginExternProto((yyvsp[0].stringVal)); ;}
    break;

  case 57:
#line 315 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endExternProtoInterface(); ;}
    break;

  case 58:
#line 316 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endExternProto(); ;}
    break;

  case 61:
#line 324 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 62:
#line 325 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->addExternEventInDecl(SKEL->_tmpString1.c_str(), (yyvsp[-2].intVal), (yyvsp[0].stringVal)); ;}
    break;

  case 63:
#line 327 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 64:
#line 328 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->addExternEventOutDecl(SKEL->_tmpString1.c_str(), (yyvsp[-2].intVal), (yyvsp[0].stringVal)); ;}
    break;

  case 65:
#line 330 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 66:
#line 331 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->addExternFieldDecl(SKEL->_tmpString1.c_str(), (yyvsp[-2].intVal), (yyvsp[0].stringVal)); ;}
    break;

  case 67:
#line 333 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 68:
#line 334 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->addExternExposedFieldDecl(SKEL->_tmpString1.c_str(), (yyvsp[-2].intVal), (yyvsp[0].stringVal)); ;}
    break;

  case 69:
#line 338 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = (yyvsp[0].stringVal); ;}
    break;

  case 70:
#line 340 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString2 = (yyvsp[0].stringVal); ;}
    break;

  case 71:
#line 342 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString3 = (yyvsp[0].stringVal); ;}
    break;

  case 72:
#line 345 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->addRoute(SKEL->_tmpString1.c_str(), SKEL->_tmpString2.c_str(), SKEL->_tmpString3.c_str(), (yyvsp[0].stringVal)); ;}
    break;

  case 73:
#line 349 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = (yyvsp[0].stringVal); ;}
    break;

  case 74:
#line 351 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString2 = (yyvsp[0].stringVal); ;}
    break;

  case 75:
#line 353 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { 
        if ((yyvsp[0].stringVal) != 0)
            SKEL->importElement(SKEL->_tmpString1.c_str(), SKEL->_tmpString2.c_str(), (yyvsp[0].stringVal));
        else
            SKEL->importElement(SKEL->_tmpString1.c_str(), SKEL->_tmpString2.c_str(), 0);
    ;}
    break;

  case 76:
#line 362 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = (yyvsp[0].stringVal); ;}
    break;

  case 77:
#line 364 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { 
        if ((yyvsp[0].stringVal) != 0)
            SKEL->exportElement(SKEL->_tmpString1.c_str(), (yyvsp[0].stringVal));
        else
            SKEL->exportElement(SKEL->_tmpString1.c_str(), 0);
    ;}
    break;

  case 78:
#line 373 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { (yyval.stringVal) = (yyvsp[0].stringVal); ;}
    break;

  case 79:
#line 374 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { (yyval.stringVal) = 0; ;}
    break;

  case 81:
#line 380 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endNode(); ;}
    break;

  case 90:
#line 396 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 91:
#line 397 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginEventInDecl(SKEL->_tmpString1.c_str(), (yyvsp[-2].intVal), (yyvsp[0].stringVal)); ;}
    break;

  case 92:
#line 398 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endEventDecl(); ;}
    break;

  case 93:
#line 402 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 94:
#line 403 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginEventOutDecl(SKEL->_tmpString1.c_str(), (yyvsp[-2].intVal), (yyvsp[0].stringVal)); ;}
    break;

  case 95:
#line 404 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endEventDecl(); ;}
    break;

  case 97:
#line 408 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->is((yyvsp[0].stringVal)); ;}
    break;

  case 98:
#line 412 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 99:
#line 413 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginFieldDecl(SKEL->_tmpString1.c_str(), (yyvsp[-2].intVal), (yyvsp[0].stringVal)); SKEL->getLexer()->expectType((yyvsp[-2].intVal)); ;}
    break;

  case 100:
#line 414 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endFieldDecl(); ;}
    break;

  case 101:
#line 418 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 102:
#line 419 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginExposedFieldDecl(SKEL->_tmpString1.c_str(), (yyvsp[-2].intVal), (yyvsp[0].stringVal)); SKEL->getLexer()->expectType((yyvsp[-2].intVal)); ;}
    break;

  case 103:
#line 420 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endExposedFieldDecl(); ;}
    break;

  case 105:
#line 424 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->is((yyvsp[0].stringVal)); ;}
    break;

  case 106:
#line 428 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        Int32 iFieldTypeId = SKEL->getFieldType((yyvsp[0].stringVal));
        if (SKEL->getMapFieldTypes() == true)
            iFieldTypeId = SKEL->mapExtIntFieldType((yyvsp[0].stringVal), iFieldTypeId);
        SKEL->getLexer()->expectType(iFieldTypeId);
        SKEL->beginField((yyvsp[0].stringVal), iFieldTypeId);
    ;}
    break;

  case 107:
#line 435 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endField(); ;}
    break;

  case 113:
#line 443 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->is((yyvsp[0].stringVal)); ;}
    break;

  case 225:
#line 573 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { (yyval.intVal) = (yyvsp[0].intVal); ;}
    break;

  case 226:
#line 574 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { (yyval.intVal) = (yyvsp[0].intVal); ;}
    break;

  case 227:
#line 577 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { (yyval.doubleVal) = (yyvsp[0].intVal); ;}
    break;

  case 228:
#line 578 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { (yyval.doubleVal) = (yyvsp[0].doubleVal); ;}
    break;

  case 229:
#line 581 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { (yyval.floatVal) = static_cast<float>((yyvsp[0].intVal)); ;}
    break;

  case 230:
#line 582 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { (yyval.floatVal) = static_cast<float>((yyvsp[0].doubleVal)); ;}
    break;

  case 231:
#line 586 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->addBoolValue((yyvsp[0].boolVal));
    ;}
    break;

  case 232:
#line 589 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->addFieldValue((yyvsp[0].stringVal)); ;}
    break;

  case 233:
#line 592 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 234:
#line 593 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 235:
#line 595 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addColorValue(Color3f((yyvsp[-4].floatVal), (yyvsp[-2].floatVal), (yyvsp[0].floatVal)));
    ;}
    break;

  case 236:
#line 601 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 237:
#line 602 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 238:
#line 603 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 239:
#line 605 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addColorRGBAValue(Color4f((yyvsp[-6].floatVal), (yyvsp[-4].floatVal), (yyvsp[-2].floatVal), (yyvsp[0].floatVal)));
    ;}
    break;

  case 240:
#line 612 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->addDoubleValue((yyvsp[0].doubleVal));
    ;}
    break;

  case 241:
#line 618 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->addFloatValue((yyvsp[0].floatVal));
    ;}
    break;

  case 242:
#line 623 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 243:
#line 624 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 244:
#line 626 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->beginImage((yyvsp[-4].intVal), (yyvsp[-2].intVal), (yyvsp[0].intVal));
    ;}
    break;

  case 245:
#line 631 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->endImage();
    ;}
    break;

  case 246:
#line 637 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->addImagePixel((yyvsp[0].intVal));
    ;}
    break;

  case 248:
#line 644 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->addInt32Value((yyvsp[0].intVal));
    ;}
    break;

  case 249:
#line 649 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 250:
#line 650 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 251:
#line 651 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 252:
#line 652 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 253:
#line 653 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 254:
#line 654 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 255:
#line 655 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 256:
#line 656 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 257:
#line 658 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addMatrix3dValue(
             (yyvsp[-16].doubleVal),  (yyvsp[-14].doubleVal),  (yyvsp[-12].doubleVal),
             (yyvsp[-10].doubleVal),  (yyvsp[-8].doubleVal), (yyvsp[-6].doubleVal),
            (yyvsp[-4].doubleVal), (yyvsp[-2].doubleVal), (yyvsp[0].doubleVal));
    ;}
    break;

  case 258:
#line 667 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 259:
#line 668 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 260:
#line 669 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 261:
#line 670 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 262:
#line 671 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 263:
#line 672 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 264:
#line 673 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 265:
#line 674 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 266:
#line 676 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addMatrix3fValue(
             (yyvsp[-16].floatVal),  (yyvsp[-14].floatVal),  (yyvsp[-12].floatVal),
             (yyvsp[-10].floatVal),  (yyvsp[-8].floatVal), (yyvsp[-6].floatVal),
            (yyvsp[-4].floatVal), (yyvsp[-2].floatVal), (yyvsp[0].floatVal));
    ;}
    break;

  case 267:
#line 685 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 268:
#line 686 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 269:
#line 687 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 270:
#line 688 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 271:
#line 689 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 272:
#line 690 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 273:
#line 691 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 274:
#line 692 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 275:
#line 693 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 276:
#line 694 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 277:
#line 695 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 278:
#line 696 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 279:
#line 697 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 280:
#line 698 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 281:
#line 699 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 282:
#line 701 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addMatrix4dValue(Matrix4d(
             (yyvsp[-30].doubleVal),  (yyvsp[-28].doubleVal),  (yyvsp[-26].doubleVal),  (yyvsp[-24].doubleVal),
             (yyvsp[-22].doubleVal), (yyvsp[-20].doubleVal), (yyvsp[-18].doubleVal), (yyvsp[-16].doubleVal),
            (yyvsp[-14].doubleVal), (yyvsp[-12].doubleVal), (yyvsp[-10].doubleVal), (yyvsp[-8].doubleVal),
            (yyvsp[-6].doubleVal), (yyvsp[-4].doubleVal), (yyvsp[-2].doubleVal), (yyvsp[0].doubleVal)));
    ;}
    break;

  case 283:
#line 711 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 284:
#line 712 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 285:
#line 713 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 286:
#line 714 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 287:
#line 715 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 288:
#line 716 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 289:
#line 717 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 290:
#line 718 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 291:
#line 719 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 292:
#line 720 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 293:
#line 721 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 294:
#line 722 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 295:
#line 723 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 296:
#line 724 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 297:
#line 725 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 298:
#line 727 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addMatrix4fValue(Matrix4f(
             (yyvsp[-30].floatVal),  (yyvsp[-28].floatVal),  (yyvsp[-26].floatVal),  (yyvsp[-24].floatVal),
             (yyvsp[-22].floatVal), (yyvsp[-20].floatVal), (yyvsp[-18].floatVal), (yyvsp[-16].floatVal),
            (yyvsp[-14].floatVal), (yyvsp[-12].floatVal), (yyvsp[-10].floatVal), (yyvsp[-8].floatVal),
            (yyvsp[-6].floatVal), (yyvsp[-4].floatVal), (yyvsp[-2].floatVal), (yyvsp[0].floatVal)));
    ;}
    break;

  case 300:
#line 738 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->nullNode(); ;}
    break;

  case 301:
#line 741 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 302:
#line 742 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 303:
#line 743 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 304:
#line 745 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addRotationValue(Vec3f((yyvsp[-6].floatVal), (yyvsp[-4].floatVal), (yyvsp[-2].floatVal)), (yyvsp[0].floatVal));
    ;}
    break;

  case 305:
#line 752 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->addStringValue((yyvsp[0].stringVal));
    ;}
    break;

  case 306:
#line 756 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { /* Not VRML conformant */
        SKEL->addStringValue((yyvsp[0].stringVal));
    ;}
    break;

  case 307:
#line 762 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->addTimeValue((yyvsp[0].doubleVal));
    ;}
    break;

  case 308:
#line 767 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 309:
#line 769 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addVec2dValue(Vec2d((yyvsp[-2].doubleVal), (yyvsp[0].doubleVal)));
    ;}
    break;

  case 310:
#line 775 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 311:
#line 777 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addVec2fValue(Vec2f((yyvsp[-2].floatVal), (yyvsp[0].floatVal)));
    ;}
    break;

  case 312:
#line 783 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 313:
#line 784 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 314:
#line 785 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 315:
#line 786 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addVec3dValue(Vec3d((yyvsp[-5].doubleVal), (yyvsp[-3].doubleVal), (yyvsp[-1].doubleVal)));
    ;}
    break;

  case 316:
#line 792 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 317:
#line 793 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 318:
#line 794 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 319:
#line 795 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addVec3fValue(Vec3f((yyvsp[-5].floatVal), (yyvsp[-3].floatVal), (yyvsp[-1].floatVal)));
    ;}
    break;

  case 320:
#line 801 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 321:
#line 802 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 322:
#line 803 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 323:
#line 804 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 324:
#line 805 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addVec4dValue(Vec4d((yyvsp[-7].doubleVal), (yyvsp[-5].doubleVal), (yyvsp[-3].doubleVal), (yyvsp[-1].doubleVal)));
    ;}
    break;

  case 325:
#line 811 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 326:
#line 812 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 327:
#line 813 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 328:
#line 814 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 329:
#line 815 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addVec4fValue(Vec4f((yyvsp[-7].floatVal), (yyvsp[-5].floatVal), (yyvsp[-3].floatVal), (yyvsp[-1].floatVal)));
    ;}
    break;

  case 414:
#line 991 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 415:
#line 992 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 416:
#line 993 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 417:
#line 995 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addColor4iValue(Color4ub(static_cast<UInt8>((yyvsp[-6].intVal)), static_cast<UInt8>((yyvsp[-4].intVal)),
                                       static_cast<UInt8>((yyvsp[-2].intVal)), static_cast<UInt8>((yyvsp[0].intVal))));
    ;}
    break;

  case 418:
#line 1002 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 419:
#line 1004 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addPnt2fValue(Pnt2f((yyvsp[-2].floatVal), (yyvsp[0].floatVal)));
    ;}
    break;

  case 420:
#line 1010 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 421:
#line 1011 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 422:
#line 1013 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addPnt3fValue(Pnt3f((yyvsp[-4].floatVal), (yyvsp[-2].floatVal), (yyvsp[0].floatVal)));
    ;}
    break;

  case 423:
#line 1019 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 424:
#line 1020 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 425:
#line 1021 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 426:
#line 1023 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addPnt4fValue(Pnt4f((yyvsp[-6].floatVal), (yyvsp[-4].floatVal), (yyvsp[-2].floatVal), (yyvsp[0].floatVal)));
    ;}
    break;

  case 427:
#line 1029 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 428:
#line 1030 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 429:
#line 1031 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 430:
#line 1033 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addPlaneValue(Plane(Vec3f((yyvsp[-6].floatVal), (yyvsp[-4].floatVal), (yyvsp[-2].floatVal)), (yyvsp[0].floatVal)));
    ;}
    break;

  case 431:
#line 1039 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 432:
#line 1040 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 433:
#line 1041 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 434:
#line 1043 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->_tmpFloat1 = (yyvsp[-6].floatVal); SKEL->_tmpFloat2 = (yyvsp[-4].floatVal);
        SKEL->_tmpFloat3 = (yyvsp[-2].floatVal); SKEL->_tmpFloat4 = (yyvsp[0].floatVal);
    ;}
    break;

  case 436:
#line 1051 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 437:
#line 1053 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        DynamicVolume dv(DynamicVolume::BOX_VOLUME);
        BoxVolume &bv = dynamic_cast<BoxVolume&>(dv.getInstance());
        bv.setBounds(SKEL->_tmpFloat1, SKEL->_tmpFloat2, SKEL->_tmpFloat3, SKEL->_tmpFloat4, (yyvsp[-2].floatVal), (yyvsp[0].floatVal));
        SKEL->addVolumeValue(dv);
    ;}
    break;

  case 438:
#line 1061 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        DynamicVolume dv(DynamicVolume::SPHERE_VOLUME);
        SphereVolume &sv = dynamic_cast<SphereVolume&>(dv.getInstance());
        sv.setValue(Pnt3f(SKEL->_tmpFloat1, SKEL->_tmpFloat2, SKEL->_tmpFloat3), SKEL->_tmpFloat4);
        SKEL->addVolumeValue(dv);
    ;}
    break;


    }

/* Line 1037 of yacc.c.  */
#line 3111 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.cpp"

  yyvsp -= yylen;
  yyssp -= yylen;


  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (YYPACT_NINF < yyn && yyn < YYLAST)
	{
	  YYSIZE_T yysize = 0;
	  int yytype = YYTRANSLATE (yychar);
	  const char* yyprefix;
	  char *yymsg;
	  int yyx;

	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  int yyxbegin = yyn < 0 ? -yyn : 0;

	  /* Stay within bounds of both yycheck and yytname.  */
	  int yychecklim = YYLAST - yyn;
	  int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
	  int yycount = 0;

	  yyprefix = ", expecting ";
	  for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	      {
		yysize += yystrlen (yyprefix) + yystrlen (yytname [yyx]);
		yycount += 1;
		if (yycount == 5)
		  {
		    yysize = 0;
		    break;
		  }
	      }
	  yysize += (sizeof ("syntax error, unexpected ")
		     + yystrlen (yytname[yytype]));
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "syntax error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[yytype]);

	      if (yycount < 5)
		{
		  yyprefix = ", expecting ";
		  for (yyx = yyxbegin; yyx < yyxend; ++yyx)
		    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
		      {
			yyp = yystpcpy (yyp, yyprefix);
			yyp = yystpcpy (yyp, yytname[yyx]);
			yyprefix = " or ";
		      }
		}
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    yyerror ("syntax error; also virtual memory exhausted");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror ("syntax error");
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* If at end of input, pop the error token,
	     then the rest of the stack, then return failure.  */
	  if (yychar == YYEOF)
	     for (;;)
	       {

		 YYPOPSTACK;
		 if (yyssp == yyss)
		   YYABORT;
		 yydestruct ("Error: popping",
                             yystos[*yyssp], yyvsp);
	       }
        }
      else
	{
	  yydestruct ("Error: discarding", yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

#ifdef __GNUC__
  /* Pacify GCC when the user code never invokes YYERROR and the label
     yyerrorlab therefore never appears in user code.  */
  if (0)
     goto yyerrorlab;
#endif

yyvsp -= yylen;
  yyssp -= yylen;
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping", yystos[yystate], yyvsp);
      YYPOPSTACK;
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token. */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yydestruct ("Error: discarding lookahead",
              yytoken, &yylval);
  yychar = YYEMPTY;
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*----------------------------------------------.
| yyoverflowlab -- parser overflow comes here.  |
`----------------------------------------------*/
yyoverflowlab:
  yyerror ("parser stack overflow");
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}


#line 1108 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"


int OSGScanParseSkel_lex(YYSTYPE *lvalp, void *pSkel)
{
    return SKEL->lex(lvalp);
}

