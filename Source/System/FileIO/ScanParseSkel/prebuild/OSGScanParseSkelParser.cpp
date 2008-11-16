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
     TOK_SFVec2i = 329,
     TOK_MFVec2i = 330,
     TOK_hex = 331,
     TOK_int32 = 332,
     TOK_double = 333,
     TOK_string = 334,
     TOK_bool = 335,
     TOK_NULL = 336,
     TOK_Id = 337,
     TOK_ImageFinished = 338,
     TOK_Error = 339
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
#define TOK_SFVec2i 329
#define TOK_MFVec2i 330
#define TOK_hex 331
#define TOK_int32 332
#define TOK_double 333
#define TOK_string 334
#define TOK_bool 335
#define TOK_NULL 336
#define TOK_Id 337
#define TOK_ImageFinished 338
#define TOK_Error 339




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
/* Line 187 of yacc.c.  */
#line 281 "build.linux.g++/type-debug--arch-x64/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.cpp"
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

#define SKEL (static_cast<ScanParseSkel *>(pSkel))

#if(!defined(__GNUC__) && defined(__ICL) && __INTEL_COMPILER_VERSION >= 900)
# define alloca(size)   __builtin_alloca (size)
#endif



/* Line 216 of yacc.c.  */
#line 323 "build.linux.g++/type-debug--arch-x64/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.cpp"

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
#define YYLAST   963

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  90
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  255
/* YYNRULES -- Number of rules.  */
#define YYNRULES  458
/* YYNRULES -- Number of states.  */
#define YYNSTATES  749

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   339

