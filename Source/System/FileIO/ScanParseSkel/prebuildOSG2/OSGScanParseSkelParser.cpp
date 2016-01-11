/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1


/* Substitute the variable and function names.  */
#define yyparse         OSGScanParseSkel_parse
#define yylex           OSGScanParseSkel_lex
#define yyerror         OSGScanParseSkel_error
#define yydebug         OSGScanParseSkel_debug
#define yynerrs         OSGScanParseSkel_nerrs


/* Copy the first part of user declarations.  */

#line 73 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "OSGScanParseSkelParser.hpp".  */
#ifndef YY_OSGSCANPARSESKEL_HOME_GERRIT_PROJECTS_OPENSG_SVN_OPENSG_BUILD_BUILD_OSGSYSTEM_OSGSCANPARSESKELPARSER_HPP_INCLUDED
# define YY_OSGSCANPARSESKEL_HOME_GERRIT_PROJECTS_OPENSG_SVN_OPENSG_BUILD_BUILD_OSGSYSTEM_OSGSCANPARSESKELPARSER_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int OSGScanParseSkel_debug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
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
    TOK_SFVec3i = 330,
    TOK_MFVec2i = 331,
    TOK_hex = 332,
    TOK_int32 = 333,
    TOK_double = 334,
    TOK_string = 335,
    TOK_bool = 336,
    TOK_NULL = 337,
    TOK_Id = 338,
    TOK_ImageFinished = 339,
    TOK_Error = 340,
    TOK_ClusterLocal = 341,
    TOK_ThreadLocal = 342
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 41 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:355  */

    long intVal;
    double doubleVal;
    float floatVal;
    const char *stringVal;
    bool boolVal;

#line 209 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int OSGScanParseSkel_parse (void *pSkel);

#endif /* !YY_OSGSCANPARSESKEL_HOME_GERRIT_PROJECTS_OPENSG_SVN_OPENSG_BUILD_BUILD_OSGSYSTEM_OSGSCANPARSESKELPARSER_HPP_INCLUDED  */

/* Copy the second part of user declarations.  */
#line 49 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:358  */


#if __GNUC__ >= 4 || __GNUC_MINOR__ >=3
#pragma GCC diagnostic warning "-Wold-style-cast"
#endif

//#define YYPARSE_PARAM pSkel
//#define YYLEX_PARAM   pSkel

#define OSGScanParseSkel_error SKEL->handleError

#include "OSGConfig.h"
#include "OSGBaseFunctions.h"
#include "OSGMatrix.h"
#include "OSGScanParseLexer.h"
#include "OSGScanParseSkel.h"

#include <iostream>

#if defined(OSG_LINUX_ICC) || defined(OSG_WIN32_ICL)
#pragma warning( disable : 193 810 177 )
#endif

OSG_USING_NAMESPACE

#ifdef OSG_USE_OSG2_NAMESPACE
#define OSGScanParseSkel_lex OSG2ScanParseSkel_lex
#endif

int OSGScanParseSkel_lex(YYSTYPE *lvalp, void *);

#define SKEL (static_cast<ScanParseSkel *>(pSkel))

#if(!defined(__GNUC__) && defined(__ICL) && __INTEL_COMPILER_VERSION >= 900)
# define alloca(size)   __builtin_alloca (size)
#endif


#line 261 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:358  */

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
#else
typedef signed char yytype_int8;
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
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
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
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   988

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  93
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  266
/* YYNRULES -- Number of rules.  */
#define YYNRULES  475
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  774

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   342

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,    92,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    88,     2,    89,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    90,     2,    91,     2,     2,     2,     2,
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
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   214,   214,   221,   222,   225,   226,   229,   232,   233,
     237,   242,   243,   250,   251,   256,   254,   261,   264,   267,
     268,   271,   272,   273,   274,   275,   290,   293,   290,   298,
     301,   302,   297,   306,   310,   311,   314,   315,   318,   319,
     322,   323,   330,   331,   330,   335,   336,   340,   339,   343,
     342,   346,   347,   345,   350,   351,   349,   355,   356,   355,
     360,   361,   365,   364,   368,   367,   371,   370,   374,   373,
     379,   381,   383,   378,   390,   392,   389,   403,   402,   413,
     415,   418,   421,   424,   425,   428,   429,   430,   431,   432,
     433,   437,   438,   436,   443,   444,   442,   447,   449,   453,
     454,   452,   457,   458,   456,   472,   473,   471,   477,   478,
     482,   481,   490,   491,   492,   493,   496,   497,   500,   503,
     506,   509,   512,   515,   516,   517,   518,   519,   520,   521,
     522,   523,   524,   525,   526,   527,   528,   529,   530,   531,
     532,   533,   534,   535,   536,   537,   538,   539,   540,   541,
     542,   543,   544,   545,   546,   547,   548,   549,   550,   551,
     552,   553,   554,   555,   556,   558,   559,   560,   561,   562,
     563,   564,   565,   566,   567,   568,   571,   572,   573,   574,
     575,   576,   577,   578,   579,   580,   581,   582,   583,   584,
     585,   586,   587,   588,   589,   590,   591,   592,   593,   594,
     595,   596,   597,   598,   599,   600,   601,   602,   603,   604,
     605,   606,   607,   608,   609,   610,   611,   612,   614,   615,
     616,   617,   618,   619,   620,   621,   622,   623,   624,   625,
     626,   627,   630,   631,   634,   635,   638,   639,   642,   646,
     649,   650,   649,   658,   659,   660,   658,   668,   674,   680,
     681,   683,   680,   693,   697,   700,   706,   707,   708,   709,
     710,   711,   712,   713,   706,   724,   725,   726,   727,   728,
     729,   730,   731,   724,   742,   743,   744,   745,   746,   747,
     748,   749,   750,   751,   752,   753,   754,   755,   756,   742,
     768,   769,   770,   771,   772,   773,   774,   775,   776,   777,
     778,   779,   780,   781,   782,   768,   794,   795,   798,   799,
     800,   798,   808,   812,   816,   820,   826,   832,   832,   840,
     840,   848,   849,   850,   848,   857,   858,   859,   857,   866,
     867,   868,   869,   866,   876,   877,   878,   879,   876,   886,
     887,   890,   891,   894,   895,   898,   899,   902,   903,   906,
     907,   910,   911,   914,   915,   918,   919,   922,   923,   926,
     927,   930,   931,   934,   935,   938,   939,   942,   943,   946,
     947,   950,   951,   954,   955,   958,   959,   962,   963,   966,
     967,   970,   971,   974,   975,   978,   979,   982,   983,   986,
     987,   990,   991,   994,   995,   998,   999,  1002,  1003,  1006,
    1007,  1010,  1011,  1014,  1015,  1018,  1019,  1022,  1023,  1026,
    1027,  1030,  1031,  1034,  1035,  1038,  1039,  1042,  1043,  1046,
    1047,  1050,  1051,  1056,  1057,  1058,  1056,  1067,  1067,  1075,
    1076,  1075,  1084,  1085,  1086,  1084,  1094,  1095,  1096,  1094,
    1104,  1105,  1106,  1107,  1108,  1109,  1104,  1121,  1121,  1129,
    1131,  1129,  1141,  1142,  1145,  1146,  1149,  1150,  1153,  1154,
    1157,  1158,  1161,  1162,  1165,  1166,  1169,  1170,  1173,  1174,
    1177,  1178,  1181,  1182,  1185,  1186
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
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
  "TOK_SFVolume", "TOK_SFVec2i", "TOK_SFVec3i", "TOK_MFVec2i", "TOK_hex",
  "TOK_int32", "TOK_double", "TOK_string", "TOK_bool", "TOK_NULL",
  "TOK_Id", "TOK_ImageFinished", "TOK_Error", "TOK_ClusterLocal",
  "TOK_ThreadLocal", "'['", "']'", "'{'", "'}'", "'.'", "$accept",
  "x3dScene", "headerStatement", "profileStatement", "profileNameId",
  "componentStatements", "componentStatement", "componentNameId",
  "metaStatements", "metaStatement", "$@1", "metakey", "metavalue",
  "statements", "statement", "nodeStatement", "$@2", "$@3", "$@4", "$@5",
  "$@6", "nodeOptionStatement", "nodeOptions", "nodeOption",
  "protoStatement", "proto", "$@7", "$@8", "interfaceDeclarations",
  "interfaceDeclaration", "$@9", "$@10", "$@11", "$@12", "$@13", "$@14",
  "externproto", "$@15", "$@16", "externInterfaceDeclarations",
  "externInterfaceDeclaration", "$@17", "$@18", "$@19", "$@20",
  "routeStatement", "$@21", "$@22", "$@23", "importStatement", "$@24",
  "$@25", "exportStatement", "$@26", "asStatement", "URLList", "node",
  "scriptBody", "scriptBodyElement", "eventInDeclaration", "$@27", "$@28",
  "eventOutDeclaration", "$@29", "$@30", "eventDeclarationEnd",
  "fieldDeclaration", "$@31", "$@32", "$@33", "$@34",
  "exposedFieldDeclaration", "$@35", "$@36", "fieldDeclarationEnd",
  "nodeBodyElement", "$@37", "fieldEnd", "nodeNameId", "nodeTypeId",
  "fieldId", "eventInId", "eventOutId", "fieldType", "fieldValue", "int32",
  "double", "float", "sfboolValue", "sfcolorValue", "$@38", "$@39",
  "sfcolorRGBAValue", "$@40", "$@41", "$@42", "sfdoubleValue",
  "sffloatValue", "sfimageValue", "$@43", "$@44", "$@45", "pixels",
  "sfint32Value", "sfmatrix3dValue", "$@46", "$@47", "$@48", "$@49",
  "$@50", "$@51", "$@52", "$@53", "sfmatrix3fValue", "$@54", "$@55",
  "$@56", "$@57", "$@58", "$@59", "$@60", "$@61", "sfmatrix4dValue",
  "$@62", "$@63", "$@64", "$@65", "$@66", "$@67", "$@68", "$@69", "$@70",
  "$@71", "$@72", "$@73", "$@74", "$@75", "$@76", "sfmatrix4fValue",
  "$@77", "$@78", "$@79", "$@80", "$@81", "$@82", "$@83", "$@84", "$@85",
  "$@86", "$@87", "$@88", "$@89", "$@90", "$@91", "sfnodeValue",
  "sfrotationValue", "$@92", "$@93", "$@94", "sfstringValue",
  "sftimeValue", "sfvec2dValue", "$@95", "sfvec2fValue", "$@96",
  "sfvec3dValue", "$@97", "$@98", "$@99", "sfvec3fValue", "$@100", "$@101",
  "$@102", "sfvec4dValue", "$@103", "$@104", "$@105", "$@106",
  "sfvec4fValue", "$@107", "$@108", "$@109", "$@110", "mfboolValue",
  "sfboolValues", "mfcolorValue", "sfcolorValues", "mfcolorRGBAValue",
  "sfcolorRGBAValues", "mfdoubleValue", "sfdoubleValues", "mffloatValue",
  "sffloatValues", "mfimageValue", "sfimageValues", "mfint32Value",
  "sfint32Values", "mfmatrix3dValue", "sfmatrix3dValues",
  "mfmatrix3fValue", "sfmatrix3fValues", "mfmatrix4dValue",
  "sfmatrix4dValues", "mfmatrix4fValue", "sfmatrix4fValues", "mfnodeValue",
  "sfnodeValues", "mfrotationValue", "sfrotationValues", "mfstringValue",
  "sfstringValues", "mftimeValue", "sftimeValues", "mfvec2dValue",
  "sfvec2dValues", "mfvec2fValue", "sfvec2fValues", "mfvec3dValue",
  "sfvec3dValues", "mfvec3fValue", "sfvec3fValues", "mfvec4dValue",
  "sfvec4dValues", "mfvec4fValue", "sfvec4fValues", "sfcolor4iValue",
  "$@111", "$@112", "$@113", "sfpnt2fValue", "$@114", "sfpnt3fValue",
  "$@115", "$@116", "sfpnt4fValue", "$@117", "$@118", "$@119",
  "sfplaneValue", "$@120", "$@121", "$@122", "sfVolumeValue", "$@123",
  "$@124", "$@125", "$@126", "$@127", "$@128", "sfvec2iValue", "$@129",
  "sfvec3iValue", "$@130", "$@131", "mfcolor4iValue", "sfcolor4iValues",
  "mfpnt2fValue", "sfpnt2fValues", "mfpnt3fValue", "sfpnt3fValues",
  "mfpnt4fValue", "sfpnt4fValues", "mfplaneValue", "sfplaneValues",
  "mfvec2iValue", "sfvec2iValues", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
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
     335,   336,   337,   338,   339,   340,   341,   342,    91,    93,
     123,   125,    46
};
# endif

