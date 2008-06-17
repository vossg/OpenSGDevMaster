/* A Bison parser, made by GNU Bison 1.875c.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003 Free Software Foundation, Inc.

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

/* If NAME_PREFIX is specified substitute the variables and functions
   names.  */
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
/* Line 191 of yacc.c.  */
#line 258 "Source/System/FileIO/ScanParseSkel/prebuild/OSGScanParseSkelParser.cpp"
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



/* Line 214 of yacc.c.  */
#line 299 "Source/System/FileIO/ScanParseSkel/prebuild/OSGScanParseSkelParser.cpp"

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
#   define YYSTACK_ALLOC alloca
#  endif
# else
#  if defined (alloca) || defined (_ALLOCA_H)
#   define YYSTACK_ALLOC alloca
#  else
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
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
  short yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE))				\
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
   typedef short yysigned_char;
#endif

/* YYFINAL -- State number of the termination state. */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   943

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  88
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  251
/* YYNRULES -- Number of rules. */
#define YYNRULES  449
/* YYNRULES -- Number of states. */
#define YYNSTATES  736

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
static const unsigned short yyprhs[] =
{
       0,     0,     3,     9,    11,    12,    15,    16,    18,    21,
      22,    25,    27,    29,    32,    33,    34,    39,    41,    43,
      46,    47,    49,    51,    53,    55,    57,    58,    62,    63,
      64,    71,    74,    76,    78,    79,    80,    91,    94,    95,
      96,   101,   102,   107,   108,   109,   116,   117,   118,   125,
     126,   127,   136,   139,   140,   141,   146,   147,   152,   153,
     158,   159,   164,   165,   166,   167,   179,   180,   181,   189,
     190,   195,   198,   199,   201,   205,   208,   209,   211,   213,
     215,   217,   219,   221,   222,   223,   230,   231,   232,   239,
     240,   243,   244,   245,   252,   253,   254,   261,   263,   267,
     268,   272,   274,   276,   278,   280,   282,   286,   288,   290,
     292,   294,   296,   298,   300,   302,   304,   306,   308,   310,
     312,   314,   316,   318,   320,   322,   324,   326,   328,   330,
     332,   334,   336,   338,   340,   342,   344,   346,   348,   350,
     352,   354,   356,   358,   360,   362,   364,   366,   368,   370,
     372,   374,   376,   378,   380,   382,   384,   386,   388,   390,
     392,   394,   396,   398,   400,   402,   405,   408,   411,   414,
     417,   420,   423,   426,   429,   432,   435,   438,   441,   444,
     447,   450,   453,   456,   459,   462,   465,   468,   471,   474,
     477,   480,   483,   486,   489,   492,   495,   498,   501,   504,
     507,   510,   513,   516,   519,   522,   525,   528,   531,   534,
     537,   540,   543,   546,   549,   552,   555,   558,   561,   563,
     565,   567,   569,   571,   573,   575,   577,   578,   579,   585,
     586,   587,   588,   596,   598,   600,   601,   602,   603,   612,
     615,   616,   618,   619,   620,   621,   622,   623,   624,   625,
     626,   644,   645,   646,   647,   648,   649,   650,   651,   652,
     670,   671,   672,   673,   674,   675,   676,   677,   678,   679,
     680,   681,   682,   683,   684,   685,   717,   718,   719,   720,
     721,   722,   723,   724,   725,   726,   727,   728,   729,   730,
     731,   732,   764,   766,   768,   769,   770,   771,   779,   781,
     783,   785,   786,   790,   791,   795,   796,   797,   798,   805,
     806,   807,   808,   815,   816,   817,   818,   819,   828,   829,
     830,   831,   832,   841,   843,   847,   850,   851,   853,   857,
     860,   861,   863,   867,   870,   871,   873,   877,   880,   881,
     883,   887,   890,   891,   893,   897,   900,   901,   903,   907,
     910,   911,   913,   917,   920,   921,   923,   927,   930,   931,
     933,   937,   940,   941,   943,   947,   950,   951,   953,   957,
     960,   961,   963,   967,   970,   971,   973,   977,   980,   981,
     983,   987,   990,   991,   993,   997,  1000,  1001,  1003,  1007,
    1010,  1011,  1013,  1017,  1020,  1021,  1023,  1027,  1030,  1031,
    1033,  1037,  1040,  1041,  1043,  1047,  1050,  1051,  1052,  1053,
    1054,  1062,  1063,  1067,  1068,  1069,  1075,  1076,  1077,  1078,
    1086,  1087,  1088,  1089,  1097,  1098,  1099,  1100,  1101,  1102,
    1114,  1116,  1120,  1123,  1124,  1126,  1130,  1133,  1134,  1136,
    1140,  1143,  1144,  1146,  1150,  1153,  1154,  1156,  1160,  1163
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const short yyrhs[] =
{
      89,     0,    -1,    90,    91,    93,    96,   101,    -1,     3,
      -1,    -1,     4,    92,    -1,    -1,    80,    -1,    93,    94,
      -1,    -1,     5,    95,    -1,    80,    -1,    77,    -1,    96,
      97,    -1,    -1,    -1,     6,    99,    98,   100,    -1,    77,
      -1,    77,    -1,   101,   102,    -1,    -1,   103,    -1,   107,
      -1,   128,    -1,   132,    -1,   135,    -1,    -1,   160,   104,
     139,    -1,    -1,    -1,    10,   159,   105,   160,   106,   139,
      -1,    11,   159,    -1,   108,    -1,   119,    -1,    -1,    -1,
       7,   160,   109,    83,   111,    84,   110,    85,   101,    86,
      -1,   111,   112,    -1,    -1,    -1,    17,   164,   113,   162,
      -1,    -1,    18,   164,   114,   163,    -1,    -1,    -1,    20,
     164,   115,   161,   116,   165,    -1,    -1,    -1,    19,   164,
     117,   161,   118,   165,    -1,    -1,    -1,     8,   160,   120,
      83,   122,    84,   121,   138,    -1,   122,   123,    -1,    -1,
      -1,    17,   164,   124,   162,    -1,    -1,    18,   164,   125,
     163,    -1,    -1,    20,   164,   126,   161,    -1,    -1,    19,
     164,   127,   161,    -1,    -1,    -1,    -1,    12,   159,   129,
      87,   163,   130,    13,   159,   131,    87,   162,    -1,    -1,
      -1,    14,   159,   133,    87,   159,   134,   137,    -1,    -1,
      15,   159,   136,   137,    -1,    16,   159,    -1,    -1,   290,
      -1,    85,   140,    86,    -1,   140,   141,    -1,    -1,   156,
      -1,   142,    -1,   145,    -1,   149,    -1,   152,    -1,     1,
      -1,    -1,    -1,    17,   164,   143,   162,   144,   148,    -1,
      -1,    -1,    18,   164,   146,   163,   147,   148,    -1,    -1,
       9,   161,    -1,    -1,    -1,    20,   164,   150,   161,   151,
     155,    -1,    -1,    -1,    19,   164,   153,   161,   154,   155,
      -1,   165,    -1,   164,     9,   161,    -1,    -1,   161,   157,
     158,    -1,   128,    -1,   107,    -1,   132,    -1,   135,    -1,
     165,    -1,   164,     9,   161,    -1,    80,    -1,    80,    -1,
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
      73,    -1,    21,   264,    -1,    22,   266,    -1,    23,   268,
      -1,    24,   270,    -1,    25,   272,    -1,    26,   274,    -1,
      27,   276,    -1,    28,   278,    -1,    29,   280,    -1,    30,
     282,    -1,    31,   284,    -1,    32,   286,    -1,    33,   288,
      -1,    34,   290,    -1,    35,   292,    -1,    36,   294,    -1,
      37,   296,    -1,    38,   298,    -1,    39,   300,    -1,    40,
     302,    -1,    41,   304,    -1,    42,   169,    -1,    43,   170,
      -1,    44,   173,    -1,    45,   177,    -1,    46,   178,    -1,
      47,   179,    -1,    48,   184,    -1,    49,   185,    -1,    50,
     194,    -1,    51,   203,    -1,    52,   219,    -1,    53,   235,
      -1,    54,   236,    -1,    55,   240,    -1,    56,   241,    -1,
      57,   242,    -1,    58,   244,    -1,    59,   246,    -1,    60,
     250,    -1,    61,   254,    -1,    62,   259,    -1,    63,   329,
      -1,    64,   331,    -1,    65,   333,    -1,    66,   335,    -1,
      67,   337,    -1,    68,   306,    -1,    69,   310,    -1,    70,
     312,    -1,    71,   315,    -1,    72,   319,    -1,    73,   323,
      -1,    74,    -1,    75,    -1,    75,    -1,    76,    -1,    75,
      -1,    76,    -1,    78,    -1,    80,    -1,    -1,    -1,   168,
     171,   168,   172,   168,    -1,    -1,    -1,    -1,   168,   174,
     168,   175,   168,   176,   168,    -1,   167,    -1,   168,    -1,
      -1,    -1,    -1,   166,   180,   166,   181,   166,   182,   183,
      81,    -1,   183,   166,    -1,    -1,   166,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   167,   186,   167,   187,
     167,   188,   167,   189,   167,   190,   167,   191,   167,   192,
     167,   193,   167,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   168,   195,   168,   196,   168,   197,   168,   198,
     168,   199,   168,   200,   168,   201,   168,   202,   168,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   167,   204,   167,   205,   167,
     206,   167,   207,   167,   208,   167,   209,   167,   210,   167,
     211,   167,   212,   167,   213,   167,   214,   167,   215,   167,
     216,   167,   217,   167,   218,   167,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   168,   220,   168,   221,   168,   222,   168,   223,
     168,   224,   168,   225,   168,   226,   168,   227,   168,   228,
     168,   229,   168,   230,   168,   231,   168,   232,   168,   233,
     168,   234,   168,    -1,   103,    -1,    79,    -1,    -1,    -1,
      -1,   168,   237,   168,   238,   168,   239,   168,    -1,    77,
      -1,    80,    -1,   167,    -1,    -1,   167,   243,   167,    -1,
      -1,   168,   245,   168,    -1,    -1,    -1,    -1,   167,   247,
     167,   248,   167,   249,    -1,    -1,    -1,    -1,   168,   251,
     168,   252,   168,   253,    -1,    -1,    -1,    -1,    -1,   167,
     255,   167,   256,   167,   257,   167,   258,    -1,    -1,    -1,
      -1,    -1,   168,   260,   168,   261,   168,   262,   168,   263,
      -1,   169,    -1,    83,   265,    84,    -1,   265,   169,    -1,
      -1,   170,    -1,    83,   267,    84,    -1,   267,   170,    -1,
      -1,   173,    -1,    83,   269,    84,    -1,   269,   173,    -1,
      -1,   177,    -1,    83,   271,    84,    -1,   271,   177,    -1,
      -1,   178,    -1,    83,   273,    84,    -1,   273,   178,    -1,
      -1,   179,    -1,    83,   275,    84,    -1,   275,   179,    -1,
      -1,   184,    -1,    83,   277,    84,    -1,   277,   184,    -1,
      -1,   185,    -1,    83,   279,    84,    -1,   279,   185,    -1,
      -1,   194,    -1,    83,   281,    84,    -1,   281,   194,    -1,
      -1,   203,    -1,    83,   283,    84,    -1,   283,   203,    -1,
      -1,   219,    -1,    83,   285,    84,    -1,   285,   219,    -1,
      -1,   235,    -1,    83,   287,    84,    -1,   287,   235,    -1,
      -1,   236,    -1,    83,   289,    84,    -1,   289,   236,    -1,
      -1,   240,    -1,    83,   291,    84,    -1,   291,   240,    -1,
      -1,   241,    -1,    83,   293,    84,    -1,   293,   241,    -1,
      -1,   242,    -1,    83,   295,    84,    -1,   295,   242,    -1,
      -1,   244,    -1,    83,   297,    84,    -1,   297,   244,    -1,
      -1,   246,    -1,    83,   299,    84,    -1,   299,   246,    -1,
      -1,   250,    -1,    83,   301,    84,    -1,   301,   250,    -1,
      -1,   254,    -1,    83,   303,    84,    -1,   303,   254,    -1,
      -1,   259,    -1,    83,   305,    84,    -1,   305,   259,    -1,
      -1,    -1,    -1,    -1,   166,   307,   166,   308,   166,   309,
     166,    -1,    -1,   168,   311,   168,    -1,    -1,    -1,   168,
     313,   168,   314,   168,    -1,    -1,    -1,    -1,   168,   316,
     168,   317,   168,   318,   168,    -1,    -1,    -1,    -1,   168,
     320,   168,   321,   168,   322,   168,    -1,    -1,    -1,    -1,
      -1,    -1,   168,   324,   168,   325,   168,   326,   168,   327,
     168,   328,   168,    -1,   306,    -1,    83,   330,    84,    -1,
     330,   306,    -1,    -1,   310,    -1,    83,   332,    84,    -1,
     332,   310,    -1,    -1,   312,    -1,    83,   334,    84,    -1,
     334,   312,    -1,    -1,   315,    -1,    83,   336,    84,    -1,
     336,   315,    -1,    -1,   319,    -1,    83,   338,    84,    -1,
     338,   319,    -1,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short yyrline[] =
{
       0,   196,   196,   203,   204,   207,   208,   211,   214,   215,
     219,   224,   225,   232,   233,   238,   236,   243,   246,   249,
     250,   253,   254,   255,   256,   257,   260,   260,   263,   264,
     262,   266,   270,   271,   278,   279,   278,   283,   284,   288,
     287,   291,   290,   294,   295,   293,   298,   299,   297,   303,
     304,   303,   308,   309,   313,   312,   316,   315,   319,   318,
     322,   321,   327,   329,   331,   326,   338,   340,   337,   351,
     350,   361,   363,   366,   369,   372,   373,   376,   377,   378,
     379,   380,   381,   385,   386,   384,   391,   392,   390,   395,
     397,   401,   402,   400,   407,   408,   406,   412,   413,   417,
     416,   425,   426,   427,   428,   431,   432,   435,   438,   441,
     444,   447,   450,   451,   452,   453,   454,   455,   456,   457,
     458,   459,   460,   461,   462,   463,   464,   465,   466,   467,
     468,   469,   470,   471,   472,   473,   474,   475,   476,   477,
     478,   479,   480,   481,   482,   483,   484,   485,   486,   487,
     488,   489,   490,   491,   493,   494,   495,   496,   497,   498,
     499,   500,   501,   502,   503,   506,   507,   508,   509,   510,
     511,   512,   513,   514,   515,   516,   517,   518,   519,   520,
     521,   522,   523,   524,   525,   526,   527,   528,   529,   530,
     531,   532,   533,   534,   535,   536,   537,   538,   539,   540,
     541,   542,   543,   544,   545,   546,   547,   549,   550,   551,
     552,   553,   554,   555,   556,   557,   558,   559,   562,   563,
     566,   567,   570,   571,   574,   578,   581,   582,   581,   590,
     591,   592,   590,   600,   606,   612,   613,   615,   612,   625,
     629,   632,   638,   639,   640,   641,   642,   643,   644,   645,
     638,   656,   657,   658,   659,   660,   661,   662,   663,   656,
     674,   675,   676,   677,   678,   679,   680,   681,   682,   683,
     684,   685,   686,   687,   688,   674,   700,   701,   702,   703,
     704,   705,   706,   707,   708,   709,   710,   711,   712,   713,
     714,   700,   726,   727,   730,   731,   732,   730,   740,   744,
     750,   756,   756,   764,   764,   772,   773,   774,   772,   781,
     782,   783,   781,   790,   791,   792,   793,   790,   800,   801,
     802,   803,   800,   810,   811,   814,   815,   818,   819,   822,
     823,   826,   827,   830,   831,   834,   835,   838,   839,   842,
     843,   846,   847,   850,   851,   854,   855,   858,   859,   862,
     863,   866,   867,   870,   871,   874,   875,   878,   879,   882,
     883,   886,   887,   890,   891,   894,   895,   898,   899,   902,
     903,   906,   907,   910,   911,   914,   915,   918,   919,   922,
     923,   926,   927,   930,   931,   934,   935,   938,   939,   942,
     943,   946,   947,   950,   951,   954,   955,   958,   959,   962,
     963,   966,   967,   970,   971,   974,   975,   980,   981,   982,
     980,   991,   991,   999,  1000,   999,  1008,  1009,  1010,  1008,
    1018,  1019,  1020,  1018,  1028,  1029,  1030,  1031,  1032,  1028,
    1042,  1043,  1046,  1047,  1050,  1051,  1054,  1055,  1058,  1059,
    1062,  1063,  1066,  1067,  1070,  1071,  1074,  1075,  1078,  1079
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
  "protoStatement", "proto", "@5", "@6", "interfaceDeclarations",
  "interfaceDeclaration", "@7", "@8", "@9", "@10", "@11", "@12",
  "externproto", "@13", "@14", "externInterfaceDeclarations",
  "externInterfaceDeclaration", "@15", "@16", "@17", "@18",
  "routeStatement", "@19", "@20", "@21", "importStatement", "@22", "@23",
  "exportStatement", "@24", "asStatement", "URLList", "node", "scriptBody",
  "scriptBodyElement", "eventInDeclaration", "@25", "@26",
  "eventOutDeclaration", "@27", "@28", "eventDeclarationEnd",
  "fieldDeclaration", "@29", "@30", "exposedFieldDeclaration", "@31",
  "@32", "fieldDeclarationEnd", "nodeBodyElement", "@33", "fieldEnd",
  "nodeNameId", "nodeTypeId", "fieldId", "eventInId", "eventOutId",
  "fieldType", "fieldValue", "int32", "double", "float", "sfboolValue",
  "sfcolorValue", "@34", "@35", "sfcolorRGBAValue", "@36", "@37", "@38",
  "sfdoubleValue", "sffloatValue", "sfimageValue", "@39", "@40", "@41",
  "pixels", "sfint32Value", "sfmatrix3dValue", "@42", "@43", "@44", "@45",
  "@46", "@47", "@48", "@49", "sfmatrix3fValue", "@50", "@51", "@52",
  "@53", "@54", "@55", "@56", "@57", "sfmatrix4dValue", "@58", "@59",
  "@60", "@61", "@62", "@63", "@64", "@65", "@66", "@67", "@68", "@69",
  "@70", "@71", "@72", "sfmatrix4fValue", "@73", "@74", "@75", "@76",
  "@77", "@78", "@79", "@80", "@81", "@82", "@83", "@84", "@85", "@86",
  "@87", "sfnodeValue", "sfrotationValue", "@88", "@89", "@90",
  "sfstringValue", "sftimeValue", "sfvec2dValue", "@91", "sfvec2fValue",
  "@92", "sfvec3dValue", "@93", "@94", "@95", "sfvec3fValue", "@96", "@97",
  "@98", "sfvec4dValue", "@99", "@100", "@101", "@102", "sfvec4fValue",
  "@103", "@104", "@105", "@106", "mfboolValue", "sfboolValues",
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
  "mfvec4fValue", "sfvec4fValues", "sfcolor4iValue", "@107", "@108",
  "@109", "sfpnt2fValue", "@110", "sfpnt3fValue", "@111", "@112",
  "sfpnt4fValue", "@113", "@114", "@115", "sfplaneValue", "@116", "@117",
  "@118", "sfVolumeValue", "@119", "@120", "@121", "@122", "@123",
  "mfcolor4iValue", "sfcolor4iValues", "mfpnt2fValue", "sfpnt2fValues",
  "mfpnt3fValue", "sfpnt3fValues", "mfpnt4fValue", "sfpnt4fValues",
  "mfplaneValue", "sfplaneValues", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const unsigned short yytoknum[] =
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
static const unsigned short yyr1[] =
{
       0,    88,    89,    90,    90,    91,    91,    92,    93,    93,
      94,    95,    95,    96,    96,    98,    97,    99,   100,   101,
     101,   102,   102,   102,   102,   102,   104,   103,   105,   106,
     103,   103,   107,   107,   109,   110,   108,   111,   111,   113,
     112,   114,   112,   115,   116,   112,   117,   118,   112,   120,
     121,   119,   122,   122,   124,   123,   125,   123,   126,   123,
     127,   123,   129,   130,   131,   128,   133,   134,   132,   136,
     135,   137,   137,   138,   139,   140,   140,   141,   141,   141,
     141,   141,   141,   143,   144,   142,   146,   147,   145,   148,
     148,   150,   151,   149,   153,   154,   152,   155,   155,   157,
     156,   156,   156,   156,   156,   158,   158,   159,   160,   161,
     162,   163,   164,   164,   164,   164,   164,   164,   164,   164,
     164,   164,   164,   164,   164,   164,   164,   164,   164,   164,
     164,   164,   164,   164,   164,   164,   164,   164,   164,   164,
     164,   164,   164,   164,   164,   164,   164,   164,   164,   164,
     164,   164,   164,   164,   164,   164,   164,   164,   164,   164,
     164,   164,   164,   164,   164,   165,   165,   165,   165,   165,
     165,   165,   165,   165,   165,   165,   165,   165,   165,   165,
     165,   165,   165,   165,   165,   165,   165,   165,   165,   165,
     165,   165,   165,   165,   165,   165,   165,   165,   165,   165,
     165,   165,   165,   165,   165,   165,   165,   165,   165,   165,
     165,   165,   165,   165,   165,   165,   165,   165,   166,   166,
     167,   167,   168,   168,   169,   169,   171,   172,   170,   174,
     175,   176,   173,   177,   178,   180,   181,   182,   179,   183,
     183,   184,   186,   187,   188,   189,   190,   191,   192,   193,
     185,   195,   196,   197,   198,   199,   200,   201,   202,   194,
     204,   205,   206,   207,   208,   209,   210,   211,   212,   213,
     214,   215,   216,   217,   218,   203,   220,   221,   222,   223,
     224,   225,   226,   227,   228,   229,   230,   231,   232,   233,
     234,   219,   235,   235,   237,   238,   239,   236,   240,   240,
     241,   243,   242,   245,   244,   247,   248,   249,   246,   251,
     252,   253,   250,   255,   256,   257,   258,   254,   260,   261,
     262,   263,   259,   264,   264,   265,   265,   266,   266,   267,
     267,   268,   268,   269,   269,   270,   270,   271,   271,   272,
     272,   273,   273,   274,   274,   275,   275,   276,   276,   277,
     277,   278,   278,   279,   279,   280,   280,   281,   281,   282,
     282,   283,   283,   284,   284,   285,   285,   286,   286,   287,
     287,   288,   288,   289,   289,   290,   290,   291,   291,   292,
     292,   293,   293,   294,   294,   295,   295,   296,   296,   297,
     297,   298,   298,   299,   299,   300,   300,   301,   301,   302,
     302,   303,   303,   304,   304,   305,   305,   307,   308,   309,
     306,   311,   310,   313,   314,   312,   316,   317,   318,   315,
     320,   321,   322,   319,   324,   325,   326,   327,   328,   323,
     329,   329,   330,   330,   331,   331,   332,   332,   333,   333,
     334,   334,   335,   335,   336,   336,   337,   337,   338,   338
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     5,     1,     0,     2,     0,     1,     2,     0,
       2,     1,     1,     2,     0,     0,     4,     1,     1,     2,
       0,     1,     1,     1,     1,     1,     0,     3,     0,     0,
       6,     2,     1,     1,     0,     0,    10,     2,     0,     0,
       4,     0,     4,     0,     0,     6,     0,     0,     6,     0,
       0,     8,     2,     0,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     0,     0,    11,     0,     0,     7,     0,
       4,     2,     0,     1,     3,     2,     0,     1,     1,     1,
       1,     1,     1,     0,     0,     6,     0,     0,     6,     0,
       2,     0,     0,     6,     0,     0,     6,     1,     3,     0,
       3,     1,     1,     1,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     0,     5,     0,
       0,     0,     7,     1,     1,     0,     0,     0,     8,     2,
       0,     1,     0,     0,     0,     0,     0,     0,     0,     0,
      17,     0,     0,     0,     0,     0,     0,     0,     0,    17,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    31,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    31,     1,     1,     0,     0,     0,     7,     1,     1,
       1,     0,     3,     0,     3,     0,     0,     0,     6,     0,
       0,     0,     6,     0,     0,     0,     0,     8,     0,     0,
       0,     0,     8,     1,     3,     2,     0,     1,     3,     2,
       0,     1,     3,     2,     0,     1,     3,     2,     0,     1,
       3,     2,     0,     1,     3,     2,     0,     1,     3,     2,
       0,     1,     3,     2,     0,     1,     3,     2,     0,     1,
       3,     2,     0,     1,     3,     2,     0,     1,     3,     2,
       0,     1,     3,     2,     0,     1,     3,     2,     0,     1,
       3,     2,     0,     1,     3,     2,     0,     1,     3,     2,
       0,     1,     3,     2,     0,     1,     3,     2,     0,     1,
       3,     2,     0,     1,     3,     2,     0,     0,     0,     0,
       7,     0,     3,     0,     0,     5,     0,     0,     0,     7,
       0,     0,     0,     7,     0,     0,     0,     0,     0,    11,
       1,     3,     2,     0,     1,     3,     2,     0,     1,     3,
       2,     0,     1,     3,     2,     0,     1,     3,     2,     0
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned short yydefact[] =
{
       4,     3,     0,     6,     1,     0,     9,     7,     5,    14,
       0,     8,    20,    12,    11,    10,     0,    13,     2,    17,
      15,     0,     0,     0,     0,     0,     0,     0,   108,    19,
      21,    22,    32,    33,    23,    24,    25,    26,     0,    34,
      49,   107,    28,    31,    62,    66,    69,     0,    18,    16,
       0,     0,     0,     0,     0,    72,    76,    27,    38,    53,
      29,     0,     0,     0,    70,     0,     0,     0,     0,   111,
      63,    67,    71,    82,     0,     0,     0,     0,   109,    74,
     102,   101,   103,   104,    75,    78,    79,    80,    81,    77,
      99,     0,     0,     0,     0,    35,    37,     0,     0,     0,
       0,    50,    52,    30,     0,    72,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,    83,
      86,    94,    91,     0,    39,    41,    46,    43,     0,    54,
      56,    60,    58,     0,     0,    68,     0,     0,     0,     0,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   100,     0,   105,     0,     0,     0,     0,
      20,     0,     0,     0,     0,   298,   299,   378,    51,   375,
      73,    64,   110,    84,    87,    95,    92,   224,   225,   326,
     323,   165,   222,   223,   330,   226,   327,   166,   334,   229,
     331,   167,   220,   221,   338,   233,   335,   168,   342,   234,
     339,   169,   218,   219,   346,   235,   343,   170,   350,   241,
     347,   171,   354,   242,   351,   172,   358,   251,   355,   173,
     362,   260,   359,   174,   366,   276,   363,   175,   293,   370,
     292,   367,   176,   374,   294,   371,   177,   178,   382,   300,
     379,   179,   386,   301,   383,   180,   390,   303,   387,   181,
     394,   305,   391,   182,   398,   309,   395,   183,   402,   313,
     399,   184,   406,   318,   403,   185,   186,   187,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   204,   205,   206,   433,   407,   430,
     207,   437,   411,   434,   208,   441,   413,   438,   209,   445,
     416,   442,   210,   449,   420,   446,   211,   212,   213,   214,
     215,   216,   424,   217,     0,    40,    42,    47,    44,     0,
      55,    57,    61,    59,     0,     0,    89,    89,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   106,     0,     0,    36,   376,
     377,     0,     0,    85,    88,    96,     0,    97,    93,   324,
     325,   328,   329,   227,   332,   333,   230,   336,   337,   340,
     341,   344,   345,   236,   348,   349,   352,   353,   243,   356,
     357,   252,   360,   361,   261,   364,   365,   277,   368,   369,
     372,   373,   295,   380,   381,   384,   385,   302,   388,   389,
     304,   392,   393,   306,   396,   397,   310,   400,   401,   314,
     404,   405,   319,   431,   432,   408,   435,   436,   412,   439,
     440,   414,   443,   444,   417,   447,   448,   421,   425,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    48,    45,    65,    90,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    98,   228,   231,   237,   244,   253,
     262,   278,   296,   307,   311,   315,   320,   409,   415,   418,
     422,   426,     0,   240,     0,     0,     0,     0,     0,   308,
     312,     0,     0,     0,     0,     0,     0,   232,     0,   245,
     254,   263,   279,   297,   316,   321,   410,   419,   423,   427,
     238,   239,     0,     0,     0,     0,   317,   322,     0,   246,
     255,   264,   280,   428,     0,     0,     0,     0,     0,   247,
     256,   265,   281,   429,     0,     0,     0,     0,   248,   257,
     266,   282,     0,     0,     0,     0,   249,   258,   267,   283,
       0,     0,     0,     0,   250,   259,   268,   284,     0,     0,
     269,   285,     0,     0,   270,   286,     0,     0,   271,   287,
       0,     0,   272,   288,     0,     0,   273,   289,     0,     0,
     274,   290,     0,     0,   275,   291
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short yydefgoto[] =
{
      -1,     2,     3,     6,     8,     9,    11,    15,    12,    17,
      38,    20,    49,    18,    29,   310,    47,    52,    68,    31,
      32,    50,   168,    66,    96,   236,   237,   239,   457,   238,
     456,    33,    51,   173,    67,   102,   241,   242,   244,   243,
      34,    53,   104,   405,    35,    54,   105,    36,    55,    64,
     248,    57,    65,    84,    85,   176,   406,    86,   177,   407,
     463,    87,   179,   409,    88,   178,   408,   465,    89,   163,
     233,    42,    37,    90,   253,    70,   466,   467,   285,   275,
     265,   260,   266,   412,   597,   270,   414,   598,   632,   276,
     280,   286,   418,   599,   633,   648,   290,   294,   421,   600,
     634,   662,   674,   684,   692,   700,   298,   423,   601,   635,
     663,   675,   685,   693,   701,   302,   425,   602,   636,   664,
     676,   686,   694,   702,   708,   712,   716,   720,   724,   728,
     732,   306,   427,   603,   637,   665,   677,   687,   695,   703,
     709,   713,   717,   721,   725,   729,   733,   311,   315,   430,
     604,   638,   249,   320,   324,   433,   328,   435,   332,   437,
     605,   639,   336,   439,   606,   640,   340,   441,   607,   641,
     666,   344,   443,   608,   642,   667,   261,   410,   267,   411,
     271,   413,   277,   415,   281,   416,   287,   417,   291,   419,
     295,   420,   299,   422,   303,   424,   307,   426,   312,   428,
     316,   429,   317,   404,   321,   431,   325,   432,   329,   434,
     333,   436,   337,   438,   341,   440,   345,   442,   369,   445,
     609,   643,   373,   447,   377,   449,   610,   381,   451,   611,
     644,   385,   453,   612,   645,   393,   454,   613,   646,   668,
     678,   370,   444,   374,   446,   378,   448,   382,   450,   386,
     452
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -205
static const short yypact[] =
{
      27,  -205,    36,    77,  -205,     7,  -205,  -205,  -205,   118,
       9,  -205,   104,  -205,  -205,  -205,    60,  -205,   143,  -205,
    -205,    61,    61,    68,    68,    68,    68,    68,  -205,  -205,
    -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,    75,  -205,
    -205,  -205,  -205,  -205,  -205,  -205,  -205,    71,  -205,  -205,
     106,   124,    61,   108,   152,   148,  -205,  -205,  -205,  -205,
    -205,    88,    68,    68,  -205,   114,    81,    85,    71,  -205,
    -205,  -205,  -205,  -205,   531,   531,   531,   531,  -205,  -205,
    -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,
    -205,   531,   531,   531,   531,  -205,  -205,   531,   531,   531,
     531,  -205,  -205,  -205,   166,   148,  -205,  -205,  -205,  -205,
    -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,
    -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,
    -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,
    -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,
    -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,
    -205,  -205,  -205,   817,  -205,  -205,  -205,  -205,   130,  -205,
    -205,  -205,  -205,   411,    68,  -205,   131,    88,   175,   175,
     -27,   -16,    33,    99,   126,   -11,    98,   129,   150,   366,
     393,    80,   395,   411,   397,   409,   414,   423,   425,   440,
     457,   141,   153,   153,   215,   153,   304,   304,   215,   153,
     215,   153,    67,   153,    47,   215,   215,   153,   215,   153,
     215,   153,   103,   530,   532,   534,   536,   304,   153,   153,
     153,   153,   153,  -205,   237,  -205,   131,    88,   175,   175,
    -205,   131,    88,   175,   175,  -205,  -205,  -205,  -205,  -205,
    -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,
    -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,
    -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,
    -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,
    -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,
    -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,
    -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,
    -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,
    -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,
    -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,
    -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,
    -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,
    -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,
    -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,
    -205,  -205,  -205,  -205,   175,  -205,  -205,  -205,  -205,   128,
    -205,  -205,  -205,  -205,   541,   171,   254,   254,   817,   817,
     256,   109,   153,   112,   153,   115,   122,     8,   304,    92,
     205,   215,   212,   153,   222,   215,   232,   153,    65,   251,
     153,   253,   255,   215,   257,   153,   267,   215,   269,   153,
     271,   215,   273,   153,    96,   304,   359,   153,   364,   153,
     370,   153,   382,   153,   153,  -205,   870,   870,  -205,  -205,
    -205,   131,   175,  -205,  -205,  -205,   284,  -205,  -205,  -205,
    -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,
    -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,
    -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,
    -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,
    -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,
    -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,
    -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,   -27,
     -16,    33,    99,   126,   -11,    98,   129,   150,   366,   393,
      80,   395,   411,   397,   409,   414,   423,   425,   440,   457,
     141,   153,   153,   215,   153,   304,   304,   215,   153,   215,
     153,    67,   153,    47,   215,   215,   153,   215,   153,   215,
     153,   103,   530,   532,   534,   536,   304,   153,   153,   153,
     153,   153,  -205,  -205,  -205,  -205,   175,   153,   153,   304,
     215,   153,   215,   153,   153,   215,   153,   215,   153,   304,
     153,   153,   153,   153,  -205,  -205,  -205,  -205,  -205,  -205,
    -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,
    -205,  -205,   153,  -205,   215,   153,   215,   153,   153,  -205,
    -205,   215,   153,   304,   153,   153,   153,  -205,   202,  -205,
    -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,
    -205,  -205,   215,   153,   215,   153,  -205,  -205,   153,  -205,
    -205,  -205,  -205,  -205,   215,   153,   215,   153,   153,  -205,
    -205,  -205,  -205,  -205,   215,   153,   215,   153,  -205,  -205,
    -205,  -205,   215,   153,   215,   153,  -205,  -205,  -205,  -205,
     215,   153,   215,   153,  -205,  -205,  -205,  -205,   215,   153,
    -205,  -205,   215,   153,  -205,  -205,   215,   153,  -205,  -205,
     215,   153,  -205,  -205,   215,   153,  -205,  -205,   215,   153,
    -205,  -205,   215,   153,  -205,  -205
};

/* YYPGOTO[NTERM-NUM].  */
static const short yypgoto[] =
{
    -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,
    -205,  -205,  -205,    38,  -205,   -15,  -205,  -205,  -205,   236,
    -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,
    -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,
     240,  -205,  -205,  -205,   244,  -205,  -205,   247,  -205,   209,
    -205,   249,  -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,
     -85,  -205,  -205,  -205,  -205,  -205,  -205,   -71,  -205,  -205,
    -205,    44,   140,  -159,  -179,  -112,    20,  -138,  -134,   105,
    -182,  -200,  -198,  -205,  -205,  -196,  -205,  -205,  -205,  -199,
    -194,  -197,  -205,  -205,  -205,  -205,  -195,  -193,  -205,  -205,
    -205,  -205,  -205,  -205,  -205,  -205,  -185,  -205,  -205,  -205,
    -205,  -205,  -205,  -205,  -205,  -188,  -205,  -205,  -205,  -205,
    -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,
    -205,  -183,  -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,
    -205,  -205,  -205,  -205,  -205,  -205,  -205,  -186,  -180,  -205,
    -205,  -205,  -201,  -181,  -178,  -205,  -172,  -205,  -163,  -205,
    -205,  -205,  -187,  -205,  -205,  -205,  -166,  -205,  -205,  -205,
    -205,  -204,  -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,
    -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,
    -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,
    -205,  -205,   151,  -205,  -205,  -205,  -205,  -205,  -205,  -205,
    -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,  -169,  -205,
    -205,  -205,  -167,  -205,  -189,  -205,  -205,  -164,  -205,  -205,
    -205,  -157,  -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,
    -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,
    -205
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const unsigned short yytable[] =
{
     269,   346,   279,    30,   347,   349,   297,   348,   305,   351,
     314,   350,   352,   359,   327,   353,   335,   366,   343,   255,
     256,   269,   355,   279,   354,   235,   357,   297,   356,   305,
       1,   314,   364,   358,   360,   327,     4,   335,   361,   343,
     389,   372,   376,   380,   384,   362,   372,   376,   380,   384,
     392,   257,   289,   258,   365,   363,   259,   395,   387,   262,
     263,   388,   400,   282,   283,   254,   390,   264,    43,    44,
      45,    46,   284,   289,   391,    23,    24,    23,    24,   397,
     398,     5,   282,   283,   402,   403,    13,     7,   368,    14,
      23,    24,   481,   368,   159,   160,   161,   162,    91,    92,
      93,    94,    97,    98,    99,   100,    71,    72,   262,   263,
      16,   164,   165,   166,   167,    73,   268,   169,   170,   171,
     172,    21,    22,    10,   245,   396,    25,   246,    26,    27,
     401,    74,    75,    76,    77,    21,    22,    19,    23,    24,
      25,    28,    26,    27,   308,    28,   308,    28,    41,   498,
      21,    22,    48,    23,    24,    25,    56,    26,    27,   308,
      28,    39,    40,   309,    63,    95,   282,   283,    69,   101,
     282,   283,   282,   283,   272,   273,   484,   282,   283,   174,
     523,   288,   274,   234,   262,   263,   367,   262,   263,    58,
     272,   273,    60,   471,    78,    61,   474,   262,   263,   477,
      79,   262,   263,   460,   272,   273,   479,    59,    28,   278,
     470,   252,   292,   472,   458,   240,   478,   475,   251,   257,
     482,   258,   480,    28,   485,   262,   263,   487,   262,   263,
     473,   269,   476,   296,   279,   455,   493,   490,   521,    62,
     297,   491,   499,   496,   305,   497,   394,   314,   502,   501,
     504,   515,   327,   510,   506,    78,   335,   516,   461,   530,
     343,   522,   509,   462,   372,   528,   376,   531,   380,   534,
     384,   537,   538,   512,   518,   524,   282,   283,   399,   527,
     272,   273,   594,   660,   483,   289,   533,   262,   263,   486,
     272,   273,   293,   596,   301,   536,   489,   272,   273,   319,
     323,    80,   331,   595,   339,    81,   492,   262,   263,    82,
     368,   525,    83,   293,   175,   301,   495,   103,   592,   593,
     319,   323,   464,   331,   250,   339,   262,   263,   272,   273,
     272,   273,   262,   263,   257,   500,   258,   503,   468,   505,
     469,   508,   272,   273,   262,   263,   272,   273,   262,   263,
       0,   511,     0,   514,     0,   517,     0,   520,     0,   269,
     346,   279,     0,   347,   349,   297,   348,   305,   351,   314,
     350,   352,   359,   327,   353,   335,   366,   343,   282,   283,
     269,   355,   279,   354,    30,   357,   297,   356,   305,     0,
     314,   364,   358,   360,   327,     0,   335,   361,   343,   389,
     372,   376,   380,   384,   362,   372,   376,   380,   384,   392,
       0,   289,     0,   365,   363,   615,   616,   387,     0,   619,
     388,   621,   622,     0,   624,   390,   626,     0,   628,   629,
     630,   631,   289,   391,   262,   263,     0,   614,     0,   262,
     263,   272,   273,   526,     0,   262,   263,   368,   529,   300,
     647,     0,   368,   650,   532,   652,   653,   262,   263,     0,
     655,     0,   657,   658,   659,   617,   535,     0,   262,   263,
     262,   263,   272,   273,     0,   627,   304,     0,   313,     0,
     318,   670,     0,   672,   272,   273,   673,     0,   245,   262,
     263,   246,   322,   680,   247,   682,   683,   326,   272,   273,
     262,   263,     0,   689,     0,   691,   330,     0,   334,   656,
       0,   697,     0,   699,   661,   272,   273,     0,     0,   705,
       0,   707,     0,   338,     0,   293,   488,   711,     0,   301,
     494,   715,   262,   263,     0,   719,   319,   323,   507,   723,
     342,   331,   513,   727,     0,   339,   519,   731,     0,     0,
       0,   735,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   262,   263,   262,   263,   262,
     263,   262,   263,   371,     0,   375,     0,   379,   245,   383,
       0,   246,     0,     0,     0,   459,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   293,     0,   301,     0,     0,     0,     0,   319,   323,
       0,   331,     0,   339,     0,     0,     0,     0,     0,     0,
       0,     0,   293,     0,   301,     0,     0,     0,     0,   319,
     323,     0,   331,     0,   339,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   618,     0,   620,     0,     0,
     623,     0,   625,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   649,
       0,   651,     0,     0,     0,     0,   654,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   669,     0,   671,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   679,
       0,   681,     0,     0,     0,     0,     0,     0,     0,   688,
       0,   690,     0,     0,     0,     0,     0,   696,     0,   698,
       0,     0,     0,     0,     0,   704,     0,   706,     0,     0,
       0,     0,     0,   710,     0,     0,     0,   714,     0,     0,
       0,   718,     0,     0,     0,   722,     0,     0,     0,   726,
       0,     0,     0,   730,     0,     0,     0,   734,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   189,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   199,   200,   201,
     202,   203,   204,   205,   206,   207,   208,   209,   210,   211,
     212,   213,   214,   215,   216,   217,   218,   219,   220,   221,
     222,   223,   224,   225,   226,   227,   228,   229,   230,   231,
     232,   539,   540,   541,   542,   543,   544,   545,   546,   547,
     548,   549,   550,   551,   552,   553,   554,   555,   556,   557,
     558,   559,   560,   561,   562,   563,   564,   565,   566,   567,
     568,   569,   570,   571,   572,   573,   574,   575,   576,   577,
     578,   579,   580,   581,   582,   583,   584,   585,   586,   587,
     588,   589,   590,   591
};

static const short yycheck[] =
{
     182,   201,   184,    18,   202,   204,   188,   203,   190,   206,
     192,   205,   207,   214,   196,   208,   198,   221,   200,   178,
     179,   203,   210,   205,   209,   163,   212,   209,   211,   211,
       3,   213,   219,   213,   215,   217,     0,   219,   216,   221,
     229,   223,   224,   225,   226,   217,   228,   229,   230,   231,
     232,    78,   186,    80,   220,   218,    83,   236,   227,    75,
      76,   228,   241,    74,    75,   177,   230,    83,    24,    25,
      26,    27,    83,   207,   231,    10,    11,    10,    11,   238,
     239,     4,    74,    75,   243,   244,    77,    80,   222,    80,
      10,    11,    84,   227,    74,    75,    76,    77,    17,    18,
      19,    20,    17,    18,    19,    20,    62,    63,    75,    76,
       6,    91,    92,    93,    94,     1,    83,    97,    98,    99,
     100,     7,     8,     5,    77,   237,    12,    80,    14,    15,
     242,    17,    18,    19,    20,     7,     8,    77,    10,    11,
      12,    80,    14,    15,    79,    80,    79,    80,    80,    84,
       7,     8,    77,    10,    11,    12,    85,    14,    15,    79,
      80,    21,    22,    83,    16,    84,    74,    75,    80,    84,
      74,    75,    74,    75,    75,    76,    84,    74,    75,    13,
      84,    83,    83,   163,    75,    76,    83,    75,    76,    83,
      75,    76,    52,    84,    80,    87,    84,    75,    76,    84,
      86,    75,    76,   404,    75,    76,    84,    83,    80,    83,
     410,    80,    83,   411,    86,    85,   415,   413,   174,    78,
     417,    80,   416,    80,   419,    75,    76,   420,    75,    76,
     412,   413,   414,    83,   416,   394,   424,   422,   442,    87,
     422,   423,   428,   426,   426,   427,     9,   429,   430,   429,
     431,   438,   434,   435,   432,    80,   438,   439,    87,   448,
     442,   443,   434,     9,   446,   447,   448,   449,   450,   451,
     452,   453,   454,   436,   440,   444,    74,    75,   240,   446,
      75,    76,   461,    81,   418,   419,   450,    75,    76,    84,
      75,    76,   187,     9,   189,   452,    84,    75,    76,   194,
     195,    65,   197,   462,   199,    65,    84,    75,    76,    65,
     444,   445,    65,   208,   105,   210,    84,    68,   456,   457,
     215,   216,   407,   218,   173,   220,    75,    76,    75,    76,
      75,    76,    75,    76,    78,    84,    80,    84,   409,    84,
      84,    84,    75,    76,    75,    76,    75,    76,    75,    76,
      -1,    84,    -1,    84,    -1,    84,    -1,    84,    -1,   541,
     560,   543,    -1,   561,   563,   547,   562,   549,   565,   551,
     564,   566,   573,   555,   567,   557,   580,   559,    74,    75,
     562,   569,   564,   568,   399,   571,   568,   570,   570,    -1,
     572,   578,   572,   574,   576,    -1,   578,   575,   580,   588,
     582,   583,   584,   585,   576,   587,   588,   589,   590,   591,
      -1,   545,    -1,   579,   577,   597,   598,   586,    -1,   601,
     587,   603,   604,    -1,   606,   589,   608,    -1,   610,   611,
     612,   613,   566,   590,    75,    76,    -1,   596,    -1,    75,
      76,    75,    76,    84,    -1,    75,    76,   581,    84,    83,
     632,    -1,   586,   635,    84,   637,   638,    75,    76,    -1,
     642,    -1,   644,   645,   646,   599,    84,    -1,    75,    76,
      75,    76,    75,    76,    -1,   609,    83,    -1,    83,    -1,
      83,   663,    -1,   665,    75,    76,   668,    -1,    77,    75,
      76,    80,    83,   675,    83,   677,   678,    83,    75,    76,
      75,    76,    -1,   685,    -1,   687,    83,    -1,    83,   643,
      -1,   693,    -1,   695,   648,    75,    76,    -1,    -1,   701,
      -1,   703,    -1,    83,    -1,   420,   421,   709,    -1,   424,
     425,   713,    75,    76,    -1,   717,   431,   432,   433,   721,
      83,   436,   437,   725,    -1,   440,   441,   729,    -1,    -1,
      -1,   733,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    75,    76,    75,    76,    75,
      76,    75,    76,    83,    -1,    83,    -1,    83,    77,    83,
      -1,    80,    -1,    -1,    -1,    84,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   546,    -1,   548,    -1,    -1,    -1,    -1,   553,   554,
      -1,   556,    -1,   558,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   567,    -1,   569,    -1,    -1,    -1,    -1,   574,
     575,    -1,   577,    -1,   579,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   600,    -1,   602,    -1,    -1,
     605,    -1,   607,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   634,
      -1,   636,    -1,    -1,    -1,    -1,   641,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   662,    -1,   664,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   674,
      -1,   676,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   684,
      -1,   686,    -1,    -1,    -1,    -1,    -1,   692,    -1,   694,
      -1,    -1,    -1,    -1,    -1,   700,    -1,   702,    -1,    -1,
      -1,    -1,    -1,   708,    -1,    -1,    -1,   712,    -1,    -1,
      -1,   716,    -1,    -1,    -1,   720,    -1,    -1,    -1,   724,
      -1,    -1,    -1,   728,    -1,    -1,    -1,   732,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned short yystos[] =
{
       0,     3,    89,    90,     0,     4,    91,    80,    92,    93,
       5,    94,    96,    77,    80,    95,     6,    97,   101,    77,
      99,     7,     8,    10,    11,    12,    14,    15,    80,   102,
     103,   107,   108,   119,   128,   132,   135,   160,    98,   160,
     160,    80,   159,   159,   159,   159,   159,   104,    77,   100,
     109,   120,   105,   129,   133,   136,    85,   139,    83,    83,
     160,    87,    87,    16,   137,   140,   111,   122,   106,    80,
     163,   159,   159,     1,    17,    18,    19,    20,    80,    86,
     107,   128,   132,   135,   141,   142,   145,   149,   152,   156,
     161,    17,    18,    19,    20,    84,   112,    17,    18,    19,
      20,    84,   123,   139,   130,   134,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,   164,
     164,   164,   164,   157,   164,   164,   164,   164,   110,   164,
     164,   164,   164,   121,    13,   137,   143,   146,   153,   150,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,   158,   164,   165,   113,   114,   117,   115,
      85,   124,   125,   127,   126,    77,    80,    83,   138,   240,
     290,   159,    80,   162,   163,   161,   161,    78,    80,    83,
     169,   264,    75,    76,    83,   168,   170,   266,    83,   168,
     173,   268,    75,    76,    83,   167,   177,   270,    83,   168,
     178,   272,    74,    75,    83,   166,   179,   274,    83,   166,
     184,   276,    83,   167,   185,   278,    83,   168,   194,   280,
      83,   167,   203,   282,    83,   168,   219,   284,    79,    83,
     103,   235,   286,    83,   168,   236,   288,   290,    83,   167,
     241,   292,    83,   167,   242,   294,    83,   168,   244,   296,
      83,   167,   246,   298,    83,   168,   250,   300,    83,   167,
     254,   302,    83,   168,   259,   304,   169,   170,   173,   177,
     178,   179,   184,   185,   194,   203,   219,   235,   236,   240,
     241,   242,   244,   246,   250,   254,   259,    83,   166,   306,
     329,    83,   168,   310,   331,    83,   168,   312,   333,    83,
     168,   315,   335,    83,   168,   319,   337,   306,   310,   312,
     315,   319,   168,   323,     9,   162,   163,   161,   161,   101,
     162,   163,   161,   161,   291,   131,   144,   147,   154,   151,
     265,   267,   171,   269,   174,   271,   273,   275,   180,   277,
     279,   186,   281,   195,   283,   204,   285,   220,   287,   289,
     237,   293,   295,   243,   297,   245,   299,   247,   301,   251,
     303,   255,   305,   260,   330,   307,   332,   311,   334,   313,
     336,   316,   338,   320,   324,   161,   118,   116,    86,    84,
     240,    87,     9,   148,   148,   155,   164,   165,   155,    84,
     169,    84,   170,   168,    84,   173,   168,    84,   177,    84,
     178,    84,   179,   166,    84,   184,    84,   185,   167,    84,
     194,   168,    84,   203,   167,    84,   219,   168,    84,   235,
      84,   236,   168,    84,   241,    84,   242,   167,    84,   244,
     168,    84,   246,   167,    84,   250,   168,    84,   254,   167,
      84,   259,   168,    84,   306,   166,    84,   310,   168,    84,
     312,   168,    84,   315,   168,    84,   319,   168,   168,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,   165,   165,   162,   161,     9,   172,   175,   181,
     187,   196,   205,   221,   238,   248,   252,   256,   261,   308,
     314,   317,   321,   325,   161,   168,   168,   166,   167,   168,
     167,   168,   168,   167,   168,   167,   168,   166,   168,   168,
     168,   168,   176,   182,   188,   197,   206,   222,   239,   249,
     253,   257,   262,   309,   318,   322,   326,   168,   183,   167,
     168,   167,   168,   168,   167,   168,   166,   168,   168,   168,
      81,   166,   189,   198,   207,   223,   258,   263,   327,   167,
     168,   167,   168,   168,   190,   199,   208,   224,   328,   167,
     168,   167,   168,   168,   191,   200,   209,   225,   167,   168,
     167,   168,   192,   201,   210,   226,   167,   168,   167,   168,
     193,   202,   211,   227,   167,   168,   167,   168,   212,   228,
     167,   168,   213,   229,   167,   168,   214,   230,   167,   168,
     215,   231,   167,   168,   216,   232,   167,   168,   217,   233,
     167,   168,   218,   234,   167,   168
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

/* YYLLOC_DEFAULT -- Compute the default location (before the actions
   are run).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)		\
   ((Current).first_line   = (Rhs)[1].first_line,	\
    (Current).first_column = (Rhs)[1].first_column,	\
    (Current).last_line    = (Rhs)[N].last_line,	\
    (Current).last_column  = (Rhs)[N].last_column)
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

# define YYDSYMPRINT(Args)			\
do {						\
  if (yydebug)					\
    yysymprint Args;				\
} while (0)

# define YYDSYMPRINTF(Title, Token, Value, Location)		\
do {								\
  if (yydebug)							\
    {								\
      YYFPRINTF (stderr, "%s ", Title);				\
      yysymprint (stderr, 					\
                  Token, Value);	\
      YYFPRINTF (stderr, "\n");					\
    }								\
} while (0)

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_stack_print (short *bottom, short *top)
#else
static void
yy_stack_print (bottom, top)
    short *bottom;
    short *top;
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
# define YYDSYMPRINT(Args)
# define YYDSYMPRINTF(Title, Token, Value, Location)
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

#if defined (YYMAXDEPTH) && YYMAXDEPTH == 0
# undef YYMAXDEPTH
#endif

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
    {
      YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
# ifdef YYPRINT
      YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
    }
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

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
yydestruct (int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yytype, yyvaluep)
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

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
  /* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;

  register int yystate;
  register int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  short	yyssa[YYINITDEPTH];
  short *yyss = yyssa;
  register short *yyssp;

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
	short *yyss1 = yyss;


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
	short *yyss1 = yyss;
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
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
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
      YYDSYMPRINTF ("Next token is", yytoken, &yylval, &yylloc);
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

  /* Shift the lookahead token.  */
  YYDPRINTF ((stderr, "Shifting token %s, ", yytname[yytoken]));

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
    { SKEL->verifyHeader(yyvsp[0].stringVal); ;}
    break;

  case 5:
#line 207 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->profileElement(yyvsp[0].stringVal); ;}
    break;

  case 10:
#line 221 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->componentElement(yyvsp[0].stringVal); ;}
    break;

  case 15:
#line 238 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = yyvsp[0].stringVal; ;}
    break;

  case 16:
#line 240 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->metaElement(SKEL->_tmpString1.c_str(), yyvsp[0].stringVal); ;}
    break;

  case 26:
#line 260 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginNode(yyvsp[0].stringVal, 0); ;}
    break;

  case 28:
#line 263 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = yyvsp[0].stringVal; ;}
    break;

  case 29:
#line 264 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginNode(yyvsp[0].stringVal, SKEL->_tmpString1.c_str()); ;}
    break;

  case 31:
#line 267 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->use(yyvsp[0].stringVal); ;}
    break;

  case 34:
#line 278 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginProto(yyvsp[0].stringVal); ;}
    break;

  case 35:
#line 279 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endProtoInterface(); ;}
    break;

  case 36:
#line 280 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endProto(); ;}
    break;

  case 39:
#line 288 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 40:
#line 289 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginEventInDecl(SKEL->_tmpString1.c_str(), yyvsp[-2].intVal, yyvsp[0].stringVal); SKEL->endEventDecl(); ;}
    break;

  case 41:
#line 291 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 42:
#line 292 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginEventOutDecl(SKEL->_tmpString1.c_str(), yyvsp[-2].intVal, yyvsp[0].stringVal); SKEL->endEventDecl(); ;}
    break;

  case 43:
#line 294 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 44:
#line 295 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginFieldDecl(SKEL->_tmpString1.c_str(), yyvsp[-2].intVal, yyvsp[0].stringVal); SKEL->getLexer()->expectType(yyvsp[-2].intVal); ;}
    break;

  case 45:
#line 296 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endFieldDecl(); ;}
    break;

  case 46:
#line 298 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 47:
#line 299 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginExposedFieldDecl(SKEL->_tmpString1.c_str(), yyvsp[-2].intVal, yyvsp[0].stringVal); SKEL->getLexer()->expectType(yyvsp[-2].intVal); ;}
    break;

  case 48:
#line 300 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endExposedFieldDecl(); ;}
    break;

  case 49:
#line 303 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginExternProto(yyvsp[0].stringVal); ;}
    break;

  case 50:
#line 304 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endExternProtoInterface(); ;}
    break;

  case 51:
#line 305 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endExternProto(); ;}
    break;

  case 54:
#line 313 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 55:
#line 314 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->addExternEventInDecl(SKEL->_tmpString1.c_str(), yyvsp[-2].intVal, yyvsp[0].stringVal); ;}
    break;

  case 56:
#line 316 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 57:
#line 317 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->addExternEventOutDecl(SKEL->_tmpString1.c_str(), yyvsp[-2].intVal, yyvsp[0].stringVal); ;}
    break;

  case 58:
#line 319 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 59:
#line 320 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->addExternFieldDecl(SKEL->_tmpString1.c_str(), yyvsp[-2].intVal, yyvsp[0].stringVal); ;}
    break;

  case 60:
#line 322 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 61:
#line 323 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->addExternExposedFieldDecl(SKEL->_tmpString1.c_str(), yyvsp[-2].intVal, yyvsp[0].stringVal); ;}
    break;

  case 62:
#line 327 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = yyvsp[0].stringVal; ;}
    break;

  case 63:
#line 329 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString2 = yyvsp[0].stringVal; ;}
    break;

  case 64:
#line 331 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString3 = yyvsp[0].stringVal; ;}
    break;

  case 65:
#line 334 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->addRoute(SKEL->_tmpString1.c_str(), SKEL->_tmpString2.c_str(), SKEL->_tmpString3.c_str(), yyvsp[0].stringVal); ;}
    break;

  case 66:
#line 338 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = yyvsp[0].stringVal; ;}
    break;

  case 67:
#line 340 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString2 = yyvsp[0].stringVal; ;}
    break;

  case 68:
#line 342 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        if (yyvsp[0].stringVal != 0)
            SKEL->importElement(SKEL->_tmpString1.c_str(), SKEL->_tmpString2.c_str(), yyvsp[0].stringVal);
        else
            SKEL->importElement(SKEL->_tmpString1.c_str(), SKEL->_tmpString2.c_str(), 0);
    ;}
    break;

  case 69:
#line 351 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = yyvsp[0].stringVal; ;}
    break;

  case 70:
#line 353 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        if (yyvsp[0].stringVal != 0)
            SKEL->exportElement(SKEL->_tmpString1.c_str(), yyvsp[0].stringVal);
        else
            SKEL->exportElement(SKEL->_tmpString1.c_str(), 0);
    ;}
    break;

  case 71:
#line 362 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { yyval.stringVal = yyvsp[0].stringVal; ;}
    break;

  case 72:
#line 363 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { yyval.stringVal = 0; ;}
    break;

  case 74:
#line 369 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endNode(); ;}
    break;

  case 83:
#line 385 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 84:
#line 386 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginEventInDecl(SKEL->_tmpString1.c_str(), yyvsp[-2].intVal, yyvsp[0].stringVal); ;}
    break;

  case 85:
#line 387 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endEventDecl(); ;}
    break;

  case 86:
#line 391 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 87:
#line 392 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginEventOutDecl(SKEL->_tmpString1.c_str(), yyvsp[-2].intVal, yyvsp[0].stringVal); ;}
    break;

  case 88:
#line 393 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endEventDecl(); ;}
    break;

  case 90:
#line 397 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->is(yyvsp[0].stringVal); ;}
    break;

  case 91:
#line 401 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 92:
#line 402 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginFieldDecl(SKEL->_tmpString1.c_str(), yyvsp[-2].intVal, yyvsp[0].stringVal); SKEL->getLexer()->expectType(yyvsp[-2].intVal); ;}
    break;

  case 93:
#line 403 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endFieldDecl(); ;}
    break;

  case 94:
#line 407 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 95:
#line 408 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginExposedFieldDecl(SKEL->_tmpString1.c_str(), yyvsp[-2].intVal, yyvsp[0].stringVal); SKEL->getLexer()->expectType(yyvsp[-2].intVal); ;}
    break;

  case 96:
#line 409 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endExposedFieldDecl(); ;}
    break;

  case 98:
#line 413 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->is(yyvsp[0].stringVal); ;}
    break;

  case 99:
#line 417 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        Int32 iFieldTypeId = SKEL->getFieldType(yyvsp[0].stringVal);
        if (SKEL->getMapFieldTypes() == true)
            iFieldTypeId = SKEL->mapExtIntFieldType(yyvsp[0].stringVal, iFieldTypeId);
        SKEL->getLexer()->expectType(iFieldTypeId);
        SKEL->beginField(yyvsp[0].stringVal, iFieldTypeId);
    ;}
    break;

  case 100:
#line 424 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endField(); ;}
    break;

  case 106:
#line 432 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->is(yyvsp[0].stringVal); ;}
    break;

  case 218:
#line 562 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { yyval.intVal = yyvsp[0].intVal; ;}
    break;

  case 219:
#line 563 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { yyval.intVal = yyvsp[0].intVal; ;}
    break;

  case 220:
#line 566 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { yyval.doubleVal = yyvsp[0].intVal; ;}
    break;

  case 221:
#line 567 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { yyval.doubleVal = yyvsp[0].doubleVal; ;}
    break;

  case 222:
#line 570 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { yyval.floatVal = static_cast<float>(yyvsp[0].intVal); ;}
    break;

  case 223:
#line 571 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { yyval.floatVal = static_cast<float>(yyvsp[0].doubleVal); ;}
    break;

  case 224:
#line 575 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->addBoolValue(yyvsp[0].boolVal);
    ;}
    break;

  case 225:
#line 578 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->addFieldValue(yyvsp[0].stringVal); ;}
    break;

  case 226:
#line 581 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 227:
#line 582 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 228:
#line 584 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addColorValue(Color3f(yyvsp[-4].floatVal, yyvsp[-2].floatVal, yyvsp[0].floatVal));
    ;}
    break;

  case 229:
#line 590 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 230:
#line 591 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 231:
#line 592 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 232:
#line 594 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addColorRGBAValue(Color4f(yyvsp[-6].floatVal, yyvsp[-4].floatVal, yyvsp[-2].floatVal, yyvsp[0].floatVal));
    ;}
    break;

  case 233:
#line 601 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->addDoubleValue(yyvsp[0].doubleVal);
    ;}
    break;

  case 234:
#line 607 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->addFloatValue(yyvsp[0].floatVal);
    ;}
    break;

  case 235:
#line 612 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 236:
#line 613 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 237:
#line 615 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->beginImage(yyvsp[-4].intVal, yyvsp[-2].intVal, yyvsp[0].intVal);
    ;}
    break;

  case 238:
#line 620 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->endImage();
    ;}
    break;

  case 239:
#line 626 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->addImagePixel(yyvsp[0].intVal);
    ;}
    break;

  case 241:
#line 633 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->addInt32Value(yyvsp[0].intVal);
    ;}
    break;

  case 242:
#line 638 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 243:
#line 639 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 244:
#line 640 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 245:
#line 641 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 246:
#line 642 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 247:
#line 643 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 248:
#line 644 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 249:
#line 645 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 250:
#line 647 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addMatrix3dValue(
            yyvsp[-16].doubleVal,  yyvsp[-10].doubleVal, yyvsp[-4].doubleVal,
            yyvsp[-14].doubleVal,  yyvsp[-8].doubleVal, yyvsp[-2].doubleVal,
            yyvsp[-12].doubleVal, yyvsp[-6].doubleVal, yyvsp[0].doubleVal);
    ;}
    break;

  case 251:
#line 656 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 252:
#line 657 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 253:
#line 658 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 254:
#line 659 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 255:
#line 660 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 256:
#line 661 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 257:
#line 662 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 258:
#line 663 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 259:
#line 665 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addMatrix3fValue(
            yyvsp[-16].floatVal,  yyvsp[-10].floatVal, yyvsp[-4].floatVal,
            yyvsp[-14].floatVal,  yyvsp[-8].floatVal, yyvsp[-2].floatVal,
            yyvsp[-12].floatVal, yyvsp[-6].floatVal, yyvsp[0].floatVal);
    ;}
    break;

  case 260:
#line 674 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 261:
#line 675 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 262:
#line 676 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 263:
#line 677 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 264:
#line 678 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 265:
#line 679 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 266:
#line 680 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 267:
#line 681 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 268:
#line 682 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 269:
#line 683 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 270:
#line 684 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 271:
#line 685 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 272:
#line 686 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 273:
#line 687 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 274:
#line 688 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 275:
#line 690 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addMatrix4dValue(Matrix4d(
            yyvsp[-30].doubleVal,  yyvsp[-22].doubleVal, yyvsp[-14].doubleVal, yyvsp[-6].doubleVal,
            yyvsp[-28].doubleVal, yyvsp[-20].doubleVal, yyvsp[-12].doubleVal, yyvsp[-4].doubleVal,
            yyvsp[-26].doubleVal, yyvsp[-18].doubleVal, yyvsp[-10].doubleVal, yyvsp[-2].doubleVal,
            yyvsp[-24].doubleVal, yyvsp[-16].doubleVal, yyvsp[-8].doubleVal, yyvsp[0].doubleVal));
    ;}
    break;

  case 276:
#line 700 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 277:
#line 701 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 278:
#line 702 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 279:
#line 703 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 280:
#line 704 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 281:
#line 705 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 282:
#line 706 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 283:
#line 707 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 284:
#line 708 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 285:
#line 709 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 286:
#line 710 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 287:
#line 711 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 288:
#line 712 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 289:
#line 713 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 290:
#line 714 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 291:
#line 716 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addMatrix4fValue(Matrix4f(
            yyvsp[-30].floatVal,  yyvsp[-22].floatVal, yyvsp[-14].floatVal, yyvsp[-6].floatVal,
            yyvsp[-28].floatVal, yyvsp[-20].floatVal, yyvsp[-12].floatVal, yyvsp[-4].floatVal,
            yyvsp[-26].floatVal, yyvsp[-18].floatVal, yyvsp[-10].floatVal, yyvsp[-2].floatVal,
            yyvsp[-24].floatVal, yyvsp[-16].floatVal, yyvsp[-8].floatVal, yyvsp[0].floatVal));
    ;}
    break;

  case 293:
#line 727 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->nullNode(); ;}
    break;

  case 294:
#line 730 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 295:
#line 731 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 296:
#line 732 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 297:
#line 734 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addRotationValue(Vec3f(yyvsp[-6].floatVal, yyvsp[-4].floatVal, yyvsp[-2].floatVal), yyvsp[0].floatVal);
    ;}
    break;

  case 298:
#line 741 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->addStringValue(yyvsp[0].stringVal);
    ;}
    break;

  case 299:
#line 745 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { /* Not VRML conformant */
        SKEL->addStringValue(yyvsp[0].stringVal);
    ;}
    break;

  case 300:
#line 751 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->addTimeValue(yyvsp[0].doubleVal);
    ;}
    break;

  case 301:
#line 756 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 302:
#line 758 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addVec2dValue(Vec2d(yyvsp[-2].doubleVal, yyvsp[0].doubleVal));
    ;}
    break;

  case 303:
#line 764 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 304:
#line 766 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addVec2fValue(Vec2f(yyvsp[-2].floatVal, yyvsp[0].floatVal));
    ;}
    break;

  case 305:
#line 772 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 306:
#line 773 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 307:
#line 774 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 308:
#line 775 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addVec3dValue(Vec3d(yyvsp[-5].doubleVal, yyvsp[-3].doubleVal, yyvsp[-1].doubleVal));
    ;}
    break;

  case 309:
#line 781 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 310:
#line 782 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 311:
#line 783 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 312:
#line 784 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addVec3fValue(Vec3f(yyvsp[-5].floatVal, yyvsp[-3].floatVal, yyvsp[-1].floatVal));
    ;}
    break;

  case 313:
#line 790 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 314:
#line 791 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 315:
#line 792 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 316:
#line 793 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 317:
#line 794 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addVec4dValue(Vec4d(yyvsp[-7].doubleVal, yyvsp[-5].doubleVal, yyvsp[-3].doubleVal, yyvsp[-1].doubleVal));
    ;}
    break;

  case 318:
#line 800 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 319:
#line 801 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 320:
#line 802 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 321:
#line 803 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 322:
#line 804 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addVec4fValue(Vec4f(yyvsp[-7].floatVal, yyvsp[-5].floatVal, yyvsp[-3].floatVal, yyvsp[-1].floatVal));
    ;}
    break;

  case 407:
#line 980 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 408:
#line 981 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 409:
#line 982 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 410:
#line 984 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addColor4iValue(Color4ub(static_cast<UInt8>(yyvsp[-6].intVal), static_cast<UInt8>(yyvsp[-4].intVal),
                                       static_cast<UInt8>(yyvsp[-2].intVal), static_cast<UInt8>(yyvsp[0].intVal)));
    ;}
    break;

  case 411:
#line 991 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 412:
#line 993 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addPnt2fValue(Pnt2f(yyvsp[-2].floatVal, yyvsp[0].floatVal));
    ;}
    break;

  case 413:
#line 999 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 414:
#line 1000 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 415:
#line 1002 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addPnt3fValue(Pnt3f(yyvsp[-4].floatVal, yyvsp[-2].floatVal, yyvsp[0].floatVal));
    ;}
    break;

  case 416:
#line 1008 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 417:
#line 1009 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 418:
#line 1010 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 419:
#line 1012 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addPnt4fValue(Pnt4f(yyvsp[-6].floatVal, yyvsp[-4].floatVal, yyvsp[-2].floatVal, yyvsp[0].floatVal));
    ;}
    break;

  case 420:
#line 1018 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 421:
#line 1019 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 422:
#line 1020 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 423:
#line 1022 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addPlaneValue(Plane(Vec3f(yyvsp[-6].floatVal, yyvsp[-4].floatVal, yyvsp[-2].floatVal), yyvsp[0].floatVal));
    ;}
    break;

  case 424:
#line 1028 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 425:
#line 1029 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 426:
#line 1030 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 427:
#line 1031 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 428:
#line 1032 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 429:
#line 1034 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        BoxVolume bv(yyvsp[-10].floatVal, yyvsp[-8].floatVal, yyvsp[-6].floatVal, yyvsp[-4].floatVal, yyvsp[-2].floatVal, yyvsp[0].floatVal);
        
        SKEL->addVolumeValue(bv);
    ;}
    break;


    }

/* Line 1000 of yacc.c.  */
#line 3047 "Source/System/FileIO/ScanParseSkel/prebuild/OSGScanParseSkelParser.cpp"

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
      /* If just tried and failed to reuse lookahead token after an
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
		 YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
		 yydestruct (yystos[*yyssp], yyvsp);
	       }
        }
      else
	{
	  YYDSYMPRINTF ("Error: discarding", yytoken, &yylval, &yylloc);
	  yydestruct (yytoken, &yylval);
	  yychar = YYEMPTY;

	}
    }

  /* Else will try to reuse lookahead token after shifting the error
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

      YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
      yydestruct (yystos[yystate], yyvsp);
      YYPOPSTACK;
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  YYDPRINTF ((stderr, "Shifting error token, "));

  *++yyvsp = yylval;


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


#line 1081 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"


int OSGScanParseSkel_lex(YYSTYPE *lvalp, void *pSkel)
{
    return SKEL->lex(lvalp);
}

