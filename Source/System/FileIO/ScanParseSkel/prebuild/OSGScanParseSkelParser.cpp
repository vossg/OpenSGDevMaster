/* A Bison parser, made by GNU Bison 2.6.1.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.6.1"

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
#define yylval          OSGScanParseSkel_lval
#define yychar          OSGScanParseSkel_char
#define yydebug         OSGScanParseSkel_debug
#define yynerrs         OSGScanParseSkel_nerrs

/* Copy the first part of user declarations.  */

/* Line 336 of yacc.c  */
#line 75 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
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
#ifndef OSGSCANPARSESKEL_HOME_GERRIT_PROJECTS_OPENSG_SVN_OPENSG_BUILD_BUILD_OSGSYSTEM_OSGSCANPARSESKELPARSER_HPP
# define OSGSCANPARSESKEL_HOME_GERRIT_PROJECTS_OPENSG_SVN_OPENSG_BUILD_BUILD_OSGSYSTEM_OSGSCANPARSESKELPARSER_HPP
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int OSGScanParseSkel_debug;
#endif

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


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 350 of yacc.c  */
#line 41 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"

    long intVal;
    double doubleVal;
    float floatVal;
    const char *stringVal;
    bool boolVal;


/* Line 350 of yacc.c  */
#line 214 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int OSGScanParseSkel_parse (void *YYPARSE_PARAM);
#else
int OSGScanParseSkel_parse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int OSGScanParseSkel_parse (void);
#else
int OSGScanParseSkel_parse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !OSGSCANPARSESKEL_HOME_GERRIT_PROJECTS_OPENSG_SVN_OPENSG_BUILD_BUILD_OSGSYSTEM_OSGSCANPARSESKELPARSER_HPP  */

/* Copy the second part of user declarations.  */
/* Line 353 of yacc.c  */
#line 49 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"


#if __GNUC__ >= 4 || __GNUC_MINOR__ >=3
#pragma GCC diagnostic warning "-Wold-style-cast"
#endif

#define YYPARSE_PARAM pSkel
#define YYLEX_PARAM   pSkel

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