#define YYPACT_NINF -286

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-286)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      42,  -286,    36,    48,  -286,   -27,  -286,  -286,  -286,    68,
      18,  -286,    71,  -286,  -286,  -286,   -11,  -286,   177,  -286,
    -286,     6,     6,    14,    14,    14,    14,    14,  -286,  -286,
    -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,    26,  -286,
    -286,  -286,  -286,  -286,  -286,  -286,  -286,    30,  -286,  -286,
      35,    41,     6,    44,    58,   141,  -286,  -286,  -286,  -286,
    -286,    82,    14,    14,  -286,   549,    78,    63,   312,    30,
    -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,
     915,   915,   915,   915,  -286,  -286,   915,   915,   915,   915,
    -286,  -286,  -286,   119,   141,   123,  -286,  -286,  -286,  -286,
    -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,
    -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,
    -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,
    -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,
    -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,
    -286,  -286,  -286,    88,  -286,  -286,  -286,  -286,   261,    78,
      14,  -286,  -286,   915,   915,   915,   740,  -286,  -286,  -286,
    -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,
     100,    82,   103,   103,  -286,   100,    82,   103,   103,  -286,
    -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,
    -286,  -286,  -286,  -286,   803,  -286,  -286,  -286,  -286,  -286,
      64,  -286,  -286,  -286,  -286,    93,   111,   100,    82,   103,
     103,   103,   -30,   300,   324,   450,   454,    84,   116,   458,
     466,   471,   483,    51,   485,   261,   488,   490,   496,   502,
     507,   513,   518,   -55,    32,    32,    49,    32,    86,    86,
      49,    32,    49,    32,    98,    32,   533,    49,    49,    32,
      49,    32,    49,    32,   163,   524,   526,   544,   546,    86,
      32,    32,    32,    32,    86,    86,    86,   277,  -286,   181,
    -286,   859,   859,  -286,  -286,  -286,   100,  -286,  -286,  -286,
    -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,
    -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,
    -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,
    -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,
    -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,
    -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,
    -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,
    -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,
    -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,
    -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,
    -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,
    -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,
    -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,
    -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,
    -286,  -286,  -286,  -286,  -286,  -286,   103,   -30,   300,   324,
     450,   454,    84,   116,   458,   466,   471,   483,    51,   485,
     261,   488,   490,   496,   502,   507,   513,   518,   -55,    32,
      32,    49,    32,    86,    86,    49,    32,    49,    32,    98,
      32,   533,    49,    49,    32,    49,    32,    49,    32,   163,
     524,   526,   544,   546,    86,    32,    32,    32,    32,    86,
    -286,  -286,  -286,   186,   186,   803,   803,   803,   127,   278,
      32,   296,    32,   298,   302,     7,    86,   124,   317,    49,
     320,    32,   326,    49,   354,    32,    77,   373,    32,   381,
     385,    49,   387,    32,   389,    49,   393,    32,   405,    49,
     407,    32,   246,    86,   414,    32,   427,    32,   432,    32,
     435,    32,    32,    86,    86,   259,  -286,   103,  -286,  -286,
    -286,   198,  -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,
    -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,
    -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,
    -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,
    -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,
    -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,
    -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,
    -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,
     103,    32,    32,    86,    49,    32,    49,    32,    32,    49,
      32,    49,    32,    86,    32,    32,    32,    32,    86,  -286,
    -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,
    -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,    32,  -286,
      49,    32,    49,    32,    32,  -286,  -286,    49,    32,    86,
      32,    32,    32,  -286,    67,  -286,  -286,  -286,  -286,  -286,
    -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,    49,    32,
      49,    32,  -286,  -286,    32,  -286,  -286,  -286,  -286,  -286,
      49,    32,    49,    32,    32,  -286,  -286,  -286,  -286,  -286,
      49,    32,    49,    32,    32,  -286,  -286,  -286,  -286,  -286,
      49,    32,    49,    32,  -286,  -286,  -286,  -286,    49,    32,
      49,    32,  -286,  -286,  -286,  -286,    49,    32,  -286,  -286,
      49,    32,  -286,  -286,    49,    32,  -286,  -286,    49,    32,
    -286,  -286,    49,    32,  -286,  -286,    49,    32,  -286,  -286,
      49,    32,  -286,  -286
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       4,     3,     0,     6,     1,     0,     9,     7,     5,    14,
       0,     8,    20,    12,    11,    10,     0,    13,     2,    17,
      15,     0,     0,     0,     0,     0,     0,     0,   119,    19,
      21,    22,    40,    41,    23,    24,    25,    26,     0,    42,
      57,   118,    29,    33,    70,    74,    77,    35,    18,    16,
       0,     0,     0,     0,     0,    80,    37,    27,    46,    61,
      30,     0,     0,     0,    78,     0,     0,     0,     0,    35,
     122,    71,    75,    79,    38,    39,    34,    36,    84,    28,
       0,     0,     0,     0,    43,    45,     0,     0,     0,     0,
      58,    60,    31,     0,    80,     0,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   138,   139,   140,   141,   142,   143,   144,   145,   146,
     147,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     157,   158,   159,   160,   161,   162,   163,   164,   165,   166,
     167,   168,   169,   170,   171,   172,   173,   174,   175,    47,
      49,    54,    51,     0,    62,    64,    68,    66,     0,     0,
       0,    76,    90,     0,     0,     0,     0,   120,    82,   113,
     112,   114,   115,    83,    86,    87,    88,    89,    85,   110,
       0,     0,     0,     0,    20,     0,     0,     0,     0,   314,
     315,   312,   313,   394,    59,   391,    81,    32,    72,    91,
      94,   105,   102,    99,     0,   121,    48,    50,    55,    52,
       0,    63,    65,    69,    67,     0,     0,     0,     0,     0,
       0,     0,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   146,   147,   148,   149,   150,
     151,   152,   153,   154,   155,   156,   157,   158,   159,   160,
     161,   162,   163,   164,   165,   166,   167,   168,   169,   170,
     171,   172,   173,   174,   175,     0,     0,     0,   111,     0,
     116,     0,     0,    44,   392,   393,     0,    92,    95,   106,
     103,   100,   238,   239,   342,   339,   176,   236,   237,   346,
     240,   343,   177,   350,   243,   347,   178,   234,   235,   354,
     247,   351,   179,   358,   248,   355,   180,   232,   233,   362,
     249,   359,   181,   366,   255,   363,   182,   370,   256,   367,
     183,   374,   265,   371,   184,   378,   274,   375,   185,   382,
     290,   379,   186,   307,   386,   306,   383,   187,   390,   308,
     387,   188,   189,   398,   316,   395,   190,   402,   317,   399,
     191,   406,   319,   403,   192,   410,   321,   407,   193,   414,
     325,   411,   194,   418,   329,   415,   195,   422,   334,   419,
     196,   197,   198,   199,   200,   201,   202,   203,   204,   205,
     206,   207,   208,   209,   210,   211,   212,   213,   214,   215,
     216,   217,   455,   423,   452,   218,   459,   427,   456,   219,
     463,   429,   460,   220,   467,   432,   464,   221,   471,   436,
     468,   222,   223,   224,   225,   226,   227,   440,   228,   447,
     229,   449,   230,   475,   472,   231,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      56,    53,    73,    97,    97,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   117,     0,    93,    96,
     107,     0,   108,   104,   101,   340,   341,   344,   345,   241,
     348,   349,   244,   352,   353,   356,   357,   360,   361,   250,
     364,   365,   368,   369,   257,   372,   373,   266,   376,   377,
     275,   380,   381,   291,   384,   385,   388,   389,   309,   396,
     397,   400,   401,   318,   404,   405,   320,   408,   409,   322,
     412,   413,   326,   416,   417,   330,   420,   421,   335,   453,
     454,   424,   457,   458,   428,   461,   462,   430,   465,   466,
     433,   469,   470,   437,   441,   448,   450,   473,   474,    98,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   109,
     242,   245,   251,   258,   267,   276,   292,   310,   323,   327,
     331,   336,   425,   431,   434,   438,   442,   451,     0,   254,
       0,     0,     0,     0,     0,   324,   328,     0,     0,     0,
       0,     0,     0,   246,     0,   259,   268,   277,   293,   311,
     332,   337,   426,   435,   439,   443,   252,   253,     0,     0,
       0,     0,   333,   338,     0,   260,   269,   278,   294,   444,
       0,     0,     0,     0,     0,   261,   270,   279,   295,   445,
       0,     0,     0,     0,     0,   262,   271,   280,   296,   446,
       0,     0,     0,     0,   263,   272,   281,   297,     0,     0,
       0,     0,   264,   273,   282,   298,     0,     0,   283,   299,
       0,     0,   284,   300,     0,     0,   285,   301,     0,     0,
     286,   302,     0,     0,   287,   303,     0,     0,   288,   304,
       0,     0,   289,   305
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,
    -286,  -286,  -286,    25,  -286,    -5,  -286,  -286,  -286,  -286,
    -286,   159,  -286,  -286,   148,  -286,  -286,  -286,  -286,  -286,
    -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,
    -286,  -286,  -286,  -286,  -286,   171,  -286,  -286,  -286,   172,
    -286,  -286,   226,  -286,   233,  -286,   174,  -286,  -286,  -286,
    -286,  -286,  -286,  -286,  -286,  -147,  -286,  -286,  -286,  -286,
    -286,  -286,  -286,  -286,  -285,  -286,  -286,  -286,    40,    73,
    -128,  -160,   -69,    33,  -182,    76,   -83,  -224,  -138,  -137,
    -286,  -286,  -155,  -286,  -286,  -286,  -214,  -207,  -162,  -286,
    -286,  -286,  -286,  -181,  -180,  -286,  -286,  -286,  -286,  -286,
    -286,  -286,  -286,  -201,  -286,  -286,  -286,  -286,  -286,  -286,
    -286,  -286,  -240,  -286,  -286,  -286,  -286,  -286,  -286,  -286,
    -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,  -233,  -286,
    -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,
    -286,  -286,  -286,  -286,  -221,  -225,  -286,  -286,  -286,  -152,
    -223,  -220,  -286,  -254,  -286,  -245,  -286,  -286,  -286,  -244,
    -286,  -286,  -286,  -255,  -286,  -286,  -286,  -286,  -260,  -286,
    -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,
    -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,
    -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,   176,
    -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,
    -286,  -286,  -286,  -286,  -286,  -258,  -286,  -286,  -286,  -246,
    -286,  -252,  -286,  -286,  -263,  -286,  -286,  -286,  -269,  -286,
    -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,  -276,
    -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,
    -286,  -286,  -286,  -286,  -286,  -286
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     6,     8,     9,    11,    15,    12,    17,
      38,    20,    49,    18,    29,   345,    47,    66,    52,    69,
     159,    57,    65,    77,    31,    32,    50,   153,    67,    85,
     180,   181,   183,   282,   182,   281,    33,    51,   158,    68,
      91,   185,   186,   188,   187,    34,    53,    93,   216,    35,
      54,    94,    36,    55,    64,   194,    79,    95,   173,   174,
     217,   493,   175,   218,   494,   548,   176,   221,   497,   220,
     496,   177,   219,   495,   550,   178,   204,   278,    42,    37,
     179,   206,    71,   551,   552,   320,   310,   300,   295,   301,
     500,   631,   305,   502,   632,   668,   311,   315,   321,   506,
     633,   669,   684,   325,   329,   509,   634,   670,   698,   710,
     720,   730,   738,   333,   511,   635,   671,   699,   711,   721,
     731,   739,   337,   513,   636,   672,   700,   712,   722,   732,
     740,   746,   750,   754,   758,   762,   766,   770,   341,   515,
     637,   673,   701,   713,   723,   733,   741,   747,   751,   755,
     759,   763,   767,   771,   346,   350,   518,   638,   674,   195,
     355,   359,   521,   363,   523,   367,   525,   639,   675,   371,
     527,   640,   676,   375,   529,   641,   677,   702,   379,   531,
     642,   678,   703,   296,   498,   302,   499,   306,   501,   312,
     503,   316,   504,   322,   505,   326,   507,   330,   508,   334,
     510,   338,   512,   342,   514,   347,   516,   351,   517,   352,
     215,   356,   519,   360,   520,   364,   522,   368,   524,   372,
     526,   376,   528,   380,   530,   404,   533,   643,   679,   408,
     535,   412,   537,   644,   416,   539,   645,   680,   420,   541,
     646,   681,   428,   542,   647,   682,   704,   714,   724,   430,
     543,   432,   544,   648,   405,   532,   409,   534,   413,   536,
     417,   538,   421,   540,   435,   545
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint16 yytable[] =
{
     304,   434,   314,   401,   426,   397,   332,   400,   340,   425,
     349,   422,   390,    30,   362,   398,   370,   399,   378,   424,
     391,   304,   280,   314,   423,   211,   292,   332,   293,   340,
     393,   349,   384,   392,   395,   362,     4,   370,   396,   378,
     385,   407,   411,   415,   419,     1,   407,   411,   415,   419,
     389,   292,     5,   293,   208,   209,     7,   287,   294,   213,
     214,    23,    24,   285,    43,    44,    45,    46,   387,    19,
     388,    21,    22,    10,    23,    24,    25,    16,    26,    27,
      80,    81,    82,    83,   317,   318,   386,    23,    24,    28,
     383,   289,   290,   291,    39,    40,   567,    41,    13,   490,
     491,    14,    72,    73,   394,   381,    48,   382,    23,    24,
     297,   298,   207,   149,   150,   151,   152,   212,    56,   154,
     155,   156,   157,    58,   162,    60,   492,   307,   308,    59,
      21,    22,   160,   343,    28,    25,    61,    26,    27,   344,
     163,   164,   165,   166,   317,   318,   328,    28,   336,   288,
      62,   696,    84,   354,   358,   283,   366,    63,   374,   343,
      28,   317,   318,   317,   318,    70,   584,   328,    78,   336,
     189,   190,   319,   191,   354,   358,   192,   366,   184,   374,
     343,    28,   284,   205,    21,    22,   167,    23,    24,    25,
     436,    26,    27,   317,   318,   547,   199,   200,   201,   203,
     198,   317,   318,   286,   323,    30,   167,   630,   292,   210,
     293,   553,   554,   570,   168,   304,   555,   314,   401,   426,
     397,   332,   400,   340,   425,   349,   422,   390,    92,   362,
     398,   370,   399,   378,   424,   391,   304,   279,   314,   423,
     317,   318,   332,   169,   340,   393,   349,   384,   392,   395,
     362,   402,   370,   396,   378,   385,   407,   411,   415,   419,
      28,   407,   411,   415,   419,   389,   170,   171,   595,   628,
     607,   622,   579,   604,   610,   619,   559,   304,   562,   598,
     314,   582,   601,   387,   616,   388,   332,   577,   613,   564,
     340,   583,   587,   349,   588,   585,   590,   566,   362,   596,
     592,   386,   370,   602,   324,   383,   378,   608,   546,   576,
     407,   614,   411,   617,   415,   620,   419,   623,   624,   394,
     381,   172,   382,   317,   318,   324,   571,   161,   573,    86,
      87,    88,    89,   197,   196,   609,   317,   318,   189,   190,
     403,   191,     0,   568,   192,   403,   561,   549,   627,   193,
     427,   429,   431,   429,   317,   318,   297,   298,     0,     0,
     556,   328,   558,   336,     0,   433,     0,   557,   354,   358,
       0,   366,     0,   374,   297,   298,   307,   308,   297,   298,
     297,   298,   328,     0,   336,   560,     0,   563,   299,   354,
     358,   565,   366,     0,   374,   307,   308,     0,   297,   298,
       0,    90,   297,   298,   307,   308,   572,   650,   651,   575,
       0,   654,   303,   656,   657,   578,   659,     0,   661,   629,
     663,   664,   665,   666,     0,   328,   574,     0,     0,   336,
     580,     0,   297,   298,     0,     0,   354,   358,   593,     0,
       0,   366,   599,   581,   683,   374,   605,   686,     0,   688,
     689,   297,   298,     0,   691,     0,   693,   694,   695,   307,
     308,     0,   586,   307,   308,   297,   298,   307,   308,     0,
     589,   297,   298,     0,   591,   706,   594,   708,   597,     0,
     709,     0,   600,   307,   308,   297,   298,   716,     0,   718,
     719,     0,   297,   298,   603,     0,   606,   726,     0,   728,
     729,     0,   649,   612,     0,   297,   298,   735,     0,   737,
     297,   298,     0,   297,   298,   743,   615,   745,     0,   324,
       0,   618,     0,   749,   621,     0,     0,   753,   307,   308,
       0,   757,   297,   298,     0,   761,   307,   308,   309,   765,
     324,     0,   313,   769,   297,   298,   327,   773,     0,   307,
     308,   653,     0,   655,   331,   403,   658,     0,   660,   335,
     403,   297,   298,   297,   298,   427,   307,   308,   307,   308,
       0,   339,     0,   348,   297,   298,   353,     0,   357,     0,
     307,   308,   569,   324,   361,   297,   298,   685,     0,   687,
     365,   307,   308,     0,   690,   369,   297,   298,     0,     0,
       0,   373,   297,   298,   297,   298,   377,     0,   403,   611,
     189,   190,   406,   191,   410,   705,   192,   707,     0,   625,
     626,   429,   297,   298,   297,   298,     0,   715,     0,   717,
       0,     0,   414,     0,   418,    74,    75,   725,    76,   727,
       0,     0,     0,     0,     0,     0,     0,   734,     0,   736,
       0,     0,     0,     0,     0,   742,     0,   744,     0,     0,
       0,     0,     0,   748,     0,     0,     0,   752,     0,     0,
       0,   756,     0,     0,     0,   760,     0,     0,     0,   764,
       0,     0,     0,   768,     0,     0,     0,   772,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   652,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   662,
       0,     0,     0,     0,   667,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   692,     0,     0,     0,     0,
     697,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   202,   222,   223,   224,   225,   226,   227,
     228,   229,   230,   231,   232,   233,   234,   235,   236,   237,
     238,   239,   240,   241,   242,   243,   244,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,   263,   264,   265,   266,   267,
     268,   269,   270,   271,   272,   273,   274,   275,   276,   277,
     437,   438,   439,   440,   441,   442,   443,   444,   445,   446,
     447,   448,   449,   450,   451,   452,   453,   454,   455,   456,
     457,   458,   459,   460,   461,   462,   463,   464,   465,   466,
     467,   468,   469,   470,   471,   472,   473,   474,   475,   476,
     477,   478,   479,   480,   481,   482,   483,   484,   485,   486,
     487,   488,   489,   275,   276,   277,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148
};