#define YYTRANSLATE(YYX)						\
  (static_cast<unsigned int>(YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,    89,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    85,     2,    86,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    87,     2,    88,     2,     2,     2,     2,
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
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
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
     537,   540,   543,   546,   549,   552,   555,   558,   561,   564,
     567,   569,   571,   573,   575,   577,   579,   581,   583,   584,
     585,   591,   592,   593,   594,   602,   604,   606,   607,   608,
     609,   618,   621,   622,   624,   625,   626,   627,   628,   629,
     630,   631,   632,   650,   651,   652,   653,   654,   655,   656,
     657,   658,   676,   677,   678,   679,   680,   681,   682,   683,
     684,   685,   686,   687,   688,   689,   690,   691,   723,   724,
     725,   726,   727,   728,   729,   730,   731,   732,   733,   734,
     735,   736,   737,   738,   770,   772,   774,   775,   776,   777,
     785,   787,   789,   791,   793,   794,   798,   799,   803,   804,
     805,   806,   813,   814,   815,   816,   823,   824,   825,   826,
     827,   836,   837,   838,   839,   840,   849,   851,   855,   858,
     859,   861,   865,   868,   869,   871,   875,   878,   879,   881,
     885,   888,   889,   891,   895,   898,   899,   901,   905,   908,
     909,   911,   915,   918,   919,   921,   925,   928,   929,   931,
     935,   938,   939,   941,   945,   948,   949,   951,   955,   958,
     959,   961,   965,   968,   969,   971,   975,   978,   979,   981,
     985,   988,   989,   991,   995,   998,   999,  1001,  1005,  1008,
    1009,  1011,  1015,  1018,  1019,  1021,  1025,  1028,  1029,  1031,
    1035,  1038,  1039,  1041,  1045,  1048,  1049,  1051,  1055,  1058,
    1059,  1060,  1061,  1062,  1070,  1071,  1075,  1076,  1077,  1083,
    1084,  1085,  1086,  1094,  1095,  1096,  1097,  1105,  1106,  1107,
    1108,  1109,  1110,  1122,  1123,  1127,  1129,  1133,  1136,  1137,
    1139,  1143,  1146,  1147,  1149,  1153,  1156,  1157,  1159,  1163,
    1166,  1167,  1169,  1173,  1176,  1177,  1179,  1183,  1186
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      91,     0,    -1,    92,    93,    95,    98,   103,    -1,     3,
      -1,    -1,     4,    94,    -1,    -1,    82,    -1,    95,    96,
      -1,    -1,     5,    97,    -1,    82,    -1,    79,    -1,    98,
      99,    -1,    -1,    -1,     6,   101,   100,   102,    -1,    79,
      -1,    79,    -1,   103,   104,    -1,    -1,   105,    -1,   109,
      -1,   130,    -1,   134,    -1,   137,    -1,    -1,   162,   106,
     141,    -1,    -1,    -1,    10,   161,   107,   162,   108,   141,
      -1,    11,   161,    -1,   110,    -1,   121,    -1,    -1,    -1,
       7,   162,   111,    85,   113,    86,   112,    87,   103,    88,
      -1,   113,   114,    -1,    -1,    -1,    17,   166,   115,   164,
      -1,    -1,    18,   166,   116,   165,    -1,    -1,    -1,    20,
     166,   117,   163,   118,   167,    -1,    -1,    -1,    19,   166,
     119,   163,   120,   167,    -1,    -1,    -1,     8,   162,   122,
      85,   124,    86,   123,   140,    -1,   124,   125,    -1,    -1,
      -1,    17,   166,   126,   164,    -1,    -1,    18,   166,   127,
     165,    -1,    -1,    20,   166,   128,   163,    -1,    -1,    19,
     166,   129,   163,    -1,    -1,    -1,    -1,    12,   161,   131,
      89,   165,   132,    13,   161,   133,    89,   164,    -1,    -1,
      -1,    14,   161,   135,    89,   161,   136,   139,    -1,    -1,
      15,   161,   138,   139,    -1,    16,   161,    -1,    -1,   292,
      -1,    87,   142,    88,    -1,   142,   143,    -1,    -1,   158,
      -1,   144,    -1,   147,    -1,   151,    -1,   154,    -1,     1,
      -1,    -1,    -1,    17,   166,   145,   164,   146,   150,    -1,
      -1,    -1,    18,   166,   148,   165,   149,   150,    -1,    -1,
       9,   163,    -1,    -1,    -1,    20,   166,   152,   163,   153,
     157,    -1,    -1,    -1,    19,   166,   155,   163,   156,   157,
      -1,   167,    -1,   166,     9,   163,    -1,    -1,   163,   159,
     160,    -1,   130,    -1,   109,    -1,   134,    -1,   137,    -1,
     167,    -1,   166,     9,   163,    -1,    82,    -1,    82,    -1,
      82,    -1,    82,    -1,    82,    -1,    21,    -1,    22,    -1,
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
      73,    -1,    21,   266,    -1,    22,   268,    -1,    23,   270,
      -1,    24,   272,    -1,    25,   274,    -1,    26,   276,    -1,
      27,   278,    -1,    28,   280,    -1,    29,   282,    -1,    30,
     284,    -1,    31,   286,    -1,    32,   288,    -1,    33,   290,
      -1,    34,   292,    -1,    35,   294,    -1,    36,   296,    -1,
      37,   298,    -1,    38,   300,    -1,    39,   302,    -1,    40,
     304,    -1,    41,   306,    -1,    42,   171,    -1,    43,   172,
      -1,    44,   175,    -1,    45,   179,    -1,    46,   180,    -1,
      47,   181,    -1,    48,   186,    -1,    49,   187,    -1,    50,
     196,    -1,    51,   205,    -1,    52,   221,    -1,    53,   237,
      -1,    54,   238,    -1,    55,   242,    -1,    56,   243,    -1,
      57,   244,    -1,    58,   246,    -1,    59,   248,    -1,    60,
     252,    -1,    61,   256,    -1,    62,   261,    -1,    63,   333,
      -1,    64,   335,    -1,    65,   337,    -1,    66,   339,    -1,
      67,   341,    -1,    68,   308,    -1,    69,   312,    -1,    70,
     314,    -1,    71,   317,    -1,    72,   321,    -1,    73,   325,
      -1,    74,   331,    -1,    75,   343,    -1,    76,    -1,    77,
      -1,    77,    -1,    78,    -1,    77,    -1,    78,    -1,    80,
      -1,    82,    -1,    -1,    -1,   170,   173,   170,   174,   170,
      -1,    -1,    -1,    -1,   170,   176,   170,   177,   170,   178,
     170,    -1,   169,    -1,   170,    -1,    -1,    -1,    -1,   168,
     182,   168,   183,   168,   184,   185,    83,    -1,   185,   168,
      -1,    -1,   168,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   169,   188,   169,   189,   169,   190,   169,   191,
     169,   192,   169,   193,   169,   194,   169,   195,   169,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   170,   197,
     170,   198,   170,   199,   170,   200,   170,   201,   170,   202,
     170,   203,   170,   204,   170,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   169,   206,   169,   207,   169,   208,   169,   209,   169,
     210,   169,   211,   169,   212,   169,   213,   169,   214,   169,
     215,   169,   216,   169,   217,   169,   218,   169,   219,   169,
     220,   169,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   170,   222,
     170,   223,   170,   224,   170,   225,   170,   226,   170,   227,
     170,   228,   170,   229,   170,   230,   170,   231,   170,   232,
     170,   233,   170,   234,   170,   235,   170,   236,   170,    -1,
     105,    -1,    81,    -1,    -1,    -1,    -1,   170,   239,   170,
     240,   170,   241,   170,    -1,    79,    -1,    82,    -1,    76,
      -1,   169,    -1,    -1,   169,   245,   169,    -1,    -1,   170,
     247,   170,    -1,    -1,    -1,    -1,   169,   249,   169,   250,
     169,   251,    -1,    -1,    -1,    -1,   170,   253,   170,   254,
     170,   255,    -1,    -1,    -1,    -1,    -1,   169,   257,   169,
     258,   169,   259,   169,   260,    -1,    -1,    -1,    -1,    -1,
     170,   262,   170,   263,   170,   264,   170,   265,    -1,   171,
      -1,    85,   267,    86,    -1,   267,   171,    -1,    -1,   172,
      -1,    85,   269,    86,    -1,   269,   172,    -1,    -1,   175,
      -1,    85,   271,    86,    -1,   271,   175,    -1,    -1,   179,
      -1,    85,   273,    86,    -1,   273,   179,    -1,    -1,   180,
      -1,    85,   275,    86,    -1,   275,   180,    -1,    -1,   181,
      -1,    85,   277,    86,    -1,   277,   181,    -1,    -1,   186,
      -1,    85,   279,    86,    -1,   279,   186,    -1,    -1,   187,
      -1,    85,   281,    86,    -1,   281,   187,    -1,    -1,   196,
      -1,    85,   283,    86,    -1,   283,   196,    -1,    -1,   205,
      -1,    85,   285,    86,    -1,   285,   205,    -1,    -1,   221,
      -1,    85,   287,    86,    -1,   287,   221,    -1,    -1,   237,
      -1,    85,   289,    86,    -1,   289,   237,    -1,    -1,   238,
      -1,    85,   291,    86,    -1,   291,   238,    -1,    -1,   242,
      -1,    85,   293,    86,    -1,   293,   242,    -1,    -1,   243,
      -1,    85,   295,    86,    -1,   295,   243,    -1,    -1,   244,
      -1,    85,   297,    86,    -1,   297,   244,    -1,    -1,   246,
      -1,    85,   299,    86,    -1,   299,   246,    -1,    -1,   248,
      -1,    85,   301,    86,    -1,   301,   248,    -1,    -1,   252,
      -1,    85,   303,    86,    -1,   303,   252,    -1,    -1,   256,
      -1,    85,   305,    86,    -1,   305,   256,    -1,    -1,   261,
      -1,    85,   307,    86,    -1,   307,   261,    -1,    -1,    -1,
      -1,    -1,   168,   309,   168,   310,   168,   311,   168,    -1,
      -1,   170,   313,   170,    -1,    -1,    -1,   170,   315,   170,
     316,   170,    -1,    -1,    -1,    -1,   170,   318,   170,   319,
     170,   320,   170,    -1,    -1,    -1,    -1,   170,   322,   170,
     323,   170,   324,   170,    -1,    -1,    -1,    -1,    -1,    -1,
     170,   326,   170,   327,   170,   328,   170,   329,   170,   330,
     170,    -1,    -1,   168,   332,   168,    -1,   308,    -1,    85,
     334,    86,    -1,   334,   308,    -1,    -1,   312,    -1,    85,
     336,    86,    -1,   336,   312,    -1,    -1,   314,    -1,    85,
     338,    86,    -1,   338,   314,    -1,    -1,   317,    -1,    85,
     340,    86,    -1,   340,   317,    -1,    -1,   321,    -1,    85,
     342,    86,    -1,   342,   321,    -1,    -1,   331,    -1,    85,
     344,    86,    -1,   344,   331,    -1,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   198,   198,   205,   206,   209,   210,   213,   216,   217,
     221,   226,   227,   234,   235,   240,   238,   245,   248,   251,
     252,   255,   256,   257,   258,   259,   262,   262,   265,   266,
     264,   268,   272,   273,   280,   281,   280,   285,   286,   290,
     289,   293,   292,   296,   297,   295,   300,   301,   299,   305,
     306,   305,   310,   311,   315,   314,   318,   317,   321,   320,
     324,   323,   329,   331,   333,   328,   340,   342,   339,   353,
     352,   363,   365,   368,   371,   374,   375,   378,   379,   380,
     381,   382,   383,   387,   388,   386,   393,   394,   392,   397,
     399,   403,   404,   402,   409,   410,   408,   414,   415,   419,
     418,   427,   428,   429,   430,   433,   434,   437,   440,   443,
     446,   449,   452,   453,   454,   455,   456,   457,   458,   459,
     460,   461,   462,   463,   464,   465,   466,   467,   468,   469,
     470,   471,   472,   473,   474,   475,   476,   477,   478,   479,
     480,   481,   482,   483,   484,   485,   486,   487,   488,   489,
     490,   491,   492,   493,   495,   496,   497,   498,   499,   500,
     501,   502,   503,   504,   505,   508,   509,   510,   511,   512,
     513,   514,   515,   516,   517,   518,   519,   520,   521,   522,
     523,   524,   525,   526,   527,   528,   529,   530,   531,   532,
     533,   534,   535,   536,   537,   538,   539,   540,   541,   542,
     543,   544,   545,   546,   547,   548,   549,   551,   552,   553,
     554,   555,   556,   557,   558,   559,   560,   561,   562,   563,
     566,   567,   570,   571,   574,   575,   578,   582,   585,   586,
     585,   594,   595,   596,   594,   604,   610,   616,   617,   619,
     616,   629,   633,   636,   642,   643,   644,   645,   646,   647,
     648,   649,   642,   660,   661,   662,   663,   664,   665,   666,
     667,   660,   678,   679,   680,   681,   682,   683,   684,   685,
     686,   687,   688,   689,   690,   691,   692,   678,   704,   705,
     706,   707,   708,   709,   710,   711,   712,   713,   714,   715,
     716,   717,   718,   704,   730,   731,   734,   735,   736,   734,
     744,   748,   752,   758,   764,   764,   772,   772,   780,   781,
     782,   780,   789,   790,   791,   789,   798,   799,   800,   801,
     798,   808,   809,   810,   811,   808,   818,   819,   822,   823,
     826,   827,   830,   831,   834,   835,   838,   839,   842,   843,
     846,   847,   850,   851,   854,   855,   858,   859,   862,   863,
     866,   867,   870,   871,   874,   875,   878,   879,   882,   883,
     886,   887,   890,   891,   894,   895,   898,   899,   902,   903,
     906,   907,   910,   911,   914,   915,   918,   919,   922,   923,
     926,   927,   930,   931,   934,   935,   938,   939,   942,   943,
     946,   947,   950,   951,   954,   955,   958,   959,   962,   963,
     966,   967,   970,   971,   974,   975,   978,   979,   982,   983,
     988,   989,   990,   988,   999,   999,  1007,  1008,  1007,  1016,
    1017,  1018,  1016,  1026,  1027,  1028,  1026,  1036,  1037,  1038,
    1039,  1040,  1036,  1050,  1050,  1058,  1059,  1062,  1063,  1066,
    1067,  1070,  1071,  1074,  1075,  1078,  1079,  1082,  1083,  1086,
    1087,  1090,  1091,  1094,  1095,  1098,  1099,  1102,  1103
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
  "TOK_SFVolume", "TOK_SFVec2i", "TOK_MFVec2i", "TOK_hex", "TOK_int32",
  "TOK_double", "TOK_string", "TOK_bool", "TOK_NULL", "TOK_Id",
  "TOK_ImageFinished", "TOK_Error", "'['", "']'", "'{'", "'}'", "'.'",
  "$accept", "x3dScene", "headerStatement", "profileStatement",
  "profileNameId", "componentStatements", "componentStatement",
  "componentNameId", "metaStatements", "metaStatement", "@1", "metakey",
  "metavalue", "statements", "statement", "nodeStatement", "@2", "@3",
  "@4", "protoStatement", "proto", "@5", "@6", "interfaceDeclarations",
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
  "sfvec2iValue", "@124", "mfcolor4iValue", "sfcolor4iValues",
  "mfpnt2fValue", "sfpnt2fValues", "mfpnt3fValue", "sfpnt3fValues",
  "mfpnt4fValue", "sfpnt4fValues", "mfplaneValue", "sfplaneValues",
  "mfvec2iValue", "sfvec2iValues", 0
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
     335,   336,   337,   338,   339,    91,    93,   123,   125,    46
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,    90,    91,    92,    92,    93,    93,    94,    95,    95,
      96,    97,    97,    98,    98,   100,    99,   101,   102,   103,
     103,   104,   104,   104,   104,   104,   106,   105,   107,   108,
     105,   105,   109,   109,   111,   112,   110,   113,   113,   115,
     114,   116,   114,   117,   118,   114,   119,   120,   114,   122,
     123,   121,   124,   124,   126,   125,   127,   125,   128,   125,
     129,   125,   131,   132,   133,   130,   135,   136,   134,   138,
     137,   139,   139,   140,   141,   142,   142,   143,   143,   143,
     143,   143,   143,   145,   146,   144,   148,   149,   147,   150,
     150,   152,   153,   151,   155,   156,   154,   157,   157,   159,
     158,   158,   158,   158,   158,   160,   160,   161,   162,   163,
     164,   165,   166,   166,   166,   166,   166,   166,   166,   166,
     166,   166,   166,   166,   166,   166,   166,   166,   166,   166,
     166,   166,   166,   166,   166,   166,   166,   166,   166,   166,
     166,   166,   166,   166,   166,   166,   166,   166,   166,   166,
     166,   166,   166,   166,   166,   166,   166,   166,   166,   166,
     166,   166,   166,   166,   166,   167,   167,   167,   167,   167,
     167,   167,   167,   167,   167,   167,   167,   167,   167,   167,
     167,   167,   167,   167,   167,   167,   167,   167,   167,   167,
     167,   167,   167,   167,   167,   167,   167,   167,   167,   167,
     167,   167,   167,   167,   167,   167,   167,   167,   167,   167,
     167,   167,   167,   167,   167,   167,   167,   167,   167,   167,
     168,   168,   169,   169,   170,   170,   171,   171,   173,   174,
     172,   176,   177,   178,   175,   179,   180,   182,   183,   184,
     181,   185,   185,   186,   188,   189,   190,   191,   192,   193,
     194,   195,   187,   197,   198,   199,   200,   201,   202,   203,
     204,   196,   206,   207,   208,   209,   210,   211,   212,   213,
     214,   215,   216,   217,   218,   219,   220,   205,   222,   223,
     224,   225,   226,   227,   228,   229,   230,   231,   232,   233,
     234,   235,   236,   221,   237,   237,   239,   240,   241,   238,
     242,   242,   242,   243,   245,   244,   247,   246,   249,   250,
     251,   248,   253,   254,   255,   252,   257,   258,   259,   260,
     256,   262,   263,   264,   265,   261,   266,   266,   267,   267,
     268,   268,   269,   269,   270,   270,   271,   271,   272,   272,
     273,   273,   274,   274,   275,   275,   276,   276,   277,   277,
     278,   278,   279,   279,   280,   280,   281,   281,   282,   282,
     283,   283,   284,   284,   285,   285,   286,   286,   287,   287,
     288,   288,   289,   289,   290,   290,   291,   291,   292,   292,
     293,   293,   294,   294,   295,   295,   296,   296,   297,   297,
     298,   298,   299,   299,   300,   300,   301,   301,   302,   302,
     303,   303,   304,   304,   305,   305,   306,   306,   307,   307,
     309,   310,   311,   308,   313,   312,   315,   316,   314,   318,
     319,   320,   317,   322,   323,   324,   321,   326,   327,   328,
     329,   330,   325,   332,   331,   333,   333,   334,   334,   335,
     335,   336,   336,   337,   337,   338,   338,   339,   339,   340,
     340,   341,   341,   342,   342,   343,   343,   344,   344
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     0,
       5,     0,     0,     0,     7,     1,     1,     0,     0,     0,
       8,     2,     0,     1,     0,     0,     0,     0,     0,     0,
       0,     0,    17,     0,     0,     0,     0,     0,     0,     0,
       0,    17,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    31,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    31,     1,     1,     0,     0,     0,     7,
       1,     1,     1,     1,     0,     3,     0,     3,     0,     0,
       0,     6,     0,     0,     0,     6,     0,     0,     0,     0,
       8,     0,     0,     0,     0,     8,     1,     3,     2,     0,
       1,     3,     2,     0,     1,     3,     2,     0,     1,     3,
       2,     0,     1,     3,     2,     0,     1,     3,     2,     0,
       1,     3,     2,     0,     1,     3,     2,     0,     1,     3,
       2,     0,     1,     3,     2,     0,     1,     3,     2,     0,
       1,     3,     2,     0,     1,     3,     2,     0,     1,     3,
       2,     0,     1,     3,     2,     0,     1,     3,     2,     0,
       1,     3,     2,     0,     1,     3,     2,     0,     1,     3,
       2,     0,     1,     3,     2,     0,     1,     3,     2,     0,
       0,     0,     0,     7,     0,     3,     0,     0,     5,     0,
       0,     0,     7,     0,     0,     0,     7,     0,     0,     0,
       0,     0,    11,     0,     3,     1,     3,     2,     0,     1,
       3,     2,     0,     1,     3,     2,     0,     1,     3,     2,
       0,     1,     3,     2,     0,     1,     3,     2,     0
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
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
     162,   163,   164,     0,     0,   100,     0,   105,     0,     0,
       0,     0,    20,     0,     0,     0,     0,   302,   300,   301,
     381,    51,   378,    73,    64,   110,    84,    87,    95,    92,
     226,   227,   329,   326,   165,   224,   225,   333,   228,   330,
     166,   337,   231,   334,   167,   222,   223,   341,   235,   338,
     168,   345,   236,   342,   169,   220,   221,   349,   237,   346,
     170,   353,   243,   350,   171,   357,   244,   354,   172,   361,
     253,   358,   173,   365,   262,   362,   174,   369,   278,   366,
     175,   295,   373,   294,   370,   176,   377,   296,   374,   177,
     178,   385,   303,   382,   179,   389,   304,   386,   180,   393,
     306,   390,   181,   397,   308,   394,   182,   401,   312,   398,
     183,   405,   316,   402,   184,   409,   321,   406,   185,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   200,   201,   202,   203,   204,   205,   206,
     438,   410,   435,   207,   442,   414,   439,   208,   446,   416,
     443,   209,   450,   419,   447,   210,   454,   423,   451,   211,
     212,   213,   214,   215,   216,   427,   217,   433,   218,   458,
     455,   219,     0,    40,    42,    47,    44,     0,    55,    57,
      61,    59,     0,     0,    89,    89,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   106,     0,     0,    36,   379,
     380,     0,     0,    85,    88,    96,     0,    97,    93,   327,
     328,   331,   332,   229,   335,   336,   232,   339,   340,   343,
     344,   347,   348,   238,   351,   352,   355,   356,   245,   359,
     360,   254,   363,   364,   263,   367,   368,   279,   371,   372,
     375,   376,   297,   383,   384,   387,   388,   305,   391,   392,
     307,   395,   396,   309,   399,   400,   313,   403,   404,   317,
     407,   408,   322,   436,   437,   411,   440,   441,   415,   444,
     445,   417,   448,   449,   420,   452,   453,   424,   428,   434,
     456,   457,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    48,    45,    65,    90,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    98,   230,   233,
     239,   246,   255,   264,   280,   298,   310,   314,   318,   323,
     412,   418,   421,   425,   429,     0,   242,     0,     0,     0,
       0,     0,   311,   315,     0,     0,     0,     0,     0,     0,
     234,     0,   247,   256,   265,   281,   299,   319,   324,   413,
     422,   426,   430,   240,   241,     0,     0,     0,     0,   320,
     325,     0,   248,   257,   266,   282,   431,     0,     0,     0,
       0,     0,   249,   258,   267,   283,   432,     0,     0,     0,
       0,   250,   259,   268,   284,     0,     0,     0,     0,   251,
     260,   269,   285,     0,     0,     0,     0,   252,   261,   270,
     286,     0,     0,   271,   287,     0,     0,   272,   288,     0,
       0,   273,   289,     0,     0,   274,   290,     0,     0,   275,
     291,     0,     0,   276,   292,     0,     0,   277,   293
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     6,     8,     9,    11,    15,    12,    17,
      38,    20,    49,    18,    29,   313,    47,    52,    68,    31,
      32,    50,   168,    66,    96,   238,   239,   241,   467,   240,
     466,    33,    51,   173,    67,   102,   243,   244,   246,   245,
      34,    53,   104,   413,    35,    54,   105,    36,    55,    64,
     251,    57,    65,    84,    85,   176,   414,    86,   177,   415,
     473,    87,   179,   417,    88,   178,   416,   475,    89,   163,
     235,    42,    37,    90,   256,    70,   476,   477,   288,   278,
     268,   263,   269,   420,   610,   273,   422,   611,   645,   279,
     283,   289,   426,   612,   646,   661,   293,   297,   429,   613,
     647,   675,   687,   697,   705,   713,   301,   431,   614,   648,
     676,   688,   698,   706,   714,   305,   433,   615,   649,   677,
     689,   699,   707,   715,   721,   725,   729,   733,   737,   741,
     745,   309,   435,   616,   650,   678,   690,   700,   708,   716,
     722,   726,   730,   734,   738,   742,   746,   314,   318,   438,
     617,   651,   252,   323,   327,   441,   331,   443,   335,   445,
     618,   652,   339,   447,   619,   653,   343,   449,   620,   654,
     679,   347,   451,   621,   655,   680,   264,   418,   270,   419,
     274,   421,   280,   423,   284,   424,   290,   425,   294,   427,
     298,   428,   302,   430,   306,   432,   310,   434,   315,   436,
     319,   437,   320,   412,   324,   439,   328,   440,   332,   442,
     336,   444,   340,   446,   344,   448,   348,   450,   372,   453,
     622,   656,   376,   455,   380,   457,   623,   384,   459,   624,
     657,   388,   461,   625,   658,   396,   462,   626,   659,   681,
     691,   398,   463,   373,   452,   377,   454,   381,   456,   385,
     458,   389,   460,   401,   464
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -203
static const yytype_int16 yypact[] =
{
      17,  -203,    36,    52,  -203,   -19,  -203,  -203,  -203,    62,
      12,  -203,    67,  -203,  -203,  -203,    -2,  -203,   102,  -203,
    -203,    24,    24,    42,    42,    42,    42,    42,  -203,  -203,
    -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,    20,  -203,
    -203,  -203,  -203,  -203,  -203,  -203,  -203,    31,  -203,  -203,
      64,    70,    24,    73,    78,   172,  -203,  -203,  -203,  -203,
    -203,   113,    42,    42,  -203,   122,   126,   134,    31,  -203,
    -203,  -203,  -203,  -203,   890,   890,   890,   890,  -203,  -203,
    -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,
    -203,   890,   890,   890,   890,  -203,  -203,   890,   890,   890,
     890,  -203,  -203,  -203,   190,   172,  -203,  -203,  -203,  -203,
    -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,
    -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,
    -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,
    -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,
    -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,
    -203,  -203,  -203,   544,  -203,  -203,  -203,  -203,   118,  -203,
    -203,  -203,  -203,   111,    42,  -203,   125,   113,   135,   135,
     413,   124,   138,   149,   236,   -25,   109,   286,   407,   412,
     425,    79,   427,   111,   436,   445,   450,   468,   543,   545,
     547,    53,   -53,   -53,   169,   -53,   194,   194,   169,   -53,
     169,   -53,    87,   -53,   378,   169,   169,   -53,   169,   -53,
     169,   -53,   121,   549,   558,   560,   562,   194,   -53,   -53,
     -53,   -53,   -53,   194,   123,  -203,   220,  -203,   125,   113,
     135,   135,  -203,   125,   113,   135,   135,  -203,  -203,  -203,
    -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,
    -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,
    -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,
    -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,
    -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,
    -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,
    -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,
    -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,
    -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,
    -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,
    -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,
    -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,
    -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,
    -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,
    -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,
    -203,  -203,   135,  -203,  -203,  -203,  -203,    68,  -203,  -203,
    -203,  -203,    95,   142,   283,   283,   544,   544,    90,   136,
     -53,   159,   -53,   181,   224,    71,   194,    89,   238,   169,
     254,   -53,   256,   169,   260,   -53,    77,   266,   -53,   270,
     272,   169,   276,   -53,   282,   169,   289,   -53,   319,   169,
     370,   -53,   103,   194,   373,   -53,   384,   -53,   401,   -53,
     405,   -53,   -53,   194,   106,  -203,   835,   835,  -203,  -203,
    -203,   125,   135,  -203,  -203,  -203,   285,  -203,  -203,  -203,
    -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,
    -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,
    -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,
    -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,
    -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,
    -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,
    -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,
    -203,  -203,   413,   124,   138,   149,   236,   -25,   109,   286,
     407,   412,   425,    79,   427,   111,   436,   445,   450,   468,
     543,   545,   547,    53,   -53,   -53,   169,   -53,   194,   194,
     169,   -53,   169,   -53,    87,   -53,   378,   169,   169,   -53,
     169,   -53,   169,   -53,   121,   549,   558,   560,   562,   194,
     -53,   -53,   -53,   -53,   -53,  -203,  -203,  -203,  -203,   135,
     -53,   -53,   194,   169,   -53,   169,   -53,   -53,   169,   -53,
     169,   -53,   194,   -53,   -53,   -53,   -53,  -203,  -203,  -203,
    -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,
    -203,  -203,  -203,  -203,  -203,   -53,  -203,   169,   -53,   169,
     -53,   -53,  -203,  -203,   169,   -53,   194,   -53,   -53,   -53,
    -203,    55,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,
    -203,  -203,  -203,  -203,  -203,   169,   -53,   169,   -53,  -203,
    -203,   -53,  -203,  -203,  -203,  -203,  -203,   169,   -53,   169,
     -53,   -53,  -203,  -203,  -203,  -203,  -203,   169,   -53,   169,
     -53,  -203,  -203,  -203,  -203,   169,   -53,   169,   -53,  -203,
    -203,  -203,  -203,   169,   -53,   169,   -53,  -203,  -203,  -203,
    -203,   169,   -53,  -203,  -203,   169,   -53,  -203,  -203,   169,
     -53,  -203,  -203,   169,   -53,  -203,  -203,   169,   -53,  -203,
    -203,   169,   -53,  -203,  -203,   169,   -53,  -203,  -203
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,
    -203,  -203,  -203,    -9,  -203,   -15,  -203,  -203,  -203,   198,
    -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,
    -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,
     226,  -203,  -203,  -203,   231,  -203,  -203,   233,  -203,   201,
    -203,   235,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,
    -107,  -203,  -203,  -203,  -203,  -203,  -203,  -100,  -203,  -203,
    -203,    45,    63,  -145,  -181,   -66,    28,  -131,  -141,   110,
    -182,  -200,  -198,  -203,  -203,  -196,  -203,  -203,  -203,  -199,
    -194,  -197,  -203,  -203,  -203,  -203,  -195,  -193,  -203,  -203,
    -203,  -203,  -203,  -203,  -203,  -203,  -187,  -203,  -203,  -203,
    -203,  -203,  -203,  -203,  -203,  -191,  -203,  -203,  -203,  -203,
    -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,
    -203,  -183,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,
    -203,  -203,  -203,  -203,  -203,  -203,  -203,  -186,  -175,  -203,
    -203,  -203,  -201,  -185,  -158,  -203,  -153,  -203,  -178,  -203,
    -203,  -203,  -202,  -203,  -203,  -203,  -167,  -203,  -203,  -203,
    -203,  -166,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,
    -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,
    -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,
    -203,  -203,   146,  -203,  -203,  -203,  -203,  -203,  -203,  -203,
    -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -159,  -203,
    -203,  -203,  -154,  -203,  -168,  -203,  -203,  -171,  -203,  -203,
    -203,  -177,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,
    -203,  -169,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,
    -203,  -203,  -203,  -203,  -203
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint16 yytable[] =
{
     272,   349,   282,    30,   350,   352,   300,   351,   308,   354,
     317,   353,   355,   362,   330,   356,   338,   367,   346,   358,
       1,   272,   357,   282,   265,   266,   360,   300,   359,   308,
     363,   317,   237,   258,   259,   330,     4,   338,   361,   346,
     366,   375,   379,   383,   387,   292,   375,   379,   383,   387,
     395,   285,   286,   368,   394,   369,     5,   403,   364,   393,
     287,   392,   408,     7,   365,   400,   292,    10,   390,    43,
      44,    45,    46,    16,   391,    21,    22,    19,    23,    24,
      25,   371,    26,    27,    39,    40,   371,    23,    24,    23,
      24,    13,   397,   397,    14,   405,   406,    23,    24,    48,
     410,   411,   159,   160,   161,   162,    28,    71,    72,    21,
      22,   257,    23,    24,    25,    60,    26,    27,    56,   164,
     165,   166,   167,    73,    41,   169,   170,   171,   172,    21,
      22,   285,   286,   260,    25,   261,    26,    27,   673,    74,
      75,    76,    77,    91,    92,    93,    94,   285,   286,    58,
      28,    97,    98,    99,   100,    59,   468,   491,   311,    28,
     311,    28,    61,   508,   312,   285,   286,    62,   311,    28,
     260,   247,   261,   404,   248,   494,   479,   249,   409,   285,
     286,   469,   285,   286,    28,   285,   286,   247,    63,   533,
     248,   236,   550,   249,   291,    69,   250,   285,   286,   285,
     286,   265,   266,   174,    78,   242,   370,   255,   399,   267,
      79,   470,    95,   265,   266,   265,   266,    78,   480,   254,
     101,   482,   481,   271,   488,   485,   275,   276,   492,   402,
     490,   471,   495,   407,   277,   497,   265,   266,   483,   272,
     486,   503,   282,   500,   525,   484,   275,   276,   300,   501,
     509,   506,   308,   507,   514,   317,   512,   465,   275,   276,
     330,   520,   511,    80,   338,   526,   522,   487,   346,   532,
     285,   286,   375,   538,   379,   541,   383,   544,   387,   547,
     548,   528,   516,   546,   531,   493,   292,   543,   540,   519,
     607,    81,   472,   534,   609,   551,    82,   296,    83,   304,
     537,   265,   266,   103,   322,   326,   175,   334,   474,   342,
     489,   371,   535,   265,   266,   275,   276,   478,   296,   253,
     304,   281,   549,   397,   496,   322,   326,   608,   334,     0,
     342,   265,   266,   275,   276,   605,   606,   265,   266,     0,
     499,     0,   502,   265,   266,     0,   505,   275,   276,   275,
     276,     0,   510,   265,   266,     0,   513,     0,   515,   275,
     276,     0,   518,   275,   276,     0,   265,   266,   521,     0,
       0,   295,   272,   349,   282,   524,   350,   352,   300,   351,
     308,   354,   317,   353,   355,   362,   330,   356,   338,   367,
     346,   358,    30,   272,   357,   282,   275,   276,   360,   300,
     359,   308,   363,   317,     0,   527,     0,   330,     0,   338,
     361,   346,   366,   375,   379,   383,   387,   292,   375,   379,
     383,   387,   395,     0,     0,   368,   394,   369,   628,   629,
     364,   393,   632,   392,   634,   635,   365,   637,   292,   639,
     390,   641,   642,   643,   644,     0,   391,   265,   266,     0,
     265,   266,     0,   371,   247,     0,   530,   248,   371,   536,
     249,   265,   266,   660,   627,     0,   663,     0,   665,   666,
     539,   630,     0,   668,     0,   670,   671,   672,   265,   266,
       0,   640,   265,   266,   265,   266,     0,   542,     0,   275,
     276,   545,   299,   260,   683,   261,   685,   303,   262,   686,
       0,     0,   265,   266,   265,   266,   693,     0,   695,   696,
     307,     0,   316,   275,   276,   669,   702,     0,   704,     0,
     674,   321,   275,   276,   710,     0,   712,   265,   266,     0,
     325,     0,   718,     0,   720,   329,     0,     0,   296,   498,
     724,     0,   304,   504,   728,   275,   276,     0,   732,   322,
     326,   517,   736,   333,   334,   523,   740,     0,   342,   529,
     744,     0,     0,     0,   748,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   226,   227,   228,   229,   230,   231,   232,   233,   234,
     265,   266,   275,   276,   265,   266,   265,   266,   337,     0,
     341,     0,   345,     0,   374,   265,   266,   265,   266,   265,
     266,     0,     0,   378,     0,   382,     0,   386,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   296,
       0,   304,     0,     0,     0,     0,   322,   326,     0,   334,
       0,   342,     0,     0,     0,     0,     0,     0,     0,     0,
     296,     0,   304,     0,     0,     0,     0,   322,   326,     0,
     334,     0,   342,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   631,     0,   633,     0,     0,   636,     0,
     638,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   662,     0,   664,
       0,     0,     0,     0,   667,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   682,     0,   684,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   692,     0,   694,
       0,     0,     0,     0,     0,     0,     0,   701,     0,   703,
       0,     0,     0,     0,     0,   709,     0,   711,     0,     0,
       0,     0,     0,   717,     0,   719,     0,     0,     0,     0,
       0,   723,     0,     0,     0,   727,     0,     0,     0,   731,
       0,     0,     0,   735,     0,     0,     0,   739,     0,     0,
       0,   743,     0,     0,     0,   747,   552,   553,   554,   555,
     556,   557,   558,   559,   560,   561,   562,   563,   564,   565,
     566,   567,   568,   569,   570,   571,   572,   573,   574,   575,
     576,   577,   578,   579,   580,   581,   582,   583,   584,   585,
     586,   587,   588,   589,   590,   591,   592,   593,   594,   595,
     596,   597,   598,   599,   600,   601,   602,   603,   604,   233,
     234,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158
};

static const yytype_int16 yycheck[] =
{
     182,   201,   184,    18,   202,   204,   188,   203,   190,   206,
     192,   205,   207,   214,   196,   208,   198,   219,   200,   210,
       3,   203,   209,   205,    77,    78,   212,   209,   211,   211,
     215,   213,   163,   178,   179,   217,     0,   219,   213,   221,
     218,   223,   224,   225,   226,   186,   228,   229,   230,   231,
     232,    76,    77,   220,   231,   221,     4,   238,   216,   230,
      85,   229,   243,    82,   217,   234,   207,     5,   227,    24,
      25,    26,    27,     6,   228,     7,     8,    79,    10,    11,
      12,   222,    14,    15,    21,    22,   227,    10,    11,    10,
      11,    79,   233,   234,    82,   240,   241,    10,    11,    79,
     245,   246,    74,    75,    76,    77,    82,    62,    63,     7,
       8,   177,    10,    11,    12,    52,    14,    15,    87,    91,
      92,    93,    94,     1,    82,    97,    98,    99,   100,     7,
       8,    76,    77,    80,    12,    82,    14,    15,    83,    17,
      18,    19,    20,    17,    18,    19,    20,    76,    77,    85,
      82,    17,    18,    19,    20,    85,    88,    86,    81,    82,
      81,    82,    89,    86,    85,    76,    77,    89,    81,    82,
      80,    76,    82,   239,    79,    86,    86,    82,   244,    76,
      77,    86,    76,    77,    82,    76,    77,    76,    16,    86,
      79,   163,    86,    82,    85,    82,    85,    76,    77,    76,
      77,    77,    78,    13,    82,    87,    85,    82,    85,    85,
      88,   412,    86,    77,    78,    77,    78,    82,   418,   174,
      86,   419,    86,    85,   423,   421,    77,    78,   425,     9,
     424,    89,   427,   242,    85,   428,    77,    78,   420,   421,
     422,   432,   424,   430,   446,    86,    77,    78,   430,   431,
     436,   434,   434,   435,   439,   437,   438,   402,    77,    78,
     442,   443,   437,    65,   446,   447,   444,    86,   450,   451,
      76,    77,   454,   455,   456,   457,   458,   459,   460,   461,
     462,   448,   440,   460,   450,   426,   427,   458,   456,   442,
     471,    65,     9,   452,     9,   464,    65,   187,    65,   189,
     454,    77,    78,    68,   194,   195,   105,   197,   415,   199,
      86,   452,   453,    77,    78,    77,    78,   417,   208,   173,
     210,    85,   463,   464,    86,   215,   216,   472,   218,    -1,
     220,    77,    78,    77,    78,   466,   467,    77,    78,    -1,
      86,    -1,    86,    77,    78,    -1,    86,    77,    78,    77,
      78,    -1,    86,    77,    78,    -1,    86,    -1,    86,    77,
      78,    -1,    86,    77,    78,    -1,    77,    78,    86,    -1,
      -1,    85,   554,   573,   556,    86,   574,   576,   560,   575,
     562,   578,   564,   577,   579,   586,   568,   580,   570,   591,
     572,   582,   407,   575,   581,   577,    77,    78,   584,   581,
     583,   583,   587,   585,    -1,    86,    -1,   589,    -1,   591,
     585,   593,   590,   595,   596,   597,   598,   558,   600,   601,
     602,   603,   604,    -1,    -1,   592,   603,   593,   610,   611,
     588,   602,   614,   601,   616,   617,   589,   619,   579,   621,
     599,   623,   624,   625,   626,    -1,   600,    77,    78,    -1,
      77,    78,    -1,   594,    76,    -1,    86,    79,   599,    86,
      82,    77,    78,   645,   609,    -1,   648,    -1,   650,   651,
      86,   612,    -1,   655,    -1,   657,   658,   659,    77,    78,
      -1,   622,    77,    78,    77,    78,    -1,    86,    -1,    77,
      78,    86,    85,    80,   676,    82,   678,    85,    85,   681,
      -1,    -1,    77,    78,    77,    78,   688,    -1,   690,   691,
      85,    -1,    85,    77,    78,   656,   698,    -1,   700,    -1,
     661,    85,    77,    78,   706,    -1,   708,    77,    78,    -1,
      85,    -1,   714,    -1,   716,    85,    -1,    -1,   428,   429,
     722,    -1,   432,   433,   726,    77,    78,    -1,   730,   439,
     440,   441,   734,    85,   444,   445,   738,    -1,   448,   449,
     742,    -1,    -1,    -1,   746,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      77,    78,    77,    78,    77,    78,    77,    78,    85,    -1,
      85,    -1,    85,    -1,    85,    77,    78,    77,    78,    77,
      78,    -1,    -1,    85,    -1,    85,    -1,    85,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   559,
      -1,   561,    -1,    -1,    -1,    -1,   566,   567,    -1,   569,
      -1,   571,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     580,    -1,   582,    -1,    -1,    -1,    -1,   587,   588,    -1,
     590,    -1,   592,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   613,    -1,   615,    -1,    -1,   618,    -1,
     620,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   647,    -1,   649,
      -1,    -1,    -1,    -1,   654,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   675,    -1,   677,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   687,    -1,   689,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   697,    -1,   699,
      -1,    -1,    -1,    -1,    -1,   705,    -1,   707,    -1,    -1,
      -1,    -1,    -1,   713,    -1,   715,    -1,    -1,    -1,    -1,
      -1,   721,    -1,    -1,    -1,   725,    -1,    -1,    -1,   729,
      -1,    -1,    -1,   733,    -1,    -1,    -1,   737,    -1,    -1,
      -1,   741,    -1,    -1,    -1,   745,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,     3,    91,    92,     0,     4,    93,    82,    94,    95,
       5,    96,    98,    79,    82,    97,     6,    99,   103,    79,
     101,     7,     8,    10,    11,    12,    14,    15,    82,   104,
     105,   109,   110,   121,   130,   134,   137,   162,   100,   162,
     162,    82,   161,   161,   161,   161,   161,   106,    79,   102,
     111,   122,   107,   131,   135,   138,    87,   141,    85,    85,
     162,    89,    89,    16,   139,   142,   113,   124,   108,    82,
     165,   161,   161,     1,    17,    18,    19,    20,    82,    88,
     109,   130,   134,   137,   143,   144,   147,   151,   154,   158,
     163,    17,    18,    19,    20,    86,   114,    17,    18,    19,
      20,    86,   125,   141,   132,   136,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,   166,
     166,   166,   166,   159,   166,   166,   166,   166,   112,   166,
     166,   166,   166,   123,    13,   139,   145,   148,   155,   152,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,   160,   166,   167,   115,   116,
     119,   117,    87,   126,   127,   129,   128,    76,    79,    82,
      85,   140,   242,   292,   161,    82,   164,   165,   163,   163,
      80,    82,    85,   171,   266,    77,    78,    85,   170,   172,
     268,    85,   170,   175,   270,    77,    78,    85,   169,   179,
     272,    85,   170,   180,   274,    76,    77,    85,   168,   181,
     276,    85,   168,   186,   278,    85,   169,   187,   280,    85,
     170,   196,   282,    85,   169,   205,   284,    85,   170,   221,
     286,    81,    85,   105,   237,   288,    85,   170,   238,   290,
     292,    85,   169,   243,   294,    85,   169,   244,   296,    85,
     170,   246,   298,    85,   169,   248,   300,    85,   170,   252,
     302,    85,   169,   256,   304,    85,   170,   261,   306,   171,
     172,   175,   179,   180,   181,   186,   187,   196,   205,   221,
     237,   238,   242,   243,   244,   246,   248,   252,   256,   261,
      85,   168,   308,   333,    85,   170,   312,   335,    85,   170,
     314,   337,    85,   170,   317,   339,    85,   170,   321,   341,
     308,   312,   314,   317,   321,   170,   325,   168,   331,    85,
     331,   343,     9,   164,   165,   163,   163,   103,   164,   165,
     163,   163,   293,   133,   146,   149,   156,   153,   267,   269,
     173,   271,   176,   273,   275,   277,   182,   279,   281,   188,
     283,   197,   285,   206,   287,   222,   289,   291,   239,   295,
     297,   245,   299,   247,   301,   249,   303,   253,   305,   257,
     307,   262,   334,   309,   336,   313,   338,   315,   340,   318,
     342,   322,   326,   332,   344,   163,   120,   118,    88,    86,
     242,    89,     9,   150,   150,   157,   166,   167,   157,    86,
     171,    86,   172,   170,    86,   175,   170,    86,   179,    86,
     180,    86,   181,   168,    86,   186,    86,   187,   169,    86,
     196,   170,    86,   205,   169,    86,   221,   170,    86,   237,
      86,   238,   170,    86,   243,    86,   244,   169,    86,   246,
     170,    86,   248,   169,    86,   252,   170,    86,   256,   169,
      86,   261,   170,    86,   308,   168,    86,   312,   170,    86,
     314,   170,    86,   317,   170,    86,   321,   170,   170,   168,
      86,   331,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,   167,   167,   164,   163,     9,
     174,   177,   183,   189,   198,   207,   223,   240,   250,   254,
     258,   263,   310,   316,   319,   323,   327,   163,   170,   170,
     168,   169,   170,   169,   170,   170,   169,   170,   169,   170,
     168,   170,   170,   170,   170,   178,   184,   190,   199,   208,
     224,   241,   251,   255,   259,   264,   311,   320,   324,   328,
     170,   185,   169,   170,   169,   170,   170,   169,   170,   168,
     170,   170,   170,    83,   168,   191,   200,   209,   225,   260,
     265,   329,   169,   170,   169,   170,   170,   192,   201,   210,
     226,   330,   169,   170,   169,   170,   170,   193,   202,   211,
     227,   169,   170,   169,   170,   194,   203,   212,   228,   169,
     170,   169,   170,   195,   204,   213,   229,   169,   170,   169,
     170,   214,   230,   169,   170,   215,   231,   169,   170,   216,
     232,   169,   170,   217,   233,   169,   170,   218,   234,   169,
     170,   219,   235,   169,   170,   220,   236,   169,   170
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
	  static_cast<union yyalloc *>( YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize)));
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
#line 205 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->verifyHeader((yyvsp[(1) - (1)].stringVal)); ;}
    break;

  case 5:
#line 209 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->profileElement((yyvsp[(2) - (2)].stringVal)); ;}
    break;

  case 10:
#line 223 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->componentElement((yyvsp[(2) - (2)].stringVal)); ;}
    break;

  case 15:
#line 240 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = (yyvsp[(2) - (2)].stringVal); ;}
    break;

  case 16:
#line 242 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->metaElement(SKEL->_tmpString1.c_str(), (yyvsp[(4) - (4)].stringVal)); ;}
    break;

  case 26:
#line 262 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginNode((yyvsp[(1) - (1)].stringVal), 0); ;}
    break;

  case 28:
#line 265 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = (yyvsp[(2) - (2)].stringVal); ;}
    break;

  case 29:
#line 266 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginNode((yyvsp[(4) - (4)].stringVal), SKEL->_tmpString1.c_str()); ;}
    break;

  case 31:
#line 269 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->use((yyvsp[(2) - (2)].stringVal)); ;}
    break;

  case 34:
#line 280 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginProto((yyvsp[(2) - (2)].stringVal)); ;}
    break;

  case 35:
#line 281 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endProtoInterface(); ;}
    break;

  case 36:
#line 282 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endProto(); ;}
    break;

  case 39:
#line 290 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 40:
#line 291 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginEventInDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); SKEL->endEventDecl(); ;}
    break;

  case 41:
#line 293 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 42:
#line 294 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginEventOutDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); SKEL->endEventDecl(); ;}
    break;

  case 43:
#line 296 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 44:
#line 297 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginFieldDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); SKEL->getLexer()->expectType((yyvsp[(2) - (4)].intVal)); ;}
    break;

  case 45:
#line 298 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endFieldDecl(); ;}
    break;

  case 46:
#line 300 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 47:
#line 301 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginExposedFieldDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); SKEL->getLexer()->expectType((yyvsp[(2) - (4)].intVal)); ;}
    break;

  case 48:
#line 302 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endExposedFieldDecl(); ;}
    break;

  case 49:
#line 305 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginExternProto((yyvsp[(2) - (2)].stringVal)); ;}
    break;

  case 50:
#line 306 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endExternProtoInterface(); ;}
    break;

  case 51:
#line 307 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endExternProto(); ;}
    break;

  case 54:
#line 315 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 55:
#line 316 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->addExternEventInDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); ;}
    break;

  case 56:
#line 318 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 57:
#line 319 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->addExternEventOutDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); ;}
    break;

  case 58:
#line 321 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 59:
#line 322 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->addExternFieldDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); ;}
    break;

  case 60:
#line 324 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 61:
#line 325 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->addExternExposedFieldDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); ;}
    break;

  case 62:
#line 329 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = (yyvsp[(2) - (2)].stringVal); ;}
    break;

  case 63:
#line 331 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString2 = (yyvsp[(5) - (5)].stringVal); ;}
    break;

  case 64:
#line 333 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString3 = (yyvsp[(8) - (8)].stringVal); ;}
    break;

  case 65:
#line 336 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->addRoute(SKEL->_tmpString1.c_str(), SKEL->_tmpString2.c_str(), SKEL->_tmpString3.c_str(), (yyvsp[(11) - (11)].stringVal)); ;}
    break;

  case 66:
#line 340 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = (yyvsp[(2) - (2)].stringVal); ;}
    break;

  case 67:
#line 342 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString2 = (yyvsp[(5) - (5)].stringVal); ;}
    break;

  case 68:
#line 344 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        if ((yyvsp[(7) - (7)].stringVal) != 0)
            SKEL->importElement(SKEL->_tmpString1.c_str(), SKEL->_tmpString2.c_str(), (yyvsp[(7) - (7)].stringVal));
        else
            SKEL->importElement(SKEL->_tmpString1.c_str(), SKEL->_tmpString2.c_str(), 0);
    ;}
    break;

  case 69:
#line 353 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = (yyvsp[(2) - (2)].stringVal); ;}
    break;

  case 70:
#line 355 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        if ((yyvsp[(4) - (4)].stringVal) != 0)
            SKEL->exportElement(SKEL->_tmpString1.c_str(), (yyvsp[(4) - (4)].stringVal));
        else
            SKEL->exportElement(SKEL->_tmpString1.c_str(), 0);
    ;}
    break;

  case 71:
#line 364 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { (yyval.stringVal) = (yyvsp[(2) - (2)].stringVal); ;}
    break;

  case 72:
#line 365 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { (yyval.stringVal) = 0; ;}
    break;

  case 74:
#line 371 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endNode(); ;}
    break;

  case 83:
#line 387 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 84:
#line 388 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginEventInDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); ;}
    break;

  case 85:
#line 389 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endEventDecl(); ;}
    break;

  case 86:
#line 393 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 87:
#line 394 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginEventOutDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); ;}
    break;

  case 88:
#line 395 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endEventDecl(); ;}
    break;

  case 90:
#line 399 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->is((yyvsp[(2) - (2)].stringVal)); ;}
    break;

  case 91:
#line 403 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 92:
#line 404 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginFieldDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); SKEL->getLexer()->expectType((yyvsp[(2) - (4)].intVal)); ;}
    break;

  case 93:
#line 405 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endFieldDecl(); ;}
    break;

  case 94:
#line 409 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 95:
#line 410 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginExposedFieldDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); SKEL->getLexer()->expectType((yyvsp[(2) - (4)].intVal)); ;}
    break;

  case 96:
#line 411 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endExposedFieldDecl(); ;}
    break;

  case 98:
#line 415 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->is((yyvsp[(3) - (3)].stringVal)); ;}
    break;

  case 99:
#line 419 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        Int32 iFieldTypeId = SKEL->getFieldType((yyvsp[(1) - (1)].stringVal));
        if (SKEL->getMapFieldTypes() == true)
            iFieldTypeId = SKEL->mapExtIntFieldType((yyvsp[(1) - (1)].stringVal), iFieldTypeId);
        SKEL->getLexer()->expectType(iFieldTypeId);
        SKEL->beginField((yyvsp[(1) - (1)].stringVal), iFieldTypeId);
    ;}
    break;

  case 100:
#line 426 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endField(); ;}
    break;

  case 106:
#line 434 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->is((yyvsp[(3) - (3)].stringVal)); ;}
    break;

  case 220:
#line 566 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { (yyval.intVal) = (yyvsp[(1) - (1)].intVal); ;}
    break;

  case 221:
#line 567 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { (yyval.intVal) = (yyvsp[(1) - (1)].intVal); ;}
    break;

  case 222:
#line 570 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { (yyval.doubleVal) = (yyvsp[(1) - (1)].intVal); ;}
    break;

  case 223:
#line 571 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { (yyval.doubleVal) = (yyvsp[(1) - (1)].doubleVal); ;}
    break;

  case 224:
#line 574 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { (yyval.floatVal) = static_cast<float>((yyvsp[(1) - (1)].intVal)); ;}
    break;

  case 225:
#line 575 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { (yyval.floatVal) = static_cast<float>((yyvsp[(1) - (1)].doubleVal)); ;}
    break;

  case 226:
#line 579 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->addBoolValue((yyvsp[(1) - (1)].boolVal));
    ;}
    break;

  case 227:
#line 582 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->addFieldValue((yyvsp[(1) - (1)].stringVal)); ;}
    break;

  case 228:
#line 585 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 229:
#line 586 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 230:
#line 588 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addColorValue(Color3f((yyvsp[(1) - (5)].floatVal), (yyvsp[(3) - (5)].floatVal), (yyvsp[(5) - (5)].floatVal)));
    ;}
    break;

  case 231:
#line 594 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 232:
#line 595 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 233:
#line 596 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 234:
#line 598 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addColorRGBAValue(Color4f((yyvsp[(1) - (7)].floatVal), (yyvsp[(3) - (7)].floatVal), (yyvsp[(5) - (7)].floatVal), (yyvsp[(7) - (7)].floatVal)));
    ;}
    break;

  case 235:
#line 605 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->addDoubleValue((yyvsp[(1) - (1)].doubleVal));
    ;}
    break;

  case 236:
#line 611 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->addFloatValue((yyvsp[(1) - (1)].floatVal));
    ;}
    break;

  case 237:
#line 616 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 238:
#line 617 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 239:
#line 619 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->beginImage((yyvsp[(1) - (5)].intVal), (yyvsp[(3) - (5)].intVal), (yyvsp[(5) - (5)].intVal));
    ;}
    break;

  case 240:
#line 624 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->endImage();
    ;}
    break;

  case 241:
#line 630 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->addImagePixel((yyvsp[(2) - (2)].intVal));
    ;}
    break;

  case 243:
#line 637 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->addInt32Value((yyvsp[(1) - (1)].intVal));
    ;}
    break;

  case 244:
#line 642 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 245:
#line 643 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 246:
#line 644 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 247:
#line 645 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 248:
#line 646 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 249:
#line 647 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 250:
#line 648 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 251:
#line 649 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 252:
#line 651 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addMatrix3dValue(
            (yyvsp[(1) - (17)].doubleVal),  (yyvsp[(7) - (17)].doubleVal), (yyvsp[(13) - (17)].doubleVal),
            (yyvsp[(3) - (17)].doubleVal),  (yyvsp[(9) - (17)].doubleVal), (yyvsp[(15) - (17)].doubleVal),
            (yyvsp[(5) - (17)].doubleVal), (yyvsp[(11) - (17)].doubleVal), (yyvsp[(17) - (17)].doubleVal));
    ;}
    break;

  case 253:
#line 660 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 254:
#line 661 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 255:
#line 662 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 256:
#line 663 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 257:
#line 664 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 258:
#line 665 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 259:
#line 666 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 260:
#line 667 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 261:
#line 669 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addMatrix3fValue(
            (yyvsp[(1) - (17)].floatVal),  (yyvsp[(7) - (17)].floatVal), (yyvsp[(13) - (17)].floatVal),
            (yyvsp[(3) - (17)].floatVal),  (yyvsp[(9) - (17)].floatVal), (yyvsp[(15) - (17)].floatVal),
            (yyvsp[(5) - (17)].floatVal), (yyvsp[(11) - (17)].floatVal), (yyvsp[(17) - (17)].floatVal));
    ;}
    break;

  case 262:
#line 678 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 263:
#line 679 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 264:
#line 680 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 265:
#line 681 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 266:
#line 682 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 267:
#line 683 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 268:
#line 684 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 269:
#line 685 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 270:
#line 686 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 271:
#line 687 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 272:
#line 688 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 273:
#line 689 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 274:
#line 690 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 275:
#line 691 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 276:
#line 692 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 277:
#line 694 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addMatrix4dValue(Matrix4d(
            (yyvsp[(1) - (31)].doubleVal),  (yyvsp[(9) - (31)].doubleVal), (yyvsp[(17) - (31)].doubleVal), (yyvsp[(25) - (31)].doubleVal),
            (yyvsp[(3) - (31)].doubleVal), (yyvsp[(11) - (31)].doubleVal), (yyvsp[(19) - (31)].doubleVal), (yyvsp[(27) - (31)].doubleVal),
            (yyvsp[(5) - (31)].doubleVal), (yyvsp[(13) - (31)].doubleVal), (yyvsp[(21) - (31)].doubleVal), (yyvsp[(29) - (31)].doubleVal),
            (yyvsp[(7) - (31)].doubleVal), (yyvsp[(15) - (31)].doubleVal), (yyvsp[(23) - (31)].doubleVal), (yyvsp[(31) - (31)].doubleVal)));
    ;}
    break;

  case 278:
#line 704 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 279:
#line 705 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 280:
#line 706 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 281:
#line 707 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 282:
#line 708 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 283:
#line 709 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 284:
#line 710 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 285:
#line 711 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 286:
#line 712 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 287:
#line 713 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 288:
#line 714 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 289:
#line 715 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 290:
#line 716 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 291:
#line 717 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 292:
#line 718 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 293:
#line 720 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addMatrix4fValue(Matrix4f(
            (yyvsp[(1) - (31)].floatVal),  (yyvsp[(9) - (31)].floatVal), (yyvsp[(17) - (31)].floatVal), (yyvsp[(25) - (31)].floatVal),
            (yyvsp[(3) - (31)].floatVal), (yyvsp[(11) - (31)].floatVal), (yyvsp[(19) - (31)].floatVal), (yyvsp[(27) - (31)].floatVal),
            (yyvsp[(5) - (31)].floatVal), (yyvsp[(13) - (31)].floatVal), (yyvsp[(21) - (31)].floatVal), (yyvsp[(29) - (31)].floatVal),
            (yyvsp[(7) - (31)].floatVal), (yyvsp[(15) - (31)].floatVal), (yyvsp[(23) - (31)].floatVal), (yyvsp[(31) - (31)].floatVal)));
    ;}
    break;

  case 295:
#line 731 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->nullNode(); ;}
    break;

  case 296:
#line 734 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 297:
#line 735 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 298:
#line 736 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 299:
#line 738 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addRotationValue(Vec3f((yyvsp[(1) - (7)].floatVal), (yyvsp[(3) - (7)].floatVal), (yyvsp[(5) - (7)].floatVal)), (yyvsp[(7) - (7)].floatVal));
    ;}
    break;

  case 300:
#line 745 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->addStringValue((yyvsp[(1) - (1)].stringVal));
    ;}
    break;

  case 301:
#line 749 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { /* Not VRML conformant */
        SKEL->addStringValue((yyvsp[(1) - (1)].stringVal));
    ;}
    break;

  case 302:
#line 753 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { /* Not VRML conformant */
        SKEL->addBufferAsStringValue();
    ;}
    break;

  case 303:
#line 759 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->addTimeValue((yyvsp[(1) - (1)].doubleVal));
    ;}
    break;

  case 304:
#line 764 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 305:
#line 766 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addVec2dValue(Vec2d((yyvsp[(1) - (3)].doubleVal), (yyvsp[(3) - (3)].doubleVal)));
    ;}
    break;

  case 306:
#line 772 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 307:
#line 774 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addVec2fValue(Vec2f((yyvsp[(1) - (3)].floatVal), (yyvsp[(3) - (3)].floatVal)));
    ;}
    break;

  case 308:
#line 780 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 309:
#line 781 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 310:
#line 782 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 311:
#line 783 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addVec3dValue(Vec3d((yyvsp[(1) - (6)].doubleVal), (yyvsp[(3) - (6)].doubleVal), (yyvsp[(5) - (6)].doubleVal)));
    ;}
    break;

  case 312:
#line 789 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 313:
#line 790 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 314:
#line 791 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 315:
#line 792 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addVec3fValue(Vec3f((yyvsp[(1) - (6)].floatVal), (yyvsp[(3) - (6)].floatVal), (yyvsp[(5) - (6)].floatVal)));
    ;}
    break;

  case 316:
#line 798 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 317:
#line 799 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 318:
#line 800 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 319:
#line 801 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 320:
#line 802 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addVec4dValue(Vec4d((yyvsp[(1) - (8)].doubleVal), (yyvsp[(3) - (8)].doubleVal), (yyvsp[(5) - (8)].doubleVal), (yyvsp[(7) - (8)].doubleVal)));
    ;}
    break;

  case 321:
#line 808 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 322:
#line 809 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 323:
#line 810 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 324:
#line 811 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 325:
#line 812 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addVec4fValue(Vec4f((yyvsp[(1) - (8)].floatVal), (yyvsp[(3) - (8)].floatVal), (yyvsp[(5) - (8)].floatVal), (yyvsp[(7) - (8)].floatVal)));
    ;}
    break;

  case 410:
#line 988 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 411:
#line 989 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 412:
#line 990 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 413:
#line 992 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addColor4iValue(Color4ub(static_cast<UInt8>((yyvsp[(1) - (7)].intVal)), static_cast<UInt8>((yyvsp[(3) - (7)].intVal)),
                                       static_cast<UInt8>((yyvsp[(5) - (7)].intVal)), static_cast<UInt8>((yyvsp[(7) - (7)].intVal))));
    ;}
    break;

  case 414:
#line 999 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 415:
#line 1001 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addPnt2fValue(Pnt2f((yyvsp[(1) - (3)].floatVal), (yyvsp[(3) - (3)].floatVal)));
    ;}
    break;

  case 416:
#line 1007 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 417:
#line 1008 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 418:
#line 1010 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addPnt3fValue(Pnt3f((yyvsp[(1) - (5)].floatVal), (yyvsp[(3) - (5)].floatVal), (yyvsp[(5) - (5)].floatVal)));
    ;}
    break;

  case 419:
#line 1016 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 420:
#line 1017 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 421:
#line 1018 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 422:
#line 1020 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addPnt4fValue(Pnt4f((yyvsp[(1) - (7)].floatVal), (yyvsp[(3) - (7)].floatVal), (yyvsp[(5) - (7)].floatVal), (yyvsp[(7) - (7)].floatVal)));
    ;}
    break;

  case 423:
#line 1026 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 424:
#line 1027 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 425:
#line 1028 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 426:
#line 1030 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addPlaneValue(Plane(Vec3f((yyvsp[(1) - (7)].floatVal), (yyvsp[(3) - (7)].floatVal), (yyvsp[(5) - (7)].floatVal)), (yyvsp[(7) - (7)].floatVal)));
    ;}
    break;

  case 427:
#line 1036 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 428:
#line 1037 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 429:
#line 1038 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 430:
#line 1039 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 431:
#line 1040 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 432:
#line 1042 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        BoxVolume bv((yyvsp[(1) - (11)].floatVal), (yyvsp[(3) - (11)].floatVal), (yyvsp[(5) - (11)].floatVal), (yyvsp[(7) - (11)].floatVal), (yyvsp[(9) - (11)].floatVal), (yyvsp[(11) - (11)].floatVal));
        
        SKEL->addVolumeValue(bv);
    ;}
    break;

  case 433:
#line 1050 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 434:
#line 1052 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addVec2iValue(Vec2i((yyvsp[(1) - (3)].intVal), (yyvsp[(3) - (3)].intVal)));
    ;}
    break;


/* Line 1267 of yacc.c.  */
#line 3416 "build.linux.g++/type-debug--arch-x64/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.cpp"
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


#line 1105 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"


int OSGScanParseSkel_lex(YYSTYPE *lvalp, void *pSkel)
{
    return SKEL->lex(lvalp);
}