/* Line 353 of yacc.c  */
#line 280 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp"

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
# if defined YYENABLE_NLS && YYENABLE_NLS
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
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
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
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

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
      while (YYID (0))
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
/* YYNRULES -- Number of states.  */
#define YYNSTATES  774

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   342

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
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
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     9,    11,    12,    15,    16,    18,    21,
      22,    25,    27,    29,    32,    33,    34,    39,    41,    43,
      46,    47,    49,    51,    53,    55,    57,    58,    59,    65,
      66,    67,    68,    77,    80,    84,    85,    88,    89,    91,
      93,    95,    97,    98,    99,   110,   113,   114,   115,   120,
     121,   126,   127,   128,   135,   136,   137,   144,   145,   146,
     155,   158,   159,   160,   165,   166,   171,   172,   177,   178,
     183,   184,   185,   186,   198,   199,   200,   208,   209,   214,
     217,   218,   220,   224,   227,   228,   230,   232,   234,   236,
     238,   240,   241,   242,   249,   250,   251,   258,   259,   262,
     263,   264,   271,   272,   273,   280,   281,   282,   289,   291,
     295,   296,   300,   302,   304,   306,   308,   310,   314,   316,
     318,   320,   322,   324,   326,   328,   330,   332,   334,   336,
     338,   340,   342,   344,   346,   348,   350,   352,   354,   356,
     358,   360,   362,   364,   366,   368,   370,   372,   374,   376,
     378,   380,   382,   384,   386,   388,   390,   392,   394,   396,
     398,   400,   402,   404,   406,   408,   410,   412,   414,   416,
     418,   420,   422,   424,   426,   428,   430,   433,   436,   439,
     442,   445,   448,   451,   454,   457,   460,   463,   466,   469,
     472,   475,   478,   481,   484,   487,   490,   493,   496,   499,
     502,   505,   508,   511,   514,   517,   520,   523,   526,   529,
     532,   535,   538,   541,   544,   547,   550,   553,   556,   559,
     562,   565,   568,   571,   574,   577,   580,   583,   586,   589,
     592,   595,   598,   600,   602,   604,   606,   608,   610,   612,
     614,   615,   616,   622,   623,   624,   625,   633,   635,   637,
     638,   639,   640,   649,   652,   653,   655,   656,   657,   658,
     659,   660,   661,   662,   663,   681,   682,   683,   684,   685,
     686,   687,   688,   689,   707,   708,   709,   710,   711,   712,
     713,   714,   715,   716,   717,   718,   719,   720,   721,   722,
     754,   755,   756,   757,   758,   759,   760,   761,   762,   763,
     764,   765,   766,   767,   768,   769,   801,   803,   805,   806,
     807,   808,   816,   818,   820,   822,   824,   826,   827,   831,
     832,   836,   837,   838,   839,   846,   847,   848,   849,   856,
     857,   858,   859,   860,   869,   870,   871,   872,   873,   882,
     884,   888,   891,   892,   894,   898,   901,   902,   904,   908,
     911,   912,   914,   918,   921,   922,   924,   928,   931,   932,
     934,   938,   941,   942,   944,   948,   951,   952,   954,   958,
     961,   962,   964,   968,   971,   972,   974,   978,   981,   982,
     984,   988,   991,   992,   994,   998,  1001,  1002,  1004,  1008,
    1011,  1012,  1014,  1018,  1021,  1022,  1024,  1028,  1031,  1032,
    1034,  1038,  1041,  1042,  1044,  1048,  1051,  1052,  1054,  1058,
    1061,  1062,  1064,  1068,  1071,  1072,  1074,  1078,  1081,  1082,
    1084,  1088,  1091,  1092,  1093,  1094,  1095,  1103,  1104,  1108,
    1109,  1110,  1116,  1117,  1118,  1119,  1127,  1128,  1129,  1130,
    1138,  1139,  1140,  1141,  1142,  1143,  1144,  1158,  1159,  1163,
    1164,  1165,  1171,  1173,  1177,  1180,  1181,  1183,  1187,  1190,
    1191,  1193,  1197,  1200,  1201,  1203,  1207,  1210,  1211,  1213,
    1217,  1220,  1221,  1223,  1227,  1230
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      94,     0,    -1,    95,    96,    98,   101,   106,    -1,     3,
      -1,    -1,     4,    97,    -1,    -1,    83,    -1,    98,    99,
      -1,    -1,     5,   100,    -1,    83,    -1,    80,    -1,   101,
     102,    -1,    -1,    -1,     6,   104,   103,   105,    -1,    80,
      -1,    80,    -1,   106,   107,    -1,    -1,   108,    -1,   117,
      -1,   138,    -1,   142,    -1,   145,    -1,    -1,    -1,   172,
     109,   114,   110,   149,    -1,    -1,    -1,    -1,    10,   171,
     111,   172,   112,   114,   113,   149,    -1,    11,   171,    -1,
      88,   115,    89,    -1,    -1,   115,   116,    -1,    -1,    86,
      -1,    87,    -1,   118,    -1,   129,    -1,    -1,    -1,     7,
     172,   119,    88,   121,    89,   120,    90,   106,    91,    -1,
     121,   122,    -1,    -1,    -1,    17,   176,   123,   174,    -1,
      -1,    18,   176,   124,   175,    -1,    -1,    -1,    20,   176,
     125,   173,   126,   177,    -1,    -1,    -1,    19,   176,   127,
     173,   128,   177,    -1,    -1,    -1,     8,   172,   130,    88,
     132,    89,   131,   148,    -1,   132,   133,    -1,    -1,    -1,
      17,   176,   134,   174,    -1,    -1,    18,   176,   135,   175,
      -1,    -1,    20,   176,   136,   173,    -1,    -1,    19,   176,
     137,   173,    -1,    -1,    -1,    -1,    12,   171,   139,    92,
     175,   140,    13,   171,   141,    92,   174,    -1,    -1,    -1,
      14,   171,   143,    92,   171,   144,   147,    -1,    -1,    15,
     171,   146,   147,    -1,    16,   171,    -1,    -1,   302,    -1,
      90,   150,    91,    -1,   150,   151,    -1,    -1,   168,    -1,
     152,    -1,   155,    -1,   159,    -1,   164,    -1,     1,    -1,
      -1,    -1,    17,   176,   153,   174,   154,   158,    -1,    -1,
      -1,    18,   176,   156,   175,   157,   158,    -1,    -1,     9,
     173,    -1,    -1,    -1,    20,   176,   160,   173,   161,   167,
      -1,    -1,    -1,    20,    83,   162,   173,   163,   167,    -1,
      -1,    -1,    19,   176,   165,   173,   166,   167,    -1,   177,
      -1,   176,     9,   173,    -1,    -1,   173,   169,   170,    -1,
     138,    -1,   117,    -1,   142,    -1,   145,    -1,   177,    -1,
     176,     9,   173,    -1,    83,    -1,    83,    -1,    83,    -1,
      83,    -1,    83,    -1,    21,    -1,    22,    -1,    23,    -1,
      24,    -1,    25,    -1,    26,    -1,    27,    -1,    28,    -1,
      29,    -1,    30,    -1,    31,    -1,    32,    -1,    33,    -1,
      34,    -1,    35,    -1,    36,    -1,    37,    -1,    38,    -1,
      39,    -1,    40,    -1,    41,    -1,    42,    -1,    43,    -1,
      44,    -1,    45,    -1,    46,    -1,    47,    -1,    48,    -1,
      49,    -1,    50,    -1,    51,    -1,    52,    -1,    53,    -1,
      54,    -1,    55,    -1,    56,    -1,    57,    -1,    58,    -1,
      59,    -1,    60,    -1,    61,    -1,    62,    -1,    63,    -1,
      64,    -1,    65,    -1,    66,    -1,    67,    -1,    68,    -1,
      69,    -1,    70,    -1,    71,    -1,    72,    -1,    73,    -1,
      21,   276,    -1,    22,   278,    -1,    23,   280,    -1,    24,
     282,    -1,    25,   284,    -1,    26,   286,    -1,    27,   288,
      -1,    28,   290,    -1,    29,   292,    -1,    30,   294,    -1,
      31,   296,    -1,    32,   298,    -1,    33,   300,    -1,    34,
     302,    -1,    35,   304,    -1,    36,   306,    -1,    37,   308,
      -1,    38,   310,    -1,    39,   312,    -1,    40,   314,    -1,
      41,   316,    -1,    42,   181,    -1,    43,   182,    -1,    44,
     185,    -1,    45,   189,    -1,    46,   190,    -1,    47,   191,
      -1,    48,   196,    -1,    49,   197,    -1,    50,   206,    -1,
      51,   215,    -1,    52,   231,    -1,    53,   247,    -1,    54,
     248,    -1,    55,   252,    -1,    56,   253,    -1,    57,   254,
      -1,    58,   256,    -1,    59,   258,    -1,    60,   262,    -1,
      61,   266,    -1,    62,   271,    -1,    63,   347,    -1,    64,
     349,    -1,    65,   351,    -1,    66,   353,    -1,    67,   355,
      -1,    68,   318,    -1,    69,   322,    -1,    70,   324,    -1,
      71,   327,    -1,    72,   331,    -1,    73,   335,    -1,    74,
     342,    -1,    75,   344,    -1,    76,   357,    -1,    77,    -1,
      78,    -1,    78,    -1,    79,    -1,    78,    -1,    79,    -1,
      81,    -1,    83,    -1,    -1,    -1,   180,   183,   180,   184,
     180,    -1,    -1,    -1,    -1,   180,   186,   180,   187,   180,
     188,   180,    -1,   179,    -1,   180,    -1,    -1,    -1,    -1,
     178,   192,   178,   193,   178,   194,   195,    84,    -1,   195,
     178,    -1,    -1,   178,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   179,   198,   179,   199,   179,   200,   179,
     201,   179,   202,   179,   203,   179,   204,   179,   205,   179,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   180,
     207,   180,   208,   180,   209,   180,   210,   180,   211,   180,
     212,   180,   213,   180,   214,   180,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   179,   216,   179,   217,   179,   218,   179,   219,
     179,   220,   179,   221,   179,   222,   179,   223,   179,   224,
     179,   225,   179,   226,   179,   227,   179,   228,   179,   229,
     179,   230,   179,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   180,
     232,   180,   233,   180,   234,   180,   235,   180,   236,   180,
     237,   180,   238,   180,   239,   180,   240,   180,   241,   180,
     242,   180,   243,   180,   244,   180,   245,   180,   246,   180,
      -1,   108,    -1,    82,    -1,    -1,    -1,    -1,   180,   249,
     180,   250,   180,   251,   180,    -1,    80,    -1,    83,    -1,
      77,    -1,    78,    -1,   179,    -1,    -1,   179,   255,   179,
      -1,    -1,   180,   257,   180,    -1,    -1,    -1,    -1,   179,
     259,   179,   260,   179,   261,    -1,    -1,    -1,    -1,   180,
     263,   180,   264,   180,   265,    -1,    -1,    -1,    -1,    -1,
     179,   267,   179,   268,   179,   269,   179,   270,    -1,    -1,
      -1,    -1,    -1,   180,   272,   180,   273,   180,   274,   180,
     275,    -1,   181,    -1,    88,   277,    89,    -1,   277,   181,
      -1,    -1,   182,    -1,    88,   279,    89,    -1,   279,   182,
      -1,    -1,   185,    -1,    88,   281,    89,    -1,   281,   185,
      -1,    -1,   189,    -1,    88,   283,    89,    -1,   283,   189,
      -1,    -1,   190,    -1,    88,   285,    89,    -1,   285,   190,
      -1,    -1,   191,    -1,    88,   287,    89,    -1,   287,   191,
      -1,    -1,   196,    -1,    88,   289,    89,    -1,   289,   196,
      -1,    -1,   197,    -1,    88,   291,    89,    -1,   291,   197,
      -1,    -1,   206,    -1,    88,   293,    89,    -1,   293,   206,
      -1,    -1,   215,    -1,    88,   295,    89,    -1,   295,   215,
      -1,    -1,   231,    -1,    88,   297,    89,    -1,   297,   231,
      -1,    -1,   247,    -1,    88,   299,    89,    -1,   299,   247,
      -1,    -1,   248,    -1,    88,   301,    89,    -1,   301,   248,
      -1,    -1,   252,    -1,    88,   303,    89,    -1,   303,   252,
      -1,    -1,   253,    -1,    88,   305,    89,    -1,   305,   253,
      -1,    -1,   254,    -1,    88,   307,    89,    -1,   307,   254,
      -1,    -1,   256,    -1,    88,   309,    89,    -1,   309,   256,
      -1,    -1,   258,    -1,    88,   311,    89,    -1,   311,   258,
      -1,    -1,   262,    -1,    88,   313,    89,    -1,   313,   262,
      -1,    -1,   266,    -1,    88,   315,    89,    -1,   315,   266,
      -1,    -1,   271,    -1,    88,   317,    89,    -1,   317,   271,
      -1,    -1,    -1,    -1,    -1,   178,   319,   178,   320,   178,
     321,   178,    -1,    -1,   180,   323,   180,    -1,    -1,    -1,
     180,   325,   180,   326,   180,    -1,    -1,    -1,    -1,   180,
     328,   180,   329,   180,   330,   180,    -1,    -1,    -1,    -1,
     180,   332,   180,   333,   180,   334,   180,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   178,   336,   180,   337,   180,   338,
     180,   339,   180,   340,   180,   341,   180,    -1,    -1,   178,
     343,   178,    -1,    -1,    -1,   178,   345,   178,   346,   178,
      -1,   318,    -1,    88,   348,    89,    -1,   348,   318,    -1,
      -1,   322,    -1,    88,   350,    89,    -1,   350,   322,    -1,
      -1,   324,    -1,    88,   352,    89,    -1,   352,   324,    -1,
      -1,   327,    -1,    88,   354,    89,    -1,   354,   327,    -1,
      -1,   331,    -1,    88,   356,    89,    -1,   356,   331,    -1,
      -1,   342,    -1,    88,   358,    89,    -1,   358,   342,    -1,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   211,   211,   218,   219,   222,   223,   226,   229,   230,
     234,   239,   240,   247,   248,   253,   251,   258,   261,   264,
     265,   268,   269,   270,   271,   272,   287,   290,   287,   295,
     298,   299,   294,   303,   307,   308,   311,   312,   315,   316,
     319,   320,   327,   328,   327,   332,   333,   337,   336,   340,
     339,   343,   344,   342,   347,   348,   346,   352,   353,   352,
     357,   358,   362,   361,   365,   364,   368,   367,   371,   370,
     376,   378,   380,   375,   387,   389,   386,   400,   399,   410,
     412,   415,   418,   421,   422,   425,   426,   427,   428,   429,
     430,   434,   435,   433,   440,   441,   439,   444,   446,   450,
     451,   449,   454,   455,   453,   469,   470,   468,   474,   475,
     479,   478,   487,   488,   489,   490,   493,   494,   497,   500,
     503,   506,   509,   512,   513,   514,   515,   516,   517,   518,
     519,   520,   521,   522,   523,   524,   525,   526,   527,   528,
     529,   530,   531,   532,   533,   534,   535,   536,   537,   538,
     539,   540,   541,   542,   543,   544,   545,   546,   547,   548,
     549,   550,   551,   552,   553,   555,   556,   557,   558,   559,
     560,   561,   562,   563,   564,   565,   568,   569,   570,   571,
     572,   573,   574,   575,   576,   577,   578,   579,   580,   581,
     582,   583,   584,   585,   586,   587,   588,   589,   590,   591,
     592,   593,   594,   595,   596,   597,   598,   599,   600,   601,
     602,   603,   604,   605,   606,   607,   608,   609,   611,   612,
     613,   614,   615,   616,   617,   618,   619,   620,   621,   622,
     623,   624,   627,   628,   631,   632,   635,   636,   639,   643,
     646,   647,   646,   655,   656,   657,   655,   665,   671,   677,
     678,   680,   677,   690,   694,   697,   703,   704,   705,   706,
     707,   708,   709,   710,   703,   721,   722,   723,   724,   725,
     726,   727,   728,   721,   739,   740,   741,   742,   743,   744,
     745,   746,   747,   748,   749,   750,   751,   752,   753,   739,
     765,   766,   767,   768,   769,   770,   771,   772,   773,   774,
     775,   776,   777,   778,   779,   765,   791,   792,   795,   796,
     797,   795,   805,   809,   813,   817,   823,   829,   829,   837,
     837,   845,   846,   847,   845,   854,   855,   856,   854,   863,
     864,   865,   866,   863,   873,   874,   875,   876,   873,   883,
     884,   887,   888,   891,   892,   895,   896,   899,   900,   903,
     904,   907,   908,   911,   912,   915,   916,   919,   920,   923,
     924,   927,   928,   931,   932,   935,   936,   939,   940,   943,
     944,   947,   948,   951,   952,   955,   956,   959,   960,   963,
     964,   967,   968,   971,   972,   975,   976,   979,   980,   983,
     984,   987,   988,   991,   992,   995,   996,   999,  1000,  1003,
    1004,  1007,  1008,  1011,  1012,  1015,  1016,  1019,  1020,  1023,
    1024,  1027,  1028,  1031,  1032,  1035,  1036,  1039,  1040,  1043,
    1044,  1047,  1048,  1053,  1054,  1055,  1053,  1064,  1064,  1072,
    1073,  1072,  1081,  1082,  1083,  1081,  1091,  1092,  1093,  1091,
    1101,  1102,  1103,  1104,  1105,  1106,  1101,  1118,  1118,  1126,
    1128,  1126,  1138,  1139,  1142,  1143,  1146,  1147,  1150,  1151,
    1154,  1155,  1158,  1159,  1162,  1163,  1166,  1167,  1170,  1171,
    1174,  1175,  1178,  1179,  1182,  1183
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
  "mfvec2iValue", "sfvec2iValues", YY_NULL
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
     335,   336,   337,   338,   339,   340,   341,   342,    91,    93,
     123,   125,    46
};
# endif

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

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
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

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
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

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -286
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

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
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