static const yytype_int16 yycheck[] =
{
     224,   277,   226,   263,   273,   259,   230,   262,   232,   272,
     234,   269,   252,    18,   238,   260,   240,   261,   242,   271,
     253,   245,   204,   247,   270,   185,    81,   251,    83,   253,
     255,   255,   246,   254,   257,   259,     0,   261,   258,   263,
     247,   265,   266,   267,   268,     3,   270,   271,   272,   273,
     251,    81,     4,    83,   182,   183,    83,   217,    88,   187,
     188,    10,    11,   215,    24,    25,    26,    27,   249,    80,
     250,     7,     8,     5,    10,    11,    12,     6,    14,    15,
      17,    18,    19,    20,    77,    78,   248,    10,    11,    83,
     245,   219,   220,   221,    21,    22,    89,    83,    80,   281,
     282,    83,    62,    63,   256,   243,    80,   244,    10,    11,
      78,    79,   181,    80,    81,    82,    83,   186,    88,    86,
      87,    88,    89,    88,     1,    52,   286,    78,    79,    88,
       7,     8,    13,    82,    83,    12,    92,    14,    15,    88,
      17,    18,    19,    20,    77,    78,   229,    83,   231,   218,
      92,    84,    89,   236,   237,    91,   239,    16,   241,    82,
      83,    77,    78,    77,    78,    83,    89,   250,    90,   252,
      77,    78,    88,    80,   257,   258,    83,   260,    90,   262,
      82,    83,    89,    83,     7,     8,    83,    10,    11,    12,
       9,    14,    15,    77,    78,     9,   163,   164,   165,   166,
     160,    77,    78,    92,    88,   210,    83,     9,    81,   184,
      83,   496,   497,    89,    91,   439,    89,   441,   478,   488,
     474,   445,   477,   447,   487,   449,   484,   467,    69,   453,
     475,   455,   476,   457,   486,   468,   460,   204,   462,   485,
      77,    78,   466,    95,   468,   470,   470,   461,   469,   472,
     474,    88,   476,   473,   478,   462,   480,   481,   482,   483,
      83,   485,   486,   487,   488,   466,    95,    95,   522,   545,
     530,   540,   512,   528,   532,   538,   500,   501,   502,   524,
     504,   514,   526,   464,   536,   465,   510,   511,   534,   503,
     514,   515,   517,   517,   518,   516,   519,   504,   522,   523,
     520,   463,   526,   527,   228,   460,   530,   531,   436,   510,
     534,   535,   536,   537,   538,   539,   540,   541,   542,   471,
     458,    95,   459,    77,    78,   249,   507,    94,   508,    17,
      18,    19,    20,   159,   158,    89,    77,    78,    77,    78,
     264,    80,    -1,   505,    83,   269,   501,   494,    89,    88,
     274,   275,   276,   277,    77,    78,    78,    79,    -1,    -1,
     498,   444,   499,   446,    -1,    88,    -1,    89,   451,   452,
      -1,   454,    -1,   456,    78,    79,    78,    79,    78,    79,
      78,    79,   465,    -1,   467,    89,    -1,    89,    88,   472,
     473,    89,   475,    -1,   477,    78,    79,    -1,    78,    79,
      -1,    89,    78,    79,    78,    79,    89,   631,   632,    89,
      -1,   635,    88,   637,   638,    89,   640,    -1,   642,   547,
     644,   645,   646,   647,    -1,   508,   509,    -1,    -1,   512,
     513,    -1,    78,    79,    -1,    -1,   519,   520,   521,    -1,
      -1,   524,   525,    89,   668,   528,   529,   671,    -1,   673,
     674,    78,    79,    -1,   678,    -1,   680,   681,   682,    78,
      79,    -1,    89,    78,    79,    78,    79,    78,    79,    -1,
      89,    78,    79,    -1,    89,   699,    89,   701,    89,    -1,
     704,    -1,    89,    78,    79,    78,    79,   711,    -1,   713,
     714,    -1,    78,    79,    89,    -1,    89,   721,    -1,   723,
     724,    -1,   630,    89,    -1,    78,    79,   731,    -1,   733,
      78,    79,    -1,    78,    79,   739,    89,   741,    -1,   443,
      -1,    89,    -1,   747,    89,    -1,    -1,   751,    78,    79,
      -1,   755,    78,    79,    -1,   759,    78,    79,    88,   763,
     464,    -1,    88,   767,    78,    79,    88,   771,    -1,    78,
      79,   634,    -1,   636,    88,   479,   639,    -1,   641,    88,
     484,    78,    79,    78,    79,   489,    78,    79,    78,    79,
      -1,    88,    -1,    88,    78,    79,    88,    -1,    88,    -1,
      78,    79,   506,   507,    88,    78,    79,   670,    -1,   672,
      88,    78,    79,    -1,   677,    88,    78,    79,    -1,    -1,
      -1,    88,    78,    79,    78,    79,    88,    -1,   532,   533,
      77,    78,    88,    80,    88,   698,    83,   700,    -1,   543,
     544,   545,    78,    79,    78,    79,    -1,   710,    -1,   712,
      -1,    -1,    88,    -1,    88,    86,    87,   720,    89,   722,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   730,    -1,   732,
      -1,    -1,    -1,    -1,    -1,   738,    -1,   740,    -1,    -1,
      -1,    -1,    -1,   746,    -1,    -1,    -1,   750,    -1,    -1,
      -1,   754,    -1,    -1,    -1,   758,    -1,    -1,    -1,   762,
      -1,    -1,    -1,   766,    -1,    -1,    -1,   770,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   633,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   643,
      -1,    -1,    -1,    -1,   648,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   679,    -1,    -1,    -1,    -1,
     684,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    83,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,     3,    94,    95,     0,     4,    96,    83,    97,    98,
       5,    99,   101,    80,    83,   100,     6,   102,   106,    80,
     104,     7,     8,    10,    11,    12,    14,    15,    83,   107,
     108,   117,   118,   129,   138,   142,   145,   172,   103,   172,
     172,    83,   171,   171,   171,   171,   171,   109,    80,   105,
     119,   130,   111,   139,   143,   146,    88,   114,    88,    88,
     172,    92,    92,    16,   147,   115,   110,   121,   132,   112,
      83,   175,   171,   171,    86,    87,    89,   116,    90,   149,
      17,    18,    19,    20,    89,   122,    17,    18,    19,    20,
      89,   133,   114,   140,   144,   150,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,   176,
     176,   176,   176,   120,   176,   176,   176,   176,   131,   113,
      13,   147,     1,    17,    18,    19,    20,    83,    91,   117,
     138,   142,   145,   151,   152,   155,   159,   164,   168,   173,
     123,   124,   127,   125,    90,   134,   135,   137,   136,    77,
      78,    80,    83,    88,   148,   252,   302,   149,   171,   176,
     176,   176,    83,   176,   169,    83,   174,   175,   173,   173,
     106,   174,   175,   173,   173,   303,   141,   153,   156,   165,
     162,   160,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,   170,   176,
     177,   128,   126,    91,    89,   252,    92,   174,   175,   173,
     173,   173,    81,    83,    88,   181,   276,    78,    79,    88,
     180,   182,   278,    88,   180,   185,   280,    78,    79,    88,
     179,   189,   282,    88,   180,   190,   284,    77,    78,    88,
     178,   191,   286,    88,   178,   196,   288,    88,   179,   197,
     290,    88,   180,   206,   292,    88,   179,   215,   294,    88,
     180,   231,   296,    82,    88,   108,   247,   298,    88,   180,
     248,   300,   302,    88,   179,   253,   304,    88,   179,   254,
     306,    88,   180,   256,   308,    88,   179,   258,   310,    88,
     180,   262,   312,    88,   179,   266,   314,    88,   180,   271,
     316,   181,   182,   185,   189,   190,   191,   196,   197,   206,
     215,   231,   247,   248,   252,   253,   254,   256,   258,   262,
     266,   271,    88,   178,   318,   347,    88,   180,   322,   349,
      88,   180,   324,   351,    88,   180,   327,   353,    88,   180,
     331,   355,   318,   322,   324,   327,   331,   178,   335,   178,
     342,   178,   344,    88,   342,   357,     9,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
     177,   177,   174,   154,   157,   166,   163,   161,   277,   279,
     183,   281,   186,   283,   285,   287,   192,   289,   291,   198,
     293,   207,   295,   216,   297,   232,   299,   301,   249,   305,
     307,   255,   309,   257,   311,   259,   313,   263,   315,   267,
     317,   272,   348,   319,   350,   323,   352,   325,   354,   328,
     356,   332,   336,   343,   345,   358,   173,     9,   158,   158,
     167,   176,   177,   167,   167,    89,   181,    89,   182,   180,
      89,   185,   180,    89,   189,    89,   190,    89,   191,   178,
      89,   196,    89,   197,   179,    89,   206,   180,    89,   215,
     179,    89,   231,   180,    89,   247,    89,   248,   180,    89,
     253,    89,   254,   179,    89,   256,   180,    89,   258,   179,
      89,   262,   180,    89,   266,   179,    89,   271,   180,    89,
     318,   178,    89,   322,   180,    89,   324,   180,    89,   327,
     180,    89,   331,   180,   180,   178,   178,    89,   342,   173,
       9,   184,   187,   193,   199,   208,   217,   233,   250,   260,
     264,   268,   273,   320,   326,   329,   333,   337,   346,   173,
     180,   180,   178,   179,   180,   179,   180,   180,   179,   180,
     179,   180,   178,   180,   180,   180,   180,   178,   188,   194,
     200,   209,   218,   234,   251,   261,   265,   269,   274,   321,
     330,   334,   338,   180,   195,   179,   180,   179,   180,   180,
     179,   180,   178,   180,   180,   180,    84,   178,   201,   210,
     219,   235,   270,   275,   339,   179,   180,   179,   180,   180,
     202,   211,   220,   236,   340,   179,   180,   179,   180,   180,
     203,   212,   221,   237,   341,   179,   180,   179,   180,   180,
     204,   213,   222,   238,   179,   180,   179,   180,   205,   214,
     223,   239,   179,   180,   179,   180,   224,   240,   179,   180,
     225,   241,   179,   180,   226,   242,   179,   180,   227,   243,
     179,   180,   228,   244,   179,   180,   229,   245,   179,   180,
     230,   246,   179,   180
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,    93,    94,    95,    95,    96,    96,    97,    98,    98,
      99,   100,   100,   101,   101,   103,   102,   104,   105,   106,
     106,   107,   107,   107,   107,   107,   109,   110,   108,   111,
     112,   113,   108,   108,   114,   114,   115,   115,   116,   116,
     117,   117,   119,   120,   118,   121,   121,   123,   122,   124,
     122,   125,   126,   122,   127,   128,   122,   130,   131,   129,
     132,   132,   134,   133,   135,   133,   136,   133,   137,   133,
     139,   140,   141,   138,   143,   144,   142,   146,   145,   147,
     147,   148,   149,   150,   150,   151,   151,   151,   151,   151,
     151,   153,   154,   152,   156,   157,   155,   158,   158,   160,
     161,   159,   162,   163,   159,   165,   166,   164,   167,   167,
     169,   168,   168,   168,   168,   168,   170,   170,   171,   172,
     173,   174,   175,   176,   176,   176,   176,   176,   176,   176,
     176,   176,   176,   176,   176,   176,   176,   176,   176,   176,
     176,   176,   176,   176,   176,   176,   176,   176,   176,   176,
     176,   176,   176,   176,   176,   176,   176,   176,   176,   176,
     176,   176,   176,   176,   176,   176,   176,   176,   176,   176,
     176,   176,   176,   176,   176,   176,   177,   177,   177,   177,
     177,   177,   177,   177,   177,   177,   177,   177,   177,   177,
     177,   177,   177,   177,   177,   177,   177,   177,   177,   177,
     177,   177,   177,   177,   177,   177,   177,   177,   177,   177,
     177,   177,   177,   177,   177,   177,   177,   177,   177,   177,
     177,   177,   177,   177,   177,   177,   177,   177,   177,   177,
     177,   177,   178,   178,   179,   179,   180,   180,   181,   181,
     183,   184,   182,   186,   187,   188,   185,   189,   190,   192,
     193,   194,   191,   195,   195,   196,   198,   199,   200,   201,
     202,   203,   204,   205,   197,   207,   208,   209,   210,   211,
     212,   213,   214,   206,   216,   217,   218,   219,   220,   221,
     222,   223,   224,   225,   226,   227,   228,   229,   230,   215,
     232,   233,   234,   235,   236,   237,   238,   239,   240,   241,
     242,   243,   244,   245,   246,   231,   247,   247,   249,   250,
     251,   248,   252,   252,   252,   252,   253,   255,   254,   257,
     256,   259,   260,   261,   258,   263,   264,   265,   262,   267,
     268,   269,   270,   266,   272,   273,   274,   275,   271,   276,
     276,   277,   277,   278,   278,   279,   279,   280,   280,   281,
     281,   282,   282,   283,   283,   284,   284,   285,   285,   286,
     286,   287,   287,   288,   288,   289,   289,   290,   290,   291,
     291,   292,   292,   293,   293,   294,   294,   295,   295,   296,
     296,   297,   297,   298,   298,   299,   299,   300,   300,   301,
     301,   302,   302,   303,   303,   304,   304,   305,   305,   306,
     306,   307,   307,   308,   308,   309,   309,   310,   310,   311,
     311,   312,   312,   313,   313,   314,   314,   315,   315,   316,
     316,   317,   317,   319,   320,   321,   318,   323,   322,   325,
     326,   324,   328,   329,   330,   327,   332,   333,   334,   331,
     336,   337,   338,   339,   340,   341,   335,   343,   342,   345,
     346,   344,   347,   347,   348,   348,   349,   349,   350,   350,
     351,   351,   352,   352,   353,   353,   354,   354,   355,   355,
     356,   356,   357,   357,   358,   358
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     5,     1,     0,     2,     0,     1,     2,     0,
       2,     1,     1,     2,     0,     0,     4,     1,     1,     2,
       0,     1,     1,     1,     1,     1,     0,     0,     5,     0,
       0,     0,     8,     2,     3,     0,     2,     0,     1,     1,
       1,     1,     0,     0,    10,     2,     0,     0,     4,     0,
       4,     0,     0,     6,     0,     0,     6,     0,     0,     8,
       2,     0,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     0,     0,    11,     0,     0,     7,     0,     4,     2,
       0,     1,     3,     2,     0,     1,     1,     1,     1,     1,
       1,     0,     0,     6,     0,     0,     6,     0,     2,     0,
       0,     6,     0,     0,     6,     0,     0,     6,     1,     3,
       0,     3,     1,     1,     1,     1,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     0,     5,     0,     0,     0,     7,     1,     1,     0,
       0,     0,     8,     2,     0,     1,     0,     0,     0,     0,
       0,     0,     0,     0,    17,     0,     0,     0,     0,     0,
       0,     0,     0,    17,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    31,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    31,     1,     1,     0,     0,
       0,     7,     1,     1,     1,     1,     1,     0,     3,     0,
       3,     0,     0,     0,     6,     0,     0,     0,     6,     0,
       0,     0,     0,     8,     0,     0,     0,     0,     8,     1,
       3,     2,     0,     1,     3,     2,     0,     1,     3,     2,
       0,     1,     3,     2,     0,     1,     3,     2,     0,     1,
       3,     2,     0,     1,     3,     2,     0,     1,     3,     2,
       0,     1,     3,     2,     0,     1,     3,     2,     0,     1,
       3,     2,     0,     1,     3,     2,     0,     1,     3,     2,
       0,     1,     3,     2,     0,     1,     3,     2,     0,     1,
       3,     2,     0,     1,     3,     2,     0,     1,     3,     2,
       0,     1,     3,     2,     0,     1,     3,     2,     0,     1,
       3,     2,     0,     0,     0,     0,     7,     0,     3,     0,
       0,     5,     0,     0,     0,     7,     0,     0,     0,     7,
       0,     0,     0,     0,     0,     0,    13,     0,     3,     0,
       0,     5,     1,     3,     2,     0,     1,     3,     2,     0,
       1,     3,     2,     0,     1,     3,     2,     0,     1,     3,
       2,     0,     1,     3,     2,     0
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (pSkel, YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, pSkel); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, void *pSkel)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (pSkel);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, void *pSkel)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep, pSkel);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule, void *pSkel)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              , pSkel);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, pSkel); \
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
#ifndef YYINITDEPTH
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
static YYSIZE_T
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, void *pSkel)
{
  YYUSE (yyvaluep);
  YYUSE (pSkel);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void *pSkel)
{
/* The lookahead symbol.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
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
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
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

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex (&yylval, pSkel);
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
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
     '$$ = $1'.

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
#line 221 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { if(SKEL->verifyHeader((yyvsp[0].stringVal)) == false) { YYABORT; } }
#line 2040 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 222 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { if(SKEL->checkHeader() == true) { YYABORT; } }
#line 2046 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 225 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->profileElement((yyvsp[0].stringVal)); }
#line 2052 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 239 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->componentElement((yyvsp[0].stringVal)); }
#line 2058 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 256 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->_tmpString1 = (yyvsp[0].stringVal); }
#line 2064 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 258 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->metaElement(SKEL->_tmpString1.c_str(), (yyvsp[0].stringVal)); }
#line 2070 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 290 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->_tmpString1 = (yyvsp[0].stringVal); 
                            SKEL->_tmpBitVector1 = 
                                TypeTraits<BitVector>::BitsClear; }
#line 2078 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 293 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->beginNode(SKEL->_tmpString1.c_str(), 
                                            0,
                                            SKEL->_tmpBitVector1     ); }
#line 2086 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 298 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->_tmpString1 = (yyvsp[0].stringVal); 
                            SKEL->_tmpBitVector1 = 
                                TypeTraits<BitVector>::BitsClear; }
#line 2094 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 301 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->_tmpString2 = (yyvsp[0].stringVal); }
#line 2100 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 302 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->beginNode(SKEL->_tmpString2.c_str(), 
                                            SKEL->_tmpString1.c_str(),
                                            SKEL->_tmpBitVector1     ); }
#line 2108 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 307 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->use((yyvsp[0].stringVal)); }
#line 2114 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 318 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->_tmpBitVector1 |= FCLocal::Cluster; }
#line 2120 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 319 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->_tmpBitVector1 |= FCLocal::MT;      }
#line 2126 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 330 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->beginProto((yyvsp[0].stringVal)); }
#line 2132 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 331 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->endProtoInterface(); }
#line 2138 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 332 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->endProto(); }
#line 2144 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 340 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); }
#line 2150 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 341 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->beginEventInDecl(SKEL->_tmpString1.c_str(), (yyvsp[-2].intVal), (yyvsp[0].stringVal)); SKEL->endEventDecl(); }
#line 2156 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 343 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); }
#line 2162 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 344 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->beginEventOutDecl(SKEL->_tmpString1.c_str(), (yyvsp[-2].intVal), (yyvsp[0].stringVal)); SKEL->endEventDecl(); }
#line 2168 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 346 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); }
#line 2174 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 347 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->beginFieldDecl(SKEL->_tmpString1.c_str(), (yyvsp[-2].intVal), (yyvsp[0].stringVal)); SKEL->getLexer()->expectType((yyvsp[-2].intVal)); }
#line 2180 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 348 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->endFieldDecl(); }
#line 2186 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 350 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); }
#line 2192 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 351 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->beginExposedFieldDecl(SKEL->_tmpString1.c_str(), (yyvsp[-2].intVal), (yyvsp[0].stringVal)); SKEL->getLexer()->expectType((yyvsp[-2].intVal)); }
#line 2198 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 352 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->endExposedFieldDecl(); }
#line 2204 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 355 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->beginExternProto((yyvsp[0].stringVal)); }
#line 2210 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 356 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->endExternProtoInterface(); }
#line 2216 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 357 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->endExternProto(); }
#line 2222 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 365 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); }
#line 2228 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 366 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->addExternEventInDecl(SKEL->_tmpString1.c_str(), (yyvsp[-2].intVal), (yyvsp[0].stringVal)); }
#line 2234 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 368 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); }
#line 2240 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 369 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->addExternEventOutDecl(SKEL->_tmpString1.c_str(), (yyvsp[-2].intVal), (yyvsp[0].stringVal)); }
#line 2246 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 371 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); }
#line 2252 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 372 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->addExternFieldDecl(SKEL->_tmpString1.c_str(), (yyvsp[-2].intVal), (yyvsp[0].stringVal)); }
#line 2258 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 374 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); }
#line 2264 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 375 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->addExternExposedFieldDecl(SKEL->_tmpString1.c_str(), (yyvsp[-2].intVal), (yyvsp[0].stringVal)); }
#line 2270 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 379 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->_tmpString1 = (yyvsp[0].stringVal); }
#line 2276 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 381 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->_tmpString2 = (yyvsp[0].stringVal); }
#line 2282 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 383 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->_tmpString3 = (yyvsp[0].stringVal); }
#line 2288 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 386 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->addRoute(SKEL->_tmpString1.c_str(), SKEL->_tmpString2.c_str(), SKEL->_tmpString3.c_str(), (yyvsp[0].stringVal)); }
#line 2294 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 390 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->_tmpString1 = (yyvsp[0].stringVal); }
#line 2300 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 392 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->_tmpString2 = (yyvsp[0].stringVal); }
#line 2306 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 76:
#line 394 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    {
        if ((yyvsp[0].stringVal) != 0)
            SKEL->importElement(SKEL->_tmpString1.c_str(), SKEL->_tmpString2.c_str(), (yyvsp[0].stringVal));
        else
            SKEL->importElement(SKEL->_tmpString1.c_str(), SKEL->_tmpString2.c_str(), 0);
    }
#line 2317 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 77:
#line 403 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->_tmpString1 = (yyvsp[0].stringVal); }
#line 2323 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 78:
#line 405 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    {
        if ((yyvsp[0].stringVal) != 0)
            SKEL->exportElement(SKEL->_tmpString1.c_str(), (yyvsp[0].stringVal));
        else
            SKEL->exportElement(SKEL->_tmpString1.c_str(), 0);
    }
#line 2334 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 79:
#line 414 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { (yyval.stringVal) = (yyvsp[0].stringVal); }
#line 2340 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 80:
#line 415 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { (yyval.stringVal) = 0; }
#line 2346 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 82:
#line 421 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->endNode(); }
#line 2352 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 91:
#line 437 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); }
#line 2358 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 92:
#line 438 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->beginEventInDecl(SKEL->_tmpString1.c_str(), (yyvsp[-2].intVal), (yyvsp[0].stringVal)); }
#line 2364 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 93:
#line 439 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->endEventDecl(); }
#line 2370 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 94:
#line 443 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); }
#line 2376 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 95:
#line 444 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->beginEventOutDecl(SKEL->_tmpString1.c_str(), (yyvsp[-2].intVal), (yyvsp[0].stringVal)); }
#line 2382 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 96:
#line 445 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->endEventDecl(); }
#line 2388 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 98:
#line 449 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->is((yyvsp[0].stringVal)); }
#line 2394 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 99:
#line 453 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); }
#line 2400 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 100:
#line 454 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->beginFieldDecl(SKEL->_tmpString1.c_str(), (yyvsp[-2].intVal), (yyvsp[0].stringVal)); SKEL->getLexer()->expectType((yyvsp[-2].intVal)); }
#line 2406 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 101:
#line 455 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->endFieldDecl(); }
#line 2412 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 102:
#line 457 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); }
#line 2418 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 103:
#line 458 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { 
               SKEL->beginFieldDecl(SKEL->_tmpString1.c_str(), 0, (yyvsp[0].stringVal)); 

               Int32 iFieldTypeId = SKEL->getFieldType((yyvsp[0].stringVal));

               if(SKEL->getMapFieldTypes() == true)
                 iFieldTypeId = SKEL->mapExtIntFieldType((yyvsp[0].stringVal), iFieldTypeId);

               SKEL->getLexer()->expectType(iFieldTypeId);
             }
#line 2433 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 104:
#line 468 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->endFieldDecl(); }
#line 2439 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 105:
#line 472 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); }
#line 2445 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 106:
#line 473 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->beginExposedFieldDecl(SKEL->_tmpString1.c_str(), (yyvsp[-2].intVal), (yyvsp[0].stringVal)); SKEL->getLexer()->expectType((yyvsp[-2].intVal)); }
#line 2451 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 107:
#line 474 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->endExposedFieldDecl(); }
#line 2457 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 109:
#line 478 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->is((yyvsp[0].stringVal)); }
#line 2463 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 110:
#line 482 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    {
        Int32 iFieldTypeId = SKEL->getFieldType((yyvsp[0].stringVal));
        if (SKEL->getMapFieldTypes() == true)
            iFieldTypeId = SKEL->mapExtIntFieldType((yyvsp[0].stringVal), iFieldTypeId);
        SKEL->getLexer()->expectType(iFieldTypeId);
        SKEL->beginField((yyvsp[0].stringVal), iFieldTypeId);
    }
#line 2475 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 111:
#line 489 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->endField(); }
#line 2481 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 117:
#line 497 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->is((yyvsp[0].stringVal)); }
#line 2487 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 232:
#line 630 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { (yyval.intVal) = (yyvsp[0].intVal); }
#line 2493 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 233:
#line 631 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { (yyval.intVal) = (yyvsp[0].intVal); }
#line 2499 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 234:
#line 634 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { (yyval.doubleVal) = (yyvsp[0].intVal); }
#line 2505 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 235:
#line 635 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { (yyval.doubleVal) = (yyvsp[0].doubleVal); }
#line 2511 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 236:
#line 638 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { (yyval.floatVal) = static_cast<float>((yyvsp[0].intVal)); }
#line 2517 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 237:
#line 639 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { (yyval.floatVal) = static_cast<float>((yyvsp[0].doubleVal)); }
#line 2523 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 238:
#line 643 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    {
        SKEL->addBoolValue((yyvsp[0].boolVal));
    }
#line 2531 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 239:
#line 646 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->addFieldValue((yyvsp[0].stringVal)); }
#line 2537 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 240:
#line 649 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->beginValue(); }
#line 2543 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 241:
#line 650 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->appendValue(); }
#line 2549 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 242:
#line 652 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    {
        SKEL->appendValue();
        SKEL->addColorValue(Color3f((yyvsp[-4].floatVal), (yyvsp[-2].floatVal), (yyvsp[0].floatVal)));
    }
#line 2558 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 243:
#line 658 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->beginValue(); }
#line 2564 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 244:
#line 659 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->appendValue(); }
#line 2570 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 245:
#line 660 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->appendValue(); }
#line 2576 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 246:
#line 662 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    {
        SKEL->appendValue();
        SKEL->addColorRGBAValue(Color4f((yyvsp[-6].floatVal), (yyvsp[-4].floatVal), (yyvsp[-2].floatVal), (yyvsp[0].floatVal)));
    }
#line 2585 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 247:
#line 669 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    {
        SKEL->addDoubleValue((yyvsp[0].doubleVal));
    }
#line 2593 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 248:
#line 675 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    {
        SKEL->addFloatValue((yyvsp[0].floatVal));
    }
#line 2601 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 249:
#line 680 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->beginValue(); }
#line 2607 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 250:
#line 681 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->appendValue(); }
#line 2613 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 251:
#line 683 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    {
        SKEL->appendValue();
        SKEL->beginImage((yyvsp[-4].intVal), (yyvsp[-2].intVal), (yyvsp[0].intVal));
    }
#line 2622 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 252:
#line 688 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    {
        SKEL->endImage();
    }
#line 2630 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 253:
#line 694 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    {
        SKEL->addImagePixel((yyvsp[0].intVal));
    }
#line 2638 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 255:
#line 701 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    {
        SKEL->addInt32Value((yyvsp[0].intVal));
    }
#line 2646 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 256:
#line 706 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->beginValue(); }
#line 2652 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 257:
#line 707 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->appendValue(); }
#line 2658 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 258:
#line 708 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->appendValue(); }
#line 2664 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 259:
#line 709 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->appendValue(); }
#line 2670 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 260:
#line 710 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->appendValue(); }
#line 2676 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 261:
#line 711 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->appendValue(); }
#line 2682 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 262:
#line 712 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->appendValue(); }
#line 2688 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 263:
#line 713 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->appendValue(); }
#line 2694 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 264:
#line 715 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    {
        SKEL->appendValue();
        SKEL->addMatrix3dValue(
            (yyvsp[-16].doubleVal),  (yyvsp[-10].doubleVal), (yyvsp[-4].doubleVal),
            (yyvsp[-14].doubleVal),  (yyvsp[-8].doubleVal), (yyvsp[-2].doubleVal),
            (yyvsp[-12].doubleVal), (yyvsp[-6].doubleVal), (yyvsp[0].doubleVal));
    }
#line 2706 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 265:
#line 724 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->beginValue(); }
#line 2712 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 266:
#line 725 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->appendValue(); }
#line 2718 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 267:
#line 726 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->appendValue(); }
#line 2724 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 268:
#line 727 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->appendValue(); }
#line 2730 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 269:
#line 728 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->appendValue(); }
#line 2736 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 270:
#line 729 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->appendValue(); }
#line 2742 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 271:
#line 730 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->appendValue(); }
#line 2748 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 272:
#line 731 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->appendValue(); }
#line 2754 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 273:
#line 733 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    {
        SKEL->appendValue();
        SKEL->addMatrix3fValue(
            (yyvsp[-16].floatVal),  (yyvsp[-10].floatVal), (yyvsp[-4].floatVal),
            (yyvsp[-14].floatVal),  (yyvsp[-8].floatVal), (yyvsp[-2].floatVal),
            (yyvsp[-12].floatVal), (yyvsp[-6].floatVal), (yyvsp[0].floatVal));
    }
#line 2766 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 274:
#line 742 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->beginValue(); }
#line 2772 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 275:
#line 743 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->appendValue(); }
#line 2778 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 276:
#line 744 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->appendValue(); }
#line 2784 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 277:
#line 745 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->appendValue(); }
#line 2790 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 278:
#line 746 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->appendValue(); }
#line 2796 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 279:
#line 747 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->appendValue(); }
#line 2802 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 280:
#line 748 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->appendValue(); }
#line 2808 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 281:
#line 749 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->appendValue(); }
#line 2814 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 282:
#line 750 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->appendValue(); }
#line 2820 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 283:
#line 751 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->appendValue(); }
#line 2826 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 284:
#line 752 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->appendValue(); }
#line 2832 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 285:
#line 753 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->appendValue(); }
#line 2838 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 286:
#line 754 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->appendValue(); }
#line 2844 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 287:
#line 755 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->appendValue(); }
#line 2850 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 288:
#line 756 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->appendValue(); }
#line 2856 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 289:
#line 758 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    {
        SKEL->appendValue();
        SKEL->addMatrix4dValue(Matrix4d(
            (yyvsp[-30].doubleVal),  (yyvsp[-22].doubleVal), (yyvsp[-14].doubleVal), (yyvsp[-6].doubleVal),
            (yyvsp[-28].doubleVal), (yyvsp[-20].doubleVal), (yyvsp[-12].doubleVal), (yyvsp[-4].doubleVal),
            (yyvsp[-26].doubleVal), (yyvsp[-18].doubleVal), (yyvsp[-10].doubleVal), (yyvsp[-2].doubleVal),
            (yyvsp[-24].doubleVal), (yyvsp[-16].doubleVal), (yyvsp[-8].doubleVal), (yyvsp[0].doubleVal)));
    }
#line 2869 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 290:
#line 768 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->beginValue(); }
#line 2875 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 291:
#line 769 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->appendValue(); }
#line 2881 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 292:
#line 770 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->appendValue(); }
#line 2887 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 293:
#line 771 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->appendValue(); }
#line 2893 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 294:
#line 772 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->appendValue(); }
#line 2899 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 295:
#line 773 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->appendValue(); }
#line 2905 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 296:
#line 774 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->appendValue(); }
#line 2911 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 297:
#line 775 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->appendValue(); }
#line 2917 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 298:
#line 776 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->appendValue(); }
#line 2923 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 299:
#line 777 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->appendValue(); }
#line 2929 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 300:
#line 778 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->appendValue(); }
#line 2935 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 301:
#line 779 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->appendValue(); }
#line 2941 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 302:
#line 780 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->appendValue(); }
#line 2947 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 303:
#line 781 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->appendValue(); }
#line 2953 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 304:
#line 782 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->appendValue(); }
#line 2959 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 305:
#line 784 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    {
        SKEL->appendValue();
        SKEL->addMatrix4fValue(Matrix4f(
            (yyvsp[-30].floatVal),  (yyvsp[-22].floatVal), (yyvsp[-14].floatVal), (yyvsp[-6].floatVal),
            (yyvsp[-28].floatVal), (yyvsp[-20].floatVal), (yyvsp[-12].floatVal), (yyvsp[-4].floatVal),
            (yyvsp[-26].floatVal), (yyvsp[-18].floatVal), (yyvsp[-10].floatVal), (yyvsp[-2].floatVal),
            (yyvsp[-24].floatVal), (yyvsp[-16].floatVal), (yyvsp[-8].floatVal), (yyvsp[0].floatVal)));
    }
#line 2972 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 307:
#line 795 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->nullNode(); }
#line 2978 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 308:
#line 798 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->beginValue(); }
#line 2984 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 309:
#line 799 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->appendValue(); }
#line 2990 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 310:
#line 800 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->appendValue(); }
#line 2996 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 311:
#line 802 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    {
        SKEL->appendValue();
        SKEL->addRotationValue(Vec3f((yyvsp[-6].floatVal), (yyvsp[-4].floatVal), (yyvsp[-2].floatVal)), (yyvsp[0].floatVal));
    }
#line 3005 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 312:
#line 809 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    {
        SKEL->addStringValue((yyvsp[0].stringVal));
    }
#line 3013 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 313:
#line 813 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { /* Not VRML conformant */
        SKEL->addStringValue((yyvsp[0].stringVal));
    }
