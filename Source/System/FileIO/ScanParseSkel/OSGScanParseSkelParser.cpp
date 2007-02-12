/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

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
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

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
/* Tokens.  */
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

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 41 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
{
    long intVal;
    double doubleVal;
    float floatVal;
    const char *stringVal;
    bool boolVal;
}
/* Line 193 of yacc.c.  */
#line 277 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.cpp"
	YYSTYPE;
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



/* Line 216 of yacc.c.  */
#line 319 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.cpp"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
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
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   975

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  88
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  258
/* YYNRULES -- Number of rules.  */
#define YYNRULES  459
/* YYNRULES -- Number of states.  */
#define YYNSTATES  750

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   337

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
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
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     9,    11,    12,    15,    16,    18,    21,
      22,    25,    27,    29,    32,    33,    34,    39,    41,    43,
      46,    47,    49,    51,    53,    55,    57,    58,    62,    63,
      64,    71,    74,    75,    79,    80,    81,    88,    90,    92,
      95,    96,    97,    98,   109,   113,   116,   117,   118,   123,
     124,   129,   130,   131,   138,   139,   140,   147,   148,   149,
     158,   161,   162,   163,   168,   169,   174,   175,   180,   181,
     186,   187,   188,   189,   201,   202,   203,   211,   212,   217,
     220,   221,   223,   227,   230,   231,   233,   235,   237,   239,
     241,   243,   244,   245,   252,   253,   254,   261,   262,   265,
     266,   267,   274,   275,   276,   283,   285,   289,   290,   294,
     296,   298,   300,   302,   304,   308,   310,   312,   314,   316,
     318,   320,   322,   324,   326,   328,   330,   332,   334,   336,
     338,   340,   342,   344,   346,   348,   350,   352,   354,   356,
     358,   360,   362,   364,   366,   368,   370,   372,   374,   376,
     378,   380,   382,   384,   386,   388,   390,   392,   394,   396,
     398,   400,   402,   404,   406,   408,   410,   412,   414,   416,
     418,   420,   422,   424,   427,   430,   433,   436,   439,   442,
     445,   448,   451,   454,   457,   460,   463,   466,   469,   472,
     475,   478,   481,   484,   487,   490,   493,   496,   499,   502,
     505,   508,   511,   514,   517,   520,   523,   526,   529,   532,
     535,   538,   541,   544,   547,   550,   553,   556,   559,   562,
     565,   568,   571,   574,   577,   580,   583,   585,   587,   589,
     591,   593,   595,   597,   599,   600,   601,   607,   608,   609,
     610,   618,   620,   622,   623,   624,   625,   634,   637,   638,
     640,   641,   642,   643,   644,   645,   646,   647,   648,   666,
     667,   668,   669,   670,   671,   672,   673,   674,   692,   693,
     694,   695,   696,   697,   698,   699,   700,   701,   702,   703,
     704,   705,   706,   707,   739,   740,   741,   742,   743,   744,
     745,   746,   747,   748,   749,   750,   751,   752,   753,   754,
     786,   788,   790,   791,   792,   793,   801,   803,   805,   807,
     808,   812,   813,   817,   818,   819,   820,   827,   828,   829,
     830,   837,   838,   839,   840,   841,   850,   851,   852,   853,
     854,   863,   865,   869,   872,   873,   875,   879,   882,   883,
     885,   889,   892,   893,   895,   899,   902,   903,   905,   909,
     912,   913,   915,   919,   922,   923,   925,   929,   932,   933,
     935,   939,   942,   943,   945,   949,   952,   953,   955,   959,
     962,   963,   965,   969,   972,   973,   975,   979,   982,   983,
     985,   989,   992,   993,   995,   999,  1002,  1003,  1005,  1009,
    1012,  1013,  1015,  1019,  1022,  1023,  1025,  1029,  1032,  1033,
    1035,  1039,  1042,  1043,  1045,  1049,  1052,  1053,  1055,  1059,
    1062,  1063,  1065,  1069,  1072,  1073,  1074,  1075,  1076,  1084,
    1085,  1089,  1090,  1091,  1097,  1098,  1099,  1100,  1108,  1109,
    1110,  1111,  1119,  1120,  1121,  1122,  1123,  1133,  1134,  1138,
    1139,  1141,  1145,  1148,  1149,  1151,  1155,  1158,  1159,  1161,
    1165,  1168,  1169,  1171,  1175,  1178,  1179,  1181,  1185,  1188
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      89,     0,    -1,    90,    91,    93,    96,   101,    -1,     3,
      -1,    -1,     4,    92,    -1,    -1,    80,    -1,    93,    94,
      -1,    -1,     5,    95,    -1,    80,    -1,    77,    -1,    96,
      97,    -1,    -1,    -1,     6,    99,    98,   100,    -1,    77,
      -1,    77,    -1,   101,   102,    -1,    -1,   103,    -1,   111,
      -1,   134,    -1,   138,    -1,   141,    -1,    -1,   166,   104,
     145,    -1,    -1,    -1,    10,   165,   105,   166,   106,   145,
      -1,    11,   165,    -1,    -1,   166,   108,   145,    -1,    -1,
      -1,    10,   165,   109,   166,   110,   145,    -1,   113,    -1,
     125,    -1,   112,   111,    -1,    -1,    -1,    -1,     7,   166,
     114,    83,   117,    84,   115,    85,   116,    86,    -1,   112,
     107,   101,    -1,   117,   118,    -1,    -1,    -1,    17,   170,
     119,   168,    -1,    -1,    18,   170,   120,   169,    -1,    -1,
      -1,    20,   170,   121,   167,   122,   171,    -1,    -1,    -1,
      19,   170,   123,   167,   124,   171,    -1,    -1,    -1,     8,
     166,   126,    83,   128,    84,   127,   144,    -1,   128,   129,
      -1,    -1,    -1,    17,   170,   130,   168,    -1,    -1,    18,
     170,   131,   169,    -1,    -1,    20,   170,   132,   167,    -1,
      -1,    19,   170,   133,   167,    -1,    -1,    -1,    -1,    12,
     165,   135,    87,   169,   136,    13,   165,   137,    87,   168,
      -1,    -1,    -1,    14,   165,   139,    87,   165,   140,   143,
      -1,    -1,    15,   165,   142,   143,    -1,    16,   165,    -1,
      -1,   296,    -1,    85,   146,    86,    -1,   146,   147,    -1,
      -1,   162,    -1,   148,    -1,   151,    -1,   155,    -1,   158,
      -1,     1,    -1,    -1,    -1,    17,   170,   149,   168,   150,
     154,    -1,    -1,    -1,    18,   170,   152,   169,   153,   154,
      -1,    -1,     9,   167,    -1,    -1,    -1,    20,   170,   156,
     167,   157,   161,    -1,    -1,    -1,    19,   170,   159,   167,
     160,   161,    -1,   171,    -1,   170,     9,   167,    -1,    -1,
     167,   163,   164,    -1,   134,    -1,   111,    -1,   138,    -1,
     141,    -1,   171,    -1,   170,     9,   167,    -1,    80,    -1,
      80,    -1,    80,    -1,    80,    -1,    80,    -1,    21,    -1,
      22,    -1,    23,    -1,    24,    -1,    25,    -1,    26,    -1,
      27,    -1,    28,    -1,    29,    -1,    30,    -1,    31,    -1,
      32,    -1,    33,    -1,    34,    -1,    35,    -1,    36,    -1,
      37,    -1,    38,    -1,    39,    -1,    40,    -1,    41,    -1,
      42,    -1,    43,    -1,    44,    -1,    45,    -1,    46,    -1,
      47,    -1,    48,    -1,    49,    -1,    50,    -1,    51,    -1,
      52,    -1,    53,    -1,    54,    -1,    55,    -1,    56,    -1,
      57,    -1,    58,    -1,    59,    -1,    60,    -1,    61,    -1,
      62,    -1,    63,    -1,    64,    -1,    65,    -1,    66,    -1,
      67,    -1,    68,    -1,    69,    -1,    70,    -1,    71,    -1,
      72,    -1,    73,    -1,    21,   270,    -1,    22,   272,    -1,
      23,   274,    -1,    24,   276,    -1,    25,   278,    -1,    26,
     280,    -1,    27,   282,    -1,    28,   284,    -1,    29,   286,
      -1,    30,   288,    -1,    31,   290,    -1,    32,   292,    -1,
      33,   294,    -1,    34,   296,    -1,    35,   298,    -1,    36,
     300,    -1,    37,   302,    -1,    38,   304,    -1,    39,   306,
      -1,    40,   308,    -1,    41,   310,    -1,    42,   175,    -1,
      43,   176,    -1,    44,   179,    -1,    45,   183,    -1,    46,
     184,    -1,    47,   185,    -1,    48,   190,    -1,    49,   191,
      -1,    50,   200,    -1,    51,   209,    -1,    52,   225,    -1,
      53,   241,    -1,    54,   242,    -1,    55,   246,    -1,    56,
     247,    -1,    57,   248,    -1,    58,   250,    -1,    59,   252,
      -1,    60,   256,    -1,    61,   260,    -1,    62,   265,    -1,
      63,   336,    -1,    64,   338,    -1,    65,   340,    -1,    66,
     342,    -1,    67,   344,    -1,    68,   312,    -1,    69,   316,
      -1,    70,   318,    -1,    71,   321,    -1,    72,   325,    -1,
      73,   329,    -1,    74,    -1,    75,    -1,    75,    -1,    76,
      -1,    75,    -1,    76,    -1,    78,    -1,    80,    -1,    -1,
      -1,   174,   177,   174,   178,   174,    -1,    -1,    -1,    -1,
     174,   180,   174,   181,   174,   182,   174,    -1,   173,    -1,
     174,    -1,    -1,    -1,    -1,   172,   186,   172,   187,   172,
     188,   189,    81,    -1,   189,   172,    -1,    -1,   172,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   173,   192,
     173,   193,   173,   194,   173,   195,   173,   196,   173,   197,
     173,   198,   173,   199,   173,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   174,   201,   174,   202,   174,   203,
     174,   204,   174,   205,   174,   206,   174,   207,   174,   208,
     174,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   173,   210,   173,
     211,   173,   212,   173,   213,   173,   214,   173,   215,   173,
     216,   173,   217,   173,   218,   173,   219,   173,   220,   173,
     221,   173,   222,   173,   223,   173,   224,   173,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   174,   226,   174,   227,   174,   228,
     174,   229,   174,   230,   174,   231,   174,   232,   174,   233,
     174,   234,   174,   235,   174,   236,   174,   237,   174,   238,
     174,   239,   174,   240,   174,    -1,   103,    -1,    79,    -1,
      -1,    -1,    -1,   174,   243,   174,   244,   174,   245,   174,
      -1,    77,    -1,    80,    -1,   173,    -1,    -1,   173,   249,
     173,    -1,    -1,   174,   251,   174,    -1,    -1,    -1,    -1,
     173,   253,   173,   254,   173,   255,    -1,    -1,    -1,    -1,
     174,   257,   174,   258,   174,   259,    -1,    -1,    -1,    -1,
      -1,   173,   261,   173,   262,   173,   263,   173,   264,    -1,
      -1,    -1,    -1,    -1,   174,   266,   174,   267,   174,   268,
     174,   269,    -1,   175,    -1,    83,   271,    84,    -1,   271,
     175,    -1,    -1,   176,    -1,    83,   273,    84,    -1,   273,
     176,    -1,    -1,   179,    -1,    83,   275,    84,    -1,   275,
     179,    -1,    -1,   183,    -1,    83,   277,    84,    -1,   277,
     183,    -1,    -1,   184,    -1,    83,   279,    84,    -1,   279,
     184,    -1,    -1,   185,    -1,    83,   281,    84,    -1,   281,
     185,    -1,    -1,   190,    -1,    83,   283,    84,    -1,   283,
     190,    -1,    -1,   191,    -1,    83,   285,    84,    -1,   285,
     191,    -1,    -1,   200,    -1,    83,   287,    84,    -1,   287,
     200,    -1,    -1,   209,    -1,    83,   289,    84,    -1,   289,
     209,    -1,    -1,   225,    -1,    83,   291,    84,    -1,   291,
     225,    -1,    -1,   241,    -1,    83,   293,    84,    -1,   293,
     241,    -1,    -1,   242,    -1,    83,   295,    84,    -1,   295,
     242,    -1,    -1,   246,    -1,    83,   297,    84,    -1,   297,
     246,    -1,    -1,   247,    -1,    83,   299,    84,    -1,   299,
     247,    -1,    -1,   248,    -1,    83,   301,    84,    -1,   301,
     248,    -1,    -1,   250,    -1,    83,   303,    84,    -1,   303,
     250,    -1,    -1,   252,    -1,    83,   305,    84,    -1,   305,
     252,    -1,    -1,   256,    -1,    83,   307,    84,    -1,   307,
     256,    -1,    -1,   260,    -1,    83,   309,    84,    -1,   309,
     260,    -1,    -1,   265,    -1,    83,   311,    84,    -1,   311,
     265,    -1,    -1,    -1,    -1,    -1,   172,   313,   172,   314,
     172,   315,   172,    -1,    -1,   174,   317,   174,    -1,    -1,
      -1,   174,   319,   174,   320,   174,    -1,    -1,    -1,    -1,
     174,   322,   174,   323,   174,   324,   174,    -1,    -1,    -1,
      -1,   174,   326,   174,   327,   174,   328,   174,    -1,    -1,
      -1,    -1,    -1,   174,   330,   174,   331,   174,   332,   174,
     333,   334,    -1,    -1,   174,   335,   174,    -1,    -1,   312,
      -1,    83,   337,    84,    -1,   337,   312,    -1,    -1,   316,
      -1,    83,   339,    84,    -1,   339,   316,    -1,    -1,   318,
      -1,    83,   341,    84,    -1,   341,   318,    -1,    -1,   321,
      -1,    83,   343,    84,    -1,   343,   321,    -1,    -1,   325,
      -1,    83,   345,    84,    -1,   345,   325,    -1,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   196,   196,   203,   204,   207,   208,   211,   214,   215,
     219,   224,   225,   232,   233,   238,   236,   243,   246,   249,
     250,   253,   254,   255,   256,   257,   260,   260,   263,   264,
     262,   266,   270,   270,   273,   274,   272,   278,   279,   282,
     283,   286,   287,   286,   291,   294,   295,   299,   298,   302,
     301,   305,   306,   304,   309,   310,   308,   314,   315,   314,
     319,   320,   324,   323,   327,   326,   330,   329,   333,   332,
     338,   340,   342,   337,   349,   351,   348,   362,   361,   372,
     374,   377,   380,   383,   384,   387,   388,   389,   390,   391,
     392,   396,   397,   395,   402,   403,   401,   406,   408,   412,
     413,   411,   418,   419,   417,   423,   424,   428,   427,   436,
     437,   438,   439,   442,   443,   446,   449,   452,   455,   458,
     461,   462,   463,   464,   465,   466,   467,   468,   469,   470,
     471,   472,   473,   474,   475,   476,   477,   478,   479,   480,
     481,   482,   483,   484,   485,   486,   487,   488,   489,   490,
     491,   492,   493,   494,   495,   496,   497,   498,   499,   500,
     501,   502,   504,   505,   506,   507,   508,   509,   510,   511,
     512,   513,   514,   517,   518,   519,   520,   521,   522,   523,
     524,   525,   526,   527,   528,   529,   530,   531,   532,   533,
     534,   535,   536,   537,   538,   539,   540,   541,   542,   543,
     544,   545,   546,   547,   548,   549,   550,   551,   552,   553,
     554,   555,   556,   557,   558,   560,   561,   562,   563,   564,
     565,   566,   567,   568,   569,   570,   573,   574,   577,   578,
     581,   582,   585,   589,   592,   593,   592,   601,   602,   603,
     601,   611,   617,   623,   624,   626,   623,   636,   640,   643,
     649,   650,   651,   652,   653,   654,   655,   656,   649,   667,
     668,   669,   670,   671,   672,   673,   674,   667,   685,   686,
     687,   688,   689,   690,   691,   692,   693,   694,   695,   696,
     697,   698,   699,   685,   711,   712,   713,   714,   715,   716,
     717,   718,   719,   720,   721,   722,   723,   724,   725,   711,
     737,   738,   741,   742,   743,   741,   751,   755,   761,   767,
     767,   775,   775,   783,   784,   785,   783,   792,   793,   794,
     792,   801,   802,   803,   804,   801,   811,   812,   813,   814,
     811,   821,   822,   825,   826,   829,   830,   833,   834,   837,
     838,   841,   842,   845,   846,   849,   850,   853,   854,   857,
     858,   861,   862,   865,   866,   869,   870,   873,   874,   877,
     878,   881,   882,   885,   886,   889,   890,   893,   894,   897,
     898,   901,   902,   905,   906,   909,   910,   913,   914,   917,
     918,   921,   922,   925,   926,   929,   930,   933,   934,   937,
     938,   941,   942,   945,   946,   949,   950,   953,   954,   957,
     958,   961,   962,   965,   966,   969,   970,   973,   974,   977,
     978,   981,   982,   985,   986,   991,   992,   993,   991,  1002,
    1002,  1010,  1011,  1010,  1019,  1020,  1021,  1019,  1029,  1030,
    1031,  1029,  1039,  1040,  1041,  1043,  1039,  1051,  1051,  1061,
    1069,  1070,  1073,  1074,  1077,  1078,  1081,  1082,  1085,  1086,
    1089,  1090,  1093,  1094,  1097,  1098,  1101,  1102,  1105,  1106
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
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
  "protoStatements", "proto", "@8", "@9", "protoBody",
  "interfaceDeclarations", "interfaceDeclaration", "@10", "@11", "@12",
  "@13", "@14", "@15", "externproto", "@16", "@17",
  "externInterfaceDeclarations", "externInterfaceDeclaration", "@18",
  "@19", "@20", "@21", "routeStatement", "@22", "@23", "@24",
  "importStatement", "@25", "@26", "exportStatement", "@27", "asStatement",
  "URLList", "node", "scriptBody", "scriptBodyElement",
  "eventInDeclaration", "@28", "@29", "eventOutDeclaration", "@30", "@31",
  "eventDeclarationEnd", "fieldDeclaration", "@32", "@33",
  "exposedFieldDeclaration", "@34", "@35", "fieldDeclarationEnd",
  "nodeBodyElement", "@36", "fieldEnd", "nodeNameId", "nodeTypeId",
  "fieldId", "eventInId", "eventOutId", "fieldType", "fieldValue", "int32",
  "double", "float", "sfboolValue", "sfcolorValue", "@37", "@38",
  "sfcolorRGBAValue", "@39", "@40", "@41", "sfdoubleValue", "sffloatValue",
  "sfimageValue", "@42", "@43", "@44", "pixels", "sfint32Value",
  "sfmatrix3dValue", "@45", "@46", "@47", "@48", "@49", "@50", "@51",
  "@52", "sfmatrix3fValue", "@53", "@54", "@55", "@56", "@57", "@58",
  "@59", "@60", "sfmatrix4dValue", "@61", "@62", "@63", "@64", "@65",
  "@66", "@67", "@68", "@69", "@70", "@71", "@72", "@73", "@74", "@75",
  "sfmatrix4fValue", "@76", "@77", "@78", "@79", "@80", "@81", "@82",
  "@83", "@84", "@85", "@86", "@87", "@88", "@89", "@90", "sfnodeValue",
  "sfrotationValue", "@91", "@92", "@93", "sfstringValue", "sftimeValue",
  "sfvec2dValue", "@94", "sfvec2fValue", "@95", "sfvec3dValue", "@96",
  "@97", "@98", "sfvec3fValue", "@99", "@100", "@101", "sfvec4dValue",
  "@102", "@103", "@104", "@105", "sfvec4fValue", "@106", "@107", "@108",
  "@109", "mfboolValue", "sfboolValues", "mfcolorValue", "sfcolorValues",
  "mfcolorRGBAValue", "sfcolorRGBAValues", "mfdoubleValue",
  "sfdoubleValues", "mffloatValue", "sffloatValues", "mfimageValue",
  "sfimageValues", "mfint32Value", "sfint32Values", "mfmatrix3dValue",
  "sfmatrix3dValues", "mfmatrix3fValue", "sfmatrix3fValues",
  "mfmatrix4dValue", "sfmatrix4dValues", "mfmatrix4fValue",
  "sfmatrix4fValues", "mfnodeValue", "sfnodeValues", "mfrotationValue",
  "sfrotationValues", "mfstringValue", "sfstringValues", "mftimeValue",
  "sftimeValues", "mfvec2dValue", "sfvec2dValues", "mfvec2fValue",
  "sfvec2fValues", "mfvec3dValue", "sfvec3dValues", "mfvec3fValue",
  "sfvec3fValues", "mfvec4dValue", "sfvec4dValues", "mfvec4fValue",
  "sfvec4fValues", "sfcolor4iValue", "@110", "@111", "@112",
  "sfpnt2fValue", "@113", "sfpnt3fValue", "@114", "@115", "sfpnt4fValue",
  "@116", "@117", "@118", "sfplaneValue", "@119", "@120", "@121",
  "sfVolumeValue", "@122", "@123", "@124", "@125", "sfVolumeValueEnd",
  "@126", "mfcolor4iValue", "sfcolor4iValues", "mfpnt2fValue",
  "sfpnt2fValues", "mfpnt3fValue", "sfpnt3fValues", "mfpnt4fValue",
  "sfpnt4fValues", "mfplaneValue", "sfplaneValues", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
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
static const yytype_uint16 yyr1[] =
{
       0,    88,    89,    90,    90,    91,    91,    92,    93,    93,
      94,    95,    95,    96,    96,    98,    97,    99,   100,   101,
     101,   102,   102,   102,   102,   102,   104,   103,   105,   106,
     103,   103,   108,   107,   109,   110,   107,   111,   111,   112,
     112,   114,   115,   113,   116,   117,   117,   119,   118,   120,
     118,   121,   122,   118,   123,   124,   118,   126,   127,   125,
     128,   128,   130,   129,   131,   129,   132,   129,   133,   129,
     135,   136,   137,   134,   139,   140,   138,   142,   141,   143,
     143,   144,   145,   146,   146,   147,   147,   147,   147,   147,
     147,   149,   150,   148,   152,   153,   151,   154,   154,   156,
     157,   155,   159,   160,   158,   161,   161,   163,   162,   162,
     162,   162,   162,   164,   164,   165,   166,   167,   168,   169,
     170,   170,   170,   170,   170,   170,   170,   170,   170,   170,
     170,   170,   170,   170,   170,   170,   170,   170,   170,   170,
     170,   170,   170,   170,   170,   170,   170,   170,   170,   170,
     170,   170,   170,   170,   170,   170,   170,   170,   170,   170,
     170,   170,   170,   170,   170,   170,   170,   170,   170,   170,
     170,   170,   170,   171,   171,   171,   171,   171,   171,   171,
     171,   171,   171,   171,   171,   171,   171,   171,   171,   171,
     171,   171,   171,   171,   171,   171,   171,   171,   171,   171,
     171,   171,   171,   171,   171,   171,   171,   171,   171,   171,
     171,   171,   171,   171,   171,   171,   171,   171,   171,   171,
     171,   171,   171,   171,   171,   171,   172,   172,   173,   173,
     174,   174,   175,   175,   177,   178,   176,   180,   181,   182,
     179,   183,   184,   186,   187,   188,   185,   189,   189,   190,
     192,   193,   194,   195,   196,   197,   198,   199,   191,   201,
     202,   203,   204,   205,   206,   207,   208,   200,   210,   211,
     212,   213,   214,   215,   216,   217,   218,   219,   220,   221,
     222,   223,   224,   209,   226,   227,   228,   229,   230,   231,
     232,   233,   234,   235,   236,   237,   238,   239,   240,   225,
     241,   241,   243,   244,   245,   242,   246,   246,   247,   249,
     248,   251,   250,   253,   254,   255,   252,   257,   258,   259,
     256,   261,   262,   263,   264,   260,   266,   267,   268,   269,
     265,   270,   270,   271,   271,   272,   272,   273,   273,   274,
     274,   275,   275,   276,   276,   277,   277,   278,   278,   279,
     279,   280,   280,   281,   281,   282,   282,   283,   283,   284,
     284,   285,   285,   286,   286,   287,   287,   288,   288,   289,
     289,   290,   290,   291,   291,   292,   292,   293,   293,   294,
     294,   295,   295,   296,   296,   297,   297,   298,   298,   299,
     299,   300,   300,   301,   301,   302,   302,   303,   303,   304,
     304,   305,   305,   306,   306,   307,   307,   308,   308,   309,
     309,   310,   310,   311,   311,   313,   314,   315,   312,   317,
     316,   319,   320,   318,   322,   323,   324,   321,   326,   327,
     328,   325,   330,   331,   332,   333,   329,   335,   334,   334,
     336,   336,   337,   337,   338,   338,   339,   339,   340,   340,
     341,   341,   342,   342,   343,   343,   344,   344,   345,   345
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     5,     1,     0,     2,     0,     1,     2,     0,
       2,     1,     1,     2,     0,     0,     4,     1,     1,     2,
       0,     1,     1,     1,     1,     1,     0,     3,     0,     0,
       6,     2,     0,     3,     0,     0,     6,     1,     1,     2,
       0,     0,     0,    10,     3,     2,     0,     0,     4,     0,
       4,     0,     0,     6,     0,     0,     6,     0,     0,     8,
       2,     0,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     0,     0,    11,     0,     0,     7,     0,     4,     2,
       0,     1,     3,     2,     0,     1,     1,     1,     1,     1,
       1,     0,     0,     6,     0,     0,     6,     0,     2,     0,
       0,     6,     0,     0,     6,     1,     3,     0,     3,     1,
       1,     1,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     0,     5,     0,     0,     0,
       7,     1,     1,     0,     0,     0,     8,     2,     0,     1,
       0,     0,     0,     0,     0,     0,     0,     0,    17,     0,
       0,     0,     0,     0,     0,     0,     0,    17,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    31,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    31,
       1,     1,     0,     0,     0,     7,     1,     1,     1,     0,
       3,     0,     3,     0,     0,     0,     6,     0,     0,     0,
       6,     0,     0,     0,     0,     8,     0,     0,     0,     0,
       8,     1,     3,     2,     0,     1,     3,     2,     0,     1,
       3,     2,     0,     1,     3,     2,     0,     1,     3,     2,
       0,     1,     3,     2,     0,     1,     3,     2,     0,     1,
       3,     2,     0,     1,     3,     2,     0,     1,     3,     2,
       0,     1,     3,     2,     0,     1,     3,     2,     0,     1,
       3,     2,     0,     1,     3,     2,     0,     1,     3,     2,
       0,     1,     3,     2,     0,     1,     3,     2,     0,     1,
       3,     2,     0,     1,     3,     2,     0,     1,     3,     2,
       0,     1,     3,     2,     0,     0,     0,     0,     7,     0,
       3,     0,     0,     5,     0,     0,     0,     7,     0,     0,
       0,     7,     0,     0,     0,     0,     9,     0,     3,     0,
       1,     3,     2,     0,     1,     3,     2,     0,     1,     3,
       2,     0,     1,     3,     2,     0,     1,     3,     2,     0
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       4,     3,     0,     6,     1,     0,     9,     7,     5,    14,
       0,     8,    20,    12,    11,    10,     0,    13,     2,    17,
      15,     0,     0,     0,     0,     0,     0,     0,   116,    19,
      21,    22,    37,    38,    23,    24,    25,    26,     0,    41,
      57,   115,    28,    31,    70,    74,    77,     0,    18,    16,
       0,     0,     0,     0,     0,    80,    84,    27,    46,    61,
      29,     0,     0,     0,    78,     0,     0,     0,     0,   119,
      71,    75,    79,    90,     0,     0,     0,     0,   117,    82,
     110,   109,   111,   112,    83,    86,    87,    88,    89,    85,
     107,     0,     0,     0,     0,    42,    45,     0,     0,     0,
       0,    58,    60,    30,     0,    80,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,    91,
      94,   102,    99,     0,    47,    49,    54,    51,     0,    62,
      64,    68,    66,     0,     0,    76,     0,     0,     0,     0,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   164,   165,   166,   167,   168,   169,
     170,   171,   172,   108,     0,   113,     0,     0,     0,     0,
      40,     0,     0,     0,     0,   306,   307,   386,    59,   383,
      81,    72,   118,    92,    95,   103,   100,   232,   233,   334,
     331,   173,   230,   231,   338,   234,   335,   174,   342,   237,
     339,   175,   228,   229,   346,   241,   343,   176,   350,   242,
     347,   177,   226,   227,   354,   243,   351,   178,   358,   249,
     355,   179,   362,   250,   359,   180,   366,   259,   363,   181,
     370,   268,   367,   182,   374,   284,   371,   183,   301,   378,
     300,   375,   184,   382,   302,   379,   185,   186,   390,   308,
     387,   187,   394,   309,   391,   188,   398,   311,   395,   189,
     402,   313,   399,   190,   406,   317,   403,   191,   410,   321,
     407,   192,   414,   326,   411,   193,   194,   195,   196,   197,
     198,   199,   200,   201,   202,   203,   204,   205,   206,   207,
     208,   209,   210,   211,   212,   213,   214,   443,   415,   440,
     215,   447,   419,   444,   216,   451,   421,   448,   217,   455,
     424,   452,   218,   459,   428,   456,   219,   220,   221,   222,
     223,   224,   432,   225,     0,    48,    50,    55,    52,     0,
       0,    63,    65,    69,    67,     0,     0,    97,    97,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   114,     0,     0,     0,
      20,    39,    32,    43,   384,   385,     0,     0,    93,    96,
     104,     0,   105,   101,   332,   333,   336,   337,   235,   340,
     341,   238,   344,   345,   348,   349,   352,   353,   244,   356,
     357,   360,   361,   251,   364,   365,   260,   368,   369,   269,
     372,   373,   285,   376,   377,   380,   381,   303,   388,   389,
     392,   393,   310,   396,   397,   312,   400,   401,   314,   404,
     405,   318,   408,   409,   322,   412,   413,   327,   441,   442,
     416,   445,   446,   420,   449,   450,   422,   453,   454,   425,
     457,   458,   429,   433,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    56,    53,    34,
      44,     0,    73,    98,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    33,   106,   236,   239,   245,   252,   261,
     270,   286,   304,   315,   319,   323,   328,   417,   423,   426,
     430,   434,    35,     0,   248,     0,     0,     0,     0,     0,
     316,   320,     0,     0,     0,     0,     0,     0,     0,   240,
       0,   253,   262,   271,   287,   305,   324,   329,   418,   427,
     431,   435,    36,   246,   247,     0,     0,     0,     0,   325,
     330,   439,   254,   263,   272,   288,   437,   436,     0,     0,
       0,     0,     0,   255,   264,   273,   289,   438,     0,     0,
       0,     0,   256,   265,   274,   290,     0,     0,     0,     0,
     257,   266,   275,   291,     0,     0,     0,     0,   258,   267,
     276,   292,     0,     0,   277,   293,     0,     0,   278,   294,
       0,     0,   279,   295,     0,     0,   280,   296,     0,     0,
     281,   297,     0,     0,   282,   298,     0,     0,   283,   299
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     6,     8,     9,    11,    15,    12,    17,
      38,    20,    49,    18,    29,   310,    47,    52,    68,   460,
     601,   622,   658,    31,   399,    32,    50,   168,   400,    66,
      96,   236,   237,   239,   458,   238,   457,    33,    51,   173,
      67,   102,   241,   242,   244,   243,    34,    53,   104,   406,
      35,    54,   105,    36,    55,    64,   248,    57,    65,    84,
      85,   176,   407,    86,   177,   408,   468,    87,   179,   410,
      88,   178,   409,   470,    89,   163,   233,    42,    37,    90,
     253,    70,   471,   472,   285,   275,   265,   260,   266,   413,
     605,   270,   415,   606,   643,   276,   280,   286,   419,   607,
     644,   660,   290,   294,   422,   608,   645,   675,   688,   698,
     706,   714,   298,   424,   609,   646,   676,   689,   699,   707,
     715,   302,   426,   610,   647,   677,   690,   700,   708,   716,
     722,   726,   730,   734,   738,   742,   746,   306,   428,   611,
     648,   678,   691,   701,   709,   717,   723,   727,   731,   735,
     739,   743,   747,   311,   315,   431,   612,   649,   249,   320,
     324,   434,   328,   436,   332,   438,   613,   650,   336,   440,
     614,   651,   340,   442,   615,   652,   679,   344,   444,   616,
     653,   680,   261,   411,   267,   412,   271,   414,   277,   416,
     281,   417,   287,   418,   291,   420,   295,   421,   299,   423,
     303,   425,   307,   427,   312,   429,   316,   430,   317,   405,
     321,   432,   325,   433,   329,   435,   333,   437,   337,   439,
     341,   441,   345,   443,   369,   446,   617,   654,   373,   448,
     377,   450,   618,   381,   452,   619,   655,   385,   454,   620,
     656,   393,   455,   621,   657,   681,   687,   692,   370,   445,
     374,   447,   378,   449,   382,   451,   386,   453
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -258
static const yytype_int16 yypact[] =
{
      36,  -258,    45,    66,  -258,    -3,  -258,  -258,  -258,    60,
     138,  -258,    82,  -258,  -258,  -258,    35,  -258,   124,  -258,
    -258,    47,    47,    57,    57,    57,    57,    57,  -258,  -258,
    -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,    53,  -258,
    -258,  -258,  -258,  -258,  -258,  -258,  -258,    58,  -258,  -258,
      80,    86,    47,    62,    64,   140,  -258,  -258,  -258,  -258,
    -258,   102,    57,    57,  -258,    99,   141,   147,    58,  -258,
    -258,  -258,  -258,  -258,   581,   581,   581,   581,  -258,  -258,
    -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,
    -258,   581,   581,   581,   581,  -258,  -258,   581,   581,   581,
     581,  -258,  -258,  -258,   163,   140,  -258,  -258,  -258,  -258,
    -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,
    -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,
    -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,
    -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,
    -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,
    -258,  -258,  -258,   849,  -258,  -258,  -258,  -258,   110,  -258,
    -258,  -258,  -258,   130,    57,  -258,   104,   102,   117,   117,
     283,    50,   151,   238,   254,    98,   100,   270,   284,   374,
     376,    61,   385,   130,   387,   398,   407,   411,   417,   420,
     422,    42,    33,    33,   189,    33,   194,   194,   189,    33,
     189,    33,    73,    33,   152,   189,   189,    33,   189,    33,
     189,    33,   103,   433,   435,   444,   453,   194,    33,    33,
      33,    33,    33,  -258,   190,  -258,   104,   102,   117,   117,
    -258,   104,   102,   117,   117,  -258,  -258,  -258,  -258,  -258,
    -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,
    -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,
    -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,
    -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,
    -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,
    -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,
    -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,
    -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,
    -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,
    -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,
    -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,
    -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,
    -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,
    -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,
    -258,  -258,  -258,  -258,   117,  -258,  -258,  -258,  -258,    68,
     115,  -258,  -258,  -258,  -258,    70,   157,   196,   196,   849,
     849,     9,   112,    33,   114,    33,   116,   118,    17,   194,
      71,   133,   189,   136,    33,   173,   189,   207,    33,     6,
     217,    33,   221,   224,   189,   227,    33,   231,   189,   248,
      33,   250,   189,   260,    33,    96,   194,   274,    33,   281,
      33,   370,    33,   372,    33,    33,  -258,   902,   902,    57,
    -258,  -258,  -258,  -258,  -258,  -258,   104,   117,  -258,  -258,
    -258,   219,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,
    -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,
    -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,
    -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,
    -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,
    -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,
    -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,
    -258,  -258,  -258,  -258,   283,    50,   151,   238,   254,    98,
     100,   270,   284,   374,   376,    61,   385,   130,   387,   398,
     407,   411,   417,   420,   422,    42,    33,    33,   189,    33,
     194,   194,   189,    33,   189,    33,    73,    33,   152,   189,
     189,    33,   189,    33,   189,    33,   103,   433,   435,   444,
     453,   194,    33,    33,    33,    33,    33,  -258,  -258,  -258,
     124,    58,  -258,  -258,   117,    33,    33,   194,   189,    33,
     189,    33,    33,   189,    33,   189,    33,   194,    33,    33,
      33,    33,    47,  -258,  -258,  -258,  -258,  -258,  -258,  -258,
    -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,
    -258,  -258,  -258,    33,  -258,   189,    33,   189,    33,    33,
    -258,  -258,   189,    33,   194,    33,    33,    33,    58,  -258,
     346,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,
    -258,  -258,  -258,  -258,  -258,   189,    33,   189,    33,  -258,
    -258,    33,  -258,  -258,  -258,  -258,  -258,  -258,   189,    33,
     189,    33,    33,  -258,  -258,  -258,  -258,  -258,   189,    33,
     189,    33,  -258,  -258,  -258,  -258,   189,    33,   189,    33,
    -258,  -258,  -258,  -258,   189,    33,   189,    33,  -258,  -258,
    -258,  -258,   189,    33,  -258,  -258,   189,    33,  -258,  -258,
     189,    33,  -258,  -258,   189,    33,  -258,  -258,   189,    33,
    -258,  -258,   189,    33,  -258,  -258,   189,    33,  -258,  -258
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,
    -258,  -258,  -258,  -257,  -258,   -15,  -258,  -258,  -258,  -258,
    -258,  -258,  -258,   -51,  -258,  -258,  -258,  -258,  -258,  -258,
    -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,
    -258,  -258,  -258,  -258,  -258,  -258,   174,  -258,  -258,  -258,
     220,  -258,  -258,   223,  -258,   185,  -258,   -66,  -258,  -258,
    -258,  -258,  -258,  -258,  -258,  -258,  -114,  -258,  -258,  -258,
    -258,  -258,  -258,  -106,  -258,  -258,  -258,    32,   -21,  -115,
    -168,  -127,     5,  -130,   -65,   123,  -177,  -197,  -196,  -258,
    -258,  -195,  -258,  -258,  -258,  -194,  -193,  -188,  -258,  -258,
    -258,  -258,  -187,  -186,  -258,  -258,  -258,  -258,  -258,  -258,
    -258,  -258,  -200,  -258,  -258,  -258,  -258,  -258,  -258,  -258,
    -258,  -183,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,
    -258,  -258,  -258,  -258,  -258,  -258,  -258,  -182,  -258,  -258,
    -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,
    -258,  -258,  -258,  -174,  -189,  -258,  -258,  -258,  -184,  -180,
    -173,  -258,  -192,  -258,  -181,  -258,  -258,  -258,  -178,  -258,
    -258,  -258,  -160,  -258,  -258,  -258,  -258,  -159,  -258,  -258,
    -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,
    -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,
    -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,   143,  -258,
    -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,
    -258,  -258,  -258,  -258,  -158,  -258,  -258,  -258,  -167,  -258,
    -163,  -258,  -258,  -156,  -258,  -258,  -258,  -164,  -258,  -258,
    -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,
    -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint16 yytable[] =
{
      39,    40,   103,    30,   346,   269,   347,   279,   348,   354,
     349,   297,   350,   305,    80,   314,    23,    24,   351,   327,
     352,   335,   353,   343,   358,   362,   269,   355,   279,   356,
     359,    60,   297,   235,   305,   360,   314,   363,   357,     1,
     327,   364,   335,   361,   343,     4,   372,   376,   380,   384,
     254,   372,   376,   380,   384,   392,    43,    44,    45,    46,
     365,   388,   366,   255,   256,    10,   389,   391,   395,   387,
       5,    23,    24,   401,   390,    21,    22,     7,   459,   159,
     160,   161,   162,    23,    24,   308,    28,   257,    16,   258,
     503,   282,   283,   474,    71,    72,   164,   165,   166,   167,
      73,   486,   169,   170,   171,   172,    21,    22,   262,   263,
     396,    25,    19,    26,    27,   402,    74,    75,    76,    77,
     257,   289,   258,   397,   398,   262,   263,    28,   403,   404,
      48,    21,    22,   264,    23,    24,    25,    41,    26,    27,
     308,    28,   289,    56,   309,   282,   283,   245,    28,    61,
     246,    62,   308,    28,   464,   489,    63,   368,    91,    92,
      93,    94,   368,    58,    97,    98,    99,   100,   234,    59,
     282,   283,   282,   283,   282,   283,   174,   282,   283,    78,
     528,   284,    69,   288,   252,    79,   367,   262,   263,   262,
     263,   272,   273,   262,   263,   240,   476,    78,   479,   394,
     482,   463,   484,   600,    28,   467,   251,   245,   272,   273,
     246,   262,   263,   247,   475,    13,   477,   491,    14,   480,
     494,   465,   483,   495,   485,    95,   262,   263,   604,   245,
     487,   101,   246,   490,   268,   492,   478,   269,   481,    81,
     279,   506,   498,   514,   466,   501,   297,   496,   272,   273,
     305,   502,   509,   314,   507,   504,   517,   497,   327,   515,
     511,   520,   335,   521,   272,   273,   343,   527,   282,   283,
     372,   533,   376,   536,   380,   539,   384,   542,   543,   456,
     532,   523,   262,   263,   526,    82,   535,   529,    83,   541,
     175,   500,   262,   263,   469,   538,   272,   273,   602,   272,
     273,   505,   262,   263,   473,   508,   272,   273,   510,     0,
     293,   513,   301,   272,   273,   516,   250,   319,   323,     0,
     331,   274,   339,   262,   263,   272,   273,   597,   598,   262,
     263,   293,   519,   301,   522,   262,   263,   278,   319,   323,
       0,   331,     0,   339,   525,   272,   273,     0,   461,   262,
     263,     0,   603,   292,   488,   289,   262,   263,   531,   262,
     263,   257,     0,   258,     0,   534,   259,   296,   346,   269,
     347,   279,   348,   354,   349,   297,   350,   305,   462,   314,
     368,   530,   351,   327,   352,   335,   353,   343,   358,   362,
     269,   355,   279,   356,   359,     0,   297,     0,   305,   360,
     314,   363,   357,     0,   327,   364,   335,   361,   343,     0,
     372,   376,   380,   384,     0,   372,   376,   380,   384,   392,
     282,   283,     0,     0,   365,   388,   366,   673,   625,   626,
     389,   391,   629,   387,   631,   632,     0,   634,   390,   636,
       0,   638,   639,   640,   641,   262,   263,   262,   263,   272,
     273,   262,   263,     0,   537,     0,   540,   300,     0,   304,
     262,   263,   272,   273,     0,     0,   659,     0,   313,   662,
     318,   664,   665,   272,   273,     0,   667,     0,   669,   670,
     671,   322,   262,   263,     0,   289,   272,   273,     0,   624,
     326,   599,   262,   263,   330,   272,   273,   262,   263,   683,
     334,   685,     0,   338,   686,   342,   289,     0,   262,   263,
     262,   263,   694,     0,   696,   697,   371,     0,   375,   262,
     263,   368,   703,     0,   705,     0,   368,   379,   262,   263,
     711,     0,   713,     0,     0,   623,   383,     0,   719,     0,
     721,     0,   627,     0,   293,   493,   725,     0,   301,   499,
     729,     0,   637,     0,   733,   319,   323,   512,   737,     0,
     331,   518,   741,     0,   339,   524,   745,     0,     0,     0,
     749,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    30,     0,     0,     0,   668,
       0,     0,   672,     0,     0,   674,     0,     0,     0,     0,
       0,   642,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   293,     0,   301,     0,     0,     0,
       0,   319,   323,     0,   331,     0,   339,     0,     0,     0,
       0,     0,     0,     0,     0,   293,     0,   301,     0,     0,
       0,     0,   319,   323,     0,   331,     0,   339,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   628,     0,   630,     0,     0,   633,     0,   635,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   661,     0,
     663,     0,     0,     0,     0,   666,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   682,     0,
     684,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   693,     0,   695,     0,     0,     0,     0,     0,     0,
       0,   702,     0,   704,     0,     0,     0,     0,     0,   710,
       0,   712,     0,     0,     0,     0,     0,   718,     0,   720,
       0,     0,     0,     0,     0,   724,     0,     0,     0,   728,
       0,     0,     0,   732,     0,     0,     0,   736,     0,     0,
       0,   740,     0,     0,     0,   744,     0,     0,     0,   748,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   204,   205,   206,   207,   208,   209,
     210,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   226,   227,   228,   229,
     230,   231,   232,   544,   545,   546,   547,   548,   549,   550,
     551,   552,   553,   554,   555,   556,   557,   558,   559,   560,
     561,   562,   563,   564,   565,   566,   567,   568,   569,   570,
     571,   572,   573,   574,   575,   576,   577,   578,   579,   580,
     581,   582,   583,   584,   585,   586,   587,   588,   589,   590,
     591,   592,   593,   594,   595,   596
};

static const yytype_int16 yycheck[] =
{
      21,    22,    68,    18,   201,   182,   202,   184,   203,   209,
     204,   188,   205,   190,    65,   192,    10,    11,   206,   196,
     207,   198,   208,   200,   213,   217,   203,   210,   205,   211,
     214,    52,   209,   163,   211,   215,   213,   218,   212,     3,
     217,   219,   219,   216,   221,     0,   223,   224,   225,   226,
     177,   228,   229,   230,   231,   232,    24,    25,    26,    27,
     220,   228,   221,   178,   179,     5,   229,   231,   236,   227,
       4,    10,    11,   241,   230,     7,     8,    80,    10,    74,
      75,    76,    77,    10,    11,    79,    80,    78,     6,    80,
      84,    74,    75,    84,    62,    63,    91,    92,    93,    94,
       1,    84,    97,    98,    99,   100,     7,     8,    75,    76,
     237,    12,    77,    14,    15,   242,    17,    18,    19,    20,
      78,   186,    80,   238,   239,    75,    76,    80,   243,   244,
      77,     7,     8,    83,    10,    11,    12,    80,    14,    15,
      79,    80,   207,    85,    83,    74,    75,    77,    80,    87,
      80,    87,    79,    80,    84,    84,    16,   222,    17,    18,
      19,    20,   227,    83,    17,    18,    19,    20,   163,    83,
      74,    75,    74,    75,    74,    75,    13,    74,    75,    80,
      84,    83,    80,    83,    80,    86,    83,    75,    76,    75,
      76,    75,    76,    75,    76,    85,    84,    80,    84,     9,
      84,    86,    84,   460,    80,     9,   174,    77,    75,    76,
      80,    75,    76,    83,   411,    77,   412,    84,    80,   414,
      84,   405,   416,   423,   417,    84,    75,    76,     9,    77,
     418,    84,    80,   420,    83,   421,   413,   414,   415,    65,
     417,   430,   425,   435,    87,   427,   423,   424,    75,    76,
     427,   428,   432,   430,   431,   429,   437,    84,   435,   436,
     433,   439,   439,   440,    75,    76,   443,   444,    74,    75,
     447,   448,   449,   450,   451,   452,   453,   454,   455,   394,
     447,   441,    75,    76,   443,    65,   449,   445,    65,   453,
     105,    84,    75,    76,   408,   451,    75,    76,   466,    75,
      76,    84,    75,    76,   410,    84,    75,    76,    84,    -1,
     187,    84,   189,    75,    76,    84,   173,   194,   195,    -1,
     197,    83,   199,    75,    76,    75,    76,   457,   458,    75,
      76,   208,    84,   210,    84,    75,    76,    83,   215,   216,
      -1,   218,    -1,   220,    84,    75,    76,    -1,   399,    75,
      76,    -1,   467,    83,   419,   420,    75,    76,    84,    75,
      76,    78,    -1,    80,    -1,    84,    83,    83,   565,   546,
     566,   548,   567,   573,   568,   552,   569,   554,   399,   556,
     445,   446,   570,   560,   571,   562,   572,   564,   577,   581,
     567,   574,   569,   575,   578,    -1,   573,    -1,   575,   579,
     577,   582,   576,    -1,   581,   583,   583,   580,   585,    -1,
     587,   588,   589,   590,    -1,   592,   593,   594,   595,   596,
      74,    75,    -1,    -1,   584,   592,   585,    81,   605,   606,
     593,   595,   609,   591,   611,   612,    -1,   614,   594,   616,
      -1,   618,   619,   620,   621,    75,    76,    75,    76,    75,
      76,    75,    76,    -1,    84,    -1,    84,    83,    -1,    83,
      75,    76,    75,    76,    -1,    -1,   643,    -1,    83,   646,
      83,   648,   649,    75,    76,    -1,   653,    -1,   655,   656,
     657,    83,    75,    76,    -1,   550,    75,    76,    -1,   604,
      83,   459,    75,    76,    83,    75,    76,    75,    76,   676,
      83,   678,    -1,    83,   681,    83,   571,    -1,    75,    76,
      75,    76,   689,    -1,   691,   692,    83,    -1,    83,    75,
      76,   586,   699,    -1,   701,    -1,   591,    83,    75,    76,
     707,    -1,   709,    -1,    -1,   601,    83,    -1,   715,    -1,
     717,    -1,   607,    -1,   421,   422,   723,    -1,   425,   426,
     727,    -1,   617,    -1,   731,   432,   433,   434,   735,    -1,
     437,   438,   739,    -1,   441,   442,   743,    -1,    -1,    -1,
     747,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   600,    -1,    -1,    -1,   654,
      -1,    -1,   658,    -1,    -1,   660,    -1,    -1,    -1,    -1,
      -1,   622,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   551,    -1,   553,    -1,    -1,    -1,
      -1,   558,   559,    -1,   561,    -1,   563,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   572,    -1,   574,    -1,    -1,
      -1,    -1,   579,   580,    -1,   582,    -1,   584,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   608,    -1,   610,    -1,    -1,   613,    -1,   615,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   645,    -1,
     647,    -1,    -1,    -1,    -1,   652,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   675,    -1,
     677,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   688,    -1,   690,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   698,    -1,   700,    -1,    -1,    -1,    -1,    -1,   706,
      -1,   708,    -1,    -1,    -1,    -1,    -1,   714,    -1,   716,
      -1,    -1,    -1,    -1,    -1,   722,    -1,    -1,    -1,   726,
      -1,    -1,    -1,   730,    -1,    -1,    -1,   734,    -1,    -1,
      -1,   738,    -1,    -1,    -1,   742,    -1,    -1,    -1,   746,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,     3,    89,    90,     0,     4,    91,    80,    92,    93,
       5,    94,    96,    77,    80,    95,     6,    97,   101,    77,
      99,     7,     8,    10,    11,    12,    14,    15,    80,   102,
     103,   111,   113,   125,   134,   138,   141,   166,    98,   166,
     166,    80,   165,   165,   165,   165,   165,   104,    77,   100,
     114,   126,   105,   135,   139,   142,    85,   145,    83,    83,
     166,    87,    87,    16,   143,   146,   117,   128,   106,    80,
     169,   165,   165,     1,    17,    18,    19,    20,    80,    86,
     111,   134,   138,   141,   147,   148,   151,   155,   158,   162,
     167,    17,    18,    19,    20,    84,   118,    17,    18,    19,
      20,    84,   129,   145,   136,   140,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,   170,
     170,   170,   170,   163,   170,   170,   170,   170,   115,   170,
     170,   170,   170,   127,    13,   143,   149,   152,   159,   156,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,   164,   170,   171,   119,   120,   123,   121,
      85,   130,   131,   133,   132,    77,    80,    83,   144,   246,
     296,   165,    80,   168,   169,   167,   167,    78,    80,    83,
     175,   270,    75,    76,    83,   174,   176,   272,    83,   174,
     179,   274,    75,    76,    83,   173,   183,   276,    83,   174,
     184,   278,    74,    75,    83,   172,   185,   280,    83,   172,
     190,   282,    83,   173,   191,   284,    83,   174,   200,   286,
      83,   173,   209,   288,    83,   174,   225,   290,    79,    83,
     103,   241,   292,    83,   174,   242,   294,   296,    83,   173,
     247,   298,    83,   173,   248,   300,    83,   174,   250,   302,
      83,   173,   252,   304,    83,   174,   256,   306,    83,   173,
     260,   308,    83,   174,   265,   310,   175,   176,   179,   183,
     184,   185,   190,   191,   200,   209,   225,   241,   242,   246,
     247,   248,   250,   252,   256,   260,   265,    83,   172,   312,
     336,    83,   174,   316,   338,    83,   174,   318,   340,    83,
     174,   321,   342,    83,   174,   325,   344,   312,   316,   318,
     321,   325,   174,   329,     9,   168,   169,   167,   167,   112,
     116,   168,   169,   167,   167,   297,   137,   150,   153,   160,
     157,   271,   273,   177,   275,   180,   277,   279,   281,   186,
     283,   285,   192,   287,   201,   289,   210,   291,   226,   293,
     295,   243,   299,   301,   249,   303,   251,   305,   253,   307,
     257,   309,   261,   311,   266,   337,   313,   339,   317,   341,
     319,   343,   322,   345,   326,   330,   167,   124,   122,    10,
     107,   111,   166,    86,    84,   246,    87,     9,   154,   154,
     161,   170,   171,   161,    84,   175,    84,   176,   174,    84,
     179,   174,    84,   183,    84,   184,    84,   185,   172,    84,
     190,    84,   191,   173,    84,   200,   174,    84,   209,   173,
      84,   225,   174,    84,   241,    84,   242,   174,    84,   247,
      84,   248,   173,    84,   250,   174,    84,   252,   173,    84,
     256,   174,    84,   260,   173,    84,   265,   174,    84,   312,
     172,    84,   316,   174,    84,   318,   174,    84,   321,   174,
      84,   325,   174,   174,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,   171,   171,   165,
     101,   108,   168,   167,     9,   178,   181,   187,   193,   202,
     211,   227,   244,   254,   258,   262,   267,   314,   320,   323,
     327,   331,   109,   145,   167,   174,   174,   172,   173,   174,
     173,   174,   174,   173,   174,   173,   174,   172,   174,   174,
     174,   174,   166,   182,   188,   194,   203,   212,   228,   245,
     255,   259,   263,   268,   315,   324,   328,   332,   110,   174,
     189,   173,   174,   173,   174,   174,   173,   174,   172,   174,
     174,   174,   145,    81,   172,   195,   204,   213,   229,   264,
     269,   333,   173,   174,   173,   174,   174,   334,   196,   205,
     214,   230,   335,   173,   174,   173,   174,   174,   197,   206,
     215,   231,   173,   174,   173,   174,   198,   207,   216,   232,
     173,   174,   173,   174,   199,   208,   217,   233,   173,   174,
     173,   174,   218,   234,   173,   174,   219,   235,   173,   174,
     220,   236,   173,   174,   221,   237,   173,   174,   222,   238,
     173,   174,   223,   239,   173,   174,   224,   240,   173,   174
};

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
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
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
    while (YYID (0))
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
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
  YYUSE (yyvaluep);

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
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */






/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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

  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

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
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
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

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

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

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
    { SKEL->verifyHeader((yyvsp[(1) - (1)].stringVal)); ;}
    break;

  case 5:
#line 207 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->profileElement((yyvsp[(2) - (2)].stringVal)); ;}
    break;

  case 10:
#line 221 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->componentElement((yyvsp[(2) - (2)].stringVal)); ;}
    break;

  case 15:
#line 238 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = (yyvsp[(2) - (2)].stringVal); ;}
    break;

  case 16:
#line 240 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->metaElement(SKEL->_tmpString1.c_str(), (yyvsp[(4) - (4)].stringVal)); ;}
    break;

  case 26:
#line 260 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginNode((yyvsp[(1) - (1)].stringVal), 0); ;}
    break;

  case 28:
#line 263 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = (yyvsp[(2) - (2)].stringVal); ;}
    break;

  case 29:
#line 264 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginNode((yyvsp[(4) - (4)].stringVal), SKEL->_tmpString1.c_str()); ;}
    break;

  case 31:
#line 267 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->use((yyvsp[(2) - (2)].stringVal)); ;}
    break;

  case 32:
#line 270 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginNode((yyvsp[(1) - (1)].stringVal), 0); ;}
    break;

  case 34:
#line 273 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = (yyvsp[(2) - (2)].stringVal); ;}
    break;

  case 35:
#line 274 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginNode((yyvsp[(4) - (4)].stringVal), SKEL->_tmpString1.c_str()); ;}
    break;

  case 41:
#line 286 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginProto((yyvsp[(2) - (2)].stringVal)); ;}
    break;

  case 42:
#line 287 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endProtoInterface(); ;}
    break;

  case 43:
#line 288 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endProto(); ;}
    break;

  case 47:
#line 299 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 48:
#line 300 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginEventInDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); SKEL->endEventDecl(); ;}
    break;

  case 49:
#line 302 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 50:
#line 303 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginEventOutDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); SKEL->endEventDecl(); ;}
    break;

  case 51:
#line 305 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 52:
#line 306 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginFieldDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); SKEL->getLexer()->expectType((yyvsp[(2) - (4)].intVal)); ;}
    break;

  case 53:
#line 307 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endFieldDecl(); ;}
    break;

  case 54:
#line 309 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 55:
#line 310 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginExposedFieldDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); SKEL->getLexer()->expectType((yyvsp[(2) - (4)].intVal)); ;}
    break;

  case 56:
#line 311 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endExposedFieldDecl(); ;}
    break;

  case 57:
#line 314 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginExternProto((yyvsp[(2) - (2)].stringVal)); ;}
    break;

  case 58:
#line 315 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endExternProtoInterface(); ;}
    break;

  case 59:
#line 316 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endExternProto(); ;}
    break;

  case 62:
#line 324 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 63:
#line 325 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->addExternEventInDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); ;}
    break;

  case 64:
#line 327 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 65:
#line 328 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->addExternEventOutDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); ;}
    break;

  case 66:
#line 330 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 67:
#line 331 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->addExternFieldDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); ;}
    break;

  case 68:
#line 333 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 69:
#line 334 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->addExternExposedFieldDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); ;}
    break;

  case 70:
#line 338 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = (yyvsp[(2) - (2)].stringVal); ;}
    break;

  case 71:
#line 340 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString2 = (yyvsp[(5) - (5)].stringVal); ;}
    break;

  case 72:
#line 342 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString3 = (yyvsp[(8) - (8)].stringVal); ;}
    break;

  case 73:
#line 345 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->addRoute(SKEL->_tmpString1.c_str(), SKEL->_tmpString2.c_str(), SKEL->_tmpString3.c_str(), (yyvsp[(11) - (11)].stringVal)); ;}
    break;

  case 74:
#line 349 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = (yyvsp[(2) - (2)].stringVal); ;}
    break;

  case 75:
#line 351 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString2 = (yyvsp[(5) - (5)].stringVal); ;}
    break;

  case 76:
#line 353 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { 
        if ((yyvsp[(7) - (7)].stringVal) != 0)
            SKEL->importElement(SKEL->_tmpString1.c_str(), SKEL->_tmpString2.c_str(), (yyvsp[(7) - (7)].stringVal));
        else
            SKEL->importElement(SKEL->_tmpString1.c_str(), SKEL->_tmpString2.c_str(), 0);
    ;}
    break;

  case 77:
#line 362 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = (yyvsp[(2) - (2)].stringVal); ;}
    break;

  case 78:
#line 364 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { 
        if ((yyvsp[(4) - (4)].stringVal) != 0)
            SKEL->exportElement(SKEL->_tmpString1.c_str(), (yyvsp[(4) - (4)].stringVal));
        else
            SKEL->exportElement(SKEL->_tmpString1.c_str(), 0);
    ;}
    break;

  case 79:
#line 373 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { (yyval.stringVal) = (yyvsp[(2) - (2)].stringVal); ;}
    break;

  case 80:
#line 374 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { (yyval.stringVal) = 0; ;}
    break;

  case 82:
#line 380 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endNode(); ;}
    break;

  case 91:
#line 396 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 92:
#line 397 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginEventInDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); ;}
    break;

  case 93:
#line 398 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endEventDecl(); ;}
    break;

  case 94:
#line 402 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 95:
#line 403 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginEventOutDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); ;}
    break;

  case 96:
#line 404 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endEventDecl(); ;}
    break;

  case 98:
#line 408 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->is((yyvsp[(2) - (2)].stringVal)); ;}
    break;

  case 99:
#line 412 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 100:
#line 413 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginFieldDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); SKEL->getLexer()->expectType((yyvsp[(2) - (4)].intVal)); ;}
    break;

  case 101:
#line 414 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endFieldDecl(); ;}
    break;

  case 102:
#line 418 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 103:
#line 419 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginExposedFieldDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); SKEL->getLexer()->expectType((yyvsp[(2) - (4)].intVal)); ;}
    break;

  case 104:
#line 420 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endExposedFieldDecl(); ;}
    break;

  case 106:
#line 424 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->is((yyvsp[(3) - (3)].stringVal)); ;}
    break;

  case 107:
#line 428 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        Int32 iFieldTypeId = SKEL->getFieldType((yyvsp[(1) - (1)].stringVal));
        if (SKEL->getMapFieldTypes() == true)
            iFieldTypeId = SKEL->mapExtIntFieldType((yyvsp[(1) - (1)].stringVal), iFieldTypeId);
        SKEL->getLexer()->expectType(iFieldTypeId);
        SKEL->beginField((yyvsp[(1) - (1)].stringVal), iFieldTypeId);
    ;}
    break;

  case 108:
#line 435 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endField(); ;}
    break;

  case 114:
#line 443 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->is((yyvsp[(3) - (3)].stringVal)); ;}
    break;

  case 226:
#line 573 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { (yyval.intVal) = (yyvsp[(1) - (1)].intVal); ;}
    break;

  case 227:
#line 574 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { (yyval.intVal) = (yyvsp[(1) - (1)].intVal); ;}
    break;

  case 228:
#line 577 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { (yyval.doubleVal) = (yyvsp[(1) - (1)].intVal); ;}
    break;

  case 229:
#line 578 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { (yyval.doubleVal) = (yyvsp[(1) - (1)].doubleVal); ;}
    break;

  case 230:
#line 581 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { (yyval.floatVal) = static_cast<float>((yyvsp[(1) - (1)].intVal)); ;}
    break;

  case 231:
#line 582 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { (yyval.floatVal) = static_cast<float>((yyvsp[(1) - (1)].doubleVal)); ;}
    break;

  case 232:
#line 586 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->addBoolValue((yyvsp[(1) - (1)].boolVal));
    ;}
    break;

  case 233:
#line 589 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->addFieldValue((yyvsp[(1) - (1)].stringVal)); ;}
    break;

  case 234:
#line 592 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 235:
#line 593 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 236:
#line 595 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addColorValue(Color3f((yyvsp[(1) - (5)].floatVal), (yyvsp[(3) - (5)].floatVal), (yyvsp[(5) - (5)].floatVal)));
    ;}
    break;

  case 237:
#line 601 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 238:
#line 602 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 239:
#line 603 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 240:
#line 605 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addColorRGBAValue(Color4f((yyvsp[(1) - (7)].floatVal), (yyvsp[(3) - (7)].floatVal), (yyvsp[(5) - (7)].floatVal), (yyvsp[(7) - (7)].floatVal)));
    ;}
    break;

  case 241:
#line 612 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->addDoubleValue((yyvsp[(1) - (1)].doubleVal));
    ;}
    break;

  case 242:
#line 618 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->addFloatValue((yyvsp[(1) - (1)].floatVal));
    ;}
    break;

  case 243:
#line 623 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 244:
#line 624 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 245:
#line 626 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->beginImage((yyvsp[(1) - (5)].intVal), (yyvsp[(3) - (5)].intVal), (yyvsp[(5) - (5)].intVal));
    ;}
    break;

  case 246:
#line 631 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->endImage();
    ;}
    break;

  case 247:
#line 637 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->addImagePixel((yyvsp[(2) - (2)].intVal));
    ;}
    break;

  case 249:
#line 644 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->addInt32Value((yyvsp[(1) - (1)].intVal));
    ;}
    break;

  case 250:
#line 649 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 251:
#line 650 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 252:
#line 651 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 253:
#line 652 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 254:
#line 653 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 255:
#line 654 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 256:
#line 655 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 257:
#line 656 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 258:
#line 658 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addMatrix3dValue(
             (yyvsp[(1) - (17)].doubleVal),  (yyvsp[(3) - (17)].doubleVal),  (yyvsp[(5) - (17)].doubleVal),
             (yyvsp[(7) - (17)].doubleVal),  (yyvsp[(9) - (17)].doubleVal), (yyvsp[(11) - (17)].doubleVal),
            (yyvsp[(13) - (17)].doubleVal), (yyvsp[(15) - (17)].doubleVal), (yyvsp[(17) - (17)].doubleVal));
    ;}
    break;

  case 259:
#line 667 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 260:
#line 668 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 261:
#line 669 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 262:
#line 670 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 263:
#line 671 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 264:
#line 672 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 265:
#line 673 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 266:
#line 674 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 267:
#line 676 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addMatrix3fValue(
             (yyvsp[(1) - (17)].floatVal),  (yyvsp[(3) - (17)].floatVal),  (yyvsp[(5) - (17)].floatVal),
             (yyvsp[(7) - (17)].floatVal),  (yyvsp[(9) - (17)].floatVal), (yyvsp[(11) - (17)].floatVal),
            (yyvsp[(13) - (17)].floatVal), (yyvsp[(15) - (17)].floatVal), (yyvsp[(17) - (17)].floatVal));
    ;}
    break;

  case 268:
#line 685 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 269:
#line 686 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 270:
#line 687 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 271:
#line 688 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 272:
#line 689 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 273:
#line 690 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 274:
#line 691 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 275:
#line 692 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 276:
#line 693 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 277:
#line 694 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 278:
#line 695 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 279:
#line 696 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 280:
#line 697 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 281:
#line 698 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 282:
#line 699 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 283:
#line 701 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addMatrix4dValue(Matrix4d(
             (yyvsp[(1) - (31)].doubleVal),  (yyvsp[(3) - (31)].doubleVal),  (yyvsp[(5) - (31)].doubleVal),  (yyvsp[(7) - (31)].doubleVal),
             (yyvsp[(9) - (31)].doubleVal), (yyvsp[(11) - (31)].doubleVal), (yyvsp[(13) - (31)].doubleVal), (yyvsp[(15) - (31)].doubleVal),
            (yyvsp[(17) - (31)].doubleVal), (yyvsp[(19) - (31)].doubleVal), (yyvsp[(21) - (31)].doubleVal), (yyvsp[(23) - (31)].doubleVal),
            (yyvsp[(25) - (31)].doubleVal), (yyvsp[(27) - (31)].doubleVal), (yyvsp[(29) - (31)].doubleVal), (yyvsp[(31) - (31)].doubleVal)));
    ;}
    break;

  case 284:
#line 711 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 285:
#line 712 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 286:
#line 713 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 287:
#line 714 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 288:
#line 715 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 289:
#line 716 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 290:
#line 717 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 291:
#line 718 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 292:
#line 719 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 293:
#line 720 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 294:
#line 721 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 295:
#line 722 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 296:
#line 723 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 297:
#line 724 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 298:
#line 725 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 299:
#line 727 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addMatrix4fValue(Matrix4f(
             (yyvsp[(1) - (31)].floatVal),  (yyvsp[(3) - (31)].floatVal),  (yyvsp[(5) - (31)].floatVal),  (yyvsp[(7) - (31)].floatVal),
             (yyvsp[(9) - (31)].floatVal), (yyvsp[(11) - (31)].floatVal), (yyvsp[(13) - (31)].floatVal), (yyvsp[(15) - (31)].floatVal),
            (yyvsp[(17) - (31)].floatVal), (yyvsp[(19) - (31)].floatVal), (yyvsp[(21) - (31)].floatVal), (yyvsp[(23) - (31)].floatVal),
            (yyvsp[(25) - (31)].floatVal), (yyvsp[(27) - (31)].floatVal), (yyvsp[(29) - (31)].floatVal), (yyvsp[(31) - (31)].floatVal)));
    ;}
    break;

  case 301:
#line 738 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->nullNode(); ;}
    break;

  case 302:
#line 741 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 303:
#line 742 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 304:
#line 743 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 305:
#line 745 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addRotationValue(Vec3f((yyvsp[(1) - (7)].floatVal), (yyvsp[(3) - (7)].floatVal), (yyvsp[(5) - (7)].floatVal)), (yyvsp[(7) - (7)].floatVal));
    ;}
    break;

  case 306:
#line 752 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->addStringValue((yyvsp[(1) - (1)].stringVal));
    ;}
    break;

  case 307:
#line 756 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { /* Not VRML conformant */
        SKEL->addStringValue((yyvsp[(1) - (1)].stringVal));
    ;}
    break;

  case 308:
#line 762 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->addTimeValue((yyvsp[(1) - (1)].doubleVal));
    ;}
    break;

  case 309:
#line 767 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 310:
#line 769 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addVec2dValue(Vec2d((yyvsp[(1) - (3)].doubleVal), (yyvsp[(3) - (3)].doubleVal)));
    ;}
    break;

  case 311:
#line 775 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 312:
#line 777 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addVec2fValue(Vec2f((yyvsp[(1) - (3)].floatVal), (yyvsp[(3) - (3)].floatVal)));
    ;}
    break;

  case 313:
#line 783 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 314:
#line 784 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 315:
#line 785 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 316:
#line 786 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addVec3dValue(Vec3d((yyvsp[(1) - (6)].doubleVal), (yyvsp[(3) - (6)].doubleVal), (yyvsp[(5) - (6)].doubleVal)));
    ;}
    break;

  case 317:
#line 792 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 318:
#line 793 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 319:
#line 794 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 320:
#line 795 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addVec3fValue(Vec3f((yyvsp[(1) - (6)].floatVal), (yyvsp[(3) - (6)].floatVal), (yyvsp[(5) - (6)].floatVal)));
    ;}
    break;

  case 321:
#line 801 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 322:
#line 802 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 323:
#line 803 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 324:
#line 804 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 325:
#line 805 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addVec4dValue(Vec4d((yyvsp[(1) - (8)].doubleVal), (yyvsp[(3) - (8)].doubleVal), (yyvsp[(5) - (8)].doubleVal), (yyvsp[(7) - (8)].doubleVal)));
    ;}
    break;

  case 326:
#line 811 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 327:
#line 812 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 328:
#line 813 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 329:
#line 814 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 330:
#line 815 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addVec4fValue(Vec4f((yyvsp[(1) - (8)].floatVal), (yyvsp[(3) - (8)].floatVal), (yyvsp[(5) - (8)].floatVal), (yyvsp[(7) - (8)].floatVal)));
    ;}
    break;

  case 415:
#line 991 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 416:
#line 992 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 417:
#line 993 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 418:
#line 995 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addColor4iValue(Color4ub(static_cast<UInt8>((yyvsp[(1) - (7)].intVal)), static_cast<UInt8>((yyvsp[(3) - (7)].intVal)),
                                       static_cast<UInt8>((yyvsp[(5) - (7)].intVal)), static_cast<UInt8>((yyvsp[(7) - (7)].intVal))));
    ;}
    break;

  case 419:
#line 1002 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 420:
#line 1004 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addPnt2fValue(Pnt2f((yyvsp[(1) - (3)].floatVal), (yyvsp[(3) - (3)].floatVal)));
    ;}
    break;

  case 421:
#line 1010 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 422:
#line 1011 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 423:
#line 1013 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addPnt3fValue(Pnt3f((yyvsp[(1) - (5)].floatVal), (yyvsp[(3) - (5)].floatVal), (yyvsp[(5) - (5)].floatVal)));
    ;}
    break;

  case 424:
#line 1019 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 425:
#line 1020 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 426:
#line 1021 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 427:
#line 1023 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addPnt4fValue(Pnt4f((yyvsp[(1) - (7)].floatVal), (yyvsp[(3) - (7)].floatVal), (yyvsp[(5) - (7)].floatVal), (yyvsp[(7) - (7)].floatVal)));
    ;}
    break;

  case 428:
#line 1029 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 429:
#line 1030 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 430:
#line 1031 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 431:
#line 1033 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addPlaneValue(Plane(Vec3f((yyvsp[(1) - (7)].floatVal), (yyvsp[(3) - (7)].floatVal), (yyvsp[(5) - (7)].floatVal)), (yyvsp[(7) - (7)].floatVal)));
    ;}
    break;

  case 432:
#line 1039 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 433:
#line 1040 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 434:
#line 1041 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 435:
#line 1043 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->_tmpFloat1 = (yyvsp[(1) - (7)].floatVal); SKEL->_tmpFloat2 = (yyvsp[(3) - (7)].floatVal);
        SKEL->_tmpFloat3 = (yyvsp[(5) - (7)].floatVal); SKEL->_tmpFloat4 = (yyvsp[(7) - (7)].floatVal);
    ;}
    break;

  case 437:
#line 1051 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 438:
#line 1053 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        DynamicVolume dv(DynamicVolume::BOX_VOLUME);
        BoxVolume &bv = dynamic_cast<BoxVolume&>(dv.getInstance());
        bv.setBounds(SKEL->_tmpFloat1, SKEL->_tmpFloat2, SKEL->_tmpFloat3, SKEL->_tmpFloat4, (yyvsp[(1) - (3)].floatVal), (yyvsp[(3) - (3)].floatVal));
        SKEL->addVolumeValue(dv);
    ;}
    break;

  case 439:
#line 1061 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        DynamicVolume dv(DynamicVolume::SPHERE_VOLUME);
        SphereVolume &sv = dynamic_cast<SphereVolume&>(dv.getInstance());
        sv.setValue(Pnt3f(SKEL->_tmpFloat1, SKEL->_tmpFloat2, SKEL->_tmpFloat3), SKEL->_tmpFloat4);
        SKEL->addVolumeValue(dv);
    ;}
    break;


/* Line 1267 of yacc.c.  */
#line 3425 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.cpp"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
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
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
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


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
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
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 1108 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"


int OSGScanParseSkel_lex(YYSTYPE *lvalp, void *pSkel)
{
    return SKEL->lex(lvalp);
}