#define yypact_value_is_default(yystate) \
  ((yystate) == (-286))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

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

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

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
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (YYID (N))                                                     \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (YYID (0))
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])



/* This macro is provided for backward compatibility. */

#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
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
  FILE *yyo = yyoutput;
  YYUSE (yyo);
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
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
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
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
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
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
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
                yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
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

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

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
/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

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
  int yytoken;
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

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

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
/* Line 1787 of yacc.c  */
#line 218 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { if(SKEL->verifyHeader((yyvsp[(1) - (1)].stringVal)) == false) { YYABORT; } }
    break;

  case 4:
/* Line 1787 of yacc.c  */
#line 219 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { if(SKEL->checkHeader() == true) { YYABORT; } }
    break;

  case 5:
/* Line 1787 of yacc.c  */
#line 222 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->profileElement((yyvsp[(2) - (2)].stringVal)); }
    break;

  case 10:
/* Line 1787 of yacc.c  */
#line 236 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->componentElement((yyvsp[(2) - (2)].stringVal)); }
    break;

  case 15:
/* Line 1787 of yacc.c  */
#line 253 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = (yyvsp[(2) - (2)].stringVal); }
    break;

  case 16:
/* Line 1787 of yacc.c  */
#line 255 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->metaElement(SKEL->_tmpString1.c_str(), (yyvsp[(4) - (4)].stringVal)); }
    break;

  case 26:
/* Line 1787 of yacc.c  */
#line 287 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = (yyvsp[(1) - (1)].stringVal); 
                            SKEL->_tmpBitVector1 = 
                                TypeTraits<BitVector>::BitsClear; }
    break;

  case 27:
/* Line 1787 of yacc.c  */
#line 290 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginNode(SKEL->_tmpString1.c_str(), 
                                            0,
                                            SKEL->_tmpBitVector1     ); }
    break;

  case 29:
/* Line 1787 of yacc.c  */
#line 295 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = (yyvsp[(2) - (2)].stringVal); 
                            SKEL->_tmpBitVector1 = 
                                TypeTraits<BitVector>::BitsClear; }
    break;

  case 30:
/* Line 1787 of yacc.c  */
#line 298 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString2 = (yyvsp[(4) - (4)].stringVal); }
    break;

  case 31:
/* Line 1787 of yacc.c  */
#line 299 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginNode(SKEL->_tmpString2.c_str(), 
                                            SKEL->_tmpString1.c_str(),
                                            SKEL->_tmpBitVector1     ); }
    break;

  case 33:
/* Line 1787 of yacc.c  */
#line 304 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->use((yyvsp[(2) - (2)].stringVal)); }
    break;

  case 38:
/* Line 1787 of yacc.c  */
#line 315 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpBitVector1 |= FCLocal::Cluster; }
    break;

  case 39:
/* Line 1787 of yacc.c  */
#line 316 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpBitVector1 |= FCLocal::MT;      }
    break;

  case 42:
/* Line 1787 of yacc.c  */
#line 327 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginProto((yyvsp[(2) - (2)].stringVal)); }
    break;

  case 43:
/* Line 1787 of yacc.c  */
#line 328 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endProtoInterface(); }
    break;

  case 44:
/* Line 1787 of yacc.c  */
#line 329 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endProto(); }
    break;

  case 47:
/* Line 1787 of yacc.c  */
#line 337 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); }
    break;

  case 48:
/* Line 1787 of yacc.c  */
#line 338 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginEventInDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); SKEL->endEventDecl(); }
    break;

  case 49:
/* Line 1787 of yacc.c  */
#line 340 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); }
    break;

  case 50:
/* Line 1787 of yacc.c  */
#line 341 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginEventOutDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); SKEL->endEventDecl(); }
    break;

  case 51:
/* Line 1787 of yacc.c  */
#line 343 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); }
    break;

  case 52:
/* Line 1787 of yacc.c  */
#line 344 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginFieldDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); SKEL->getLexer()->expectType((yyvsp[(2) - (4)].intVal)); }
    break;

  case 53:
/* Line 1787 of yacc.c  */
#line 345 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endFieldDecl(); }
    break;

  case 54:
/* Line 1787 of yacc.c  */
#line 347 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); }
    break;

  case 55:
/* Line 1787 of yacc.c  */
#line 348 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginExposedFieldDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); SKEL->getLexer()->expectType((yyvsp[(2) - (4)].intVal)); }
    break;

  case 56:
/* Line 1787 of yacc.c  */
#line 349 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endExposedFieldDecl(); }
    break;

  case 57:
/* Line 1787 of yacc.c  */
#line 352 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginExternProto((yyvsp[(2) - (2)].stringVal)); }
    break;

  case 58:
/* Line 1787 of yacc.c  */
#line 353 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endExternProtoInterface(); }
    break;

  case 59:
/* Line 1787 of yacc.c  */
#line 354 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endExternProto(); }
    break;

  case 62:
/* Line 1787 of yacc.c  */
#line 362 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); }
    break;

  case 63:
/* Line 1787 of yacc.c  */
#line 363 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->addExternEventInDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); }
    break;

  case 64:
/* Line 1787 of yacc.c  */
#line 365 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); }
    break;

  case 65:
/* Line 1787 of yacc.c  */
#line 366 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->addExternEventOutDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); }
    break;

  case 66:
/* Line 1787 of yacc.c  */
#line 368 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); }
    break;

  case 67:
/* Line 1787 of yacc.c  */
#line 369 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->addExternFieldDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); }
    break;

  case 68:
/* Line 1787 of yacc.c  */
#line 371 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); }
    break;

  case 69:
/* Line 1787 of yacc.c  */
#line 372 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->addExternExposedFieldDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); }
    break;

  case 70:
/* Line 1787 of yacc.c  */
#line 376 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = (yyvsp[(2) - (2)].stringVal); }
    break;

  case 71:
/* Line 1787 of yacc.c  */
#line 378 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString2 = (yyvsp[(5) - (5)].stringVal); }
    break;

  case 72:
/* Line 1787 of yacc.c  */
#line 380 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString3 = (yyvsp[(8) - (8)].stringVal); }
    break;

  case 73:
/* Line 1787 of yacc.c  */
#line 383 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->addRoute(SKEL->_tmpString1.c_str(), SKEL->_tmpString2.c_str(), SKEL->_tmpString3.c_str(), (yyvsp[(11) - (11)].stringVal)); }
    break;

  case 74:
/* Line 1787 of yacc.c  */
#line 387 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = (yyvsp[(2) - (2)].stringVal); }
    break;

  case 75:
/* Line 1787 of yacc.c  */
#line 389 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString2 = (yyvsp[(5) - (5)].stringVal); }
    break;

  case 76:
/* Line 1787 of yacc.c  */
#line 391 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        if ((yyvsp[(7) - (7)].stringVal) != 0)
            SKEL->importElement(SKEL->_tmpString1.c_str(), SKEL->_tmpString2.c_str(), (yyvsp[(7) - (7)].stringVal));
        else
            SKEL->importElement(SKEL->_tmpString1.c_str(), SKEL->_tmpString2.c_str(), 0);
    }
    break;

  case 77:
/* Line 1787 of yacc.c  */
#line 400 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = (yyvsp[(2) - (2)].stringVal); }
    break;

  case 78:
/* Line 1787 of yacc.c  */
#line 402 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        if ((yyvsp[(4) - (4)].stringVal) != 0)
            SKEL->exportElement(SKEL->_tmpString1.c_str(), (yyvsp[(4) - (4)].stringVal));
        else
            SKEL->exportElement(SKEL->_tmpString1.c_str(), 0);
    }
    break;

  case 79:
/* Line 1787 of yacc.c  */
#line 411 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { (yyval.stringVal) = (yyvsp[(2) - (2)].stringVal); }
    break;

  case 80:
/* Line 1787 of yacc.c  */
#line 412 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { (yyval.stringVal) = 0; }
    break;

  case 82:
/* Line 1787 of yacc.c  */
#line 418 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endNode(); }
    break;

  case 91:
/* Line 1787 of yacc.c  */
#line 434 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); }
    break;

  case 92:
/* Line 1787 of yacc.c  */
#line 435 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginEventInDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); }
    break;

  case 93:
/* Line 1787 of yacc.c  */
#line 436 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endEventDecl(); }
    break;

  case 94:
/* Line 1787 of yacc.c  */
#line 440 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); }
    break;

  case 95:
/* Line 1787 of yacc.c  */
#line 441 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginEventOutDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); }
    break;

  case 96:
/* Line 1787 of yacc.c  */
#line 442 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endEventDecl(); }
    break;

  case 98:
/* Line 1787 of yacc.c  */
#line 446 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->is((yyvsp[(2) - (2)].stringVal)); }
    break;

  case 99:
/* Line 1787 of yacc.c  */
#line 450 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); }
    break;

  case 100:
/* Line 1787 of yacc.c  */
#line 451 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginFieldDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); SKEL->getLexer()->expectType((yyvsp[(2) - (4)].intVal)); }
    break;

  case 101:
/* Line 1787 of yacc.c  */
#line 452 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endFieldDecl(); }
    break;

  case 102:
/* Line 1787 of yacc.c  */
#line 454 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); }
    break;

  case 103:
/* Line 1787 of yacc.c  */
#line 455 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { 
               SKEL->beginFieldDecl(SKEL->_tmpString1.c_str(), 0, (yyvsp[(4) - (4)].stringVal)); 

               Int32 iFieldTypeId = SKEL->getFieldType((yyvsp[(4) - (4)].stringVal));

               if(SKEL->getMapFieldTypes() == true)
                 iFieldTypeId = SKEL->mapExtIntFieldType((yyvsp[(4) - (4)].stringVal), iFieldTypeId);

               SKEL->getLexer()->expectType(iFieldTypeId);
             }
    break;

  case 104:
/* Line 1787 of yacc.c  */
#line 465 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endFieldDecl(); }
    break;

  case 105:
/* Line 1787 of yacc.c  */
#line 469 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); }
    break;

  case 106:
/* Line 1787 of yacc.c  */
#line 470 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginExposedFieldDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); SKEL->getLexer()->expectType((yyvsp[(2) - (4)].intVal)); }
    break;

  case 107:
/* Line 1787 of yacc.c  */
#line 471 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endExposedFieldDecl(); }
    break;

  case 109:
/* Line 1787 of yacc.c  */
#line 475 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->is((yyvsp[(3) - (3)].stringVal)); }
    break;

  case 110:
/* Line 1787 of yacc.c  */
#line 479 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        Int32 iFieldTypeId = SKEL->getFieldType((yyvsp[(1) - (1)].stringVal));
        if (SKEL->getMapFieldTypes() == true)
            iFieldTypeId = SKEL->mapExtIntFieldType((yyvsp[(1) - (1)].stringVal), iFieldTypeId);
        SKEL->getLexer()->expectType(iFieldTypeId);
        SKEL->beginField((yyvsp[(1) - (1)].stringVal), iFieldTypeId);
    }
    break;

  case 111:
/* Line 1787 of yacc.c  */
#line 486 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endField(); }
    break;

  case 117:
/* Line 1787 of yacc.c  */
#line 494 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->is((yyvsp[(3) - (3)].stringVal)); }
    break;

  case 232:
/* Line 1787 of yacc.c  */
#line 627 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { (yyval.intVal) = (yyvsp[(1) - (1)].intVal); }
    break;

  case 233:
/* Line 1787 of yacc.c  */
#line 628 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { (yyval.intVal) = (yyvsp[(1) - (1)].intVal); }
    break;

  case 234:
/* Line 1787 of yacc.c  */
#line 631 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { (yyval.doubleVal) = (yyvsp[(1) - (1)].intVal); }
    break;

  case 235:
/* Line 1787 of yacc.c  */
#line 632 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { (yyval.doubleVal) = (yyvsp[(1) - (1)].doubleVal); }
    break;

  case 236:
/* Line 1787 of yacc.c  */
#line 635 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { (yyval.floatVal) = static_cast<float>((yyvsp[(1) - (1)].intVal)); }
    break;

  case 237:
/* Line 1787 of yacc.c  */
#line 636 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { (yyval.floatVal) = static_cast<float>((yyvsp[(1) - (1)].doubleVal)); }
    break;

  case 238:
/* Line 1787 of yacc.c  */
#line 640 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->addBoolValue((yyvsp[(1) - (1)].boolVal));
    }
    break;

  case 239:
/* Line 1787 of yacc.c  */
#line 643 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->addFieldValue((yyvsp[(1) - (1)].stringVal)); }
    break;

  case 240:
/* Line 1787 of yacc.c  */
#line 646 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); }
    break;

  case 241:
/* Line 1787 of yacc.c  */
#line 647 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); }
    break;

  case 242:
/* Line 1787 of yacc.c  */
#line 649 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addColorValue(Color3f((yyvsp[(1) - (5)].floatVal), (yyvsp[(3) - (5)].floatVal), (yyvsp[(5) - (5)].floatVal)));
    }
    break;

  case 243:
/* Line 1787 of yacc.c  */
#line 655 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); }
    break;

  case 244:
/* Line 1787 of yacc.c  */
#line 656 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); }
    break;

  case 245:
/* Line 1787 of yacc.c  */
#line 657 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); }
    break;

  case 246:
/* Line 1787 of yacc.c  */
#line 659 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addColorRGBAValue(Color4f((yyvsp[(1) - (7)].floatVal), (yyvsp[(3) - (7)].floatVal), (yyvsp[(5) - (7)].floatVal), (yyvsp[(7) - (7)].floatVal)));
    }
    break;

  case 247:
/* Line 1787 of yacc.c  */
#line 666 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->addDoubleValue((yyvsp[(1) - (1)].doubleVal));
    }
    break;

  case 248:
/* Line 1787 of yacc.c  */
#line 672 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->addFloatValue((yyvsp[(1) - (1)].floatVal));
    }
    break;

  case 249:
/* Line 1787 of yacc.c  */
#line 677 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); }
    break;

  case 250:
/* Line 1787 of yacc.c  */
#line 678 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); }
    break;

  case 251:
/* Line 1787 of yacc.c  */
#line 680 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->beginImage((yyvsp[(1) - (5)].intVal), (yyvsp[(3) - (5)].intVal), (yyvsp[(5) - (5)].intVal));
    }
    break;

  case 252:
/* Line 1787 of yacc.c  */
#line 685 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->endImage();
    }
    break;

  case 253:
/* Line 1787 of yacc.c  */
#line 691 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->addImagePixel((yyvsp[(2) - (2)].intVal));
    }
    break;

  case 255:
/* Line 1787 of yacc.c  */
#line 698 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->addInt32Value((yyvsp[(1) - (1)].intVal));
    }
    break;

  case 256:
/* Line 1787 of yacc.c  */
#line 703 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); }
    break;

  case 257:
/* Line 1787 of yacc.c  */
#line 704 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); }
    break;

  case 258:
/* Line 1787 of yacc.c  */
#line 705 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); }
    break;

  case 259:
/* Line 1787 of yacc.c  */
#line 706 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); }
    break;

  case 260:
/* Line 1787 of yacc.c  */
#line 707 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); }
    break;

  case 261:
/* Line 1787 of yacc.c  */
#line 708 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); }
    break;

  case 262:
/* Line 1787 of yacc.c  */
#line 709 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); }
    break;

  case 263:
/* Line 1787 of yacc.c  */
#line 710 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); }
    break;

  case 264:
/* Line 1787 of yacc.c  */
#line 712 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addMatrix3dValue(
            (yyvsp[(1) - (17)].doubleVal),  (yyvsp[(7) - (17)].doubleVal), (yyvsp[(13) - (17)].doubleVal),
            (yyvsp[(3) - (17)].doubleVal),  (yyvsp[(9) - (17)].doubleVal), (yyvsp[(15) - (17)].doubleVal),
            (yyvsp[(5) - (17)].doubleVal), (yyvsp[(11) - (17)].doubleVal), (yyvsp[(17) - (17)].doubleVal));
    }
    break;

  case 265:
/* Line 1787 of yacc.c  */
#line 721 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); }
    break;

  case 266:
/* Line 1787 of yacc.c  */
#line 722 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); }
    break;

  case 267:
/* Line 1787 of yacc.c  */
#line 723 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); }
    break;

  case 268:
/* Line 1787 of yacc.c  */
#line 724 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); }
    break;

  case 269:
/* Line 1787 of yacc.c  */
#line 725 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); }
    break;

  case 270:
/* Line 1787 of yacc.c  */
#line 726 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); }
    break;

  case 271:
/* Line 1787 of yacc.c  */
#line 727 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); }
    break;

  case 272:
/* Line 1787 of yacc.c  */
#line 728 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); }
    break;

  case 273:
/* Line 1787 of yacc.c  */
#line 730 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addMatrix3fValue(
            (yyvsp[(1) - (17)].floatVal),  (yyvsp[(7) - (17)].floatVal), (yyvsp[(13) - (17)].floatVal),
            (yyvsp[(3) - (17)].floatVal),  (yyvsp[(9) - (17)].floatVal), (yyvsp[(15) - (17)].floatVal),
            (yyvsp[(5) - (17)].floatVal), (yyvsp[(11) - (17)].floatVal), (yyvsp[(17) - (17)].floatVal));
    }
    break;

  case 274:
/* Line 1787 of yacc.c  */
#line 739 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); }
    break;

  case 275:
/* Line 1787 of yacc.c  */
#line 740 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); }
    break;

  case 276:
/* Line 1787 of yacc.c  */
#line 741 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); }
    break;

  case 277:
/* Line 1787 of yacc.c  */
#line 742 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); }
    break;

  case 278:
/* Line 1787 of yacc.c  */
#line 743 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); }
    break;

  case 279:
/* Line 1787 of yacc.c  */
#line 744 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); }
    break;

  case 280:
/* Line 1787 of yacc.c  */
#line 745 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); }
    break;

  case 281:
/* Line 1787 of yacc.c  */
#line 746 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); }
    break;

  case 282:
/* Line 1787 of yacc.c  */
#line 747 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); }
    break;

  case 283:
/* Line 1787 of yacc.c  */
#line 748 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); }
    break;

  case 284:
/* Line 1787 of yacc.c  */
#line 749 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); }
    break;

  case 285:
/* Line 1787 of yacc.c  */
#line 750 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); }
    break;

  case 286:
/* Line 1787 of yacc.c  */
#line 751 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); }
    break;

  case 287:
/* Line 1787 of yacc.c  */
#line 752 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); }
    break;

  case 288:
/* Line 1787 of yacc.c  */
#line 753 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); }
    break;

  case 289:
/* Line 1787 of yacc.c  */
#line 755 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addMatrix4dValue(Matrix4d(
            (yyvsp[(1) - (31)].doubleVal),  (yyvsp[(9) - (31)].doubleVal), (yyvsp[(17) - (31)].doubleVal), (yyvsp[(25) - (31)].doubleVal),
            (yyvsp[(3) - (31)].doubleVal), (yyvsp[(11) - (31)].doubleVal), (yyvsp[(19) - (31)].doubleVal), (yyvsp[(27) - (31)].doubleVal),
            (yyvsp[(5) - (31)].doubleVal), (yyvsp[(13) - (31)].doubleVal), (yyvsp[(21) - (31)].doubleVal), (yyvsp[(29) - (31)].doubleVal),
            (yyvsp[(7) - (31)].doubleVal), (yyvsp[(15) - (31)].doubleVal), (yyvsp[(23) - (31)].doubleVal), (yyvsp[(31) - (31)].doubleVal)));
    }
    break;

  case 290:
/* Line 1787 of yacc.c  */
#line 765 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); }
    break;

  case 291:
/* Line 1787 of yacc.c  */
#line 766 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); }
    break;

  case 292:
/* Line 1787 of yacc.c  */
#line 767 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); }
    break;

  case 293:
/* Line 1787 of yacc.c  */
#line 768 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); }
    break;

  case 294:
/* Line 1787 of yacc.c  */
#line 769 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); }
    break;

  case 295:
/* Line 1787 of yacc.c  */
#line 770 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); }
    break;

  case 296:
/* Line 1787 of yacc.c  */
#line 771 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); }
    break;

  case 297:
/* Line 1787 of yacc.c  */
#line 772 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); }
    break;

  case 298:
/* Line 1787 of yacc.c  */
#line 773 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); }
    break;

  case 299:
/* Line 1787 of yacc.c  */
#line 774 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); }
    break;

  case 300:
/* Line 1787 of yacc.c  */
#line 775 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); }
    break;

  case 301:
/* Line 1787 of yacc.c  */
#line 776 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); }
    break;

  case 302:
/* Line 1787 of yacc.c  */
#line 777 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); }
    break;

  case 303:
/* Line 1787 of yacc.c  */
#line 778 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); }
    break;

  case 304:
/* Line 1787 of yacc.c  */
#line 779 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); }
    break;

  case 305:
/* Line 1787 of yacc.c  */
#line 781 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addMatrix4fValue(Matrix4f(
            (yyvsp[(1) - (31)].floatVal),  (yyvsp[(9) - (31)].floatVal), (yyvsp[(17) - (31)].floatVal), (yyvsp[(25) - (31)].floatVal),
            (yyvsp[(3) - (31)].floatVal), (yyvsp[(11) - (31)].floatVal), (yyvsp[(19) - (31)].floatVal), (yyvsp[(27) - (31)].floatVal),
            (yyvsp[(5) - (31)].floatVal), (yyvsp[(13) - (31)].floatVal), (yyvsp[(21) - (31)].floatVal), (yyvsp[(29) - (31)].floatVal),
            (yyvsp[(7) - (31)].floatVal), (yyvsp[(15) - (31)].floatVal), (yyvsp[(23) - (31)].floatVal), (yyvsp[(31) - (31)].floatVal)));
    }
    break;

  case 307:
/* Line 1787 of yacc.c  */
#line 792 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->nullNode(); }
    break;

  case 308:
/* Line 1787 of yacc.c  */
#line 795 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); }
    break;

  case 309:
/* Line 1787 of yacc.c  */
#line 796 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); }
    break;

  case 310:
/* Line 1787 of yacc.c  */
#line 797 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); }
    break;

  case 311:
/* Line 1787 of yacc.c  */
#line 799 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addRotationValue(Vec3f((yyvsp[(1) - (7)].floatVal), (yyvsp[(3) - (7)].floatVal), (yyvsp[(5) - (7)].floatVal)), (yyvsp[(7) - (7)].floatVal));
    }
    break;

  case 312:
/* Line 1787 of yacc.c  */
#line 806 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->addStringValue((yyvsp[(1) - (1)].stringVal));
    }
    break;

  case 313:
/* Line 1787 of yacc.c  */
#line 810 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { /* Not VRML conformant */
        SKEL->addStringValue((yyvsp[(1) - (1)].stringVal));
    }
    break;

  case 314:
/* Line 1787 of yacc.c  */
#line 814 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { /* Not VRML conformant */
        SKEL->addBufferAsStringValue();
    }
    break;

  case 315:
/* Line 1787 of yacc.c  */
#line 818 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { /* Not VRML conformant */
        SKEL->addBufferAsStringValue();
    }
    break;

  case 316:
/* Line 1787 of yacc.c  */
#line 824 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->addTimeValue((yyvsp[(1) - (1)].doubleVal));
    }
    break;

  case 317:
/* Line 1787 of yacc.c  */
#line 829 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); }
    break;

  case 318:
/* Line 1787 of yacc.c  */
#line 831 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addVec2dValue(Vec2d((yyvsp[(1) - (3)].doubleVal), (yyvsp[(3) - (3)].doubleVal)));
    }
    break;

  case 319:
/* Line 1787 of yacc.c  */
#line 837 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); }
    break;

  case 320:
/* Line 1787 of yacc.c  */
#line 839 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addVec2fValue(Vec2f((yyvsp[(1) - (3)].floatVal), (yyvsp[(3) - (3)].floatVal)));
    }
    break;

  case 321:
/* Line 1787 of yacc.c  */
#line 845 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); }
    break;

  case 322:
/* Line 1787 of yacc.c  */
#line 846 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); }
    break;

  case 323:
/* Line 1787 of yacc.c  */
#line 847 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); }
    break;

  case 324:
/* Line 1787 of yacc.c  */
#line 848 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addVec3dValue(Vec3d((yyvsp[(1) - (6)].doubleVal), (yyvsp[(3) - (6)].doubleVal), (yyvsp[(5) - (6)].doubleVal)));
    }
    break;

  case 325:
/* Line 1787 of yacc.c  */
#line 854 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); }
    break;

  case 326:
/* Line 1787 of yacc.c  */
#line 855 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); }
    break;

  case 327:
/* Line 1787 of yacc.c  */
#line 856 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); }
    break;

  case 328:
/* Line 1787 of yacc.c  */
#line 857 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addVec3fValue(Vec3f((yyvsp[(1) - (6)].floatVal), (yyvsp[(3) - (6)].floatVal), (yyvsp[(5) - (6)].floatVal)));
    }
    break;

  case 329:
/* Line 1787 of yacc.c  */
#line 863 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); }
    break;

  case 330:
/* Line 1787 of yacc.c  */
#line 864 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); }
    break;

  case 331:
/* Line 1787 of yacc.c  */
#line 865 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); }
    break;

  case 332:
/* Line 1787 of yacc.c  */
#line 866 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); }
    break;

  case 333:
/* Line 1787 of yacc.c  */
#line 867 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addVec4dValue(Vec4d((yyvsp[(1) - (8)].doubleVal), (yyvsp[(3) - (8)].doubleVal), (yyvsp[(5) - (8)].doubleVal), (yyvsp[(7) - (8)].doubleVal)));
    }
    break;

  case 334:
/* Line 1787 of yacc.c  */
#line 873 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); }
    break;

  case 335:
/* Line 1787 of yacc.c  */
#line 874 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); }
    break;

  case 336:
/* Line 1787 of yacc.c  */
#line 875 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); }
    break;

  case 337:
/* Line 1787 of yacc.c  */
#line 876 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); }
    break;

  case 338:
/* Line 1787 of yacc.c  */
#line 877 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addVec4fValue(Vec4f((yyvsp[(1) - (8)].floatVal), (yyvsp[(3) - (8)].floatVal), (yyvsp[(5) - (8)].floatVal), (yyvsp[(7) - (8)].floatVal)));
    }
    break;

  case 423:
/* Line 1787 of yacc.c  */
#line 1053 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); }
    break;

  case 424:
/* Line 1787 of yacc.c  */
#line 1054 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); }
    break;

  case 425:
/* Line 1787 of yacc.c  */
#line 1055 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); }
    break;

  case 426:
/* Line 1787 of yacc.c  */
#line 1057 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addColor4iValue(Color4ub(static_cast<UInt8>((yyvsp[(1) - (7)].intVal)), static_cast<UInt8>((yyvsp[(3) - (7)].intVal)),
                                       static_cast<UInt8>((yyvsp[(5) - (7)].intVal)), static_cast<UInt8>((yyvsp[(7) - (7)].intVal))));
    }
    break;

  case 427:
/* Line 1787 of yacc.c  */
#line 1064 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); }
    break;

  case 428:
/* Line 1787 of yacc.c  */
#line 1066 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addPnt2fValue(Pnt2f((yyvsp[(1) - (3)].floatVal), (yyvsp[(3) - (3)].floatVal)));
    }
    break;

  case 429:
/* Line 1787 of yacc.c  */
#line 1072 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); }
    break;

  case 430:
/* Line 1787 of yacc.c  */
#line 1073 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); }
    break;

  case 431:
/* Line 1787 of yacc.c  */
#line 1075 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addPnt3fValue(Pnt3f((yyvsp[(1) - (5)].floatVal), (yyvsp[(3) - (5)].floatVal), (yyvsp[(5) - (5)].floatVal)));
    }
    break;

  case 432:
/* Line 1787 of yacc.c  */
#line 1081 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); }
    break;

  case 433:
/* Line 1787 of yacc.c  */
#line 1082 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); }
    break;

  case 434:
/* Line 1787 of yacc.c  */
#line 1083 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); }
    break;

  case 435:
/* Line 1787 of yacc.c  */
#line 1085 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addPnt4fValue(Pnt4f((yyvsp[(1) - (7)].floatVal), (yyvsp[(3) - (7)].floatVal), (yyvsp[(5) - (7)].floatVal), (yyvsp[(7) - (7)].floatVal)));
    }
    break;

  case 436:
/* Line 1787 of yacc.c  */
#line 1091 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); }
    break;

  case 437:
/* Line 1787 of yacc.c  */
#line 1092 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); }
    break;

  case 438:
/* Line 1787 of yacc.c  */
#line 1093 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); }
    break;

  case 439:
/* Line 1787 of yacc.c  */
#line 1095 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addPlaneValue(Plane(Vec3f((yyvsp[(1) - (7)].floatVal), (yyvsp[(3) - (7)].floatVal), (yyvsp[(5) - (7)].floatVal)), (yyvsp[(7) - (7)].floatVal)));
    }
    break;

  case 440:
/* Line 1787 of yacc.c  */
#line 1101 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue();  }
    break;

  case 441:
/* Line 1787 of yacc.c  */
#line 1102 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); }
    break;

  case 442:
/* Line 1787 of yacc.c  */
#line 1103 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); }
    break;

  case 443:
/* Line 1787 of yacc.c  */
#line 1104 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); }
    break;

  case 444:
/* Line 1787 of yacc.c  */
#line 1105 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); }
    break;

  case 445:
/* Line 1787 of yacc.c  */
#line 1106 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); }
    break;

  case 446:
/* Line 1787 of yacc.c  */
#line 1108 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        BoxVolume bv((yyvsp[(3) - (13)].floatVal), (yyvsp[(5) - (13)].floatVal), (yyvsp[(7) - (13)].floatVal), (yyvsp[(9) - (13)].floatVal), (yyvsp[(11) - (13)].floatVal), (yyvsp[(13) - (13)].floatVal));
        
        bv.setState((yyvsp[(1) - (13)].intVal));

        SKEL->addVolumeValue(bv);
    }
    break;

  case 447:
/* Line 1787 of yacc.c  */
#line 1118 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); }
    break;

  case 448:
/* Line 1787 of yacc.c  */
#line 1120 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addVec2iValue(Vec2i((yyvsp[(1) - (3)].intVal), (yyvsp[(3) - (3)].intVal)));
    }
    break;

  case 449:
/* Line 1787 of yacc.c  */
#line 1126 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); }
    break;

  case 450:
/* Line 1787 of yacc.c  */
#line 1128 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
    }
    break;

  case 451:
/* Line 1787 of yacc.c  */
#line 1132 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addVec3iValue(Vec3i((yyvsp[(1) - (5)].intVal), (yyvsp[(3) - (5)].intVal), (yyvsp[(5) - (5)].intVal)));
    }
    break;


/* Line 1787 of yacc.c  */
#line 3721 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp"
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
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
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
        yyerror (yymsgp);
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
		      yytoken, &yylval);
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
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

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

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
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
                  yytoken, &yylval);
    }
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


/* Line 2048 of yacc.c  */
#line 1185 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"


int OSGScanParseSkel_lex(YYSTYPE *lvalp, void *pSkel)
{
    return SKEL->lex(lvalp);
}