#line 3021 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 314:
#line 817 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { /* Not VRML conformant */
        SKEL->addBufferAsStringValue();
    }
#line 3029 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 315:
#line 821 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { /* Not VRML conformant */
        SKEL->addBufferAsStringValue();
    }
#line 3037 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 316:
#line 827 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    {
        SKEL->addTimeValue((yyvsp[0].doubleVal));
    }
#line 3045 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 317:
#line 832 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->beginValue(); }
#line 3051 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 318:
#line 834 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    {
        SKEL->appendValue();
        SKEL->addVec2dValue(Vec2d((yyvsp[-2].doubleVal), (yyvsp[0].doubleVal)));
    }
#line 3060 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 319:
#line 840 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->beginValue(); }
#line 3066 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 320:
#line 842 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    {
        SKEL->appendValue();
        SKEL->addVec2fValue(Vec2f((yyvsp[-2].floatVal), (yyvsp[0].floatVal)));
    }
#line 3075 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 321:
#line 848 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->beginValue(); }
#line 3081 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 322:
#line 849 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->appendValue(); }
#line 3087 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 323:
#line 850 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->appendValue(); }
#line 3093 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 324:
#line 851 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    {
        SKEL->appendValue();
        SKEL->addVec3dValue(Vec3d((yyvsp[-5].doubleVal), (yyvsp[-3].doubleVal), (yyvsp[-1].doubleVal)));
    }
#line 3102 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 325:
#line 857 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->beginValue(); }
#line 3108 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 326:
#line 858 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->appendValue(); }
#line 3114 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 327:
#line 859 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->appendValue(); }
#line 3120 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 328:
#line 860 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    {
        SKEL->appendValue();
        SKEL->addVec3fValue(Vec3f((yyvsp[-5].floatVal), (yyvsp[-3].floatVal), (yyvsp[-1].floatVal)));
    }
#line 3129 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 329:
#line 866 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->beginValue(); }
#line 3135 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 330:
#line 867 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->appendValue(); }
#line 3141 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 331:
#line 868 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->appendValue(); }
#line 3147 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 332:
#line 869 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->appendValue(); }
#line 3153 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 333:
#line 870 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    {
        SKEL->appendValue();
        SKEL->addVec4dValue(Vec4d((yyvsp[-7].doubleVal), (yyvsp[-5].doubleVal), (yyvsp[-3].doubleVal), (yyvsp[-1].doubleVal)));
    }
#line 3162 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 334:
#line 876 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->beginValue(); }
#line 3168 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 335:
#line 877 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->appendValue(); }
#line 3174 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 336:
#line 878 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->appendValue(); }
#line 3180 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 337:
#line 879 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->appendValue(); }
#line 3186 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 338:
#line 880 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    {
        SKEL->appendValue();
        SKEL->addVec4fValue(Vec4f((yyvsp[-7].floatVal), (yyvsp[-5].floatVal), (yyvsp[-3].floatVal), (yyvsp[-1].floatVal)));
    }
#line 3195 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 423:
#line 1056 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->beginValue(); }
#line 3201 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 424:
#line 1057 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->appendValue(); }
#line 3207 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 425:
#line 1058 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->appendValue(); }
#line 3213 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 426:
#line 1060 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    {
        SKEL->appendValue();
        SKEL->addColor4iValue(Color4ub(static_cast<UInt8>((yyvsp[-6].intVal)), static_cast<UInt8>((yyvsp[-4].intVal)),
                                       static_cast<UInt8>((yyvsp[-2].intVal)), static_cast<UInt8>((yyvsp[0].intVal))));
    }
#line 3223 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 427:
#line 1067 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->beginValue(); }
#line 3229 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 428:
#line 1069 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    {
        SKEL->appendValue();
        SKEL->addPnt2fValue(Pnt2f((yyvsp[-2].floatVal), (yyvsp[0].floatVal)));
    }
#line 3238 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 429:
#line 1075 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->beginValue(); }
#line 3244 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 430:
#line 1076 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->appendValue(); }
#line 3250 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 431:
#line 1078 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    {
        SKEL->appendValue();
        SKEL->addPnt3fValue(Pnt3f((yyvsp[-4].floatVal), (yyvsp[-2].floatVal), (yyvsp[0].floatVal)));
    }
#line 3259 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 432:
#line 1084 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->beginValue(); }
#line 3265 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 433:
#line 1085 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->appendValue(); }
#line 3271 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 434:
#line 1086 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->appendValue(); }
#line 3277 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 435:
#line 1088 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    {
        SKEL->appendValue();
        SKEL->addPnt4fValue(Pnt4f((yyvsp[-6].floatVal), (yyvsp[-4].floatVal), (yyvsp[-2].floatVal), (yyvsp[0].floatVal)));
    }
#line 3286 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 436:
#line 1094 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->beginValue(); }
#line 3292 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 437:
#line 1095 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->appendValue(); }
#line 3298 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 438:
#line 1096 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->appendValue(); }
#line 3304 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 439:
#line 1098 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    {
        SKEL->appendValue();
        SKEL->addPlaneValue(Plane(Vec3f((yyvsp[-6].floatVal), (yyvsp[-4].floatVal), (yyvsp[-2].floatVal)), (yyvsp[0].floatVal)));
    }
#line 3313 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 440:
#line 1104 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->beginValue();  }
#line 3319 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 441:
#line 1105 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->appendValue(); }
#line 3325 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 442:
#line 1106 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->appendValue(); }
#line 3331 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 443:
#line 1107 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->appendValue(); }
#line 3337 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 444:
#line 1108 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->appendValue(); }
#line 3343 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 445:
#line 1109 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->appendValue(); }
#line 3349 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 446:
#line 1111 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    {
        SKEL->appendValue();
        BoxVolume bv((yyvsp[-10].floatVal), (yyvsp[-8].floatVal), (yyvsp[-6].floatVal), (yyvsp[-4].floatVal), (yyvsp[-2].floatVal), (yyvsp[0].floatVal));
        
        bv.setState((yyvsp[-12].intVal));

        SKEL->addVolumeValue(bv);
    }
#line 3362 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 447:
#line 1121 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->beginValue(); }
#line 3368 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 448:
#line 1123 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    {
        SKEL->appendValue();
        SKEL->addVec2iValue(Vec2i((yyvsp[-2].intVal), (yyvsp[0].intVal)));
    }
#line 3377 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 449:
#line 1129 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    { SKEL->beginValue(); }
#line 3383 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 450:
#line 1131 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    {
        SKEL->appendValue();
    }
#line 3391 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;

  case 451:
#line 1135 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1646  */
    {
        SKEL->appendValue();
        SKEL->addVec3iValue(Vec3i((yyvsp[-4].intVal), (yyvsp[-2].intVal), (yyvsp[0].intVal)));
    }
#line 3400 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
    break;


#line 3404 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (pSkel, YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (pSkel, yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
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
                      yytoken, &yylval, pSkel);
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
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
                  yystos[yystate], yyvsp, pSkel);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (pSkel, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, pSkel);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, pSkel);
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
  return yyresult;
}
#line 1188 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1906  */


int OSGScanParseSkel_lex(YYSTYPE *lvalp, void *pSkel)
{
    return SKEL->lex(lvalp);
}
